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
// pattern: :: %name%
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %name% ::
MAYBE_UNUSED static inline bool match2(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: %name% <
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: >|>> ::
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: {
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ; }
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: } }
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: do|try|else {
MAYBE_UNUSED static inline bool match8(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do")) || (tok->str() == MatchCompiler::makeConstString("try")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("else"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: )|] {
MAYBE_UNUSED static inline bool match9(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: enum class| %name%| {|:
MAYBE_UNUSED static inline bool match10(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("class"))))
        tok = tok->next();
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: [{:]
MAYBE_UNUSED static inline bool match11(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{:", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name%|::
MAYBE_UNUSED static inline bool match12(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: [
MAYBE_UNUSED static inline bool match13(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: %name% :: %name%
MAYBE_UNUSED static inline bool match14(const Token* tok) {
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
// pattern: class|struct|union|namespace ::| %name% final| {|:|::|<
MAYBE_UNUSED static inline bool match15(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || (tok->str() == MatchCompiler::makeConstString("namespace"))))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("final"))))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: new|friend|const|enum|typedef|mutable|volatile|using|)|(|<
MAYBE_UNUSED static inline bool match16(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("new")) || (tok->str() == MatchCompiler::makeConstString("friend")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef")) || (tok->str() == MatchCompiler::makeConstString("mutable")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || (tok->str() == MatchCompiler::makeConstString("using")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: struct|union|enum %name% {
MAYBE_UNUSED static inline bool match17(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: final
MAYBE_UNUSED static inline bool match18(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("final")))
        return false;
    return true;
}
// pattern: {|:
MAYBE_UNUSED static inline bool match19(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: = {
MAYBE_UNUSED static inline bool match20(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } ;
MAYBE_UNUSED static inline bool match21(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: (|{
MAYBE_UNUSED static inline bool match22(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: *|&|>
MAYBE_UNUSED static inline bool match23(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: %name% (
MAYBE_UNUSED static inline bool match24(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %name% [|=
MAYBE_UNUSED static inline bool match25(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: ;
MAYBE_UNUSED static inline bool match26(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: template|> class|struct
MAYBE_UNUSED static inline bool match27(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("template")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    return true;
}
// pattern: class|struct|union
MAYBE_UNUSED static inline bool match28(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    return true;
}
// pattern: (
MAYBE_UNUSED static inline bool match29(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) ;
MAYBE_UNUSED static inline bool match30(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: namespace %name% %type% (
MAYBE_UNUSED static inline bool match31(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) {
MAYBE_UNUSED static inline bool match32(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: class|struct|union %name% ;
MAYBE_UNUSED static inline bool match33(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: using namespace ::| %type% ;|::
MAYBE_UNUSED static inline bool match34(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: %type% ::
MAYBE_UNUSED static inline bool match35(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: using %name% =
MAYBE_UNUSED static inline bool match36(const Token* tok) {
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
// pattern: decltype (
MAYBE_UNUSED static inline bool match37(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("decltype")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: struct|union {
MAYBE_UNUSED static inline bool match38(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } *|&| %name% ;|[|=
MAYBE_UNUSED static inline bool match39(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: namespace {
MAYBE_UNUSED static inline bool match40(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: enum class| %name% ;
MAYBE_UNUSED static inline bool match41(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("class"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: enum class| %name% : %name% ;
MAYBE_UNUSED static inline bool match42(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("class"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: public|protected|private %name% :
MAYBE_UNUSED static inline bool match43(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("protected")) || (tok->str() == MatchCompiler::makeConstString("private"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: (|<
MAYBE_UNUSED static inline bool match44(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: %name%|> {
MAYBE_UNUSED static inline bool match45(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } ,|{
MAYBE_UNUSED static inline bool match46(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: friend class|struct| ::| %any% ;|::
MAYBE_UNUSED static inline bool match47(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("friend")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: default|delete
MAYBE_UNUSED static inline bool match48(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("default")) || (tok->str() == MatchCompiler::makeConstString("delete"))))
        return false;
    return true;
}
// pattern: else|try|do {
MAYBE_UNUSED static inline bool match49(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("else")) || (tok->str() == MatchCompiler::makeConstString("try")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: if|for|while|catch|switch (
MAYBE_UNUSED static inline bool match50(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || (tok->str() == MatchCompiler::makeConstString("catch")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("switch"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %var% {
MAYBE_UNUSED static inline bool match51(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: extern %type%
MAYBE_UNUSED static inline bool match52(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: %name%|*|&
MAYBE_UNUSED static inline bool match53(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: static|const|struct|union|enum
MAYBE_UNUSED static inline bool match54(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    return true;
}
// pattern: >
MAYBE_UNUSED static inline bool match55(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    return true;
}
// pattern: %var% .|[
MAYBE_UNUSED static inline bool match56(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: . %var%
MAYBE_UNUSED static inline bool match57(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    return true;
}
// pattern: %name% [{}(,)>;:]]
MAYBE_UNUSED static inline bool match58(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("{}(,)>;:]", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name% {|(
MAYBE_UNUSED static inline bool match59(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: <
MAYBE_UNUSED static inline bool match60(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: .
MAYBE_UNUSED static inline bool match61(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: *
MAYBE_UNUSED static inline bool match62(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: ) . %name% !!(
MAYBE_UNUSED static inline bool match63(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    return true;
}
// pattern: ) [
MAYBE_UNUSED static inline bool match64(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] . %name% !!(
MAYBE_UNUSED static inline bool match65(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    return true;
}
// pattern: <
template<class T> MAYBE_UNUSED static inline T * findmatch66(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: catch|typeid (
MAYBE_UNUSED static inline bool match67(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("catch")) || (tok->str() == MatchCompiler::makeConstString("typeid"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: static_cast|dynamic_cast|const_cast|reinterpret_cast
MAYBE_UNUSED static inline bool match68(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("static_cast")) || (tok->str() == MatchCompiler::makeConstString("dynamic_cast")) || (tok->str() == MatchCompiler::makeConstString("const_cast")) || (tok->str() == MatchCompiler::makeConstString("reinterpret_cast"))))
        return false;
    return true;
}
// pattern: ;
template<class T> MAYBE_UNUSED static inline T * findmatch69(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: ::|.|(|{|:|%var%
MAYBE_UNUSED static inline bool match70(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || (tok->str() == MatchCompiler::makeConstString(".")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->varId() != 0)))
        return false;
    return true;
}
// pattern: &|&&|* *| *| )|,|%var%|const
MAYBE_UNUSED static inline bool match71(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->varId() != 0) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        return false;
    return true;
}
// pattern: %type% ,
MAYBE_UNUSED static inline bool match72(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: , %type%
MAYBE_UNUSED static inline bool match73(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: goto
MAYBE_UNUSED static inline bool match74(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("goto")))
        return false;
    return true;
}
// pattern: ::
MAYBE_UNUSED static inline bool match75(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: %name%
MAYBE_UNUSED static inline bool match76(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: ::|[|{
MAYBE_UNUSED static inline bool match77(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: new
MAYBE_UNUSED static inline bool match78(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    return true;
}
// pattern: [])]
MAYBE_UNUSED static inline bool match79(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("])", tok->str()[0]))
        return false;
    return true;
}
// pattern: return
template<class T> MAYBE_UNUSED static inline T * findmatch80(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: (|.|[|::|?|:|++|--|%cop%|%assign%
MAYBE_UNUSED static inline bool match81(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString(".")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--")) || tok->isConstOp() || tok->isAssignmentOp()))
        return false;
    return true;
}
// pattern: *|&|&&
MAYBE_UNUSED static inline bool match82(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: .|::
MAYBE_UNUSED static inline bool match83(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: [{[]
MAYBE_UNUSED static inline bool match84(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{[", tok->str()[0]))
        return false;
    return true;
}
// pattern: { }
MAYBE_UNUSED static inline bool match85(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: ++|--
MAYBE_UNUSED static inline bool match86(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--"))))
        return false;
    return true;
}
// pattern: %or%|%oror%|+|*|&|&&|^|==|!=
MAYBE_UNUSED static inline bool match87(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("==")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("!="))))
        return false;
    return true;
}
// pattern: decltype|sizeof|typeof (
MAYBE_UNUSED static inline bool match88(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("decltype")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")) || (tok->str() == MatchCompiler::makeConstString("typeof"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %var% [
MAYBE_UNUSED static inline bool match89(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: . %name%
MAYBE_UNUSED static inline bool match90(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: [{,]
MAYBE_UNUSED static inline bool match91(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{,", tok->str()[0]))
        return false;
    return true;
}
// pattern: [<,]
MAYBE_UNUSED static inline bool match92(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("<,", tok->str()[0]))
        return false;
    return true;
}
// pattern: [,>]
MAYBE_UNUSED static inline bool match93(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",>", tok->str()[0]))
        return false;
    return true;
}
// pattern: ; %num% ;
MAYBE_UNUSED static inline bool match94(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: ) const
MAYBE_UNUSED static inline bool match95(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    return true;
}
// pattern: {|;|const|=
MAYBE_UNUSED static inline bool match96(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: {|;
template<class T> MAYBE_UNUSED static inline T * findmatch97(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: %name% ( !!*
MAYBE_UNUSED static inline bool match98(const Token* tok) {
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
// pattern: %name%|>|&|&&|*|::|~
MAYBE_UNUSED static inline bool match99(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~"))))
        return false;
    return true;
}
// pattern: const|noexcept|throw|override|final|volatile|&|&&
MAYBE_UNUSED static inline bool match100(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("noexcept")) || (tok->str() == MatchCompiler::makeConstString("throw")) || (tok->str() == MatchCompiler::makeConstString("override")) || (tok->str() == MatchCompiler::makeConstString("final")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: ;|{|=|override|final
MAYBE_UNUSED static inline bool match101(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || (tok->str() == MatchCompiler::makeConstString("override")) || (tok->str() == MatchCompiler::makeConstString("final"))))
        return false;
    return true;
}
// pattern: <|[|(
MAYBE_UNUSED static inline bool match102(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: {|}|;|public:|protected:|private:
MAYBE_UNUSED static inline bool match103(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";")) || (tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("private:"))))
        return false;
    return true;
}
// pattern: %type%|*|&|&&
MAYBE_UNUSED static inline bool match104(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: )
MAYBE_UNUSED static inline bool match105(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: const|static|extern|template|virtual|struct|class|enum|%name%
MAYBE_UNUSED static inline bool match106(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern")) || (tok->str() == MatchCompiler::makeConstString("template")) || (tok->str() == MatchCompiler::makeConstString("virtual")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || tok->isName()))
        return false;
    return true;
}
// pattern: >|{|}|;|public:|protected:|private:
MAYBE_UNUSED static inline bool match107(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";")) || (tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("private:"))))
        return false;
    return true;
}
// pattern: ;|{|=
MAYBE_UNUSED static inline bool match108(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: %name% ;|{
MAYBE_UNUSED static inline bool match109(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: : ::| %name% (|::|<|{
MAYBE_UNUSED static inline bool match110(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: &|&&| ;|{
MAYBE_UNUSED static inline bool match111(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: = delete|default ;
MAYBE_UNUSED static inline bool match112(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("delete")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("default"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: final|override
MAYBE_UNUSED static inline bool match113(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("final")) || (tok->str() == MatchCompiler::makeConstString("override"))))
        return false;
    return true;
}
// pattern: [;{}]
MAYBE_UNUSED static inline bool match114(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    return true;
}
// pattern: > (
MAYBE_UNUSED static inline bool match115(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) const| ;|{|=
MAYBE_UNUSED static inline bool match116(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: ) : ::| %name% (|::|<|{
MAYBE_UNUSED static inline bool match117(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: ) const| noexcept {|;|(
MAYBE_UNUSED static inline bool match118(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("noexcept")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: ;|}
MAYBE_UNUSED static inline bool match119(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: &
MAYBE_UNUSED static inline bool match120(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    return true;
}
// pattern: =
MAYBE_UNUSED static inline bool match121(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: return
MAYBE_UNUSED static inline bool match122(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")))
        return false;
    return true;
}
// pattern: ) =
MAYBE_UNUSED static inline bool match123(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: ) :
MAYBE_UNUSED static inline bool match124(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: [:,] %var% [({]
MAYBE_UNUSED static inline bool match125(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(":,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("({", tok->str()[0]))
        return false;
    return true;
}
// pattern: %type%|*|&
MAYBE_UNUSED static inline bool match126(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: const|struct|static
MAYBE_UNUSED static inline bool match127(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static"))))
        return false;
    return true;
}
// pattern: &&
MAYBE_UNUSED static inline bool match128(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")))
        return false;
    return true;
}
// pattern: =|{
MAYBE_UNUSED static inline bool match129(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: for (
MAYBE_UNUSED static inline bool match130(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: [;:,)={]
MAYBE_UNUSED static inline bool match131(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";:,)={", tok->str()[0]))
        return false;
    return true;
}
// pattern: (|[|<
MAYBE_UNUSED static inline bool match132(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: [={(]
MAYBE_UNUSED static inline bool match133(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("={(", tok->str()[0]))
        return false;
    return true;
}
// pattern: std :: atomic <
MAYBE_UNUSED static inline bool match134(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("std")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("atomic")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: %name% [
MAYBE_UNUSED static inline bool match135(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: * const| %name% )
MAYBE_UNUSED static inline bool match136(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: static|const|constexpr|volatile %any%
MAYBE_UNUSED static inline bool match137(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("constexpr")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    return true;
}
// pattern: const|volatile
MAYBE_UNUSED static inline bool match138(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        return false;
    return true;
}
// pattern: %type% :: %type%
MAYBE_UNUSED static inline bool match139(const Token* tok) {
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
// pattern: std ::
MAYBE_UNUSED static inline bool match140(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("std")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: ; %name% =
MAYBE_UNUSED static inline bool match141(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: float|double
MAYBE_UNUSED static inline bool match142(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("float")) || (tok->str() == MatchCompiler::makeConstString("double"))))
        return false;
    return true;
}
// pattern: decltype (
template<class T> MAYBE_UNUSED static inline T * findmatch143(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("decltype")))
        continue;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: ( * %name% )
MAYBE_UNUSED static inline bool match144(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: < %name% >
MAYBE_UNUSED static inline bool match145(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    return true;
}
// pattern: &|&&| .
MAYBE_UNUSED static inline bool match146(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: extern|virtual|static|friend|struct|union|enum
MAYBE_UNUSED static inline bool match147(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern")) || (tok->str() == MatchCompiler::makeConstString("virtual")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || (tok->str() == MatchCompiler::makeConstString("friend")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    return true;
}
// pattern: ( false )
MAYBE_UNUSED static inline bool match148(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBoolean) && tok->str() == MatchCompiler::makeConstString("false")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: throw (
MAYBE_UNUSED static inline bool match149(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("throw")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: = 0|default|delete ;
MAYBE_UNUSED static inline bool match150(const Token* tok) {
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
// pattern: ;|{|override|final
MAYBE_UNUSED static inline bool match151(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString("override")) || (tok->str() == MatchCompiler::makeConstString("final"))))
        return false;
    return true;
}
// pattern: &|&&|*|::|)|]|%name%
MAYBE_UNUSED static inline bool match152(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || tok->isName()))
        return false;
    return true;
}
// pattern: ;|}|{|public:|protected:|private:
MAYBE_UNUSED static inline bool match153(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("private:"))))
        return false;
    return true;
}
// pattern: template <
MAYBE_UNUSED static inline bool match154(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: ( )
MAYBE_UNUSED static inline bool match155(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ( void )
MAYBE_UNUSED static inline bool match156(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("void")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: const
MAYBE_UNUSED static inline bool match157(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    return true;
}
// pattern: %name%|%type%|::
MAYBE_UNUSED static inline bool match158(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->isName() && tok->varId() == 0U) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: ,|)|=
MAYBE_UNUSED static inline bool match159(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: struct|enum|union|class
MAYBE_UNUSED static inline bool match160(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || (tok->str() == MatchCompiler::makeConstString("class"))))
        return false;
    return true;
}
// pattern: !!( )
MAYBE_UNUSED static inline bool match161(const Token* tok) {
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    tok = tok ? tok->next() : nullptr;
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ,|)
MAYBE_UNUSED static inline bool match162(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: (|, %type% ,|)
MAYBE_UNUSED static inline bool match163(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: * %name%| ,|)|=
MAYBE_UNUSED static inline bool match164(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: %name%| [ ] ,|)
MAYBE_UNUSED static inline bool match165(const Token* tok) {
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: %name%| ,|)
MAYBE_UNUSED static inline bool match166(const Token* tok) {
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: %name% ,|)|=|[
MAYBE_UNUSED static inline bool match167(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: %name% ,|)|[
MAYBE_UNUSED static inline bool match168(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: > :: %name%
MAYBE_UNUSED static inline bool match169(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: decltype|typeof
MAYBE_UNUSED static inline bool match170(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("decltype")) || (tok->str() == MatchCompiler::makeConstString("typeof"))))
        return false;
    return true;
}
// pattern: (|[|{|<
MAYBE_UNUSED static inline bool match171(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: ,
MAYBE_UNUSED static inline bool match172(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: %name%|> %name%
MAYBE_UNUSED static inline bool match173(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: > :: type
MAYBE_UNUSED static inline bool match174(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("type")))
        return false;
    return true;
}
// pattern: enable_if|enable_if_t|EnableIf
MAYBE_UNUSED static inline bool match175(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("enable_if")) || (tok->str() == MatchCompiler::makeConstString("enable_if_t")) || (tok->str() == MatchCompiler::makeConstString("EnableIf"))))
        return false;
    return true;
}
// pattern: const
template<class T> MAYBE_UNUSED static inline T * findmatch176(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: &|&&
MAYBE_UNUSED static inline bool match177(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: void
MAYBE_UNUSED static inline bool match178(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("void")))
        return false;
    return true;
}
// pattern: ) noexcept (
MAYBE_UNUSED static inline bool match179(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("noexcept")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: = default ;
MAYBE_UNUSED static inline bool match180(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("default")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: = default|delete ;
MAYBE_UNUSED static inline bool match181(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("default")) || (tok->str() == MatchCompiler::makeConstString("delete"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: :|,
MAYBE_UNUSED static inline bool match182(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: ::|<|>|(|)|[|]|*|&|&&|%name%
MAYBE_UNUSED static inline bool match183(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || tok->isName()))
        return false;
    return true;
}
// pattern: <|(|[
MAYBE_UNUSED static inline bool match184(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: %num% [,>]
MAYBE_UNUSED static inline bool match185(const Token* tok) {
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",>", tok->str()[0]))
        return false;
    return true;
}
// pattern: {|;|override|final
MAYBE_UNUSED static inline bool match186(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString(";")) || (tok->str() == MatchCompiler::makeConstString("override")) || (tok->str() == MatchCompiler::makeConstString("final"))))
        return false;
    return true;
}
// pattern: ( & %var% ) [
MAYBE_UNUSED static inline bool match187(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ( * const| %var% ) (
MAYBE_UNUSED static inline bool match188(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) [,)]
MAYBE_UNUSED static inline bool match189(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: ( * %var% ) [
MAYBE_UNUSED static inline bool match190(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: const|volatile|enum|struct|::
MAYBE_UNUSED static inline bool match191(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: %type% <
MAYBE_UNUSED static inline bool match192(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: > :: %type%
MAYBE_UNUSED static inline bool match193(const Token* tok) {
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
// pattern: [{[(<]
MAYBE_UNUSED static inline bool match194(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{[(<", tok->str()[0]))
        return false;
    return true;
}
// pattern: enum|struct|const|volatile
MAYBE_UNUSED static inline bool match195(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        return false;
    return true;
}
// pattern: ...
MAYBE_UNUSED static inline bool match196(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")))
        return false;
    return true;
}
// pattern: virtual|public:|private:|protected:|{|}|;
MAYBE_UNUSED static inline bool match197(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("virtual")) || (tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("private:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: :|{
MAYBE_UNUSED static inline bool match198(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: if|while ( %type%
MAYBE_UNUSED static inline bool match199(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: class|struct|union|namespace %type% :|{
MAYBE_UNUSED static inline bool match200(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || (tok->str() == MatchCompiler::makeConstString("namespace"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: } %name% ;|[
MAYBE_UNUSED static inline bool match201(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: private:|protected:|public:
MAYBE_UNUSED static inline bool match202(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("private:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("public:"))))
        return false;
    return true;
}
// pattern: return|delete|goto
MAYBE_UNUSED static inline bool match203(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("delete")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("goto"))))
        return false;
    return true;
}
// pattern: case|default
MAYBE_UNUSED static inline bool match204(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("default"))))
        return false;
    return true;
}
// pattern: [:;{}]
MAYBE_UNUSED static inline bool match205(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(":;{}", tok->str()[0]))
        return false;
    return true;
}
// pattern: ;|{|}|public:|protected:|private:
MAYBE_UNUSED static inline bool match206(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("private:"))))
        return false;
    return true;
}
// pattern: throw %any% (
MAYBE_UNUSED static inline bool match207(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("throw")))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: throw %any% :: %any% (
MAYBE_UNUSED static inline bool match208(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("throw")))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: friend %type%
MAYBE_UNUSED static inline bool match209(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("friend")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: ;|{
template<class T> MAYBE_UNUSED static inline T * findmatch210(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: const|constexpr|volatile|static|mutable|extern
MAYBE_UNUSED static inline bool match211(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("constexpr")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || (tok->str() == MatchCompiler::makeConstString("mutable")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern"))))
        return false;
    return true;
}
// pattern: auto &|&&| [
MAYBE_UNUSED static inline bool match212(const Token* tok) {
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
template<class T> MAYBE_UNUSED static inline T * findmatch213(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: %name%|,
MAYBE_UNUSED static inline bool match214(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: class|struct|union|enum
MAYBE_UNUSED static inline bool match215(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    return true;
}
// pattern: [|{
MAYBE_UNUSED static inline bool match216(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: enum|struct
MAYBE_UNUSED static inline bool match217(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    return true;
}
// pattern: [;:]
MAYBE_UNUSED static inline bool match218(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";:", tok->str()[0]))
        return false;
    return true;
}
// pattern: , %name%
MAYBE_UNUSED static inline bool match219(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: ( [*&]
MAYBE_UNUSED static inline bool match220(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("*&", tok->str()[0]))
        return false;
    return true;
}
// pattern: (|[
MAYBE_UNUSED static inline bool match221(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: ( *
MAYBE_UNUSED static inline bool match222(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: ] ) ;
MAYBE_UNUSED static inline bool match223(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: const|static|volatile
MAYBE_UNUSED static inline bool match224(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        return false;
    return true;
}
// pattern: throw|new
MAYBE_UNUSED static inline bool match225(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("throw")) || (tok->str() == MatchCompiler::makeConstString("new"))))
        return false;
    return true;
}
// pattern: ) %name%
MAYBE_UNUSED static inline bool match226(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: alignas (
MAYBE_UNUSED static inline bool match227(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("alignas")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: const_cast|dynamic_cast|reinterpret_cast|static_cast <
MAYBE_UNUSED static inline bool match228(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("const_cast")) || (tok->str() == MatchCompiler::makeConstString("dynamic_cast")) || (tok->str() == MatchCompiler::makeConstString("reinterpret_cast")) || (tok->str() == MatchCompiler::makeConstString("static_cast"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: :: %type% %name% [;=({]
MAYBE_UNUSED static inline bool match229(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";=({", tok->str()[0]))
        return false;
    return true;
}
// pattern: [)}] ;
MAYBE_UNUSED static inline bool match230(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(")}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: %type%
MAYBE_UNUSED static inline bool match231(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: ) %name%|*|&|&&
MAYBE_UNUSED static inline bool match232(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: const|*|&
MAYBE_UNUSED static inline bool match233(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: %name% ;|=
MAYBE_UNUSED static inline bool match234(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: %name% )|[
MAYBE_UNUSED static inline bool match235(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: %name% (|{
MAYBE_UNUSED static inline bool match236(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: )|} ;
MAYBE_UNUSED static inline bool match237(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: %name% )
MAYBE_UNUSED static inline bool match238(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: %name% =|,|}
MAYBE_UNUSED static inline bool match239(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: ) ,|}
MAYBE_UNUSED static inline bool match240(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: ,|}
MAYBE_UNUSED static inline bool match241(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: :
MAYBE_UNUSED static inline bool match242(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: > ::
MAYBE_UNUSED static inline bool match243(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: [ ]
MAYBE_UNUSED static inline bool match244(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    return true;
}
// pattern: ~
MAYBE_UNUSED static inline bool match245(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~")))
        return false;
    return true;
}
// pattern: char|wchar_t
MAYBE_UNUSED static inline bool match246(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("char")) || (tok->str() == MatchCompiler::makeConstString("wchar_t"))))
        return false;
    return true;
}
// pattern: char|short|int|long
MAYBE_UNUSED static inline bool match247(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("char")) || (tok->str() == MatchCompiler::makeConstString("short")) || (tok->str() == MatchCompiler::makeConstString("int")) || (tok->str() == MatchCompiler::makeConstString("long"))))
        return false;
    return true;
}
// pattern: %name%|*|&|::
MAYBE_UNUSED static inline bool match248(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: %name% const| %var%|*|&
MAYBE_UNUSED static inline bool match249(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !((tok->varId() != 0) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: %name%|*|&|::|<
MAYBE_UNUSED static inline bool match250(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: %var% ,|)
MAYBE_UNUSED static inline bool match251(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: nullptr|NULL ,|)
MAYBE_UNUSED static inline bool match252(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("nullptr")) || (tok->str() == MatchCompiler::makeConstString("NULL"))))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: >|%type% ::
MAYBE_UNUSED static inline bool match253(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || (tok->isName() && tok->varId() == 0U)))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: %type% :: %name% [(),>]
MAYBE_UNUSED static inline bool match254(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("(),>", tok->str()[0]))
        return false;
    return true;
}
// pattern: > :: %name% (
MAYBE_UNUSED static inline bool match255(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: !!this .
MAYBE_UNUSED static inline bool match256(const Token* tok) {
    if (tok && tok->str() == MatchCompiler::makeConstString("this"))
        return false;
    tok = tok ? tok->next() : nullptr;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: %var% .
MAYBE_UNUSED static inline bool match257(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: struct|union
MAYBE_UNUSED static inline bool match258(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    return true;
}
// pattern: struct|union|enum
MAYBE_UNUSED static inline bool match259(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    return true;
}
// pattern: ::|<
MAYBE_UNUSED static inline bool match260(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: std :: array
MAYBE_UNUSED static inline bool match261(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("std")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("array")))
        return false;
    return true;
}
// pattern: <<|>>
MAYBE_UNUSED static inline bool match262(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("<<")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    return true;
}
// pattern: . %name% (
MAYBE_UNUSED static inline bool match263(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %var% ; %var% =
MAYBE_UNUSED static inline bool match264(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: %var% =
MAYBE_UNUSED static inline bool match265(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: auto
MAYBE_UNUSED static inline bool match266(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("auto")))
        return false;
    return true;
}
// pattern: auto *|&|&&
MAYBE_UNUSED static inline bool match267(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("auto")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: auto * const
MAYBE_UNUSED static inline bool match268(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("auto")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    return true;
}
// pattern: const|constexpr
MAYBE_UNUSED static inline bool match269(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("constexpr"))))
        return false;
    return true;
}
// pattern: volatile
MAYBE_UNUSED static inline bool match270(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")))
        return false;
    return true;
}
// pattern: *|&
MAYBE_UNUSED static inline bool match271(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: * const
MAYBE_UNUSED static inline bool match272(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    return true;
}
// pattern: * volatile
MAYBE_UNUSED static inline bool match273(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")))
        return false;
    return true;
}
// pattern: std :: move (
MAYBE_UNUSED static inline bool match274(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("std")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("move")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ( const| auto *|&|&&| %var% :
MAYBE_UNUSED static inline bool match275(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("auto")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: for
MAYBE_UNUSED static inline bool match276(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")))
        return false;
    return true;
}
// pattern: auto %var% {
MAYBE_UNUSED static inline bool match277(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("auto")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %name%|*|&|&&|::|(
MAYBE_UNUSED static inline bool match278(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: typename|template
MAYBE_UNUSED static inline bool match279(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("typename")) || (tok->str() == MatchCompiler::makeConstString("template"))))
        return false;
    return true;
}
// pattern: ) const| {
MAYBE_UNUSED static inline bool match280(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %name%|*|&|&&|::
MAYBE_UNUSED static inline bool match281(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: %type%|::|<
MAYBE_UNUSED static inline bool match282(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: !!:: %name% !!::
MAYBE_UNUSED static inline bool match283(const Token* tok) {
    if (tok && tok->str() == MatchCompiler::makeConstString("::"))
        return false;
    tok = tok ? tok->next() : nullptr;
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("::"))
        return false;
    return true;
}
// pattern: ; %varid% = [
MAYBE_UNUSED static inline bool match284(const Token* tok, const int varid) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: { [
MAYBE_UNUSED static inline bool match285(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ( %name%
MAYBE_UNUSED static inline bool match286(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: static_cast|const_cast|dynamic_cast|reinterpret_cast < %name%
MAYBE_UNUSED static inline bool match287(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("static_cast")) || (tok->str() == MatchCompiler::makeConstString("const_cast")) || (tok->str() == MatchCompiler::makeConstString("dynamic_cast")) || (tok->str() == MatchCompiler::makeConstString("reinterpret_cast"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: sizeof (
MAYBE_UNUSED static inline bool match288(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ( %type% %type%| *| *| )
MAYBE_UNUSED static inline bool match289(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (tok && ((tok->isName() && tok->varId() == 0U)))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: :: %name% < %name%
MAYBE_UNUSED static inline bool match290(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: return {
MAYBE_UNUSED static inline bool match291(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ( std| ::| nothrow )
MAYBE_UNUSED static inline bool match292(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("std"))))
        tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("nothrow")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: %type% ;|[|(
MAYBE_UNUSED static inline bool match293(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: %name% ; %name% = [
MAYBE_UNUSED static inline bool match294(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: %name% {|= [
MAYBE_UNUSED static inline bool match295(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/symboldatabase.cpp"
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
#include "symboldatabase.h"

#include "astutils.h"
#include "errorlogger.h"
#include "errortypes.h"
#include "keywords.h"
#include "library.h"
#include "mathlib.h"
#include "path.h"
#include "platform.h"
#include "settings.h"
#include "standards.h"
#include "templatesimplifier.h"
#include "token.h"
#include "tokenize.h"
#include "tokenlist.h"
#include "utils.h"
#include "valueflow.h"
#include "vfvalue.h"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
//---------------------------------------------------------------------------

SymbolDatabase::SymbolDatabase(Tokenizer& tokenizer)
    : mTokenizer(tokenizer)
    , mSettings(tokenizer.getSettings())
    , mErrorLogger(tokenizer.getErrorLogger())
{
    if (!mTokenizer.tokens())
        return;

    if (mSettings.platform.defaultSign == 's' || mSettings.platform.defaultSign == 'S')
        mDefaultSignedness = ValueType::SIGNED;
    else if (mSettings.platform.defaultSign == 'u' || mSettings.platform.defaultSign == 'U')
        mDefaultSignedness = ValueType::UNSIGNED;
    else
        mDefaultSignedness = ValueType::UNKNOWN_SIGN;

    createSymbolDatabaseFindAllScopes();
    createSymbolDatabaseClassInfo();
    createSymbolDatabaseVariableInfo();
    createSymbolDatabaseCopyAndMoveConstructors();
    createSymbolDatabaseFunctionScopes();
    createSymbolDatabaseClassAndStructScopes();
    createSymbolDatabaseFunctionReturnTypes();
    createSymbolDatabaseNeedInitialization();
    createSymbolDatabaseVariableSymbolTable();
    createSymbolDatabaseSetScopePointers();
    createSymbolDatabaseSetVariablePointers();
    createSymbolDatabaseSetTypePointers();
    setValueTypeInTokenList(false);
    createSymbolDatabaseSetFunctionPointers(true);
    createSymbolDatabaseSetSmartPointerType();
    setValueTypeInTokenList(false);
    createSymbolDatabaseEnums();
    createSymbolDatabaseEscapeFunctions();
    createSymbolDatabaseIncompleteVars();
    createSymbolDatabaseExprIds();
    debugSymbolDatabase();
}

static const Token* skipScopeIdentifiers(const Token* tok)
{
    if (match1(tok))
        tok = tok->next();
    while (match2(tok) ||
           (match3(tok) && match4(tok->linkAt(1)))) {
        if (tok->strAt(1) == MatchCompiler::makeConstString("::"))
            tok = tok->tokAt(2);
        else
            tok = tok->linkAt(1)->tokAt(2);
    }

    return tok;
}

static bool isExecutableScope(const Token* tok)
{
    if (!match5(tok))
        return false;
    const Token * tok2 = tok->link()->previous();
    if (match6(tok2))
        return true;
    if (tok2 == tok)
        return false;
    if (match7(tok2)) { // inner scope
        const Token* startTok = tok2->link();
        if (match8(startTok->previous()))
            return true;
        if (match9(startTok->previous()))
            return !findLambdaStartToken(tok2);
        return isExecutableScope(startTok);
    }
    return false;
}

const Token* SymbolDatabase::isEnumDefinition(const Token* tok)
{
    if (!match10(tok))
        return nullptr;
    while (!match11(tok))
        tok = tok->next();
    if (tok->str() == MatchCompiler::makeConstString("{"))
        return tok;
    tok = tok->next(); // skip ':'
    while (match12(tok))
        tok = tok->next();
    return match5(tok) ? tok : nullptr;
}

void SymbolDatabase::createSymbolDatabaseFindAllScopes()
{
    // create global scope
    scopeList.emplace_back(*this, nullptr, nullptr);

    // pointer to current scope
    Scope *scope = &scopeList.back();

    // Store the ending of init lists
    std::stack<std::pair<const Token*, const Scope*>> endInitList;
    auto inInitList = [&] {
        if (endInitList.empty())
            return false;
        return endInitList.top().second == scope;
    };

    std::stack<const Token*> inIfCondition;

    auto addLambda = [this, &scope](const Token* tok, const Token* lambdaEndToken) -> const Token* {
        const Token* lambdaStartToken = lambdaEndToken->link();
        const Token* argStart = lambdaStartToken->astParent();
        const Token* funcStart = match13(argStart) ? argStart : argStart->astParent();
        const Function* function = addGlobalFunction(scope, tok, argStart, funcStart);
        if (!function)
            mTokenizer.syntaxError(tok);
        return lambdaStartToken;
    };

    // Store current access in each scope (depends on evaluation progress)
    std::map<const Scope*, AccessControl> access;

    const bool doProgress = (mSettings.reportProgress != -1);

    std::map<Scope *, std::set<std::string>> forwardDecls;

    const std::function<Scope *(const Token *, Scope *)> findForwardDeclScope = [&](const Token *tok, Scope *startScope) {
        if (tok->str() == MatchCompiler::makeConstString("::"))
            return findForwardDeclScope(tok->next(), &scopeList.front());

        if (match14(tok)) {
            auto it = std::find_if(startScope->nestedList.cbegin(), startScope->nestedList.cend(), [&](const Scope *scope) {
                return scope->className == tok->str();
            });

            if (it == startScope->nestedList.cend())
                return static_cast<Scope *>(nullptr);

            return findForwardDeclScope(tok->tokAt(2), *it);
        }

        auto it = forwardDecls.find(startScope);
        if (it == forwardDecls.cend())
            return static_cast<Scope *>(nullptr);

        return it->second.count(tok->str()) > 0 ? startScope : nullptr;
    };

    // find all scopes
    for (const Token *tok = mTokenizer.tokens(); tok; tok = tok ? tok->next() : nullptr) {
        // #5593 suggested to add here:
        if (doProgress)
            mErrorLogger.reportProgress(mTokenizer.list.getSourceFilePath(),
                                        "SymbolDatabase",
                                        tok->progressValue());
        // Locate next class
        if ((tok->isCpp() && tok->isKeyword() &&
             ((match15(tok) &&
               !match16(tok->previous())) ||
              isEnumDefinition(tok)))
            || (tok->isC() && tok->isKeyword() && match17(tok))) {
            const Token *tok2 = tok->tokAt(2);

            if (tok->strAt(1) == MatchCompiler::makeConstString("::"))
                tok2 = tok2->next();
            else if (tok->isCpp() && tok->strAt(1) == MatchCompiler::makeConstString("class"))
                tok2 = tok2->next();

            while (match1(tok2))
                tok2 = tok2->tokAt(2);
            while (match14(tok2))
                tok2 = tok2->tokAt(2);

            // skip over template args
            while (tok2 && tok2->str() == MatchCompiler::makeConstString("<") && tok2->link()) {
                tok2 = tok2->link()->next();
                while (match1(tok2))
                    tok2 = tok2->tokAt(2);
            }

            // skip over final
            if (tok2 && tok2->isCpp() && match18(tok2))
                tok2 = tok2->next();

            // make sure we have valid code
            if (!match19(tok2)) {
                // check for qualified variable
                if (tok2 && tok2->next()) {
                    if (tok2->strAt(1) == MatchCompiler::makeConstString(";"))
                        tok = tok2->next();
                    else if (match20(tok2->next()) &&
                             match21(tok2->linkAt(2)))
                        tok = tok2->linkAt(2)->next();
                    else if (match22(tok2->next()) &&
                             tok2->linkAt(1)->strAt(1) == MatchCompiler::makeConstString(";"))
                        tok = tok2->linkAt(1)->next();
                    // skip variable declaration
                    else if (match23(tok2))
                        continue;
                    else if (match24(tok2) && TokenList::isFunctionHead(tok2->next(), "{;"))
                        continue;
                    else if (match25(tok2))
                        continue;
                    // skip template
                    else if (match26(tok2) &&
                             match27(tok->previous())) {
                        tok = tok2;
                        continue;
                    }
                    // forward declaration
                    else if (match26(tok2) &&
                             match28(tok)) {
                        // TODO: see if it can be used
                        tok = tok2;
                        continue;
                    }
                    // skip constructor
                    else if (match29(tok2) &&
                             match30(tok2->link())) {
                        tok = tok2->link()->next();
                        continue;
                    } else
                        throw InternalError(tok2, "SymbolDatabase bailout; unhandled code", InternalError::SYNTAX);
                    continue;
                }
                break; // bail
            }

            const Token * name = tok->next();

            if (name->str() == MatchCompiler::makeConstString("class") && name->strAt(-1) == MatchCompiler::makeConstString("enum"))
                name = name->next();

            Scope *new_scope = findScope(name, scope);

            if (new_scope) {
                // only create base list for classes and structures
                if (new_scope->isClassOrStruct()) {
                    // goto initial '{'
                    if (!new_scope->definedType)
                        mTokenizer.syntaxError(nullptr); // #6808
                    tok2 = new_scope->definedType->initBaseInfo(tok, tok2);
                    // make sure we have valid code
                    if (!tok2) {
                        break;
                    }
                }

                // definition may be different than declaration
                if (tok->isCpp() && tok->str() == MatchCompiler::makeConstString("class")) {
                    access[new_scope] = AccessControl::Private;
                    new_scope->type = ScopeType::eClass;
                } else if (tok->str() == MatchCompiler::makeConstString("struct")) {
                    access[new_scope] = AccessControl::Public;
                    new_scope->type = ScopeType::eStruct;
                }

                new_scope->classDef = tok;
                new_scope->setBodyStartEnd(tok2);
                // make sure we have valid code
                if (!new_scope->bodyEnd) {
                    mTokenizer.syntaxError(tok);
                }
                scope = new_scope;
                tok = tok2;
            } else {

                const Scope *forwardDeclScope = findForwardDeclScope(tok->next(), scope);
                const Scope *nestedIn = forwardDeclScope ? forwardDeclScope : scope;

                scopeList.emplace_back(*this, tok, nestedIn);
                new_scope = &scopeList.back();

                if (tok->str() == MatchCompiler::makeConstString("class"))
                    access[new_scope] = AccessControl::Private;
                else if (tok->str() == MatchCompiler::makeConstString("struct") || tok->str() == MatchCompiler::makeConstString("union"))
                    access[new_scope] = AccessControl::Public;

                // fill typeList...
                if (new_scope->isClassOrStructOrUnion() || new_scope->type == ScopeType::eEnum) {
                    Type* new_type = findType(name, scope);
                    if (!new_type) {
                        typeList.emplace_back(new_scope->classDef, new_scope, nestedIn);
                        new_type = &typeList.back();
                        scope->definedTypesMap[new_type->name()] = new_type;
                    } else
                        new_type->classScope = new_scope;
                    new_scope->definedType = new_type;
                }

                // only create base list for classes and structures
                if (new_scope->isClassOrStruct()) {
                    // goto initial '{'
                    tok2 = new_scope->definedType->initBaseInfo(tok, tok2);

                    // make sure we have valid code
                    if (!tok2) {
                        mTokenizer.syntaxError(tok);
                    }
                } else if (new_scope->type == ScopeType::eEnum) {
                    if (tok2->str() == MatchCompiler::makeConstString(":")) {
                        tok2 = tok2->tokAt(2);
                        while (match12(tok2))
                            tok2 = tok2->next();
                    }
                }

                new_scope->setBodyStartEnd(tok2);

                // make sure we have valid code
                if (!new_scope->bodyEnd) {
                    mTokenizer.syntaxError(tok);
                }

                if (new_scope->type == ScopeType::eEnum) {
                    tok2 = new_scope->addEnum(tok);
                    scope->nestedList.push_back(new_scope);

                    if (!tok2)
                        mTokenizer.syntaxError(tok);
                } else {
                    // make the new scope the current scope
                    scope->nestedList.push_back(new_scope);
                    scope = new_scope;
                }

                tok = tok2;
            }
        }

        // Namespace and unknown macro (#3854)
        else if (tok->isCpp() && tok->isKeyword() &&
                 match31(tok) &&
                 tok->tokAt(2)->isUpperCaseName() &&
                 match32(tok->linkAt(3))) {
            scopeList.emplace_back(*this, tok, scope);

            Scope *new_scope = &scopeList.back();
            access[new_scope] = AccessControl::Public;

            const Token *tok2 = tok->linkAt(3)->next();

            new_scope->setBodyStartEnd(tok2);

            // make sure we have valid code
            if (!new_scope->bodyEnd) {
                scopeList.pop_back();
                break;
            }

            // make the new scope the current scope
            scope->nestedList.push_back(new_scope);
            scope = &scopeList.back();

            tok = tok2;
        }

        // forward declaration
        else if (tok->isKeyword() && match33(tok) &&
                 tok->strAt(-1) != MatchCompiler::makeConstString("friend")) {
            if (!findType(tok->next(), scope)) {
                // fill typeList..
                typeList.emplace_back(tok, nullptr, scope);
                Type* new_type = &typeList.back();
                scope->definedTypesMap[new_type->name()] = new_type;
                forwardDecls[scope].insert(tok->strAt(1));
            }
            tok = tok->tokAt(2);
        }

        // using namespace
        else if (tok->isCpp() && tok->isKeyword() && match34(tok)) {
            Scope::UsingInfo using_info;

            using_info.start = tok; // save location
            using_info.scope = findNamespace(tok->tokAt(2), scope);

            scope->usingList.push_back(using_info);

            // check for global namespace
            if (tok->strAt(2) == MatchCompiler::makeConstString("::"))
                tok = tok->tokAt(4);
            else
                tok = tok->tokAt(3);

            // skip over qualification
            while (match35(tok))
                tok = tok->tokAt(2);
        }

        // using type alias
        else if (tok->isCpp() && tok->isKeyword() && match36(tok) && !tok->tokAt(2)->isSimplifiedTypedef()) {
            if (tok->strAt(-1) != MatchCompiler::makeConstString(">") && !findType(tok->next(), scope)) {
                // fill typeList..
                typeList.emplace_back(tok, nullptr, scope);
                Type* new_type = &typeList.back();
                scope->definedTypesMap[new_type->name()] = new_type;
            }

            tok = tok->tokAt(3);

            while (tok && tok->str() != MatchCompiler::makeConstString(";")) {
                if (match37(tok))
                    tok = tok->linkAt(1);
                else
                    tok = tok->next();
            }
        }

        // unnamed struct and union
        else if (tok->isKeyword() && match38(tok) &&
                 match39(tok->linkAt(1))) {
            scopeList.emplace_back(*this, tok, scope);

            Scope *new_scope = &scopeList.back();
            access[new_scope] = AccessControl::Public;

            const Token* varNameTok = tok->linkAt(1)->next();
            if (varNameTok->str() == MatchCompiler::makeConstString("*")) {
                varNameTok = varNameTok->next();
            } else if (varNameTok->str() == MatchCompiler::makeConstString("&")) {
                varNameTok = varNameTok->next();
            }

            typeList.emplace_back(tok, new_scope, scope);
            {
                Type* new_type = &typeList.back();
                new_scope->definedType = new_type;
                scope->definedTypesMap[new_type->name()] = new_type;
            }

            scope->addVariable(varNameTok, tok, tok, access[scope], new_scope->definedType, scope);

            const Token *tok2 = tok->next();

            new_scope->setBodyStartEnd(tok2);

            // make sure we have valid code
            if (!new_scope->bodyEnd) {
                scopeList.pop_back();
                break;
            }

            // make the new scope the current scope
            scope->nestedList.push_back(new_scope);
            scope = new_scope;

            tok = tok2;
        }

        // anonymous struct, union and namespace
        else if (tok->isKeyword() && ((match38(tok) &&
                                       match21(tok->linkAt(1))) ||
                                      match40(tok))) {
            scopeList.emplace_back(*this, tok, scope);

            Scope *new_scope = &scopeList.back();
            access[new_scope] = AccessControl::Public;

            const Token *tok2 = tok->next();

            new_scope->setBodyStartEnd(tok2);

            typeList.emplace_back(tok, new_scope, scope);
            {
                Type* new_type = &typeList.back();
                new_scope->definedType = new_type;
                scope->definedTypesMap[new_type->name()] = new_type;
            }

            // make sure we have valid code
            if (!new_scope->bodyEnd) {
                scopeList.pop_back();
                break;
            }

            // make the new scope the current scope
            scope->nestedList.push_back(new_scope);
            scope = new_scope;

            tok = tok2;
        }

        // forward declared enum
        else if (tok->isKeyword() && (match41(tok) || match42(tok))) {
            typeList.emplace_back(tok, nullptr, scope);
            Type* new_type = &typeList.back();
            scope->definedTypesMap[new_type->name()] = new_type;
            tok = tok->tokAt(2);
        }

        // check for end of scope
        else if (tok == scope->bodyEnd) {
            do {
                access.erase(scope);
                scope = const_cast<Scope*>(scope->nestedIn);
            } while (scope->type != ScopeType::eGlobal && succeeds(tok, scope->bodyEnd));
            continue;
        }
        // check for end of init list
        else if (inInitList() && tok == endInitList.top().first) {
            endInitList.pop();
            continue;
        }

        // check if in class or structure or union
        else if (scope->isClassOrStructOrUnion()) {
            const Token *funcStart = nullptr;
            const Token *argStart = nullptr;
            const Token *declEnd = nullptr;

            // What section are we in..
            if (tok->str() == MatchCompiler::makeConstString("private:"))
                access[scope] = AccessControl::Private;
            else if (tok->str() == MatchCompiler::makeConstString("protected:"))
                access[scope] = AccessControl::Protected;
            else if (tok->str() == MatchCompiler::makeConstString("public:") || tok->str() == MatchCompiler::makeConstString("__published:"))
                access[scope] = AccessControl::Public;
            else if (match43(tok)) {
                if (tok->str() == MatchCompiler::makeConstString("private"))
                    access[scope] = AccessControl::Private;
                else if (tok->str() == MatchCompiler::makeConstString("protected"))
                    access[scope] = AccessControl::Protected;
                else
                    access[scope] = AccessControl::Public;

                tok = tok->tokAt(2);
            }

            // class function?
            else if (isFunction(tok, scope, funcStart, argStart, declEnd)) {
                if (tok->strAt(-1) != MatchCompiler::makeConstString("::") || tok->strAt(-2) == scope->className) {
                    Function function(tok, scope, funcStart, argStart);

                    // save the access type
                    function.access = access[scope];

                    const Token *end = function.argDef->link();

                    // count the number of constructors
                    if (function.isConstructor())
                        scope->numConstructors++;

                    // assume implementation is inline (definition and implementation same)
                    function.token = function.tokenDef;
                    function.arg = function.argDef;

                    // out of line function
                    if (const Token *endTok = TokenList::isFunctionHead(end, ";")) {
                        tok = endTok;
                        scope->addFunction(std::move(function));
                    }

                    // inline function
                    else {
                        // find start of function '{'
                        bool foundInitList = false;
                        while (end && end->str() != MatchCompiler::makeConstString("{") && end->str() != MatchCompiler::makeConstString(";")) {
                            if (end->link() && match44(end)) {
                                end = end->link();
                            } else if (foundInitList &&
                                       match45(end) &&
                                       match46(end->linkAt(1))) {
                                end = end->linkAt(1);
                            } else {
                                if (end->str() == MatchCompiler::makeConstString(":"))
                                    foundInitList = true;
                                end = end->next();
                            }
                        }

                        if (!end || end->str() == MatchCompiler::makeConstString(";"))
                            continue;

                        scope->addFunction(function);

                        Function* funcptr = &scope->functionList.back();
                        const Token *tok2 = funcStart;

                        addNewFunction(scope, tok2);
                        if (scope) {
                            scope->functionOf = function.nestedIn;
                            scope->function = funcptr;
                            scope->function->functionScope = scope;
                        }

                        tok = tok2;
                    }
                }

                // nested class or friend function?
                else {
                    /** @todo check entire qualification for match */
                    const Scope * const nested = scope->findInNestedListRecursive(tok->strAt(-2));

                    if (nested)
                        addClassFunction(scope, tok, argStart);
                    else {
                        /** @todo handle friend functions */
                    }
                }
            }

            // friend class declaration?
            else if (tok->isCpp() && tok->isKeyword() && match47(tok)) {
                Type::FriendInfo friendInfo;

                // save the name start
                friendInfo.nameStart = tok->strAt(1) == MatchCompiler::makeConstString("class") ? tok->tokAt(2) : tok->next();
                friendInfo.nameEnd = friendInfo.nameStart;

                // skip leading "::"
                if (friendInfo.nameEnd->str() == MatchCompiler::makeConstString("::"))
                    friendInfo.nameEnd = friendInfo.nameEnd->next();

                // skip qualification "name ::"
                while (friendInfo.nameEnd && friendInfo.nameEnd->strAt(1) == MatchCompiler::makeConstString("::"))
                    friendInfo.nameEnd = friendInfo.nameEnd->tokAt(2);

                // fill this in after parsing is complete
                friendInfo.type = nullptr;

                if (!scope->definedType)
                    mTokenizer.syntaxError(tok);

                scope->definedType->friendList.push_back(friendInfo);
            }
        } else if (scope->type == ScopeType::eNamespace || scope->type == ScopeType::eGlobal) {
            const Token *funcStart = nullptr;
            const Token *argStart = nullptr;
            const Token *declEnd = nullptr;

            // function?
            if (isFunction(tok, scope, funcStart, argStart, declEnd)) {
                // has body?
                if (declEnd && declEnd->str() == MatchCompiler::makeConstString("{")) {
                    tok = funcStart;

                    // class function
                    if (tok->previous() && tok->strAt(-1) == MatchCompiler::makeConstString("::"))
                        addClassFunction(scope, tok, argStart);

                    // class destructor
                    else if (tok->previous() &&
                             tok->strAt(-1) == MatchCompiler::makeConstString("~") &&
                             tok->strAt(-2) == MatchCompiler::makeConstString("::"))
                        addClassFunction(scope, tok, argStart);

                    // regular function
                    else {
                        const Function* const function = addGlobalFunction(scope, tok, argStart, funcStart);

                        if (!function)
                            mTokenizer.syntaxError(tok);
                    }

                    // syntax error?
                    if (!scope)
                        mTokenizer.syntaxError(tok);
                }
                // function prototype?
                else if (declEnd && declEnd->str() == MatchCompiler::makeConstString(";")) {
                    if (tok->astParent() && tok->astParent()->str() == MatchCompiler::makeConstString("::") &&
                        match48(declEnd->previous())) {
                        addClassFunction(scope, tok, argStart);
                        continue;
                    }

                    bool newFunc = true; // Is this function already in the database?
                    auto range = scope->functionMap.equal_range(tok->str());
                    for (std::multimap<std::string, const Function*>::const_iterator it = range.first; it != range.second; ++it) {
                        if (it->second->argsMatch(scope, it->second->argDef, argStart, emptyString, 0)) {
                            newFunc = false;
                            break;
                        }
                    }

                    // save function prototype in database
                    if (newFunc) {
                        addGlobalFunctionDecl(scope, tok, argStart, funcStart);
                    }

                    tok = declEnd;
                    continue;
                }
            } else if (const Token *lambdaEndToken = findLambdaEndToken(tok)) {
                tok = addLambda(tok, lambdaEndToken);
            }
        } else if (scope->isExecutable()) {
            if (tok->isKeyword() && match49(tok)) {
                const Token* tok1 = tok->next();
                if (tok->str() == MatchCompiler::makeConstString("else"))
                    scopeList.emplace_back(*this, tok, scope, ScopeType::eElse, tok1);
                else if (tok->str() == MatchCompiler::makeConstString("do"))
                    scopeList.emplace_back(*this, tok, scope, ScopeType::eDo, tok1);
                else //if (tok->str() == MatchCompiler::makeConstString("try"))
                    scopeList.emplace_back(*this, tok, scope, ScopeType::eTry, tok1);

                tok = tok1;
                scope->nestedList.push_back(&scopeList.back());
                scope = &scopeList.back();
            } else if (tok->isKeyword() && match50(tok) && match32(tok->linkAt(1))) {
                const Token *scopeStartTok = tok->linkAt(1)->next();
                if (tok->str() == MatchCompiler::makeConstString("if"))
                    scopeList.emplace_back(*this, tok, scope, ScopeType::eIf, scopeStartTok);
                else if (tok->str() == MatchCompiler::makeConstString("for")) {
                    scopeList.emplace_back(*this, tok, scope, ScopeType::eFor, scopeStartTok);
                } else if (tok->str() == MatchCompiler::makeConstString("while"))
                    scopeList.emplace_back(*this, tok, scope, ScopeType::eWhile, scopeStartTok);
                else if (tok->str() == MatchCompiler::makeConstString("catch")) {
                    scopeList.emplace_back(*this, tok, scope, ScopeType::eCatch, scopeStartTok);
                } else // if (tok->str() == MatchCompiler::makeConstString("switch"))
                    scopeList.emplace_back(*this, tok, scope, ScopeType::eSwitch, scopeStartTok);

                scope->nestedList.push_back(&scopeList.back());
                scope = &scopeList.back();
                if (scope->type == ScopeType::eFor)
                    scope->checkVariable(tok->tokAt(2), AccessControl::Local); // check for variable declaration and add it to new scope if found
                else if (scope->type == ScopeType::eCatch)
                    scope->checkVariable(tok->tokAt(2), AccessControl::Throw); // check for variable declaration and add it to new scope if found
                tok = tok->next();
                inIfCondition.push(scopeStartTok);
            } else if (match51(tok)) {
                endInitList.emplace(tok->linkAt(1), scope);
                tok = tok->next();
            } else if (const Token *lambdaEndToken = findLambdaEndToken(tok)) {
                tok = addLambda(tok, lambdaEndToken);
            } else if (tok->str() == MatchCompiler::makeConstString("{")) {
                if (inInitList()) {
                    endInitList.emplace(tok->link(), scope);
                } else if (!inIfCondition.empty() && tok == inIfCondition.top()) {
                    inIfCondition.pop();
                } else if (isExecutableScope(tok)) {
                    scopeList.emplace_back(*this, tok, scope, ScopeType::eUnconditional, tok);
                    scope->nestedList.push_back(&scopeList.back());
                    scope = &scopeList.back();
                } else {
                    endInitList.emplace(tok->link(), scope);
                }
            } else if (match52(tok)) {
                const Token * ftok = tok->next();
                while (match53(ftok))
                    ftok = ftok->next();
                if (!ftok || ftok->str() != MatchCompiler::makeConstString("("))
                    continue;
                ftok = ftok->previous();
                if (match30(ftok->linkAt(1))) {
                    const Token *funcStart = nullptr;
                    const Token *argStart = nullptr;
                    const Token *declEnd = nullptr;
                    if (isFunction(ftok, scope, funcStart, argStart, declEnd)) {
                        if (declEnd && declEnd->str() == MatchCompiler::makeConstString(";")) {
                            bool newFunc = true; // Is this function already in the database?
                            auto range = scope->functionMap.equal_range(ftok->str());
                            for (std::multimap<std::string, const Function*>::const_iterator it = range.first; it != range.second; ++it) {
                                if (it->second->argsMatch(scope, it->second->argDef, argStart, emptyString, 0)) {
                                    newFunc = false;
                                    break;
                                }
                            }
                            // save function prototype in database
                            if (newFunc) {
                                Function function(ftok, scope, funcStart, argStart);
                                if (function.isExtern()) {
                                    scope->addFunction(std::move(function));
                                    tok = declEnd;
                                }
                            }
                        }
                    }
                }
            }
            // syntax error?
            if (!scope)
                mTokenizer.syntaxError(tok);
            // End of scope or list should be handled above
            if (tok->str() == MatchCompiler::makeConstString("}"))
                mTokenizer.syntaxError(tok);
        }
    }
}

void SymbolDatabase::createSymbolDatabaseClassInfo()
{
    if (mTokenizer.isC())
        return;

    // fill in using info
    for (Scope& scope : scopeList) {
        for (Scope::UsingInfo& usingInfo : scope.usingList) {
            // only find if not already found
            if (usingInfo.scope == nullptr) {
                // check scope for match
                const Scope * const found = findScope(usingInfo.start->tokAt(2), &scope);
                if (found) {
                    // set found scope
                    usingInfo.scope = found;
                    break;
                }
            }
        }
    }

    // fill in base class info
    for (Type& type : typeList) {
        // finish filling in base class info
        for (Type::BaseInfo & i : type.derivedFrom) {
            const Type* found = findType(i.nameTok, type.enclosingScope, /*lookOutside*/ true);
            if (found && found->findDependency(&type)) {
                // circular dependency
                //mTokenizer.syntaxError(nullptr);
            } else {
                i.type = found;
            }
        }
    }

    // fill in friend info
    for (Type & type : typeList) {
        for (Type::FriendInfo &friendInfo : type.friendList) {
            friendInfo.type = findType(friendInfo.nameStart, type.enclosingScope);
        }
    }
}


void SymbolDatabase::createSymbolDatabaseVariableInfo()
{
    // fill in variable info
    for (Scope& scope : scopeList) {
        // find variables
        scope.getVariableList();
    }

    // fill in function arguments
    for (Scope& scope : scopeList) {
        for (auto func = scope.functionList.begin(); func != scope.functionList.end(); ++func) {
            // add arguments
            func->addArguments(&scope);
        }
    }
}

void SymbolDatabase::createSymbolDatabaseCopyAndMoveConstructors()
{
    // fill in class and struct copy/move constructors
    for (Scope& scope : scopeList) {
        if (!scope.isClassOrStruct())
            continue;

        for (auto func = scope.functionList.begin(); func != scope.functionList.end(); ++func) {
            if (!func->isConstructor() || func->minArgCount() != 1)
                continue;

            const Variable* firstArg = func->getArgumentVar(0);
            if (firstArg->type() == scope.definedType) {
                if (firstArg->isRValueReference())
                    func->type = FunctionType::eMoveConstructor;
                else if (firstArg->isReference() && !firstArg->isPointer())
                    func->type = FunctionType::eCopyConstructor;
            }

            if (func->type == FunctionType::eCopyConstructor ||
                func->type == FunctionType::eMoveConstructor)
                scope.numCopyOrMoveConstructors++;
        }
    }
}

void SymbolDatabase::createSymbolDatabaseFunctionScopes()
{
    // fill in function scopes
    for (const Scope & scope : scopeList) {
        if (scope.type == ScopeType::eFunction)
            functionScopes.push_back(&scope);
    }
}

void SymbolDatabase::createSymbolDatabaseClassAndStructScopes()
{
    // fill in class and struct scopes
    for (const Scope& scope : scopeList) {
        if (scope.isClassOrStruct())
            classAndStructScopes.push_back(&scope);
    }
}

void SymbolDatabase::createSymbolDatabaseFunctionReturnTypes()
{
    // fill in function return types
    for (Scope& scope : scopeList) {
        for (auto func = scope.functionList.begin(); func != scope.functionList.end(); ++func) {
            // add return types
            if (func->retDef) {
                const Token *type = func->retDef;
                while (match54(type))
                    type = type->next();
                if (type) {
                    func->retType = findVariableTypeInBase(&scope, type);
                    if (!func->retType)
                        func->retType = findTypeInNested(type, func->nestedIn);
                }
            }
        }
    }
}

void SymbolDatabase::createSymbolDatabaseNeedInitialization()
{
    if (mTokenizer.isC()) {
        // For C code it is easy, as there are no constructors and no default values
        for (const Scope& scope : scopeList) {
            if (scope.definedType)
                scope.definedType->needInitialization = Type::NeedInitialization::True;
        }
    } else {
        // For C++, it is more difficult: Determine if user defined type needs initialization...
        unsigned int unknowns = 0; // stop checking when there are no unknowns
        unsigned int retry = 0;    // bail if we don't resolve all the variable types for some reason

        do {
            unknowns = 0;

            for (Scope& scope : scopeList) {
                if (!scope.isClassOrStructOrUnion())
                    continue;
                if (scope.classDef && match55(scope.classDef->previous())) // skip uninstantiated template
                    continue;

                if (!scope.definedType) {
                    mBlankTypes.emplace_back();
                    scope.definedType = &mBlankTypes.back();
                }

                if (scope.isClassOrStruct() && scope.definedType->needInitialization == Type::NeedInitialization::Unknown) {
                    // check for default constructor
                    bool hasDefaultConstructor = false;

                    for (const Function& func : scope.functionList) {
                        if (func.type == FunctionType::eConstructor) {
                            // check for no arguments: func ( )
                            if (func.argCount() == 0) {
                                hasDefaultConstructor = true;
                                break;
                            }

                            /** check for arguments with default values */
                            if (func.argCount() == func.initializedArgCount()) {
                                hasDefaultConstructor = true;
                                break;
                            }
                        }
                    }

                    // User defined types with user defined default constructor doesn't need initialization.
                    // We assume the default constructor initializes everything.
                    // Another check will figure out if the constructor actually initializes everything.
                    if (hasDefaultConstructor)
                        scope.definedType->needInitialization = Type::NeedInitialization::False;

                    // check each member variable to see if it needs initialization
                    else {
                        bool needInitialization = false;
                        bool unknown = false;

                        for (const Variable& var: scope.varlist) {
                            if (var.isStatic())
                                continue;
                            if (var.isClass() && !var.isReference()) {
                                if (var.type()) {
                                    // does this type need initialization?
                                    if (var.type()->needInitialization == Type::NeedInitialization::True && !var.hasDefault() && !var.isStatic())
                                        needInitialization = true;
                                    else if (var.type()->needInitialization == Type::NeedInitialization::Unknown) {
                                        if (!(var.valueType() && var.valueType()->type == ValueType::CONTAINER))
                                            unknown = true;
                                    }
                                }
                            } else if (!var.hasDefault()) {
                                needInitialization = true;
                                break;
                            }
                        }

                        if (needInitialization)
                            scope.definedType->needInitialization = Type::NeedInitialization::True;
                        else if (!unknown)
                            scope.definedType->needInitialization = Type::NeedInitialization::False;
                        else {
                            if (scope.definedType->needInitialization == Type::NeedInitialization::Unknown)
                                unknowns++;
                        }
                    }
                } else if (scope.type == ScopeType::eUnion && scope.definedType->needInitialization == Type::NeedInitialization::Unknown)
                    scope.definedType->needInitialization = Type::NeedInitialization::True;
            }

            retry++;
        } while (unknowns && retry < 100);

        // this shouldn't happen so output a debug warning
        if (retry == 100 && mSettings.debugwarnings) {
            for (const Scope& scope : scopeList) {
                if (scope.isClassOrStruct() && scope.definedType->needInitialization == Type::NeedInitialization::Unknown)
                    debugMessage(scope.classDef, "debug", "SymbolDatabase couldn't resolve all user defined types.");
            }
        }
    }
}

void SymbolDatabase::createSymbolDatabaseVariableSymbolTable()
{
    // create variable symbol table
    mVariableList.resize(mTokenizer.varIdCount() + 1);
    std::fill_n(mVariableList.begin(), mVariableList.size(), nullptr);

    // check all scopes for variables
    for (Scope& scope : scopeList) {
        // add all variables
        for (Variable& var: scope.varlist) {
            const int varId = var.declarationId();
            if (varId)
                mVariableList[varId] = &var;
            // fix up variables without type
            if (!var.type() && !var.typeStartToken()->isStandardType()) {
                const Type *type = findType(var.typeStartToken(), &scope);
                if (type)
                    var.type(type);
            }
        }

        // add all function parameters
        for (Function& func : scope.functionList) {
            for (Variable& arg: func.argumentList) {
                // check for named parameters
                if (arg.nameToken() && arg.declarationId()) {
                    const int declarationId = arg.declarationId();
                    mVariableList[declarationId] = &arg;
                    // fix up parameters without type
                    if (!arg.type() && !arg.typeStartToken()->isStandardType()) {
                        const Type *type = findTypeInNested(arg.typeStartToken(), &scope);
                        if (type)
                            arg.type(type);
                    }
                }
            }
        }
    }

    // fill in missing variables if possible
    for (const Scope *func: functionScopes) {
        for (const Token *tok = func->bodyStart->next(); tok && tok != func->bodyEnd; tok = tok->next()) {
            // check for member variable
            if (!match56(tok))
                continue;
            const Token* tokDot = tok->next();
            while (match13(tokDot))
                tokDot = tokDot->link()->next();
            if (!match57(tokDot))
                continue;
            const Token *member = tokDot->next();
            if (mVariableList[member->varId()] == nullptr) {
                const Variable *var1 = mVariableList[tok->varId()];
                if (var1 && var1->typeScope()) {
                    const Variable* memberVar = var1->typeScope()->getVariable(member->str());
                    if (memberVar) {
                        // add this variable to the look up table
                        mVariableList[member->varId()] = memberVar;
                    }
                }
            }
        }
    }
}

void SymbolDatabase::createSymbolDatabaseSetScopePointers()
{
    auto setScopePointers = [](const Scope &scope, const Token *bodyStart, const Token *bodyEnd) {
        assert(bodyStart);
        assert(bodyEnd);

        const_cast<Token *>(bodyEnd)->scope(&scope);

        for (auto* tok = const_cast<Token *>(bodyStart); tok != bodyEnd; tok = tok->next()) {
            if (bodyStart != bodyEnd && tok->str() == MatchCompiler::makeConstString("{")) {
                bool isEndOfScope = false;
                for (Scope* innerScope: scope.nestedList) {
                    const auto &list = innerScope->bodyStartList;
                    if (std::find(list.cbegin(), list.cend(), tok) != list.cend()) {     // Is begin of inner scope
                        tok = tok->link();
                        if (tok->next() == bodyEnd || !tok->next()) {
                            isEndOfScope = true;
                            break;
                        }
                        tok = tok->next();
                        break;
                    }
                }
                if (isEndOfScope)
                    break;
            }
            tok->scope(&scope);
        }
    };

    // Set scope pointers
    for (const Scope& scope: scopeList) {
        if (scope.type == ScopeType::eGlobal)
            setScopePointers(scope, mTokenizer.list.front(), mTokenizer.list.back());
        else {
            for (const Token *bodyStart: scope.bodyStartList)
                setScopePointers(scope, bodyStart, bodyStart->link());
        }
    }
}

void SymbolDatabase::createSymbolDatabaseSetFunctionPointers(bool firstPass)
{
    if (firstPass) {
        // Set function definition and declaration pointers
        for (const Scope& scope: scopeList) {
            for (const Function& func: scope.functionList) {
                if (func.tokenDef)
                    const_cast<Token *>(func.tokenDef)->function(&func);

                if (func.token)
                    const_cast<Token *>(func.token)->function(&func);
            }
        }
    }

    // Set function call pointers
    const Token* inTemplateArg = nullptr;
    for (Token* tok = mTokenizer.list.front(); tok != mTokenizer.list.back(); tok = tok->next()) {
        if (inTemplateArg == nullptr && tok->link() && tok->str() == MatchCompiler::makeConstString("<"))
            inTemplateArg = tok->link();
        if (inTemplateArg == tok)
            inTemplateArg = nullptr;
        if (tok->isName() && !tok->function() && tok->varId() == 0 && ((tok->astParent() && tok->astParent()->isComparisonOp()) || match58(tok)) && !isReservedName(tok)) {
            if (tok->strAt(1) == MatchCompiler::makeConstString(">") && !tok->linkAt(1))
                continue;

            const Function *function = findFunction(tok);
            if (!function || (inTemplateArg && function->isConstructor()))
                continue;

            tok->function(function);

            if (tok->strAt(1) != MatchCompiler::makeConstString("("))
                const_cast<Function *>(function)->functionPointerUsage = tok;
        }
    }

    // Set C++ 11 delegate constructor function call pointers
    for (const Scope& scope: scopeList) {
        for (const Function& func: scope.functionList) {
            // look for initializer list
            if (func.isConstructor() && func.functionScope && func.functionScope->functionOf && func.arg) {
                const Token * tok = func.arg->link()->next();
                if (tok->str() == MatchCompiler::makeConstString("noexcept")) {
                    const Token * closingParenTok = tok->linkAt(1);
                    if (!closingParenTok || !closingParenTok->next()) {
                        continue;
                    }
                    tok = closingParenTok->next();
                }
                if (tok->str() != MatchCompiler::makeConstString(":")) {
                    continue;
                }
                tok = tok->next();
                while (tok && tok != func.functionScope->bodyStart) {
                    if (match59(tok)) {
                        if (tok->str() == func.tokenDef->str()) {
                            const Function *function = func.functionScope->functionOf->findFunction(tok);
                            if (function)
                                const_cast<Token *>(tok)->function(function);
                            break;
                        }
                        tok = tok->linkAt(1);
                    }
                    tok = tok->next();
                }
            }
        }
    }
}

void SymbolDatabase::createSymbolDatabaseSetTypePointers()
{
    std::unordered_set<std::string> typenames;
    for (const Type &t : typeList) {
        typenames.insert(t.name());
    }

    // Set type pointers
    for (Token* tok = mTokenizer.list.front(); tok != mTokenizer.list.back(); tok = tok->next()) {
        if (!tok->isName() || tok->varId() || tok->function() || tok->type() || tok->enumerator())
            continue;

        if (match60(tok->next()))
            continue;

        if (typenames.find(tok->str()) == typenames.end())
            continue;

        const Type *type = findVariableType(tok->scope(), tok);
        if (type)
            tok->type(type);
    }
}

void SymbolDatabase::createSymbolDatabaseSetSmartPointerType()
{
    for (Scope &scope: scopeList) {
        for (Variable &var: scope.varlist) {
            if (var.valueType() && var.valueType()->smartPointerTypeToken && !var.valueType()->smartPointerType) {
                ValueType vt(*var.valueType());
                vt.smartPointerType = vt.smartPointerTypeToken->type();
                var.setValueType(vt);
            }
        }
    }
}

void SymbolDatabase::fixVarId(VarIdMap & varIds, const Token * vartok, Token * membertok, const Variable * membervar)
{
    auto varId = varIds.find(vartok->varId());
    if (varId == varIds.end()) {
        MemberIdMap memberId;
        if (membertok->varId() == 0) {
            memberId[membervar->nameToken()->varId()] = mTokenizer.newVarId();
            mVariableList.push_back(membervar);
        } else
            mVariableList[membertok->varId()] = membervar;
        varIds.emplace(vartok->varId(), memberId);
        varId = varIds.find(vartok->varId());
    }
    auto memberId = utils::as_const(varId->second).find(membervar->nameToken()->varId());
    if (memberId == varId->second.cend()) {
        if (membertok->varId() == 0) {
            varId->second.emplace(membervar->nameToken()->varId(), mTokenizer.newVarId());
            mVariableList.push_back(membervar);
            memberId = varId->second.find(membervar->nameToken()->varId());
        } else
            mVariableList[membertok->varId()] = membervar;
    }
    if (membertok->varId() == 0)
        membertok->varId(memberId->second);
}

static bool isContainerYieldElement(Library::Container::Yield yield);

void SymbolDatabase::createSymbolDatabaseSetVariablePointers()
{
    VarIdMap varIds;

    auto setMemberVar = [&](const Variable* membervar, Token* membertok, const Token* vartok) -> void {
        if (membervar) {
            membertok->variable(membervar);
            if (vartok && (membertok->varId() == 0 || mVariableList[membertok->varId()] == nullptr))
                fixVarId(varIds, vartok, membertok, membervar);
        }
    };

    // Set variable pointers
    for (Token* tok = mTokenizer.list.front(); tok != mTokenizer.list.back(); tok = tok->next()) {
        if (!tok->isName() || tok->isKeyword() || tok->isStandardType())
            continue;
        if (tok->varId())
            tok->variable(getVariableFromVarId(tok->varId()));

        // Set Token::variable pointer for array member variable
        // Since it doesn't point at a fixed location it doesn't have varid
        const bool isVar = tok->variable() && (tok->variable()->typeScope() || tok->variable()->isSmartPointer() ||
                                               (tok->valueType() && (tok->valueType()->type == ValueType::CONTAINER || tok->valueType()->type == ValueType::ITERATOR)));
        const bool isArrayAccess = isVar && match13(tok->astParent());
        const bool isDirectAccess = isVar && !isArrayAccess && match61(tok->astParent());
        const bool isDerefAccess = isVar && !isDirectAccess && match62(tok->astParent()) && match61(tok->astParent()->astParent());
        if (isVar && (isArrayAccess || isDirectAccess || isDerefAccess)) {
            Token* membertok{};
            if (isArrayAccess) {
                membertok = tok->astParent();
                while (match13(membertok))
                    membertok = membertok->astParent();
                if (membertok)
                    membertok = membertok->astOperand2();
            }
            else if (isDirectAccess) {
                membertok = tok->astParent()->astOperand2();
                if (membertok == tok) {
                    Token* gptok = tok->astParent()->astParent();
                    if (match61(gptok)) // chained access
                        membertok = gptok->astOperand2();
                    else if (match13(gptok) && match61(gptok->astParent()))
                        membertok = gptok->astParent()->astOperand2();
                }
            }
            else { // isDerefAccess
                membertok = tok->astParent();
                while (match62(membertok))
                    membertok = membertok->astParent();
                if (membertok)
                    membertok = membertok->astOperand2();
            }

            if (membertok && membertok != tok) {
                const Variable *var = tok->variable();
                if (var->typeScope()) {
                    const Variable *membervar = var->typeScope()->getVariable(membertok->str());
                    setMemberVar(membervar, membertok, tok);
                } else if (const ::Type *type = var->smartPointerType()) {
                    const Scope *classScope = type->classScope;
                    const Variable *membervar = classScope ? classScope->getVariable(membertok->str()) : nullptr;
                    setMemberVar(membervar, membertok, tok);
                } else if (tok->valueType() && tok->valueType()->type == ValueType::CONTAINER) {
                    if (const Token* ctt = tok->valueType()->containerTypeToken) {
                        while (ctt && ctt->isKeyword())
                            ctt = ctt->next();
                        const Type* ct = findTypeInNested(ctt, tok->scope());
                        if (ct && ct->classScope && ct->classScope->definedType) {
                            const Variable *membervar = ct->classScope->getVariable(membertok->str());
                            setMemberVar(membervar, membertok, tok);
                        }
                    }
                } else if (const Type* iterType = var->iteratorType()) {
                    if (iterType->classScope && iterType->classScope->definedType) {
                        const Variable *membervar = iterType->classScope->getVariable(membertok->str());
                        setMemberVar(membervar, membertok, tok);
                    }
                }
            }
        }

        // check for function returning record type
        // func(...).var
        // func(...)[...].var
        else if (tok->function() && tok->strAt(1) == MatchCompiler::makeConstString("(") &&
                 (match63(tok->linkAt(1)) ||
                  (match64(tok->linkAt(1)) && match65(tok->linkAt(1)->linkAt(1))))) {
            const Type *type = tok->function()->retType;
            Token* membertok;
            if (tok->linkAt(1)->strAt(1) == MatchCompiler::makeConstString("."))
                membertok = tok->linkAt(1)->tokAt(2);
            else
                membertok = tok->linkAt(1)->linkAt(1)->tokAt(2);
            if (type) {
                const Variable *membervar = membertok->variable();
                if (!membervar) {
                    if (type->classScope) {
                        membervar = type->classScope->getVariable(membertok->str());
                        setMemberVar(membervar, membertok, tok->function()->retDef);
                    }
                }
            } else if (mSettings.library.detectSmartPointer(tok->function()->retDef)) {
                if (const Token* templateArg = findmatch66(tok->function()->retDef) ) {
                    if (const Type* spType = findTypeInNested(templateArg->next(), tok->scope())) {
                        if (spType->classScope) {
                            const Variable* membervar = spType->classScope->getVariable(membertok->str());
                            setMemberVar(membervar, membertok, tok->function()->retDef);
                        }
                    }
                }
            }
        }
        else if (match61(tok->astParent()) && tok->strAt(1) == MatchCompiler::makeConstString("(") &&
                 astIsContainer(tok->astParent()->astOperand1()) && match63(tok->linkAt(1))) {
            const ValueType* vt = tok->astParent()->astOperand1()->valueType();
            const Library::Container* cont = vt->container;
            auto it = cont->functions.find(tok->str());
            if (it != cont->functions.end() && isContainerYieldElement(it->second.yield) && vt->containerTypeToken) {
                Token* memberTok = tok->linkAt(1)->tokAt(2);
                const Scope* scope = vt->containerTypeToken->scope();
                const Type* contType{};
                const std::string& typeStr = vt->containerTypeToken->str(); // TODO: handle complex type expressions
                while (scope && !contType) {
                    contType = scope->findType(typeStr); // find the type stored in the container
                    scope = scope->nestedIn;
                }
                if (contType && contType->classScope) {
                    const Variable* membervar = contType->classScope->getVariable(memberTok->str());
                    setMemberVar(membervar, memberTok, vt->containerTypeToken);
                }
            }
        }
    }
}

void SymbolDatabase::createSymbolDatabaseEnums()
{
    // fill in enumerators in enum
    for (const Scope &scope : scopeList) {
        if (scope.type != ScopeType::eEnum)
            continue;

        // add enumerators to enumerator tokens
        for (const Enumerator & i : scope.enumeratorList)
            const_cast<Token *>(i.name)->enumerator(&i);
    }

    std::set<std::string> tokensThatAreNotEnumeratorValues;

    for (const Scope &scope : scopeList) {
        if (scope.type != ScopeType::eEnum)
            continue;

        for (const Enumerator & enumerator : scope.enumeratorList) {
            // look for initialization tokens that can be converted to enumerators and convert them
            if (enumerator.start) {
                if (!enumerator.end)
                    mTokenizer.syntaxError(enumerator.start);
                for (const Token * tok3 = enumerator.start; tok3 && tok3 != enumerator.end->next(); tok3 = tok3->next()) {
                    if (tok3->tokType() == Token::eName) {
                        const Enumerator * e = findEnumerator(tok3, tokensThatAreNotEnumeratorValues);
                        if (e)
                            const_cast<Token *>(tok3)->enumerator(e);
                    }
                }
            }
        }
    }

    // find enumerators
    for (Token* tok = mTokenizer.list.front(); tok != mTokenizer.list.back(); tok = tok->next()) {
        const bool isVariable = (tok->tokType() == Token::eVariable && !tok->variable());
        if (tok->tokType() != Token::eName && !isVariable)
            continue;
        const Enumerator * enumerator = findEnumerator(tok, tokensThatAreNotEnumeratorValues);
        if (enumerator) {
            if (isVariable)
                tok->varId(0);
            tok->enumerator(enumerator);
        }
    }
}

void SymbolDatabase::createSymbolDatabaseIncompleteVars()
{
    for (Token* tok = mTokenizer.list.front(); tok != mTokenizer.list.back(); tok = tok->next()) {
        const Scope * scope = tok->scope();
        if (!scope)
            continue;
        if (!scope->isExecutable())
            continue;
        if (tok->varId() != 0)
            continue;
        if (tok->isCast() && !isCPPCast(tok) && tok->link() && tok->str() == MatchCompiler::makeConstString("(")) {
            tok = tok->link();
            continue;
        }
        if (tok->isCpp()) {
            if (match67(tok) ||
                match68(tok)) {
                tok = tok->linkAt(1);
                continue;
            }
            if (tok->str() == MatchCompiler::makeConstString("using")) {
                tok = findmatch69(tok) ;
                continue;
            }
        }
        if (tok->str() == MatchCompiler::makeConstString("NULL"))
            continue;
        if (tok->isKeyword() || !tok->isNameOnly())
            continue;
        if (tok->type())
            continue;
        if (match70(tok->next()))
            continue;
        if (match71(tok->next()))
            continue;
        // Very likely a typelist
        if (match72(tok->tokAt(-2)) || match73(tok->next()))
            continue;
        // Inside template brackets
        if (match60(tok->next()) && tok->linkAt(1)) {
            tok = tok->linkAt(1);
            continue;
        }
        // Skip goto labels
        if (match74(tok->previous()))
            continue;
        std::string fstr = tok->str();
        const Token* ftok = tok->previous();
        while (match75(ftok)) {
            if (!match76(ftok->previous()))
                break;
            fstr.insert(0, ftok->strAt(-1) + "::");
            ftok = ftok->tokAt(-2);
        }
        if (mSettings.library.functions().find(fstr) != mSettings.library.functions().end())
            continue;
        if (tok->isCpp()) {
            const Token* parent = tok->astParent();
            while (match77(parent))
                parent = parent->astParent();
            if (match78(parent))
                continue;
            // trailing return type
            if (match61(ftok) && ftok->originalName() == MatchCompiler::makeConstString("->") && match79(ftok->tokAt(-1)))
                continue;
        }
        tok->isIncompleteVar(true);
    }
}

void SymbolDatabase::createSymbolDatabaseEscapeFunctions()
{
    for (const Scope& scope : scopeList) {
        if (scope.type != ScopeType::eFunction)
            continue;
        Function * function = scope.function;
        if (!function)
            continue;
        if (findmatch80(scope.bodyStart, scope.bodyEnd) )
            continue;
        function->isEscapeFunction(isReturnScope(scope.bodyEnd, mSettings.library, nullptr, true));
    }
}

static bool isExpression(const Token* tok)
{
    if (!tok)
        return false;
    if (match5(tok) && tok->scope() && tok->scope()->bodyStart != tok &&
        (tok->astOperand1() || tok->astOperand2()))
        return true;
    if (!match81(tok))
        return false;
    if (match82(tok)) {
        const Token* vartok = findAstNode(tok, [&](const Token* tok2) {
            const Variable* var = tok2->variable();
            if (!var)
                return false;
            return var->nameToken() == tok2;
        });
        if (vartok)
            return false;
    }
    return true;
}

static std::string getIncompleteNameID(const Token* tok)
{
    std::string result = tok->str() + "@";
    while (match83(tok->astParent()))
        tok = tok->astParent();
    return result + tok->expressionString();
}

namespace {
    struct ExprIdKey {
        std::string parentOp;
        nonneg int operand1;
        nonneg int operand2;
        bool operator<(const ExprIdKey& k) const {
            return std::tie(parentOp, operand1, operand2) < std::tie(k.parentOp, k.operand1, k.operand2);
        }
    };
    using ExprIdMap = std::map<ExprIdKey, nonneg int>;
    void setParentExprId(Token* tok, ExprIdMap& exprIdMap, nonneg int &id) {
        for (;;) {
            if (!tok->astParent() || tok->astParent()->isControlFlowKeyword())
                break;
            const Token* op1 = tok->astParent()->astOperand1();
            if (op1 && op1->exprId() == 0 && !match84(op1))
                break;
            const Token* op2 = tok->astParent()->astOperand2();
            if (op2 && op2->exprId() == 0 &&
                !((tok->astParent()->astParent() && tok->astParent()->isAssignmentOp() && tok->astParent()->astParent()->isAssignmentOp()) ||
                  isLambdaCaptureList(op2) ||
                  (op2->str() == MatchCompiler::makeConstString("(") && isLambdaCaptureList(op2->astOperand1())) ||
                  match85(op2) ||
                  (match13(tok->astParent()) && op2->str() == MatchCompiler::makeConstString("{"))))
                break;

            if (tok->astParent()->isExpandedMacro() || match86(tok->astParent())) {
                tok->astParent()->exprId(id);
                ++id;
                tok = tok->astParent();
                continue;
            }

            ExprIdKey key;
            key.parentOp = tok->astParent()->str();
            key.operand1 = op1 ? op1->exprId() : 0;
            key.operand2 = op2 ? op2->exprId() : 0;

            if (tok->astParent()->isCast() && tok->astParent()->str() == MatchCompiler::makeConstString("(")) {
                const Token* typeStartToken;
                const Token* typeEndToken;
                if (tok->astParent()->astOperand2()) {
                    typeStartToken = tok->astParent()->astOperand1();
                    typeEndToken = tok;
                } else {
                    typeStartToken = tok->astParent()->next();
                    typeEndToken = tok->astParent()->link();
                }
                std::string type;
                for (const Token* t = typeStartToken; precedes(t, typeEndToken); t = t->next()) {
                    type += " " + t->str();
                }
                key.parentOp += type;
            }

            for (const auto& ref: followAllReferences(op1)) {
                if (ref.token->exprId() != 0) { // cppcheck-suppress useStlAlgorithm
                    key.operand1 = ref.token->exprId();
                    break;
                }
            }
            for (const auto& ref: followAllReferences(op2)) {
                if (ref.token->exprId() != 0) { // cppcheck-suppress useStlAlgorithm
                    key.operand2 = ref.token->exprId();
                    break;
                }
            }

            if (key.operand1 > key.operand2 && key.operand2 &&
                match87(tok->astParent())) {
                // In C++ the order of operands of + might matter
                if (!tok->isCpp() ||
                    key.parentOp != MatchCompiler::makeConstString("+") ||
                    !tok->astParent()->valueType() ||
                    tok->astParent()->valueType()->isIntegral() ||
                    tok->astParent()->valueType()->isFloat() ||
                    tok->astParent()->valueType()->pointer > 0)
                    std::swap(key.operand1, key.operand2);
            }

            const auto it = exprIdMap.find(key);
            if (it == exprIdMap.end()) {
                exprIdMap[key] = id;
                tok->astParent()->exprId(id);
                ++id;
            } else {
                tok->astParent()->exprId(it->second);
            }
            tok = tok->astParent();
        }
    }
}

void SymbolDatabase::createSymbolDatabaseExprIds()
{
    // Find highest varId
    nonneg int maximumVarId = 0;
    for (const Token* tok = mTokenizer.list.front(); tok; tok = tok->next()) {
        maximumVarId = std::max(tok->varId(), maximumVarId);
    }
    nonneg int id = maximumVarId + 1;
    // Find incomplete vars that are used in constant context
    std::unordered_map<std::string, nonneg int> unknownConstantIds;
    const Token* inConstExpr = nullptr;
    for (const Token* tok = mTokenizer.list.front(); tok != mTokenizer.list.back(); tok = tok->next()) {
        if (match88(tok) && tok->linkAt(1)) {
            tok = tok->linkAt(1)->previous();
        } else if (tok == inConstExpr) {
            inConstExpr = nullptr;
        } else if (inConstExpr) {
            if (!tok->isIncompleteVar())
                continue;
            if (!isExpression(tok->astParent()))
                continue;
            const std::string& name = getIncompleteNameID(tok);
            if (unknownConstantIds.count(name) > 0)
                continue;
            unknownConstantIds[name] = id++;
        } else if (tok->link() && tok->str() == MatchCompiler::makeConstString("<")) {
            inConstExpr = tok->link();
        } else if (match89(tok) && tok->variable() && tok->variable()->nameToken() == tok) {
            inConstExpr = tok->linkAt(1);
        }
    }

    auto exprScopes = functionScopes; // functions + global lambdas + namespaces
    std::copy_if(scopeList.front().nestedList.begin(), scopeList.front().nestedList.end(), std::back_inserter(exprScopes), [](const Scope* scope) {
        return scope && (scope->type == ScopeType::eLambda || scope->type == ScopeType::eNamespace);
    });

    for (const Scope * scope : exprScopes) {
        std::unordered_map<std::string, nonneg int> unknownIds;
        // Assign IDs to incomplete vars which are part of an expression
        // Such variables should be assumed global
        for (auto* tok = const_cast<Token*>(scope->bodyStart); tok != scope->bodyEnd; tok = tok->next()) {
            if (!tok->isIncompleteVar())
                continue;
            if (!isExpression(tok->astParent()))
                continue;
            const std::string& name = getIncompleteNameID(tok);
            nonneg int sid = 0;
            if (unknownConstantIds.count(name) > 0) {
                sid = unknownConstantIds.at(name);
                tok->isIncompleteConstant(true);
            } else if (unknownIds.count(name) == 0) {
                sid = id++;
                unknownIds[name] = sid;
            } else {
                sid = unknownIds.at(name);
            }
            assert(sid > 0);
            tok->exprId(sid);
        }

        // Assign IDs
        ExprIdMap exprIdMap;
        std::map<std::string, std::pair<nonneg int, const Token*>> baseIds;
        for (auto* tok = const_cast<Token*>(scope->bodyStart); tok != scope->bodyEnd; tok = tok->next()) {
            if (tok->varId() > 0) {
                tok->exprId(tok->varId());
                if (tok->astParent() && tok->astParent()->exprId() == 0)
                    setParentExprId(tok, exprIdMap, id);
            } else if (tok->astParent() && !tok->astOperand1() && !tok->astOperand2()) {
                if (tok->tokType() == Token::Type::eBracket)
                    continue;
                if (tok->astParent()->str() == MatchCompiler::makeConstString("="))
                    continue;
                if (tok->isControlFlowKeyword())
                    continue;
                if (match90(tok->tokAt(-1)) && match91(tok->tokAt(-2))) // designated initializers
                    continue;

                if (match3(tok) && tok->linkAt(1)) {
                    tok->exprId(id);
                    ++id;
                } else {
                    const auto it = baseIds.find(tok->str());
                    if (it != baseIds.end() && compareTokenFlags(tok, it->second.second, /*macro*/ true)) {
                        tok->exprId(it->second.first);
                    } else {
                        baseIds[tok->str()] = { id, tok };
                        tok->exprId(id);
                        ++id;
                    }
                }

                setParentExprId(tok, exprIdMap, id);
            }
        }
        for (auto* tok = const_cast<Token*>(scope->bodyStart); tok != scope->bodyEnd; tok = tok->next()) {
            if (tok->varId() == 0 && tok->exprId() > 0 && tok->astParent() && !tok->astOperand1() && !tok->astOperand2()) {
                if (tok->isNumber() || tok->isKeyword() || match83(tok->astParent()) ||
                    (match29(tok->astParent()) && precedes(tok, tok->astParent())))
                    tok->exprId(0);
            }
        }
    }

    // Mark expressions that are unique
    std::vector<std::pair<Token*, int>> uniqueExprId(id);
    for (Token* tok = mTokenizer.list.front(); tok; tok = tok->next()) {
        const auto id2 = tok->exprId();
        if (id2 == 0 || id2 <= maximumVarId)
            continue;
        uniqueExprId[id2].first = tok;
        uniqueExprId[id2].second++;
    }
    for (const auto& p : uniqueExprId) {
        if (!p.first || p.second != 1)
            continue;
        if (p.first->variable()) {
            const Variable* var = p.first->variable();
            if (var->nameToken() != p.first)
                continue;
        }
        p.first->setUniqueExprId();
    }
}

// cppcheck-suppress functionConst - has side effects
void SymbolDatabase::setArrayDimensionsUsingValueFlow()
{
    // set all unknown array dimensions
    for (const Variable *var : mVariableList) {
        // check each array variable
        if (!var || !var->isArray())
            continue;
        // check each array dimension
        for (const Dimension &const_dimension : var->dimensions()) {
            auto &dimension = const_cast<Dimension &>(const_dimension);
            if (dimension.num != 0 || !dimension.tok)
                continue;

            if (match92(dimension.tok->previous())) {
                if (dimension.known)
                    continue;

                // In template arguments, there might not be AST
                // Determine size by using the "raw tokens"
                TokenList tokenList(mSettings, dimension.tok->isCpp() ? Standards::Language::CPP : Standards::Language::C);
                tokenList.addtoken(";", 0, 0, 0, false);
                bool fail = false;
                for (const Token *tok = dimension.tok; tok && !match93(tok); tok = tok->next()) {
                    if (!tok->isName())
                        tokenList.addtoken(tok->str(), 0, 0, 0, false);

                    else if (const ValueFlow::Value* v = tok->getKnownValue(ValueFlow::Value::ValueType::INT))
                        tokenList.addtoken(MathLib::toString(v->intvalue), 0, 0, 0, false);

                    else {
                        fail = true;
                        break;
                    }
                }

                if (fail)
                    continue;

                tokenList.addtoken(";", 0, 0, 0, false);

                for (Token *tok = tokenList.front(); tok;) {
                    if (TemplateSimplifier::simplifyNumericCalculations(tok, false))
                        tok = tokenList.front();
                    else
                        tok = tok->next();
                }

                if (match94(tokenList.front())) {
                    dimension.known = true;
                    dimension.num = MathLib::toBigNumber(tokenList.front()->tokAt(1));
                }

                continue;
            }

            // Normal array [..dimension..]
            dimension.known = false;

            // check for a single token dimension
            if (const ValueFlow::Value* v = dimension.tok->getKnownValue(ValueFlow::Value::ValueType::INT)) {
                dimension.known = true;
                dimension.num = v->intvalue;
                continue;
            }

            if (dimension.tok->valueType() && dimension.tok->valueType()->pointer == 0) {
                std::uint8_t bits = 0;
                switch (dimension.tok->valueType()->type) {
                case ValueType::Type::CHAR:
                    bits = mSettings.platform.char_bit;
                    break;
                case ValueType::Type::SHORT:
                    bits = mSettings.platform.short_bit;
                    break;
                case ValueType::Type::INT:
                    bits = mSettings.platform.int_bit;
                    break;
                case ValueType::Type::LONG:
                    bits = mSettings.platform.long_bit;
                    break;
                case ValueType::Type::LONGLONG:
                    bits = mSettings.platform.long_long_bit;
                    break;
                default:
                    break;
                }

                if (bits > 0 && bits <= 62) {
                    if (dimension.tok->valueType()->sign == ValueType::Sign::UNSIGNED)
                        dimension.num = 1LL << bits;
                    else
                        dimension.num = 1LL << (bits - 1);
                }
            }
        }
    }
}

SymbolDatabase::~SymbolDatabase()
{
    // Clear scope, type, function and variable pointers
    for (Token* tok = mTokenizer.list.front(); tok; tok = tok->next()) {
        tok->scope(nullptr);
        tok->type(nullptr);
        tok->function(nullptr);
        tok->variable(nullptr);
        tok->enumerator(nullptr);
        tok->setValueType(nullptr);
    }
}

bool SymbolDatabase::isFunction(const Token *tok, const Scope* outerScope, const Token *&funcStart, const Token *&argStart, const Token*& declEnd) const
{
    if (tok->varId())
        return false;

    // function returning function pointer? '... ( ... %name% ( ... ))( ... ) {'
    // function returning reference to array '... ( & %name% ( ... ))[ ... ] {'
    // TODO: Activate this again
    if ((false) && tok->str() == MatchCompiler::makeConstString("(") && tok->strAt(1) != MatchCompiler::makeConstString("*") && // NOLINT(readability-simplify-boolean-expr)
        (tok->link()->strAt(-1) == MatchCompiler::makeConstString(")") || match95(tok->link()->tokAt(-2)))) {
        const Token* tok2 = tok->link()->next();
        if (tok2 && tok2->str() == MatchCompiler::makeConstString("(") && match96(tok2->link()->next())) {
            const Token* argStartTok;
            if (tok->link()->strAt(-1) == MatchCompiler::makeConstString("const"))
                argStartTok = tok->link()->linkAt(-2);
            else
                argStartTok = tok->link()->linkAt(-1);
            funcStart = argStartTok->previous();
            argStart = argStartTok;
            declEnd = findmatch97(tok2->link()->next()) ;
            return true;
        }
        if (tok2 && tok2->str() == MatchCompiler::makeConstString("[")) {
            while (tok2 && tok2->str() == MatchCompiler::makeConstString("["))
                tok2 = tok2->link()->next();
            if (match96(tok2)) {
                const Token* argStartTok;
                if (tok->link()->strAt(-1) == MatchCompiler::makeConstString("const"))
                    argStartTok = tok->link()->linkAt(-2);
                else
                    argStartTok = tok->link()->linkAt(-1);
                funcStart = argStartTok->previous();
                argStart = argStartTok;
                declEnd = findmatch97(tok2) ;
                return true;
            }
        }
    }

    else if (!tok->isName() || !tok->next() || !tok->linkAt(1))
        return false;

    // regular function?
    else if (match98(tok) && !isReservedName(tok) && tok->previous() &&
             (match99(tok->previous()) || // Either a return type or scope qualifier in front of tok
              outerScope->isClassOrStructOrUnion())) { // or a ctor/dtor
        const Token* tok1 = tok->previous();
        const Token* tok2 = tok->linkAt(1)->next();

        if (!TokenList::isFunctionHead(tok->next(), ";:{"))
            return false;

        // skip over destructor "~"
        if (tok1->str() == MatchCompiler::makeConstString("~"))
            tok1 = tok1->previous();

        // skip over qualification
        while (match75(tok1)) {
            tok1 = tok1->previous();
            if (tok1 && tok1->isName())
                tok1 = tok1->previous();
            else if (tok1 && tok1->str() == MatchCompiler::makeConstString(">") && tok1->link() && match76(tok1->link()->previous()))
                tok1 = tok1->link()->tokAt(-2);
        }

        // skip over const, noexcept, throw, override, final and volatile specifiers
        while (match100(tok2)) {
            tok2 = tok2->next();
            if (tok2 && tok2->str() == MatchCompiler::makeConstString("("))
                tok2 = tok2->link()->next();
        }

        // skip over trailing return type
        bool hasTrailingRet = false;
        if (tok2 && tok2->str() == MatchCompiler::makeConstString(".")) {
            hasTrailingRet = true;
            for (tok2 = tok2->next(); tok2; tok2 = tok2->next()) {
                if (match101(tok2))
                    break;
                if (tok2->link() && match102(tok2))
                    tok2 = tok2->link();
            }
        }

        // done if constructor or destructor
        if (!match103(tok1) && tok1) {
            // skip over pointers and references
            while (match104(tok1) && !endsWith(tok1->str(), ':') && (!isReservedName(tok1) || tok1->str() == MatchCompiler::makeConstString("const")))
                tok1 = tok1->previous();

            // skip over decltype
            if (match105(tok1) && tok1->link() &&
                match37(tok1->link()->previous()))
                tok1 = tok1->link()->tokAt(-2);

            // skip over template
            if (tok1 && tok1->str() == MatchCompiler::makeConstString(">")) {
                if (tok1->link())
                    tok1 = tok1->link()->previous();
                else
                    return false;
            }

            // function can't have number or variable as return type
            if (tok1 && (tok1->isNumber() || tok1->varId()))
                return false;

            // skip over return type
            if (tok1 && tok1->isName()) {
                if (tok1->str() == MatchCompiler::makeConstString("return"))
                    return false;
                if (tok1->str() != MatchCompiler::makeConstString("friend"))
                    tok1 = tok1->previous();
            }

            // skip over qualification
            while (match75(tok1)) {
                tok1 = tok1->previous();
                if (tok1 && tok1->isName())
                    tok1 = tok1->previous();
                else if (tok1 && tok1->str() == MatchCompiler::makeConstString(">") && tok1->link() && match76(tok1->link()->previous()))
                    tok1 = tok1->link()->tokAt(-2);
                else if (match105(tok1) && tok1->link() &&
                         match37(tok1->link()->previous()))
                    tok1 = tok1->link()->tokAt(-2);
            }

            // skip over modifiers and other stuff
            while (match106(tok1)) {
                // friend type func(); is not a function
                if (tok1->isCpp() && tok1->str() == MatchCompiler::makeConstString("friend") && tok2->str() == MatchCompiler::makeConstString(";"))
                    return false;
                tok1 = tok1->previous();
            }

            // should be at a sequence point if this is a function
            if (!match107(tok1) && tok1)
                return false;
        }

        if (tok2 &&
            (match108(tok2) ||
             (tok2->isUpperCaseName() && match109(tok2)) ||
             (tok2->isUpperCaseName() && match24(tok2) && tok2->linkAt(1)->strAt(1) == MatchCompiler::makeConstString("{")) ||
             match110(tok2) ||
             match111(tok2) ||
             match112(tok2) ||
             (hasTrailingRet && match113(tok2)))) {
            funcStart = tok;
            argStart = tok->next();
            declEnd = findmatch97(tok2) ;
            return true;
        }
    }

    // UNKNOWN_MACRO(a,b) { ... }
    else if (outerScope->type == ScopeType::eGlobal &&
             match24(tok) &&
             tok->isUpperCaseName() &&
             match32(tok->linkAt(1)) &&
             (!tok->previous() || match114(tok->previous()))) {
        funcStart = tok;
        argStart = tok->next();
        declEnd = tok->linkAt(1)->next();
        return true;
    }

    // template constructor?
    else if (match3(tok) && match115(tok->linkAt(1))) {
        if (tok->isKeyword() || tok->isStandardType() || !outerScope->isClassOrStructOrUnion())
            return false;
        const Token* tok2 = tok->linkAt(1)->linkAt(1);
        if (match116(tok2) ||
            match117(tok2) ||
            match118(tok2)) {
            funcStart = tok;
            argStart = tok2->link();
            declEnd = findmatch97(tok2->next()) ;
            return true;
        }
    }

    // regular C function with missing return or invalid C++ ?
    else if (match24(tok) && !isReservedName(tok) &&
             match32(tok->linkAt(1)) &&
             (!tok->previous() || match119(tok->previous()))) {
        if (tok->isC()) {
            returnImplicitIntError(tok);
            funcStart = tok;
            argStart = tok->next();
            declEnd = tok->linkAt(1)->next();
            return true;
        }
        mTokenizer.syntaxError(tok);
    }

    return false;
}

void SymbolDatabase::validateExecutableScopes() const
{
    const std::size_t functions = functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope* const scope = functionScopes[i];
        const Function* const function = scope->function;
        if (scope->isExecutable() && !function) {
            const std::list<const Token*> callstack(1, scope->classDef);
            const std::string msg = std::string("Executable scope '") + scope->classDef->str() + "' with unknown function.";
            const ErrorMessage errmsg(callstack, &mTokenizer.list, Severity::debug,
                                      "symbolDatabaseWarning",
                                      msg,
                                      Certainty::normal);
            mErrorLogger.reportErr(errmsg);
        }
    }
}

namespace {
    const Function* getFunctionForArgumentvariable(const Variable * const var)
    {
        if (const Scope* scope = var->nameToken()->scope()) {
            auto it = std::find_if(scope->functionList.begin(), scope->functionList.end(), [&](const Function& function) {
                for (nonneg int arg = 0; arg < function.argCount(); ++arg) {
                    if (var == function.getArgumentVar(arg))
                        return true;
                }
                return false;
            });
            if (it != scope->functionList.end())
                return &*it;
        }
        return nullptr;
    }
}

void SymbolDatabase::validateVariables() const
{
    for (auto iter = mVariableList.cbegin(); iter!=mVariableList.cend(); ++iter) {
        const Variable * const var = *iter;
        if (var) {
            if (!var->scope()) {
                const Function* function = getFunctionForArgumentvariable(var);
                if (!var->isArgument() || (!function || function->hasBody())) { // variables which only appear in a function declaration do not have a scope
                    throw InternalError(var->nameToken(), "Analysis failed (variable without scope). If the code is valid then please report this failure.", InternalError::INTERNAL);
                }
            }
        }
    }
}

bool SymbolDatabase::isVariableWithoutSideEffects(const Variable& var, const Type* type) const
{
    const Type* variableType = var.type();
    if (variableType && variableType != type) {
        if (!isRecordTypeWithoutSideEffects(variableType))
            return false;
    }
    else {
        if (!var.valueType())
            return false;
        const ValueType::Type valueType = var.valueType()->type;
        if ((valueType == ValueType::Type::UNKNOWN_TYPE) || (valueType == ValueType::Type::NONSTD))
            return false;
    }

    return true;
}

bool SymbolDatabase::isFunctionWithoutSideEffects(const Function& func, const Token* functionUsageToken, std::list<const Function*> checkedFuncs) const
{
    // no body to analyze
    if (!func.hasBody()) {
        return false;
    }

    for (const Token* argsToken = functionUsageToken->next(); !match105(argsToken); argsToken = argsToken->next()) {
        const Variable* argVar = argsToken->variable();
        if (argVar && argVar->isGlobal()) {
            return false; // TODO: analyze global variable usage
        }
    }

    bool sideEffectReturnFound = false;
    std::set<const Variable*> pointersToGlobals;
    for (const Token* bodyToken = func.functionScope->bodyStart->next(); bodyToken != func.functionScope->bodyEnd;
         bodyToken = bodyToken->next()) {
        // check variable inside function body
        const Variable* bodyVariable = bodyToken->variable();
        if (bodyVariable) {
            if (!isVariableWithoutSideEffects(*bodyVariable)) {
                return false;
            }
            // check if global variable is changed
            if (bodyVariable->isGlobal() || (pointersToGlobals.find(bodyVariable) != pointersToGlobals.end())) {
                const int indirect = bodyVariable->isArray() ? bodyVariable->dimensions().size() : bodyVariable->isPointer();
                if (isVariableChanged(bodyToken, indirect, mSettings)) {
                    return false;
                }
                // check if pointer to global variable assigned to another variable (another_var = &global_var)
                if (match120(bodyToken->tokAt(-1)) && match121(bodyToken->tokAt(-2))) {
                    const Token* assigned_var_token = bodyToken->tokAt(-3);
                    if (assigned_var_token && assigned_var_token->variable()) {
                        pointersToGlobals.insert(assigned_var_token->variable());
                    }
                }
            }
        }

        // check nested function
        const Function* bodyFunction = bodyToken->function();
        if (bodyFunction) {
            if (std::find(checkedFuncs.cbegin(), checkedFuncs.cend(), bodyFunction) != checkedFuncs.cend()) { // recursion found
                continue;
            }
            checkedFuncs.push_back(bodyFunction);
            if (!isFunctionWithoutSideEffects(*bodyFunction, bodyToken, checkedFuncs)) {
                return false;
            }
        }

        // check returned value
        if (match122(bodyToken)) {
            const Token* returnValueToken = bodyToken->next();
            // TODO: handle complex return expressions
            if (!match26(returnValueToken->next())) {
                sideEffectReturnFound = true;
                continue;
            }
            // simple one-token return
            const Variable* returnVariable = returnValueToken->variable();
            if (returnValueToken->isLiteral() ||
                (returnVariable && isVariableWithoutSideEffects(*returnVariable))) {
                continue;
            }
            sideEffectReturnFound = true;
        }

        // unknown name
        if (bodyToken->isNameOnly()) {
            return false;
        }
    }

    return !sideEffectReturnFound;
}

bool SymbolDatabase::isRecordTypeWithoutSideEffects(const Type* type) const
{
    const std::pair<std::map<const Type*, bool>::iterator, bool> found = mIsRecordTypeWithoutSideEffectsMap.insert(
        std::pair<const Type*, bool>(type, false));         //Initialize with side effects for possible recursions
    bool& withoutSideEffects = found.first->second;
    if (!found.second)
        return withoutSideEffects;

    // unknown types are assumed to have side effects
    if (!type || !type->classScope)
        return (withoutSideEffects = false);

    // Non-empty constructors => possible side effects
    for (const Function& f : type->classScope->functionList) {
        if (!f.isConstructor() && !f.isDestructor())
            continue;
        if (f.argDef && match123(f.argDef->link()))
            continue; // ignore default/deleted constructors
        const bool emptyBody = (f.functionScope && match85(f.functionScope->bodyStart));

        const Token* nextToken = f.argDef ? f.argDef->link() : nullptr;
        if (match124(nextToken)) {
            // validating initialization list
            nextToken = nextToken->next(); // goto ":"

            for (const Token* initListToken = nextToken; match125(initListToken); initListToken = initListToken->linkAt(2)->next()) {
                const Token* varToken = initListToken->next();
                const Variable* variable = varToken->variable();
                if (variable && !isVariableWithoutSideEffects(*variable)) {
                    return withoutSideEffects = false;
                }

                const Token* valueEnd = initListToken->linkAt(2);
                for (const Token* valueToken = initListToken->tokAt(3); valueToken != valueEnd; valueToken = valueToken->next()) {
                    const Variable* initValueVar = valueToken->variable();
                    if (initValueVar && !isVariableWithoutSideEffects(*initValueVar)) {
                        return withoutSideEffects = false;
                    }
                    if ((valueToken->tokType() == Token::Type::eName) ||
                        (valueToken->tokType() == Token::Type::eLambda) ||
                        (valueToken->tokType() == Token::Type::eOther)) {
                        return withoutSideEffects = false;
                    }
                    const Function* initValueFunc = valueToken->function();
                    if (initValueFunc && !isFunctionWithoutSideEffects(*initValueFunc, valueToken,
                                                                       std::list<const Function*> {})) {
                        return withoutSideEffects = false;
                    }
                }
            }
        }

        if (!emptyBody)
            return (withoutSideEffects = false);
    }

    // Derived from type that has side effects?
    if (std::any_of(type->derivedFrom.cbegin(), type->derivedFrom.cend(), [this](const Type::BaseInfo& derivedFrom) {
        return !isRecordTypeWithoutSideEffects(derivedFrom.type);
    }))
        return (withoutSideEffects = false);

    // Is there a member variable with possible side effects
    for (const Variable& var : type->classScope->varlist) {
        withoutSideEffects = isVariableWithoutSideEffects(var, type);
        if (!withoutSideEffects) {
            return withoutSideEffects;
        }
    }
    return (withoutSideEffects = true);
}

void SymbolDatabase::validate() const
{
    if (mSettings.debugwarnings) {
        validateExecutableScopes();
    }
    validateVariables();
}

void SymbolDatabase::clangSetVariables(const std::vector<const Variable *> &variableList)
{
    mVariableList = variableList;
}

void SymbolDatabase::debugSymbolDatabase() const
{
    if (!mSettings.debugnormal && !mSettings.debugwarnings)
        return;
    for (const Token* tok = mTokenizer.list.front(); tok != mTokenizer.list.back(); tok = tok->next()) {
        if (tok->astParent() && tok->astParent()->getTokenDebug() == tok->getTokenDebug())
            continue;
        if (tok->getTokenDebug() == TokenDebug::ValueType) {

            std::string msg = "Value type is ";
            ErrorPath errorPath;
            if (tok->valueType()) {
                msg += tok->valueType()->str();
                errorPath.insert(errorPath.end(), tok->valueType()->debugPath.cbegin(), tok->valueType()->debugPath.cend());

            } else {
                msg += "missing";
            }
            errorPath.emplace_back(tok, "");
            mErrorLogger.reportErr(
                {std::move(errorPath), &mTokenizer.list, Severity::debug, "valueType", msg, CWE{0}, Certainty::normal});
        }
    }
}

Variable::Variable(const Token *name_, const std::string &clangType, const Token *typeStart,
                   const Token *typeEnd, nonneg int index_, AccessControl access_,
                   const Type *type_, const Scope *scope_)
    : mNameToken(name_),
    mTypeStartToken(typeStart),
    mTypeEndToken(typeEnd),
    mIndex(index_),
    mAccess(access_),
    mFlags(0),
    mType(type_),
    mScope(scope_)
{
    if (!mTypeStartToken && mTypeEndToken) {
        mTypeStartToken = mTypeEndToken;
        while (match126(mTypeStartToken->previous()))
            mTypeStartToken = mTypeStartToken->previous();
    }

    while (match127(mTypeStartToken)) {
        if (mTypeStartToken->str() == MatchCompiler::makeConstString("static"))
            setFlag(fIsStatic, true);
        mTypeStartToken = mTypeStartToken->next();
    }

    if (match120(mTypeEndToken))
        setFlag(fIsReference, true);
    else if (match128(mTypeEndToken)) {
        setFlag(fIsReference, true);
        setFlag(fIsRValueRef, true);
    }

    std::string::size_type pos = clangType.find('[');
    if (pos != std::string::npos) {
        setFlag(fIsArray, true);
        do {
            const std::string::size_type pos1 = pos+1;
            pos = clangType.find(']', pos1);
            Dimension dim;
            dim.tok = nullptr;
            dim.known = pos > pos1;
            if (pos > pos1)
                dim.num = MathLib::toBigNumber(clangType.substr(pos1, pos - pos1));
            else
                dim.num = 0;
            mDimensions.push_back(dim);
            ++pos;
        } while (pos < clangType.size() && clangType[pos] == '[');
    }

    // Is there initialization in variable declaration
    const Token *initTok = mNameToken ? mNameToken->next() : nullptr;
    while (initTok && initTok->str() == MatchCompiler::makeConstString("["))
        initTok = initTok->link()->next();
    if (match129(initTok) || (initTok && initTok->isSplittedVarDeclEq()))
        setFlag(fIsInit, true);
}

Variable::Variable(const Variable &var, const Scope *scope)
{
    *this = var;
    mScope = scope;
}

Variable::Variable(const Variable &var)
{
    *this = var;
}

Variable::~Variable()
{
    delete mValueType;
}

Variable& Variable::operator=(const Variable &var) &
{
    if (this == &var)
        return *this;

    const ValueType* vt = nullptr;
    if (var.mValueType)
        vt = new ValueType(*var.mValueType);

    mNameToken = var.mNameToken;
    mTypeStartToken = var.mTypeStartToken;
    mTypeEndToken = var.mTypeEndToken;
    mIndex = var.mIndex;
    mAccess = var.mAccess;
    mFlags = var.mFlags;
    mType = var.mType;
    mScope = var.mScope;
    mDimensions = var.mDimensions;
    delete mValueType;
    mValueType = vt;

    return *this;
}

bool Variable::isMember() const {
    return mScope && mScope->isClassOrStructOrUnion();
}

bool Variable::isPointerArray() const
{
    return isArray() && nameToken() && nameToken()->previous() && (nameToken()->strAt(-1) == MatchCompiler::makeConstString("*"));
}

bool Variable::isUnsigned() const
{
    return mValueType ? (mValueType->sign == ValueType::Sign::UNSIGNED) : mTypeStartToken->isUnsigned();
}

const Token * Variable::declEndToken() const
{
    Token const * declEnd = typeStartToken();
    if (declEnd->tokAt(-1) && match130(declEnd->tokAt(-2)))
        declEnd = nameToken();
    while (declEnd && !match131(declEnd)) {
        if (declEnd->link() && match132(declEnd))
            declEnd = declEnd->link();
        declEnd = declEnd->next();
    }
    return declEnd;
}

void Variable::evaluate(const Settings& settings)
{
    // Is there initialization in variable declaration
    const Token *initTok = mNameToken ? mNameToken->next() : nullptr;
    while (match13(initTok)) {
        initTok = initTok->link()->next();
        if (match105(initTok))
            initTok = initTok->next();
    }
    if (match133(initTok) || (initTok && initTok->isSplittedVarDeclEq()))
        setFlag(fIsInit, true);

    const Library & lib = settings.library;

    bool isContainer = false;
    if (mNameToken) {
        setFlag(fIsArray, arrayDimensions(settings, isContainer));
        setFlag(fIsMaybeUnused, mNameToken->isAttributeMaybeUnused());
    }


    if (mTypeStartToken)
        setValueType(ValueType::parseDecl(mTypeStartToken,settings));

    const Token* tok = mTypeStartToken;
    while (tok && tok->previous() && tok->previous()->isName())
        tok = tok->previous();
    const Token* end = mTypeEndToken;
    if (end)
        end = end->next();
    while (tok != end) {
        if (tok->str() == MatchCompiler::makeConstString("static"))
            setFlag(fIsStatic, true);
        else if (tok->str() == MatchCompiler::makeConstString("extern"))
            setFlag(fIsExtern, true);
        else if (tok->str() == MatchCompiler::makeConstString("volatile") || match134(tok))
            setFlag(fIsVolatile, true);
        else if (tok->str() == MatchCompiler::makeConstString("mutable"))
            setFlag(fIsMutable, true);
        else if (tok->str() == MatchCompiler::makeConstString("const"))
            setFlag(fIsConst, true);
        else if (tok->str() == MatchCompiler::makeConstString("constexpr")) {
            setFlag(fIsConst, true);
            setFlag(fIsStatic, true);
        } else if (tok->str() == MatchCompiler::makeConstString("*")) {
            setFlag(fIsPointer, !isArray() || (isContainer && !match135(tok->next())) || match136(tok));
            setFlag(fIsConst, false); // Points to const, isn't necessarily const itself
        } else if (tok->str() == MatchCompiler::makeConstString("&")) {
            if (isReference())
                setFlag(fIsRValueRef, true);
            setFlag(fIsReference, true);
        } else if (tok->str() == MatchCompiler::makeConstString("&&")) { // Before simplification, && isn't split up
            setFlag(fIsRValueRef, true);
            setFlag(fIsReference, true); // Set also fIsReference
        }

        if (tok->str() == MatchCompiler::makeConstString("<") && tok->link())
            tok = tok->link();
        else
            tok = tok->next();
    }

    while (match137(mTypeStartToken))
        mTypeStartToken = mTypeStartToken->next();
    while (mTypeEndToken && mTypeEndToken->previous() && match138(mTypeEndToken))
        mTypeEndToken = mTypeEndToken->previous();

    if (mTypeStartToken) {
        std::string strtype = mTypeStartToken->str();
        for (const Token *typeToken = mTypeStartToken; match139(typeToken); typeToken = typeToken->tokAt(2))
            strtype += "::" + typeToken->strAt(2);
        setFlag(fIsClass, !lib.podtype(strtype) && !mTypeStartToken->isStandardType() && !isEnumType() && !isPointer() && !isReference() && strtype != MatchCompiler::makeConstString("..."));
        setFlag(fIsStlType, match140(mTypeStartToken));
        setFlag(fIsStlString, ::isStlStringType(mTypeStartToken));
        setFlag(fIsSmartPointer, mTypeStartToken->isCpp() && lib.isSmartPointer(mTypeStartToken));
    }
    if (mAccess == AccessControl::Argument) {
        tok = mNameToken;
        if (!tok) {
            // Argument without name
            tok = mTypeEndToken;
            // back up to start of array dimensions
            while (tok && tok->str() == MatchCompiler::makeConstString("]"))
                tok = tok->link()->previous();
            // add array dimensions if present
            if (tok && tok->strAt(1) == MatchCompiler::makeConstString("["))
                setFlag(fIsArray, arrayDimensions(settings, isContainer));
        }
        if (!tok)
            return;
        tok = tok->next();
        while (tok->str() == MatchCompiler::makeConstString("["))
            tok = tok->link();
        setFlag(fHasDefault, tok->str() == MatchCompiler::makeConstString("="));
    }
    // check for C++11 member initialization
    if (mScope && mScope->isClassOrStruct()) {
        // type var = x or
        // type var = {x}
        // type var = x; gets simplified to: type var ; var = x ;
        Token const * declEnd = declEndToken();
        if ((match141(declEnd) && declEnd->strAt(1) == mNameToken->str()) ||
            match129(declEnd))
            setFlag(fHasDefault, true);
    }

    if (mTypeStartToken) {
        if (match142(mTypeStartToken))
            setFlag(fIsFloatType, true);
    }
}

void Variable::setValueType(const ValueType &valueType)
{
    if (valueType.type == ValueType::Type::UNKNOWN_TYPE) {
        const Token *declType = findmatch143(mTypeStartToken, mTypeEndToken) ;
        if (declType && !declType->next()->valueType())
            return;
    }
    const auto* vt = new ValueType(valueType);
    delete mValueType;
    mValueType = vt;
    if ((mValueType->pointer > 0) && (!isArray() || match144(mNameToken->previous())))
        setFlag(fIsPointer, true);
    setFlag(fIsConst, mValueType->constness & (1U << mValueType->pointer));
    setFlag(fIsVolatile, mValueType->volatileness & (1U << mValueType->pointer));
    if (mValueType->smartPointerType)
        setFlag(fIsSmartPointer, true);
}

const Type* Variable::smartPointerType() const
{
    if (!isSmartPointer())
        return nullptr;

    if (mValueType->smartPointerType)
        return mValueType->smartPointerType;

    // TODO: Cache result, handle more complex type expression
    const Token* typeTok = typeStartToken();
    while (match12(typeTok))
        typeTok = typeTok->next();
    if (match145(typeTok)) {
        // cppcheck-suppress shadowFunction - TODO: fix this
        const Scope* scope = typeTok->scope();
        const Type* ptrType{};
        while (scope && !ptrType) {
            ptrType = scope->findType(typeTok->strAt(1));
            scope = scope->nestedIn;
        }
        return ptrType;
    }
    return nullptr;
}

const Type* Variable::iteratorType() const
{
    if (!mValueType || mValueType->type != ValueType::ITERATOR)
        return nullptr;

    if (mValueType->containerTypeToken)
        return mValueType->containerTypeToken->type();

    return nullptr;
}

bool Variable::isStlStringViewType() const
{
    return getFlag(fIsStlType) && valueType() && valueType()->container && valueType()->container->stdStringLike && valueType()->container->view;
}

std::string Variable::getTypeName() const
{
    std::string ret;
    // TODO: For known types, generate the full type name
    for (const Token *typeTok = mTypeStartToken; match12(typeTok) && typeTok->varId() == 0; typeTok = typeTok->next()) {
        ret += typeTok->str();
        if (match60(typeTok->next()) && typeTok->linkAt(1)) // skip template arguments
            typeTok = typeTok->linkAt(1);
    }
    return ret;
}

static bool isOperator(const Token *tokenDef)
{
    if (!tokenDef)
        return false;
    if (tokenDef->isOperatorKeyword())
        return true;
    const std::string &name = tokenDef->str();
    return name.size() > 8 && startsWith(name,"operator") && std::strchr("+-*/%&|~^<>!=[(", name[8]);
}

static bool isTrailingReturnType(const Token* tok)
{
    while (tok && tok->isKeyword())
        tok = tok->next();
    return match146(tok);
}

Function::Function(const Token *tok,
                   const Scope *scope,
                   const Token *tokDef,
                   const Token *tokArgDef)
    : tokenDef(tokDef),
    argDef(tokArgDef),
    nestedIn(scope)
{
    // operator function
    if (::isOperator(tokenDef)) {
        isOperator(true);

        // 'operator =' is special
        if (tokenDef->str() == MatchCompiler::makeConstString("operator="))
            type = FunctionType::eOperatorEqual;
    }

    else if (tokenDef->str() == MatchCompiler::makeConstString("[")) {
        type = FunctionType::eLambda;
    }

    // class constructor/destructor
    else if (scope->isClassOrStructOrUnion() &&
             ((tokenDef->str() == scope->className) ||
              (tokenDef->str().substr(0, scope->className.size()) == scope->className &&
               tokenDef->str().size() > scope->className.size() + 1 &&
               tokenDef->str()[scope->className.size() + 1] == '<'))) {
        // destructor
        if (tokenDef->strAt(-1) == MatchCompiler::makeConstString("~")) {
            type = FunctionType::eDestructor;
            isNoExcept(true);
        }
        // constructor of any kind
        else
            type = FunctionType::eConstructor;
    }

    const Token *tok1 = setFlags(tok, scope);

    // find the return type
    if (!isConstructor() && !isDestructor()) {
        // @todo auto type deduction should be checked
        // @todo attributes and exception specification can also precede trailing return type
        if (isTrailingReturnType(argDef->link()->next())) { // Trailing return type
            hasTrailingReturnType(true);
            if (argDef->link()->strAt(1) == MatchCompiler::makeConstString("."))
                retDef = argDef->link()->tokAt(2);
            else if (argDef->link()->strAt(2) == MatchCompiler::makeConstString("."))
                retDef = argDef->link()->tokAt(3);
            else if (argDef->link()->strAt(3) == MatchCompiler::makeConstString("."))
                retDef = argDef->link()->tokAt(4);
        } else if (!isLambda()) {
            if (tok1->str() == MatchCompiler::makeConstString(">"))
                tok1 = tok1->next();
            while (match147(tok1))
                tok1 = tok1->next();
            retDef = tok1;
        }
    }

    const Token *end = argDef->link();

    // parse function attributes..
    tok = end->next();
    while (tok) {
        if (tok->str() == MatchCompiler::makeConstString("const"))
            isConst(true);
        else if (tok->str() == MatchCompiler::makeConstString("&"))
            hasLvalRefQualifier(true);
        else if (tok->str() == MatchCompiler::makeConstString("&&"))
            hasRvalRefQualifier(true);
        else if (tok->str() == MatchCompiler::makeConstString("override"))
            setFlag(fHasOverrideSpecifier, true);
        else if (tok->str() == MatchCompiler::makeConstString("final"))
            setFlag(fHasFinalSpecifier, true);
        else if (tok->str() == MatchCompiler::makeConstString("volatile"))
            isVolatile(true);
        else if (tok->str() == MatchCompiler::makeConstString("noexcept")) {
            isNoExcept(!match148(tok->next()));
            if (tok->strAt(1) == MatchCompiler::makeConstString("("))
                tok = tok->linkAt(1);
        } else if (match149(tok)) {
            isThrow(true);
            if (tok->strAt(2) != MatchCompiler::makeConstString(")"))
                throwArg = tok->next();
            tok = tok->linkAt(1);
        } else if (match150(tok)) {
            const std::string& modifier = tok->strAt(1);
            isPure(modifier == MatchCompiler::makeConstString("0"));
            isDefault(modifier == MatchCompiler::makeConstString("default"));
            isDelete(modifier == MatchCompiler::makeConstString("delete"));
        } else if (tok->str() == MatchCompiler::makeConstString(".")) { // trailing return type
            // skip over return type
            while (tok && !match151(tok->next()))
                tok = tok->next();
        } else
            break;
        if (tok)
            tok = tok->next();
    }

    if (TokenList::isFunctionHead(end, ":{")) {
        // assume implementation is inline (definition and implementation same)
        token = tokenDef;
        arg = argDef;
        isInline(true);
        hasBody(true);
    }

    for (tok = tokenDef->previous(); match152(tok); tok = tok->previous()) {
        // We should set other keywords here as well
        if (tok->str() == MatchCompiler::makeConstString("explicit"))
            isExplicit(true);
        if (tok->str() == MatchCompiler::makeConstString("]") || tok->str() == MatchCompiler::makeConstString(")"))
            tok = tok->link();
    }
}

Function::Function(const Token *tokenDef, const std::string &clangType)
    : tokenDef(tokenDef)
{
    // operator function
    if (::isOperator(tokenDef)) {
        isOperator(true);

        // 'operator =' is special
        if (tokenDef->str() == MatchCompiler::makeConstString("operator="))
            type = FunctionType::eOperatorEqual;
    }

    setFlags(tokenDef, tokenDef->scope());

    if (endsWith(clangType, " const"))
        isConst(true);
}

const Token *Function::setFlags(const Token *tok1, const Scope *scope)
{
    if (tok1->isInline())
        isInlineKeyword(true);

    if (tok1->isExternC())
        isExtern(true);

    // look for end of previous statement
    while (tok1->previous() && !match153(tok1->previous())) {
        tok1 = tok1->previous();

        if (tok1->isInline())
            isInlineKeyword(true);

        // extern function
        if (tok1->str() == MatchCompiler::makeConstString("extern")) {
            isExtern(true);
        }

        // virtual function
        else if (tok1->str() == MatchCompiler::makeConstString("virtual")) {
            hasVirtualSpecifier(true);
        }

        // static function
        else if (tok1->str() == MatchCompiler::makeConstString("static")) {
            isStatic(true);
            if (scope->type == ScopeType::eNamespace || scope->type == ScopeType::eGlobal)
                isStaticLocal(true);
        }

        // friend function
        else if (tok1->str() == MatchCompiler::makeConstString("friend")) {
            isFriend(true);
        }

        // constexpr function
        else if (tok1->str() == MatchCompiler::makeConstString("constexpr")) {
            isConstexpr(true);
        }

        // decltype
        else if (tok1->str() == MatchCompiler::makeConstString(")") && match37(tok1->link()->previous())) {
            tok1 = tok1->link()->previous();
        }

        else if (tok1->link() && tok1->str() == MatchCompiler::makeConstString(">")) {
            // Function template
            if (match154(tok1->link()->previous())) {
                templateDef = tok1->link()->previous();
                break;
            }
            tok1 = tok1->link();
        }
    }
    return tok1;
}

std::string Function::fullName() const
{
    std::string ret = name();
    for (const Scope *s = nestedIn; s; s = s->nestedIn) {
        if (!s->className.empty())
            ret = s->className + "::" + ret;
    }
    ret += "(";
    for (const Variable &a : argumentList)
        ret += (a.index() == 0 ? "" : ",") + a.name();
    return ret + ")";
}

static std::string qualifiedName(const Scope *scope)
{
    std::string name = scope->className;
    while (scope->nestedIn) {
        if (!scope->nestedIn->className.empty())
            name = (scope->nestedIn->className + " :: ") + name;
        scope = scope->nestedIn;
    }
    return name;
}

static bool usingNamespace(const Scope *scope, const Token *first, const Token *second, int &offset)
{
    // check if qualifications match first before checking if using is needed
    const Token *tok1 = first;
    const Token *tok2 = second;
    bool match = false;
    while (match139(tok1) && match139(tok2)) {
        if (tok1->str() == tok2->str()) {
            tok1 = tok1->tokAt(2);
            tok2 = tok2->tokAt(2);
            match = true;
        } else {
            match = false;
            break;
        }
    }

    if (match)
        return false;

    offset = 0;
    std::string name = first->str();

    while (match139(first)) {
        if (offset)
            name += (" :: " + first->str());
        offset += 2;
        first = first->tokAt(2);
        if (first->str() == second->str()) {
            break;
        }
    }

    if (offset) {
        while (scope) {
            for (const auto & info : scope->usingList) {
                if (info.scope) {
                    if (name == qualifiedName(info.scope))
                        return true;
                }
                // no scope so get name from using
                else {
                    const Token *start = info.start->tokAt(2);
                    std::string nsName;
                    while (start && start->str() != MatchCompiler::makeConstString(";")) {
                        if (!nsName.empty())
                            nsName += " ";
                        nsName += start->str();
                        start = start->next();
                    }
                    if (nsName == name)
                        return true;
                }
            }
            scope = scope->nestedIn;
        }
    }

    return false;
}

static bool typesMatch(
    const Scope *first_scope,
    const Token *first_token,
    const Scope *second_scope,
    const Token *second_token,
    const Token *&new_first,
    const Token *&new_second)
{
    // get first type
    const Type* first_type = first_scope->symdb.findType(first_token, first_scope, /*lookOutside*/ true);
    if (first_type) {
        // get second type
        const Type* second_type = second_scope->symdb.findType(second_token, second_scope, /*lookOutside*/ true);
        // check if types match
        if (first_type == second_type) {
            const Token* tok1 = first_token;
            while (tok1 && tok1->str() != first_type->name())
                tok1 = tok1->next();
            const Token *tok2 = second_token;
            while (tok2 && tok2->str() != second_type->name())
                tok2 = tok2->next();
            // update parser token positions
            if (tok1 && tok2) {
                new_first = tok1->previous();
                new_second = tok2->previous();
                return true;
            }
        }
    }
    return false;
}

bool Function::argsMatch(const Scope *scope, const Token *first, const Token *second, const std::string &path, nonneg int path_length) const
{
    if (!first->isCpp()) // C does not support overloads
        return true;

    int arg_path_length = path_length;
    int offset = 0;
    int openParen = 0;

    // check for () == (void) and (void) == ()
    if ((match155(first) && match156(second)) ||
        (match156(first) && match155(second)))
        return true;

    auto skipTopLevelConst = [](const Token* start) -> const Token* {
        const Token* tok = start->next();
        if (match157(tok)) {
            tok = tok->next();
            while (match158(tok))
                tok = tok->next();
            if (match159(tok))
                return start->next();
        }
        return start;
    };

    while (first->str() == second->str() &&
           first->isLong() == second->isLong() &&
           first->isUnsigned() == second->isUnsigned()) {
        if (first->str() == MatchCompiler::makeConstString("("))
            openParen++;

        // at end of argument list
        else if (first->str() == MatchCompiler::makeConstString(")")) {
            if (openParen == 1)
                return true;
            --openParen;
        }

        // skip optional type information
        if (match160(first->next()))
            first = first->next();
        if (match160(second->next()))
            second = second->next();

        // skip const on type passed by value
        const Token* const oldSecond = second;
        first = skipTopLevelConst(first);
        second = skipTopLevelConst(second);

        // skip default value assignment
        if (oldSecond == second && first->strAt(1) == MatchCompiler::makeConstString("=")) {
            first = first->nextArgument();
            if (first)
                first = first->tokAt(-2);
            if (second->strAt(1) == MatchCompiler::makeConstString("=")) {
                second = second->nextArgument();
                if (second)
                    second = second->tokAt(-2);
                if (!first || !second) { // End of argument list (first or second)
                    return !first && !second;
                }
            } else if (!first) { // End of argument list (first)
                return !second->nextArgument(); // End of argument list (second)
            }
        } else if (oldSecond == second && second->strAt(1) == MatchCompiler::makeConstString("=")) {
            second = second->nextArgument();
            if (second)
                second = second->tokAt(-2);
            if (!second) { // End of argument list (second)
                return !first->nextArgument();
            }
        }

        // definition missing variable name
        else if ((first->strAt(1) == MatchCompiler::makeConstString(",") && second->strAt(1) != MatchCompiler::makeConstString(",")) ||
                 (match161(first) && second->strAt(1) != MatchCompiler::makeConstString(")"))) {
            second = second->next();
            // skip default value assignment
            if (second->strAt(1) == MatchCompiler::makeConstString("=")) {
                do {
                    second = second->next();
                } while (!match162(second->next()));
            }
        } else if (first->strAt(1) == MatchCompiler::makeConstString("[") && second->strAt(1) != MatchCompiler::makeConstString("["))
            second = second->next();

        // function missing variable name
        else if ((second->strAt(1) == MatchCompiler::makeConstString(",") && first->strAt(1) != MatchCompiler::makeConstString(",")) ||
                 (match161(second) && first->strAt(1) != MatchCompiler::makeConstString(")"))) {
            first = first->next();
            // skip default value assignment
            if (first->strAt(1) == MatchCompiler::makeConstString("=")) {
                do {
                    first = first->next();
                } while (!match162(first->next()));
            }
        } else if (second->strAt(1) == MatchCompiler::makeConstString("[") && first->strAt(1) != MatchCompiler::makeConstString("["))
            first = first->next();

        // unnamed parameters
        else if (match163(first) && match163(second)) {
            if (first->next()->expressionString() != second->next()->expressionString())
                break;
            first = first->next();
            second = second->next();
            continue;
        }

        // argument list has different number of arguments
        else if (openParen == 1 && second->str() == MatchCompiler::makeConstString(")") && first->str() != MatchCompiler::makeConstString(")"))
            break;

        // check for type * x == type x[]
        else if (match164(first->next()) &&
                 match165(second->next())) {
            do {
                first = first->next();
            } while (!match162(first->next()));
            do {
                second = second->next();
            } while (!match162(second->next()));
        }

        // const after *
        else if (first->strAt(1) == MatchCompiler::makeConstString("*") && second->strAt(1) == MatchCompiler::makeConstString("*") &&
                 ((first->strAt(2) != MatchCompiler::makeConstString("const") && second->strAt(2) == MatchCompiler::makeConstString("const")) ||
                  (first->strAt(2) == MatchCompiler::makeConstString("const") && second->strAt(2) != MatchCompiler::makeConstString("const")))) {
            if (first->strAt(2) != MatchCompiler::makeConstString("const")) {
                if (match166(first->tokAt(2)) && match166(second->tokAt(3))) {
                    first = first->tokAt(match76(first->tokAt(2)) ? 2 : 1);
                    second = second->tokAt(match76(second->tokAt(3)) ? 3 : 2);
                } else {
                    first = first->next();
                    second = second->tokAt(2);
                }
            } else {
                if (match166(second->tokAt(2)) && match166(first->tokAt(3))) {
                    first = first->tokAt(match76(first->tokAt(3)) ? 3 : 2);
                    second = second->tokAt(match76(second->tokAt(2)) ? 2 : 1);
                } else {
                    first = first->tokAt(2);
                    second = second->next();
                }
            }
        }

        // variable names are different
        else if ((match167(first->next()) &&
                  match168(second->next())) &&
                 (first->strAt(1) != second->strAt(1))) {
            // skip variable names
            first = first->next();
            second = second->next();

            // skip default value assignment
            if (first->strAt(1) == MatchCompiler::makeConstString("=")) {
                do {
                    first = first->next();
                } while (!match162(first->next()));
            }
        }

        // using namespace
        else if (usingNamespace(scope, first->next(), second->next(), offset))
            first = first->tokAt(offset);

        // same type with different qualification
        else if (typesMatch(scope, first->next(), nestedIn, second->next(), first, second))
            ;

        // variable with class path
        else if (arg_path_length && match76(first->next()) && first->strAt(1) != MatchCompiler::makeConstString("const")) {
            std::string param = path;

            if (Token::simpleMatch(second->next(), param.c_str(), param.size())) {
                // check for redundant qualification before skipping it
                if (!Token::simpleMatch(first->next(), param.c_str(), param.size())) {
                    second = second->tokAt(arg_path_length);
                    arg_path_length = 0;
                }
            }

            // nested or base class variable
            else if (arg_path_length <= 2 && match76(first->next()) &&
                     (match14(second->next()) ||
                      (match3(second->next()) &&
                       match169(second->linkAt(1)))) &&
                     ((second->strAt(1) == scope->className) ||
                      (scope->nestedIn && second->strAt(1) == scope->nestedIn->className) ||
                      (scope->definedType && scope->definedType->isDerivedFrom(second->strAt(1)))) &&
                     (first->strAt(1) == second->strAt(3))) {
                if (match3(second->next()))
                    second = second->linkAt(1)->next();
                else
                    second = second->tokAt(2);
            }

            // remove class name
            else if (arg_path_length > 2 && first->strAt(1) != second->strAt(1)) {
                std::string short_path = path;
                int short_path_length = arg_path_length;

                // remove last " :: "
                short_path.resize(short_path.size() - 4);
                short_path_length--;

                // remove last name
                std::string::size_type lastSpace = short_path.find_last_of(' ');
                if (lastSpace != std::string::npos) {
                    short_path.resize(lastSpace+1);
                    short_path_length--;
                    if (short_path[short_path.size() - 1] == '>') {
                        short_path.resize(short_path.size() - 3);
                        while (short_path[short_path.size() - 1] == '<') {
                            lastSpace = short_path.find_last_of(' ');
                            short_path.resize(lastSpace+1);
                            short_path_length--;
                        }
                    }
                }

                param = std::move(short_path);
                if (Token::simpleMatch(second->next(), param.c_str(), param.size())) {
                    second = second->tokAt(short_path_length);
                    arg_path_length = 0;
                }
            }
        }

        first = first->next();
        second = second->next();

        // reset path length
        if (first->str() == MatchCompiler::makeConstString(",") || second->str() == MatchCompiler::makeConstString(","))
            arg_path_length = path_length;
    }

    return false;
}

static bool isUnknownType(const Token* start, const Token* end)
{
    while (match138(start))
        start = start->next();
    start = skipScopeIdentifiers(start);
    if (start->tokAt(1) == end && !start->type() && !start->isStandardType())
        return true;
    // TODO: Try to deduce the type of the expression
    if (match170(start))
        return true;
    return false;
}

static const Token* getEnableIfReturnType(const Token* start)
{
    if (!start)
        return nullptr;
    for (const Token* tok = start->next(); precedes(tok, start->link()); tok = tok->next()) {
        if (tok->link() && match171(tok)) {
            tok = tok->link();
            continue;
        }
        if (match172(tok))
            return tok->next();
    }
    return nullptr;
}

template<class Predicate>
static bool checkReturns(const Function* function, bool unknown, bool emptyEnableIf, Predicate pred)
{
    if (!function)
        return false;
    if (function->type != FunctionType::eFunction && function->type != FunctionType::eOperatorEqual && function->type != FunctionType::eLambda)
        return false;
    const Token* defStart = function->retDef;
    if (!defStart)
        return unknown;
    const Token* defEnd = function->returnDefEnd();
    if (!defEnd)
        return unknown;
    if (defEnd == defStart)
        return unknown;
    if (pred(defStart, defEnd))
        return true;
    if (match82(defEnd->tokAt(-1)))
        return false;
    // void STDCALL foo()
    while (defEnd->previous() != defStart && match173(defEnd->tokAt(-2)) &&
           !match138(defEnd->tokAt(-2)))
        defEnd = defEnd->previous();
    // enable_if
    const Token* enableIfEnd = nullptr;
    if (match55(defEnd->previous()))
        enableIfEnd = defEnd->previous();
    else if (match174(defEnd->tokAt(-3)))
        enableIfEnd = defEnd->tokAt(-3);
    if (enableIfEnd && enableIfEnd->link() &&
        match175(enableIfEnd->link()->previous())) {
        if (const Token* start = getEnableIfReturnType(enableIfEnd->link())) {
            defStart = start;
            defEnd = enableIfEnd;
        } else {
            return emptyEnableIf;
        }
    }
    assert(defEnd != defStart);
    if (pred(defStart, defEnd))
        return true;
    if (isUnknownType(defStart, defEnd))
        return unknown;
    return false;
}

bool Function::returnsConst(const Function* function, bool unknown)
{
    return checkReturns(function, unknown, false, [](const Token* defStart, const Token* defEnd) {
        return findmatch176(defStart, defEnd) ;
    });
}

bool Function::returnsReference(const Function* function, bool unknown, bool includeRValueRef)
{
    return checkReturns(function, unknown, false, [includeRValueRef](const Token* /*defStart*/, const Token* defEnd) {
        return includeRValueRef ? match177(defEnd->previous()) : match120(defEnd->previous());
    });
}

bool Function::returnsPointer(const Function* function, bool unknown)
{
    return checkReturns(function, unknown, false, [](const Token* /*defStart*/, const Token* defEnd) {
        return match62(defEnd->previous());
    });
}

bool Function::returnsStandardType(const Function* function, bool unknown)
{
    return checkReturns(function, unknown, true, [](const Token* /*defStart*/, const Token* defEnd) {
        return defEnd->previous() && defEnd->previous()->isStandardType();
    });
}

bool Function::returnsVoid(const Function* function, bool unknown)
{
    return checkReturns(function, unknown, true, [](const Token* /*defStart*/, const Token* defEnd) {
        return match178(defEnd->previous());
    });
}

std::vector<const Token*> Function::findReturns(const Function* f)
{
    std::vector<const Token*> result;
    if (!f)
        return result;
    const Scope* scope = f->functionScope;
    if (!scope)
        return result;
    if (!scope->bodyStart)
        return result;
    for (const Token* tok = scope->bodyStart->next(); tok && tok != scope->bodyEnd; tok = tok->next()) {
        if (tok->str() == MatchCompiler::makeConstString("{") && tok->scope() &&
            (tok->scope()->type == ScopeType::eLambda || tok->scope()->type == ScopeType::eClass)) {
            tok = tok->link();
            continue;
        }
        if (match122(tok->astParent())) {
            result.push_back(tok);
        }
        // Skip lambda functions since the scope may not be set correctly
        const Token* lambdaEndToken = findLambdaEndToken(tok);
        if (lambdaEndToken) {
            tok = lambdaEndToken;
        }
    }
    return result;
}

const Token * Function::constructorMemberInitialization() const
{
    if (!isConstructor() || !arg)
        return nullptr;
    if (match124(arg->link()))
        return arg->link()->next();
    if (match179(arg->link()) && arg->link()->linkAt(2)->strAt(1) == MatchCompiler::makeConstString(":"))
        return arg->link()->linkAt(2)->next();
    return nullptr;
}

bool Function::isSafe(const Settings &settings) const
{
    if (settings.safeChecks.externalFunctions) {
        if (nestedIn->type == ScopeType::eNamespace && token->fileIndex() != 0)
            return true;
        if (nestedIn->type == ScopeType::eGlobal && (token->fileIndex() != 0 || !isStatic()))
            return true;
    }

    if (settings.safeChecks.internalFunctions) {
        if (nestedIn->type == ScopeType::eNamespace && token->fileIndex() == 0)
            return true;
        if (nestedIn->type == ScopeType::eGlobal && (token->fileIndex() == 0 || isStatic()))
            return true;
    }

    if (settings.safeChecks.classes && access == AccessControl::Public && (nestedIn->type == ScopeType::eClass || nestedIn->type == ScopeType::eStruct))
        return true;

    return false;
}

Function* SymbolDatabase::addGlobalFunction(Scope*& scope, const Token*& tok, const Token *argStart, const Token* funcStart)
{
    Function* function = nullptr;
    // Lambda functions are always unique
    if (tok->str() != MatchCompiler::makeConstString("[")) {
        auto range = scope->functionMap.equal_range(tok->str());
        for (std::multimap<std::string, const Function*>::const_iterator it = range.first; it != range.second; ++it) {
            const Function *f = it->second;
            if (f->hasBody())
                continue;
            if (f->argsMatch(scope, f->argDef, argStart, emptyString, 0)) {
                function = const_cast<Function *>(it->second);
                break;
            }
        }
    }

    if (!function)
        function = addGlobalFunctionDecl(scope, tok, argStart, funcStart);

    function->arg = argStart;
    function->token = funcStart;
    function->hasBody(true);

    addNewFunction(scope, tok);

    if (scope) {
        scope->function = function;
        function->functionScope = scope;
        return function;
    }
    return nullptr;
}

Function* SymbolDatabase::addGlobalFunctionDecl(Scope*& scope, const Token *tok, const Token *argStart, const Token* funcStart)
{
    Function function(tok, scope, funcStart, argStart);
    scope->addFunction(std::move(function));
    return &scope->functionList.back();
}

void SymbolDatabase::addClassFunction(Scope *&scope, const Token *&tok, const Token *argStart)
{
    const bool destructor(tok->strAt(-1) == MatchCompiler::makeConstString("~"));
    const bool has_const(argStart->link()->strAt(1) == MatchCompiler::makeConstString("const"));
    const bool lval(argStart->link()->strAt(has_const ? 2 : 1) == MatchCompiler::makeConstString("&"));
    const bool rval(argStart->link()->strAt(has_const ? 2 : 1) == MatchCompiler::makeConstString("&&"));
    int count = 0;
    std::string path;
    unsigned int path_length = 0;
    const Token *tok1 = tok;

    if (destructor)
        tok1 = tok1->previous();

    // back up to head of path
    while (tok1 && tok1->previous() && tok1->strAt(-1) == MatchCompiler::makeConstString("::") && tok1->tokAt(-2) &&
           ((tok1->tokAt(-2)->isName() && !tok1->tokAt(-2)->isStandardType()) ||
            (tok1->strAt(-2) == MatchCompiler::makeConstString(">") && tok1->linkAt(-2) && match76(tok1->linkAt(-2)->previous())))) {
        count++;
        const Token * tok2 = tok1->tokAt(-2);
        if (tok2->str() == MatchCompiler::makeConstString(">"))
            tok2 = tok2->link()->previous();

        if (tok2) {
            do {
                path = tok1->strAt(-1) + " " + path;
                tok1 = tok1->previous();
                path_length++;
            } while (tok1 != tok2);
        } else
            return; // syntax error ?
    }

    // syntax error?
    if (!tok1)
        return;

    // add global namespace if present
    if (tok1->strAt(-1) == MatchCompiler::makeConstString("::")) {
        path_length++;
        path.insert(0, ":: ");
    }

    // search for match
    for (auto it1 = scopeList.begin(); it1 != scopeList.end(); ++it1) {
        Scope *scope1 = &(*it1);

        bool match = false;

        // check in namespace if using found
        if (scope == scope1 && !scope1->usingList.empty()) {
            for (auto it2 = scope1->usingList.cbegin(); it2 != scope1->usingList.cend(); ++it2) {
                if (it2->scope) {
                    Function * func = findFunctionInScope(tok1, it2->scope, path, path_length);
                    if (func) {
                        if (!func->hasBody()) {
                            const Token *closeParen = tok->linkAt(1);
                            if (closeParen) {
                                const Token *eq = TokenList::isFunctionHead(closeParen, ";");
                                if (eq && match180(eq->tokAt(-2))) {
                                    func->isDefault(true);
                                    return;
                                }
                            }
                            func->hasBody(true);
                            func->token = tok;
                            func->arg = argStart;
                            addNewFunction(scope, tok);
                            if (scope) {
                                scope->functionOf = func->nestedIn;
                                scope->function = func;
                                scope->function->functionScope = scope;
                            }
                            return;
                        }
                    }
                }
            }
        }

        const bool isAnonymousNamespace = (scope1->type == ScopeType::eNamespace && scope1->className.empty());
        if ((scope1->className == tok1->str() && (scope1->type != ScopeType::eFunction)) || isAnonymousNamespace) {
            // do the scopes match (same scope) or do their names match (multiple namespaces)
            if ((scope == scope1->nestedIn) || (scope &&
                                                scope->className == scope1->nestedIn->className &&
                                                !scope->className.empty() &&
                                                scope->type == scope1->nestedIn->type)) {

                // nested scopes => check that they match
                {
                    const Scope *s1 = scope;
                    const Scope *s2 = scope1->nestedIn;
                    while (s1 && s2) {
                        if (s1->className != s2->className)
                            break;
                        s1 = s1->nestedIn;
                        s2 = s2->nestedIn;
                    }
                    // Not matching scopes
                    if (s1 || s2)
                        continue;
                }

                Scope *scope2 = scope1;

                while (scope2 && count > 1) {
                    count--;
                    if (tok1->strAt(1) == MatchCompiler::makeConstString("<"))
                        tok1 = tok1->linkAt(1)->tokAt(2);
                    else
                        tok1 = tok1->tokAt(2);
                    scope2 = scope2->findRecordInNestedList(tok1->str());
                }
                if (scope2 && isAnonymousNamespace)
                    scope2 = scope2->findRecordInNestedList(tok1->str());

                if (count == 1 && scope2) {
                    match = true;
                    scope1 = scope2;
                }
            }
        }

        if (match) {
            auto range = scope1->functionMap.equal_range(tok->str());
            for (std::multimap<std::string, const Function*>::const_iterator it = range.first; it != range.second; ++it) {
                auto * func = const_cast<Function *>(it->second);
                if (destructor && func->type != FunctionType::eDestructor)
                    continue;
                if (!func->hasBody()) {
                    if (func->argsMatch(scope1, func->argDef, tok->next(), path, path_length)) {
                        const Token *closeParen = tok->linkAt(1);
                        if (closeParen) {
                            const Token *eq = TokenList::isFunctionHead(closeParen, ";");
                            if (eq && match181(eq->tokAt(-2))) {
                                if (eq->strAt(-1) == MatchCompiler::makeConstString("default"))
                                    func->isDefault(true);
                                else
                                    func->isDelete(true);
                                return;
                            }
                            if (func->type == FunctionType::eDestructor && destructor) {
                                func->hasBody(true);
                            } else if (func->type != FunctionType::eDestructor && !destructor) {
                                // normal function?
                                const bool hasConstKeyword = closeParen->strAt(1) == MatchCompiler::makeConstString("const");
                                if ((func->isConst() == hasConstKeyword) &&
                                    (func->hasLvalRefQualifier() == lval) &&
                                    (func->hasRvalRefQualifier() == rval)) {
                                    func->hasBody(true);
                                }
                            }
                        }

                        if (func->hasBody()) {
                            func->token = tok;
                            func->arg = argStart;
                            addNewFunction(scope, tok);
                            if (scope) {
                                scope->functionOf = scope1;
                                scope->function = func;
                                scope->function->functionScope = scope;
                            }
                            return;
                        }
                    }
                }
            }
        }
    }

    // class function of unknown class
    addNewFunction(scope, tok);
}

void SymbolDatabase::addNewFunction(Scope *&scope, const Token *&tok)
{
    const Token *tok1 = tok;
    scopeList.emplace_back(*this, tok1, scope);
    Scope *newScope = &scopeList.back();

    // find start of function '{'
    bool foundInitList = false;
    while (tok1 && tok1->str() != MatchCompiler::makeConstString("{") && tok1->str() != MatchCompiler::makeConstString(";")) {
        if (tok1->link() && match132(tok1)) {
            tok1 = tok1->link();
        } else if (foundInitList && match45(tok1) && match46(tok1->linkAt(1))) {
            tok1 = tok1->linkAt(1);
        } else {
            if (tok1->str() == MatchCompiler::makeConstString(":"))
                foundInitList = true;
            tok1 = tok1->next();
        }
    }

    if (tok1 && tok1->str() == MatchCompiler::makeConstString("{")) {
        newScope->setBodyStartEnd(tok1);

        // syntax error?
        if (!newScope->bodyEnd) {
            mTokenizer.unmatchedToken(tok1);
        } else {
            scope->nestedList.push_back(newScope);
            scope = newScope;
        }
    } else if (tok1 && match181(tok1->tokAt(-2))) {
        scopeList.pop_back();
    } else {
        throw InternalError(tok, "Analysis failed (function not recognized). If the code is valid then please report this failure.");
    }
    tok = tok1;
}

bool Type::isClassType() const
{
    return classScope && classScope->type == ScopeType::eClass;
}

bool Type::isEnumType() const
{
    //We explicitly check for "enum" because a forward declared enum doesn't get its own scope
    return (classDef && classDef->str() == MatchCompiler::makeConstString("enum")) ||
           (classScope && classScope->type == ScopeType::eEnum);
}

bool Type::isStructType() const
{
    return classScope && classScope->type == ScopeType::eStruct;
}

bool Type::isUnionType() const
{
    return classScope && classScope->type == ScopeType::eUnion;
}

const Token *Type::initBaseInfo(const Token *tok, const Token *tok1)
{
    // goto initial '{'
    const Token *tok2 = tok1;
    while (tok2 && tok2->str() != MatchCompiler::makeConstString("{")) {
        // skip unsupported templates
        if (tok2->str() == MatchCompiler::makeConstString("<"))
            tok2 = tok2->link();

        // check for base classes
        else if (match182(tok2)) {
            tok2 = tok2->next();

            // check for invalid code
            if (!tok2 || !tok2->next())
                return nullptr;

            Type::BaseInfo base;

            if (tok2->str() == MatchCompiler::makeConstString("virtual")) {
                base.isVirtual = true;
                tok2 = tok2->next();
            }

            if (tok2->str() == MatchCompiler::makeConstString("public")) {
                base.access = AccessControl::Public;
                tok2 = tok2->next();
            } else if (tok2->str() == MatchCompiler::makeConstString("protected")) {
                base.access = AccessControl::Protected;
                tok2 = tok2->next();
            } else if (tok2->str() == MatchCompiler::makeConstString("private")) {
                base.access = AccessControl::Private;
                tok2 = tok2->next();
            } else {
                if (tok->str() == MatchCompiler::makeConstString("class"))
                    base.access = AccessControl::Private;
                else if (tok->str() == MatchCompiler::makeConstString("struct"))
                    base.access = AccessControl::Public;
            }
            if (!tok2)
                return nullptr;
            if (tok2->str() == MatchCompiler::makeConstString("virtual")) {
                base.isVirtual = true;
                tok2 = tok2->next();
            }
            if (!tok2)
                return nullptr;

            base.nameTok = tok2;
            // handle global namespace
            if (tok2->str() == MatchCompiler::makeConstString("::")) {
                tok2 = tok2->next();
            }

            // handle derived base classes
            while (match2(tok2)) {
                tok2 = tok2->tokAt(2);
            }
            if (!tok2)
                return nullptr;

            base.name = tok2->str();

            tok2 = tok2->next();
            // add unhandled templates
            if (tok2 && tok2->link() && tok2->str() == MatchCompiler::makeConstString("<")) {
                for (const Token* const end = tok2->link()->next(); tok2 != end; tok2 = tok2->next()) {
                    base.name += tok2->str();
                }
            }

            const Type * baseType = classScope->symdb.findType(base.nameTok, enclosingScope);
            if (baseType && !baseType->findDependency(this))
                base.type = baseType;

            // save pattern for base class name
            derivedFrom.push_back(std::move(base));
        } else
            tok2 = tok2->next();
    }

    return tok2;
}

std::string Type::name() const
{
    const Token* start = classDef->next();
    if (classScope && classScope->enumClass && isEnumType())
        start = start->tokAt(1);
    else if (start->str() == MatchCompiler::makeConstString("class"))
        start = start->tokAt(1);
    else if (!start->isName())
        return emptyString;
    const Token* next = start;
    while (match183(next)) {
        if (match184(next) && next->link())
            next = next->link();
        next = next->next();
    }
    std::string result;
    for (const Token* tok = start; tok != next; tok = tok->next()) {
        if (!result.empty())
            result += ' ';
        result += tok->str();
    }
    return result;
}

void SymbolDatabase::debugMessage(const Token *tok, const std::string &type, const std::string &msg) const
{
    if (tok && mSettings.debugwarnings) {
        const std::list<const Token*> locationList(1, tok);
        const ErrorMessage errmsg(locationList, &mTokenizer.list,
                                  Severity::debug,
                                  type,
                                  msg,
                                  Certainty::normal);
        mErrorLogger.reportErr(errmsg);
    }
}

void SymbolDatabase::returnImplicitIntError(const Token *tok) const
{
    if (tok && mSettings.severity.isEnabled(Severity::portability) && (tok->isC() && mSettings.standards.c != Standards::C89)) {
        const std::list<const Token*> locationList(1, tok);
        const ErrorMessage errmsg(locationList, &mTokenizer.list,
                                  Severity::portability,
                                  "returnImplicitInt",
                                  "Omitted return type of function '" + tok->str() + "' defaults to int, this is not supported by ISO C99 and later standards.",
                                  Certainty::normal);
        mErrorLogger.reportErr(errmsg);
    }
}

const Function* Type::getFunction(const std::string& funcName) const
{
    if (classScope) {
        const auto it = utils::as_const(classScope->functionMap).find(funcName);
        if (it != classScope->functionMap.end())
            return it->second;
    }

    for (const Type::BaseInfo & i : derivedFrom) {
        if (i.type) {
            const Function* const func = i.type->getFunction(funcName);
            if (func)
                return func;
        }
    }
    return nullptr;
}

bool Type::hasCircularDependencies(std::set<BaseInfo>* ancestors) const
{
    std::set<BaseInfo> knownAncestors;
    if (!ancestors) {
        ancestors=&knownAncestors;
    }
    for (auto parent=derivedFrom.cbegin(); parent!=derivedFrom.cend(); ++parent) {
        if (!parent->type)
            continue;
        if (this==parent->type)
            return true;
        if (ancestors->find(*parent)!=ancestors->end())
            return true;

        ancestors->insert(*parent);
        if (parent->type->hasCircularDependencies(ancestors))
            return true;
    }
    return false;
}

bool Type::findDependency(const Type* ancestor) const
{
    return this == ancestor || std::any_of(derivedFrom.cbegin(), derivedFrom.cend(), [&](const BaseInfo& d) {
        return d.type && (d.type == this || d.type->findDependency(ancestor));
    });
}

bool Type::isDerivedFrom(const std::string & ancestor) const
{
    for (auto parent=derivedFrom.cbegin(); parent!=derivedFrom.cend(); ++parent) {
        if (parent->name == ancestor)
            return true;
        if (parent->type && parent->type->isDerivedFrom(ancestor))
            return true;
    }
    return false;
}

bool Variable::arrayDimensions(const Settings& settings, bool& isContainer)
{
    isContainer = false;
    const Library::Container* container = (mTypeStartToken && mTypeStartToken->isCpp()) ? settings.library.detectContainer(mTypeStartToken) : nullptr;
    if (container && container->arrayLike_indexOp && container->size_templateArgNo > 0) {
        const Token* tok = mTypeStartToken;
        while (match12(tok))
            tok = tok->next();
        if (tok && tok->str() == MatchCompiler::makeConstString("<")) {
            isContainer = true;
            Dimension dimension_;
            tok = tok->next();
            for (int i = 0; i < container->size_templateArgNo && tok; i++) {
                tok = tok->nextTemplateArgument();
            }
            if (match185(tok)) {
                dimension_.tok = tok;
                dimension_.known = true;
                dimension_.num = MathLib::toBigNumber(tok);
            } else if (tok) {
                dimension_.tok = tok;
                dimension_.known = false;
            }
            mDimensions.push_back(dimension_);
            return true;
        }
    }

    const Token *dim = mNameToken;
    if (!dim) {
        // Argument without name
        dim = mTypeEndToken;
        // back up to start of array dimensions
        while (dim && dim->str() == MatchCompiler::makeConstString("]"))
            dim = dim->link()->previous();
    }
    if (dim)
        dim = dim->next();
    if (dim && dim->str() == MatchCompiler::makeConstString(")"))
        dim = dim->next();

    bool arr = false;
    while (dim && dim->next() && dim->str() == MatchCompiler::makeConstString("[")) {
        Dimension dimension_;
        dimension_.known = false;
        // check for empty array dimension []
        if (dim->strAt(1) != MatchCompiler::makeConstString("]")) {
            dimension_.tok = dim->astOperand2();
            // TODO: only perform when ValueFlow is enabled
            // TODO: collect timing information for this call?
            ValueFlow::valueFlowConstantFoldAST(const_cast<Token *>(dimension_.tok), settings);
            if (dimension_.tok) {
                if (const ValueFlow::Value* v = dimension_.tok->getKnownValue(ValueFlow::Value::ValueType::INT)) {
                    dimension_.num = v->intvalue;
                    dimension_.known = true;
                }
                else if (dimension_.tok->isTemplateArg() && !dimension_.tok->values().empty()) {
                    assert(dimension_.tok->values().size() == 1);
                    dimension_.num = dimension_.tok->values().front().intvalue;
                    dimension_.known = true;
                }
            }
        }
        mDimensions.push_back(dimension_);
        dim = dim->link()->next();
        arr = true;
    }
    return arr;
}

static std::string scopeTypeToString(ScopeType type)
{
    switch (type) {
    case ScopeType::eGlobal:
        return "Global";
    case ScopeType::eClass:
        return "Class";
    case ScopeType::eStruct:
        return "Struct";
    case ScopeType::eUnion:
        return "Union";
    case ScopeType::eNamespace:
        return "Namespace";
    case ScopeType::eFunction:
        return "Function";
    case ScopeType::eIf:
        return "If";
    case ScopeType::eElse:
        return "Else";
    case ScopeType::eFor:
        return "For";
    case ScopeType::eWhile:
        return "While";
    case ScopeType::eDo:
        return "Do";
    case ScopeType::eSwitch:
        return "Switch";
    case ScopeType::eTry:
        return "Try";
    case ScopeType::eCatch:
        return "Catch";
    case ScopeType::eUnconditional:
        return "Unconditional";
    case ScopeType::eLambda:
        return "Lambda";
    case ScopeType::eEnum:
        return "Enum";
    }
    return "Unknown";
}

static std::ostream & operator << (std::ostream & s, ScopeType type)
{
    s << scopeTypeToString(type);
    return s;
}

static std::string accessControlToString(AccessControl access)
{
    switch (access) {
    case AccessControl::Public:
        return "Public";
    case AccessControl::Protected:
        return "Protected";
    case AccessControl::Private:
        return "Private";
    case AccessControl::Global:
        return "Global";
    case AccessControl::Namespace:
        return "Namespace";
    case AccessControl::Argument:
        return "Argument";
    case AccessControl::Local:
        return "Local";
    case AccessControl::Throw:
        return "Throw";
    }
    return "Unknown";
}

static const char* functionTypeToString(FunctionType type)
{
    switch (type) {
    case FunctionType::eConstructor:
        return "Constructor";
    case FunctionType::eCopyConstructor:
        return "CopyConstructor";
    case FunctionType::eMoveConstructor:
        return "MoveConstructor";
    case FunctionType::eOperatorEqual:
        return "OperatorEqual";
    case FunctionType::eDestructor:
        return "Destructor";
    case FunctionType::eFunction:
        return "Function";
    case FunctionType::eLambda:
        return "Lambda";
    default:
        return "Unknown";
    }
}

static std::string tokenToString(const Token* tok, const Tokenizer& tokenizer)
{
    std::ostringstream oss;
    if (tok) {
        oss << tok->str() << " ";
        oss << tokenizer.list.fileLine(tok) << " ";
    }
    oss << tok;
    return oss.str();
}

static std::string scopeToString(const Scope* scope, const Tokenizer& tokenizer)
{
    std::ostringstream oss;
    if (scope) {
        oss << scope->type << " ";
        if (!scope->className.empty())
            oss << scope->className << " ";
        if (scope->classDef)
            oss << tokenizer.list.fileLine(scope->classDef) << " ";
    }
    oss << scope;
    return oss.str();
}

static std::string tokenType(const Token * tok)
{
    std::ostringstream oss;
    if (tok) {
        if (tok->isUnsigned())
            oss << "unsigned ";
        else if (tok->isSigned())
            oss << "signed ";
        if (tok->isComplex())
            oss << "_Complex ";
        if (tok->isLong())
            oss << "long ";
        oss << tok->str();
    }
    return oss.str();
}

void SymbolDatabase::printVariable(const Variable *var, const char *indent) const
{
    std::cout << indent << "mNameToken: " << tokenToString(var->nameToken(), mTokenizer) << std::endl;
    if (var->nameToken()) {
        std::cout << indent << "    declarationId: " << var->declarationId() << std::endl;
    }
    std::cout << indent << "mTypeStartToken: " << tokenToString(var->typeStartToken(), mTokenizer) << std::endl;
    std::cout << indent << "mTypeEndToken: " << tokenToString(var->typeEndToken(), mTokenizer) << std::endl;

    if (var->typeStartToken()) {
        const Token * autoTok = nullptr;
        std::cout << indent << "   ";
        for (const Token * tok = var->typeStartToken(); tok != var->typeEndToken()->next(); tok = tok->next()) {
            std::cout << " " << tokenType(tok);
            if (tok->str() == MatchCompiler::makeConstString("auto"))
                autoTok = tok;
        }
        std::cout << std::endl;
        if (autoTok) {
            const ValueType * valueType = autoTok->valueType();
            std::cout << indent << "    auto valueType: " << valueType << std::endl;
            if (var->typeStartToken()->valueType()) {
                std::cout << indent << "        " << valueType->str() << std::endl;
            }
        }
    } else if (var->valueType()) {
        std::cout << indent << "   " << var->valueType()->str() << std::endl;
    }
    std::cout << indent << "mIndex: " << var->index() << std::endl;
    std::cout << indent << "mAccess: " << accessControlToString(var->accessControl()) << std::endl;
    std::cout << indent << "mFlags: " << std::endl;
    std::cout << indent << "    isMutable: " << var->isMutable() << std::endl;
    std::cout << indent << "    isStatic: " << var->isStatic() << std::endl;
    std::cout << indent << "    isExtern: " << var->isExtern() << std::endl;
    std::cout << indent << "    isLocal: " << var->isLocal() << std::endl;
    std::cout << indent << "    isConst: " << var->isConst() << std::endl;
    std::cout << indent << "    isClass: " << var->isClass() << std::endl;
    std::cout << indent << "    isArray: " << var->isArray() << std::endl;
    std::cout << indent << "    isPointer: " << var->isPointer() << std::endl;
    std::cout << indent << "    isReference: " << var->isReference() << std::endl;
    std::cout << indent << "    isRValueRef: " << var->isRValueReference() << std::endl;
    std::cout << indent << "    hasDefault: " << var->hasDefault() << std::endl;
    std::cout << indent << "    isStlType: " << var->isStlType() << std::endl;
    std::cout << indent << "mType: ";
    if (var->type()) {
        std::cout << var->type()->type() << " " << var->type()->name();
        std::cout << " " << mTokenizer.list.fileLine(var->type()->classDef);
        std::cout << " " << var->type() << std::endl;
    } else
        std::cout << "none" << std::endl;

    if (var->nameToken()) {
        const ValueType * valueType = var->nameToken()->valueType();
        std::cout << indent << "valueType: " << valueType << std::endl;
        if (valueType) {
            std::cout << indent << "    " << valueType->str() << std::endl;
        }
    }

    std::cout << indent << "mScope: " << scopeToString(var->scope(), mTokenizer) << std::endl;

    std::cout << indent << "mDimensions:";
    for (std::size_t i = 0; i < var->dimensions().size(); i++) {
        std::cout << " " << var->dimension(i);
        if (!var->dimensions()[i].known)
            std::cout << "?";
    }
    std::cout << std::endl;
}

void SymbolDatabase::printOut(const char *title) const
{
    std::cout << std::setiosflags(std::ios::boolalpha);
    if (title)
        std::cout << "\n### " << title << " ###\n";

    for (auto scope = scopeList.cbegin(); scope != scopeList.cend(); ++scope) {
        std::cout << "Scope: " << &*scope << " " << scope->type << std::endl;
        std::cout << "    className: " << scope->className << std::endl;
        std::cout << "    classDef: " << tokenToString(scope->classDef, mTokenizer) << std::endl;
        std::cout << "    bodyStart: " << tokenToString(scope->bodyStart, mTokenizer) << std::endl;
        std::cout << "    bodyEnd: " << tokenToString(scope->bodyEnd, mTokenizer) << std::endl;

        // find the function body if not implemented inline
        for (auto func = scope->functionList.cbegin(); func != scope->functionList.cend(); ++func) {
            std::cout << "    Function: " << &*func << std::endl;
            std::cout << "        name: " << tokenToString(func->tokenDef, mTokenizer) << std::endl;
            std::cout << "        type: " << functionTypeToString(func->type) << std::endl;
            std::cout << "        access: " << accessControlToString(func->access) << std::endl;
            std::cout << "        hasBody: " << func->hasBody() << std::endl;
            std::cout << "        isInline: " << func->isInline() << std::endl;
            std::cout << "        isConst: " << func->isConst() << std::endl;
            std::cout << "        hasVirtualSpecifier: " << func->hasVirtualSpecifier() << std::endl;
            std::cout << "        isPure: " << func->isPure() << std::endl;
            std::cout << "        isStatic: " << func->isStatic() << std::endl;
            std::cout << "        isStaticLocal: " << func->isStaticLocal() << std::endl;
            std::cout << "        isExtern: " << func->isExtern() << std::endl;
            std::cout << "        isFriend: " << func->isFriend() << std::endl;
            std::cout << "        isExplicit: " << func->isExplicit() << std::endl;
            std::cout << "        isDefault: " << func->isDefault() << std::endl;
            std::cout << "        isDelete: " << func->isDelete() << std::endl;
            std::cout << "        hasOverrideSpecifier: " << func->hasOverrideSpecifier() << std::endl;
            std::cout << "        hasFinalSpecifier: " << func->hasFinalSpecifier() << std::endl;
            std::cout << "        isNoExcept: " << func->isNoExcept() << std::endl;
            std::cout << "        isThrow: " << func->isThrow() << std::endl;
            std::cout << "        isOperator: " << func->isOperator() << std::endl;
            std::cout << "        hasLvalRefQual: " << func->hasLvalRefQualifier() << std::endl;
            std::cout << "        hasRvalRefQual: " << func->hasRvalRefQualifier() << std::endl;
            std::cout << "        isVariadic: " << func->isVariadic() << std::endl;
            std::cout << "        isVolatile: " << func->isVolatile() << std::endl;
            std::cout << "        hasTrailingReturnType: " << func->hasTrailingReturnType() << std::endl;
            std::cout << "        attributes:";
            if (func->isAttributeConst())
                std::cout << " const ";
            if (func->isAttributePure())
                std::cout << " pure ";
            if (func->isAttributeNoreturn())
                std::cout << " noreturn ";
            if (func->isAttributeNothrow())
                std::cout << " nothrow ";
            if (func->isAttributeConstructor())
                std::cout << " constructor ";
            if (func->isAttributeDestructor())
                std::cout << " destructor ";
            if (func->isAttributeNodiscard())
                std::cout << " nodiscard ";
            std::cout << std::endl;
            std::cout << "        noexceptArg: " << (func->noexceptArg ? func->noexceptArg->str() : "none") << std::endl;
            std::cout << "        throwArg: " << (func->throwArg ? func->throwArg->str() : "none") << std::endl;
            std::cout << "        tokenDef: " << tokenToString(func->tokenDef, mTokenizer) << std::endl;
            std::cout << "        argDef: " << tokenToString(func->argDef, mTokenizer) << std::endl;
            if (!func->isConstructor() && !func->isDestructor())
                std::cout << "        retDef: " << tokenToString(func->retDef, mTokenizer) << std::endl;
            if (func->retDef) {
                std::cout << "           ";
                for (const Token * tok = func->retDef; tok && tok != func->tokenDef && !match186(tok); tok = tok->next())
                    std::cout << " " << tokenType(tok);
                std::cout << std::endl;
            }
            std::cout << "        retType: " << func->retType << std::endl;

            if (const ValueType* valueType = func->tokenDef->next()->valueType()) {
                std::cout << "        valueType: " << valueType << std::endl;
                std::cout << "            " << valueType->str() << std::endl;
            }

            if (func->hasBody()) {
                std::cout << "        token: " << tokenToString(func->token, mTokenizer) << std::endl;
                std::cout << "        arg: " << tokenToString(func->arg, mTokenizer) << std::endl;
            }
            std::cout << "        nestedIn: " << scopeToString(func->nestedIn, mTokenizer) << std::endl;
            std::cout << "        functionScope: " << scopeToString(func->functionScope, mTokenizer) << std::endl;

            for (auto var = func->argumentList.cbegin(); var != func->argumentList.cend(); ++var) {
                std::cout << "        Variable: " << &*var << std::endl;
                printVariable(&*var, "            ");
            }
        }

        for (auto var = scope->varlist.cbegin(); var != scope->varlist.cend(); ++var) {
            std::cout << "    Variable: " << &*var << std::endl;
            printVariable(&*var, "        ");
        }

        if (scope->type == ScopeType::eEnum) {
            std::cout << "    enumType: ";
            if (scope->enumType) {
                std::cout << scope->enumType->stringify(false, true, false);
            } else
                std::cout << "int";
            std::cout << std::endl;
            std::cout << "    enumClass: " << scope->enumClass << std::endl;
            for (const Enumerator &enumerator : scope->enumeratorList) {
                std::cout << "        Enumerator: " << enumerator.name->str() << " = ";
                if (enumerator.value_known)
                    std::cout << enumerator.value;

                if (enumerator.start) {
                    const Token * tok = enumerator.start;
                    std::cout << (enumerator.value_known ? " " : "") << "[" << tok->str();
                    while (tok && tok != enumerator.end) {
                        if (tok->next())
                            std::cout << " " << tok->strAt(1);
                        tok = tok->next();
                    }

                    std::cout << "]";
                }

                std::cout << std::endl;
            }
        }

        std::cout << "    nestedIn: " << scope->nestedIn;
        if (scope->nestedIn) {
            std::cout << " " << scope->nestedIn->type << " "
                      << scope->nestedIn->className;
        }
        std::cout << std::endl;

        std::cout << "    definedType: " << scope->definedType << std::endl;

        std::cout << "    nestedList[" << scope->nestedList.size() << "] = (";

        std::size_t count = scope->nestedList.size();
        for (auto nsi = scope->nestedList.cbegin(); nsi != scope->nestedList.cend(); ++nsi) {
            std::cout << " " << (*nsi) << " " << (*nsi)->type << " " << (*nsi)->className;
            if (count-- > 1)
                std::cout << ",";
        }

        std::cout << " )" << std::endl;

        for (auto use = scope->usingList.cbegin(); use != scope->usingList.cend(); ++use) {
            std::cout << "    using: " << use->scope << " " << use->start->strAt(2);
            const Token *tok1 = use->start->tokAt(3);
            while (tok1 && tok1->str() == MatchCompiler::makeConstString("::")) {
                std::cout << "::" << tok1->strAt(1);
                tok1 = tok1->tokAt(2);
            }
            std::cout << " " << mTokenizer.list.fileLine(use->start) << std::endl;
        }

        std::cout << "    functionOf: " << scopeToString(scope->functionOf, mTokenizer) << std::endl;

        std::cout << "    function: " << scope->function;
        if (scope->function)
            std::cout << " " << scope->function->name();
        std::cout << std::endl;
    }

    for (auto type = typeList.cbegin(); type != typeList.cend(); ++type) {
        std::cout << "Type: " << &(*type) << std::endl;
        std::cout << "    name: " << type->name() << std::endl;
        std::cout << "    classDef: " << tokenToString(type->classDef, mTokenizer) << std::endl;
        std::cout << "    classScope: " << type->classScope << std::endl;
        std::cout << "    enclosingScope: " << type->enclosingScope;
        if (type->enclosingScope) {
            std::cout << " " << type->enclosingScope->type << " "
                      << type->enclosingScope->className;
        }
        std::cout << std::endl;
        std::cout << "    needInitialization: " << (type->needInitialization == Type::NeedInitialization::Unknown ? "Unknown" :
                                                    type->needInitialization == Type::NeedInitialization::True ? "True" :
                                                    type->needInitialization == Type::NeedInitialization::False ? "False" :
                                                    "Invalid") << std::endl;

        std::cout << "    derivedFrom[" << type->derivedFrom.size() << "] = (";
        std::size_t count = type->derivedFrom.size();
        for (const Type::BaseInfo & i : type->derivedFrom) {
            if (i.isVirtual)
                std::cout << "Virtual ";

            std::cout << (i.access == AccessControl::Public    ? " Public" :
                          i.access == AccessControl::Protected ? " Protected" :
                          i.access == AccessControl::Private   ? " Private" :
                          " Unknown");

            if (i.type)
                std::cout << " " << i.type;
            else
                std::cout << " Unknown";

            std::cout << " " << i.name;
            if (count-- > 1)
                std::cout << ",";
        }

        std::cout << " )" << std::endl;

        std::cout << "    friendList[" << type->friendList.size() << "] = (";
        for (size_t i = 0; i < type->friendList.size(); i++) {
            if (type->friendList[i].type)
                std::cout << type->friendList[i].type;
            else
                std::cout << " Unknown";

            std::cout << ' ';
            if (type->friendList[i].nameEnd)
                std::cout << type->friendList[i].nameEnd->str();
            if (i+1 < type->friendList.size())
                std::cout << ',';
        }

        std::cout << " )" << std::endl;
    }

    for (std::size_t i = 1; i < mVariableList.size(); i++) {
        std::cout << "mVariableList[" << i << "]: " << mVariableList[i];
        if (mVariableList[i]) {
            std::cout << " " << mVariableList[i]->name() << " "
                      << mTokenizer.list.fileLine(mVariableList[i]->nameToken());
        }
        std::cout << std::endl;
    }
    std::cout << std::resetiosflags(std::ios::boolalpha);
}

void SymbolDatabase::printXml(std::ostream &out) const
{
    std::string outs;

    std::set<const Variable *> variables;

    // Scopes..
    outs += "  <scopes>\n";
    for (auto scope = scopeList.cbegin(); scope != scopeList.cend(); ++scope) {
        outs += "    <scope";
        outs += " id=\"";
        outs += id_string(&*scope);
        outs += "\"";
        outs += " type=\"";
        outs += scopeTypeToString(scope->type);
        outs += "\"";
        if (!scope->className.empty()) {
            outs += " className=\"";
            outs += ErrorLogger::toxml(scope->className);
            outs += "\"";
        }
        if (scope->bodyStart) {
            outs += " bodyStart=\"";
            outs += id_string(scope->bodyStart);
            outs += '\"';
        }
        if (scope->bodyEnd) {
            outs += " bodyEnd=\"";
            outs += id_string(scope->bodyEnd);
            outs += '\"';
        }
        if (scope->nestedIn) {
            outs += " nestedIn=\"";
            outs += id_string(scope->nestedIn);
            outs += "\"";
        }
        if (scope->function) {
            outs += " function=\"";
            outs += id_string(scope->function);
            outs += "\"";
        }
        if (scope->definedType) {
            outs += " definedType=\"";
            outs += id_string(scope->definedType);
            outs += "\"";
        }
        if (scope->functionList.empty() && scope->varlist.empty())
            outs += "/>\n";
        else {
            outs += ">\n";
            if (!scope->functionList.empty()) {
                outs += "      <functionList>\n";
                for (auto function = scope->functionList.cbegin(); function != scope->functionList.cend(); ++function) {
                    outs += "        <function id=\"";
                    outs += id_string(&*function);
                    outs += "\" token=\"";
                    outs += id_string(function->token);
                    outs += "\" tokenDef=\"";
                    outs += id_string(function->tokenDef);
                    outs += "\" name=\"";
                    outs += ErrorLogger::toxml(function->name());
                    outs += '\"';
                    outs += " type=\"";
                    outs += functionTypeToString(function->type);
                    outs += '\"';
                    if (function->nestedIn->definedType) {
                        if (function->hasVirtualSpecifier())
                            outs += " hasVirtualSpecifier=\"true\"";
                        else if (function->isImplicitlyVirtual())
                            outs += " isImplicitlyVirtual=\"true\"";
                    }
                    if (function->access == AccessControl::Public || function->access == AccessControl::Protected || function->access == AccessControl::Private) {
                        outs += " access=\"";
                        outs += accessControlToString(function->access);
                        outs +="\"";
                    }
                    if (function->isOperator())
                        outs += " isOperator=\"true\"";
                    if (function->isExplicit())
                        outs += " isExplicit=\"true\"";
                    if (function->hasOverrideSpecifier())
                        outs += " hasOverrideSpecifier=\"true\"";
                    if (function->hasFinalSpecifier())
                        outs += " hasFinalSpecifier=\"true\"";
                    if (function->isInlineKeyword())
                        outs += " isInlineKeyword=\"true\"";
                    if (function->isStatic())
                        outs += " isStatic=\"true\"";
                    if (function->isFriend())
                        outs += " isFriend=\"true\"";
                    if (function->isAttributeNoreturn())
                        outs += " isAttributeNoreturn=\"true\"";
                    if (const Function* overriddenFunction = function->getOverriddenFunction()) {
                        outs += " overriddenFunction=\"";
                        outs += id_string(overriddenFunction);
                        outs += "\"";
                    }
                    if (function->isAttributeConst())
                        outs += " isAttributeConst=\"true\"";
                    if (function->isAttributePure())
                        outs += " isAttributePure=\"true\"";
                    if (function->argCount() == 0U)
                        outs += "/>\n";
                    else {
                        outs += ">\n";
                        for (unsigned int argnr = 0; argnr < function->argCount(); ++argnr) {
                            const Variable *arg = function->getArgumentVar(argnr);
                            outs += "          <arg nr=\"";
                            outs += std::to_string(argnr+1);
                            outs += "\" variable=\"";
                            outs += id_string(arg);
                            outs += "\"/>\n";
                            variables.insert(arg);
                        }
                        outs += "        </function>\n";
                    }
                }
                outs += "      </functionList>\n";
            }
            if (!scope->varlist.empty()) {
                outs += "      <varlist>\n";
                for (auto var = scope->varlist.cbegin(); var != scope->varlist.cend(); ++var) {
                    outs += "        <var id=\"";
                    outs += id_string(&*var);
                    outs += "\"/>\n";
                }
                outs += "      </varlist>\n";
            }
            outs += "    </scope>\n";
        }
    }
    outs += "  </scopes>\n";

    if (!typeList.empty()) {
        outs += "  <types>\n";
        for (const Type& type:typeList) {
            outs += "    <type id=\"";
            outs += id_string(&type);
            outs += "\" classScope=\"";
            outs += id_string(type.classScope);
            outs += "\"";
            if (type.derivedFrom.empty()) {
                outs += "/>\n";
                continue;
            }
            outs += ">\n";
            for (const Type::BaseInfo& baseInfo: type.derivedFrom) {
                outs += "      <derivedFrom";
                outs += " access=\"";
                outs += accessControlToString(baseInfo.access);
                outs += "\"";
                outs += " type=\"";
                outs += id_string(baseInfo.type);
                outs += "\"";
                outs += " isVirtual=\"";
                outs += bool_to_string(baseInfo.isVirtual);
                outs += "\"";
                outs += " nameTok=\"";
                outs += id_string(baseInfo.nameTok);
                outs += "\"";
                outs += "/>\n";
            }
            outs += "    </type>\n";
        }
        outs += "  </types>\n";
    }

    // Variables..
    for (const Variable *var : mVariableList)
        variables.insert(var);
    outs += "  <variables>\n";
    for (const Variable *var : variables) {
        if (!var)
            continue;
        outs += "    <var id=\"";
        outs += id_string(var);
        outs += '\"';
        outs += " nameToken=\"";
        outs += id_string(var->nameToken());
        outs += '\"';
        outs += " typeStartToken=\"";
        outs += id_string(var->typeStartToken());
        outs += '\"';
        outs += " typeEndToken=\"";
        outs += id_string(var->typeEndToken());
        outs += '\"';
        outs += " access=\"";
        outs += accessControlToString(var->mAccess);
        outs += '\"';
        outs += " scope=\"";
        outs += id_string(var->scope());
        outs += '\"';
        if (var->valueType()) {
            outs += " constness=\"";
            outs += std::to_string(var->valueType()->constness);
            outs += '\"';

            outs += " volatileness=\"";
            outs += std::to_string(var->valueType()->volatileness);
            outs += '\"';
        }
        outs += " isArray=\"";
        outs += bool_to_string(var->isArray());
        outs += '\"';
        outs += " isClass=\"";
        outs += bool_to_string(var->isClass());
        outs += '\"';
        outs += " isConst=\"";
        outs += bool_to_string(var->isConst());
        outs += '\"';
        outs += " isExtern=\"";
        outs += bool_to_string(var->isExtern());
        outs += '\"';
        outs += " isPointer=\"";
        outs += bool_to_string(var->isPointer());
        outs += '\"';
        outs += " isReference=\"";
        outs += bool_to_string(var->isReference());
        outs += '\"';
        outs += " isStatic=\"";
        outs += bool_to_string(var->isStatic());
        outs += '\"';
        outs += " isVolatile=\"";
        outs += bool_to_string(var->isVolatile());
        outs += '\"';
        outs += "/>\n";
    }
    outs += "  </variables>\n";

    out << outs;
}

//---------------------------------------------------------------------------

static const Type* findVariableTypeIncludingUsedNamespaces(const Scope* scope, const Token* typeTok)
{
    const Type* argType = scope->symdb.findVariableType(scope, typeTok);
    if (argType)
        return argType;

    // look for variable type in any using namespace in this scope or above
    while (scope) {
        for (const Scope::UsingInfo &ui : scope->usingList) {
            if (ui.scope) {
                argType = scope->symdb.findVariableType(ui.scope, typeTok);
                if (argType)
                    return argType;
            }
        }
        scope = scope->nestedIn;
    }
    return nullptr;
}

//---------------------------------------------------------------------------

void Function::addArguments(const Scope *scope)
{
    // check for non-empty argument list "( ... )"
    const Token * start = arg ? arg : argDef;
    if (!match29(start))
        return;
    if (!(start && start->link() != start->next() && !match156(start)))
        return;

    unsigned int count = 0;

    for (const Token* tok = start->next(); tok; tok = tok->next()) {
        if (match162(tok))
            return; // Syntax error

        const Token* startTok = tok;
        const Token* endTok   = nullptr;
        const Token* nameTok  = nullptr;

        do {
            if (match37(tok)) {
                tok = tok->linkAt(1)->next();
                continue;
            }
            if (tok != startTok && !nameTok && match187(tok)) {
                nameTok = tok->tokAt(2);
                endTok = nameTok->previous();
                tok = tok->link();
            } else if (tok != startTok && !nameTok && match188(tok) && match189(tok->link()->linkAt(1))) {
                nameTok = tok->link()->previous();
                endTok = nameTok->previous();
                tok = tok->link()->linkAt(1);
            } else if (tok != startTok && !nameTok && match190(tok)) {
                nameTok = tok->tokAt(2);
                endTok = nameTok->previous();
                tok = tok->link();
            } else if (tok->varId() != 0) {
                nameTok = tok;
                endTok = tok->previous();
            } else if (tok->str() == MatchCompiler::makeConstString("[")) {
                // skip array dimension(s)
                tok = tok->link();
                while (tok->strAt(1) == MatchCompiler::makeConstString("["))
                    tok = tok->linkAt(1);
            } else if (tok->str() == MatchCompiler::makeConstString("<")) {
                tok = tok->link();
                if (!tok) // something is wrong so just bail out
                    return;
            }

            tok = tok->next();

            if (!tok) // something is wrong so just bail
                return;
        } while (tok->str() != MatchCompiler::makeConstString(",") && tok->str() != MatchCompiler::makeConstString(")") && tok->str() != MatchCompiler::makeConstString("="));

        const Token *typeTok = startTok;
        // skip over stuff to get to type
        while (match191(typeTok))
            typeTok = typeTok->next();
        if (match162(typeTok)) { // #8333
            scope->symdb.mTokenizer.syntaxError(typeTok);
        }
        if (match192(typeTok) && match193(typeTok->linkAt(1)))
            typeTok = typeTok->linkAt(1)->tokAt(2);
        // skip over qualification
        while (match35(typeTok)) {
            typeTok = typeTok->tokAt(2);
            if (match192(typeTok) && match193(typeTok->linkAt(1)))
                typeTok = typeTok->linkAt(1)->tokAt(2);
        }

        // check for argument with no name or missing varid
        if (!endTok) {
            if (tok->previous()->isName() && !match138(tok->tokAt(-1))) {
                if (tok->previous() != typeTok) {
                    nameTok = tok->previous();
                    endTok = nameTok->previous();

                    if (hasBody())
                        scope->symdb.debugMessage(nameTok, "varid0", "Function::addArguments found argument \'" + nameTok->str() + "\' with varid 0.");
                } else
                    endTok = typeTok;
            } else
                endTok = tok->previous();
        }

        const ::Type *argType = nullptr;
        if (!typeTok->isStandardType()) {
            argType = findVariableTypeIncludingUsedNamespaces(scope, typeTok);

            // save type
            const_cast<Token *>(typeTok)->type(argType);
        }

        // skip default values
        if (tok->str() == MatchCompiler::makeConstString("=")) {
            do {
                if (tok->link() && match194(tok))
                    tok = tok->link();
                tok = tok->next();
            } while (tok->str() != MatchCompiler::makeConstString(",") && tok->str() != MatchCompiler::makeConstString(")"));
        }

        // skip over stuff before type
        while (match195(startTok))
            startTok = startTok->next();

        if (startTok == nameTok)
            break;

        argumentList.emplace_back(nameTok, startTok, endTok, count++, AccessControl::Argument, argType, functionScope, scope->symdb.mSettings);

        if (tok->str() == MatchCompiler::makeConstString(")")) {
            // check for a variadic function or a variadic template function
            if (match196(endTok))
                isVariadic(true);

            break;
        }
    }

    // count default arguments
    for (const Token* tok = argDef->next(); tok && tok != argDef->link(); tok = tok->next()) {
        if (tok->str() == MatchCompiler::makeConstString("=")) {
            initArgCount++;
            if (tok->strAt(1) == MatchCompiler::makeConstString("[")) {
                const Token* lambdaStart = tok->next();
                if (type == FunctionType::eLambda)
                    tok = findLambdaEndTokenWithoutAST(lambdaStart);
                else {
                    tok = findLambdaEndToken(lambdaStart);
                    if (!tok)
                        tok = findLambdaEndTokenWithoutAST(lambdaStart);
                }
                if (!tok)
                    throw InternalError(lambdaStart, "Analysis failed (lambda not recognized). If the code is valid then please report this failure.", InternalError::INTERNAL);
            }
        }
    }
}

bool Function::isImplicitlyVirtual(bool defaultVal, bool* pFoundAllBaseClasses) const
{
    if (hasVirtualSpecifier() || hasOverrideSpecifier() || hasFinalSpecifier())
        return true;
    bool foundAllBaseClasses = true;
    if (getOverriddenFunction(&foundAllBaseClasses)) //If it overrides a base class's method then it's virtual
        return true;
    if (pFoundAllBaseClasses)
        *pFoundAllBaseClasses = foundAllBaseClasses;
    if (foundAllBaseClasses) //If we've seen all the base classes and none of the above were true then it must not be virtual
        return false;
    return defaultVal; //If we can't see all the bases classes then we can't say conclusively
}

std::vector<const Function*> Function::getOverloadedFunctions() const
{
    std::vector<const Function*> result;
    const Scope* scope = nestedIn;

    while (scope) {
        const bool isMemberFunction = scope->isClassOrStruct() && !isStatic();
        for (auto it = utils::as_const(scope->functionMap).find(tokenDef->str());
             it != scope->functionMap.end() && it->first == tokenDef->str();
             ++it) {
            const Function* func = it->second;
            if (isMemberFunction && isMemberFunction == func->isStatic())
                continue;
            result.push_back(func);
        }
        if (isMemberFunction)
            break;
        scope = scope->nestedIn;
    }

    return result;
}

const Function *Function::getOverriddenFunction(bool *foundAllBaseClasses) const
{
    if (foundAllBaseClasses)
        *foundAllBaseClasses = true;
    if (!nestedIn->isClassOrStruct())
        return nullptr;
    return getOverriddenFunctionRecursive(nestedIn->definedType, foundAllBaseClasses);
}

// prevent recursion if base is the same except for different template parameters
static bool isDerivedFromItself(const std::string& thisName, const std::string& baseName)
{
    if (thisName.back() != '>')
        return false;
    const auto pos = thisName.find('<');
    if (pos == std::string::npos)
        return false;
    return thisName.compare(0, pos + 1, baseName, 0, pos + 1) == 0;
}

const Function * Function::getOverriddenFunctionRecursive(const ::Type* baseType, bool *foundAllBaseClasses) const
{
    // check each base class
    for (const ::Type::BaseInfo & i : baseType->derivedFrom) {
        const ::Type* derivedFromType = i.type;
        // check if base class exists in database
        if (!derivedFromType || !derivedFromType->classScope) {
            if (foundAllBaseClasses)
                *foundAllBaseClasses = false;
            continue;
        }

        const Scope *parent = derivedFromType->classScope;

        // check if function defined in base class
        auto range = utils::as_const(parent->functionMap).equal_range(tokenDef->str());
        for (auto it = range.first; it != range.second; ++it) {
            const Function * func = it->second;
            if (func->isImplicitlyVirtual()) { // Base is virtual and of same name
                const Token *temp1 = func->tokenDef->previous();
                const Token *temp2 = tokenDef->previous();
                bool match = true;

                // check for matching return parameters
                while (!match197(temp1)) {
                    if (temp1->str() != temp2->str() &&
                        !(temp1->type() && temp2->type() && temp2->type()->isDerivedFrom(temp1->type()->name()))) {
                        match = false;
                        break;
                    }

                    temp1 = temp1->previous();
                    temp2 = temp2->previous();
                }

                // check for matching function parameters
                match = match && argsMatch(baseType->classScope, func->argDef, argDef, emptyString, 0);

                // check for matching cv-ref qualifiers
                match = match
                        && isConst() == func->isConst()
                        && isVolatile() == func->isVolatile()
                        && hasRvalRefQualifier() == func->hasRvalRefQualifier()
                        && hasLvalRefQualifier() == func->hasLvalRefQualifier();

                // it's a match
                if (match) {
                    return func;
                }
            }
        }

        if (isDestructor()) {
            auto it = std::find_if(parent->functionList.begin(), parent->functionList.end(), [](const Function& f) {
                return f.isDestructor() && f.isImplicitlyVirtual();
            });
            if (it != parent->functionList.end())
                return &*it;
        }

        if (!derivedFromType->derivedFrom.empty() && !derivedFromType->hasCircularDependencies() && !isDerivedFromItself(baseType->classScope->className, i.name)) {
            // avoid endless recursion, see #5289 Crash: Stack overflow in isImplicitlyVirtual_rec when checking SVN and
            // #5590 with a loop within the class hierarchy.
            const Function *func = getOverriddenFunctionRecursive(derivedFromType, foundAllBaseClasses);
            if (func) {
                return func;
            }
        }
    }
    return nullptr;
}

const Variable* Function::getArgumentVar(nonneg int num) const
{
    if (num < argumentList.size()) {
        auto it = argumentList.begin();
        std::advance(it, num);
        return &*it;
    }
    return nullptr;
}


//---------------------------------------------------------------------------

Scope::Scope(const SymbolDatabase &symdb_, const Token *classDef_, const Scope *nestedIn_, ScopeType type_, const Token *start_) :
    symdb(symdb_),
    classDef(classDef_),
    nestedIn(nestedIn_),
    type(type_)
{
    setBodyStartEnd(start_);
}

Scope::Scope(const SymbolDatabase &symdb_, const Token *classDef_, const Scope *nestedIn_) :
    symdb(symdb_),
    classDef(classDef_),
    nestedIn(nestedIn_)
{
    const Token *nameTok = classDef;
    if (!classDef) {
        type = ScopeType::eGlobal;
    } else if (classDef->str() == MatchCompiler::makeConstString("class") && classDef->isCpp()) {
        type = ScopeType::eClass;
        nameTok = nameTok->next();
    } else if (classDef->str() == MatchCompiler::makeConstString("struct")) {
        type = ScopeType::eStruct;
        nameTok = nameTok->next();
    } else if (classDef->str() == MatchCompiler::makeConstString("union")) {
        type = ScopeType::eUnion;
        nameTok = nameTok->next();
    } else if (classDef->str() == MatchCompiler::makeConstString("namespace")) {
        type = ScopeType::eNamespace;
        nameTok = nameTok->next();
    } else if (classDef->str() == MatchCompiler::makeConstString("enum")) {
        type = ScopeType::eEnum;
        nameTok = nameTok->next();
        if (nameTok->str() == MatchCompiler::makeConstString("class")) {
            enumClass = true;
            nameTok = nameTok->next();
        }
    } else if (classDef->str() == MatchCompiler::makeConstString("[")) {
        type = ScopeType::eLambda;
    } else {
        type = ScopeType::eFunction;
    }
    // skip over qualification if present
    nameTok = skipScopeIdentifiers(nameTok);
    if (nameTok && ((type == ScopeType::eEnum && match198(nameTok)) || nameTok->str() != MatchCompiler::makeConstString("{"))) // anonymous and unnamed structs/unions don't have a name
        className = nameTok->str();
}

AccessControl Scope::defaultAccess() const
{
    switch (type) {
    case ScopeType::eGlobal:
        return AccessControl::Global;
    case ScopeType::eClass:
        return AccessControl::Private;
    case ScopeType::eStruct:
        return AccessControl::Public;
    case ScopeType::eUnion:
        return AccessControl::Public;
    case ScopeType::eNamespace:
        return AccessControl::Namespace;
    default:
        return AccessControl::Local;
    }
}

void Scope::addVariable(const Token *token_, const Token *start_, const Token *end_,
                        AccessControl access_, const Type *type_, const Scope *scope_)
{
    // keep possible size_t -> int truncation outside emplace_back() to have a single line
    // C4267 VC++ warning instead of several dozens lines
    const int varIndex = varlist.size();
    varlist.emplace_back(token_, start_, end_, varIndex, access_, type_, scope_, scope_->symdb.mSettings);
}

// Get variable list..
void Scope::getVariableList()
{
    if (!bodyStartList.empty()) {
        for (const Token *bs: bodyStartList)
            getVariableList(bs->next(), bs->link());
    }

    // global scope
    else if (type == ScopeType::eGlobal)
        getVariableList(symdb.mTokenizer.tokens(), nullptr);

    // forward declaration
    else
        return;
}

void Scope::getVariableList(const Token* start, const Token* end)
{
    // Variable declared in condition: if (auto x = bar())
    if (match199(classDef) && match121(classDef->next()->astOperand2())) {
        checkVariable(classDef->tokAt(2), defaultAccess());
    }

    AccessControl varaccess = defaultAccess();
    for (const Token *tok = start; tok && tok != end; tok = tok->next()) {
        // syntax error?
        if (tok->next() == nullptr)
            break;

        // Is it a function?
        if (tok->str() == MatchCompiler::makeConstString("{")) {
            tok = tok->link();
            continue;
        }

        // Is it a nested class or structure?
        if (tok->isKeyword() && match200(tok)) {
            tok = tok->tokAt(2);
            while (tok && tok->str() != MatchCompiler::makeConstString("{"))
                tok = tok->next();
            if (tok) {
                // skip implementation
                tok = tok->link();
                continue;
            }
            break;
        }
        if (tok->isKeyword() && match38(tok)) {
            if (match201(tok->linkAt(1))) {
                tok = tok->linkAt(1)->tokAt(2);
                continue;
            }
            if (match21(tok->linkAt(1))) {
                tok = tok->next();
                continue;
            }
        }

        // Borland C++: Skip all variables in the __published section.
        // These are automatically initialized.
        else if (tok->str() == MatchCompiler::makeConstString("__published:")) {
            for (; tok; tok = tok->next()) {
                if (tok->str() == MatchCompiler::makeConstString("{"))
                    tok = tok->link();
                if (match202(tok->next()))
                    break;
            }
            if (tok)
                continue;
            break;
        }

        // "private:" "public:" "protected:" etc
        else if (tok->str() == MatchCompiler::makeConstString("public:")) {
            varaccess = AccessControl::Public;
            continue;
        } else if (tok->str() == MatchCompiler::makeConstString("protected:")) {
            varaccess = AccessControl::Protected;
            continue;
        } else if (tok->str() == MatchCompiler::makeConstString("private:")) {
            varaccess = AccessControl::Private;
            continue;
        }

        // Is it a forward declaration?
        else if (tok->isKeyword() && match33(tok)) {
            tok = tok->tokAt(2);
            continue;
        }

        // Borland C++: Ignore properties..
        else if (tok->str() == MatchCompiler::makeConstString("__property"))
            continue;

        // skip return, goto and delete
        else if (tok->isKeyword() && match203(tok)) {
            while (tok->next() &&
                   tok->strAt(1) != MatchCompiler::makeConstString(";") &&
                   tok->strAt(1) != MatchCompiler::makeConstString("}") /* ticket #4994 */) {
                tok = tok->next();
            }
            continue;
        }

        // skip case/default
        if (tok->isKeyword() && match204(tok)) {
            while (tok->next() && !match205(tok->next()))
                tok = tok->next();
            continue;
        }

        // Search for start of statement..
        if (tok->previous() && !match206(tok->previous()))
            continue;
        if (tok->str() == MatchCompiler::makeConstString(";"))
            continue;

        tok = checkVariable(tok, varaccess);

        if (!tok)
            break;
    }
}

const Token *Scope::checkVariable(const Token *tok, AccessControl varaccess)
{
    // Is it a throw..?
    if (tok->isKeyword() && match207(tok) &&
        match30(tok->linkAt(2))) {
        return tok->linkAt(2);
    }

    if (tok->isKeyword() && match208(tok) &&
        match30(tok->linkAt(4))) {
        return tok->linkAt(4);
    }

    // friend?
    if (tok->isKeyword() && match209(tok) && tok->next()->varId() == 0) {
        const Token *next = findmatch210(tok->tokAt(2)) ;
        if (next && next->str() == MatchCompiler::makeConstString("{"))
            next = next->link();
        return next;
    }

    // skip const|volatile|static|mutable|extern
    while (tok && tok->isKeyword() && match211(tok)) {
        tok = tok->next();
    }

    // the start of the type tokens does not include the above modifiers
    const Token *typestart = tok;

    // C++17 structured bindings
    if (tok && tok->isCpp() && (symdb.mSettings.standards.cpp >= Standards::CPP17) && match212(tok)) {
        const Token *typeend = findmatch213(typestart) ->previous();
        for (tok = typeend->tokAt(2); match214(tok); tok = tok->next()) {
            if (tok->varId())
                addVariable(tok, typestart, typeend, varaccess, nullptr, this);
        }
        return typeend->linkAt(1);
    }

    while (tok && tok->isKeyword() && match215(tok)) {
        tok = tok->next();
    }

    // This is the start of a statement
    const Token *vartok = nullptr;
    const Token *typetok = nullptr;

    if (tok && isVariableDeclaration(tok, vartok, typetok)) {
        const Token* const orig = tok;
        // If the vartok was set in the if-blocks above, create a entry for this variable..
        tok = vartok->next();
        while (match216(tok))
            tok = tok->link()->next();

        if (vartok->varId() == 0) {
            if (!vartok->isBoolean())
                symdb.debugMessage(vartok, "varid0", "Scope::checkVariable found variable \'" + vartok->str() + "\' with varid 0.");
            return tok;
        }

        const Type *vType = nullptr;

        if (typetok) {
            vType = findVariableTypeIncludingUsedNamespaces(this, typetok);

            const_cast<Token *>(typetok)->type(vType);
        }

        // skip "enum" or "struct"
        if (match217(typestart))
            typestart = typestart->next();

        addVariable(vartok, typestart, vartok->previous(), varaccess, vType, this);

        if (type == ScopeType::eFor && orig->strAt(-2) == MatchCompiler::makeConstString("for")) {
            for (const Token* tok2 = tok; tok2 && !match218(tok2); tok2 = tok2->next()) {
                if (tok2->link() && precedes(tok2, tok2->link())) {
                    tok2 = tok2->link();
                    continue;
                }
                if (match219(tok2)) {
                    if (tok2->next()->varId() == 0) {
                        symdb.debugMessage(tok2->next(), "varid0", "Scope::checkVariable found variable \'" + tok2->strAt(1) + "\' with varid 0.");
                        return tok;
                    }
                    addVariable(tok2->next(), typestart, vartok->previous(), varaccess, vType, this);
                }
            }
        }
    }

    return tok;
}

const Variable *Scope::getVariable(const std::string &varname) const
{
    auto it = std::find_if(varlist.begin(), varlist.end(), [&varname](const Variable& var) {
        return var.name() == varname;
    });
    if (it != varlist.end())
        return &*it;

    if (definedType) {
        for (const Type::BaseInfo& baseInfo: definedType->derivedFrom) {
            if (baseInfo.type && baseInfo.type->classScope) {
                if (const Variable* var = baseInfo.type->classScope->getVariable(varname))
                    return var;
            }
        }
    }
    return nullptr;
}

static const Token* skipPointers(const Token* tok)
{
    while (match82(tok) || (match220(tok) && match221(tok->link()->next()))) {
        tok = tok->next();
        if (tok && tok->strAt(-1) == MatchCompiler::makeConstString("(") && match35(tok))
            tok = tok->tokAt(2);
    }

    if (match222(tok) && match223(tok->link()->previous()) &&
        (tok->tokAt(-1)->isStandardType() || tok->tokAt(-1)->isKeyword() || tok->strAt(-1) == MatchCompiler::makeConstString("*"))) {
        const Token *tok2 = skipPointers(tok->next());
        if (match135(tok2) && match223(tok2->linkAt(1)))
            return tok2;
    }

    return tok;
}

static const Token* skipPointersAndQualifiers(const Token* tok)
{
    tok = skipPointers(tok);
    while (match224(tok)) {
        tok = tok->next();
        tok = skipPointers(tok);
    }

    return tok;
}

bool Scope::isVariableDeclaration(const Token* const tok, const Token*& vartok, const Token*& typetok) const
{
    if (!tok)
        return false;

    const bool isCPP = tok->isCpp();

    if (isCPP && match225(tok))
        return false;

    const bool isCPP11 = isCPP && symdb.mSettings.standards.cpp >= Standards::CPP11;

    if (isCPP11 && tok->str() == MatchCompiler::makeConstString("using"))
        return false;

    const Token* localTypeTok = skipScopeIdentifiers(tok);
    const Token* localVarTok = nullptr;

    while (match227(localTypeTok) && match226(localTypeTok->linkAt(1)))
        localTypeTok = localTypeTok->linkAt(1)->next();

    if (match192(localTypeTok)) {
        if (match228(tok))
            return false;

        const Token* closeTok = localTypeTok->linkAt(1);
        if (closeTok) {
            localVarTok = skipPointers(closeTok->next());

            if (match229(localVarTok)) {
                if (localVarTok->strAt(3) != MatchCompiler::makeConstString("(") ||
                    match230(localVarTok->linkAt(3))) {
                    localTypeTok = localVarTok->next();
                    localVarTok = localVarTok->tokAt(2);
                }
            }
        }
    } else if (match231(localTypeTok)) {

        if (isCPP11 && match37(localTypeTok) && match232(localTypeTok->linkAt(1)))
            localVarTok = skipPointersAndQualifiers(localTypeTok->linkAt(1)->next());
        else {
            localVarTok = skipPointersAndQualifiers(localTypeTok->next());
            if (isCPP11 && match37(localVarTok) && match232(localVarTok->linkAt(1)))
                localVarTok = skipPointersAndQualifiers(localVarTok->linkAt(1)->next());
        }
    }

    if (!localVarTok)
        return false;

    if (match222(localVarTok) && match215(localTypeTok->previous())) // not a function call
        localVarTok = localVarTok->next();
    while (match233(localVarTok))
        localVarTok = localVarTok->next();

    if (match234(localVarTok) || (localVarTok && localVarTok->varId() && localVarTok->strAt(1) == MatchCompiler::makeConstString(":"))) {
        vartok = localVarTok;
        typetok = localTypeTok;
    } else if (match235(localVarTok) && localVarTok->str() != MatchCompiler::makeConstString("operator")) {
        vartok = localVarTok;
        typetok = localTypeTok;
    } else if (localVarTok && localVarTok->varId() && match236(localVarTok) &&
               match237(localVarTok->linkAt(1))) {
        vartok = localVarTok;
        typetok = localTypeTok;
    } else if (type == ScopeType::eCatch &&
               match238(localVarTok)) {
        vartok = localVarTok;
        typetok = localTypeTok;
    }

    return nullptr != vartok;
}

const Token * Scope::addEnum(const Token * tok)
{
    const Token * tok2 = tok->next();

    // skip over class if present
    if (tok2->isCpp() && tok2->str() == MatchCompiler::makeConstString("class"))
        tok2 = tok2->next();

    // skip over name
    tok2 = tok2->next();

    // save type if present
    if (tok2->str() == MatchCompiler::makeConstString(":")) {
        tok2 = tok2->next();

        enumType = tok2;
        while (match12(tok2))
            tok2 = tok2->next();
    }

    // add enumerators
    if (tok2->str() == MatchCompiler::makeConstString("{")) {
        const Token * end = tok2->link();
        tok2 = tok2->next();

        while (match239(tok2) ||
               (match24(tok2) && match240(tok2->linkAt(1)))) {
            Enumerator enumerator(this);

            // save enumerator name
            enumerator.name = tok2;

            // skip over name
            tok2 = tok2->next();

            if (tok2->str() == MatchCompiler::makeConstString("=")) {
                // skip over "="
                tok2 = tok2->next();

                if (tok2->str() == MatchCompiler::makeConstString("}"))
                    return nullptr;

                enumerator.start = tok2;

                while (!match241(tok2)) {
                    if (tok2->link())
                        tok2 = tok2->link();
                    enumerator.end = tok2;
                    tok2 = tok2->next();
                }
            } else if (tok2->str() == MatchCompiler::makeConstString("(")) {
                // skip over unknown macro
                tok2 = tok2->link()->next();
            }

            if (tok2->str() == MatchCompiler::makeConstString(",")) {
                enumeratorList.push_back(enumerator);
                tok2 = tok2->next();
            } else if (tok2->str() == MatchCompiler::makeConstString("}")) {
                enumeratorList.push_back(enumerator);
                break;
            }
        }

        if (tok2 == end) {
            tok2 = tok2->next();

            if (tok2 && tok2->str() != MatchCompiler::makeConstString(";") && (tok2->isCpp() || tok2->str() != MatchCompiler::makeConstString(")")))
                tok2 = nullptr;
        } else
            tok2 = nullptr;
    } else
        tok2 = nullptr;

    return tok2;
}

static const Scope* findEnumScopeInBase(const Scope* scope, const std::string& tokStr)
{
    if (scope->definedType) {
        const std::vector<Type::BaseInfo>& derivedFrom = scope->definedType->derivedFrom;
        for (const Type::BaseInfo& i : derivedFrom) {
            const Type *derivedFromType = i.type;
            if (derivedFromType && derivedFromType->classScope) {
                if (const Scope* enumScope = derivedFromType->classScope->findRecordInNestedList(tokStr))
                    return enumScope;
            }
        }
    }
    return nullptr;
}

static const Enumerator* findEnumeratorInUsingList(const Scope* scope, const std::string& name)
{
    for (const auto& u : scope->usingList) {
        if (!u.scope)
            continue;
        for (const Scope* nested : u.scope->nestedList) {
            if (nested->type != ScopeType::eEnum)
                continue;
            const Enumerator* e = nested->findEnumerator(name);
            if (e && !(e->scope && e->scope->enumClass))
                return e;
        }
    }
    return nullptr;
}

const Enumerator * SymbolDatabase::findEnumerator(const Token * tok, std::set<std::string>& tokensThatAreNotEnumeratorValues) const
{
    if (tok->isKeyword())
        return nullptr;

    const std::string& tokStr = tok->str();
    const Scope* scope = tok->scope();

    // check for qualified name
    if (tok->strAt(-1) == MatchCompiler::makeConstString("::")) {
        // find first scope
        const Token *tok1 = tok;
        while (match2(tok1->tokAt(-2)))
            tok1 = tok1->tokAt(-2);

        if (tok1->strAt(-1) == MatchCompiler::makeConstString("::"))
            scope = &scopeList.front();
        else {
            const Scope* temp = nullptr;
            if (scope)
                temp = scope->findRecordInNestedList(tok1->str());
            // find first scope
            while (scope && scope->nestedIn) {
                if (!temp)
                    temp = scope->nestedIn->findRecordInNestedList(tok1->str());
                if (!temp && scope->functionOf) {
                    temp = scope->functionOf->findRecordInNestedList(tok1->str());
                    const Scope* nested = scope->functionOf->nestedIn;
                    while (!temp && nested) {
                        temp = nested->findRecordInNestedList(tok1->str());
                        nested = nested->nestedIn;
                    }
                }
                if (!temp)
                    temp = findEnumScopeInBase(scope, tok1->str());
                if (temp) {
                    scope = temp;
                    break;
                }
                scope = scope->nestedIn;
            }
        }

        if (scope) {
            tok1 = tok1->tokAt(2);
            while (scope && match2(tok1)) {
                scope = scope->findRecordInNestedList(tok1->str());
                tok1 = tok1->tokAt(2);
            }

            if (scope) {
                const Enumerator * enumerator = scope->findEnumerator(tokStr);

                if (enumerator) // enum class
                    return enumerator;
                // enum
                for (auto it = scope->nestedList.cbegin(), end = scope->nestedList.cend(); it != end; ++it) {
                    enumerator = (*it)->findEnumerator(tokStr);

                    if (enumerator && !(enumerator->scope && enumerator->scope->enumClass))
                        return enumerator;
                }
            }
        }
    } else { // unqualified name

        if (tokensThatAreNotEnumeratorValues.find(tokStr) != tokensThatAreNotEnumeratorValues.end())
            return nullptr;

        if (tok->scope()->type == ScopeType::eGlobal) {
            const Token* astTop = tok->astTop();
            if (match242(astTop) && match29(astTop->astOperand1())) { // ctor init list
                const Token* ctor = astTop->astOperand1()->previous();
                if (ctor && ctor->function() && ctor->function()->nestedIn)
                    scope = ctor->function()->nestedIn;
            }
        }
        const Enumerator * enumerator = scope->findEnumerator(tokStr);
        if (!enumerator)
            enumerator = findEnumeratorInUsingList(scope, tokStr);

        if (enumerator && !(enumerator->scope && enumerator->scope->enumClass))
            return enumerator;

        if (match61(tok->astParent())) {
            const Token* varTok = tok->astParent()->astOperand1();
            if (varTok && varTok->variable() && varTok->variable()->type() && varTok->variable()->type()->classScope)
                scope = varTok->variable()->type()->classScope;
        }
        else if (match13(tok->astParent())) {
            const Token* varTok = tok->astParent()->previous();
            if (varTok && varTok->variable() && varTok->variable()->scope() && match75(tok->astParent()->astOperand1()))
                scope = varTok->variable()->scope();
        }

        for (auto s = scope->nestedList.cbegin(); s != scope->nestedList.cend(); ++s) {
            enumerator = (*s)->findEnumerator(tokStr);

            if (enumerator && !(enumerator->scope && enumerator->scope->enumClass))
                return enumerator;
        }

        if (scope->definedType) {
            const std::vector<Type::BaseInfo> & derivedFrom = scope->definedType->derivedFrom;
            for (const Type::BaseInfo & i : derivedFrom) {
                const Type *derivedFromType = i.type;
                if (derivedFromType && derivedFromType->classScope) {
                    enumerator = derivedFromType->classScope->findEnumerator(tokStr);

                    if (enumerator && !(enumerator->scope && enumerator->scope->enumClass))
                        return enumerator;
                }
            }
        }

        while (scope->nestedIn) {
            if (scope->type == ScopeType::eFunction && scope->functionOf)
                scope = scope->functionOf;
            else
                scope = scope->nestedIn;

            enumerator = scope->findEnumerator(tokStr);
            if (!enumerator)
                enumerator = findEnumeratorInUsingList(scope, tokStr);

            if (enumerator && !(enumerator->scope && enumerator->scope->enumClass))
                return enumerator;

            for (auto s = scope->nestedList.cbegin(); s != scope->nestedList.cend(); ++s) {
                enumerator = (*s)->findEnumerator(tokStr);

                if (enumerator && !(enumerator->scope && enumerator->scope->enumClass))
                    return enumerator;

                if (tok->isCpp() && (*s)->type == ScopeType::eNamespace && match40((*s)->classDef)) {
                    for (const Scope* nested : (*s)->nestedList) {
                        if (nested->type != ScopeType::eEnum)
                            continue;
                        enumerator = nested->findEnumerator(tokStr);

                        if (enumerator && !(enumerator->scope && enumerator->scope->enumClass))
                            return enumerator;
                    }
                }
            }
        }
    }

    tokensThatAreNotEnumeratorValues.insert(tokStr);

    return nullptr;
}

//---------------------------------------------------------------------------

const Type* SymbolDatabase::findVariableTypeInBase(const Scope* scope, const Token* typeTok)
{
    if (scope && scope->definedType && !scope->definedType->derivedFrom.empty()) {
        const std::vector<Type::BaseInfo> &derivedFrom = scope->definedType->derivedFrom;
        for (const Type::BaseInfo & i : derivedFrom) {
            const Type *base = i.type;
            if (base && base->classScope) {
                if (base->classScope == scope)
                    return nullptr;
                const Type * type = base->classScope->findType(typeTok->str());
                if (type)
                    return type;
                type = findVariableTypeInBase(base->classScope, typeTok);
                if (type)
                    return type;
            }
        }
    }

    return nullptr;
}

//---------------------------------------------------------------------------

const Type* SymbolDatabase::findVariableType(const Scope *start, const Token *typeTok) const
{
    const Scope *scope = start;

    // check if type does not have a namespace
    if (typeTok->strAt(-1) != MatchCompiler::makeConstString("::") && typeTok->strAt(1) != MatchCompiler::makeConstString("::")) {
        // check if type same as scope
        if (start->isClassOrStruct() && typeTok->str() == start->className)
            return start->definedType;

        while (scope) {
            // look for type in this scope
            const Type * type = scope->findType(typeTok->str());

            if (type)
                return type;

            // look for type in base classes if possible
            if (scope->isClassOrStruct()) {
                type = findVariableTypeInBase(scope, typeTok);

                if (type)
                    return type;
            }

            // check if in member function class to see if it's present in class
            if (scope->type == ScopeType::eFunction && scope->functionOf) {
                const Scope *scope1 = scope->functionOf;

                type = scope1->findType(typeTok->str());

                if (type)
                    return type;

                type = findVariableTypeInBase(scope1, typeTok);

                if (type)
                    return type;
            }

            scope = scope->nestedIn;
        }
    }

    // check for a qualified name and use it when given
    else if (typeTok->strAt(-1) == MatchCompiler::makeConstString("::")) {
        // check if type is not part of qualification
        if (typeTok->strAt(1) == MatchCompiler::makeConstString("::"))
            return nullptr;

        // find start of qualified function name
        const Token *tok1 = typeTok;

        while ((match35(tok1->tokAt(-2)) && !tok1->tokAt(-2)->isKeyword()) ||
               (match243(tok1->tokAt(-2)) && tok1->linkAt(-2) && match231(tok1->linkAt(-2)->tokAt(-1)))) {
            if (tok1->strAt(-1) == MatchCompiler::makeConstString("::"))
                tok1 = tok1->tokAt(-2);
            else
                tok1 = tok1->linkAt(-2)->tokAt(-1);
        }

        // check for global scope
        if (tok1->strAt(-1) == MatchCompiler::makeConstString("::")) {
            scope = &scopeList.front();

            scope = scope->findRecordInNestedList(tok1->str());
        }

        // find start of qualification
        else {
            while (scope) {
                if (scope->className == tok1->str())
                    break;

                const Scope *scope1 = scope->findRecordInNestedList(tok1->str());

                if (scope1) {
                    scope = scope1;
                    break;
                }
                if (scope->type == ScopeType::eFunction && scope->functionOf)
                    scope = scope->functionOf;
                else
                    scope = scope->nestedIn;
            }
        }

        if (scope) {
            // follow qualification
            while (scope && (match35(tok1) ||
                             (match192(tok1) && match243(tok1->linkAt(1))))) {
                if (tok1->strAt(1) == MatchCompiler::makeConstString("::"))
                    tok1 = tok1->tokAt(2);
                else
                    tok1 = tok1->linkAt(1)->tokAt(2);
                const Scope * temp = scope->findRecordInNestedList(tok1->str());
                if (!temp) {
                    // look in base classes
                    const Type * type = findVariableTypeInBase(scope, tok1);

                    if (type)
                        return type;
                }
                scope = temp;
            }

            if (scope && scope->definedType)
                return scope->definedType;
        }
    }

    return nullptr;
}

static bool hasEmptyCaptureList(const Token* tok) {
    if (!match5(tok))
        return false;
    const Token* listTok = tok->astParent();
    if (match29(listTok))
        listTok = listTok->astParent();
    return match244(listTok);
}

bool Scope::hasInlineOrLambdaFunction(const Token** tokStart, bool onlyInline) const
{
    return std::any_of(nestedList.begin(), nestedList.end(), [&](const Scope* s) {
        // Inline function
        if (s->type == ScopeType::eUnconditional && match32(s->bodyStart->previous())) {
            if (tokStart)
                *tokStart = nullptr; // bailout for e.g. loop-like macros
            return true;
        }
        // Lambda function
        if (!onlyInline && s->type == ScopeType::eLambda && !hasEmptyCaptureList(s->bodyStart)) {
            if (tokStart)
                *tokStart = s->bodyStart;
            return true;
        }
        if (s->hasInlineOrLambdaFunction(tokStart, onlyInline))
            return true;
        return false;
    });
}

void Scope::findFunctionInBase(const Token* tok, nonneg int args, std::vector<const Function *> & matches) const
{
    if (isClassOrStruct() && definedType && !definedType->derivedFrom.empty()) {
        const std::vector<Type::BaseInfo> &derivedFrom = definedType->derivedFrom;
        for (const Type::BaseInfo & i : derivedFrom) {
            const Type *base = i.type;
            if (base && base->classScope) {
                if (base->classScope == this) // Ticket #5120, #5125: Recursive class; tok should have been found already
                    continue;

                auto range = utils::as_const(base->classScope->functionMap).equal_range(tok->str());
                for (auto it = range.first; it != range.second; ++it) {
                    const Function *func = it->second;
                    if (func->isDestructor() && !match245(tok->tokAt(-1)))
                        continue;
                    if ((func->isVariadic() && args >= (func->argCount() - 1)) ||
                        (args == func->argCount() || (args < func->argCount() && args >= func->minArgCount()))) {
                        matches.push_back(func);
                    }
                }

                base->classScope->findFunctionInBase(tok, args, matches);
            }
        }
    }
}

const Scope *Scope::findRecordInBase(const std::string & name) const
{
    if (isClassOrStruct() && definedType && !definedType->derivedFrom.empty()) {
        const std::vector<Type::BaseInfo> &derivedFrom = definedType->derivedFrom;
        for (const Type::BaseInfo & i : derivedFrom) {
            const Type *base = i.type;
            if (base && base->classScope) {
                if (base->classScope == this) // Recursive class; tok should have been found already
                    continue;

                if (base->name() == name) {
                    return base->classScope;
                }

                const ::Type * t = base->classScope->findType(name);
                if (t)
                    return t->classScope;
            }
        }
    }

    return nullptr;
}

std::vector<const Scope*> Scope::findAssociatedScopes() const
{
    std::vector<const Scope*> result = {this};
    if (isClassOrStruct() && definedType && !definedType->derivedFrom.empty()) {
        const std::vector<Type::BaseInfo>& derivedFrom = definedType->derivedFrom;
        for (const Type::BaseInfo& i : derivedFrom) {
            const Type* base = i.type;
            if (base && base->classScope) {
                if (contains(result, base->classScope))
                    continue;
                std::vector<const Scope*> baseScopes = base->classScope->findAssociatedScopes();
                result.insert(result.end(), baseScopes.cbegin(), baseScopes.cend());
            }
        }
    }
    return result;
}

//---------------------------------------------------------------------------

static void checkVariableCallMatch(const Variable* callarg, const Variable* funcarg, size_t& same, size_t& fallback1, size_t& fallback2)
{
    if (callarg) {
        const ValueType::MatchResult res = ValueType::matchParameter(callarg->valueType(), callarg, funcarg);
        if (res == ValueType::MatchResult::SAME) {
            same++;
            return;
        }
        if (res == ValueType::MatchResult::FALLBACK1) {
            fallback1++;
            return;
        }
        if (res == ValueType::MatchResult::FALLBACK2) {
            fallback2++;
            return;
        }
        if (res == ValueType::MatchResult::NOMATCH)
            return;

        const bool ptrequals = callarg->isArrayOrPointer() == funcarg->isArrayOrPointer();
        const bool constEquals = !callarg->isArrayOrPointer() || ((callarg->typeStartToken()->strAt(-1) == MatchCompiler::makeConstString("const")) == (funcarg->typeStartToken()->strAt(-1) == MatchCompiler::makeConstString("const")));
        if (ptrequals && constEquals &&
            callarg->typeStartToken()->str() == funcarg->typeStartToken()->str() &&
            callarg->typeStartToken()->isUnsigned() == funcarg->typeStartToken()->isUnsigned() &&
            callarg->typeStartToken()->isLong() == funcarg->typeStartToken()->isLong()) {
            same++;
        } else if (callarg->isArrayOrPointer()) {
            if (ptrequals && constEquals && funcarg->typeStartToken()->str() == MatchCompiler::makeConstString("void"))
                fallback1++;
            else if (constEquals && funcarg->isStlStringType() && match246(callarg->typeStartToken()))
                fallback2++;
        } else if (ptrequals) {
            const bool takesInt = match247(funcarg->typeStartToken());
            const bool takesFloat = match142(funcarg->typeStartToken());
            const bool passesInt = match247(callarg->typeStartToken());
            const bool passesFloat = match142(callarg->typeStartToken());
            if ((takesInt && passesInt) || (takesFloat && passesFloat))
                fallback1++;
            else if ((takesInt && passesFloat) || (takesFloat && passesInt))
                fallback2++;
        }
    }
}

static std::string getTypeString(const Token *typeToken)
{
    if (!typeToken)
        return "";
    while (match248(typeToken)) {
        if (typeToken->str() == MatchCompiler::makeConstString("::")) {
            std::string ret;
            while (match1(typeToken)) {
                ret += "::" + typeToken->strAt(1);
                typeToken = typeToken->tokAt(2);
                if (typeToken->str() == MatchCompiler::makeConstString("<")) {
                    for (const Token *tok = typeToken; tok != typeToken->link(); tok = tok->next())
                        ret += tok->str();
                    ret += ">";
                    typeToken = typeToken->link()->next();
                }
            }
            return ret;
        }
        if (match249(typeToken)) {
            return typeToken->str();
        }
        typeToken = typeToken->next();
    }
    return "";
}

static bool hasMatchingConstructor(const Scope* classScope, const ValueType* argType) {
    if (!classScope || !argType)
        return false;
    return std::any_of(classScope->functionList.cbegin(),
                       classScope->functionList.cend(),
                       [&](const Function& f) {
        if (!f.isConstructor() || f.argCount() != 1 || !f.getArgumentVar(0))
            return false;
        const ValueType* vt = f.getArgumentVar(0)->valueType();
        return vt &&
               vt->type == argType->type &&
               (argType->sign == ValueType::Sign::UNKNOWN_SIGN || vt->sign == argType->sign) &&
               vt->pointer == argType->pointer &&
               (vt->constness & 1) >= (argType->constness & 1) &&
               (vt->volatileness & 1) >= (argType->volatileness & 1);
    });
}

const Function* Scope::findFunction(const Token *tok, bool requireConst, Reference ref) const
{
    const bool isCall = match22(tok->next());

    const std::vector<const Token *> arguments = getArguments(tok);

    std::vector<const Function *> matches;

    // find all the possible functions that could match
    const std::size_t args = arguments.size();

    auto addMatchingFunctions = [&](const Scope *scope) {
        auto range = utils::as_const(scope->functionMap).equal_range(tok->str());
        for (auto it = range.first; it != range.second; ++it) {
            const Function *func = it->second;
            if (ref == Reference::LValue && func->hasRvalRefQualifier())
                continue;
            if (ref == Reference::None && func->hasRvalRefQualifier()) {
                if (match61(tok->astParent())) {
                    const Token* obj = tok->astParent()->astOperand1();
                    while (obj && obj->str() == MatchCompiler::makeConstString("["))
                        obj = obj->astOperand1();
                    if (!obj || obj->isName())
                        continue;
                }
            }
            if (func->isDestructor() && !match245(tok->tokAt(-1)))
                continue;
            if (!isCall || args == func->argCount() ||
                (func->isVariadic() && args >= (func->minArgCount() - 1)) ||
                (args < func->argCount() && args >= func->minArgCount())) {
                matches.push_back(func);
            }
        }
    };

    addMatchingFunctions(this);

    // check in anonymous namespaces
    for (const Scope *nestedScope : nestedList) {
        if (nestedScope->type == ScopeType::eNamespace && nestedScope->className.empty())
            addMatchingFunctions(nestedScope);
    }

    const std::size_t numberOfMatchesNonBase = matches.size();

    // check in base classes
    findFunctionInBase(tok, args, matches);

    // Non-call => Do not match parameters
    if (!isCall) {
        return matches.empty() ? nullptr : matches[0];
    }

    // store function and number of matching arguments
    std::vector<std::pair<const Function*, size_t>> fallback1Func, fallback2Func;

    // check each function against the arguments in the function call for a match
    for (std::size_t i = 0; i < matches.size();) {
        if (i > 0 && i == numberOfMatchesNonBase && fallback1Func.empty() && !fallback2Func.empty())
            break;

        bool constFallback = false;
        const Function * func = matches[i];
        size_t same = 0;

        if (requireConst && !func->isConst()) {
            i++;
            continue;
        }

        if (!requireConst || !func->isConst()) {
            // get the function this call is in
            const Scope * scope = tok->scope();

            // check if this function is a member function
            if (scope && scope->functionOf && scope->functionOf->isClassOrStruct() && scope->function &&
                func->nestedIn == scope->functionOf) {
                // check if isConst mismatches
                if (scope->function->isConst() != func->isConst()) {
                    if (scope->function->isConst()) {
                        ++i;
                        continue;
                    }
                    constFallback = true;
                }
            }
        }

        size_t fallback1 = 0;
        size_t fallback2 = 0;
        bool erased = false;
        for (std::size_t j = 0; j < args; ++j) {

            // don't check variadic arguments
            if (func->isVariadic() && j > (func->argCount() - 1)) {
                break;
            }
            const Variable *funcarg = func->getArgumentVar(j);

            if (!arguments[j]->valueType()) {
                const Token *vartok = arguments[j];
                int pointer = 0;
                while (vartok && (vartok->isUnaryOp("&") || vartok->isUnaryOp("*"))) {
                    pointer += vartok->isUnaryOp("&") ? 1 : -1;
                    vartok = vartok->astOperand1();
                }
                if (vartok && vartok->variable()) {
                    const Token *callArgTypeToken = vartok->variable()->typeStartToken();
                    const Token *funcArgTypeToken = funcarg->typeStartToken();

                    auto parseDecl = [](const Token *typeToken) -> ValueType {
                        ValueType ret;
                        while (match76(typeToken->previous()))
                            typeToken = typeToken->previous();
                        while (match250(typeToken))
                        {
                            if (typeToken->str() == MatchCompiler::makeConstString("const"))
                                ret.constness |= (1 << ret.pointer);
                            else if (typeToken->str() == MatchCompiler::makeConstString("volatile"))
                                ret.volatileness |= (1 << ret.pointer);
                            else if (typeToken->str() == MatchCompiler::makeConstString("*"))
                                ret.pointer++;
                            else if (typeToken->str() == MatchCompiler::makeConstString("<")) {
                                if (!typeToken->link())
                                    break;
                                typeToken = typeToken->link();
                            }
                            typeToken = typeToken->next();
                        }
                        return ret;
                    };

                    const std::string type1 = getTypeString(callArgTypeToken);
                    const std::string type2 = getTypeString(funcArgTypeToken);
                    if (!type1.empty() && type1 == type2) {
                        ValueType callArgType = parseDecl(callArgTypeToken);
                        callArgType.pointer += pointer;
                        ValueType funcArgType = parseDecl(funcArgTypeToken);

                        callArgType.sign = funcArgType.sign = ValueType::Sign::SIGNED;
                        callArgType.type = funcArgType.type = ValueType::Type::INT;

                        const ValueType::MatchResult res = ValueType::matchParameter(&callArgType, &funcArgType);
                        if (res == ValueType::MatchResult::SAME)
                            ++same;
                        else if (res == ValueType::MatchResult::FALLBACK1)
                            ++fallback1;
                        else if (res == ValueType::MatchResult::FALLBACK2)
                            ++fallback2;
                        continue;
                    }
                }
            }

            // check for a match with a variable
            if (match251(arguments[j])) {
                const Variable * callarg = arguments[j]->variable();
                checkVariableCallMatch(callarg, funcarg, same, fallback1, fallback2);
            }

            else if (funcarg->isStlStringType() && arguments[j]->valueType() && arguments[j]->valueType()->pointer == 1 && arguments[j]->valueType()->type == ValueType::Type::CHAR)
                fallback2++;

            // check for a match with nullptr
            else if (funcarg->isPointer() && match252(arguments[j]))
                same++;

            else if (funcarg->isPointer() && MathLib::isNullValue(arguments[j]->str()))
                fallback1++;

            else if (!funcarg->isPointer() && funcarg->type() && hasMatchingConstructor(funcarg->type()->classScope, arguments[j]->valueType()))
                fallback2++;

            // Try to evaluate the apparently more complex expression
            else if (arguments[j]->isCpp()) {
                const Token *vartok = arguments[j];
                if (vartok->str() == MatchCompiler::makeConstString(".")) {
                    const Token* rml = nextAfterAstRightmostLeaf(vartok);
                    if (rml)
                        vartok = rml->previous();
                }
                while (vartok->isUnaryOp("&") || vartok->isUnaryOp("*"))
                    vartok = vartok->astOperand1();
                const Variable* var = vartok->variable();
                // smart pointer deref?
                bool unknownDeref = false;
                if (var && vartok->astParent() && vartok->astParent()->str() == MatchCompiler::makeConstString("*")) {
                    if (var->isSmartPointer() && var->valueType() && var->valueType()->smartPointerTypeToken)
                        var = var->valueType()->smartPointerTypeToken->variable();
                    else
                        unknownDeref = true;
                }
                const Token* valuetok = arguments[j];
                if (valuetok->str() == MatchCompiler::makeConstString("::")) {
                    const Token* rml = nextAfterAstRightmostLeaf(valuetok);
                    if (rml)
                        valuetok = rml->previous();
                }
                if (vartok->isEnumerator())
                    valuetok = vartok;
                const ValueType::MatchResult res = ValueType::matchParameter(valuetok->valueType(), var, funcarg);
                if (res == ValueType::MatchResult::SAME)
                    ++same;
                else if (res == ValueType::MatchResult::FALLBACK1)
                    ++fallback1;
                else if (res == ValueType::MatchResult::FALLBACK2)
                    ++fallback2;
                else if (res == ValueType::MatchResult::NOMATCH) {
                    if (unknownDeref)
                        continue;
                    // can't match so remove this function from possible matches
                    matches.erase(matches.begin() + i);
                    erased = true;
                    break;
                }
            }

            else
                // C code: if number of arguments match then do not match types
                fallback1++;
        }

        const size_t hasToBe = func->isVariadic() ? (func->argCount() - 1) : args;

        // check if all arguments matched
        if (same == hasToBe) {
            if (constFallback || (!requireConst && func->isConst()))
                fallback1Func.emplace_back(func, same);
            else
                return func;
        }

        else {
            if (same + fallback1 == hasToBe)
                fallback1Func.emplace_back(func, same);
            else if (same + fallback2 + fallback1 == hasToBe)
                fallback2Func.emplace_back(func, same);
        }

        if (!erased)
            ++i;
    }

    // Fallback cases
    auto fb_pred = [](const std::pair<const Function*, size_t>& a, const std::pair<const Function*, size_t>& b) {
        return a.second > b.second;
    };
    // sort according to matching arguments
    std::sort(fallback1Func.begin(), fallback1Func.end(), fb_pred);
    std::sort(fallback2Func.begin(), fallback2Func.end(), fb_pred);
    const auto fallbackFuncs = { std::move(fallback1Func), std::move(fallback2Func) };
    for (const auto& fb : fallbackFuncs) {
        if (fb.size() == 1)
            return fb[0].first;
        if (fb.size() >= 2) {
            if (fb[0].second > fb[1].second)
                return fb[0].first;
        }
        if (fb.size() == 2) {
            if (fb[0].first->isConst() && !fb[1].first->isConst())
                return fb[1].first;
            if (fb[1].first->isConst() && !fb[0].first->isConst())
                return fb[0].first;
        }
    }

    // remove pure virtual function if there is an overrider
    auto itPure = std::find_if(matches.begin(), matches.end(), [](const Function* m) {
        return m->isPure();
    });
    if (itPure != matches.end() && std::any_of(matches.begin(), matches.end(), [&](const Function* m) {
        return m->isImplicitlyVirtual() && m != *itPure;
    }))
        matches.erase(itPure);

    // Only one candidate left
    if (matches.size() == 1 && std::none_of(functionList.begin(), functionList.end(), [tok](const Function& f) {
        return startsWith(f.name(), tok->str() + " <");
    }))
        return matches[0];

    // Prioritize matches in derived scopes
    for (const auto& fb : fallbackFuncs) {
        const Function* ret = nullptr;
        for (std::size_t i = 0; i < fb.size(); ++i) {
            if (std::find(matches.cbegin(), matches.cend(), fb[i].first) == matches.cend())
                continue;
            if (this == fb[i].first->nestedIn) {
                if (!ret)
                    ret = fb[i].first;
                else {
                    ret = nullptr;
                    break;
                }
            }
        }
        if (ret)
            return ret;
    }

    return nullptr;
}

//---------------------------------------------------------------------------

const Function* SymbolDatabase::findFunction(const Token* const tok) const
{
    if (tok->tokType() == Token::Type::eEnumerator)
        return nullptr;

    // find the scope this function is in
    const Scope *currScope = tok->scope();
    while (currScope && currScope->isExecutable()) {
        if (const Function* f = currScope->findFunction(tok)) {
            return f;
        }
        if (currScope->functionOf)
            currScope = currScope->functionOf;
        else
            currScope = currScope->nestedIn;
    }

    // check for a qualified name and use it when given
    if (tok->strAt(-1) == MatchCompiler::makeConstString("::")) {
        // find start of qualified function name
        const Token *tok1 = tok;

        while (match253(tok1->tokAt(-2))) {
            if (tok1->strAt(-2) == MatchCompiler::makeConstString(">")) {
                if (tok1->linkAt(-2))
                    tok1 = tok1->linkAt(-2)->tokAt(-1);
                else
                    break;
            } else
                tok1 = tok1->tokAt(-2);
        }

        // check for global scope
        if (tok1->strAt(-1) == MatchCompiler::makeConstString("::")) {
            currScope = &scopeList.front();

            if (const Function* f = currScope->findFunction(tok))
                return f;

            currScope = currScope->findRecordInNestedList(tok1->str());
        }

        // find start of qualification
        else {
            while (currScope) {
                if (currScope->className == tok1->str())
                    break;

                const Scope *scope = currScope->findRecordInNestedList(tok1->str());

                if (scope) {
                    currScope = scope;
                    break;
                }
                currScope = currScope->nestedIn;
            }
        }

        if (currScope) {
            while (currScope && tok1 && !(match254(tok1) ||
                                          (match192(tok1) && match255(tok1->linkAt(1))))) {
                if (tok1->strAt(1) == MatchCompiler::makeConstString("::"))
                    tok1 = tok1->tokAt(2);
                else if (tok1->strAt(1) == MatchCompiler::makeConstString("<"))
                    tok1 = tok1->linkAt(1)->tokAt(2);
                else
                    tok1 = nullptr;

                if (tok1) {
                    const Function* func = currScope->findFunction(tok1);
                    if (func)
                        return func;

                    currScope = currScope->findRecordInNestedList(tok1->str());
                }
            }

            if (tok1)
                tok1 = tok1->tokAt(2);

            if (currScope && tok1) {
                const Function* func = currScope->findFunction(tok1);
                if (func)
                    return func;
            }
        }
    }

    // check for member function
    else if (match256(tok->tokAt(-2))) {
        const Token* tok1 = tok->previous()->astOperand1();
        if (tok1 && tok1->valueType() && tok1->valueType()->typeScope)
            return tok1->valueType()->typeScope->findFunction(tok, tok1->valueType()->constness == 1, tok1->valueType()->reference);
        if (tok1 && match24(tok1->previous()) && tok1->previous()->function() &&
            tok1->previous()->function()->retDef) {
            ValueType vt = ValueType::parseDecl(tok1->previous()->function()->retDef, mSettings);
            if (vt.typeScope)
                return vt.typeScope->findFunction(tok, vt.constness == 1);
        } else if (match257(tok1)) {
            const Variable *var = getVariableFromVarId(tok1->varId());
            if (var && var->typeScope())
                return var->typeScope()->findFunction(tok, var->valueType()->constness == 1);
            if (var && var->smartPointerType() && var->smartPointerType()->classScope && tok1->next()->originalName() == MatchCompiler::makeConstString("->"))
                return var->smartPointerType()->classScope->findFunction(tok, var->valueType()->constness == 1);
            if (var && var->iteratorType() && var->iteratorType()->classScope && tok1->next()->originalName() == MatchCompiler::makeConstString("->"))
                return var->iteratorType()->classScope->findFunction(tok, var->valueType()->constness == 1);
        } else if (match29(tok->previous()->astOperand1())) {
            const Token *castTok = tok->previous()->astOperand1();
            if (castTok->isCast()) {
                ValueType vt = ValueType::parseDecl(castTok->next(),mSettings);
                if (vt.typeScope)
                    return vt.typeScope->findFunction(tok, vt.constness == 1);
            }
        }
    }

    // check in enclosing scopes
    else {
        while (currScope) {
            const Function *func = currScope->findFunction(tok);
            if (func)
                return func;
            currScope = currScope->nestedIn;
        }
        // check using namespace
        currScope = tok->scope();
        while (currScope) {
            for (const auto& ul : currScope->usingList) {
                if (ul.scope) {
                    const Function* func = ul.scope->findFunction(tok);
                    if (func)
                        return func;
                }
            }
            currScope = currScope->nestedIn;
        }
    }
    // Check for constructor
    if (match236(tok)) {
        ValueType vt = ValueType::parseDecl(tok, mSettings);
        if (vt.typeScope)
            return vt.typeScope->findFunction(tok, false);
    }
    return nullptr;
}

//---------------------------------------------------------------------------

const Scope *SymbolDatabase::findScopeByName(const std::string& name) const
{
    auto it = std::find_if(scopeList.cbegin(), scopeList.cend(), [&](const Scope& s) {
        return s.className == name;
    });
    return it == scopeList.end() ? nullptr : &*it;
}

//---------------------------------------------------------------------------

template<class S, class T, REQUIRES("S must be a Scope class", std::is_convertible<S*, const Scope*> ), REQUIRES("T must be a Type class", std::is_convertible<T*, const Type*> )>
static S* findRecordInNestedListImpl(S& thisScope, const std::string& name, bool isC, std::set<const Scope*>& visited)
{
    for (S* scope: thisScope.nestedList) {
        if (scope->className == name && scope->type != ScopeType::eFunction)
            return scope;
        if (isC) {
            S* nestedScope = scope->findRecordInNestedList(name, isC);
            if (nestedScope)
                return nestedScope;
        }
    }

    for (const auto& u : thisScope.usingList) {
        if (!u.scope || u.scope == &thisScope || visited.find(u.scope) != visited.end())
            continue;
        visited.emplace(u.scope);
        S* nestedScope = findRecordInNestedListImpl<S, T>(const_cast<S&>(*u.scope), name, false, visited);
        if (nestedScope)
            return nestedScope;
    }

    T * nested_type = thisScope.findType(name);

    if (nested_type) {
        if (nested_type->isTypeAlias()) {
            if (nested_type->typeStart == nested_type->typeEnd)
                return thisScope.findRecordInNestedList(nested_type->typeStart->str()); // TODO: pass isC?
        } else
            return const_cast<S*>(nested_type->classScope);
    }

    return nullptr;
}

const Scope* Scope::findRecordInNestedList(const std::string & name, bool isC) const
{
    std::set<const Scope*> visited;
    return findRecordInNestedListImpl<const Scope, const Type>(*this, name, isC, visited);
}

Scope* Scope::findRecordInNestedList(const std::string & name, bool isC)
{
    std::set<const Scope*> visited;
    return findRecordInNestedListImpl<Scope, Type>(*this, name, isC, visited);
}

//---------------------------------------------------------------------------

template<class S, class T, REQUIRES("S must be a Scope class", std::is_convertible<S*, const Scope*> ), REQUIRES("T must be a Type class", std::is_convertible<T*, const Type*> )>
static T* findTypeImpl(S& thisScope, const std::string & name)
{
    auto it = thisScope.definedTypesMap.find(name);

    // Type was found
    if (thisScope.definedTypesMap.end() != it)
        return it->second;

    // is type defined in anonymous namespace..
    it = thisScope.definedTypesMap.find(emptyString);
    if (it != thisScope.definedTypesMap.end()) {
        for (S *scope : thisScope.nestedList) {
            if (scope->className.empty() && (scope->type == ScopeType::eNamespace || scope->isClassOrStructOrUnion())) {
                T *t = scope->findType(name);
                if (t)
                    return t;
            }
        }
    }

    // Type was not found
    return nullptr;
}

const Type* Scope::findType(const std::string& name) const
{
    return findTypeImpl<const Scope, const Type>(*this, name);
}

Type* Scope::findType(const std::string& name)
{
    return findTypeImpl<Scope, Type>(*this, name);
}

//---------------------------------------------------------------------------

Scope *Scope::findInNestedListRecursive(const std::string & name)
{
    auto it = std::find_if(nestedList.cbegin(), nestedList.cend(), [&](const Scope* s) {
        return s->className == name;
    });
    if (it != nestedList.end())
        return *it;

    for (Scope* scope: nestedList) {
        Scope *child = scope->findInNestedListRecursive(name);
        if (child)
            return child;
    }
    return nullptr;
}

//---------------------------------------------------------------------------

const Function *Scope::getDestructor() const
{
    auto it = std::find_if(functionList.cbegin(), functionList.cend(), [](const Function& f) {
        return f.type == FunctionType::eDestructor;
    });
    return it == functionList.end() ? nullptr : &*it;
}

//---------------------------------------------------------------------------

const Scope *SymbolDatabase::findScope(const Token *tok, const Scope *startScope) const
{
    const Scope *scope = nullptr;
    // absolute path
    if (tok->str() == MatchCompiler::makeConstString("::")) {
        tok = tok->next();
        scope = &scopeList.front();
    }
    // relative path
    else if (tok->isName()) {
        scope = startScope;
    }

    while (scope && tok && tok->isName()) {
        if (tok->strAt(1) == MatchCompiler::makeConstString("::")) {
            scope = scope->findRecordInNestedList(tok->str());
            tok = tok->tokAt(2);
        } else if (tok->strAt(1) == MatchCompiler::makeConstString("<"))
            return nullptr;
        else
            return scope->findRecordInNestedList(tok->str());
    }

    // not a valid path
    return nullptr;
}

//---------------------------------------------------------------------------

const Type* SymbolDatabase::findType(const Token *startTok, const Scope *startScope, bool lookOutside) const
{
    // skip over struct or union
    if (match258(startTok))
        startTok = startTok->next();

    // type same as scope
    if (startTok->str() == startScope->className && startScope->isClassOrStruct() && startTok->strAt(1) != MatchCompiler::makeConstString("::"))
        return startScope->definedType;

    if (startTok->isC()) {
        const Scope* scope = startScope;
        while (scope) {
            if (startTok->str() == scope->className && scope->isClassOrStruct())
                return scope->definedType;
            const Scope* typeScope = scope->findRecordInNestedList(startTok->str(), /*isC*/ true);
            if (typeScope) {
                if (startTok->str() == typeScope->className && typeScope->isClassOrStruct()) {
                    if (const Type* type = typeScope->definedType)
                        return type;
                }
            }
            scope = scope->nestedIn;
        }
        return nullptr;
    }

    const Scope* start_scope = startScope;

    // absolute path - directly start in global scope
    if (startTok->str() == MatchCompiler::makeConstString("::")) {
        startTok = startTok->next();
        start_scope = &scopeList.front();
    }

    const Token* tok = startTok;
    const Scope* scope = start_scope;

    while (scope && tok && tok->isName()) {
        if (tok->strAt(1) == MatchCompiler::makeConstString("::") || (tok->strAt(1) == MatchCompiler::makeConstString("<") && match243(tok->linkAt(1)))) {
            scope = scope->findRecordInNestedList(tok->str());
            if (scope) {
                if (tok->strAt(1) == MatchCompiler::makeConstString("::"))
                    tok = tok->tokAt(2);
                else
                    tok = tok->linkAt(1)->tokAt(2);
            } else {
                start_scope = start_scope->nestedIn;
                if (!start_scope)
                    break;
                scope = start_scope;
                tok = startTok;
            }
        } else {
            const Scope* scope1{};
            const Type* type = scope->findType(tok->str());
            if (type)
                return type;
            if (lookOutside && (scope1 = scope->findRecordInBase(tok->str()))) {
                type = scope1->definedType;
                if (type)
                    return type;
            } else if (lookOutside && scope->type == ScopeType::eNamespace) {
                scope = scope->nestedIn;
                continue;
            } else
                break;
        }
    }

    // check using namespaces
    while (startScope) {
        for (auto it = startScope->usingList.cbegin();
             it != startScope->usingList.cend(); ++it) {
            tok = startTok;
            scope = it->scope;
            start_scope = startScope;

            while (scope && tok && tok->isName()) {
                if (tok->strAt(1) == MatchCompiler::makeConstString("::") || (tok->strAt(1) == MatchCompiler::makeConstString("<") && match243(tok->linkAt(1)))) {
                    scope = scope->findRecordInNestedList(tok->str());
                    if (scope) {
                        if (tok->strAt(1) == MatchCompiler::makeConstString("::"))
                            tok = tok->tokAt(2);
                        else
                            tok = tok->linkAt(1)->tokAt(2);
                    } else {
                        start_scope = start_scope->nestedIn;
                        if (!start_scope)
                            break;
                        scope = start_scope;
                        tok = startTok;
                    }
                } else {
                    const Type * type = scope->findType(tok->str());
                    if (type)
                        return type;
                    if (const Scope *scope1 = scope->findRecordInBase(tok->str())) {
                        type = scope1->definedType;
                        if (type)
                            return type;
                    } else
                        break;
                }
            }
        }
        startScope = startScope->nestedIn;
    }

    // not a valid path
    return nullptr;
}

//---------------------------------------------------------------------------

const Type* SymbolDatabase::findTypeInNested(const Token *startTok, const Scope *startScope) const
{
    // skip over struct or union
    if (match259(startTok))
        startTok = startTok->next();

    // type same as scope
    if (startScope->isClassOrStruct() && startTok->str() == startScope->className && !match75(startTok->next()))
        return startScope->definedType;

    bool hasPath = false;

    // absolute path - directly start in global scope
    if (startTok->str() == MatchCompiler::makeConstString("::")) {
        hasPath = true;
        startTok = startTok->next();
        startScope = &scopeList.front();
    }

    const Token* tok = startTok;
    const Scope* scope = startScope;

    while (scope && tok && tok->isName()) {
        if (tok->strAt(1) == MatchCompiler::makeConstString("::") || (tok->strAt(1) == MatchCompiler::makeConstString("<") && match243(tok->linkAt(1)))) {
            hasPath = true;
            scope = scope->findRecordInNestedList(tok->str());
            if (scope) {
                if (tok->strAt(1) == MatchCompiler::makeConstString("::"))
                    tok = tok->tokAt(2);
                else
                    tok = tok->linkAt(1)->tokAt(2);
            } else {
                startScope = startScope->nestedIn;
                if (!startScope)
                    break;
                scope = startScope;
                tok = startTok;
            }
        } else {
            const Type * type = scope->findType(tok->str());
            if (hasPath || type)
                return type;

            scope = scope->nestedIn;
            if (!scope)
                break;
        }
    }

    // not a valid path
    return nullptr;
}

//---------------------------------------------------------------------------

const Scope * SymbolDatabase::findNamespace(const Token * tok, const Scope * scope) const
{
    const Scope * s = findScope(tok, scope);

    if (s)
        return s;
    if (scope->nestedIn)
        return findNamespace(tok, scope->nestedIn);

    return nullptr;
}

//---------------------------------------------------------------------------

Function * SymbolDatabase::findFunctionInScope(const Token *func, const Scope *ns, const std::string & path, nonneg int path_length)
{
    const Function * function = nullptr;
    const bool destructor = func->strAt(-1) == MatchCompiler::makeConstString("~");

    auto range = utils::as_const(ns->functionMap).equal_range(func->str());
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second->argsMatch(ns, it->second->argDef, func->next(), path, path_length) &&
            it->second->isDestructor() == destructor) {
            function = it->second;
            break;
        }
    }

    if (!function) {
        const Scope * scope = ns->findRecordInNestedList(func->str());
        if (scope && match260(func->tokAt(1))) {
            if (func->strAt(1) == MatchCompiler::makeConstString("::"))
                func = func->tokAt(2);
            else if (func->linkAt(1))
                func = func->linkAt(1)->tokAt(2);
            else
                return nullptr;
            if (func->str() == MatchCompiler::makeConstString("~"))
                func = func->next();
            function = findFunctionInScope(func, scope, path, path_length);
        }
    }

    return const_cast<Function *>(function);
}

//---------------------------------------------------------------------------

bool SymbolDatabase::isReservedName(const Token* tok)
{
    const std::string& iName = tok->str();
    if (tok->isCpp()) {
        static const auto& cpp_keywords = Keywords::getAll(Standards::cppstd_t::CPPLatest);
        return cpp_keywords.find(iName) != cpp_keywords.cend();
    }
    static const auto& c_keywords = Keywords::getAll(Standards::cstd_t::CLatest);
    return c_keywords.find(iName) != c_keywords.cend();
}

nonneg int SymbolDatabase::sizeOfType(const Token *type) const
{
    int size = mTokenizer.sizeOfType(type);

    if (size == 0 && type->type() && type->type()->isEnumType() && type->type()->classScope) {
        size = mSettings.platform.sizeof_int;
        const Token * enum_type = type->type()->classScope->enumType;
        if (enum_type)
            size = mTokenizer.sizeOfType(enum_type);
    }

    return size;
}

static const Token* parsedecl(const Token* type,
                              ValueType* valuetype,
                              ValueType::Sign defaultSignedness,
                              const Settings& settings,
                              SourceLocation loc = SourceLocation::current());

void SymbolDatabase::setValueType(Token* tok, const Variable& var, const SourceLocation &loc)
{
    ValueType valuetype;
    if (mSettings.debugnormal || mSettings.debugwarnings)
        valuetype.setDebugPath(tok, loc);
    if (var.nameToken())
        valuetype.bits = var.nameToken()->bits();

    valuetype.pointer = var.dimensions().size();
    // HACK: don't set pointer for plain std::array
    if (var.valueType() && var.valueType()->container && match261(var.typeStartToken()) && !match13(var.nameToken()->next()))
        valuetype.pointer = 0;

    valuetype.typeScope = var.typeScope();
    if (var.valueType()) {
        valuetype.container = var.valueType()->container;
        valuetype.containerTypeToken = var.valueType()->containerTypeToken;
    }
    valuetype.smartPointerType = var.smartPointerType();
    if (parsedecl(var.typeStartToken(), &valuetype, mDefaultSignedness, mSettings)) {
        if (tok->str() == MatchCompiler::makeConstString(".") && tok->astOperand1()) {
            const ValueType * const vt = tok->astOperand1()->valueType();
            if (vt && (vt->constness & 1) != 0) {
                if (var.isArray()) // constness propagates to arrays, but not to regular pointers
                    valuetype.constness |= 1;
                else
                    valuetype.constness |= (1 << valuetype.pointer);
            }
            if (vt && (vt->volatileness & 1) != 0) {
                if (var.isArray())
                    valuetype.volatileness |= 1;
                else
                    valuetype.volatileness |= (1 << valuetype.pointer);
            }
        }
        setValueType(tok, valuetype);
    }
}

static ValueType::Type getEnumType(const Scope* scope, const Platform& platform);

void SymbolDatabase::setValueType(Token* tok, const Enumerator& enumerator, const SourceLocation &loc)
{
    ValueType valuetype;
    if (mSettings.debugnormal || mSettings.debugwarnings)
        valuetype.setDebugPath(tok, loc);
    valuetype.typeScope = enumerator.scope;
    const Token * type = enumerator.scope->enumType;
    if (type && type->astParent())
        type = type->astParent();
    if (type) {
        valuetype.type = ValueType::typeFromString(type->str(), type->isLong());
        if (valuetype.type == ValueType::Type::UNKNOWN_TYPE)
            valuetype.fromLibraryType(type->expressionString(), mSettings);

        if (valuetype.isIntegral()) {
            if (type->isSigned())
                valuetype.sign = ValueType::Sign::SIGNED;
            else if (type->isUnsigned())
                valuetype.sign = ValueType::Sign::UNSIGNED;
            else if (valuetype.type == ValueType::Type::CHAR)
                valuetype.sign = mDefaultSignedness;
            else
                valuetype.sign = ValueType::Sign::SIGNED;
        }

        setValueType(tok, valuetype);
    } else {
        valuetype.sign = ValueType::SIGNED;
        valuetype.type = getEnumType(enumerator.scope, mSettings.platform);
        setValueType(tok, valuetype);
    }
}

static void setAutoTokenProperties(Token * const autoTok)
{
    const ValueType *valuetype = autoTok->valueType();
    if (valuetype->isIntegral() || valuetype->isFloat())
        autoTok->isStandardType(true);
}

static bool isContainerYieldElement(Library::Container::Yield yield)
{
    return yield == Library::Container::Yield::ITEM || yield == Library::Container::Yield::AT_INDEX ||
           yield == Library::Container::Yield::BUFFER || yield == Library::Container::Yield::BUFFER_NT;
}

static bool isContainerYieldPointer(Library::Container::Yield yield)
{
    return yield == Library::Container::Yield::BUFFER || yield == Library::Container::Yield::BUFFER_NT;
}

void SymbolDatabase::setValueType(Token* tok, const ValueType& valuetype, const SourceLocation &loc)
{
    auto* valuetypePtr = new ValueType(valuetype);
    if (mSettings.debugnormal || mSettings.debugwarnings)
        valuetypePtr->setDebugPath(tok, loc);
    tok->setValueType(valuetypePtr);
    Token *parent = tok->astParent();
    if (!parent || parent->valueType())
        return;
    if (!parent->astOperand1())
        return;

    const ValueType *vt1 = parent->astOperand1()->valueType();
    const ValueType *vt2 = parent->astOperand2() ? parent->astOperand2()->valueType() : nullptr;

    if (vt1 && match262(parent)) {
        if (!parent->isCpp() || (vt2 && vt2->isIntegral())) {
            if (vt1->type < ValueType::Type::BOOL || vt1->type >= ValueType::Type::INT) {
                ValueType vt(*vt1);
                vt.reference = Reference::None;
                setValueType(parent, vt);
            } else {
                ValueType vt(*vt1);
                vt.type = ValueType::Type::INT; // Integer promotion
                vt.sign = ValueType::Sign::SIGNED;
                vt.reference = Reference::None;
                setValueType(parent, vt);
            }

        }
        return;
    }

    if (vt1 && vt1->container && vt1->containerTypeToken && match263(parent) &&
        isContainerYieldElement(vt1->container->getYield(parent->strAt(1)))) {
        ValueType item;
        if (parsedecl(vt1->containerTypeToken, &item, mDefaultSignedness, mSettings)) {
            if (item.constness == 0)
                item.constness = vt1->constness;
            if (item.volatileness == 0)
                item.volatileness = vt1->volatileness;
            if (isContainerYieldPointer(vt1->container->getYield(parent->strAt(1))))
                item.pointer += 1;
            else
                item.reference = Reference::LValue;
            setValueType(parent->tokAt(2), item);
        }
    }

    if (vt1 && vt1->smartPointerType && match263(parent) && parent->originalName() == MatchCompiler::makeConstString("->") && !parent->next()->function()) {
        const Scope *scope = vt1->smartPointerType->classScope;
        const Function *f = scope ? scope->findFunction(parent->next(), false) : nullptr;
        if (f)
            parent->next()->function(f);
    }

    if (parent->isAssignmentOp()) {
        if (vt1) {
            auto vt = *vt1;
            vt.reference = Reference::None;
            setValueType(parent, vt);
        } else if (parent->isCpp() && ((match264(parent->tokAt(-3)) && parent->strAt(-3) == parent->strAt(-1)) ||
                                       match265(parent->tokAt(-1)))) {
            Token *var1Tok = parent->strAt(-2) == MatchCompiler::makeConstString(";") ? parent->tokAt(-3) : parent->tokAt(-1);
            Token *autoTok = nullptr;
            if (match266(var1Tok->tokAt(-1)))
                autoTok = var1Tok->previous();
            else if (match267(var1Tok->tokAt(-2)))
                autoTok = var1Tok->tokAt(-2);
            else if (match268(var1Tok->tokAt(-3)))
                autoTok = var1Tok->tokAt(-3);
            if (autoTok) {
                ValueType vt(*vt2);
                if (vt.constness & (1 << vt.pointer))
                    vt.constness &= ~(1 << vt.pointer);
                if (vt.volatileness & (1 << vt.pointer))
                    vt.volatileness &= ~(1 << vt.pointer);
                if (autoTok->strAt(1) == MatchCompiler::makeConstString("*") && vt.pointer)
                    vt.pointer--;
                if (match269(autoTok->tokAt(-1)))
                    vt.constness |= (1 << vt.pointer);
                if (match270(autoTok->tokAt(-1)))
                    vt.volatileness |= (1 << vt.pointer);
                setValueType(autoTok, vt);
                setAutoTokenProperties(autoTok);
                if (vt2->pointer > vt.pointer)
                    vt.pointer++;
                setValueType(var1Tok, vt);
                if (var1Tok != parent->previous())
                    setValueType(parent->previous(), vt);
                auto *var = const_cast<Variable *>(parent->previous()->variable());
                if (var) {
                    ValueType vt2_(*vt2);
                    if (vt2_.pointer == 0 && autoTok->strAt(1) == MatchCompiler::makeConstString("*"))
                        vt2_.pointer = 1;
                    if ((vt.constness & (1 << vt2->pointer)) != 0)
                        vt2_.constness |= (1 << vt2->pointer);
                    if ((vt.volatileness & (1 << vt2->pointer)) != 0)
                        vt2_.volatileness |= (1 << vt2->pointer);
                    if (!match271(autoTok->tokAt(1))) {
                        vt2_.constness = vt.constness;
                        vt2_.volatileness = vt.volatileness;
                    }
                    if (match272(autoTok->tokAt(1)))
                        vt2_.constness |= (1 << vt2->pointer);
                    if (match273(autoTok->tokAt(1)))
                        vt2_.volatileness |= (1 << vt2->pointer);
                    var->setValueType(vt2_);
                    if (vt2->typeScope && vt2->typeScope->definedType) {
                        var->type(vt2->typeScope->definedType);
                        if (autoTok->valueType()->pointer == 0)
                            autoTok->type(vt2->typeScope->definedType);
                    }
                }
            }
        }
        return;
    }

    if (parent->str() == MatchCompiler::makeConstString("[") && (!parent->isCpp() || parent->astOperand1() == tok) && valuetype.pointer > 0U && !match91(parent->previous())) {
        const Token *op1 = parent->astOperand1();
        while (op1 && op1->str() == MatchCompiler::makeConstString("["))
            op1 = op1->astOperand1();

        ValueType vt(valuetype);
        // the "[" is a dereference unless this is a variable declaration
        if (!(op1 && op1->variable() && op1->variable()->nameToken() == op1))
            vt.pointer -= 1U;
        setValueType(parent, vt);
        return;
    }
    if (match24(parent->previous()) && parent->astOperand1() == tok && valuetype.pointer > 0U) {
        ValueType vt(valuetype);
        vt.pointer -= 1U;
        setValueType(parent, vt);
        return;
    }
    // std::move
    if (vt2 && parent->str() == MatchCompiler::makeConstString("(") && match274(parent->tokAt(-3))) {
        ValueType vt = valuetype;
        vt.reference = Reference::RValue;
        setValueType(parent, vt);
        return;
    }
    if (parent->str() == MatchCompiler::makeConstString("*") && !parent->astOperand2() && valuetype.pointer > 0U) {
        ValueType vt(valuetype);
        vt.pointer -= 1U;
        setValueType(parent, vt);
        return;
    }
    // Dereference iterator
    if (parent->str() == MatchCompiler::makeConstString("*") && !parent->astOperand2() && valuetype.type == ValueType::Type::ITERATOR &&
        valuetype.containerTypeToken) {
        ValueType vt;
        if (parsedecl(valuetype.containerTypeToken, &vt, mDefaultSignedness, mSettings)) {
            if (vt.constness == 0)
                vt.constness = valuetype.constness;
            if (vt.volatileness == 0)
                vt.volatileness = valuetype.volatileness;
            vt.reference = Reference::LValue;
            setValueType(parent, vt);
            return;
        }
    }
    // Dereference smart pointer
    if (parent->str() == MatchCompiler::makeConstString("*") && !parent->astOperand2() && valuetype.type == ValueType::Type::SMART_POINTER &&
        valuetype.smartPointerTypeToken) {
        ValueType vt;
        if (parsedecl(valuetype.smartPointerTypeToken, &vt, mDefaultSignedness, mSettings)) {
            if (vt.constness == 0)
                vt.constness = valuetype.constness;
            if (vt.volatileness == 0)
                vt.volatileness = valuetype.volatileness;
            setValueType(parent, vt);
            return;
        }
    }
    if (parent->str() == MatchCompiler::makeConstString("*") && match13(parent->astOperand2()) && valuetype.pointer > 0U) {
        const Token *op1 = parent->astOperand2()->astOperand1();
        while (op1 && op1->str() == MatchCompiler::makeConstString("["))
            op1 = op1->astOperand1();
        const ValueType& vt(valuetype);
        if (op1 && op1->variable() && op1->variable()->nameToken() == op1) {
            setValueType(parent, vt);
            return;
        }
    }
    if (parent->str() == MatchCompiler::makeConstString("&") && !parent->astOperand2()) {
        ValueType vt(valuetype);
        vt.reference = Reference::None; //Given int& x; the type of &x is int* not int&*
        bool isArrayToPointerDecay = false;
        for (const Token* child = parent->astOperand1(); child;) {
            if (match83(child))
                child = child->astOperand2();
            else {
                isArrayToPointerDecay = child->variable() && child->variable()->isArray();
                break;
            }
        }
        if (!isArrayToPointerDecay)
            vt.pointer += 1U;
        setValueType(parent, vt);
        return;
    }

    if ((parent->str() == MatchCompiler::makeConstString(".") || parent->str() == MatchCompiler::makeConstString("::")) &&
        parent->astOperand2() && parent->astOperand2()->isName()) {
        const Variable* var = parent->astOperand2()->variable();
        if (!var && valuetype.typeScope && vt1) {
            const std::string &name = parent->astOperand2()->str();
            const Scope *typeScope = vt1->typeScope;
            if (!typeScope)
                return;
            auto it = std::find_if(typeScope->varlist.begin(), typeScope->varlist.end(), [&name](const Variable& v) {
                return v.nameToken()->str() == name;
            });
            if (it != typeScope->varlist.end())
                var = &*it;
        }
        if (var) {
            setValueType(parent, *var);
            return;
        }
        if (const Enumerator* enu = parent->astOperand2()->enumerator())
            setValueType(parent, *enu);
        return;
    }

    // range for loop, auto
    if (vt2 &&
        parent->str() == MatchCompiler::makeConstString(":") &&
        match275(parent->astParent()) && // TODO: east-const, multiple const, ref to ptr
        !parent->previous()->valueType() &&
        match276(parent->astParent()->astOperand1())) {
        const bool isconst = match157(parent->astParent()->next());
        const bool isvolatile = match270(parent->astParent()->next());
        Token * const autoToken = parent->astParent()->tokAt(isconst ? 2 : 1);
        if (vt2->pointer) {
            ValueType autovt(*vt2);
            autovt.pointer--;
            autovt.constness = 0;
            autovt.volatileness = 0;
            setValueType(autoToken, autovt);
            setAutoTokenProperties(autoToken);
            ValueType varvt(*vt2);
            varvt.pointer--;
            if (match120(autoToken->next()))
                varvt.reference = Reference::LValue;
            if (isconst) {
                if (varvt.pointer && varvt.reference != Reference::None)
                    varvt.constness |= (1 << varvt.pointer);
                else
                    varvt.constness |= 1;
            }
            if (isvolatile) {
                if (varvt.pointer && varvt.reference != Reference::None)
                    varvt.volatileness |= (1 << varvt.pointer);
                else
                    varvt.volatileness |= 1;
            }
            setValueType(parent->previous(), varvt);
            auto *var = const_cast<Variable *>(parent->previous()->variable());
            if (var) {
                var->setValueType(varvt);
                if (vt2->typeScope && vt2->typeScope->definedType) {
                    var->type(vt2->typeScope->definedType);
                    autoToken->type(vt2->typeScope->definedType);
                }
            }
        } else if (vt2->container) {
            // TODO: Determine exact type of RHS
            const Token *typeStart = parent->astOperand2();
            while (typeStart) {
                if (typeStart->variable())
                    typeStart = typeStart->variable()->typeStartToken();
                else if (typeStart->str() == MatchCompiler::makeConstString("(") && typeStart->previous() && typeStart->previous()->function())
                    typeStart = typeStart->previous()->function()->retDef;
                else
                    break;
            }

            // Try to determine type of "auto" token.
            // TODO: Get type better
            bool setType = false;
            ValueType autovt;
            const Type *templateArgType = nullptr; // container element type / smart pointer type
            if (!vt2->container->rangeItemRecordType.empty()) {
                setType = true;
                autovt.type = ValueType::Type::RECORD;
            } else if (vt2->containerTypeToken) {
                if (mSettings.library.isSmartPointer(vt2->containerTypeToken)) {
                    const Token *smartPointerTypeTok = vt2->containerTypeToken;
                    while (match12(smartPointerTypeTok))
                        smartPointerTypeTok = smartPointerTypeTok->next();
                    if (match60(smartPointerTypeTok)) {
                        if ((templateArgType = findTypeInNested(smartPointerTypeTok->next(), tok->scope()))) {
                            setType = true;
                            autovt.smartPointerType = templateArgType;
                            autovt.type = ValueType::Type::NONSTD;
                        }
                    }
                } else if (parsedecl(vt2->containerTypeToken, &autovt, mDefaultSignedness, mSettings)) {
                    setType = true;
                    templateArgType = vt2->containerTypeToken->type();
                    if (match120(autoToken->next()))
                        autovt.reference = Reference::LValue;
                    else if (match128(autoToken->next()))
                        autovt.reference = Reference::RValue;
                    if (autoToken->strAt(-1) == MatchCompiler::makeConstString("const")) {
                        if (autovt.pointer && autovt.reference != Reference::None)
                            autovt.constness |= 2;
                        else
                            autovt.constness |= 1;
                    }
                    if (autoToken->strAt(-1) == MatchCompiler::makeConstString("volatile")) {
                        if (autovt.pointer && autovt.reference != Reference::None)
                            autovt.volatileness |= 2;
                        else
                            autovt.volatileness |= 1;
                    }
                }
            }

            if (setType) {
                // Type of "auto" has been determined.. set type information for "auto" and variable tokens
                setValueType(autoToken, autovt);
                setAutoTokenProperties(autoToken);
                ValueType varvt(autovt);
                if (autoToken->strAt(1) == MatchCompiler::makeConstString("*") && autovt.pointer)
                    autovt.pointer--;
                if (isconst)
                    varvt.constness |= (1 << autovt.pointer);
                if (isvolatile)
                    varvt.volatileness |= (1 << autovt.pointer);
                setValueType(parent->previous(), varvt);
                auto * var = const_cast<Variable *>(parent->previous()->variable());
                if (var) {
                    var->setValueType(varvt);
                    if (templateArgType && templateArgType->classScope && templateArgType->classScope->definedType) {
                        autoToken->type(templateArgType->classScope->definedType);
                        var->type(templateArgType->classScope->definedType);
                    }
                }
            }
        }
    }

    if (vt1 && vt1->containerTypeToken && parent->str() == MatchCompiler::makeConstString("[")) {
        ValueType vtParent;
        if (parsedecl(vt1->containerTypeToken, &vtParent, mDefaultSignedness, mSettings)) {
            setValueType(parent, vtParent);
            return;
        }
    }

    if (parent->isCpp() && vt2 && match37(parent->previous())) {
        setValueType(parent, *vt2);
        return;
    }

    // c++17 auto type deduction of braced init list
    if (parent->isCpp() && mSettings.standards.cpp >= Standards::CPP17 && vt2 && match277(parent->tokAt(-2))) {
        Token *autoTok = parent->tokAt(-2);
        setValueType(autoTok, *vt2);
        setAutoTokenProperties(autoTok);
        if (parent->previous()->variable())
            const_cast<Variable*>(parent->previous()->variable())->setValueType(*vt2);
        else
            debugMessage(parent->previous(), "debug", "Missing variable class for variable with varid");
        return;
    }

    if (!vt1)
        return;
    if (parent->astOperand2() && !vt2)
        return;

    const bool ternary = parent->str() == MatchCompiler::makeConstString(":") && parent->astParent() && parent->astParent()->str() == MatchCompiler::makeConstString("?");
    if (ternary) {
        if (vt2 && vt1->pointer == vt2->pointer && vt1->type == vt2->type && vt1->sign == vt2->sign)
            setValueType(parent, *vt2);
        parent = parent->astParent();
    }

    if (ternary || parent->isArithmeticalOp() || parent->tokType() == Token::eIncDecOp) {

        // CONTAINER + x => CONTAINER
        if (parent->str() == MatchCompiler::makeConstString("+") && vt1->type == ValueType::Type::CONTAINER && vt2 && vt2->isIntegral()) {
            setValueType(parent, *vt1);
            return;
        }
        // x + CONTAINER => CONTAINER
        if (parent->str() == MatchCompiler::makeConstString("+") && vt1->isIntegral() && vt2 && vt2->type == ValueType::Type::CONTAINER) {
            setValueType(parent, *vt2);
            return;
        }

        if (parent->isArithmeticalOp()) {
            if (vt1->pointer != 0U && vt2 && vt2->pointer == 0U) {
                setValueType(parent, *vt1);
                return;
            }

            if (vt1->pointer == 0U && vt2 && vt2->pointer != 0U) {
                setValueType(parent, *vt2);
                return;
            }
        } else if (ternary) {
            if (vt1->pointer != 0U && vt2 && vt2->pointer == 0U) {
                if (vt2->isPrimitive())
                    setValueType(parent, *vt1);
                else
                    setValueType(parent, *vt2);
                return;
            }

            if (vt1->pointer == 0U && vt2 && vt2->pointer != 0U) {
                if (vt1->isPrimitive())
                    setValueType(parent, *vt2);
                else
                    setValueType(parent, *vt1);
                return;
            }

            if (vt1->isTypeEqual(vt2)) {
                setValueType(parent, *vt1);
                return;
            }
        }

        if (vt1->pointer != 0U) {
            if (ternary || parent->tokType() == Token::eIncDecOp) // result is pointer
                setValueType(parent, *vt1);
            else // result is pointer diff
                setValueType(parent, ValueType(ValueType::Sign::SIGNED, ValueType::Type::INT, 0U, 0U, "ptrdiff_t"));
            return;
        }

        if (vt1->type == ValueType::Type::LONGDOUBLE || (vt2 && vt2->type == ValueType::Type::LONGDOUBLE)) {
            setValueType(parent, ValueType(ValueType::Sign::UNKNOWN_SIGN, ValueType::Type::LONGDOUBLE, 0U));
            return;
        }
        if (vt1->type == ValueType::Type::DOUBLE || (vt2 && vt2->type == ValueType::Type::DOUBLE)) {
            setValueType(parent, ValueType(ValueType::Sign::UNKNOWN_SIGN, ValueType::Type::DOUBLE, 0U));
            return;
        }
        if (vt1->type == ValueType::Type::FLOAT || (vt2 && vt2->type == ValueType::Type::FLOAT)) {
            setValueType(parent, ValueType(ValueType::Sign::UNKNOWN_SIGN, ValueType::Type::FLOAT, 0U));
            return;
        }

        // iterator +/- integral = iterator
        if (vt1->type == ValueType::Type::ITERATOR && vt2 && vt2->isIntegral() &&
            (parent->str() == MatchCompiler::makeConstString("+") || parent->str() == MatchCompiler::makeConstString("-"))) {
            setValueType(parent, *vt1);
            return;
        }

        if (parent->str() == MatchCompiler::makeConstString("+") && vt1->type == ValueType::Type::CONTAINER && vt2 && vt2->type == ValueType::Type::CONTAINER && vt1->container == vt2->container) {
            setValueType(parent, *vt1);
            return;
        }
    }

    if (vt1->isIntegral() && vt1->pointer == 0U &&
        (!vt2 || (vt2->isIntegral() && vt2->pointer == 0U)) &&
        (ternary || parent->isArithmeticalOp() || parent->tokType() == Token::eBitOp || parent->tokType() == Token::eIncDecOp || parent->isAssignmentOp())) {

        ValueType vt;
        if (!vt2 || vt1->type > vt2->type) {
            vt.type = vt1->type;
            vt.sign = vt1->sign;
            vt.originalTypeName = vt1->originalTypeName;
        } else if (vt1->type == vt2->type) {
            vt.type = vt1->type;
            if (vt1->sign == ValueType::Sign::UNSIGNED || vt2->sign == ValueType::Sign::UNSIGNED)
                vt.sign = ValueType::Sign::UNSIGNED;
            else if (vt1->sign == ValueType::Sign::UNKNOWN_SIGN || vt2->sign == ValueType::Sign::UNKNOWN_SIGN)
                vt.sign = ValueType::Sign::UNKNOWN_SIGN;
            else
                vt.sign = ValueType::Sign::SIGNED;
            vt.originalTypeName = (vt1->originalTypeName.empty() ? vt2 : vt1)->originalTypeName;
        } else {
            vt.type = vt2->type;
            vt.sign = vt2->sign;
            vt.originalTypeName = vt2->originalTypeName;
        }
        if (vt.type < ValueType::Type::INT && !(ternary && vt.type==ValueType::Type::BOOL)) {
            vt.type = ValueType::Type::INT;
            vt.sign = ValueType::Sign::SIGNED;
            vt.originalTypeName.clear();
        }

        setValueType(parent, vt);
        return;
    }
}

static ValueType::Type getEnumType(const Scope* scope, const Platform& platform) // TODO: also determine sign?
{
    ValueType::Type type = ValueType::Type::INT;
    for (const Token* tok = scope->bodyStart; tok && tok != scope->bodyEnd; tok = tok->next()) {
        if (const Token* lam = findLambdaEndToken(tok)) {
            tok = lam;
            continue;
        }
        if (!tok->isAssignmentOp())
            continue;
        const Token* vTok = tok->astOperand2();
        if (!vTok->hasKnownIntValue()) {
            if (!vTok->isLiteral())
                continue;
            if (const ValueType* vt = vTok->valueType()) {
                if ((vt->type > type && (vt->type == ValueType::Type::LONG || vt->type == ValueType::Type::LONGLONG)))
                    type = vt->type;
            }
            continue;
        }
        const MathLib::bigint value = vTok->getKnownIntValue();
        if (!platform.isIntValue(value)) {
            type = ValueType::Type::LONG;
            if (!platform.isLongValue(value))
                type = ValueType::Type::LONGLONG;
        }
    }
    return type;
}

static const Token* parsedecl(const Token* type,
                              ValueType* const valuetype,
                              ValueType::Sign defaultSignedness,
                              const Settings& settings,
                              SourceLocation loc)
{
    if (settings.debugnormal || settings.debugwarnings)
        valuetype->setDebugPath(type, loc);
    const Token * const previousType = type;
    const int pointer0 = valuetype->pointer;
    while (match76(type->previous()) && !endsWith(type->strAt(-1), ':'))
        type = type->previous();
    valuetype->sign = ValueType::Sign::UNKNOWN_SIGN;
    if (!valuetype->typeScope && !valuetype->smartPointerType)
        valuetype->type = ValueType::Type::UNKNOWN_TYPE;
    else if (valuetype->smartPointerType)
        valuetype->type = ValueType::Type::SMART_POINTER;
    else if (valuetype->typeScope->type == ScopeType::eEnum) {
        const Token * enum_type = valuetype->typeScope->enumType;
        if (enum_type) {
            if (enum_type->isSigned())
                valuetype->sign = ValueType::Sign::SIGNED;
            else if (enum_type->isUnsigned())
                valuetype->sign = ValueType::Sign::UNSIGNED;
            else
                valuetype->sign = defaultSignedness; // TODO: this is implementation-dependent might be separate from char
            const ValueType::Type t = ValueType::typeFromString(enum_type->str(), enum_type->isLong());
            if (t != ValueType::Type::UNKNOWN_TYPE)
                valuetype->type = t;
            else if (enum_type->isStandardType())
                valuetype->fromLibraryType(enum_type->str(), settings);
        } else
            valuetype->type = getEnumType(valuetype->typeScope, settings.platform);
    } else
        valuetype->type = ValueType::Type::RECORD;
    const bool cpp = type->isCpp();
    bool par = false;
    while (match278(type) && !match279(type) && type->varId() == 0 &&
           !type->variable() && !type->function()) {
        bool isIterator = false;
        if (type->str() == MatchCompiler::makeConstString("(")) {
            if (!match222(type))
                break;
            if (match280(type->link()))
                break;
            if (par)
                break;
            par = true;
        }
        if (match37(type) && type->next()->valueType()) {
            const ValueType *vt2 = type->next()->valueType();
            if (valuetype->sign == ValueType::Sign::UNKNOWN_SIGN)
                valuetype->sign = vt2->sign;
            if (valuetype->type == ValueType::Type::UNKNOWN_TYPE)
                valuetype->type = vt2->type;
            valuetype->constness += vt2->constness;
            valuetype->pointer += vt2->pointer;
            valuetype->reference = vt2->reference;
            type = type->linkAt(1)->next();
            continue;
        }
        if (type->isSigned())
            valuetype->sign = ValueType::Sign::SIGNED;
        else if (type->isUnsigned())
            valuetype->sign = ValueType::Sign::UNSIGNED;
        if (valuetype->type == ValueType::Type::UNKNOWN_TYPE &&
            type->type() && type->type()->isTypeAlias() && type->type()->typeStart &&
            type->type()->typeStart->str() != type->str() && type->type()->typeStart != previousType)
            parsedecl(type->type()->typeStart, valuetype, defaultSignedness, settings);
        else if (match269(type))
            valuetype->constness |= (1 << (valuetype->pointer - pointer0));
        else if (match270(type))
            valuetype->volatileness |= (1 << (valuetype->pointer - pointer0));
        else if (settings.clang && type->str().size() > 2 && type->str().find("::") < type->str().find('<')) {
            TokenList typeTokens(settings, type->isCpp() ? Standards::Language::CPP : Standards::Language::C);
            std::string::size_type pos1 = 0;
            do {
                const std::string::size_type pos2 = type->str().find("::", pos1);
                if (pos2 == std::string::npos) {
                    typeTokens.addtoken(type->str().substr(pos1), 0, 0, 0, false);
                    break;
                }
                typeTokens.addtoken(type->str().substr(pos1, pos2 - pos1), 0, 0, 0, false);
                typeTokens.addtoken("::", 0, 0, 0, false);
                pos1 = pos2 + 2;
            } while (pos1 < type->str().size());
            const Library::Container* container =
                settings.library.detectContainerOrIterator(typeTokens.front(), &isIterator);
            if (container) {
                if (isIterator)
                    valuetype->type = ValueType::Type::ITERATOR;
                else
                    valuetype->type = ValueType::Type::CONTAINER;
                valuetype->container = container;
            } else {
                const Scope *scope = type->scope();
                valuetype->typeScope = scope->symdb.findScope(typeTokens.front(), scope);
                if (valuetype->typeScope)
                    valuetype->type = (scope->type == ScopeType::eClass) ? ValueType::Type::RECORD : ValueType::Type::NONSTD;
            }
        } else if (ValueType::Type type_s = ValueType::typeFromString(type->str(), type->isLong())) { // != UNKNOWN_TYPE
            const ValueType::Type t0 = valuetype->type;
            valuetype->type = type_s;
            if (t0 == ValueType::Type::LONG) {
                if (valuetype->type == ValueType::Type::LONG)
                    valuetype->type = ValueType::Type::LONGLONG;
                else if (valuetype->type == ValueType::Type::DOUBLE)
                    valuetype->type = ValueType::Type::LONGDOUBLE;
            }
        } else if (type->str() == MatchCompiler::makeConstString("auto")) {
            const ValueType *vt = type->valueType();
            if (!vt)
                return nullptr;
            valuetype->type = vt->type;
            valuetype->pointer = vt->pointer;
            valuetype->reference = vt->reference;
            if (vt->sign != ValueType::Sign::UNKNOWN_SIGN)
                valuetype->sign = vt->sign;
            valuetype->constness = vt->constness;
            valuetype->volatileness = vt->volatileness;
            valuetype->originalTypeName = vt->originalTypeName;
            const bool hasConst = match157(type->previous());
            const bool hasVolatile = match270(type->previous());
            while (match281(type) && !type->variable()) {
                if (type->str() == MatchCompiler::makeConstString("*")) {
                    valuetype->pointer = 1;
                    if (hasConst)
                        valuetype->constness = 1;
                    if (hasVolatile)
                        valuetype->volatileness = 1;
                } else if (type->str() == MatchCompiler::makeConstString("&")) {
                    valuetype->reference = Reference::LValue;
                } else if (type->str() == MatchCompiler::makeConstString("&&")) {
                    valuetype->reference = Reference::RValue;
                }
                if (type->str() == MatchCompiler::makeConstString("const"))
                    valuetype->constness |= (1 << valuetype->pointer);
                if (type->str() == MatchCompiler::makeConstString("volatile"))
                    valuetype->volatileness |= (1 << valuetype->pointer);
                type = type->next();
            }
            break;
        } else if (type->str() == MatchCompiler::makeConstString("*"))
            valuetype->pointer++;
        else if (type->str() == MatchCompiler::makeConstString("&"))
            valuetype->reference = Reference::LValue;
        else if (type->str() == MatchCompiler::makeConstString("&&"))
            valuetype->reference = Reference::RValue;
        else if (type->isStandardType())
            valuetype->fromLibraryType(type->str(), settings);
        else if (const Library::Container* container = (cpp ? settings.library.detectContainerOrIterator(type, &isIterator) : nullptr)) {
            if (isIterator)
                valuetype->type = ValueType::Type::ITERATOR;
            else
                valuetype->type = ValueType::Type::CONTAINER;
            valuetype->container = container;
            while (match282(type) && type->str() != MatchCompiler::makeConstString("const")) {
                if (type->str() == MatchCompiler::makeConstString("<") && type->link()) {
                    if (container->type_templateArgNo >= 0) {
                        const Token *templateType = type->next();
                        for (int j = 0; templateType && j < container->type_templateArgNo; j++)
                            templateType = templateType->nextTemplateArgument();
                        valuetype->containerTypeToken = templateType;
                    }
                    type = type->link();
                }
                type = type->next();
            }
            if (type && type->str() == MatchCompiler::makeConstString("(") && type->previous()->function())
                // we are past the end of the type
                type = type->previous();
            continue;
        } else if (const Library::SmartPointer* smartPointer = (cpp ? settings.library.detectSmartPointer(type) : nullptr)) {
            const Token* argTok = findmatch66(type) ;
            if (!argTok)
                break;
            valuetype->smartPointer = smartPointer;
            valuetype->smartPointerTypeToken = argTok->next();
            valuetype->smartPointerType = argTok->next()->type();
            valuetype->type = ValueType::Type::SMART_POINTER;
            type = argTok->link();
            if (type)
                type = type->next();
            continue;
        } else if (match14(type)) {
            std::string typestr;
            const Token *end = type;
            while (match14(end)) {
                typestr += end->str() + "::";
                end = end->tokAt(2);
            }
            typestr += end->str();
            if (valuetype->fromLibraryType(typestr, settings))
                type = end;
        } else if (!valuetype->typeScope && (type->str() == MatchCompiler::makeConstString("struct") || type->str() == MatchCompiler::makeConstString("enum")) && valuetype->type != ValueType::Type::SMART_POINTER)
            valuetype->type = type->str() == MatchCompiler::makeConstString("struct") ? ValueType::Type::RECORD : ValueType::Type::NONSTD;
        else if (!valuetype->typeScope && type->type() && type->type()->classScope && valuetype->type != ValueType::Type::SMART_POINTER) {
            if (type->type()->classScope->type == ScopeType::eEnum) {
                valuetype->sign = ValueType::Sign::SIGNED;
                valuetype->type = getEnumType(type->type()->classScope, settings.platform);
            } else {
                valuetype->type = ValueType::Type::RECORD;
            }
            valuetype->typeScope = type->type()->classScope;
        } else if (type->isName() && valuetype->sign != ValueType::Sign::UNKNOWN_SIGN && valuetype->pointer == 0U)
            return nullptr;
        else if (match283(type->previous())) {
            if (!type->isKeyword())
                valuetype->fromLibraryType(type->str(), settings);
        }
        if (!type->originalName().empty())
            valuetype->originalTypeName = type->originalName();
        type = type->next();
        if (type && type->link() && type->str() == MatchCompiler::makeConstString("<"))
            type = type->link()->next();
    }

    // Set signedness for integral types..
    if (valuetype->isIntegral() && valuetype->sign == ValueType::Sign::UNKNOWN_SIGN) {
        if (valuetype->type == ValueType::Type::CHAR)
            valuetype->sign = defaultSignedness;
        else if (valuetype->type >= ValueType::Type::SHORT)
            valuetype->sign = ValueType::Sign::SIGNED;
    }

    return (type && (valuetype->type != ValueType::Type::UNKNOWN_TYPE || valuetype->pointer > 0 || valuetype->reference != Reference::None)) ? type : nullptr;
}

static const Scope *getClassScope(const Token *tok)
{
    return tok && tok->valueType() && tok->valueType()->typeScope && tok->valueType()->typeScope->isClassOrStruct() ?
           tok->valueType()->typeScope :
           nullptr;
}

static const Function *getOperatorFunction(const Token * const tok)
{
    const std::string functionName("operator" + tok->str());

    const Scope *classScope = getClassScope(tok->astOperand1());
    if (classScope) {
        auto it = utils::as_const(classScope->functionMap).find(functionName);
        if (it != classScope->functionMap.end())
            return it->second;
    }

    classScope = getClassScope(tok->astOperand2());
    if (classScope) {
        auto it = utils::as_const(classScope->functionMap).find(functionName);
        if (it != classScope->functionMap.end())
            return it->second;
    }

    return nullptr;
}

static const Function* getFunction(const Token* tok) {
    if (!tok)
        return nullptr;
    if (tok->function() && tok->function()->retDef)
        return tok->function();
    if (const Variable* lvar = tok->variable()) { // lambda
        const Function* lambda{};
        if (match284(lvar->nameToken()->next(), lvar->declarationId()))
            lambda = lvar->nameToken()->tokAt(4)->function();
        else if (match285(lvar->nameToken()->next()))
            lambda = lvar->nameToken()->tokAt(2)->function();
        if (lambda && lambda->retDef)
            return lambda;
    }
    return nullptr;
}

static int getIntegerConstantMacroWidth(const Token* tok) {
    if (!match24(tok) || match172(tok->next()->astOperand2()))
        return 0;
    const std::string &name = tok->str();
    if (name.back() != 'C')
        return 0;
    size_t pos = (name[0] == 'U') ? 1 : 0;
    if (name[pos] != 'I' || name[pos + 1] != 'N' || name[pos + 2] != 'T')
        return 0;
    pos += 3;
    int intnum = 0;
    if (name[pos] == '8') {
        ++pos;
        intnum = 8;
    }
    else if (name[pos] == '1' && name[pos + 1] == '6') {
        pos += 2;
        intnum = 16;
    }
    else if (name[pos] == '3' && name[pos + 1] == '2') {
        pos += 2;
        intnum = 32;
    }
    else if (name[pos] == '6' && name[pos + 1] == '4') {
        pos += 2;
        intnum = 64;
    }
    else
        return 0;
    if (pos + 2 != name.size() || name[pos] != '_')
        return 0;
    return intnum;
}

void SymbolDatabase::setValueTypeInTokenList(bool reportDebugWarnings, Token *tokens)
{
    if (!tokens)
        tokens = mTokenizer.list.front();

    for (Token *tok = tokens; tok; tok = tok->next())
        tok->setValueType(nullptr);

    for (Token *tok = tokens; tok; tok = tok->next()) {
        if (tok->isNumber()) {
            if (MathLib::isFloat(tok->str())) {
                ValueType::Type type = ValueType::Type::DOUBLE;
                const char suffix = tok->str()[tok->str().size() - 1];
                if (suffix == 'f' || suffix == 'F')
                    type = ValueType::Type::FLOAT;
                else if (suffix == 'L' || suffix == 'l')
                    type = ValueType::Type::LONGDOUBLE;
                setValueType(tok, ValueType(ValueType::Sign::UNKNOWN_SIGN, type, 0U));
            } else if (MathLib::isInt(tok->str())) {
                const std::string tokStr = MathLib::abs(tok->str());
                const bool unsignedSuffix = (tokStr.find_last_of("uU") != std::string::npos);
                ValueType::Sign sign = unsignedSuffix ? ValueType::Sign::UNSIGNED : ValueType::Sign::SIGNED;
                ValueType::Type type = ValueType::Type::INT;
                const MathLib::biguint value = MathLib::toBigUNumber(tokStr, tok);
                for (std::size_t pos = tokStr.size() - 1U; pos > 0U; --pos) {
                    const char suffix = tokStr[pos];
                    if (suffix == 'u' || suffix == 'U')
                        sign = ValueType::Sign::UNSIGNED;
                    else if (suffix == 'l' || suffix == 'L')
                        type = (type == ValueType::Type::INT) ? ValueType::Type::LONG : ValueType::Type::LONGLONG;
                    else if (pos > 2U && suffix == '4' && tokStr[pos - 1] == '6' && tokStr[pos - 2] == 'i') {
                        type = ValueType::Type::LONGLONG;
                        pos -= 2;
                    } else break;
                }
                if (mSettings.platform.type != Platform::Type::Unspecified) {
                    if (type <= ValueType::Type::INT && mSettings.platform.isIntValue(unsignedSuffix ? (value >> 1) : value))
                        type = ValueType::Type::INT;
                    else if (type <= ValueType::Type::INT && !MathLib::isDec(tokStr) && mSettings.platform.isIntValue(value >> 2)) {
                        type = ValueType::Type::INT;
                        sign = ValueType::Sign::UNSIGNED;
                    } else if (type <= ValueType::Type::LONG && mSettings.platform.isLongValue(unsignedSuffix ? (value >> 1) : value))
                        type = ValueType::Type::LONG;
                    else if (type <= ValueType::Type::LONG && !MathLib::isDec(tokStr) && mSettings.platform.isLongValue(value >> 2)) {
                        type = ValueType::Type::LONG;
                        sign = ValueType::Sign::UNSIGNED;
                    } else if (mSettings.platform.isLongLongValue(unsignedSuffix ? (value >> 1) : value))
                        type = ValueType::Type::LONGLONG;
                    else {
                        type = ValueType::Type::LONGLONG;
                        sign = ValueType::Sign::UNSIGNED;
                    }
                }

                setValueType(tok, ValueType(sign, type, 0U));
            }
        } else if (tok->isComparisonOp() || tok->tokType() == Token::eLogicalOp) {
            if (tok->isCpp() && tok->isComparisonOp() && (getClassScope(tok->astOperand1()) || getClassScope(tok->astOperand2()))) {
                const Function *function = getOperatorFunction(tok);
                if (function) {
                    ValueType vt;
                    parsedecl(function->retDef, &vt, mDefaultSignedness, mSettings);
                    setValueType(tok, vt);
                    continue;
                }
            }
            setValueType(tok, ValueType(ValueType::Sign::UNKNOWN_SIGN, ValueType::Type::BOOL, 0U));
        } else if (tok->isBoolean()) {
            setValueType(tok, ValueType(ValueType::Sign::UNKNOWN_SIGN, ValueType::Type::BOOL, 0U));
        } else if (tok->tokType() == Token::eChar || tok->tokType() == Token::eString) {
            nonneg int const pointer = tok->tokType() == Token::eChar ? 0 : 1;
            nonneg int const constness = tok->tokType() == Token::eChar ? 0 : 1;
            nonneg int const volatileness = 0;
            ValueType valuetype(ValueType::Sign::UNKNOWN_SIGN, ValueType::Type::CHAR, pointer, constness, volatileness);

            if (tok->isCpp() && mSettings.standards.cpp >= Standards::CPP20 && tok->isUtf8()) {
                valuetype.originalTypeName = "char8_t";
                valuetype.fromLibraryType(valuetype.originalTypeName, mSettings);
            } else if (tok->isUtf16()) {
                valuetype.originalTypeName = "char16_t";
                valuetype.fromLibraryType(valuetype.originalTypeName, mSettings);
            } else if (tok->isUtf32()) {
                valuetype.originalTypeName = "char32_t";
                valuetype.fromLibraryType(valuetype.originalTypeName, mSettings);
            } else if (tok->isLong()) {
                valuetype.originalTypeName = "wchar_t";
                valuetype.type = ValueType::Type::WCHAR_T;
            } else if ((tok->tokType() == Token::eChar) && ((!tok->isCpp() && tok->isCChar()) || (tok->isCMultiChar()))) {
                valuetype.type = ValueType::Type::INT;
                valuetype.sign = ValueType::Sign::SIGNED;
            }
            setValueType(tok, valuetype);
        } else if (tok->link() && match22(tok)) {
            const Token* start = tok->astOperand1() ? tok->astOperand1()->findExpressionStartEndTokens().first : nullptr;
            // cast
            if (tok->isCast() && !tok->astOperand2() && match286(tok)) {
                ValueType valuetype;
                if (match105(parsedecl(tok->next(), &valuetype, mDefaultSignedness, mSettings)))
                    setValueType(tok, valuetype);
            }

            // C++ cast
            else if (tok->astOperand2() && match287(tok->astOperand1()) && tok->astOperand1()->linkAt(1)) {
                ValueType valuetype;
                if (match55(parsedecl(tok->astOperand1()->tokAt(2), &valuetype, mDefaultSignedness, mSettings)))
                    setValueType(tok, valuetype);
            }

            // Construct smart pointer
            else if (start && start->isCpp() && mSettings.library.isSmartPointer(start)) {
                ValueType valuetype;
                if (parsedecl(start, &valuetype, mDefaultSignedness, mSettings)) {
                    setValueType(tok, valuetype);
                    setValueType(tok->astOperand1(), valuetype);
                }

            }

            // function or lambda
            else if (const Function* f = getFunction(tok->previous())) {
                ValueType valuetype;
                if (parsedecl(f->retDef, &valuetype, mDefaultSignedness, mSettings))
                    setValueType(tok, valuetype);
            }

            else if (match288(tok->previous())) {
                ValueType valuetype(ValueType::Sign::UNSIGNED, ValueType::Type::LONG, 0U);
                if (mSettings.platform.type == Platform::Type::Win64)
                    valuetype.type = ValueType::Type::LONGLONG;

                valuetype.originalTypeName = "size_t";
                setValueType(tok, valuetype);

                if (match289(tok)) {
                    ValueType vt;
                    if (parsedecl(tok->next(), &vt, mDefaultSignedness, mSettings)) {
                        setValueType(tok->next(), vt);
                    }
                }
            }

            // functions from stdint.h
            else if (const int macroWidth = getIntegerConstantMacroWidth(tok->previous())) {
                ValueType valuetype;
                if (macroWidth == mSettings.platform.char_bit)
                    valuetype.type = ValueType::Type::CHAR;
                else if (macroWidth == mSettings.platform.short_bit)
                    valuetype.type = ValueType::Type::SHORT;
                else if (macroWidth == mSettings.platform.int_bit)
                    valuetype.type = ValueType::Type::INT;
                else if (macroWidth == mSettings.platform.long_bit)
                    valuetype.type = ValueType::Type::LONG;
                else if (macroWidth == mSettings.platform.long_long_bit)
                    valuetype.type = ValueType::Type::LONGLONG;
                else
                    valuetype.type = ValueType::Type::INT;

                if (tok->strAt(-1)[0] == 'U')
                    valuetype.sign = ValueType::Sign::UNSIGNED;
                else
                    valuetype.sign = ValueType::Sign::SIGNED;
                setValueType(tok, valuetype);
            }

            // function style cast
            else if (tok->previous() && tok->previous()->isStandardType()) {
                ValueType valuetype;
                if (tok->astOperand1() && valuetype.fromLibraryType(tok->astOperand1()->expressionString(), mSettings)) {
                    setValueType(tok, valuetype);
                    continue;
                }

                valuetype.type = ValueType::typeFromString(tok->strAt(-1), tok->previous()->isLong());
                if (tok->previous()->isUnsigned())
                    valuetype.sign = ValueType::Sign::UNSIGNED;
                else if (tok->previous()->isSigned())
                    valuetype.sign = ValueType::Sign::SIGNED;
                else if (valuetype.isIntegral() && valuetype.type != ValueType::UNKNOWN_INT)
                    valuetype.sign = (valuetype.type == ValueType::Type::CHAR) ? mDefaultSignedness : ValueType::Sign::SIGNED;
                setValueType(tok, valuetype);
            }

            // constructor call
            else if (tok->previous() && tok->previous()->function() && tok->previous()->function()->isConstructor()) {
                ValueType valuetype;
                valuetype.type = ValueType::RECORD;
                valuetype.typeScope = tok->previous()->function()->tokenDef->scope();
                setValueType(tok, valuetype);
            }

            else if (match20(tok->previous()) && tok->tokAt(-2) && tok->tokAt(-2)->valueType()) {
                ValueType vt = *tok->tokAt(-2)->valueType();
                setValueType(tok, vt);
            }

            // library type/function
            else if (tok->previous()) {
                // Aggregate constructor
                if (match76(tok->previous())) {
                    ValueType valuetype;
                    if (parsedecl(tok->previous(), &valuetype, mDefaultSignedness, mSettings)) {
                        if (valuetype.typeScope) {
                            setValueType(tok, valuetype);
                            continue;
                        }
                    }
                }
                if (tok->isCpp() && tok->astParent() && match12(tok->astOperand1())) {
                    const Token *typeStartToken = tok->astOperand1();
                    while (typeStartToken && typeStartToken->str() == MatchCompiler::makeConstString("::"))
                        typeStartToken = typeStartToken->astOperand1();
                    if (mSettings.library.detectContainerOrIterator(typeStartToken) ||
                        mSettings.library.detectSmartPointer(typeStartToken)) {
                        ValueType vt;
                        if (parsedecl(typeStartToken, &vt, mDefaultSignedness, mSettings)) {
                            setValueType(tok, vt);
                            continue;
                        }
                    }

                    const std::string e = tok->astOperand1()->expressionString();

                    if ((e == MatchCompiler::makeConstString("std::make_shared") || e == MatchCompiler::makeConstString("std::make_unique")) && match290(tok->astOperand1())) {
                        ValueType vt;
                        parsedecl(tok->astOperand1()->tokAt(3), &vt, mDefaultSignedness, mSettings);
                        if (vt.typeScope) {
                            vt.smartPointerType = vt.typeScope->definedType;
                            vt.typeScope = nullptr;
                        }
                        if (e == MatchCompiler::makeConstString("std::make_shared") && mSettings.library.smartPointers().count("std::shared_ptr") > 0)
                            vt.smartPointer = &mSettings.library.smartPointers().at("std::shared_ptr");
                        if (e == MatchCompiler::makeConstString("std::make_unique") && mSettings.library.smartPointers().count("std::unique_ptr") > 0)
                            vt.smartPointer = &mSettings.library.smartPointers().at("std::unique_ptr");
                        vt.type = ValueType::Type::SMART_POINTER;
                        vt.smartPointerTypeToken = tok->astOperand1()->tokAt(3);
                        setValueType(tok, vt);
                        continue;
                    }

                    ValueType podtype;
                    if (podtype.fromLibraryType(e, mSettings)) {
                        setValueType(tok, podtype);
                        continue;
                    }
                }

                const std::string& typestr(mSettings.library.returnValueType(tok->previous()));
                if (!typestr.empty()) {
                    ValueType valuetype;
                    TokenList tokenList(mSettings, tok->isCpp() ? Standards::Language::CPP : Standards::Language::C);
                    const std::string str(typestr+";");
                    tokenList.createTokensFromBuffer(str.data(), str.size()); // TODO: check result?
                    tokenList.simplifyStdType();
                    if (parsedecl(tokenList.front(), &valuetype, mDefaultSignedness, mSettings)) {
                        valuetype.originalTypeName = typestr;
                        setValueType(tok, valuetype);
                    }
                }

                //Is iterator fetching function invoked on container?
                const bool isReturnIter = typestr == MatchCompiler::makeConstString("iterator");
                if (typestr.empty() || isReturnIter) {
                    if (match61(tok->astOperand1()) &&
                        tok->astOperand1()->astOperand1() &&
                        tok->astOperand1()->astOperand2() &&
                        tok->astOperand1()->astOperand1()->valueType() &&
                        tok->astOperand1()->astOperand1()->valueType()->container) {
                        const Library::Container *cont = tok->astOperand1()->astOperand1()->valueType()->container;
                        const auto it = cont->functions.find(tok->astOperand1()->astOperand2()->str());
                        if (it != cont->functions.end()) {
                            if (it->second.yield == Library::Container::Yield::START_ITERATOR ||
                                it->second.yield == Library::Container::Yield::END_ITERATOR ||
                                it->second.yield == Library::Container::Yield::ITERATOR) {
                                ValueType vt;
                                vt.type = ValueType::Type::ITERATOR;
                                vt.container = cont;
                                vt.containerTypeToken =
                                    tok->astOperand1()->astOperand1()->valueType()->containerTypeToken;
                                setValueType(tok, vt);
                                continue;
                            }
                        }
                        //Is iterator fetching function called?
                    } else if (match75(tok->astOperand1()) &&
                               tok->astOperand2() &&
                               tok->astOperand2()->isVariable()) {
                        const auto* const paramVariable = tok->astOperand2()->variable();
                        if (!paramVariable ||
                            !paramVariable->valueType() ||
                            !paramVariable->valueType()->container) {
                            continue;
                        }

                        const auto yield = astFunctionYield(tok->previous(), mSettings);
                        if (yield == Library::Container::Yield::START_ITERATOR ||
                            yield == Library::Container::Yield::END_ITERATOR ||
                            yield == Library::Container::Yield::ITERATOR) {
                            ValueType vt;
                            vt.type = ValueType::Type::ITERATOR;
                            vt.container = paramVariable->valueType()->container;
                            vt.containerTypeToken = paramVariable->valueType()->containerTypeToken;
                            setValueType(tok, vt);
                        }
                    }
                    if (isReturnIter) {
                        const std::vector<const Token*> args = getArguments(tok);
                        if (!args.empty()) {
                            const Library::ArgumentChecks::IteratorInfo* info = mSettings.library.getArgIteratorInfo(tok->previous(), 1);
                            if (info && info->it) {
                                const Token* contTok = args[0];
                                if (match61(args[0]->astOperand1()) && args[0]->astOperand1()->astOperand1()) // .begin()
                                    contTok = args[0]->astOperand1()->astOperand1();
                                else if (match29(args[0]) && args[0]->astOperand2()) // std::begin()
                                    contTok = args[0]->astOperand2();
                                while (match13(contTok)) // move to container token
                                    contTok = contTok->astOperand1();
                                if (match61(contTok))
                                    contTok = contTok->astOperand2();
                                if (contTok && contTok->variable() && contTok->variable()->valueType() && contTok->variable()->valueType()->container) {
                                    ValueType vt;
                                    vt.type = ValueType::Type::ITERATOR;
                                    vt.container = contTok->variable()->valueType()->container;
                                    vt.containerTypeToken = contTok->variable()->valueType()->containerTypeToken;
                                    setValueType(tok, vt);
                                } else if (match29(contTok) && contTok->astOperand1() && contTok->astOperand1()->function()) {
                                    const Function* func = contTok->astOperand1()->function();
                                    if (const ValueType* funcVt = func->tokenDef->next()->valueType()) {
                                        ValueType vt;
                                        vt.type = ValueType::Type::ITERATOR;
                                        vt.container = funcVt->container;
                                        vt.containerTypeToken = funcVt->containerTypeToken;
                                        setValueType(tok, vt);
                                    }
                                }
                            }
                        }
                    }
                    continue;
                }
                TokenList tokenList(mSettings, tok->isCpp() ? Standards::Language::CPP : Standards::Language::C);
                const std::string str(typestr+";");
                if (tokenList.createTokensFromBuffer(str.data(), str.size())) {
                    ValueType vt;
                    tokenList.simplifyPlatformTypes();
                    tokenList.simplifyStdType();
                    if (parsedecl(tokenList.front(), &vt, mDefaultSignedness, mSettings)) {
                        vt.originalTypeName = typestr;
                        setValueType(tok, vt);
                    }
                }
            }
        } else if (tok->str() == MatchCompiler::makeConstString("return")) {
            const Scope *functionScope = tok->scope();
            while (functionScope && functionScope->isExecutable() && functionScope->type != ScopeType::eLambda && functionScope->type != ScopeType::eFunction)
                functionScope = functionScope->nestedIn;
            if (functionScope && functionScope->type == ScopeType::eFunction && functionScope->function &&
                functionScope->function->retDef) {
                ValueType vt = ValueType::parseDecl(functionScope->function->retDef, mSettings);
                setValueType(tok, vt);
                if (match291(tok))
                    setValueType(tok->next(), vt);
            }
        } else if (tok->variable()) {
            setValueType(tok, *tok->variable());
            if (!tok->variable()->valueType() && tok->valueType())
                const_cast<Variable*>(tok->variable())->setValueType(*tok->valueType());
        } else if (tok->enumerator()) {
            setValueType(tok, *tok->enumerator());
        } else if (tok->isKeyword() && tok->str() == MatchCompiler::makeConstString("new")) {
            const Token *typeTok = tok->next();
            if (match292(typeTok))
                typeTok = typeTok->link()->next();
            bool isIterator = false;
            if (const Library::Container* c = mSettings.library.detectContainerOrIterator(typeTok, &isIterator)) {
                ValueType vt;
                vt.pointer = 1;
                vt.container = c;
                vt.type = isIterator ? ValueType::Type::ITERATOR : ValueType::Type::CONTAINER;
                setValueType(tok, vt);
                continue;
            }
            std::string typestr;
            while (match14(typeTok)) {
                typestr += typeTok->str() + "::";
                typeTok = typeTok->tokAt(2);
            }
            if (!match293(typeTok))
                continue;
            typestr += typeTok->str();
            ValueType vt;
            vt.pointer = 1;
            if (typeTok->type() && typeTok->type()->classScope) {
                vt.type = ValueType::Type::RECORD;
                vt.typeScope = typeTok->type()->classScope;
            } else {
                vt.type = ValueType::typeFromString(typestr, typeTok->isLong());
                if (vt.type == ValueType::Type::UNKNOWN_TYPE)
                    vt.fromLibraryType(typestr, mSettings);
                if (vt.type == ValueType::Type::UNKNOWN_TYPE)
                    continue;
                if (typeTok->isUnsigned())
                    vt.sign = ValueType::Sign::UNSIGNED;
                else if (typeTok->isSigned())
                    vt.sign = ValueType::Sign::SIGNED;
                if (vt.sign == ValueType::Sign::UNKNOWN_SIGN && vt.isIntegral())
                    vt.sign = (vt.type == ValueType::Type::CHAR) ? mDefaultSignedness : ValueType::Sign::SIGNED;
            }
            setValueType(tok, vt);
            if (match29(tok->astOperand1())) {
                vt.pointer--;
                setValueType(tok->astOperand1(), vt);
            }
        } else if (tok->isKeyword() && tok->str() == MatchCompiler::makeConstString("return") && tok->scope()) {
            const Scope* fscope = tok->scope();
            while (fscope && !fscope->function)
                fscope = fscope->nestedIn;
            if (fscope && fscope->function && fscope->function->retDef) {
                ValueType vt;
                parsedecl(fscope->function->retDef, &vt, mDefaultSignedness, mSettings);
                setValueType(tok, vt);
            }
        } else if (tok->isKeyword() && tok->str() == MatchCompiler::makeConstString("this") && tok->scope()->isExecutable()) {
            const Scope* fscope = tok->scope();
            while (fscope && !fscope->function)
                fscope = fscope->nestedIn;
            const Scope* defScope = fscope && fscope->function->tokenDef ? fscope->function->tokenDef->scope() : nullptr;
            if (defScope && defScope->isClassOrStruct()) {
                ValueType vt(ValueType::Sign::UNKNOWN_SIGN, ValueType::Type::RECORD, 1);
                vt.typeScope = defScope;
                if (fscope->function->isConst())
                    vt.constness = 1;
                if (fscope->function->isVolatile())
                    vt.volatileness = 1;
                setValueType(tok, vt);
            }
        }
    }

    if (reportDebugWarnings && mSettings.debugwarnings) {
        for (Token *tok = tokens; tok; tok = tok->next()) {
            if (tok->str() == MatchCompiler::makeConstString("auto") && !tok->valueType()) {
                if (match294(tok->next()) && isLambdaCaptureList(tok->tokAt(5)))
                    continue;
                if (match295(tok->next()) && isLambdaCaptureList(tok->tokAt(3)))
                    continue;
                debugMessage(tok, "autoNoType", "auto token with no type.");
            }
        }
    }

    // Update functions with new type information.
    createSymbolDatabaseSetFunctionPointers(false);

    // Update auto variables with new type information.
    createSymbolDatabaseSetVariablePointers();
}

ValueType ValueType::parseDecl(const Token *type, const Settings &settings)
{
    ValueType vt;
    parsedecl(type, &vt, settings.platform.defaultSign == 'u' ? Sign::UNSIGNED : Sign::SIGNED, settings);
    return vt;
}

ValueType::Type ValueType::typeFromString(const std::string &typestr, bool longType)
{
    if (typestr == MatchCompiler::makeConstString("void"))
        return ValueType::Type::VOID;
    if (typestr == MatchCompiler::makeConstString("bool") || typestr == MatchCompiler::makeConstString("_Bool"))
        return ValueType::Type::BOOL;
    if (typestr== MatchCompiler::makeConstString("char"))
        return ValueType::Type::CHAR;
    if (typestr == MatchCompiler::makeConstString("short"))
        return ValueType::Type::SHORT;
    if (typestr == MatchCompiler::makeConstString("wchar_t"))
        return ValueType::Type::WCHAR_T;
    if (typestr == MatchCompiler::makeConstString("int"))
        return ValueType::Type::INT;
    if (typestr == MatchCompiler::makeConstString("long"))
        return longType ? ValueType::Type::LONGLONG : ValueType::Type::LONG;
    if (typestr == MatchCompiler::makeConstString("float"))
        return ValueType::Type::FLOAT;
    if (typestr == MatchCompiler::makeConstString("double"))
        return longType ? ValueType::Type::LONGDOUBLE : ValueType::Type::DOUBLE;
    return ValueType::Type::UNKNOWN_TYPE;
}

bool ValueType::fromLibraryType(const std::string &typestr, const Settings &settings)
{
    const Library::PodType* podtype = settings.library.podtype(typestr);
    if (podtype && (podtype->sign == 's' || podtype->sign == 'u')) {
        if (podtype->size == 1)
            type = ValueType::Type::CHAR;
        else if (podtype->size == settings.platform.sizeof_int)
            type = ValueType::Type::INT;
        else if (podtype->size == settings.platform.sizeof_short)
            type = ValueType::Type::SHORT;
        else if (podtype->size == settings.platform.sizeof_long)
            type = ValueType::Type::LONG;
        else if (podtype->size == settings.platform.sizeof_long_long)
            type = ValueType::Type::LONGLONG;
        else if (podtype->stdtype == Library::PodType::Type::BOOL)
            type = ValueType::Type::BOOL;
        else if (podtype->stdtype == Library::PodType::Type::CHAR)
            type = ValueType::Type::CHAR;
        else if (podtype->stdtype == Library::PodType::Type::SHORT)
            type = ValueType::Type::SHORT;
        else if (podtype->stdtype == Library::PodType::Type::INT)
            type = ValueType::Type::INT;
        else if (podtype->stdtype == Library::PodType::Type::LONG)
            type = ValueType::Type::LONG;
        else if (podtype->stdtype == Library::PodType::Type::LONGLONG)
            type = ValueType::Type::LONGLONG;
        else
            type = ValueType::Type::UNKNOWN_INT;
        sign = (podtype->sign == 'u') ? ValueType::UNSIGNED : ValueType::SIGNED;
        return true;
    }
    if (podtype && podtype->stdtype == Library::PodType::Type::NO) {
        type = ValueType::Type::POD;
        sign = ValueType::UNKNOWN_SIGN;
        return true;
    }

    const Library::PlatformType *platformType = settings.library.platform_type(typestr, settings.platform.toString());
    if (platformType) {
        if (platformType->mType == MatchCompiler::makeConstString("char"))
            type = ValueType::Type::CHAR;
        else if (platformType->mType == MatchCompiler::makeConstString("short"))
            type = ValueType::Type::SHORT;
        else if (platformType->mType == MatchCompiler::makeConstString("wchar_t"))
            type = ValueType::Type::WCHAR_T;
        else if (platformType->mType == MatchCompiler::makeConstString("int"))
            type = platformType->mLong ? ValueType::Type::LONG : ValueType::Type::INT;
        else if (platformType->mType == MatchCompiler::makeConstString("long"))
            type = platformType->mLong ? ValueType::Type::LONGLONG : ValueType::Type::LONG;
        if (platformType->mSigned)
            sign = ValueType::SIGNED;
        else if (platformType->mUnsigned)
            sign = ValueType::UNSIGNED;
        if (platformType->mPointer)
            pointer = 1;
        if (platformType->mPtrPtr)
            pointer = 2;
        if (platformType->mConstPtr)
            constness = 1;
        return true;
    }
    if (!podtype && (typestr == MatchCompiler::makeConstString("size_t") || typestr == MatchCompiler::makeConstString("std::size_t"))) {
        originalTypeName = "size_t";
        sign = ValueType::UNSIGNED;
        if (settings.platform.sizeof_size_t == settings.platform.sizeof_long)
            type = ValueType::Type::LONG;
        else if (settings.platform.sizeof_size_t == settings.platform.sizeof_long_long)
            type = ValueType::Type::LONGLONG;
        else if (settings.platform.sizeof_size_t == settings.platform.sizeof_int)
            type = ValueType::Type::INT;
        else
            type = ValueType::Type::UNKNOWN_INT;
        return true;
    }

    return false;
}

std::string ValueType::dump() const
{
    std::string ret;
    switch (type) {
    case UNKNOWN_TYPE:
        return "";
    case NONSTD:
        ret += "valueType-type=\"nonstd\"";
        break;
    case POD:
        ret += "valueType-type=\"pod\"";
        break;
    case RECORD:
        ret += "valueType-type=\"record\"";
        break;
    case SMART_POINTER:
        ret += "valueType-type=\"smart-pointer\"";
        break;
    case CONTAINER: {
        ret += "valueType-type=\"container\"";
        ret += " valueType-containerId=\"";
        ret += id_string(container);
        ret += "\"";
        break;
    }
    case ITERATOR:
        ret += "valueType-type=\"iterator\"";
        break;
    case VOID:
        ret += "valueType-type=\"void\"";
        break;
    case BOOL:
        ret += "valueType-type=\"bool\"";
        break;
    case CHAR:
        ret += "valueType-type=\"char\"";
        break;
    case SHORT:
        ret += "valueType-type=\"short\"";
        break;
    case WCHAR_T:
        ret += "valueType-type=\"wchar_t\"";
        break;
    case INT:
        ret += "valueType-type=\"int\"";
        break;
    case LONG:
        ret += "valueType-type=\"long\"";
        break;
    case LONGLONG:
        ret += "valueType-type=\"long long\"";
        break;
    case UNKNOWN_INT:
        ret += "valueType-type=\"unknown int\"";
        break;
    case FLOAT:
        ret += "valueType-type=\"float\"";
        break;
    case DOUBLE:
        ret += "valueType-type=\"double\"";
        break;
    case LONGDOUBLE:
        ret += "valueType-type=\"long double\"";
        break;
    }

    switch (sign) {
    case Sign::UNKNOWN_SIGN:
        break;
    case Sign::SIGNED:
        ret += " valueType-sign=\"signed\"";
        break;
    case Sign::UNSIGNED:
        ret += " valueType-sign=\"unsigned\"";
        break;
    }

    if (bits >= 0) {
        ret += " valueType-bits=\"";
        ret += std::to_string(bits);
        ret += '\"';
    }

    if (pointer > 0) {
        ret += " valueType-pointer=\"";
        ret += std::to_string(pointer);
        ret += '\"';
    }

    if (constness > 0) {
        ret += " valueType-constness=\"";
        ret += std::to_string(constness);
        ret += '\"';
    }

    if (volatileness > 0) {
        ret += " valueType-volatileness=\"";
        ret += std::to_string(volatileness);
        ret += '\"';
    }

    if (reference == Reference::None)
        ret += " valueType-reference=\"None\"";
    else if (reference == Reference::LValue)
        ret += " valueType-reference=\"LValue\"";
    else if (reference == Reference::RValue)
        ret += " valueType-reference=\"RValue\"";

    if (typeScope) {
        ret += " valueType-typeScope=\"";
        ret += id_string(typeScope);
        ret += '\"';
    }

    if (!originalTypeName.empty()) {
        ret += " valueType-originalTypeName=\"";
        ret += ErrorLogger::toxml(originalTypeName);
        ret += '\"';
    }

    return ret;
}

bool ValueType::isConst(nonneg int indirect) const
{
    if (indirect > pointer)
        return false;
    return constness & (1 << (pointer - indirect));
}

bool ValueType::isVolatile(nonneg int indirect) const
{
    if (indirect > pointer)
        return false;
    return volatileness & (1 << (pointer - indirect));
}
MathLib::bigint ValueType::typeSize(const Platform &platform, bool p) const
{
    if (p && pointer)
        return platform.sizeof_pointer;

    if (typeScope && typeScope->definedType && typeScope->definedType->sizeOf)
        return typeScope->definedType->sizeOf;

    switch (type) {
    case ValueType::Type::BOOL:
        return platform.sizeof_bool;
    case ValueType::Type::CHAR:
        return 1;
    case ValueType::Type::SHORT:
        return platform.sizeof_short;
    case ValueType::Type::WCHAR_T:
        return platform.sizeof_wchar_t;
    case ValueType::Type::INT:
        return platform.sizeof_int;
    case ValueType::Type::LONG:
        return platform.sizeof_long;
    case ValueType::Type::LONGLONG:
        return platform.sizeof_long_long;
    case ValueType::Type::FLOAT:
        return platform.sizeof_float;
    case ValueType::Type::DOUBLE:
        return platform.sizeof_double;
    case ValueType::Type::LONGDOUBLE:
        return platform.sizeof_long_double;
    default:
        break;
    }

    // Unknown invalid size
    return 0;
}

bool ValueType::isTypeEqual(const ValueType* that) const
{
    if (!that)
        return false;
    auto tie = [](const ValueType* vt) {
        return std::tie(vt->type, vt->container, vt->pointer, vt->typeScope, vt->smartPointer);
    };
    return tie(this) == tie(that);
}

std::string ValueType::str() const
{
    std::string ret;
    if (constness & 1)
        ret = " const";
    if (volatileness & 1)
        ret = " volatile";
    if (type == VOID)
        ret += " void";
    else if (isIntegral()) {
        if (sign == SIGNED)
            ret += " signed";
        else if (sign == UNSIGNED)
            ret += " unsigned";
        if (type == BOOL)
            ret += " bool";
        else if (type == CHAR)
            ret += " char";
        else if (type == SHORT)
            ret += " short";
        else if (type == WCHAR_T)
            ret += " wchar_t";
        else if (type == INT)
            ret += " int";
        else if (type == LONG)
            ret += " long";
        else if (type == LONGLONG)
            ret += " long long";
        else if (type == UNKNOWN_INT)
            ret += " unknown_int";
    } else if (type == FLOAT)
        ret += " float";
    else if (type == DOUBLE)
        ret += " double";
    else if (type == LONGDOUBLE)
        ret += " long double";
    else if ((type == ValueType::Type::NONSTD || type == ValueType::Type::RECORD) && typeScope) {
        std::string className(typeScope->className);
        const Scope *scope = typeScope->definedType ? typeScope->definedType->enclosingScope : typeScope->nestedIn;
        while (scope && scope->type != ScopeType::eGlobal) {
            if (scope->type == ScopeType::eClass || scope->type == ScopeType::eStruct || scope->type == ScopeType::eNamespace)
                className = scope->className + "::" + className;
            scope = (scope->definedType && scope->definedType->enclosingScope) ? scope->definedType->enclosingScope : scope->nestedIn;
        }
        ret += ' ' + className;
    } else if (type == ValueType::Type::CONTAINER && container) {
        ret += " container(" + container->startPattern + ')';
    } else if (type == ValueType::Type::ITERATOR && container) {
        ret += " iterator(" + container->startPattern + ')';
    } else if (type == ValueType::Type::SMART_POINTER && smartPointer) {
        ret += " smart-pointer(" + smartPointer->name + ")";
    }
    for (unsigned int p = 0; p < pointer; p++) {
        ret += " *";
        if (constness & (2 << p))
            ret += " const";
        if (volatileness & (2 << p))
            ret += " volatile";
    }
    if (reference == Reference::LValue)
        ret += " &";
    else if (reference == Reference::RValue)
        ret += " &&";
    if (ret.empty())
        return {};
    return ret.substr(1);
}

void ValueType::setDebugPath(const Token* tok, SourceLocation ctx, const SourceLocation &local)
{
    std::string file = ctx.file_name();
    if (file.empty())
        return;
    std::string s = Path::stripDirectoryPart(file) + ":" + std::to_string(ctx.line()) + ": " + ctx.function_name() +
                    " => " + local.function_name();
    debugPath.emplace_back(tok, std::move(s));
}

ValueType::MatchResult ValueType::matchParameter(const ValueType *call, const ValueType *func)
{
    if (!call || !func)
        return ValueType::MatchResult::UNKNOWN;
    if (call->pointer != func->pointer) {
        if (call->pointer > 1 && func->pointer == 1 && func->type == ValueType::Type::VOID)
            return ValueType::MatchResult::FALLBACK1;
        if (call->pointer == 1 && func->pointer == 0 && func->isIntegral() && func->sign != ValueType::Sign::SIGNED)
            return ValueType::MatchResult::FALLBACK1;
        if (call->pointer == 1 && call->type == ValueType::Type::CHAR && func->pointer == 0 && func->container && func->container->stdStringLike)
            return ValueType::MatchResult::FALLBACK2;
        return ValueType::MatchResult::NOMATCH; // TODO
    }
    if (call->pointer > 0) {
        if ((call->constness | func->constness) != func->constness)
            return ValueType::MatchResult::NOMATCH;
        if ((call->volatileness | func->volatileness) != func->volatileness)
            return ValueType::MatchResult::NOMATCH;
        if (call->constness == 0 && func->constness != 0 && func->reference != Reference::None)
            return ValueType::MatchResult::NOMATCH;
        if (call->volatileness == 0 && func->volatileness != 0 && func->reference != Reference::None)
            return ValueType::MatchResult::NOMATCH;
    }
    if (call->type != func->type || (call->isEnum() && !func->isEnum())) {
        if (call->type == ValueType::Type::VOID || func->type == ValueType::Type::VOID)
            return ValueType::MatchResult::FALLBACK1;
        if (call->pointer > 0)
            return func->type == ValueType::UNKNOWN_TYPE ? ValueType::MatchResult::UNKNOWN : ValueType::MatchResult::NOMATCH;
        if (call->isIntegral() && func->isIntegral())
            return call->type < func->type ?
                   ValueType::MatchResult::FALLBACK1 :
                   ValueType::MatchResult::FALLBACK2;
        if (call->isFloat() && func->isFloat())
            return ValueType::MatchResult::FALLBACK1;
        if (call->isIntegral() && func->isFloat())
            return ValueType::MatchResult::FALLBACK2;
        if (call->isFloat() && func->isIntegral())
            return ValueType::MatchResult::FALLBACK2;
        return ValueType::MatchResult::UNKNOWN; // TODO
    }

    if (call->typeScope != nullptr || func->typeScope != nullptr) {
        if (call->typeScope != func->typeScope &&
            !(call->typeScope && func->typeScope && call->typeScope->definedType && call->typeScope->definedType->isDerivedFrom(func->typeScope->className)))
            return ValueType::MatchResult::NOMATCH;
    }

    if (call->container != nullptr || func->container != nullptr) {
        if (call->container != func->container)
            return ValueType::MatchResult::NOMATCH;
    }

    if (func->typeScope != nullptr && func->container != nullptr) {
        if (func->type < ValueType::Type::VOID || func->type == ValueType::Type::UNKNOWN_INT)
            return ValueType::MatchResult::UNKNOWN;
    }

    if (call->isIntegral() && func->isIntegral() && call->sign != ValueType::Sign::UNKNOWN_SIGN && func->sign != ValueType::Sign::UNKNOWN_SIGN && call->sign != func->sign)
        return ValueType::MatchResult::FALLBACK1;

    if (func->reference != Reference::None && (func->constness > call->constness || func->volatileness > call->volatileness))
        return ValueType::MatchResult::FALLBACK1;

    return ValueType::MatchResult::SAME;
}

ValueType::MatchResult ValueType::matchParameter(const ValueType *call, const Variable *callVar, const Variable *funcVar)
{
    ValueType vt;
    const ValueType* pvt = funcVar->valueType();
    if (pvt && funcVar->isArray() && !(funcVar->isStlType() && match261(funcVar->typeStartToken()))) { // std::array doesn't decay to a pointer
        vt = *pvt;
        if (vt.pointer == 0) // don't bump array of pointers
            vt.pointer = funcVar->dimensions().size();
        pvt = &vt;
    }
    ValueType cvt;
    if (call && callVar && callVar->isArray() && !(callVar->isStlType() && match261(callVar->typeStartToken()))) {
        cvt = *call;
        if (cvt.pointer == 0) // don't bump array of pointers
            cvt.pointer = callVar->dimensions().size();
        call = &cvt;
    }
    const ValueType::MatchResult res = ValueType::matchParameter(call, pvt);
    if (callVar && ((res == ValueType::MatchResult::SAME && call->container) || res == ValueType::MatchResult::UNKNOWN)) {
        const std::string type1 = getTypeString(callVar->typeStartToken());
        const std::string type2 = getTypeString(funcVar->typeStartToken());
        const bool templateVar =
            funcVar->scope() && funcVar->scope()->function && funcVar->scope()->function->templateDef;
        if (type1 == type2)
            return ValueType::MatchResult::SAME;
        if (!templateVar && type1.find("auto") == std::string::npos && type2.find("auto") == std::string::npos)
            return ValueType::MatchResult::NOMATCH;
    }
    return res;
}

void SymbolDatabase::getErrorMessages(ErrorLogger& /*errorLogger*/)
{
    // TODO
    //SymbolDatabase symdb;
    //symdb.returnImplicitIntError(nullptr);
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
