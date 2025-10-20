#include "matchcompiler.h"
#include <string>
#include <cstring>
#include "errorlogger.h"
#include "token.h"
#if defined(__clang__)
#include "config.h"
#define MAYBE_UNUSED [[maybe_unused]]
SUPPRESS_WARNING_CLANG_PUSH("-Wc++17-attribute-extensions")
#else
#define MAYBE_UNUSED
#endif
// pattern: requires
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("requires")))
        return false;
    return true;
}
// pattern: %oror%|&&|requires %name%|(
MAYBE_UNUSED static inline bool match2(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->str() == MatchCompiler::makeConstString("requires"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: requires (
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("requires")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) {
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %name% :: %name%
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %name% <
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: template < >
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    return true;
}
// pattern: > template <
MAYBE_UNUSED static inline bool match8(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: >|%name% ::
MAYBE_UNUSED static inline bool match9(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || tok->isName()))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: class|struct|union %name% <|{|:|;|::
MAYBE_UNUSED static inline bool match10(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString(";")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: %name% ...
template<class T> MAYBE_UNUSED static inline T * findmatch11(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !tok->isName())
        continue;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: =|;
MAYBE_UNUSED static inline bool match12(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: ;|{
MAYBE_UNUSED static inline bool match13(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: (|[
MAYBE_UNUSED static inline bool match14(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: :: ~
MAYBE_UNUSED static inline bool match15(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~")))
        return false;
    return true;
}
// pattern: %name% ::
MAYBE_UNUSED static inline bool match16(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: > ::
MAYBE_UNUSED static inline bool match17(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: [;{}]
MAYBE_UNUSED static inline bool match18(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    return true;
}
// pattern: ;
template<class T> MAYBE_UNUSED static inline T * findmatch19(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: ( {
MAYBE_UNUSED static inline bool match20(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: try {
MAYBE_UNUSED static inline bool match21(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("try")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } catch (
MAYBE_UNUSED static inline bool match22(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("catch")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: typedef|typename
MAYBE_UNUSED static inline bool match23(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef")) || (tok->str() == MatchCompiler::makeConstString("typename"))))
        return false;
    return true;
}
// pattern: %type% ::
MAYBE_UNUSED static inline bool match24(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: %type% <
MAYBE_UNUSED static inline bool match25(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: template
MAYBE_UNUSED static inline bool match26(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    return true;
}
// pattern: ;
MAYBE_UNUSED static inline bool match27(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: {
MAYBE_UNUSED static inline bool match28(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: >|%type%
MAYBE_UNUSED static inline bool match29(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || (tok->isName() && tok->varId() == 0U)))
        return false;
    return true;
}
// pattern: } ;
MAYBE_UNUSED static inline bool match30(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: operator <
MAYBE_UNUSED static inline bool match31(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: %type%
MAYBE_UNUSED static inline bool match32(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: *| %type%|%num% ;
MAYBE_UNUSED static inline bool match33(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (!tok || !((tok->isName() && tok->varId() == 0U) || tok->isNumber()))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: *| %type% . %type% ;
MAYBE_UNUSED static inline bool match34(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: (|{
MAYBE_UNUSED static inline bool match35(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: < typename
MAYBE_UNUSED static inline bool match36(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("typename")))
        return false;
    return true;
}
// pattern: <|, %type% <
MAYBE_UNUSED static inline bool match37(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: < %type%
MAYBE_UNUSED static inline bool match38(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: %var% <
MAYBE_UNUSED static inline bool match39(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: template <
MAYBE_UNUSED static inline bool match40(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: >|>>|>>=
MAYBE_UNUSED static inline bool match41(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>")) || (tok->str() == MatchCompiler::makeConstString(">>="))))
        return false;
    return true;
}
// pattern: const|volatile
MAYBE_UNUSED static inline bool match42(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        return false;
    return true;
}
// pattern: struct|union
MAYBE_UNUSED static inline bool match43(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    return true;
}
// pattern: & ::| %name%
MAYBE_UNUSED static inline bool match44(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: ...
MAYBE_UNUSED static inline bool match45(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")))
        return false;
    return true;
}
// pattern: <|,|::
MAYBE_UNUSED static inline bool match46(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: >|&|&&|*
MAYBE_UNUSED static inline bool match47(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: =|?|:
MAYBE_UNUSED static inline bool match48(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: *|&|&&|const
MAYBE_UNUSED static inline bool match49(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        return false;
    return true;
}
// pattern: %num%
MAYBE_UNUSED static inline bool match50(const Token* tok) {
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: %name% (|{
MAYBE_UNUSED static inline bool match51(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: %any% %any%
MAYBE_UNUSED static inline bool match52(const Token* tok) {
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    return true;
}
// pattern: %name%|...|,|=|>
MAYBE_UNUSED static inline bool match53(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: decltype (
MAYBE_UNUSED static inline bool match54(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("decltype")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: {|=|;
MAYBE_UNUSED static inline bool match55(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: %name% (
MAYBE_UNUSED static inline bool match56(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: > (
MAYBE_UNUSED static inline bool match57(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) const
MAYBE_UNUSED static inline bool match58(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    return true;
}
// pattern: typename|class %name% ,|>
MAYBE_UNUSED static inline bool match59(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("typename")) || (tok->str() == MatchCompiler::makeConstString("class"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: %type% %name% ::|<
MAYBE_UNUSED static inline bool match60(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: [,:] private|protected|public %name% ::|<
MAYBE_UNUSED static inline bool match61(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",:", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("private")) || (tok->str() == MatchCompiler::makeConstString("protected")) || (tok->str() == MatchCompiler::makeConstString("public"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: (|{|}|;|=|>|<<|:|.|*|&|return|<|,|!|[ %name% ::|<|(
MAYBE_UNUSED static inline bool match62(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("<<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString(".")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: (|{|}|;|=|<<|:|.|*|&|return|<|,|!|[ :: %name% ::|<|(
MAYBE_UNUSED static inline bool match63(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("<<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString(".")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: template using %name% <
MAYBE_UNUSED static inline bool match64(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: using %name% <
MAYBE_UNUSED static inline bool match65(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: %num%|%str%|%char%|%bool% ,|)
MAYBE_UNUSED static inline bool match66(const Token* tok) {
    if (!tok || !(tok->isNumber() || (tok->tokType() == Token::eString) || (tok->tokType() == Token::eChar) || tok->isBoolean()))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: const| %type% &| %name%| ,|)
MAYBE_UNUSED static inline bool match67(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: const_cast|dynamic_cast|reinterpret_cast|static_cast
MAYBE_UNUSED static inline bool match68(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("const_cast")) || (tok->str() == MatchCompiler::makeConstString("dynamic_cast")) || (tok->str() == MatchCompiler::makeConstString("reinterpret_cast")) || (tok->str() == MatchCompiler::makeConstString("static_cast"))))
        return false;
    return true;
}
// pattern: ,|< %name% <
MAYBE_UNUSED static inline bool match69(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: class|struct
MAYBE_UNUSED static inline bool match70(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    return true;
}
// pattern: {|(|[
MAYBE_UNUSED static inline bool match71(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: typename|class|%type% %name% ,|>
MAYBE_UNUSED static inline bool match72(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("typename")) || (tok->str() == MatchCompiler::makeConstString("class")) || (tok->isName() && tok->varId() == 0U)))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: = !!>
MAYBE_UNUSED static inline bool match73(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString(">"))
        return false;
    return true;
}
// pattern: (|[|{
MAYBE_UNUSED static inline bool match74(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: )|]|}
MAYBE_UNUSED static inline bool match75(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: ;|)|}|]
MAYBE_UNUSED static inline bool match76(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    return true;
}
// pattern: (|{|[
MAYBE_UNUSED static inline bool match77(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: ,|>
MAYBE_UNUSED static inline bool match78(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: [,>;{}]
MAYBE_UNUSED static inline bool match79(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",>;{}", tok->str()[0]))
        return false;
    return true;
}
// pattern: %type% (
MAYBE_UNUSED static inline bool match80(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ;|{|(|using
MAYBE_UNUSED static inline bool match81(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString("using"))))
        return false;
    return true;
}
// pattern: %type% =|;
MAYBE_UNUSED static inline bool match82(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: > friend| class|struct|union %type% :|<|;|{|::
MAYBE_UNUSED static inline bool match83(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("friend"))))
        tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: %type% :: %type%
MAYBE_UNUSED static inline bool match84(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: > :: %type%
MAYBE_UNUSED static inline bool match85(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: > using %name% =
MAYBE_UNUSED static inline bool match86(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: class|struct|union|enum %name%| {
MAYBE_UNUSED static inline bool match87(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    tok = tok->next();
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: {|[|(
MAYBE_UNUSED static inline bool match88(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: ;|{|:
MAYBE_UNUSED static inline bool match89(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: <|(|{
MAYBE_UNUSED static inline bool match90(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: >|)|}
MAYBE_UNUSED static inline bool match91(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: <|, %type% >|,
MAYBE_UNUSED static inline bool match92(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: %name% ... %name%
MAYBE_UNUSED static inline bool match93(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: const
MAYBE_UNUSED static inline bool match94(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    return true;
}
// pattern: . template
MAYBE_UNUSED static inline bool match95(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    return true;
}
// pattern: [|{|(
MAYBE_UNUSED static inline bool match96(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: ]|}|)
MAYBE_UNUSED static inline bool match97(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: }|;|extern
MAYBE_UNUSED static inline bool match98(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern"))))
        return false;
    return true;
}
// pattern: template !!<
MAYBE_UNUSED static inline bool match99(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("<"))
        return false;
    return true;
}
// pattern: class|typename|struct
MAYBE_UNUSED static inline bool match100(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || (tok->str() == MatchCompiler::makeConstString("typename")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    return true;
}
// pattern: .|::
MAYBE_UNUSED static inline bool match101(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: ...|<
MAYBE_UNUSED static inline bool match102(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: %num% ,|>|>>
MAYBE_UNUSED static inline bool match103(const Token* tok) {
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    return true;
}
// pattern: %assign%|%cop%|( %name% %cop%|;|)
MAYBE_UNUSED static inline bool match104(const Token* tok) {
    if (!tok || !(tok->isAssignmentOp() || tok->isConstOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->isConstOp() || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: %name%|::|*
MAYBE_UNUSED static inline bool match105(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: [<,]
MAYBE_UNUSED static inline bool match106(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("<,", tok->str()[0]))
        return false;
    return true;
}
// pattern: const_cast|dynamic_cast|reinterpret_cast|static_cast <
MAYBE_UNUSED static inline bool match107(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("const_cast")) || (tok->str() == MatchCompiler::makeConstString("dynamic_cast")) || (tok->str() == MatchCompiler::makeConstString("reinterpret_cast")) || (tok->str() == MatchCompiler::makeConstString("static_cast"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: <
MAYBE_UNUSED static inline bool match108(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: (|::
MAYBE_UNUSED static inline bool match109(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: > friend class|struct|union
MAYBE_UNUSED static inline bool match110(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("friend")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    return true;
}
// pattern: [:{=;[]),]
MAYBE_UNUSED static inline bool match111(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(":{=;[]),", tok->str()[0]))
        return false;
    return true;
}
// pattern: template|static_cast|const_cast|reinterpret_cast|dynamic_cast
MAYBE_UNUSED static inline bool match112(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("template")) || (tok->str() == MatchCompiler::makeConstString("static_cast")) || (tok->str() == MatchCompiler::makeConstString("const_cast")) || (tok->str() == MatchCompiler::makeConstString("reinterpret_cast")) || (tok->str() == MatchCompiler::makeConstString("dynamic_cast"))))
        return false;
    return true;
}
// pattern: >|>>
MAYBE_UNUSED static inline bool match113(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    return true;
}
// pattern: &
MAYBE_UNUSED static inline bool match114(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    return true;
}
// pattern: } >|,|{
MAYBE_UNUSED static inline bool match115(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: }|;|(|[|]|)|,|?|:|%oror%|return|throw|case
MAYBE_UNUSED static inline bool match116(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("throw")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case"))))
        return false;
    return true;
}
// pattern: %comp%|<<|>>
MAYBE_UNUSED static inline bool match117(const Token* tok) {
    if (!tok || !(tok->isComparisonOp() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("<<")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    return true;
}
// pattern: +|-
MAYBE_UNUSED static inline bool match118(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-"))))
        return false;
    return true;
}
// pattern: [*/%]
MAYBE_UNUSED static inline bool match119(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("*/%", tok->str()[0]))
        return false;
    return true;
}
// pattern: * %num% /
MAYBE_UNUSED static inline bool match120(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("/")))
        return false;
    return true;
}
// pattern: [/%]
MAYBE_UNUSED static inline bool match121(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("/%", tok->str()[0]))
        return false;
    return true;
}
// pattern: [+-]
MAYBE_UNUSED static inline bool match122(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("+-", tok->str()[0]))
        return false;
    return true;
}
// pattern: >>|<<
MAYBE_UNUSED static inline bool match123(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("<<"))))
        return false;
    return true;
}
// pattern: [/%] 0
MAYBE_UNUSED static inline bool match124(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("/%", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    return true;
}
// pattern: >>|<<|&|^|%or%
MAYBE_UNUSED static inline bool match125(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("<<")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^")) || (tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") )))
        return false;
    return true;
}
// pattern: %oror%|&&
MAYBE_UNUSED static inline bool match126(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: - %num% - %num%
MAYBE_UNUSED static inline bool match127(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: - %num% + %num%
MAYBE_UNUSED static inline bool match128(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: [{};)]
MAYBE_UNUSED static inline bool match129(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{};)", tok->str()[0]))
        return false;
    return true;
}
// pattern: ( %char% )
MAYBE_UNUSED static inline bool match130(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eChar))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ( %str% )
MAYBE_UNUSED static inline bool match131(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ( %type% * )
MAYBE_UNUSED static inline bool match132(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ( * )
MAYBE_UNUSED static inline bool match133(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ( %type% )
MAYBE_UNUSED static inline bool match134(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: %num% %comp% %num%
MAYBE_UNUSED static inline bool match135(const Token* tok) {
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !tok->isComparisonOp())
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: (|&&|%oror%|,
MAYBE_UNUSED static inline bool match136(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: )|&&|%oror%|?
MAYBE_UNUSED static inline bool match137(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?"))))
        return false;
    return true;
}
// pattern: ( %type% ) %num%
MAYBE_UNUSED static inline bool match138(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: ( %bool%|%num% )
MAYBE_UNUSED static inline bool match139(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isBoolean() || tok->isNumber()))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: false|0
MAYBE_UNUSED static inline bool match140(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBoolean) && tok->str() == MatchCompiler::makeConstString("false")) || (tok->str() == MatchCompiler::makeConstString("0"))))
        return false;
    return true;
}
// pattern: )|}|]|;|,|:|>
MAYBE_UNUSED static inline bool match141(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: ( %num%|%bool% )
MAYBE_UNUSED static inline bool match142(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isNumber() || tok->isBoolean()))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ( %name% ) ;|)|,|]
MAYBE_UNUSED static inline bool match143(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    return true;
}
// pattern: ( %name% ) %cop%
MAYBE_UNUSED static inline bool match144(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isConstOp())
        return false;
    return true;
}
// pattern: [*&+-~]
MAYBE_UNUSED static inline bool match145(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("*&+-~", tok->str()[0]))
        return false;
    return true;
}
// pattern: (|&&|%oror% %char% %comp% %num% &&|%oror%|)
MAYBE_UNUSED static inline bool match146(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eChar))
        return false;
    tok = tok->next();
    if (!tok || !tok->isComparisonOp())
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: decltype ( %type% { } )
MAYBE_UNUSED static inline bool match147(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("decltype")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: decltype ( %bool%|%num% )
MAYBE_UNUSED static inline bool match148(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("decltype")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isBoolean() || tok->isNumber()))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: char|short|int|long { }
MAYBE_UNUSED static inline bool match149(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("char")) || (tok->str() == MatchCompiler::makeConstString("short")) || (tok->str() == MatchCompiler::makeConstString("int")) || (tok->str() == MatchCompiler::makeConstString("long"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: char|short|int|long ( )
MAYBE_UNUSED static inline bool match150(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("char")) || (tok->str() == MatchCompiler::makeConstString("short")) || (tok->str() == MatchCompiler::makeConstString("int")) || (tok->str() == MatchCompiler::makeConstString("long"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: [(=,] 0 &&
MAYBE_UNUSED static inline bool match151(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(=,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")))
        return false;
    return true;
}
// pattern: [(=,] 1 %oror%
MAYBE_UNUSED static inline bool match152(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(=,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("1")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")))
        return false;
    return true;
}
// pattern: [+-] 0 %cop%|;
MAYBE_UNUSED static inline bool match153(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("+-", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isConstOp() || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: %or% 0 %cop%|;
MAYBE_UNUSED static inline bool match154(const Token* tok) {
    if (!tok || !(tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isConstOp() || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: [;{}] %name% = %name% [+-|] 0 ;
MAYBE_UNUSED static inline bool match155(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("+-|", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: [=([,] 0 [+|]
MAYBE_UNUSED static inline bool match156(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("=([,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("+|", tok->str()[0]))
        return false;
    return true;
}
// pattern: return|case 0 [+|]
MAYBE_UNUSED static inline bool match157(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("+|", tok->str()[0]))
        return false;
    return true;
}
// pattern: [=[(,] 0 * %name%|%num% ,|]|)|;|=|%cop%
MAYBE_UNUSED static inline bool match158(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("=[(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || tok->isNumber()))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || tok->isConstOp()))
        return false;
    return true;
}
// pattern: return|case 0 *|&& %name%|%num% ,|:|;|=|%cop%
MAYBE_UNUSED static inline bool match159(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || tok->isNumber()))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || tok->isConstOp()))
        return false;
    return true;
}
// pattern: [=[(,] 0 * (
MAYBE_UNUSED static inline bool match160(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("=[(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: return|case 0 *|&& (
MAYBE_UNUSED static inline bool match161(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: [=[(,] 0 && *|& %any% ,|]|)|;|=|%cop%
MAYBE_UNUSED static inline bool match162(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("=[(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || tok->isConstOp()))
        return false;
    return true;
}
// pattern: return|case 0 && *|& %any% ,|:|;|=|%cop%
MAYBE_UNUSED static inline bool match163(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || tok->isConstOp()))
        return false;
    return true;
}
// pattern: [=[(,] 1 %oror% %any% ,|]|)|;|=|%cop%
MAYBE_UNUSED static inline bool match164(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("=[(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("1")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || tok->isConstOp()))
        return false;
    return true;
}
// pattern: return|case 1 %oror% %any% ,|:|;|=|%cop%
MAYBE_UNUSED static inline bool match165(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("1")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || tok->isConstOp()))
        return false;
    return true;
}
// pattern: [=[(,] 1 %oror% *|& %any% ,|]|)|;|=|%cop%
MAYBE_UNUSED static inline bool match166(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("=[(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("1")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || tok->isConstOp()))
        return false;
    return true;
}
// pattern: return|case 1 %oror% *|& %any% ,|:|;|=|%cop%
MAYBE_UNUSED static inline bool match167(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("1")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || tok->isConstOp()))
        return false;
    return true;
}
// pattern: %any% * 1
MAYBE_UNUSED static inline bool match168(const Token* tok) {
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("1")))
        return false;
    return true;
}
// pattern: %any% 1 *
MAYBE_UNUSED static inline bool match169(const Token* tok) {
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("1")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: %op%|< ( %num% )
MAYBE_UNUSED static inline bool match170(const Token* tok) {
    if (!tok || !(tok->isOp() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ( 0 [|+]
MAYBE_UNUSED static inline bool match171(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("|+", tok->str()[0]))
        return false;
    return true;
}
// pattern: [|+-] 0 )
MAYBE_UNUSED static inline bool match172(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("|+-", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: [|+-]
MAYBE_UNUSED static inline bool match173(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("|+-", tok->str()[0]))
        return false;
    return true;
}
// pattern: (|&&|%oror%
MAYBE_UNUSED static inline bool match174(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||"))))
        return false;
    return true;
}
// pattern: %name% ,|>|=
MAYBE_UNUSED static inline bool match175(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: %name% !!<
MAYBE_UNUSED static inline bool match176(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("<"))
        return false;
    return true;
}
// pattern: %num%| ]
MAYBE_UNUSED static inline bool match177(const Token* tok) {
    if (tok && (tok->isNumber()))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    return true;
}
// pattern: <|,|:: %name% <
MAYBE_UNUSED static inline bool match178(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: > ,|>|::
MAYBE_UNUSED static inline bool match179(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: )|]
MAYBE_UNUSED static inline bool match180(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    return true;
}
// pattern: class|struct|enum
MAYBE_UNUSED static inline bool match181(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    return true;
}
// pattern: >|%name% :: %name%
MAYBE_UNUSED static inline bool match182(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || tok->isName()))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: ;|{|}|=|const
MAYBE_UNUSED static inline bool match183(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        return false;
    return true;
}
// pattern: > (|{
MAYBE_UNUSED static inline bool match184(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: template|const_cast|dynamic_cast|reinterpret_cast|static_cast
MAYBE_UNUSED static inline bool match185(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("template")) || (tok->str() == MatchCompiler::makeConstString("const_cast")) || (tok->str() == MatchCompiler::makeConstString("dynamic_cast")) || (tok->str() == MatchCompiler::makeConstString("reinterpret_cast")) || (tok->str() == MatchCompiler::makeConstString("static_cast"))))
        return false;
    return true;
}
// pattern: >
MAYBE_UNUSED static inline bool match186(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    return true;
}
// pattern: {|(|<
MAYBE_UNUSED static inline bool match187(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: }|)|>
MAYBE_UNUSED static inline bool match188(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: sizeof ...
MAYBE_UNUSED static inline bool match189(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")))
        return false;
    return true;
}
// pattern: typename %name%
MAYBE_UNUSED static inline bool match190(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("typename")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: using %name% =
MAYBE_UNUSED static inline bool match191(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: )|>|>> requires %name%|(
MAYBE_UNUSED static inline bool match192(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("requires")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: explicit (
MAYBE_UNUSED static inline bool match193(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("explicit")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: false )
MAYBE_UNUSED static inline bool match194(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBoolean) && tok->str() == MatchCompiler::makeConstString("false")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: )|;
MAYBE_UNUSED static inline bool match195(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: ( ... %op%
MAYBE_UNUSED static inline bool match196(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isOp())
        return false;
    return true;
}
// pattern: ( %name% %op% ...
MAYBE_UNUSED static inline bool match197(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !tok->isOp())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")))
        return false;
    return true;
}
// pattern: ] (
MAYBE_UNUSED static inline bool match198(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %op% ... )
MAYBE_UNUSED static inline bool match199(const Token* tok) {
    if (!tok || !tok->isOp())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ... %op% %name% )
MAYBE_UNUSED static inline bool match200(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isOp())
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/templatesimplifier.cpp"
/*
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2025 Cppcheck team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "templatesimplifier.h"

#include "errorlogger.h"
#include "errortypes.h"
#include "mathlib.h"
#include "settings.h"
#include "standards.h"
#include "token.h"
#include "tokenize.h"
#include "tokenlist.h"
#include "utils.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <type_traits>
#include <utility>

static Token *skipRequires(Token *tok)
{
    if (!match1(tok))
        return tok;

    while (match2(tok)) {
        Token *after = tok->next();
        if (after->str() == MatchCompiler::makeConstString("(")) {
            tok = after->link()->next();
            continue;
        }
        if (match3(after) && match4(after->linkAt(1))) {
            tok = after->linkAt(1)->linkAt(1)->next();
            continue;
        }
        while (match5(after))
            after = after->tokAt(2);
        if (match6(after)) {
            after = after->next()->findClosingBracket();
            tok = after ? after->next() : nullptr;
        } else
            break;
    }
    return tok;
}

namespace {
    class FindToken {
    public:
        explicit FindToken(const Token *token) : mToken(token) {}
        bool operator()(const TemplateSimplifier::TokenAndName &tokenAndName) const {
            return tokenAndName.token() == mToken;
        }
    private:
        const Token * const mToken;
    };

    class FindName {
    public:
        explicit FindName(std::string name) : mName(std::move(name)) {}
        bool operator()(const TemplateSimplifier::TokenAndName &tokenAndName) const {
            return tokenAndName.name() == mName;
        }
    private:
        const std::string mName;
    };

    class FindFullName {
    public:
        explicit FindFullName(std::string fullName) : mFullName(std::move(fullName)) {}
        bool operator()(const TemplateSimplifier::TokenAndName &tokenAndName) const {
            return tokenAndName.fullName() == mFullName;
        }
    private:
        const std::string mFullName;
    };
}

TemplateSimplifier::TokenAndName::TokenAndName(Token *token, std::string scope) :
    mToken(token), mScope(std::move(scope)), mName(mToken ? mToken->str() : ""),
    mFullName(mScope.empty() ? mName : (mScope + " :: " + mName)),
    mNameToken(nullptr), mParamEnd(nullptr), mFlags(0)
{
    if (mToken) {
        if (mToken->strAt(1) == MatchCompiler::makeConstString("<")) {
            const Token *end = mToken->next()->findClosingBracket();
            if (end && end->strAt(1) == MatchCompiler::makeConstString("(")) {
                isFunction(true);
            }
        }
        mToken->templateSimplifierPointer(this);
    }
}

TemplateSimplifier::TokenAndName::TokenAndName(Token *token, std::string scope, const Token *nameToken, const Token *paramEnd) :
    mToken(token), mScope(std::move(scope)), mName(nameToken->str()),
    mFullName(mScope.empty() ? mName : (mScope + " :: " + mName)),
    mNameToken(nameToken), mParamEnd(paramEnd), mFlags(0)
{
    // only set flags for declaration
    if (mToken && mNameToken && mParamEnd) {
        isSpecialization(match7(mToken));

        if (!isSpecialization()) {
            if (match8(mToken->next()->findClosingBracket())) {
                const Token * temp = mNameToken->tokAt(-2);
                while (match9(temp)) {
                    if (temp->str() == MatchCompiler::makeConstString(">"))
                        temp = temp->findOpeningBracket()->previous();
                    else
                        temp = temp->tokAt(-2);
                }
                isPartialSpecialization(temp->strAt(1) == MatchCompiler::makeConstString("<"));
            } else
                isPartialSpecialization(mNameToken->strAt(1) == MatchCompiler::makeConstString("<"));
        }

        isAlias(mParamEnd->strAt(1) == MatchCompiler::makeConstString("using"));

        if (isAlias() && isPartialSpecialization()) {
            throw InternalError(mToken, "partial specialization of alias templates is not permitted", InternalError::SYNTAX);
        }
        if (isAlias() && isSpecialization()) {
            throw InternalError(mToken, "explicit specialization of alias templates is not permitted", InternalError::SYNTAX);
        }

        isFriend(mParamEnd->strAt(1) == MatchCompiler::makeConstString("friend"));
        const Token *next = mParamEnd->next();
        if (isFriend())
            next = next->next();

        isClass(match10(next));
        if (mToken->strAt(1) == MatchCompiler::makeConstString("<") && !isSpecialization()) {
            const Token *end = mToken->next()->findClosingBracket();
            isVariadic(end && findmatch11(mToken->tokAt(2), end) );
        }
        const Token *tok1 = mNameToken->next();
        if (tok1->str() == MatchCompiler::makeConstString("<")) {
            const Token *closing = tok1->findClosingBracket();
            if (closing)
                tok1 = closing->next();
            else
                throw InternalError(mToken, "unsupported syntax", InternalError::SYNTAX);
        }
        isFunction(tok1->str() == MatchCompiler::makeConstString("("));
        isVariable(!isClass() && !isAlias() && !isFriend() && match12(tok1));
        if (!isFriend()) {
            if (isVariable())
                isForwardDeclaration(tok1->str() == MatchCompiler::makeConstString(";"));
            else if (!isAlias()) {
                if (isFunction())
                    tok1 = tok1->link()->next();
                while (tok1 && !match13(tok1)) {
                    if (tok1->str() == MatchCompiler::makeConstString("<"))
                        tok1 = tok1->findClosingBracket();
                    else if (match14(tok1) && tok1->link())
                        tok1 = tok1->link();
                    if (tok1)
                        tok1 = tok1->next();
                }
                if (tok1)
                    isForwardDeclaration(tok1->str() == MatchCompiler::makeConstString(";"));
            }
        }
        // check for member class or function and adjust scope
        if ((isFunction() || isClass()) &&
            (mNameToken->strAt(-1) == MatchCompiler::makeConstString("::") || match15(mNameToken->tokAt(-2)))) {
            const Token * start = mNameToken;
            if (start->strAt(-1) == MatchCompiler::makeConstString("~"))
                start = start->previous();
            const Token *end = start;

            while (start && (match16(start->tokAt(-2)) ||
                             (match17(start->tokAt(-2)) &&
                              start->tokAt(-2)->findOpeningBracket() &&
                              match6(start->tokAt(-2)->findOpeningBracket()->previous())))) {
                if (start->strAt(-2) == MatchCompiler::makeConstString(">"))
                    start = start->tokAt(-2)->findOpeningBracket()->previous();
                else
                    start = start->tokAt(-2);
            }

            if (start && start != end) {
                if (!mScope.empty())
                    mScope += " ::";
                while (start && start->next() != end) {
                    if (start->str() == MatchCompiler::makeConstString("<"))
                        start = start->findClosingBracket();
                    else {
                        if (!mScope.empty())
                            mScope += " ";
                        mScope += start->str();
                    }
                    start = start->next();
                }
                if (start)
                    mFullName = mScope.empty() ? mName : (mScope + " :: " + mName);
            }
        }
    }

    // make sure at most only one family flag is set
    assert(isClass() ? !(isFunction() || isVariable()) : true);
    assert(isFunction() ? !(isClass() || isVariable()) : true);
    assert(isVariable() ? !(isClass() || isFunction()) : true);

    if (mToken)
        mToken->templateSimplifierPointer(this);
}

TemplateSimplifier::TokenAndName::TokenAndName(const TokenAndName& other) :
    mToken(other.mToken), mScope(other.mScope), mName(other.mName), mFullName(other.mFullName),
    mNameToken(other.mNameToken), mParamEnd(other.mParamEnd), mFlags(other.mFlags)
{
    if (mToken)
        mToken->templateSimplifierPointer(this);
}

TemplateSimplifier::TokenAndName::~TokenAndName()
{
    if (mToken && mToken->templateSimplifierPointers())
        mToken->templateSimplifierPointers()->erase(this);
}

std::string TemplateSimplifier::TokenAndName::dump(const std::vector<std::string>& fileNames) const {
    std::string ret = "    <TokenAndName name=\"" + ErrorLogger::toxml(mName) + "\" file=\"" + ErrorLogger::toxml(fileNames.at(mToken->fileIndex())) + "\" line=\"" + std::to_string(mToken->linenr()) + "\">\n";
    for (const Token* tok = mToken; tok && !match18(tok); tok = tok->next())
        ret += "      <template-token str=\"" + ErrorLogger::toxml(tok->str()) + "\"/>\n";
    return ret + "    </TokenAndName>\n";
}

const Token * TemplateSimplifier::TokenAndName::aliasStartToken() const
{
    if (mParamEnd)
        return mParamEnd->tokAt(4);
    return nullptr;
}

const Token * TemplateSimplifier::TokenAndName::aliasEndToken() const
{
    if (aliasStartToken())
        return findmatch19(aliasStartToken()) ;
    return nullptr;
}

bool TemplateSimplifier::TokenAndName::isAliasToken(const Token *tok) const
{
    const Token *end = aliasEndToken();

    for (const Token *tok1 = aliasStartToken(); tok1 != end; tok1 = tok1->next()) {
        if (tok1 == tok)
            return true;
    }
    return false;
}

TemplateSimplifier::TemplateSimplifier(Tokenizer &tokenizer)
    : mTokenizer(tokenizer), mTokenList(mTokenizer.list), mSettings(mTokenizer.getSettings()),
    mErrorLogger(mTokenizer.mErrorLogger)
{}

void TemplateSimplifier::checkComplicatedSyntaxErrorsInTemplates()
{
    // check for more complicated syntax errors when using templates..
    for (const Token *tok = mTokenList.front(); tok; tok = tok->next()) {
        // skip executing scopes (ticket #3183)..
        if (match20(tok)) {
            tok = tok->link();
            if (!tok)
                syntaxError(nullptr);
        }
        // skip executing scopes..
        const Token *start = Tokenizer::startOfExecutableScope(tok);
        if (start) {
            tok = start->link();
        }

        // skip executing scopes (ticket #1985)..
        else if (match21(tok)) {
            tok = tok->linkAt(1);
            while (match22(tok)) {
                tok = tok->linkAt(2);
                if (match4(tok))
                    tok = tok->linkAt(1);
            }
        }

        if (!tok)
            syntaxError(nullptr);
        // not start of statement?
        if (tok->previous() && !match18(tok))
            continue;

        // skip starting tokens.. ;;; typedef typename foo::bar::..
        while (match13(tok))
            tok = tok->next();
        while (match23(tok))
            tok = tok->next();
        while (match24(tok))
            tok = tok->tokAt(2);
        if (!tok)
            break;

        // template variable or type..
        if (match25(tok) && !match26(tok)) {
            // these are used types..
            std::set<std::string> usedtypes;

            // parse this statement and see if the '<' and '>' are matching
            unsigned int level = 0;
            for (const Token *tok2 = tok; tok2 && !match27(tok2); tok2 = tok2->next()) {
                if (match28(tok2) &&
                    (!match29(tok2->previous()) || match30(tok2->link())))
                    break;
                if (tok2->str() == MatchCompiler::makeConstString("("))
                    tok2 = tok2->link();
                else if (tok2->str() == MatchCompiler::makeConstString("<")) {
                    bool inclevel = false;
                    if (match31(tok2->previous()))
                        ;
                    else if (level == 0 && match32(tok2->previous())) {
                        // @todo add better expression detection
                        if (!(match33(tok2->next()) ||
                              match34(tok2->next()))) {
                            inclevel = true;
                        }
                    } else if (tok2->next() && tok2->next()->isStandardType() && !match35(tok2->tokAt(2)))
                        inclevel = true;
                    else if (match36(tok2))
                        inclevel = true;
                    else if (match37(tok2->tokAt(-2)) && usedtypes.find(tok2->strAt(-1)) != usedtypes.end())
                        inclevel = true;
                    else if (match38(tok2) && usedtypes.find(tok2->strAt(1)) != usedtypes.end())
                        inclevel = true;
                    else if (match38(tok2)) {
                        // is the next token a type and not a variable/constant?
                        // assume it's a type if there comes another "<"
                        const Token *tok3 = tok2->next();
                        while (match24(tok3))
                            tok3 = tok3->tokAt(2);
                        if (match25(tok3))
                            inclevel = true;
                    } else if (tok2->strAt(-1) == MatchCompiler::makeConstString(">"))
                        syntaxError(tok);

                    if (inclevel) {
                        ++level;
                        if (match37(tok2->tokAt(-2)))
                            usedtypes.insert(tok2->strAt(-1));
                    }
                } else if (tok2->str() == MatchCompiler::makeConstString(">")) {
                    if (level > 0)
                        --level;
                } else if (tok2->str() == MatchCompiler::makeConstString(">>")) {
                    if (level > 0)
                        --level;
                    if (level > 0)
                        --level;
                }
            }
            if (level > 0)
                syntaxError(tok);
        }
    }
}

unsigned int TemplateSimplifier::templateParameters(const Token *tok)
{
    unsigned int numberOfParameters = 1;

    if (!tok)
        return 0;
    if (tok->str() != MatchCompiler::makeConstString("<"))
        return 0;
    if (match39(tok->previous()))
        return 0;
    tok = tok->next();
    if (!tok || tok->str() == MatchCompiler::makeConstString(">"))
        return 0;

    unsigned int level = 0;

    while (tok) {
        // skip template template
        if (level == 0 && match40(tok)) {
            const Token *closing = tok->next()->findClosingBracket();
            if (closing) {
                if (closing->str() == MatchCompiler::makeConstString(">>"))
                    return numberOfParameters;
                tok = closing->next();
                if (!tok)
                    syntaxError(tok);
                if (match41(tok))
                    return numberOfParameters;
                if (tok->str() == MatchCompiler::makeConstString(",")) {
                    ++numberOfParameters;
                    tok = tok->next();
                    continue;
                }
            } else
                return 0;
        }

        // skip const/volatile
        if (match42(tok))
            tok = tok->next();

        // skip struct/union
        if (match43(tok))
            tok = tok->next();

        // Skip '&'
        if (match44(tok))
            tok = tok->next();

        // Skip variadic types (Ticket #5774, #6059, #6172)
        if (match45(tok)) {
            if ((tok->previous()->isName() && !match46(tok->tokAt(-2))) ||
                (!tok->previous()->isName() && !match47(tok->previous())))
                return 0; // syntax error
            tok = tok->next();
            if (!tok)
                return 0;
            if (tok->str() == MatchCompiler::makeConstString(">")) {
                if (level == 0)
                    return numberOfParameters;
                --level;
            } else if (tok->str() == MatchCompiler::makeConstString(">>") || tok->str() == MatchCompiler::makeConstString(">>=")) {
                if (level == 1)
                    return numberOfParameters;
                level -= 2;
            } else if (tok->str() == MatchCompiler::makeConstString(",")) {
                if (level == 0)
                    ++numberOfParameters;
                tok = tok->next();
                continue;
            }
        }

        // Skip '=', '?', ':'
        if (match48(tok))
            tok = tok->next();
        if (!tok)
            return 0;

        // Skip links
        if (match35(tok)) {
            tok = tok->link();
            if (tok)
                tok = tok->next();
            if (!tok)
                return 0;
            if (tok->str() == MatchCompiler::makeConstString(">") && level == 0)
                return numberOfParameters;
            if ((tok->str() == MatchCompiler::makeConstString(">>") || tok->str() == MatchCompiler::makeConstString(">>=")) && level == 1)
                return numberOfParameters;
            if (tok->str() == MatchCompiler::makeConstString(",")) {
                if (level == 0)
                    ++numberOfParameters;
                tok = tok->next();
            }
            continue;
        }

        // skip std::
        if (tok->str() == MatchCompiler::makeConstString("::"))
            tok = tok->next();
        while (match16(tok)) {
            tok = tok->tokAt(2);
            if (tok && tok->str() == MatchCompiler::makeConstString("*")) // Ticket #5759: Class member pointer as a template argument; skip '*'
                tok = tok->next();
        }
        if (!tok)
            return 0;

        // num/type ..
        if (!tok->isNumber() && tok->tokType() != Token::eChar && tok->tokType() != Token::eString && !tok->isName() && !tok->isOp())
            return 0;
        tok = tok->next();
        if (!tok)
            return 0;

        // * / const
        while (match49(tok))
            tok = tok->next();

        if (!tok)
            return 0;

        // Function pointer or prototype..
        while (match14(tok)) {
            if (!tok->link())
                syntaxError(tok);

            tok = tok->link()->next();
            while (match42(tok)) // Ticket #5786: Skip function cv-qualifiers
                tok = tok->next();
        }
        if (!tok)
            return 0;

        // inner template
        if (tok->str() == MatchCompiler::makeConstString("<") && tok->previous()->isName()) {
            ++level;
            tok = tok->next();
        }

        if (!tok)
            return 0;

        // ,/>
        while (match41(tok)) {
            if (level == 0)
                return tok->str() == MatchCompiler::makeConstString(">") && !match50(tok->next()) ? numberOfParameters : 0;
            --level;
            if (tok->str() == MatchCompiler::makeConstString(">>") || tok->str() == MatchCompiler::makeConstString(">>=")) {
                if (level == 0)
                    return !match50(tok->next()) ? numberOfParameters : 0;
                --level;
            }
            tok = tok->next();

            if (match14(tok))
                tok = tok->link()->next();

            if (!tok)
                return 0;
        }

        if (tok->str() != MatchCompiler::makeConstString(","))
            continue;
        if (level == 0)
            ++numberOfParameters;
        tok = tok->next();
    }
    return 0;
}

template<class T, REQUIRES("T must be a Token class", std::is_convertible<T*, const Token*> )>
static T *findTemplateDeclarationEndImpl(T *tok)
{
    if (match40(tok)) {
        tok = tok->next()->findClosingBracket();
        if (tok)
            tok = tok->next();
    }

    if (!tok)
        return nullptr;

    T * tok2 = tok;
    bool in_init = false;
    while (tok2 && !match13(tok2)) {
        if (tok2->str() == MatchCompiler::makeConstString("<"))
            tok2 = tok2->findClosingBracket();
        else if (match14(tok2) && tok2->link())
            tok2 = tok2->link();
        else if (tok2->str() == MatchCompiler::makeConstString(":"))
            in_init = true;
        else if (in_init && match51(tok2)) {
            tok2 = tok2->linkAt(1);
            if (tok2->strAt(1) == MatchCompiler::makeConstString("{"))
                in_init = false;
        }
        if (tok2)
            tok2 = tok2->next();
    }
    if (tok2 && tok2->str() == MatchCompiler::makeConstString("{")) {
        tok = tok2->link();
        if (tok && tok->strAt(1) == MatchCompiler::makeConstString(";"))
            tok = tok->next();
    } else if (tok2 && tok2->str() == MatchCompiler::makeConstString(";"))
        tok = tok2;
    else
        tok = nullptr;

    return tok;
}

Token *TemplateSimplifier::findTemplateDeclarationEnd(Token *tok)
{
    return findTemplateDeclarationEndImpl(tok);
}

const Token *TemplateSimplifier::findTemplateDeclarationEnd(const Token *tok)
{
    return findTemplateDeclarationEndImpl(tok);
}

void TemplateSimplifier::eraseTokens(Token *begin, const Token *end)
{
    if (!begin || begin == end)
        return;

    while (begin->next() && begin->next() != end) {
        begin->deleteNext();
    }
}

void TemplateSimplifier::deleteToken(Token *tok)
{
    if (tok->next())
        tok->next()->deletePrevious();
    else
        tok->deleteThis();
}

static void invalidateForwardDecls(const Token* beg, const Token* end, std::map<Token*, Token*>* forwardDecls) {
    if (!forwardDecls)
        return;
    for (auto& fwd : *forwardDecls) {
        for (const Token* tok = beg; tok != end; tok = tok->next())
            if (fwd.second == tok) {
                fwd.second = nullptr;
                break;
            }
    }
}

bool TemplateSimplifier::removeTemplate(Token *tok, std::map<Token*, Token*>* forwardDecls)
{
    if (!match40(tok))
        return false;

    Token *end = findTemplateDeclarationEnd(tok);
    if (end && end->next()) {
        invalidateForwardDecls(tok, end->next(), forwardDecls);
        eraseTokens(tok, end->next());
        deleteToken(tok);
        return true;
    }

    return false;
}

bool TemplateSimplifier::getTemplateDeclarations()
{
    bool codeWithTemplates = false;
    for (Token *tok = mTokenList.front(); tok; tok = tok->next()) {
        if (!match40(tok))
            continue;
        // ignore template template parameter
        if (tok->strAt(-1) == MatchCompiler::makeConstString("<") || tok->strAt(-1) == MatchCompiler::makeConstString(","))
            continue;
        // ignore nested template
        if (tok->strAt(-1) == MatchCompiler::makeConstString(">"))
            continue;
        // skip to last nested template parameter
        const Token *tok1 = tok;
        while (tok1 && tok1->next()) {
            const Token *closing = tok1->next()->findClosingBracket();
            if (!match8(closing))
                break;
            tok1 = closing->next();
        }
        if (!match52(tok))
            syntaxError(tok);
        if (tok->strAt(2)==MatchCompiler::makeConstString("typename") &&
            !match53(tok->tokAt(3)))
            syntaxError(tok->next());
        codeWithTemplates = true;
        const Token * const parmEnd = tok1->next()->findClosingBracket();
        for (const Token *tok2 = parmEnd; tok2; tok2 = tok2->next()) {
            if (tok2->str() == MatchCompiler::makeConstString("(") && tok2->link())
                tok2 = tok2->link();
            else if (tok2->str() == MatchCompiler::makeConstString(")"))
                break;
            // skip decltype(...)
            else if (match54(tok2))
                tok2 = tok2->linkAt(1);
            else if (match55(tok2)) {
                const int namepos = getTemplateNamePosition(parmEnd);
                if (namepos > 0) {
                    TokenAndName decl(tok, tok->scopeInfo()->name, parmEnd->tokAt(namepos), parmEnd);
                    if (decl.isForwardDeclaration()) {
                        // Declaration => add to mTemplateForwardDeclarations
                        mTemplateForwardDeclarations.emplace_back(std::move(decl));
                    } else {
                        // Implementation => add to mTemplateDeclarations
                        mTemplateDeclarations.emplace_back(std::move(decl));
                    }
                    Token *end = findTemplateDeclarationEnd(tok);
                    if (end)
                        tok = end;
                    break;
                }
            }
        }
    }
    return codeWithTemplates;
}

void TemplateSimplifier::addInstantiation(Token *token, const std::string &scope)
{
    simplifyTemplateArgs(token->tokAt(2), token->next()->findClosingBracket());

    TokenAndName instantiation(token, scope);

    // check if instantiation already exists before adding it
    const auto it = std::find(mTemplateInstantiations.cbegin(),
                              mTemplateInstantiations.cend(),
                              instantiation);

    if (it == mTemplateInstantiations.cend())
        mTemplateInstantiations.emplace_back(std::move(instantiation));
}

static const Token* getFunctionToken(const Token* nameToken)
{
    if (match56(nameToken))
        return nameToken->next();

    if (match6(nameToken)) {
        const Token* end = nameToken->next()->findClosingBracket();
        if (match57(end))
            return end->next();
    }

    return nullptr;
}

static void getFunctionArguments(const Token* nameToken, std::vector<const Token*>& args)
{
    const Token* functionToken = getFunctionToken(nameToken);
    if (!functionToken)
        return;

    const Token* argToken = functionToken->next();

    if (argToken->str() == MatchCompiler::makeConstString(")"))
        return;

    args.push_back(argToken);

    while ((argToken = argToken->nextArgumentBeforeCreateLinks2()))
        args.push_back(argToken);
}

static bool isConstMethod(const Token* nameToken)
{
    const Token* functionToken = getFunctionToken(nameToken);
    if (!functionToken)
        return false;
    const Token* endToken = functionToken->link();
    return match58(endToken);
}

static bool areAllParamsTypes(const std::vector<const Token *> &params)
{
    if (params.empty())
        return false;

    return std::all_of(params.cbegin(), params.cend(), [](const Token* param) {
        return match59(param->previous());
    });
}

static bool isTemplateInstantion(const Token* tok)
{
    if (!tok->isName() || (tok->isKeyword() && !tok->isOperatorKeyword()))
        return false;
    if (match60(tok->tokAt(-1)))
        return true;
    if (match61(tok->tokAt(-2)))
        return true;
    if (match62(tok->tokAt(-1)))
        return true;
    return match63(tok->tokAt(-2));
}

void TemplateSimplifier::getTemplateInstantiations()
{
    std::multimap<std::string, const TokenAndName *> functionNameMap;

    for (const auto & decl : mTemplateDeclarations) {
        if (decl.isFunction())
            functionNameMap.emplace(decl.name(), &decl);
    }

    for (const auto & decl : mTemplateForwardDeclarations) {
        if (decl.isFunction())
            functionNameMap.emplace(decl.name(), &decl);
    }

    const Token *skip = nullptr;

    for (Token *tok = mTokenList.front(); tok; tok = tok->next()) {

        // template definition.. skip it
        if (match40(tok)) {
            tok = tok->next()->findClosingBracket();
            if (!tok)
                break;

            const bool isUsing = tok->strAt(1) == MatchCompiler::makeConstString("using");
            if (isUsing && match6(tok->tokAt(2))) {
                // Can't have specialized type alias so ignore it
                Token *tok2 = findmatch19(tok->tokAt(3)) ;
                if (tok2)
                    tok = tok2;
            } else if (tok->strAt(-1) == MatchCompiler::makeConstString("<")) {
                // Don't ignore user specialization but don't consider it an instantiation.
                // Instantiations in return type, function parameters, and executable code
                // are not ignored.
                const int pos = getTemplateNamePosition(tok);
                if (pos > 0)
                    skip = tok->tokAt(pos);
            } else {
                // #7914
                // Ignore template instantiations within template definitions: they will only be
                // handled if the definition is actually instantiated

                Token * tok2 = findTemplateDeclarationEnd(tok->next());
                if (tok2)
                    tok = tok2;
            }
        } else if (match64(tok)) {
            // Can't have specialized type alias so ignore it
            Token *tok2 = findmatch19(tok->tokAt(3)) ;
            if (tok2)
                tok = tok2;
        } else if (match65(tok)) {
            // Can't have specialized type alias so ignore it
            Token *tok2 = findmatch19(tok->tokAt(2)) ;
            if (tok2)
                tok = tok2;
        } else if (isTemplateInstantion(tok)) {
            if (!tok->scopeInfo())
                syntaxError(tok);
            std::string scopeName = tok->scopeInfo()->name;
            std::string qualification;
            Token * qualificationTok = tok;
            while (match5(tok)) {
                qualification += (qualification.empty() ? "" : " :: ") + tok->str();
                tok = tok->tokAt(2);
            }

            // skip specialization
            if (tok == skip) {
                skip = nullptr;
                continue;
            }

            // look for function instantiation with type deduction
            if (tok->strAt(1) == MatchCompiler::makeConstString("(")) {
                std::vector<const Token *> instantiationArgs;
                getFunctionArguments(tok, instantiationArgs);

                std::string fullName;
                if (!qualification.empty())
                    fullName = qualification + " :: " + tok->str();
                else if (!scopeName.empty())
                    fullName = scopeName + " :: " + tok->str();
                else
                    fullName = tok->str();

                // get all declarations with this name
                auto range = functionNameMap.equal_range(tok->str());
                for (auto pos = range.first; pos != range.second; ++pos) {
                    // look for declaration with same qualification or constructor with same qualification
                    if (pos->second->fullName() == fullName ||
                        (pos->second->scope() == fullName && tok->str() == pos->second->name())) {
                        std::vector<const Token *> templateParams;
                        getTemplateParametersInDeclaration(pos->second->token()->tokAt(2), templateParams);

                        // todo: handle more than one template parameter
                        if (templateParams.size() != 1 || !areAllParamsTypes(templateParams))
                            continue;

                        std::vector<const Token *> declarationParams;
                        getFunctionArguments(pos->second->nameToken(), declarationParams);

                        // function argument counts must match
                        if (instantiationArgs.empty() || instantiationArgs.size() != declarationParams.size())
                            continue;

                        size_t match = 0;
                        size_t argMatch = 0;
                        for (size_t i = 0; i < declarationParams.size(); ++i) {
                            // fixme: only type deduction from literals is supported
                            const bool isArgLiteral = match66(instantiationArgs[i]);
                            if (isArgLiteral && match67(declarationParams[i])) {
                                match++;

                                // check if parameter types match
                                if (templateParams[0]->str() == declarationParams[i]->str())
                                    argMatch = i;
                                else {
                                    // todo: check if non-template args match for function overloads
                                }
                            }
                        }

                        if (match == declarationParams.size()) {
                            const Token *arg = instantiationArgs[argMatch];
                            tok->insertToken(">");
                            switch (arg->tokType()) {
                            case Token::eBoolean:
                                tok->insertToken("bool");
                                break;
                            case Token::eChar:
                                if (arg->isLong())
                                    tok->insertToken("wchar_t");
                                else
                                    tok->insertToken("char");
                                break;
                            case Token::eString:
                                tok->insertToken("*");
                                if (arg->isLong())
                                    tok->insertToken("wchar_t");
                                else
                                    tok->insertToken("char");
                                tok->insertToken("const");
                                break;
                            case Token::eNumber: {
                                MathLib::value num(arg->str());
                                if (num.isFloat()) {
                                    // MathLib::getSuffix doesn't work for floating point numbers
                                    const char suffix = arg->str().back();
                                    if (suffix == 'f' || suffix == 'F')
                                        tok->insertToken("float");
                                    else if (suffix == 'l' || suffix == 'L') {
                                        tok->insertToken("double");
                                        tok->next()->isLong(true);
                                    } else
                                        tok->insertToken("double");
                                } else if (num.isInt()) {
                                    std::string suffix = MathLib::getSuffix(tok->strAt(3));
                                    if (suffix.find("LL") != std::string::npos) {
                                        tok->insertToken("long");
                                        tok->next()->isLong(true);
                                    } else if (suffix.find('L') != std::string::npos)
                                        tok->insertToken("long");
                                    else
                                        tok->insertToken("int");
                                    if (suffix.find('U') != std::string::npos)
                                        tok->next()->isUnsigned(true);
                                }
                                break;
                            }
                            default:
                                break;
                            }
                            tok->insertToken("<");
                            break;
                        }
                    }
                }
            }

            if (!match6(tok) ||
                match68(tok))
                continue;

            if (tok == skip) {
                skip = nullptr;
                continue;
            }

            // Add inner template instantiations first => go to the ">"
            // and then parse backwards, adding all seen instantiations
            Token *tok2 = tok->next()->findClosingBracket();

            // parse backwards and add template instantiations
            // TODO
            for (; tok2 && tok2 != tok; tok2 = tok2->previous()) {
                if (match69(tok2) && !tok2->next()->isKeyword() &&
                    (tok2->strAt(3) == MatchCompiler::makeConstString(">") || templateParameters(tok2->tokAt(2)))) {
                    addInstantiation(tok2->next(), tok->scopeInfo()->name);
                } else if (match70(tok2->next()))
                    tok2->deleteNext();
            }

            // Add outer template..
            if (templateParameters(tok->next()) || tok->strAt(2) == MatchCompiler::makeConstString(">")) {
                while (true) {
                    std::string fullName = scopeName + (scopeName.empty()?"":" :: ") +
                                           qualification + (qualification.empty()?"":" :: ") + tok->str();
                    const auto it = std::find_if(mTemplateDeclarations.cbegin(), mTemplateDeclarations.cend(), FindFullName(std::move(fullName)));
                    if (it != mTemplateDeclarations.end()) {
                        // full name matches
                        addInstantiation(tok, it->scope());
                        break;
                    }
                    // full name doesn't match so try with using namespaces if available
                    bool found = false;
                    for (const auto & nameSpace :  tok->scopeInfo()->usingNamespaces) {
                        std::string fullNameSpace = scopeName + (scopeName.empty()?"":" :: ") +
                                                    nameSpace + (qualification.empty()?"":" :: ") + qualification;
                        std::string newFullName = fullNameSpace + " :: " + tok->str();
                        const auto it1 = std::find_if(mTemplateDeclarations.cbegin(), mTemplateDeclarations.cend(), FindFullName(std::move(newFullName)));
                        if (it1 != mTemplateDeclarations.end()) {
                            // insert using namespace into token stream
                            std::string::size_type offset = 0;
                            std::string::size_type pos = 0;
                            while ((pos = nameSpace.find(' ', offset)) != std::string::npos) {
                                qualificationTok->insertTokenBefore(nameSpace.substr(offset, pos - offset));
                                offset = pos + 1;
                            }
                            qualificationTok->insertTokenBefore(nameSpace.substr(offset));
                            qualificationTok->insertTokenBefore("::");
                            addInstantiation(tok, it1->scope());
                            found = true;
                            break;
                        }
                    }
                    if (found)
                        break;

                    if (scopeName.empty()) {
                        if (!qualification.empty())
                            addInstantiation(tok, qualification);
                        else
                            addInstantiation(tok,  tok->scopeInfo()->name);
                        break;
                    }
                    const std::string::size_type pos = scopeName.rfind(" :: ");
                    scopeName = (pos == std::string::npos) ? std::string() : scopeName.substr(0,pos);
                }
            }
        }
    }
}


void TemplateSimplifier::useDefaultArgumentValues()
{
    for (TokenAndName &declaration : mTemplateDeclarations)
        useDefaultArgumentValues(declaration);

    for (TokenAndName &declaration : mTemplateForwardDeclarations)
        useDefaultArgumentValues(declaration);
}

void TemplateSimplifier::useDefaultArgumentValues(TokenAndName &declaration)
{
    // Ticket #5762: Skip specialization tokens
    if (declaration.isSpecialization() || declaration.isAlias() || declaration.isFriend())
        return;

    // template parameters with default value has syntax such as:
    //     x = y
    // this list will contain all the '=' tokens for such arguments
    struct Default {
        Token *eq;
        Token *end;
    };
    std::list<Default> eq;
    // and this set the position of parameters with a default value
    std::set<std::size_t> defaultedArgPos;

    // parameter number. 1,2,3,..
    std::size_t templatepar = 1;

    // parameter depth
    std::size_t templateParmDepth = 0;

    // map type parameter name to index
    std::map<std::string, unsigned int> typeParameterNames;

    // Scan template declaration..
    for (Token *tok = declaration.token()->next(); tok; tok = tok->next()) {
        if (match40(tok)) {
            Token* end = tok->next()->findClosingBracket();
            if (end)
                tok = end;
            continue;
        }

        if (tok->link() && match71(tok)) { // Ticket #6835
            tok = tok->link();
            continue;
        }

        if (tok->str() == MatchCompiler::makeConstString("<") &&
            (tok->strAt(1) == MatchCompiler::makeConstString(">") || (tok->previous()->isName() &&
                                      typeParameterNames.find(tok->strAt(-1)) == typeParameterNames.end())))
            ++templateParmDepth;

        // end of template parameters?
        if (tok->str() == MatchCompiler::makeConstString(">")) {
            if (templateParmDepth<2) {
                if (!eq.empty())
                    eq.back().end = tok;
                break;
            }
            --templateParmDepth;
        }

        // map type parameter name to index
        if (match72(tok))
            typeParameterNames[tok->strAt(1)] = templatepar - 1;

        // next template parameter
        if (tok->str() == MatchCompiler::makeConstString(",") && (1 == templateParmDepth)) { // Ticket #5823: Properly count parameters
            if (!eq.empty())
                eq.back().end = tok;
            ++templatepar;
        }

        // default parameter value?
        else if (match73(tok)) {
            if (defaultedArgPos.insert(templatepar).second) {
                eq.emplace_back(Default{tok, nullptr});
            } else {
                // Ticket #5605: Syntax error (two equal signs for the same parameter), bail out
                eq.clear();
                break;
            }
        }
    }
    if (eq.empty())
        return;

    // iterate through all template instantiations
    for (const TokenAndName &instantiation : mTemplateInstantiations) {
        if (declaration.fullName() != instantiation.fullName())
            continue;

        // instantiation arguments..
        std::vector<std::vector<const Token *>> instantiationArgs;
        std::size_t index = 0;
        const Token *end = instantiation.token()->next()->findClosingBracket();
        if (!end)
            continue;
        if (end != instantiation.token()->tokAt(2))
            instantiationArgs.resize(1);
        for (const Token *tok1 = instantiation.token()->tokAt(2); tok1 && tok1 != end; tok1 = tok1->next()) {
            if (tok1->link() && match71(tok1)) {
                const Token *endLink = tok1->link();
                do {
                    instantiationArgs[index].push_back(tok1);
                    tok1 = tok1->next();
                } while (tok1 && tok1 != endLink);
                instantiationArgs[index].push_back(tok1);
            } else if (tok1->str() == MatchCompiler::makeConstString("<") &&
                       (tok1->strAt(1) == MatchCompiler::makeConstString(">") || (tok1->previous()->isName() &&
                                                  typeParameterNames.find(tok1->strAt(-1)) == typeParameterNames.end()))) {
                const Token *endLink = tok1->findClosingBracket();
                do {
                    instantiationArgs[index].push_back(tok1);
                    tok1 = tok1->next();
                } while (tok1 && tok1 != endLink);
                instantiationArgs[index].push_back(tok1);
            } else if (tok1->str() == MatchCompiler::makeConstString(",")) {
                ++index;
                instantiationArgs.resize(index + 1);
            } else
                instantiationArgs[index].push_back(tok1);
        }

        // count the parameters..
        Token *tok = instantiation.token()->next();
        unsigned int usedpar = templateParameters(tok);
        Token *instantiationEnd = tok->findClosingBracket();
        tok = instantiationEnd;

        if (tok && tok->str() == MatchCompiler::makeConstString(">")) {
            tok = tok->previous();
            auto it = eq.cbegin();
            for (std::size_t i = (templatepar - eq.size()); it != eq.cend() && i < usedpar; ++i)
                ++it;
            int count = 0;
            while (it != eq.cend()) {
                // check for end
                if (!it->end) {
                    if (mSettings.debugwarnings && mSettings.severity.isEnabled(Severity::debug)) {
                        const std::list<const Token*> locationList(1, it->eq);
                        const ErrorMessage errmsg(locationList, &mTokenizer.list,
                                                  Severity::debug,
                                                  "noparamend",
                                                  "TemplateSimplifier couldn't find end of template parameter.",
                                                  Certainty::normal);
                        mErrorLogger.reportErr(errmsg);
                    }
                    break;
                }

                if ((usedpar + count) && usedpar <= (instantiationArgs.size() + count)) {
                    tok->insertToken(",");
                    tok = tok->next();
                }
                std::stack<Token *> links;
                for (const Token* from = it->eq->next(); from && from != it->end; from = from->next()) {
                    auto entry = typeParameterNames.find(from->str());
                    if (entry != typeParameterNames.end() && entry->second < instantiationArgs.size()) {
                        for (const Token *tok1 : instantiationArgs[entry->second]) {
                            tok->insertToken(tok1->str(), tok1->originalName());
                            tok = tok->next();

                            if (match74(tok))
                                links.push(tok);
                            else if (!links.empty() && match75(tok)) {
                                Token::createMutualLinks(links.top(), tok);
                                links.pop();
                            }
                        }
                    } else {
                        tok->insertToken(from->str(), from->originalName());
                        tok = tok->next();

                        if (match74(tok))
                            links.push(tok);
                        else if (!links.empty() && match75(tok)) {
                            Token::createMutualLinks(links.top(), tok);
                            links.pop();
                        }
                    }
                }
                ++it;
                count++;
                usedpar++;
            }
        }

        simplifyTemplateArgs(instantiation.token()->next(), instantiationEnd);
    }

    for (const auto & entry : eq) {
        Token *const eqtok = entry.eq;
        Token *tok2;
        int indentlevel = 0;
        for (tok2 = eqtok->next(); tok2; tok2 = tok2->next()) {
            if (match76(tok2)) { // bail out #6607
                tok2 = nullptr;
                break;
            }
            if (match77(tok2))
                tok2 = tok2->link();
            else if (match25(tok2) && (tok2->strAt(2) == MatchCompiler::makeConstString(">") || templateParameters(tok2->next()))) {
                const auto ti = std::find_if(mTemplateInstantiations.cbegin(),
                                             mTemplateInstantiations.cend(),
                                             FindToken(tok2));
                if (ti != mTemplateInstantiations.end())
                    mTemplateInstantiations.erase(ti);
                ++indentlevel;
            } else if (indentlevel > 0 && tok2->str() == MatchCompiler::makeConstString(">"))
                --indentlevel;
            else if (indentlevel == 0 && match78(tok2))
                break;
            if (indentlevel < 0)
                break;
        }
        // something went wrong, don't call eraseTokens()
        // with a nullptr "end" parameter (=all remaining tokens).
        if (!tok2)
            continue;

        // don't strip args from uninstantiated templates
        const auto ti2 = std::find_if(mTemplateInstantiations.cbegin(),
                                      mTemplateInstantiations.cend(),
                                      FindName(declaration.name()));

        if (ti2 == mTemplateInstantiations.end())
            continue;

        eraseTokens(eqtok, tok2);
        eqtok->deleteThis();

        // update parameter end pointer
        declaration.paramEnd(declaration.token()->next()->findClosingBracket());
    }
}

void TemplateSimplifier::simplifyTemplateAliases()
{
    for (auto it1 = mTemplateDeclarations.cbegin(); it1 != mTemplateDeclarations.cend();) {
        const TokenAndName &aliasDeclaration = *it1;

        if (!aliasDeclaration.isAlias()) {
            ++it1;
            continue;
        }

        // alias parameters..
        std::vector<const Token *> aliasParameters;
        getTemplateParametersInDeclaration(aliasDeclaration.token()->tokAt(2), aliasParameters);
        std::map<std::string, unsigned int> aliasParameterNames;
        for (unsigned int argnr = 0; argnr < aliasParameters.size(); ++argnr)
            aliasParameterNames[aliasParameters[argnr]->str()] = argnr;

        // Look for alias usages..
        bool found = false;
        for (auto it2 = mTemplateInstantiations.cbegin(); it2 != mTemplateInstantiations.cend();) {
            const TokenAndName &aliasUsage = *it2;
            if (!aliasUsage.token() || aliasUsage.fullName() != aliasDeclaration.fullName()) {
                ++it2;
                continue;
            }

            // don't recurse
            if (aliasDeclaration.isAliasToken(aliasUsage.token())) {
                ++it2;
                continue;
            }

            std::vector<std::pair<Token *, Token *>> args;
            Token *tok2 = aliasUsage.token()->tokAt(2);
            while (tok2) {
                Token * const start = tok2;
                while (tok2 && !match79(tok2)) {
                    if (tok2->link() && match14(tok2))
                        tok2 = tok2->link();
                    else if (tok2->str() == MatchCompiler::makeConstString("<")) {
                        tok2 = tok2->findClosingBracket();
                        if (!tok2)
                            break;
                    }
                    tok2 = tok2->next();
                }

                args.emplace_back(start, tok2);
                if (tok2 && tok2->str() == MatchCompiler::makeConstString(",")) {
                    tok2 = tok2->next();
                } else {
                    break;
                }
            }
            if (!tok2 || tok2->str() != MatchCompiler::makeConstString(">") ||
                (!aliasDeclaration.isVariadic() && (args.size() != aliasParameters.size())) ||
                (aliasDeclaration.isVariadic() && (args.size() < aliasParameters.size()))) {
                ++it2;
                continue;
            }

            mChanged = true;

            // copy template-id from declaration to after instantiation
            Token * dst = aliasUsage.token()->next()->findClosingBracket();
            const Token* end = TokenList::copyTokens(dst, aliasDeclaration.aliasStartToken(), aliasDeclaration.aliasEndToken()->previous(), false)->next();

            // replace parameters
            for (Token *tok1 = dst->next(); tok1 != end; tok1 = tok1->next()) {
                if (!tok1->isName())
                    continue;
                if (aliasParameterNames.find(tok1->str()) != aliasParameterNames.end()) {
                    const unsigned int argnr = aliasParameterNames[tok1->str()];
                    const Token * const fromStart = args[argnr].first;
                    const Token * const fromEnd   = args[argnr].second->previous();
                    Token *temp = TokenList::copyTokens(tok1, fromStart, fromEnd, true);
                    const bool tempOK(temp != tok1->next());
                    tok1->deleteThis();
                    if (tempOK)
                        tok1 = temp; // skip over inserted parameters
                } else if (tok1->str() == MatchCompiler::makeConstString("typename"))
                    tok1->deleteThis();
            }

            // add new instantiations
            for (Token *tok1 = dst->next(); tok1 != end; tok1 = tok1->next()) {
                if (!tok1->isName())
                    continue;
                if (aliasParameterNames.find(tok2->str()) == aliasParameterNames.end()) {
                    // Create template instance..
                    if (match6(tok1)) {
                        const auto it = std::find_if(mTemplateInstantiations.cbegin(),
                                                     mTemplateInstantiations.cend(),
                                                     FindToken(tok1));
                        if (it != mTemplateInstantiations.cend())
                            addInstantiation(tok2, it->scope());
                    }
                }
            }

            // erase the instantiation tokens
            eraseTokens(aliasUsage.token()->previous(), dst->next());
            found = true;

            // erase this instantiation
            it2 = mTemplateInstantiations.erase(it2);
        }

        if (found) {
            auto *end = const_cast<Token *>(aliasDeclaration.aliasEndToken());

            // remove declaration tokens
            if (aliasDeclaration.token()->previous())
                eraseTokens(aliasDeclaration.token()->previous(), end->next() ? end->next() : end);
            else {
                eraseTokens(mTokenList.front(), end->next() ? end->next() : end);
                deleteToken(mTokenList.front());
            }

            // remove declaration
            it1 = mTemplateDeclarations.erase(it1);
        } else
            ++it1;
    }
}

bool TemplateSimplifier::instantiateMatch(const Token *instance, const std::size_t numberOfArguments, bool variadic, const char patternAfter[])
{
    assert(instance->strAt(1) == MatchCompiler::makeConstString("<"));

    auto n = templateParameters(instance->next());
    if (variadic ? (n + 1 < numberOfArguments) : (numberOfArguments != n))
        return false;

    if (patternAfter) {
        const Token *tok = instance->next()->findClosingBracket();
        if (!tok || !Token::Match(tok->next(), patternAfter))
            return false;
    }

    // nothing mismatching was found..
    return true;
}

// Utility function for TemplateSimplifier::getTemplateNamePosition, that works on template functions
bool TemplateSimplifier::getTemplateNamePositionTemplateFunction(const Token *tok, int &namepos)
{
    namepos = 1;
    while (tok && tok->next()) {
        if (match13(tok->next()))
            return false;
        // skip decltype(...)
        if (match54(tok->next())) {
            const Token * end = tok->linkAt(2)->previous();
            while (tok->next() && tok != end) {
                tok = tok->next();
                namepos++;
            }
        } else if (match25(tok->next())) {
            const Token *closing = tok->tokAt(2)->findClosingBracket();
            if (closing) {
                if (closing->strAt(1) == MatchCompiler::makeConstString("(") && TokenList::isFunctionHead(closing->next(), ";{:"))
                    return true;
                while (tok->next() && tok->next() != closing) {
                    tok = tok->next();
                    namepos++;
                }
            }
        } else if (match80(tok->next()) && TokenList::isFunctionHead(tok->tokAt(2), ";{:")) {
            return true;
        }
        tok = tok->next();
        namepos++;
    }
    return false;
}

bool TemplateSimplifier::getTemplateNamePositionTemplateVariable(const Token *tok, int &namepos)
{
    namepos = 1;
    while (tok && tok->next()) {
        if (match81(tok->next()))
            return false;
        // skip decltype(...)
        if (match54(tok->next())) {
            const Token * end = tok->linkAt(2);
            while (tok->next() && tok != end) {
                tok = tok->next();
                namepos++;
            }
        } else if (match25(tok->next())) {
            const Token *closing = tok->tokAt(2)->findClosingBracket();
            if (closing) {
                if (match12(closing->next()))
                    return true;
                while (tok->next() && tok->next() != closing) {
                    tok = tok->next();
                    namepos++;
                }
            }
        } else if (match82(tok->next())) {
            return true;
        }
        tok = tok->next();
        namepos++;
    }
    return false;
}

bool TemplateSimplifier::getTemplateNamePositionTemplateClass(const Token *tok, int &namepos)
{
    if (match83(tok)) {
        namepos = tok->strAt(1) == MatchCompiler::makeConstString("friend") ? 3 : 2;
        tok = tok->tokAt(namepos);
        while (match84(tok) ||
               (match25(tok) && match85(tok->next()->findClosingBracket()))) {
            if (tok->strAt(1) == MatchCompiler::makeConstString("::")) {
                tok = tok->tokAt(2);
                namepos += 2;
            } else {
                const Token *end = tok->next()->findClosingBracket();
                if (!end || !end->tokAt(2)) {
                    // syntax error
                    namepos = -1;
                    return true;
                }
                end = end->tokAt(2);
                do {
                    tok = tok->next();
                    namepos += 1;
                } while (tok && tok != end);
            }
        }
        return true;
    }
    return false;
}

int TemplateSimplifier::getTemplateNamePosition(const Token *tok)
{
    if (!tok || tok->str() != MatchCompiler::makeConstString(">"))
        syntaxError(tok);

    auto it = mTemplateNamePos.find(tok);
    if (!mSettings.debugtemplate && it != mTemplateNamePos.end()) {
        return it->second;
    }
    // get the position of the template name
    int namepos = 0;
    if (getTemplateNamePositionTemplateClass(tok, namepos))
        ;
    else if (match86(tok)) {
        // types may not be defined in alias template declarations
        if (!match87(tok->tokAt(4)))
            namepos = 2;
    } else if (getTemplateNamePositionTemplateVariable(tok, namepos))
        ;
    else if (!getTemplateNamePositionTemplateFunction(tok, namepos))
        namepos = -1; // Name not found
    mTemplateNamePos[tok] = namepos;
    return namepos;
}

void TemplateSimplifier::addNamespace(const TokenAndName &templateDeclaration, const Token *tok)
{
    // find start of qualification
    const Token * tokStart = tok;
    int offset = 0;
    while (match16(tokStart->tokAt(-2))) {
        tokStart = tokStart->tokAt(-2);
        offset -= 2;
    }
    // decide if namespace needs to be inserted in or appended to token list
    const bool insert = tokStart != tok;

    std::string::size_type start = 0;
    std::string::size_type end = 0;
    bool inTemplate = false;
    int level = 0;
    while ((end = templateDeclaration.scope().find(' ', start)) != std::string::npos) {
        std::string token = templateDeclaration.scope().substr(start, end - start);
        // done if scopes overlap
        if (token == tokStart->str() && tok->strAt(-1) != MatchCompiler::makeConstString("::"))
            break;
        if (token == MatchCompiler::makeConstString("<")) {
            inTemplate = true;
            ++level;
        }
        if (inTemplate) {
            if (insert)
                mTokenList.back()->tokAt(offset)->str(mTokenList.back()->strAt(offset) + token);
            else
                mTokenList.back()->str(mTokenList.back()->str() + token);
            if (token == MatchCompiler::makeConstString(">")) {
                --level;
                if (level == 0)
                    inTemplate = false;
            }
        } else {
            if (insert)
                mTokenList.back()->tokAt(offset)->insertToken(token);
            else
                mTokenList.addtoken(token, tok->linenr(), tok->column(), tok->fileIndex());
        }
        start = end + 1;
    }
    // don't add if it already exists
    std::string token = templateDeclaration.scope().substr(start, end - start);
    if (token != tokStart->str() || tok->strAt(-1) != MatchCompiler::makeConstString("::")) {
        if (insert) {
            if (!inTemplate)
                mTokenList.back()->tokAt(offset)->insertToken(templateDeclaration.scope().substr(start));
            else
                mTokenList.back()->tokAt(offset)->str(mTokenList.back()->strAt(offset) + templateDeclaration.scope().substr(start));
            mTokenList.back()->tokAt(offset)->insertToken("::");
        } else {
            if (!inTemplate)
                mTokenList.addtoken(templateDeclaration.scope().substr(start), tok->linenr(), tok->column(), tok->fileIndex());
            else
                mTokenList.back()->str(mTokenList.back()->str() + templateDeclaration.scope().substr(start));
            mTokenList.addtoken("::", tok->linenr(), tok->column(), tok->fileIndex());
        }
    }
}

bool TemplateSimplifier::alreadyHasNamespace(const TokenAndName &templateDeclaration, const Token *tok)
{
    const std::string& scope = templateDeclaration.scope();

    // get the length in tokens of the namespace
    std::string::size_type pos = 0;
    int offset = -2;

    while ((pos = scope.find("::", pos)) != std::string::npos) {
        offset -= 2;
        pos += 2;
    }

    return Token::simpleMatch(tok->tokAt(offset), scope.c_str(), scope.size());
}

struct newInstantiation {
    newInstantiation(Token* t, std::string s) : token(t), scope(std::move(s)) {}
    Token* token;
    std::string scope;
};

void TemplateSimplifier::expandTemplate(
    const TokenAndName &templateDeclaration,
    const TokenAndName &templateInstantiation,
    const std::vector<const Token *> &typeParametersInDeclaration,
    const std::string &newName,
    bool copy)
{
    bool inTemplateDefinition = false;
    const Token *startOfTemplateDeclaration = nullptr;
    const Token *endOfTemplateDefinition = nullptr;
    const Token * const templateDeclarationNameToken = templateDeclaration.nameToken();
    const Token * const templateDeclarationToken = templateDeclaration.paramEnd();
    const bool isClass = templateDeclaration.isClass();
    const bool isFunction = templateDeclaration.isFunction();
    const bool isSpecialization = templateDeclaration.isSpecialization();
    const bool isVariable = templateDeclaration.isVariable();

    std::vector<newInstantiation> newInstantiations;

    for (const Token* tok = templateInstantiation.token()->next()->findClosingBracket();
         tok && tok != templateInstantiation.token(); tok = tok->previous()) {
        if (tok->isName())
            mUsedVariables[newName].insert(tok->str());
    }

    // add forward declarations
    if (copy && isClass) {
        templateDeclaration.token()->insertTokenBefore(templateDeclarationToken->strAt(1));
        templateDeclaration.token()->insertTokenBefore(newName);
        templateDeclaration.token()->insertTokenBefore(";");
    } else if ((isFunction && (copy || isSpecialization)) ||
               (isVariable && !isSpecialization) ||
               (isClass && isSpecialization && mTemplateSpecializationMap.find(templateDeclaration.token()) != mTemplateSpecializationMap.end())) {
        Token * dst = templateDeclaration.token();
        Token * dstStart = dst->previous();
        bool isStatic = false;
        std::string scope;
        const Token * start;
        const Token * end;
        auto it = mTemplateForwardDeclarationsMap.find(dst);
        if (!isSpecialization && it != mTemplateForwardDeclarationsMap.end()) {
            dst = it->second;
            dstStart = dst->previous();
            const Token * temp1 = dst->tokAt(1)->findClosingBracket();
            const Token * temp2 = temp1->tokAt(getTemplateNamePosition(temp1));
            start = temp1->next();
            end = temp2->linkAt(1)->next();
        } else {
            if (it != mTemplateForwardDeclarationsMap.end()) {
                const auto it1 = std::find_if(mTemplateForwardDeclarations.cbegin(),
                                              mTemplateForwardDeclarations.cend(),
                                              FindToken(it->second));
                if (it1 != mTemplateForwardDeclarations.cend())
                    mMemberFunctionsToDelete.push_back(*it1);
            }

            auto it2 = mTemplateSpecializationMap.find(dst);
            if (it2 != mTemplateSpecializationMap.end()) {
                dst = it2->second;
                dstStart = dst->previous();
                isStatic = dst->next()->findClosingBracket()->strAt(1) == MatchCompiler::makeConstString("static");
                const Token * temp = templateDeclarationNameToken;
                while (match16(temp->tokAt(-2))) {
                    scope.insert(0, temp->strAt(-2) + " :: ");
                    temp = temp->tokAt(-2);
                }
            }
            start = templateDeclarationToken->next();
            end = templateDeclarationNameToken->next();
            if (end->str() == MatchCompiler::makeConstString("<"))
                end = end->findClosingBracket()->next();
            if (end->str() == MatchCompiler::makeConstString("("))
                end = end->link()->next();
            else if (isVariable && end->str() == MatchCompiler::makeConstString("=")) {
                const Token *temp = end->next();
                while (temp && temp->str() != MatchCompiler::makeConstString(";")) {
                    if (temp->link() && match88(temp))
                        temp = temp->link();
                    temp = temp->next();
                }
                end = temp;
            }
        }
        unsigned int typeindentlevel = 0;
        while (end && !(typeindentlevel == 0 && match89(end))) {
            if (match90(end))
                ++typeindentlevel;
            else if (match91(end))
                --typeindentlevel;
            end = end->next();
        }

        if (isStatic) {
            dst->insertTokenBefore("static");
            if (start) {
                dst->previous()->linenr(start->linenr());
                dst->previous()->column(start->column());
            }
        }

        std::map<const Token *, Token *> links;
        bool inAssignment = false;
        while (start && start != end) {
            if (isVariable && start->str() == MatchCompiler::makeConstString("="))
                inAssignment = true;
            unsigned int itype = 0;
            while (itype < typeParametersInDeclaration.size() && typeParametersInDeclaration[itype]->str() != start->str())
                ++itype;

            if (itype < typeParametersInDeclaration.size() && itype < mTypesUsedInTemplateInstantiation.size() &&
                (!isVariable || !match92(typeParametersInDeclaration[itype]->previous()))) {
                typeindentlevel = 0;
                std::stack<Token *> brackets1; // holds "(" and "{" tokens
                bool pointerType = false;
                Token * const dst1 = dst->previous();
                const bool isVariadicTemplateArg = templateDeclaration.isVariadic() && itype + 1 == typeParametersInDeclaration.size();
                if (isVariadicTemplateArg && match93(start))
                    start = start->tokAt(2);
                const std::string endStr(isVariadicTemplateArg ? ">" : ",>");
                for (const Token *typetok = mTypesUsedInTemplateInstantiation[itype].token();
                     typetok && (typeindentlevel > 0 || endStr.find(typetok->str()[0]) == std::string::npos);
                     typetok = typetok->next()) {
                    if (typeindentlevel == 0 && typetok->str() == MatchCompiler::makeConstString("*"))
                        pointerType = true;
                    if (match45(typetok))
                        continue;
                    if (match6(typetok) && (typetok->strAt(2) == MatchCompiler::makeConstString(">") || templateParameters(typetok->next())))
                        ++typeindentlevel;
                    else if (typeindentlevel > 0 && typetok->str() == MatchCompiler::makeConstString(">"))
                        --typeindentlevel;
                    else if (typetok->str() == MatchCompiler::makeConstString("("))
                        ++typeindentlevel;
                    else if (typetok->str() == MatchCompiler::makeConstString(")"))
                        --typeindentlevel;
                    dst->insertTokenBefore(typetok->str(), typetok->originalName(), typetok->getMacroName());
                    dst->previous()->linenr(start->linenr());
                    dst->previous()->column(start->column());
                    Token *previous = dst->previous();
                    previous->templateArgFrom(typetok);
                    previous->isSigned(typetok->isSigned());
                    previous->isUnsigned(typetok->isUnsigned());
                    previous->isLong(typetok->isLong());
                    if (match71(previous)) {
                        brackets1.push(previous);
                    } else if (previous->str() == MatchCompiler::makeConstString("}")) {
                        assert(brackets1.empty() == false);
                        assert(brackets1.top()->str() == MatchCompiler::makeConstString("{"));
                        Token::createMutualLinks(brackets1.top(), previous);
                        brackets1.pop();
                    } else if (previous->str() == MatchCompiler::makeConstString(")")) {
                        assert(brackets1.empty() == false);
                        assert(brackets1.top()->str() == MatchCompiler::makeConstString("("));
                        Token::createMutualLinks(brackets1.top(), previous);
                        brackets1.pop();
                    } else if (previous->str() == MatchCompiler::makeConstString("]")) {
                        assert(brackets1.empty() == false);
                        assert(brackets1.top()->str() == MatchCompiler::makeConstString("["));
                        Token::createMutualLinks(brackets1.top(), previous);
                        brackets1.pop();
                    }
                }
                if (pointerType && match94(dst1)) {
                    dst->insertTokenBefore("const", dst1->originalName(), dst1->getMacroName());
                    dst->previous()->linenr(start->linenr());
                    dst->previous()->column(start->column());
                    dst1->deleteThis();
                }
            } else {
                if (isSpecialization && !copy && !scope.empty() && Token::Match(start, (scope + templateDeclarationNameToken->str()).c_str())) {
                    // skip scope
                    while (start->strAt(1) != templateDeclarationNameToken->str())
                        start = start->next();
                } else if (start->str() == templateDeclarationNameToken->str() &&
                           !(templateDeclaration.isFunction() && templateDeclaration.scope().empty() &&
                             (start->strAt(-1) == MatchCompiler::makeConstString(".") || match95(start->tokAt(-2))))) {
                    if (start->strAt(1) != MatchCompiler::makeConstString("<") || Token::Match(start, newName.c_str()) || !inAssignment) {
                        dst->insertTokenBefore(newName);
                        dst->previous()->linenr(start->linenr());
                        dst->previous()->column(start->column());
                        if (start->strAt(1) == MatchCompiler::makeConstString("<"))
                            start = start->next()->findClosingBracket();
                    } else {
                        dst->insertTokenBefore(start->str());
                        dst->previous()->linenr(start->linenr());
                        dst->previous()->column(start->column());
                        newInstantiations.emplace_back(dst->previous(), templateDeclaration.scope());
                    }
                } else {
                    // check if type is a template
                    if (start->strAt(1) == MatchCompiler::makeConstString("<")) {
                        // get the instantiated name
                        const Token * closing = start->next()->findClosingBracket();
                        if (closing) {
                            std::string name;
                            const Token * type = start;
                            while (type && type != closing->next()) {
                                if (!name.empty())
                                    name += " ";
                                name += type->str();
                                type = type->next();
                            }
                            // check if type is instantiated
                            if (std::any_of(mTemplateInstantiations.cbegin(), mTemplateInstantiations.cend(), [&](const TokenAndName& inst) {
                                return Token::simpleMatch(inst.token(), name.c_str(), name.size());
                            })) {
                                // use the instantiated name
                                dst->insertTokenBefore(name);
                                dst->previous()->linenr(start->linenr());
                                dst->previous()->column(start->column());
                                start = closing;
                            }
                        }
                        // just copy the token if it wasn't instantiated
                        if (start != closing) {
                            dst->insertTokenBefore(start->str(), start->originalName(), start->getMacroName());
                            dst->previous()->linenr(start->linenr());
                            dst->previous()->column(start->column());
                            dst->previous()->isSigned(start->isSigned());
                            dst->previous()->isUnsigned(start->isUnsigned());
                            dst->previous()->isLong(start->isLong());
                        }
                    } else {
                        dst->insertTokenBefore(start->str(), start->originalName(), start->getMacroName());
                        dst->previous()->linenr(start->linenr());
                        dst->previous()->column(start->column());
                        dst->previous()->isSigned(start->isSigned());
                        dst->previous()->isUnsigned(start->isUnsigned());
                        dst->previous()->isLong(start->isLong());
                    }
                }

                if (!start)
                    continue;

                if (start->link()) {
                    if (match96(start)) {
                        links[start->link()] = dst->previous();
                    } else if (match97(start)) {
                        const auto link = utils::as_const(links).find(start);
                        // make sure link is valid
                        if (link != links.cend()) {
                            Token::createMutualLinks(link->second, dst->previous());
                            links.erase(start);
                        }
                    }
                }
            }

            start = start->next();
        }
        dst->insertTokenBefore(";");
        dst->previous()->linenr(dst->tokAt(-2)->linenr());
        dst->previous()->column(dst->tokAt(-2)->column() + 1);

        if (isVariable || isFunction)
            simplifyTemplateArgs(dstStart, dst);
    }

    if (copy && (isClass || isFunction)) {
        // check if this is an explicit instantiation
        Token * start = templateInstantiation.token();
        while (start && !match98(start->previous()))
            start = start->previous();
        if (match99(start)) {
            if (start->strAt(-1) == MatchCompiler::makeConstString("extern"))
                start = start->previous();
            mExplicitInstantiationsToDelete.emplace_back(start, "");
        }
    }

    for (Token *tok3 = mTokenList.front(); tok3; tok3 = tok3 ? tok3->next() : nullptr) {
        if (inTemplateDefinition) {
            if (!endOfTemplateDefinition) {
                if (isVariable) {
                    Token *temp = tok3->findClosingBracket();
                    if (temp) {
                        while (temp && temp->str() != MatchCompiler::makeConstString(";")) {
                            if (temp->link() && match88(temp))
                                temp = temp->link();
                            temp = temp->next();
                        }
                        endOfTemplateDefinition = temp;
                    }
                } else if (tok3->str() == MatchCompiler::makeConstString("{"))
                    endOfTemplateDefinition = tok3->link();
            }
            if (tok3 == endOfTemplateDefinition) {
                inTemplateDefinition = false;
                startOfTemplateDeclaration = nullptr;
            }
        }

        if (tok3->str()==MatchCompiler::makeConstString("template")) {
            if (tok3->next() && tok3->strAt(1)==MatchCompiler::makeConstString("<")) {
                std::vector<const Token *> localTypeParametersInDeclaration;
                getTemplateParametersInDeclaration(tok3->tokAt(2), localTypeParametersInDeclaration);
                inTemplateDefinition = localTypeParametersInDeclaration.size() == typeParametersInDeclaration.size(); // Partial specialization
            } else {
                inTemplateDefinition = false; // Only template instantiation
            }
            startOfTemplateDeclaration = tok3;
        }
        if (match14(tok3))
            tok3 = tok3->link();

        // Start of template..
        if (tok3 == templateDeclarationToken) {
            tok3 = tok3->next();
            if (tok3->str() == MatchCompiler::makeConstString("static"))
                tok3 = tok3->next();
        }

        // member function implemented outside class definition
        else if (inTemplateDefinition &&
                 match6(tok3) &&
                 templateInstantiation.name() == tok3->str() &&
                 instantiateMatch(tok3, typeParametersInDeclaration.size(), templateDeclaration.isVariadic(), ":: ~| %name% (")) {
            // there must be template..
            bool istemplate = false;
            Token * tok5 = nullptr; // start of function return type
            for (Token *prev = tok3; prev && !match18(prev); prev = prev->previous()) {
                if (prev->str() == MatchCompiler::makeConstString("template")) {
                    istemplate = true;
                    tok5 = prev;
                    break;
                }
            }
            if (!istemplate)
                continue;

            const Token *tok4 = tok3->next()->findClosingBracket();
            while (tok4 && tok4->str() != MatchCompiler::makeConstString("("))
                tok4 = tok4->next();
            if (!TokenList::isFunctionHead(tok4, ":{"))
                continue;
            // find function return type start
            tok5 = tok5->next()->findClosingBracket();
            if (tok5)
                tok5 = tok5->next();
            // copy return type
            std::stack<Token *> brackets2; // holds "(" and "{" tokens
            while (tok5 && tok5 != tok3) {
                // replace name if found
                if (match6(tok5) && tok5->str() == templateInstantiation.name()) {
                    if (copy) {
                        if (!templateDeclaration.scope().empty() && tok5->strAt(-1) != MatchCompiler::makeConstString("::"))
                            addNamespace(templateDeclaration, tok5);
                        mTokenList.addtoken(newName, tok5->linenr(), tok5->column(), tok5->fileIndex());
                        tok5 = tok5->next()->findClosingBracket();
                    } else {
                        tok5->str(newName);
                        eraseTokens(tok5, tok5->next()->findClosingBracket()->next());
                    }
                } else if (copy) {
                    bool added = false;
                    if (tok5->isName() && !match100(tok5) && !tok5->isStandardType()) {
                        // search for this token in the type vector
                        unsigned int itype = 0;
                        while (itype < typeParametersInDeclaration.size() && typeParametersInDeclaration[itype]->str() != tok5->str())
                            ++itype;

                        // replace type with given type..
                        if (itype < typeParametersInDeclaration.size() && itype < mTypesUsedInTemplateInstantiation.size()) {
                            std::stack<Token *> brackets1; // holds "(" and "{" tokens
                            for (const Token *typetok = mTypesUsedInTemplateInstantiation[itype].token();
                                 typetok && !match78(typetok);
                                 typetok = typetok->next()) {
                                if (!match45(typetok)) {
                                    mTokenList.addtoken(typetok, tok5);
                                    Token *back = mTokenList.back();
                                    if (match71(back)) {
                                        brackets1.push(back);
                                    } else if (back->str() == MatchCompiler::makeConstString("}")) {
                                        assert(brackets1.empty() == false);
                                        assert(brackets1.top()->str() == MatchCompiler::makeConstString("{"));
                                        Token::createMutualLinks(brackets1.top(), back);
                                        brackets1.pop();
                                    } else if (back->str() == MatchCompiler::makeConstString(")")) {
                                        assert(brackets1.empty() == false);
                                        assert(brackets1.top()->str() == MatchCompiler::makeConstString("("));
                                        Token::createMutualLinks(brackets1.top(), back);
                                        brackets1.pop();
                                    } else if (back->str() == MatchCompiler::makeConstString("]")) {
                                        assert(brackets1.empty() == false);
                                        assert(brackets1.top()->str() == MatchCompiler::makeConstString("["));
                                        Token::createMutualLinks(brackets1.top(), back);
                                        brackets1.pop();
                                    }
                                    back->templateArgFrom(typetok);
                                    back->isUnsigned(typetok->isUnsigned());
                                    back->isSigned(typetok->isSigned());
                                    back->isLong(typetok->isLong());
                                    added = true;
                                    break;
                                }
                            }
                        }
                    }
                    if (!added) {
                        mTokenList.addtoken(tok5);
                        Token *back = mTokenList.back();
                        if (match71(back)) {
                            brackets2.push(back);
                        } else if (back->str() == MatchCompiler::makeConstString("}")) {
                            assert(brackets2.empty() == false);
                            assert(brackets2.top()->str() == MatchCompiler::makeConstString("{"));
                            Token::createMutualLinks(brackets2.top(), back);
                            brackets2.pop();
                        } else if (back->str() == MatchCompiler::makeConstString(")")) {
                            assert(brackets2.empty() == false);
                            assert(brackets2.top()->str() == MatchCompiler::makeConstString("("));
                            Token::createMutualLinks(brackets2.top(), back);
                            brackets2.pop();
                        } else if (back->str() == MatchCompiler::makeConstString("]")) {
                            assert(brackets2.empty() == false);
                            assert(brackets2.top()->str() == MatchCompiler::makeConstString("["));
                            Token::createMutualLinks(brackets2.top(), back);
                            brackets2.pop();
                        }
                    }
                }

                tok5 = tok5->next();
            }
            if (copy) {
                if (!templateDeclaration.scope().empty() && tok3->strAt(-1) != MatchCompiler::makeConstString("::"))
                    addNamespace(templateDeclaration, tok3);
                mTokenList.addtoken(newName, tok3->linenr(), tok3->column(), tok3->fileIndex());
            }

            while (tok3 && tok3->str() != MatchCompiler::makeConstString("::"))
                tok3 = tok3->next();

            const auto it = std::find_if(mTemplateDeclarations.cbegin(),
                                         mTemplateDeclarations.cend(),
                                         FindToken(startOfTemplateDeclaration));
            if (it != mTemplateDeclarations.cend())
                mMemberFunctionsToDelete.push_back(*it);
        }

        // not part of template.. go on to next token
        else
            continue;

        std::stack<Token *> brackets; // holds "(", "[" and "{" tokens

        // FIXME use full name matching somehow
        const std::string lastName = (templateInstantiation.name().find(' ') != std::string::npos) ? templateInstantiation.name().substr(templateInstantiation.name().rfind(' ')+1) : templateInstantiation.name();

        std::stack<const Token *> templates;
        int scopeCount = 0;
        for (; tok3; tok3 = tok3->next()) {
            if (tok3->str() == MatchCompiler::makeConstString("{"))
                ++scopeCount;
            else if (tok3->str() == MatchCompiler::makeConstString("}"))
                --scopeCount;
            if (scopeCount < 0)
                break;
            if (tok3->isName() && !match100(tok3) && !tok3->isStandardType() && !match101(tok3->previous())) {
                // search for this token in the type vector
                unsigned int itype = 0;
                while (itype < typeParametersInDeclaration.size() && typeParametersInDeclaration[itype]->str() != tok3->str())
                    ++itype;

                // replace type with given type..
                if (itype < typeParametersInDeclaration.size() && itype < mTypesUsedInTemplateInstantiation.size()) {
                    unsigned int typeindentlevel = 0;
                    std::stack<Token *> brackets1; // holds "(" and "{" tokens
                    Token * const beforeTypeToken = mTokenList.back();
                    bool pointerType = false;
                    const bool isVariadicTemplateArg = templateDeclaration.isVariadic() && itype + 1 == typeParametersInDeclaration.size();
                    if (isVariadicTemplateArg && mTypesUsedInTemplateInstantiation.size() > 1 && !match102(tok3->next()))
                        continue;
                    if (isVariadicTemplateArg && match93(tok3))
                        tok3 = tok3->tokAt(2);
                    if (!isVariadicTemplateArg && copy && match103(mTypesUsedInTemplateInstantiation[itype].token()) &&
                        match104(tok3->previous())) {
                        const Token* declTok = typeParametersInDeclaration[itype];
                        while (match105(declTok->previous()))
                            declTok = declTok->previous();
                        if (match106(declTok->previous())) {
                            const Token* typetok = mTypesUsedInTemplateInstantiation[itype].token();
                            mTokenList.addtoken("(", declTok);
                            Token* const par1 = mTokenList.back();
                            while (declTok != typeParametersInDeclaration[itype]) {
                                mTokenList.addtoken(declTok);
                                declTok = declTok->next();
                            }
                            mTokenList.addtoken(")", declTok);
                            Token::createMutualLinks(par1, mTokenList.back());
                            mTokenList.addtoken(typetok, tok3);
                            for (Token* t = par1; t; t = t->next())
                                t->templateArgFrom(typetok);
                            continue;
                        }
                    }
                    const std::string endStr(isVariadicTemplateArg ? ">" : ",>");
                    for (Token *typetok = mTypesUsedInTemplateInstantiation[itype].token();
                         typetok && (typeindentlevel > 0 || endStr.find(typetok->str()[0]) == std::string::npos);
                         typetok = typetok->next()) {
                        if (typeindentlevel == 0 && typetok->str() == MatchCompiler::makeConstString("*"))
                            pointerType = true;
                        if (match45(typetok))
                            continue;
                        if (match6(typetok) &&
                            (typetok->strAt(2) == MatchCompiler::makeConstString(">") || templateParameters(typetok->next()))) {
                            brackets1.push(typetok->next());
                            ++typeindentlevel;
                        } else if (typeindentlevel > 0 && typetok->str() == MatchCompiler::makeConstString(">") && brackets1.top()->str() == MatchCompiler::makeConstString("<")) {
                            --typeindentlevel;
                            brackets1.pop();
                        } else if (match107(typetok)) {
                            brackets1.push(typetok->next());
                            ++typeindentlevel;
                        } else if (typetok->str() == MatchCompiler::makeConstString("("))
                            ++typeindentlevel;
                        else if (typetok->str() == MatchCompiler::makeConstString(")"))
                            --typeindentlevel;
                        Token *back;
                        if (copy) {
                            mTokenList.addtoken(typetok, tok3);
                            back = mTokenList.back();
                        } else
                            back = typetok;
                        if (match71(back))
                            brackets1.push(back);
                        else if (back->str() == MatchCompiler::makeConstString("}")) {
                            assert(brackets1.empty() == false);
                            assert(brackets1.top()->str() == MatchCompiler::makeConstString("{"));
                            if (copy)
                                Token::createMutualLinks(brackets1.top(), back);
                            brackets1.pop();
                        } else if (back->str() == MatchCompiler::makeConstString(")")) {
                            assert(brackets1.empty() == false);
                            assert(brackets1.top()->str() == MatchCompiler::makeConstString("("));
                            if (copy)
                                Token::createMutualLinks(brackets1.top(), back);
                            brackets1.pop();
                        } else if (back->str() == MatchCompiler::makeConstString("]")) {
                            assert(brackets1.empty() == false);
                            assert(brackets1.top()->str() == MatchCompiler::makeConstString("["));
                            if (copy)
                                Token::createMutualLinks(brackets1.top(), back);
                            brackets1.pop();
                        }
                        if (copy)
                            back->templateArgFrom(typetok);
                    }
                    if (pointerType && match94(beforeTypeToken)) {
                        mTokenList.addtoken(beforeTypeToken);
                        beforeTypeToken->deleteThis();
                    }
                    continue;
                }
            }

            // replace name..
            if (tok3->str() == lastName) {
                if (match108(tok3->next())) {
                    Token *closingBracket = tok3->next()->findClosingBracket();
                    if (closingBracket) {
                        // replace multi token name with single token name
                        if (tok3 == templateDeclarationNameToken ||
                            Token::Match(tok3, newName.c_str())) {
                            if (copy) {
                                mTokenList.addtoken(newName, tok3);
                                tok3 = closingBracket;
                            } else {
                                tok3->str(newName);
                                eraseTokens(tok3, closingBracket->next());
                            }
                            continue;
                        }
                        if (!templateDeclaration.scope().empty() &&
                            !alreadyHasNamespace(templateDeclaration, tok3) &&
                            !match109(closingBracket->next())) {
                            if (copy)
                                addNamespace(templateDeclaration, tok3);
                        }
                    }
                } else {
                    // don't modify friend
                    if (match110(tok3->tokAt(-3))) {
                        if (copy)
                            mTokenList.addtoken(tok3);
                    } else if (copy) {
                        // add namespace if necessary
                        if (!templateDeclaration.scope().empty() &&
                            (isClass ? tok3->strAt(1) != MatchCompiler::makeConstString("(") : true)) {
                            addNamespace(templateDeclaration, tok3);
                        }
                        mTokenList.addtoken(newName, tok3);
                    } else if (!match111(tok3->next()))
                        tok3->str(newName);
                    continue;
                }
            }

            // copy
            if (copy)
                mTokenList.addtoken(tok3);

            // look for template definitions
            if (match40(tok3)) {
                Token * tok2 = findTemplateDeclarationEnd(tok3);
                if (tok2)
                    templates.push(tok2);
            } else if (!templates.empty() && templates.top() == tok3)
                templates.pop();

            if (match25(tok3) &&
                !match112(tok3) &&
                match113(tok3->next()->findClosingBracket())) {
                const Token *closingBracket = tok3->next()->findClosingBracket();
                if (match114(closingBracket->next())) {
                    int num = 0;
                    const Token *par = tok3->next();
                    while (num < typeParametersInDeclaration.size() && par != closingBracket) {
                        const std::string pattern("[<,] " + typeParametersInDeclaration[num]->str() + " [,>]");
                        if (!Token::Match(par, pattern.c_str()))
                            break;
                        ++num;
                        par = par->tokAt(2);
                    }
                    if (num < typeParametersInDeclaration.size() || par != closingBracket)
                        continue;
                }

                // don't add instantiations in template definitions
                if (!templates.empty())
                    continue;

                std::string scope;
                const Token *prev = tok3;
                for (; match16(prev->tokAt(-2)); prev = prev->tokAt(-2)) {
                    if (scope.empty())
                        scope = prev->strAt(-2);
                    else
                        scope = prev->strAt(-2) + " :: " + scope;
                }

                // check for global scope
                if (prev->strAt(-1) != MatchCompiler::makeConstString("::")) {
                    // adjust for current scope
                    std::string token_scope = tok3->scopeInfo()->name;
                    const std::string::size_type end = token_scope.find_last_of(" :: ");
                    if (end != std::string::npos) {
                        token_scope.resize(end);
                        if (scope.empty())
                            scope = std::move(token_scope);
                        else
                            scope = token_scope + " :: " + scope;
                    }
                }

                if (copy)
                    newInstantiations.emplace_back(mTokenList.back(), std::move(scope));
                else if (!inTemplateDefinition)
                    newInstantiations.emplace_back(tok3, std::move(scope));
            }

            // link() newly tokens manually
            else if (copy) {
                if (tok3->str() == MatchCompiler::makeConstString("{")) {
                    brackets.push(mTokenList.back());
                } else if (tok3->str() == MatchCompiler::makeConstString("(")) {
                    brackets.push(mTokenList.back());
                } else if (tok3->str() == MatchCompiler::makeConstString("[")) {
                    brackets.push(mTokenList.back());
                } else if (tok3->str() == MatchCompiler::makeConstString("}")) {
                    assert(brackets.empty() == false);
                    assert(brackets.top()->str() == MatchCompiler::makeConstString("{"));
                    Token::createMutualLinks(brackets.top(), mTokenList.back());
                    brackets.pop();
                    if (brackets.empty() && !match115(tok3)) {
                        inTemplateDefinition = false;
                        if (isClass && tok3->strAt(1) == MatchCompiler::makeConstString(";")) {
                            const Token* tokSemicolon = tok3->next();
                            mTokenList.addtoken(tokSemicolon, tokSemicolon->linenr(), tokSemicolon->column(), tokSemicolon->fileIndex());
                        }
                        break;
                    }
                } else if (tok3->str() == MatchCompiler::makeConstString(")")) {
                    assert(brackets.empty() == false);
                    assert(brackets.top()->str() == MatchCompiler::makeConstString("("));
                    Token::createMutualLinks(brackets.top(), mTokenList.back());
                    brackets.pop();
                } else if (tok3->str() == MatchCompiler::makeConstString("]")) {
                    assert(brackets.empty() == false);
                    assert(brackets.top()->str() == MatchCompiler::makeConstString("["));
                    Token::createMutualLinks(brackets.top(), mTokenList.back());
                    brackets.pop();
                }
            }
        }

        assert(brackets.empty());
    }

    // add new instantiations
    for (const auto & inst : newInstantiations) {
        if (!inst.token)
            continue;
        simplifyTemplateArgs(inst.token->tokAt(2), inst.token->next()->findClosingBracket(), &newInstantiations);
        // only add recursive instantiation if its arguments are a constant expression
        if (templateDeclaration.name() != inst.token->str() ||
            (inst.token->tokAt(2)->isNumber() || inst.token->tokAt(2)->isStandardType()))
            mTemplateInstantiations.emplace_back(inst.token, inst.scope);
    }
}

static bool isLowerThanLogicalAnd(const Token *lower)
{
    return lower->isAssignmentOp() || match116(lower);
}
static bool isLowerThanOr(const Token* lower)
{
    return isLowerThanLogicalAnd(lower) || lower->str() == MatchCompiler::makeConstString("&&");
}
static bool isLowerThanXor(const Token* lower)
{
    return isLowerThanOr(lower) || lower->str() == MatchCompiler::makeConstString("|");
}
static bool isLowerThanAnd(const Token* lower)
{
    return isLowerThanXor(lower) || lower->str() == MatchCompiler::makeConstString("^");
}
static bool isLowerThanShift(const Token* lower)
{
    return isLowerThanAnd(lower) || lower->str() == MatchCompiler::makeConstString("&");
}
static bool isLowerThanPlusMinus(const Token* lower)
{
    return isLowerThanShift(lower) || match117(lower);
}
static bool isLowerThanMulDiv(const Token* lower)
{
    return isLowerThanPlusMinus(lower) || match118(lower);
}
static bool isLowerEqualThanMulDiv(const Token* lower)
{
    return isLowerThanMulDiv(lower) || match119(lower);
}


bool TemplateSimplifier::simplifyNumericCalculations(Token *tok, bool isTemplate)
{
    bool ret = false;
    // (1-2)
    while (tok->tokAt(3) && tok->isNumber() && tok->tokAt(2)->isNumber()) { // %any% %num% %any% %num% %any%
        const Token *before = tok->previous();
        if (!before)
            break;
        const Token* op = tok->next();
        const Token* after = tok->tokAt(3);
        const std::string &num1 = op->strAt(-1);
        const std::string &num2 = op->strAt(1);
        if (match120(before) && (num2 != MatchCompiler::makeConstString("0")) && num1 == MathLib::multiply(num2, MathLib::divide(num1, num2))) {
            // Division where result is a whole number
        } else if (!((op->str() == MatchCompiler::makeConstString("*") && (isLowerThanMulDiv(before) || before->str() == MatchCompiler::makeConstString("*")) && isLowerEqualThanMulDiv(after)) || // associative
                     (match121(op) && isLowerThanMulDiv(before) && isLowerEqualThanMulDiv(after)) || // NOT associative
                     (match122(op) && isLowerThanMulDiv(before) && isLowerThanMulDiv(after)) || // Only partially (+) associative, but handled later
                     (match123(op) && isLowerThanShift(before) && isLowerThanPlusMinus(after)) || // NOT associative
                     (op->str() == MatchCompiler::makeConstString("&") && isLowerThanShift(before) && isLowerThanShift(after)) || // associative
                     (op->str() == MatchCompiler::makeConstString("^") && isLowerThanAnd(before) && isLowerThanAnd(after)) || // associative
                     (op->str() == MatchCompiler::makeConstString("|") && isLowerThanXor(before) && isLowerThanXor(after)) || // associative
                     (op->str() == MatchCompiler::makeConstString("&&") && isLowerThanOr(before) && isLowerThanOr(after)) ||
                     (op->str() == MatchCompiler::makeConstString("||") && isLowerThanLogicalAnd(before) && isLowerThanLogicalAnd(after))))
            break;

        // Don't simplify "%num% / 0"
        if (match124(op)) {
            if (isTemplate)
                throw InternalError(op, "Instantiation error: Divide by zero in template instantiation.", InternalError::INSTANTIATION);
            return ret;
        }

        // Integer operations
        if (match125(op)) {
            // Don't simplify if operand is negative, shifting with negative
            // operand is UB. Bitmasking with negative operand is implementation
            // defined behaviour.
            if (MathLib::isNegative(num1) || MathLib::isNegative(num2))
                break;

            const MathLib::value v1(num1);
            const MathLib::value v2(num2);

            if (!v1.isInt() || !v2.isInt())
                break;

            switch (op->str()[0]) {
            case '<':
                tok->str((v1 << v2).str());
                break;
            case '>':
                tok->str((v1 >> v2).str());
                break;
            case '&':
                tok->str((v1 & v2).str());
                break;
            case '|':
                tok->str((v1 | v2).str());
                break;
            case '^':
                tok->str((v1 ^ v2).str());
                break;
            }
        }

        // Logical operations
        else if (match126(op)) {
            const bool op1 = !MathLib::isNullValue(num1);
            const bool op2 = !MathLib::isNullValue(num2);
            const bool result = (op->str() == MatchCompiler::makeConstString("||")) ? (op1 || op2) : (op1 && op2);
            tok->str(result ? "1" : "0");
        }

        else if (match127(tok->previous()))
            tok->str(MathLib::add(num1, num2));
        else if (match128(tok->previous()))
            tok->str(MathLib::subtract(num1, num2));
        else {
            try {
                tok->str(MathLib::calculate(num1, num2, op->str()[0]));
            } catch (InternalError &e) {
                e.token = tok;
                throw;
            }
        }

        tok->deleteNext(2);

        ret = true;
    }

    return ret;
}

static Token *skipTernaryOp(Token *tok, const Token *backToken)
{
    unsigned int colonLevel = 1;
    while (nullptr != (tok = tok->next())) {
        if (tok->str() == MatchCompiler::makeConstString("?")) {
            ++colonLevel;
        } else if (tok->str() == MatchCompiler::makeConstString(":")) {
            --colonLevel;
            if (colonLevel == 0) {
                tok = tok->next();
                break;
            }
        }
        if (tok->link() && tok->str() == MatchCompiler::makeConstString("("))
            tok = tok->link();
        else if (match129(tok->next()) || tok->next() == backToken)
            break;
    }
    if (colonLevel > 0) // Ticket #5214: Make sure the ':' matches the proper '?'
        return nullptr;
    return tok;
}

static void invalidateInst(const Token* beg, const Token* end, std::vector<newInstantiation>* newInst) {
    if (!newInst)
        return;
    for (auto& inst : *newInst) {
        for (const Token* tok = beg; tok != end; tok = tok->next())
            if (inst.token == tok) {
                inst.token = nullptr;
                break;
            }
    }
}

void TemplateSimplifier::simplifyTemplateArgs(Token *start, const Token *end, std::vector<newInstantiation>* newInst)
{
    // start could be erased so use the token before start if available
    Token * first = (start && start->previous()) ? start->previous() : mTokenList.front();
    bool again = true;

    while (again) {
        again = false;

        for (Token *tok = first->next(); tok && tok != end; tok = tok->next()) {
            if (tok->str() == MatchCompiler::makeConstString("sizeof")) {
                // sizeof('x')
                if (match130(tok->next())) {
                    tok->deleteNext();
                    tok->deleteThis();
                    tok->deleteNext();
                    tok->str(std::to_string(1));
                    again = true;
                }

                // sizeof ("text")
                else if (match131(tok->next())) {
                    tok->deleteNext();
                    tok->deleteThis();
                    tok->deleteNext();
                    tok->str(std::to_string(Token::getStrLength(tok) + 1));
                    again = true;
                }

                else if (match132(tok->next())) {
                    tok->str(std::to_string(mTokenizer.sizeOfType(tok->tokAt(3))));
                    tok->deleteNext(4);
                    again = true;
                } else if (match133(tok->next())) {
                    tok->str(std::to_string(mTokenizer.sizeOfType(tok->tokAt(2))));
                    tok->deleteNext(3);
                    again = true;
                } else if (match134(tok->next())) {
                    const unsigned int size = mTokenizer.sizeOfType(tok->tokAt(2));
                    if (size > 0) {
                        tok->str(std::to_string(size));
                        tok->deleteNext(3);
                        again = true;
                    }
                } else if (tok->strAt(1) == MatchCompiler::makeConstString("(")) {
                    tok = tok->linkAt(1);
                }
            } else if (match135(tok) &&
                       MathLib::isInt(tok->str()) &&
                       MathLib::isInt(tok->strAt(2))) {
                if ((match136(tok->previous()) || tok == start) &&
                    (match137(tok->tokAt(3)) || tok->tokAt(3) == end)) {
                    const MathLib::bigint op1(MathLib::toBigNumber(tok));
                    const std::string &cmp(tok->strAt(1));
                    const MathLib::bigint op2(MathLib::toBigNumber(tok->tokAt(2)));

                    std::string result;

                    if (cmp == MatchCompiler::makeConstString("=="))
                        result = bool_to_string(op1 == op2);
                    else if (cmp == MatchCompiler::makeConstString("!="))
                        result = bool_to_string(op1 != op2);
                    else if (cmp == MatchCompiler::makeConstString("<="))
                        result = bool_to_string(op1 <= op2);
                    else if (cmp == MatchCompiler::makeConstString(">="))
                        result = bool_to_string(op1 >= op2);
                    else if (cmp == MatchCompiler::makeConstString("<"))
                        result = bool_to_string(op1 < op2);
                    else
                        result = bool_to_string(op1 > op2);

                    tok->str(result);
                    tok->deleteNext(2);
                    again = true;
                    tok = tok->previous();
                }
            } else if (match138(tok)) {
                tok = tok->previous();
                again = true;
                tok->deleteNext(3);
            }
        }

        if (simplifyCalculations(first->next(), end))
            again = true;

        for (Token *tok = first->next(); tok && tok != end; tok = tok->next()) {
            if (tok->str() == MatchCompiler::makeConstString("?") &&
                ((tok->previous()->isNumber() || tok->previous()->isBoolean()) ||
                 match139(tok->tokAt(-3)))) {
                const int offset = (tok->strAt(-1) == MatchCompiler::makeConstString(")")) ? 2 : 1;

                // Find the token ":" then go to the next token
                Token *colon = skipTernaryOp(tok, end);
                if (!colon || colon->strAt(-1) != MatchCompiler::makeConstString(":") || !colon->next())
                    continue;

                //handle the GNU extension: "x ? : y" <-> "x ? x : y"
                if (colon->previous() == tok->next())
                    tok->insertToken(tok->strAt(-offset));

                // go back before the condition, if possible
                tok = tok->tokAt(-2);
                if (offset == 2) {
                    // go further back before the "("
                    tok = tok->tokAt(-2);
                    //simplify the parentheses
                    tok->deleteNext();
                    tok->next()->deleteNext();
                }

                if (match140(tok->next())) {
                    invalidateInst(tok->next(), colon, newInst);
                    // Use code after colon, remove code before it.
                    Token::eraseTokens(tok, colon);

                    tok = tok->next();
                    again = true;
                }

                // The condition is true. Delete the operator after the ":"..
                else {
                    // delete the condition token and the "?"
                    tok->deleteNext(2);

                    unsigned int ternaryOplevel = 0;
                    for (const Token *endTok = colon; endTok; endTok = endTok->next()) {
                        if (match74(endTok))
                            endTok = endTok->link();
                        else if (endTok->str() == MatchCompiler::makeConstString("<") && (endTok->strAt(1) == MatchCompiler::makeConstString(">") || templateParameters(endTok)))
                            endTok = endTok->findClosingBracket();
                        else if (endTok->str() == MatchCompiler::makeConstString("?"))
                            ++ternaryOplevel;
                        else if (match141(endTok)) {
                            if (endTok->str() == MatchCompiler::makeConstString(":") && ternaryOplevel)
                                --ternaryOplevel;
                            else if (endTok->str() == MatchCompiler::makeConstString(">") && !end)
                                ;
                            else {
                                invalidateInst(colon->tokAt(-1), endTok, newInst);
                                Token::eraseTokens(colon->tokAt(-2), endTok);
                                again = true;
                                break;
                            }
                        }
                    }
                }
            }
        }

        for (Token *tok = first->next(); tok && tok != end; tok = tok->next()) {
            if (tok->isKeyword() && endsWith(tok->str(), "_cast")) {
                Token* tok2 = tok->next()->findClosingBracket();
                if (!match57(tok2))
                    syntaxError(tok);
                tok = tok2->linkAt(1);
                continue;
            }
            if (match142(tok) &&
                (tok->previous() && !tok->previous()->isName())) {
                tok->deleteThis();
                tok->deleteNext();
                again = true;
            }
        }
    }
}

static bool validTokenStart(bool bounded, const Token *tok, const Token *frontToken, int offset)
{
    if (!bounded)
        return true;

    if (frontToken)
        frontToken = frontToken->previous();

    while (tok && offset <= 0) {
        if (tok == frontToken)
            return false;
        ++offset;
        tok = tok->previous();
    }

    return tok && offset > 0;
}

static bool validTokenEnd(bool bounded, const Token *tok, const Token *backToken, int offset)
{
    if (!bounded)
        return true;

    while (tok && offset >= 0) {
        if (tok == backToken)
            return false;
        --offset;
        tok = tok->next();
    }

    return tok && offset < 0;
}

// TODO: This is not the correct class for simplifyCalculations(), so it
// should be moved away.
bool TemplateSimplifier::simplifyCalculations(Token* frontToken, const Token *backToken, bool isTemplate)
{
    bool ret = false;
    const bool bounded = frontToken || backToken;
    if (!frontToken) {
        frontToken = mTokenList.front();
    }
    for (Token *tok = frontToken; tok && tok != backToken; tok = tok->next()) {
        // Remove parentheses around variable..
        // keep parentheses here: dynamic_cast<Fred *>(p);
        // keep parentheses here: A operator * (int);
        // keep parentheses here: int ( * ( * f ) ( ... ) ) (int) ;
        // keep parentheses here: int ( * * ( * compilerHookVector ) (void) ) ( ) ;
        // keep parentheses here: operator new [] (size_t);
        // keep parentheses here: Functor()(a ... )
        // keep parentheses here: ) ( var ) ;
        if (validTokenEnd(bounded, tok, backToken, 4) &&
            (match143(tok->next()) ||
             (match144(tok->next()) &&
              (tok->tokAt(2)->varId()>0 ||
               !match145(tok->tokAt(4))))) &&
            !tok->isName() &&
            tok->str() != MatchCompiler::makeConstString(">") &&
            tok->str() != MatchCompiler::makeConstString(")") &&
            tok->str() != MatchCompiler::makeConstString("]")) {
            tok->deleteNext();
            tok = tok->next();
            tok->deleteNext();
            ret = true;
        }

        if (validTokenEnd(bounded, tok, backToken, 3) &&
            match146(tok->previous())) {
            tok->str(MathLib::toString(MathLib::toBigNumber(tok)));
        }

        if (validTokenEnd(bounded, tok, backToken, 5) &&
            match147(tok)) {
            tok->deleteThis();
            tok->deleteThis();
            tok->deleteNext();
            tok->deleteNext();
            tok->deleteNext();
            ret = true;
        }

        if (validTokenEnd(bounded, tok, backToken, 3) &&
            match148(tok)) {
            tok->deleteThis();
            tok->deleteThis();
            if (tok->isBoolean())
                tok->str("bool");
            else if (MathLib::isFloat(tok->str())) {
                // MathLib::getSuffix doesn't work for floating point numbers
                const char suffix = tok->str().back();
                if (suffix == 'f' || suffix == 'F')
                    tok->str("float");
                else if (suffix == 'l' || suffix == 'L') {
                    tok->str("double");
                    tok->isLong(true);
                } else
                    tok->str("double");
            } else if (MathLib::isInt(tok->str())) {
                std::string suffix = MathLib::getSuffix(tok->str());
                if (suffix.find("LL") != std::string::npos) {
                    tok->str("long");
                    tok->isLong(true);
                } else if (suffix.find('L') != std::string::npos)
                    tok->str("long");
                else
                    tok->str("int");
                tok->isUnsigned(suffix.find('U') != std::string::npos);
            }
            tok->deleteNext();
            ret = true;
        }

        if (validTokenEnd(bounded, tok, backToken, 2) &&
            (match149(tok) ||
             match150(tok))) {
            tok->str("0"); // FIXME add type suffix
            tok->isSigned(false);
            tok->isUnsigned(false);
            tok->isLong(false);
            tok->deleteNext();
            tok->deleteNext();
            ret = true;
        }

        if (tok && tok->isNumber()) {
            if (validTokenEnd(bounded, tok, backToken, 2) &&
                simplifyNumericCalculations(tok, isTemplate)) {
                ret = true;
                Token *prev = tok->tokAt(-2);
                while (validTokenStart(bounded, tok, frontToken, -2) &&
                       prev && simplifyNumericCalculations(prev, isTemplate)) {
                    tok = prev;
                    prev = prev->tokAt(-2);
                }
            }

            // Remove redundant conditions (0&&x) (1||x)
            if (validTokenStart(bounded, tok, frontToken, -1) &&
                validTokenEnd(bounded, tok, backToken, 1) &&
                (match151(tok->previous()) ||
                 match152(tok->previous()))) {
                unsigned int par = 0;
                const Token *tok2 = tok;
                const bool andAnd = (tok->strAt(1) == MatchCompiler::makeConstString("&&"));
                for (; tok2; tok2 = tok2->next()) {
                    if (tok2->str() == MatchCompiler::makeConstString("(") || tok2->str() == MatchCompiler::makeConstString("["))
                        ++par;
                    else if (tok2->str() == MatchCompiler::makeConstString(")") || tok2->str() == MatchCompiler::makeConstString("]")) {
                        if (par == 0)
                            break;
                        --par;
                    } else if (par == 0 && isLowerThanLogicalAnd(tok2) && (andAnd || tok2->str() != MatchCompiler::makeConstString("||")))
                        break;
                }
                if (tok2) {
                    eraseTokens(tok, tok2);
                    ret = true;
                }
                continue;
            }

            if (tok->str() == MatchCompiler::makeConstString("0") && validTokenStart(bounded, tok, frontToken, -1)) {
                if (validTokenEnd(bounded, tok, backToken, 1) &&
                    ((match153(tok->previous()) && isLowerThanMulDiv(tok->next())) ||
                     (match154(tok->previous()) && isLowerThanXor(tok->next())))) {
                    tok = tok->previous();
                    if (match155(tok->tokAt(-4)) &&
                        tok->strAt(-3) == tok->strAt(-1)) {
                        tok = tok->tokAt(-4);
                        tok->deleteNext(5);
                    } else {
                        tok = tok->previous();
                        tok->deleteNext(2);
                    }
                    ret = true;
                } else if (validTokenEnd(bounded, tok, backToken, 1) &&
                           (match156(tok->previous()) ||
                            match157(tok->previous()))) {
                    tok = tok->previous();
                    tok->deleteNext(2);
                    ret = true;
                } else if ((((match158(tok->previous()) ||
                              match159(tok->previous())) &&
                             validTokenEnd(bounded, tok, backToken, 3)) ||
                            (((match160(tok->previous()) ||
                               match161(tok->previous())) &&
                              validTokenEnd(bounded, tok, backToken, 2))))) {
                    tok->deleteNext();
                    if (tok->strAt(1) == MatchCompiler::makeConstString("("))
                        eraseTokens(tok, tok->linkAt(1));
                    tok->deleteNext();
                    ret = true;
                } else if (validTokenEnd(bounded, tok, backToken, 4) &&
                           (match162(tok->previous()) ||
                            match163(tok->previous()))) {
                    tok->deleteNext();
                    tok->deleteNext();
                    if (tok->strAt(1) == MatchCompiler::makeConstString("("))
                        eraseTokens(tok, tok->linkAt(1));
                    tok->deleteNext();
                    ret = true;
                }
            }

            if (tok->str() == MatchCompiler::makeConstString("1") && validTokenStart(bounded, tok, frontToken, -1)) {
                if (validTokenEnd(bounded, tok, backToken, 3) &&
                    (match164(tok->previous()) ||
                     match165(tok->previous()))) {
                    tok->deleteNext();
                    if (tok->strAt(1) == MatchCompiler::makeConstString("("))
                        eraseTokens(tok, tok->linkAt(1));
                    tok->deleteNext();
                    ret = true;
                } else if (validTokenEnd(bounded, tok, backToken, 4) &&
                           (match166(tok->previous()) ||
                            match167(tok->previous()))) {
                    tok->deleteNext();
                    tok->deleteNext();
                    if (tok->strAt(1) == MatchCompiler::makeConstString("("))
                        eraseTokens(tok, tok->linkAt(1));
                    tok->deleteNext();
                    ret = true;
                }
            }

            if ((match168(tok->tokAt(-2)) &&
                 validTokenStart(bounded, tok, frontToken, -2)) ||
                (match169(tok->previous()) &&
                 validTokenStart(bounded, tok, frontToken, -1))) {
                tok = tok->previous();
                if (tok->str() == MatchCompiler::makeConstString("*"))
                    tok = tok->previous();
                tok->deleteNext(2);
                ret = true;
            }

            // Remove parentheses around number..
            if (validTokenStart(bounded, tok, frontToken, -2) &&
                match170(tok->tokAt(-2)) &&
                tok->strAt(-2) != MatchCompiler::makeConstString(">")) {
                tok = tok->previous();
                tok->deleteThis();
                tok->deleteNext();
                ret = true;
            }

            if (validTokenStart(bounded, tok, frontToken, -1) &&
                validTokenEnd(bounded, tok, backToken, 1) &&
                (match171(tok->previous()) ||
                 match172(tok->previous()))) {
                tok = tok->previous();
                if (match173(tok))
                    tok = tok->previous();
                tok->deleteNext(2);
                ret = true;
            }

            if (validTokenEnd(bounded, tok, backToken, 2) &&
                match135(tok) &&
                MathLib::isInt(tok->str()) &&
                MathLib::isInt(tok->strAt(2))) {
                if (validTokenStart(bounded, tok, frontToken, -1) &&
                    match174(tok->previous()) &&
                    match137(tok->tokAt(3))) {
                    const MathLib::bigint op1(MathLib::toBigNumber(tok));
                    const std::string &cmp(tok->strAt(1));
                    const MathLib::bigint op2(MathLib::toBigNumber(tok->tokAt(2)));

                    std::string result;

                    if (cmp == MatchCompiler::makeConstString("=="))
                        result = (op1 == op2) ? "1" : "0";
                    else if (cmp == MatchCompiler::makeConstString("!="))
                        result = (op1 != op2) ? "1" : "0";
                    else if (cmp == MatchCompiler::makeConstString("<="))
                        result = (op1 <= op2) ? "1" : "0";
                    else if (cmp == MatchCompiler::makeConstString(">="))
                        result = (op1 >= op2) ? "1" : "0";
                    else if (cmp == MatchCompiler::makeConstString("<"))
                        result = (op1 < op2) ? "1" : "0";
                    else
                        result = (op1 > op2) ? "1" : "0";

                    tok->str(result);
                    tok->deleteNext(2);
                    ret = true;
                    tok = tok->previous();
                }
            }
        }
    }
    return ret;
}

void TemplateSimplifier::getTemplateParametersInDeclaration(
    const Token * tok,
    std::vector<const Token *> & typeParametersInDeclaration)
{
    assert(tok->strAt(-1) == MatchCompiler::makeConstString("<"));

    typeParametersInDeclaration.clear();
    const Token *end = tok->previous()->findClosingBracket();
    bool inDefaultValue = false;
    for (; tok && tok!= end; tok = tok->next()) {
        if (match40(tok)) {
            const Token *closing = tok->next()->findClosingBracket();
            if (closing)
                tok = closing->next();
        } else if (tok->link() && match71(tok))
            tok = tok->link();
        else if (match175(tok)) {
            if (!inDefaultValue) {
                typeParametersInDeclaration.push_back(tok);
                if (tok->strAt(1) == MatchCompiler::makeConstString("="))
                    inDefaultValue = true;
            }
        } else if (inDefaultValue) {
            if (tok->str() == MatchCompiler::makeConstString(","))
                inDefaultValue = false;
            else if (tok->str() == MatchCompiler::makeConstString("<")) {
                const Token *closing = tok->findClosingBracket();
                if (closing)
                    tok = closing;
            }
        }
    }
}

bool TemplateSimplifier::matchSpecialization(
    const Token *templateDeclarationNameToken,
    const Token *templateInstantiationNameToken,
    const std::list<const Token *> & specializations)
{
    // Is there a matching specialization?
    for (auto it = specializations.cbegin(); it != specializations.cend(); ++it) {
        if (!match6(*it))
            continue;
        const Token *startToken = (*it);
        while (startToken->previous() && !match18(startToken->previous()))
            startToken = startToken->previous();
        if (!match40(startToken))
            continue;
        // cppcheck-suppress shadowFunction - TODO: fix this
        std::vector<const Token *> templateParameters;
        getTemplateParametersInDeclaration(startToken->tokAt(2), templateParameters);

        const Token *instToken = templateInstantiationNameToken->tokAt(2);
        const Token *declToken = (*it)->tokAt(2);
        const Token * const endToken = (*it)->next()->findClosingBracket();
        if (!endToken)
            continue;
        while (declToken != endToken) {
            if (declToken->str() != instToken->str() ||
                declToken->isSigned() != instToken->isSigned() ||
                declToken->isUnsigned() != instToken->isUnsigned() ||
                declToken->isLong() != instToken->isLong()) {
                int nr = 0;
                while (nr < templateParameters.size() && templateParameters[nr]->str() != declToken->str())
                    ++nr;

                if (nr == templateParameters.size())
                    break;
            }
            declToken = declToken->next();
            instToken = instToken->next();
        }

        if (declToken && instToken && declToken == endToken && instToken->str() == MatchCompiler::makeConstString(">")) {
            // specialization matches.
            return templateDeclarationNameToken == *it;
        }
    }

    // No specialization matches. Return true if the declaration is not a specialization.
    return match176(templateDeclarationNameToken) &&
           (templateDeclarationNameToken->str().find('<') == std::string::npos);
}

std::string TemplateSimplifier::getNewName(
    Token *tok2,
    std::list<std::string> &typeStringsUsedInTemplateInstantiation)
{
    std::string typeForNewName;
    unsigned int indentlevel = 0;
    const Token * endToken = tok2->next()->findClosingBracket();
    for (Token *tok3 = tok2->tokAt(2); tok3 != endToken && (indentlevel > 0 || tok3->str() != MatchCompiler::makeConstString(">")); tok3 = tok3->next()) {
        // #2721 - unhandled [ => bail out
        if (tok3->str() == MatchCompiler::makeConstString("[") && !match177(tok3->next())) {
            typeForNewName.clear();
            break;
        }
        if (!tok3->next()) {
            typeForNewName.clear();
            break;
        }
        if (match178(tok3->tokAt(-2)) && (tok3->strAt(1) == MatchCompiler::makeConstString(">") || templateParameters(tok3)))
            ++indentlevel;
        else if (indentlevel > 0 && match179(tok3))
            --indentlevel;
        else if (indentlevel == 0 && match106(tok3->previous())) {
            mTypesUsedInTemplateInstantiation.emplace_back(tok3, "");
        }
        if (match14(tok3))
            ++indentlevel;
        else if (match180(tok3))
            --indentlevel;
        const bool constconst = tok3->str() == MatchCompiler::makeConstString("const") && tok3->strAt(1) == MatchCompiler::makeConstString("const");
        if (!constconst) {
            if (tok3->isUnsigned())
                typeStringsUsedInTemplateInstantiation.emplace_back("unsigned");
            else if (tok3->isSigned())
                typeStringsUsedInTemplateInstantiation.emplace_back("signed");
            if (tok3->isLong())
                typeStringsUsedInTemplateInstantiation.emplace_back("long");
            typeStringsUsedInTemplateInstantiation.push_back(tok3->str());
        }
        // add additional type information
        if (!constconst && !match181(tok3)) {
            if (!typeForNewName.empty())
                typeForNewName += ' ';
            if (tok3->isUnsigned())
                typeForNewName += "unsigned ";
            else if (tok3->isSigned())
                typeForNewName += "signed ";
            if (tok3->isLong()) {
                typeForNewName += "long ";
            }
            typeForNewName += tok3->str();
        }
    }

    return typeForNewName;
}

bool TemplateSimplifier::simplifyTemplateInstantiations(
    const TokenAndName &templateDeclaration,
    const std::list<const Token *> &specializations,
    const std::time_t maxtime,
    std::set<std::string> &expandedtemplates)
{
    // this variable is not used at the moment. The intention was to
    // allow continuous instantiations until all templates has been expanded
    //bool done = false;

    // Contains tokens such as "T"
    std::vector<const Token *> typeParametersInDeclaration;
    getTemplateParametersInDeclaration(templateDeclaration.token()->tokAt(2), typeParametersInDeclaration);
    const bool printDebug = mSettings.debugwarnings;
    const bool specialized = templateDeclaration.isSpecialization();
    const bool isfunc = templateDeclaration.isFunction();
    const bool isVar = templateDeclaration.isVariable();

    // locate template usage..
    std::string::size_type numberOfTemplateInstantiations = mTemplateInstantiations.size();
    unsigned int recursiveCount = 0;

    bool instantiated = false;

    for (const TokenAndName &instantiation : mTemplateInstantiations) {
        // skip deleted instantiations
        if (!instantiation.token())
            continue;
        if (numberOfTemplateInstantiations != mTemplateInstantiations.size()) {
            numberOfTemplateInstantiations = mTemplateInstantiations.size();
            ++recursiveCount;
            if (recursiveCount > mSettings.maxTemplateRecursion) {
                if (mSettings.severity.isEnabled(Severity::information)) {
                    std::list<std::string> typeStringsUsedInTemplateInstantiation;
                    const std::string typeForNewName = templateDeclaration.name() + "<" + getNewName(instantiation.token(), typeStringsUsedInTemplateInstantiation) + ">";

                    const std::list<const Token *> callstack(1, instantiation.token());
                    const ErrorMessage errmsg(callstack,
                                              &mTokenizer.list,
                                              Severity::information,
                                              "templateRecursion",
                                              "TemplateSimplifier: max template recursion ("
                                              + std::to_string(mSettings.maxTemplateRecursion)
                                              + ") reached for template '"+typeForNewName+"'. You might want to limit Cppcheck recursion.",
                                              Certainty::normal);
                    mErrorLogger.reportErr(errmsg);
                }

                // bail out..
                break;
            }
        }

        // already simplified
        if (!match6(instantiation.token()))
            continue;

        if (!((instantiation.fullName() == templateDeclaration.fullName()) ||
              (instantiation.name() == templateDeclaration.name() &&
               instantiation.fullName() == templateDeclaration.scope()))) {
            // FIXME: fallback to not matching scopes until type deduction works

            // names must match
            if (instantiation.name() != templateDeclaration.name())
                continue;

            // scopes must match when present
            if (!instantiation.scope().empty() && !templateDeclaration.scope().empty())
                continue;
        }

        // make sure constructors and destructors don't match each other
        if (templateDeclaration.nameToken()->strAt(-1) == MatchCompiler::makeConstString("~") && instantiation.token()->strAt(-1) != MatchCompiler::makeConstString("~"))
            continue;

        // template families should match
        if (!instantiation.isFunction() && templateDeclaration.isFunction()) {
            // there are exceptions
            if (!match54(instantiation.token()->tokAt(-2)))
                continue;
        }

        if (templateDeclaration.isFunction() && instantiation.isFunction()) {
            std::vector<const Token*> declFuncArgs;
            getFunctionArguments(templateDeclaration.nameToken(), declFuncArgs);
            std::vector<const Token*> instFuncParams;
            getFunctionArguments(instantiation.token(), instFuncParams);

            if (declFuncArgs.size() != instFuncParams.size()) {
                // check for default arguments
                const Token* tok = templateDeclaration.nameToken()->tokAt(2);
                const Token* end = templateDeclaration.nameToken()->linkAt(1);
                size_t count = 0;
                for (; tok != end; tok = tok->next()) {
                    if (tok->str() == MatchCompiler::makeConstString("="))
                        count++;
                }

                if (instFuncParams.size() < (declFuncArgs.size() - count) || instFuncParams.size() > declFuncArgs.size())
                    continue;
            }
        }

        // A global function can't be called through a pointer.
        if (templateDeclaration.isFunction() && templateDeclaration.scope().empty() &&
            (instantiation.token()->strAt(-1) == MatchCompiler::makeConstString(".") ||
             match95(instantiation.token()->tokAt(-2))))
            continue;

        if (!matchSpecialization(templateDeclaration.nameToken(), instantiation.token(), specializations))
            continue;

        Token * const tok2 = instantiation.token();
        if ((mSettings.reportProgress != -1) && !mTokenList.getFiles().empty())
            mErrorLogger.reportProgress(mTokenList.getFiles()[0], "TemplateSimplifier::simplifyTemplateInstantiations()", tok2->progressValue());

        if (maxtime > 0 && std::time(nullptr) > maxtime) {
            if (mSettings.debugwarnings) {
                ErrorMessage::FileLocation loc(mTokenList.getFiles()[0], 0, 0);
                ErrorMessage errmsg({std::move(loc)},
                                    "",
                                    Severity::debug,
                                    "Template instantiation maximum time exceeded",
                                    "templateMaxTime",
                                    Certainty::normal);
                mErrorLogger.reportErr(errmsg);
            }
            return false;
        }

        assert(mTokenList.validateToken(tok2)); // that assertion fails on examples from #6021

        const Token *startToken = tok2;
        while (match182(startToken->tokAt(-2))) {
            if (startToken->strAt(-2) == MatchCompiler::makeConstString(">")) {
                const Token * tok3 = startToken->tokAt(-2)->findOpeningBracket();
                if (tok3)
                    startToken = tok3->previous();
                else
                    break;
            } else
                startToken = startToken->tokAt(-2);
        }

        if (match183(startToken->previous())) {
            const char* patternAfter = isfunc ? "(" : isVar ? ";|%op%|(" : "*|&|::| %name%";
            if (!isfunc && !isVar)
                if (const Token* end = startToken->next()->findClosingBracket())
                    if (match184(end))
                        patternAfter = "(|{";
            if (!specialized && !instantiateMatch(tok2, typeParametersInDeclaration.size(), templateDeclaration.isVariadic(), patternAfter))
                continue;
        }

        // New type..
        mTypesUsedInTemplateInstantiation.clear();
        std::list<std::string> typeStringsUsedInTemplateInstantiation;
        std::string typeForNewName = getNewName(tok2, typeStringsUsedInTemplateInstantiation);

        if ((typeForNewName.empty() && !templateDeclaration.isVariadic()) ||
            (!typeParametersInDeclaration.empty() && !instantiateMatch(tok2, typeParametersInDeclaration.size(), templateDeclaration.isVariadic(), nullptr))) {
            if (printDebug) {
                std::list<const Token *> callstack(1, tok2);
                mErrorLogger.reportErr(ErrorMessage(callstack, &mTokenList, Severity::debug, "templateInstantiation",
                                                    "Failed to instantiate template \"" + instantiation.name() + "\". The checking continues anyway.", Certainty::normal));
            }
            if (typeForNewName.empty())
                continue;
            break;
        }

        // New classname/funcname..
        const std::string newName(templateDeclaration.name() + " < " + typeForNewName + " >");
        std::string newFullName(templateDeclaration.scope() + (templateDeclaration.scope().empty() ? "" : " :: ") + newName);

        if (expandedtemplates.insert(std::move(newFullName)).second) {
            expandTemplate(templateDeclaration, instantiation, typeParametersInDeclaration, newName, !specialized && !isVar);
            instantiated = true;
            mChanged = true;
        }

        // Replace all these template usages..
        replaceTemplateUsage(instantiation, typeStringsUsedInTemplateInstantiation, newName);
    }

    // process uninstantiated templates
    // TODO: remove the specialized check and handle all uninstantiated templates someday.
    if (!instantiated && specialized) {
        auto * tok2 = const_cast<Token *>(templateDeclaration.nameToken());
        if ((mSettings.reportProgress != -1) && !mTokenList.getFiles().empty())
            mErrorLogger.reportProgress(mTokenList.getFiles()[0], "TemplateSimplifier::simplifyTemplateInstantiations()", tok2->progressValue());

        if (maxtime > 0 && std::time(nullptr) > maxtime) {
            if (mSettings.debugwarnings) {
                ErrorMessage::FileLocation loc(mTokenList.getFiles()[0], 0, 0);
                ErrorMessage errmsg({std::move(loc)},
                                    "",
                                    Severity::debug,
                                    "Template instantiation maximum time exceeded",
                                    "templateMaxTime",
                                    Certainty::normal);
                mErrorLogger.reportErr(errmsg);
            }
            return false;
        }

        assert(mTokenList.validateToken(tok2)); // that assertion fails on examples from #6021

        Token *startToken = tok2;
        while (match182(startToken->tokAt(-2))) {
            if (startToken->strAt(-2) == MatchCompiler::makeConstString(">")) {
                Token * tok3 = startToken->tokAt(-2)->findOpeningBracket();
                if (tok3)
                    startToken = tok3->previous();
                else
                    break;
            } else
                startToken = startToken->tokAt(-2);
        }

        // TODO: re-enable when specialized check is removed
        // if (Token::Match(startToken->previous(), ";|{|}|=|const") &&
        //     (!specialized && !instantiateMatch(tok2, typeParametersInDeclaration.size(), isfunc ? "(" : isVar ? ";|%op%|(" : "*|&|::| %name%")))
        //     return false;

        // already simplified
        if (!match6(tok2))
            return false;

        if (!matchSpecialization(templateDeclaration.nameToken(), tok2, specializations))
            return false;

        // New type..
        mTypesUsedInTemplateInstantiation.clear();
        std::list<std::string> typeStringsUsedInTemplateInstantiation;
        std::string typeForNewName = getNewName(tok2, typeStringsUsedInTemplateInstantiation);

        if (typeForNewName.empty()) {
            if (printDebug) {
                std::list<const Token *> callstack(1, tok2);
                mErrorLogger.reportErr(ErrorMessage(callstack, &mTokenList, Severity::debug, "templateInstantiation",
                                                    "Failed to instantiate template \"" + templateDeclaration.name() + "\". The checking continues anyway.", Certainty::normal));
            }
            return false;
        }

        // New classname/funcname..
        const std::string newName(templateDeclaration.name() + " < " + typeForNewName + " >");
        std::string newFullName(templateDeclaration.scope() + (templateDeclaration.scope().empty() ? "" : " :: ") + newName);

        if (expandedtemplates.insert(std::move(newFullName)).second) {
            expandTemplate(templateDeclaration, templateDeclaration, typeParametersInDeclaration, newName, !specialized && !isVar);
            instantiated = true;
            mChanged = true;
        }

        // Replace all these template usages..
        replaceTemplateUsage(templateDeclaration, typeStringsUsedInTemplateInstantiation, newName);
    }

    // Template has been instantiated .. then remove the template declaration
    return instantiated;
}

static bool matchTemplateParameters(const Token *nameTok, const std::list<std::string> &strings)
{
    const Token *tok = nameTok->tokAt(2);
    const Token *end = nameTok->next()->findClosingBracket();
    if (!end)
        return false;
    auto it = strings.cbegin();
    while (tok && tok != end && it != strings.cend()) {
        if (tok->isUnsigned()) {
            if (*it != MatchCompiler::makeConstString("unsigned"))
                return false;

            ++it;
            if (it == strings.cend())
                return false;
        } else if (tok->isSigned()) {
            if (*it != MatchCompiler::makeConstString("signed"))
                return false;

            ++it;
            if (it == strings.cend())
                return false;
        }
        if (tok->isLong()) {
            if (*it != MatchCompiler::makeConstString("long"))
                return false;

            ++it;
            if (it == strings.cend())
                return false;
        }
        if (*it != tok->str())
            return false;
        tok = tok->next();
        ++it;
    }
    return it == strings.cend() && tok && tok->str() == MatchCompiler::makeConstString(">");
}

void TemplateSimplifier::replaceTemplateUsage(
    const TokenAndName &instantiation,
    const std::list<std::string> &typeStringsUsedInTemplateInstantiation,
    const std::string &newName)
{
    std::list<std::pair<Token *, Token *>> removeTokens;
    for (Token *nameTok = mTokenList.front(); nameTok; nameTok = nameTok->next()) {
        if (!match6(nameTok) ||
            match185(nameTok))
            continue;

        std::set<TemplateSimplifier::TokenAndName*>* pointers = nameTok->templateSimplifierPointers();

        // check if instantiation matches token instantiation from pointer
        if (pointers && !pointers->empty()) {
            // check full name
            if (instantiation.fullName() != (*pointers->begin())->fullName()) {
                // FIXME:  fallback to just matching name
                if (nameTok->str() != instantiation.name())
                    continue;
            }
        }
        // no pointer available look at tokens directly
        else {
            // FIXME:  fallback to just matching name
            if (nameTok->str() != instantiation.name())
                continue;
        }

        if (!matchTemplateParameters(nameTok, typeStringsUsedInTemplateInstantiation))
            continue;

        Token *tok2 = nameTok->next()->findClosingBracket();

        if (!tok2)
            break;

        const Token * const nameTok1 = nameTok;
        nameTok->str(newName);

        // matching template usage => replace tokens..
        // Foo < int >  =>  Foo<int>
        for (const Token *tok = nameTok1->next(); tok != tok2; tok = tok->next()) {
            if (tok->isName() && tok->templateSimplifierPointers() && !tok->templateSimplifierPointers()->empty()) {
                for (auto ti = mTemplateInstantiations.cbegin(); ti != mTemplateInstantiations.cend();) {
                    if (ti->token() == tok) {
                        mTemplateInstantiations.erase(ti);
                        break;
                    }
                    ++ti;
                }
            }
        }
        // Fix crash in #9007
        if (match186(nameTok->previous()))
            mTemplateNamePos.erase(nameTok->previous());
        removeTokens.emplace_back(nameTok, tok2->next());

        nameTok = tok2;
    }
    while (!removeTokens.empty()) {
        eraseTokens(removeTokens.back().first, removeTokens.back().second);
        removeTokens.pop_back();
    }
}

static bool specMatch(
    const TemplateSimplifier::TokenAndName &spec,
    const TemplateSimplifier::TokenAndName &decl)
{
    // make sure decl is really a declaration
    if (decl.isPartialSpecialization() || decl.isSpecialization() || decl.isAlias() || decl.isFriend())
        return false;

    if (!spec.isSameFamily(decl))
        return false;

    // make sure the scopes and names match
    if (spec.fullName() == decl.fullName()) {
        if (spec.isFunction()) {
            std::vector<const Token*> specArgs;
            std::vector<const Token*> declArgs;
            getFunctionArguments(spec.nameToken(), specArgs);
            getFunctionArguments(decl.nameToken(), declArgs);

            if (specArgs.size() == declArgs.size()) {
                // @todo make sure function parameters also match
                return true;
            }
        } else
            return true;
    }

    return false;
}

void TemplateSimplifier::getSpecializations()
{
    // try to locate a matching declaration for each user defined specialization
    for (const auto& spec : mTemplateDeclarations) {
        if (spec.isSpecialization()) {
            auto it = std::find_if(mTemplateDeclarations.cbegin(), mTemplateDeclarations.cend(), [&](const TokenAndName& decl) {
                return specMatch(spec, decl);
            });
            if (it != mTemplateDeclarations.cend())
                mTemplateSpecializationMap[spec.token()] = it->token();
            else {
                it = std::find_if(mTemplateForwardDeclarations.cbegin(), mTemplateForwardDeclarations.cend(), [&](const TokenAndName& decl) {
                    return specMatch(spec, decl);
                });
                if (it != mTemplateForwardDeclarations.cend())
                    mTemplateSpecializationMap[spec.token()] = it->token();
            }
        }
    }
}

void TemplateSimplifier::getPartialSpecializations()
{
    // try to locate a matching declaration for each user defined partial specialization
    for (const auto& spec : mTemplateDeclarations) {
        if (spec.isPartialSpecialization()) {
            auto it = std::find_if(mTemplateDeclarations.cbegin(), mTemplateDeclarations.cend(), [&](const TokenAndName& decl) {
                return specMatch(spec, decl);
            });
            if (it != mTemplateDeclarations.cend())
                mTemplatePartialSpecializationMap[spec.token()] = it->token();
            else {
                it = std::find_if(mTemplateForwardDeclarations.cbegin(), mTemplateForwardDeclarations.cend(), [&](const TokenAndName& decl) {
                    return specMatch(spec, decl);
                });
                if (it != mTemplateForwardDeclarations.cend())
                    mTemplatePartialSpecializationMap[spec.token()] = it->token();
            }
        }
    }
}

void TemplateSimplifier::fixForwardDeclaredDefaultArgumentValues()
{
    // try to locate a matching declaration for each forward declaration
    for (const auto & forwardDecl : mTemplateForwardDeclarations) {
        std::vector<const Token *> params1;

        getTemplateParametersInDeclaration(forwardDecl.token()->tokAt(2), params1);

        for (auto & decl : mTemplateDeclarations) {
            // skip partializations, type aliases and friends
            if (decl.isPartialSpecialization() || decl.isAlias() || decl.isFriend())
                continue;

            std::vector<const Token *> params2;

            getTemplateParametersInDeclaration(decl.token()->tokAt(2), params2);

            // make sure the number of arguments match
            if (params1.size() == params2.size()) {
                // make sure the scopes and names match
                if (forwardDecl.fullName() == decl.fullName()) {
                    // save forward declaration for lookup later
                    if ((decl.nameToken()->strAt(1) == MatchCompiler::makeConstString("(") && forwardDecl.nameToken()->strAt(1) == MatchCompiler::makeConstString("(")) ||
                        (decl.nameToken()->strAt(1) == MatchCompiler::makeConstString("{") && forwardDecl.nameToken()->strAt(1) == MatchCompiler::makeConstString(";"))) {
                        mTemplateForwardDeclarationsMap[decl.token()] = forwardDecl.token();
                    }

                    for (size_t k = 0; k < params1.size(); k++) {
                        // copy default value to declaration if not present
                        if (params1[k]->strAt(1) == MatchCompiler::makeConstString("=") && params2[k]->strAt(1) != MatchCompiler::makeConstString("=")) {
                            int level = 0;
                            const Token *end = params1[k]->next();
                            while (end && !(level == 0 && match78(end))) {
                                if (match187(end))
                                    level++;
                                else if (match188(end))
                                    level--;
                                end = end->next();
                            }
                            if (end)
                                TokenList::copyTokens(const_cast<Token *>(params2[k]), params1[k]->next(), end->previous());
                        }
                    }

                    // update parameter end pointer
                    decl.paramEnd(decl.token()->next()->findClosingBracket());
                }
            }
        }
    }
}

void TemplateSimplifier::printOut(const TokenAndName &tokenAndName, const std::string &indent) const
{
    std::cout << indent << "token: ";
    if (tokenAndName.token())
        std::cout << "\"" << tokenAndName.token()->str() << "\" " << mTokenList.fileLine(tokenAndName.token());
    else
        std::cout << "nullptr";
    std::cout << std::endl;
    std::cout << indent << "scope: \"" << tokenAndName.scope() << "\"" << std::endl;
    std::cout << indent << "name: \"" << tokenAndName.name() << "\"" << std::endl;
    std::cout << indent << "fullName: \"" << tokenAndName.fullName() << "\"" << std::endl;
    std::cout << indent << "nameToken: ";
    if (tokenAndName.nameToken())
        std::cout << "\"" << tokenAndName.nameToken()->str() << "\" " << mTokenList.fileLine(tokenAndName.nameToken());
    else
        std::cout << "nullptr";
    std::cout << std::endl;
    std::cout << indent << "paramEnd: ";
    if (tokenAndName.paramEnd())
        std::cout << "\"" << tokenAndName.paramEnd()->str() << "\" " << mTokenList.fileLine(tokenAndName.paramEnd());
    else
        std::cout << "nullptr";
    std::cout << std::endl;
    std::cout << indent << "flags: ";
    if (tokenAndName.isClass())
        std::cout << " isClass";
    if (tokenAndName.isFunction())
        std::cout << " isFunction";
    if (tokenAndName.isVariable())
        std::cout << " isVariable";
    if (tokenAndName.isAlias())
        std::cout << " isAlias";
    if (tokenAndName.isSpecialization())
        std::cout << " isSpecialization";
    if (tokenAndName.isPartialSpecialization())
        std::cout << " isPartialSpecialization";
    if (tokenAndName.isForwardDeclaration())
        std::cout << " isForwardDeclaration";
    if (tokenAndName.isVariadic())
        std::cout << " isVariadic";
    if (tokenAndName.isFriend())
        std::cout << " isFriend";
    std::cout << std::endl;
    if (tokenAndName.token() && !tokenAndName.paramEnd() && tokenAndName.token()->strAt(1) == MatchCompiler::makeConstString("<")) {
        const Token *end = tokenAndName.token()->next()->findClosingBracket();
        if (end) {
            const Token *start = tokenAndName.token()->next();
            std::cout << indent << "type: ";
            while (start && start != end) {
                if (start->isUnsigned())
                    std::cout << "unsigned";
                else if (start->isSigned())
                    std::cout << "signed";
                if (start->isLong())
                    std::cout << "long";
                std::cout << start->str();
                start = start->next();
            }
            std::cout << end->str() << std::endl;
        }
    } else if (tokenAndName.isAlias() && tokenAndName.paramEnd()) {
        if (tokenAndName.aliasStartToken()) {
            std::cout << indent << "aliasStartToken: \"" << tokenAndName.aliasStartToken()->str() << "\" "
                      << mTokenList.fileLine(tokenAndName.aliasStartToken()) << std::endl;
        }
        if (tokenAndName.aliasEndToken()) {
            std::cout << indent << "aliasEndToken: \"" << tokenAndName.aliasEndToken()->str() << "\" "
                      << mTokenList.fileLine(tokenAndName.aliasEndToken()) << std::endl;
        }
    }
}

void TemplateSimplifier::printOut(const std::string & text) const
{
    std::cout << std::endl;
    std::cout << text << std::endl;
    std::cout << std::endl;
    std::cout << "mTemplateDeclarations: " << mTemplateDeclarations.size() << std::endl;
    int count = 0;
    for (const auto & decl : mTemplateDeclarations) {
        std::cout << "mTemplateDeclarations[" << count++ << "]:" << std::endl;
        printOut(decl);
    }
    std::cout << "mTemplateForwardDeclarations: " << mTemplateForwardDeclarations.size() << std::endl;
    count = 0;
    for (const auto & decl : mTemplateForwardDeclarations) {
        std::cout << "mTemplateForwardDeclarations[" << count++ << "]:" << std::endl;
        printOut(decl);
    }
    std::cout << "mTemplateForwardDeclarationsMap: " << mTemplateForwardDeclarationsMap.size() << std::endl;
    unsigned int mapIndex = 0;
    for (const auto & mapItem : mTemplateForwardDeclarationsMap) {
        unsigned int declIndex = 0;
        for (const auto & decl : mTemplateDeclarations) {
            if (mapItem.first == decl.token()) {
                unsigned int forwardIndex = 0;
                for (const auto & forwardDecl : mTemplateForwardDeclarations) {
                    if (mapItem.second == forwardDecl.token()) {
                        std::cout << "mTemplateForwardDeclarationsMap[" << mapIndex << "]:" << std::endl;
                        std::cout << "    mTemplateDeclarations[" << declIndex
                                  << "] => mTemplateForwardDeclarations[" << forwardIndex << "]" << std::endl;
                        break;
                    }
                    forwardIndex++;
                }
                break;
            }
            declIndex++;
        }
        mapIndex++;
    }
    std::cout << "mTemplateSpecializationMap: " << mTemplateSpecializationMap.size() << std::endl;
    for (const auto & mapItem : mTemplateSpecializationMap) {
        unsigned int decl1Index = 0;
        for (const auto & decl1 : mTemplateDeclarations) {
            if (decl1.isSpecialization() && mapItem.first == decl1.token()) {
                bool found = false;
                unsigned int decl2Index = 0;
                for (const auto & decl2 : mTemplateDeclarations) {
                    if (mapItem.second == decl2.token()) {
                        std::cout << "mTemplateSpecializationMap[" << mapIndex << "]:" << std::endl;
                        std::cout << "    mTemplateDeclarations[" << decl1Index
                                  << "] => mTemplateDeclarations[" << decl2Index << "]" << std::endl;
                        found = true;
                        break;
                    }
                    decl2Index++;
                }
                if (!found) {
                    decl2Index = 0;
                    for (const auto & decl2 : mTemplateForwardDeclarations) {
                        if (mapItem.second == decl2.token()) {
                            std::cout << "mTemplateSpecializationMap[" << mapIndex << "]:" << std::endl;
                            std::cout << "    mTemplateDeclarations[" << decl1Index
                                      << "] => mTemplateForwardDeclarations[" << decl2Index << "]" << std::endl;
                            break;
                        }
                        decl2Index++;
                    }
                }
                break;
            }
            decl1Index++;
        }
        mapIndex++;
    }
    std::cout << "mTemplatePartialSpecializationMap: " << mTemplatePartialSpecializationMap.size() << std::endl;
    for (const auto & mapItem : mTemplatePartialSpecializationMap) {
        unsigned int decl1Index = 0;
        for (const auto & decl1 : mTemplateDeclarations) {
            if (mapItem.first == decl1.token()) {
                bool found = false;
                unsigned int decl2Index = 0;
                for (const auto & decl2 : mTemplateDeclarations) {
                    if (mapItem.second == decl2.token()) {
                        std::cout << "mTemplatePartialSpecializationMap[" << mapIndex << "]:" << std::endl;
                        std::cout << "    mTemplateDeclarations[" << decl1Index
                                  << "] => mTemplateDeclarations[" << decl2Index << "]" << std::endl;
                        found = true;
                        break;
                    }
                    decl2Index++;
                }
                if (!found) {
                    decl2Index = 0;
                    for (const auto & decl2 : mTemplateForwardDeclarations) {
                        if (mapItem.second == decl2.token()) {
                            std::cout << "mTemplatePartialSpecializationMap[" << mapIndex << "]:" << std::endl;
                            std::cout << "    mTemplateDeclarations[" << decl1Index
                                      << "] => mTemplateForwardDeclarations[" << decl2Index << "]" << std::endl;
                            break;
                        }
                        decl2Index++;
                    }
                }
                break;
            }
            decl1Index++;
        }
        mapIndex++;
    }
    std::cout << "mTemplateInstantiations: " << mTemplateInstantiations.size() << std::endl;
    count = 0;
    for (const auto & decl : mTemplateInstantiations) {
        std::cout << "mTemplateInstantiations[" << count++ << "]:" << std::endl;
        printOut(decl);
    }
}

void TemplateSimplifier::simplifyTemplates(const std::time_t maxtime)
{
    // convert "sizeof ..." to "sizeof..."
    for (Token *tok = mTokenList.front(); tok; tok = tok->next()) {
        if (match189(tok)) {
            tok->str("sizeof...");
            tok->deleteNext();
        }
    }

    // Remove "typename" unless used in template arguments or using type alias..
    for (Token *tok = mTokenList.front(); tok; tok = tok->next()) {
        if (match190(tok) && !match191(tok->tokAt(-3)))
            tok->deleteThis();

        if (match40(tok)) {
            tok = tok->next()->findClosingBracket();
            if (!tok)
                break;
        }
    }

    if (mSettings.standards.cpp >= Standards::CPP20) {
        // Remove concepts/requires
        // TODO concepts are not removed yet
        for (Token *tok = mTokenList.front(); tok; tok = tok->next()) {
            if (!match192(tok))
                continue;
            const Token* end = skipRequires(tok->next());
            if (end)
                Token::eraseTokens(tok, end);
        }

        // explicit(bool)
        for (Token *tok = mTokenList.front(); tok; tok = tok->next()) {
            if (match193(tok)) {
                const bool isFalse = match194(tok->tokAt(2));
                Token::eraseTokens(tok, tok->linkAt(1)->next());
                if (isFalse)
                    tok->deleteThis();
            }
        }
    }

    mTokenizer.calculateScopes();

    unsigned int passCount = 0;
    constexpr unsigned int passCountMax = 10;
    for (; passCount < passCountMax; ++passCount) {
        if (passCount) {
            // it may take more than one pass to simplify type aliases
            bool usingChanged = false;
            while (mTokenizer.simplifyUsing())
                usingChanged = true;

            if (!usingChanged && !mChanged)
                break;

            mChanged = usingChanged;
            mTemplateDeclarations.clear();
            mTemplateForwardDeclarations.clear();
            mTemplateForwardDeclarationsMap.clear();
            mTemplateSpecializationMap.clear();
            mTemplatePartialSpecializationMap.clear();
            mTemplateInstantiations.clear();
            mInstantiatedTemplates.clear();
            mExplicitInstantiationsToDelete.clear();
            mTemplateNamePos.clear();
        }

        getTemplateDeclarations();

        if (passCount == 0) {
            mDump.clear();
            for (const TokenAndName& t: mTemplateDeclarations)
                mDump += t.dump(mTokenizer.list.getFiles());
            for (const TokenAndName& t: mTemplateForwardDeclarations)
                mDump += t.dump(mTokenizer.list.getFiles());
            if (!mDump.empty())
                mDump = "  <TemplateSimplifier>\n" + mDump + "  </TemplateSimplifier>\n";
        }

        // Make sure there is something to simplify.
        if (mTemplateDeclarations.empty() && mTemplateForwardDeclarations.empty())
            return;

        if (mSettings.debugtemplate && mSettings.debugnormal) {
            std::string title("Template Simplifier pass " + std::to_string(passCount + 1));
            mTokenList.front()->printOut(std::cout, false, title.c_str(), mTokenList.getFiles());
        }

        // Copy default argument values from forward declaration to declaration
        fixForwardDeclaredDefaultArgumentValues();

        // Locate user defined specializations.
        getSpecializations();

        // Locate user defined partial specializations.
        getPartialSpecializations();

        // Locate possible instantiations of templates..
        getTemplateInstantiations();

        // Template arguments with default values
        useDefaultArgumentValues();

        simplifyTemplateAliases();

        if (mSettings.debugtemplate)
            printOut("### Template Simplifier pass " + std::to_string(passCount + 1) + " ###");

        // Keep track of the order the names appear so sort can preserve that order
        std::unordered_map<std::string, int> nameOrdinal;
        int ordinal = 0;
        for (const auto& decl : mTemplateDeclarations) {
            nameOrdinal.emplace(decl.fullName(), ordinal++);
        }

        auto score = [&](const Token* arg) {
            int i = 0;
            for (const Token* tok = arg; tok; tok = tok->next()) {
                if (tok->str() == MatchCompiler::makeConstString(","))
                    return i;
                if (tok->link() && match77(tok))
                    tok = tok->link();
                else if (tok->str() == MatchCompiler::makeConstString("<")) {
                    const Token* temp = tok->findClosingBracket();
                    if (temp)
                        tok = temp;
                } else if (match195(tok))
                    return i;
                else if (match94(tok))
                    i--;
            }
            return 0;
        };
        // Sort so const parameters come first in the list
        mTemplateDeclarations.sort([&](const TokenAndName& x, const TokenAndName& y) {
            if (x.fullName() != y.fullName())
                return nameOrdinal.at(x.fullName()) < nameOrdinal.at(y.fullName());
            if (x.isFunction() && y.isFunction()) {
                std::vector<const Token*> xargs;
                getFunctionArguments(x.nameToken(), xargs);
                std::vector<const Token*> yargs;
                getFunctionArguments(y.nameToken(), yargs);
                if (xargs.size() != yargs.size())
                    return xargs.size() < yargs.size();
                if (isConstMethod(x.nameToken()) != isConstMethod(y.nameToken()))
                    return isConstMethod(x.nameToken());
                return std::lexicographical_compare(xargs.begin(),
                                                    xargs.end(),
                                                    yargs.begin(),
                                                    yargs.end(),
                                                    [&](const Token* xarg, const Token* yarg) {
                    if (xarg != yarg)
                        return score(xarg) < score(yarg);
                    return false;
                });
            }
            return false;
        });

        std::set<std::string> expandedtemplates;

        for (auto iter1 = mTemplateDeclarations.crbegin(); iter1 != mTemplateDeclarations.crend(); ++iter1) {
            if (iter1->isAlias() || iter1->isFriend())
                continue;

            // get specializations..
            std::list<const Token *> specializations;
            for (auto iter2 = mTemplateDeclarations.cbegin(); iter2 != mTemplateDeclarations.cend(); ++iter2) {
                if (iter2->isAlias() || iter2->isFriend())
                    continue;

                if (iter1->fullName() == iter2->fullName())
                    specializations.push_back(iter2->nameToken());
            }

            const bool instantiated = simplifyTemplateInstantiations(
                *iter1,
                specializations,
                maxtime,
                expandedtemplates);
            if (instantiated) {
                mInstantiatedTemplates.push_back(*iter1);
                mTemplateNamePos.clear(); // positions might be invalid after instantiations
            }
        }

        for (auto it = mInstantiatedTemplates.cbegin(); it != mInstantiatedTemplates.cend(); ++it) {
            auto decl = std::find_if(mTemplateDeclarations.begin(), mTemplateDeclarations.end(), [&it](const TokenAndName& decl) {
                return decl.token() == it->token();
            });
            if (decl != mTemplateDeclarations.end()) {
                if (it->isSpecialization()) {
                    // delete the "template < >"
                    Token * tok = it->token();
                    tok->deleteNext(2);
                    tok->deleteThis();
                } else {
                    // remove forward declaration if found
                    auto it1 = mTemplateForwardDeclarationsMap.find(it->token());
                    if (it1 != mTemplateForwardDeclarationsMap.end())
                        removeTemplate(it1->second, &mTemplateForwardDeclarationsMap);
                    removeTemplate(it->token(), &mTemplateForwardDeclarationsMap);
                }
                mTemplateDeclarations.erase(decl);
            }
        }

        // remove out of line member functions
        while (!mMemberFunctionsToDelete.empty()) {
            const auto it = std::find_if(mTemplateDeclarations.begin(),
                                         mTemplateDeclarations.end(),
                                         FindToken(mMemberFunctionsToDelete.cbegin()->token()));
            // multiple functions can share the same declaration so make sure it hasn't already been deleted
            if (it != mTemplateDeclarations.end()) {
                removeTemplate(it->token());
                mTemplateDeclarations.erase(it);
            } else {
                const auto it1 = std::find_if(mTemplateForwardDeclarations.begin(),
                                              mTemplateForwardDeclarations.end(),
                                              FindToken(mMemberFunctionsToDelete.cbegin()->token()));
                // multiple functions can share the same declaration so make sure it hasn't already been deleted
                if (it1 != mTemplateForwardDeclarations.end()) {
                    removeTemplate(it1->token());
                    mTemplateForwardDeclarations.erase(it1);
                }
            }
            mMemberFunctionsToDelete.erase(mMemberFunctionsToDelete.begin());
        }

        // remove explicit instantiations
        for (const TokenAndName& j : mExplicitInstantiationsToDelete) {
            Token * start = j.token();
            if (start) {
                Token * end = start->next();
                while (end && end->str() != MatchCompiler::makeConstString(";"))
                    end = end->next();
                if (start->previous())
                    start = start->previous();
                if (end && end->next())
                    end = end->next();
                eraseTokens(start, end);
            }
        }
    }

    if (passCount == passCountMax) {
        if (mSettings.debugwarnings) {
            const std::list<const Token*> locationList(1, mTokenList.front());
            const ErrorMessage errmsg(locationList, &mTokenizer.list,
                                      Severity::debug,
                                      "debug",
                                      "TemplateSimplifier: pass count limit hit before simplifications were finished.",
                                      Certainty::normal);
            mErrorLogger.reportErr(errmsg);
        }
    }

    // Tweak uninstantiated C++17 fold expressions (... && args)
    if (mSettings.standards.cpp >= Standards::CPP17) {
        bool simplify = false;
        for (Token *tok = mTokenList.front(); tok; tok = tok->next()) {
            if (tok->str() == MatchCompiler::makeConstString("template"))
                simplify = false;
            if (tok->str() == MatchCompiler::makeConstString("{"))
                simplify = true;
            if (!simplify || tok->str() != MatchCompiler::makeConstString("("))
                continue;
            const Token *op = nullptr;
            const Token *args = nullptr;
            if (match196(tok)) {
                op = tok->tokAt(2);
                args = tok->link()->previous();
            } else if (match197(tok) && !match198(tok->previous())) {
                op = tok->tokAt(2);
                args = tok->link()->previous()->isName() ? nullptr : tok->next();
            } else if (match199(tok->link()->tokAt(-3))) {
                op = tok->link()->tokAt(-2);
                args = tok->next();
            } else if (match200(tok->link()->tokAt(-3))) {
                op = tok->link()->tokAt(-2);
                args = tok->next()->isName() ? nullptr : tok->link()->previous();
            } else {
                continue;
            }

            const std::string strop = op->str();
            const std::string strargs = (args && args->isName()) ? args->str() : "";

            Token::eraseTokens(tok, tok->link());
            tok->insertToken(")");
            if (!strargs.empty()) {
                tok->insertToken("...");
                tok->insertToken(strargs);
            }
            tok->insertToken("(");
            Token::createMutualLinks(tok->next(), tok->link()->previous());
            tok->insertToken("__cppcheck_fold_" + strop + "__");
        }
    }
}

void TemplateSimplifier::syntaxError(const Token *tok)
{
    throw InternalError(tok, "syntax error", InternalError::SYNTAX);
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
