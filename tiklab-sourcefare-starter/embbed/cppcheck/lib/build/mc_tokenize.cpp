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
// pattern: {
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %name%|::|:
MAYBE_UNUSED static inline bool match2(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: class
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("class")))
        return false;
    return true;
}
// pattern: enum
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")))
        return false;
    return true;
}
// pattern: class|struct|union|enum|%name%|>|>> {
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: class|struct|union|enum|{|}|;
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: class|struct|union|enum
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    return true;
}
// pattern: ;|,|[|=|)|>|(|{
MAYBE_UNUSED static inline bool match8(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: public|private|protected
MAYBE_UNUSED static inline bool match9(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("private")) || (tok->str() == MatchCompiler::makeConstString("protected"))))
        return false;
    return true;
}
// pattern: ;|)|>
MAYBE_UNUSED static inline bool match10(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: public:|private:|protected:
MAYBE_UNUSED static inline bool match11(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("private:")) || (tok->str() == MatchCompiler::makeConstString("protected:"))))
        return false;
    return true;
}
// pattern: %type%
MAYBE_UNUSED static inline bool match12(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: ,|<
MAYBE_UNUSED static inline bool match13(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: ) {
MAYBE_UNUSED static inline bool match14(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: return|new|const|struct
MAYBE_UNUSED static inline bool match15(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("new")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    return true;
}
// pattern: return|new|const|volatile
MAYBE_UNUSED static inline bool match16(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("new")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        return false;
    return true;
}
// pattern: typedef|}|>
MAYBE_UNUSED static inline bool match17(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: return|new|const|friend|public|private|protected|throw|extern
MAYBE_UNUSED static inline bool match18(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("new")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("friend")) || (tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("private")) || (tok->str() == MatchCompiler::makeConstString("protected")) || (tok->str() == MatchCompiler::makeConstString("throw")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern"))))
        return false;
    return true;
}
// pattern: friend class
MAYBE_UNUSED static inline bool match19(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("friend")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("class")))
        return false;
    return true;
}
// pattern: ;|{
MAYBE_UNUSED static inline bool match20(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: )|*
MAYBE_UNUSED static inline bool match21(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: ) .|(|[
MAYBE_UNUSED static inline bool match22(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: const|volatile
MAYBE_UNUSED static inline bool match23(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        return false;
    return true;
}
// pattern: %name%
MAYBE_UNUSED static inline bool match24(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: ( * %type% ) (
MAYBE_UNUSED static inline bool match25(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
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
// pattern: * ( * %type% ) (
MAYBE_UNUSED static inline bool match26(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
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
// pattern: * ( * %type% ) ;
MAYBE_UNUSED static inline bool match27(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: * ( %type% [
MAYBE_UNUSED static inline bool match28(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] ) ;|=
MAYBE_UNUSED static inline bool match29(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: * ( * %type% (
MAYBE_UNUSED static inline bool match30(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: * [
MAYBE_UNUSED static inline bool match31(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] ;
MAYBE_UNUSED static inline bool match32(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: [|>|;
MAYBE_UNUSED static inline bool match33(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: *|&
MAYBE_UNUSED static inline bool match34(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: [)>,]
MAYBE_UNUSED static inline bool match35(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(")>,", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name% ::
MAYBE_UNUSED static inline bool match36(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: const
MAYBE_UNUSED static inline bool match37(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    return true;
}
// pattern: ;|{|}|:|public:|private:|protected:
MAYBE_UNUSED static inline bool match38(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("private:")) || (tok->str() == MatchCompiler::makeConstString("protected:"))))
        return false;
    return true;
}
// pattern: if|for|while
MAYBE_UNUSED static inline bool match39(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while"))))
        return false;
    return true;
}
// pattern: )
MAYBE_UNUSED static inline bool match40(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: }
MAYBE_UNUSED static inline bool match41(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: [;{}]
MAYBE_UNUSED static inline bool match42(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    return true;
}
// pattern: typename
MAYBE_UNUSED static inline bool match43(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("typename")))
        return false;
    return true;
}
// pattern: const| enum|struct|union|class %name%| {
MAYBE_UNUSED static inline bool match44(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || (tok->str() == MatchCompiler::makeConstString("class"))))
        return false;
    tok = tok->next();
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: {
template<class T> MAYBE_UNUSED static inline T * findmatch45(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: %name%|* %name%|*
MAYBE_UNUSED static inline bool match46(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: %name% ;
MAYBE_UNUSED static inline bool match47(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: enum|struct|union|class {
MAYBE_UNUSED static inline bool match48(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || (tok->str() == MatchCompiler::makeConstString("class"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %name%|*|&|&&
MAYBE_UNUSED static inline bool match49(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: %name% [
MAYBE_UNUSED static inline bool match50(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] [
MAYBE_UNUSED static inline bool match51(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ( * const| %name% ) (
MAYBE_UNUSED static inline bool match52(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
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
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) ;
MAYBE_UNUSED static inline bool match53(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: %name% ( !!(
MAYBE_UNUSED static inline bool match54(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    return true;
}
// pattern: typedef const %name% %name% ;
MAYBE_UNUSED static inline bool match55(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
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
// pattern: %name% )
MAYBE_UNUSED static inline bool match57(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: %name% [({]
MAYBE_UNUSED static inline bool match58(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("({", tok->str()[0]))
        return false;
    return true;
}
// pattern: ) (
MAYBE_UNUSED static inline bool match59(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: const| struct|class %name% {
MAYBE_UNUSED static inline bool match60(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("class"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: public|protected|private|<
MAYBE_UNUSED static inline bool match61(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("protected")) || (tok->str() == MatchCompiler::makeConstString("private")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: const| struct|class|union|enum %name% %name%|{
MAYBE_UNUSED static inline bool match62(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: %name% %name% ;
MAYBE_UNUSED static inline bool match63(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: enum|union|struct|class
MAYBE_UNUSED static inline bool match64(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("class"))))
        return false;
    return true;
}
// pattern: const|class|struct|union
MAYBE_UNUSED static inline bool match65(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    return true;
}
// pattern: %name%|*|&|&&|::
MAYBE_UNUSED static inline bool match66(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: *
MAYBE_UNUSED static inline bool match67(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: (|[
MAYBE_UNUSED static inline bool match68(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: [
MAYBE_UNUSED static inline bool match69(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: %name% ( !!*
MAYBE_UNUSED static inline bool match70(const Token* tok) {
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
// pattern: %name% ( * %name% ) [
MAYBE_UNUSED static inline bool match71(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
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
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: *|&|&&
MAYBE_UNUSED static inline bool match72(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: ( * %name% ) (
MAYBE_UNUSED static inline bool match73(const Token* tok) {
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
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ( *
MAYBE_UNUSED static inline bool match74(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: &|&& %name% ;
MAYBE_UNUSED static inline bool match75(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: ] ; %name% = {
MAYBE_UNUSED static inline bool match76(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
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
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: [{([]
MAYBE_UNUSED static inline bool match77(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{([", tok->str()[0]))
        return false;
    return true;
}
// pattern: [})]]
MAYBE_UNUSED static inline bool match78(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("})]", tok->str()[0]))
        return false;
    return true;
}
// pattern: typedef|const
MAYBE_UNUSED static inline bool match79(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        return false;
    return true;
}
// pattern: %name% %name%|*|&|&&|;|(|)|,|::
MAYBE_UNUSED static inline bool match80(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: ( %name% =
MAYBE_UNUSED static inline bool match81(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: ) %name%|{
MAYBE_UNUSED static inline bool match82(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: , %name% =
MAYBE_UNUSED static inline bool match83(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: new %name% [
MAYBE_UNUSED static inline bool match84(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: < %name%
MAYBE_UNUSED static inline bool match85(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: , %name% >|>>
MAYBE_UNUSED static inline bool match86(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    return true;
}
// pattern: [;{}(]
MAYBE_UNUSED static inline bool match87(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}(", tok->str()[0]))
        return false;
    return true;
}
// pattern: public|protected|private
MAYBE_UNUSED static inline bool match88(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("protected")) || (tok->str() == MatchCompiler::makeConstString("private"))))
        return false;
    return true;
}
// pattern: , %name% :
MAYBE_UNUSED static inline bool match89(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: )|]
MAYBE_UNUSED static inline bool match90(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    return true;
}
// pattern: _Generic (
MAYBE_UNUSED static inline bool match91(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("_Generic")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %name%|;|{|}|(|,|<
MAYBE_UNUSED static inline bool match92(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: !!. %name% (
MAYBE_UNUSED static inline bool match93(const Token* tok) {
    if (tok && tok->str() == MatchCompiler::makeConstString("."))
        return false;
    tok = tok ? tok->next() : nullptr;
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: (
MAYBE_UNUSED static inline bool match94(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: struct|union|class|enum %name% %name%
MAYBE_UNUSED static inline bool match95(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: ; %name% ;
MAYBE_UNUSED static inline bool match96(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: <|, %name% * ,|>
MAYBE_UNUSED static inline bool match97(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: %name%|::|&|*|&&
MAYBE_UNUSED static inline bool match98(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: [+-*/&|~!]
MAYBE_UNUSED static inline bool match99(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("+-*/&|~!", tok->str()[0]))
        return false;
    return true;
}
// pattern: struct|union|class|enum
MAYBE_UNUSED static inline bool match100(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    return true;
}
// pattern: ( %name% ) (|%name%|%num%
MAYBE_UNUSED static inline bool match101(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || tok->isName() || tok->isNumber()))
        return false;
    return true;
}
// pattern: < %name% > (
MAYBE_UNUSED static inline bool match102(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %name%|:|::
MAYBE_UNUSED static inline bool match103(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: %name% ) (
MAYBE_UNUSED static inline bool match104(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ; %any%
MAYBE_UNUSED static inline bool match105(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    return true;
}
// pattern: ( typedef
MAYBE_UNUSED static inline bool match106(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef")))
        return false;
    return true;
}
// pattern: class|struct|namespace %any%
MAYBE_UNUSED static inline bool match107(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("namespace"))))
        return false;
    tok = tok->next();
    if (!tok || false)
        return false;
    return true;
}
// pattern: %name% :: %name%
MAYBE_UNUSED static inline bool match108(const Token* tok) {
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
// pattern: struct|enum|union|class %type%| {|:
MAYBE_UNUSED static inline bool match109(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || (tok->str() == MatchCompiler::makeConstString("class"))))
        return false;
    tok = tok->next();
    if (tok && ((tok->isName() && tok->varId() == 0U)))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: enum %type% %type% ;
MAYBE_UNUSED static inline bool match110(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: %type% ::
MAYBE_UNUSED static inline bool match111(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: const|struct|enum %type%
MAYBE_UNUSED static inline bool match112(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: unsigned|signed
MAYBE_UNUSED static inline bool match113(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("unsigned")) || (tok->str() == MatchCompiler::makeConstString("signed"))))
        return false;
    return true;
}
// pattern: [|;|,|(
MAYBE_UNUSED static inline bool match114(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: const (
MAYBE_UNUSED static inline bool match115(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: :: %type%
MAYBE_UNUSED static inline bool match116(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: *|&|&&|const
MAYBE_UNUSED static inline bool match117(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        return false;
    return true;
}
// pattern: ;|,
MAYBE_UNUSED static inline bool match118(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: ( *|%name%
MAYBE_UNUSED static inline bool match119(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || tok->isName()))
        return false;
    return true;
}
// pattern: * %name% ) (
MAYBE_UNUSED static inline bool match120(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: typeof (
MAYBE_UNUSED static inline bool match121(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("typeof")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) %type% ;
MAYBE_UNUSED static inline bool match122(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: %type% ) (
MAYBE_UNUSED static inline bool match123(const Token* tok) {
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
// pattern: ) const|volatile|;
MAYBE_UNUSED static inline bool match124(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: ( (
MAYBE_UNUSED static inline bool match125(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) const|volatile| ) ;|,
MAYBE_UNUSED static inline bool match126(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: ( * (
MAYBE_UNUSED static inline bool match127(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ;
MAYBE_UNUSED static inline bool match128(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: ( %type% (
MAYBE_UNUSED static inline bool match129(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ( * ( * %type% ) (
MAYBE_UNUSED static inline bool match130(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
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
// pattern: ) ) (
MAYBE_UNUSED static inline bool match131(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) ;|,
MAYBE_UNUSED static inline bool match132(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: ( * %type% (
MAYBE_UNUSED static inline bool match133(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ( * ( %type% ) (
MAYBE_UNUSED static inline bool match134(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
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
// pattern: ( *|& %type% ) [
MAYBE_UNUSED static inline bool match135(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ( %type% :: * %type% ) ;
MAYBE_UNUSED static inline bool match136(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: typedef
MAYBE_UNUSED static inline bool match137(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef")))
        return false;
    return true;
}
// pattern: %name% ;|,|)|=
MAYBE_UNUSED static inline bool match138(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: %name% ) {
MAYBE_UNUSED static inline bool match139(const Token* tok) {
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
// pattern: (|{|[
MAYBE_UNUSED static inline bool match140(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: ) const| {
MAYBE_UNUSED static inline bool match141(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: class|struct %name% [:{]
MAYBE_UNUSED static inline bool match142(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(":{", tok->str()[0]))
        return false;
    return true;
}
// pattern: case|;|{|} %type% :
MAYBE_UNUSED static inline bool match143(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: %type% *|&
MAYBE_UNUSED static inline bool match144(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: =
MAYBE_UNUSED static inline bool match145(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: <
MAYBE_UNUSED static inline bool match146(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: >
MAYBE_UNUSED static inline bool match147(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    return true;
}
// pattern: public|protected|private|: %type% {|,
MAYBE_UNUSED static inline bool match148(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("protected")) || (tok->str() == MatchCompiler::makeConstString("private")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: > (
MAYBE_UNUSED static inline bool match149(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ( const %name% )
MAYBE_UNUSED static inline bool match150(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: <|,
MAYBE_UNUSED static inline bool match151(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: &|*| &|*| >|,
MAYBE_UNUSED static inline bool match152(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: sizeof ( %type% )
MAYBE_UNUSED static inline bool match153(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
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
// pattern: operator const
MAYBE_UNUSED static inline bool match154(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    return true;
}
// pattern: class|struct
MAYBE_UNUSED static inline bool match155(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    return true;
}
// pattern: struct|class|union
MAYBE_UNUSED static inline bool match156(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    return true;
}
// pattern: %name% ( )
MAYBE_UNUSED static inline bool match157(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: class|struct|union
MAYBE_UNUSED static inline bool match158(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    return true;
}
// pattern: using %name% ::|;
MAYBE_UNUSED static inline bool match159(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: %name%|] [
MAYBE_UNUSED static inline bool match160(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: * (
MAYBE_UNUSED static inline bool match161(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %type% (
MAYBE_UNUSED static inline bool match162(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: &|*|&&
MAYBE_UNUSED static inline bool match163(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: ( *|&|&& *|&|&& %name%
MAYBE_UNUSED static inline bool match164(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: [(),;]
MAYBE_UNUSED static inline bool match165(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(),;", tok->str()[0]))
        return false;
    return true;
}
// pattern: const|noexcept
MAYBE_UNUSED static inline bool match166(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("noexcept"))))
        return false;
    return true;
}
// pattern: ( true|false )
MAYBE_UNUSED static inline bool match167(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBoolean) && tok->str() == MatchCompiler::makeConstString("true")) || ((tok->tokType() == Token::eBoolean) && tok->str() == MatchCompiler::makeConstString("false"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: , %name% ;|=|,
MAYBE_UNUSED static inline bool match168(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: namespace|class|struct|union %name% {|:|::|<
MAYBE_UNUSED static inline bool match169(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("namespace")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: using namespace %name% ;|::
MAYBE_UNUSED static inline bool match170(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: const|volatile|final|override|&|&&|noexcept
MAYBE_UNUSED static inline bool match171(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || (tok->str() == MatchCompiler::makeConstString("final")) || (tok->str() == MatchCompiler::makeConstString("override")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->str() == MatchCompiler::makeConstString("noexcept"))))
        return false;
    return true;
}
// pattern: throw|noexcept (
MAYBE_UNUSED static inline bool match172(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("throw")) || (tok->str() == MatchCompiler::makeConstString("noexcept"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: :|, %name%
MAYBE_UNUSED static inline bool match173(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %name% :: ~ %name%
MAYBE_UNUSED static inline bool match174(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: :: %name%
MAYBE_UNUSED static inline bool match175(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: class|struct|union %name%
MAYBE_UNUSED static inline bool match176(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: public|protected|private|virtual
MAYBE_UNUSED static inline bool match177(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("protected")) || (tok->str() == MatchCompiler::makeConstString("private")) || (tok->str() == MatchCompiler::makeConstString("virtual"))))
        return false;
    return true;
}
// pattern: ;|,|{
MAYBE_UNUSED static inline bool match178(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: class|struct|union|enum|namespace
MAYBE_UNUSED static inline bool match179(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || (tok->str() == MatchCompiler::makeConstString("namespace"))))
        return false;
    return true;
}
// pattern: > ::
MAYBE_UNUSED static inline bool match180(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: >|>>
MAYBE_UNUSED static inline bool match181(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    return true;
}
// pattern: [;{}] %name%
MAYBE_UNUSED static inline bool match182(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: :: %name% (
MAYBE_UNUSED static inline bool match183(const Token* tok) {
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
// pattern: :: ~ %name% (
MAYBE_UNUSED static inline bool match184(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: using ::| %name% ::
MAYBE_UNUSED static inline bool match185(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: [;,]
MAYBE_UNUSED static inline bool match186(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";,", tok->str()[0]))
        return false;
    return true;
}
// pattern: enum class|struct
MAYBE_UNUSED static inline bool match187(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    return true;
}
// pattern: %name%|:|::|<
MAYBE_UNUSED static inline bool match188(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: {|}|namespace|class|struct|union
MAYBE_UNUSED static inline bool match189(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString("namespace")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    return true;
}
// pattern: template < !!>
MAYBE_UNUSED static inline bool match190(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString(">"))
        return false;
    return true;
}
// pattern: using %name% = ::| %name%
MAYBE_UNUSED static inline bool match191(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: using %name% [ [
MAYBE_UNUSED static inline bool match192(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] ] = ::| %name%
MAYBE_UNUSED static inline bool match193(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: class|struct|union|enum %name%| {|:
MAYBE_UNUSED static inline bool match194(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    tok = tok->next();
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: template %name%
MAYBE_UNUSED static inline bool match195(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: const|class|struct|union|enum %type%
MAYBE_UNUSED static inline bool match196(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: [|,|(
MAYBE_UNUSED static inline bool match197(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: .
MAYBE_UNUSED static inline bool match198(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: enum %name% {
MAYBE_UNUSED static inline bool match199(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: typedef
template<class T> MAYBE_UNUSED static inline T * findmatch200(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: %type% *
MAYBE_UNUSED static inline bool match201(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: > *
MAYBE_UNUSED static inline bool match202(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: private|protected|public|__published : !!:
MAYBE_UNUSED static inline bool match203(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("private")) || (tok->str() == MatchCompiler::makeConstString("protected")) || (tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("__published"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString(":"))
        return false;
    return true;
}
// pattern: ( & %name% )
MAYBE_UNUSED static inline bool match204(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: %str%
MAYBE_UNUSED static inline bool match205(const Token* tok) {
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    return true;
}
// pattern: _T|_TEXT|TEXT ( %str% )
MAYBE_UNUSED static inline bool match206(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("_T")) || (tok->str() == MatchCompiler::makeConstString("_TEXT")) || (tok->str() == MatchCompiler::makeConstString("TEXT"))))
        return false;
    tok = tok->next();
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
// pattern: ?|:|,|(|[|{|return|case|sizeof|%op% +|-
MAYBE_UNUSED static inline bool match207(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")) || tok->isOp()))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-"))))
        return false;
    return true;
}
// pattern: %name% (|;
MAYBE_UNUSED static inline bool match208(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: %op%
MAYBE_UNUSED static inline bool match209(const Token* tok) {
    if (!tok || !tok->isOp())
        return false;
    return true;
}
// pattern: +|- %num%
MAYBE_UNUSED static inline bool match210(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: extern \"C\"|\"C++\"
MAYBE_UNUSED static inline bool match211(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("\"C\"")) || (tok->str() == MatchCompiler::makeConstString("\"C++\""))))
        return false;
    return true;
}
// pattern: [;{]
MAYBE_UNUSED static inline bool match212(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{", tok->str()[0]))
        return false;
    return true;
}
// pattern: [;{}:] ( {
MAYBE_UNUSED static inline bool match213(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}:", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } ) ;
MAYBE_UNUSED static inline bool match214(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: [;{}] %type% :
MAYBE_UNUSED static inline bool match215(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: [;{}] %num%|%str% ;
MAYBE_UNUSED static inline bool match216(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isNumber() || (tok->tokType() == Token::eString)))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: ( { %bool%|%char%|%num%|%str%|%name% ; } )
MAYBE_UNUSED static inline bool match217(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isBoolean() || (tok->tokType() == Token::eChar) || tok->isNumber() || (tok->tokType() == Token::eString) || tok->isName()))
        return false;
    tok = tok->next();
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
// pattern: __CPPCHECK_EMBEDDED_SQL_EXEC__ SQL
MAYBE_UNUSED static inline bool match218(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("__CPPCHECK_EMBEDDED_SQL_EXEC__")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("SQL")))
        return false;
    return true;
}
// pattern: %num% [ %name% ]
MAYBE_UNUSED static inline bool match219(const Token* tok) {
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    return true;
}
// pattern: %name% ( void )
MAYBE_UNUSED static inline bool match220(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
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
// pattern: sizeof|decltype|typeof|return
MAYBE_UNUSED static inline bool match221(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")) || (tok->str() == MatchCompiler::makeConstString("decltype")) || (tok->str() == MatchCompiler::makeConstString("typeof")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return"))))
        return false;
    return true;
}
// pattern: = {
MAYBE_UNUSED static inline bool match222(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: { {
MAYBE_UNUSED static inline bool match223(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } }
MAYBE_UNUSED static inline bool match224(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: %var% [ ] =
MAYBE_UNUSED static inline bool match225(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: !!* %var% [ ] = { %str% } ;
MAYBE_UNUSED static inline bool match226(const Token* tok) {
    if (tok && tok->str() == MatchCompiler::makeConstString("*"))
        return false;
    tok = tok ? tok->next() : nullptr;
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: %var% [ ] = {
MAYBE_UNUSED static inline bool match227(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: {|(|[|<
MAYBE_UNUSED static inline bool match228(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: [ %num% ]
MAYBE_UNUSED static inline bool match229(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    return true;
}
// pattern: [},]
MAYBE_UNUSED static inline bool match230(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("},", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name% [ ] = { [
MAYBE_UNUSED static inline bool match231(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: [{,] [
MAYBE_UNUSED static inline bool match232(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] =
MAYBE_UNUSED static inline bool match233(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: [(<]
MAYBE_UNUSED static inline bool match234(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(<", tok->str()[0]))
        return false;
    return true;
}
// pattern: [{};)]
MAYBE_UNUSED static inline bool match235(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{};)", tok->str()[0]))
        return false;
    return true;
}
// pattern: [:{};]
MAYBE_UNUSED static inline bool match236(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(":{};", tok->str()[0]))
        return false;
    return true;
}
// pattern: : %name% [({]
MAYBE_UNUSED static inline bool match237(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("({", tok->str()[0]))
        return false;
    return true;
}
// pattern: [:,] %name% [({]
MAYBE_UNUSED static inline bool match238(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(":,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("({", tok->str()[0]))
        return false;
    return true;
}
// pattern: [;{}:] case
MAYBE_UNUSED static inline bool match239(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}:", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case")))
        return false;
    return true;
}
// pattern: [;{}] %name% : !!;
MAYBE_UNUSED static inline bool match240(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString(";"))
        return false;
    return true;
}
// pattern: class|struct|enum
MAYBE_UNUSED static inline bool match241(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    return true;
}
// pattern: case %num%|%char% ... %num%|%char% :
MAYBE_UNUSED static inline bool match242(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isNumber() || (tok->tokType() == Token::eChar)))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isNumber() || (tok->tokType() == Token::eChar)))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: using namespace %name% ::|<|;
MAYBE_UNUSED static inline bool match243(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: namespace|class|struct|union %name% {|::|:|<
MAYBE_UNUSED static inline bool match244(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("namespace")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: {|:
MAYBE_UNUSED static inline bool match245(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: ;|<
MAYBE_UNUSED static inline bool match246(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: throw|noexcept
MAYBE_UNUSED static inline bool match247(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("throw")) || (tok->str() == MatchCompiler::makeConstString("noexcept"))))
        return false;
    return true;
}
// pattern: alignas (
MAYBE_UNUSED static inline bool match248(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("alignas")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: namespace|public|private|protected
MAYBE_UNUSED static inline bool match249(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("namespace")) || (tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("private")) || (tok->str() == MatchCompiler::makeConstString("protected"))))
        return false;
    return true;
}
// pattern: decltype (
MAYBE_UNUSED static inline bool match250(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("decltype")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: struct|union|enum
MAYBE_UNUSED static inline bool match251(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    return true;
}
// pattern: class|typename
MAYBE_UNUSED static inline bool match252(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || (tok->str() == MatchCompiler::makeConstString("typename"))))
        return false;
    return true;
}
// pattern: const|extern
MAYBE_UNUSED static inline bool match253(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern"))))
        return false;
    return true;
}
// pattern: void const| *|(
MAYBE_UNUSED static inline bool match254(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("void")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: < >
MAYBE_UNUSED static inline bool match255(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    return true;
}
// pattern: %or%|%oror%|&&|&|^|+|-|*|/
MAYBE_UNUSED static inline bool match256(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("/"))))
        return false;
    return true;
}
// pattern: > %name% %or%|%oror%|&&|&|^|+|-|*|/
MAYBE_UNUSED static inline bool match257(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("/"))))
        return false;
    return true;
}
// pattern: > const [*&]
MAYBE_UNUSED static inline bool match258(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("*&", tok->str()[0]))
        return false;
    return true;
}
// pattern: > %name% )
MAYBE_UNUSED static inline bool match259(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: if|for|while (
MAYBE_UNUSED static inline bool match260(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %name%|] (
MAYBE_UNUSED static inline bool match261(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: &|&&
MAYBE_UNUSED static inline bool match262(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: ( [*&]
MAYBE_UNUSED static inline bool match263(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("*&", tok->str()[0]))
        return false;
    return true;
}
// pattern: ) (|[
MAYBE_UNUSED static inline bool match264(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: !!)
MAYBE_UNUSED static inline bool match265(const Token* tok) {
    if (tok && tok->str() == MatchCompiler::makeConstString(")"))
        return false;
    return true;
}
// pattern: ( * %name% [
MAYBE_UNUSED static inline bool match266(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] ) [;,]
MAYBE_UNUSED static inline bool match267(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";,", tok->str()[0]))
        return false;
    return true;
}
// pattern: ( *|&| %name% ) ;
MAYBE_UNUSED static inline bool match268(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: ;|(|[|{
MAYBE_UNUSED static inline bool match269(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: %name%|*
MAYBE_UNUSED static inline bool match270(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: ] (
MAYBE_UNUSED static inline bool match271(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) . %name%
MAYBE_UNUSED static inline bool match272(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: (|=|{|:
MAYBE_UNUSED static inline bool match273(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: )| [
MAYBE_UNUSED static inline bool match274(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: = %num%
MAYBE_UNUSED static inline bool match275(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: [(,]
MAYBE_UNUSED static inline bool match276(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    return true;
}
// pattern: ,|)|%cop%
MAYBE_UNUSED static inline bool match277(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || tok->isConstOp()))
        return false;
    return true;
}
// pattern: !!:: %type%
MAYBE_UNUSED static inline bool match278(const Token* tok) {
    if (tok && tok->str() == MatchCompiler::makeConstString("::"))
        return false;
    tok = tok ? tok->next() : nullptr;
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: %name% = { . %name% =|{
MAYBE_UNUSED static inline bool match279(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
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
// pattern: {|[|(
MAYBE_UNUSED static inline bool match280(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: [,{] . %name% =|{
MAYBE_UNUSED static inline bool match281(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",{", tok->str()[0]))
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
// pattern: )| . %name% !!(
MAYBE_UNUSED static inline bool match282(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
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
// pattern: %name%|]
MAYBE_UNUSED static inline bool match283(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    return true;
}
// pattern: class|struct|enum %type% [:{]
MAYBE_UNUSED static inline bool match284(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(":{", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name%|>|>> {|(
MAYBE_UNUSED static inline bool match285(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: }|) ,|{
MAYBE_UNUSED static inline bool match286(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: [,:] %name% [({]
MAYBE_UNUSED static inline bool match287(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",:", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("({", tok->str()[0]))
        return false;
    return true;
}
// pattern: ::|.
MAYBE_UNUSED static inline bool match288(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    return true;
}
// pattern: ( * this ) .
MAYBE_UNUSED static inline bool match289(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("this")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: %name% :: %name% ::
MAYBE_UNUSED static inline bool match290(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: !!this .
MAYBE_UNUSED static inline bool match291(const Token* tok) {
    if (tok && tok->str() == MatchCompiler::makeConstString("this"))
        return false;
    tok = tok ? tok->next() : nullptr;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: template <
MAYBE_UNUSED static inline bool match292(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: %name%|::
MAYBE_UNUSED static inline bool match293(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: {|}
MAYBE_UNUSED static inline bool match294(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: union|struct|enum|namespace {
MAYBE_UNUSED static inline bool match295(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || (tok->str() == MatchCompiler::makeConstString("namespace"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %name%|>|>>|(
MAYBE_UNUSED static inline bool match296(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: } ,|{|)|...
MAYBE_UNUSED static inline bool match297(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("..."))))
        return false;
    return true;
}
// pattern: %name%|.
MAYBE_UNUSED static inline bool match298(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    return true;
}
// pattern: ) %type%
MAYBE_UNUSED static inline bool match299(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: )|}|...
MAYBE_UNUSED static inline bool match300(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("..."))))
        return false;
    return true;
}
// pattern: sizeof (
MAYBE_UNUSED static inline bool match301(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: const new
MAYBE_UNUSED static inline bool match302(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    return true;
}
// pattern: [(;{}] const| auto &|&&| [
MAYBE_UNUSED static inline bool match303(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(;{}", tok->str()[0]))
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
template<class T> MAYBE_UNUSED static inline T * findmatch304(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: for (
MAYBE_UNUSED static inline bool match305(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ] :
MAYBE_UNUSED static inline bool match306(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: %name% [,]]
MAYBE_UNUSED static inline bool match307(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",]", tok->str()[0]))
        return false;
    return true;
}
// pattern: decltype (
template<class T> MAYBE_UNUSED static inline T * findmatch308(T * start_tok, const Token * end) {
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
// pattern: %type% [;[=,)]
MAYBE_UNUSED static inline bool match309(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";[=,)", tok->str()[0]))
        return false;
    return true;
}
// pattern: %type% [:({]
MAYBE_UNUSED static inline bool match310(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(":({", tok->str()[0]))
        return false;
    return true;
}
// pattern: %type% ( !!)
MAYBE_UNUSED static inline bool match311(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString(")"))
        return false;
    return true;
}
// pattern: struct|union|class %type%
MAYBE_UNUSED static inline bool match312(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || (tok->str() == MatchCompiler::makeConstString("class"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: [&*]
MAYBE_UNUSED static inline bool match313(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("&*", tok->str()[0]))
        return false;
    return true;
}
// pattern: %type% {
MAYBE_UNUSED static inline bool match314(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } ;
MAYBE_UNUSED static inline bool match315(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: do|try|else
MAYBE_UNUSED static inline bool match316(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do")) || (tok->str() == MatchCompiler::makeConstString("try")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("else"))))
        return false;
    return true;
}
// pattern: struct|class|:
MAYBE_UNUSED static inline bool match317(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: %name% [=[({,]
MAYBE_UNUSED static inline bool match318(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("=[({,", tok->str()[0]))
        return false;
    return true;
}
// pattern: [([]
MAYBE_UNUSED static inline bool match319(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("([", tok->str()[0]))
        return false;
    return true;
}
// pattern: , %name% [=[({,;]
MAYBE_UNUSED static inline bool match320(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("=[({,;", tok->str()[0]))
        return false;
    return true;
}
// pattern: struct|enum|union
MAYBE_UNUSED static inline bool match321(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    return true;
}
// pattern: )|]|%name%
MAYBE_UNUSED static inline bool match322(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || tok->isName()))
        return false;
    return true;
}
// pattern: :: template
MAYBE_UNUSED static inline bool match323(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    return true;
}
// pattern: %name% [,)[]
MAYBE_UNUSED static inline bool match324(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)[", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name%|*|&|,|(
MAYBE_UNUSED static inline bool match325(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: [(,] %type% %name%|*|&
MAYBE_UNUSED static inline bool match326(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: %name%|*|&|,|[|]|%num%
MAYBE_UNUSED static inline bool match327(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || tok->isNumber()))
        return false;
    return true;
}
// pattern: [;{}] %type% %name%|*
MAYBE_UNUSED static inline bool match328(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: {|,
MAYBE_UNUSED static inline bool match329(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: ,|=|}
MAYBE_UNUSED static inline bool match330(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: {|, .
MAYBE_UNUSED static inline bool match331(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: : ;
MAYBE_UNUSED static inline bool match332(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: ::|. %name%
MAYBE_UNUSED static inline bool match333(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: )|]|>|%name%
MAYBE_UNUSED static inline bool match334(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || tok->isName()))
        return false;
    return true;
}
// pattern: class %type%
MAYBE_UNUSED static inline bool match335(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("class")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: %name% ::|<
MAYBE_UNUSED static inline bool match336(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: ~| %name%
MAYBE_UNUSED static inline bool match337(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: ~| %name% (
MAYBE_UNUSED static inline bool match338(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: [:,] ::| %name%
MAYBE_UNUSED static inline bool match339(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(":,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: [({<]
MAYBE_UNUSED static inline bool match340(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("({<", tok->str()[0]))
        return false;
    return true;
}
// pattern: using namespace %name% ::|;
MAYBE_UNUSED static inline bool match341(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: namespace %name% {
MAYBE_UNUSED static inline bool match342(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %name% :: ~| %name%
MAYBE_UNUSED static inline bool match343(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %name% <
MAYBE_UNUSED static inline bool match344(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: > :: ~| %name%
MAYBE_UNUSED static inline bool match345(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: .|namespace|class|struct|&|&&|*|> %name%
MAYBE_UNUSED static inline bool match346(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("namespace")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %type%| %name% ( %type%|)
MAYBE_UNUSED static inline bool match347(const Token* tok) {
    if (tok && ((tok->isName() && tok->varId() == 0U)))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: }|; %name%
MAYBE_UNUSED static inline bool match348(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: :: ~| %name%
MAYBE_UNUSED static inline bool match349(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: namespace|class|struct %name% {|:|::|<
MAYBE_UNUSED static inline bool match350(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("namespace")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: :|::|,|%name%
MAYBE_UNUSED static inline bool match351(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || tok->isName()))
        return false;
    return true;
}
// pattern: %name% ,|{
MAYBE_UNUSED static inline bool match352(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: union
MAYBE_UNUSED static inline bool match353(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")))
        return false;
    return true;
}
// pattern: ( %name%|)
MAYBE_UNUSED static inline bool match354(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: ) :
MAYBE_UNUSED static inline bool match355(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: ) %name% (
MAYBE_UNUSED static inline bool match356(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) : ::| %name%
MAYBE_UNUSED static inline bool match357(const Token* tok) {
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
    return true;
}
// pattern: [)}] [,:]
MAYBE_UNUSED static inline bool match358(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(")}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",:", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name% (|{|<
MAYBE_UNUSED static inline bool match359(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: )|} {
MAYBE_UNUSED static inline bool match360(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %name%|> %name% [:<]
MAYBE_UNUSED static inline bool match361(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(":<", tok->str()[0]))
        return false;
    return true;
}
// pattern: }|]|)
MAYBE_UNUSED static inline bool match362(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: %oror%|&&|;
MAYBE_UNUSED static inline bool match363(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: && [,>]
MAYBE_UNUSED static inline bool match364(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",>", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name%|%num%|%str%|%cop%|)|]
MAYBE_UNUSED static inline bool match365(const Token* tok) {
    if (!tok || !(tok->isName() || tok->isNumber() || (tok->tokType() == Token::eString) || tok->isConstOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    return true;
}
// pattern: %name%|%num%|%str%|%cop%|(|[
MAYBE_UNUSED static inline bool match366(const Token* tok) {
    if (!tok || !(tok->isName() || tok->isNumber() || (tok->tokType() == Token::eString) || tok->isConstOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: > %comp%|;|.|=|{|(|::
MAYBE_UNUSED static inline bool match367(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isComparisonOp() || (tok->str() == MatchCompiler::makeConstString(";")) || (tok->str() == MatchCompiler::makeConstString(".")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: > %var% ;
MAYBE_UNUSED static inline bool match368(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: ;|}|{
MAYBE_UNUSED static inline bool match369(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: %name%|)
MAYBE_UNUSED static inline bool match370(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: %name%|%cop%|%assign%|::|,|(|)|{|}|;|[|]|:|.|=|?|...
MAYBE_UNUSED static inline bool match371(const Token* tok) {
    if (!tok || !(tok->isName() || tok->isConstOp() || tok->isAssignmentOp() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString(".")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?")) || ((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("..."))))
        return false;
    return true;
}
// pattern: && %name% =
MAYBE_UNUSED static inline bool match372(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: > %name%
MAYBE_UNUSED static inline bool match373(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %op% %name% <
MAYBE_UNUSED static inline bool match374(const Token* tok) {
    if (!tok || !tok->isOp())
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: const_cast|dynamic_cast|reinterpret_cast|static_cast
MAYBE_UNUSED static inline bool match375(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("const_cast")) || (tok->str() == MatchCompiler::makeConstString("dynamic_cast")) || (tok->str() == MatchCompiler::makeConstString("reinterpret_cast")) || (tok->str() == MatchCompiler::makeConstString("static_cast"))))
        return false;
    return true;
}
// pattern: sizeof !!(
MAYBE_UNUSED static inline bool match376(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    return true;
}
// pattern: %name%|*|~|!|&
MAYBE_UNUSED static inline bool match377(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: * *
MAYBE_UNUSED static inline bool match378(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: %name%|%num%|%str%|[|(|.|::|++|--|!|~
MAYBE_UNUSED static inline bool match379(const Token* tok) {
    if (!tok || !(tok->isName() || tok->isNumber() || (tok->tokType() == Token::eString) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~"))))
        return false;
    return true;
}
// pattern: %type% * %op%|?|:|const|;|,
MAYBE_UNUSED static inline bool match380(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: if|for|while %name% (
MAYBE_UNUSED static inline bool match381(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: for each
MAYBE_UNUSED static inline bool match382(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("each")))
        return false;
    return true;
}
// pattern: in
template<class T> MAYBE_UNUSED static inline T * findmatch383(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("in")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: if (
MAYBE_UNUSED static inline bool match384(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) {|else
MAYBE_UNUSED static inline bool match385(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("else"))))
        return false;
    return true;
}
// pattern: > struct {
MAYBE_UNUSED static inline bool match386(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: 0 [
MAYBE_UNUSED static inline bool match387(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: %type% <
MAYBE_UNUSED static inline bool match388(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: >|>> %name%|::|(
MAYBE_UNUSED static inline bool match389(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: class %type% %type% [:{]
MAYBE_UNUSED static inline bool match390(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("class")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(":{", tok->str()[0]))
        return false;
    return true;
}
// pattern: > class|struct %name% {
MAYBE_UNUSED static inline bool match391(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %name% %name%|::|*|&|<
MAYBE_UNUSED static inline bool match392(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: ) const| ;
MAYBE_UNUSED static inline bool match393(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: %name%|,
MAYBE_UNUSED static inline bool match394(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: template < %name%
MAYBE_UNUSED static inline bool match395(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: > class|struct %name% [;:{]
MAYBE_UNUSED static inline bool match396(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";:{", tok->str()[0]))
        return false;
    return true;
}
// pattern: > %type% %name% (
MAYBE_UNUSED static inline bool match397(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %name%|>|) .|:: template %name%
MAYBE_UNUSED static inline bool match398(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: operator %op%|(
MAYBE_UNUSED static inline bool match399(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: [;{}] %type% %type% [;,=]
MAYBE_UNUSED static inline bool match400(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";,=", tok->str()[0]))
        return false;
    return true;
}
// pattern: >>|>>=
MAYBE_UNUSED static inline bool match401(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>")) || (tok->str() == MatchCompiler::makeConstString(">>="))))
        return false;
    return true;
}
// pattern: class|struct|union|=|:|public|protected|private %name% <
MAYBE_UNUSED static inline bool match402(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("protected")) || (tok->str() == MatchCompiler::makeConstString("private"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: >>
MAYBE_UNUSED static inline bool match403(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>")))
        return false;
    return true;
}
// pattern: >> ;|{|%type%
MAYBE_UNUSED static inline bool match404(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->isName() && tok->varId() == 0U)))
        return false;
    return true;
}
// pattern: ) %type% {
MAYBE_UNUSED static inline bool match405(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: override|final
MAYBE_UNUSED static inline bool match406(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("override")) || (tok->str() == MatchCompiler::makeConstString("final"))))
        return false;
    return true;
}
// pattern: %name% *|&|::|<| %name%
MAYBE_UNUSED static inline bool match407(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: requires|namespace|class|struct|union|private:|protected:|public:
MAYBE_UNUSED static inline bool match408(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("requires")) || (tok->str() == MatchCompiler::makeConstString("namespace")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || (tok->str() == MatchCompiler::makeConstString("private:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("public:"))))
        return false;
    return true;
}
// pattern: noexcept|throw
MAYBE_UNUSED static inline bool match409(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("noexcept")) || (tok->str() == MatchCompiler::makeConstString("throw"))))
        return false;
    return true;
}
// pattern: namespace|class|struct|union
MAYBE_UNUSED static inline bool match410(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("namespace")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    return true;
}
// pattern: [;{}()]
MAYBE_UNUSED static inline bool match411(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}()", tok->str()[0]))
        return false;
    return true;
}
// pattern: %type% :: %type%
MAYBE_UNUSED static inline bool match412(const Token* tok) {
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
// pattern: %type% :: %type% ::
MAYBE_UNUSED static inline bool match413(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: %type% :: %type% (
MAYBE_UNUSED static inline bool match414(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: _Pragma (
MAYBE_UNUSED static inline bool match415(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("_Pragma")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: class|struct %name% %name% final| {|:
MAYBE_UNUSED static inline bool match416(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("final"))))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: ) try
MAYBE_UNUSED static inline bool match417(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("try")))
        return false;
    return true;
}
// pattern: ) using
MAYBE_UNUSED static inline bool match418(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    return true;
}
// pattern: (|[|{
MAYBE_UNUSED static inline bool match419(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: namespace %name%| {
MAYBE_UNUSED static inline bool match420(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ; ;
MAYBE_UNUSED static inline bool match421(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: ; { ; }
MAYBE_UNUSED static inline bool match422(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: for|switch|BOOST_FOREACH
MAYBE_UNUSED static inline bool match423(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("switch")) || (tok->str() == MatchCompiler::makeConstString("BOOST_FOREACH"))))
        return false;
    return true;
}
// pattern: operator \"\"
MAYBE_UNUSED static inline bool match424(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("\"\"")))
        return false;
    return true;
}
// pattern: )|}|,
MAYBE_UNUSED static inline bool match425(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: %name% :
MAYBE_UNUSED static inline bool match426(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: try {
MAYBE_UNUSED static inline bool match427(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("try")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } catch (
MAYBE_UNUSED static inline bool match428(const Token* tok) {
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
// pattern: ;|)|}
MAYBE_UNUSED static inline bool match429(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: %name% ( %name% [,)]
MAYBE_UNUSED static inline bool match430(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name% [,)]
MAYBE_UNUSED static inline bool match431(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: ; {
MAYBE_UNUSED static inline bool match432(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: (|)
MAYBE_UNUSED static inline bool match433(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: & %name% [ 0 ] !![
MAYBE_UNUSED static inline bool match434(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("["))
        return false;
    return true;
}
// pattern: [,(=]
MAYBE_UNUSED static inline bool match435(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",(=", tok->str()[0]))
        return false;
    return true;
}
// pattern: ( %type% %type%| *| *| ( * ) (
MAYBE_UNUSED static inline bool match436(const Token* tok) {
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
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: static_cast < %type% %type%| *| *| ( * ) (
MAYBE_UNUSED static inline bool match437(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("static_cast")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
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
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) )|>
MAYBE_UNUSED static inline bool match438(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: {|}|;|,|(|public:|protected:|private:
MAYBE_UNUSED static inline bool match439(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("private:"))))
        return false;
    return true;
}
// pattern: delete|else|return|throw|typedef
MAYBE_UNUSED static inline bool match440(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("delete")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("else")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("throw")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef"))))
        return false;
    return true;
}
// pattern: %type%|:: %type%|::
MAYBE_UNUSED static inline bool match441(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->isName() && tok->varId() == 0U) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: (|:: %type%
MAYBE_UNUSED static inline bool match442(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: (|:: * *| %name%
MAYBE_UNUSED static inline bool match443(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %name% [ ] ) (
MAYBE_UNUSED static inline bool match444(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) throw (
MAYBE_UNUSED static inline bool match445(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("throw")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) const|volatile| const|volatile| ;|,|)|=|[|{
MAYBE_UNUSED static inline bool match446(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: ) )
MAYBE_UNUSED static inline bool match447(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: %name%|*|&|[|(|)|::|,|<
MAYBE_UNUSED static inline bool match448(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: %type%|*|&|> %name% [,)[]
MAYBE_UNUSED static inline bool match449(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)[", tok->str()[0]))
        return false;
    return true;
}
// pattern: ( %type% ::
MAYBE_UNUSED static inline bool match450(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: {|;
MAYBE_UNUSED static inline bool match451(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: class|struct|namespace|union
MAYBE_UNUSED static inline bool match452(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("namespace")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    return true;
}
// pattern: decltype|noexcept (
MAYBE_UNUSED static inline bool match453(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("decltype")) || (tok->str() == MatchCompiler::makeConstString("noexcept"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %name%|> {
MAYBE_UNUSED static inline bool match454(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: else|try|do|const|constexpr|override|volatile|noexcept
MAYBE_UNUSED static inline bool match455(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("else")) || (tok->str() == MatchCompiler::makeConstString("try")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("constexpr")) || (tok->str() == MatchCompiler::makeConstString("override")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || (tok->str() == MatchCompiler::makeConstString("noexcept"))))
        return false;
    return true;
}
// pattern: ]
MAYBE_UNUSED static inline bool match456(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    return true;
}
// pattern: ) !!{
MAYBE_UNUSED static inline bool match457(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("{"))
        return false;
    return true;
}
// pattern: [(,] [
MAYBE_UNUSED static inline bool match458(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: {|}|;|)|public:|protected:|private:
MAYBE_UNUSED static inline bool match459(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || (tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("private:"))))
        return false;
    return true;
}
// pattern: ::|extern| %type%
MAYBE_UNUSED static inline bool match460(const Token* tok) {
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: else|return|public:|protected:|private:
MAYBE_UNUSED static inline bool match461(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("else")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("private:"))))
        return false;
    return true;
}
// pattern: namespace|delete
MAYBE_UNUSED static inline bool match462(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("namespace")) || (tok->str() == MatchCompiler::makeConstString("delete"))))
        return false;
    return true;
}
// pattern: ::|extern
MAYBE_UNUSED static inline bool match463(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern"))))
        return false;
    return true;
}
// pattern: const|static|constexpr
MAYBE_UNUSED static inline bool match464(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || (tok->str() == MatchCompiler::makeConstString("constexpr"))))
        return false;
    return true;
}
// pattern: %type% const|static
MAYBE_UNUSED static inline bool match465(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static"))))
        return false;
    return true;
}
// pattern: const|constexpr
MAYBE_UNUSED static inline bool match466(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("constexpr"))))
        return false;
    return true;
}
// pattern: static|constexpr
MAYBE_UNUSED static inline bool match467(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || (tok->str() == MatchCompiler::makeConstString("constexpr"))))
        return false;
    return true;
}
// pattern: & %name% ,
MAYBE_UNUSED static inline bool match468(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: %type% *|&| %name% , %type% *|&| %name%
MAYBE_UNUSED static inline bool match469(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: public:|private:|protected:|using
MAYBE_UNUSED static inline bool match470(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("private:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("using"))))
        return false;
    return true;
}
// pattern: %type% %type%
MAYBE_UNUSED static inline bool match471(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: ) =
MAYBE_UNUSED static inline bool match472(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: %name% ,|=
MAYBE_UNUSED static inline bool match473(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: {|(|[
MAYBE_UNUSED static inline bool match474(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: ] ,|=|[
MAYBE_UNUSED static inline bool match475(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: =|,
MAYBE_UNUSED static inline bool match476(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: %name% {
MAYBE_UNUSED static inline bool match477(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: const|noexcept|override|final
MAYBE_UNUSED static inline bool match478(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("noexcept")) || (tok->str() == MatchCompiler::makeConstString("override")) || (tok->str() == MatchCompiler::makeConstString("final"))))
        return false;
    return true;
}
// pattern: ,
MAYBE_UNUSED static inline bool match479(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: %name%|*|& %name%|*|&
MAYBE_UNUSED static inline bool match480(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: %type%|struct|::
MAYBE_UNUSED static inline bool match481(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: private:|protected:|public:|operator|template
MAYBE_UNUSED static inline bool match482(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("private:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("operator")) || (tok->str() == MatchCompiler::makeConstString("template"))))
        return false;
    return true;
}
// pattern: ;|{|}|(|,|private:|protected:|public:
MAYBE_UNUSED static inline bool match483(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->str() == MatchCompiler::makeConstString("private:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("public:"))))
        return false;
    return true;
}
// pattern: %name% = %name% = %num%|%name% ;
MAYBE_UNUSED static inline bool match484(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isNumber() || tok->isName()))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: %type%|* %name% [;,=]
MAYBE_UNUSED static inline bool match485(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";,=", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name%|%num%|%char%|%str%|)|]|> %name% %name%|%num%|%char%|%op%|%str%|(
MAYBE_UNUSED static inline bool match486(const Token* tok) {
    if (!tok || !(tok->isName() || tok->isNumber() || (tok->tokType() == Token::eChar) || (tok->tokType() == Token::eString) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || tok->isNumber() || (tok->tokType() == Token::eChar) || tok->isOp() || (tok->tokType() == Token::eString) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: %assign%|%or%|%oror%|&&|*|/|%|^
MAYBE_UNUSED static inline bool match487(const Token* tok) {
    if (!tok || !(tok->isAssignmentOp() || (tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("/")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("%")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^"))))
        return false;
    return true;
}
// pattern: %num%|%char%|) %name% *
MAYBE_UNUSED static inline bool match488(const Token* tok) {
    if (!tok || !(tok->isNumber() || (tok->tokType() == Token::eChar) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: [;}]
MAYBE_UNUSED static inline bool match489(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";}", tok->str()[0]))
        return false;
    return true;
}
// pattern: not|compl
MAYBE_UNUSED static inline bool match490(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("not")) || (tok->str() == MatchCompiler::makeConstString("compl"))))
        return false;
    return true;
}
// pattern: %assign%
MAYBE_UNUSED static inline bool match491(const Token* tok) {
    if (!tok || !tok->isAssignmentOp())
        return false;
    return true;
}
// pattern: %num%
MAYBE_UNUSED static inline bool match492(const Token* tok) {
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: .|->
MAYBE_UNUSED static inline bool match493(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("->"))))
        return false;
    return true;
}
// pattern: %name%|(
MAYBE_UNUSED static inline bool match494(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: %type% *|&| %name% (|{
MAYBE_UNUSED static inline bool match495(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: namespace
MAYBE_UNUSED static inline bool match496(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    return true;
}
// pattern: (|{
MAYBE_UNUSED static inline bool match497(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: %type% *| %name% ( %type% (
MAYBE_UNUSED static inline bool match498(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: class|struct|union| %type% *| %name% ( &| %any% ) ,
MAYBE_UNUSED static inline bool match499(const Token* tok) {
    if (tok && ((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: %type% (|{
MAYBE_UNUSED static inline bool match500(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: ;|}
MAYBE_UNUSED static inline bool match501(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: }|;
MAYBE_UNUSED static inline bool match502(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: if|switch|for (
MAYBE_UNUSED static inline bool match503(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("switch")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: [;)]
MAYBE_UNUSED static inline bool match504(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";)", tok->str()[0]))
        return false;
    return true;
}
// pattern: } else {
MAYBE_UNUSED static inline bool match505(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("else")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } (
MAYBE_UNUSED static inline bool match506(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %name%|>|] {
MAYBE_UNUSED static inline bool match507(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ( {
MAYBE_UNUSED static inline bool match508(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ) %num%
MAYBE_UNUSED static inline bool match509(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: %op% (
MAYBE_UNUSED static inline bool match510(const Token* tok) {
    if (!tok || !tok->isOp())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) %op%
MAYBE_UNUSED static inline bool match511(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isOp())
        return false;
    return true;
}
// pattern: [;{}=(] new (
MAYBE_UNUSED static inline bool match512(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}=(", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) [;,{}[]
MAYBE_UNUSED static inline bool match513(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";,{}[", tok->str()[0]))
        return false;
    return true;
}
// pattern: ! ( %name% )
MAYBE_UNUSED static inline bool match514(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")))
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
    return true;
}
// pattern: [(,;{}] ( %name% ) .
MAYBE_UNUSED static inline bool match515(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,;{}", tok->str()[0]))
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
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: [(,;{}] ( %name% (
MAYBE_UNUSED static inline bool match516(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,;{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: [,;{}] ( delete [| ]| %name% ) ;
MAYBE_UNUSED static inline bool match517(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",;{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("delete")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: operator delete
MAYBE_UNUSED static inline bool match518(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("delete")))
        return false;
    return true;
}
// pattern: delete|; (
MAYBE_UNUSED static inline bool match519(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("delete")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: [(!*;{}] ( %name% )
MAYBE_UNUSED static inline bool match520(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(!*;{}", tok->str()[0]))
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
    return true;
}
// pattern: [+-/=]
MAYBE_UNUSED static inline bool match521(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("+-/=", tok->str()[0]))
        return false;
    return true;
}
// pattern: [;{}[(,!*] ( %name% .
MAYBE_UNUSED static inline bool match522(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}[(,!*", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: . %name%
MAYBE_UNUSED static inline bool match523(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: [{([,] ( !!{
MAYBE_UNUSED static inline bool match524(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{([,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("{"))
        return false;
    return true;
}
// pattern: ) [;,])] !!{
MAYBE_UNUSED static inline bool match525(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";,])", tok->str()[0]))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("{"))
        return false;
    return true;
}
// pattern: operator ,
MAYBE_UNUSED static inline bool match526(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: ,
template<class T> MAYBE_UNUSED static inline T * findmatch527(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: , (
MAYBE_UNUSED static inline bool match528(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ( %bool%|%num% ) %cop%|;|,|)
MAYBE_UNUSED static inline bool match529(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isBoolean() || tok->isNumber()))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isConstOp() || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: %name%|)|]
MAYBE_UNUSED static inline bool match530(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    return true;
}
// pattern: *|& ( %name% )
MAYBE_UNUSED static inline bool match531(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
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
    return true;
}
// pattern: %type%|static|const|extern
MAYBE_UNUSED static inline bool match532(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern"))))
        return false;
    return true;
}
// pattern: ) ; }
MAYBE_UNUSED static inline bool match533(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: const_cast|dynamic_cast|reinterpret_cast|static_cast <
MAYBE_UNUSED static inline bool match534(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("const_cast")) || (tok->str() == MatchCompiler::makeConstString("dynamic_cast")) || (tok->str() == MatchCompiler::makeConstString("reinterpret_cast")) || (tok->str() == MatchCompiler::makeConstString("static_cast"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: %name% < %name% > (
MAYBE_UNUSED static inline bool match535(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: [()]
MAYBE_UNUSED static inline bool match536(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("()", tok->str()[0]))
        return false;
    return true;
}
// pattern: using namespace %name% ;
MAYBE_UNUSED static inline bool match537(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: template < class|typename %name% [,>]
MAYBE_UNUSED static inline bool match538(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || (tok->str() == MatchCompiler::makeConstString("typename"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",>", tok->str()[0]))
        return false;
    return true;
}
// pattern: class|namespace %name% :|::|{
MAYBE_UNUSED static inline bool match539(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || (tok->str() == MatchCompiler::makeConstString("namespace"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: [ [
MAYBE_UNUSED static inline bool match540(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: %name% %num%
MAYBE_UNUSED static inline bool match541(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: %op%|(
MAYBE_UNUSED static inline bool match542(const Token* tok) {
    if (!tok || !(tok->isOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: )|; %name% } !!)
MAYBE_UNUSED static inline bool match543(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString(")"))
        return false;
    return true;
}
// pattern: if
MAYBE_UNUSED static inline bool match544(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")))
        return false;
    return true;
}
// pattern: ;|)
MAYBE_UNUSED static inline bool match545(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: [[({]
MAYBE_UNUSED static inline bool match546(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("[({", tok->str()[0]))
        return false;
    return true;
}
// pattern: [,(] . %name% =|{
MAYBE_UNUSED static inline bool match547(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",(", tok->str()[0]))
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
// pattern: if|switch|for|while|return
MAYBE_UNUSED static inline bool match548(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("switch")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return"))))
        return false;
    return true;
}
// pattern: ) [;{]
MAYBE_UNUSED static inline bool match549(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";{", tok->str()[0]))
        return false;
    return true;
}
// pattern: public|private|protected %name% :
MAYBE_UNUSED static inline bool match550(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("private")) || (tok->str() == MatchCompiler::makeConstString("protected"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: %str% %name% (
MAYBE_UNUSED static inline bool match551(const Token* tok) {
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) %str%
MAYBE_UNUSED static inline bool match552(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    return true;
}
// pattern: %str% %name% %str%
MAYBE_UNUSED static inline bool match553(const Token* tok) {
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    return true;
}
// pattern: [(,] %name% (
MAYBE_UNUSED static inline bool match554(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) %name% %name%|,|)
MAYBE_UNUSED static inline bool match555(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: ) %name% (|.
MAYBE_UNUSED static inline bool match556(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    return true;
}
// pattern: %name%|::|>
MAYBE_UNUSED static inline bool match557(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: ;|goto|return|typedef
MAYBE_UNUSED static inline bool match558(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("goto")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef"))))
        return false;
    return true;
}
// pattern: %assign% [
MAYBE_UNUSED static inline bool match559(const Token* tok) {
    if (!tok || !tok->isAssignmentOp())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: [({<] %assign%
MAYBE_UNUSED static inline bool match560(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("({<", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isAssignmentOp())
        return false;
    return true;
}
// pattern: %assign% >
MAYBE_UNUSED static inline bool match561(const Token* tok) {
    if (!tok || !tok->isAssignmentOp())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    return true;
}
// pattern: [`\\@]
MAYBE_UNUSED static inline bool match562(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("`\\@", tok->str()[0]))
        return false;
    return true;
}
// pattern: throw|return )
MAYBE_UNUSED static inline bool match563(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("throw")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: %name% return
MAYBE_UNUSED static inline bool match564(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")))
        return false;
    return true;
}
// pattern: %name% throw
MAYBE_UNUSED static inline bool match565(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("throw")))
        return false;
    return true;
}
// pattern: !!) %num%|%str%|%char% %assign%|++|--
MAYBE_UNUSED static inline bool match566(const Token* tok) {
    if (tok && tok->str() == MatchCompiler::makeConstString(")"))
        return false;
    tok = tok ? tok->next() : nullptr;
    if (!tok || !(tok->isNumber() || (tok->tokType() == Token::eString) || (tok->tokType() == Token::eChar)))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isAssignmentOp() || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--"))))
        return false;
    return true;
}
// pattern: %name% : %num% =
MAYBE_UNUSED static inline bool match567(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: if|while|for (
MAYBE_UNUSED static inline bool match568(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) return
MAYBE_UNUSED static inline bool match569(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")))
        return false;
    return true;
}
// pattern: if|while|for|switch
MAYBE_UNUSED static inline bool match570(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("switch"))))
        return false;
    return true;
}
// pattern: %name%|:|;|{|}|)
MAYBE_UNUSED static inline bool match571(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: [,(]
MAYBE_UNUSED static inline bool match572(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",(", tok->str()[0]))
        return false;
    return true;
}
// pattern: operator \"\" if
MAYBE_UNUSED static inline bool match573(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("\"\"")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")))
        return false;
    return true;
}
// pattern: ( !!)
MAYBE_UNUSED static inline bool match574(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString(")"))
        return false;
    return true;
}
// pattern: do {
MAYBE_UNUSED static inline bool match575(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } while (
MAYBE_UNUSED static inline bool match576(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %name% %name%
MAYBE_UNUSED static inline bool match577(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %op%|%num%|%str%|%char%
MAYBE_UNUSED static inline bool match578(const Token* tok) {
    if (!tok || !(tok->isOp() || tok->isNumber() || (tok->tokType() == Token::eString) || (tok->tokType() == Token::eChar)))
        return false;
    return true;
}
// pattern: extern \"C\"
MAYBE_UNUSED static inline bool match579(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("\"C\"")))
        return false;
    return true;
}
// pattern: > typedef
MAYBE_UNUSED static inline bool match580(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef")))
        return false;
    return true;
}
// pattern: struct|class|enum %name%| {
MAYBE_UNUSED static inline bool match581(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    tok = tok->next();
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } %op%
MAYBE_UNUSED static inline bool match582(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isOp())
        return false;
    return true;
}
// pattern: : %num%| {
MAYBE_UNUSED static inline bool match583(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (tok && (tok->isNumber()))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: operator %str%
MAYBE_UNUSED static inline bool match584(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    return true;
}
// pattern: switch (
MAYBE_UNUSED static inline bool match585(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("switch")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: > %cop%
MAYBE_UNUSED static inline bool match586(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isConstOp())
        return false;
    return true;
}
// pattern: %or%|%oror%|==|!=|+|-|/|!|>=|<=|~|^|++|--|::|sizeof
MAYBE_UNUSED static inline bool match587(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("==")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("!=")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("/")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">=")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<=")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof"))))
        return false;
    return true;
}
// pattern: {|if|else|while|do|for|return|switch|break
MAYBE_UNUSED static inline bool match588(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("else")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("switch")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("break"))))
        return false;
    return true;
}
// pattern: throw|decltype|typeof
MAYBE_UNUSED static inline bool match589(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("throw")) || (tok->str() == MatchCompiler::makeConstString("decltype")) || (tok->str() == MatchCompiler::makeConstString("typeof"))))
        return false;
    return true;
}
// pattern: try|catch|namespace
MAYBE_UNUSED static inline bool match590(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("try")) || (tok->str() == MatchCompiler::makeConstString("catch")) || (tok->str() == MatchCompiler::makeConstString("namespace"))))
        return false;
    return true;
}
// pattern: %or%|%oror%|~|^|!|%comp%|+|-|/|%
MAYBE_UNUSED static inline bool match591(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")) || tok->isComparisonOp() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("/")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("%"))))
        return false;
    return true;
}
// pattern: )|]|}
MAYBE_UNUSED static inline bool match592(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: ( )
MAYBE_UNUSED static inline bool match593(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: operator
MAYBE_UNUSED static inline bool match594(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    return true;
}
// pattern: %num%|%bool%|%char%|%str% %num%|%bool%|%char%|%str%
MAYBE_UNUSED static inline bool match595(const Token* tok) {
    if (!tok || !(tok->isNumber() || tok->isBoolean() || (tok->tokType() == Token::eChar) || (tok->tokType() == Token::eString)))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isNumber() || tok->isBoolean() || (tok->tokType() == Token::eChar) || (tok->tokType() == Token::eString)))
        return false;
    return true;
}
// pattern: %str% %str%
MAYBE_UNUSED static inline bool match596(const Token* tok) {
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    return true;
}
// pattern: %num%|%bool%|%char%|%str% {|(
MAYBE_UNUSED static inline bool match597(const Token* tok) {
    if (!tok || !(tok->isNumber() || tok->isBoolean() || (tok->tokType() == Token::eChar) || (tok->tokType() == Token::eString)))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: extern
MAYBE_UNUSED static inline bool match598(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("extern")))
        return false;
    return true;
}
// pattern: requires
MAYBE_UNUSED static inline bool match599(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("requires")))
        return false;
    return true;
}
// pattern: ( ) %num%|%bool%|%char%|%str%
MAYBE_UNUSED static inline bool match600(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isNumber() || tok->isBoolean() || (tok->tokType() == Token::eChar) || (tok->tokType() == Token::eString)))
        return false;
    return true;
}
// pattern: %assign% typename|class %assign%
MAYBE_UNUSED static inline bool match601(const Token* tok) {
    if (!tok || !tok->isAssignmentOp())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("typename")) || (tok->str() == MatchCompiler::makeConstString("class"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isAssignmentOp())
        return false;
    return true;
}
// pattern: %assign% [;)}]
MAYBE_UNUSED static inline bool match602(const Token* tok) {
    if (!tok || !tok->isAssignmentOp())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";)}", tok->str()[0]))
        return false;
    return true;
}
// pattern: ; %assign%
MAYBE_UNUSED static inline bool match603(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isAssignmentOp())
        return false;
    return true;
}
// pattern: %assign% %name%
MAYBE_UNUSED static inline bool match604(const Token* tok) {
    if (!tok || !tok->isAssignmentOp())
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %cop%|=|,|[ %or%|%oror%|/|%
MAYBE_UNUSED static inline bool match605(const Token* tok) {
    if (!tok || !(tok->isConstOp() || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("/")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("%"))))
        return false;
    return true;
}
// pattern: [;([{] %comp%|%oror%|%or%|%|/
MAYBE_UNUSED static inline bool match606(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";([{", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isComparisonOp() || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || (tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("%")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("/"))))
        return false;
    return true;
}
// pattern: %cop%|= ]
MAYBE_UNUSED static inline bool match607(const Token* tok) {
    if (!tok || !(tok->isConstOp() || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    return true;
}
// pattern: %type%|[|,|%num% &|=|> ]
MAYBE_UNUSED static inline bool match608(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || tok->isNumber()))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    return true;
}
// pattern: [+-] [;,)]}]
MAYBE_UNUSED static inline bool match609(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("+-", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";,)]}", tok->str()[0]))
        return false;
    return true;
}
// pattern: [ = , &|%name%
MAYBE_UNUSED static inline bool match610(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || tok->isName()))
        return false;
    return true;
}
// pattern: (|[|{|<|%assign%|%or%|%oror%|==|!=|+|-|/|!|>=|<=|~|^|::|sizeof
MAYBE_UNUSED static inline bool match611(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || tok->isAssignmentOp() || (tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("==")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("!=")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("/")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">=")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<=")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof"))))
        return false;
    return true;
}
// pattern: )|]|>|%assign%|%or%|%oror%|==|!=|/|>=|<=|&&
MAYBE_UNUSED static inline bool match612(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || tok->isAssignmentOp() || (tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("==")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("!=")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("/")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">=")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<=")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&"))))
        return false;
    return true;
}
// pattern: {|, . %name% =|.|[|{
MAYBE_UNUSED static inline bool match613(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || (tok->str() == MatchCompiler::makeConstString(".")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: , . %name%
MAYBE_UNUSED static inline bool match614(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %name%|)|]|>|}
MAYBE_UNUSED static inline bool match615(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: %name%|*|~
MAYBE_UNUSED static inline bool match616(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~"))))
        return false;
    return true;
}
// pattern: [{,] . %name%
MAYBE_UNUSED static inline bool match617(const Token* tok) {
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
// pattern: [.=[{]
MAYBE_UNUSED static inline bool match618(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(".=[{", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name% %op% %name%
MAYBE_UNUSED static inline bool match619(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !tok->isOp())
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: [!|+-/%^~] )|]
MAYBE_UNUSED static inline bool match620(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("!|+-/%^~", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]"))))
        return false;
    return true;
}
// pattern: ==|!=|<=|>= %comp%
MAYBE_UNUSED static inline bool match621(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("==")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("!=")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<=")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">="))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isComparisonOp())
        return false;
    return true;
}
// pattern: ::
MAYBE_UNUSED static inline bool match622(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: new|delete|operator
MAYBE_UNUSED static inline bool match623(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("new")) || (tok->str() == MatchCompiler::makeConstString("delete")) || (tok->str() == MatchCompiler::makeConstString("operator"))))
        return false;
    return true;
}
// pattern: & %comp%|&&|%oror%|&|%or%
MAYBE_UNUSED static inline bool match624(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isComparisonOp() || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || (tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") )))
        return false;
    return true;
}
// pattern: ^ %op%
MAYBE_UNUSED static inline bool match625(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isOp())
        return false;
    return true;
}
// pattern: [>*+-!~]
MAYBE_UNUSED static inline bool match626(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(">*+-!~", tok->str()[0]))
        return false;
    return true;
}
// pattern: : [)]=]
MAYBE_UNUSED static inline bool match627(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(")]=", tok->str()[0]))
        return false;
    return true;
}
// pattern: typedef [,;:]
MAYBE_UNUSED static inline bool match628(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",;:", tok->str()[0]))
        return false;
    return true;
}
// pattern: !|~ %comp%
MAYBE_UNUSED static inline bool match629(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isComparisonOp())
        return false;
    return true;
}
// pattern: ] %name%
MAYBE_UNUSED static inline bool match630(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: delete [
MAYBE_UNUSED static inline bool match631(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("delete")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: , ,
MAYBE_UNUSED static inline bool match632(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: [,;] ,
MAYBE_UNUSED static inline bool match633(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",;", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: typedef|static|.
MAYBE_UNUSED static inline bool match634(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    return true;
}
// pattern: enum|struct|union
MAYBE_UNUSED static inline bool match635(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    return true;
}
// pattern: class|::
MAYBE_UNUSED static inline bool match636(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: ;|{|}|using|inline
MAYBE_UNUSED static inline bool match637(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString("using")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("inline"))))
        return false;
    return true;
}
// pattern: ::|%name%
MAYBE_UNUSED static inline bool match638(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || tok->isName()))
        return false;
    return true;
}
// pattern: %cop%
MAYBE_UNUSED static inline bool match639(const Token* tok) {
    if (!tok || !tok->isConstOp())
        return false;
    return true;
}
// pattern: %name%|;|}|)
MAYBE_UNUSED static inline bool match640(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: %name%|> (
MAYBE_UNUSED static inline bool match641(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: void|char|short|int|long|float|double|const|volatile|static|inline|struct|class|enum|union|template|sizeof|case|break|continue|typedef
MAYBE_UNUSED static inline bool match642(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("void")) || (tok->str() == MatchCompiler::makeConstString("char")) || (tok->str() == MatchCompiler::makeConstString("short")) || (tok->str() == MatchCompiler::makeConstString("int")) || (tok->str() == MatchCompiler::makeConstString("long")) || (tok->str() == MatchCompiler::makeConstString("float")) || (tok->str() == MatchCompiler::makeConstString("double")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("inline")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || (tok->str() == MatchCompiler::makeConstString("template")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("break")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("continue")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("typedef"))))
        return false;
    return true;
}
// pattern: operator %op%
MAYBE_UNUSED static inline bool match643(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isOp())
        return false;
    return true;
}
// pattern: : template
MAYBE_UNUSED static inline bool match644(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("template")))
        return false;
    return true;
}
// pattern: :|,|;|{|}|)|<|>|\"C++\"
MAYBE_UNUSED static inline bool match645(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || (tok->str() == MatchCompiler::makeConstString("\"C++\""))))
        return false;
    return true;
}
// pattern: >|>> ::|...| %name%
MAYBE_UNUSED static inline bool match646(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("..."))))
        tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: >|>> [ [ %name%
MAYBE_UNUSED static inline bool match647(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: > >|*
MAYBE_UNUSED static inline bool match648(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: [;{}] [ %name% %name% ] ;
MAYBE_UNUSED static inline bool match649(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: try {|:
MAYBE_UNUSED static inline bool match650(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("try")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: enum {|:
MAYBE_UNUSED static inline bool match651(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: using %name% =
MAYBE_UNUSED static inline bool match652(const Token* tok) {
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
// pattern: } (| %type%| )| [*,;[({=]
MAYBE_UNUSED static inline bool match653(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        tok = tok->next();
    if (tok && ((tok->isName() && tok->varId() == 0U)))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("*,;[({=", tok->str()[0]))
        return false;
    return true;
}
// pattern: struct|union {
MAYBE_UNUSED static inline bool match654(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } const| *|&| const| %type% ,|;|[|(|{|=
MAYBE_UNUSED static inline bool match655(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: class|struct :
MAYBE_UNUSED static inline bool match656(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: } const| *|&| const| %type% ,|;|[|(|{
MAYBE_UNUSED static inline bool match657(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: ( %type% )
MAYBE_UNUSED static inline bool match658(const Token* tok) {
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
// pattern: const|)
MAYBE_UNUSED static inline bool match659(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: class|struct|union|enum %type% :|{
MAYBE_UNUSED static inline bool match660(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: [{;]
MAYBE_UNUSED static inline bool match661(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{;", tok->str()[0]))
        return false;
    return true;
}
// pattern: const|static|volatile| *|&| const| (| %type% )| ,|;|[|=|(|{
MAYBE_UNUSED static inline bool match662(const Token* tok) {
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (tok && (((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: struct|class|union|enum
MAYBE_UNUSED static inline bool match663(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum"))))
        return false;
    return true;
}
// pattern: %any% (|{
MAYBE_UNUSED static inline bool match664(const Token* tok) {
    if (!tok || false)
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: { !!}
MAYBE_UNUSED static inline bool match665(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("}"))
        return false;
    return true;
}
// pattern: __cdecl|__stdcall|__fastcall|__thiscall|__clrcall|__syscall|__pascal|__fortran|__far|__near
MAYBE_UNUSED static inline bool match666(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("__cdecl")) || (tok->str() == MatchCompiler::makeConstString("__stdcall")) || (tok->str() == MatchCompiler::makeConstString("__fastcall")) || (tok->str() == MatchCompiler::makeConstString("__thiscall")) || (tok->str() == MatchCompiler::makeConstString("__clrcall")) || (tok->str() == MatchCompiler::makeConstString("__syscall")) || (tok->str() == MatchCompiler::makeConstString("__pascal")) || (tok->str() == MatchCompiler::makeConstString("__fortran")) || (tok->str() == MatchCompiler::makeConstString("__far")) || (tok->str() == MatchCompiler::makeConstString("__near"))))
        return false;
    return true;
}
// pattern: WINAPI|APIENTRY|CALLBACK
MAYBE_UNUSED static inline bool match667(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("WINAPI")) || (tok->str() == MatchCompiler::makeConstString("APIENTRY")) || (tok->str() == MatchCompiler::makeConstString("CALLBACK"))))
        return false;
    return true;
}
// pattern: __attribute__|__attribute (
MAYBE_UNUSED static inline bool match668(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("__attribute__")) || (tok->str() == MatchCompiler::makeConstString("__attribute"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: __declspec|_declspec (
MAYBE_UNUSED static inline bool match669(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("__declspec")) || (tok->str() == MatchCompiler::makeConstString("_declspec"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: [;={]
MAYBE_UNUSED static inline bool match670(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";={", tok->str()[0]))
        return false;
    return true;
}
// pattern: const|volatile|static|*|&|&&|%type%
MAYBE_UNUSED static inline bool match671(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->isName() && tok->varId() == 0U)))
        return false;
    return true;
}
// pattern: %name%|*|&|(
MAYBE_UNUSED static inline bool match672(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: %name%|::|<|*|& !!(
MAYBE_UNUSED static inline bool match673(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    return true;
}
// pattern: %name% (|)
MAYBE_UNUSED static inline bool match674(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: [;{=:]
MAYBE_UNUSED static inline bool match675(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{=:", tok->str()[0]))
        return false;
    return true;
}
// pattern: operator %op% (
MAYBE_UNUSED static inline bool match676(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isOp())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: [;{}*]
MAYBE_UNUSED static inline bool match677(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}*", tok->str()[0]))
        return false;
    return true;
}
// pattern: noreturn|nothrow|dllexport
MAYBE_UNUSED static inline bool match678(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("noreturn")) || (tok->str() == MatchCompiler::makeConstString("nothrow")) || (tok->str() == MatchCompiler::makeConstString("dllexport"))))
        return false;
    return true;
}
// pattern: [(,] constructor|__constructor__ [,()]
MAYBE_UNUSED static inline bool match679(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("constructor")) || (tok->str() == MatchCompiler::makeConstString("__constructor__"))))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",()", tok->str()[0]))
        return false;
    return true;
}
// pattern: [(,] destructor|__destructor__ [,()]
MAYBE_UNUSED static inline bool match680(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("destructor")) || (tok->str() == MatchCompiler::makeConstString("__destructor__"))))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",()", tok->str()[0]))
        return false;
    return true;
}
// pattern: [(,] unused|__unused__|used|__used__ [,)]
MAYBE_UNUSED static inline bool match681(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("unused")) || (tok->str() == MatchCompiler::makeConstString("__unused__")) || (tok->str() == MatchCompiler::makeConstString("used")) || (tok->str() == MatchCompiler::makeConstString("__used__"))))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: [(,] pure|__pure__|const|__const__|noreturn|__noreturn__|nothrow|__nothrow__|warn_unused_result [,)]
MAYBE_UNUSED static inline bool match682(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("pure")) || (tok->str() == MatchCompiler::makeConstString("__pure__")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("__const__")) || (tok->str() == MatchCompiler::makeConstString("noreturn")) || (tok->str() == MatchCompiler::makeConstString("__noreturn__")) || (tok->str() == MatchCompiler::makeConstString("nothrow")) || (tok->str() == MatchCompiler::makeConstString("__nothrow__")) || (tok->str() == MatchCompiler::makeConstString("warn_unused_result"))))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: [(,] packed [,)]
MAYBE_UNUSED static inline bool match683(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("packed")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: ( __visibility__ ( \"default\" ) )
MAYBE_UNUSED static inline bool match684(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("__visibility__")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("\"default\"")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: [(,] cleanup ( %name% )
MAYBE_UNUSED static inline bool match685(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("cleanup")))
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
    return true;
}
// pattern: %name%|*|&|::
MAYBE_UNUSED static inline bool match686(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: __cppcheck_low__ ( %num% )
MAYBE_UNUSED static inline bool match687(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("__cppcheck_low__")))
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
// pattern: __cppcheck_high__ ( %num% )
MAYBE_UNUSED static inline bool match688(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("__cppcheck_high__")))
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
// pattern: noreturn
template<class T> MAYBE_UNUSED static inline T * findmatch689(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("noreturn")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: %name%|::|*|&|<|>|,
MAYBE_UNUSED static inline bool match690(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: ) __attribute__
MAYBE_UNUSED static inline bool match691(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("__attribute__")))
        return false;
    return true;
}
// pattern: nodiscard
template<class T> MAYBE_UNUSED static inline T * findmatch692(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("nodiscard")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: fallthrough
template<class T> MAYBE_UNUSED static inline T * findmatch693(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("fallthrough")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: __fallthrough__
template<class T> MAYBE_UNUSED static inline T * findmatch694(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("__fallthrough__")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: __maybe_unused__
template<class T> MAYBE_UNUSED static inline T * findmatch695(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("__maybe_unused__")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: maybe_unused
template<class T> MAYBE_UNUSED static inline T * findmatch696(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("maybe_unused")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: %name%|*|&|&&|const|static|inline|volatile
MAYBE_UNUSED static inline bool match697(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("inline")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile"))))
        return false;
    return true;
}
// pattern: auto [
MAYBE_UNUSED static inline bool match698(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("auto")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] [;={]
MAYBE_UNUSED static inline bool match699(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";={", tok->str()[0]))
        return false;
    return true;
}
// pattern: unused
template<class T> MAYBE_UNUSED static inline T * findmatch700(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("unused")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: ) [ [ expects|ensures|assert default|audit|axiom| : %name% <|<=|>|>= %num% ] ]
MAYBE_UNUSED static inline bool match701(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("expects")) || (tok->str() == MatchCompiler::makeConstString("ensures")) || (tok->str() == MatchCompiler::makeConstString("assert"))))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("default")) || (tok->str() == MatchCompiler::makeConstString("audit")) || (tok->str() == MatchCompiler::makeConstString("axiom"))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<=")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">="))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    return true;
}
// pattern: <= >
MAYBE_UNUSED static inline bool match702(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    return true;
}
// pattern: [ static %num%
MAYBE_UNUSED static inline bool match703(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("static")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: struct|class|union %type%
MAYBE_UNUSED static inline bool match704(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("union"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: final [:{]
MAYBE_UNUSED static inline bool match705(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("final")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(":{", tok->str()[0]))
        return false;
    return true;
}
// pattern: ) const|override|final| noexcept :|{|;|,|const|override|final
MAYBE_UNUSED static inline bool match706(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("override")) || (tok->str() == MatchCompiler::makeConstString("final"))))
        tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("noexcept")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || (tok->str() == MatchCompiler::makeConstString("override")) || (tok->str() == MatchCompiler::makeConstString("final"))))
        return false;
    return true;
}
// pattern: [;{}] %name% = ( {
MAYBE_UNUSED static inline bool match707(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: )|}
MAYBE_UNUSED static inline bool match708(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: %type%|*
MAYBE_UNUSED static inline bool match709(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: } )
MAYBE_UNUSED static inline bool match710(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: [;{}] %num%|%name% ;
MAYBE_UNUSED static inline bool match711(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isNumber() || tok->isName()))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: __asm|_asm|asm {
MAYBE_UNUSED static inline bool match712(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("__asm")) || (tok->str() == MatchCompiler::makeConstString("_asm")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("asm"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: asm|__asm|__asm__ volatile|__volatile|__volatile__|goto|inline| (
MAYBE_UNUSED static inline bool match713(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("asm")) || (tok->str() == MatchCompiler::makeConstString("__asm")) || (tok->str() == MatchCompiler::makeConstString("__asm__"))))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || (tok->str() == MatchCompiler::makeConstString("__volatile")) || (tok->str() == MatchCompiler::makeConstString("__volatile__")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("goto")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("inline"))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: _asm|__asm
MAYBE_UNUSED static inline bool match714(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("_asm")) || (tok->str() == MatchCompiler::makeConstString("__asm"))))
        return false;
    return true;
}
// pattern: %num%|%name%|,|:|;
MAYBE_UNUSED static inline bool match715(const Token* tok) {
    if (!tok || !(tok->isNumber() || tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: _asm|__asm|__endasm
MAYBE_UNUSED static inline bool match716(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("_asm")) || (tok->str() == MatchCompiler::makeConstString("__asm")) || (tok->str() == MatchCompiler::makeConstString("__endasm"))))
        return false;
    return true;
}
// pattern: __endasm
MAYBE_UNUSED static inline bool match717(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("__endasm")))
        return false;
    return true;
}
// pattern: ) %name% %name% (
MAYBE_UNUSED static inline bool match718(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ^ {
MAYBE_UNUSED static inline bool match719(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: [,(;{}=]
MAYBE_UNUSED static inline bool match720(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",(;{}=", tok->str()[0]))
        return false;
    return true;
}
// pattern: )|]|>
MAYBE_UNUSED static inline bool match721(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: %cop%|,|;|{|}|)
MAYBE_UNUSED static inline bool match722(const Token* tok) {
    if (!tok || !(tok->isConstOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: %name%|]|) @ %num%|%name%|%str%|(
MAYBE_UNUSED static inline bool match723(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("@")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isNumber() || tok->isName() || (tok->tokType() == Token::eString) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: : %num% ;
MAYBE_UNUSED static inline bool match724(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: [;=]
MAYBE_UNUSED static inline bool match725(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";=", tok->str()[0]))
        return false;
    return true;
}
// pattern: @ builtin|eeprom|far|inline|interrupt|near|noprd|nostack|nosvf|packed|stack|svlreg|tiny|vector
MAYBE_UNUSED static inline bool match726(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("@")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("builtin")) || (tok->str() == MatchCompiler::makeConstString("eeprom")) || (tok->str() == MatchCompiler::makeConstString("far")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("inline")) || (tok->str() == MatchCompiler::makeConstString("interrupt")) || (tok->str() == MatchCompiler::makeConstString("near")) || (tok->str() == MatchCompiler::makeConstString("noprd")) || (tok->str() == MatchCompiler::makeConstString("nostack")) || (tok->str() == MatchCompiler::makeConstString("nosvf")) || (tok->str() == MatchCompiler::makeConstString("packed")) || (tok->str() == MatchCompiler::makeConstString("stack")) || (tok->str() == MatchCompiler::makeConstString("svlreg")) || (tok->str() == MatchCompiler::makeConstString("tiny")) || (tok->str() == MatchCompiler::makeConstString("vector"))))
        return false;
    return true;
}
// pattern: ;|{|}|public:|protected:|private:
MAYBE_UNUSED static inline bool match727(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("private:"))))
        return false;
    return true;
}
// pattern: %type% %name% :
MAYBE_UNUSED static inline bool match728(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: case|public|protected|private|class|struct
MAYBE_UNUSED static inline bool match729(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("case")) || (tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("protected")) || (tok->str() == MatchCompiler::makeConstString("private")) || (tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        return false;
    return true;
}
// pattern: default :
MAYBE_UNUSED static inline bool match730(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("default")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: %name% : %num% [;=,]
MAYBE_UNUSED static inline bool match731(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";=,", tok->str()[0]))
        return false;
    return true;
}
// pattern: %bool%|%num%
MAYBE_UNUSED static inline bool match732(const Token* tok) {
    if (!tok || !(tok->isBoolean() || tok->isNumber()))
        return false;
    return true;
}
// pattern: public|protected|private| %type% ::|<|,|{|;
MAYBE_UNUSED static inline bool match733(const Token* tok) {
    if (tok && ((tok->str() == MatchCompiler::makeConstString("public")) || (tok->str() == MatchCompiler::makeConstString("protected")) || (tok->str() == MatchCompiler::makeConstString("private"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: [;,)]{}=]
MAYBE_UNUSED static inline bool match734(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";,)]{}=", tok->str()[0]))
        return false;
    return true;
}
// pattern: } %name%| : %num% ;
MAYBE_UNUSED static inline bool match735(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: %type% : %num%|%bool% ;
MAYBE_UNUSED static inline bool match736(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isNumber() || tok->isBoolean()))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: using namespace std ;
template<class T> MAYBE_UNUSED static inline T * findmatch737(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        continue;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        continue;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("std")))
        continue;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: enum class|struct| %name%| :|{
MAYBE_UNUSED static inline bool match738(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("enum")))
        return false;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        tok = tok->next();
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: .|::|namespace
MAYBE_UNUSED static inline bool match739(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("::")) || (tok->str() == MatchCompiler::makeConstString("namespace"))))
        return false;
    return true;
}
// pattern: %type%|*|&
MAYBE_UNUSED static inline bool match740(const Token* tok) {
    if (!tok || !((tok->isName() && tok->varId() == 0U) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: using namespace std ;
MAYBE_UNUSED static inline bool match741(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("using")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("std")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: CopyMemory|RtlCopyMemory|RtlCopyBytes
MAYBE_UNUSED static inline bool match742(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("CopyMemory")) || (tok->str() == MatchCompiler::makeConstString("RtlCopyMemory")) || (tok->str() == MatchCompiler::makeConstString("RtlCopyBytes"))))
        return false;
    return true;
}
// pattern: MoveMemory|RtlMoveMemory
MAYBE_UNUSED static inline bool match743(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("MoveMemory")) || (tok->str() == MatchCompiler::makeConstString("RtlMoveMemory"))))
        return false;
    return true;
}
// pattern: FillMemory|RtlFillMemory|RtlFillBytes
MAYBE_UNUSED static inline bool match744(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("FillMemory")) || (tok->str() == MatchCompiler::makeConstString("RtlFillMemory")) || (tok->str() == MatchCompiler::makeConstString("RtlFillBytes"))))
        return false;
    return true;
}
// pattern: ZeroMemory|RtlZeroMemory|RtlZeroBytes|RtlSecureZeroMemory
MAYBE_UNUSED static inline bool match745(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("ZeroMemory")) || (tok->str() == MatchCompiler::makeConstString("RtlZeroMemory")) || (tok->str() == MatchCompiler::makeConstString("RtlZeroBytes")) || (tok->str() == MatchCompiler::makeConstString("RtlSecureZeroMemory"))))
        return false;
    return true;
}
// pattern: RtlCompareMemory
MAYBE_UNUSED static inline bool match746(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("RtlCompareMemory")))
        return false;
    return true;
}
// pattern: _T|_TEXT|TEXT ( %char%|%str% )
MAYBE_UNUSED static inline bool match747(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("_T")) || (tok->str() == MatchCompiler::makeConstString("_TEXT")) || (tok->str() == MatchCompiler::makeConstString("TEXT"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eChar) || (tok->tokType() == Token::eString)))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ( __closure * %name% )
MAYBE_UNUSED static inline bool match748(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("__closure")))
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
// pattern: namespace %type%
MAYBE_UNUSED static inline bool match749(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: class %name% :|{
MAYBE_UNUSED static inline bool match750(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("class")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: ;|{|}|protected:|public:|__published:
MAYBE_UNUSED static inline bool match751(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString("protected:")) || (tok->str() == MatchCompiler::makeConstString("public:")) || (tok->str() == MatchCompiler::makeConstString("__published:"))))
        return false;
    return true;
}
// pattern: [=;{}),]
MAYBE_UNUSED static inline bool match752(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("=;{}),", tok->str()[0]))
        return false;
    return true;
}
// pattern: const|volatile|override
MAYBE_UNUSED static inline bool match753(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")) || (tok->str() == MatchCompiler::makeConstString("override"))))
        return false;
    return true;
}
// pattern: %op% !!(
MAYBE_UNUSED static inline bool match754(const Token* tok) {
    if (!tok || !tok->isOp())
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    return true;
}
// pattern: using|:: operator %op%|%name% ;
MAYBE_UNUSED static inline bool match755(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("using")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isOp() || tok->isName()))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: :: %name%|%op%|.
MAYBE_UNUSED static inline bool match756(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || tok->isOp() || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    return true;
}
// pattern: .|%op%|,
MAYBE_UNUSED static inline bool match757(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || tok->isOp() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    return true;
}
// pattern: <|>
MAYBE_UNUSED static inline bool match758(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: [ ]
MAYBE_UNUSED static inline bool match759(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    return true;
}
// pattern: ( *| )
MAYBE_UNUSED static inline bool match760(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ...
MAYBE_UNUSED static inline bool match761(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eEllipsis) && tok->str() == MatchCompiler::makeConstString("...")))
        return false;
    return true;
}
// pattern: \"\" %name% )| (|;|<
MAYBE_UNUSED static inline bool match762(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("\"\"")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: ( & (
MAYBE_UNUSED static inline bool match763(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %op% %str% %name%
MAYBE_UNUSED static inline bool match764(const Token* tok) {
    if (!tok || !tok->isOp())
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: operator
template<class T> MAYBE_UNUSED static inline T * findmatch765(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: this ) (
MAYBE_UNUSED static inline bool match766(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("this")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: operator() (
MAYBE_UNUSED static inline bool match767(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator()")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %type% &| %var%
MAYBE_UNUSED static inline bool match768(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    return true;
}
// pattern: %var% (
MAYBE_UNUSED static inline bool match769(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: [:,]
MAYBE_UNUSED static inline bool match770(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(":,", tok->str()[0]))
        return false;
    return true;
}
// pattern: )|} , %name% (|{
MAYBE_UNUSED static inline bool match771(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: :
MAYBE_UNUSED static inline bool match772(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: class|struct|namespace %type% :|{
MAYBE_UNUSED static inline bool match773(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("class")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct")) || (tok->str() == MatchCompiler::makeConstString("namespace"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: %type% :: ~| %type% (
MAYBE_UNUSED static inline bool match774(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %type% :: operator
MAYBE_UNUSED static inline bool match775(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("operator")))
        return false;
    return true;
}
// pattern: ) const| {|;|:
MAYBE_UNUSED static inline bool match776(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const"))))
        tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: %type% :: ~| %type%
MAYBE_UNUSED static inline bool match777(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: %type% * *|&
MAYBE_UNUSED static inline bool match778(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: [|(|<
MAYBE_UNUSED static inline bool match779(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: ;|{|}|,|(
MAYBE_UNUSED static inline bool match780(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: END - __CPPCHECK_EMBEDDED_SQL_EXEC__ ;
MAYBE_UNUSED static inline bool match781(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("END")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("__CPPCHECK_EMBEDDED_SQL_EXEC__")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: {|}|==|&&|!|^|<<|>>|++|+=|-=|/=|*=|>>=|<<=|~
MAYBE_UNUSED static inline bool match782(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("==")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("<<")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("+=")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("-=")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("/=")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("*=")) || (tok->str() == MatchCompiler::makeConstString(">>=")) || (tok->str() == MatchCompiler::makeConstString("<<=")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("~"))))
        return false;
    return true;
}
// pattern: namespace %name% ::
MAYBE_UNUSED static inline bool match783(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: co_return|co_yield|co_await
MAYBE_UNUSED static inline bool match784(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("co_return")) || (tok->str() == MatchCompiler::makeConstString("co_yield")) || (tok->str() == MatchCompiler::makeConstString("co_await"))))
        return false;
    return true;
}
// pattern: [({[]
MAYBE_UNUSED static inline bool match785(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("({[", tok->str()[0]))
        return false;
    return true;
}
// pattern: [)]}]
MAYBE_UNUSED static inline bool match786(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(")]}", tok->str()[0]))
        return false;
    return true;
}
// pattern: ;
template<class T> MAYBE_UNUSED static inline T * findmatch787(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: namespace %name% =
MAYBE_UNUSED static inline bool match788(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("namespace")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/tokenize.cpp"
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
#include "tokenize.h"

#include "astutils.h"
#include "errorlogger.h"
#include "errortypes.h"
#include "library.h"
#include "mathlib.h"
#include "path.h"
#include "platform.h"
#include "preprocessor.h"
#include "settings.h"
#include "standards.h"
#include "summaries.h"
#include "symboldatabase.h"
#include "templatesimplifier.h"
#include "timer.h"
#include "token.h"
#include "utils.h"
#include "valueflow.h"
#include "vfvalue.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <iterator>
#include <exception>
#include <memory>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <simplecpp.h>

//---------------------------------------------------------------------------

namespace {
    // local struct used in setVarId
    // in order to store information about the scope
    struct VarIdScopeInfo {
        VarIdScopeInfo() = default;
        VarIdScopeInfo(bool isExecutable, bool isStructInit, bool isEnum, nonneg int startVarid)
            : isExecutable(isExecutable), isStructInit(isStructInit), isEnum(isEnum), startVarid(startVarid) {}

        const bool isExecutable{};
        const bool isStructInit{};
        const bool isEnum{};
        const nonneg int startVarid{};
    };
}

/** Return whether tok is the "{" that starts an enumerator list */
static bool isEnumStart(const Token* tok)
{
    if (!match1(tok))
        return false;
    tok = tok->previous();
    while (tok && (!tok->isKeyword() || Token::isStandardType(tok->str())) && match2(tok))
        tok = tok->previous();
    if (match3(tok))
        tok = tok->previous();
    return match4(tok);
}

template<typename T>
static void skipEnumBody(T *&tok)
{
    T *defStart = tok;
    while (match2(defStart))
        defStart = defStart->next();
    if (defStart && defStart->str() == MatchCompiler::makeConstString("{"))
        tok = defStart->link()->next();
}

/**
 * is tok the start brace { of a class, struct, union, or enum
 */
static bool isClassStructUnionEnumStart(const Token * tok)
{
    if (!match5(tok->previous()))
        return false;
    const Token * tok2 = tok->previous();
    while (tok2 && !match6(tok2))
        tok2 = tok2->previous();
    return match7(tok2);
}

//---------------------------------------------------------------------------

Tokenizer::Tokenizer(TokenList tokenList, ErrorLogger &errorLogger) :
    list(std::move(tokenList)),
    mSettings(list.getSettings()),
    mErrorLogger(errorLogger),
    mTemplateSimplifier(new TemplateSimplifier(*this))
{}

Tokenizer::~Tokenizer()
{
    delete mSymbolDatabase;
    delete mTemplateSimplifier;
}


//---------------------------------------------------------------------------
// SizeOfType - gives the size of a type
//---------------------------------------------------------------------------

nonneg int Tokenizer::sizeOfType(const std::string& type) const
{
    const auto it = utils::as_const(mTypeSize).find(type);
    if (it == mTypeSize.end()) {
        const Library::PodType* podtype = mSettings.library.podtype(type);
        if (!podtype)
            return 0;

        return podtype->size;
    }
    return it->second;
}

nonneg int Tokenizer::sizeOfType(const Token *type) const
{
    if (!type || type->str().empty())
        return 0;

    if (type->tokType() == Token::eString)
        return Token::getStrLength(type) + 1U;

    const auto it = utils::as_const(mTypeSize).find(type->str());
    if (it == mTypeSize.end()) {
        const Library::PodType* podtype = mSettings.library.podtype(type->str());
        if (!podtype)
            return 0;

        return podtype->size;
    }
    if (type->isLong()) {
        if (type->str() == MatchCompiler::makeConstString("double"))
            return mSettings.platform.sizeof_long_double;
        if (type->str() == MatchCompiler::makeConstString("long"))
            return mSettings.platform.sizeof_long_long;
    }

    return it->second;
}
//---------------------------------------------------------------------------

// check if this statement is a duplicate definition
bool Tokenizer::duplicateTypedef(Token *&tokPtr, const Token *name, const Token *typeDef) const
{
    // check for an end of definition
    Token * tok = tokPtr;
    if (tok && match8(tok->next())) {
        Token * end = tok->next();

        if (end->str() == MatchCompiler::makeConstString("[")) {
            if (!end->link())
                syntaxError(end); // invalid code
            end = end->link()->next();
        } else if (end->str() == MatchCompiler::makeConstString(",")) {
            // check for derived class
            if (match9(tok->previous()))
                return false;

            // find end of definition
            while (end && end->next() && !match10(end->next())) {
                if (end->strAt(1) == MatchCompiler::makeConstString("("))
                    end = end->linkAt(1);

                end = (end)?end->next():nullptr;
            }
            if (end)
                end = end->next();
        } else if (end->str() == MatchCompiler::makeConstString("(")) {
            if (startsWith(tok->strAt(-1), "operator"))
                // conversion operator
                return false;
            if (tok->strAt(-1) == MatchCompiler::makeConstString("typedef"))
                // typedef of function returning this type
                return false;
            if (match11(tok->previous()))
                return false;
            if (tok->strAt(-1) == MatchCompiler::makeConstString(">")) {
                if (!match12(tok->tokAt(-2)))
                    return false;

                if (!match13(tok->tokAt(-3)))
                    return false;

                tokPtr = end->link();
                return true;
            }
        }

        if (end) {
            if (match14(end)) { // function parameter ?
                // look backwards
                if (match12(tok->previous()) &&
                    !match15(tok->previous())) {
                    // duplicate definition so skip entire function
                    tokPtr = end->linkAt(1);
                    return true;
                }
            } else if (end->str() == MatchCompiler::makeConstString(">")) { // template parameter ?
                // look backwards
                if (match12(tok->previous()) &&
                    !match16(tok->previous())) {
                    // duplicate definition so skip entire template
                    while (end && end->str() != MatchCompiler::makeConstString("{"))
                        end = end->next();
                    if (end) {
                        tokPtr = end->link();
                        return true;
                    }
                }
            } else {
                // look backwards
                if (match17(tok->previous()) ||
                    (end->str() == MatchCompiler::makeConstString(";") && tok->strAt(-1) == MatchCompiler::makeConstString(",")) ||
                    (tok->strAt(-1) == MatchCompiler::makeConstString("*") && tok->strAt(1) != MatchCompiler::makeConstString("(")) ||
                    (match12(tok->previous()) &&
                     (!match18(tok->previous()) &&
                      !match19(tok->tokAt(-2))))) {
                    // scan backwards for the end of the previous statement
                    while (tok && tok->previous() && !match20(tok->previous())) {
                        if (tok->strAt(-1) == MatchCompiler::makeConstString("}")) {
                            tok = tok->linkAt(-1);
                        } else if (tok->strAt(-1) == MatchCompiler::makeConstString("typedef")) {
                            return true;
                        } else if (tok->strAt(-1) == MatchCompiler::makeConstString("enum")) {
                            return true;
                        } else if (tok->strAt(-1) == MatchCompiler::makeConstString("struct")) {
                            if (tok->strAt(-2) == MatchCompiler::makeConstString("typedef") &&
                                tok->strAt(1) == MatchCompiler::makeConstString("{") &&
                                typeDef->strAt(3) != MatchCompiler::makeConstString("{")) {
                                // declaration after forward declaration
                                return true;
                            }
                            if (tok->strAt(1) == MatchCompiler::makeConstString("{"))
                                return true;
                            if (match21(tok->next()))
                                return true;
                            if (tok->strAt(1) == name->str())
                                return true;
                            if (tok->strAt(1) != MatchCompiler::makeConstString(";"))
                                return true;
                            return false;
                        } else if (tok->strAt(-1) == MatchCompiler::makeConstString("union")) {
                            return tok->strAt(1) != MatchCompiler::makeConstString(";");
                        } else if (tok->isCpp() && tok->strAt(-1) == MatchCompiler::makeConstString("class")) {
                            return tok->strAt(1) != MatchCompiler::makeConstString(";");
                        }
                        if (tok)
                            tok = tok->previous();
                    }

                    if (tokPtr->strAt(1) != MatchCompiler::makeConstString("(") || !match22(tokPtr->linkAt(1)))
                        return true;
                }
            }
        }
    }

    return false;
}

void Tokenizer::unsupportedTypedef(const Token *tok) const
{
    if (!mSettings.debugwarnings)
        return;

    std::ostringstream str;
    const Token *tok1 = tok;
    int level = 0;
    while (tok) {
        if (level == 0 && tok->str() == MatchCompiler::makeConstString(";"))
            break;
        if (tok->str() == MatchCompiler::makeConstString("{"))
            ++level;
        else if (tok->str() == MatchCompiler::makeConstString("}")) {
            if (level == 0)
                break;
            --level;
        }

        if (tok != tok1)
            str << " ";
        str << tok->str();
        tok = tok->next();
    }
    if (tok)
        str << " ;";

    reportError(tok1, Severity::debug, "simplifyTypedef",
                "Failed to parse \'" + str.str() + "\'. The checking continues anyway.");
}

Token * Tokenizer::deleteInvalidTypedef(Token *typeDef)
{
    Token *tok = nullptr;

    // remove typedef but leave ;
    while (typeDef->next()) {
        if (typeDef->strAt(1) == MatchCompiler::makeConstString(";")) {
            typeDef->deleteNext();
            break;
        }
        if (typeDef->strAt(1) == MatchCompiler::makeConstString("{"))
            Token::eraseTokens(typeDef, typeDef->linkAt(1));
        else if (typeDef->strAt(1) == MatchCompiler::makeConstString("}"))
            break;
        typeDef->deleteNext();
    }

    if (typeDef != list.front()) {
        tok = typeDef->previous();
        tok->deleteNext();
    } else {
        list.front()->deleteThis();
        tok = list.front();
    }

    return tok;
}

namespace {
    struct Space {
        std::string className;
        const Token* bodyEnd{};  // for body contains typedef define
        const Token* bodyEnd2{}; // for body contains typedef using
        bool isNamespace{};
        std::set<std::string> recordTypes;
    };
}

static Token *splitDefinitionFromTypedef(Token *tok, nonneg int *unnamedCount)
{
    std::string name;
    std::set<std::string> qualifiers;

    while (match23(tok->next())) {
        qualifiers.insert(tok->strAt(1));
        tok->deleteNext();
    }

    // skip "class|struct|union|enum"
    Token *tok1 = tok->tokAt(2);

    const bool hasName = match24(tok1);

    // skip name
    if (hasName) {
        name = tok1->str();
        tok1 = tok1->next();
    }

    // skip base classes if present
    if (tok1->str() == MatchCompiler::makeConstString(":")) {
        tok1 = tok1->next();
        while (tok1 && tok1->str() != MatchCompiler::makeConstString("{"))
            tok1 = tok1->next();
        if (!tok1)
            return nullptr;
    }

    // skip to end
    tok1 = tok1->link();

    if (!hasName) { // unnamed
        if (tok1->next()) {
            // use typedef name if available
            if (match12(tok1->next()))
                name = tok1->strAt(1);
            else // create a unique name
                name = "Unnamed" + std::to_string((*unnamedCount)++);
            tok->next()->insertToken(name);
        } else
            return nullptr;
    }

    tok1->insertToken(";");
    tok1 = tok1->next();

    if (tok1->next() && tok1->strAt(1) == MatchCompiler::makeConstString(";") && tok1->strAt(-1) == MatchCompiler::makeConstString("}")) {
        tok->deleteThis();
        tok1->deleteThis();
        return nullptr;
    }
    tok1->insertToken("typedef");
    tok1 = tok1->next();
    Token * tok3 = tok1;
    for (const std::string &qualifier : qualifiers) {
        tok1->insertToken(qualifier);
        tok1 = tok1->next();
    }
    tok1->insertToken(tok->strAt(1)); // struct, union or enum
    tok1 = tok1->next();
    tok1->insertToken(name);
    tok->deleteThis();
    tok = tok3;

    return tok;
}

/* This function is called when processing function related typedefs.
 * If simplifyTypedef generates an "Internal Error" message and the
 * code that generated it deals in some way with functions, then this
 * function will probably need to be extended to handle a new function
 * related pattern */
const Token *Tokenizer::processFunc(const Token *tok2, bool inOperator) const
{
    if (tok2->next() && tok2->strAt(1) != MatchCompiler::makeConstString(")") &&
        tok2->strAt(1) != MatchCompiler::makeConstString(",")) {
        // skip over tokens for some types of canonicalization
        if (match25(tok2->next()))
            tok2 = tok2->linkAt(5);
        else if (match26(tok2->next()))
            tok2 = tok2->linkAt(6);
        else if (match27(tok2->next()))
            tok2 = tok2->tokAt(5);
        else if (match28(tok2->next()) &&
                 match29(tok2->linkAt(4)))
            tok2 = tok2->linkAt(4)->next();
        else if (match30(tok2->next()))
            tok2 = tok2->linkAt(5)->next();
        else if (match31(tok2->next()) &&
                 match32(tok2->linkAt(2)))
            tok2 = tok2->next();
        else {
            if (tok2->strAt(1) == MatchCompiler::makeConstString("("))
                tok2 = tok2->linkAt(1);
            else if (!inOperator && !match33(tok2->next())) {
                tok2 = tok2->next();

                while (match34(tok2) &&
                       !match35(tok2->next()))
                    tok2 = tok2->next();

                // skip over namespace
                while (match36(tok2))
                    tok2 = tok2->tokAt(2);

                if (match37(tok2))
                    tok2 = tok2->next();

                if (!tok2)
                    return nullptr;

                if (tok2->str() == MatchCompiler::makeConstString("(") &&
                    tok2->link()->next() &&
                    tok2->link()->strAt(1) == MatchCompiler::makeConstString("(")) {
                    tok2 = tok2->link();

                    if (tok2->strAt(1) == MatchCompiler::makeConstString("("))
                        tok2 = tok2->linkAt(1);
                }

                // skip over typedef parameter
                if (tok2->next() && tok2->strAt(1) == MatchCompiler::makeConstString("(")) {
                    tok2 = tok2->linkAt(1);
                    if (!tok2->next())
                        syntaxError(tok2);

                    if (tok2->strAt(1) == MatchCompiler::makeConstString("("))
                        tok2 = tok2->linkAt(1);
                }
            }
        }
    }
    return tok2;
}

Token *Tokenizer::processFunc(Token *tok2, bool inOperator)
{
    return const_cast<Token*>(processFunc(const_cast<const Token*>(tok2), inOperator));
}

void Tokenizer::simplifyTypedefLHS()
{
    if (!list.front())
        return;

    for (Token* tok = list.front()->next(); tok; tok = tok->next()) {
        if (tok->str() == MatchCompiler::makeConstString("typedef")) {
            bool doSimplify = !match38(tok->previous());
            if (doSimplify && match40(tok->previous()) && match39(tok->linkAt(-1)->previous()))
                doSimplify = false;
            bool haveStart = false;
            Token* start{};
            if (!doSimplify && match41(tok->previous())) {
                start = tok->linkAt(-1)->previous();
                while (match24(start)) {
                    if (match7(start)) {
                        start = start->previous();
                        doSimplify = true;
                        haveStart = true;
                        break;
                    }
                    start = start->previous();
                }
            }
            if (doSimplify) {
                if (!haveStart) {
                    start = tok;
                    while (start && !match42(start))
                        start = start->previous();
                }
                if (start)
                    start = start->next();
                else
                    start = list.front();
                start->insertTokenBefore(tok->str());
                tok->deleteThis();
            }
        }
    }
}

namespace {
    class TypedefSimplifier {
    private:
        Token* mTypedefToken;  // The "typedef" token
        Token* mEndToken{nullptr};  // Semicolon
        std::pair<Token*, Token*> mRangeType;
        std::pair<Token*, Token*> mRangeTypeQualifiers;
        std::pair<Token*, Token*> mRangeAfterVar;
        Token* mNameToken{nullptr};
        bool mFail = false;
        bool mReplaceFailed = false;
        bool mUsed = false;

    public:
        explicit TypedefSimplifier(Token* typedefToken) : mTypedefToken(typedefToken) {
            Token* start = typedefToken->next();
            if (match43(start))
                start = start->next();

            // TODO handle unnamed structs etc
            if (match44(start)) {
                const std::pair<Token*, Token*> rangeBefore(start, findmatch45(start) );

                // find typedef name token
                Token* nameToken = rangeBefore.second->link()->next();
                while (match46(nameToken))
                    nameToken = nameToken->next();
                const std::pair<Token*, Token*> rangeQualifiers(rangeBefore.second->link()->next(), nameToken);

                if (match47(nameToken)) {
                    if (match48(rangeBefore.second->previous()))
                        rangeBefore.second->previous()->insertToken(nameToken->str());
                    mRangeType = rangeBefore;
                    mRangeTypeQualifiers = rangeQualifiers;
                    Token* typeName = rangeBefore.second->previous();
                    if (typeName->isKeyword()) {
                        // TODO typeName->insertToken("T:" + std::to_string(num++));
                        typeName->insertToken(nameToken->str());
                    }
                    mNameToken = nameToken;
                    mEndToken = nameToken->next();
                    return;
                }
            }

            for (Token* type = start; match49(type); type = type->next()) {
                if (type != start && match47(type) && !type->isStandardType()) {
                    mRangeType.first = start;
                    mRangeType.second = type;
                    mNameToken = type;
                    mEndToken = mNameToken->next();
                    return;
                }
                if (type != start && match50(type)) {
                    Token* end = type->linkAt(1);
                    while (match51(end))
                        end = end->linkAt(1);
                    if (!match32(end))
                        break;
                    mRangeType.first = start;
                    mRangeType.second = type;
                    mNameToken = type;
                    mEndToken = end->next();
                    mRangeAfterVar.first = mNameToken->next();
                    mRangeAfterVar.second = mEndToken;
                    return;
                }
                if (match52(type->next()) && match53(type->linkAt(1)->linkAt(1))) {
                    mNameToken = type->linkAt(1)->previous();
                    mEndToken = type->linkAt(1)->linkAt(1)->next();
                    mRangeType.first = start;
                    mRangeType.second = mNameToken;
                    mRangeAfterVar.first = mNameToken->next();
                    mRangeAfterVar.second = mEndToken;
                    return;
                }
                if (type != start && match54(type) && match53(type->linkAt(1)) && !type->isStandardType()) {
                    mNameToken = type;
                    mEndToken = type->linkAt(1)->next();
                    mRangeType.first = start;
                    mRangeType.second = type;
                    mRangeAfterVar.first = mNameToken->next();
                    mRangeAfterVar.second = mEndToken;
                    return;
                }
            }
            // TODO: handle all typedefs
            if ((false))
                printTypedef(typedefToken, std::cout);
            mFail = true;
        }

        const Token* getTypedefToken() const {
            return mTypedefToken;
        }

        bool isUsed() const {
            return mUsed;
        }

        bool isInvalidConstFunctionType(const std::map<std::string, TypedefSimplifier>& m) const {
            if (!match55(mTypedefToken))
                return false;
            const auto it = m.find(mTypedefToken->strAt(2));
            if (it == m.end())
                return false;
            return match56(it->second.mNameToken);
        }

        bool fail() const {
            return mFail;
        }

        bool replaceFailed() const {
            return mReplaceFailed;
        }

        bool isStructEtc() const {
            return mRangeType.second && mRangeType.second->str() == MatchCompiler::makeConstString("{");
        }

        std::string name() const {
            return mNameToken ? mNameToken->str() : "";
        }

        void replace(Token* tok) {
            if (tok == mNameToken)
                return;

            mUsed = true;
            const bool isFunctionPointer = match57(mNameToken);

            // Special handling for T(...) when T is a pointer
            if (match58(tok) && !isFunctionPointer && !match59(tok->linkAt(1))) {
                bool pointerType = false;
                for (const Token* type = mRangeType.first; type != mRangeType.second; type = type->next()) {
                    if (type->str() == MatchCompiler::makeConstString("*") || type->str() == MatchCompiler::makeConstString("&")) {
                        pointerType = true;
                        break;
                    }
                }
                for (const Token* type = mRangeTypeQualifiers.first; type != mRangeTypeQualifiers.second; type = type->next()) {
                    if (type->str() == MatchCompiler::makeConstString("*") || type->str() == MatchCompiler::makeConstString("&")) {
                        pointerType = true;
                        break;
                    }
                }
                if (pointerType) {
                    tok->tokAt(1)->str("(");
                    tok->linkAt(1)->str(")");
                    if (tok->linkAt(1) == tok->tokAt(2)) { // T() or T{}
                        tok->deleteThis();
                        tok->next()->insertToken("0");
                        Token* tok2 = insertTokens(tok, mRangeType);
                        insertTokens(tok2, mRangeTypeQualifiers);
                    }
                    else { // functional-style cast
                        tok->originalName(tok->str());
                        tok->isSimplifiedTypedef(true);
                        tok->str("(");
                        Token* tok2 = insertTokens(tok, mRangeType);
                        tok2 = insertTokens(tok2, mRangeTypeQualifiers);
                        Token* tok3 = tok2->insertToken(")");
                        Token::createMutualLinks(tok, tok3);
                        tok->insertTokenBefore("(");
                        tok3 = tok3->linkAt(1);
                        tok3 = tok3->insertToken(")");
                        Token::createMutualLinks(tok->tokAt(-1), tok3);
                    }
                    return;
                }
            }

            // Special handling of function pointer cast
            if (isFunctionPointer && isCast(tok->previous())) {
                tok->insertToken("*");
                Token* const tok_1 = insertTokens(tok, std::pair<Token*, Token*>(mRangeType.first, mNameToken->linkAt(1)));
                tok_1->originalName(tok->str());
                tok->deleteThis();
                return;
            }

            // Inherited type => skip "struct" / "class"
            if (match60(mRangeType.first) && match61(tok->previous())) {
                tok->originalName(tok->str());
                tok->str(mRangeType.second->strAt(-1));
                return;
            }

            if (match36(tok)) {
                if (match62(mRangeType.first) ||
                    match63(mRangeType.first)) {
                    tok->originalName(tok->str());
                    tok->str(mRangeType.second->strAt(-1));
                } else {
                    mReplaceFailed = true;
                }
                return;
            }

            // pointer => move "const"
            if (match37(tok->previous())) {
                bool pointerType = false;
                for (const Token* type = mRangeType.first; type != mRangeType.second; type = type->next()) {
                    if (type->str() == MatchCompiler::makeConstString("*")) {
                        pointerType = true;
                        break;
                    }
                }
                if (pointerType) {
                    tok->insertToken("const");
                    tok->next()->column(tok->column());
                    if (!tok->previous()->getMacroName().empty())
                        tok->next()->setMacroName(tok->previous()->getMacroName());
                    tok->deletePrevious();
                }
            }

            // Do not duplicate class/struct/enum/union
            if (match64(tok->previous())) {
                bool found = false;
                const std::string &kw = tok->strAt(-1);
                for (const Token* type = mRangeType.first; type != mRangeType.second; type = type->next()) {
                    if (type->str() == kw) {
                        found = true;
                        break;
                    }
                }
                if (found)
                    tok->deletePrevious();
                else {
                    mReplaceFailed = true;
                    return;
                }
            }

            // don't add class|struct|union in inheritance list
            auto rangeType = mRangeType;
            if (match9(tok->previous())) {
                while (match65(rangeType.first))
                    rangeType.first = rangeType.first->next();
            }

            Token* const tok2 = insertTokens(tok, rangeType);
            Token* const tok3 = insertTokens(tok2, mRangeTypeQualifiers);

            tok2->originalName(tok->str());
            tok3->originalName(tok->str());
            Token *after = tok3;
            while (match66(after))
                after = after->next();
            if (match56(mNameToken) && match67(tok3->next())) {
                while (match68(after))
                    after = after->link()->next();
                if (after) {
                    tok3->insertToken("(");
                    after->previous()->insertToken(")");
                    Token::createMutualLinks(tok3->next(), after->previous());
                }
            }
            if (!after) {
                mReplaceFailed = true;
                return;
            }

            bool useAfterVarRange = true;
            if (match69(mRangeAfterVar.first)) {
                if (match70(after->previous())) {
                    useAfterVarRange = false;
                    // Function return type => replace array with "*"
                    for (const Token* a = mRangeAfterVar.first; match69(a); a = a->link()->next())
                        tok3->insertToken("*");
                } else if (match71(after->previous())) {
                    after = after->linkAt(4)->next();
                } else {
                    Token* prev = after->previous();
                    if (prev->isName() && prev != tok3)
                        prev = prev->previous();
                    if (match72(prev) && prev != tok3) {
                        while (match72(prev) && prev != tok3)
                            prev = prev->previous();
                        prev->insertToken("(");
                        after->previous()->insertToken(")");
                    }
                }
            }

            if (isFunctionPointer) {
                if (match73(after))
                    after = after->link()->linkAt(1)->next();
                else if (after->str() == MatchCompiler::makeConstString("(")) {
                    useAfterVarRange = false;
                    if (match74(tok3->previous()))
                        tok3->deletePrevious();
                }
                else if (after->str() == MatchCompiler::makeConstString("[")) {
                    while (after && after->str() == MatchCompiler::makeConstString("["))
                        after = after->link()->next();
                }
            }
            else {
                while (match69(after))
                    after = after->link()->next();
            }

            if (!after)
                throw InternalError(tok, "Failed to simplify typedef. Is the code valid?");

            Token* const tok4 = useAfterVarRange ? insertTokens(after->previous(), mRangeAfterVar)->next() : tok3->next();

            if (tok->next() == tok4)
                throw InternalError(tok, "Failed to simplify typedef. Is the code valid?");

            tok->deleteThis();

            // Unsplit variable declarations
            if (tok4 && tok4->isSplittedVarDeclEq() &&
                ((tok4->isCpp() && match75(tok4->tokAt(-2))) || match76(tok4->previous()))) {
                tok4->deleteNext();
                tok4->deleteThis();
            }

            // Set links
            std::stack<Token*> brackets;
            for (; tok != tok4; tok = tok->next()) {
                if (match77(tok))
                    brackets.push(tok);
                else if (match78(tok)) {
                    Token::createMutualLinks(brackets.top(), tok);
                    brackets.pop();
                }
            }
        }

        void removeDeclaration() {
            if (match1(mRangeType.second)) {
                while (match79(mTypedefToken))
                    mTypedefToken->deleteThis();
                Token::eraseTokens(mRangeType.second->link(), mEndToken);
            } else {
                Token::eraseTokens(mTypedefToken, mEndToken);
                mTypedefToken->deleteThis();
            }
        }

        static int canReplaceStatic(const Token* tok) {
            if (!match80(tok)) {
                if (match81(tok->previous()) && match82(tok->linkAt(-1)) && !tok->tokAt(-2)->isKeyword())
                    return true;
                if (match83(tok->previous()))
                    return true;
                if (match84(tok->previous()))
                    return true;
                if (match85(tok->previous()) && tok->previous()->findClosingBracket())
                    return true;
                if (match86(tok->previous())) {
                    for (const Token* prev = tok->previous(); prev; prev = prev->previous()) {
                        if (match87(prev))
                            break;
                        if (prev->str() == MatchCompiler::makeConstString("<") && prev->findClosingBracket() == tok->next())
                            return true;
                        if (prev->str() == MatchCompiler::makeConstString(")"))
                            prev = prev->link();
                    }
                    return true;
                }
                if (match88(tok->previous()))
                    return true;
                if (match89(tok->previous())) {
                    bool isGeneric = false;
                    for (; tok; tok = tok->previous()) {
                        if (match90(tok))
                            tok = tok->link();
                        else if (match87(tok)) {
                            isGeneric = match91(tok->previous());
                            break;
                        }
                    }
                    return isGeneric;
                }
                return false;
            }
            return -1;
        }

        bool canReplace(const Token* tok) {
            if (mNameToken == tok)
                return false;
            if (!match92(tok->previous()) && !match93(tok->previous()))
                return false;
            {
                const int res = canReplaceStatic(tok);
                if (res == 0 || res == 1)
                    return res != 0;
            }
            if (match24(tok->previous()) && !tok->previous()->isKeyword())
                return false;
            if (match94(tok->next()) && match82(tok->linkAt(1)))
                return false;
            if (match95(tok->previous()) &&
                match1(mRangeType.second) &&
                tok->str() != mRangeType.second->strAt(-1))
                return true;
            if (match96(tok->previous()))
                return false;
            if (match97(tok->previous()))
                return true;
            for (const Token* after = tok->next(); after; after = after->next()) {
                if (match98(after))
                    continue;
                if (after->str() == MatchCompiler::makeConstString("<") && after->link())
                    break;
                if (after->isNumber())
                    return false;
                if (after->isComparisonOp() || after->isArithmeticalOp())
                    return false;
                break;
            }
            for (const Token* before = tok->previous(); before; before = before->previous()) {
                if (match99(before))
                    return false;
                if (match100(before) || before->isStandardType())
                    return false;
                if (before->str() == MatchCompiler::makeConstString("::"))
                    return false;
                if (before->isName())
                    continue;
                break;
            }
            return true;
        }

        Token* endToken() const {
            return mEndToken;
        }

        Token* nameToken() const {
            return mNameToken;
        }

    private:
        static bool isCast(const Token* tok) {
            if (match101(tok))
                return !tok->tokAt(3)->isKeyword();
            if (match102(tok) && tok->previous() && endsWith(tok->strAt(-1), "_cast", 5))
                return true;
            return false;
        }

        static Token* insertTokens(Token* to, std::pair<Token*,Token*> range) {
            for (const Token* from = range.first; from != range.second; from = from->next()) {
                to->insertToken(from->str());
                to->next()->column(to->column());
                to = to->next();
                to->isSimplifiedTypedef(true);
                to->isExternC(from->isExternC());
            }
            return to;
        }

        static void printTypedef(const Token *tok, std::ostream& out) {
            int indent = 0;
            while (tok && (indent > 0 || tok->str() != MatchCompiler::makeConstString(";"))) {
                if (tok->str() == MatchCompiler::makeConstString("{"))
                    ++indent;
                else if (tok->str() == MatchCompiler::makeConstString("}"))
                    --indent;
                out << " " << tok->str();
                tok = tok->next();
            }
            out << "\n";
        }
    };
}

void Tokenizer::simplifyTypedef()
{
    // Simplify global typedefs that are not redefined with the fast 1-pass simplification.
    // Then use the slower old typedef simplification.
    std::map<std::string, int> numberOfTypedefs;
    for (Token* tok = list.front(); tok; tok = tok->next()) {
        if (tok->str() == MatchCompiler::makeConstString("typedef")) {
            TypedefSimplifier ts(tok);
            if (!ts.fail())
                numberOfTypedefs[ts.name()]++;
            continue;
        }
    }

    int indentlevel = 0;
    std::map<std::string, TypedefSimplifier> typedefs;
    for (Token* tok = list.front(); tok; tok = tok->next()) {
        if (!tok->isName()) {
            if (tok->str()[0] == '{')
                ++indentlevel;
            else if (tok->str()[0] == '}')
                --indentlevel;
            continue;
        }

        if (indentlevel == 0 && tok->str() == MatchCompiler::makeConstString("typedef")) {
            TypedefSimplifier ts(tok);
            if (!ts.fail() && numberOfTypedefs[ts.name()] == 1 &&
                (numberOfTypedefs.find(ts.getTypedefToken()->strAt(1)) == numberOfTypedefs.end() || ts.getTypedefToken()->strAt(2) == MatchCompiler::makeConstString("("))) {
                if (mSettings.severity.isEnabled(Severity::portability) && ts.isInvalidConstFunctionType(typedefs))
                    invalidConstFunctionTypeError(tok->next());
                typedefs.emplace(ts.name(), ts);
                if (!ts.isStructEtc())
                    tok = ts.endToken();
            }
            continue;
        }

        auto it = typedefs.find(tok->str());
        if (it != typedefs.end() && it->second.canReplace(tok)) {
            std::set<std::string> r;
            while (it != typedefs.end() && r.insert(tok->str()).second) {
                it->second.replace(tok);
                it = typedefs.find(tok->str());
            }
        } else if (tok->str() == MatchCompiler::makeConstString("enum")) {
            while (match103(tok))
                tok = tok->next();
            if (!tok)
                break;
            if (tok->str() == MatchCompiler::makeConstString("{"))
                tok = tok->link();
        }
    }

    if (!typedefs.empty())
    {
        // remove typedefs
        for (auto &t: typedefs) {
            if (t.second.replaceFailed()) {
                syntaxError(t.second.getTypedefToken());
            } else {
                const Token* const typedefToken = t.second.getTypedefToken();
                TypedefInfo typedefInfo;
                typedefInfo.name = t.second.name();
                typedefInfo.filename = list.file(typedefToken);
                typedefInfo.lineNumber = typedefToken->linenr();
                typedefInfo.column = typedefToken->column();
                typedefInfo.used = t.second.isUsed();
                typedefInfo.isFunctionPointer = match104(t.second.nameToken());
                mTypedefInfo.push_back(std::move(typedefInfo));

                t.second.removeDeclaration();
            }
        }

        while (match105(list.front()))
            list.front()->deleteThis();
    }

    simplifyTypedefCpp();
}

static Token* simplifyTypedefCopyTokens(Token* to, const Token* fromStart, const Token* toEnd, const Token* location) {
    Token* ret = TokenList::copyTokens(to, fromStart, toEnd);
    for (Token* tok = to->next(); tok != ret->next(); tok = tok->next()) {
        tok->linenr(location->linenr());
        tok->column(location->column());
        tok->isSimplifiedTypedef(true);
    }
    return ret;
}

static Token* simplifyTypedefInsertToken(Token* tok, const std::string& str, const Token* location) {
    tok = tok->insertToken(str);
    tok->linenr(location->linenr());
    tok->column(location->column());
    tok->isSimplifiedTypedef(true);
    return tok;
}

// TODO: rename - it is not C++ specific
void Tokenizer::simplifyTypedefCpp()
{
    const bool cpp = isCPP();
    bool isNamespace = false;
    std::string className, fullClassName;
    bool hasClass = false;
    bool goback = false;

    // add global namespace
    std::vector<Space> spaceInfo(1);

    const std::time_t maxTime = mSettings.typedefMaxTime > 0 ? std::time(nullptr) + mSettings.typedefMaxTime: 0;
    const bool doProgress = (mSettings.reportProgress != -1) && !list.getFiles().empty();

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (doProgress)
            mErrorLogger.reportProgress(list.getFiles()[0], "Tokenize (typedef)", tok->progressValue());

        if (Settings::terminated())
            return;

        if (maxTime > 0 && std::time(nullptr) > maxTime) {
            if (mSettings.debugwarnings) {
                ErrorMessage::FileLocation loc(list.getFiles()[0], 0, 0);
                ErrorMessage errmsg({std::move(loc)},
                                    "",
                                    Severity::debug,
                                    "Typedef simplification instantiation maximum time exceeded",
                                    "typedefMaxTime",
                                    Certainty::normal);
                mErrorLogger.reportErr(errmsg);
            }
            return;
        }

        if (goback) {
            //jump back once, see the comment at the end of the function
            goback = false;
            tok = tok->previous();
        }

        if (tok->str() != MatchCompiler::makeConstString("typedef")) {
            if (match106(tok)) {
                // Skip typedefs inside parentheses (#2453 and #4002)
                tok = tok->next();
            } else if (match107(tok) &&
                       (!tok->previous() || tok->strAt(-1) != MatchCompiler::makeConstString("enum"))) {
                isNamespace = (tok->str() == MatchCompiler::makeConstString("namespace"));
                hasClass = true;
                className = tok->strAt(1);
                const Token *tok1 = tok->next();
                fullClassName = className;
                while (match108(tok1)) {
                    tok1 = tok1->tokAt(2);
                    fullClassName += " :: " + tok1->str();
                }
            } else if (hasClass && tok->str() == MatchCompiler::makeConstString(";")) {
                hasClass = false;
            } else if (hasClass && tok->str() == MatchCompiler::makeConstString("{")) {
                if (!isNamespace)
                    spaceInfo.back().recordTypes.insert(fullClassName);

                Space info;
                info.isNamespace = isNamespace;
                info.className = className;
                info.bodyEnd = tok->link();
                info.bodyEnd2 = tok->link();
                spaceInfo.push_back(std::move(info));

                hasClass = false;
            } else if (spaceInfo.size() > 1 && tok->str() == MatchCompiler::makeConstString("}") && spaceInfo.back().bodyEnd == tok) {
                spaceInfo.pop_back();
            }
            continue;
        }

        // pull struct, union, enum or class definition out of typedef
        // use typedef name for unnamed struct, union, enum or class
        const Token* tokClass = tok->next();
        while (match23(tokClass))
            tokClass = tokClass->next();
        if (match109(tokClass)) {
            Token *tok1 = splitDefinitionFromTypedef(tok, &mUnnamedCount);
            if (!tok1)
                continue;
            tok = tok1;
        }

        /** @todo add support for union */
        if (match110(tok->next()) && tok->strAt(2) == tok->strAt(3)) {
            tok->deleteNext(3);
            tok->deleteThis();
            if (tok->next())
                tok->deleteThis();
            //now the next token to process is 'tok', not 'tok->next()';
            goback = true;
            continue;
        }

        Token *typeName;
        Token *typeStart = nullptr;
        Token *typeEnd = nullptr;
        Token *argStart = nullptr;
        Token *argEnd = nullptr;
        Token *arrayStart = nullptr;
        Token *arrayEnd = nullptr;
        Token *specStart = nullptr;
        Token *specEnd = nullptr;
        Token *typeDef = tok;
        Token *argFuncRetStart = nullptr;
        Token *argFuncRetEnd = nullptr;
        Token *funcStart = nullptr;
        Token *funcEnd = nullptr;
        Token *tokOffset = tok->next();
        bool function = false;
        bool functionPtr = false;
        bool functionRetFuncPtr = false;
        bool functionPtrRetFuncPtr = false;
        bool ptrToArray = false;
        bool refToArray = false;
        bool ptrMember = false;
        bool typeOf = false;
        const Token *namespaceStart = nullptr;
        Token *namespaceEnd = nullptr;

        // check for invalid input
        if (!tokOffset || tokOffset->isControlFlowKeyword())
            syntaxError(tok);

        if (tokOffset->str() == MatchCompiler::makeConstString("::")) {
            typeStart = tokOffset;
            tokOffset = tokOffset->next();

            while (match111(tokOffset))
                tokOffset = tokOffset->tokAt(2);

            typeEnd = tokOffset;

            if (match12(tokOffset))
                tokOffset = tokOffset->next();
        } else if (match111(tokOffset)) {
            typeStart = tokOffset;

            do {
                tokOffset = tokOffset->tokAt(2);
            } while (match111(tokOffset));

            typeEnd = tokOffset;

            if (match12(tokOffset))
                tokOffset = tokOffset->next();
        } else if (match12(tokOffset)) {
            typeStart = tokOffset;

            while (match112(tokOffset) ||
                   (tokOffset->next() && tokOffset->next()->isStandardType() && !match47(tokOffset->next())))
                tokOffset = tokOffset->next();

            typeEnd = tokOffset;
            if (!match47(tokOffset->next()))
                tokOffset = tokOffset->next();

            while (match12(tokOffset) &&
                   (tokOffset->isStandardType() || match113(tokOffset)) &&
                   !match47(tokOffset->next())) {
                typeEnd = tokOffset;
                tokOffset = tokOffset->next();
            }

            bool atEnd = false;
            while (!atEnd) {
                if (tokOffset && tokOffset->str() == MatchCompiler::makeConstString("::")) {
                    typeEnd = tokOffset;
                    tokOffset = tokOffset->next();
                }

                if (match12(tokOffset) &&
                    tokOffset->next() && !match114(tokOffset->next())) {
                    typeEnd = tokOffset;
                    tokOffset = tokOffset->next();
                } else if (match115(tokOffset)) {
                    typeEnd = tokOffset;
                    tokOffset = tokOffset->next();
                    atEnd = true;
                } else
                    atEnd = true;
            }
        } else
            continue; // invalid input

        // check for invalid input
        if (!tokOffset)
            syntaxError(tok);

        // check for template
        if (!isC() && tokOffset->str() == MatchCompiler::makeConstString("<")) {
            typeEnd = tokOffset->findClosingBracket();

            while (typeEnd && match116(typeEnd->next()))
                typeEnd = typeEnd->tokAt(2);

            if (!typeEnd) {
                // internal error
                return;
            }

            while (match23(typeEnd->next()))
                typeEnd = typeEnd->next();

            tok = typeEnd;
            tokOffset = tok->next();
        }

        std::list<std::string> pointers;
        // check for pointers and references
        while (match117(tokOffset)) {
            pointers.push_back(tokOffset->str());
            tokOffset = tokOffset->next();
        }

        // check for invalid input
        if (!tokOffset)
            syntaxError(tok);

        if (tokOffset->isName() && !tokOffset->isKeyword()) {
            // found the type name
            typeName = tokOffset;
            tokOffset = tokOffset->next();

            // check for array
            while (tokOffset && tokOffset->str() == MatchCompiler::makeConstString("[")) {
                if (!arrayStart)
                    arrayStart = tokOffset;
                arrayEnd = tokOffset->link();
                tokOffset = arrayEnd->next();
            }

            // check for end or another
            if (match118(tokOffset))
                tok = tokOffset;

            // or a function typedef
            else if (tokOffset && tokOffset->str() == MatchCompiler::makeConstString("(")) {
                Token *tokOffset2 = nullptr;
                if (match119(tokOffset)) {
                    tokOffset2 = tokOffset->next();
                    if (tokOffset2->str() == MatchCompiler::makeConstString("typename"))
                        tokOffset2 = tokOffset2->next();
                    while (match111(tokOffset2))
                        tokOffset2 = tokOffset2->tokAt(2);
                }

                // unhandled typedef, skip it and continue
                if (typeName->str() == MatchCompiler::makeConstString("void")) {
                    unsupportedTypedef(typeDef);
                    tok = deleteInvalidTypedef(typeDef);
                    if (tok == list.front())
                        //now the next token to process is 'tok', not 'tok->next()';
                        goback = true;
                    continue;
                }

                // function pointer
                if (match120(tokOffset2)) {
                    // name token wasn't a name, it was part of the type
                    typeEnd = typeEnd->next();
                    functionPtr = true;
                    funcStart = funcEnd = tokOffset2; // *
                    tokOffset = tokOffset2->tokAt(3); // (
                    typeName = tokOffset->tokAt(-2);
                    argStart = tokOffset;
                    argEnd = tokOffset->link();
                    tok = argEnd->next();
                }

                // function
                else if (TokenList::isFunctionHead(tokOffset->link(), ";,")) {
                    function = true;
                    if (tokOffset->link()->strAt(1) == MatchCompiler::makeConstString("const")) {
                        specStart = tokOffset->link()->next();
                        specEnd = specStart;
                    }
                    argStart = tokOffset;
                    argEnd = tokOffset->link();
                    tok = argEnd->next();
                    if (specStart)
                        tok = tok->next();
                }

                // syntax error
                else
                    syntaxError(tok);
            }

            // unhandled typedef, skip it and continue
            else {
                unsupportedTypedef(typeDef);
                tok = deleteInvalidTypedef(typeDef);
                if (tok == list.front())
                    //now the next token to process is 'tok', not 'tok->next()';
                    goback = true;
                continue;
            }
        }

        // typeof: typedef typeof ( ... ) type;
        else if (match121(tokOffset->previous()) &&
                 match122(tokOffset->link())) {
            argStart = tokOffset;
            argEnd = tokOffset->link();
            typeName = tokOffset->link()->next();
            tok = typeName->next();
            typeOf = true;
        }

        // function: typedef ... ( ... type )( ... );
        //           typedef ... (( ... type )( ... ));
        //           typedef ... ( * ( ... type )( ... ));
        else if (tokOffset->str() == MatchCompiler::makeConstString("(") && (
                     (tokOffset->link() && match123(tokOffset->link()->previous()) &&
                      match124(tokOffset->link()->linkAt(1))) ||
                     (match125(tokOffset) &&
                      tokOffset->next() && match123(tokOffset->linkAt(1)->previous()) &&
                      match126(tokOffset->linkAt(1)->linkAt(1))) ||
                     (match127(tokOffset) &&
                      tokOffset->linkAt(2) && match123(tokOffset->linkAt(2)->previous()) &&
                      match126(tokOffset->linkAt(2)->linkAt(1))))) {
            if (tokOffset->strAt(1) == MatchCompiler::makeConstString("("))
                tokOffset = tokOffset->next();
            else if (match127(tokOffset)) {
                pointers.emplace_back("*");
                tokOffset = tokOffset->tokAt(2);
            }

            if (tokOffset->link()->strAt(-2) == MatchCompiler::makeConstString("*"))
                functionPtr = true;
            else
                function = true;
            funcStart = tokOffset->next();
            tokOffset = tokOffset->link();
            funcEnd = tokOffset->tokAt(-2);
            typeName = tokOffset->previous();
            argStart = tokOffset->next();
            argEnd = tokOffset->linkAt(1);
            if (!argEnd)
                syntaxError(argStart);
            const Token* tok2 = argEnd->next();
            while (tok2 && (tok2->isKeyword() || tok2->str() == MatchCompiler::makeConstString(")")))
                tok2 = tok2->next();
            if (!match128(tok2))
                syntaxError(tok2);

            tok = argEnd->next();
            Token *spec = tok;
            if (match23(spec)) {
                specStart = spec;
                specEnd = spec;
                while (match23(spec->next())) {
                    specEnd = spec->next();
                    spec = specEnd;
                }
                tok = specEnd->next();
            }
            if (!tok)
                syntaxError(specEnd);

            if (tok->str() == MatchCompiler::makeConstString(")"))
                tok = tok->next();
        }

        else if (match129(tokOffset)) {
            function = true;
            if (tokOffset->link()->next()) {
                tok = tokOffset->link()->next();
                tokOffset = tokOffset->tokAt(2);
                typeName = tokOffset->previous();
                argStart = tokOffset;
                argEnd = tokOffset->link();
            } else {
                // internal error
                continue;
            }
        }

        // pointer to function returning pointer to function
        else if (match130(tokOffset) &&
                 match131(tokOffset->linkAt(6)) &&
                 match132(tokOffset->linkAt(6)->linkAt(2))) {
            functionPtrRetFuncPtr = true;

            tokOffset = tokOffset->tokAt(6);
            typeName = tokOffset->tokAt(-2);
            argStart = tokOffset;
            argEnd = tokOffset->link();
            if (!argEnd)
                syntaxError(arrayStart);

            argFuncRetStart = argEnd->tokAt(2);
            argFuncRetEnd = argFuncRetStart->link();
            if (!argFuncRetEnd)
                syntaxError(argFuncRetStart);

            tok = argFuncRetEnd->next();
        }

        // function returning pointer to function
        else if (match133(tokOffset) &&
                 match131(tokOffset->linkAt(3)) &&
                 match132(tokOffset->linkAt(3)->linkAt(2))) {
            functionRetFuncPtr = true;

            tokOffset = tokOffset->tokAt(3);
            typeName = tokOffset->previous();
            argStart = tokOffset;
            argEnd = tokOffset->link();

            argFuncRetStart = argEnd->tokAt(2);
            if (!argFuncRetStart)
                syntaxError(tokOffset);

            argFuncRetEnd = argFuncRetStart->link();
            if (!argFuncRetEnd)
                syntaxError(tokOffset);

            tok = argFuncRetEnd->next();
        } else if (match134(tokOffset)) {
            functionRetFuncPtr = true;

            tokOffset = tokOffset->tokAt(5);
            typeName = tokOffset->tokAt(-2);
            argStart = tokOffset;
            argEnd = tokOffset->link();
            if (!argEnd)
                syntaxError(arrayStart);

            argFuncRetStart = argEnd->tokAt(2);
            if (!argFuncRetStart)
                syntaxError(tokOffset);

            argFuncRetEnd = argFuncRetStart->link();
            if (!argFuncRetEnd)
                syntaxError(tokOffset);

            tok = argFuncRetEnd->next();
        }

        // pointer/reference to array
        else if (match135(tokOffset)) {
            ptrToArray = (tokOffset->strAt(1) == MatchCompiler::makeConstString("*"));
            refToArray = !ptrToArray;
            tokOffset = tokOffset->tokAt(2);
            typeName = tokOffset;
            arrayStart = tokOffset->tokAt(2);
            arrayEnd = arrayStart->link();
            if (!arrayEnd)
                syntaxError(arrayStart);

            tok = arrayEnd->next();
        }

        // pointer to class member
        else if (match136(tokOffset)) {
            tokOffset = tokOffset->tokAt(2);
            namespaceStart = tokOffset->previous();
            namespaceEnd = tokOffset;
            ptrMember = true;
            tokOffset = tokOffset->tokAt(2);
            typeName = tokOffset;
            tok = tokOffset->tokAt(2);
        }

        // unhandled typedef, skip it and continue
        else {
            unsupportedTypedef(typeDef);
            tok = deleteInvalidTypedef(typeDef);
            if (tok == list.front())
                //now the next token to process is 'tok', not 'tok->next()';
                goback = true;
            continue;
        }

        bool done = false;
        bool ok = true;

        TypedefInfo typedefInfo;
        typedefInfo.name = typeName->str();
        typedefInfo.filename = list.file(typeName);
        typedefInfo.lineNumber = typeName->linenr();
        typedefInfo.column = typeName->column();
        typedefInfo.used = false;
        typedefInfo.isFunctionPointer = match104(typeName);
        mTypedefInfo.push_back(std::move(typedefInfo));

        while (!done) {
            std::string pattern = typeName->str();
            int scope = 0;
            bool simplifyType = false;
            bool inMemberFunc = false;
            int memberScope = 0;
            bool globalScope = false;
            int classLevel = spaceInfo.size();
            bool inTypeDef = false;
            bool inEnum = false;
            std::string removed;
            std::string classPath;
            for (size_t i = 1; i < spaceInfo.size(); ++i) {
                if (!classPath.empty())
                    classPath += " :: ";
                classPath += spaceInfo[i].className;
            }

            for (Token *tok2 = tok; tok2; tok2 = tok2->next()) {
                if (Settings::terminated())
                    return;

                removed.clear();

                if (match137(tok2))
                    inTypeDef = true;

                if (inTypeDef && match128(tok2))
                    inTypeDef = false;

                // Check for variable declared with the same name
                if (!inTypeDef && spaceInfo.size() == 1 && match24(tok2->previous()) &&
                    !tok2->previous()->isKeyword()) {
                    Token* varDecl = tok2;
                    while (match117(varDecl))
                        varDecl = varDecl->next();
                    if (match138(varDecl) && varDecl->str() == typeName->str()) {
                        // Skip to the next closing brace
                        if (match139(varDecl)) { // is argument variable
                            tok2 = varDecl->linkAt(2)->next();
                        } else {
                            tok2 = varDecl;
                            while (tok2 && !match41(tok2)) {
                                if (match140(tok2))
                                    tok2 = tok2->link();
                                tok2 = tok2->next();
                            }
                        }
                        if (!tok2)
                            break;
                        continue;
                    }
                }

                if (tok2->link()) { // Pre-check for performance
                    // check for end of scope
                    if (tok2->str() == MatchCompiler::makeConstString("}")) {
                        // check for end of member function
                        if (inMemberFunc) {
                            --memberScope;
                            if (memberScope == 0)
                                inMemberFunc = false;
                        }
                        inEnum = false;

                        if (classLevel > 1 && tok2 == spaceInfo[classLevel - 1].bodyEnd2) {
                            --classLevel;
                            pattern.clear();

                            for (std::size_t i = classLevel; i < spaceInfo.size(); ++i)
                                pattern += (spaceInfo[i].className + " :: ");

                            pattern += typeName->str();
                        } else {
                            if (scope == 0 && !(classLevel > 1 && tok2 == spaceInfo[classLevel - 1].bodyEnd))
                                break;
                            scope = std::max(scope - 1, 0);
                        }
                    }

                    // check for member functions
                    else if (cpp && tok2->str() == MatchCompiler::makeConstString("(") && TokenList::isFunctionHead(tok2, "{:")) {
                        const Token *func = tok2->previous();

                        /** @todo add support for multi-token operators */
                        if (func->strAt(-1) == MatchCompiler::makeConstString("operator"))
                            func = func->previous();

                        if (!func->previous())
                            syntaxError(func);

                        // check for qualifier
                        if (match36(func->tokAt(-2))) {
                            int offset = -2;
                            while (match36(func->tokAt(offset - 2)))
                                offset -= 2;
                            // check for available and matching class name
                            if (spaceInfo.size() > 1 && classLevel < spaceInfo.size() &&
                                func->strAt(offset) == spaceInfo[classLevel].className) {
                                memberScope = 0;
                                inMemberFunc = true;
                            }
                        }
                    }

                    // check for entering a new scope
                    else if (tok2->str() == MatchCompiler::makeConstString("{")) {
                        // check for entering a new namespace
                        if (cpp) {
                            if (tok2->strAt(-2) == MatchCompiler::makeConstString("namespace")) {
                                if (classLevel < spaceInfo.size() &&
                                    spaceInfo[classLevel].isNamespace &&
                                    spaceInfo[classLevel].className == tok2->strAt(-1)) {
                                    spaceInfo[classLevel].bodyEnd2 = tok2->link();
                                    ++classLevel;
                                    pattern.clear();
                                    for (std::size_t i = classLevel; i < spaceInfo.size(); ++i)
                                        pattern += spaceInfo[i].className + " :: ";

                                    pattern += typeName->str();
                                }
                                ++scope;
                            }
                            if (isEnumStart(tok2))
                                inEnum = true;
                        }

                        // keep track of scopes within member function
                        if (inMemberFunc)
                            ++memberScope;

                        ++scope;
                    }
                }

                // check for operator typedef
                /** @todo add support for multi-token operators */
                else if (cpp &&
                         tok2->str() == MatchCompiler::makeConstString("operator") &&
                         tok2->next() &&
                         tok2->strAt(1) == typeName->str() &&
                         tok2->linkAt(2) &&
                         tok2->strAt(2) == MatchCompiler::makeConstString("(") &&
                         match141(tok2->linkAt(2))) {
                    // check for qualifier
                    if (tok2->strAt(-1) == MatchCompiler::makeConstString("::")) {
                        // check for available and matching class name
                        if (spaceInfo.size() > 1 && classLevel < spaceInfo.size() &&
                            tok2->strAt(-2) == spaceInfo[classLevel].className) {
                            tok2 = tok2->next();
                            simplifyType = true;
                        }
                    }
                }

                else if (match142(tok2->previous())) {
                    // don't replace names in struct/class definition
                }

                // check for typedef that can be substituted
                else if ((tok2->isNameOnly() || (tok2->isName() && (tok2->isExpandedMacro() || tok2->isInline() || tok2->isExternC()))) &&
                         (Token::simpleMatch(tok2, pattern.c_str(), pattern.size()) ||
                          (inMemberFunc && tok2->str() == typeName->str()))) {
                    // member function class variables don't need qualification
                    if (!(inMemberFunc && tok2->str() == typeName->str()) && pattern.find("::") != std::string::npos) { // has a "something ::"
                        Token *start = tok2;
                        int count = 0;
                        int back = classLevel - 1;
                        bool good = true;
                        // check for extra qualification
                        while (back >= 1) {
                            Token *qualificationTok = start->tokAt(-2);
                            if (!match111(qualificationTok))
                                break;
                            if (qualificationTok->str() == spaceInfo[back].className) {
                                start = qualificationTok;
                                back--;
                                count++;
                            } else {
                                good = false;
                                break;
                            }
                        }
                        // check global namespace
                        if (good && back == 1 && start->strAt(-1) == MatchCompiler::makeConstString("::"))
                            good = false;

                        if (good) {
                            // remove any extra qualification if present
                            while (count) {
                                if (!removed.empty())
                                    removed.insert(0, " ");
                                removed.insert(0, tok2->strAt(-2) + " " + tok2->strAt(-1));
                                tok2->tokAt(-3)->deleteNext(2);
                                --count;
                            }

                            // remove global namespace if present
                            if (tok2->strAt(-1) == MatchCompiler::makeConstString("::")) {
                                removed.insert(0, ":: ");
                                tok2->tokAt(-2)->deleteNext();
                                globalScope = true;
                            }

                            // remove qualification if present
                            for (std::size_t i = classLevel; i < spaceInfo.size(); ++i) {
                                if (!removed.empty())
                                    removed += " ";
                                removed += (tok2->str() + " " + tok2->strAt(1));
                                tok2->deleteThis();
                                tok2->deleteThis();
                            }
                            simplifyType = true;
                        }
                    } else {
                        if (tok2->strAt(-1) == MatchCompiler::makeConstString("::")) {
                            int relativeSpaceInfoSize = spaceInfo.size();
                            Token * tokBeforeType = tok2->previous();
                            while (relativeSpaceInfoSize > 1 &&
                                   tokBeforeType && tokBeforeType->str() == MatchCompiler::makeConstString("::") &&
                                   tokBeforeType->strAt(-1) == spaceInfo[relativeSpaceInfoSize-1].className) {
                                tokBeforeType = tokBeforeType->tokAt(-2);
                                --relativeSpaceInfoSize;
                            }
                            if (tokBeforeType && tokBeforeType->str() != MatchCompiler::makeConstString("::")) {
                                Token::eraseTokens(tokBeforeType, tok2);
                                simplifyType = true;
                            }
                        } else if (match143(tok2->previous())) {
                            tok2 = tok2->next();
                        } else if (duplicateTypedef(tok2, typeName, typeDef)) {
                            // skip to end of scope if not already there
                            if (tok2->str() != MatchCompiler::makeConstString("}")) {
                                while (tok2->next()) {
                                    if (tok2->strAt(1) == MatchCompiler::makeConstString("{"))
                                        tok2 = tok2->linkAt(1)->previous();
                                    else if (tok2->strAt(1) == MatchCompiler::makeConstString("}"))
                                        break;

                                    tok2 = tok2->next();
                                }
                            }
                        } else if (match144(tok2->tokAt(-2))) {
                            // Ticket #5868: Don't substitute variable names
                        } else if (tok2->strAt(-1) != MatchCompiler::makeConstString(".")) {
                            simplifyType = (TypedefSimplifier::canReplaceStatic(tok2) != 0);
                        }
                    }
                }

                simplifyType = simplifyType && (!inEnum || !match145(tok2->next()));
                simplifyType = simplifyType && !(match146(tok2->next()) && match147(typeEnd));

                if (simplifyType) {
                    mTypedefInfo.back().used = true;

                    // can't simplify 'operator functionPtr ()' and 'functionPtr operator ... ()'
                    if (functionPtr && (tok2->strAt(-1) == MatchCompiler::makeConstString("operator") ||
                                        (tok2->next() && tok2->strAt(1) == MatchCompiler::makeConstString("operator")))) {
                        simplifyType = false;
                        tok2 = tok2->next();
                        continue;
                    }

                    // There are 2 categories of typedef substitutions:
                    // 1. variable declarations that preserve the variable name like
                    //    global, local, and function parameters
                    // 2. not variable declarations that have no name like derived
                    //    classes, casts, operators, and template parameters

                    // try to determine which category this substitution is
                    bool inCast = false;
                    bool inTemplate = false;
                    bool inOperator = false;
                    bool inSizeof = false;

                    const bool sameStartEnd = (typeStart == typeEnd);

                    // check for derived class: class A : some_typedef {
                    const bool isDerived = match148(tok2->previous());

                    // check for cast: (some_typedef) A or static_cast<some_typedef>(A)
                    // todo: check for more complicated casts like: (const some_typedef *)A
                    if ((tok2->strAt(-1) == MatchCompiler::makeConstString("(") && tok2->strAt(1) == MatchCompiler::makeConstString(")") && tok2->strAt(-2) != MatchCompiler::makeConstString("sizeof")) ||
                        (tok2->strAt(-1) == MatchCompiler::makeConstString("<") && match149(tok2->next())) ||
                        match150(tok2->tokAt(-2)))
                        inCast = true;

                    // check for template parameters: t<some_typedef> t1
                    else if (match151(tok2->previous()) &&
                             match152(tok2->next()))
                        inTemplate = true;

                    else if (match153(tok2->tokAt(-2)))
                        inSizeof = true;

                    // check for operator
                    if (tok2->strAt(-1) == MatchCompiler::makeConstString("operator") ||
                        match154(tok2->tokAt(-2)))
                        inOperator = true;

                    if (typeStart->str() == MatchCompiler::makeConstString("typename") && tok2->strAt(-1)==MatchCompiler::makeConstString("typename")) {
                        // Remove one typename if it is already contained in the goal
                        typeStart = typeStart->next();
                    }

                    // skip over class or struct in derived class declaration
                    bool structRemoved = false;
                    if ((isDerived || inTemplate) && match155(typeStart)) {
                        if (typeStart->str() == MatchCompiler::makeConstString("struct"))
                            structRemoved = true;
                        typeStart = typeStart->next();
                    }
                    if (match156(typeStart) && match36(tok2))
                        typeStart = typeStart->next();

                    if (sameStartEnd)
                        typeEnd = typeStart;

                    // Is this a "T()" expression where T is a pointer type?
                    const bool isPointerTypeCall = !inOperator && match157(tok2) && !pointers.empty();

                    // start substituting at the typedef name by replacing it with the type
                    const Token* location = tok2;
                    for (Token* tok3 = typeStart; tok3 && (tok3->str() != MatchCompiler::makeConstString(";")); tok3 = tok3->next())
                        tok3->isSimplifiedTypedef(true);
                    if (isPointerTypeCall) {
                        tok2->deleteThis();
                        tok2 = simplifyTypedefInsertToken(tok2, "0", location);
                        simplifyTypedefInsertToken(tok2->next(), "0", location);
                    }
                    if (match158(tok2->tokAt(-1)) && tok2->strAt(-1) == typeStart->str())
                        tok2->deletePrevious();

                    if (cpp && match159(tok2->previous())) {
                        tok2->previous()->str("typedef");
                        tok2->insertToken(tok2->str());
                    }
                    tok2->str(typeStart->str());

                    // restore qualification if it was removed
                    if (match158(typeStart) || structRemoved) {
                        if (structRemoved)
                            tok2 = tok2->previous();

                        if (globalScope) {
                            tok2 = simplifyTypedefInsertToken(tok2, "::", location);
                        }

                        for (std::size_t i = classLevel; i < spaceInfo.size(); ++i) {
                            tok2 = simplifyTypedefInsertToken(tok2, spaceInfo[i].className, location);
                            tok2 = simplifyTypedefInsertToken(tok2, "::", location);
                        }
                    }

                    // add some qualification back if needed
                    Token *start = tok2;
                    std::string removed1 = removed;
                    std::string::size_type idx = removed1.rfind(" ::");

                    if (idx != std::string::npos)
                        removed1.resize(idx);
                    if (removed1 == classPath && !removed1.empty()) {
                        for (auto it = spaceInfo.crbegin(); it != spaceInfo.crend(); ++it) {
                            if (it->recordTypes.find(start->str()) != it->recordTypes.end()) {
                                std::string::size_type spaceIdx = 0;
                                std::string::size_type startIdx = 0;
                                while ((spaceIdx = removed1.find(' ', startIdx)) != std::string::npos) {
                                    simplifyTypedefInsertToken(tok2->previous(), removed1.substr(startIdx, spaceIdx - startIdx), location);
                                    startIdx = spaceIdx + 1;
                                }
                                simplifyTypedefInsertToken(tok2->previous(), removed1.substr(startIdx), location);
                                simplifyTypedefInsertToken(tok2->previous(), "::", location);
                                break;
                            }
                            idx = removed1.rfind(" ::");
                            if (idx == std::string::npos)
                                break;

                            removed1.resize(idx);
                        }
                    }
                    Token* constTok = match37(tok2->previous()) ? tok2->previous() : nullptr;
                    // add remainder of type
                    tok2 = simplifyTypedefCopyTokens(tok2, typeStart->next(), typeEnd, location);

                    if (!pointers.empty()) {
                        for (const std::string &p : pointers)
                            // cppcheck-suppress useStlAlgorithm
                            tok2 = simplifyTypedefInsertToken(tok2, p, location);
                        if (constTok && !functionPtr) {
                            tok2 = simplifyTypedefInsertToken(tok2, "const", location);
                            constTok->deleteThis();
                            location = constTok;
                        }
                    }

                    if (funcStart && funcEnd) {
                        tok2 = simplifyTypedefInsertToken(tok2, "(", location);
                        Token *paren = tok2;
                        tok2 = simplifyTypedefCopyTokens(tok2, funcStart, funcEnd, location);

                        if (!inCast)
                            tok2 = processFunc(tok2, inOperator);

                        if (!tok2)
                            break;

                        while (match160(tok2))
                            tok2 = tok2->linkAt(1);

                        tok2 = simplifyTypedefInsertToken(tok2, ")", location);
                        Token::createMutualLinks(tok2, paren);

                        tok2 = simplifyTypedefCopyTokens(tok2, argStart, argEnd, location);

                        if (specStart) {
                            Token *spec = specStart;
                            tok2 = simplifyTypedefInsertToken(tok2, spec->str(), location);
                            while (spec != specEnd) {
                                spec = spec->next();
                                tok2 = simplifyTypedefInsertToken(tok2, spec->str(), location);
                            }
                        }
                    }

                    else if (functionPtr || function) {
                        // don't add parentheses around function names because it
                        // confuses other simplifications
                        bool needParen = true;
                        if (!inTemplate && function && tok2->next() && tok2->strAt(1) != MatchCompiler::makeConstString("*"))
                            needParen = false;
                        if (needParen) {
                            tok2 = simplifyTypedefInsertToken(tok2, "(", location);
                        }
                        Token *tok3 = tok2;
                        if (namespaceStart) {
                            const Token *tok4 = namespaceStart;

                            while (tok4 != namespaceEnd) {
                                tok2 = simplifyTypedefInsertToken(tok2, tok4->str(), location);
                                tok4 = tok4->next();
                            }
                            tok2 = simplifyTypedefInsertToken(tok2, namespaceEnd->str(), location);
                        }
                        if (functionPtr) {
                            tok2 = simplifyTypedefInsertToken(tok2, "*", location);
                        }

                        if (!inCast)
                            tok2 = processFunc(tok2, inOperator);

                        if (needParen) {
                            if (!tok2)
                                syntaxError(nullptr);

                            tok2 = simplifyTypedefInsertToken(tok2, ")", location);
                            Token::createMutualLinks(tok2, tok3);
                        }
                        if (!tok2)
                            syntaxError(nullptr);

                        tok2 = simplifyTypedefCopyTokens(tok2, argStart, argEnd, location);
                        if (inTemplate) {
                            tok2 = tok2->next();
                        }

                        if (specStart) {
                            Token *spec = specStart;
                            tok2 = simplifyTypedefInsertToken(tok2, spec->str(), location);
                            while (spec != specEnd) {
                                spec = spec->next();
                                tok2 = simplifyTypedefInsertToken(tok2, spec->str(), location);
                            }
                        }
                    } else if (functionRetFuncPtr || functionPtrRetFuncPtr) {
                        tok2 = simplifyTypedefInsertToken(tok2, "(", location);
                        Token *tok3 = tok2;
                        tok2 = simplifyTypedefInsertToken(tok2, "*", location);

                        Token * tok4 = nullptr;
                        if (functionPtrRetFuncPtr) {
                            tok2 = simplifyTypedefInsertToken(tok2, "(", location);
                            tok4 = tok2;
                            tok2 = simplifyTypedefInsertToken(tok2, "*", location);
                        }

                        // skip over variable name if there
                        if (!inCast) {
                            if (!tok2 || !tok2->next())
                                syntaxError(nullptr);

                            if (tok2->strAt(1) != MatchCompiler::makeConstString(")"))
                                tok2 = tok2->next();
                        }

                        if (tok4 && functionPtrRetFuncPtr) {
                            tok2 = simplifyTypedefInsertToken(tok2,")", location);
                            Token::createMutualLinks(tok2, tok4);
                        }

                        tok2 = simplifyTypedefCopyTokens(tok2, argStart, argEnd, location);

                        tok2 = simplifyTypedefInsertToken(tok2, ")", location);
                        Token::createMutualLinks(tok2, tok3);

                        tok2 = simplifyTypedefCopyTokens(tok2, argFuncRetStart, argFuncRetEnd, location);
                    } else if (ptrToArray || refToArray) {
                        tok2 = simplifyTypedefInsertToken(tok2, "(", location);
                        Token *tok3 = tok2;

                        if (ptrToArray)
                            tok2 = simplifyTypedefInsertToken(tok2, "*", location);
                        else
                            tok2 = simplifyTypedefInsertToken(tok2, "&", location);

                        bool hasName = false;
                        // skip over name
                        if (tok2->next() && tok2->strAt(1) != MatchCompiler::makeConstString(")") && tok2->strAt(1) != MatchCompiler::makeConstString(",") &&
                            tok2->strAt(1) != MatchCompiler::makeConstString(">")) {
                            hasName = true;
                            if (tok2->strAt(1) != MatchCompiler::makeConstString("("))
                                tok2 = tok2->next();

                            // check for function and skip over args
                            if (tok2 && tok2->next() && tok2->strAt(1) == MatchCompiler::makeConstString("("))
                                tok2 = tok2->linkAt(1);

                            // check for array
                            if (tok2 && tok2->next() && tok2->strAt(1) == MatchCompiler::makeConstString("["))
                                tok2 = tok2->linkAt(1);
                        }

                        simplifyTypedefInsertToken(tok2, ")", location);
                        Token::createMutualLinks(tok2->next(), tok3);

                        if (!hasName)
                            tok2 = tok2->next();
                    } else if (ptrMember) {
                        if (match161(tok2)) {
                            tok2 = simplifyTypedefInsertToken(tok2, "*", location);
                        } else {
                            // This is the case of casting operator.
                            // Name is not available, and () should not be
                            // inserted
                            const bool castOperator = inOperator && match162(tok2);
                            Token *openParenthesis = nullptr;

                            if (!castOperator) {
                                tok2 = simplifyTypedefInsertToken(tok2, "(", location);

                                openParenthesis = tok2;
                            }

                            const Token *tok4 = namespaceStart;

                            while (tok4 != namespaceEnd) {
                                tok2 = simplifyTypedefInsertToken(tok2, tok4->str(), location);
                                tok4 = tok4->next();
                            }
                            tok2 = simplifyTypedefInsertToken(tok2, namespaceEnd->str(), location);

                            tok2 = simplifyTypedefInsertToken(tok2, "*", location);

                            if (openParenthesis) {
                                // Skip over name, if any
                                if (match24(tok2->next()))
                                    tok2 = tok2->next();

                                tok2 = simplifyTypedefInsertToken(tok2, ")", location);

                                Token::createMutualLinks(tok2, openParenthesis);
                            }
                        }
                    } else if (typeOf) {
                        tok2 = simplifyTypedefCopyTokens(tok2, argStart, argEnd, location);
                    } else if (match50(tok2)) {
                        while (match160(tok2)) {
                            tok2 = tok2->linkAt(1);
                        }
                        tok2 = tok2->previous();
                    }

                    if (arrayStart && arrayEnd) {
                        do {
                            if (!tok2->next())
                                syntaxError(tok2); // can't recover so quit

                            if (!inCast && !inSizeof && !inTemplate)
                                tok2 = tok2->next();

                            if (tok2->str() == MatchCompiler::makeConstString("const"))
                                tok2 = tok2->next();

                            // reference or pointer to array?
                            if (match163(tok2)) {
                                tok2 = tok2->previous();
                                Token *tok3 = simplifyTypedefInsertToken(tok2, "(", location);

                                // handle missing variable name
                                if (match164(tok3))
                                    tok2 = tok3->tokAt(3);
                                else if (match165(tok2->tokAt(3)))
                                    tok2 = tok2->tokAt(2);
                                else if (match147(tok2->tokAt(3)))
                                    tok2 = tok2->tokAt(2);
                                else
                                    tok2 = tok2->tokAt(3);
                                if (!tok2)
                                    syntaxError(nullptr);

                                while (tok2->strAt(1) == MatchCompiler::makeConstString("::"))
                                    tok2 = tok2->tokAt(2);

                                // skip over function parameters
                                if (tok2->str() == MatchCompiler::makeConstString("("))
                                    tok2 = tok2->link();

                                if (tok2->strAt(1) == MatchCompiler::makeConstString("("))
                                    tok2 = tok2->linkAt(1);

                                // skip over const/noexcept
                                while (match166(tok2->next())) {
                                    tok2 = tok2->next();
                                    if (match167(tok2->next()))
                                        tok2 = tok2->tokAt(3);
                                }

                                tok2 = simplifyTypedefInsertToken(tok2, ")", location);
                                Token::createMutualLinks(tok2, tok3);
                            }

                            if (!tok2->next())
                                syntaxError(tok2); // can't recover so quit

                            // skip over array dimensions
                            while (tok2->strAt(1) == MatchCompiler::makeConstString("["))
                                tok2 = tok2->linkAt(1);

                            tok2 = simplifyTypedefCopyTokens(tok2, arrayStart, arrayEnd, location);
                            if (!tok2->next())
                                syntaxError(tok2);

                            if (match76(tok2) && tok2->next()->isSplittedVarDeclEq())
                                tok2->deleteNext(2);

                            if (tok2->str() == MatchCompiler::makeConstString("=")) {
                                if (tok2->strAt(1) == MatchCompiler::makeConstString("{"))
                                    tok2 = tok2->linkAt(1)->next();
                                else if (tok2->strAt(1).at(0) == '\"')
                                    tok2 = tok2->tokAt(2);
                            }
                        } while (match168(tok2));
                    }

                    simplifyType = false;
                }
                if (!tok2)
                    break;
            }

            if (!tok)
                syntaxError(nullptr);

            if (tok->str() == MatchCompiler::makeConstString(";"))
                done = true;
            else if (tok->str() == MatchCompiler::makeConstString(",")) {
                arrayStart = nullptr;
                arrayEnd = nullptr;
                tokOffset = tok->next();
                pointers.clear();

                while (match34(tokOffset)) {
                    pointers.push_back(tokOffset->str());
                    tokOffset = tokOffset->next();
                }

                if (match12(tokOffset)) {
                    typeName = tokOffset;
                    tokOffset = tokOffset->next();

                    if (tokOffset && tokOffset->str() == MatchCompiler::makeConstString("[")) {
                        arrayStart = tokOffset;

                        for (;;) {
                            while (tokOffset->next() && !match118(tokOffset->next()))
                                tokOffset = tokOffset->next();

                            if (!tokOffset->next())
                                return; // invalid input
                            if (tokOffset->strAt(1) == MatchCompiler::makeConstString(";"))
                                break;
                            if (tokOffset->str() == MatchCompiler::makeConstString("]"))
                                break;
                            tokOffset = tokOffset->next();
                        }

                        arrayEnd = tokOffset;
                        tokOffset = tokOffset->next();
                    }

                    if (match118(tokOffset))
                        tok = tokOffset;
                    else {
                        // we encountered a typedef we don't support yet so just continue
                        done = true;
                        ok = false;
                    }
                } else {
                    // we encountered a typedef we don't support yet so just continue
                    done = true;
                    ok = false;
                }
            } else {
                // something is really wrong (internal error)
                done = true;
                ok = false;
            }
        }

        if (ok) {
            // remove typedef
            Token::eraseTokens(typeDef, tok);

            if (typeDef != list.front()) {
                tok = typeDef->previous();
                tok->deleteNext();
                //no need to remove last token in the list
                if (tok->tokAt(2))
                    tok->deleteNext();
            } else {
                list.front()->deleteThis();
                //no need to remove last token in the list
                if (list.front()->next())
                    list.front()->deleteThis();
                tok = list.front();
                //now the next token to process is 'tok', not 'tok->next()';
                goback = true;
            }
        }
    }
}

namespace {
    struct ScopeInfo3 {
        enum Type : std::uint8_t { Global, Namespace, Record, MemberFunction, Other };
        ScopeInfo3() : parent(nullptr), type(Global), bodyStart(nullptr), bodyEnd(nullptr) {}
        ScopeInfo3(ScopeInfo3 *parent_, Type type_, std::string name_, const Token *bodyStart_, const Token *bodyEnd_)
            : parent(parent_), type(type_), name(std::move(name_)), bodyStart(bodyStart_), bodyEnd(bodyEnd_) {
            if (name.empty())
                return;
            fullName = name;
            ScopeInfo3 *scope = parent;
            while (scope && scope->parent) {
                if (scope->name.empty())
                    break;
                fullName = scope->name + " :: " + fullName;
                scope = scope->parent;
            }
        }
        ScopeInfo3 *parent;
        std::list<ScopeInfo3> children;
        Type type;
        std::string fullName;
        std::string name;
        const Token * bodyStart;
        const Token * bodyEnd;
        std::set<std::string> usingNamespaces;
        std::set<std::string> recordTypes;
        std::set<std::string> baseTypes;

        ScopeInfo3 *addChild(Type scopeType, std::string scopeName, const Token *bodyStartToken, const Token *bodyEndToken) {
            children.emplace_back(this, scopeType, std::move(scopeName), bodyStartToken, bodyEndToken);
            return &children.back();
        }

        bool hasChild(const std::string &childName) const {
            return std::any_of(children.cbegin(), children.cend(), [&](const ScopeInfo3& child) {
                return child.name == childName;
            });
        }

        const ScopeInfo3 * findInChildren(const std::string & scope) const {
            for (const auto & child : children) {
                if (child.type == Record && (child.name == scope || child.fullName == scope))
                    return &child;

                const ScopeInfo3 * temp = child.findInChildren(scope);
                if (temp)
                    return temp;
            }
            return nullptr;
        }

        const ScopeInfo3 * findScope(const std::string & scope) const {
            const ScopeInfo3 * tempScope = this;
            while (tempScope) {
                // check children
                auto it = std::find_if(tempScope->children.cbegin(), tempScope->children.cend(), [&](const ScopeInfo3& child) {
                    return &child != this && child.type == Record && (child.name == scope || child.fullName == scope);
                });
                if (it != tempScope->children.end())
                    return &*it;
                // check siblings for same name
                if (tempScope->parent) {
                    for (const auto &sibling : tempScope->parent->children) {
                        if (sibling.name == tempScope->name && &sibling != this) {
                            const ScopeInfo3 * temp = sibling.findInChildren(scope);
                            if (temp)
                                return temp;
                        }
                    }
                }
                tempScope = tempScope->parent;
            }
            return nullptr;
        }

        bool findTypeInBase(const std::string &scope) const {
            if (scope.empty())
                return false;
            // check in base types first
            if (baseTypes.find(scope) != baseTypes.end())
                return true;
            // check in base types base types
            for (const std::string & base : baseTypes) {
                const ScopeInfo3 * baseScope = findScope(base);
                // bail on uninstantiated recursive template
                if (baseScope == this)
                    return false;
                if (baseScope && baseScope->fullName == scope)
                    return true;
                if (baseScope && baseScope->findTypeInBase(scope))
                    return true;
            }
            return false;
        }

        ScopeInfo3 * findScope(const ScopeInfo3 * scope) {
            if (scope->bodyStart == bodyStart)
                return this;
            for (auto & child : children) {
                ScopeInfo3 * temp = child.findScope(scope);
                if (temp)
                    return temp;
            }
            return nullptr;
        }
    };

    void setScopeInfo(Token *tok, ScopeInfo3 *&scopeInfo, bool debug=false)
    {
        if (!tok)
            return;
        if (tok->str() == MatchCompiler::makeConstString("{") && scopeInfo->parent && tok == scopeInfo->bodyStart)
            return;
        if (tok->str() == MatchCompiler::makeConstString("}")) {
            if (scopeInfo->parent && tok == scopeInfo->bodyEnd)
                scopeInfo = scopeInfo->parent;
            else {
                // Try to find parent scope
                ScopeInfo3 *parent = scopeInfo->parent;
                while (parent && parent->bodyEnd != tok)
                    parent = parent->parent;
                if (parent) {
                    scopeInfo = parent;
                    if (debug)
                        throw std::runtime_error("Internal error: unmatched }");
                }
            }
            return;
        }
        if (!match169(tok)) {
            // check for using namespace
            if (match170(tok)) {
                const Token * tok1 = tok->tokAt(2);
                std::string nameSpace;
                while (tok1 && tok1->str() != MatchCompiler::makeConstString(";")) {
                    if (!nameSpace.empty())
                        nameSpace += " ";
                    nameSpace += tok1->str();
                    tok1 = tok1->next();
                }
                scopeInfo->usingNamespaces.insert(std::move(nameSpace));
            }
            // check for member function
            else if (tok->str() == MatchCompiler::makeConstString("{")) {
                bool added = false;
                Token *tok1 = tok;
                while (match171(tok1->previous()))
                    tok1 = tok1->previous();
                if (tok1->previous() && (tok1->strAt(-1) == MatchCompiler::makeConstString(")") || tok->strAt(-1) == MatchCompiler::makeConstString("}"))) {
                    tok1 = tok1->linkAt(-1);
                    if (match172(tok1->previous())) {
                        tok1 = tok1->previous();
                        while (match171(tok1->previous()))
                            tok1 = tok1->previous();
                        if (tok1->strAt(-1) != MatchCompiler::makeConstString(")"))
                            return;
                        tok1 = tok1->linkAt(-1);
                    } else {
                        while (match173(tok1->tokAt(-2))) {
                            tok1 = tok1->tokAt(-2);
                            if (tok1->strAt(-1) != MatchCompiler::makeConstString(")") && tok1->strAt(-1) != MatchCompiler::makeConstString("}"))
                                return;
                            tok1 = tok1->linkAt(-1);
                        }
                    }
                    if (tok1->strAt(-1) == MatchCompiler::makeConstString(">"))
                        tok1 = tok1->previous()->findOpeningBracket();
                    if (tok1 && (match108(tok1->tokAt(-3)) ||
                                 match174(tok1->tokAt(-4)))) {
                        tok1 = tok1->tokAt(-2);
                        if (tok1->str() == MatchCompiler::makeConstString("~"))
                            tok1 = tok1->previous();
                        std::string scope = tok1->strAt(-1);
                        while (match175(tok1->tokAt(-2))) {
                            scope = tok1->strAt(-3) + " :: " + scope;
                            tok1 = tok1->tokAt(-2);
                        }
                        scopeInfo = scopeInfo->addChild(ScopeInfo3::MemberFunction, std::move(scope), tok, tok->link());
                        added = true;
                    }
                    // inline member function
                    else if ((scopeInfo->type == ScopeInfo3::Record || scopeInfo->type == ScopeInfo3::Namespace) && tok1 && match56(tok1->tokAt(-1))) {
                        std::string scope = scopeInfo->name + "::" + tok1->strAt(-1);
                        scopeInfo = scopeInfo->addChild(ScopeInfo3::MemberFunction, std::move(scope), tok, tok->link());
                        added = true;
                    }
                }

                if (!added)
                    scopeInfo = scopeInfo->addChild(ScopeInfo3::Other, "", tok, tok->link());
            }
            return;
        }

        const bool record = match176(tok);
        tok = tok->next();
        std::string classname = tok->str();
        while (match108(tok)) {
            tok = tok->tokAt(2);
            classname += " :: " + tok->str();
        }

        // add record type to scope info
        if (record)
            scopeInfo->recordTypes.insert(classname);
        tok = tok->next();

        // skip template parameters
        if (tok && tok->str() == MatchCompiler::makeConstString("<")) {
            tok = tok->findClosingBracket();
            if (tok)
                tok = tok->next();
        }

        // get base class types
        std::set<std::string> baseTypes;
        if (tok && tok->str() == MatchCompiler::makeConstString(":")) {
            do {
                tok = tok->next();
                while (match177(tok))
                    tok = tok->next();
                std::string base;
                while (tok && !match178(tok)) {
                    if (!base.empty())
                        base += ' ';
                    base += tok->str();
                    tok = tok->next();
                    // add template parameters
                    if (tok && tok->str() == MatchCompiler::makeConstString("<")) {
                        const Token* endTok = tok->findClosingBracket();
                        if (endTok) {
                            endTok = endTok->next();
                            while (tok != endTok) {
                                base += tok->str();
                                tok = tok->next();
                            }
                        }
                    }
                }
                baseTypes.insert(std::move(base));
            } while (tok && !match20(tok));
        }

        if (tok && tok->str() == MatchCompiler::makeConstString("{")) {
            scopeInfo = scopeInfo->addChild(record ? ScopeInfo3::Record : ScopeInfo3::Namespace, std::move(classname), tok, tok->link());
            scopeInfo->baseTypes = std::move(baseTypes);
        }
    }

    Token *findSemicolon(Token *tok)
    {
        int level = 0;

        for (; tok && (level > 0 || tok->str() != MatchCompiler::makeConstString(";")); tok = tok->next()) {
            if (tok->str() == MatchCompiler::makeConstString("{"))
                ++level;
            else if (level > 0 && tok->str() == MatchCompiler::makeConstString("}"))
                --level;
        }

        return tok;
    }

    bool usingMatch(
        const Token *nameToken,
        const std::string &scope,
        Token *&tok,
        const std::string &scope1,
        const ScopeInfo3 *currentScope,
        const ScopeInfo3 *memberClassScope)
    {
        Token *tok1 = tok;

        if (tok1 && tok1->str() != nameToken->str())
            return false;

        // skip this using
        if (tok1 == nameToken) {
            tok = findSemicolon(tok1);
            return false;
        }

        // skip other using with this name
        if (tok1->strAt(-1) == MatchCompiler::makeConstString("using")) {
            // fixme: this is wrong
            // skip to end of scope
            if (currentScope->bodyEnd)
                tok = const_cast<Token*>(currentScope->bodyEnd->previous());
            return false;
        }

        if (match179(tok1->tokAt(-1))) {
            // fixme
            return false;
        }

        if (match180(tok1->tokAt(-2))) {
            return false;
        }

        if (match56(tok1) && TokenList::isFunctionHead(tok1->next(), "{;:")) {
            if (match24(tok1->previous()) && !tok1->previous()->isControlFlowKeyword())
                return false;
            if (match181(tok1->previous()) && tok1->linkAt(-1))
                return false;
            if (match72(tok1->previous())) {
                const Token* prev = tok1->previous();
                while (match66(prev) && !prev->isControlFlowKeyword())
                    prev = prev->previous();
                if (match181(prev) && tok1->linkAt(-1))
                    return false;
                if (match182(prev))
                    return false;
            }
        }

        // get qualification
        std::string qualification;
        const Token* tok2 = tok1;
        std::string::size_type index = scope.size();
        std::string::size_type new_index = std::string::npos;
        bool match = true;
        while (match36(tok2->tokAt(-2)) && !tok2->tokAt(-2)->isKeyword()) {
            std::string last;
            if (match && !scope1.empty()) {
                new_index = scope1.rfind(' ', index - 1);
                if (new_index != std::string::npos)
                    last = scope1.substr(new_index, index - new_index);
                else if (!qualification.empty())
                    last.clear();
                else
                    last = scope1;
            } else
                match = false;
            if (match && tok2->strAt(-2) == last)
                index = new_index;
            else {
                if (!qualification.empty())
                    qualification = " :: " + qualification;
                qualification = tok2->strAt(-2) + qualification;
            }
            tok2 = tok2->tokAt(-2);
        }

        std::string fullScope1 = scope1;
        if (!scope1.empty() && !qualification.empty())
            fullScope1 += " :: ";
        fullScope1 += qualification;

        if (scope == fullScope1)
            return true;

        const ScopeInfo3 *scopeInfo = memberClassScope ? memberClassScope : currentScope;

        // check in base types
        if (qualification.empty() && scopeInfo->findTypeInBase(scope))
            return true;

        // check using namespace
        const ScopeInfo3 * tempScope = scopeInfo;
        while (tempScope) {
            //if (!tempScope->parent->usingNamespaces.empty()) {
            const std::set<std::string>& usingNS = tempScope->usingNamespaces;
            if (!usingNS.empty()) {
                if (qualification.empty()) {
                    if (usingNS.find(scope) != usingNS.end())
                        return true;
                } else {
                    const std::string suffix = " :: " + qualification;
                    if (std::any_of(usingNS.cbegin(), usingNS.cend(), [&](const std::string& ns) {
                        return scope == ns + suffix;
                    }))
                        return true;
                }
            }
            tempScope = tempScope->parent;
        }

        std::string newScope1 = scope1;

        // scopes didn't match so try higher scopes
        index = newScope1.size();
        while (!newScope1.empty()) {
            const std::string::size_type separator = newScope1.rfind(" :: ", index - 1);
            if (separator != std::string::npos)
                newScope1.resize(separator);
            else
                newScope1.clear();

            std::string newFullScope1 = newScope1;
            if (!newScope1.empty() && !qualification.empty())
                newFullScope1 += " :: ";
            newFullScope1 += qualification;

            if (scope == newFullScope1)
                return true;
        }

        return false;
    }

    std::string memberFunctionScope(const Token *tok)
    {
        std::string qualification;
        const Token *qualTok = tok->strAt(-2) == MatchCompiler::makeConstString("~") ? tok->tokAt(-4) : tok->tokAt(-3);
        while (match111(qualTok)) {
            if (!qualification.empty())
                qualification = " :: " + qualification;
            qualification = qualTok->str() + qualification;
            qualTok = qualTok->tokAt(-2);
        }
        return qualification;
    }

    const Token * memberFunctionEnd(const Token *tok)
    {
        if (tok->str() != MatchCompiler::makeConstString("("))
            return nullptr;
        const Token *end = tok->link()->next();
        while (end) {
            if (end->str() == MatchCompiler::makeConstString("{") && !match173(end->tokAt(-2)))
                return end;
            if (end->str() == MatchCompiler::makeConstString(";"))
                break;
            end = end->next();
        }
        return nullptr;
    }
} // namespace

bool Tokenizer::isMemberFunction(const Token *openParen)
{
    return (match183(openParen->tokAt(-2)) ||
            match184(openParen->tokAt(-3))) &&
           TokenList::isFunctionHead(openParen, "{:");
}

static bool scopesMatch(const std::string &scope1, const std::string &scope2, const ScopeInfo3 *globalScope)
{
    if (scope1.empty() || scope2.empty())
        return false;

    // check if scopes match
    if (scope1 == scope2)
        return true;

    // check if scopes only differ by global qualification
    if (scope1 == (":: " + scope2)) {
        std::string::size_type end = scope2.find_first_of(' ');
        if (end == std::string::npos)
            end = scope2.size();
        if (globalScope->hasChild(scope2.substr(0, end)))
            return true;
    } else if (scope2 == (":: " + scope1)) {
        std::string::size_type end = scope1.find_first_of(' ');
        if (end == std::string::npos)
            end = scope1.size();
        if (globalScope->hasChild(scope1.substr(0, end)))
            return true;
    }

    return false;
}

static unsigned int tokDistance(const Token* tok1, const Token* tok2) { // use when index() is not available yet
    unsigned int dist = 0;
    const Token* tok = tok1;
    while (tok != tok2) {
        ++dist;
        tok = tok->next();
    }
    return dist;
}

static const Token* skipConstVolatileBackwards(const Token* tok) {
    while (match23(tok))
        tok = tok->previous();
    return tok;
}

bool Tokenizer::simplifyUsing()
{
    if (!isCPP() || mSettings.standards.cpp < Standards::CPP11)
        return false;

    // simplify using N::x; to using x = N::x;
    for (Token* tok = list.front(); tok; tok = tok->next()) {
        if (!match185(tok))
            continue;
        const Token* ns = tok->tokAt(tok->strAt(1) == MatchCompiler::makeConstString("::") ? 2 : 1);
        if (ns->isKeyword())
            continue;
        Token* end = tok->tokAt(3);
        while (end && !match186(end)) {
            if (end->str() == MatchCompiler::makeConstString("<")) // skip template args
                end = end->findClosingBracket();
            else
                end = end->next();
        }
        if (!end)
            continue;
        if (!end->tokAt(-1)->isNameOnly() || end->tokAt(-2)->isLiteral()) // e.g. operator=, operator""sv
            continue;
        tok->insertToken(end->strAt(-1))->insertToken("=")->isSimplifiedTypedef(true);
        if (end->str() == MatchCompiler::makeConstString(",")) { // comma-separated list
            end->str(";");
            end->insertToken("using");
        }
        tok = end;
    }

    const unsigned int maxReplacementTokens = 1000; // limit the number of tokens we replace

    bool substitute = false;
    ScopeInfo3 scopeInfo;
    ScopeInfo3 *currentScope = &scopeInfo;
    struct Using {
        Using(Token *start, Token *end) : startTok(start), endTok(end) {}
        Token *startTok;
        Token *endTok;
    };
    std::list<Using> usingList;

    const bool doProgress = (mSettings.reportProgress != -1) && !list.getFiles().empty();

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (doProgress)
            mErrorLogger.reportProgress(list.getFiles()[0], "Tokenize (using)", tok->progressValue());

        if (Settings::terminated())
            return substitute;

        if (match187(tok)) {
            Token *bodyStart = tok;
            while (match188(bodyStart)) {
                if (bodyStart->str() == MatchCompiler::makeConstString("<"))
                    bodyStart = bodyStart->findClosingBracket();
                bodyStart = bodyStart ? bodyStart->next() : nullptr;
            }
            if (match1(bodyStart))
                tok = bodyStart->link();
            continue;
        }

        if (match189(tok) ||
            match170(tok)) {
            try {
                setScopeInfo(tok, currentScope, mSettings.debugwarnings);
            } catch (const std::runtime_error &) {
                reportError(tok, Severity::debug, "simplifyUsingUnmatchedBodyEnd",
                            "simplifyUsing: unmatched body end");
            }
            continue;
        }

        // skip template declarations
        if (match190(tok)) {
            // add template record type to scope info
            const Token *end = tok->next()->findClosingBracket();
            if (end && match176(end->next()))
                currentScope->recordTypes.insert(end->strAt(2));

            Token *declEndToken = TemplateSimplifier::findTemplateDeclarationEnd(tok);
            if (declEndToken)
                tok = declEndToken;
            continue;
        }

        // look for non-template type aliases
        if (!(tok->strAt(-1) != MatchCompiler::makeConstString(">") &&
              (match191(tok) ||
               (match192(tok) &&
                match193(tok->linkAt(2))))))
            continue;

        const std::string& name = tok->strAt(1);
        const Token *nameToken = tok->next();
        std::string scope = currentScope->fullName;
        Token *usingStart = tok;
        Token *start;
        if (tok->strAt(2) == MatchCompiler::makeConstString("=")) {
            if (currentScope->type == ScopeInfo3::Record && tok->tokAt(2)->isSimplifiedTypedef())  // don't simplify within class definition
                continue;
            start = tok->tokAt(3);
        }
        else
            start = tok->linkAt(2)->tokAt(3);
        Token *usingEnd = findSemicolon(start);
        if (!usingEnd)
            continue;

        // Move struct defined in using out of using.
        // using T = struct t { }; => struct t { }; using T = struct t;
        // fixme: this doesn't handle attributes
        if (match194(start)) {
            Token *structEnd = start->tokAt(1);
            const bool hasName = match24(structEnd);

            // skip over name if present
            if (hasName)
                structEnd = structEnd->next();

            // skip over base class information
            if (structEnd->str() == MatchCompiler::makeConstString(":")) {
                structEnd = structEnd->next(); // skip over ":"
                while (structEnd && structEnd->str() != MatchCompiler::makeConstString("{"))
                    structEnd = structEnd->next();
                if (!structEnd)
                    continue;
            }

            // use link to go to end
            structEnd = structEnd->link();

            // add ';' after end of struct
            structEnd->insertToken(";");

            // add name for anonymous struct
            if (!hasName) {
                std::string newName;
                if (structEnd->strAt(2) == MatchCompiler::makeConstString(";"))
                    newName = name;
                else
                    newName = "Unnamed" + std::to_string(mUnnamedCount++);
                TokenList::copyTokens(structEnd->next(), tok, start);
                structEnd->tokAt(5)->insertToken(newName);
                start->insertToken(newName);
            } else
                TokenList::copyTokens(structEnd->next(), tok, start->next());

            // add using after end of struct
            usingStart = structEnd->tokAt(2);
            nameToken = usingStart->next();
            if (usingStart->strAt(2) == MatchCompiler::makeConstString("="))
                start = usingStart->tokAt(3);
            else
                start = usingStart->linkAt(2)->tokAt(3);
            usingEnd = findSemicolon(start);

            // delete original using before struct
            tok->deleteThis();
            tok->deleteThis();
            tok->deleteThis();
            tok = usingStart;
        }

        // remove 'typename' and 'template'
        else if (start->str() == MatchCompiler::makeConstString("typename")) {
            start->deleteThis();
            Token *temp = start;
            while (match36(temp))
                temp = temp->tokAt(2);
            if (match195(temp))
                temp->deleteThis();
        }

        if (usingEnd)
            tok = usingEnd;

        if (match7(start))
            start = start->next();

        // Unfortunately we have to start searching from the beginning
        // of the token stream because templates are instantiated at
        // the end of the token stream and it may be used before then.
        ScopeInfo3 scopeInfo1;
        ScopeInfo3 *currentScope1 = &scopeInfo1;
        Token *startToken = list.front();
        const Token *endToken = nullptr;
        bool inMemberFunc = false;
        const ScopeInfo3 * memberFuncScope = nullptr;
        const Token * memberFuncEnd = nullptr;

        // We can limit the search to the current function when the type alias
        // is defined in that function.
        if (currentScope->type == ScopeInfo3::Other ||
            currentScope->type == ScopeInfo3::MemberFunction) {
            scopeInfo1 = scopeInfo;
            currentScope1 = scopeInfo1.findScope(currentScope);
            if (!currentScope1)
                return substitute; // something bad happened
            startToken = usingEnd->next();
            endToken = currentScope->bodyEnd->next();
            if (currentScope->type == ScopeInfo3::MemberFunction) {
                const ScopeInfo3 * temp = currentScope->findScope(currentScope->fullName);
                if (temp) {
                    inMemberFunc = true;
                    memberFuncScope = temp;
                    memberFuncEnd = endToken;
                }
            }
        }

        bool isTypedefInfoAdded = false; // TODO should we add a separate mUsingInfo?

        std::string scope1 = currentScope1->fullName;
        bool skip = false; // don't erase type aliases we can't parse
        Token *enumOpenBrace = nullptr;
        for (Token* tok1 = startToken; !skip && tok1 && tok1 != endToken; tok1 = tok1->next()) {
            // skip enum body
            if (tok1 && tok1 == enumOpenBrace) {
                tok1 = tok1->link();
                enumOpenBrace = nullptr;
                continue;
            }

            if ((match189(tok1) && tok1->strAt(-1) != MatchCompiler::makeConstString("using")) ||
                match170(tok1)) {
                try {
                    setScopeInfo(tok1, currentScope1, mSettings.debugwarnings);
                } catch (const std::runtime_error &) {
                    reportError(tok1, Severity::debug, "simplifyUsingUnmatchedBodyEnd",
                                "simplifyUsing: unmatched body end");
                }
                scope1 = currentScope1->fullName;
                if (inMemberFunc && memberFuncEnd && tok1 == memberFuncEnd) {
                    inMemberFunc = false;
                    memberFuncScope = nullptr;
                    memberFuncEnd = nullptr;
                }
                continue;
            }

            // skip template definitions
            if (match190(tok1)) {
                Token *declEndToken = TemplateSimplifier::findTemplateDeclarationEnd(tok1);
                if (declEndToken)
                    tok1 = declEndToken;
                continue;
            }

            // check for enum with body
            if (tok1->str() == MatchCompiler::makeConstString("enum")) {
                if (match187(tok1))
                    tok1 = tok1->next();
                Token *defStart = tok1;
                while (match2(defStart))
                    defStart = defStart->next();
                if (match1(defStart))
                    enumOpenBrace = defStart;
                continue;
            }

            // check for member function and adjust scope
            if (isMemberFunction(tok1)) {
                if (!scope1.empty())
                    scope1 += " :: ";
                scope1 += memberFunctionScope(tok1);
                const ScopeInfo3 * temp = currentScope1->findScope(scope1);
                if (temp) {
                    const Token *end = memberFunctionEnd(tok1);
                    if (end) {
                        inMemberFunc = true;
                        memberFuncScope = temp;
                        memberFuncEnd = end;
                    }
                }
                continue;
            }
            if (inMemberFunc && memberFuncScope) {
                if (!usingMatch(nameToken, scope, tok1, scope1, currentScope1, memberFuncScope))
                    continue;
            } else if (!usingMatch(nameToken, scope, tok1, scope1, currentScope1, nullptr))
                continue;

            if (!isTypedefInfoAdded && match56(tok1)) {
                isTypedefInfoAdded = true;
                TypedefInfo usingInfo;
                usingInfo.name = name;
                usingInfo.filename = list.file(nameToken);
                usingInfo.lineNumber = nameToken->linenr();
                usingInfo.column = nameToken->column();
                usingInfo.used = true;
                usingInfo.isFunctionPointer = false;
                mTypedefInfo.push_back(std::move(usingInfo));
            }

            const auto nReplace = tokDistance(start, usingEnd);
            if (nReplace > maxReplacementTokens) {
                simplifyUsingError(usingStart, usingEnd);
                continue;
            }

            // remove the qualification
            std::string fullScope = scope;
            std::string removed;
            while (match36(tok1->tokAt(-2)) && !tok1->tokAt(-2)->isKeyword()) {
                removed = (tok1->strAt(-2) + " :: ") + removed;
                if (fullScope == tok1->strAt(-2)) {
                    tok1->deletePrevious();
                    tok1->deletePrevious();
                    break;
                }
                const std::string::size_type idx = fullScope.rfind("::");

                if (idx == std::string::npos)
                    break;

                if (tok1->strAt(-2) == fullScope.substr(idx + 3)) {
                    tok1->deletePrevious();
                    tok1->deletePrevious();
                    fullScope.resize(idx - 1);
                } else
                    break;
            }

            // remove global namespace if present
            if (tok1->strAt(-1) == MatchCompiler::makeConstString("::")) {
                removed.insert(0, ":: ");
                tok1->deletePrevious();
            }

            Token * arrayStart = nullptr;

            // parse the type
            Token *type = start;
            if (type->str() == MatchCompiler::makeConstString("::")) {
                type = type->next();
                while (match111(type))
                    type = type->tokAt(2);
                if (match12(type))
                    type = type->next();
            } else if (match111(type)) {
                do {
                    type = type->tokAt(2);
                } while (match111(type));
                if (match12(type))
                    type = type->next();
            } else if (match12(type)) {
                while (match196(type) ||
                       (type->next() && type->next()->isStandardType()))
                    type = type->next();

                type = type->next();

                while (match12(type) &&
                       (type->isStandardType() || match113(type))) {
                    type = type->next();
                }

                bool atEnd = false;
                while (!atEnd) {
                    if (type && type->str() == MatchCompiler::makeConstString("::")) {
                        type = type->next();
                    }

                    if (match12(type) &&
                        type->next() && !match197(type->next())) {
                        type = type->next();
                    } else if (match115(type)) {
                        type = type->next();
                        atEnd = true;
                    } else
                        atEnd = true;
                }
            } else
                syntaxError(type);

            // check for invalid input
            if (!type)
                syntaxError(tok1);

            // check for template
            if (type->str() == MatchCompiler::makeConstString("<")) {
                type = type->findClosingBracket();

                while (type && match116(type->next()))
                    type = type->tokAt(2);

                if (!type) {
                    syntaxError(tok1);
                }

                while (match23(type->next()))
                    type = type->next();

                type = type->next();
            }

            // check for pointers and references
            std::list<std::string> pointers;
            while (match117(type)) {
                pointers.push_back(type->str());
                type = type->next();
            }

            // check for array
            if (type && type->str() == MatchCompiler::makeConstString("[")) {
                do {
                    if (!arrayStart)
                        arrayStart = type;

                    bool atEnd = false;
                    while (!atEnd) {
                        while (type->next() && !match118(type->next())) {
                            type = type->next();
                        }

                        if (!type->next())
                            syntaxError(type); // invalid input
                        else if (type->strAt(1) == MatchCompiler::makeConstString(";"))
                            atEnd = true;
                        else if (type->str() == MatchCompiler::makeConstString("]"))
                            atEnd = true;
                        else
                            type = type->next();
                    }

                    type = type->next();
                } while (type && type->str() == MatchCompiler::makeConstString("["));
            }

            // make sure we are in a good state
            if (!tok1 || !tok1->next())
                break; // bail

            Token* after = tok1->next();
            // check if type was parsed
            if (type && type == usingEnd) {
                // check for array syntax and add type around variable
                if (arrayStart) {
                    if (match24(tok1->next())) {
                        TokenList::copyTokens(tok1->next(), arrayStart, usingEnd->previous());
                        TokenList::copyTokens(tok1, start, arrayStart->previous());
                        tok1->deleteThis();
                        substitute = true;
                    }
                } else {
                    // add some qualification back if needed
                    std::string removed1 = std::move(removed);
                    std::string::size_type idx = removed1.rfind(" ::");
                    if (idx != std::string::npos)
                        removed1.resize(idx);
                    if (scopesMatch(removed1, scope, &scopeInfo1)) {
                        ScopeInfo3 * tempScope = currentScope;
                        while (tempScope->parent) {
                            if (tempScope->recordTypes.find(start->str()) != tempScope->recordTypes.end()) {
                                std::string::size_type spaceIdx = 0;
                                std::string::size_type startIdx = 0;
                                while ((spaceIdx = removed1.find(' ', startIdx)) != std::string::npos) {
                                    tok1->previous()->insertToken(removed1.substr(startIdx, spaceIdx - startIdx));
                                    startIdx = spaceIdx + 1;
                                }
                                tok1->previous()->insertToken(removed1.substr(startIdx));
                                tok1->previous()->insertToken("::");
                                break;
                            }
                            idx = removed1.rfind(" ::");
                            if (idx == std::string::npos)
                                break;

                            removed1.resize(idx);
                            tempScope = tempScope->parent;
                        }
                    }

                    // Is this a "T(...)" expression where T is a pointer type?
                    if (match58(tok1) && !pointers.empty() && !match198(skipConstVolatileBackwards(tok1->tokAt(-1)))) {
                        tok1->tokAt(1)->str("(");
                        tok1->linkAt(1)->str(")");
                        if (tok1->linkAt(1) == tok1->tokAt(2)) { // T() or T{}
                            Token* tok2 = tok1->linkAt(1);
                            tok1->deleteThis();
                            TokenList::copyTokens(tok1, start, usingEnd->previous());
                            tok2->insertToken("0");
                            after = tok2->next();
                        }
                        else { // functional-style cast
                            Token* tok2 = tok1->linkAt(1);
                            tok1->originalName(tok1->str());
                            tok1->isSimplifiedTypedef(true);
                            tok1->str("(");
                            Token* tok3 = TokenList::copyTokens(tok1, start, usingEnd->previous());
                            tok3->insertToken(")");
                            Token::createMutualLinks(tok1, tok3->next());
                            after = tok2->next();
                        }
                    }
                    else { // just replace simple type aliases
                        TokenList::copyTokens(tok1, start, usingEnd->previous());
                        tok1->deleteThis();
                    }
                    substitute = true;
                }
            } else {
                skip = true;
                simplifyUsingError(usingStart, usingEnd);
            }
            tok1 = after->previous();
        }

        if (!skip)
            usingList.emplace_back(usingStart, usingEnd);
    }

    // delete all used type alias definitions
    for (auto it = usingList.rbegin(); it != usingList.rend(); ++it) {
        Token *usingStart = it->startTok;
        Token *usingEnd = it->endTok;
        if (usingStart->previous()) {
            Token::eraseTokens(usingStart->previous(), usingEnd->next());
        } else {
            if (usingEnd->next()) {
                Token::eraseTokens(usingStart, usingEnd->next());
                usingStart->deleteThis();
            } else {
                // this is the only code being checked so leave ';'
                Token::eraseTokens(usingStart, usingEnd);
                usingStart->deleteThis();
            }
        }
    }

    return substitute;
}

void Tokenizer::simplifyUsingError(const Token* usingStart, const Token* usingEnd)
{
    if (mSettings.debugwarnings) {
        std::string str;
        for (const Token *tok = usingStart; tok && tok != usingEnd; tok = tok->next()) {
            if (!str.empty())
                str += ' ';
            str += tok->str();
        }
        str += " ;";
        std::list<const Token *> callstack(1, usingStart);
        mErrorLogger.reportErr(ErrorMessage(callstack, &list, Severity::debug, "simplifyUsing",
                                            "Failed to parse \'" + str + "\'. The checking continues anyway.", Certainty::normal));
    }
}

bool Tokenizer::simplifyTokens1(const std::string &configuration, int fileIndex)
{
    // Fill the map mTypeSize..
    fillTypeSizes();

    mConfiguration = configuration;

    if (mTimerResults) {
        Timer t("Tokenizer::simplifyTokens1::simplifyTokenList1", mSettings.showtime, mTimerResults);
        if (!simplifyTokenList1(list.getFiles().front().c_str()))
            return false;
    } else {
        if (!simplifyTokenList1(list.getFiles().front().c_str()))
            return false;
    }

    const SHOWTIME_MODES showTime = mTimerResults ? mSettings.showtime : SHOWTIME_MODES::SHOWTIME_NONE;

    Timer::run("Tokenizer::simplifyTokens1::createAst", showTime, mTimerResults, [&]() {
        list.createAst();
        list.validateAst(mSettings.debugnormal);
    });

    Timer::run("Tokenizer::simplifyTokens1::createSymbolDatabase", showTime, mTimerResults, [&]() {
        createSymbolDatabase();
    });

    Timer::run("Tokenizer::simplifyTokens1::setValueType", showTime, mTimerResults, [&]() {
        mSymbolDatabase->setValueTypeInTokenList(false);
        mSymbolDatabase->setValueTypeInTokenList(true);
    });

    if (!mSettings.buildDir.empty())
        Summaries::create(*this, configuration, fileIndex);

    // TODO: apply this through Settings::ValueFlowOptions
    // TODO: do not run valueflow if no checks are being performed at all - e.g. unusedFunctions only
    // TODO: log message when this is active?
    const char* disableValueflowEnv = std::getenv("DISABLE_VALUEFLOW");
    const bool doValueFlow = !disableValueflowEnv || (std::strcmp(disableValueflowEnv, "1") != 0);

    if (doValueFlow) {
        Timer::run("Tokenizer::simplifyTokens1::ValueFlow", showTime, mTimerResults, [&]() {
            ValueFlow::setValues(list, *mSymbolDatabase, mErrorLogger, mSettings, mTimerResults);
        });

        arraySizeAfterValueFlow();
    }

    // Warn about unhandled character literals
    if (mSettings.severity.isEnabled(Severity::portability)) {
        for (const Token *tok = tokens(); tok; tok = tok->next()) {
            if (tok->tokType() == Token::eChar && tok->values().empty()) {
                try {
                    simplecpp::characterLiteralToLL(tok->str());
                } catch (const std::exception &e) {
                    unhandledCharLiteral(tok, e.what());
                }
            }
        }
    }

    if (doValueFlow) {
        mSymbolDatabase->setArrayDimensionsUsingValueFlow();
    }

    printDebugOutput(std::cout);

    return true;
}

//---------------------------------------------------------------------------

void Tokenizer::findComplicatedSyntaxErrorsInTemplates()
{
    validate();
    mTemplateSimplifier->checkComplicatedSyntaxErrorsInTemplates();
}

void Tokenizer::checkForEnumsWithTypedef()
{
    for (const Token *tok = list.front(); tok; tok = tok->next()) {
        if (match199(tok)) {
            tok = tok->tokAt(2);
            const Token *tok2 = findmatch200(tok, tok->link()) ;
            if (tok2)
                syntaxError(tok2);
            tok = tok->link();
        }
    }
}

void Tokenizer::fillTypeSizes()
{
    mTypeSize.clear();
    mTypeSize["char"] = 1;
    mTypeSize["_Bool"] = mSettings.platform.sizeof_bool;
    mTypeSize["bool"] = mSettings.platform.sizeof_bool;
    mTypeSize["short"] = mSettings.platform.sizeof_short;
    mTypeSize["int"] = mSettings.platform.sizeof_int;
    mTypeSize["long"] = mSettings.platform.sizeof_long;
    mTypeSize["long long"] = mSettings.platform.sizeof_long_long;
    mTypeSize["float"] = mSettings.platform.sizeof_float;
    mTypeSize["double"] = mSettings.platform.sizeof_double;
    mTypeSize["long double"] = mSettings.platform.sizeof_long_double;
    mTypeSize["wchar_t"] = mSettings.platform.sizeof_wchar_t;
    mTypeSize["size_t"] = mSettings.platform.sizeof_size_t;
    mTypeSize["*"] = mSettings.platform.sizeof_pointer;
}

void Tokenizer::combineOperators()
{
    const bool cpp = isCPP();

    // Combine tokens..
    for (Token *tok = list.front(); tok && tok->next(); tok = tok->next()) {
        const char c1 = tok->str()[0];

        if (tok->str().length() == 1 && tok->strAt(1).length() == 1) {
            const char c2 = tok->strAt(1)[0];

            // combine +-*/ and =
            if (c2 == '=' && (std::strchr("+-*/%|^=!<>", c1)) && !match201(tok->previous())) {
                // skip templates
                if (cpp && (tok->str() == MatchCompiler::makeConstString(">") || match202(tok->previous()))) {
                    const Token* opening =
                        tok->str() == MatchCompiler::makeConstString(">") ? tok->findOpeningBracket() : tok->previous()->findOpeningBracket();
                    if (opening && match24(opening->previous()))
                        continue;
                }
                tok->str(tok->str() + c2);
                tok->deleteNext();
                continue;
            }
        } else if (tok->strAt(1) == MatchCompiler::makeConstString("=")) {
            if (tok->str() == MatchCompiler::makeConstString(">>")) {
                tok->str(">>=");
                tok->deleteNext();
            } else if (tok->str() == MatchCompiler::makeConstString("<<")) {
                tok->str("<<=");
                tok->deleteNext();
            }
        } else if (cpp && (c1 == 'p' || c1 == '_') &&
                   match203(tok)) {
            bool simplify = false;
            int par = 0;
            for (const Token *prev = tok->previous(); prev; prev = prev->previous()) {
                if (prev->str() == MatchCompiler::makeConstString(")")) {
                    ++par;
                } else if (prev->str() == MatchCompiler::makeConstString("(")) {
                    if (par == 0U)
                        break;
                    --par;
                }
                if (par != 0U || prev->str() == MatchCompiler::makeConstString("("))
                    continue;
                if (match42(prev)) {
                    simplify = true;
                    break;
                }
                if (prev->isName() && prev->isUpperCaseName())
                    continue;
                if (prev->isName() && endsWith(prev->str(), ':'))
                    simplify = true;
                break;
            }
            if (simplify) {
                tok->str(tok->str() + ":");
                tok->tokType(Token::Type::eKeyword); // we need to preserve the keyword type after setting a non-keyword string
                tok->deleteNext();
            }
        } else if (tok->str() == MatchCompiler::makeConstString("->")) {
            // If the preceding sequence is "( & %name% )", replace it by "%name%"
            Token* t = tok->tokAt(-4);
            if (match204(t) && !match147(t->previous())) {
                t->deleteThis();
                t->deleteThis();
                t->deleteNext();
                tok->str(".");
            } else {
                tok->str(".");
                tok->originalName("->");
            }
        }
    }
}

void Tokenizer::combineStringAndCharLiterals()
{
    // Combine strings
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!isStringLiteral(tok->str()))
            continue;

        tok->str(simplifyString(tok->str()));

        while (match205(tok->next()) || match206(tok->next())) {
            if (tok->next()->isName()) {
                if (!mSettings.platform.isWindows())
                    break;
                tok->deleteNext(2);
                tok->next()->deleteNext();
            }
            // Two strings after each other, combine them
            tok->concatStr(simplifyString(tok->strAt(1)));
            tok->deleteNext();
        }
    }
}

void Tokenizer::concatenateNegativeNumberAndAnyPositive()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!match207(tok) || tok->tokType() == Token::eIncDecOp)
            continue;

        if (tok->findOpeningBracket())
            continue;

        while (tok->str() != MatchCompiler::makeConstString(">") && tok->next() && tok->strAt(1) == MatchCompiler::makeConstString("+") && (!match208(tok->tokAt(2)) || match209(tok)))
            tok->deleteNext();

        if (match210(tok->next())) {
            // cppcheck-suppress redundantCopyLocalConst - cannot make it a reference because it is deleted afterwards
            std::string prefix = tok->strAt(1);
            tok->deleteNext();
            tok->next()->str(prefix + tok->strAt(1));
        }
    }
}

void Tokenizer::simplifyExternC()
{
    if (isC())
        return;

    // Add attributes to all tokens within `extern "C"` inlines and blocks, and remove the `extern "C"` tokens.
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (match211(tok)) {
            Token *tok2 = tok->next();
            const bool isExtC = tok->strAt(1).size() == 3;
            if (tok->strAt(2) == MatchCompiler::makeConstString("{")) {
                tok2 = tok2->next(); // skip {
                while ((tok2 = tok2->next()) && tok2 != tok->linkAt(2))
                    tok2->isExternC(isExtC);
                tok->linkAt(2)->deleteThis(); // }
                tok->deleteNext(2); // "C" {
            } else {
                while ((tok2 = tok2->next()) && !match212(tok2))
                    tok2->isExternC(isExtC);
                tok->deleteNext(); // "C"
            }
            tok->deleteThis(); // extern
        }
    }
}

void Tokenizer::simplifyCompoundStatements()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        while (match213(tok) &&
               match214(tok->linkAt(2))) {
            if (tok->str() == MatchCompiler::makeConstString(":") && !match215(tok->tokAt(-2)))
                break;
            Token *end = tok->linkAt(2)->tokAt(-3);
            if (match216(end))
                end->deleteNext(2);
            tok->linkAt(2)->previous()->deleteNext(3);
            tok->deleteNext(2);
        }
        if (match217(tok)) {
            tok->deleteNext();
            tok->deleteThis();
            tok->deleteNext(3);
        }
        else if (tok->str() == MatchCompiler::makeConstString("("))
            tok = tok->link();
    }
}

void Tokenizer::simplifySQL()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!match218(tok))
            continue;

        const Token *end = findSQLBlockEnd(tok);
        if (end == nullptr)
            syntaxError(nullptr);

        const std::string instruction = tok->stringifyList(end);
        // delete all tokens until the embedded SQL block end
        Token::eraseTokens(tok, end);

        // insert "asm ( "instruction" ) ;"
        tok->str("asm");
        // it can happen that 'end' is NULL when wrong code is inserted
        if (!tok->next())
            tok->insertToken(";");
        tok->insertToken(")");
        tok->insertToken("\"" + instruction + "\"");
        tok->insertToken("(");
        // jump to ';' and continue
        tok = tok->tokAt(3);
    }
}

void Tokenizer::simplifyParenthesizedLibraryFunctions()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!match59(tok))
            continue;
        Token *rpar = tok, *lpar = tok->link();
        if (!lpar || match24(lpar->previous()))
            continue;
        const Token *ftok = rpar->previous();
        if (mSettings.library.isNotLibraryFunction(ftok))
            continue;
        lpar->deleteThis();
        rpar->deleteThis();
    }
}

void Tokenizer::simplifyArrayAccessSyntax()
{
    // 0[a] -> a[0]
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->isNumber() && match219(tok)) {
            const std::string number(tok->str());
            Token* indexTok = tok->tokAt(2);
            tok->str(indexTok->str());
            tok->varId(indexTok->varId());
            indexTok->str(number);
        }
    }
}

void Tokenizer::simplifyParameterVoid()
{
    for (Token* tok = list.front(); tok; tok = tok->next()) {
        if (match220(tok) && !match221(tok)) {
            tok->next()->deleteNext();
            tok->next()->setRemovedVoidParameter(true);
        }
    }
}

void Tokenizer::simplifyRedundantConsecutiveBraces()
{
    // Remove redundant consecutive braces, i.e. '.. { { .. } } ..' -> '.. { .. } ..'.
    for (Token *tok = list.front(); tok;) {
        if (match222(tok)) {
            tok = tok->linkAt(1);
        } else if (match223(tok) && match224(tok->linkAt(1))) {
            //remove internal parentheses
            tok->linkAt(1)->deleteThis();
            tok->deleteNext();
        } else
            tok = tok->next();
    }
}

void Tokenizer::simplifyDoublePlusAndDoubleMinus()
{
    // Convert - - into + and + - into -
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        while (tok->next()) {
            if (tok->str() == MatchCompiler::makeConstString("+")) {
                if (tok->strAt(1)[0] == '-') {
                    tok = tok->next();
                    if (tok->str().size() == 1) {
                        tok = tok->previous();
                        tok->str("-");
                        tok->deleteNext();
                    } else if (tok->isNumber()) {
                        tok->str(tok->str().substr(1));
                        tok = tok->previous();
                        tok->str("-");
                    }
                    continue;
                }
            } else if (tok->str() == MatchCompiler::makeConstString("-")) {
                if (tok->strAt(1)[0] == '-') {
                    tok = tok->next();
                    if (tok->str().size() == 1) {
                        tok = tok->previous();
                        tok->str("+");
                        tok->deleteNext();
                    } else if (tok->isNumber()) {
                        tok->str(tok->str().substr(1));
                        tok = tok->previous();
                        tok->str("+");
                    }
                    continue;
                }
            }

            break;
        }
    }
}

/** Specify array size if it hasn't been given */

void Tokenizer::arraySize()
{
    auto getStrTok = [](Token* tok, bool addLength, Token*& endStmt) -> Token* {
        if (addLength) {
            endStmt = tok->tokAt(5);
            return tok->tokAt(4);
        }
        if (match225(tok)) {
            tok = tok->tokAt(4);
            int parCount = 0;
            while (match94(tok)) {
                ++parCount;
                tok = tok->next();
            }
            if (match205(tok)) {
                endStmt = tok->tokAt(parCount + 1);
                return tok;
            }
        }
        return nullptr;
    };

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!tok->isName() || !match225(tok))
            continue;
        bool addlength = false;
        if (match226(tok->previous())) {
            Token *t = tok->tokAt(3);
            t->deleteNext();
            t->next()->deleteNext();
            addlength = true;
        }

        Token* endStmt{};
        if (const Token* strTok = getStrTok(tok, addlength, endStmt)) {
            const int sz = Token::getStrArraySize(strTok);
            tok->next()->insertToken(std::to_string(sz));
            tok = endStmt;
        }

        else if (match227(tok)) {
            MathLib::biguint sz = 1;
            tok = tok->next();
            Token *end = tok->linkAt(3);
            for (Token *tok2 = tok->tokAt(4); tok2 && tok2 != end; tok2 = tok2->next()) {
                if (tok2->link() && match228(tok2)) {
                    if (tok2->str() == MatchCompiler::makeConstString("[") && tok2->link()->strAt(1) == MatchCompiler::makeConstString("=")) { // designated initializer
                        if (match229(tok2))
                            sz = std::max(sz, MathLib::toBigUNumber(tok2->tokAt(1)) + 1U);
                        else {
                            sz = 0;
                            break;
                        }
                    }
                    tok2 = tok2->link();
                } else if (tok2->str() == MatchCompiler::makeConstString(",")) {
                    if (!match230(tok2->next()))
                        ++sz;
                    else {
                        tok2 = tok2->previous();
                        tok2->deleteNext();
                    }
                }
            }

            if (sz != 0)
                tok->insertToken(MathLib::toString(sz));

            tok = end->next() ? end->next() : end;
        }
    }
}

// cppcheck-suppress functionConst
void Tokenizer::arraySizeAfterValueFlow()
{
    // After ValueFlow, adjust array sizes.
    for (const Variable* var: mSymbolDatabase->variableList()) {
        if (!var || !var->isArray())
            continue;
        if (!match231(var->nameToken()))
            continue;
        MathLib::bigint maxIndex = -1;
        const Token* const startToken = var->nameToken()->tokAt(4);
        const Token* const endToken = startToken->link();
        for (const Token* tok = startToken; tok != endToken; tok = tok->next()) {
            if (!match232(tok) || !match233(tok->linkAt(1)))
                continue;
            const Token* expr = tok->next()->astOperand1();
            if (expr && expr->hasKnownIntValue())
                maxIndex = std::max(maxIndex, expr->getKnownIntValue());
        }
        if (maxIndex >= 0) {
            // insert array size
            auto* tok = const_cast<Token*>(var->nameToken()->next());
            tok->insertToken(MathLib::toString(maxIndex + 1));
            // ast
            tok->astOperand2(tok->next());
            // Token::scope
            tok->next()->scope(tok->scope());
            // Value flow
            ValueFlow::Value value(maxIndex + 1);
            value.setKnown();
            tok->next()->addValue(value);
            // Set array dimensions
            Dimension d;
            d.num = maxIndex + 1;
            std::vector<Dimension> dimensions{d};
            const_cast<Variable*>(var)->setDimensions(dimensions);
        }
    }
}

static Token *skipTernaryOp(Token *tok)
{
    int colonLevel = 1;
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
        if (tok->link() && match234(tok))
            tok = tok->link();
        else if (match235(tok->next()))
            break;
    }
    if (colonLevel > 0) // Ticket #5214: Make sure the ':' matches the proper '?'
        return nullptr;
    return tok;
}

// Skips until the colon at the end of the case label, the argument must point to the "case" token.
// In case of success returns the colon token.
// In case of failure returns the token that caused the error.
static Token *skipCaseLabel(Token *tok)
{
    assert(tok->str() == MatchCompiler::makeConstString("case"));
    while (nullptr != (tok = tok->next())) {
        if (match68(tok))
            tok = tok->link();
        else if (tok->str() == MatchCompiler::makeConstString("?")) {
            Token * tok1 = skipTernaryOp(tok);
            if (!tok1)
                return tok;
            tok = tok1;
        }
        if (match236(tok))
            return tok;
    }
    return nullptr;
}

const Token * Tokenizer::startOfExecutableScope(const Token * tok)
{
    if (tok->str() != MatchCompiler::makeConstString(")"))
        return nullptr;

    tok = TokenList::isFunctionHead(tok, ":{");

    if (match237(tok)) {
        while (match238(tok))
            tok = tok->linkAt(2)->next();
    }

    return (tok && tok->str() == MatchCompiler::makeConstString("{")) ? tok : nullptr;
}


/** simplify labels and case|default in the code: add a ";" if not already in.*/

void Tokenizer::simplifyLabelsCaseDefault()
{
    const bool cpp = isCPP();
    bool executablescope = false;
    int indentLevel = 0;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        // Simplify labels in the executable scope..
        auto *start = const_cast<Token *>(startOfExecutableScope(tok));
        if (start) {
            tok = start;
            executablescope = true;
        }

        if (!executablescope)
            continue;

        if (tok->str() == MatchCompiler::makeConstString("{")) {
            if (tok->strAt(-1) == MatchCompiler::makeConstString("="))
                tok = tok->link();
            else
                ++indentLevel;
        } else if (tok->str() == MatchCompiler::makeConstString("}")) {
            --indentLevel;
            if (indentLevel == 0) {
                executablescope = false;
                continue;
            }
        } else if (match68(tok))
            tok = tok->link();

        if (match239(tok)) {
            tok = skipCaseLabel(tok->next());
            if (!tok)
                break;
            if (tok->str() != MatchCompiler::makeConstString(":") || tok->strAt(-1) == MatchCompiler::makeConstString("case") || !tok->next())
                syntaxError(tok);
            if (tok->strAt(1) != MatchCompiler::makeConstString(";") && tok->strAt(1) != MatchCompiler::makeConstString("case"))
                tok->insertToken(";");
            else
                tok = tok->previous();
        } else if (match240(tok)) {
            if (!cpp || !match241(tok->next())) {
                tok = tok->tokAt(2);
                tok->insertToken(";");
            }
        }
    }
}


void Tokenizer::simplifyCaseRange()
{
    for (Token* tok = list.front(); tok; tok = tok->next()) {
        if (match242(tok)) {
            const MathLib::bigint start = MathLib::toBigNumber(tok->tokAt(1));
            MathLib::bigint end = MathLib::toBigNumber(tok->tokAt(3));
            end = std::min(start + 50, end); // Simplify it 50 times at maximum
            if (start < end) {
                tok = tok->tokAt(2);
                tok->str(":");
                tok->insertToken("case");
                for (MathLib::bigint i = end-1; i > start; i--) {
                    tok->insertToken(":");
                    tok->insertToken(MathLib::toString(i));
                    tok->insertToken("case");
                }
            }
        }
    }
}

void Tokenizer::calculateScopes()
{
    for (auto *tok = list.front(); tok; tok = tok->next())
        tok->scopeInfo(nullptr);

    std::string nextScopeNameAddition;
    std::shared_ptr<ScopeInfo2> primaryScope = std::make_shared<ScopeInfo2>("", nullptr);
    list.front()->scopeInfo(std::move(primaryScope));

    for (Token* tok = list.front(); tok; tok = tok->next()) {
        if (tok == list.front() || !tok->scopeInfo()) {
            if (tok != list.front())
                tok->scopeInfo(tok->previous()->scopeInfo());

            if (match243(tok)) {
                std::string usingNamespaceName;
                for (const Token* namespaceNameToken = tok->tokAt(2);
                     namespaceNameToken && namespaceNameToken->str() != MatchCompiler::makeConstString(";");
                     namespaceNameToken = namespaceNameToken->next()) {
                    usingNamespaceName += namespaceNameToken->str();
                    usingNamespaceName += " ";
                }
                if (!usingNamespaceName.empty())
                    usingNamespaceName.pop_back();
                tok->scopeInfo()->usingNamespaces.insert(std::move(usingNamespaceName));
            } else if (match244(tok)) {
                for (Token* nameTok = tok->next(); nameTok && !match245(nameTok); nameTok = nameTok->next()) {
                    if (match246(nameTok)) {
                        nextScopeNameAddition = "";
                        break;
                    }
                    nextScopeNameAddition.append(nameTok->str());
                    nextScopeNameAddition.append(" ");
                }
                if (!nextScopeNameAddition.empty())
                    nextScopeNameAddition.pop_back();
            }

            if (match1(tok)) {
                // This might be the opening of a member function
                Token *tok1 = tok;
                while (match171(tok1->previous()))
                    tok1 = tok1->previous();
                if (tok1->previous() && tok1->strAt(-1) == MatchCompiler::makeConstString(")")) {
                    bool member = true;
                    tok1 = tok1->linkAt(-1);
                    if (match247(tok1->previous())) {
                        tok1 = tok1->previous();
                        while (match171(tok1->previous()))
                            tok1 = tok1->previous();
                        if (tok1->strAt(-1) != MatchCompiler::makeConstString(")"))
                            member = false;
                    } else if (match173(tok->tokAt(-2))) {
                        tok1 = tok1->tokAt(-2);
                        if (tok1->strAt(-1) != MatchCompiler::makeConstString(")"))
                            member = false;
                    }
                    if (member) {
                        if (tok1->strAt(-1) == MatchCompiler::makeConstString(">"))
                            tok1 = tok1->previous()->findOpeningBracket();
                        if (tok1 && match108(tok1->tokAt(-3))) {
                            tok1 = tok1->tokAt(-2);
                            std::string scope = tok1->strAt(-1);
                            while (match175(tok1->tokAt(-2))) {
                                scope = tok1->strAt(-3) + " :: " + scope;
                                tok1 = tok1->tokAt(-2);
                            }

                            if (!nextScopeNameAddition.empty() && !scope.empty())
                                nextScopeNameAddition += " :: ";
                            nextScopeNameAddition += scope;
                        }
                    }
                }

                // New scope is opening, record it here
                std::shared_ptr<ScopeInfo2> newScopeInfo = std::make_shared<ScopeInfo2>(tok->scopeInfo()->name, tok->link(), tok->scopeInfo()->usingNamespaces);

                if (!newScopeInfo->name.empty() && !nextScopeNameAddition.empty())
                    newScopeInfo->name.append(" :: ");
                newScopeInfo->name.append(nextScopeNameAddition);
                nextScopeNameAddition = "";

                if (tok->link())
                    tok->link()->scopeInfo(tok->scopeInfo());
                tok->scopeInfo(std::move(newScopeInfo));
            }
        }
    }
}

void Tokenizer::simplifyTemplates()
{
    if (isC())
        return;

    const std::time_t maxTime = mSettings.templateMaxTime > 0 ? std::time(nullptr) + mSettings.templateMaxTime : 0;
    mTemplateSimplifier->simplifyTemplates(
        maxTime);
}
//---------------------------------------------------------------------------


namespace {
    /** Class used in Tokenizer::setVarIdPass1 */
    class VariableMap {
    private:
        std::unordered_map<std::string, nonneg int> mVariableId;
        std::unordered_map<std::string, nonneg int> mVariableId_global;
        std::stack<std::vector<std::pair<std::string, nonneg int>>> mScopeInfo;
        mutable nonneg int mVarId{};
    public:
        VariableMap() = default;
        void enterScope();
        bool leaveScope();
        void addVariable(const std::string& varname, bool globalNamespace);
        bool hasVariable(const std::string& varname) const {
            return mVariableId.find(varname) != mVariableId.end();
        }

        const std::unordered_map<std::string, nonneg int>& map(bool global) const {
            return global ? mVariableId_global : mVariableId;
        }
        nonneg int& getVarId() {
            return mVarId;
        }
    };
}


void VariableMap::enterScope()
{
    mScopeInfo.emplace(/*std::vector<std::pair<std::string, nonneg int>>()*/);
}

bool VariableMap::leaveScope()
{
    if (mScopeInfo.empty())
        return false;

    for (const std::pair<std::string, nonneg int>& outerVariable : mScopeInfo.top()) {
        if (outerVariable.second != 0)
            mVariableId[outerVariable.first] = outerVariable.second;
        else
            mVariableId.erase(outerVariable.first);
    }
    mScopeInfo.pop();
    return true;
}

void VariableMap::addVariable(const std::string& varname, bool globalNamespace)
{
    if (mScopeInfo.empty()) {
        mVariableId[varname] = ++mVarId;
        if (globalNamespace)
            mVariableId_global[varname] = mVariableId[varname];
        return;
    }
    const auto it = mVariableId.find(varname);
    if (it == mVariableId.end()) {
        mScopeInfo.top().emplace_back(varname, 0);
        mVariableId[varname] = ++mVarId;
        if (globalNamespace)
            mVariableId_global[varname] = mVariableId[varname];
        return;
    }
    mScopeInfo.top().emplace_back(varname, it->second);
    it->second = ++mVarId;
}

static bool setVarIdParseDeclaration(Token*& tok, const VariableMap& variableMap, bool executableScope)
{
    const Token* const tok1 = tok;
    Token* tok2 = tok;
    if (!tok2->isName())
        return false;

    nonneg int typeCount = 0;
    nonneg int singleNameCount = 0;
    bool hasstruct = false;   // Is there a "struct" or "class"?
    bool bracket = false;
    bool ref = false;
    while (tok2) {
        if (tok2->isName()) {
            if (match248(tok2)) {
                tok2 = tok2->linkAt(1)->next();
                continue;
            }
            if (tok2->isCpp() && match249(tok2))
                return false;
            if (tok2->isCpp() && match250(tok2)) {
                typeCount = 1;
                tok2 = tok2->linkAt(1)->next();
                continue;
            }
            if (match251(tok2) || (tok2->isCpp() && match252(tok2))) {
                hasstruct = true;
                typeCount = 0;
                singleNameCount = 0;
            } else if (match253(tok2)) {
                // just skip "const", "extern"
            } else if (!hasstruct && variableMap.map(false).count(tok2->str()) && tok2->strAt(-1) != MatchCompiler::makeConstString("::")) {
                ++typeCount;
                tok2 = tok2->next();
                if (!tok2 || tok2->str() != MatchCompiler::makeConstString("::"))
                    break;
            } else {
                if (tok2->str() != MatchCompiler::makeConstString("void") || match254(tok2)) // just "void" cannot be a variable type
                    ++typeCount;
                ++singleNameCount;
            }
        } else if (tok2->isCpp() && ((TemplateSimplifier::templateParameters(tok2) > 0) ||
                                     match255(tok2) /* Ticket #4764 */)) {
            const Token *start = tok;
            if (match256(start->previous()))
                return false;
            Token* const closingBracket = tok2->findClosingBracket();
            if (closingBracket == nullptr) { /* Ticket #8151 */
                throw tok2;
            }
            tok2 = closingBracket;
            if (tok2->str() != MatchCompiler::makeConstString(">"))
                break;
            singleNameCount = 1;
            if (match257(tok2) && !match258(tok2))
                return false;
            if (match259(tok2)) {
                if (match260(tok2->linkAt(2)->previous()))
                    return false;
                if (!match261(tok2->linkAt(2)->previous()))
                    return false;
            }
        } else if (match262(tok2)) {
            ref = !bracket;
        } else if (singleNameCount >= 1 && match263(tok2) && match264(tok2->link())) {
            for (const Token* tok3 = tok2->tokAt(2); match265(tok3); tok3 = tok3->next()) {
                if (match68(tok3))
                    tok3 = tok3->link();
                if (tok3->str() == MatchCompiler::makeConstString(","))
                    return false;
            }
            bracket = true; // Skip: Seems to be valid pointer to array or function pointer
        } else if (singleNameCount >= 1 && match266(tok2) && match267(tok2->linkAt(3)) && !variableMap.map(false).count(tok2->strAt(2))) {
            bracket = true;
        } else if (singleNameCount >= 1 && tok2->previous() && tok2->previous()->isStandardType() && match268(tok2)) {
            bracket = true;
        } else if (tok2->str() == MatchCompiler::makeConstString("::")) {
            singleNameCount = 0;
        } else if (tok2->str() != MatchCompiler::makeConstString("*") && tok2->str() != MatchCompiler::makeConstString("...")) {
            break;
        }
        tok2 = tok2->next();
    }

    if (tok2) {
        bool isLambdaArg = false;
        {
            const Token *tok3 = tok->previous();
            if (tok3 && tok3->str() == MatchCompiler::makeConstString(",")) {
                while (tok3 && !match269(tok3)) {
                    if (match90(tok3))
                        tok3 = tok3->link();
                    tok3 = tok3->previous();
                }

                if (tok3 && executableScope && match56(tok3->previous())) {
                    const Token *fdecl = tok3->previous();
                    int count = 0;
                    while (match270(fdecl)) {
                        fdecl = fdecl->previous();
                        count++;
                    }
                    if (!match182(fdecl) || count <= 1)
                        return false;
                }
            }

            if (tok3 && tok3->isCpp() && match271(tok3->previous()) &&
                (match14(tok3->link()) || match272(tok3->link())))
                isLambdaArg = true;
        }


        tok = tok2;

        // In executable scopes, references must be assigned
        // Catching by reference is an exception
        if (executableScope && ref && !isLambdaArg) {
            if (match273(tok2))
                ;   // reference is assigned => ok
            else if (tok2->str() != MatchCompiler::makeConstString(")") || tok2->link()->strAt(-1) != MatchCompiler::makeConstString("catch"))
                return false;   // not catching by reference => not declaration
        }
    }

    // Check if array declaration is valid (#2638)
    // invalid declaration: AAA a[4] = 0;
    if (typeCount >= 2 && executableScope && match274(tok2)) {
        const Token *tok3 = tok2->str() == MatchCompiler::makeConstString(")") ? tok2->next() : tok2;
        while (tok3 && tok3->str() == MatchCompiler::makeConstString("[")) {
            tok3 = tok3->link()->next();
        }
        if (match275(tok3))
            return false;
        if (bracket && match276(tok1->previous()) && match277(tok3))
            return false;
    }

    return (typeCount >= 2 && tok2 && match278(tok2->tokAt(-2)));
}


static void setVarIdStructMembers(Token *&tok1,
                                  std::map<nonneg int, std::map<std::string, nonneg int>>& structMembers,
                                  nonneg int &varId)
{
    Token *tok = tok1;

    if (match279(tok)) {
        const nonneg int struct_varid = tok->varId();
        if (struct_varid == 0)
            return;

        std::map<std::string, nonneg int>& members = structMembers[struct_varid];

        tok = tok->tokAt(3);
        while (tok->str() != MatchCompiler::makeConstString("}")) {
            if (match280(tok))
                tok = tok->link();
            if (match281(tok->previous())) {
                tok = tok->next();
                const auto it = utils::as_const(members).find(tok->str());
                if (it == members.cend()) {
                    members[tok->str()] = ++varId;
                    tok->varId(varId);
                } else {
                    tok->varId(it->second);
                }
            }
            tok = tok->next();
        }

        return;
    }

    while (match282(tok->next())) {
        // Don't set varid for trailing return type
        if (tok->strAt(1) == MatchCompiler::makeConstString(")") && match283(tok->linkAt(1)->tokAt(-1)) && !tok->linkAt(1)->tokAt(-1)->isKeyword() &&
            TokenList::isFunctionHead(tok->linkAt(1), "{;")) {
            tok = tok->tokAt(3);
            continue;
        }
        const nonneg int struct_varid = tok->varId();
        tok = tok->tokAt(2);
        if (struct_varid == 0)
            continue;

        if (tok->str() == MatchCompiler::makeConstString("."))
            tok = tok->next();

        // Don't set varid for template function
        if (TemplateSimplifier::templateParameters(tok->next()) > 0)
            break;

        std::map<std::string, nonneg int>& members = structMembers[struct_varid];
        const auto it = utils::as_const(members).find(tok->str());
        if (it == members.cend()) {
            members[tok->str()] = ++varId;
            tok->varId(varId);
        } else {
            tok->varId(it->second);
        }
    }
    // tok can't be null
    tok1 = tok;
}

static void addTemplateVarIdUsage(const std::string &tokstr,
                                  const std::map<std::string, std::set<std::string>>& templateVarUsage,
                                  const std::unordered_map<std::string, nonneg int>& variableMap,
                                  std::set<nonneg int>& templateVarIdUsage) {
    const auto v = templateVarUsage.find(tokstr);
    if (v != templateVarUsage.end()) {
        for (const std::string& varname: v->second) {
            const auto it = variableMap.find(varname);
            if (it != variableMap.end())
                templateVarIdUsage.insert(it->second);
        }
    }
}

static bool setVarIdClassDeclaration(Token* const startToken,
                                     VariableMap& variableMap,
                                     const nonneg int scopeStartVarId,
                                     const std::map<std::string, std::set<std::string>>& templateVarUsage,
                                     std::map<nonneg int, std::map<std::string, nonneg int>>& structMembers,
                                     std::set<nonneg int>& templateVarIdUsage)
{
    // end of scope
    const Token* const endToken = startToken->link();

    // determine class name
    std::string className;
    for (const Token *tok = startToken->previous(); tok; tok = tok->previous()) {
        if (!tok->isName() && tok->str() != MatchCompiler::makeConstString(":"))
            break;
        if (match284(tok)) {
            className = tok->strAt(1);
            break;
        }
    }

    // replace varids..
    int indentlevel = 0;
    bool initList = false;
    bool inEnum = false;
    const Token *initListArgLastToken = nullptr;
    for (Token *tok = startToken->next(); tok != endToken; tok = tok->next()) {
        if (!tok)
            return false;
        if (initList) {
            if (tok == initListArgLastToken)
                initListArgLastToken = nullptr;
            else if (!initListArgLastToken &&
                     match285(tok->previous()) &&
                     match286(tok->link()))
                initListArgLastToken = tok->link();
        }
        if (tok->str() == MatchCompiler::makeConstString("{")) {
            inEnum = isEnumStart(tok);
            if (!inEnum && isClassStructUnionEnumStart(tok)) { // nested type
                tok = tok->link();
                continue;
            }
            if (initList && !initListArgLastToken)
                initList = false;
            ++indentlevel;
        } else if (tok->str() == MatchCompiler::makeConstString("}")) {
            --indentlevel;
            inEnum = false;
        } else if (initList && indentlevel == 0 && match287(tok->previous())) {
            const auto it = variableMap.map(false).find(tok->str());
            if (it != variableMap.map(false).end()) {
                tok->varId(it->second);
            }
        } else if (tok->isName() && tok->varId() <= scopeStartVarId) {
            if (indentlevel > 0 || initList) {
                if (match288(tok->previous()) && tok->strAt(-2) != MatchCompiler::makeConstString("this") && !match289(tok->tokAt(-5)))
                    continue;
                if (!tok->next())
                    return false;
                if (tok->strAt(1) == MatchCompiler::makeConstString("::")) {
                    if (tok->str() == className)
                        tok = tok->tokAt(2);
                    else
                        continue;
                }

                if (!inEnum) {
                    const auto it = variableMap.map(false).find(tok->str());
                    if (it != variableMap.map(false).end()) {
                        tok->varId(it->second);
                        setVarIdStructMembers(tok, structMembers, variableMap.getVarId());
                    } else if (tok->str().back() == '>') {
                        addTemplateVarIdUsage(tok->str(), templateVarUsage, variableMap.map(false), templateVarIdUsage);
                    }
                }
            }
        } else if (indentlevel == 0 && tok->str() == MatchCompiler::makeConstString(":") && !initListArgLastToken)
            initList = true;
    }
    return true;
}



// Update the variable ids..
// Parse each function..
void Tokenizer::setVarIdClassFunction(const std::string &classname,
                                      Token * const startToken,
                                      const Token * const endToken,
                                      const std::map<std::string, nonneg int> &varlist,
                                      std::map<nonneg int, std::map<std::string, nonneg int>>& structMembers,
                                      nonneg int &varId_)
{
    const auto pos = classname.rfind(' '); // TODO handle multiple scopes
    const std::string lastScope = classname.substr(pos == std::string::npos ? 0 : pos + 1);
    for (Token *tok2 = startToken; tok2 && tok2 != endToken; tok2 = tok2->next()) {
        if (tok2->varId() != 0 || !tok2->isName())
            continue;
        if (Token::Match(tok2->tokAt(-2), ("!!" + lastScope + " ::").c_str()))
            continue;
        if (match290(tok2->tokAt(-4))) // Currently unsupported
            continue;
        if (match291(tok2->tokAt(-2)) && !match289(tok2->tokAt(-5)))
            continue;
        if (match36(tok2))
            continue;

        const auto it = utils::as_const(varlist).find(tok2->str());
        if (it != varlist.end()) {
            tok2->varId(it->second);
            setVarIdStructMembers(tok2, structMembers, varId_);
        }
    }
}



void Tokenizer::setVarId()
{
    // Clear all variable ids
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->isName())
            tok->varId(0);
    }

    setVarIdPass1();

    setPodTypes();

    setVarIdPass2();
}


// Variable declarations can't start with "return" etc.
#define NOTSTART_C "NOT", "case", "default", "goto", "not", "return", "sizeof", "typedef"
static const std::unordered_set<std::string> notstart_c = { NOTSTART_C };
static const std::unordered_set<std::string> notstart_cpp = { NOTSTART_C,
                                                              "delete", "friend", "new", "throw", "using", "virtual", "explicit", "const_cast", "dynamic_cast", "reinterpret_cast", "static_cast", "template"
};

void Tokenizer::setVarIdPass1()
{
    const bool cpp = isCPP();
    // Variable declarations can't start with "return" etc.
    const std::unordered_set<std::string>& notstart = (isC()) ? notstart_c : notstart_cpp;

    VariableMap variableMap;
    std::map<nonneg int, std::map<std::string, nonneg int>> structMembers;

    std::stack<VarIdScopeInfo> scopeStack;

    scopeStack.emplace(/*VarIdScopeInfo()*/);
    std::stack<const Token *> functionDeclEndStack;
    const Token *functionDeclEndToken = nullptr;
    bool initlist = false;
    bool inlineFunction = false;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->isOp())
            continue;
        if (cpp && match292(tok)) {
            Token* closingBracket = tok->next()->findClosingBracket();
            if (closingBracket)
                tok = closingBracket;
            continue;
        }

        if (tok == functionDeclEndToken) {
            functionDeclEndStack.pop();
            functionDeclEndToken = functionDeclEndStack.empty() ? nullptr : functionDeclEndStack.top();
            if (tok->str() == MatchCompiler::makeConstString(":"))
                initlist = true;
            else if (tok->str() == MatchCompiler::makeConstString(";")) {
                if (!variableMap.leaveScope())
                    cppcheckError(tok);
            } else if (tok->str() == MatchCompiler::makeConstString("{")) {
                scopeStack.emplace(true, scopeStack.top().isStructInit || tok->strAt(-1) == MatchCompiler::makeConstString("="), /*isEnum=*/ false, variableMap.getVarId());

                // check if this '{' is a start of an "if" body
                const Token * ifToken = tok->previous();
                if (ifToken && ifToken->str() == MatchCompiler::makeConstString(")"))
                    ifToken = ifToken->link();
                else
                    ifToken = nullptr;
                if (ifToken)
                    ifToken = ifToken->previous();
                if (ifToken && ifToken->str() == MatchCompiler::makeConstString("if")) {
                    // open another scope to differentiate between variables declared in the "if" condition and in the "if" body
                    variableMap.enterScope();
                }
            }
        } else if (!initlist && tok->str()==MatchCompiler::makeConstString("(")) {
            const Token * newFunctionDeclEnd = nullptr;
            if (!scopeStack.top().isExecutable)
                newFunctionDeclEnd = TokenList::isFunctionHead(tok, "{:;");
            else {
                const Token* tokenLinkNext = tok->link()->next();
                if (match198(tokenLinkNext)) { // skip trailing return type
                    tokenLinkNext = tokenLinkNext->next();
                    while (match293(tokenLinkNext)) {
                        tokenLinkNext = tokenLinkNext->next();
                        if (match146(tokenLinkNext) && tokenLinkNext->link())
                            tokenLinkNext = tokenLinkNext->link()->next();
                    }
                }
                if (tokenLinkNext && tokenLinkNext->str() == MatchCompiler::makeConstString("{")) // might be for- or while-loop or if-statement
                    newFunctionDeclEnd = tokenLinkNext;
            }
            if (newFunctionDeclEnd && newFunctionDeclEnd != functionDeclEndToken) {
                functionDeclEndStack.push(newFunctionDeclEnd);
                functionDeclEndToken = newFunctionDeclEnd;
                variableMap.enterScope();
            }
        } else if (match294(tok)) {
            inlineFunction = false;

            const Token * const startToken = (tok->str() == MatchCompiler::makeConstString("{")) ? tok : tok->link();

            // parse anonymous namespaces as part of the current scope
            if (!match295(startToken->previous()) &&
                !(initlist && match296(startToken->previous()) && match297(startToken->link()))) {

                if (tok->str() == MatchCompiler::makeConstString("{")) {
                    bool isExecutable;
                    const Token *prev = tok->previous();
                    while (match298(prev))
                        prev = prev->previous();
                    const bool isLambda = prev && prev->str() == MatchCompiler::makeConstString(")") && match271(prev->link()->previous());
                    if ((!isLambda && (tok->strAt(-1) == MatchCompiler::makeConstString(")") || match299(tok->tokAt(-2)))) ||
                        (initlist && tok->strAt(-1) == MatchCompiler::makeConstString("}"))) {
                        isExecutable = true;
                    } else {
                        isExecutable = ((scopeStack.top().isExecutable || initlist || tok->strAt(-1) == MatchCompiler::makeConstString("else")) &&
                                        !isClassStructUnionEnumStart(tok));
                        if (!(scopeStack.top().isStructInit || tok->strAt(-1) == MatchCompiler::makeConstString("=")))
                            variableMap.enterScope();
                    }
                    const bool isStructInit = scopeStack.top().isStructInit || tok->strAt(-1) == MatchCompiler::makeConstString("=") || (initlist && !match300(tok->tokAt(-1)));
                    scopeStack.emplace(isExecutable, isStructInit, isEnumStart(tok), variableMap.getVarId());
                    initlist = false;
                } else { /* if (tok->str() == MatchCompiler::makeConstString("}")) */
                    bool isNamespace = false;
                    for (const Token *tok1 = tok->link()->previous(); tok1 && tok1->isName(); tok1 = tok1->previous()) {
                        if (tok1->str() == MatchCompiler::makeConstString("namespace")) {
                            isNamespace = true;
                            break;
                        }
                    }
                    // Set variable ids in class declaration..
                    if (!initlist && !isC() && !scopeStack.top().isExecutable && tok->link() && !isNamespace) {
                        if (!setVarIdClassDeclaration(tok->link(),
                                                      variableMap,
                                                      scopeStack.top().startVarid,
                                                      mTemplateSimplifier->getUsedVariables(),
                                                      structMembers,
                                                      mTemplateVarIdUsage)) {
                            syntaxError(nullptr);
                        }
                    }

                    if (!scopeStack.top().isStructInit) {
                        variableMap.leaveScope();

                        // check if this '}' is an end of an "else" body or an "if" body without an "else" part
                        const Token * ifToken = startToken->previous();
                        if (ifToken && ifToken->str() == MatchCompiler::makeConstString(")"))
                            ifToken = ifToken->link()->previous();
                        else
                            ifToken = nullptr;
                        if (startToken->strAt(-1) == MatchCompiler::makeConstString("else") || (ifToken && ifToken->str() == MatchCompiler::makeConstString("if") && tok->strAt(1) != MatchCompiler::makeConstString("else"))) {
                            // leave the extra scope used to differentiate between variables declared in the "if" condition and in the "if" body
                            variableMap.leaveScope();
                        }
                    }

                    scopeStack.pop();
                    if (scopeStack.empty()) {  // should be impossible
                        scopeStack.emplace(/*VarIdScopeInfo()*/);
                    }
                }
            }
        }

        if ((!scopeStack.top().isStructInit &&
             (tok == list.front() ||
              match42(tok) ||
              (tok->str() == MatchCompiler::makeConstString("(") && !scopeStack.top().isExecutable && TokenList::isFunctionHead(tok,";:")) ||
              (tok->str() == MatchCompiler::makeConstString(",") && (!scopeStack.top().isExecutable || inlineFunction || !tok->previous()->varId())) ||
              (tok->isName() && endsWith(tok->str(), ':')))) ||
            (tok->str() == MatchCompiler::makeConstString("(") && TokenList::isFunctionHead(tok, "{"))) {

            // No variable declarations in sizeof
            if (match301(tok->previous())) {
                continue;
            }

            if (Settings::terminated())
                return;

            // locate the variable name..
            Token* tok2 = (tok->isName()) ? tok : tok->next();

            // private: protected: public: etc
            while (tok2 && endsWith(tok2->str(), ':')) {
                tok2 = tok2->next();
            }
            if (!tok2)
                break;

            // Variable declaration can't start with "return", etc
            if (notstart.find(tok2->str()) != notstart.end())
                continue;

            if (!isC() && match302(tok2))
                continue;

            bool decl;
            if (cpp && mSettings.standards.cpp >= Standards::CPP17 && match303(tok)) {
                // Structured bindings
                tok2 = findmatch304(tok) ;
                if ((match305(tok->previous()) && match306(tok2->link())) ||
                    match233(tok2->link())) {
                    while (tok2 && tok2->str() != MatchCompiler::makeConstString("]")) {
                        if (match307(tok2))
                            variableMap.addVariable(tok2->str(), false);
                        tok2 = tok2->next();
                    }
                    continue;
                }
            }

            try { /* Ticket #8151 */
                decl = setVarIdParseDeclaration(tok2, variableMap, scopeStack.top().isExecutable);
            } catch (const Token * errTok) {
                syntaxError(errTok);
            }

            if (tok->str() == MatchCompiler::makeConstString("(") && TokenList::isFunctionHead(tok, "{") && scopeStack.top().isExecutable)
                inlineFunction = true;

            if (decl) {
                if (cpp) {
                    for (const Token* tok3 = tok->next(); tok3->isName(); tok3 = tok3->next()) {
                        addTemplateVarIdUsage(tok3->str(),
                                              mTemplateSimplifier->getUsedVariables(),
                                              variableMap.map(false),
                                              mTemplateVarIdUsage);
                        addTemplateVarIdUsage(tok3->str(),
                                              mTemplateSimplifier->getUsedVariables(),
                                              variableMap.map(true),
                                              mTemplateVarIdUsage);
                    }
                    if (Token *declTypeTok = findmatch308(tok, tok2) ) {
                        for (Token *declTok = declTypeTok->linkAt(1); declTok != declTypeTok; declTok = declTok->previous()) {
                            if (declTok->isName() && !match288(declTok->previous()) && variableMap.hasVariable(declTok->str()))
                                declTok->varId(variableMap.map(false).find(declTok->str())->second);
                        }
                    }
                }

                const Token* prev2 = tok2->previous();
                if (match309(prev2) && tok2->strAt(-1) != MatchCompiler::makeConstString("const"))
                    ;
                else if (match310(prev2) && tok->strAt(-1) == MatchCompiler::makeConstString("for"))
                    ;
                else if (match311(prev2) && match53(tok2->link())) {
                    // In C++ , a variable can't be called operator+ or something like that.
                    if (cpp &&
                        prev2->isOperatorKeyword())
                        continue;

                    const Token *tok3 = tok2->next();
                    if (!tok3->isStandardType() && tok3->str() != MatchCompiler::makeConstString("void") && !match312(tok3) && tok3->str() != MatchCompiler::makeConstString(".") && !match313(tok2->link()->previous())) {
                        if (!scopeStack.top().isExecutable) {
                            // Detecting initializations with () in non-executable scope is hard and often impossible to be done safely. Thus, only treat code as a variable that definitely is one.
                            decl = false;
                            bool rhs = false;
                            for (; tok3; tok3 = tok3->nextArgumentBeforeCreateLinks2()) {
                                if (tok3->str() == MatchCompiler::makeConstString("=")) {
                                    rhs = true;
                                    continue;
                                }

                                if (tok3->str() == MatchCompiler::makeConstString(",")) {
                                    rhs = false;
                                    continue;
                                }

                                if (rhs)
                                    continue;

                                if (tok3->isLiteral() ||
                                    (tok3->isName() && (variableMap.hasVariable(tok3->str()) ||
                                                        (tok3->strAt(-1) == MatchCompiler::makeConstString("(") && match94(tok3->next()) && !match94(tok3->linkAt(1)->next())))) ||
                                    tok3->isOp() ||
                                    tok3->str() == MatchCompiler::makeConstString("(") ||
                                    notstart.find(tok3->str()) != notstart.end()) {
                                    decl = true;
                                    break;
                                }
                            }
                        }
                    } else
                        decl = false;
                } else if (cpp && match314(prev2) && match315(tok2->link())) { // C++11 initialization style
                    if (tok2->link() != tok2->next() && // add value-initialized variable T x{};
                        (match316(prev2) || match317(prev2->tokAt(-2))))
                        continue;
                } else
                    decl = false;

                if (decl) {
                    if (isC() && match262(prev2->previous()))
                        syntaxErrorC(prev2, prev2->strAt(-2) + prev2->strAt(-1) + " " + prev2->str());
                    variableMap.addVariable(prev2->str(), scopeStack.size() <= 1);

                    if (match305(tok->previous()) && match318(prev2)) {
                        for (const Token *tok3 = prev2->next(); tok3 && tok3->str() != MatchCompiler::makeConstString(";"); tok3 = tok3->next()) {
                            if (match319(tok3))
                                tok3 = tok3->link();
                            if (match320(tok3))
                                variableMap.addVariable(tok3->strAt(1), false);
                        }
                    }

                    // set varid for template parameters..
                    tok = tok->next();
                    while (match293(tok))
                        tok = tok->next();
                    if (tok && tok->str() == MatchCompiler::makeConstString("<")) {
                        const Token *end = tok->findClosingBracket();
                        while (tok != end) {
                            if (tok->isName() && !(match146(tok->next()) &&
                                                   match175(tok->tokAt(-1)))) {
                                const auto it = variableMap.map(false).find(tok->str());
                                if (it != variableMap.map(false).end())
                                    tok->varId(it->second);
                            }
                            tok = tok->next();
                        }
                    }

                    tok = tok2->previous();
                }
            }
        }

        if (tok->isName() && !tok->isKeyword() && !tok->isStandardType()) {
            // don't set variable id after a struct|enum|union
            if (match321(tok->previous()) || (cpp && tok->strAt(-1) == MatchCompiler::makeConstString("class")))
                continue;

            bool globalNamespace = false;
            if (!isC()) {
                if (tok->previous() && tok->strAt(-1) == MatchCompiler::makeConstString("::")) {
                    if (match322(tok->tokAt(-2)))
                        continue;
                    globalNamespace = true;
                }
                if (tok->next() && tok->strAt(1) == MatchCompiler::makeConstString("::"))
                    continue;
                if (match323(tok->tokAt(-2)))
                    continue;
            }

            if (tok->str().back() == '>') {
                addTemplateVarIdUsage(tok->str(),
                                      mTemplateSimplifier->getUsedVariables(),
                                      variableMap.map(globalNamespace),
                                      mTemplateVarIdUsage);
            }

            // function declaration inside executable scope? Function declaration is of form: type name "(" args ")"
            if (scopeStack.top().isExecutable && !scopeStack.top().isStructInit && match324(tok)) {
                bool par = false;
                const Token* start;
                Token* end;

                // search begin of function declaration
                for (start = tok; match325(start); start = start->previous()) {
                    if (start->str() == MatchCompiler::makeConstString("(")) {
                        if (par)
                            break;
                        par = true;
                    }
                    if (match276(start)) {
                        if (!match326(start))
                            break;
                    }
                    if (start->varId() > 0)
                        break;
                }

                // search end of function declaration
                for (end = tok->next(); match327(end); end = end->next()) {}

                // there are tokens which can't appear at the begin of a function declaration such as "return"
                const bool isNotstartKeyword = start->next() && notstart.find(start->strAt(1)) != notstart.end();

                // now check if it is a function declaration
                if (match328(start) && par && match53(end) && !isNotstartKeyword) {
                    // function declaration => don't set varid
                    tok = end;
                    continue;
                }
            }

            if (tok->varId() == 0 && (!scopeStack.top().isEnum || !(match329(tok->previous()) && match330(tok->next()))) &&
                !match332(tok->next()) && !(tok->tokAt(-1) && match331(tok->tokAt(-2)))) {
                const auto it = variableMap.map(globalNamespace).find(tok->str());
                if (it != variableMap.map(globalNamespace).end()) {
                    tok->varId(it->second);
                    setVarIdStructMembers(tok, structMembers, variableMap.getVarId());
                }
            }
        } else if (match333(tok) && match334(tok->previous())) {
            // Don't set varid after a :: or . token
            tok = tok->next();
        } else if (tok->str() == MatchCompiler::makeConstString(":") && match335(tok->tokAt(-2))) {
            do {
                tok = tok->next();
            } while (tok && (tok->isName() || tok->str() == MatchCompiler::makeConstString(",")));
            if (!tok)
                break;
            tok = tok->previous();
        }
    }

    mVarId = variableMap.getVarId();
}

namespace {
    struct Member {
        Member(std::list<std::string> s, std::list<const Token *> ns, Token *t) : usingnamespaces(std::move(ns)), scope(std::move(s)), tok(t) {}
        std::list<const Token *> usingnamespaces;
        std::list<std::string> scope;
        Token *tok;
    };
}

static std::string getScopeName(const std::list<ScopeInfo2> &scopeInfo)
{
    std::string ret;
    for (const ScopeInfo2 &si : scopeInfo)
        ret += (ret.empty() ? "" : " :: ") + (si.name);
    return ret;
}

static Token * matchMemberName(const std::list<std::string> &scope, const Token *nsToken, Token *memberToken, const std::list<ScopeInfo2> &scopeInfo)
{
    auto scopeIt = scopeInfo.cbegin();

    // Current scope..
    for (auto it = scope.cbegin(); it != scope.cend(); ++it) {
        if (scopeIt == scopeInfo.cend() || scopeIt->name != *it)
            return nullptr;
        ++scopeIt;
    }

    // using namespace..
    if (nsToken) {
        while (match36(nsToken)) {
            if (scopeIt != scopeInfo.end() && nsToken->str() == scopeIt->name) {
                nsToken = nsToken->tokAt(2);
                ++scopeIt;
            } else {
                return nullptr;
            }
        }
        if (!match47(nsToken))
            return nullptr;
        if (scopeIt == scopeInfo.end() || nsToken->str() != scopeIt->name)
            return nullptr;
        ++scopeIt;
    }

    // Parse member tokens..
    while (scopeIt != scopeInfo.end()) {
        if (!match336(memberToken))
            return nullptr;
        if (memberToken->str() != scopeIt->name)
            return nullptr;
        if (memberToken->strAt(1) == MatchCompiler::makeConstString("<")) {
            memberToken = memberToken->next()->findClosingBracket();
            if (!match180(memberToken))
                return nullptr;
        }
        memberToken = memberToken->tokAt(2);
        ++scopeIt;
    }

    return match337(memberToken) ? memberToken : nullptr;
}

static Token * matchMemberName(const Member &member, const std::list<ScopeInfo2> &scopeInfo)
{
    if (scopeInfo.empty())
        return nullptr;

    // Does this member match without "using namespace"..
    Token *ret = matchMemberName(member.scope, nullptr, member.tok, scopeInfo);
    if (ret)
        return ret;

    // Try to match member using the "using namespace ..." namespaces..
    for (const Token *ns : member.usingnamespaces) {
        ret = matchMemberName(member.scope, ns, member.tok, scopeInfo);
        if (ret)
            return ret;
    }

    return nullptr;
}

static Token * matchMemberVarName(const Member &var, const std::list<ScopeInfo2> &scopeInfo)
{
    Token *tok = matchMemberName(var, scopeInfo);
    if (match24(tok)) {
        if (!tok->next() || tok->strAt(1) != MatchCompiler::makeConstString("(") || (tok->tokAt(2) && tok->tokAt(2)->isLiteral()))
            return tok;
    }
    return nullptr;
}

static Token * matchMemberFunctionName(const Member &func, const std::list<ScopeInfo2> &scopeInfo)
{
    Token *tok = matchMemberName(func, scopeInfo);
    return match338(tok) ? tok : nullptr;
}

template<typename T>
static T* skipInitializerList(T* tok)
{
    T* const start = tok;
    while (match339(tok)) {
        tok = tok->tokAt(tok->strAt(1) == MatchCompiler::makeConstString("::") ? 1 : 2);
        while (match175(tok))
            tok = tok->tokAt(2);
        if (!match340(tok) || !tok->link())
            return start;
        const bool isTemplate = tok->str() == MatchCompiler::makeConstString("<");
        tok = tok->link()->next();
        if (isTemplate && tok && tok->link())
            tok = tok->link()->next();
    }
    return tok;
}

void Tokenizer::setVarIdPass2()
{
    std::map<nonneg int, std::map<std::string, nonneg int>> structMembers;

    // Member functions and variables in this source
    std::list<Member> allMemberFunctions;
    std::list<Member> allMemberVars;
    if (!isC()) {
        std::map<const Token *, std::string> endOfScope;
        std::list<std::string> scope;
        std::list<const Token *> usingnamespaces;
        for (Token *tok = list.front(); tok; tok = tok->next()) {
            if (!tok->previous() || match42(tok->previous())) {
                if (match341(tok)) {
                    Token *endtok = tok->tokAt(2);
                    while (match36(endtok))
                        endtok = endtok->tokAt(2);
                    if (match47(endtok))
                        usingnamespaces.push_back(tok->tokAt(2));
                    tok = endtok;
                    continue;
                }
                if (match342(tok)) {
                    scope.push_back(tok->strAt(1));
                    endOfScope[tok->linkAt(2)] = tok->strAt(1);
                }
            }

            if (tok->str() == MatchCompiler::makeConstString("}")) {
                const auto it = utils::as_const(endOfScope).find(tok);
                if (it != endOfScope.cend())
                    scope.remove(it->second);
            }

            Token* const tok1 = tok;
            if (match343(tok))
                tok = tok->next();
            else if (match344(tok) && match345(tok->next()->findClosingBracket()))
                tok = tok->next()->findClosingBracket()->next();
            else if (usingnamespaces.empty() || tok->varId() || !tok->isName() || tok->isStandardType() || tok->tokType() == Token::eKeyword || tok->tokType() == Token::eBoolean ||
                     match346(tok->previous()) || match347(tok->previous()) || match11(tok) ||
                     (!tok->next() && match348(tok->previous())))
                continue;

            if (tok->strAt(-1) == MatchCompiler::makeConstString("::") && tok->tokAt(-2) && tok->tokAt(-2)->isName())
                continue;

            while (match349(tok)) {
                tok = tok->next();
                if (tok->str() == MatchCompiler::makeConstString("~"))
                    tok = tok->next();
                else if (match344(tok) && match345(tok->next()->findClosingBracket()))
                    tok = tok->next()->findClosingBracket()->next();
                else if (match36(tok))
                    tok = tok->next();
                else
                    break;
            }
            if (!tok->next())
                syntaxError(tok);
            if (match56(tok) && !(tok->tokAt(2) && tok->tokAt(2)->isLiteral()))
                allMemberFunctions.emplace_back(scope, usingnamespaces, tok1);
            else
                allMemberVars.emplace_back(scope, usingnamespaces, tok1);
        }
    }

    std::list<ScopeInfo2> scopeInfo;

    // class members..
    std::map<std::string, std::map<std::string, nonneg int>> varsByClass;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        while (tok->str() == MatchCompiler::makeConstString("}") && !scopeInfo.empty() && tok == scopeInfo.back().bodyEnd)
            scopeInfo.pop_back();

        if (!match350(tok))
            continue;

        const std::string &scopeName(getScopeName(scopeInfo));
        const std::string scopeName2(scopeName.empty() ? std::string() : (scopeName + " :: "));

        std::list<const Token*> classnameTokens{ tok->next() };
        Token* tokStart = tok->tokAt(2);
        while (match175(tokStart) || tokStart->str() == MatchCompiler::makeConstString("<")) {
            if (tokStart->str() == MatchCompiler::makeConstString("<")) {
                // skip the template part
                Token* closeTok = tokStart->findClosingBracket();
                if (!closeTok)
                    syntaxError(tok);
                tokStart = closeTok->next();
            } else {
                classnameTokens.push_back(tokStart->next());
                tokStart = tokStart->tokAt(2);
            }
            if (!tokStart)
                syntaxError(tok);
        }

        std::string classname;
        for (const Token *it : classnameTokens)
            classname += (classname.empty() ? "" : " :: ") + it->str();

        std::map<std::string, nonneg int> &thisClassVars = varsByClass[scopeName2 + classname];
        while (match351(tokStart)) {
            if (match344(tokStart)) { // TODO: why skip templates?
                tokStart = tokStart->next()->findClosingBracket();
                if (tokStart)
                    tokStart = tokStart->next();
                continue;
            }
            if (match352(tokStart)) {
                std::string baseClassName = tokStart->str();
                const Token* baseStart = tokStart;
                while (match36(baseStart->tokAt(-2))) { // build base class name
                    baseClassName.insert(0, baseStart->strAt(-2) + " :: ");
                    baseStart = baseStart->tokAt(-2);
                }
                std::string scopeName3(scopeName2);
                while (!scopeName3.empty()) {
                    std::string name = scopeName3 + baseClassName;
                    if (varsByClass.find(name) != varsByClass.end()) {
                        baseClassName = std::move(name);
                        break;
                    }
                    // Remove last scope name
                    if (scopeName3.size() <= 8)
                        break;
                    scopeName3.erase(scopeName3.size() - 4);
                    const std::string::size_type pos = scopeName3.rfind(" :: ");
                    if (pos == std::string::npos)
                        break;
                    scopeName3.erase(pos + 4);
                }
                const std::map<std::string, nonneg int>& baseClassVars = varsByClass[baseClassName];
                thisClassVars.insert(baseClassVars.cbegin(), baseClassVars.cend());
            }
            tokStart = tokStart->next();
        }
        if (!match1(tokStart))
            continue;

        // What member variables are there in this class?
        std::transform(classnameTokens.cbegin(), classnameTokens.cend(), std::back_inserter(scopeInfo), [&](const Token* tok) {
            return ScopeInfo2(tok->str(), tokStart->link());
        });

        for (Token *tok2 = tokStart->next(); tok2 && tok2 != tokStart->link(); tok2 = tok2->next()) {
            // skip parentheses..
            if (tok2->link()) {
                if (tok2->str() == MatchCompiler::makeConstString("(")) {
                    Token *funcstart = const_cast<Token*>(TokenList::isFunctionHead(tok2, "{"));
                    if (funcstart) {
                        setVarIdClassFunction(scopeName2 + classname, funcstart, funcstart->link(), thisClassVars, structMembers, mVarId);
                        tok2 = funcstart->link();
                        continue;
                    }
                }
                if (tok2->str() == MatchCompiler::makeConstString("{") && !match353(tok2->previous())) {
                    if (tok2->strAt(-1) == MatchCompiler::makeConstString(")"))
                        setVarIdClassFunction(scopeName2 + classname, tok2, tok2->link(), thisClassVars, structMembers, mVarId);
                    tok2 = tok2->link();
                } else if (match354(tok2)) {
                    tok2 = tok2->link();

                    // Skip initialization list
                    if (match355(tok2)) {
                        tok2 = skipInitializerList(tok2->next());
                        if (match1(tok2))
                            tok2 = tok2->link();
                    }
                }
            }

            // Found a member variable..
            else if (tok2->varId() > 0)
                thisClassVars[tok2->str()] = tok2->varId();
        }

        // Are there any member variables in this class?
        if (thisClassVars.empty())
            continue;

        // Member variables
        for (const Member &var : allMemberVars) {
            Token *tok2 = matchMemberVarName(var, scopeInfo);
            if (!tok2)
                continue;
            if (tok2->varId() == 0)
                tok2->varId(thisClassVars[tok2->str()]);
        }

        if (isC() || tok->str() == MatchCompiler::makeConstString("namespace"))
            continue;

        // Set variable ids in member functions for this class..
        for (const Member &func : allMemberFunctions) {
            Token *tok2 = matchMemberFunctionName(func, scopeInfo);
            if (!tok2)
                continue;

            if (tok2->str() == MatchCompiler::makeConstString("~"))
                tok2 = tok2->linkAt(2);
            else
                tok2 = tok2->linkAt(1);

            // If this is a function implementation.. add it to funclist
            Token * start = const_cast<Token *>(TokenList::isFunctionHead(tok2, "{"));
            if (start) {
                setVarIdClassFunction(classname, start, start->link(), thisClassVars, structMembers, mVarId);
            }

            if (match356(tok2))
                tok2 = tok2->linkAt(2);

            // constructor with initializer list
            if (!match357(tok2))
                continue;

            Token *tok3 = tok2;
            while (match358(tok3)) {
                tok3 = tok3->tokAt(2);
                if (match175(tok3))
                    tok3 = tok3->next();
                while (match108(tok3))
                    tok3 = tok3->tokAt(2);
                if (!match359(tok3))
                    break;

                // set varid
                const auto varpos = utils::as_const(thisClassVars).find(tok3->str());
                if (varpos != thisClassVars.end())
                    tok3->varId(varpos->second);

                // goto end of var
                if (tok3->strAt(1) == MatchCompiler::makeConstString("<")) {
                    tok3 = tok3->next()->findClosingBracket();
                    if (tok3 && tok3->next() && tok3->linkAt(1))
                        tok3 = tok3->linkAt(1);
                } else
                    tok3 = tok3->linkAt(1);
            }
            if (match360(tok3)) {
                setVarIdClassFunction(classname, tok2, tok3->linkAt(1), thisClassVars, structMembers, mVarId);
            }
        }
    }
}

static void linkBrackets(const Tokenizer & tokenizer, std::stack<const Token*>& type, std::stack<Token*>& links, Token * const token, const char open, const char close)
{
    if (token->str()[0] == open) {
        links.push(token);
        type.push(token);
    } else if (token->str()[0] == close) {
        if (links.empty()) {
            // Error, { and } don't match.
            tokenizer.unmatchedToken(token);
        }
        if (type.top()->str()[0] != open) {
            tokenizer.unmatchedToken(type.top());
        }
        type.pop();

        Token::createMutualLinks(links.top(), token);
        links.pop();
    }
}

void Tokenizer::createLinks()
{
    std::stack<const Token*> type;
    std::stack<Token*> links1;
    std::stack<Token*> links2;
    std::stack<Token*> links3;
    for (Token *token = list.front(); token; token = token->next()) {
        if (token->link()) {
            token->link(nullptr);
        }

        linkBrackets(*this, type, links1, token, '{', '}');

        linkBrackets(*this, type, links2, token, '(', ')');

        linkBrackets(*this, type, links3, token, '[', ']');
    }

    if (!links1.empty()) {
        // Error, { and } don't match.
        unmatchedToken(links1.top());
    }

    if (!links2.empty()) {
        // Error, ( and ) don't match.
        unmatchedToken(links2.top());
    }

    if (!links3.empty()) {
        // Error, [ and ] don't match.
        unmatchedToken(links3.top());
    }
}

void Tokenizer::createLinks2()
{
    if (isC())
        return;

    bool isStruct = false;

    std::stack<Token*> type;
    std::stack<Token*> templateTokens;
    for (Token *token = list.front(); token; token = token->next()) {
        if (match361(token))
            isStruct = true;
        else if (match42(token))
            isStruct = false;

        if (token->link()) {
            if (match280(token))
                type.push(token);
            else if (!type.empty() && match362(token)) {
                while (type.top()->str() == MatchCompiler::makeConstString("<")) {
                    if (!templateTokens.empty() && templateTokens.top()->next() == type.top())
                        templateTokens.pop();
                    type.pop();
                }
                type.pop();
            }
        } else if (templateTokens.empty() && !isStruct && match363(token)) {
            if (match364(token))
                continue;
            // If there is some such code:  A<B||C>..
            // Then this is probably a template instantiation if either "B" or "C" has comparisons
            if (token->tokType() == Token::eLogicalOp && !type.empty() && type.top()->str() == MatchCompiler::makeConstString("<")) {
                const Token *prev = token->previous();
                bool foundComparison = false;
                while (match365(prev) && prev != type.top()) {
                    if (prev->str() == MatchCompiler::makeConstString(")") || prev->str() == MatchCompiler::makeConstString("]"))
                        prev = prev->link();
                    else if (prev->tokType() == Token::eLogicalOp)
                        break;
                    else if (prev->isComparisonOp())
                        foundComparison = true;
                    prev = prev->previous();
                }
                if (prev == type.top() && foundComparison)
                    continue;
                const Token *next = token->next();
                foundComparison = false;
                while (match366(next) && next->str() != MatchCompiler::makeConstString(">")) {
                    if (next->str() == MatchCompiler::makeConstString("(") || next->str() == MatchCompiler::makeConstString("["))
                        next = next->link();
                    else if (next->tokType() == Token::eLogicalOp)
                        break;
                    else if (next->isComparisonOp())
                        foundComparison = true;
                    next = next->next();
                }
                if (next && next->str() == MatchCompiler::makeConstString(">") && foundComparison)
                    continue;
            }

            while (!type.empty() && type.top()->str() == MatchCompiler::makeConstString("<")) {
                const Token* end = type.top()->findClosingBracket();
                if (match367(end))
                    break;
                // Variable declaration
                if (match368(end) && (type.top()->tokAt(-2) == nullptr || match369(type.top()->tokAt(-2))))
                    break;
                type.pop();
            }
        } else if (token->str() == MatchCompiler::makeConstString("<") &&
                   ((token->previous() && (token->previous()->isTemplate() ||
                                           (token->previous()->isName() && !token->previous()->varId()) ||
                                           (token->strAt(-1) == MatchCompiler::makeConstString("]") && (!match370(token->linkAt(-1)->previous()) || token->linkAt(-1)->previous()->isKeyword())) ||
                                           (token->strAt(-1) == MatchCompiler::makeConstString(")") && token->linkAt(-1)->strAt(-1) == MatchCompiler::makeConstString("operator")))) ||
                    match181(token->next()))) {
            type.push(token);
            if (token->strAt(-1) == MatchCompiler::makeConstString("template"))
                templateTokens.push(token);
        } else if (token->str() == MatchCompiler::makeConstString(">") || token->str() == MatchCompiler::makeConstString(">>")) {
            if (type.empty() || type.top()->str() != MatchCompiler::makeConstString("<")) // < and > don't match.
                continue;
            Token * const top1 = type.top();
            type.pop();
            Token * const top2 = type.empty() ? nullptr : type.top();
            type.push(top1);
            if (!top2 || top2->str() != MatchCompiler::makeConstString("<")) {
                if (token->str() == MatchCompiler::makeConstString(">>"))
                    continue;
                if (!match371(token->next()) &&
                    !match372(token->next()))
                    continue;
            }

            if (token->str() == MatchCompiler::makeConstString(">>") && top1 && top2) {
                type.pop();
                type.pop();
                // Split the angle brackets
                token->str(">");
                Token::createMutualLinks(top1, token->insertTokenBefore(">"));
                Token::createMutualLinks(top2, token);
                if (templateTokens.size() == 2 && (top1 == templateTokens.top() || top2 == templateTokens.top())) {
                    templateTokens.pop();
                    templateTokens.pop();
                }
            } else {
                type.pop();
                if (match373(token) && !token->next()->isKeyword() &&
                    match374(top1->tokAt(-2)) && top1->strAt(-2) != MatchCompiler::makeConstString("<") &&
                    (templateTokens.empty() || top1 != templateTokens.top()))
                    continue;
                Token::createMutualLinks(top1, token);
                if (!templateTokens.empty() && top1 == templateTokens.top())
                    templateTokens.pop();
            }
        }
    }
}

void Tokenizer::markCppCasts()
{
    if (isC())
        return;
    for (Token* tok = list.front(); tok; tok = tok->next()) {
        if (match375(tok)) {
            if (!match146(tok->next()) || !match149(tok->linkAt(1)))
                syntaxError(tok);
            tok = tok->linkAt(1)->next();
            tok->isCast(true);
        }
    }

}

void Tokenizer::sizeofAddParentheses()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!match376(tok))
            continue;
        if (tok->next()->isLiteral() || match377(tok->next())) {
            Token *endToken = tok->next();
            while (match378(endToken))
                endToken = endToken->next();
            while (match379(endToken->next()) || (match380(endToken))) {
                if (match68(endToken->next()))
                    endToken = endToken->linkAt(1);
                else
                    endToken = endToken->next();
            }

            // Add ( after sizeof and ) behind endToken
            tok->insertToken("(");
            endToken->insertToken(")");
            Token::createMutualLinks(tok->next(), endToken->next());
        }
    }
}

bool Tokenizer::simplifyTokenList1(const char FileName[])
{
    if (Settings::terminated())
        return false;

    // if MACRO
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (match381(tok)) {
            if (match382(tok)) {
                // 'for each (x in y )' -> 'for (x : y)'
                if (Token* in = findmatch383(tok->tokAt(2), tok->linkAt(2)) )
                    in->str(":");
                tok->deleteNext();
            } else if (tok->strAt(1) == MatchCompiler::makeConstString("constexpr")) {
                tok->deleteNext();
                tok->isConstexpr(true);
            } else {
                syntaxError(tok);
            }
        }
    }

    // Is there C++ code in C file?
    validateC();

    // Combine strings and character literals, e.g. L"string", L'c', "string1" "string2"
    combineStringAndCharLiterals();

    // replace inline SQL with "asm()" (Oracle PRO*C). Ticket: #1959
    simplifySQL();

    createLinks();

    // replace library function calls such as (std::min)(a, b) with std::min(a, b)
    simplifyParenthesizedLibraryFunctions();

    // Simplify debug intrinsics
    simplifyDebug();

    removePragma();

    // Simplify the C alternative tokens (and, or, etc.)
    simplifyCAlternativeTokens();

    simplifyFunctionTryCatch();

    simplifyHeadersAndUnusedTemplates();

    // Remove __asm..
    simplifyAsm();

    // foo < bar < >> => foo < bar < > >
    if (isCPP() || mSettings.daca)
        splitTemplateRightAngleBrackets(!isCPP());

    // Remove extra "template" tokens that are not used by cppcheck
    removeExtraTemplateKeywords();

    simplifySpaceshipOperator();

    // @..
    simplifyAt();

    // Remove __declspec()
    simplifyDeclspec();

    // Remove "inline", "register", and "restrict"
    simplifyKeyword();

    // Remove [[attribute]]
    simplifyCPPAttribute();

    // remove __attribute__((?))
    simplifyAttribute();

    validate();

    const SHOWTIME_MODES showTime = mTimerResults ? mSettings.showtime : SHOWTIME_MODES::SHOWTIME_NONE;

    // Bail out if code is garbage
    Timer::run("Tokenizer::simplifyTokens1::simplifyTokenList1::findGarbageCode", showTime, mTimerResults, [&]() {
        findGarbageCode();
    });

    checkConfiguration();

    // if (x) MACRO() ..
    for (const Token *tok = list.front(); tok; tok = tok->next()) {
        if (match384(tok)) {
            tok = tok->linkAt(1);
            if (match356(tok) &&
                tok->next()->isUpperCaseName() &&
                match385(tok->linkAt(2))) {
                syntaxError(tok->next());
            }
        }
    }

    if (Settings::terminated())
        return false;

    // convert C++17 style nested namespaces to old style namespaces
    simplifyNestedNamespace();

    // convert c++20 coroutines
    simplifyCoroutines();

    // simplify namespace aliases
    simplifyNamespaceAliases();

    // simplify cppcheck attributes __cppcheck_?__(?)
    simplifyCppcheckAttribute();

    // Combine tokens..
    combineOperators();

    // combine "- %num%"
    concatenateNegativeNumberAndAnyPositive();

    // remove extern "C" and extern "C" {}
    if (isCPP())
        simplifyExternC();

    // simplify compound statements: "[;{}] ( { code; } ) ;"->"[;{}] code;"
    simplifyCompoundStatements();

    // check for simple syntax errors..
    for (const Token *tok = list.front(); tok; tok = tok->next()) {
        if (match386(tok) &&
            match315(tok->linkAt(2))) {
            syntaxError(tok);
        }
    }

    if (!simplifyAddBraces())
        return false;

    sizeofAddParentheses();

    // Simplify: 0[foo] -> *(foo)
    for (Token* tok = list.front(); tok; tok = tok->next()) {
        if (match387(tok) && tok->linkAt(1)) {
            tok->str("*");
            tok->next()->str("(");
            tok->linkAt(1)->str(")");
        }
    }

    if (Settings::terminated())
        return false;

    validate();

    // simplify simple calculations inside <..>
    if (isCPP()) {
        Token *lt = nullptr;
        for (Token *tok = list.front(); tok; tok = tok->next()) {
            if (match42(tok))
                lt = nullptr;
            else if (match388(tok))
                lt = tok->next();
            else if (lt && match389(tok)) {
                const Token * const end = tok;
                for (tok = lt; tok != end; tok = tok->next()) {
                    if (tok->isNumber())
                        TemplateSimplifier::simplifyNumericCalculations(tok);
                }
                lt = tok->next();
            }
        }
    }

    // Convert K&R function declarations to modern C
    simplifyVarDecl(true);
    simplifyFunctionParameters();

    // simplify case ranges (gcc extension)
    simplifyCaseRange();

    // simplify labels and 'case|default'-like syntaxes
    simplifyLabelsCaseDefault();

    if (!isC() && !mSettings.library.markupFile(FileName)) {
        findComplicatedSyntaxErrorsInTemplates();
    }

    if (Settings::terminated())
        return false;

    // remove calling conventions __cdecl, __stdcall..
    simplifyCallingConvention();

    addSemicolonAfterUnknownMacro();

    // remove some unhandled macros in global scope
    removeMacrosInGlobalScope();

    // remove undefined macro in class definition:
    // class DLLEXPORT Fred { };
    // class Fred FINAL : Base { };
    removeMacroInClassDef();

    // That call here fixes #7190
    validate();

    // remove unnecessary member qualification..
    removeUnnecessaryQualification();

    // convert Microsoft memory functions
    simplifyMicrosoftMemoryFunctions();

    // convert Microsoft string functions
    simplifyMicrosoftStringFunctions();

    if (Settings::terminated())
        return false;

    // remove Borland stuff..
    simplifyBorland();

    // syntax error: enum with typedef in it
    checkForEnumsWithTypedef();

    // Add parentheses to ternary operator where necessary
    prepareTernaryOpForAST();

    // Change initialisation of variable to assignment
    simplifyInitVar();

    // Split up variable declarations.
    simplifyVarDecl(false);

    reportUnknownMacros();

    simplifyTypedefLHS();

    // typedef..
    Timer::run("Tokenizer::simplifyTokens1::simplifyTokenList1::simplifyTypedef", showTime, mTimerResults, [&]() {
        simplifyTypedef();
    });

    // using A = B;
    while (simplifyUsing())
        ;

    // Add parentheses to ternary operator where necessary
    // TODO: this is only necessary if one typedef simplification had a comma and was used within ?:
    // If typedef handling is refactored and moved to symboldatabase someday we can remove this
    prepareTernaryOpForAST();

    // class x y {
    if (isCPP() && mSettings.severity.isEnabled(Severity::information)) {
        for (const Token *tok = list.front(); tok; tok = tok->next()) {
            if (match390(tok)) {
                unhandled_macro_class_x_y(tok, tok->str(), tok->strAt(1), tok->strAt(2), tok->strAt(3));
            }
        }
    }

    // catch bad typedef canonicalization
    //
    // to reproduce bad typedef, download upx-ucl from:
    // http://packages.debian.org/sid/upx-ucl
    // analyse the file src/stub/src/i386-linux.elf.interp-main.c
    validate();

    // The simplify enum have inner loops
    if (Settings::terminated())
        return false;

    // Put ^{} statements in asm()
    simplifyAsm2();

    // When the assembly code has been cleaned up, no @ is allowed
    for (const Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->str() == MatchCompiler::makeConstString("(")) {
            const Token *tok1 = tok;
            tok = tok->link();
            if (!tok)
                syntaxError(tok1);
        } else if (tok->str() == MatchCompiler::makeConstString("@")) {
            syntaxError(tok);
        }
    }

    // Order keywords "static" and "const"
    simplifyStaticConst();

    // convert platform dependent types to standard types
    // 32 bits: size_t -> unsigned long
    // 64 bits: size_t -> unsigned long long
    list.simplifyPlatformTypes();

    // collapse compound standard types into a single token
    // unsigned long long int => long (with _isUnsigned=true,_isLong=true)
    list.simplifyStdType();

    if (Settings::terminated())
        return false;

    // simplify bit fields..
    simplifyBitfields();

    if (Settings::terminated())
        return false;

    // struct simplification "struct S {} s; => struct S { } ; S s ;
    simplifyStructDecl();

    if (Settings::terminated())
        return false;

    // x = ({ 123; });  =>   { x = 123; }
    simplifyAssignmentBlock();

    if (Settings::terminated())
        return false;

    simplifyVariableMultipleAssign();

    // Collapse operator name tokens into single token
    // operator = => operator=
    simplifyOperatorName();

    // Remove redundant parentheses
    simplifyRedundantParentheses();

    if (isCPP()) {
        simplifyTypeIntrinsics();

        // Handle templates..
        Timer::run("Tokenizer::simplifyTokens1::simplifyTokenList1::simplifyTemplates", showTime, mTimerResults, [&]() {
            simplifyTemplates();
        });

        // The simplifyTemplates have inner loops
        if (Settings::terminated())
            return false;

        validate(); // #6847 - invalid code
    }

    // Simplify pointer to standard types (C only)
    simplifyPointerToStandardType();

    // simplify function pointers
    simplifyFunctionPointers();

    // Change initialisation of variable to assignment
    simplifyInitVar();

    // Split up variable declarations.
    simplifyVarDecl(false);

    elseif();

    validate(); // #6772 "segmentation fault (invalid code) in Tokenizer::setVarId"

    Timer::run("Tokenizer::simplifyTokens1::simplifyTokenList1::setVarId", showTime, mTimerResults, [&](){
        setVarId();
    });

    // Link < with >
    createLinks2();

    // Mark C++ casts
    markCppCasts();

    // specify array size
    arraySize();

    // The simplify enum might have inner loops
    if (Settings::terminated())
        return false;

    // Add std:: in front of std classes, when using namespace std; was given
    simplifyNamespaceStd();

    // Change initialisation of variable to assignment
    simplifyInitVar();

    simplifyDoublePlusAndDoubleMinus();

    simplifyArrayAccessSyntax();

    Token::assignProgressValues(list.front());

    removeRedundantSemicolons();

    simplifyParameterVoid();

    simplifyRedundantConsecutiveBraces();

    simplifyEmptyNamespaces();

    simplifyIfSwitchForInit();

    simplifyOverloadedOperators();

    validate();

    list.front()->assignIndexes();

    return true;
}
//---------------------------------------------------------------------------

void Tokenizer::printDebugOutput(std::ostream &out) const
{
    if (!list.front())
        return;

    const bool debug = mSettings.debugSimplified || mSettings.debugnormal || mSettings.debugsymdb || mSettings.debugast || mSettings.debugvalueflow;
    if (!debug)
        return;

    const bool xml = (mSettings.outputFormat == Settings::OutputFormat::xml);

    if (xml)
        out << "<debug>" << std::endl;

    if (mSettings.debugSimplified || mSettings.debugnormal)
        list.front()->printOut(out, xml, nullptr, list.getFiles());

    if (mSymbolDatabase) {
        if (xml)
            mSymbolDatabase->printXml(out);
        else if (mSettings.debugsymdb)
            mSymbolDatabase->printOut("Symbol database");
    }

    if (mSettings.debugast)
        list.front()->printAst(xml, list.getFiles(), out);

    if (mSettings.debugvalueflow)
        list.front()->printValueFlow(list.getFiles(), xml, out);

    if (xml)
        out << "</debug>" << std::endl;
}

void Tokenizer::dump(std::ostream &out) const
{
    // Create a xml data dump.
    // The idea is not that this will be readable for humans. It's a
    // data dump that 3rd party tools could load and get useful info from.

    std::string outs;

    std::set<const Library::Container*> containers;

    outs += "  <directivelist>";
    outs += '\n';
    for (const Directive &dir : mDirectives) {
        outs += "    <directive ";
        outs += "file=\"";
        outs += ErrorLogger::toxml(Path::getRelativePath(dir.file, mSettings.basePaths));
        outs += "\" ";
        outs += "linenr=\"";
        outs += std::to_string(dir.linenr);
        outs += "\" ";
        // str might contain characters such as '"', '<' or '>' which
        // could result in invalid XML, so run it through toxml().
        outs += "str=\"";
        outs += ErrorLogger::toxml(dir.str);
        outs +="\">";
        outs += '\n';
        for (const auto & strToken : dir.strTokens) {
            outs += "      <token ";
            outs += "column=\"";
            outs += std::to_string(strToken.column);
            outs += "\" ";
            outs += "str=\"";
            outs += ErrorLogger::toxml(strToken.tokStr);
            outs +="\"/>";
            outs += '\n';
        }
        outs += "    </directive>";
        outs += '\n';
    }
    outs += "  </directivelist>";
    outs += '\n';

    // tokens..
    outs += "  <tokenlist>";
    outs += '\n';
    for (const Token *tok = list.front(); tok; tok = tok->next()) {
        outs += "    <token id=\"";
        outs += id_string(tok);
        outs += "\" file=\"";
        outs += ErrorLogger::toxml(list.file(tok));
        outs += "\" linenr=\"";
        outs += std::to_string(tok->linenr());
        outs += "\" column=\"";
        outs += std::to_string(tok->column());
        outs += "\"";

        outs += " str=\"";
        outs += ErrorLogger::toxml(tok->str());
        outs += '\"';

        outs += " scope=\"";
        outs += id_string(tok->scope());
        outs += '\"';
        if (tok->isName()) {
            outs += " type=\"name\"";
            if (tok->isUnsigned())
                outs += " isUnsigned=\"true\"";
            else if (tok->isSigned())
                outs += " isSigned=\"true\"";
        } else if (tok->isNumber()) {
            outs += " type=\"number\"";
            if (MathLib::isInt(tok->str()))
                outs += " isInt=\"true\"";
            if (MathLib::isFloat(tok->str()))
                outs += " isFloat=\"true\"";
        } else if (tok->tokType() == Token::eString) {
            outs += " type=\"string\" strlen=\"";
            outs += std::to_string(Token::getStrLength(tok));
            outs += '\"';
        }
        else if (tok->tokType() == Token::eChar)
            outs += " type=\"char\"";
        else if (tok->isBoolean())
            outs += " type=\"boolean\"";
        else if (tok->isOp()) {
            outs += " type=\"op\"";
            if (tok->isArithmeticalOp())
                outs += " isArithmeticalOp=\"true\"";
            else if (tok->isAssignmentOp())
                outs += " isAssignmentOp=\"true\"";
            else if (tok->isComparisonOp())
                outs += " isComparisonOp=\"true\"";
            else if (tok->tokType() == Token::eLogicalOp)
                outs += " isLogicalOp=\"true\"";
        }
        if (tok->isCast())
            outs += " isCast=\"true\"";
        if (tok->isExternC())
            outs += " externLang=\"C\"";
        if (tok->isExpandedMacro())
            outs += " macroName=\"" + tok->getMacroName() + "\"";
        if (tok->isTemplateArg()) {
            outs += " isTemplateArg=\"true\"";
            outs += " templateArgFileIndex=\"" + std::to_string(tok->templateArgFileIndex()) + "\"";
            outs += " templateArgLineNumber=\"" + std::to_string(tok->templateArgLineNumber()) + "\"";
            outs += " templateArgColumn=\"" + std::to_string(tok->templateArgColumn()) + "\"";
        }
        if (tok->isRemovedVoidParameter())
            outs += " isRemovedVoidParameter=\"true\"";
        if (tok->isSplittedVarDeclComma())
            outs += " isSplittedVarDeclComma=\"true\"";
        if (tok->isSplittedVarDeclEq())
            outs += " isSplittedVarDeclEq=\"true\"";
        if (tok->isImplicitInt())
            outs += " isImplicitInt=\"true\"";
        if (tok->isComplex())
            outs += " isComplex=\"true\"";
        if (tok->isRestrict())
            outs += " isRestrict=\"true\"";
        if (tok->isAtomic())
            outs += " isAtomic=\"true\"";
        if (tok->isAttributeExport())
            outs += " isAttributeExport=\"true\"";
        if (tok->isAttributeMaybeUnused())
            outs += " isAttributeMaybeUnused=\"true\"";
        if (tok->isAttributeUnused())
            outs += " isAttributeUnused=\"true\"";
        if (tok->isAttributeFallthrough())
            outs += " isAttributeFallthrough=\"true\"";
        if (tok->isInitBracket())
            outs += " isInitBracket=\"true\"";
        if (tok->isAnonymous())
            outs += " isAnonymous=\"true\"";
        if (tok->hasAttributeAlignas()) {
            const std::vector<std::string>& a = tok->getAttributeAlignas();
            outs += " alignas=\"" + ErrorLogger::toxml(a[0]) + "\"";
            if (a.size() > 1)
                // we could write all alignas expressions but currently we only need 2
                outs += " alignas2=\"" + ErrorLogger::toxml(a[1]) + "\"";
        }
        if (tok->link()) {
            outs += " link=\"";
            outs += id_string(tok->link());
            outs += '\"';
        }
        if (tok->varId() > 0) {
            outs += " varId=\"";
            outs += std::to_string(tok->varId());
            outs += '\"';
        }
        if (tok->exprId() > 0) {
            outs += " exprId=\"";
            outs += std::to_string(tok->exprId());
            outs += '\"';
        }
        if (tok->variable()) {
            outs += " variable=\"";
            outs += id_string(tok->variable());
            outs += '\"';
        }
        if (tok->function()) {
            outs += " function=\"";
            outs += id_string(tok->function());
            outs += '\"';
        }
        if (!tok->values().empty()) {
            outs += " values=\"";
            outs += id_string(&tok->values());
            outs += '\"';
        }
        if (tok->type()) {
            outs += " type-scope=\"";
            outs += id_string(tok->type()->classScope);
            outs += '\"';
        }
        if (tok->astParent()) {
            outs += " astParent=\"";
            outs += id_string(tok->astParent());
            outs += '\"';
        }
        if (tok->astOperand1()) {
            outs += " astOperand1=\"";
            outs += id_string(tok->astOperand1());
            outs += '\"';
        }
        if (tok->astOperand2()) {
            outs += " astOperand2=\"";
            outs += id_string(tok->astOperand2());
            outs += '\"';
        }
        if (!tok->originalName().empty()) {
            outs += " originalName=\"";
            outs += tok->originalName();
            outs += '\"';
        }
        if (tok->valueType()) {
            const std::string vt = tok->valueType()->dump();
            if (!vt.empty()) {
                outs += ' ';
                outs += vt;
            }
            containers.insert(tok->valueType()->container);
        }
        if (!tok->varId() && tok->scope()->isExecutable() && match56(tok)) {
            if (mSettings.library.isnoreturn(tok))
                outs += " noreturn=\"true\"";
        }

        outs += "/>";
        outs += '\n';
    }
    outs += "  </tokenlist>";
    outs += '\n';

    out << outs;
    outs.clear();

    if (mSymbolDatabase)
        mSymbolDatabase->printXml(out);

    containers.erase(nullptr);
    if (!containers.empty()) {
        outs += "  <containers>";
        outs += '\n';
        for (const Library::Container* c: containers) {
            outs += "    <container id=\"";
            outs += id_string(c);
            outs += "\" array-like-index-op=\"";
            outs += bool_to_string(c->arrayLike_indexOp);
            outs += "\" ";
            outs += "std-string-like=\"";
            outs += bool_to_string(c->stdStringLike);
            outs += "\"";
            if (c->functions.empty()) {
                outs += "/>\n";
                continue;
            }
            outs += ">\n";
            for (const auto& fp: c->functions) {
                std::string action;
                std::string yield;
                if (fp.second.action != Library::Container::Action::NO_ACTION)
                    action = " action=\"" + Library::Container::toString(fp.second.action) + "\"";
                if (fp.second.yield != Library::Container::Yield::NO_YIELD)
                    yield = " yield=\"" + Library::Container::toString(fp.second.yield) + "\"";
                if (!action.empty() || !yield.empty())
                    outs += "      <f name=\"" + fp.first + "\"" + action + yield + "/>\n";
            }
            outs += "    </container>\n";
        }
        outs += "  </containers>";
        outs += '\n';
    }

    if (list.front())
        list.front()->printValueFlow(list.getFiles(), true, out);

    outs += dumpTypedefInfo();

    outs += mTemplateSimplifier->dump();
    if (!mTemplateVarIdUsage.empty()) {
        outs += "  <template-varid-usage>\n";
        for (nonneg int id: mTemplateVarIdUsage)
            outs += "    <var id=\"" + std::to_string(id) + "\"/>\n";
        outs += "  </template-varid-usage>\n";
    }

    out << outs;
}

std::string Tokenizer::dumpTypedefInfo() const
{
    if (mTypedefInfo.empty())
        return "";
    std::string outs = "  <typedef-info>";
    outs += '\n';
    for (const TypedefInfo &typedefInfo: mTypedefInfo) {
        outs += "    <info";

        outs += " name=\"";
        outs += typedefInfo.name;
        outs += "\"";

        outs += " file=\"";
        outs += ErrorLogger::toxml(typedefInfo.filename);
        outs += "\"";

        outs += " line=\"";
        outs += std::to_string(typedefInfo.lineNumber);
        outs += "\"";

        outs += " column=\"";
        outs += std::to_string(typedefInfo.column);
        outs += "\"";

        outs += " used=\"";
        outs += std::to_string(typedefInfo.used?1:0);
        outs += "\"";

        outs += " isFunctionPointer=\"";
        outs += std::to_string(typedefInfo.isFunctionPointer);
        outs += "\"";

        outs += "/>";
        outs += '\n';
    }
    outs += "  </typedef-info>";
    outs += '\n';

    return outs;
}

void Tokenizer::simplifyHeadersAndUnusedTemplates()
{
    if (mSettings.checkHeaders && mSettings.checkUnusedTemplates)
        // Full analysis. All information in the headers are kept.
        return;

    const bool checkHeaders = mSettings.checkHeaders;
    const bool removeUnusedIncludedFunctions = !mSettings.checkHeaders;
    const bool removeUnusedIncludedClasses   = !mSettings.checkHeaders;
    const bool removeUnusedIncludedTemplates = !mSettings.checkUnusedTemplates || !mSettings.checkHeaders;
    const bool removeUnusedTemplates = !mSettings.checkUnusedTemplates;

    // checkHeaders:
    //
    // If it is true then keep all code in the headers. It's possible
    // to remove unused types/variables if false positives / false
    // negatives can be avoided.
    //
    // If it is false, then we want to remove selected stuff from the
    // headers but not *everything*. The intention here is to not damage
    // the analysis of the source file. You should get all warnings in
    // the source file. You should not get false positives.

    // functions and types to keep
    std::set<std::string> keep;
    for (const Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->isCpp() && match292(tok)) {
            const Token *closingBracket = tok->next()->findClosingBracket();
            if (match391(closingBracket))
                tok = closingBracket->linkAt(3);
        }

        if (!tok->isName() || tok->isKeyword())
            continue;

        if (!checkHeaders && tok->fileIndex() != 0)
            continue;

        if (match56(tok) && !match14(tok->linkAt(1))) {
            keep.insert(tok->str());
            continue;
        }

        if (match392(tok)) {
            keep.insert(tok->str());
        }
    }

    const std::set<std::string> functionStart{"static", "const", "unsigned", "signed", "void", "bool", "char", "short", "int", "long", "float", "*"};
    bool goBack = false;

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        const bool isIncluded = (tok->fileIndex() != 0);

        if (goBack) {
            tok = tok->previous();
        }
        goBack = false;

        // Remove executable code
        if (isIncluded && !mSettings.checkHeaders && tok->str() == MatchCompiler::makeConstString("{")) {
            // TODO: We probably need to keep the executable code if this function is called from the source file.
            const Token *prev = tok->previous();
            while (prev && prev->isName())
                prev = prev->previous();
            if (match40(prev)) {
                // Replace all tokens from { to } with a ";".
                Token::eraseTokens(tok,tok->link()->next());
                tok->str(";");
                tok->link(nullptr);
            }
        }

        if (!tok->previous() || match42(tok->previous())) {
            // Remove unused function declarations
            if (isIncluded && removeUnusedIncludedFunctions) {
                while (true) {
                    Token *start = tok;
                    while (start && functionStart.find(start->str()) != functionStart.end())
                        start = start->next();
                    if (match56(start) && match393(start->linkAt(1)) && keep.find(start->str()) == keep.end()) {
                        Token::eraseTokens(tok, start->linkAt(1)->tokAt(2));
                        tok->deleteThis();
                    } else
                        break;
                }
            }

            if (isIncluded && removeUnusedIncludedClasses) {
                if (match142(tok) && keep.find(tok->strAt(1)) == keep.end()) {
                    // Remove this class/struct
                    const Token *endToken = tok->tokAt(2);
                    if (endToken->str() == MatchCompiler::makeConstString(":")) {
                        endToken = endToken->next();
                        while (match394(endToken))
                            endToken = endToken->next();
                    }
                    if (endToken && endToken->str() == MatchCompiler::makeConstString("{") && match315(endToken->link())) {
                        Token::eraseTokens(tok, endToken->link()->next());
                        tok->deleteThis();
                    }
                }
            }

            if (removeUnusedTemplates || (isIncluded && removeUnusedIncludedTemplates)) {
                if (match395(tok)) {
                    const Token *closingBracket = tok->next()->findClosingBracket();
                    if (match396(closingBracket) && keep.find(closingBracket->strAt(2)) == keep.end()) {
                        const Token *endToken = closingBracket->tokAt(3);
                        if (endToken->str() == MatchCompiler::makeConstString(":")) {
                            endToken = endToken->next();
                            while (match394(endToken))
                                endToken = endToken->next();
                        }
                        if (endToken && endToken->str() == MatchCompiler::makeConstString("{"))
                            endToken = endToken->link()->next();
                        if (endToken && endToken->str() == MatchCompiler::makeConstString(";")) {
                            Token::eraseTokens(tok, endToken);
                            tok->deleteThis();
                        }
                    } else if (match397(closingBracket) && match14(closingBracket->linkAt(3)) && keep.find(closingBracket->strAt(2)) == keep.end()) {
                        const Token *endToken = closingBracket->linkAt(3)->linkAt(1)->next();
                        Token::eraseTokens(tok, endToken);
                        tok->deleteThis();
                        goBack = true;
                    }
                }
            }
        }
    }
}

void Tokenizer::removeExtraTemplateKeywords()
{
    if (isCPP()) {
        for (Token *tok = list.front(); tok; tok = tok->next()) {
            if (match398(tok)) {
                tok->next()->deleteNext();
                Token* templateName = tok->tokAt(2);
                while (match293(templateName)) {
                    templateName->isTemplate(true);
                    templateName = templateName->next();
                }
                if (!templateName)
                    syntaxError(tok);
                if (match399(templateName->previous())) {
                    templateName->isTemplate(true);
                    if (templateName->str() == MatchCompiler::makeConstString("(") && templateName->link())
                        templateName->link()->isTemplate(true);
                }
            }
        }
    }
}

static std::string getExpression(const Token *tok)
{
    std::string line;
    for (const Token *prev = tok->previous(); prev && !match42(prev); prev = prev->previous())
        line = prev->str() + " " + line;
    line += "!!!" + tok->str() + "!!!";
    for (const Token *next = tok->next(); next && !match42(next); next = next->next())
        line += " " + next->str();
    return line;
}

void Tokenizer::splitTemplateRightAngleBrackets(bool check)
{
    std::vector<std::pair<std::string, int>> vars;

    int scopeLevel = 0;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->str() == MatchCompiler::makeConstString("{"))
            ++scopeLevel;
        else if (tok->str() == MatchCompiler::makeConstString("}")) {
            vars.erase(std::remove_if(vars.begin(), vars.end(), [scopeLevel](const std::pair<std::string, int>& v) {
                return v.second == scopeLevel;
            }), vars.end());
            --scopeLevel;
        }
        if (match400(tok) && tok->next()->isStandardType())
            vars.emplace_back(tok->strAt(2), scopeLevel);

        // Ticket #6181: normalize C++11 template parameter list closing syntax
        if (tok->previous() && tok->str() == MatchCompiler::makeConstString("<") && TemplateSimplifier::templateParameters(tok) && std::none_of(vars.begin(), vars.end(), [&](const std::pair<std::string, int>& v) {
            return v.first == tok->strAt(-1);
        })) {
            Token *endTok = tok->findClosingBracket();
            if (check) {
                if (match401(endTok))
                    reportError(tok, Severity::debug, "dacaWrongSplitTemplateRightAngleBrackets", "bad closing bracket for !!!<!!!: " + getExpression(tok), false);
                continue;
            }
            if (endTok && endTok->str() == MatchCompiler::makeConstString(">>")) {
                endTok->str(">");
                endTok->insertToken(">");
            } else if (endTok && endTok->str() == MatchCompiler::makeConstString(">>=")) {
                endTok->str(">");
                endTok->insertToken("=");
                endTok->insertToken(">");
            }
        } else if (match402(tok) && std::none_of(vars.begin(), vars.end(), [&](const std::pair<std::string, int>& v) {
            return v.first == tok->strAt(1);
        })) {
            Token *endTok = tok->tokAt(2)->findClosingBracket();
            if (check) {
                if (match403(endTok))
                    reportError(tok, Severity::debug, "dacaWrongSplitTemplateRightAngleBrackets", "bad closing bracket for !!!<!!!: " + getExpression(tok), false);
                continue;
            }
            if (match404(endTok)) {
                endTok->str(">");
                endTok->insertToken(">");
            }
        }
    }
}

void Tokenizer::removeMacrosInGlobalScope()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->str() == MatchCompiler::makeConstString("(")) {
            tok = tok->link();
            if (match405(tok) &&
                !tok->next()->isStandardType() &&
                !tok->next()->isKeyword() &&
                !match406(tok->next()) &&
                tok->next()->isUpperCaseName())
                tok->deleteNext();
        }

        if (match12(tok) && tok->isUpperCaseName() &&
            (!tok->previous() || match42(tok->previous()) || (tok->previous()->isName() && endsWith(tok->strAt(-1), ':')))) {
            const Token *tok2 = tok->next();
            if (tok2 && tok2->str() == MatchCompiler::makeConstString("("))
                tok2 = tok2->link()->next();

            // Several unknown macros...
            while (match162(tok2) && tok2->isUpperCaseName())
                tok2 = tok2->linkAt(1)->next();

            if (match56(tok) && match407(tok2) &&
                !match408(tok2))
                unknownMacroError(tok);

            if (match162(tok) && match162(tok2) && !match409(tok2) && TokenList::isFunctionHead(tok2->next(), ":;{"))
                unknownMacroError(tok);

            // remove unknown macros before namespace|class|struct|union
            if (match410(tok2)) {
                // is there a "{" for?
                const Token *tok3 = tok2;
                while (tok3 && !match411(tok3))
                    tok3 = tok3->next();
                if (tok3 && tok3->str() == MatchCompiler::makeConstString("{")) {
                    Token::eraseTokens(tok, tok2);
                    tok->deleteThis();
                }
                continue;
            }

            // replace unknown macros before foo(
            /*
                        if (match162(tok2) && TokenList::isFunctionHead(tok2->next(), "{")) {
                            std::string typeName;
                            for (const Token* tok3 = tok; tok3 != tok2; tok3 = tok3->next())
                                typeName += tok3->str();
                            Token::eraseTokens(tok, tok2);
                            tok->str(typeName);
                        }
             */
            // remove unknown macros before foo::foo(
            if (match412(tok2)) {
                const Token *tok3 = tok2;
                while (match413(tok3))
                    tok3 = tok3->tokAt(2);
                if (match414(tok3) && tok3->str() == tok3->strAt(2)) {
                    Token::eraseTokens(tok, tok2);
                    tok->deleteThis();
                }
                continue;
            }
        }

        // Skip executable scopes
        if (tok->str() == MatchCompiler::makeConstString("{")) {
            const Token *prev = tok->previous();
            while (prev && prev->isName())
                prev = prev->previous();
            if (prev && prev->str() == MatchCompiler::makeConstString(")"))
                tok = tok->link();
        }
    }
}

//---------------------------------------------------------------------------

void Tokenizer::removePragma()
{
    if (isC() && mSettings.standards.c == Standards::C89)
        return;
    if (isCPP() && mSettings.standards.cpp == Standards::CPP03)
        return;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        while (match415(tok)) {
            Token::eraseTokens(tok, tok->linkAt(1)->next());
            tok->deleteThis();
        }
    }
}

//---------------------------------------------------------------------------

void Tokenizer::removeMacroInClassDef()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!match416(tok))
            continue;

        const bool nextIsUppercase = tok->next()->isUpperCaseName();
        const bool afterNextIsUppercase = tok->tokAt(2)->isUpperCaseName();
        if (nextIsUppercase && !afterNextIsUppercase)
            tok->deleteNext();
        else if (!nextIsUppercase && afterNextIsUppercase)
            tok->next()->deleteNext();
    }
}

//---------------------------------------------------------------------------

void Tokenizer::addSemicolonAfterUnknownMacro()
{
    if (!isCPP())
        return;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->str() != MatchCompiler::makeConstString(")"))
            continue;
        const Token *macro = tok->link() ? tok->link()->previous() : nullptr;
        if (!macro || !macro->isName())
            continue;
        if (match417(tok) && !match39(macro))
            tok->insertToken(";");
        else if (match418(tok))
            tok->insertToken(";");
    }
}
//---------------------------------------------------------------------------

void Tokenizer::simplifyEmptyNamespaces()
{
    if (isC())
        return;

    bool goback = false;
    for (Token *tok = list.front(); tok; tok = tok ? tok->next() : nullptr) {
        if (goback) {
            tok = tok->previous();
            goback = false;
        }
        if (match419(tok)) {
            tok = tok->link();
            continue;
        }
        if (!match420(tok))
            continue;
        const bool isAnonymousNS = tok->strAt(1) == MatchCompiler::makeConstString("{");
        if (tok->strAt(3 - isAnonymousNS) == MatchCompiler::makeConstString("}")) {
            tok->deleteNext(3 - isAnonymousNS); // remove '%name%| { }'
            if (!tok->previous()) {
                // remove 'namespace' or replace it with ';' if isolated
                tok->deleteThis();
                goback = true;
            } else {                    // '%any% namespace %any%'
                tok = tok->previous();  // goto previous token
                tok->deleteNext();      // remove next token: 'namespace'
                if (tok->str() == MatchCompiler::makeConstString("{")) {
                    // Go back in case we were within a namespace that's empty now
                    tok = tok->tokAt(-2) ? tok->tokAt(-2) : tok->previous();
                    goback = true;
                }
            }
        } else {
            tok = tok->tokAt(2 - isAnonymousNS);
        }
    }
}

void Tokenizer::removeRedundantSemicolons()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->link() && tok->str() == MatchCompiler::makeConstString("(")) {
            tok = tok->link();
            continue;
        }
        for (;;) {
            if (match421(tok)) {
                tok->deleteNext();
            } else if (match422(tok)) {
                tok->deleteNext(3);
            } else {
                break;
            }
        }
    }
}


bool Tokenizer::simplifyAddBraces()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        Token const * tokRet=simplifyAddBracesToCommand(tok);
        if (!tokRet)
            return false;
    }
    return true;
}

Token *Tokenizer::simplifyAddBracesToCommand(Token *tok)
{
    Token * tokEnd=tok;
    if (match423(tok)) {
        tokEnd=simplifyAddBracesPair(tok,true);
    } else if (tok->str()==MatchCompiler::makeConstString("while")) {
        Token *tokPossibleDo=tok->previous();
        if (match1(tok->previous()))
            tokPossibleDo = nullptr;
        else if (match41(tokPossibleDo))
            tokPossibleDo = tokPossibleDo->link();
        if (!tokPossibleDo || tokPossibleDo->strAt(-1) != MatchCompiler::makeConstString("do"))
            tokEnd=simplifyAddBracesPair(tok,true);
    } else if (tok->str()==MatchCompiler::makeConstString("do")) {
        tokEnd=simplifyAddBracesPair(tok,false);
        if (tokEnd!=tok) {
            // walk on to next token, i.e. "while"
            // such that simplifyAddBracesPair does not close other braces
            // before the "while"
            if (tokEnd) {
                tokEnd=tokEnd->next();
                if (!tokEnd || tokEnd->str()!=MatchCompiler::makeConstString("while")) // no while
                    syntaxError(tok);
            }
        }
    } else if (tok->str()==MatchCompiler::makeConstString("if") && !match424(tok->tokAt(-2))) {
        tokEnd=simplifyAddBracesPair(tok,true);
        if (!tokEnd)
            return nullptr;
        if (tokEnd->strAt(1) == MatchCompiler::makeConstString("else")) {
            Token * tokEndNextNext= tokEnd->tokAt(2);
            if (!tokEndNextNext || tokEndNextNext->str() == MatchCompiler::makeConstString("}"))
                syntaxError(tokEndNextNext);
            if (tokEndNextNext->str() == MatchCompiler::makeConstString("if"))
                // do not change "else if ..." to "else { if ... }"
                tokEnd=simplifyAddBracesToCommand(tokEndNextNext);
            else
                tokEnd=simplifyAddBracesPair(tokEnd->next(),false);
        }
    }

    return tokEnd;
}

Token *Tokenizer::simplifyAddBracesPair(Token *tok, bool commandWithCondition)
{
    Token * tokCondition=tok->next();
    if (!tokCondition) // Missing condition
        return tok;

    Token *tokAfterCondition=tokCondition;
    if (commandWithCondition) {
        if (tokCondition->str()==MatchCompiler::makeConstString("("))
            tokAfterCondition=tokCondition->link();
        else
            syntaxError(tok); // Bad condition

        if (!tokAfterCondition || tokAfterCondition->strAt(1) == MatchCompiler::makeConstString("]"))
            syntaxError(tok); // Bad condition

        tokAfterCondition=tokAfterCondition->next();
        if (!tokAfterCondition || match425(tokAfterCondition)) {
            // No tokens left where to add braces around
            return tok;
        }
    }
    // Skip labels
    Token * tokStatement = tokAfterCondition;
    while (true) {
        if (match426(tokStatement))
            tokStatement = tokStatement->tokAt(2);
        else if (tokStatement->str() == MatchCompiler::makeConstString("case")) {
            tokStatement = skipCaseLabel(tokStatement);
            if (!tokStatement)
                return tok;
            if (tokStatement->str() != MatchCompiler::makeConstString(":"))
                syntaxError(tokStatement);
            tokStatement = tokStatement->next();
        } else
            break;
        if (!tokStatement)
            return tok;
    }
    Token * tokBracesEnd=nullptr;
    if (tokStatement->str() == MatchCompiler::makeConstString("{")) {
        // already surrounded by braces
        if (tokStatement != tokAfterCondition) {
            // Move the opening brace before labels
            Token::move(tokStatement, tokStatement, tokAfterCondition->previous());
        }
        tokBracesEnd = tokStatement->link();
    } else if (match427(tokStatement) &&
               match428(tokStatement->linkAt(1))) {
        tokAfterCondition->previous()->insertToken("{");
        Token * tokOpenBrace = tokAfterCondition->previous();
        Token * tokEnd = tokStatement->linkAt(1)->linkAt(2)->linkAt(1);
        if (!tokEnd) {
            syntaxError(tokStatement);
        }
        tokEnd->insertToken("}");
        Token * tokCloseBrace = tokEnd->next();
        tokCloseBrace->column(tokEnd->column());

        Token::createMutualLinks(tokOpenBrace, tokCloseBrace);
        tokBracesEnd = tokCloseBrace;
    } else {
        Token * tokEnd = simplifyAddBracesToCommand(tokStatement);
        if (!tokEnd) // Ticket #4887
            return tok;
        if (tokEnd->str()!=MatchCompiler::makeConstString("}")) {
            // Token does not end with brace
            // Look for ; to add own closing brace after it
            while (tokEnd && !match429(tokEnd)) {
                if (tokEnd->tokType()==Token::eBracket || tokEnd->str() == MatchCompiler::makeConstString("(")) {
                    tokEnd = tokEnd->link();
                    if (!tokEnd) {
                        // Inner bracket does not close
                        return tok;
                    }
                }
                tokEnd=tokEnd->next();
            }
            if (!tokEnd || tokEnd->str() != MatchCompiler::makeConstString(";")) {
                // No trailing ;
                if (tokStatement->isUpperCaseName())
                    unknownMacroError(tokStatement);
                else
                    syntaxError(tokStatement);
            }
        }

        tokAfterCondition->previous()->insertToken("{");
        Token * tokOpenBrace=tokAfterCondition->previous();

        tokEnd->insertToken("}");
        Token * tokCloseBrace=tokEnd->next();
        tokCloseBrace->column(tokEnd->column());

        Token::createMutualLinks(tokOpenBrace,tokCloseBrace);
        tokBracesEnd=tokCloseBrace;
    }

    return tokBracesEnd;
}

void Tokenizer::simplifyFunctionParameters()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->link() && match280(tok)) {
            tok = tok->link();
        }

        // Find the function e.g. foo( x ) or foo( x, y )
        else if (match430(tok) &&
                 !(tok->strAt(-1) == MatchCompiler::makeConstString(":") || tok->strAt(-1) == MatchCompiler::makeConstString(",") || tok->strAt(-1) == MatchCompiler::makeConstString("::"))) {
            // We have found old style function, now we need to change it

            // First step: Get list of argument names in parentheses
            std::map<std::string, Token *> argumentNames;
            bool bailOut = false;
            const Token * tokparam = nullptr;

            //take count of the function name..
            const std::string& funcName(tok->str());

            //floating token used to check for parameters
            Token *tok1 = tok;

            while (nullptr != (tok1 = tok1->tokAt(2))) {
                if (!match431(tok1)) {
                    bailOut = true;
                    break;
                }

                //same parameters: take note of the parameter
                if (argumentNames.find(tok1->str()) != argumentNames.end())
                    tokparam = tok1;
                else if (tok1->str() != funcName)
                    argumentNames[tok1->str()] = tok1;
                else {
                    if (tok1->strAt(1) == MatchCompiler::makeConstString(")")) {
                        if (tok1->strAt(-1) == MatchCompiler::makeConstString(",")) {
                            tok1 = tok1->tokAt(-2);
                            tok1->deleteNext(2);
                        } else {
                            tok1 = tok1->previous();
                            tok1->deleteNext();
                            bailOut = true;
                            break;
                        }
                    } else {
                        tok1 = tok1->tokAt(-2);
                        tok1->next()->deleteNext(2);
                    }
                }

                if (tok1->strAt(1) == MatchCompiler::makeConstString(")")) {
                    tok1 = tok1->tokAt(2);
                    //expect at least a type name after round brace..
                    if (!tok1 || !tok1->isName())
                        bailOut = true;
                    break;
                }
            }

            //goto '('
            tok = tok->next();

            if (bailOut) {
                tok = tok->link();
                continue;
            }

            tok1 = tok->link()->next();

            // there should be the sequence '; {' after the round parentheses
            for (const Token* tok2 = tok1; tok2; tok2 = tok2->next()) {
                if (match432(tok2))
                    break;
                if (tok2->str() == MatchCompiler::makeConstString("{")) {
                    bailOut = true;
                    break;
                }
            }

            if (bailOut) {
                tok = tok->link();
                continue;
            }

            // Last step: check out if the declarations between ')' and '{' match the parameters list
            std::map<std::string, Token *> argumentNames2;

            while (tok1 && tok1->str() != MatchCompiler::makeConstString("{")) {
                if (match433(tok1)) {
                    bailOut = true;
                    break;
                }
                if (tok1->str() == MatchCompiler::makeConstString(";")) {
                    if (tokparam) {
                        syntaxError(tokparam);
                    }
                    Token *tok2 = tok1->previous();
                    while (tok2->str() == MatchCompiler::makeConstString("]"))
                        tok2 = tok2->link()->previous();

                    //it should be a name..
                    if (!tok2->isName()) {
                        bailOut = true;
                        break;
                    }

                    if (argumentNames2.find(tok2->str()) != argumentNames2.end()) {
                        //same parameter names...
                        syntaxError(tok1);
                    } else
                        argumentNames2[tok2->str()] = tok2;

                    if (argumentNames.find(tok2->str()) == argumentNames.end()) {
                        //non-matching parameter... bailout
                        bailOut = true;
                        break;
                    }
                }
                tok1 = tok1->next();
            }

            if (bailOut || !tok1) {
                tok = tok->link();
                continue;
            }

            //the two containers may not hold the same size...
            //in that case, the missing parameters are defined as 'int'
            if (argumentNames.size() != argumentNames2.size()) {
                //move back 'tok1' to the last ';'
                tok1 = tok1->previous();
                for (const std::pair<const std::string, Token *>& argumentName : argumentNames) {
                    if (argumentNames2.find(argumentName.first) == argumentNames2.end()) {
                        //add the missing parameter argument declaration
                        tok1->insertToken(";");
                        tok1->insertToken(argumentName.first);
                        //register the change inside argumentNames2
                        argumentNames2[argumentName.first] = tok1->next();
                        tok1->insertToken("int");
                    }
                }
            }

            while (tok->str() != MatchCompiler::makeConstString(")")) {
                //initialize start and end tokens to be moved
                Token *declStart = argumentNames2[tok->strAt(1)];
                Token *declEnd = declStart;
                while (declStart->strAt(-1) != MatchCompiler::makeConstString(";") && declStart->strAt(-1) != MatchCompiler::makeConstString(")"))
                    declStart = declStart->previous();
                while (declEnd->strAt(1) != MatchCompiler::makeConstString(";") && declEnd->strAt(1) != MatchCompiler::makeConstString("{"))
                    declEnd = declEnd->next();

                //remove ';' after declaration
                declEnd->deleteNext();

                //replace the parameter name in the parentheses with all the declaration
                Token::replace(tok->next(), declStart, declEnd);

                //since there are changes to tokens, put tok where tok1 is
                tok = declEnd->next();

                //fix up line number
                if (tok->str() == MatchCompiler::makeConstString(","))
                    tok->linenr(tok->previous()->linenr());
            }
            //goto forward and continue
            tok = tok->linkAt(1);
        }
    }
}

void Tokenizer::simplifyPointerToStandardType()
{
    if (!isC())
        return;

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!match434(tok))
            continue;

        if (!match435(tok->previous()))
            continue;

        // Remove '[ 0 ]' suffix
        Token::eraseTokens(tok->next(), tok->tokAt(5));
        // Remove '&' prefix
        tok = tok->previous();
        if (!tok)
            break;
        tok->deleteNext();
    }
}

void Tokenizer::simplifyFunctionPointers()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        // #2873 - do not simplify function pointer usage here:
        // (void)(xy(*p)(0));
        if (match59(tok)) {
            tok = tok->linkAt(1);
            continue;
        }

        // check for function pointer cast
        if (match436(tok) ||
            match437(tok)) {
            Token *tok1 = tok;

            if (tok1->isCpp() && tok1->str() == MatchCompiler::makeConstString("static_cast"))
                tok1 = tok1->next();

            tok1 = tok1->next();

            if (match12(tok1->next()))
                tok1 = tok1->next();

            while (tok1->strAt(1) == MatchCompiler::makeConstString("*"))
                tok1 = tok1->next();

            // check that the cast ends
            if (!match438(tok1->linkAt(4)))
                continue;

            // ok simplify this function pointer cast to an ordinary pointer cast
            tok1->deleteNext();
            tok1->next()->deleteNext();
            Token::eraseTokens(tok1->next(), tok1->linkAt(2)->next());
            continue;
        }

        // check for start of statement
        if (tok->previous() && !match439(tok->previous()))
            continue;

        if (match440(tok))
            continue;

        while (match441(tok))
            tok = tok->next();

        Token *tok2 = (tok && tok->isName()) ? tok->next() : nullptr;
        while (match34(tok2))
            tok2 = tok2->next();
        if (!tok2 || tok2->str() != MatchCompiler::makeConstString("("))
            continue;
        while (match442(tok2))
            tok2 = tok2->tokAt(2);
        if (!match443(tok2))
            continue;
        tok2 = tok2->tokAt(2);
        if (tok2->str() == MatchCompiler::makeConstString("*"))
            tok2 = tok2->next();
        while (match441(tok2))
            tok2 = tok2->next();

        if (!match104(tok2) &&
            !match444(tok2) &&
            !(match56(tok2) && match131(tok2->linkAt(1))))
            continue;

        while (tok && tok->str() != MatchCompiler::makeConstString("("))
            tok = tok->next();

        // check that the declaration ends
        if (!tok || !tok->link() || !tok->link()->next()) {
            syntaxError(nullptr);
        }
        Token *endTok = tok->link()->linkAt(1);
        if (match445(endTok))
            endTok = endTok->linkAt(2);
        if (!match446(endTok))
            continue;

        while (match23(endTok->next()))
            endTok->deleteNext();

        // ok simplify this function pointer to an ordinary pointer
        if (match447(tok->link()->previous())) {
            // Function returning function pointer
            // void (*dostuff(void))(void) {}
            Token::eraseTokens(tok->link(), endTok->next());
            tok->link()->deleteThis();
            tok->deleteThis();
        } else {
            Token::eraseTokens(tok->link()->linkAt(1), endTok->next());

            // remove variable names
            int indent = 0;
            for (Token* tok3 = tok->link()->tokAt(2); match448(tok3); tok3 = tok3->next()) {
                if (tok3->str() == MatchCompiler::makeConstString(")") && --indent < 0)
                    break;
                if (tok3->str() == MatchCompiler::makeConstString("<") && tok3->link())
                    tok3 = tok3->link();
                else if (match69(tok3))
                    tok3 = tok3->link();
                else if (tok3->str() == MatchCompiler::makeConstString("(")) {
                    tok3 = tok3->link();
                    if (match59(tok3)) {
                        tok3 = tok3->next();
                        ++indent;
                    } else
                        break;
                }
                if (match449(tok3))
                    tok3->deleteNext();
            }

            // TODO Keep this info
            while (match450(tok))
                tok->deleteNext(2);
        }
    }
}

void Tokenizer::simplifyVarDecl(const bool only_k_r_fpar)
{
    simplifyVarDecl(list.front(), nullptr, only_k_r_fpar);
}

// cppcheck-suppress functionConst - has side effects
void Tokenizer::simplifyVarDecl(Token * tokBegin, const Token * const tokEnd, const bool only_k_r_fpar)
{
    const bool cpp = isCPP();
    const bool isCPP11 = cpp && (mSettings.standards.cpp >= Standards::CPP11);

    // Split up variable declarations..
    // "int a=4;" => "int a; a=4;"
    bool finishedwithkr = true;
    bool scopeDecl = false;
    for (Token *tok = tokBegin; tok != tokEnd; tok = tok->next()) {
        if (match451(tok))
            scopeDecl = false;
        if (cpp) {
            if (match452(tok))
                scopeDecl = true;
            if (match453(tok)) {
                tok = tok->linkAt(1);
                // skip decltype(...){...}
                if (tok && match14(tok->previous()))
                    tok = tok->link();
            } else if (match222(tok) ||
                       (!scopeDecl && match454(tok) &&
                        !match455(tok))) {
                if (!tok->linkAt(1))
                    syntaxError(tokBegin);
                // Check for lambdas before skipping
                if (match272(tok->tokAt(-2))) { // trailing return type
                    // TODO: support lambda without parameter clause?
                    Token* lambdaStart = tok->linkAt(-2)->previous();
                    if (match456(lambdaStart))
                        lambdaStart = lambdaStart->link();
                    Token* lambdaEnd = findLambdaEndScope(lambdaStart);
                    if (lambdaEnd)
                        simplifyVarDecl(lambdaEnd->link()->next(), lambdaEnd, only_k_r_fpar);
                } else {
                    for (Token* tok2 = tok->next(); tok2 != tok->linkAt(1); tok2 = tok2->next()) {
                        Token* lambdaEnd = findLambdaEndScope(tok2);
                        if (!lambdaEnd)
                            continue;
                        simplifyVarDecl(lambdaEnd->link()->next(), lambdaEnd, only_k_r_fpar);
                    }
                }
                tok = tok->linkAt(1);
            }

        } else if (match222(tok)) {
            tok = tok->linkAt(1);
        }
        if (!tok) {
            syntaxError(tokBegin);
        }
        if (only_k_r_fpar && finishedwithkr) {
            if (match419(tok)) {
                tok = tok->link();
                if (tok->next() && match457(tok))
                    tok = tok->next();
                else
                    continue;
            } else
                continue;
        } else if (tok->str() == MatchCompiler::makeConstString("(")) {
            if (cpp) {
                for (Token * tok2 = tok; tok2 && tok2 != tok->link(); tok2 = tok2->next()) {
                    if (match458(tok2)) {
                        // lambda function at tok2->next()
                        // find start of lambda body
                        Token * lambdaBody = tok2;
                        while (lambdaBody && lambdaBody != tok2->link() && lambdaBody->str() != MatchCompiler::makeConstString("{"))
                            lambdaBody = lambdaBody->next();
                        if (lambdaBody && lambdaBody != tok2->link() && lambdaBody->link())
                            simplifyVarDecl(lambdaBody, lambdaBody->link()->next(), only_k_r_fpar);
                    }
                }
            }
            tok = tok->link();
        }

        if (!tok)
            syntaxError(nullptr); // #7043 invalid code
        if (tok->previous() && !match459(tok->previous()))
            continue;
        if (match292(tok))
            continue;

        Token *type0 = tok;
        if (!match460(type0))
            continue;
        if (match461(type0))
            continue;
        if (isCPP11 && type0->str() == MatchCompiler::makeConstString("using"))
            continue;
        if (cpp && match462(type0))
            continue;

        bool isconst = false;
        bool isstatic = false;
        Token *tok2 = type0;
        int typelen = 1;

        if (match463(tok2)) {
            tok2 = tok2->next();
            typelen++;
        }

        //check if variable is declared 'const' or 'static' or both
        while (tok2) {
            if (!match464(tok2) && match465(tok2)) {
                tok2 = tok2->next();
                ++typelen;
            }

            if (match466(tok2))
                isconst = true;

            else if (match467(tok2))
                isstatic = true;

            else if (match412(tok2)) {
                tok2 = tok2->next();
                ++typelen;
            }

            else
                break;

            if (tok2->strAt(1) == MatchCompiler::makeConstString("*"))
                break;

            if (match468(tok2->next()))
                break;

            tok2 = tok2->next();
            ++typelen;
        }

        // strange looking variable declaration => don't split up.
        if (match469(tok2))
            continue;

        if (match312(tok2)) {
            tok2 = tok2->next();
            ++typelen;
        }

        // check for qualification..
        if (match116(tok2)) {
            ++typelen;
            tok2 = tok2->next();
        }

        //skip combinations of templates and namespaces
        while (!isC() && (match388(tok2) || match111(tok2))) {
            if (tok2->strAt(1) == MatchCompiler::makeConstString("<") && !TemplateSimplifier::templateParameters(tok2->next())) {
                tok2 = nullptr;
                break;
            }
            typelen += 2;
            tok2 = tok2->tokAt(2);
            if (tok2 && tok2->strAt(-1) == MatchCompiler::makeConstString("::"))
                continue;
            int indentlevel = 0;
            int parens = 0;

            for (Token *tok3 = tok2; tok3; tok3 = tok3->next()) {
                ++typelen;

                if (!parens && tok3->str() == MatchCompiler::makeConstString("<")) {
                    ++indentlevel;
                } else if (!parens && tok3->str() == MatchCompiler::makeConstString(">")) {
                    if (indentlevel == 0) {
                        tok2 = tok3->next();
                        break;
                    }
                    --indentlevel;
                } else if (!parens && tok3->str() == MatchCompiler::makeConstString(">>")) {
                    if (indentlevel <= 1) {
                        tok2 = tok3->next();
                        break;
                    }
                    indentlevel -= 2;
                } else if (tok3->str() == MatchCompiler::makeConstString("(")) {
                    ++parens;
                } else if (tok3->str() == MatchCompiler::makeConstString(")")) {
                    if (!parens) {
                        tok2 = nullptr;
                        break;
                    }
                    --parens;
                } else if (tok3->str() == MatchCompiler::makeConstString(";")) {
                    break;
                }
            }

            if (match116(tok2)) {
                ++typelen;
                tok2 = tok2->next();
            }

            // east const
            if (match37(tok2))
                isconst = true;
        }

        //pattern: "%type% *| ... *| const| %name% ,|="
        if (match12(tok2) ||
            (tok2 && tok2->previous() && tok2->strAt(-1) == MatchCompiler::makeConstString(">"))) {
            Token *varName = tok2;
            if (!tok2->previous() || tok2->strAt(-1) != MatchCompiler::makeConstString(">"))
                varName = varName->next();
            else
                --typelen;
            if (cpp && match470(varName))
                continue;
            //skip all the pointer part
            bool isPointerOrRef = false;
            while (match67(varName) || match468(varName)) {
                isPointerOrRef = true;
                varName = varName->next();
            }

            while (match471(varName)) {
                if (varName->str() != MatchCompiler::makeConstString("const") && varName->str() != MatchCompiler::makeConstString("volatile")) {
                    ++typelen;
                }
                varName = varName->next();
            }
            // Function pointer
            if (match74(varName) &&
                match104(varName->link()->previous()) &&
                match472(varName->link()->linkAt(1))) {
                Token *endDecl = varName->link()->linkAt(1);
                varName = varName->link()->previous();
                endDecl->insertToken(";");
                endDecl = endDecl->next();
                endDecl->next()->isSplittedVarDeclEq(true);
                endDecl->insertToken(varName->str());
                if (!varName->getMacroName().empty())
                    endDecl->next()->setMacroName(varName->getMacroName());
                continue;
            }
            //non-VLA case
            if (match473(varName)) {
                if (varName->str() != MatchCompiler::makeConstString("operator")) {
                    tok2 = varName->next(); // The ',' or '=' token

                    if (tok2->str() == MatchCompiler::makeConstString("=") && (isstatic || (isconst && !isPointerOrRef))) {
                        //do not split const non-pointer variables..
                        while (tok2 && tok2->str() != MatchCompiler::makeConstString(",") && tok2->str() != MatchCompiler::makeConstString(";")) {
                            if (match474(tok2))
                                tok2 = tok2->link();
                            const Token *tok3 = tok2;
                            if (!isC() && tok2->str() == MatchCompiler::makeConstString("<") && TemplateSimplifier::templateParameters(tok2) > 0) {
                                tok2 = tok2->findClosingBracket();
                            }
                            if (!tok2)
                                syntaxError(tok3); // #6881 invalid code
                            tok2 = tok2->next();
                        }
                        if (tok2 && tok2->str() == MatchCompiler::makeConstString(";"))
                            tok2 = nullptr;
                    }
                } else
                    tok2 = nullptr;
            }

            //VLA case
            else if (match50(varName)) {
                tok2 = varName->next();

                while (match475(tok2->link()))
                    tok2 = tok2->link()->next();
                if (!match476(tok2))
                    tok2 = nullptr;
                if (tok2 && tok2->str() == MatchCompiler::makeConstString("=")) {
                    while (tok2 && tok2->str() != MatchCompiler::makeConstString(",") && tok2->str() != MatchCompiler::makeConstString(";")) {
                        if (match474(tok2))
                            tok2 = tok2->link();
                        tok2 = tok2->next();
                    }
                    if (tok2 && tok2->str() == MatchCompiler::makeConstString(";"))
                        tok2 = nullptr;
                }
            }

            // brace initialization
            else if (match477(varName)) {
                tok2 = varName->next();
                tok2 = tok2->link();
                if (tok2)
                    tok2 = tok2->next();
                if (tok2 && tok2->str() != MatchCompiler::makeConstString(","))
                    tok2 = nullptr;
            }

            // function declaration
            else if (match56(varName)) {
                Token* commaTok = varName->linkAt(1)->next();
                while (match478(commaTok)) {
                    commaTok = commaTok->next();
                    if (match167(commaTok))
                        commaTok = commaTok->link()->next();
                }
                tok2 = match479(commaTok) ? commaTok : nullptr;
            }

            else
                tok2 = nullptr;
        } else {
            tok2 = nullptr;
        }

        if (!tok2) {
            if (only_k_r_fpar)
                finishedwithkr = false;
            continue;
        }

        if (tok2->str() == MatchCompiler::makeConstString(",")) {
            tok2->str(";");
            tok2->isSplittedVarDeclComma(true);
            //TODO: should we have to add also template '<>' links?
            TokenList::insertTokens(tok2, type0, typelen);
        }

        else {
            Token *eq = tok2;

            while (tok2) {
                if (match474(tok2))
                    tok2 = tok2->link();

                else if (!isC() && tok2->str() == MatchCompiler::makeConstString("<") && ((tok2->previous()->isName() && !tok2->previous()->varId()) || tok2->strAt(-1) == MatchCompiler::makeConstString("]")))
                    tok2 = tok2->findClosingBracket();

                else if (std::strchr(";,", tok2->str()[0])) {
                    // "type var ="   =>   "type var; var ="
                    const Token *varTok = type0->tokAt(typelen);
                    while (match480(varTok))
                        varTok = varTok->next();
                    if (!varTok)
                        syntaxError(tok2); // invalid code
                    TokenList::insertTokens(eq, varTok, 2);
                    eq->str(";");
                    eq->isSplittedVarDeclEq(true);

                    // "= x, "   =>   "= x; type "
                    if (tok2->str() == MatchCompiler::makeConstString(",")) {
                        tok2->str(";");
                        tok2->isSplittedVarDeclComma(true);
                        TokenList::insertTokens(tok2, type0, typelen);
                    }
                    break;
                }
                if (tok2)
                    tok2 = tok2->next();
            }
        }
        finishedwithkr = (only_k_r_fpar && tok2 && tok2->strAt(1) == MatchCompiler::makeConstString("{"));
    }
}

void Tokenizer::simplifyStaticConst()
{
    // This function will simplify the token list so that the qualifiers "extern", "static"
    // and "const" appear in the same order as in the array below.
    static const std::array<std::string, 3> qualifiers = {"extern", "static", "const"};

    // Move 'const' before all other qualifiers and types and then
    // move 'static' before all other qualifiers and types, ...
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        bool continue2 = false;
        for (std::size_t i = 0; i < qualifiers.size(); i++) {

            // Keep searching for a qualifier
            if (!tok->next() || tok->strAt(1) != qualifiers[i])
                continue;

            // Look backwards to find the beginning of the declaration
            Token* leftTok = tok;
            bool behindOther = false;
            for (; leftTok; leftTok = leftTok->previous()) {
                behindOther = std::any_of(qualifiers.cbegin(), qualifiers.cbegin() + i + 1, [&](const std::string& q) {
                    return q == leftTok->str();
                });
                if (behindOther)
                    break;
                if (isCPP() && match147(leftTok)) {
                    Token* opening = leftTok->findOpeningBracket();
                    if (opening) {
                        leftTok = opening;
                        continue;
                    }
                }
                if (!match481(leftTok) ||
                    (isCPP() && match482(leftTok))) {
                    break;
                }
            }

            // The token preceding the declaration should indicate the start of a declaration
            if (leftTok == tok)
                continue;

            if (leftTok && !behindOther && !match483(leftTok)) {
                continue2 = true;
                break;
            }

            // Move the qualifier to the left-most position in the declaration
            tok->deleteNext();
            if (!leftTok) {
                list.front()->insertToken(qualifiers[i]);
                list.front()->swapWithNext();
                tok = list.front();
            } else if (leftTok->next()) {
                leftTok->next()->insertTokenBefore(qualifiers[i]);
                tok = leftTok->next();
            } else {
                leftTok->insertToken(qualifiers[i]);
                tok = leftTok;
            }
        }
        if (continue2)
            continue;
    }
}

void Tokenizer::simplifyVariableMultipleAssign()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (match484(tok)) {
            // skip intermediate assignments
            Token *tok2 = tok->previous();
            while (tok2 &&
                   tok2->str() == MatchCompiler::makeConstString("=") &&
                   match24(tok2->previous())) {
                tok2 = tok2->tokAt(-2);
            }

            if (!tok2 || tok2->str() != MatchCompiler::makeConstString(";")) {
                continue;
            }

            Token *stopAt = tok->tokAt(2);
            const Token *valueTok = stopAt->tokAt(2);
            const std::string& value(valueTok->str());
            tok2 = tok2->next();

            while (tok2 != stopAt) {
                tok2->next()->insertToken(";");
                tok2->next()->insertToken(value);
                tok2 = tok2->tokAt(4);
            }
        }
    }
}

// Binary operators simplification map
static const std::unordered_map<std::string, std::string> cAlternativeTokens = {
    std::make_pair("and", "&&")
    , std::make_pair("and_eq", "&=")
    , std::make_pair("bitand", "&")
    , std::make_pair("bitor", "|")
    , std::make_pair("not_eq", "!=")
    , std::make_pair("or", "||")
    , std::make_pair("or_eq", "|=")
    , std::make_pair("xor", "^")
    , std::make_pair("xor_eq", "^=")
};

// Simplify the C alternative tokens:
//  and      =>     &&
//  and_eq   =>     &=
//  bitand   =>     &
//  bitor    =>     |
//  compl    =>     ~
//  not      =>     !
//  not_eq   =>     !=
//  or       =>     ||
//  or_eq    =>     |=
//  xor      =>     ^
//  xor_eq   =>     ^=
bool Tokenizer::simplifyCAlternativeTokens()
{
    /* executable scope level */
    int executableScopeLevel = 0;

    std::vector<Token *> alt;
    bool replaceAll = false;  // replace all or none

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->str() == MatchCompiler::makeConstString(")")) {
            if (const Token *end = TokenList::isFunctionHead(tok, "{")) {
                ++executableScopeLevel;
                tok = const_cast<Token *>(end);
                continue;
            }
        }

        if (tok->str() == MatchCompiler::makeConstString("{")) {
            if (executableScopeLevel > 0)
                ++executableScopeLevel;
            continue;
        }

        if (tok->str() == MatchCompiler::makeConstString("}")) {
            if (executableScopeLevel > 0)
                --executableScopeLevel;
            continue;
        }

        if (!tok->isName())
            continue;

        const auto cOpIt = utils::as_const(cAlternativeTokens).find(tok->str());
        if (cOpIt != cAlternativeTokens.end()) {
            alt.push_back(tok);

            // Is this a variable declaration..
            if (isC() && match485(tok->previous()))
                return false;

            if (!match486(tok->previous()))
                continue;
            if (match487(tok->next()) && !match488(tok->previous()))
                continue;
            if (executableScopeLevel == 0 && match56(tok)) {
                const Token *start = tok;
                while (match270(start))
                    start = start->previous();
                if (!start || match489(start))
                    continue;
            }
            replaceAll = true;
        } else if (match490(tok)) {
            alt.push_back(tok);

            if ((match491(tok->previous()) || match492(tok->next())) && !match493(tok->next())) {
                replaceAll = true;
                continue;
            }

            // Don't simplify 'not p;' (in case 'not' is a type)
            if (!match494(tok->next()) ||
                match42(tok->previous()) ||
                (executableScopeLevel == 0U && tok->strAt(-1) == MatchCompiler::makeConstString("(")))
                continue;

            replaceAll = true;
        }
    }

    if (!replaceAll)
        return false;

    for (Token *tok: alt) {
        const auto cOpIt = utils::as_const(cAlternativeTokens).find(tok->str());
        if (cOpIt != cAlternativeTokens.end())
            tok->str(cOpIt->second);
        else if (tok->str() == MatchCompiler::makeConstString("not"))
            tok->str("!");
        else
            tok->str("~");
    }

    return !alt.empty();
}

// int i(0); => int i; i = 0;
// int i(0), j; => int i; i = 0; int j;
void Tokenizer::simplifyInitVar()
{
    if (isC())
        return;

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!tok->isName() || (tok->previous() && !match42(tok->previous())))
            continue;

        if (tok->str() == MatchCompiler::makeConstString("return"))
            continue;

        if (match495(tok)) {
            bool isNamespace = match496(tok);
            while (tok && !match497(tok))
                tok = tok->next();
            if (isNamespace)
                continue;
            if (tok)
                tok->isInitBracket(true);
            /* tok = initVar(tok);
               } else if (match498(tok)) {
               const Token* tok2 = tok->tokAt(2);
               if (!tok2->link())
                tok2 = tok2->next();
               if (!tok2->link() || (tok2->link()->strAt(1) == MatchCompiler::makeConstString(";") && !match59(tok2->linkAt(2))))
                tok = initVar(tok);
               } else if (match499(tok) && tok->str() != MatchCompiler::makeConstString("new")) {
               Token *tok1 = tok->tokAt(5);
               while (tok1->str() != MatchCompiler::makeConstString(","))
                tok1 = tok1->next();
               tok1->str(";");

               const int numTokens = (match158(tok)) ? 2 : 1;
               TokenList::insertTokens(tok1, tok, numTokens);
               tok = initVar(tok); */
        }
    }
}

Token * Tokenizer::initVar(Token * tok)
{
    // call constructor of class => no simplification
    if (match158(tok)) {
        if (tok->strAt(2) != MatchCompiler::makeConstString("*"))
            return tok;

        tok = tok->next();
    } else if (!tok->isStandardType() && tok->str() != MatchCompiler::makeConstString("auto") && tok->strAt(1) != MatchCompiler::makeConstString("*"))
        return tok;

    // goto variable name..
    tok = tok->next();
    if (tok->str() == MatchCompiler::makeConstString("*"))
        tok = tok->next();

    // sizeof is not a variable name..
    if (tok->str() == MatchCompiler::makeConstString("sizeof"))
        return tok;

    // check initializer..
    if (tok->tokAt(2)->isStandardType() || tok->strAt(2) == MatchCompiler::makeConstString("void"))
        return tok;
    if (!tok->tokAt(2)->isNumber() && !match500(tok->tokAt(2)) && tok->strAt(2) != MatchCompiler::makeConstString("&") && tok->tokAt(2)->varId() == 0)
        return tok;

    // insert '; var ='
    tok->insertToken(";");
    tok->next()->insertToken(tok->str());
    tok->next()->isSplittedVarDeclEq(true);
    tok->tokAt(2)->varId(tok->varId());
    tok = tok->tokAt(2);
    tok->insertToken("=");

    // goto '('..
    tok = tok->tokAt(2);

    // delete ')'
    tok->link()->deleteThis();

    // delete this
    tok->deleteThis();

    return tok;
}

void Tokenizer::elseif()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->str() != MatchCompiler::makeConstString("else"))
            continue;

        if (!match501(tok->previous()))
            syntaxError(tok->previous());

        if (!match24(tok->next()))
            continue;

        if (tok->strAt(1) != MatchCompiler::makeConstString("if"))
            unknownMacroError(tok->next());

        for (Token *tok2 = tok; tok2; tok2 = tok2->next()) {
            if (match140(tok2))
                tok2 = tok2->link();

            if (match502(tok2)) {
                if (tok2->next() && tok2->strAt(1) != MatchCompiler::makeConstString("else")) {
                    tok->insertToken("{");
                    tok2->insertToken("}");
                    Token::createMutualLinks(tok->next(), tok2->next());
                    break;
                }
            }
        }
    }
}


void Tokenizer::simplifyIfSwitchForInit()
{
    if (!isCPP() || mSettings.standards.cpp < Standards::CPP17)
        return;

    const bool forInit = (mSettings.standards.cpp >= Standards::CPP20);

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!match503(tok))
            continue;

        Token *semicolon = tok->tokAt(2);
        while (!match504(semicolon)) {
            if (match140(semicolon) && semicolon->link())
                semicolon = semicolon->link();
            semicolon = semicolon->next();
        }
        if (semicolon->str() != MatchCompiler::makeConstString(";"))
            continue;

        if (tok->str() ==  MatchCompiler::makeConstString("for")) {
            if (!forInit)
                continue;

            // Is it a for range..
            const Token *tok2 = semicolon->next();
            bool rangeFor = false;
            while (!match504(tok2)) {
                if (tok2->str() == MatchCompiler::makeConstString("("))
                    tok2 = tok2->link();
                else if (!rangeFor && tok2->str() == MatchCompiler::makeConstString("?"))
                    break;
                else if (tok2->str() == MatchCompiler::makeConstString(":"))
                    rangeFor = true;
                tok2 = tok2->next();
            }
            if (!rangeFor || tok2->str() != MatchCompiler::makeConstString(")"))
                continue;
        }

        Token *endpar = tok->linkAt(1);
        if (!match14(endpar))
            continue;

        Token *endscope = endpar->linkAt(1);
        if (match505(endscope))
            endscope = endscope->linkAt(2);

        // Simplify, the initialization expression is broken out..
        semicolon->insertToken(tok->str());
        semicolon->next()->insertToken("(");
        Token::createMutualLinks(semicolon->tokAt(2), endpar);
        tok->deleteNext();
        tok->str("{");
        endscope->insertToken("}");
        Token::createMutualLinks(tok, endscope->next());
        tok->isSimplifiedScope(true);
    }
}


bool Tokenizer::simplifyRedundantParentheses()
{
    bool ret = false;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->str() != MatchCompiler::makeConstString("("))
            continue;

        if (tok->isCpp() && match506(tok->previous())) {
            const Token* plp = tok->linkAt(-1)->previous();
            if (match507(plp) || (match40(plp) && match456(plp->link()->previous())))
                continue;
        }

        if (match508(tok))
            continue;

        if (match509(tok->link())) {
            tok = tok->link();
            continue;
        }

        // Do not simplify if there is comma inside parentheses..
        if (match510(tok->previous()) || match511(tok->link())) {
            bool innerComma = false;
            for (const Token *inner = tok->link()->previous(); inner != tok; inner = inner->previous()) {
                if (inner->str() == MatchCompiler::makeConstString(")"))
                    inner = inner->link();
                if (inner->str() == MatchCompiler::makeConstString(",")) {
                    innerComma = true;
                    break;
                }
            }
            if (innerComma)
                continue;
        }

        // !!operator = ( x ) ;
        if (tok->strAt(-2) != MatchCompiler::makeConstString("operator") &&
            tok->previous() && tok->strAt(-1) == MatchCompiler::makeConstString("=") &&
            tok->next() && tok->strAt(1) != MatchCompiler::makeConstString("{") &&
            match53(tok->link())) {
            tok->link()->deleteThis();
            tok->deleteThis();
            continue;
        }

        if (isCPP() && match512(tok->tokAt(-2)) && match513(tok->link())) {
            // Remove the parentheses in "new (type)" constructs
            tok->link()->deleteThis();
            tok->deleteThis();
            ret = true;
        }

        if (match514(tok->previous())) {
            // Remove the parentheses
            tok->deleteThis();
            tok->deleteNext();
            ret = true;
        }

        if (match515(tok->previous())) {
            // Remove the parentheses
            tok->deleteThis();
            tok->deleteNext();
            ret = true;
        }

        if (match516(tok->previous()) && !tok->next()->isKeyword() &&
            tok->link()->previous() == tok->linkAt(2)) {
            // We have "( func ( *something* ))", remove the outer
            // parentheses
            tok->link()->deleteThis();
            tok->deleteThis();
            ret = true;
        }

        if (match517(tok->previous())) {
            // We have "( delete [| ]| var )", remove the outer
            // parentheses
            tok->link()->deleteThis();
            tok->deleteThis();
            ret = true;
        }

        if (!match518(tok->tokAt(-2)) &&
            match519(tok->previous()) &&
            (tok->strAt(-1) != MatchCompiler::makeConstString("delete") || tok->next()->varId() > 0) &&
            match132(tok->link())) {
            tok->link()->deleteThis();
            tok->deleteThis();
            ret = true;
        }

        if (match520(tok->previous()) &&
            (tok->next()->varId() != 0 || match521(tok->tokAt(3))) && !tok->next()->isStandardType()) {
            // We have "( var )", remove the parentheses
            tok->deleteThis();
            tok->deleteNext();
            ret = true;
        }

        while (match522(tok->previous())) {
            Token *tok2 = tok->tokAt(2);
            while (match523(tok2)) {
                tok2 = tok2->tokAt(2);
            }
            if (tok2 != tok->link())
                break;
            // We have "( var . var . ... . var )", remove the parentheses
            tok = tok->previous();
            tok->deleteNext();
            tok2->deleteThis();
            ret = true;
        }

        while (match524(tok->previous()) &&
               match525(tok->link()) &&
               !match526(tok->tokAt(-2)) && // Ticket #5709
               !findmatch527(tok, tok->link()) ) {
            // We have "( ... )", remove the parentheses
            tok->link()->deleteThis();
            tok->deleteThis();
            ret = true;
        }

        if (match528(tok->previous()) &&
            match472(tok->link())) {
            tok->link()->deleteThis();
            tok->deleteThis();
            ret = true;
        }

        // Simplify "!!operator !!%name%|)|]|>|>> ( %num%|%bool% ) %op%|;|,|)"
        if (match529(tok) &&
            tok->strAt(-2) != MatchCompiler::makeConstString("operator") &&
            tok->previous() &&
            !match530(tok->previous()) &&
            (!(isCPP() && match181(tok->previous())))) {
            tok->link()->deleteThis();
            tok->deleteThis();
            ret = true;
        }

        if (match531(tok->previous())) {
            // We may have a variable declaration looking like "type_name *(var_name)"
            Token *tok2 = tok->tokAt(-2);
            while (match532(tok2) && tok2->str() != MatchCompiler::makeConstString("operator")) {
                tok2 = tok2->previous();
            }
            if (tok2 && !match212(tok2)) {
                // Not a variable declaration
            } else {
                tok->deleteThis();
                tok->deleteNext();
            }
        }
    }
    return ret;
}

void Tokenizer::simplifyTypeIntrinsics()
{
    static const std::unordered_map<std::string, std::string> intrinsics = {
        { "__has_nothrow_assign", "has_nothrow_assign" },
        { "__has_nothrow_constructor", "has_nothrow_constructor" },
        { "__has_nothrow_copy", "has_nothrow_copy" },
        { "__has_trivial_assign", "has_trivial_assign" },
        { "__has_trivial_constructor", "has_trivial_constructor" },
        { "__has_trivial_copy", "has_trivial_copy" },
        { "__has_trivial_destructor", "has_trivial_destructor" },
        { "__has_virtual_destructor", "has_virtual_destructor" },
        { "__is_abstract", "is_abstract" },
        { "__is_aggregate", "is_aggregate" },
        { "__is_assignable", "is_assignable" },
        { "__is_base_of", "is_base_of" },
        { "__is_class", "is_class" },
        { "__is_constructible", "is_constructible" },
        { "__is_convertible_to", "is_convertible_to" },
        { "__is_destructible", "is_destructible" },
        { "__is_empty", "is_empty" },
        { "__is_enum", "is_enum" },
        { "__is_final", "is_final" },
        { "__is_nothrow_assignable", "is_nothrow_assignable" },
        { "__is_nothrow_constructible", "is_nothrow_constructible" },
        { "__is_nothrow_destructible", "is_nothrow_destructible" },
        { "__is_pod", "is_pod" },
        { "__is_polymorphic", "is_polymorphic" },
        { "__is_trivially_assignable", "is_trivially_assignable" },
        { "__is_trivially_constructible", "is_trivially_constructible" },
        { "__is_union", "is_union" },
    };
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!match56(tok))
            continue;
        auto p = intrinsics.find(tok->str());
        if (p == intrinsics.end())
            continue;
        Token * end = tok->linkAt(1);
        Token * prev = tok->previous();
        tok->str(p->second);
        prev->insertToken("::");
        prev->insertToken("std");
        tok->next()->str("<");
        end->str(">");
        end->insertToken("}");
        end->insertToken("{");
        Token::createMutualLinks(end->tokAt(1), end->tokAt(2));
    }
}

//---------------------------------------------------------------------------
// Helper functions for handling the tokens list
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

bool Tokenizer::isScopeNoReturn(const Token *endScopeToken, bool *unknown) const
{
    std::string unknownFunc;
    const bool ret = mSettings.library.isScopeNoReturn(endScopeToken,&unknownFunc);
    if (!unknownFunc.empty() && mSettings.summaryReturn.find(unknownFunc) != mSettings.summaryReturn.end()) {
        return false;
    }
    if (unknown)
        *unknown = !unknownFunc.empty();
    if (!unknownFunc.empty() && mSettings.checkLibrary) {
        bool warn = true;
        if (match533(endScopeToken->tokAt(-2))) {
            const Token * const ftok = endScopeToken->linkAt(-2)->previous();
            if (ftok && (ftok->type() || ftok->function() || ftok->variable())) // constructor call
                warn = false;
        }

        if (warn) {
            reportError(endScopeToken->previous(),
                        Severity::information,
                        "checkLibraryNoReturn",
                        "--check-library: Function " + unknownFunc + "() should have <noreturn> configuration");
        }
    }
    return ret;
}

//---------------------------------------------------------------------------

void Tokenizer::syntaxError(const Token *tok, const std::string &code) const
{
    if (mSettings.debugSimplified || mSettings.debugnormal)
        printDebugOutput(std::cout);
    throw InternalError(tok, code.empty() ? "syntax error" : "syntax error: " + code, InternalError::SYNTAX);
}

void Tokenizer::unmatchedToken(const Token *tok) const
{
    if (mSettings.debugSimplified || mSettings.debugnormal)
        printDebugOutput(std::cout);
    throw InternalError(tok,
                        "Unmatched '" + tok->str() + "'. Configuration: '" + mConfiguration + "'.",
                        InternalError::SYNTAX);
}

void Tokenizer::syntaxErrorC(const Token *tok, const std::string &what) const
{
    if (mSettings.debugSimplified || mSettings.debugnormal)
        printDebugOutput(std::cout);
    throw InternalError(tok, "Code '"+what+"' is invalid C code.", "Use --std, -x or --language to enforce C++. Or --cpp-header-probe to identify C++ headers via the Emacs marker.", InternalError::SYNTAX);
}

void Tokenizer::unknownMacroError(const Token *tok1) const
{
    if (mSettings.debugSimplified || mSettings.debugnormal)
        printDebugOutput(std::cout);
    throw InternalError(tok1, "There is an unknown macro here somewhere. Configuration is required. If " + tok1->str() + " is a macro then please configure it.", InternalError::UNKNOWN_MACRO);
}

void Tokenizer::unhandled_macro_class_x_y(const Token *tok, const std::string& type, const std::string& x, const std::string& y, const std::string& bracket) const
{
    reportError(tok,
                Severity::information,
                "class_X_Y",
                "The code '" +
                type + " " +
                x + " " +
                y + " " +
                bracket + "' is not handled. You can use -I or --include to add handling of this code.");
}

void Tokenizer::macroWithSemicolonError(const Token *tok, const std::string &macroName) const
{
    reportError(tok,
                Severity::information,
                "macroWithSemicolon",
                "Ensure that '" + macroName + "' is defined either using -I, --include or -D.");
}

void Tokenizer::invalidConstFunctionTypeError(const Token *tok) const
{
    reportError(tok,
                Severity::portability,
                "invalidConstFunctionType",
                "It is unspecified behavior to const qualify a function type.");
}

void Tokenizer::cppcheckError(const Token *tok) const
{
    printDebugOutput(std::cout);
    throw InternalError(tok, "Analysis failed. If the code is valid then please report this failure.", InternalError::INTERNAL);
}

void Tokenizer::unhandledCharLiteral(const Token *tok, const std::string& msg) const
{
    std::string s = tok ? (" " + tok->str()) : "";
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (static_cast<unsigned char>(s[i]) >= 0x80)
            s.clear();
    }

    reportError(tok,
                Severity::portability,
                "nonStandardCharLiteral",
                "Non-standard character literal" + s + ". " + msg);
}

/**
 * Helper function to check whether number is equal to integer constant X
 * or floating point pattern X.0
 * @param s the string to check
 * @param intConstant the integer constant to check against
 * @param floatConstant the string with stringified float constant to check against
 * @return true in case s is equal to X or X.0 and false otherwise.
 */
static bool isNumberOneOf(const std::string &s, MathLib::bigint intConstant, const char* floatConstant)
{
    if (MathLib::isInt(s)) {
        if (MathLib::toBigNumber(s) == intConstant)
            return true;
    } else if (MathLib::isFloat(s)) {
        if (MathLib::toString(MathLib::toDoubleNumber(s)) == floatConstant)
            return true;
    }
    return false;
}

// ------------------------------------------------------------------------
// Helper function to check whether number is one (1 or 0.1E+1 or 1E+0) or not?
// @param s the string to check
// @return true in case s is one and false otherwise.
// ------------------------------------------------------------------------
bool Tokenizer::isOneNumber(const std::string &s)
{
    if (!MathLib::isPositive(s))
        return false;
    return isNumberOneOf(s, 1L, "1.0");
}
// ------------------------------------------------------------------------
void Tokenizer::checkConfiguration() const
{
    if (!mSettings.checkConfiguration)
        return;
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        if (!match56(tok))
            continue;
        if (tok->isControlFlowKeyword())
            continue;
        for (const Token *tok2 = tok->tokAt(2); tok2 && tok2->str() != MatchCompiler::makeConstString(")"); tok2 = tok2->next()) {
            if (tok2->str() == MatchCompiler::makeConstString(";")) {
                macroWithSemicolonError(tok, tok->str());
                break;
            }
            if (match497(tok2))
                tok2 = tok2->link();
        }
    }
}

void Tokenizer::validateC() const
{
    if (isCPP())
        return;
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        // That might trigger false positives, but it's much faster to have this truncated pattern
        if (match534(tok))
            syntaxErrorC(tok, "C++ cast <...");
        // Template function..
        if (match535(tok)) {
            const Token *tok2 = tok->tokAt(5);
            while (tok2 && !match536(tok2))
                tok2 = tok2->next();
            if (match14(tok2))
                syntaxErrorC(tok, tok->str() + '<' + tok->strAt(2) + ">() {}");
        }
        if (tok->previous() && !match42(tok->previous()))
            continue;
        if (match537(tok))
            syntaxErrorC(tok, "using namespace " + tok->strAt(2));
        if (match538(tok))
            syntaxErrorC(tok, "template<...");
        if (match108(tok))
            syntaxErrorC(tok, tok->str() + tok->strAt(1) + tok->strAt(2));
        if (match539(tok))
            syntaxErrorC(tok, tok->str() + tok->strAt(1) + tok->strAt(2));
    }
}

void Tokenizer::validate() const
{
    std::stack<const Token *> linkTokens;
    const Token *lastTok = nullptr;
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        lastTok = tok;
        if (match77(tok) || (tok->str() == MatchCompiler::makeConstString("<") && tok->link())) {
            if (tok->link() == nullptr)
                cppcheckError(tok);

            linkTokens.push(tok);
        }

        else if (match78(tok) || (match181(tok) && tok->link())) {
            if (tok->link() == nullptr)
                cppcheckError(tok);

            if (linkTokens.empty())
                cppcheckError(tok);

            if (tok->link() != linkTokens.top())
                cppcheckError(tok);

            if (tok != tok->link()->link())
                cppcheckError(tok);

            linkTokens.pop();
        }

        else if (tok->link() != nullptr)
            cppcheckError(tok);
    }

    if (!linkTokens.empty())
        cppcheckError(linkTokens.top());

    // Validate that the Tokenizer::list.back() is updated correctly during simplifications
    if (lastTok != list.back())
        cppcheckError(lastTok);
}

static const Token *findUnmatchedTernaryOp(const Token * const begin, const Token * const end, int depth = 0)
{
    std::stack<const Token *> ternaryOp;
    for (const Token *tok = begin; tok != end && tok->str() != MatchCompiler::makeConstString(";"); tok = tok->next()) {
        if (tok->str() == MatchCompiler::makeConstString("?"))
            ternaryOp.push(tok);
        else if (!ternaryOp.empty() && tok->str() == MatchCompiler::makeConstString(":"))
            ternaryOp.pop();
        else if (depth < 100 && match68(tok)) {
            const Token *inner = findUnmatchedTernaryOp(tok->next(), tok->link(), depth+1);
            if (inner)
                return inner;
            tok = tok->link();
        }
    }
    return ternaryOp.empty() ? nullptr : ternaryOp.top();
}

static bool isCPPAttribute(const Token * tok)
{
    return match540(tok) && tok->link() && tok->link()->previous() == tok->linkAt(1);
}

static bool isAlignAttribute(const Token * tok)
{
    return match248(tok) && tok->linkAt(1);
}

template<typename T>
static T* skipCPPOrAlignAttribute(T * tok)
{
    if (isCPPAttribute(tok))
        return tok->link();
    if (isAlignAttribute(tok)) {
        return tok->linkAt(1);
    }
    return tok;
}

static bool isNonMacro(const Token* tok)
{
    if (tok->isKeyword() || tok->isStandardType())
        return true;
    if (cAlternativeTokens.count(tok->str()) > 0)
        return true;
    if (startsWith(tok->str(), "__")) // attribute/annotation
        return true;
    if (match248(tok))
        return true;
    return false;
}

void Tokenizer::reportUnknownMacros() const
{
    // Report unknown macros used in expressions "%name% %num%"
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        if (match541(tok)) {
            // A keyword is not an unknown macro
            if (tok->isKeyword())
                continue;

            if (match542(tok->previous()))
                unknownMacroError(tok);
        }
    }

    // Report unknown macros before } "{ .. if (x) MACRO }"
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        if (match543(tok)) {
            if (tok->link() && !match544(tok->link()->tokAt(-1)))
                continue;
            const Token* prev = tok->linkAt(2);
            while (match1(prev))
                prev = prev->previous();
            if (match545(prev))
                unknownMacroError(tok->next());
        }
    }

    // Report unknown macros that contain several statements "MACRO(a;b;c)"
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        if (!match56(tok))
            continue;
        if (!tok->isUpperCaseName())
            continue;
        const Token *endTok = tok->linkAt(1);
        for (const Token *inner = tok->tokAt(2); inner != endTok; inner = inner->next()) {
            if (match546(inner))
                inner = inner->link();
            else if (inner->str() == MatchCompiler::makeConstString(";"))
                unknownMacroError(tok);
        }
    }

    // Report unknown macros that contain struct initialization "MACRO(a, .b=3)"
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        if (!match56(tok))
            continue;
        const Token *endTok = tok->linkAt(1);
        for (const Token *inner = tok->tokAt(2); inner != endTok; inner = inner->next()) {
            if (match546(inner))
                inner = inner->link();
            else if (match547(inner->previous()))
                unknownMacroError(tok);
        }
    }

    const bool cpp = isCPP();

    // Report unknown macros in non-executable scopes..
    std::set<std::string> possible;
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        // Skip executable scopes..
        if (tok->str() == MatchCompiler::makeConstString("{")) {
            const Token *prev = tok->previous();
            while (prev && prev->isName())
                prev = prev->previous();
            if (prev && prev->str() == MatchCompiler::makeConstString(")"))
                tok = tok->link();
            else
                possible.clear();
        } else if (tok->str() == MatchCompiler::makeConstString("}"))
            possible.clear();

        if (match56(tok) && tok->isUpperCaseName() && match59(tok->linkAt(1)) && match14(tok->linkAt(1)->linkAt(1))) {
            // A keyword is not an unknown macro
            if (tok->isKeyword())
                continue;

            const Token *bodyStart = tok->linkAt(1)->linkAt(1)->tokAt(2);
            const Token *bodyEnd = tok->link();
            for (const Token *tok2 = bodyStart; tok2 && tok2 != bodyEnd; tok2 = tok2->next()) {
                if (match548(tok2))
                    unknownMacroError(tok);
            }
        } else if (match56(tok) && tok->isUpperCaseName() && match356(tok->linkAt(1)) && match549(tok->linkAt(1)->linkAt(2))) {
            if (!(tok->linkAt(1)->next() && tok->linkAt(1)->next()->isKeyword())) { // e.g. noexcept(true)
                if (possible.count(tok->str()) == 0)
                    possible.insert(tok->str());
                else
                    unknownMacroError(tok);
            }
        } else if (cpp && match550(tok)) {
            unknownMacroError(tok->next());
        }
    }

    // String concatenation with unknown macros
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        if ((match551(tok) && match552(tok->linkAt(2))) ||
            (match553(tok) && !(startsWith(tok->strAt(1), "PRI") || startsWith(tok->strAt(1), "SCN")))) { // TODO: implement macros in std.cfg
            if (tok->next()->isKeyword())
                continue;
            unknownMacroError(tok->next());
        }
        if (match554(tok) && match555(tok->linkAt(2))) {
            if (tok->next()->isKeyword() || tok->linkAt(2)->next()->isKeyword())
                continue;
            if (cAlternativeTokens.count(tok->linkAt(2)->strAt(1)) > 0)
                continue;
            if (startsWith(tok->strAt(1), "__")) // attribute/annotation
                continue;
            if (tok->next()->isStandardType() && !tok->linkAt(2)->next()->isStandardType())
                unknownMacroError(tok->linkAt(2)->next());
            else
                unknownMacroError(tok->next());
        }
    }

    // Report unknown macros without commas or operators inbetween statements: MACRO1() MACRO2()
    for (const Token* tok = tokens(); tok; tok = tok->next()) {
        if (!match56(tok))
            continue;
        if (isNonMacro(tok) && !tok->isStandardType())
            continue;

        const Token* endTok = tok->linkAt(1);
        if (!match556(endTok))
            continue;

        const Token* tok2 = endTok->next();
        if (isNonMacro(tok2))
            continue;

        if (tok2->strAt(1) == MatchCompiler::makeConstString("(")) {
            if (match557(tok->previous()))
                continue;
        }

        unknownMacroError(tok->isStandardType() ? tok2 : tok);
    }
}

void Tokenizer::findGarbageCode() const
{
    const bool cpp = isCPP();
    const bool isCPP11 = cpp && mSettings.standards.cpp >= Standards::CPP11;

    static const std::unordered_set<std::string> nonConsecutiveKeywords{ "break",
                                                                         "continue",
                                                                         "for",
                                                                         "goto",
                                                                         "if",
                                                                         "return",
                                                                         "switch",
                                                                         "throw",
                                                                         "typedef",
                                                                         "while" };

    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        // initialization: = {
        if (match222(tok) && match506(tok->linkAt(1)))
            syntaxError(tok->linkAt(1));

        // Inside [] there can't be ; or various keywords
        else if (tok->str() == MatchCompiler::makeConstString("[")) {
            for (const Token* inner = tok->next(); inner != tok->link(); inner = inner->next()) {
                if (match419(inner))
                    inner = inner->link();
                else if (match558(inner))
                    syntaxError(inner);
            }
        }

        // array assignment
        else if (match559(tok) && match32(tok->linkAt(1)))
            syntaxError(tok, tok->str() + "[...];");

        else if (match560(tok))
            syntaxError(tok);

        else if (match561(tok))
            syntaxError(tok);

        else if (match562(tok))
            syntaxError(tok);

        // UNKNOWN_MACRO(return)
        if (tok->isKeyword() && match563(tok) && match56(tok->linkAt(1)->previous()))
            unknownMacroError(tok->linkAt(1)->previous());

        // UNKNOWN_MACRO(return)
        else if (!tok->isKeyword() && (match564(tok) || (isCPP() && match565(tok))))
            unknownMacroError(tok);

        // Assign/increment/decrement literal
        else if (match566(tok)) {
            if (!cpp || mSettings.standards.cpp < Standards::CPP20 || !match567(tok->previous()))
                syntaxError(tok, tok->strAt(1) + " " + tok->strAt(2));
        }
        else if (match569(tok) && !match568(tok->link()->previous())) {
            if (tok->link()->previous() && tok->link()->previous()->isUpperCaseName())
                unknownMacroError(tok->link()->previous());
            else
                syntaxError(tok);
        }

        if (tok->isControlFlowKeyword()) {
            if (match570(tok)) { // if|while|for|switch (EXPR) { ... }
                if (tok->previous() && !match571(tok->previous())) {
                    if (match572(tok->previous())) {
                        const Token *prev = tok->previous();
                        while (prev && prev->str() != MatchCompiler::makeConstString("(")) {
                            if (prev->str() == MatchCompiler::makeConstString(")"))
                                prev = prev->link();
                            prev = prev->previous();
                        }
                        if (prev && match56(prev->previous()))
                            unknownMacroError(prev->previous());
                    }
                    if (!match573(tok->tokAt(-2)))
                        syntaxError(tok);
                }
                if (!match574(tok->next()))
                    syntaxError(tok);
                if (tok->str() != MatchCompiler::makeConstString("for")) {
                    if (isGarbageExpr(tok->next(), tok->linkAt(1), cpp && (mSettings.standards.cpp>=Standards::cppstd_t::CPP17)))
                        syntaxError(tok);
                }
            }
            if (match575(tok)) {
                if (!match576(tok->linkAt(1)))
                    syntaxError(tok->linkAt(1));
                if (!match53(tok->linkAt(1)->linkAt(2)))
                    syntaxError(tok->linkAt(1)->linkAt(2));
            }
        }

        // keyword keyword
        if (tok->isKeyword() && nonConsecutiveKeywords.count(tok->str()) != 0) {
            if (match577(tok) && nonConsecutiveKeywords.count(tok->strAt(1)) == 1)
                syntaxError(tok);
            const Token* prev = tok;
            while (prev && prev->isName())
                prev = prev->previous();
            if (match578(prev)) {
                if (!match573(tok->tokAt(-2)) &&
                    !match579(tok->tokAt(-2)) &&
                    !match580(prev))
                    syntaxError(tok, prev == tok->previous() ? (prev->str() + " " + tok->str()) : (prev->str() + " .. " + tok->str()));
            }
        }
    }

    // invalid struct declaration
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        if (match581(tok) && (!tok->previous() || match42(tok->previous()))) {
            const Token *tok2 = tok->linkAt(tok->next()->isName() ? 2 : 1);
            if (match582(tok2)) {
                tok2 = tok2->next();
                if (!match72(tok2))
                    syntaxError(tok2, "Unexpected token '" + tok2->str() + "'");
                while (match72(tok2))
                    tok2 = tok2->next();
                if (!match24(tok2))
                    syntaxError(tok2, "Unexpected token '" + (tok2 ? tok2->str() : "") + "'");
            }
        }
        if (tok->str() == MatchCompiler::makeConstString("enum")) {
            if (match583(tok->next()))
                syntaxError(tok->tokAt(2), "Unexpected token '" + tok->strAt(2) + "'");
            if (const Token* start = SymbolDatabase::isEnumDefinition(tok)) {
                int nEquals = 0;
                for (const Token* tok2 = start->next(); tok2 && tok2 != start->link(); tok2 = tok2->next()) {
                    if (match301(tok2)) {
                        tok2 = tok2->linkAt(1);
                        continue;
                    }
                    if (const Token* lam = findLambdaEndTokenWithoutAST(tok2)) {
                        tok2 = lam;
                        continue;
                    }
                    if (tok2->str() == MatchCompiler::makeConstString(";"))
                        syntaxError(tok2);
                    if (tok2->str() == MatchCompiler::makeConstString("="))
                        ++nEquals;
                    else if (tok2->str() == MatchCompiler::makeConstString(","))
                        nEquals = 0;
                    if (nEquals > 1)
                        syntaxError(tok2);
                }
            }
        }
    }

    // Keywords in global scope
    static const std::unordered_set<std::string> nonGlobalKeywords{"break",
                                                                   "continue",
                                                                   "for",
                                                                   "goto",
                                                                   "if",
                                                                   "return",
                                                                   "switch",
                                                                   "while",
                                                                   "try",
                                                                   "catch"};
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        if (tok->str() == MatchCompiler::makeConstString("{"))
            tok = tok->link();
        else if (tok->isKeyword() && nonGlobalKeywords.count(tok->str()) && !match584(tok->tokAt(-2)))
            syntaxError(tok, "keyword '" + tok->str() + "' is not allowed in global scope");
    }

    // case keyword must be inside switch
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        if (match585(tok)) {
            if (match14(tok->linkAt(1))) {
                tok = tok->linkAt(1)->linkAt(1);
                continue;
            }
            const Token *switchToken = tok;
            tok = tok->linkAt(1);
            if (!tok)
                syntaxError(switchToken);
            // Look for the end of the switch statement, i.e. the first semi-colon or '}'
            for (; tok; tok = tok->next()) {
                if (tok->str() == MatchCompiler::makeConstString("{")) {
                    tok = tok->link();
                }
                if (match501(tok)) {
                    // We're at the end of the switch block
                    if (tok->str() == MatchCompiler::makeConstString("}") && tok->strAt(-1) == MatchCompiler::makeConstString(":")) // Invalid case
                        syntaxError(switchToken);
                    break;
                }
            }
            if (!tok)
                break;
        } else if (tok->str() == MatchCompiler::makeConstString("(")) {
            tok = tok->link();
        } else if (tok->str() == MatchCompiler::makeConstString("case")) {
            syntaxError(tok);
        }
    }

    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        if (!match305(tok)) // find for loops
            continue;
        // count number of semicolons
        int semicolons = 0, colons = 0;
        const Token* const startTok = tok;
        tok = tok->linkAt(1)->previous(); // find ")" of the for-loop
        // walk backwards until we find the beginning (startTok) of the for() again
        for (; tok != startTok; tok = tok->previous()) {
            if (tok->str() == MatchCompiler::makeConstString(";")) { // do the counting
                semicolons++;
            } else if (tok->str() == MatchCompiler::makeConstString(":")) {
                colons++;
            } else if (tok->str() == MatchCompiler::makeConstString(")")) { // skip pairs of ( )
                tok = tok->link();
            }
        }
        // if we have an invalid number of semicolons inside for( ), assume syntax error
        if (semicolons > 2)
            syntaxError(tok);
        if (semicolons == 1 && !(cpp && mSettings.standards.cpp >= Standards::CPP20))
            syntaxError(tok);
        if (semicolons == 0 && colons == 0)
            syntaxError(tok);
    }

    // Operators without operands..
    const Token *templateEndToken = nullptr;
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        if (!templateEndToken) {
            if (tok->str() == MatchCompiler::makeConstString("<") && cpp)
                templateEndToken = tok->findClosingBracket();
        } else {
            if (templateEndToken == tok)
                templateEndToken = nullptr;
            if (match586(tok))
                continue;
        }
        // skip C++ attributes [[...]]
        if (isCPP11 && (isCPPAttribute(tok) || isAlignAttribute(tok))) {
            tok = skipCPPOrAlignAttribute(tok);
            continue;
        }
        {
            bool match1 = match587(tok);
            bool match2 = match588(tok->next());
            if (cpp) {
                match1 = match1 || match589(tok);
                match2 = match2 || match590(tok->next());
            }
            if (match1 && !tok->isIncDecOp()) {
                match2 = match2 || match491(tok->next());
            }
            if (match1 && match2)
                syntaxError(tok);
        }
        if (match591(tok)) {
            std::string code;
            if (match592(tok->next()))
                code = tok->str() + tok->strAt(1);
            if (match593(tok->next()))
                code = tok->str() + "()";
            if (!code.empty()) {
                if (isC() || (tok->str() != MatchCompiler::makeConstString(">") && !match594(tok->previous())))
                    syntaxError(tok, code);
            }
        }
        if (match595(tok) && !match596(tok))
            syntaxError(tok);
        if (match597(tok)) {
            if (tok->strAt(1) == MatchCompiler::makeConstString("("))
                syntaxError(tok);
            else if (!(tok->tokType() == Token::Type::eString && match598(tok->tokAt(-1))) &&
                     !(tok->tokType() == Token::Type::eBoolean && cpp && match599(tok->tokAt(-1))))
                syntaxError(tok);
        }
        if (match600(tok))
            syntaxError(tok);
        if (match601(tok))
            syntaxError(tok);
        if (match602(tok) && (!cpp || !match594(tok->previous())))
            syntaxError(tok);
        if (match603(tok))
            syntaxError(tok);
        if (match604(tok) && tok->next()->isControlFlowKeyword())
            syntaxError(tok);
        if (match605(tok))
            syntaxError(tok);
        if (match606(tok))
            syntaxError(tok);
        if (match607(tok) && !match67(tok) && !(cpp && match608(tok->previous())))
            syntaxError(tok);
        if (match609(tok) && !(cpp && match594(tok->previous())))
            syntaxError(tok);
        if (match479(tok) &&
            !match610(tok->tokAt(-2))) {
            if (match611(tok->previous()))
                syntaxError(tok);
            if (cpp && match589(tok->previous()))
                syntaxError(tok);
            if (match612(tok->next()))
                syntaxError(tok);
        }
        if (match198(tok) &&
            !match198(tok->previous()) &&
            !match198(tok->next()) &&
            !match613(tok->previous()) &&
            !(tok->previous() && tok->previous()->isLiteral()) &&
            !match614(tok->previous())) {
            if (!match615(tok->previous()))
                syntaxError(tok, tok->strAt(-1) + " " + tok->str() + " " + tok->strAt(1));
            if (!match616(tok->next()))
                syntaxError(tok, tok->strAt(-1) + " " + tok->str() + " " + tok->strAt(1));
        }
        if (match617(tok) && !match618(tok->tokAt(3)))
            syntaxError(tok->next());
        if (match619(tok) && !tok->isKeyword() && tok->next()->isIncDecOp())
            syntaxError(tok->next());
        if (match620(tok))
            syntaxError(tok);
        if (match621(tok) && tok->strAt(-1) != MatchCompiler::makeConstString("operator"))
            syntaxError(tok, tok->str() + " " + tok->strAt(1));
        if (match622(tok) && (!match616(tok->next()) ||
                                              (tok->next()->isKeyword() && !match623(tok->next()))))
            syntaxError(tok);
        if (match624(tok) && tok->strAt(1) != MatchCompiler::makeConstString(">"))
            syntaxError(tok);
        if (match625(tok) && !match626(tok->next()))
            syntaxError(tok);
        if (match627(tok))
            syntaxError(tok);
        if (match628(tok))
            syntaxError(tok);
        if (match629(tok) &&
            !(cpp && tok->strAt(1) == MatchCompiler::makeConstString(">") && match594(tok->tokAt(-1))))
            syntaxError(tok);
        if (match630(tok) && (!cpp || !(tok->tokAt(-1) && match631(tok->tokAt(-2))))) {
            if (tok->next()->isUpperCaseName())
                unknownMacroError(tok->next());
            else
                syntaxError(tok);
        }

        if (tok->link() && match319(tok) && (!tok->tokAt(-1) || !tok->tokAt(-1)->isControlFlowKeyword())) {
            const Token* const end = tok->link();
            for (const Token* inner = tok->next(); inner != end; inner = inner->next()) {
                if (inner->str() == MatchCompiler::makeConstString("{"))
                    inner = inner->link();
                else if (inner->str() == MatchCompiler::makeConstString(";") || (match632(inner) && (!cpp || !match594(inner->previous())))) {
                    if (tok->tokAt(-1) && tok->tokAt(-1)->isUpperCaseName())
                        unknownMacroError(tok->tokAt(-1));
                    else
                        syntaxError(inner);
                }
            }
        }

        if ((!cpp || !match594(tok->previous())) && match633(tok))
            syntaxError(tok);
        if (tok->str() == MatchCompiler::makeConstString("typedef")) {
            for (const Token* tok2 = tok->next(); tok2 && tok2->str() != MatchCompiler::makeConstString(";"); tok2 = tok2->next()) {
                if (tok2->str() == MatchCompiler::makeConstString("{")) {
                    tok2 = tok2->link();
                    continue;
                }
                if (isUnevaluated(tok2)) {
                    tok2 = tok2->linkAt(1);
                    continue;
                }
                if (!tok2->next() || tok2->isControlFlowKeyword() || match634(tok2))
                    syntaxError(tok);
                if (match577(tok2) && tok2->str() == tok2->strAt(1)) {
                    if (match128(tok2->tokAt(2)))
                        continue;
                    if (tok2->isStandardType() && tok2->str() == MatchCompiler::makeConstString("long"))
                        continue;
                    if (match635(tok2->tokAt(-1)) || (isCPP() && match636(tok2->tokAt(-1))))
                        continue;
                    syntaxError(tok2);
                }
            }
        }
        if (cpp && tok->str() == MatchCompiler::makeConstString("namespace") && tok->tokAt(-1)) {
            if (!match637(tok->tokAt(-1))) {
                if (tok->tokAt(-1)->isUpperCaseName())
                    unknownMacroError(tok->tokAt(-1));
                else if (tok->linkAt(-1) && tok->linkAt(-1)->tokAt(-1) && tok->linkAt(-1)->tokAt(-1)->isUpperCaseName())
                    unknownMacroError(tok->linkAt(-1)->tokAt(-1));
                else
                    syntaxError(tok);
            }
        }
        if (cpp && tok->str() == MatchCompiler::makeConstString("using") && !match638(tok->next()))
            syntaxError(tok);
    }

    // ternary operator without :
    if (const Token *ternaryOp = findUnmatchedTernaryOp(tokens(), nullptr))
        syntaxError(ternaryOp);

    // Code must not start with an arithmetical operand
    if (match639(list.front()))
        syntaxError(list.front());

    // Code must end with } ; ) NAME
    if (!match640(list.back()))
        syntaxError(list.back());
    if (list.back()->str() == MatchCompiler::makeConstString(")") && !match641(list.back()->link()->previous()))
        syntaxError(list.back());
    for (const Token *end = list.back(); end && end->isName(); end = end->previous()) {
        if (match642(end))
            syntaxError(list.back());
    }
    if ((list.back()->str()==MatchCompiler::makeConstString(")") || list.back()->str()==MatchCompiler::makeConstString("}")) && list.back()->previous() && list.back()->previous()->isControlFlowKeyword())
        syntaxError(list.back()->previous());

    // Garbage templates..
    if (cpp) {
        for (const Token *tok = tokens(); tok; tok = tok->next()) {
            if (match255(tok) && !(match24(tok->tokAt(-1)) || (tok->tokAt(-1) && match643(tok->tokAt(-2)))))
                syntaxError(tok);
            if (match644(tok) && !match9(tok->tokAt(-1)))
                syntaxError(tok);
            if (!match292(tok))
                continue;
            if (!tok->tokAt(2) || tok->tokAt(2)->isLiteral())
                syntaxError(tok);
            if (tok->previous() && !match645(tok->previous())) {
                if (tok->previous()->isUpperCaseName())
                    unknownMacroError(tok->previous());
                else
                    syntaxError(tok);
            }
            const Token * const tok1 = tok->next()->findClosingBracket();
            if (!tok1)
                syntaxError(tok);
            if (!match646(tok1) &&
                !match647(tok1) &&
                !match648(tok1))
                syntaxError(tok1->next() ? tok1->next() : tok);
        }
    }

    // Objective C/C++
    for (const Token *tok = tokens(); tok; tok = tok->next()) {
        if (match649(tok))
            syntaxError(tok->next());
    }
}


bool Tokenizer::isGarbageExpr(const Token *start, const Token *end, bool allowSemicolon)
{
    for (const Token *tok = start; tok != end; tok = tok->next()) {
        if (tok->isControlFlowKeyword())
            return true;
        if (!allowSemicolon && tok->str() == MatchCompiler::makeConstString(";"))
            return true;
        if (tok->str() == MatchCompiler::makeConstString("{"))
            tok = tok->link();
    }
    return false;
}

std::string Tokenizer::simplifyString(const std::string &source)
{
    std::string str = source;

    for (std::string::size_type i = 0; i + 1U < str.size(); ++i) {
        if (str[i] != '\\')
            continue;

        int c = 'a';   // char
        int sz = 0;    // size of stringdata
        if (str[i+1] == 'x') {
            sz = 2;
            while (sz < 4 && std::isxdigit(static_cast<unsigned char>(str[i+sz])))
                sz++;
            if (sz > 2) {
                std::istringstream istr(str.substr(i+2, sz-2));
                istr >> std::hex >> c;
            }
        } else if (MathLib::isOctalDigit(str[i+1])) {
            sz = 2;
            while (sz < 4 && MathLib::isOctalDigit(str[i+sz]))
                sz++;
            std::istringstream istr(str.substr(i+1, sz-1));
            istr >> std::oct >> c;
            str = str.replace(i, sz, std::string(1U, static_cast<char>(c)));
            continue;
        }

        if (sz <= 2)
            i++;
        else if (i+sz < str.size())
            str.replace(i, sz, std::string(1U, static_cast<char>(c)));
        else
            str.replace(i, str.size() - i - 1U, "a");
    }

    return str;
}

void Tokenizer::simplifyFunctionTryCatch()
{
    if (!isCPP())
        return;

    for (Token * tok = list.front(); tok; tok = tok->next()) {
        if (!match650(tok))
            continue;
        const Token* par = tok->previous();
        while (par && par->isKeyword())
            par = par->previous();
        if (!TokenList::isFunctionHead(par, "try")) // TODO: this is supposed to a list of characters and not strings
            continue;

        Token* tryStartToken = skipInitializerList(tok->next());

        if (!match1(tryStartToken))
            syntaxError(tryStartToken, "Invalid function-try-catch block code. Did not find '{' for try body.");

        // find the end of the last catch block
        Token * const tryEndToken = tryStartToken->link();
        Token * endToken = tryEndToken;
        while (match428(endToken)) {
            endToken = endToken->linkAt(2)->next();
            if (!endToken)
                break;
            if (endToken->str() != MatchCompiler::makeConstString("{")) {
                endToken = nullptr;
                break;
            }
            endToken = endToken->link();
        }
        if (!endToken || endToken == tryEndToken)
            continue;

        tok->previous()->insertToken("{");
        endToken->insertToken("}");
        Token::createMutualLinks(tok->previous(), endToken->next());
    }
}

static bool isAnonymousEnum(const Token* tok)
{
    if (!match651(tok))
        return false;
    if (tok->index() > 2 && match652(tok->tokAt(-3)))
        return false;
    const Token* end = tok->next();
    if (end->str() == MatchCompiler::makeConstString(":")) {
        end = end->next();
        while (match293(end))
            end = end->next();
    }
    return end && match653(end->link());
}

void Tokenizer::simplifyStructDecl()
{
    const bool cpp = isCPP();

    // A counter that is used when giving unique names for anonymous structs.
    int count = 0;

    // Add names for anonymous structs
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!tok->isName())
            continue;
        // check for anonymous struct/union
        if (match654(tok)) {
            if (match655(tok->linkAt(1))) {
                tok->insertToken("Anonymous" + std::to_string(count++));
            }
        }
        // check for derived anonymous class/struct
        else if (cpp && match656(tok)) {
            const Token *tok1 = findmatch45(tok) ;
            if (tok1 && match657(tok1->link())) {
                tok->insertToken("Anonymous" + std::to_string(count++));
            }
        }
        // check for anonymous enum
        else if (isAnonymousEnum(tok)) {
            Token *start = tok->strAt(1) == MatchCompiler::makeConstString(":") ? tok->linkAt(3) : tok->linkAt(1);
            if (start && match658(start->next())) {
                start->linkAt(1)->deleteThis();
                start->next()->deleteThis();
            }
            tok->insertToken("Anonymous" + std::to_string(count++));
        }
    }

    // "{" token for current scope
    std::stack<const Token*> scopeStart;
    const Token* functionEnd = nullptr;

    for (Token *tok = list.front(); tok; tok = tok->next()) {

        // check for start of scope and determine if it is in a function
        if (tok->str() == MatchCompiler::makeConstString("{")) {
            scopeStart.push(tok);
            if (!functionEnd && match659(tok->previous()))
                functionEnd = tok->link();
        }

        // end of scope
        else if (tok->str() == MatchCompiler::makeConstString("}")) {
            if (!scopeStart.empty())
                scopeStart.pop();
            if (tok == functionEnd)
                functionEnd = nullptr;
        }

        // check for named struct/union
        else if (match660(tok)) {
            Token *start = tok;
            while (match12(start->previous()))
                start = start->previous();
            const Token * const type = tok->next();
            Token *next = tok->tokAt(2);

            while (next && !match661(next))
                next = next->next();
            if (!next || next->str() == MatchCompiler::makeConstString(";"))
                continue;
            Token* after = next->link();
            if (!after)
                break; // see #4869 segmentation fault in Tokenizer::simplifyStructDecl (invalid code)

            // check for named type
            if (match662(after->next())) {
                after->insertToken(";");
                after = after->next();
                while (!match663(start)) {
                    after->insertToken(start->str());
                    after = after->next();
                    start->deleteThis();
                }
                tok = start;
                if (!after)
                    break; // see #4869 segmentation fault in Tokenizer::simplifyStructDecl (invalid code)
                after->insertToken(type->str());
                if (start->str() != MatchCompiler::makeConstString("class")) {
                    after->insertToken(start->str());
                    after = after->next();
                }

                after = after->tokAt(2);

                if (match658(after)) {
                    after->link()->deleteThis();
                    after->deleteThis();
                }

                // check for initialization
                bool isFuncDecl = match56(after) && match14(after->linkAt(1));
                if (match664(after) && !isFuncDecl) {
                    after->insertToken("=");
                    after = after->next();
                    const bool isEnum = start->str() == MatchCompiler::makeConstString("enum");
                    if (!isEnum && cpp) {
                        after->insertToken(type->str());
                        after = after->next();
                    }

                    if (isEnum) {
                        if (match665(after->next())) {
                            after->next()->str("(");
                            after->linkAt(1)->str(")");
                        }
                    }
                }
            }
        }

        // check for anonymous struct/union
        else {
            // unnamed anonymous struct/union so possibly remove it
            bool done = false;
            while (!done && match654(tok) && match315(tok->linkAt(1))) {
                done = true;

                // is this a class/struct/union scope?
                bool isClassStructUnionScope = false;
                if (!scopeStart.empty()) {
                    for (const Token* tok2 = scopeStart.top()->previous(); tok2 && !match42(tok2); tok2 = tok2->previous()) {
                        if (match158(tok2)) {
                            isClassStructUnionScope = true;
                            break;
                        }
                    }
                }

                // remove unnamed anonymous struct/union
                // * not in class/struct/union scopes
                if (match315(tok->linkAt(1)) && !isClassStructUnionScope && tok->str() != MatchCompiler::makeConstString("union")) {
                    tok->linkAt(1)->previous()->deleteNext(2);
                    tok->deleteNext();
                    tok->deleteThis();
                    done = false;
                }
            }
        }
    }
}

void Tokenizer::simplifyCallingConvention()
{
    const bool windows = mSettings.platform.isWindows();

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        while (match666(tok) || (windows && match667(tok))) {
            tok->deleteThis();
        }
    }
}

static bool isAttribute(const Token* tok, bool gcc) {
    return gcc ? match668(tok) : match669(tok);
}

static Token* getTokenAfterAttributes(Token* tok, bool gccattr) {
    Token* after = tok;
    while (isAttribute(after, gccattr))
        after = after->linkAt(1)->next();
    return after;
}

static Token* getVariableTokenAfterAttributes(Token* tok) {
    Token *vartok = nullptr;
    Token *after = getTokenAfterAttributes(tok, true);

    // check if after variable name
    if (match670(after)) {
        Token *prev = tok->previous();
        while (match456(prev))
            prev = prev->link()->previous();
        if (match12(prev))
            vartok = prev;
    }


    // check if before variable name
    else {
        while (match671(after->next())) {
            after = after->next();
        }
        if (match24(after)) {
            vartok = after;
        }
    }

    return vartok;
}

Token* Tokenizer::getAttributeFuncTok(Token* tok, bool gccattr) const {
    if (!match56(tok))
        return nullptr;
    Token* const after = getTokenAfterAttributes(tok, gccattr);
    if (!after)
        syntaxError(tok);

    if (match672(after)) {
        Token *ftok = after;
        while (match673(ftok)) {
            if (ftok->str() == MatchCompiler::makeConstString("<")) {
                ftok = ftok->findClosingBracket();
                if (!ftok)
                    break;
            }
            ftok = ftok->next();
        }
        if (match74(ftok))
            ftok = ftok->tokAt(2);
        if (match674(ftok))
            return ftok;
    } else if (match675(after)) {
        Token *prev = tok->previous();
        while (match24(prev))
            prev = prev->previous();
        if (match40(prev)) {
            if (match56(prev->link()->previous()))
                return prev->link()->previous();
            if (match104(prev->link()->tokAt(-2)))
                return prev->link()->tokAt(-2);
        }
        if (match40(prev) && match676(prev->link()->tokAt(-2)) && isCPP())
            return prev->link()->tokAt(-2);
        if ((!prev || match677(prev)) && match24(tok->previous()))
            return tok->previous();
    }
    return nullptr;
}

void Tokenizer::simplifyDeclspec()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        while (isAttribute(tok, false)) {
            if (match678(tok->tokAt(2))) {
                Token *functok = getAttributeFuncTok(tok, false);
                if (functok) {
                    if (tok->strAt(2) == MatchCompiler::makeConstString("noreturn"))
                        functok->isAttributeNoreturn(true);
                    else if (tok->strAt(2) == MatchCompiler::makeConstString("nothrow"))
                        functok->isAttributeNothrow(true);
                    else
                        functok->isAttributeExport(true);
                }
            } else if (tok->strAt(2) == MatchCompiler::makeConstString("property"))
                tok->linkAt(1)->insertToken("__property");

            Token::eraseTokens(tok, tok->linkAt(1)->next());
            tok->deleteThis();
        }
    }
}

void Tokenizer::simplifyAttribute()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!tok->isKeyword() && match162(tok) && !mSettings.library.isNotLibraryFunction(tok)) {
            if (mSettings.library.isFunctionConst(tok->str(), true))
                tok->isAttributePure(true);
            if (mSettings.library.isFunctionConst(tok->str(), false))
                tok->isAttributeConst(true);
        }
        while (isAttribute(tok, true)) {
            Token *functok = getAttributeFuncTok(tok, true);

            for (Token *attr = tok->tokAt(2); attr->str() != MatchCompiler::makeConstString(")"); attr = attr->next()) {
                if (match56(attr))
                    attr = attr->linkAt(1);

                if (match679(attr)) {
                    if (!functok)
                        syntaxError(tok);
                    functok->isAttributeConstructor(true);
                }

                else if (match680(attr)) {
                    if (!functok)
                        syntaxError(tok);
                    functok->isAttributeDestructor(true);
                }

                else if (match681(attr)) {
                    Token *vartok = getVariableTokenAfterAttributes(tok);
                    if (!vartok)
                        vartok = functok;
                    if (vartok) {
                        const std::string &attribute(attr->strAt(1));
                        if (attribute.find("unused") != std::string::npos)
                            vartok->isAttributeUnused(true);
                        else
                            vartok->isAttributeUsed(true);
                    }
                }

                else if (match682(attr)) {
                    if (!functok)
                        syntaxError(tok);

                    const std::string &attribute(attr->strAt(1));
                    if (attribute.find("pure") != std::string::npos)
                        functok->isAttributePure(true);
                    else if (attribute.find("const") != std::string::npos)
                        functok->isAttributeConst(true);
                    else if (attribute.find("noreturn") != std::string::npos)
                        functok->isAttributeNoreturn(true);
                    else if (attribute.find("nothrow") != std::string::npos)
                        functok->isAttributeNothrow(true);
                    else if (attribute.find("warn_unused_result") != std::string::npos)
                        functok->isAttributeNodiscard(true);
                }

                else if (match683(attr) && match41(tok->previous()))
                    tok->previous()->isAttributePacked(true);

                else if (functok && match684(attr))
                    functok->isAttributeExport(true);

                else if (match685(attr)) {
                    Token *vartok = getVariableTokenAfterAttributes(tok);
                    if (vartok) {
                        const std::string& funcname = attr->strAt(3);
                        vartok->addAttributeCleanup(funcname);
                    }
                }
            }

            Token::eraseTokens(tok, tok->linkAt(1)->next());
            tok->deleteThis();
        }
    }
}

void Tokenizer::simplifyCppcheckAttribute()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->str() != MatchCompiler::makeConstString("("))
            continue;
        if (!tok->previous())
            continue;
        const std::string &attr = tok->strAt(-1);
        if (!startsWith(attr, "__cppcheck_"))
            continue;
        if (attr.compare(attr.size()-2, 2, "__") != 0) // TODO: ends_with("__")
            continue;

        Token *vartok = tok->link();
        while (match686(vartok->next())) {
            vartok = vartok->next();
            if (match56(vartok) && startsWith(vartok->str(),"__cppcheck_"))
                vartok = vartok->linkAt(1);
        }

        if (vartok->isName()) {
            if (match687(tok->previous()))
                vartok->setCppcheckAttribute(Token::CppcheckAttributesType::LOW,
                                             MathLib::toBigNumber(tok->tokAt(1)));
            else if (match688(tok->previous()))
                vartok->setCppcheckAttribute(Token::CppcheckAttributesType::HIGH,
                                             MathLib::toBigNumber(tok->tokAt(1)));
        }

        // Delete cppcheck attribute..
        if (tok->tokAt(-2)) {
            tok = tok->tokAt(-2);
            Token::eraseTokens(tok, tok->linkAt(2)->next());
        } else {
            tok = tok->previous();
            Token::eraseTokens(tok, tok->linkAt(1)->next());
            tok->str(";");
        }
    }
}

void Tokenizer::simplifyCPPAttribute()
{
    // According to cppreference alignas is a c21 feature however the macro is often available when compiling c11
    const bool hasAlignas = ((isCPP() && mSettings.standards.cpp >= Standards::CPP11) || (isC() && mSettings.standards.c >= Standards::C11));
    const bool hasCppAttribute = ((isCPP() && mSettings.standards.cpp >= Standards::CPP11) || (isC() && mSettings.standards.c >= Standards::C23));
    const bool hasMaybeUnused =((isCPP() && mSettings.standards.cpp >= Standards::CPP17) || (isC() && mSettings.standards.c >= Standards::C23));
    const bool hasMaybeUnusedUnderscores = (isC() && mSettings.standards.c >= Standards::C23);

    if (!hasAlignas && !hasCppAttribute)
        return;

    for (Token *tok = list.front(); tok;) {
        if (!isCPPAttribute(tok) && !isAlignAttribute(tok)) {
            tok = tok->next();
            continue;
        }
        if (isCPPAttribute(tok)) {
            if (!hasCppAttribute) {
                tok = skipCPPOrAlignAttribute(tok)->next();
                continue;
            }
            if (findmatch689(tok->tokAt(2), tok->link()) ) {
                Token * head = skipCPPOrAlignAttribute(tok)->next();
                while (isCPPAttribute(head) || isAlignAttribute(head))
                    head = skipCPPOrAlignAttribute(head)->next();
                while (match690(head)) // skip return type
                    head = head->next();
                if (head && head->str() == MatchCompiler::makeConstString("(") && (TokenList::isFunctionHead(head, "{;") || match691(head->link()))) {
                    head->previous()->isAttributeNoreturn(true);
                }
            } else if (findmatch692(tok->tokAt(2), tok->link()) ) {
                Token * head = skipCPPOrAlignAttribute(tok)->next();
                while (isCPPAttribute(head) || isAlignAttribute(head))
                    head = skipCPPOrAlignAttribute(head)->next();
                while (match690(head))
                    head = head->next();
                if (head && head->str() == MatchCompiler::makeConstString("(") && TokenList::isFunctionHead(head, "{;")) {
                    head->previous()->isAttributeNodiscard(true);
                }
            } else if (findmatch693(tok->tokAt(2), tok->link())  || findmatch694(tok->tokAt(2), tok->link()) ) {
                Token * head = skipCPPOrAlignAttribute(tok)->next();
                while (isCPPAttribute(head) || isAlignAttribute(head))
                    head = skipCPPOrAlignAttribute(head)->next();
                while (head && head->str() == MatchCompiler::makeConstString(";")) // we have semicollon after the attribute which would be removed in 'removeRedundantSemicolons()' so we skip it
                    head = head->next();
                if (head)
                    head->isAttributeFallthrough(true);
            } else if ((hasMaybeUnusedUnderscores && findmatch695(tok->tokAt(2), tok->link()) )
                       || (hasMaybeUnused && findmatch696(tok->tokAt(2), tok->link()) )) {
                Token* head = skipCPPOrAlignAttribute(tok)->next();
                while (isCPPAttribute(head) || isAlignAttribute(head))
                    head = skipCPPOrAlignAttribute(head)->next();

                if (!head)
                    syntaxError(tok);

                while (match697(head->next()))
                    head = head->next();
                if (match24(head) && !match698(head))
                    head->isAttributeMaybeUnused(true);
                else if (match24(tok->previous()) && match699(tok->link())) {
                    tok->previous()->isAttributeMaybeUnused(true);
                } else {
                    if (match69(head->next())) {
                        head = head->next();
                        const Token *end = head->link();
                        for (head = head->next(); end && head != end; head = head->next()) {
                            if (match24(head)) {
                                head->isAttributeMaybeUnused(true);
                            }
                        }
                    }
                }
            } else if (findmatch700(tok->tokAt(2), tok->link()) ) {
                Token* head = skipCPPOrAlignAttribute(tok)->next();
                while (isCPPAttribute(head) || isAlignAttribute(head))
                    head = skipCPPOrAlignAttribute(head)->next();
                if (!head)
                    syntaxError(tok);
                head->isAttributeUnused(true);
            } else if (match701(tok->previous())) {
                const Token *vartok = tok->tokAt(4);
                if (vartok->str() == MatchCompiler::makeConstString(":"))
                    vartok = vartok->next();
                Token *argtok = tok->tokAt(-2);
                while (argtok && argtok->str() != MatchCompiler::makeConstString("(")) {
                    if (argtok->str() == vartok->str())
                        break;
                    if (argtok->str() == MatchCompiler::makeConstString(")"))
                        argtok = argtok->link();
                    argtok = argtok->previous();
                }
                if (argtok && argtok->str() == vartok->str()) {
                    if (vartok->strAt(1) == MatchCompiler::makeConstString(">="))
                        argtok->setCppcheckAttribute(Token::CppcheckAttributesType::LOW,
                                                     MathLib::toBigNumber(vartok->tokAt(2)));
                    else if (vartok->strAt(1) == MatchCompiler::makeConstString(">"))
                        argtok->setCppcheckAttribute(Token::CppcheckAttributesType::LOW,
                                                     MathLib::toBigNumber(vartok->tokAt(2)) + 1);
                    else if (vartok->strAt(1) == MatchCompiler::makeConstString("<="))
                        argtok->setCppcheckAttribute(Token::CppcheckAttributesType::HIGH,
                                                     MathLib::toBigNumber(vartok->tokAt(2)));
                    else if (vartok->strAt(1) == MatchCompiler::makeConstString("<"))
                        argtok->setCppcheckAttribute(Token::CppcheckAttributesType::HIGH,
                                                     MathLib::toBigNumber(vartok->tokAt(2)) - 1);
                }
            }
        } else {
            // alignas(expr)

            if (!hasAlignas) {
                tok = skipCPPOrAlignAttribute(tok)->next();
                continue;
            }

            // alignment requirements could be checked here

            Token* atok = nullptr;
            if (match24(tok->previous()))
                atok = tok->previous();
            else {
                atok = tok;
                while (isCPPAttribute(atok) || isAlignAttribute(atok))
                    atok = skipCPPOrAlignAttribute(atok)->next();
            }
            if (atok) {
                std::string a;
                for (const Token* t = tok->tokAt(2); t && t->str() != MatchCompiler::makeConstString(")"); t = t->next())
                    a += " " + t->str();
                if (a.size() > 1)
                    atok->addAttributeAlignas(a.substr(1));
            }
        }
        Token::eraseTokens(tok, skipCPPOrAlignAttribute(tok)->next());
        tok->deleteThis();
    }
}

void Tokenizer::simplifySpaceshipOperator()
{
    if (isCPP() && mSettings.standards.cpp >= Standards::CPP20) {
        for (Token *tok = list.front(); tok && tok->next(); tok = tok->next()) {
            if (match702(tok)) {
                tok->str("<=>");
                tok->deleteNext();
            }
        }
    }
}

static const std::unordered_set<std::string> keywords = {
    "inline"
    , "_inline"
    , "__inline"
    , "__forceinline"
    , "register"
    , "__restrict"
    , "__restrict__"
    , "__thread"
};
// Remove "inline", "register", "restrict", "override", "static" and "constexpr"
// "restrict" keyword
//   - New to 1999 ANSI/ISO C standard
//   - Not in C++ standard yet
void Tokenizer::simplifyKeyword()
{
    // FIXME: There is a risk that "keywords" are removed by mistake. This
    // code should be fixed so it doesn't remove variables etc. Nonstandard
    // keywords should be defined with a library instead. For instance the
    // linux kernel code at least uses "_inline" as struct member name at some
    // places.

    const bool c99 = isC() && mSettings.standards.c >= Standards::C99;
    const bool cpp11 = isCPP() && mSettings.standards.cpp >= Standards::CPP11;
    const bool cpp20 = isCPP() && mSettings.standards.cpp >= Standards::CPP20;

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (keywords.find(tok->str()) != keywords.end()) {
            // Don't remove struct members
            if (!match198(tok->previous())) {
                const bool isinline = (tok->str().find("inline") != std::string::npos);
                const bool isrestrict = (tok->str().find("restrict") != std::string::npos);
                if (isinline || isrestrict) {
                    for (Token *temp = tok->next(); match24(temp); temp = temp->next()) {
                        if (isinline)
                            temp->isInline(true);
                        if (isrestrict)
                            temp->isRestrict(true);
                    }
                }
                tok->deleteThis(); // Simplify..
            }
        }

        if (isC() || mSettings.standards.cpp == Standards::CPP03) {
            if (tok->str() == MatchCompiler::makeConstString("auto"))
                tok->deleteThis();
        }

        // simplify static keyword:
        // void foo( int [ static 5 ] ); ==> void foo( int [ 5 ] );
        if (match703(tok))
            tok->deleteNext();

        if (c99) {
            auto getTypeTokens = [tok]() {
                std::vector<Token*> ret;
                for (Token *temp = tok; match24(temp); temp = temp->previous()) {
                    if (!temp->isKeyword())
                        ret.emplace_back(temp);
                }
                for (Token *temp = tok->next(); match24(temp); temp = temp->next()) {
                    if (!temp->isKeyword())
                        ret.emplace_back(temp);
                }
                return ret;
            };

            if (tok->str() == MatchCompiler::makeConstString("restrict")) {
                for (Token* temp: getTypeTokens())
                    temp->isRestrict(true);
                tok->deleteThis();
            }

            if (mSettings.standards.c >= Standards::C11) {
                while (tok->str() == MatchCompiler::makeConstString("_Atomic")) {
                    if (match94(tok->next())) {
                        tok->linkAt(1)->deleteThis();
                        tok->next()->deleteThis();
                    }
                    for (Token* temp: getTypeTokens())
                        temp->isAtomic(true);
                    tok->deleteThis();
                }
            }
        }

        else if (cpp11) {
            if (cpp20 && tok->str() == MatchCompiler::makeConstString("consteval")) {
                tok->originalName(tok->str());
                tok->str("constexpr");
            } else if (cpp20 && tok->str() == MatchCompiler::makeConstString("constinit")) {
                tok->deleteThis();
            }

            // final:
            // 1) struct name final { };   <- struct is final
            if (match704(tok->previous())) {
                Token* finalTok = tok->next();
                if (tok->isUpperCaseName() && match12(finalTok) && finalTok->str() != MatchCompiler::makeConstString("final")) {
                    tok = finalTok;
                    finalTok = finalTok->next();
                }
                if (match146(finalTok)) { // specialization
                    finalTok = finalTok->findClosingBracket();
                    if (finalTok)
                        finalTok = finalTok->next();
                }
                if (match705(finalTok)) {
                    finalTok->deleteThis();
                    tok->previous()->isFinalType(true);
                }
            }

            // noexcept -> noexcept(true)
            // 2) void f() noexcept; -> void f() noexcept(true);
            else if (match706(tok)) {
                // Insertion is done in inverse order
                // The brackets are linked together accordingly afterwards
                Token* tokNoExcept = tok->next();
                while (tokNoExcept->str() != MatchCompiler::makeConstString("noexcept"))
                    tokNoExcept = tokNoExcept->next();
                tokNoExcept->insertToken(")");
                Token * braceEnd = tokNoExcept->next();
                tokNoExcept->insertToken("true");
                tokNoExcept->insertToken("(");
                Token * braceStart = tokNoExcept->next();
                tok = tok->tokAt(3);
                Token::createMutualLinks(braceStart, braceEnd);
            }

            // 3) thread_local -> static
            //    on single thread thread_local has the effect of static
            else if (tok->str() == MatchCompiler::makeConstString("thread_local")) {
                tok->originalName(tok->str());
                tok->str("static");
            }
        }
    }
}

static Token* setTokenDebug(Token* start, TokenDebug td)
{
    if (!start->link())
        return nullptr;
    Token* end = start->link();
    start->deleteThis();
    for (Token* tok = start; tok != end; tok = tok->next()) {
        tok->setTokenDebug(td);
    }
    end->deleteThis();
    return end;
}

void Tokenizer::simplifyDebug()
{
    if (!mSettings.debugnormal && !mSettings.debugwarnings)
        return;
    static const std::unordered_map<std::string, TokenDebug> m = {{"debug_valueflow", TokenDebug::ValueFlow},
        {"debug_valuetype", TokenDebug::ValueType}};
    for (Token* tok = list.front(); tok; tok = tok->next()) {
        if (!match56(tok))
            continue;
        auto it = m.find(tok->str());
        if (it != m.end()) {
            tok->deleteThis();
            tok = setTokenDebug(tok, it->second);
        }
    }
}

void Tokenizer::simplifyAssignmentBlock()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (match707(tok)) {
            const std::string &varname = tok->strAt(1);

            // goto the "} )"
            int indentlevel = 0;
            Token *tok2 = tok;
            while (nullptr != (tok2 = tok2->next())) {
                if (match497(tok2))
                    ++indentlevel;
                else if (match708(tok2)) {
                    if (indentlevel <= 2)
                        break;
                    --indentlevel;
                } else if (indentlevel == 2 && tok2->str() == varname && match709(tok2->previous()))
                    // declaring variable in inner scope with same name as lhs variable
                    break;
            }
            if (indentlevel == 2 && match710(tok2)) {
                tok2 = tok2->tokAt(-3);
                if (match711(tok2)) {
                    tok2->insertToken("=");
                    tok2->insertToken(tok->strAt(1));
                    tok2->next()->varId(tok->next()->varId());
                    tok->deleteNext(3);
                    tok2->tokAt(5)->deleteNext();
                }
            }
        }
    }
}

// Remove __asm..
void Tokenizer::simplifyAsm()
{
    std::string instruction;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (match712(tok) &&
            tok->linkAt(1)->next()) {
            instruction = tok->tokAt(2)->stringifyList(tok->linkAt(1));
            Token::eraseTokens(tok, tok->linkAt(1)->next());
        }

        else if (match713(tok)) {
            // Goto "("
            Token *partok = tok->next();
            if (partok->str() != MatchCompiler::makeConstString("("))
                partok = partok->next();
            instruction = partok->next()->stringifyList(partok->link());
            Token::eraseTokens(tok, partok->link()->next());
        }

        else if (match714(tok)) {
            Token *endasm = tok->next();
            const Token *firstSemiColon = nullptr;
            int comment = 0;
            while (match715(endasm) || (endasm && (endasm->isLiteral() || endasm->linenr() == comment))) {
                if (match716(endasm))
                    break;
                if (endasm->str() == MatchCompiler::makeConstString(";")) {
                    comment = endasm->linenr();
                    if (!firstSemiColon)
                        firstSemiColon = endasm;
                }
                endasm = endasm->next();
            }
            if (match717(endasm)) {
                instruction = tok->next()->stringifyList(endasm);
                Token::eraseTokens(tok, endasm->next());
                if (!match128(tok->next()))
                    tok->insertToken(";");
            } else if (firstSemiColon) {
                instruction = tok->next()->stringifyList(firstSemiColon);
                Token::eraseTokens(tok, firstSemiColon);
            } else if (!endasm) {
                instruction = tok->next()->stringifyList(endasm);
                Token::eraseTokens(tok, endasm);
                tok->insertToken(";");
            } else
                continue;
        }

        else
            continue;

        if (match718(tok->previous())) {
            tok->deleteThis();
            continue;
        }

        // insert "asm ( "instruction" )"
        tok->str("asm");
        if (tok->strAt(1) != MatchCompiler::makeConstString(";") && tok->strAt(1) != MatchCompiler::makeConstString("{"))
            tok->insertToken(";");
        tok->insertToken(")");
        tok->insertToken("\"" + instruction + "\"");
        tok->insertToken("(");

        tok = tok->next();
        Token::createMutualLinks(tok, tok->tokAt(2));

        //move the new tokens in the same line as ";" if available
        tok = tok->tokAt(2);
        if (tok->next() && tok->strAt(1) == MatchCompiler::makeConstString(";") &&
            tok->next()->linenr() != tok->linenr()) {
            const int endposition = tok->next()->linenr();
            tok = tok->tokAt(-3);
            for (int i = 0; i < 4; ++i) {
                tok = tok->next();
                tok->linenr(endposition);
            }
        }
    }
}

void Tokenizer::simplifyAsm2()
{
    // Block declarations: ^{}
    // A C extension used to create lambda like closures.

    // Put ^{} statements in asm()
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->str() != MatchCompiler::makeConstString("^"))
            continue;

        if (match719(tok) || (match14(tok->linkAt(1)) && tok->strAt(-1) != MatchCompiler::makeConstString("operator"))) {
            Token * start = tok;
            while (start && !match720(start)) {
                if (start->link() && match721(start))
                    start = start->link();
                start = start->previous();
            }

            const Token *last = tok->linkAt(1);
            if (match14(last))
                last = last->linkAt(1);
            last = last->next();
            while (last && !match722(last)) {
                if (match68(last))
                    last = last->link();
                last = last->next();
            }

            if (start && last) {
                std::string asmcode;
                while (start->next() != last) {
                    asmcode += start->strAt(1);
                    start->deleteNext();
                }
                if (last->str() == MatchCompiler::makeConstString("}"))
                    start->insertToken(";");
                start->insertToken(")");
                start->insertToken("\"" + asmcode + "\"");
                start->insertToken("(");
                start->insertToken("asm");
                start->tokAt(2)->link(start->tokAt(4));
                start->tokAt(4)->link(start->tokAt(2));
                tok = start->tokAt(4);
            }
        }
    }
}

void Tokenizer::simplifyAt()
{
    std::set<std::string> var;

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (match723(tok)) {
            const Token *end = tok->tokAt(2);
            if (end->isLiteral())
                end = end->next();
            else if (end->str() == MatchCompiler::makeConstString("(")) {
                int par = 0;
                while ((end = end->next()) != nullptr) {
                    if (end->str() == MatchCompiler::makeConstString("("))
                        par++;
                    else if (end->str() == MatchCompiler::makeConstString(")")) {
                        if (--par < 0)
                            break;
                    }
                }
                end = end ? end->next() : nullptr;
            } else if (var.find(end->str()) != var.end())
                end = end->next();
            else
                continue;

            if (match724(end))
                end = end->tokAt(2);

            if (match725(end)) {
                if (tok->isName())
                    var.insert(tok->str());
                tok->isAtAddress(true);
                Token::eraseTokens(tok, end);
            }
        }

        // keywords in compiler from cosmic software for STM8
        // TODO: Should use platform configuration.
        if (match726(tok)) {
            tok->str(tok->strAt(1) + "@");
            tok->deleteNext();
        }
    }
}

// Simplify bitfields
void Tokenizer::simplifyBitfields()
{
    std::size_t anonymousBitfieldCounter = 0;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        Token *last = nullptr;

        if (match305(tok))
            tok = tok->linkAt(1);

        if (!match727(tok))
            continue;

        bool isEnum = false;
        if (tok->str() == MatchCompiler::makeConstString("}")) {
            const Token *type = tok->link()->previous();
            while (type && type->isName()) {
                if (type->str() == MatchCompiler::makeConstString("enum")) {
                    isEnum = true;
                    break;
                }
                type = type->previous();
            }
        }

        const auto tooLargeError = [this](const Token *tok) {
            const auto max = std::numeric_limits<short>::max();
            reportError(tok,
                        Severity::warning,
                        "tooLargeBitField",
                        "Bit-field size exceeds max number of bits " + std::to_string(max));
        };

        Token* typeTok = tok->next();
        while (match23(typeTok))
            typeTok = typeTok->next();
        if (match175(typeTok))
            typeTok = typeTok->next();
        while (match108(typeTok))
            typeTok = typeTok->tokAt(2);
        if (match728(typeTok) &&
            !match729(tok->next()) &&
            !match730(tok->tokAt(2))) {
            Token *tok1 = typeTok->next();
            if (match731(tok1))
                if (!tok1->setBits(MathLib::toBigNumber(tok1->tokAt(2))))
                    tooLargeError(tok1->tokAt(2));
            if (tok1 && tok1->tokAt(2) &&
                (match732(tok1->tokAt(2)) ||
                 !match733(tok1->tokAt(2)))) {
                while (tok1->next() && !match734(tok1->next())) {
                    if (match319(tok1->next()))
                        Token::eraseTokens(tok1, tok1->linkAt(1));
                    tok1->deleteNext();
                }

                last = tok1->next();
            }
        } else if (isEnum && match735(tok)) {
            if (tok->strAt(1) == MatchCompiler::makeConstString(":")) {
                tok->deleteNext(2);
                tok->insertToken("Anonymous");
            } else {
                tok->next()->deleteNext(2);
            }
        } else if (match736(typeTok) &&
                   typeTok->str() != MatchCompiler::makeConstString("default")) {
            const std::size_t id = anonymousBitfieldCounter++;
            const std::string name = "anonymous@" + std::to_string(id);
            Token *newTok = typeTok->insertToken(name);
            newTok->isAnonymous(true);
            bool failed;
            if (newTok->tokAt(2)->isBoolean())
                failed = !newTok->setBits(newTok->strAt(2) == MatchCompiler::makeConstString("true"));
            else
                failed = !newTok->setBits(MathLib::toBigNumber(newTok->tokAt(2)));
            if (failed)
                tooLargeError(newTok->tokAt(2));
            newTok->deleteNext(2);
        }

        if (last && last->str() == MatchCompiler::makeConstString(",")) {
            Token * tok1 = last;
            tok1->str(";");

            const Token *const tok2 = tok->next();
            tok1->insertToken(tok2->str());
            tok1 = tok1->next();
            tok1->isSigned(tok2->isSigned());
            tok1->isUnsigned(tok2->isUnsigned());
            tok1->isLong(tok2->isLong());
        }
    }
}

static bool isStdContainerOrIterator(const Token* tok, const Settings& settings)
{
    const Library::Container* ctr = settings.library.detectContainerOrIterator(tok, nullptr, /*withoutStd*/ true);
    return ctr && startsWith(ctr->startPattern, "std ::");
}

static bool isStdSmartPointer(const Token* tok, const Settings& settings)
{
    const Library::SmartPointer* ptr = settings.library.detectSmartPointer(tok, /*withoutStd*/ true);
    return ptr && startsWith(ptr->name, "std::");
}

// Add std:: in front of std classes, when using namespace std; was given
void Tokenizer::simplifyNamespaceStd()
{
    if (!isCPP())
        return;

    std::set<std::string> userFunctions;

    for (Token* tok = findmatch737(list.front()) ; tok; tok = tok->next()) {
        bool insert = false;
        if (match738(tok)) { // Don't replace within enum definitions
            skipEnumBody(tok);
        }
        if (!tok->isName() || tok->isKeyword() || tok->isStandardType() || tok->varId())
            continue;
        if (match739(tok->previous()))
            continue;
        if (match94(tok->next())) {
            if (TokenList::isFunctionHead(tok->next(), "{"))
                userFunctions.insert(tok->str());
            else if (TokenList::isFunctionHead(tok->next(), ";")) {
                const Token *start = tok;
                while (match740(start->previous()))
                    start = start->previous();
                if (start != tok && start->isName() && !start->isKeyword() && (!start->previous() || match42(start->previous())))
                    userFunctions.insert(tok->str());
            }
            if (userFunctions.find(tok->str()) == userFunctions.end() && mSettings.library.matchArguments(tok, "std::" + tok->str()))
                insert = true;
        } else if (match146(tok->next()) &&
                   (isStdContainerOrIterator(tok, mSettings) || isStdSmartPointer(tok, mSettings)))
            insert = true;
        else if (mSettings.library.hasAnyTypeCheck("std::" + tok->str()) ||
                 mSettings.library.podtype("std::" + tok->str()) ||
                 isStdContainerOrIterator(tok, mSettings))
            insert = true;

        if (insert) {
            tok->previous()->insertToken("std");
            tok->previous()->linenr(tok->linenr()); // For stylistic reasons we put the std:: in the same line as the following token
            tok->previous()->fileIndex(tok->fileIndex());
            tok->previous()->insertToken("::");
        }
    }

    for (Token* tok = list.front(); tok; tok = tok->next()) {
        if (match741(tok)) {
            Token::eraseTokens(tok, tok->tokAt(4));
            tok->deleteThis();
        }
    }
}


void Tokenizer::simplifyMicrosoftMemoryFunctions()
{
    // skip if not Windows
    if (!mSettings.platform.isWindows())
        return;

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->strAt(1) != MatchCompiler::makeConstString("("))
            continue;

        if (match742(tok)) {
            tok->str("memcpy");
        } else if (match743(tok)) {
            tok->str("memmove");
        } else if (match744(tok)) {
            // FillMemory(dst, len, val) -> memset(dst, val, len)
            tok->str("memset");

            Token *tok1 = tok->tokAt(2);
            if (tok1)
                tok1 = tok1->nextArgument(); // Second argument
            if (tok1) {
                Token *tok2 = tok1->nextArgument(); // Third argument

                if (tok2)
                    Token::move(tok1->previous(), tok2->tokAt(-2), tok->linkAt(1)->previous()); // Swap third with second argument
            }
        } else if (match745(tok)) {
            // ZeroMemory(dst, len) -> memset(dst, 0, len)
            tok->str("memset");

            Token *tok1 = tok->tokAt(2);
            if (tok1)
                tok1 = tok1->nextArgument(); // Second argument

            if (tok1) {
                tok1 = tok1->previous();
                tok1->insertToken("0");
                tok1 = tok1->next();
                tok1->insertToken(",");
            }
        } else if (match746(tok)) {
            // RtlCompareMemory(src1, src2, len) -> memcmp(src1, src2, len)
            tok->str("memcmp");
            // For the record, when memcmp returns 0, both strings are equal.
            // When RtlCompareMemory returns len, both strings are equal.
            // It might be needed to improve this replacement by something
            // like ((len - memcmp(src1, src2, len)) % (len + 1)) to
            // respect execution path (if required)
        }
    }
}

namespace {
    struct triplet {
        triplet(const char* m, const char* u) :  mbcs(m), unicode(u) {}
        std::string mbcs, unicode;
    };

    const std::map<std::string, triplet> apis = {
        std::make_pair("_topen", triplet("open", "_wopen")),
        std::make_pair("_tsopen_s", triplet("_sopen_s", "_wsopen_s")),
        std::make_pair("_tfopen", triplet("fopen", "_wfopen")),
        std::make_pair("_tfopen_s", triplet("fopen_s", "_wfopen_s")),
        std::make_pair("_tfreopen", triplet("freopen", "_wfreopen")),
        std::make_pair("_tfreopen_s", triplet("freopen_s", "_wfreopen_s")),
        std::make_pair("_tcscat", triplet("strcat", "wcscat")),
        std::make_pair("_tcschr", triplet("strchr", "wcschr")),
        std::make_pair("_tcscmp", triplet("strcmp", "wcscmp")),
        std::make_pair("_tcsdup", triplet("strdup", "wcsdup")),
        std::make_pair("_tcscpy", triplet("strcpy", "wcscpy")),
        std::make_pair("_tcslen", triplet("strlen", "wcslen")),
        std::make_pair("_tcsncat", triplet("strncat", "wcsncat")),
        std::make_pair("_tcsncpy", triplet("strncpy", "wcsncpy")),
        std::make_pair("_tcsnlen", triplet("strnlen", "wcsnlen")),
        std::make_pair("_tcsrchr", triplet("strrchr", "wcsrchr")),
        std::make_pair("_tcsstr", triplet("strstr", "wcsstr")),
        std::make_pair("_tcstok", triplet("strtok", "wcstok")),
        std::make_pair("_ftprintf", triplet("fprintf", "fwprintf")),
        std::make_pair("_tprintf", triplet("printf", "wprintf")),
        std::make_pair("_stprintf", triplet("sprintf", "swprintf")),
        std::make_pair("_sntprintf", triplet("_snprintf", "_snwprintf")),
        std::make_pair("_ftscanf", triplet("fscanf", "fwscanf")),
        std::make_pair("_tscanf", triplet("scanf", "wscanf")),
        std::make_pair("_stscanf", triplet("sscanf", "swscanf")),
        std::make_pair("_ftprintf_s", triplet("fprintf_s", "fwprintf_s")),
        std::make_pair("_tprintf_s", triplet("printf_s", "wprintf_s")),
        std::make_pair("_stprintf_s", triplet("sprintf_s", "swprintf_s")),
        std::make_pair("_sntprintf_s", triplet("_snprintf_s", "_snwprintf_s")),
        std::make_pair("_ftscanf_s", triplet("fscanf_s", "fwscanf_s")),
        std::make_pair("_tscanf_s", triplet("scanf_s", "wscanf_s")),
        std::make_pair("_stscanf_s", triplet("sscanf_s", "swscanf_s"))
    };
}

void Tokenizer::simplifyMicrosoftStringFunctions()
{
    // skip if not Windows
    if (!mSettings.platform.isWindows())
        return;

    const bool ansi = mSettings.platform.type == Platform::Type::Win32A;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->strAt(1) != MatchCompiler::makeConstString("("))
            continue;

        const auto match = utils::as_const(apis).find(tok->str());
        if (match!=apis.end()) {
            tok->str(ansi ? match->second.mbcs : match->second.unicode);
            tok->originalName(match->first);
        } else if (match747(tok)) {
            tok->deleteNext();
            tok->deleteThis();
            tok->deleteNext();
            if (!ansi) {
                tok->isLong(true);
                if (tok->str()[0] != 'L')
                    tok->str("L" + tok->str());
            }
            while (match747(tok->next())) {
                tok->next()->deleteNext();
                tok->next()->deleteThis();
                tok->next()->deleteNext();
                tok->concatStr(tok->strAt(1));
                tok->deleteNext();
            }
        }
    }
}

// Remove Borland code
void Tokenizer::simplifyBorland()
{
    // skip if not Windows
    if (!mSettings.platform.isWindows())
        return;
    if (isC())
        return;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (match748(tok)) {
            tok->deleteNext();
        }
    }

    // I think that these classes are always declared at the outer scope
    // I save some time by ignoring inner classes.
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (tok->str() == MatchCompiler::makeConstString("{") && !match749(tok->tokAt(-2))) {
            tok = tok->link();
            if (!tok)
                break;
        } else if (match750(tok)) {
            while (tok && tok->str() != MatchCompiler::makeConstString("{") && tok->str() != MatchCompiler::makeConstString(";"))
                tok = tok->next();
            if (!tok)
                break;
            if (tok->str() == MatchCompiler::makeConstString(";"))
                continue;

            const Token* end = tok->link()->next();
            for (Token *tok2 = tok->next(); tok2 != end; tok2 = tok2->next()) {
                if (tok2->str() == MatchCompiler::makeConstString("__property") &&
                    match751(tok2->previous())) {
                    while (tok2->next() && !match451(tok2->next()))
                        tok2->deleteNext();
                    tok2->deleteThis();
                    if (tok2->str() == MatchCompiler::makeConstString("{")) {
                        Token::eraseTokens(tok2, tok2->link());
                        tok2->deleteNext();
                        tok2->deleteThis();

                        // insert "; __property ;"
                        tok2->previous()->insertToken(";");
                        tok2->previous()->insertToken("__property");
                        tok2->previous()->insertToken(";");
                    }
                }
            }
        }
    }
}

void Tokenizer::createSymbolDatabase()
{
    if (!mSymbolDatabase)
        mSymbolDatabase = new SymbolDatabase(*this);
    mSymbolDatabase->validate();
}

bool Tokenizer::operatorEnd(const Token * tok)
{
    if (tok && tok->str() == MatchCompiler::makeConstString(")")) {
        if (TokenList::isFunctionHead(tok, "{;?:["))
            return true;

        tok = tok->next();
        while (tok && !match752(tok)) {
            if (match753(tok)) {
                tok = tok->next();
            } else if (tok->str() == MatchCompiler::makeConstString("noexcept")) {
                tok = tok->next();
                if (tok && tok->str() == MatchCompiler::makeConstString("(")) {
                    tok = tok->link()->next();
                }
            } else if (tok->str() == MatchCompiler::makeConstString("throw") && tok->next() && tok->strAt(1) == MatchCompiler::makeConstString("(")) {
                tok = tok->linkAt(1)->next();
            }
            // unknown macros ") MACRO {" and ") MACRO(...) {"
            else if (tok->isUpperCaseName()) {
                tok = tok->next();
                if (tok && tok->str() == MatchCompiler::makeConstString("(")) {
                    tok = tok->link()->next();
                }
            } else if (match754(tok) ||
                       (match510(tok) && !TokenList::isFunctionHead(tok->next(), "{")))
                break;
            else
                return false;
        }

        return true;
    }

    return false;
}

void Tokenizer::simplifyOperatorName()
{
    if (isC())
        return;

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (match755(tok)) {
            tok->next()->str("operator" + tok->strAt(2));
            tok->next()->tokType(Token::Type::eKeyword); // we need to preserve the keyword type after setting a non-keyword string
            // TODO: tok->next()->isOperatorKeyword(true);
            tok->next()->deleteNext();
            continue;
        }

        if (tok->str() != MatchCompiler::makeConstString("operator"))
            continue;
        // operator op
        if (match676(tok) && !operatorEnd(tok->linkAt(2))) {
            tok->str(tok->str() + tok->strAt(1));
            tok->tokType(Token::Type::eKeyword); // we need to preserve the keyword type after setting a non-keyword string
            // TODO: tok->isOperatorKeyword(true);
            tok->deleteNext();
            continue;
        }
        std::string op;
        Token *par = tok->next();
        bool done = false;
        while (!done && par) {
            done = true;
            if (par->isName()) {
                op += par->str();
                par = par->next();
                // merge namespaces eg. 'operator std :: string () const {'
                if (match756(par)) {
                    op += par->str();
                    par = par->next();
                }
                done = false;
            } else if (match757(par)) {
                // check for operator in template
                if (par->str() == MatchCompiler::makeConstString(",") && !op.empty())
                    break;
                if (!(match758(par) && !op.empty())) {
                    op += par->str() == MatchCompiler::makeConstString(".") ? par->originalName() : par->str();
                    par = par->next();
                    done = false;
                }
            } else if (match759(par)) {
                op += "[]";
                par = par->tokAt(2);
                done = false;
            } else if (match760(par)) {
                // break out and simplify..
                if (operatorEnd(par->next()))
                    break;

                while (par->str() != MatchCompiler::makeConstString(")")) {
                    op += par->str();
                    par = par->next();
                }
                op += ")";
                par = par->next();
                if (match761(par)) {
                    op.clear();
                    par = nullptr;
                    break;
                }
                done = false;
            } else if (match762(par)) {
                op += "\"\"";
                op += par->strAt(1);
                par = par->tokAt(2);
                if (par->str() == MatchCompiler::makeConstString(")")) {
                    par->link()->deleteThis();
                    par = par->next();
                    par->deletePrevious();
                    tok = par->tokAt(-3);
                }
                done = true;
            } else if (par->str() == MatchCompiler::makeConstString("::")) {
                op += par->str();
                par = par->next();
                done = false;
            } else if (par->str() == MatchCompiler::makeConstString(";") || par->str() == MatchCompiler::makeConstString(")")) {
                done = true;
            } else if (par->str() != MatchCompiler::makeConstString("(")) {
                syntaxError(par, "operator");
            }
        }

        const bool returnsRef = match763(par) && tok->next()->isName();
        if (par && !op.empty()) {
            if (returnsRef) {
                Token* tok_op = par->next()->insertToken("operator" + op);
                // TODO: tok_op->tokType(Token::Type::eKeyword); // the given token is not a keyword but should be treated as such
                tok_op->isOperatorKeyword(true);
                tok->deleteThis();
            }
            else {
                tok->str("operator" + op);
                tok->tokType(Token::Type::eKeyword); // we need to preserve the keyword type after setting a non-keyword string
                // TODO: tok->isOperatorKeyword(true);
                Token::eraseTokens(tok, par);
            }
        }

        if (!op.empty() && !returnsRef)
            tok->isOperatorKeyword(true);
    }

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (match764(tok)) {
            const std::string name = tok->strAt(2);
            Token * const str = tok->next();
            str->deleteNext();
            tok->insertToken("operator\"\"" + name);
            tok = tok->next();
            tok->isOperatorKeyword(true);
            tok->insertToken("(");
            str->insertToken(")");
            Token::createMutualLinks(tok->next(), str->next());
            str->insertToken(std::to_string(Token::getStrLength(str)));
            str->insertToken(",");
        }
    }

    if (mSettings.debugwarnings) {
        const Token *tok = list.front();

        while ((tok = findmatch765(tok) ) != nullptr) {
            reportError(tok, Severity::debug, "debug",
                        "simplifyOperatorName: found unsimplified operator name");
            tok = tok->next();
        }
    }
}

void Tokenizer::simplifyOverloadedOperators()
{
    if (isC())
        return;
    std::set<std::string> classNames;
    std::set<nonneg int> classVars;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!tok->isName())
            continue;

        if (match766(tok) && match74(tok->tokAt(-2))) {
            tok = tok->next();
            tok->insertToken("operator()");
            tok->insertToken(".");
            continue;
        }

        // Get classes that have operator() member
        if (match142(tok)) {
            int indent = 0;
            for (const Token *tok2 = tok->next(); tok2; tok2 = tok2->next()) {
                if (tok2->str() == MatchCompiler::makeConstString("}"))
                    break;
                if (indent == 0 && tok2->str() == MatchCompiler::makeConstString(";"))
                    break;
                if (tok2->str() == MatchCompiler::makeConstString("{")) {
                    if (indent == 0)
                        ++indent;
                    else
                        tok2 = tok2->link();
                } else if (indent == 1 && match767(tok2) && TokenList::isFunctionHead(tok2->next(), ";{")) {
                    classNames.insert(tok->strAt(1));
                    break;
                }
            }
        }

        // Get variables that have operator() member
        if (match768(tok) && classNames.find(tok->str()) != classNames.end()) {
            tok = tok->next();
            while (!tok->isName())
                tok = tok->next();
            classVars.insert(tok->varId());
        }

        // Simplify operator() calls
        if (match769(tok) && classVars.find(tok->varId()) != classVars.end()) {
            // constructor init list..
            if (match770(tok->previous())) {
                const Token *start = tok->previous();
                while (match479(start)) {
                    if (match40(start->previous()))
                        start = start->linkAt(-1);
                    else
                        break;
                    if (match24(start->previous()))
                        start = start->tokAt(-2);
                    else
                        break;
                }
                const Token *after = tok->linkAt(1);
                while (match771(after))
                    after = after->linkAt(3);

                // Do not simplify initlist
                if (match772(start) && match14(after))
                    continue;
            }

            tok->insertToken("operator()");
            tok->insertToken(".");
        }
    }
}

// remove unnecessary member qualification..
void Tokenizer::removeUnnecessaryQualification()
{
    if (isC())
        return;

    std::vector<Space> classInfo;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (match773(tok) &&
            (!tok->previous() || tok->strAt(-1) != MatchCompiler::makeConstString("enum"))) {
            Space info;
            info.isNamespace = tok->str() == MatchCompiler::makeConstString("namespace");
            tok = tok->next();
            info.className = tok->str();
            tok = tok->next();
            while (tok && tok->str() != MatchCompiler::makeConstString("{"))
                tok = tok->next();
            if (!tok)
                return;
            info.bodyEnd = tok->link();
            classInfo.push_back(std::move(info));
        } else if (!classInfo.empty()) {
            if (tok == classInfo.back().bodyEnd)
                classInfo.pop_back();
            else if (tok->str() == classInfo.back().className &&
                     !classInfo.back().isNamespace && tok->strAt(-1) != MatchCompiler::makeConstString(":") &&
                     (match774(tok) ||
                      match775(tok))) {
                const Token *tok1 = tok->tokAt(3);
                if (tok->strAt(2) == MatchCompiler::makeConstString("operator")) {
                    // check for operator ()
                    if (tok1->str() == MatchCompiler::makeConstString("("))
                        tok1 = tok1->next();

                    while (tok1 && tok1->str() != MatchCompiler::makeConstString("(")) {
                        if (tok1->str() == MatchCompiler::makeConstString(";"))
                            break;
                        tok1 = tok1->next();
                    }
                    if (!tok1 || tok1->str() != MatchCompiler::makeConstString("("))
                        continue;
                } else if (tok->strAt(2) == MatchCompiler::makeConstString("~"))
                    tok1 = tok1->next();

                if (!tok1 || !match776(tok1->link())) {
                    continue;
                }

                const bool isConstructorOrDestructor =
                    match777(tok) && (tok->strAt(2) == tok->str() || (tok->strAt(2) == MatchCompiler::makeConstString("~") && tok->strAt(3) == tok->str()));
                if (!isConstructorOrDestructor) {
                    bool isPrependedByType = match12(tok->previous());
                    if (!isPrependedByType) {
                        const Token* tok2 = tok->tokAt(-2);
                        isPrependedByType = match144(tok2);
                    }
                    if (!isPrependedByType) {
                        const Token* tok3 = tok->tokAt(-3);
                        isPrependedByType = match778(tok3);
                    }
                    if (!isPrependedByType) {
                        // It's not a constructor declaration and it's not a function declaration so
                        // this is a function call which can have all the qualifiers just fine - skip.
                        continue;
                    }
                }
            }
        }
    }
}

void Tokenizer::prepareTernaryOpForAST()
{
    // http://en.cppreference.com/w/cpp/language/operator_precedence says about ternary operator:
    //       "The expression in the middle of the conditional operator (between ? and :) is parsed as if parenthesized: its precedence relative to ?: is ignored."
    // The AST parser relies on this function to add such parentheses where necessary.
    for (Token* tok = list.front(); tok; tok = tok->next()) {
        if (tok->str() == MatchCompiler::makeConstString("?")) {
            bool parenthesesNeeded = false;
            int depth = 0;
            Token* tok2 = tok->next();
            for (; tok2; tok2 = tok2->next()) {
                if (tok2->link() && match779(tok2))
                    tok2 = tok2->link();
                else if (tok2->str() == MatchCompiler::makeConstString(":")) {
                    if (depth == 0)
                        break;
                    depth--;
                } else if (tok2->str() == MatchCompiler::makeConstString(";") || (tok2->link() && tok2->str() != MatchCompiler::makeConstString("{") && tok2->str() != MatchCompiler::makeConstString("}")))
                    break;
                else if (tok2->str() == MatchCompiler::makeConstString(","))
                    parenthesesNeeded = true;
                else if (tok2->str() == MatchCompiler::makeConstString("<"))
                    parenthesesNeeded = true;
                else if (tok2->str() == MatchCompiler::makeConstString("?")) {
                    depth++;
                    parenthesesNeeded = true;
                }
            }
            if (parenthesesNeeded && tok2 && tok2->str() == MatchCompiler::makeConstString(":")) {
                tok->insertToken("(");
                tok2->insertTokenBefore(")");
                Token::createMutualLinks(tok->next(), tok2->previous());
            }
        }
    }
}

void Tokenizer::reportError(const Token* tok, const Severity severity, const std::string& id, const std::string& msg, bool inconclusive) const
{
    const std::list<const Token*> callstack(1, tok);
    reportError(callstack, severity, id, msg, inconclusive);
}

void Tokenizer::reportError(const std::list<const Token*>& callstack, Severity severity, const std::string& id, const std::string& msg, bool inconclusive) const
{
    const ErrorMessage errmsg(callstack, &list, severity, id, msg, inconclusive ? Certainty::inconclusive : Certainty::normal);
    mErrorLogger.reportErr(errmsg);
}

void Tokenizer::setPodTypes()
{
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!tok->isName() || tok->varId())
            continue;

        // pod type
        const Library::PodType *podType = mSettings.library.podtype(tok->str());
        if (podType) {
            const Token *prev = tok->previous();
            while (prev && prev->isName())
                prev = prev->previous();
            if (prev && !match780(prev))
                continue;
            tok->isStandardType(true);
        }
    }
}

const Token *Tokenizer::findSQLBlockEnd(const Token *tokSQLStart)
{
    const Token *tokLastEnd = nullptr;
    for (const Token *tok = tokSQLStart->tokAt(2); tok != nullptr; tok = tok->next()) {
        if (tokLastEnd == nullptr && tok->str() == MatchCompiler::makeConstString(";"))
            tokLastEnd = tok;
        else if (tok->str() == MatchCompiler::makeConstString("__CPPCHECK_EMBEDDED_SQL_EXEC__")) {
            if (match781(tok->tokAt(-2)))
                return tok->next();
            return tokLastEnd;
        } else if (match782(tok))
            break; // We are obviously outside the SQL block
    }

    return tokLastEnd;
}

void Tokenizer::simplifyNestedNamespace()
{
    if (!isCPP())
        return;

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (match783(tok) && tok->strAt(-1) != MatchCompiler::makeConstString("using")) {
            Token * tok2 = tok->tokAt(2);

            // validate syntax
            while (match175(tok2))
                tok2 = tok2->tokAt(2);

            if (!tok2 || tok2->str() != MatchCompiler::makeConstString("{"))
                return; // syntax error

            std::stack<Token *> links;
            tok2 = tok->tokAt(2);

            while (tok2->str() == MatchCompiler::makeConstString("::")) {
                links.push(tok2);
                tok2->str("{");
                tok2->insertToken("namespace");
                tok2 = tok2->tokAt(3);
            }

            tok = tok2;

            if (!links.empty() && tok2->str() == MatchCompiler::makeConstString("{")) {
                tok2 = tok2->link();
                while (!links.empty()) {
                    tok2->insertToken("}");
                    tok2 = tok2->next();
                    Token::createMutualLinks(links.top(), tok2);
                    links.pop();
                }
            }
        }
    }
}

void Tokenizer::simplifyCoroutines()
{
    if (!isCPP() || mSettings.standards.cpp < Standards::CPP20)
        return;
    for (Token *tok = list.front(); tok; tok = tok->next()) {
        if (!tok->isName() || !match784(tok))
            continue;
        Token *end = tok->next();
        while (end && end->str() != MatchCompiler::makeConstString(";")) {
            if (match785(end))
                end = end->link();
            else if (match786(end))
                break;
            end = end->next();
        }
        if (match128(end)) {
            tok->insertToken("(");
            end->previous()->insertToken(")");
            Token::createMutualLinks(tok->next(), end->previous());
        }
    }
}

static bool sameTokens(const Token *first, const Token *last, const Token *other)
{
    while (other && first->str() == other->str()) {
        if (first == last)
            return true;
        first = first->next();
        other = other->next();
    }

    return false;
}

static bool alreadyHasNamespace(const Token *first, const Token *last, const Token *end)
{
    while (end && last->str() == end->str()) {
        if (first == last)
            return true;
        last = last->previous();
        end = end->previous();
    }

    return false;
}

static Token * deleteAlias(Token * tok)
{
    Token::eraseTokens(tok, findmatch787(tok) );

    // delete first token
    tok->deleteThis();

    // delete ';' if not last token
    tok->deleteThis();

    return tok;
}

void Tokenizer::simplifyNamespaceAliases()
{
    if (!isCPP())
        return;

    int scope = 0;

    for (Token *tok = list.front(); tok; tok = tok->next()) {
        bool isPrev{};
        if (tok->str() == MatchCompiler::makeConstString("{"))
            scope++;
        else if (tok->str() == MatchCompiler::makeConstString("}"))
            scope--;
        else if (match788(tok) || (isPrev = match788(tok->previous()))) {
            if (isPrev)
                tok = tok->previous();
            if (tok->tokAt(-1) && !match42(tok->tokAt(-1)))
                syntaxError(tok->tokAt(-1));
            const std::string name(tok->strAt(1));
            Token * tokNameStart = tok->tokAt(3);
            Token * tokNameEnd = tokNameStart;

            while (tokNameEnd && tokNameEnd->next() && tokNameEnd->strAt(1) != MatchCompiler::makeConstString(";")) {
                if (tokNameEnd->str() == MatchCompiler::makeConstString("(")) {
                    if (tokNameEnd->previous()->isName())
                        unknownMacroError(tokNameEnd->previous());
                    else
                        syntaxError(tokNameEnd);
                }
                tokNameEnd = tokNameEnd->next();
            }

            if (!tokNameEnd)
                return; // syntax error

            int endScope = scope;
            Token * tokLast = tokNameEnd->next();
            if (!tokLast)
                return;
            Token * tokNext = tokLast->next();
            Token * tok2 = tokNext;

            while (tok2 && endScope >= scope) {
                if (match1(tok2))
                    endScope++;
                else if (match41(tok2))
                    endScope--;
                else if (tok2->str() == name) {
                    if (match788(tok2->previous())) {
                        // check for possible duplicate aliases
                        if (sameTokens(tokNameStart, tokNameEnd, tok2->tokAt(2))) {
                            // delete duplicate
                            tok2 = deleteAlias(tok2->previous());
                            continue;
                        }
                        // conflicting declaration (syntax error)
                        // cppcheck-suppress duplicateBranch - remove when TODO below is addressed
                        if (endScope == scope) {
                            // delete conflicting declaration
                            tok2 = deleteAlias(tok2->previous());
                        }

                        // new declaration
                        else {
                            // TODO: use the new alias in this scope
                            tok2 = deleteAlias(tok2->previous());
                        }
                        continue;
                    }

                    if (tok2->strAt(1) == MatchCompiler::makeConstString("::") && !alreadyHasNamespace(tokNameStart, tokNameEnd, tok2)) {
                        if (match622(tok2->tokAt(-1)) && tokNameStart->str() == MatchCompiler::makeConstString("::"))
                            tok2->deletePrevious();
                        tok2->str(tokNameStart->str());
                        Token * tok3 = tokNameStart;
                        while (tok3 != tokNameEnd) {
                            tok2->insertToken(tok3->strAt(1));
                            tok2 = tok2->next();
                            tok3 = tok3->next();
                        }
                    }
                }
                tok2 = tok2->next();
            }

            if (tok->previous() && tokNext) {
                Token::eraseTokens(tok->previous(), tokNext);
                tok = tokNext->previous();
            } else if (tok->previous()) {
                Token::eraseTokens(tok->previous(), tokLast);
                tok = tokLast;
            } else if (tokNext) {
                Token::eraseTokens(tok, tokNext);
                tok->deleteThis();
            } else {
                Token::eraseTokens(tok, tokLast);
                tok->deleteThis();
            }
        }
    }
}

void Tokenizer::setDirectives(std::list<Directive> directives)
{
    mDirectives = std::move(directives);
}

bool Tokenizer::hasIfdef(const Token *start, const Token *end) const
{
    const auto& directives = mDirectives;
    return std::any_of(directives.cbegin(), directives.cend(), [&](const Directive& d) {
        return startsWith(d.str, "#if") &&
               d.linenr >= start->linenr() &&
               d.linenr <= end->linenr() &&
               start->fileIndex() < list.getFiles().size() &&
               d.file == list.getFiles()[start->fileIndex()];
    });
}

bool Tokenizer::isPacked(const Token * bodyStart) const
{
    const auto& directives = mDirectives;
    // TODO: should this return true if the #pragma exists in any line before the start token?
    return std::any_of(directives.cbegin(), directives.cend(), [&](const Directive& d) {
        return d.linenr < bodyStart->linenr() && d.str == MatchCompiler::makeConstString("#pragma pack(1)") && d.file == list.getFiles().front();
    });
}

void Tokenizer::getErrorMessages(ErrorLogger& errorLogger, const Settings& settings)
{
    TokenList tokenlist{settings, Standards::Language::C};
    Tokenizer tokenizer(std::move(tokenlist), errorLogger);
    tokenizer.invalidConstFunctionTypeError(nullptr);
    // checkLibraryNoReturn
    tokenizer.unhandled_macro_class_x_y(nullptr, "", "", "", "");
    tokenizer.macroWithSemicolonError(nullptr, "");
    tokenizer.unhandledCharLiteral(nullptr, "");
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
