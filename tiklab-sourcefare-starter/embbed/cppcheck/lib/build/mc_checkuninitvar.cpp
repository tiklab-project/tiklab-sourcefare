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
// pattern: .|::
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: ( %type% )
MAYBE_UNUSED static inline bool match2(const Token* tok) {
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
// pattern: %var% =|{
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: *|&|.
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    return true;
}
// pattern: %name% [
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: %type% %var% ;
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: [({:]
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("({:", tok->str()[0]))
        return false;
    return true;
}
// pattern: %name% =
MAYBE_UNUSED static inline bool match8(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: %name% ) (
MAYBE_UNUSED static inline bool match9(const Token* tok) {
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
// pattern: ) =
MAYBE_UNUSED static inline bool match10(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: ] [
MAYBE_UNUSED static inline bool match11(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] =|{|(
MAYBE_UNUSED static inline bool match12(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: std :: array
MAYBE_UNUSED static inline bool match13(const Token* tok) {
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
// pattern: for (
MAYBE_UNUSED static inline bool match14(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: {
MAYBE_UNUSED static inline bool match15(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %type% * %name% [,)]
MAYBE_UNUSED static inline bool match16(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: [;{}] %varid% =
MAYBE_UNUSED static inline bool match17(const Token* tok, const int varid) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: %name% ::
MAYBE_UNUSED static inline bool match18(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: [?:]
MAYBE_UNUSED static inline bool match19(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("?:", tok->str()[0]))
        return false;
    return true;
}
// pattern: *|[
MAYBE_UNUSED static inline bool match20(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: ,|;|{|}|]|try
MAYBE_UNUSED static inline bool match21(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")) || (tok->str() == MatchCompiler::makeConstString("try"))))
        return false;
    return true;
}
// pattern: [;{}.] %var% =
MAYBE_UNUSED static inline bool match22(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}.", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: [;{}] %var% = - %name% ;
MAYBE_UNUSED static inline bool match23(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: if (
MAYBE_UNUSED static inline bool match24(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ==|!=
MAYBE_UNUSED static inline bool match25(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("==")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("!="))))
        return false;
    return true;
}
// pattern: .
MAYBE_UNUSED static inline bool match26(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: } else {
MAYBE_UNUSED static inline bool match27(const Token* tok) {
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
// pattern: %name% {
MAYBE_UNUSED static inline bool match28(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: = {
MAYBE_UNUSED static inline bool match29(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %varid%
template<class T> MAYBE_UNUSED static inline T * findmatch30(T * start_tok, const Token * end, int varid) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: & %varid%
template<class T> MAYBE_UNUSED static inline T * findmatch31(T * start_tok, const Token * end, int varid) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        continue;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: %varid%
MAYBE_UNUSED static inline bool match32(const Token* tok, const int varid) {
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    return true;
}
// pattern: for|while (
MAYBE_UNUSED static inline bool match33(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: do {
MAYBE_UNUSED static inline bool match34(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } while (
MAYBE_UNUSED static inline bool match35(const Token* tok) {
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
// pattern: ) {
MAYBE_UNUSED static inline bool match36(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ( {
MAYBE_UNUSED static inline bool match37(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: asm|setjmp (
MAYBE_UNUSED static inline bool match38(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("asm")) || (tok->str() == MatchCompiler::makeConstString("setjmp"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: [;{}] %name% :
MAYBE_UNUSED static inline bool match39(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: %varid% . *
MAYBE_UNUSED static inline bool match40(const Token* tok, const int varid) {
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: return|break|continue|throw|goto
MAYBE_UNUSED static inline bool match41(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("break")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("continue")) || (tok->str() == MatchCompiler::makeConstString("throw")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("goto"))))
        return false;
    return true;
}
// pattern: %name% . %name%
MAYBE_UNUSED static inline bool match42(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %cop%|return|throw|?
MAYBE_UNUSED static inline bool match43(const Token* tok) {
    if (!tok || !(tok->isConstOp() || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("throw")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?"))))
        return false;
    return true;
}
// pattern: %name%
MAYBE_UNUSED static inline bool match44(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: return|throw|?
MAYBE_UNUSED static inline bool match45(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("throw")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?"))))
        return false;
    return true;
}
// pattern: =
MAYBE_UNUSED static inline bool match46(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: %name% (
MAYBE_UNUSED static inline bool match47(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: = new
MAYBE_UNUSED static inline bool match48(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    return true;
}
// pattern: = new %type% (
MAYBE_UNUSED static inline bool match49(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: = new %type% [
MAYBE_UNUSED static inline bool match50(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] (
MAYBE_UNUSED static inline bool match51(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: >>
MAYBE_UNUSED static inline bool match52(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>")))
        return false;
    return true;
}
// pattern: [(,] %name% [,)]
MAYBE_UNUSED static inline bool match53(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: = %var% . %var% ;
MAYBE_UNUSED static inline bool match54(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: %oror%|&&|?
MAYBE_UNUSED static inline bool match55(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?"))))
        return false;
    return true;
}
// pattern: ( ! %name% %oror%
MAYBE_UNUSED static inline bool match56(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")))
        return false;
    return true;
}
// pattern: asm ( %str% ) ;
MAYBE_UNUSED static inline bool match57(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("asm")))
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
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: ;
MAYBE_UNUSED static inline bool match58(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: (
MAYBE_UNUSED static inline bool match59(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: return
MAYBE_UNUSED static inline bool match60(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")))
        return false;
    return true;
}
// pattern: %var% =
MAYBE_UNUSED static inline bool match61(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: [(,&]
MAYBE_UNUSED static inline bool match62(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,&", tok->str()[0]))
        return false;
    return true;
}
// pattern: & )
MAYBE_UNUSED static inline bool match63(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ,|{
MAYBE_UNUSED static inline bool match64(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: %name% [.(]
MAYBE_UNUSED static inline bool match65(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(".(", tok->str()[0]))
        return false;
    return true;
}
// pattern: +|-|*|[|.
MAYBE_UNUSED static inline bool match66(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    return true;
}
// pattern: &
MAYBE_UNUSED static inline bool match67(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    return true;
}
// pattern: [+-]
MAYBE_UNUSED static inline bool match68(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("+-", tok->str()[0]))
        return false;
    return true;
}
// pattern: ( %name% ) &
MAYBE_UNUSED static inline bool match69(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    return true;
}
// pattern: %comp%|%oror%|&&|?|!
MAYBE_UNUSED static inline bool match70(const Token* tok) {
    if (!tok || !(tok->isComparisonOp() || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!"))))
        return false;
    return true;
}
// pattern: %or%|&
MAYBE_UNUSED static inline bool match71(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") ) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: [(,]
MAYBE_UNUSED static inline bool match72(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    return true;
}
// pattern: ,
MAYBE_UNUSED static inline bool match73(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: +
MAYBE_UNUSED static inline bool match74(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")))
        return false;
    return true;
}
// pattern: (|=
MAYBE_UNUSED static inline bool match75(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: :
MAYBE_UNUSED static inline bool match76(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: <<|>>
MAYBE_UNUSED static inline bool match77(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("<<")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>"))))
        return false;
    return true;
}
// pattern: [;{}(]
MAYBE_UNUSED static inline bool match78(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}(", tok->str()[0]))
        return false;
    return true;
}
// pattern: if|for|while|switch
MAYBE_UNUSED static inline bool match79(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("switch"))))
        return false;
    return true;
}
// pattern: %type% %name%| [,)]
MAYBE_UNUSED static inline bool match80(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (tok && (tok->isName()))
        tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: const %type% & %name% [,)]
MAYBE_UNUSED static inline bool match81(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: const %type% %name% [
MAYBE_UNUSED static inline bool match82(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: ] [,)]
MAYBE_UNUSED static inline bool match83(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: if|while|for
MAYBE_UNUSED static inline bool match84(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for"))))
        return false;
    return true;
}
// pattern: [=.[]
MAYBE_UNUSED static inline bool match85(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("=.[", tok->str()[0]))
        return false;
    return true;
}
// pattern: [(,=] &
MAYBE_UNUSED static inline bool match86(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,=", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    return true;
}
// pattern: [|=
MAYBE_UNUSED static inline bool match87(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("="))))
        return false;
    return true;
}
// pattern: [(,] %name% . %name% [,)]
MAYBE_UNUSED static inline bool match88(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: %var% . %name% (
MAYBE_UNUSED static inline bool match89(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
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
// pattern: [(,] & %name%
MAYBE_UNUSED static inline bool match90(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: const struct| %type% * const| %name% [,)]
MAYBE_UNUSED static inline bool match91(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("struct"))))
        tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
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
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: = * (
MAYBE_UNUSED static inline bool match92(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: = %name% ;
MAYBE_UNUSED static inline bool match93(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: *
MAYBE_UNUSED static inline bool match94(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: = * (| &
MAYBE_UNUSED static inline bool match95(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    return true;
}
// pattern: [(,] & %name% [,)]
MAYBE_UNUSED static inline bool match96(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: . %name%
MAYBE_UNUSED static inline bool match97(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: . %name% (|[
MAYBE_UNUSED static inline bool match98(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/checkuninitvar.cpp"
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
#include "checkuninitvar.h"

#include "astutils.h"
#include "ctu.h"
#include "errorlogger.h"
#include "library.h"
#include "mathlib.h"
#include "settings.h"
#include "symboldatabase.h"
#include "token.h"
#include "tokenize.h"
#include "tokenlist.h"
#include "utils.h"
#include "vfvalue.h"

#include "checknullpointer.h"   // CheckNullPointer::isPointerDeref

#include <algorithm>
#include <cassert>
#include <functional>
#include <initializer_list>
#include <list>
#include <map>
#include <unordered_set>
#include <utility>
#include <vector>

//---------------------------------------------------------------------------

// CWE ids used:
static const CWE CWE_USE_OF_UNINITIALIZED_VARIABLE(457U);

// Register this check class (by creating a static instance of it)
namespace {
    CheckUninitVar instance;
}

//---------------------------------------------------------------------------

// get ast parent, skip possible address-of and casts
static const Token *getAstParentSkipPossibleCastAndAddressOf(const Token *vartok, bool *unknown)
{
    if (unknown)
        *unknown = false;
    if (!vartok)
        return nullptr;
    const Token *parent = vartok->astParent();
    while (match1(parent))
        parent = parent->astParent();
    if (!parent)
        return nullptr;
    if (parent->isUnaryOp("&"))
        parent = parent->astParent();
    else if (parent->str() == MatchCompiler::makeConstString("&") && vartok == parent->astOperand2() && match2(parent->astOperand1()->previous())) {
        parent = parent->astParent();
        if (unknown)
            *unknown = true;
    }
    while (parent && parent->isCast())
        parent = parent->astParent();
    return parent;
}

static std::map<nonneg int, VariableValue> getVariableValues(const Token* tok) {
    std::map<nonneg int, VariableValue> ret;
    if (!tok || !tok->scope()->isExecutable())
        return ret;
    while (tok && tok->str() != MatchCompiler::makeConstString("{")) {
        if (tok->str() == MatchCompiler::makeConstString("}")) {
            if (tok->link()->isBinaryOp())
                tok = tok->link()->previous();
            else
                break;
        }
        if (match3(tok) && tok->next()->isBinaryOp() && tok->varId() && ret.count(tok->varId()) == 0) {
            const Token* rhs = tok->next()->astOperand2();
            if (rhs && rhs->hasKnownIntValue())
                ret[tok->varId()] = VariableValue(rhs->getKnownIntValue());
        }
        tok = tok->previous();
    }
    return ret;
}

bool CheckUninitVar::diag(const Token* tok)
{
    if (!tok)
        return true;
    while (match4(tok->astParent()))
        tok = tok->astParent();
    return !mUninitDiags.insert(tok).second;
}

void CheckUninitVar::check()
{
    logChecker("CheckUninitVar::check");

    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();

    std::set<std::string> arrayTypeDefs;
    for (const Token *tok = mTokenizer->tokens(); tok; tok = tok->next()) {
        if (match5(tok) && tok->variable() && match6(tok->variable()->typeStartToken()))
            arrayTypeDefs.insert(tok->variable()->typeStartToken()->str());
    }

    // check every executable scope
    for (const Scope &scope : symbolDatabase->scopeList) {
        if (scope.isExecutable()) {
            checkScope(&scope, arrayTypeDefs);
        }
    }
}

void CheckUninitVar::checkScope(const Scope* scope, const std::set<std::string> &arrayTypeDefs)
{
    for (const Variable &var : scope->varlist) {
        if ((mTokenizer->isCPP() && var.type() && !var.isPointer() && var.type()->needInitialization != Type::NeedInitialization::True) ||
            var.isStatic() || var.isExtern() || var.isReference())
            continue;

        // don't warn for try/catch exception variable
        if (var.isThrow())
            continue;

        if (match7(var.nameToken()->next()))
            continue;

        if (match8(var.nameToken())) { // Variable is initialized, but Rhs might be not
            checkRhs(var.nameToken(), var, NO_ALLOC, 0U, emptyString);
            continue;
        }
        if (match9(var.nameToken()) && match10(var.nameToken()->linkAt(2))) { // Function pointer is initialized, but Rhs might be not
            checkRhs(var.nameToken()->linkAt(2)->next(), var, NO_ALLOC, 0U, emptyString);
            continue;
        }

        if (var.isArray() || var.isPointerToArray()) {
            const Token *tok = var.nameToken()->next();
            if (var.isPointerToArray())
                tok = tok->next();
            while (match11(tok->link()))
                tok = tok->link()->next();
            if (match12(tok->link()))
                continue;
        }

        bool stdtype = var.typeStartToken()->isC() && arrayTypeDefs.find(var.typeStartToken()->str()) == arrayTypeDefs.end();
        const Token* tok = var.typeStartToken();
        for (; tok != var.nameToken() && tok->str() != MatchCompiler::makeConstString("<"); tok = tok->next()) {
            if (tok->isStandardType() || tok->isEnumType())
                stdtype = true;
        }
        if (var.isArray() && !stdtype) { // std::array
            if (!(var.isStlType() && match13(var.typeStartToken()) && var.valueType() &&
                  var.valueType()->containerTypeToken && var.valueType()->containerTypeToken->isStandardType()))
                continue;
        }

        while (tok && tok->str() != MatchCompiler::makeConstString(";"))
            tok = tok->next();
        if (!tok)
            continue;

        if (tok->astParent() && match14(tok->astParent()->previous()) && match15(tok->astParent()->link()->next()) &&
            checkLoopBody(tok->astParent()->link()->next(), var, var.isArray() ? ARRAY : NO_ALLOC, emptyString, true))
            continue;

        if (var.isArray()) {
            bool init = false;
            for (const Token *parent = var.nameToken(); parent; parent = parent->astParent()) {
                if (parent->str() == MatchCompiler::makeConstString("=")) {
                    init = true;
                    break;
                }
            }
            if (!init) {
                Alloc alloc = ARRAY;
                std::map<nonneg int, VariableValue> variableValue = getVariableValues(var.typeStartToken());
                checkScopeForVariable(tok, var, nullptr, nullptr, &alloc, emptyString, variableValue);
            }
            continue;
        }
        if (stdtype || var.isPointer()) {
            Alloc alloc = NO_ALLOC;
            std::map<nonneg int, VariableValue> variableValue = getVariableValues(var.typeStartToken());
            checkScopeForVariable(tok, var, nullptr, nullptr, &alloc, emptyString, variableValue);
        }
        if (var.type())
            checkStruct(tok, var);
    }

    if (scope->function) {
        for (const Variable &arg : scope->function->argumentList) {
            if (arg.declarationId() && match16(arg.typeStartToken())) {
                // Treat the pointer as initialized until it is assigned by malloc
                for (const Token *tok = scope->bodyStart; tok != scope->bodyEnd; tok = tok->next()) {
                    if (!match17(tok, arg.declarationId()))
                        continue;
                    const Token *allocFuncCallToken = findAllocFuncCallToken(tok->tokAt(2)->astOperand2(), mSettings->library);
                    if (!allocFuncCallToken)
                        continue;
                    const Library::AllocFunc *allocFunc = mSettings->library.getAllocFuncInfo(allocFuncCallToken);
                    if (!allocFunc || allocFunc->initData)
                        continue;

                    if (arg.typeStartToken()->strAt(-1) == MatchCompiler::makeConstString("struct") || (arg.type() && arg.type()->isStructType()))
                        checkStruct(tok, arg);
                    else if (arg.typeStartToken()->isStandardType() || arg.typeStartToken()->isEnumType()) {
                        Alloc alloc = NO_ALLOC;
                        std::map<nonneg int, VariableValue> variableValue;
                        checkScopeForVariable(tok->next(), arg, nullptr, nullptr, &alloc, emptyString, variableValue);
                    }
                }
            }
        }
    }
}

void CheckUninitVar::checkStruct(const Token *tok, const Variable &structvar)
{
    const Token *typeToken = structvar.typeStartToken();
    while (match18(typeToken))
        typeToken = typeToken->tokAt(2);
    const SymbolDatabase * symbolDatabase = mTokenizer->getSymbolDatabase();
    for (const Scope *scope2 : symbolDatabase->classAndStructScopes) {
        if (scope2->className == typeToken->str() && scope2->numConstructors == 0U) {
            for (const Variable &var : scope2->varlist) {
                if (var.isStatic() || var.hasDefault() || var.isArray() ||
                    (!mTokenizer->isC() && var.isClass() && (!var.type() || var.type()->needInitialization != Type::NeedInitialization::True)))
                    continue;

                // is the variable declared in a inner union?
                bool innerunion = false;
                for (const Scope *innerScope : scope2->nestedList) {
                    if (innerScope->type == ScopeType::eUnion) {
                        if (var.typeStartToken()->linenr() >= innerScope->bodyStart->linenr() &&
                            var.typeStartToken()->linenr() <= innerScope->bodyEnd->linenr()) {
                            innerunion = true;
                            break;
                        }
                    }
                }

                if (!innerunion) {
                    Alloc alloc = NO_ALLOC;
                    const Token *tok2 = tok;
                    if (tok->str() == MatchCompiler::makeConstString("}"))
                        tok2 = tok2->next();
                    std::map<nonneg int, VariableValue> variableValue = getVariableValues(structvar.typeStartToken());
                    checkScopeForVariable(tok2, structvar, nullptr, nullptr, &alloc, var.name(), variableValue);
                }
            }
        }
    }
}

static VariableValue operator!(VariableValue v)
{
    v.notEqual = !v.notEqual;
    return v;
}
static bool operator==(const VariableValue & v, MathLib::bigint i)
{
    return v.notEqual ? (i != v.value) : (i == v.value);
}
static bool operator!=(const VariableValue & v, MathLib::bigint i)
{
    return v.notEqual ? (i == v.value) : (i != v.value);
}

static void conditionAlwaysTrueOrFalse(const Token *tok, const std::map<nonneg int, VariableValue> &variableValue, bool *alwaysTrue, bool *alwaysFalse)
{
    if (!tok)
        return;

    if (const ValueFlow::Value* v = tok->getKnownValue(ValueFlow::Value::ValueType::INT)) {
        if (v->intvalue == 0)
            *alwaysFalse = true;
        else
            *alwaysTrue = true;
        return;
    }

    if (tok->isName() || tok->str() == MatchCompiler::makeConstString(".")) {
        while (tok && tok->str() == MatchCompiler::makeConstString("."))
            tok = tok->astOperand2();
        const auto it = utils::as_const(variableValue).find(tok ? tok->varId() : ~0U);
        if (it != variableValue.end()) {
            *alwaysTrue = (it->second != 0LL);
            *alwaysFalse = (it->second == 0LL);
        }
    }

    else if (tok->isComparisonOp()) {
        if (variableValue.empty()) {
            return;
        }

        const Token *vartok, *numtok;
        if (tok->astOperand2() && tok->astOperand2()->isNumber()) {
            vartok = tok->astOperand1();
            numtok = tok->astOperand2();
        } else if (tok->astOperand1() && tok->astOperand1()->isNumber()) {
            vartok = tok->astOperand2();
            numtok = tok->astOperand1();
        } else {
            return;
        }

        while (vartok && vartok->str() == MatchCompiler::makeConstString("."))
            vartok = vartok->astOperand2();

        const auto it = utils::as_const(variableValue).find(vartok ? vartok->varId() : ~0U);
        if (it == variableValue.end())
            return;

        if (tok->str() == MatchCompiler::makeConstString("=="))
            *alwaysTrue  = (it->second == MathLib::toBigNumber(numtok));
        else if (tok->str() == MatchCompiler::makeConstString("!="))
            *alwaysTrue  = (it->second != MathLib::toBigNumber(numtok));
        else
            return;
        *alwaysFalse = !(*alwaysTrue);
    }

    else if (tok->str() == MatchCompiler::makeConstString("!")) {
        bool t=false,f=false;
        conditionAlwaysTrueOrFalse(tok->astOperand1(), variableValue, &t, &f);
        if (t || f) {
            *alwaysTrue = !t;
            *alwaysFalse = !f;
        }
    }

    else if (tok->str() == MatchCompiler::makeConstString("||")) {
        bool t1=false, f1=false;
        conditionAlwaysTrueOrFalse(tok->astOperand1(), variableValue, &t1, &f1);
        bool t2=false, f2=false;
        if (!t1)
            conditionAlwaysTrueOrFalse(tok->astOperand2(), variableValue, &t2, &f2);
        *alwaysTrue = (t1 || t2);
        *alwaysFalse = (f1 && f2);
    }

    else if (tok->str() == MatchCompiler::makeConstString("&&")) {
        bool t1=false, f1=false;
        conditionAlwaysTrueOrFalse(tok->astOperand1(), variableValue, &t1, &f1);
        bool t2=false, f2=false;
        if (!f1)
            conditionAlwaysTrueOrFalse(tok->astOperand2(), variableValue, &t2, &f2);
        *alwaysTrue = (t1 && t2);
        *alwaysFalse = (f1 || f2);
    }
}

static bool isVariableUsed(const Token *tok, const Variable& var)
{
    if (!tok)
        return false;
    if (tok->str() == MatchCompiler::makeConstString("&") && !tok->astOperand2())
        return false;
    if (tok->isConstOp())
        return isVariableUsed(tok->astOperand1(),var) || isVariableUsed(tok->astOperand2(),var);
    if (tok->varId() != var.declarationId())
        return false;
    if (!var.isArray())
        return true;

    const Token *parent = tok->astParent();
    while (match19(parent))
        parent = parent->astParent();
    // no dereference, then array is not "used"
    if (!match20(parent))
        return false;
    const Token *parent2 = parent->astParent();
    // TODO: handle function calls. There is a TODO assertion in TestUninitVar::uninitvar_arrays
    return !parent2 || parent2->isConstOp() || (parent2->str() == MatchCompiler::makeConstString("=") && parent2->astOperand2() == parent);
}

bool CheckUninitVar::checkScopeForVariable(const Token *tok, const Variable& var, bool * const possibleInit, bool * const noreturn, Alloc* const alloc, const std::string &membervar, std::map<nonneg int, VariableValue>& variableValue)
{
    const bool suppressErrors(possibleInit && *possibleInit);  // Assume that this is a variable declaration, rather than a fundef
    const bool printDebug = mSettings->debugwarnings;

    if (possibleInit)
        *possibleInit = false;

    int number_of_if = 0;

    if (var.declarationId() == 0U)
        return true;

    for (; tok; tok = tok->next()) {
        // End of scope..
        if (tok->str() == MatchCompiler::makeConstString("}")) {
            if (number_of_if && possibleInit)
                *possibleInit = true;

            // might be a noreturn function..
            if (mTokenizer->isScopeNoReturn(tok)) {
                if (noreturn)
                    *noreturn = true;
                return false;
            }

            break;
        }

        // Unconditional inner scope, try, lambda, init list
        if (tok->str() == MatchCompiler::makeConstString("{") && match21(tok->previous())) {
            bool possibleInitInner = false;
            if (checkScopeForVariable(tok->next(), var, &possibleInitInner, noreturn, alloc, membervar, variableValue))
                return true;
            tok = tok->link();
            if (possibleInitInner) {
                number_of_if = 1;
                if (possibleInit)
                    *possibleInit = true;
            }
            continue;
        }

        // track values of other variables..
        if (match22(tok->previous())) {
            if (tok->next()->astOperand2() && tok->next()->astOperand2()->hasKnownIntValue())
                variableValue[tok->varId()] = VariableValue(tok->next()->astOperand2()->getKnownIntValue());
            else if (match23(tok->previous()))
                variableValue[tok->varId()] = !VariableValue(0);
            else
                variableValue.erase(tok->varId());
        }

        // Inner scope..
        else if (match24(tok)) {
            bool alwaysTrue = false;
            bool alwaysFalse = false;

            // Is variable assigned in condition?
            if (!membervar.empty()) {
                for (const Token *cond = tok->linkAt(1); cond != tok; cond = cond->previous()) {
                    if (cond->varId() == var.declarationId() && isMemberVariableAssignment(cond, membervar))
                        return true;
                }
            }

            conditionAlwaysTrueOrFalse(tok->next()->astOperand2(), variableValue, &alwaysTrue, &alwaysFalse);

            // initialization / usage in condition..
            if (!alwaysTrue && checkIfForWhileHead(tok->next(), var, suppressErrors, (number_of_if == 0), *alloc, membervar))
                return true;

            // checking if a not-zero variable is zero => bail out
            nonneg int condVarId = 0;
            VariableValue condVarValue(0);
            const Token *condVarTok = nullptr;
            if (alwaysFalse)
                ;
            else if (astIsVariableComparison(tok->next()->astOperand2(), "!=", "0", &condVarTok)) {
                const auto it = utils::as_const(variableValue).find(condVarTok->varId());
                if (it != variableValue.cend() && it->second != 0)
                    return true;   // this scope is not fully analysed => return true

                condVarId = condVarTok->varId();
                condVarValue = !VariableValue(0);
            } else if (match25(tok->next()->astOperand2())) {
                const Token *condition = tok->next()->astOperand2();
                const Token *lhs = condition->astOperand1();
                const Token *rhs = condition->astOperand2();
                const Token *vartok = (lhs && lhs->hasKnownIntValue()) ? rhs : lhs;
                const Token *numtok = (lhs == vartok) ? rhs : lhs;
                while (match26(vartok))
                    vartok = vartok->astOperand2();
                if (vartok && vartok->varId() && numtok && numtok->hasKnownIntValue()) {
                    const auto it = utils::as_const(variableValue).find(vartok->varId());
                    if (it != variableValue.cend() && it->second != numtok->getKnownIntValue())
                        return true;   // this scope is not fully analysed => return true
                    condVarId = vartok->varId();
                    condVarValue = VariableValue(numtok->getKnownIntValue());
                    if (condition->str() == MatchCompiler::makeConstString("!="))
                        condVarValue = !condVarValue;
                }
            }

            // goto the {
            tok = tok->linkAt(1)->next();

            if (!tok)
                break;
            if (tok->str() == MatchCompiler::makeConstString("{")) {
                bool possibleInitIf((!alwaysTrue && number_of_if > 0) || suppressErrors);
                bool noreturnIf = false;
                std::map<nonneg int, VariableValue> varValueIf(variableValue);
                const bool initif = !alwaysFalse && checkScopeForVariable(tok->next(), var, &possibleInitIf, &noreturnIf, alloc, membervar, varValueIf);

                // bail out for such code:
                //    if (a) x=0;    // conditional initialization
                //    if (b) return; // cppcheck doesn't know if b can be false when a is false.
                //    x++;           // it's possible x is always initialized
                if (!alwaysTrue && noreturnIf && number_of_if > 0) {
                    if (printDebug) {
                        std::string condition;
                        for (const Token *tok2 = tok->linkAt(-1); tok2 != tok; tok2 = tok2->next()) {
                            condition += tok2->str();
                            if (tok2->isName() && tok2->next()->isName())
                                condition += ' ';
                        }
                        reportError(tok, Severity::debug, "bailoutUninitVar", "bailout uninitialized variable checking for '" + var.name() + "'. can't determine if this condition can be false when previous condition is false: " + condition);
                    }
                    return true;
                }

                if (alwaysTrue && (initif || noreturnIf))
                    return true;

                if (!alwaysFalse && !initif && !noreturnIf)
                    variableValue = varValueIf;

                if (initif && condVarId > 0)
                    variableValue[condVarId] = !condVarValue;

                // goto the }
                tok = tok->link();

                if (!match27(tok)) {
                    if (initif || possibleInitIf) {
                        ++number_of_if;
                        if (number_of_if >= 2)
                            return true;
                    }
                } else {
                    // goto the {
                    tok = tok->tokAt(2);

                    bool possibleInitElse((!alwaysFalse && number_of_if > 0) || suppressErrors);
                    bool noreturnElse = false;
                    std::map<nonneg int, VariableValue> varValueElse(variableValue);
                    const bool initelse = !alwaysTrue && checkScopeForVariable(tok->next(), var, &possibleInitElse, &noreturnElse, alloc, membervar, varValueElse);

                    if (!alwaysTrue && !initelse && !noreturnElse)
                        variableValue = varValueElse;

                    if (initelse && condVarId > 0 && !noreturnIf && !noreturnElse)
                        variableValue[condVarId] = condVarValue;

                    // goto the }
                    tok = tok->link();

                    if ((alwaysFalse || initif || noreturnIf) &&
                        (alwaysTrue || initelse || noreturnElse))
                        return true;

                    if (initif || initelse || possibleInitElse)
                        ++number_of_if;
                    if (!initif && !noreturnIf)
                        variableValue.insert(varValueIf.cbegin(), varValueIf.cend());
                    if (!initelse && !noreturnElse)
                        variableValue.insert(varValueElse.cbegin(), varValueElse.cend());
                }
            }
        }

        // = { .. }
        else if (match29(tok) || (match28(tok) && tok->variable() && tok == tok->variable()->nameToken())) {
            // end token
            const Token *end = tok->linkAt(1);

            // If address of variable is taken in the block then bail out
            if (var.isPointer() || var.isArray()) {
                if (findmatch30(tok->tokAt(2), end, var.declarationId()) )
                    return true;
            } else if (findmatch31(tok->tokAt(2), end, var.declarationId()) ) {
                return true;
            }

            const Token *errorToken = nullptr;
            visitAstNodes(tok->next(),
                          [&](const Token *child) {
                if (child->isUnaryOp("&"))
                    return ChildrenToVisit::none;
                if (child->str() == MatchCompiler::makeConstString(",") || child->str() == MatchCompiler::makeConstString("{") || child->isConstOp())
                    return ChildrenToVisit::op1_and_op2;
                if (child->str() == MatchCompiler::makeConstString(".") && match32(child->astOperand1(), var.declarationId()) && child->astOperand2() && child->astOperand2()->str() == membervar) {
                    errorToken = child;
                    return ChildrenToVisit::done;
                }
                return ChildrenToVisit::none;
            });

            if (errorToken) {
                uninitStructMemberError(errorToken->astOperand2(), errorToken->astOperand1()->str() + "." + membervar);
                return true;
            }

            // Skip block
            tok = end;
            continue;
        }

        // skip sizeof / offsetof
        if (isUnevaluated(tok))
            tok = tok->linkAt(1);

        // for/while..
        else if (match33(tok) || match34(tok)) {
            const bool forwhile = match33(tok);

            // is variable initialized in for-head?
            if (forwhile && checkIfForWhileHead(tok->next(), var, tok->str() == MatchCompiler::makeConstString("for"), false, *alloc, membervar))
                return true;

            // goto the {
            const Token *tok2 = forwhile ? tok->linkAt(1)->next() : tok->next();

            if (tok2 && tok2->str() == MatchCompiler::makeConstString("{")) {
                const bool init = checkLoopBody(tok2, var, *alloc, membervar, (number_of_if > 0) || suppressErrors);

                // variable is initialized in the loop..
                if (init)
                    return true;

                // is variable used in for-head?
                bool initcond = false;
                if (!suppressErrors) {
                    const Token *startCond = forwhile ? tok->next() : tok->linkAt(1)->tokAt(2);
                    initcond = checkIfForWhileHead(startCond, var, false, (number_of_if == 0), *alloc, membervar);
                }

                // goto "}"
                tok = tok2->link();

                // do-while => goto ")"
                if (!forwhile) {
                    // Assert that the tokens are '} while ('
                    if (!match35(tok)) {
                        if (printDebug)
                            reportError(tok,Severity::debug,"","assertion failed '} while ('");
                        break;
                    }

                    // Goto ')'
                    tok = tok->linkAt(2);

                    if (!tok)
                        // bailout : invalid code / bad tokenizer
                        break;

                    if (initcond)
                        // variable is initialized in while-condition
                        return true;
                }
            }
        }

        // Unknown or unhandled inner scope
        else if (match36(tok) || (match28(tok) && tok->str() != MatchCompiler::makeConstString("try") && !(tok->variable() && tok == tok->variable()->nameToken()))) {
            if (tok->str() == MatchCompiler::makeConstString("struct") || tok->str() == MatchCompiler::makeConstString("union")) {
                tok = tok->linkAt(1);
                continue;
            }
            return true;
        }

        // bailout if there is ({
        if (match37(tok)) {
            return true;
        }

        // bailout if there is assembler code or setjmp
        if (match38(tok)) {
            return true;
        }

        // bailout if there is a goto label
        if (match39(tok)) {
            return true;
        }

        // bailout if there is a pointer to member
        if (match40(tok, var.declarationId())) {
            return true;
        }

        if (tok->str() == MatchCompiler::makeConstString("?")) {
            if (!tok->astOperand2())
                return true;
            const bool used1 = isVariableUsed(tok->astOperand2()->astOperand1(), var);
            const bool used0 = isVariableUsed(tok->astOperand2()->astOperand2(), var);
            const bool err = (number_of_if == 0) ? (used1 || used0) : (used1 && used0);
            if (err)
                uninitvarError(tok, var.nameToken()->str(), *alloc);

            // Todo: skip expression if there is no error
            return true;
        }

        if (match41(tok)) {
            if (noreturn)
                *noreturn = true;

            tok = tok->next();
            while (tok && tok->str() != MatchCompiler::makeConstString(";")) {
                // variable is seen..
                if (tok->varId() == var.declarationId()) {
                    if (!membervar.empty()) {
                        if (!suppressErrors && match42(tok) && tok->strAt(2) == membervar && match43(tok->next()->astParent()))
                            uninitStructMemberError(tok, tok->str() + "." + membervar);
                        else if (tok->isCpp() && !suppressErrors && match44(tok) && match45(tok->astParent())) {
                            if (std::any_of(tok->values().cbegin(), tok->values().cend(), [](const ValueFlow::Value& v) {
                                return v.isUninitValue() && !v.isInconclusive();
                            }))
                                uninitStructMemberError(tok, tok->str() + "." + membervar);
                        }
                    }

                    // Use variable
                    else if (!suppressErrors && isVariableUsage(tok, var.isPointer(), *alloc))
                        uninitvarError(tok, tok->str(), *alloc);

                    return true;
                }

                if (isUnevaluated(tok))
                    tok = tok->linkAt(1);

                else if (tok->str() == MatchCompiler::makeConstString("?")) {
                    if (!tok->astOperand2())
                        return true;
                    const bool used1 = isVariableUsed(tok->astOperand2()->astOperand1(), var);
                    const bool used0 = isVariableUsed(tok->astOperand2()->astOperand2(), var);
                    const bool err = (number_of_if == 0) ? (used1 || used0) : (used1 && used0);
                    if (err)
                        uninitvarError(tok, var.nameToken()->str(), *alloc);
                    return true;
                }

                tok = tok->next();
            }

            return (noreturn == nullptr);
        }

        // variable is seen..
        if (tok->varId() == var.declarationId()) {
            // calling function that returns uninit data through pointer..
            if (var.isPointer() && match46(tok->next())) {
                const Token *rhs = tok->next()->astOperand2();
                while (rhs && rhs->isCast())
                    rhs = rhs->astOperand2() ? rhs->astOperand2() : rhs->astOperand1();
                if (rhs && match47(rhs->previous())) {
                    const Library::AllocFunc *allocFunc = mSettings->library.getAllocFuncInfo(rhs->astOperand1());
                    if (allocFunc && !allocFunc->initData) {
                        *alloc = NO_CTOR_CALL;
                        continue;
                    }
                }
            }
            if (mTokenizer->isCPP() && var.isPointer() && (var.typeStartToken()->isStandardType() || var.typeStartToken()->isEnumType() || (var.type() && var.type()->needInitialization == Type::NeedInitialization::True)) && match48(tok->next())) {
                *alloc = CTOR_CALL;

                // type has constructor(s)
                if (var.typeScope() && var.typeScope()->numConstructors > 0)
                    return true;

                // standard or enum type: check if new initializes the allocated memory
                if (var.typeStartToken()->isStandardType() || var.typeStartToken()->isEnumType()) {
                    // scalar new with initialization
                    if (match49(tok->next()))
                        return true;

                    // array new
                    if (match50(tok->next()) && match51(tok->linkAt(4)))
                        return true;
                }

                continue;
            }


            if (!membervar.empty()) {
                if (mTokenizer->isCPP() && match52(tok->astParent()))
                    return true;

                if (isMemberVariableAssignment(tok, membervar)) {
                    checkRhs(tok, var, *alloc, number_of_if, membervar);
                    return true;
                }

                if (isMemberVariableUsage(tok, var.isPointer(), *alloc, membervar)) {
                    uninitStructMemberError(tok, tok->str() + "." + membervar);
                    return true;
                }

                if (match53(tok->previous()))
                    return true;

                if (match54(tok->previous()) && membervar == tok->strAt(2))
                    return true;

            } else {
                // Use variable
                if (!suppressErrors && isVariableUsage(tok, var.isPointer(), *alloc)) {
                    uninitvarError(tok, tok->str(), *alloc);
                    return true;
                }

                const Token *parent = tok;
                while (parent->astParent() && ((astIsLHS(parent) && parent->astParent()->str() == MatchCompiler::makeConstString("[")) || parent->astParent()->isUnaryOp("*"))) {
                    parent = parent->astParent();
                    if (parent->str() == MatchCompiler::makeConstString("[")) {
                        if (const Token *errorToken = checkExpr(parent->astOperand2(), var, *alloc, number_of_if==0)) {
                            if (!suppressErrors)
                                uninitvarError(errorToken, errorToken->expressionString(), *alloc);
                            return true;
                        }
                    }
                }
                if (match46(parent->astParent()) && astIsLHS(parent)) {
                    const Token *eq = parent->astParent();
                    if (const Token *errorToken = checkExpr(eq->astOperand2(), var, *alloc, number_of_if==0)) {
                        if (!suppressErrors)
                            uninitvarError(errorToken, errorToken->expressionString(), *alloc);
                        return true;
                    }
                }

                // assume that variable is assigned
                return true;
            }
        }
    }

    return false;
}

const Token* CheckUninitVar::checkExpr(const Token* tok, const Variable& var, const Alloc alloc, bool known, bool* bailout) const
{
    if (!tok)
        return nullptr;
    if (isUnevaluated(tok->previous()))
        return nullptr;

    if (tok->astOperand1()) {
        bool bailout1 = false;
        const Token *errorToken = checkExpr(tok->astOperand1(), var, alloc, known, &bailout1);
        if (bailout && bailout1)
            *bailout = true;
        if (errorToken)
            return errorToken;
        if ((bailout1 || !known) && match55(tok))
            return nullptr;
    }
    if (tok->astOperand2())
        return checkExpr(tok->astOperand2(), var, alloc, known, bailout);
    if (tok->varId() == var.declarationId()) {
        const Token *errorToken = isVariableUsage(tok, var.isPointer(), alloc);
        if (errorToken)
            return errorToken;
        if (bailout)
            *bailout = true;
    }
    return nullptr;
}

bool CheckUninitVar::checkIfForWhileHead(const Token *startparentheses, const Variable& var, bool suppressErrors, bool isuninit, Alloc alloc, const std::string &membervar)
{
    const Token * const endpar = startparentheses->link();
    if (match56(startparentheses) && startparentheses->tokAt(2)->getValue(0))
        suppressErrors = true;
    for (const Token *tok = startparentheses->next(); tok && tok != endpar; tok = tok->next()) {
        if (tok->varId() == var.declarationId()) {
            if (match42(tok)) {
                if (membervar.empty())
                    return true;
                if (tok->strAt(2) == membervar) {
                    if (isMemberVariableAssignment(tok, membervar))
                        return true;

                    if (!suppressErrors && isMemberVariableUsage(tok, var.isPointer(), alloc, membervar))
                        uninitStructMemberError(tok, tok->str() + "." + membervar);
                }
                continue;
            }

            if (const Token *errorToken = isVariableUsage(tok, var.isPointer(), alloc)) {
                if (suppressErrors)
                    continue;
                uninitvarError(errorToken, errorToken->expressionString(), alloc);
            }
            return true;
        }
        // skip sizeof / offsetof
        if (isUnevaluated(tok))
            tok = tok->linkAt(1);
        if ((!isuninit || !membervar.empty()) && tok->str() == MatchCompiler::makeConstString("&&"))
            suppressErrors = true;
    }
    return false;
}

/** recursively check loop, return error token */
const Token* CheckUninitVar::checkLoopBodyRecursive(const Token *start, const Variable& var, const Alloc alloc, const std::string &membervar, bool &bailout, bool &alwaysReturns) const
{
    assert(start->str() == MatchCompiler::makeConstString("{"));

    const Token *errorToken = nullptr;

    const Token *const end = start->link();
    for (const Token *tok = start->next(); tok != end; tok = tok->next()) {
        // skip sizeof / offsetof
        if (isUnevaluated(tok)) {
            tok = tok->linkAt(1);
            continue;
        }

        if (match57(tok)) {
            bailout = true;
            return nullptr;
        }

        // for loop; skip third expression until loop body has been analyzed..
        if (tok->str() == MatchCompiler::makeConstString(";") && match58(tok->astParent()) && match59(tok->astParent()->astParent())) {
            const Token *top = tok->astParent()->astParent();
            if (!match14(top->previous()) || !match36(top->link()))
                continue;
            const Token *bodyStart = top->link()->next();
            const Token *errorToken1 = checkLoopBodyRecursive(bodyStart, var, alloc, membervar, bailout, alwaysReturns);
            if (!errorToken)
                errorToken = errorToken1;
            bailout |= alwaysReturns;
            if (bailout)
                return nullptr;
        }
        // for loop; skip loop body if there is third expression
        if (match36(tok) &&
            match14(tok->link()->previous()) &&
            match58(tok->link()->astOperand2()) &&
            match58(tok->link()->astOperand2()->astOperand2())) {
            tok = tok->linkAt(1);
        }

        if (tok->str() == MatchCompiler::makeConstString("{")) {
            // switch => bailout
            if (tok->scope() && tok->scope()->type == ScopeType::eSwitch) {
                bailout = true;
                return nullptr;
            }

            bool alwaysReturnsUnused;
            const Token *errorToken1 = checkLoopBodyRecursive(tok, var, alloc, membervar, bailout, alwaysReturnsUnused);
            tok = tok->link();
            if (match27(tok)) {
                const Token *elseBody = tok->tokAt(2);
                const Token *errorToken2 = checkLoopBodyRecursive(elseBody, var, alloc, membervar, bailout, alwaysReturnsUnused);
                tok = elseBody->link();
                if (errorToken1 && errorToken2)
                    return errorToken1;
                if (errorToken2)
                    errorToken = errorToken2;
            }
            if (bailout)
                return nullptr;
            if (!errorToken)
                errorToken = errorToken1;
        }

        if (match60(tok)) {
            bool returnWithoutVar = true;
            while (tok && !match58(tok)) {
                if (tok->isVariable() && tok->variable() == &var) {
                    returnWithoutVar = false;
                    break;
                }
                tok = tok->next();
            }
            if (returnWithoutVar) {
                alwaysReturns = true;
                return nullptr;
            }
        }
        if (!tok)
            break;

        if (tok->varId() != var.declarationId())
            continue;

        bool conditionalUsage = false;
        for (const Token* parent = tok; parent; parent = parent->astParent()) {
            if (match55(parent->astParent()) && astIsRHS(parent)) {
                conditionalUsage = true;
                break;
            }
        }

        if (!membervar.empty()) {
            if (isMemberVariableAssignment(tok, membervar)) {
                bool assign = true;
                bool rhs = false;
                // Used for tracking if an ")" is inner or outer
                const Token *rpar = nullptr;
                for (const Token *tok2 = tok->next(); tok2; tok2 = tok2->next()) {
                    if (tok2->str() == MatchCompiler::makeConstString("="))
                        rhs = true;

                    // Look at inner expressions but not outer expressions
                    if (!rpar && tok2->str() == MatchCompiler::makeConstString("("))
                        rpar = tok2->link();
                    else if (tok2->str() == MatchCompiler::makeConstString(")")) {
                        // No rpar => this is an outer right parenthesis
                        if (!rpar)
                            break;
                        if (rpar == tok2)
                            rpar = nullptr;
                    }

                    if (tok2->str() == MatchCompiler::makeConstString(";") || (!rpar && tok2->str() == MatchCompiler::makeConstString(",")))
                        break;
                    if (rhs && tok2->varId() == var.declarationId() && isMemberVariableUsage(tok2, var.isPointer(), alloc, membervar)) {
                        assign = false;
                        break;
                    }
                }
                if (assign) {
                    bailout = true;
                    return nullptr;
                }
            }
            if (isMemberVariableUsage(tok, var.isPointer(), alloc, membervar)) {
                if (!conditionalUsage)
                    return tok;
                if (!errorToken)
                    errorToken = tok;
            } else if (match53(tok->previous())) {
                bailout = true;
                return nullptr;
            }
        } else {
            if (const Token *errtok = isVariableUsage(tok, var.isPointer(), alloc)) {
                if (!conditionalUsage)
                    return errtok;
                if (!errorToken)
                    errorToken = errtok;
            } else if (tok->strAt(1) == MatchCompiler::makeConstString("=")) {
                bool varIsUsedInRhs = false;
                visitAstNodes(tok->next()->astOperand2(), [&](const Token * t) {
                    if (!t)
                        return ChildrenToVisit::none;
                    if (t->varId() == var.declarationId()) {
                        varIsUsedInRhs = true;
                        return ChildrenToVisit::done;
                    }
                    if (isUnevaluated(t->previous()))
                        return ChildrenToVisit::none;
                    return ChildrenToVisit::op1_and_op2;
                });
                if (!varIsUsedInRhs) {
                    bailout = true;
                    return nullptr;
                }
            } else {
                bailout = true;
                return nullptr;
            }
        }
    }

    return errorToken;
}

bool CheckUninitVar::checkLoopBody(const Token *tok, const Variable& var, const Alloc alloc, const std::string &membervar, const bool suppressErrors)
{
    bool bailout = false;
    bool alwaysReturns = false;
    const Token *errorToken = checkLoopBodyRecursive(tok, var, alloc, membervar, bailout, alwaysReturns);

    if (!suppressErrors && !bailout && !alwaysReturns && errorToken) {
        if (membervar.empty())
            uninitvarError(errorToken, errorToken->expressionString(), alloc);
        else
            uninitStructMemberError(errorToken, errorToken->expressionString() + "." + membervar);
        return true;
    }

    return bailout || alwaysReturns;
}

void CheckUninitVar::checkRhs(const Token *tok, const Variable &var, Alloc alloc, nonneg int number_of_if, const std::string &membervar)
{
    bool rhs = false;
    int indent = 0;
    while (nullptr != (tok = tok->next())) {
        if (tok->str() == MatchCompiler::makeConstString("="))
            rhs = true;
        else if (rhs && tok->varId() == var.declarationId()) {
            if (membervar.empty() && isVariableUsage(tok, var.isPointer(), alloc))
                uninitvarError(tok, tok->str(), alloc);
            else if (!membervar.empty() && isMemberVariableUsage(tok, var.isPointer(), alloc, membervar))
                uninitStructMemberError(tok, tok->str() + "." + membervar);
            else if (match61(tok))
                break;
            else if (match62(tok->previous()))
                break;
        } else if (tok->str() == MatchCompiler::makeConstString(";") || (indent==0 && tok->str() == MatchCompiler::makeConstString(",")))
            break;
        else if (tok->str() == MatchCompiler::makeConstString("("))
            ++indent;
        else if (tok->str() == MatchCompiler::makeConstString(")")) {
            if (indent == 0)
                break;
            --indent;
        } else if (tok->str() == MatchCompiler::makeConstString("?") && tok->astOperand2()) {
            const bool used1 = isVariableUsed(tok->astOperand2()->astOperand1(), var);
            const bool used0 = isVariableUsed(tok->astOperand2()->astOperand2(), var);
            const bool err = (number_of_if == 0) ? (used1 || used0) : (used1 && used0);
            if (err)
                uninitvarError(tok, var.nameToken()->str(), alloc);
            break;
        } else if (isUnevaluated(tok))
            tok = tok->linkAt(1);

    }
}

static bool astIsLhs(const Token *tok)
{
    return tok && tok->astParent() && tok == tok->astParent()->astOperand1();
}

static bool astIsRhs(const Token *tok)
{
    return tok && tok->astParent() && tok == tok->astParent()->astOperand2();
}

const Token* CheckUninitVar::isVariableUsage(const Token *vartok, const Library& library, bool pointer, Alloc alloc, int indirect)
{
    const bool cpp = vartok->isCpp();
    const Token *valueExpr = vartok;   // non-dereferenced , no address of value as variable
    while (match1(valueExpr->astParent()) && astIsRhs(valueExpr))
        valueExpr = valueExpr->astParent();
    // stuff we ignore..
    while (valueExpr->astParent()) {
        // *&x
        if (valueExpr->astParent()->isUnaryOp("&") && valueExpr->astParent()->astParent() && valueExpr->astParent()->astParent()->isUnaryOp("*"))
            valueExpr = valueExpr->astParent()->astParent();
        // (type &)x
        else if (valueExpr->astParent()->isCast() && valueExpr->astParent()->isUnaryOp("(") && match63(valueExpr->astParent()->link()->previous()))
            valueExpr = valueExpr->astParent();
        // designated initializers: {.x | { ... , .x
        else if (match26(valueExpr->astParent()) &&
                 match64(valueExpr->astParent()->previous()))
            valueExpr = valueExpr->astParent();
        else
            break;
    }
    if (!pointer) {
        if (match65(vartok) && vartok->variable() && !vartok->variable()->isPointer())
            return nullptr;
        while (match26(valueExpr->astParent()) && astIsLhs(valueExpr) && valueExpr->astParent()->valueType() && valueExpr->astParent()->valueType()->pointer == 0)
            valueExpr = valueExpr->astParent();
    }
    const Token *derefValue = nullptr; // dereferenced value expression
    if (alloc != NO_ALLOC) {
        const int arrayDim = (vartok->variable() && vartok->variable()->isArray()) ? vartok->variable()->dimensions().size() : 1;
        int deref = 0;
        derefValue = valueExpr;
        while (match66(derefValue->astParent()) ||
               (derefValue->astParent() && derefValue->astParent()->isCast()) ||
               (deref < arrayDim && match67(derefValue->astParent()) && derefValue->astParent()->isBinaryOp())) {
            const Token * const derefValueParent = derefValue->astParent();
            if (derefValueParent->str() == MatchCompiler::makeConstString("*")) {
                if (derefValueParent->isUnaryOp("*"))
                    ++deref;
                else
                    break;
            } else if (derefValueParent->str() == MatchCompiler::makeConstString("[")) {
                if (astIsLhs(derefValue))
                    ++deref;
                else
                    break;
            } else if (match68(derefValueParent)) {
                if (deref >= arrayDim)
                    break;
            } else if (derefValueParent->str() == MatchCompiler::makeConstString("."))
                ++deref;
            derefValue = derefValueParent;
            if (deref < arrayDim)
                valueExpr = derefValue;
        }
        if (deref < arrayDim) {
            // todo compare deref with array dimensions
            derefValue = nullptr;
        }
    } else if (vartok->astParent() && vartok->astParent()->isUnaryOp("&")) {
        const Token *child = vartok->astParent();
        const Token *parent = child->astParent();
        while (parent && (parent->isCast() || parent->str() == MatchCompiler::makeConstString("+"))) {
            child = parent;
            parent = child->astParent();
        }
        if (parent && (parent->isUnaryOp("*") || (parent->str() == MatchCompiler::makeConstString("[") && astIsLhs(child))))
            derefValue = parent;
    }

    if (!valueExpr->astParent())
        return nullptr;

    // FIXME handle address of!!
    if (derefValue && derefValue->astParent() && derefValue->astParent()->isUnaryOp("&"))
        return nullptr;

    // BAILOUT for binary & without parent
    if (match67(valueExpr->astParent()) && astIsRhs(valueExpr) && match69(valueExpr->astParent()->tokAt(-3)))
        return nullptr;

    // safe operations
    if (isVoidCast(valueExpr->astParent()))
        return nullptr;
    if (match26(valueExpr->astParent())) {
        const Token *parent = valueExpr->astParent();
        while (match26(parent))
            parent = parent->astParent();
        if (isVoidCast(parent))
            return nullptr;
    }
    if (alloc != NO_ALLOC) {
        if (match70(valueExpr->astParent()))
            return nullptr;
        if (match71(valueExpr->astParent()) && valueExpr->astParent()->isBinaryOp())
            return nullptr;
        if (alloc == CTOR_CALL && derefValue && match59(derefValue->astParent()) && astIsLhs(derefValue))
            return nullptr;
        if (match60(valueExpr->astParent()))
            return nullptr;
    }

    // Passing variable to function..
    if (match72(valueExpr->astParent()) && (valueExpr->astParent()->str() == MatchCompiler::makeConstString(",") || astIsRhs(valueExpr))) {
        const Token *parent = valueExpr->astParent();
        while (match73(parent))
            parent = parent->astParent();
        if (match15(parent))
            return valueExpr;
        const int use = isFunctionParUsage(valueExpr, library, pointer, alloc, indirect);
        return (use>0) ? valueExpr : nullptr;
    }
    if (derefValue && match72(derefValue->astParent()) && (derefValue->astParent()->str() == MatchCompiler::makeConstString(",") || astIsRhs(derefValue))) {
        const int use = isFunctionParUsage(derefValue, library, false, NO_ALLOC, indirect);
        return (use>0) ? derefValue : nullptr;
    }
    if (valueExpr->astParent()->isUnaryOp("&")) {
        const Token *parent = valueExpr->astParent();
        if (match72(parent->astParent()) && (parent->astParent()->str() == MatchCompiler::makeConstString(",") || astIsRhs(parent))) {
            const int use = isFunctionParUsage(valueExpr, library, pointer, alloc, indirect);
            return (use>0) ? valueExpr : nullptr;
        }
        return nullptr;
    }

    // Assignments;
    // * Is this LHS in assignment
    // * Passing address in RHS to pointer variable
    {
        const Token *tok = derefValue ? derefValue : valueExpr;
        if (alloc == NO_ALLOC) {
            while (tok->valueType() && tok->valueType()->pointer == 0 && match26(tok->astParent()))
                tok = tok->astParent();
        }
        if (match46(tok->astParent())) {
            if (astIsLhs(tok)) {
                if (alloc == ARRAY || !derefValue || !derefValue->isUnaryOp("*") || !pointer)
                    return nullptr;
                const Token* deref = derefValue->astOperand1();
                while (deref && deref->isCast())
                    deref = deref->astOperand1();
                if (deref == vartok || match74(deref))
                    return nullptr;
            }
            if (alloc != NO_ALLOC && astIsRhs(valueExpr))
                return nullptr;
        }
    }

    // Initialize reference variable
    if (match75((derefValue ? derefValue : vartok)->astParent()) && astIsRhs(derefValue ? derefValue : vartok)) {
        const Token *rhstok = derefValue ? derefValue : vartok;
        const Token *lhstok = rhstok->astParent()->astOperand1();
        const Variable *lhsvar = lhstok ? lhstok->variable() : nullptr;
        if (lhsvar && lhsvar->isReference() && lhsvar->nameToken() == lhstok)
            return nullptr;
    }

    // range for loop
    if (match76(valueExpr->astParent()) &&
        valueExpr->astParent()->astParent() &&
        match14(valueExpr->astParent()->astParent()->previous())) {
        if (astIsLhs(valueExpr))
            return nullptr;
        // Taking value by reference?
        const Token *lhs = valueExpr->astParent()->astOperand1();
        if (lhs && lhs->variable() && lhs->variable()->nameToken() == lhs && lhs->variable()->isReference())
            return nullptr;
    }

    // Stream read/write
    // FIXME this code is a hack!!
    if (cpp && match77(valueExpr->astParent())) {
        if (isLikelyStreamRead(vartok->previous()))
            return nullptr;

        if (const auto* vt = valueExpr->valueType()) {
            if (vt->type == ValueType::Type::VOID)
                return nullptr;
            // passing a char* to a stream will dereference it
            if ((alloc == CTOR_CALL || alloc == ARRAY) && vt->pointer && vt->type != ValueType::Type::CHAR && vt->type != ValueType::Type::WCHAR_T)
                return nullptr;
        }
    }
    if (astIsRhs(derefValue) && isLikelyStreamRead(derefValue->astParent()))
        return nullptr;

    // Assignment with overloaded &
    if (cpp && match67(valueExpr->astParent()) && astIsRhs(valueExpr)) {
        const Token *parent = valueExpr->astParent();
        while (match67(parent) && parent->isBinaryOp())
            parent = parent->astParent();
        if (!parent) {
            const Token *lhs = valueExpr->astParent();
            while (match67(lhs) && lhs->isBinaryOp())
                lhs = lhs->astOperand1();
            if (lhs && lhs->isName() && (!lhs->valueType() || lhs->valueType()->type <= ValueType::Type::CONTAINER))
                return nullptr; // <- possible assignment
        }
    }

    return derefValue ? derefValue : valueExpr;
}

const Token* CheckUninitVar::isVariableUsage(const Token *vartok, bool pointer, Alloc alloc, int indirect) const
{
    return isVariableUsage(vartok, mSettings->library, pointer, alloc, indirect);
}

/***
 * Is function parameter "used" so a "usage of uninitialized variable" can
 * be written? If parameter is passed "by value" then it is "used". If it
 * is passed "by reference" then it is not necessarily "used".
 * @return  -1 => unknown   0 => not used   1 => used
 */
int CheckUninitVar::isFunctionParUsage(const Token *vartok, const Library& library, bool pointer, Alloc alloc, int indirect)
{
    bool unknown = false;
    const Token *parent = getAstParentSkipPossibleCastAndAddressOf(vartok, &unknown);
    if (unknown || !match72(parent))
        return -1;

    // locate start parentheses in function call..
    int argumentNumber = 0;
    const Token *start = vartok;
    while (start && !match78(start)) {
        if (start->str() == MatchCompiler::makeConstString(")"))
            start = start->link();
        else if (start->str() == MatchCompiler::makeConstString(","))
            ++argumentNumber;
        start = start->previous();
    }
    if (!start)
        return -1;

    if (match36(start->link()) && match79(start->previous()))
        return (!pointer || alloc == NO_ALLOC);

    // is this a function call?
    if (match47(start->previous())) {
        const bool address(vartok->strAt(-1) == MatchCompiler::makeConstString("&"));
        const bool array(vartok->variable() && vartok->variable()->isArray());
        // check how function handle uninitialized data arguments..
        const Function *func = start->previous()->function();
        if (func) {
            const Variable *arg = func->getArgumentVar(argumentNumber);
            if (arg) {
                const Token *argStart = arg->typeStartToken();
                if (!address && !array && match80(argStart))
                    return 1;
                if (pointer && !address && alloc == NO_ALLOC && match16(argStart))
                    return 1;
                while (argStart->previous() && argStart->previous()->isName())
                    argStart = argStart->previous();
                if (match81(argStart)) {
                    // If it's a record it's ok to pass a partially uninitialized struct.
                    if (vartok->variable() && vartok->variable()->valueType() && vartok->variable()->valueType()->type == ValueType::Type::RECORD)
                        return -1;
                    return 1;
                }
                if ((pointer || address) && match82(argStart) && match83(argStart->linkAt(3)))
                    return 1;
            }

        } else if (match84(start->previous())) {
            // control-flow statement reading the variable "by value"
            return alloc == NO_ALLOC;
        } else {
            const bool isnullbad = library.isnullargbad(start->previous(), argumentNumber + 1);
            if (indirect == 0 && pointer && !address && isnullbad && alloc == NO_ALLOC)
                return 1;
            bool hasIndirect = false;
            const bool isuninitbad = library.isuninitargbad(start->previous(), argumentNumber + 1, indirect, &hasIndirect);
            if (alloc != NO_ALLOC)
                return (isnullbad || hasIndirect) && isuninitbad;
            return isuninitbad && (!address || isnullbad);
        }
    }

    // unknown
    return -1;
}

int CheckUninitVar::isFunctionParUsage(const Token *vartok, bool pointer, Alloc alloc, int indirect) const
{
    return CheckUninitVar::isFunctionParUsage(vartok, mSettings->library, pointer, alloc, indirect);
}

bool CheckUninitVar::isMemberVariableAssignment(const Token *tok, const std::string &membervar) const
{
    if (match42(tok) && tok->strAt(2) == membervar) {
        if (match85(tok->tokAt(3)))
            return true;
        if (match86(tok->tokAt(-2)))
            return true;
        if (isLikelyStreamRead(tok->previous()))
            return true;
        if ((tok->previous() && tok->previous()->isConstOp()) || match87(tok->previous()))
            ; // member variable usage
        else if (tok->tokAt(3)->isConstOp())
            ; // member variable usage
        else if (match88(tok->previous()) &&
                 1 == isFunctionParUsage(tok, false, NO_ALLOC)) {
            return false;
        } else
            return true;
    } else if (tok->strAt(1) == MatchCompiler::makeConstString("="))
        return true;
    else if (match89(tok)) {
        const Token *ftok = tok->tokAt(2);
        if (!ftok->function() || !ftok->function()->isConst())
            // TODO: Try to determine if membervar is assigned in method
            return true;
    } else if (tok->strAt(-1) == MatchCompiler::makeConstString("&")) {
        if (match90(tok->tokAt(-2))) {
            // locate start parentheses in function call..
            int argumentNumber = 0;
            const Token *ftok = tok;
            while (ftok && !match78(ftok)) {
                if (ftok->str() == MatchCompiler::makeConstString(")"))
                    ftok = ftok->link();
                else if (ftok->str() == MatchCompiler::makeConstString(","))
                    ++argumentNumber;
                ftok = ftok->previous();
            }

            // is this a function call?
            ftok = ftok ? ftok->previous() : nullptr;
            if (match47(ftok)) {
                // check how function handle uninitialized data arguments..
                const Function *function = ftok->function();

                if (!function && mSettings) {
                    // Function definition not seen, check if direction is specified in the library configuration
                    const Library::ArgumentChecks::Direction argDirection = mSettings->library.getArgDirection(ftok, 1 + argumentNumber);
                    if (argDirection == Library::ArgumentChecks::Direction::DIR_IN)
                        return false;
                    if (argDirection == Library::ArgumentChecks::Direction::DIR_OUT)
                        return true;
                }

                const Variable *arg      = function ? function->getArgumentVar(argumentNumber) : nullptr;
                const Token *argStart    = arg ? arg->typeStartToken() : nullptr;
                while (argStart && argStart->previous() && argStart->previous()->isName())
                    argStart = argStart->previous();
                if (match91(argStart))
                    return false;
            }

            else if (ftok && match92(ftok->previous()))
                return false;
        }
        return true;
    }
    return false;
}

bool CheckUninitVar::isMemberVariableUsage(const Token *tok, bool isPointer, Alloc alloc, const std::string &membervar) const
{
    if (match88(tok->previous()) &&
        tok->strAt(2) == membervar) {
        const int use = isFunctionParUsage(tok, isPointer, alloc);
        if (use == 1)
            return true;
    }

    if (isMemberVariableAssignment(tok, membervar))
        return false;

    if (match42(tok) && tok->strAt(2) == membervar && !(tok->tokAt(-2)->variable() && tok->tokAt(-2)->variable()->isReference())) {
        const Token *parent = tok->next()->astParent();
        return !parent || !parent->isUnaryOp("&");
    }
    if (!isPointer && !match26(tok->astParent()) && match53(tok->previous()) && isVariableUsage(tok, isPointer, alloc))
        return true;

    if (!isPointer && match93(tok->previous())) {
        const Token* lhs = tok->previous()->astOperand1();
        return !(lhs && lhs->variable() && lhs->variable()->isReference() && lhs == lhs->variable()->nameToken());
    }

    // = *(&var);
    if (!isPointer &&
        match67(tok->astParent()) &&
        match94(tok->astParent()->astParent()) &&
        match95(tok->astParent()->astParent()->astParent()) &&
        tok->astParent()->astParent()->astParent()->astOperand2() == tok->astParent()->astParent())
        return true;

    // TODO: this used to be experimental - enable or remove see #5586
    if ((false) && // NOLINT(readability-simplify-boolean-expr)
        !isPointer &&
        match96(tok->tokAt(-2)) &&
        isVariableUsage(tok, isPointer, alloc))
        return true;

    return false;
}

void CheckUninitVar::uninitdataError(const Token *tok, const std::string &varname)
{
    reportError(tok, Severity::error, "uninitdata", "$symbol:" + varname + "\nMemory is allocated but not initialized: $symbol", CWE_USE_OF_UNINITIALIZED_VARIABLE, Certainty::normal);
}

void CheckUninitVar::uninitvarError(const Token *tok, const std::string &varname, ErrorPath errorPath)
{
    if (diag(tok))
        return;
    errorPath.emplace_back(tok, "");
    reportError(std::move(errorPath),
                Severity::error,
                "legacyUninitvar",
                "$symbol:" + varname + "\nUninitialized variable: $symbol",
                CWE_USE_OF_UNINITIALIZED_VARIABLE,
                Certainty::normal);
}

void CheckUninitVar::uninitvarError(const Token* tok, const ValueFlow::Value& v)
{
    if (!mSettings->isEnabled(&v))
        return;
    if (diag(tok))
        return;
    const Token* ltok = tok;
    if (tok && match26(tok->astParent()) && astIsRHS(tok))
        ltok = tok->astParent();
    const std::string& varname = ltok ? ltok->expressionString() : "x";
    ErrorPath errorPath = v.errorPath;
    errorPath.emplace_back(tok, "");
    auto severity = v.isKnown() ? Severity::error : Severity::warning;
    auto certainty = v.isInconclusive() ? Certainty::inconclusive : Certainty::normal;
    if (v.subexpressions.empty()) {
        reportError(std::move(errorPath),
                    severity,
                    "uninitvar",
                    "$symbol:" + varname + "\nUninitialized variable: $symbol",
                    CWE_USE_OF_UNINITIALIZED_VARIABLE,
                    certainty);
        return;
    }
    std::string vars = v.subexpressions.size() == 1 ? "variable: " : "variables: ";
    std::string prefix;
    for (const std::string& var : v.subexpressions) {
        vars += prefix + varname + "." + var;
        prefix = ", ";
    }
    reportError(std::move(errorPath),
                severity,
                "uninitvar",
                "$symbol:" + varname + "\nUninitialized " + vars,
                CWE_USE_OF_UNINITIALIZED_VARIABLE,
                certainty);
}

void CheckUninitVar::uninitStructMemberError(const Token *tok, const std::string &membername)
{
    reportError(tok,
                Severity::error,
                "uninitStructMember",
                "$symbol:" + membername + "\nUninitialized struct member: $symbol", CWE_USE_OF_UNINITIALIZED_VARIABLE, Certainty::normal);
}

void CheckUninitVar::valueFlowUninit()
{
    logChecker("CheckUninitVar::valueFlowUninit");

    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();

    std::unordered_set<nonneg int> ids;
    for (const bool subfunction : {false, true}) {
        // check every executable scope
        for (const Scope* scope : symbolDatabase->functionScopes) {
            for (const Token* tok = scope->bodyStart; tok != scope->bodyEnd; tok = tok->next()) {
                if (isUnevaluated(tok)) {
                    tok = tok->linkAt(1);
                    continue;
                }
                if (ids.count(tok->exprId()) > 0)
                    continue;
                if (!tok->variable() && !tok->isUnaryOp("*") && !tok->isUnaryOp("&"))
                    continue;
                if (match47(tok))
                    continue;
                const Token* parent = tok->astParent();
                while (match26(parent))
                    parent = parent->astParent();
                if (parent && parent->isUnaryOp("&"))
                    continue;
                if (isVoidCast(parent))
                    continue;
                auto v = std::find_if(
                    tok->values().cbegin(), tok->values().cend(), std::mem_fn(&ValueFlow::Value::isUninitValue));
                if (v == tok->values().cend())
                    continue;
                if (v->tokvalue && ids.count(v->tokvalue->exprId()) > 0)
                    continue;
                if (subfunction == (v->path == 0))
                    continue;
                if (v->isInconclusive())
                    continue;
                if (v->indirect > 1 || v->indirect < 0)
                    continue;
                bool uninitderef = false;
                if (tok->variable()) {
                    bool unknown;
                    const bool isarray = tok->variable()->isArray();
                    if (isarray && tok->variable()->isMember())
                        continue; // Todo: this is a bailout
                    if (isarray && tok->variable()->isStlType() && match26(tok->astParent())) {
                        const auto yield = astContainerYield(tok, mSettings->library);
                        if (yield != Library::Container::Yield::AT_INDEX && yield != Library::Container::Yield::ITEM)
                            continue;
                    }
                    const bool deref = CheckNullPointer::isPointerDeRef(tok, unknown, *mSettings);
                    uninitderef = deref && v->indirect == 0;
                    const bool isleaf = isLeafDot(tok) || uninitderef;
                    if (!isleaf && match97(tok->astParent()) &&
                        (tok->astParent()->next()->variable() || tok->astParent()->next()->isEnumerator()))
                        continue;
                }
                const ExprUsage usage = getExprUsage(tok, v->indirect, *mSettings);
                if (usage == ExprUsage::NotUsed || usage == ExprUsage::Inconclusive)
                    continue;
                if (!v->subexpressions.empty() && usage == ExprUsage::PassedByReference)
                    continue;
                if (usage != ExprUsage::Used) {
                    if (!(match98(tok->astParent()) && uninitderef) &&
                        isVariableChanged(tok, v->indirect, *mSettings))
                        continue;
                    bool inconclusive = false;
                    if (isVariableChangedByFunctionCall(tok, v->indirect, *mSettings, &inconclusive) || inconclusive)
                        continue;
                }
                uninitvarError(tok, *v);
                ids.insert(tok->exprId());
                if (v->tokvalue)
                    ids.insert(v->tokvalue->exprId());
            }
        }
    }
}

// NOLINTNEXTLINE(readability-non-const-parameter) - used as callback so we need to preserve the signature
static bool isVariableUsage(const Settings &settings, const Token *vartok, MathLib::bigint *value)
{
    (void)value;
    return CheckUninitVar::isVariableUsage(vartok, settings.library, true, CheckUninitVar::Alloc::ARRAY);
}

// a Clang-built executable will crash when using the anonymous MyFileInfo later on - so put it in a unique namespace for now
// see https://trac.cppcheck.net/ticket/12108 for more details
#ifdef __clang__
inline namespace CheckUninitVar_internal
#else
namespace
#endif
{
    /* data for multifile checking */
    class MyFileInfo : public Check::FileInfo {
    public:
        using Check::FileInfo::FileInfo;
        /** function arguments that data are unconditionally read */
        std::list<CTU::FileInfo::UnsafeUsage> unsafeUsage;

        /** Convert data into xml string */
        std::string toString() const override
        {
            return CTU::toString(unsafeUsage);
        }
    };
}

static bool isVariableUsage(const Settings &settings, const Token *argtok, CTU::FileInfo::Value *value) {
    return isVariableUsage(settings, argtok, &value->value);
}

Check::FileInfo *CheckUninitVar::getFileInfo(const Tokenizer &tokenizer, const Settings &settings, const std::string& /*currentConfig*/) const
{
    const std::list<CTU::FileInfo::UnsafeUsage> &unsafeUsage = CTU::getUnsafeUsage(tokenizer, settings, ::isVariableUsage);
    if (unsafeUsage.empty())
        return nullptr;

    auto *fileInfo = new MyFileInfo(tokenizer.list.getFiles()[0]);
    fileInfo->unsafeUsage = unsafeUsage;
    return fileInfo;
}

Check::FileInfo * CheckUninitVar::loadFileInfoFromXml(const tinyxml2::XMLElement *xmlElement) const
{
    const std::list<CTU::FileInfo::UnsafeUsage> &unsafeUsage = CTU::loadUnsafeUsageListFromXml(xmlElement);
    if (unsafeUsage.empty())
        return nullptr;

    auto *fileInfo = new MyFileInfo;
    fileInfo->unsafeUsage = unsafeUsage;
    return fileInfo;
}

bool CheckUninitVar::analyseWholeProgram(const CTU::FileInfo &ctu, const std::list<Check::FileInfo*> &fileInfo, const Settings& settings, ErrorLogger &errorLogger)
{
    (void)settings;

    CheckUninitVar dummy(nullptr, &settings, &errorLogger);
    dummy.
    logChecker("CheckUninitVar::analyseWholeProgram");

    if (fileInfo.empty())
        return false;

    const std::map<std::string, std::list<const CTU::FileInfo::CallBase *>> callsMap = ctu.getCallsMap();

    bool foundErrors = false;

    for (const Check::FileInfo* fi1 : fileInfo) {
        const auto *fi = dynamic_cast<const MyFileInfo*>(fi1);
        if (!fi)
            continue;
        for (const CTU::FileInfo::UnsafeUsage &unsafeUsage : fi->unsafeUsage) {
            const CTU::FileInfo::FunctionCall *functionCall = nullptr;

            std::list<ErrorMessage::FileLocation> locationList =
                CTU::FileInfo::getErrorPath(CTU::FileInfo::InvalidValueType::uninit,
                                            unsafeUsage,
                                            callsMap,
                                            "Using argument ARG",
                                            &functionCall,
                                            false,
                                            settings.maxCtuDepth);
            if (locationList.empty())
                continue;

            const ErrorMessage errmsg(std::move(locationList),
                                      fi->file0,
                                      Severity::error,
                                      "Using argument " + unsafeUsage.myArgumentName + " that points at uninitialized variable " + functionCall->callArgumentExpression,
                                      "ctuuninitvar",
                                      CWE_USE_OF_UNINITIALIZED_VARIABLE,
                                      Certainty::normal);
            errorLogger.reportErr(errmsg);

            foundErrors = true;
        }
    }
    return foundErrors;
}

void CheckUninitVar::runChecks(const Tokenizer &tokenizer, ErrorLogger *errorLogger)
{
    CheckUninitVar checkUninitVar(&tokenizer, &tokenizer.getSettings(), errorLogger);
    checkUninitVar.valueFlowUninit();
    checkUninitVar.check();
}

void CheckUninitVar::getErrorMessages(ErrorLogger* errorLogger, const Settings* settings) const
{
    CheckUninitVar c(nullptr, settings, errorLogger);

    ValueFlow::Value v{};

    c.uninitvarError(nullptr, v); // TODO: does not produce any output
    c.uninitdataError(nullptr, "varname");
    c.uninitStructMemberError(nullptr, "a.b");
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
