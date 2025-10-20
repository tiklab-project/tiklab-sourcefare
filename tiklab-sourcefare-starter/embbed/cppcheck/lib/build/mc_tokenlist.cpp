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
// pattern: (|[|{
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: )|]|}
MAYBE_UNUSED static inline bool match2(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: )
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: *|&|&&|const
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        return false;
    return true;
}
// pattern: (
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %name%| ,|)
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: ( %name%
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %name%|*|&|::|<
MAYBE_UNUSED static inline bool match8(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: %var% [:=({]
MAYBE_UNUSED static inline bool match9(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(":=({", tok->str()[0]))
        return false;
    return true;
}
// pattern: decltype|typeof (
MAYBE_UNUSED static inline bool match10(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("decltype")) || (tok->str() == MatchCompiler::makeConstString("typeof"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ( ::| %name%
MAYBE_UNUSED static inline bool match11(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: ) ( )
MAYBE_UNUSED static inline bool match12(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ) %assign%|,|...
MAYBE_UNUSED static inline bool match13(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isAssignmentOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("..."))))
        return false;
    return true;
}
// pattern: return|case
MAYBE_UNUSED static inline bool match14(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case"))))
        return false;
    return true;
}
// pattern: delete|throw
MAYBE_UNUSED static inline bool match15(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("delete")) || (tok->str() == MatchCompiler::makeConstString("throw"))))
        return false;
    return true;
}
// pattern: >
MAYBE_UNUSED static inline bool match16(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    return true;
}
// pattern: ( (| typeof (
MAYBE_UNUSED static inline bool match17(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("typeof")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) %num%
MAYBE_UNUSED static inline bool match18(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: ) }|)|]|;
MAYBE_UNUSED static inline bool match19(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: ) ++|-- [;)]
MAYBE_UNUSED static inline bool match20(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--"))))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";)", tok->str()[0]))
        return false;
    return true;
}
// pattern: ) %cop%
MAYBE_UNUSED static inline bool match21(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isConstOp())
        return false;
    return true;
}
// pattern: ) [&*+-~!]
MAYBE_UNUSED static inline bool match22(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("&*+-~!", tok->str()[0]))
        return false;
    return true;
}
// pattern: = ( %name% ) {
MAYBE_UNUSED static inline bool match23(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: (|[|<
MAYBE_UNUSED static inline bool match24(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: ) (
MAYBE_UNUSED static inline bool match25(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) .
MAYBE_UNUSED static inline bool match26(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: ) {
MAYBE_UNUSED static inline bool match27(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: [{}]
MAYBE_UNUSED static inline bool match28(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{}", tok->str()[0]))
        return false;
    return true;
}
// pattern: ) ~
MAYBE_UNUSED static inline bool match29(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~")))
        return false;
    return true;
}
// pattern: ) %any%
MAYBE_UNUSED static inline bool match30(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    return true;
}
// pattern: !|~|++|--
MAYBE_UNUSED static inline bool match31(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--"))))
        return false;
    return true;
}
// pattern: [[]);,?:.]
MAYBE_UNUSED static inline bool match32(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("[]);,?:.", tok->str()[0]))
        return false;
    return true;
}
// pattern: &|&& )
MAYBE_UNUSED static inline bool match33(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: %name%|*|::
MAYBE_UNUSED static inline bool match34(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: ( * *| )
MAYBE_UNUSED static inline bool match35(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: [,()] %name%
MAYBE_UNUSED static inline bool match36(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",()", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %name%|::|<
MAYBE_UNUSED static inline bool match37(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: [*&]
MAYBE_UNUSED static inline bool match38(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("*&", tok->str()[0]))
        return false;
    return true;
}
// pattern: {
MAYBE_UNUSED static inline bool match39(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ; }
MAYBE_UNUSED static inline bool match40(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: } ,
MAYBE_UNUSED static inline bool match41(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: decltype (
MAYBE_UNUSED static inline bool match42(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("decltype")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: .
MAYBE_UNUSED static inline bool match43(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: , {
MAYBE_UNUSED static inline bool match44(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ]|*
MAYBE_UNUSED static inline bool match45(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: %type%|::|*
MAYBE_UNUSED static inline bool match46(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: new
MAYBE_UNUSED static inline bool match47(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    return true;
}
// pattern: %name%|%num%|%char%|) :
MAYBE_UNUSED static inline bool match48(const Token* tok) {
    if (!tok || !(tok->isName() || tok->isNumber() || (tok->tokType() == Token::eChar) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: case
MAYBE_UNUSED static inline bool match49(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case")))
        return false;
    return true;
}
// pattern: ::|%name%
MAYBE_UNUSED static inline bool match50(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || tok->isName()))
        return false;
    return true;
}
// pattern: %name%|return|: {
MAYBE_UNUSED static inline bool match51(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: [
MAYBE_UNUSED static inline bool match52(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: %name% <
MAYBE_UNUSED static inline bool match53(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: > {
MAYBE_UNUSED static inline bool match54(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %name%|> ( {
MAYBE_UNUSED static inline bool match55(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: decltype
MAYBE_UNUSED static inline bool match56(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("decltype")))
        return false;
    return true;
}
// pattern: else|try|do|const|constexpr|override|volatile|&|&&
MAYBE_UNUSED static inline bool match57(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("else")) || (tok->str() == MatchCompiler::makeConstString("try")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("constexpr")) || (tok->str() == MatchCompiler::makeConstString("override")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: . void {
MAYBE_UNUSED static inline bool match58(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("void")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: namespace
MAYBE_UNUSED static inline bool match59(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    return true;
}
// pattern: return|:
MAYBE_UNUSED static inline bool match60(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: } ;
MAYBE_UNUSED static inline bool match61(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: %name%|::|:|<|>|(|)|,|%num%|%cop%|...
MAYBE_UNUSED static inline bool match62(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || tok->isNumber() || tok->isConstOp() || ((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("..."))))
        return false;
    return true;
}
// pattern: class|struct|union|enum
MAYBE_UNUSED static inline bool match63(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    return true;
}
// pattern: &|&&|*
MAYBE_UNUSED static inline bool match64(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: {|;
MAYBE_UNUSED static inline bool match65(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: [({[]
MAYBE_UNUSED static inline bool match66(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("({[", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name%|*|:|(
MAYBE_UNUSED static inline bool match67(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: :
MAYBE_UNUSED static inline bool match68(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: ,
MAYBE_UNUSED static inline bool match69(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: ::|. ~
MAYBE_UNUSED static inline bool match70(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~")))
        return false;
    return true;
}
// pattern: L %str%|%char%
MAYBE_UNUSED static inline bool match71(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("L")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eString) || (tok->tokType() == Token::eChar)))
        return false;
    return true;
}
// pattern: [{,] . %name%
MAYBE_UNUSED static inline bool match72(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: [{,] [ %num%|%name% ]
MAYBE_UNUSED static inline bool match73(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isNumber() || tok->isName()))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    return true;
}
// pattern: %name%|%str%
MAYBE_UNUSED static inline bool match74(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->tokType() == Token::eString)))
        return false;
    return true;
}
// pattern: : ;
MAYBE_UNUSED static inline bool match75(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: sizeof !!(
MAYBE_UNUSED static inline bool match76(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    return true;
}
// pattern: { . %name% =|{
MAYBE_UNUSED static inline bool match77(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: new|delete %name%|*|&|::|(|[
MAYBE_UNUSED static inline bool match78(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("new")) || (tok->str() == MatchCompiler::makeConstString("delete"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: %name%
MAYBE_UNUSED static inline bool match79(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: > %name%
MAYBE_UNUSED static inline bool match80(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: <
MAYBE_UNUSED static inline bool match81(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: %name% ...
MAYBE_UNUSED static inline bool match82(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")))
        return false;
    return true;
}
// pattern: !!& ) ( %name% ) =
MAYBE_UNUSED static inline bool match83(const Token* tok) {
    if (tok && tok->str() == MatchCompiler::makeConstString("&"))
        return false;
    tok = tok ? tok->next() : nullptr;
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: %str%
MAYBE_UNUSED static inline bool match84(const Token* tok) {
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    return true;
}
// pattern: %name% %assign%
MAYBE_UNUSED static inline bool match85(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !tok->isAssignmentOp())
        return false;
    return true;
}
// pattern: } [
MAYBE_UNUSED static inline bool match86(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] {
MAYBE_UNUSED static inline bool match87(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: [{,]
MAYBE_UNUSED static inline bool match88(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{,", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name% (
MAYBE_UNUSED static inline bool match89(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: !!, { . %name% =|{
MAYBE_UNUSED static inline bool match90(const Token* tok) {
    if (tok && tok->str() == MatchCompiler::makeConstString(","))
        return false;
    tok = tok ? tok->next() : nullptr;
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: { }
MAYBE_UNUSED static inline bool match91(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: %name% ( {
MAYBE_UNUSED static inline bool match92(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ;
template<class T> MAYBE_UNUSED static inline T * findmatch93(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: =
MAYBE_UNUSED static inline bool match94(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: } [,};]
MAYBE_UNUSED static inline bool match95(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",};", tok->str()[0]))
        return false;
    return true;
}
// pattern: :: %name%
MAYBE_UNUSED static inline bool match96(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: * [
MAYBE_UNUSED static inline bool match97(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: %name%|::|*|&|>|>>
MAYBE_UNUSED static inline bool match98(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    return true;
}
// pattern: >|>>
MAYBE_UNUSED static inline bool match99(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    return true;
}
// pattern: (|[|{|%op%|;|?|:|,|.|case|return|::
MAYBE_UNUSED static inline bool match100(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || tok->isOp() || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->str() == MatchCompiler::makeConstString(".")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: %type%
MAYBE_UNUSED static inline bool match101(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: *
MAYBE_UNUSED static inline bool match102(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: :: %type%
MAYBE_UNUSED static inline bool match103(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: new ::| %type%
MAYBE_UNUSED static inline bool match104(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: ] (|{|<
MAYBE_UNUSED static inline bool match105(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: ] <
MAYBE_UNUSED static inline bool match106(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: > (
MAYBE_UNUSED static inline bool match107(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ] (
MAYBE_UNUSED static inline bool match108(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: mutable|const|constexpr|consteval
MAYBE_UNUSED static inline bool match109(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("mutable")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("constexpr")) || (tok->str() == MatchCompiler::makeConstString("consteval"))))
        return false;
    return true;
}
// pattern: noexcept
MAYBE_UNUSED static inline bool match110(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("noexcept")))
        return false;
    return true;
}
// pattern: %type%|* [
MAYBE_UNUSED static inline bool match111(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] { !!}
MAYBE_UNUSED static inline bool match112(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("}"))
        return false;
    return true;
}
// pattern: requires {
MAYBE_UNUSED static inline bool match113(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("requires")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ( {
MAYBE_UNUSED static inline bool match114(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ; } )
MAYBE_UNUSED static inline bool match115(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: if|while|for|switch|catch
MAYBE_UNUSED static inline bool match116(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("switch")) || (tok->str() == MatchCompiler::makeConstString("catch"))))
        return false;
    return true;
}
// pattern: _Generic
MAYBE_UNUSED static inline bool match117(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("_Generic")))
        return false;
    return true;
}
// pattern: } (
MAYBE_UNUSED static inline bool match118(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: throw|delete
MAYBE_UNUSED static inline bool match119(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("throw")) || (tok->str() == MatchCompiler::makeConstString("delete"))))
        return false;
    return true;
}
// pattern: new|delete
MAYBE_UNUSED static inline bool match120(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("new")) || (tok->str() == MatchCompiler::makeConstString("delete"))))
        return false;
    return true;
}
// pattern: ::
MAYBE_UNUSED static inline bool match121(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: [+-!~*&]
MAYBE_UNUSED static inline bool match122(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("+-!~*&", tok->str()[0]))
        return false;
    return true;
}
// pattern: * [*,)]
MAYBE_UNUSED static inline bool match123(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("*,)", tok->str()[0]))
        return false;
    return true;
}
// pattern: [>),]
MAYBE_UNUSED static inline bool match124(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(">),", tok->str()[0]))
        return false;
    return true;
}
// pattern: new %name%|::|(
MAYBE_UNUSED static inline bool match125(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: ( &| %name%
MAYBE_UNUSED static inline bool match126(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: ) ( %type%
MAYBE_UNUSED static inline bool match127(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: ) ::| %type%
MAYBE_UNUSED static inline bool match128(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: ( !!)
MAYBE_UNUSED static inline bool match129(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString(")"))
        return false;
    return true;
}
// pattern: ( %type%
MAYBE_UNUSED static inline bool match130(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: ) [();,[]
MAYBE_UNUSED static inline bool match131(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("();,[", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name%|*|&|<|::
MAYBE_UNUSED static inline bool match132(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: ( const| %type% ) (
MAYBE_UNUSED static inline bool match133(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: (|{|[
MAYBE_UNUSED static inline bool match134(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: ) [
MAYBE_UNUSED static inline bool match135(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: :: new
MAYBE_UNUSED static inline bool match136(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    return true;
}
// pattern: ) ,
MAYBE_UNUSED static inline bool match137(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: delete %name%|*|&|::|(|[
MAYBE_UNUSED static inline bool match138(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("delete")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: :: delete
MAYBE_UNUSED static inline bool match139(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("delete")))
        return false;
    return true;
}
// pattern: . *
MAYBE_UNUSED static inline bool match140(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: [/%]
MAYBE_UNUSED static inline bool match141(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("/%", tok->str()[0]))
        return false;
    return true;
}
// pattern: +|-
MAYBE_UNUSED static inline bool match142(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-"))))
        return false;
    return true;
}
// pattern: <<|>>
MAYBE_UNUSED static inline bool match143(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("<<")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    return true;
}
// pattern: <|<=|>=|>
MAYBE_UNUSED static inline bool match144(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<=")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">=")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: ==|!=
MAYBE_UNUSED static inline bool match145(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("==")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("!="))))
        return false;
    return true;
}
// pattern: ,|)
MAYBE_UNUSED static inline bool match146(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: , }
MAYBE_UNUSED static inline bool match147(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: ] (|{
MAYBE_UNUSED static inline bool match148(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: mutable
MAYBE_UNUSED static inline bool match149(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("mutable")))
        return false;
    return true;
}
// pattern: .|->
MAYBE_UNUSED static inline bool match150(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("->"))))
        return false;
    return true;
}
// pattern: %type%|%name%|::|&|&&|*|<|(
MAYBE_UNUSED static inline bool match151(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: ( * ) [
MAYBE_UNUSED static inline bool match152(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: %type% %type%
MAYBE_UNUSED static inline bool match153(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: return|throw|new|delete
MAYBE_UNUSED static inline bool match154(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("throw")) || (tok->str() == MatchCompiler::makeConstString("new")) || (tok->str() == MatchCompiler::makeConstString("delete"))))
        return false;
    return true;
}
// pattern: %type%|*|&
MAYBE_UNUSED static inline bool match155(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: %var% [;,)]
MAYBE_UNUSED static inline bool match156(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";,)", tok->str()[0]))
        return false;
    return true;
}
// pattern: decltype|noexcept (
MAYBE_UNUSED static inline bool match157(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("decltype")) || (tok->str() == MatchCompiler::makeConstString("noexcept"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: return|throw|if|while|new|delete
MAYBE_UNUSED static inline bool match158(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("throw")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || (tok->str() == MatchCompiler::makeConstString("new")) || (tok->str() == MatchCompiler::makeConstString("delete"))))
        return false;
    return true;
}
// pattern: %type%|*|&|<
MAYBE_UNUSED static inline bool match159(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: const|mutable|static|volatile
MAYBE_UNUSED static inline bool match160(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("mutable")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        return false;
    return true;
}
// pattern: ( * *| %var%
MAYBE_UNUSED static inline bool match161(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    return true;
}
// pattern: %var%|] ) (
MAYBE_UNUSED static inline bool match162(const Token* tok) {
    if (!tok || !((tok->varId() != 0) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) [;,)]
MAYBE_UNUSED static inline bool match163(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";,)", tok->str()[0]))
        return false;
    return true;
}
// pattern: for (
MAYBE_UNUSED static inline bool match164(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: for ( const| auto &|&&| [
MAYBE_UNUSED static inline bool match165(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("auto")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: [
template<class T> MAYBE_UNUSED static inline T * findmatch166(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: ] :
MAYBE_UNUSED static inline bool match167(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: %name% ,|]
MAYBE_UNUSED static inline bool match168(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    return true;
}
// pattern: %op%|(
MAYBE_UNUSED static inline bool match169(const Token* tok) {
    if (!tok || !(tok->isOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: ( !!{
MAYBE_UNUSED static inline bool match170(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("{"))
        return false;
    return true;
}
// pattern: %op%|(|[
MAYBE_UNUSED static inline bool match171(const Token* tok) {
    if (!tok || !(tok->isOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: %name% )| %op%|(|[|{|.|:|::
MAYBE_UNUSED static inline bool match172(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        tok = tok->next();
    if (!tok || !(tok->isOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString(".")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: [(;{}] %cop%|(
MAYBE_UNUSED static inline bool match173(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(;{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isConstOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: ;|)
MAYBE_UNUSED static inline bool match174(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: %type% <
MAYBE_UNUSED static inline bool match175(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: > [({]
MAYBE_UNUSED static inline bool match176(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("({", tok->str()[0]))
        return false;
    return true;
}
// pattern: %type% ::|<|%name%
MAYBE_UNUSED static inline bool match177(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || tok->isName()))
        return false;
    return true;
}
// pattern: %name%|> :: %name%
MAYBE_UNUSED static inline bool match178(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %name%|> %name% {
MAYBE_UNUSED static inline bool match179(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %type% %name%|*|&|&&|::
MAYBE_UNUSED static inline bool match180(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: return|new|delete
MAYBE_UNUSED static inline bool match181(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("new")) || (tok->str() == MatchCompiler::makeConstString("delete"))))
        return false;
    return true;
}
// pattern: %type%|::|*|&|&&|<
MAYBE_UNUSED static inline bool match182(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: %var% =
MAYBE_UNUSED static inline bool match183(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: return|throw
MAYBE_UNUSED static inline bool match184(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("throw"))))
        return false;
    return true;
}
// pattern: %name% ( !!*
MAYBE_UNUSED static inline bool match185(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("*"))
        return false;
    return true;
}
// pattern: ) ;|{
MAYBE_UNUSED static inline bool match186(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: %name% %op%|(|[|.|::|<|?|;
MAYBE_UNUSED static inline bool match187(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->isOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || (tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: %name% {
MAYBE_UNUSED static inline bool match188(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: [;{}:] %cop%|++|--|( !!{
MAYBE_UNUSED static inline bool match189(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}:", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isConstOp() || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("{"))
        return false;
    return true;
}
// pattern: [;{}] %num%|%str%|%char%
MAYBE_UNUSED static inline bool match190(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isNumber() || (tok->tokType() == Token::eString) || (tok->tokType() == Token::eChar)))
        return false;
    return true;
}
// pattern: [;{}] delete new
MAYBE_UNUSED static inline bool match191(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("delete")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    return true;
}
// pattern: [;{}] [
MAYBE_UNUSED static inline bool match192(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: [;{}] new|delete %name%
MAYBE_UNUSED static inline bool match193(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("new")) || (tok->str() == MatchCompiler::makeConstString("delete"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: [;{}] :: new|delete %name%
MAYBE_UNUSED static inline bool match194(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("new")) || (tok->str() == MatchCompiler::makeConstString("delete"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: [|^/%]
MAYBE_UNUSED static inline bool match195(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("|^/%", tok->str()[0]))
        return false;
    return true;
}
// pattern: %or%|%oror%|%assign%|%comp%
MAYBE_UNUSED static inline bool match196(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || tok->isAssignmentOp() || tok->isComparisonOp()))
        return false;
    return true;
}
// pattern: ) = 0
MAYBE_UNUSED static inline bool match197(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    return true;
}
// pattern: operator
MAYBE_UNUSED static inline bool match198(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    return true;
}
// pattern: = {|^|[
MAYBE_UNUSED static inline bool match199(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: %name% = %name%
MAYBE_UNUSED static inline bool match200(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: ++|--
MAYBE_UNUSED static inline bool match201(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--"))))
        return false;
    return true;
}
// pattern: if|while|for|switch|assert|ASSERT (
MAYBE_UNUSED static inline bool match202(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("switch")) || (tok->str() == MatchCompiler::makeConstString("assert")) || (tok->str() == MatchCompiler::makeConstString("ASSERT"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %var% .
MAYBE_UNUSED static inline bool match203(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: std| ::| %type%
MAYBE_UNUSED static inline bool match204(const Token* tok) {
    if (tok && ((tok->str() == MatchCompiler::makeConstString("std"))))
        tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: std| ::| size_t|uintptr_t|uintmax_t
MAYBE_UNUSED static inline bool match205(const Token* tok) {
    if (tok && ((tok->str() == MatchCompiler::makeConstString("std"))))
        tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("size_t")) || (tok->str() == MatchCompiler::makeConstString("uintptr_t")) || (tok->str() == MatchCompiler::makeConstString("uintmax_t"))))
        return false;
    return true;
}
// pattern: std| ::| ssize_t|ptrdiff_t|intptr_t|intmax_t
MAYBE_UNUSED static inline bool match206(const Token* tok) {
    if (tok && ((tok->str() == MatchCompiler::makeConstString("std"))))
        tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("ssize_t")) || (tok->str() == MatchCompiler::makeConstString("ptrdiff_t")) || (tok->str() == MatchCompiler::makeConstString("intptr_t")) || (tok->str() == MatchCompiler::makeConstString("intmax_t"))))
        return false;
    return true;
}
// pattern: %name% [({]
MAYBE_UNUSED static inline bool match207(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("({", tok->str()[0]))
        return false;
    return true;
}
// pattern: }
MAYBE_UNUSED static inline bool match208(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: struct|union|enum
MAYBE_UNUSED static inline bool match209(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    return true;
}
// pattern: const|extern *|&|%name%
MAYBE_UNUSED static inline bool match210(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern"))))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || tok->isName()))
        return false;
    return true;
}
// pattern: [;{}]
MAYBE_UNUSED static inline bool match211(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name% !!;
MAYBE_UNUSED static inline bool match212(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString(";"))
        return false;
    return true;
}
// pattern: char|short|int|long|unsigned|signed|double|float
MAYBE_UNUSED static inline bool match213(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("char")) || (tok->str() == MatchCompiler::makeConstString("short")) || (tok->str() == MatchCompiler::makeConstString("int")) || (tok->str() == MatchCompiler::makeConstString("long")) || (tok->str() == MatchCompiler::makeConstString("unsigned")) || (tok->str() == MatchCompiler::makeConstString("signed")) || (tok->str() == MatchCompiler::makeConstString("double")) || (tok->str() == MatchCompiler::makeConstString("float"))))
        return false;
    return true;
}
// pattern: complex|_Complex
MAYBE_UNUSED static inline bool match214(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("complex")) || (tok->str() == MatchCompiler::makeConstString("_Complex"))))
        return false;
    return true;
}
// pattern: float|double
MAYBE_UNUSED static inline bool match215(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("float")) || (tok->str() == MatchCompiler::makeConstString("double"))))
        return false;
    return true;
}
// pattern: *|&|%name%
MAYBE_UNUSED static inline bool match216(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || tok->isName()))
        return false;
    return true;
}
// pattern: char|int
MAYBE_UNUSED static inline bool match217(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("char")) || (tok->str() == MatchCompiler::makeConstString("int"))))
        return false;
    return true;
}
// pattern: %name%|(|)
MAYBE_UNUSED static inline bool match218(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: ) ;|{|[
MAYBE_UNUSED static inline bool match219(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: const|noexcept|override|final|volatile|mutable|&|&& !!(
MAYBE_UNUSED static inline bool match220(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("noexcept")) || (tok->str() == MatchCompiler::makeConstString("override")) || (tok->str() == MatchCompiler::makeConstString("final")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || (tok->str() == MatchCompiler::makeConstString("mutable")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    return true;
}
// pattern: %name% !!(
MAYBE_UNUSED static inline bool match221(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    return true;
}
// pattern: throw|noexcept (
MAYBE_UNUSED static inline bool match222(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("throw")) || (tok->str() == MatchCompiler::makeConstString("noexcept"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ;|{|override|final|}|)|]
MAYBE_UNUSED static inline bool match223(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString("override")) || (tok->str() == MatchCompiler::makeConstString("final")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    return true;
}
// pattern: <|[|(
MAYBE_UNUSED static inline bool match224(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: override|final !!(
MAYBE_UNUSED static inline bool match225(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("override")) || (tok->str() == MatchCompiler::makeConstString("final"))))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    return true;
}
// pattern: = 0|default|delete ;
MAYBE_UNUSED static inline bool match226(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("0")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("default")) || (tok->str() == MatchCompiler::makeConstString("delete"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: requires
MAYBE_UNUSED static inline bool match227(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("requires")))
        return false;
    return true;
}
// pattern: ;|{|}|)|]
MAYBE_UNUSED static inline bool match228(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    return true;
}
// pattern: bool {
MAYBE_UNUSED static inline bool match229(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("bool")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %name%|::
MAYBE_UNUSED static inline bool match230(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/tokenlist.cpp"
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

//---------------------------------------------------------------------------

#include "tokenlist.h"

#include "astutils.h"
#include "errorlogger.h"
#include "errortypes.h"
#include "keywords.h"
#include "library.h"
#include "path.h"
#include "platform.h"
#include "settings.h"
#include "standards.h"
#include "token.h"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
#include <utility>
#include <set>
#include <stack>
#include <unordered_set>

#include <simplecpp.h>

// How many compileExpression recursions are allowed?
// For practical code this could be endless. But in some special torture test
// there needs to be a limit.
static constexpr int AST_MAX_DEPTH = 150;


TokenList::TokenList(const Settings& settings, Standards::Language lang)
    : mTokensFrontBack(new TokensFrontBack)
    , mSettings(settings)
{
    assert(lang != Standards::Language::None);
    mLang = lang;
}

TokenList::~TokenList()
{
    deallocateTokens();
}

//---------------------------------------------------------------------------

const std::string& TokenList::getSourceFilePath() const
{
    if (getFiles().empty()) {
        static const std::string s_empty_string;
        return s_empty_string;
    }
    return getFiles()[0];
}

//---------------------------------------------------------------------------

// Deallocate lists..
void TokenList::deallocateTokens()
{
    if (mTokensFrontBack) {
        deleteTokens(mTokensFrontBack->front);
        mTokensFrontBack->front = nullptr;
        mTokensFrontBack->back = nullptr;
    }
    // TODO: clear mOrigFiles?
    mFiles.clear();
}

// TODO: also update mOrigFiles?
int TokenList::appendFileIfNew(std::string fileName)
{
    assert(!fileName.empty());

    // Has this file been tokenized already?
    auto it = std::find_if(mFiles.cbegin(), mFiles.cend(), [&](const std::string& f) {
        return Path::sameFileName(f, fileName);
    });
    if (it != mFiles.cend())
        return static_cast<int>(std::distance(mFiles.cbegin(), it));

    assert(mTokensFrontBack->front == nullptr); // has no effect if tokens have already been created

    // The "mFiles" vector remembers what files have been tokenized..
    mFiles.push_back(std::move(fileName));

    return mFiles.size() - 1;
}

void TokenList::clangSetOrigFiles()
{
    mOrigFiles = mFiles;
}

void TokenList::deleteTokens(Token *tok)
{
    while (tok) {
        Token *next = tok->next();
        delete tok;
        tok = next;
    }
}

//---------------------------------------------------------------------------
// add a token.
//---------------------------------------------------------------------------

void TokenList::addtoken(const std::string& str, const nonneg int lineno, const nonneg int column, const nonneg int fileno, bool split)
{
    if (str.empty())
        return;

    // If token contains # characters, split it up
    if (split) {
        size_t begin = 0;
        size_t end = 0;
        while ((end = str.find("##", begin)) != std::string::npos) {
            addtoken(str.substr(begin, end - begin), lineno, fileno, false);
            addtoken("##", lineno, column, fileno, false);
            begin = end+2;
        }
        if (begin != 0) {
            addtoken(str.substr(begin), lineno, column, fileno, false);
            return;
        }
    }

    if (mTokensFrontBack->back) {
        mTokensFrontBack->back->insertToken(str);
    } else {
        mTokensFrontBack->front = new Token(*this, mTokensFrontBack);
        mTokensFrontBack->back = mTokensFrontBack->front;
        mTokensFrontBack->back->str(str);
    }

    mTokensFrontBack->back->linenr(lineno);
    mTokensFrontBack->back->column(column);
    mTokensFrontBack->back->fileIndex(fileno);
}

void TokenList::addtoken(const std::string& str, const Token *locationTok)
{
    if (str.empty())
        return;

    if (mTokensFrontBack->back) {
        mTokensFrontBack->back->insertToken(str);
    } else {
        mTokensFrontBack->front = new Token(*this, mTokensFrontBack);
        mTokensFrontBack->back = mTokensFrontBack->front;
        mTokensFrontBack->back->str(str);
    }

    mTokensFrontBack->back->linenr(locationTok->linenr());
    mTokensFrontBack->back->column(locationTok->column());
    mTokensFrontBack->back->fileIndex(locationTok->fileIndex());
}

void TokenList::addtoken(const Token * tok, const nonneg int lineno, const nonneg int column, const nonneg int fileno)
{
    if (tok == nullptr)
        return;

    if (mTokensFrontBack->back) {
        mTokensFrontBack->back->insertToken(tok->str(), tok->originalName());
    } else {
        mTokensFrontBack->front = new Token(*this, mTokensFrontBack);
        mTokensFrontBack->back = mTokensFrontBack->front;
        mTokensFrontBack->back->str(tok->str());
        if (!tok->originalName().empty())
            mTokensFrontBack->back->originalName(tok->originalName());
    }

    mTokensFrontBack->back->linenr(lineno);
    mTokensFrontBack->back->column(column);
    mTokensFrontBack->back->fileIndex(fileno);
    mTokensFrontBack->back->flags(tok->flags());
}

void TokenList::addtoken(const Token *tok, const Token *locationTok)
{
    if (tok == nullptr || locationTok == nullptr)
        return;

    if (mTokensFrontBack->back) {
        mTokensFrontBack->back->insertToken(tok->str(), tok->originalName());
    } else {
        mTokensFrontBack->front = new Token(*this, mTokensFrontBack);
        mTokensFrontBack->back = mTokensFrontBack->front;
        mTokensFrontBack->back->str(tok->str());
        if (!tok->originalName().empty())
            mTokensFrontBack->back->originalName(tok->originalName());
    }

    mTokensFrontBack->back->flags(tok->flags());
    mTokensFrontBack->back->linenr(locationTok->linenr());
    mTokensFrontBack->back->column(locationTok->column());
    mTokensFrontBack->back->fileIndex(locationTok->fileIndex());
}

void TokenList::addtoken(const Token *tok)
{
    if (tok == nullptr)
        return;

    if (mTokensFrontBack->back) {
        mTokensFrontBack->back->insertToken(tok->str(), tok->originalName(), tok->getMacroName());
    } else {
        mTokensFrontBack->front = new Token(*this, mTokensFrontBack);
        mTokensFrontBack->back = mTokensFrontBack->front;
        mTokensFrontBack->back->str(tok->str());
        if (!tok->originalName().empty())
            mTokensFrontBack->back->originalName(tok->originalName());
        if (!tok->getMacroName().empty())
            mTokensFrontBack->back->setMacroName(tok->getMacroName());
    }

    mTokensFrontBack->back->flags(tok->flags());
    mTokensFrontBack->back->linenr(tok->linenr());
    mTokensFrontBack->back->column(tok->column());
    mTokensFrontBack->back->fileIndex(tok->fileIndex());
}


//---------------------------------------------------------------------------
// copyTokens - Copy and insert tokens
//---------------------------------------------------------------------------

Token *TokenList::copyTokens(Token *dest, const Token *first, const Token *last, bool one_line)
{
    std::stack<Token *> links;
    Token *tok2 = dest;
    int linenr = dest->linenr();
    const int commonFileIndex = dest->fileIndex();
    for (const Token *tok = first; tok != last->next(); tok = tok->next()) {
        tok2->insertToken(tok->str());
        tok2 = tok2->next();
        tok2->fileIndex(commonFileIndex);
        tok2->linenr(linenr);
        tok2->tokType(tok->tokType());
        tok2->flags(tok->flags());
        tok2->varId(tok->varId());
        tok2->setTokenDebug(tok->getTokenDebug());

        // Check for links and fix them up
        if (match1(tok2))
            links.push(tok2);
        else if (match2(tok2)) {
            if (links.empty())
                return tok2;

            Token * link = links.top();

            tok2->link(link);
            link->link(tok2);

            links.pop();
        }
        if (!one_line && tok->next())
            linenr += tok->next()->linenr() - tok->linenr();
    }
    return tok2;
}

//---------------------------------------------------------------------------
// InsertTokens - Copy and insert tokens
//---------------------------------------------------------------------------

void TokenList::insertTokens(Token *dest, const Token *src, nonneg int n)
{
    // TODO: put the linking in a helper?
    std::stack<Token *> link;

    while (n > 0) {
        dest->insertToken(src->str(), src->originalName());
        dest = dest->next();

        // Set links
        if (match1(dest))
            link.push(dest);
        else if (!link.empty() && match2(dest)) {
            Token::createMutualLinks(dest, link.top());
            link.pop();
        }

        dest->fileIndex(src->fileIndex());
        dest->linenr(src->linenr());
        dest->column(src->column());
        dest->varId(src->varId());
        dest->tokType(src->tokType());
        dest->flags(src->flags());
        if (!src->getMacroName().empty())
            dest->setMacroName(src->getMacroName());
        src  = src->next();
        --n;
    }
}

//---------------------------------------------------------------------------

bool TokenList::createTokensFromBuffer(const uint8_t* data, size_t size)
{
    return createTokensFromBufferInternal(data, size, mFiles.empty() ? "" : *mFiles.cbegin());
}

//---------------------------------------------------------------------------

bool TokenList::createTokensFromBufferInternal(const uint8_t* data, size_t size, const std::string& file0)
{
    simplecpp::OutputList outputList;
    simplecpp::TokenList tokens(data, size, mFiles, file0, &outputList);

    createTokens(std::move(tokens));

    return outputList.empty();
}

//---------------------------------------------------------------------------

// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
void TokenList::createTokens(simplecpp::TokenList&& tokenList)
{
    // TODO: what to do if the list has been filled already? clear mTokensFrontBack?

    // tokenList.cfront() might be NULL if the file contained nothing to tokenize so we need to check the files instead
    if (!tokenList.getFiles().empty()) {
        // this is a copy
        // TODO: this points to mFiles when called from createTokens(std::istream &, const std::string&)
        mOrigFiles = mFiles = tokenList.getFiles();
    }
    else {
        // TODO: clear mOrigFiles?
        mFiles.clear();
    }

    for (const simplecpp::Token *tok = tokenList.cfront(); tok;) {

        // TODO: move from TokenList
        std::string str = tok->str();

        // Float literal
        if (str.size() > 1 && str[0] == '.' && std::isdigit(str[1]))
            str = '0' + str;

        if (mTokensFrontBack->back) {
            mTokensFrontBack->back->insertToken(str);
        } else {
            mTokensFrontBack->front = new Token(*this, mTokensFrontBack);
            mTokensFrontBack->back = mTokensFrontBack->front;
            mTokensFrontBack->back->str(str);
        }

        mTokensFrontBack->back->fileIndex(tok->location.fileIndex);
        mTokensFrontBack->back->linenr(tok->location.line);
        mTokensFrontBack->back->column(tok->location.col);
        if (!tok->macro.empty())
            mTokensFrontBack->back->setMacroName(tok->macro);

        tok = tok->next;
        if (tok)
            tokenList.deleteToken(tok->previous);
    }

    if (mSettings.relativePaths) {
        for (std::string & mFile : mFiles)
            mFile = Path::getRelativePath(mFile, mSettings.basePaths);
    }

    Token::assignProgressValues(mTokensFrontBack->front);
}

//---------------------------------------------------------------------------

std::size_t TokenList::calculateHash() const
{
    std::string hashData;
    for (const Token* tok = front(); tok; tok = tok->next()) {
        hashData += std::to_string(tok->flags());
        hashData += std::to_string(tok->varId());
        hashData += std::to_string(tok->tokType());
        hashData += tok->str();
        hashData += tok->originalName();
    }
    return (std::hash<std::string>{})(hashData);
}


//---------------------------------------------------------------------------

namespace {
    struct AST_state {
        std::stack<Token*> op;
        int depth{};
        int inArrayAssignment{};
        bool cpp;
        int assign{};
        bool inCase{}; // true from case to :
        bool inGeneric{};
        bool stopAtColon{}; // help to properly parse ternary operators
        const Token* functionCallEndPar{};
        explicit AST_state(bool cpp) : cpp(cpp) {}
    };
}

static Token* skipDecl(Token* tok, std::vector<Token*>* inner = nullptr)
{
    auto isDecltypeFuncParam = [](const Token* tok) -> bool {
        if (!match3(tok))
            return false;
        tok = tok->next();
        while (match4(tok))
            tok = tok->next();
        if (match5(tok))
            tok = tok->link()->next();
        return match6(tok);
    };

    if (!match7(tok->previous()))
        return tok;
    Token *vartok = tok;
    while (match8(vartok)) {
        if (vartok->str() == MatchCompiler::makeConstString("<")) {
            if (vartok->link())
                vartok = vartok->link();
            else
                return tok;
        } else if (match9(vartok)) {
            return vartok;
        } else if (match10(vartok) && !isDecltypeFuncParam(tok->linkAt(1))) {
            if (inner)
                inner->push_back(vartok->tokAt(2));
            return vartok->linkAt(1)->next();
        }
        vartok = vartok->next();
    }
    return tok;
}

static bool iscast(const Token *tok, bool cpp)
{
    if (!match11(tok))
        return false;

    if (match12(tok->link()))
        return false;

    if (match13(tok->link()))
        return false;

    if (tok->previous() && tok->previous()->isName() && !match14(tok->previous()) &&
        (!cpp || !match15(tok->previous())))
        return false;

    if (match16(tok->previous()) && tok->linkAt(-1))
        return false;

    if (match17(tok) && match18(tok->link()))
        return true;

    if (match19(tok->link()))
        return false;

    if (match20(tok->link()))
        return false;

    if (match21(tok->link()) && !match22(tok->link()))
        return false;

    if (match23(tok->previous()) && tok->next()->varId() == 0)
        return true;

    bool type = false;
    for (const Token *tok2 = tok->next(); tok2; tok2 = tok2->next()) {
        if (tok2->varId() != 0)
            return false;
        if (cpp && !type && tok2->str() == MatchCompiler::makeConstString("new"))
            return false;

        while (tok2->link() && match24(tok2))
            tok2 = tok2->link()->next();

        if (tok2->str() == MatchCompiler::makeConstString(")")) {
            if (match25(tok2) && match26(tok2->linkAt(1)))
                return true;
            if (match27(tok2) && !type) {
                const Token *tok3 = tok2->linkAt(1);
                while (tok3 != tok2 && match28(tok3))
                    tok3 = tok3->previous();
                return tok3->str() != MatchCompiler::makeConstString(";");
            }
            const bool res = type || tok2->strAt(-1) == MatchCompiler::makeConstString("*") || match29(tok2) ||
                             (match30(tok2) &&
                              (!tok2->next()->isOp() || match31(tok2->next())) &&
                              !match32(tok2->next()));
            return res;
        }

        if (match33(tok2))
            return true;

        if (!match34(tok2))
            return false;

        if (tok2->isStandardType() && (tok2->strAt(1) != MatchCompiler::makeConstString("(") || match35(tok2->next())))
            type = true;
    }

    return false;
}

// int(1), int*(2), ..
static Token * findCppTypeInitPar(Token *tok)
{
    if (!tok || !match36(tok->previous()))
        return nullptr;
    bool istype = false;
    while (match37(tok)) {
        if (tok->str() == MatchCompiler::makeConstString("<")) {
            tok = tok->link();
            if (!tok)
                return nullptr;
        }
        istype |= tok->isStandardType();
        tok = tok->next();
    }
    if (!istype)
        return nullptr;
    if (!match38(tok))
        return nullptr;
    while (match38(tok))
        tok = tok->next();
    return (tok && tok->str() == MatchCompiler::makeConstString("(")) ? tok : nullptr;
}

// X{} X<Y>{} etc
static bool iscpp11init_impl(const Token * tok);
static bool iscpp11init(const Token * const tok)
{
    if (tok->isCpp11init() == Token::Cpp11init::UNKNOWN)
        tok->setCpp11init(iscpp11init_impl(tok));
    return tok->isCpp11init() == Token::Cpp11init::CPP11INIT;
}

static bool iscpp11init_impl(const Token * const tok)
{
    if (match39(tok) && match40(tok->link()->previous()))
        return false;
    const Token *nameToken = tok;
    while (nameToken && nameToken->str() == MatchCompiler::makeConstString("{")) {
        if (nameToken->isCpp11init() != Token::Cpp11init::UNKNOWN)
            return nameToken->isCpp11init() == Token::Cpp11init::CPP11INIT;
        nameToken = nameToken->previous();
        if (nameToken && nameToken->str() == MatchCompiler::makeConstString(",") && match41(nameToken->previous()))
            nameToken = nameToken->linkAt(-1);
    }
    if (!nameToken)
        return false;
    if (nameToken->str() == MatchCompiler::makeConstString(")") && match42(nameToken->link()->previous()) &&
        !match43(nameToken->link()->tokAt(-2)))
        nameToken = nameToken->link()->previous();
    if (match44(nameToken))
        return true;
    if (nameToken->str() == MatchCompiler::makeConstString(">") && nameToken->link())
        nameToken = nameToken->link()->previous();
    if (match45(nameToken)) {
        const Token* newTok = nameToken->link() ? nameToken->link()->previous() : nameToken->previous();
        while (match46(newTok) && !newTok->isKeyword())
            newTok = newTok->previous();
        if (match47(newTok))
            return true;
    }

    auto isCaseStmt = [](const Token* colonTok) {
        if (!match48(colonTok->tokAt(-1)))
            return false;
        if (const Token* castTok = colonTok->linkAt(-1)) {
            if (match49(castTok->astParent()))
                return true;
        }
        if (findParent(colonTok->previous(), [](const Token *parent){
            return parent->str() == MatchCompiler::makeConstString("case");
        }))
            return true;
        const Token* caseTok = colonTok->tokAt(-2);
        while (caseTok && match50(caseTok->tokAt(-1)))
            caseTok = caseTok->tokAt(-1);
        return match49(caseTok);
    };

    const Token *endtok = nullptr;
    if (match51(nameToken) && !isCaseStmt(nameToken) &&
        (!match52(nameToken->tokAt(2)) || findLambdaEndScope(nameToken->tokAt(2))))
        endtok = nameToken->linkAt(1);
    else if (match53(nameToken) && match54(nameToken->linkAt(1)))
        endtok = nameToken->linkAt(1)->linkAt(1);
    else if (match55(nameToken->previous()))
        endtok = nameToken->linkAt(1);
    else if (match56(nameToken) && nameToken->linkAt(1))
        endtok = nameToken->linkAt(1)->linkAt(1);
    else
        return false;
    if (match57(nameToken))
        return false;
    if (match58(nameToken->previous()) && nameToken->previous()->originalName() == MatchCompiler::makeConstString("->"))
        return false; // trailing return type. The only function body that can contain no semicolon is a void function.
    if (match59(nameToken->previous()) || match59(nameToken) /*anonymous namespace*/)
        return false;
    if (precedes(nameToken->next(), endtok) && !match60(nameToken)) {
        // If there is semicolon between {..} this is not a initlist
        for (const Token *tok2 = nameToken->next(); tok2 != endtok; tok2 = tok2->next()) {
            if (tok2->str() == MatchCompiler::makeConstString(";"))
                return false;
            const Token * lambdaEnd = findLambdaEndScope(tok2);
            if (lambdaEnd)
                tok2 = lambdaEnd;
        }
    }
    // There is no initialisation for example here: 'class Fred {};'
    if (!match61(endtok))
        return true;
    const Token *prev = nameToken;
    while (match62(prev)) {
        if (match63(prev))
            return false;

        prev = prev->previous();
    }
    return true;
}

static bool isQualifier(const Token* tok)
{
    while (match64(tok))
        tok = tok->next();
    return match65(tok);
}

static void compileUnaryOp(Token *&tok, AST_state& state, void (*f)(Token *&tok, AST_state& state))
{
    Token *unaryop = tok;
    if (f) {
        tok = tok->next();
        state.depth++;
        if (state.depth > AST_MAX_DEPTH)
            throw InternalError(tok, "maximum AST depth exceeded", InternalError::AST);
        if (tok)
            f(tok, state);
        state.depth--;
    }

    if (!state.op.empty() && (!precedes(state.op.top(), unaryop) || unaryop->isIncDecOp() || match66(unaryop))) { // nullary functions, empty lists/arrays
        unaryop->astOperand1(state.op.top());
        state.op.pop();
    }
    state.op.push(unaryop);
}

static void skipGenericType(Token *&tok)
{
    Token *skip = tok;
    while (match67(skip)) {
        if (skip->link()) {
            skip = skip->link()->next();
            continue;
        }
        if (match68(skip)) {
            tok = skip->next();
            return;
        }
        skip = skip->next();
    }
}

static void compileBinOp(Token *&tok, AST_state& state, void (*f)(Token *&tok, AST_state& state))
{
    Token *binop = tok;
    if (f) {
        tok = tok->next();
        if (match69(binop) && state.inGeneric)
            skipGenericType(tok);
        const bool inGenericSaved = state.inGeneric;
        state.inGeneric = false;
        if (match70(binop))
            tok = tok->next();
        state.depth++;
        if (tok && state.depth <= AST_MAX_DEPTH)
            f(tok, state);
        if (state.depth > AST_MAX_DEPTH)
            throw InternalError(tok, "maximum AST depth exceeded", InternalError::AST);
        state.depth--;
        state.inGeneric = inGenericSaved;
    }

    // TODO: Should we check if op is empty.
    // * Is it better to add assertion that it isn't?
    // * Write debug warning if it's empty?
    if (!state.op.empty()) {
        binop->astOperand2(state.op.top());
        state.op.pop();
    }
    if (!state.op.empty()) {
        binop->astOperand1(state.op.top());
        state.op.pop();
    }
    state.op.push(binop);
}

static void compileExpression(Token *&tok, AST_state& state);

static void compileTerm(Token *&tok, AST_state& state)
{
    if (!tok)
        return;
    if (match71(tok))
        tok = tok->next();
    if (state.inArrayAssignment && match72(tok->previous())) { // Jump over . in C style struct initialization
        state.op.push(tok);
        tok->astOperand1(tok->next());
        tok = tok->tokAt(2);
    }
    if (state.inArrayAssignment && match73(tok->previous())) {
        state.op.push(tok);
        tok->astOperand1(tok->next());
        tok = tok->tokAt(3);
    }
    if (tok->isLiteral()) {
        state.op.push(tok);
        do {
            tok = tok->next();
        } while (match74(tok));
    } else if (tok->isName()) {
        if (match14(tok) || (state.cpp && (tok->str() == MatchCompiler::makeConstString("throw")))) {
            if (tok->str() == MatchCompiler::makeConstString("case"))
                state.inCase = true;
            const bool tokIsReturn = tok->str() == MatchCompiler::makeConstString("return");
            const bool stopAtColon = state.stopAtColon;
            state.stopAtColon=true;
            compileUnaryOp(tok, state, compileExpression);
            state.stopAtColon=stopAtColon;
            if (tokIsReturn)
                state.op.pop();
            if (state.inCase && match75(tok)) {
                state.inCase = false;
                tok = tok->next();
            }
        } else if (match76(tok)) {
            compileUnaryOp(tok, state, compileExpression);
            state.op.pop();
        } else if (state.cpp && findCppTypeInitPar(tok)) {  // int(0), int*(123), ..
            tok = findCppTypeInitPar(tok);
            state.op.push(tok);
            tok = tok->tokAt(2);
        } else if (state.cpp && iscpp11init(tok)) { // X{} X<Y>{} etc
            state.op.push(tok);
            tok = tok->next();
            if (tok->str() == MatchCompiler::makeConstString("<"))
                tok = tok->link()->next();

            if (match77(tok)) {
                const Token* end = tok->link();
                const int inArrayAssignment = state.inArrayAssignment;
                state.inArrayAssignment = 1;
                compileBinOp(tok, state, compileExpression);
                state.inArrayAssignment = inArrayAssignment;
                if (tok == end)
                    tok = tok->next();
                else
                    throw InternalError(tok, "Syntax error. Unexpected tokens in designated initializer.", InternalError::AST);
            }
        } else if (!state.cpp || !match78(tok)) {
            std::vector<Token*> inner;
            tok = skipDecl(tok, &inner);
            for (Token* tok3 : inner) {
                AST_state state1(state.cpp);
                compileExpression(tok3, state1);
            }
            bool repeat = true;
            while (repeat) {
                repeat = false;
                if (match79(tok->next())) {
                    tok = tok->next();
                    repeat = true;
                }
                if (match81(tok->next()) && match80(tok->linkAt(1))) {
                    tok = tok->linkAt(1)->next();
                    repeat = true;
                }
            }
            state.op.push(tok);
            if (match53(tok) && tok->linkAt(1))
                tok = tok->linkAt(1);
            else if (match82(tok) || (state.op.size() == 1 && state.depth == 0 && match83(tok->tokAt(-3))))
                tok = tok->next();
            tok = tok->next();
            if (match84(tok)) {
                while (match74(tok))
                    tok = tok->next();
            }
            if (match85(tok))
                tok = tok->next();
        }
    } else if (tok->str() == MatchCompiler::makeConstString("{")) {
        const Token *prev = tok->previous();
        if (match27(prev) && iscast(prev->link(), state.cpp))
            prev = prev->link()->previous();
        if (match86(tok->link())) {
            tok = tok->next();
        } else if ((state.cpp && iscpp11init(tok)) || match87(tok->previous())) {
            Token *const end = tok->link();
            if (state.op.empty() || match88(tok->previous()) || match89(tok->tokAt(-2))) {
                if (match90(tok->tokAt(-1)) && !match5(tok->tokAt(-1))) {
                    const int inArrayAssignment = state.inArrayAssignment;
                    state.inArrayAssignment = 1;
                    compileBinOp(tok, state, compileExpression);
                    state.inArrayAssignment = inArrayAssignment;
                } else if (match91(tok)) {
                    state.op.push(tok);
                    tok = tok->next();
                } else {
                    compileUnaryOp(tok, state, compileExpression);
                    if (precedes(tok,end)) // typically for something like `MACRO(x, { if (c) { ... } })`, where end is the last curly, and tok is the open curly for the if
                        tok = end;
                }
            } else if (tok->next() == end) {
                tok->astOperand1(state.op.top());
                state.op.pop();
                tok = tok->next();
            } else
                compileBinOp(tok, state, compileExpression);
            if (tok != end)
                throw InternalError(tok, "Syntax error. Unexpected tokens in initializer.", InternalError::AST);
            if (tok->next())
                tok = tok->next();
        } else if (state.cpp && match92(tok->tokAt(-2)) && !findmatch93(tok, tok->link()) ) {
            if (match91(tok))
                tok = tok->tokAt(2);
            else {
                Token *tok1 = tok;
                state.inArrayAssignment++;
                compileUnaryOp(tok, state, compileExpression);
                state.inArrayAssignment--;
                tok = tok1->link()->next();
            }
        } else if (!state.inArrayAssignment && !match94(prev)) {
            state.op.push(tok);
            tok = tok->link()->next();
        } else {
            if (tok->link() != tok->next()) {
                state.inArrayAssignment++;
                compileUnaryOp(tok, state, compileExpression);
                if (match95(tok) && state.inArrayAssignment > 0) {
                    tok = tok->next();
                    state.inArrayAssignment--;
                }
            } else {
                state.op.push(tok);
                tok = tok->tokAt(2);
            }
        }
    }
}

static void compileScope(Token *&tok, AST_state& state)
{
    compileTerm(tok, state);
    while (tok) {
        if (tok->str() == MatchCompiler::makeConstString("::")) {
            const Token *lastOp = state.op.empty() ? nullptr : state.op.top();
            if (match96(lastOp))
                lastOp = lastOp->next();
            if (match79(lastOp) &&
                (lastOp->next() == tok || (match53(lastOp) && lastOp->linkAt(1) && tok == lastOp->linkAt(1)->next())))
                compileBinOp(tok, state, compileTerm);
            else
                compileUnaryOp(tok, state, compileTerm);
        } else break;
    }
}

static bool isPrefixUnary(const Token* tok, bool cpp)
{
    if (cpp && match97(tok->previous()) && match87(tok->link())) {
        for (const Token* prev = tok->previous(); match98(prev); prev = prev->previous()) {
            if (match99(prev)) {
                if (!prev->link())
                    break;
                prev = prev->link();
            }
            if (prev->str() == MatchCompiler::makeConstString("new"))
                return false;
        }
    }
    if (!tok->previous()
        || ((match100(tok->previous()) || (cpp && tok->strAt(-1) == MatchCompiler::makeConstString("throw")))
            && (tok->previous()->tokType() != Token::eIncDecOp || tok->tokType() == Token::eIncDecOp)))
        return true;

    if (tok->strAt(-1) == MatchCompiler::makeConstString("}")) {
        const Token* parent = tok->linkAt(-1)->tokAt(-1);
        return !match101(parent) || parent->isKeyword();
    }

    if (tok->str() == MatchCompiler::makeConstString("*") && tok->previous()->tokType() == Token::eIncDecOp && isPrefixUnary(tok->previous(), cpp))
        return true;

    return tok->strAt(-1) == MatchCompiler::makeConstString(")") && iscast(tok->linkAt(-1), cpp);
}

static void compilePrecedence2(Token *&tok, AST_state& state)
{
    auto doCompileScope = [&](const Token* tok) -> bool {
        const bool isStartOfCpp11Init = state.cpp && tok && tok->str() == MatchCompiler::makeConstString("{") && iscpp11init(tok);
        if (isStartOfCpp11Init || match5(tok)) {
            tok = tok->previous();
            while (match102(tok))
                tok = tok->previous();
            while (tok && match103(tok->previous()))
                tok = tok->tokAt(-2);
            if (tok && !tok->isKeyword())
                tok = tok->previous();
            return !match104(tok);
        }
        return !findLambdaEndTokenWithoutAST(tok);
    };

    bool isNew = true;
    if (doCompileScope(tok)) {
        compileScope(tok, state);
        isNew = false;
    }
    while (tok) {
        if (tok->tokType() == Token::eIncDecOp && !isPrefixUnary(tok, state.cpp)) {
            compileUnaryOp(tok, state, compileScope);
        } else if (tok->str() == MatchCompiler::makeConstString("...")) {
            if (!match3(tok->previous()))
                state.op.push(tok);
            tok = tok->next();
            break;
        } else if (tok->str() == MatchCompiler::makeConstString(".") && tok->strAt(1) != MatchCompiler::makeConstString("*")) {
            if (tok->strAt(1) == MatchCompiler::makeConstString(".")) {
                state.op.push(tok);
                tok = tok->tokAt(3);
                break;
            }
            if (!match88(tok->tokAt(-1)))
                compileBinOp(tok, state, compileScope);
            else
                compileUnaryOp(tok, state, compileScope);
        } else if (tok->str() == MatchCompiler::makeConstString("[")) {
            if (state.cpp && isPrefixUnary(tok, /*cpp*/ true) && match105(tok->link())) { // Lambda
                // What we do here:
                // - Nest the round bracket under the square bracket.
                // - Nest what follows the lambda (if anything) with the lambda opening [
                // - Compile the content of the lambda function as separate tree (this is done later)
                // this must be consistent with isLambdaCaptureList
                Token* const squareBracket = tok;
                // Parse arguments in the capture list
                if (tok->strAt(1) != MatchCompiler::makeConstString("]")) {
                    Token* tok2 = tok->next();
                    AST_state state2(state.cpp);
                    compileExpression(tok2, state2);
                    if (!state2.op.empty()) {
                        squareBracket->astOperand2(state2.op.top());
                    }
                }

                const bool hasTemplateArg = match106(squareBracket->link()) &&
                                            match107(squareBracket->link()->linkAt(1));
                if (match108(squareBracket->link()) || hasTemplateArg) {
                    Token* const roundBracket = hasTemplateArg ? squareBracket->link()->linkAt(1)->next() : squareBracket->link()->next();
                    Token* curlyBracket = roundBracket->link()->next();
                    while (match109(curlyBracket))
                        curlyBracket = curlyBracket->next();
                    if (match110(curlyBracket)) {
                        if (match5(curlyBracket->next())) {
                            AST_state state2(state.cpp);
                            Token *tok2 = curlyBracket->tokAt(2);
                            compileExpression(tok2, state2);
                            curlyBracket = curlyBracket->linkAt(1)->next();
                        } else
                            curlyBracket = curlyBracket->next();
                    }
                    if (curlyBracket && curlyBracket->originalName() == MatchCompiler::makeConstString("->")) {
                        if (match42(curlyBracket->next())) {
                            AST_state state2(state.cpp);
                            Token *tok2 = curlyBracket->tokAt(3);
                            compileExpression(tok2, state2);
                        }
                        curlyBracket = findTypeEnd(curlyBracket->next());
                    }
                    if (curlyBracket && curlyBracket->str() == MatchCompiler::makeConstString("{")) {
                        squareBracket->astOperand1(roundBracket);
                        roundBracket->astOperand1(curlyBracket);
                        state.op.push(squareBracket);
                        tok = curlyBracket->link()->next();
                        continue;
                    }
                } else {
                    Token* const curlyBracket = squareBracket->link()->next();
                    squareBracket->astOperand1(curlyBracket);
                    state.op.push(squareBracket);
                    tok = curlyBracket->link() ? curlyBracket->link()->next() : nullptr;
                    continue;
                }
            }

            Token* const tok2 = tok;
            if (tok->strAt(1) != MatchCompiler::makeConstString("]")) {
                compileBinOp(tok, state, compileExpression);
                if (match111(tok2->previous()) && match112(tok)) {
                    tok = tok->next();
                    Token* const tok3 = tok;
                    compileBinOp(tok, state, compileExpression);
                    if (tok != tok3->link())
                        throw InternalError(tok, "Syntax error in {..}", InternalError::AST);
                    tok = tok->next();
                    continue;
                }
            }
            else
                compileUnaryOp(tok, state, compileExpression);
            tok = tok2->link()->next();
        } else if (match113(tok->previous())) {
            tok->astOperand1(state.op.top());
            state.op.pop();
            state.op.push(tok);
            tok = tok->link()->next();
            continue;
        } else if (match114(tok) && match115(tok->linkAt(1)->previous()) &&
                   !match89(tok->previous())) {
            state.op.push(tok->next());
            tok = tok->link()->next();
            continue;
        } else if (tok->str() == MatchCompiler::makeConstString("(") &&
                   (!iscast(tok, state.cpp) || match116(tok->previous()))) {
            const bool inGenericSaved = state.inGeneric;
            if (match117(tok->previous()))
                state.inGeneric = true;
            Token* tok2 = tok;
            tok = tok->next();
            const bool opPrevTopSquare = !state.op.empty() && state.op.top() && state.op.top()->str() == MatchCompiler::makeConstString("[");
            const std::size_t oldOpSize = state.op.size();
            compileExpression(tok, state);
            tok = tok2;
            if ((oldOpSize > 0 && (isNew || match118(tok->previous())))
                || (tok->previous() && tok->previous()->isName() && !match14(tok->previous()) && (!state.cpp || !match119(tok->previous())))
                || (tok->strAt(-1) == MatchCompiler::makeConstString("]") && (!state.cpp || !match120(tok->linkAt(-1)->previous())))
                || (tok->strAt(-1) == MatchCompiler::makeConstString(">") && tok->linkAt(-1))
                || (tok->strAt(-1) == MatchCompiler::makeConstString(")") && !iscast(tok->linkAt(-1), state.cpp)) // Don't treat brackets to clarify precedence as function calls
                || (tok->strAt(-1) == MatchCompiler::makeConstString("}") && opPrevTopSquare)) {
                const bool operandInside = oldOpSize < state.op.size();
                if (operandInside)
                    compileBinOp(tok, state, nullptr);
                else
                    compileUnaryOp(tok, state, nullptr);
            }
            state.inGeneric = inGenericSaved;
            tok = tok->link()->next();
            if (match121(tok))
                compileBinOp(tok, state, compileScope);
        } else if (iscast(tok, state.cpp) && match27(tok->link()) &&
                   match86(tok->link()->linkAt(1))) {
            Token *cast = tok;
            tok = tok->link()->next();
            Token *tok1 = tok;
            compileUnaryOp(tok, state, compileExpression);
            cast->astOperand1(tok1);
            tok = tok1->link()->next();
        } else if (state.cpp && tok->str() == MatchCompiler::makeConstString("{") && iscpp11init(tok)) {
            Token* end = tok->link();
            if (match91(tok))
            {
                compileUnaryOp(tok, state, nullptr);
                tok = tok->next();
            }
            else
            {
                compileBinOp(tok, state, compileExpression);
            }
            if (tok == end)
                tok = end->next();
            else
                throw InternalError(tok, "Syntax error. Unexpected tokens in initializer.", InternalError::AST);
        } else
            break;
    }
}

static void compilePrecedence3(Token *&tok, AST_state& state)
{
    compilePrecedence2(tok, state);
    while (tok) {
        if ((match122(tok) || tok->tokType() == Token::eIncDecOp) &&
            isPrefixUnary(tok, state.cpp)) {
            if (match123(tok)) {
                Token* tok2 = tok->next();
                while (tok2->next() && tok2->str() == MatchCompiler::makeConstString("*"))
                    tok2 = tok2->next();
                if (match124(tok2)) {
                    tok = tok2;
                    continue;
                }
            }
            compileUnaryOp(tok, state, compilePrecedence3);
        } else if (tok->str() == MatchCompiler::makeConstString("(") && iscast(tok, state.cpp)) {
            Token* castTok = tok;
            castTok->isCast(true);
            tok = tok->link()->next();
            const int inArrayAssignment = state.inArrayAssignment;
            if (tok && tok->str() == MatchCompiler::makeConstString("{"))
                state.inArrayAssignment = 1;
            compilePrecedence3(tok, state);
            state.inArrayAssignment = inArrayAssignment;
            compileUnaryOp(castTok, state, nullptr);
        } else if (state.cpp && match125(tok)) {
            Token* newtok = tok;
            tok = tok->next();
            bool innertype = false;
            if (tok->str() == MatchCompiler::makeConstString("(")) {
                if (match126(tok) && match127(tok->link()) && match25(tok->link()->linkAt(1)))
                    tok = tok->link()->next();
                if (match128(tok->link())) {
                    if (match129(tok)) {
                        Token *innerTok = tok->next();
                        AST_state innerState(true);
                        compileExpression(innerTok, innerState);
                    }
                    tok = tok->link()->next();
                } else if (match130(tok) && match131(tok->link())) {
                    tok = tok->next();
                    innertype = true;
                } else if (match126(tok) && match25(tok->link())) {
                    tok = tok->next();
                    innertype = true;
                } else {
                    /* bad code */
                    continue;
                }
            }

            Token* leftToken = tok;
            if (match121(tok)) {
                tok->astOperand1(tok->next());
                tok = tok->next();
            }
            else {
                while (match96(tok->next())) {
                    Token* scopeToken = tok->next(); //The ::
                    scopeToken->astOperand1(leftToken);
                    scopeToken->astOperand2(scopeToken->next());
                    leftToken = scopeToken;
                    tok = scopeToken->next();
                }
            }

            state.op.push(tok);
            while (match132(tok)) {
                if (tok->link())
                    tok = tok->link();
                tok = tok->next();
            }
            if (match133(tok)) {
                state.op.push(tok->next());
                tok = tok->link()->next();
                compileBinOp(tok, state, compilePrecedence2);
            } else if (match134(tok))
                compilePrecedence2(tok, state);
            else if (innertype && match135(tok)) {
                tok = tok->next();
                compilePrecedence2(tok, state);
            }
            compileUnaryOp(newtok, state, nullptr);
            if (match136(newtok->previous())) {
                newtok->previous()->astOperand1(newtok);
                state.op.pop();
            }
            if (innertype && match137(tok))
                tok = tok->next();
        } else if (state.cpp && match138(tok)) {
            Token* tok2 = tok;
            tok = tok->next();
            if (tok && tok->str() == MatchCompiler::makeConstString("["))
                tok = tok->link()->next();
            compilePrecedence3(tok, state);
            compileUnaryOp(tok2, state, nullptr);
            if (match139(tok2->previous())) {
                tok2->previous()->astOperand1(tok2);
                state.op.pop();
            }
        }
        // TODO: Handle sizeof
        else break;
    }
}

static void compilePointerToElem(Token *&tok, AST_state& state)
{
    compilePrecedence3(tok, state);
    while (tok) {
        if (match140(tok)) {
            compileBinOp(tok, state, compilePrecedence3);
        } else break;
    }
}

static void compileMulDiv(Token *&tok, AST_state& state)
{
    compilePointerToElem(tok, state);
    while (tok) {
        if (match141(tok) || (tok->str() == MatchCompiler::makeConstString("*") && !tok->astOperand1() && !isQualifier(tok))) {
            if (match123(tok)) {
                Token* tok2 = tok->next();
                while (tok2->next() && tok2->str() == MatchCompiler::makeConstString("*"))
                    tok2 = tok2->next();
                if (match124(tok2)) {
                    tok = tok2;
                    break;
                }
            }
            compileBinOp(tok, state, compilePointerToElem);
        } else break;
    }
}

static void compileAddSub(Token *&tok, AST_state& state)
{
    compileMulDiv(tok, state);
    while (tok) {
        if (match142(tok) && !tok->astOperand1()) {
            compileBinOp(tok, state, compileMulDiv);
        } else break;
    }
}

static void compileShift(Token *&tok, AST_state& state)
{
    compileAddSub(tok, state);
    while (tok) {
        if (match143(tok)) {
            compileBinOp(tok, state, compileAddSub);
        } else break;
    }
}

static void compileThreewayComp(Token *&tok, AST_state& state)
{
    compileShift(tok, state);
    while (tok) {
        if (tok->str() == MatchCompiler::makeConstString("<=>")) {
            compileBinOp(tok, state, compileShift);
        } else break;
    }
}

static void compileRelComp(Token *&tok, AST_state& state)
{
    compileThreewayComp(tok, state);
    while (tok) {
        if (match144(tok) && !tok->link()) {
            compileBinOp(tok, state, compileThreewayComp);
        } else break;
    }
}

static void compileEqComp(Token *&tok, AST_state& state)
{
    compileRelComp(tok, state);
    while (tok) {
        if (match145(tok)) {
            compileBinOp(tok, state, compileRelComp);
        } else break;
    }
}

static void compileAnd(Token *&tok, AST_state& state)
{
    compileEqComp(tok, state);
    while (tok) {
        if (tok->str() == MatchCompiler::makeConstString("&") && !tok->astOperand1() && !isQualifier(tok)) {
            Token* tok2 = tok->next();
            if (!tok2)
                break;
            if (tok2->str() == MatchCompiler::makeConstString("&"))
                tok2 = tok2->next();
            if (state.cpp && match146(tok2)) {
                tok = tok2;
                break; // rValue reference
            }
            compileBinOp(tok, state, compileEqComp);
        } else break;
    }
}

static void compileXor(Token *&tok, AST_state& state)
{
    compileAnd(tok, state);
    while (tok) {
        if (tok->str() == MatchCompiler::makeConstString("^")) {
            compileBinOp(tok, state, compileAnd);
        } else break;
    }
}

static void compileOr(Token *&tok, AST_state& state)
{
    compileXor(tok, state);
    while (tok) {
        if (tok->str() == MatchCompiler::makeConstString("|")) {
            compileBinOp(tok, state, compileXor);
        } else break;
    }
}

static void compileLogicAnd(Token *&tok, AST_state& state)
{
    compileOr(tok, state);
    while (tok) {
        if (tok->str() == MatchCompiler::makeConstString("&&") && !isQualifier(tok)) {
            if (!tok->astOperand1()) {
                Token* tok2 = tok->next();
                if (!tok2)
                    break;
                if (state.cpp && match146(tok2)) {
                    tok = tok2;
                    break; // rValue reference
                }
            }
            compileBinOp(tok, state, compileOr);
        } else break;
    }
}

static void compileLogicOr(Token *&tok, AST_state& state)
{
    compileLogicAnd(tok, state);
    while (tok) {
        if (tok->str() == MatchCompiler::makeConstString("||")) {
            compileBinOp(tok, state, compileLogicAnd);
        } else break;
    }
}

static void compileAssignTernary(Token *&tok, AST_state& state)
{
    compileLogicOr(tok, state);
    while (tok) {
        if (tok->isAssignmentOp()) {
            state.assign++;
            const Token *tok1 = tok->next();
            compileBinOp(tok, state, compileAssignTernary);
            if (match39(tok1) && tok == tok1->link() && tok->next())
                tok = tok->next();
            if (state.assign > 0)
                state.assign--;
        } else if (tok->str() == MatchCompiler::makeConstString("?")) {
            // http://en.cppreference.com/w/cpp/language/operator_precedence says about ternary operator:
            //       "The expression in the middle of the conditional operator (between ? and :) is parsed as if parenthesized: its precedence relative to ?: is ignored."
            // Hence, we rely on Tokenizer::prepareTernaryOpForAST() to add such parentheses where necessary.
            const bool stopAtColon = state.stopAtColon;
            state.stopAtColon = false;
            if (tok->strAt(1) == MatchCompiler::makeConstString(":")) {
                state.op.push(nullptr);
            }
            const int assign = state.assign;
            state.assign = 0;
            compileBinOp(tok, state, compileAssignTernary);
            state.assign = assign;
            state.stopAtColon = stopAtColon;
        } else if (tok->str() == MatchCompiler::makeConstString(":")) {
            if (state.depth == 1U && state.inCase) {
                state.inCase = false;
                tok = tok->next();
                break;
            }
            if (state.stopAtColon)
                break;
            if (state.assign > 0)
                break;
            compileBinOp(tok, state, compileAssignTernary);
        } else break;
    }
}

static void compileComma(Token *&tok, AST_state& state)
{
    compileAssignTernary(tok, state);
    while (tok) {
        if (tok->str() == MatchCompiler::makeConstString(",")) {
            if (match147(tok))
                tok = tok->next();
            else
                compileBinOp(tok, state, compileAssignTernary);
        } else if (tok->str() == MatchCompiler::makeConstString(";") && state.functionCallEndPar && tok->index() < state.functionCallEndPar->index()) {
            compileBinOp(tok, state, compileAssignTernary);
        } else break;
    }
}

static void compileExpression(Token *&tok, AST_state& state)
{
    if (state.depth > AST_MAX_DEPTH)
        throw InternalError(tok, "maximum AST depth exceeded", InternalError::AST); // ticket #5592
    if (tok)
        compileComma(tok, state);
}

const Token* isLambdaCaptureList(const Token * tok)
{
    // a lambda expression '[x](y){}' is compiled as:
    // [
    // `-(  <<-- optional
    //   `-{
    // see compilePrecedence2
    if (!match52(tok))
        return nullptr;
    if (!match148(tok->link()))
        return nullptr;
    if (match39(tok->astOperand1()) && tok->astOperand1() == tok->link()->next())
        return tok->astOperand1();
    if (!tok->astOperand1() || tok->astOperand1()->str() != MatchCompiler::makeConstString("("))
        return nullptr;
    const Token * params = tok->astOperand1();
    if (!match39(params->astOperand1()))
        return nullptr;
    return params->astOperand1();
}

const Token* findLambdaEndTokenWithoutAST(const Token* tok) {
    if (!(match52(tok) && tok->link()))
        return nullptr;
    tok = tok->link()->next();
    if (match5(tok) && tok->link())
        tok = tok->link()->next();
    if (match149(tok))
        tok = tok->next();
    if (match150(tok)) { // trailing return type
        tok = tok->next();
        while (match151(tok)) {
            if (tok->link())
                tok = tok->link()->next();
            else
                tok = tok->next();
        }
    }
    if (!(match39(tok) && tok->link()))
        return nullptr;
    return tok->link()->next();
}

static Token * createAstAtToken(Token *tok);

// Compile inner expressions inside inner ({..}) and lambda bodies
static void createAstAtTokenInner(Token * const tok1, const Token *endToken, bool cpp)
{
    for (Token* tok = tok1; precedes(tok, endToken); tok = tok ? tok->next() : nullptr) {
        if (tok->str() == MatchCompiler::makeConstString("{") && !iscpp11init(tok)) {
            const Token * const endToken2 = tok->link();
            bool hasAst = false;
            for (const Token *inner = tok->next(); inner != endToken2; inner = inner->next()) {
                if (inner->astOperand1()) {
                    hasAst = true;
                    break;
                }
                if (tok->isConstOp())
                    break;
                if (inner->str() == MatchCompiler::makeConstString("{"))
                    inner = inner->link();
            }
            if (!hasAst) {
                for (; tok && tok != endToken && tok != endToken2; tok = tok ? tok->next() : nullptr)
                    tok = createAstAtToken(tok);
            }
        } else if (cpp && tok->str() == MatchCompiler::makeConstString("[")) {
            if (isLambdaCaptureList(tok)) {
                tok = tok->astOperand1();
                if (tok->str() == MatchCompiler::makeConstString("("))
                    tok = tok->astOperand1();
                const Token * const endToken2 = tok->link();
                tok = tok->next();
                for (; tok && tok != endToken && tok != endToken2; tok = tok ? tok->next() : nullptr)
                    tok = createAstAtToken(tok);
            }
        }
        else if (match152(tok)) {
            bool hasAst = false;
            for (const Token* tok2 = tok->linkAt(3); tok2 != tok; tok2 = tok2->previous()) {
                if (tok2->astParent() || tok2->astOperand1() || tok2->astOperand2()) {
                    hasAst = true;
                    break;
                }
            }
            if (!hasAst) {
                Token *const startTok = tok = tok->tokAt(4);
                const Token* const endtok = startTok->linkAt(-1);
                AST_state state(cpp);
                compileExpression(tok, state);
                createAstAtTokenInner(startTok, endtok, cpp);
            }
        }
    }
}

static Token * findAstTop(Token *tok1, const Token *tok2)
{
    for (Token *tok = tok1; tok && (tok != tok2); tok = tok->next()) {
        if (tok->astParent() || tok->astOperand1() || tok->astOperand2()) {
            while (tok->astParent() && tok->astParent()->index() >= tok1->index() && tok->astParent()->index() <= tok2->index())
                tok = tok->astParent();
            return tok;
        }
        if (match114(tok))
            tok = tok->link();
    }
    for (Token *tok = tok1; tok && (tok != tok2); tok = tok->next()) {
        if (tok->isName() || tok->isNumber())
            return tok;
        if (match114(tok))
            tok = tok->link();
    }
    return nullptr;
}

static Token *skipMethodDeclEnding(Token *tok)
{
    if (tok->str() != MatchCompiler::makeConstString(")"))
        tok = tok->previous();
    if (!tok || tok->str() != MatchCompiler::makeConstString(")"))
        return nullptr;
    Token *const tok2 = const_cast<Token*>(TokenList::isFunctionHead(tok, ";{"));
    if (tok2 && tok->next() != tok2)
        return tok2;
    return nullptr;
}

static Token * createAstAtToken(Token *tok)
{
    const bool cpp = tok->isCpp();
    // skip function pointer declaration
    if (match153(tok) && !match154(tok)) {
        Token* tok2 = tok->tokAt(2);
        // skip type tokens and qualifiers etc
        while (match155(tok2))
            tok2 = tok2->next();
        if (match156(tok2))
            return tok2;
    }
    if (Token *const endTok = skipMethodDeclEnding(tok)) {
        Token *tok2 = tok;
        do {
            tok2 = tok2->next();
            tok2->setCpp11init(false);
            if (match157(tok2)) {
                AST_state state(cpp);
                Token *tok3 = tok2->tokAt(2);
                compileExpression(tok3, state);
                tok2 = tok2->linkAt(1);
            }
        } while (tok2 != endTok && !precedes(endTok, tok2));
        return endTok;
    }
    if (match101(tok) && !match158(tok)) {
        bool isStandardTypeOrQualifier = false;
        Token* type = tok;
        while (match159(type)) {
            if (type->isName() && (type->isStandardType() || match160(type)))
                isStandardTypeOrQualifier = true;
            if (type->str() == MatchCompiler::makeConstString("<")) {
                if (type->link())
                    type = type->link();
                else
                    break;
            }
            type = type->next();
        }
        if (isStandardTypeOrQualifier && match156(type))
            return type;
        if (match161(type) &&
            match162(type->link()->previous()) &&
            match163(type->link()->linkAt(1)))
            return type->link()->linkAt(1)->next();
    }

    if (match164(tok)) {
        if (cpp && match165(tok)) {
            Token *decl = findmatch166(tok) ;
            if (match167(decl->link())) {
                AST_state state1(cpp);
                while (decl->str() != MatchCompiler::makeConstString("]")) {
                    if (match168(decl)) {
                        state1.op.push(decl);
                    } else if (decl->str() == MatchCompiler::makeConstString(",")) {
                        if (!state1.op.empty()) {
                            decl->astOperand1(state1.op.top());
                            state1.op.pop();
                        }
                        if (!state1.op.empty()) {
                            state1.op.top()->astOperand2(decl);
                            state1.op.pop();
                        }
                        state1.op.push(decl);
                    }
                    decl = decl->next();
                }
                if (state1.op.size() > 1) {
                    Token *lastName = state1.op.top();
                    state1.op.pop();
                    state1.op.top()->astOperand2(lastName);
                }
                decl = decl->next();

                Token *colon = decl;
                compileExpression(decl, state1);

                tok->next()->astOperand1(tok);
                tok->next()->astOperand2(colon);

                return decl;
            }
        }

        std::vector<Token*> inner;
        Token* tok2 = skipDecl(tok->tokAt(2), &inner);
        for (Token* tok3 : inner) {
            AST_state state1(cpp);
            compileExpression(tok3, state1);
        }
        Token *init1 = nullptr;
        Token * const endPar = tok->linkAt(1);
        if (tok2 == tok->tokAt(2) && match169(tok2)) {
            init1 = tok2;
            AST_state state1(cpp);
            compileExpression(tok2, state1);
            if (match170(init1)) {
                for (Token *tok3 = init1; tok3 && tok3 != tok3->link(); tok3 = tok3->next()) {
                    if (tok3->astParent()) {
                        while (tok3->astParent())
                            tok3 = tok3->astParent();
                        init1 = tok3;
                        break;
                    }
                    if (!match171(tok3))
                        init1 = tok3;
                }
            }
        } else {
            while (tok2 && tok2 != endPar && tok2->str() != MatchCompiler::makeConstString(";")) {
                if (tok2->str() == MatchCompiler::makeConstString("<") && tok2->link()) {
                    tok2 = tok2->link();
                } else if (match172(tok2) || match173(tok2->previous())) {
                    init1 = tok2;
                    AST_state state1(cpp);
                    compileExpression(tok2, state1);
                    if (match174(tok2))
                        break;
                    init1 = nullptr;
                }
                if (!tok2) // #7109 invalid code
                    return nullptr;
                tok2 = tok2->next();
            }
        }
        if (!tok2 || tok2->str() != MatchCompiler::makeConstString(";")) {
            if (tok2 == endPar && init1) {
                createAstAtTokenInner(init1->next(), endPar, cpp);
                tok->next()->astOperand2(init1);
                tok->next()->astOperand1(tok);
            }
            return tok2;
        }

        Token * const init = init1 ? init1 : tok2;

        Token * const semicolon1 = tok2;
        tok2 = tok2->next();
        AST_state state2(cpp);
        compileExpression(tok2, state2);

        Token * const semicolon2 = tok2;
        if (!semicolon2)
            return nullptr; // invalid code #7235

        if (semicolon2->str() == MatchCompiler::makeConstString(";")) {
            tok2 = tok2->next();
            AST_state state3(cpp);
            if (match114(tok2)) {
                state3.op.push(tok2->next());
                tok2 = tok2->link()->next();
            }
            compileExpression(tok2, state3);

            tok2 = findAstTop(semicolon1->next(), semicolon2);
            if (tok2)
                semicolon2->astOperand1(tok2);
            tok2 = findAstTop(semicolon2->next(), endPar);
            if (tok2)
                semicolon2->astOperand2(tok2);
            else if (!state3.op.empty())
                semicolon2->astOperand2(state3.op.top());
            semicolon1->astOperand2(semicolon2);
        } else {
            if (!cpp || state2.op.empty() || !match68(state2.op.top()))
                throw InternalError(tok, "syntax error", InternalError::SYNTAX);

            semicolon1->astOperand2(state2.op.top());
        }

        if (init != semicolon1)
            semicolon1->astOperand1(init->astTop());
        tok->next()->astOperand1(tok);
        tok->next()->astOperand2(semicolon1);

        createAstAtTokenInner(endPar->link(), endPar, cpp);

        return endPar;
    }

    if (match114(tok))
        return tok;

    if (match175(tok) && tok->linkAt(1) && !match176(tok->linkAt(1)))
        return tok->linkAt(1);

    if (cpp && !tok->isKeyword() && match177(tok)) {
        Token *tok2 = tok;
        while (true) {
            if (match178(tok2))
                tok2 = tok2->tokAt(2);
            else if (match53(tok2) && tok2->linkAt(1))
                tok2 = tok2->linkAt(1);
            else
                break;
        }
        if (match179(tok2) && tok2->next()->varId() && iscpp11init(tok2->tokAt(2))) {
            Token *const tok1 = tok = tok2->next();
            AST_state state(cpp);
            compileExpression(tok, state);
            createAstAtTokenInner(tok1->next(), tok1->linkAt(1), cpp);
            return tok;
        }
    }

    if (match180(tok) && !match181(tok)) {
        int typecount = 0;
        Token *typetok = tok;
        while (match182(typetok)) {
            if (typetok->isName() && !match121(typetok->previous()))
                typecount++;
            if (typetok->str() == MatchCompiler::makeConstString("<")) {
                if (Token* closing = typetok->findClosingBracket()) {
                    typetok = closing->next();
                    continue;
                }
                break;
            }
            typetok = typetok->next();
        }
        if (match183(typetok) && typetok->varId())
            tok = typetok;

        // Do not create AST for function declaration
        if (typetok &&
            typecount >= 2 &&
            !match184(tok) &&
            match185(typetok->previous()) &&
            typetok->previous()->varId() == 0 &&
            !typetok->previous()->isKeyword() &&
            (skipMethodDeclEnding(typetok->link()) || match186(typetok->link())))
            return typetok;
    }

    if (match14(tok) ||
        (cpp && tok->str() == MatchCompiler::makeConstString("throw")) ||
        !tok->previous() ||
        match187(tok) ||
        (cpp && match188(tok) && iscpp11init(tok->next())) ||
        match189(tok->previous()) ||
        match190(tok->previous()) ||
        match191(tok->previous()) ||
        (cpp && match192(tok->previous()))) {
        if (cpp && (match193(tok->tokAt(-2)) || match194(tok->tokAt(-3))))
            tok = tok->previous();

        Token * const tok1 = tok;
        AST_state state(cpp);
        if (match89(tok))
            state.functionCallEndPar = tok->linkAt(1);
        if (match121(tok->tokAt(-1)) && (!tok->tokAt(-2) || !tok->tokAt(-2)->isName()))
            tok = tok->tokAt(-1);
        compileExpression(tok, state);
        Token * const endToken = tok;
        if (endToken == tok1 || !endToken)
            return tok1;

        createAstAtTokenInner(tok1->next(), endToken, cpp);

        return endToken->previous();
    }

    if (cpp && tok->str() == MatchCompiler::makeConstString("{") && iscpp11init(tok)) {
        Token * const tok1 = tok;
        AST_state state(cpp);
        compileExpression(tok, state);
        Token* const endToken = tok;
        if (endToken == tok1 || !endToken)
            return tok1;

        createAstAtTokenInner(tok1->next(), endToken, cpp);
        return endToken->previous();
    }

    return tok;
}

void TokenList::createAst() const
{
    for (Token *tok = mTokensFrontBack->front; tok; tok = tok ? tok->next() : nullptr) {
        Token* const nextTok = createAstAtToken(tok);
        if (precedes(nextTok, tok))
            throw InternalError(tok, "Syntax Error: Infinite loop when creating AST.", InternalError::AST);
        tok = nextTok;
    }
}

namespace {
    struct OnException {
        std::function<void()> f;

        ~OnException() {
#ifndef _MSC_VER
            if (std::uncaught_exception())
                f();
#endif
        }
    };
}

void TokenList::validateAst(bool print) const
{
    OnException oe{[&] {
            if (print)
                mTokensFrontBack->front->printOut(std::cout);
        }};
    // Check for some known issues in AST to avoid crash/hang later on
    std::set<const Token*> safeAstTokens;    // list of "safe" AST tokens without endless recursion
    for (const Token *tok = mTokensFrontBack->front; tok; tok = tok->next()) {
        // Syntax error if binary operator only has 1 operand
        if ((tok->isAssignmentOp() || tok->isComparisonOp() || match195(tok)) && tok->astOperand1() && !tok->astOperand2())
            throw InternalError(tok, "Syntax Error: AST broken, binary operator has only one operand.", InternalError::AST);

        // Syntax error if we encounter "?" with operand2 that is not ":"
        if (tok->str() == MatchCompiler::makeConstString("?")) {
            if (!tok->astOperand1() || !tok->astOperand2())
                throw InternalError(tok, "AST broken, ternary operator missing operand(s)", InternalError::AST);
            if (tok->astOperand2()->str() != MatchCompiler::makeConstString(":"))
                throw InternalError(tok, "Syntax Error: AST broken, ternary operator lacks ':'.", InternalError::AST);
        }

        // Check for endless recursion
        const Token* parent = tok->astParent();
        if (parent) {
            std::set<const Token*> astTokens;    // list of ancestors
            astTokens.insert(tok);
            do {
                if (safeAstTokens.find(parent) != safeAstTokens.end())
                    break;
                if (astTokens.find(parent) != astTokens.end())
                    throw InternalError(tok, "AST broken: endless recursion from '" + tok->str() + "'", InternalError::AST);
                astTokens.insert(parent);
            } while ((parent = parent->astParent()) != nullptr);
            safeAstTokens.insert(astTokens.cbegin(), astTokens.cend());
        } else if (tok->str() == MatchCompiler::makeConstString(";")) {
            safeAstTokens.clear();
        } else {
            safeAstTokens.insert(tok);
        }

        // Don't check templates
        if (tok->str() == MatchCompiler::makeConstString("<") && tok->link()) {
            tok = tok->link();
            continue;
        }
        if (tok->isCast()) {
            if (!tok->astOperand2() && precedes(tok->astOperand1(), tok))
                throw InternalError(tok, "AST broken: '" + tok->str() + "' has improper operand.", InternalError::AST);
            if (tok->astOperand1() && tok->link()) { // skip casts (not part of the AST)
                tok = tok->link();
                continue;
            }
        }

        if (findLambdaEndToken(tok)) { // skip lambda captures
            tok = tok->link();
            continue;
        }

        // Check binary operators
        if (match196(tok)) {
            // Skip pure virtual functions
            if (match197(tok->previous()))
                continue;
            // Skip operator definitions
            if (match198(tok->previous()))
                continue;
            // Skip incomplete code
            if (!tok->astOperand1() && !tok->astOperand2() && !tok->astParent())
                continue;
            // Skip lambda assignment and/or initializer
            if (match199(tok))
                continue;
            // FIXME: Workaround broken AST assignment in type aliases
            if (match200(tok->previous()))
                continue;
            if (!tok->astOperand1() || !tok->astOperand2())
                throw InternalError(tok, "Syntax Error: AST broken, binary operator '" + tok->str() + "' doesn't have two operands.", InternalError::AST);
        }

        if (match201(tok) && !tok->astOperand1()) {
            throw InternalError(tok, "Syntax Error: AST broken, operator '" + tok->str() + "' doesn't have an operand.", InternalError::AST);
        }

        // Check control blocks and asserts
        if (match202(tok->previous())) {
            if (!tok->astOperand1() || !tok->astOperand2())
                throw InternalError(tok,
                                    "Syntax Error: AST broken, '" + tok->strAt(-1) +
                                    "' doesn't have two operands.",
                                    InternalError::AST);
        }
        if (tok->str() == MatchCompiler::makeConstString("case") && !tok->astOperand1()) {
            throw InternalError(tok,
                                "Syntax Error: AST broken, 'case' doesn't have an operand.",
                                InternalError::AST);
        }

        // Check member access
        if (match203(tok)) {
            if (!tok->astParent()) {
                throw InternalError(
                          tok, "Syntax Error: AST broken, '" + tok->str() + "' doesn't have a parent.", InternalError::AST);
            }
            if (!tok->next()->astOperand1() || !tok->next()->astOperand2()) {
                const std::string& op =
                    tok->next()->originalName().empty() ? tok->strAt(1) : tok->next()->originalName();
                throw InternalError(
                          tok, "Syntax Error: AST broken, '" + op + "' doesn't have two operands.", InternalError::AST);
            }
        }
    }
}

std::string TokenList::getOrigFile(const Token *tok) const
{
    return mOrigFiles.at(tok->fileIndex());
}

const std::string& TokenList::file(const Token *tok) const
{
    return mFiles.at(tok->fileIndex());
}

std::string TokenList::fileLine(const Token *tok) const
{
    return ErrorMessage::FileLocation(tok, this).stringify();
}

bool TokenList::validateToken(const Token* tok) const
{
    if (!tok)
        return true;
    for (const Token *t = mTokensFrontBack->front; t; t = t->next()) {
        if (tok==t)
            return true;
    }
    return false;
}

void TokenList::simplifyPlatformTypes()
{
    const bool isCPP11 = isCPP() && (mSettings.standards.cpp >= Standards::CPP11);

    enum : std::uint8_t { isLongLong, isLong, isInt } type;

    /** @todo This assumes a flat address space. Not true for segmented address space (FAR *). */

    if (mSettings.platform.sizeof_size_t == mSettings.platform.sizeof_long)
        type = isLong;
    else if (mSettings.platform.sizeof_size_t == mSettings.platform.sizeof_long_long)
        type = isLongLong;
    else if (mSettings.platform.sizeof_size_t == mSettings.platform.sizeof_int)
        type = isInt;
    else
        return;

    for (Token *tok = front(); tok; tok = tok->next()) {
        // pre-check to reduce unneeded match calls
        if (!match204(tok))
            continue;
        bool isUnsigned;
        if (match205(tok)) {
            if (isCPP11 && tok->strAt(-1) == MatchCompiler::makeConstString("using") && tok->strAt(1) == MatchCompiler::makeConstString("="))
                continue;
            isUnsigned = true;
        } else if (match206(tok)) {
            if (isCPP11 && tok->strAt(-1) == MatchCompiler::makeConstString("using") && tok->strAt(1) == MatchCompiler::makeConstString("="))
                continue;
            isUnsigned = false;
        } else
            continue;

        bool inStd = false;
        if (tok->str() == MatchCompiler::makeConstString("::")) {
            tok->deleteThis();
        } else if (tok->str() == MatchCompiler::makeConstString("std")) {
            if (tok->strAt(1) != MatchCompiler::makeConstString("::"))
                continue;
            inStd = true;
            tok->deleteNext();
            tok->deleteThis();
        }

        if (inStd)
            tok->originalName("std::" + tok->str());
        else
            tok->originalName(tok->str());
        if (isUnsigned)
            tok->isUnsigned(true);

        switch (type) {
        case isLongLong:
            tok->isLong(true);
            tok->str("long");
            break;
        case isLong:
            tok->str("long");
            break;
        case isInt:
            tok->str("int");
            break;
        }
    }

    const std::string platform_type(mSettings.platform.toString());

    for (Token *tok = front(); tok; tok = tok->next()) {
        if (tok->tokType() != Token::eType && tok->tokType() != Token::eName)
            continue;

        const Library::PlatformType * const platformtype = mSettings.library.platform_type(tok->str(), platform_type);

        if (platformtype) {
            // check for namespace
            if (tok->strAt(-1) == MatchCompiler::makeConstString("::")) {
                const Token * tok1 = tok->tokAt(-2);
                // skip when non-global namespace defined
                if (tok1 && tok1->tokType() == Token::eName)
                    continue;
                tok = tok->previous();
                tok->deleteThis();
            }
            tok->originalName(tok->str());
            const bool isFunctionalPtrCast = (platformtype->mConstPtr || platformtype->mPointer || platformtype->mPtrPtr) &&
                                             match207(tok) && !match25(tok->linkAt(1));
            Token* start = isFunctionalPtrCast ? tok->tokAt(1) : nullptr;
            Token* end = isFunctionalPtrCast ? tok->linkAt(1) : nullptr;
            Token *typeToken;
            if (platformtype->mConstPtr) {
                tok->str("const");
                tok->isSimplifiedTypedef(true);
                tok->insertToken("*")->isSimplifiedTypedef(true);
                tok->insertToken(platformtype->mType)->isSimplifiedTypedef(true);
                typeToken = tok;
            } else if (platformtype->mPointer) {
                tok->str(platformtype->mType);
                tok->isSimplifiedTypedef(true);
                typeToken = tok;
                tok->insertToken("*")->isSimplifiedTypedef(true);
            } else if (platformtype->mPtrPtr) {
                tok->str(platformtype->mType);
                tok->isSimplifiedTypedef(true);
                typeToken = tok;
                tok->insertToken("*")->isSimplifiedTypedef(true);
                tok->insertToken("*")->isSimplifiedTypedef(true);
            } else {
                tok->str(platformtype->mType);
                tok->isSimplifiedTypedef(true);
                typeToken = tok;
            }
            if (platformtype->mSigned)
                typeToken->isSigned(true);
            if (platformtype->mUnsigned)
                typeToken->isUnsigned(true);
            if (platformtype->mLong)
                typeToken->isLong(true);

            if (isFunctionalPtrCast) {
                start->str("(");
                end->str(")");
                if (end == start->tokAt(1))
                    end->insertTokenBefore("0");
                end = start->insertTokenBefore(")");
                start = tok->insertTokenBefore("(");
                start->isSimplifiedTypedef(true);
                Token::createMutualLinks(start, end);
            }
        }
    }
}

void TokenList::simplifyStdType()
{
    auto isVarDeclC = [](const Token* tok) -> bool {
        if (!match208(tok))
            return false;
        tok = tok->link()->previous();
        while (match79(tok)) {
            if (match209(tok))
                return true;
            tok = tok->previous();
        }
        return false;
    };

    for (Token *tok = front(); tok; tok = tok->next()) {

        if (isC() && match210(tok) && (!tok->previous() || match211(tok->previous()))) {
            if (match212(tok->next()))
                continue;
            if (isVarDeclC(tok->previous()))
                continue;

            tok->insertToken("int");
            tok->next()->isImplicitInt(true);
            continue;
        }

        if (match213(tok) || (isC() && (mSettings.standards.c >= Standards::C99) && match214(tok))) {
            bool isFloat= false;
            bool isSigned = false;
            bool isUnsigned = false;
            bool isComplex = false;
            int countLong = 0;
            Token* typeSpec = nullptr;

            Token* tok2 = tok;
            for (; tok2->next(); tok2 = tok2->next()) {
                if (tok2->str() == MatchCompiler::makeConstString("long")) {
                    countLong++;
                    if (!isFloat)
                        typeSpec = tok2;
                } else if (tok2->str() == MatchCompiler::makeConstString("short")) {
                    typeSpec = tok2;
                } else if (tok2->str() == MatchCompiler::makeConstString("unsigned"))
                    isUnsigned = true;
                else if (tok2->str() == MatchCompiler::makeConstString("signed"))
                    isSigned = true;
                else if (match215(tok2)) {
                    isFloat = true;
                    typeSpec = tok2;
                } else if (isC() && (mSettings.standards.c >= Standards::C99) && match214(tok2))
                    isComplex = !isFloat || tok2->str() == MatchCompiler::makeConstString("_Complex") || match216(tok2->next()); // Ensure that "complex" is not the variables name
                else if (match217(tok2)) {
                    if (!typeSpec)
                        typeSpec = tok2;
                } else
                    break;
            }

            if (!typeSpec) { // unsigned i; or similar declaration
                if (!isComplex) { // Ensure that "complex" is not the variables name
                    tok->str("int");
                    tok->isSigned(isSigned);
                    tok->isUnsigned(isUnsigned);
                    tok->isImplicitInt(true);
                }
            } else {
                typeSpec->isLong(typeSpec->isLong() || (isFloat && countLong == 1) || countLong > 1);
                typeSpec->isComplex(typeSpec->isComplex() || (isFloat && isComplex));
                typeSpec->isSigned(typeSpec->isSigned() || isSigned);
                typeSpec->isUnsigned(typeSpec->isUnsigned() || isUnsigned);

                // Remove specifiers
                const Token* tok3 = tok->previous();
                tok2 = tok2->previous();
                while (tok3 != tok2) {
                    if (tok2 != typeSpec &&
                        (isComplex || !match214(tok2)))  // Ensure that "complex" is not the variables name
                        tok2->deleteThis();
                    tok2 = tok2->previous();
                }
            }
        }
    }
}

bool TokenList::isKeyword(const std::string &str) const
{
    if (isCPP()) {
        const auto &cpp_keywords = Keywords::getAll(mSettings.standards.cpp);
        const bool b = cpp_keywords.find(str) != cpp_keywords.end();
        if (b) {
            // TODO: integrate into keywords?
            // types and literals are not handled as keywords
            static const std::unordered_set<std::string> cpp_types = {"bool", "false", "true"};
            if (cpp_types.find(str) != cpp_types.end())
                return false;
        }
        return b;
    }

    const auto &c_keywords = Keywords::getAll(mSettings.standards.c);
    const bool b = c_keywords.find(str) != c_keywords.end();
    if (b) {
        // TODO: integrate into Keywords?
        // types are not handled as keywords
        static const std::unordered_set<std::string> c_types = {"char", "double", "float", "int", "long", "short"};
        if (c_types.find(str) != c_types.end())
            return false;
    }
    return b;
}

bool TokenList::isC() const
{
    return mLang == Standards::Language::C;
}

bool TokenList::isCPP() const
{
    return mLang == Standards::Language::CPP;
}

const Token * TokenList::isFunctionHead(const Token *tok, const std::string &endsWith)
{
    if (!tok)
        return nullptr;
    if (tok->str() == MatchCompiler::makeConstString("("))
        tok = tok->link();
    if (tok->str() != MatchCompiler::makeConstString(")"))
        return nullptr;
    if (!tok->isCpp() && !match218(tok->link()->previous()))
        return nullptr;
    if (match219(tok)) {
        tok = tok->next();
        while (tok && tok->str() == MatchCompiler::makeConstString("[") && tok->link()) {
            if (endsWith.find(tok->str()) != std::string::npos)
                return tok;
            tok = tok->link()->next();
        }
        return (tok && endsWith.find(tok->str()) != std::string::npos) ? tok : nullptr;
    }
    if (tok->isCpp() && tok->str() == MatchCompiler::makeConstString(")")) {
        tok = tok->next();
        while (match220(tok) ||
               (match221(tok) && tok->isUpperCaseName()))
            tok = tok->next();
        if (tok && tok->str() == MatchCompiler::makeConstString(")"))
            tok = tok->next();
        while (tok && tok->str() == MatchCompiler::makeConstString("["))
            tok = tok->link()->next();
        if (match222(tok))
            tok = tok->linkAt(1)->next();
        if (match89(tok) && tok->isUpperCaseName())
            tok = tok->linkAt(1)->next();
        if (tok && tok->originalName() == MatchCompiler::makeConstString("->")) { // trailing return type
            for (tok = tok->next(); tok && !match223(tok); tok = tok->next())
                if (tok->link() && match224(tok))
                    tok = tok->link();
        }
        while (match225(tok) ||
               (match221(tok) && tok->isUpperCaseName()))
            tok = tok->next();
        if (match226(tok))
            tok = tok->tokAt(2);
        if (match227(tok)) {
            for (tok = tok->next(); tok && !match228(tok); tok = tok->next()) {
                if (tok->link() && match224(tok))
                    tok = tok->link();
                if (match229(tok))
                    tok = tok->linkAt(1);
            }
        }
        if (tok && tok->str() == MatchCompiler::makeConstString(":") && !match230(tok->next()))
            return nullptr;
        return (tok && endsWith.find(tok->str()) != std::string::npos) ? tok : nullptr;
    }
    return nullptr;
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
