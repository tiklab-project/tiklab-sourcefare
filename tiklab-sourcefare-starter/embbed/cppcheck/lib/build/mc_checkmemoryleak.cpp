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
// pattern: %name% :: %type%
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: %name% . %type%
MAYBE_UNUSED static inline bool match2(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: ( std| ::| nothrow )
MAYBE_UNUSED static inline bool match3(const Token* tok) {
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
// pattern: %name% :: %name%
MAYBE_UNUSED static inline bool match4(const Token* tok) {
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
// pattern: open|openat|creat|mkstemp|mkostemp|socket (
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("open")) || (tok->str() == MatchCompiler::makeConstString("openat")) || (tok->str() == MatchCompiler::makeConstString("creat")) || (tok->str() == MatchCompiler::makeConstString("mkstemp")) || (tok->str() == MatchCompiler::makeConstString("mkostemp")) || (tok->str() == MatchCompiler::makeConstString("socket"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: popen (
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("popen")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %name% (
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %varid% [,)]
MAYBE_UNUSED static inline bool match8(const Token* tok, const int varid) {
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: .|::
MAYBE_UNUSED static inline bool match9(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: fcloseall ( )
MAYBE_UNUSED static inline bool match10(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("fcloseall")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: %name% .|::
MAYBE_UNUSED static inline bool match11(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: %varid% )|,|-
MAYBE_UNUSED static inline bool match12(const Token* tok, const int varid) {
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-"))))
        return false;
    return true;
}
// pattern: , 0 )
MAYBE_UNUSED static inline bool match13(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("0")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: stdin|stdout|stderr
MAYBE_UNUSED static inline bool match14(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("stdin")) || (tok->str() == MatchCompiler::makeConstString("stdout")) || (tok->str() == MatchCompiler::makeConstString("stderr"))))
        return false;
    return true;
}
// pattern: \"/dev/null\"
MAYBE_UNUSED static inline bool match15(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("\"/dev/null\"")))
        return false;
    return true;
}
// pattern: %varid% =
MAYBE_UNUSED static inline bool match16(const Token* tok, const int varid) {
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: = %varid% ;
MAYBE_UNUSED static inline bool match17(const Token* tok, const int varid) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: [(,] %varid% [,)]
MAYBE_UNUSED static inline bool match18(const Token* tok, const int varid) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: [(,] & %varid% [.,)]
MAYBE_UNUSED static inline bool match19(const Token* tok, const int varid) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(".,)", tok->str()[0]))
        return false;
    return true;
}
// pattern: [;{}] %varid% .
MAYBE_UNUSED static inline bool match20(const Token* tok, const int varid) {
    if (!tok || tok->str().size() != 1U || !strchr(";{}", tok->str()[0]))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: &&|;
MAYBE_UNUSED static inline bool match21(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        return false;
    return true;
}
// pattern: UNLIKELY|LIKELY
MAYBE_UNUSED static inline bool match22(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("UNLIKELY")) || (tok->str() == MatchCompiler::makeConstString("LIKELY"))))
        return false;
    return true;
}
// pattern: if (
MAYBE_UNUSED static inline bool match23(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %name% =
MAYBE_UNUSED static inline bool match24(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: %name% = %varid% ;
template<class T> MAYBE_UNUSED static inline T * findmatch25(T * start_tok, const Token * end, int varid) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !tok->isName())
        continue;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        continue;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        continue;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: [{};] %varid% = *| %var% .| %var%| [;=]
template<class T> MAYBE_UNUSED static inline T * findmatch26(T * start_tok, const Token * end, int varid) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || tok->str().size() != 1U || !strchr("{};", tok->str()[0]))
        continue;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        continue;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        continue;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        continue;
    tok = tok->next();
    if (tok && ((tok->str() == MatchCompiler::makeConstString("."))))
        tok = tok->next();
    if (tok && ((tok->varId() != 0)))
        tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";=", tok->str()[0]))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: ; if (
MAYBE_UNUSED static inline bool match27(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: :|, %varid% (
MAYBE_UNUSED static inline bool match28(const Token* tok, const int varid) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(","))))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %varid% =|[
MAYBE_UNUSED static inline bool match29(const Token* tok, const int varid) {
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: [{};] %name% (
MAYBE_UNUSED static inline bool match30(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("{};", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %type% :: %varid% =
MAYBE_UNUSED static inline bool match31(const Token* tok, const int varid) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
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
// pattern: = %varid% [;=]
MAYBE_UNUSED static inline bool match32(const Token* tok, const int varid) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(";=", tok->str()[0]))
        return false;
    return true;
}
// pattern: %varid% = %name% (
MAYBE_UNUSED static inline bool match33(const Token* tok, const int varid) {
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: [(,] &| %varid% [,)]
MAYBE_UNUSED static inline bool match34(const Token* tok, const int varid) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr(",)", tok->str()[0]))
        return false;
    return true;
}
// pattern: [(,] &| %varid% . %name% [,)]
MAYBE_UNUSED static inline bool match35(const Token* tok, const int varid) {
    if (!tok || tok->str().size() != 1U || !strchr("(,", tok->str()[0]))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
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
// pattern: (|[
MAYBE_UNUSED static inline bool match36(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("["))))
        return false;
    return true;
}
// pattern: =
MAYBE_UNUSED static inline bool match37(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: .
MAYBE_UNUSED static inline bool match38(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: %name% ( %varid% )
MAYBE_UNUSED static inline bool match39(const Token* tok, const int varid) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: ) {
MAYBE_UNUSED static inline bool match40(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: %name% ( %var% . %varid% )
MAYBE_UNUSED static inline bool match41(const Token* tok, const int varid) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: return %varid% ;
MAYBE_UNUSED static inline bool match42(const Token* tok, const int varid) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: return & %varid%
MAYBE_UNUSED static inline bool match43(const Token* tok, const int varid) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    return true;
}
// pattern: return %varid% . %var%
MAYBE_UNUSED static inline bool match44(const Token* tok, const int varid) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    return true;
}
// pattern: return %name% (
MAYBE_UNUSED static inline bool match45(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: = %var% . %varid% ;
MAYBE_UNUSED static inline bool match46(const Token* tok, const int varid) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: ?|:
MAYBE_UNUSED static inline bool match47(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: %assign%
MAYBE_UNUSED static inline bool match48(const Token* tok) {
    if (!tok || !tok->isAssignmentOp())
        return false;
    return true;
}
// pattern: return
MAYBE_UNUSED static inline bool match49(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")))
        return false;
    return true;
}
// pattern: (
MAYBE_UNUSED static inline bool match50(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: new
MAYBE_UNUSED static inline bool match51(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    return true;
}
// pattern: }|;
template<class T> MAYBE_UNUSED static inline T * findmatch52(T * start_tok) {
    for (; start_tok; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || (tok->str() == MatchCompiler::makeConstString(";"))))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: %name%
MAYBE_UNUSED static inline bool match53(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %comp%|!|,|%oror%|&&|:
MAYBE_UNUSED static inline bool match54(const Token* tok) {
    if (!tok || !(tok->isComparisonOp() || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || (tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":"))))
        return false;
    return true;
}
// pattern: ?
MAYBE_UNUSED static inline bool match55(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?")))
        return false;
    return true;
}
// pattern: shared_ptr|unique_ptr <
MAYBE_UNUSED static inline bool match56(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("shared_ptr")) || (tok->str() == MatchCompiler::makeConstString("unique_ptr"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: > ( new %name%
MAYBE_UNUSED static inline bool match57(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: > (
MAYBE_UNUSED static inline bool match58(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/checkmemoryleak.cpp"
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


#include "checkmemoryleak.h"

#include "astutils.h"
#include "errorlogger.h"
#include "errortypes.h"
#include "library.h"
#include "mathlib.h"
#include "platform.h"
#include "settings.h"
#include "symboldatabase.h"
#include "token.h"
#include "tokenize.h"

#include <algorithm>
#include <utility>
#include <vector>

//---------------------------------------------------------------------------

// Register this check class (by creating a static instance of it)
namespace {
    CheckMemoryLeakInFunction instance1;
    CheckMemoryLeakInClass instance2;
    CheckMemoryLeakStructMember instance3;
    CheckMemoryLeakNoVar instance4;
}

// CWE ID used:
static const CWE CWE398(398U);  // Indicator of Poor Code Quality
static const CWE CWE401(401U);  // Improper Release of Memory Before Removing Last Reference ('Memory Leak')
static const CWE CWE771(771U);  // Missing Reference to Active Allocated Resource
static const CWE CWE772(772U);  // Missing Release of Resource after Effective Lifetime

//---------------------------------------------------------------------------

CheckMemoryLeak::AllocType CheckMemoryLeak::getAllocationType(const Token *tok2, nonneg int varid, std::list<const Function*> *callstack) const
{
    // What we may have...
    //     * var = (char *)malloc(10);
    //     * var = new char[10];
    //     * var = strdup("hello");
    //     * var = strndup("hello", 3);
    if (tok2 && tok2->str() == MatchCompiler::makeConstString("(")) {
        tok2 = tok2->link();
        tok2 = tok2 ? tok2->next() : nullptr;
    }
    if (!tok2)
        return No;
    if (tok2->str() == MatchCompiler::makeConstString("::"))
        tok2 = tok2->next();
    while (match1(tok2))
        tok2 = tok2->tokAt(2);
    if (!tok2->isName())
        return No;

    if (!match2(tok2)) {
        // Using realloc..
        AllocType reallocType = getReallocationType(tok2, varid);
        if (reallocType != No)
            return reallocType;

        if (tok2->isCpp() && tok2->str() == MatchCompiler::makeConstString("new")) {
            if (tok2->strAt(1) == MatchCompiler::makeConstString("(") && !match3(tok2->next()))
                return No;
            if (tok2->astOperand1() && (tok2->astOperand1()->str() == MatchCompiler::makeConstString("[") || (tok2->astOperand1()->astOperand1() && tok2->astOperand1()->astOperand1()->str() == MatchCompiler::makeConstString("["))))
                return NewArray;
            const Token *typeTok = tok2->next();
            while (match4(typeTok))
                typeTok = typeTok->tokAt(2);
            const Scope* classScope = nullptr;
            if (typeTok->type() && (typeTok->type()->isClassType() || typeTok->type()->isStructType() || typeTok->type()->isUnionType())) {
                classScope = typeTok->type()->classScope;
            } else if (typeTok->function() && typeTok->function()->isConstructor()) {
                classScope = typeTok->function()->nestedIn;
            }
            if (classScope && classScope->numConstructors > 0)
                return No;
            return New;
        }

        if (mSettings_->hasLib("posix")) {
            if (match5(tok2)) {
                // simple sanity check of function parameters..
                // TODO: Make such check for all these functions
                const int num = numberOfArguments(tok2);
                if (tok2->str() == MatchCompiler::makeConstString("open") && num != 2 && num != 3)
                    return No;

                // is there a user function with this name?
                if (tok2->function())
                    return No;
                return Fd;
            }

            if (match6(tok2))
                return Pipe;
        }

        // Does tok2 point on a Library allocation function?
        const int alloctype = mSettings_->library.getAllocId(tok2, -1);
        if (alloctype > 0) {
            if (alloctype == mSettings_->library.deallocId("free"))
                return Malloc;
            if (alloctype == mSettings_->library.deallocId("fclose"))
                return File;
            return Library::ismemory(alloctype) ? OtherMem : OtherRes;
        }
    }

    while (match2(tok2))
        tok2 = tok2->tokAt(2);

    // User function
    const Function* func = tok2->function();
    if (func == nullptr)
        return No;

    // Prevent recursion
    if (callstack && std::find(callstack->cbegin(), callstack->cend(), func) != callstack->cend())
        return No;

    std::list<const Function*> cs;
    if (!callstack)
        callstack = &cs;

    callstack->push_back(func);
    return functionReturnType(func, callstack);
}


CheckMemoryLeak::AllocType CheckMemoryLeak::getReallocationType(const Token *tok2, nonneg int varid) const
{
    // What we may have...
    //     * var = (char *)realloc(..;
    if (tok2 && tok2->str() == MatchCompiler::makeConstString("(")) {
        tok2 = tok2->link();
        tok2 = tok2 ? tok2->next() : nullptr;
    }
    if (!tok2)
        return No;

    if (!match7(tok2))
        return No;

    const Library::AllocFunc *f = mSettings_->library.getReallocFuncInfo(tok2);
    if (!(f && f->reallocArg > 0 && f->reallocArg <= numberOfArguments(tok2)))
        return No;
    const auto args = getArguments(tok2);
    if (args.size() < (f->reallocArg))
        return No;
    const Token* arg = args.at(f->reallocArg - 1);
    while (arg && arg->isCast())
        arg = arg->astOperand1();
    while (arg && arg->isUnaryOp("*"))
        arg = arg->astOperand1();
    if (varid > 0 && !match8(arg, varid))
        return No;

    const int realloctype = mSettings_->library.getReallocId(tok2, -1);
    if (realloctype > 0) {
        if (realloctype == mSettings_->library.deallocId("free"))
            return Malloc;
        if (realloctype == mSettings_->library.deallocId("fclose"))
            return File;
        return Library::ismemory(realloctype) ? OtherMem : OtherRes;
    }
    return No;
}


CheckMemoryLeak::AllocType CheckMemoryLeak::getDeallocationType(const Token *tok, nonneg int varid) const
{
    if (tok->isCpp() && tok->str() == MatchCompiler::makeConstString("delete") && tok->astOperand1()) {
        const Token* vartok = tok->astOperand1();
        if (match9(vartok))
            vartok = vartok->astOperand2();

        if (vartok && vartok->varId() == varid) {
            if (tok->strAt(1) == MatchCompiler::makeConstString("["))
                return NewArray;
            return New;
        }
    }

    if (tok->str() == MatchCompiler::makeConstString("::"))
        tok = tok->next();

    if (match7(tok)) {
        if (match10(tok))
            return File;

        int argNr = 1;
        for (const Token* tok2 = tok->tokAt(2); tok2; tok2 = tok2->nextArgument()) {
            const Token* vartok = tok2;
            while (match11(vartok))
                vartok = vartok->tokAt(2);

            if (match12(vartok, varid)) {
                if (tok->str() == MatchCompiler::makeConstString("realloc") && match13(vartok->next()))
                    return Malloc;

                if (mSettings_->hasLib("posix")) {
                    if (tok->str() == MatchCompiler::makeConstString("close"))
                        return Fd;
                    if (tok->str() == MatchCompiler::makeConstString("pclose"))
                        return Pipe;
                }

                // Does tok point on a Library deallocation function?
                const int dealloctype = mSettings_->library.getDeallocId(tok, argNr);
                if (dealloctype > 0) {
                    if (dealloctype == mSettings_->library.deallocId("free"))
                        return Malloc;
                    if (dealloctype == mSettings_->library.deallocId("fclose"))
                        return File;
                    return Library::ismemory(dealloctype) ? OtherMem : OtherRes;
                }
            }
            argNr++;
        }
    }

    return No;
}

bool CheckMemoryLeak::isReopenStandardStream(const Token *tok) const
{
    if (getReallocationType(tok, 0) == File) {
        const Library::AllocFunc *f = mSettings_->library.getReallocFuncInfo(tok);
        if (f && f->reallocArg > 0 && f->reallocArg <= numberOfArguments(tok)) {
            const Token* arg = getArguments(tok).at(f->reallocArg - 1);
            if (match14(arg))
                return true;
        }
    }
    return false;
}

bool CheckMemoryLeak::isOpenDevNull(const Token *tok) const
{
    if (mSettings_->hasLib("posix") && tok->str() == MatchCompiler::makeConstString("open") && numberOfArguments(tok) == 2) {
        const Token* arg = getArguments(tok).at(0);
        if (match15(arg))
            return true;
    }
    return false;
}

//--------------------------------------------------------------------------


//--------------------------------------------------------------------------

void CheckMemoryLeak::memoryLeak(const Token *tok, const std::string &varname, AllocType alloctype) const
{
    if (alloctype == CheckMemoryLeak::File ||
        alloctype == CheckMemoryLeak::Pipe ||
        alloctype == CheckMemoryLeak::Fd ||
        alloctype == CheckMemoryLeak::OtherRes)
        resourceLeakError(tok, varname);
    else
        memleakError(tok, varname);
}
//---------------------------------------------------------------------------

void CheckMemoryLeak::reportErr(const Token *tok, Severity severity, const std::string &id, const std::string &msg, const CWE &cwe) const
{
    std::list<const Token *> callstack;

    if (tok)
        callstack.push_back(tok);

    reportErr(callstack, severity, id, msg, cwe);
}

void CheckMemoryLeak::reportErr(const std::list<const Token *> &callstack, Severity severity, const std::string &id, const std::string &msg, const CWE &cwe) const
{
    const ErrorMessage errmsg(callstack, mTokenizer_ ? &mTokenizer_->list : nullptr, severity, id, msg, cwe, Certainty::normal);
    if (mErrorLogger_)
        mErrorLogger_->reportErr(errmsg);
    else
        Check::writeToErrorList(errmsg);
}

void CheckMemoryLeak::memleakError(const Token *tok, const std::string &varname) const
{
    reportErr(tok, Severity::error, "memleak", "$symbol:" + varname + "\nMemory leak: $symbol", CWE(401U));
}

void CheckMemoryLeak::memleakUponReallocFailureError(const Token *tok, const std::string &reallocfunction, const std::string &varname) const
{
    reportErr(tok, Severity::error, "memleakOnRealloc", "$symbol:" + varname + "\nCommon " + reallocfunction + " mistake: \'$symbol\' nulled but not freed upon failure", CWE(401U));
}

void CheckMemoryLeak::resourceLeakError(const Token *tok, const std::string &varname) const
{
    std::string errmsg("Resource leak");
    if (!varname.empty())
        errmsg = "$symbol:" + varname + '\n' + errmsg + ": $symbol";
    reportErr(tok, Severity::error, "resourceLeak", errmsg, CWE(775U));
}

void CheckMemoryLeak::deallocuseError(const Token *tok, const std::string &varname) const
{
    reportErr(tok, Severity::error, "deallocuse", "$symbol:" + varname + "\nDereferencing '$symbol' after it is deallocated / released", CWE(416U));
}

void CheckMemoryLeak::mismatchAllocDealloc(const std::list<const Token *> &callstack, const std::string &varname) const
{
    reportErr(callstack, Severity::error, "mismatchAllocDealloc", "$symbol:" + varname + "\nMismatching allocation and deallocation: $symbol", CWE(762U));
}

CheckMemoryLeak::AllocType CheckMemoryLeak::functionReturnType(const Function* func, std::list<const Function*> *callstack) const
{
    if (!func || !func->hasBody() || !func->functionScope)
        return No;

    // Get return pointer..
    const Variable* var = nullptr;
    for (const Token *tok2 = func->functionScope->bodyStart; tok2 != func->functionScope->bodyEnd; tok2 = tok2->next()) {
        if (const Token *endOfLambda = findLambdaEndToken(tok2))
            tok2 = endOfLambda;
        if (tok2->str() == MatchCompiler::makeConstString("{") && !tok2->scope()->isExecutable())
            tok2 = tok2->link();
        if (tok2->str() == MatchCompiler::makeConstString("return")) {
            const AllocType allocType = getAllocationType(tok2->next(), 0, callstack);
            if (allocType != No)
                return allocType;

            if (tok2->scope() != func->functionScope || !tok2->astOperand1())
                return No;
            const Token* tok = tok2->astOperand1();
            if (match9(tok))
                tok = tok->astOperand2() ? tok->astOperand2() : tok->astOperand1();
            if (tok)
                var = tok->variable();
            break;
        }
    }

    // Not returning pointer value..
    if (!var)
        return No;

    // If variable is not local then alloctype shall be "No"
    // Todo: there can be false negatives about mismatching allocation/deallocation.
    //       => Generate "alloc ; use ;" if variable is not local?
    if (!var->isLocal() || var->isStatic())
        return No;

    // Check if return pointer is allocated..
    AllocType allocType = No;
    nonneg int const varid = var->declarationId();
    for (const Token* tok = func->functionScope->bodyStart; tok != func->functionScope->bodyEnd; tok = tok->next()) {
        if (match16(tok, varid)) {
            allocType = getAllocationType(tok->tokAt(2), varid, callstack);
        }
        if (match17(tok, varid)) {
            return No;
        }
        if (!tok->isC() && match18(tok, varid)) {
            return No;
        }
        if (match19(tok, varid)) {
            return No;
        }
        if (match20(tok, varid)) {
            return No;
        }
        if (allocType == No && tok->str() == MatchCompiler::makeConstString("return"))
            return No;
    }

    return allocType;
}


static bool notvar(const Token *tok, nonneg int varid)
{
    if (!tok)
        return false;
    if (match21(tok))
        return notvar(tok->astOperand1(),varid) || notvar(tok->astOperand2(),varid);
    if (tok->str() == MatchCompiler::makeConstString("(") && match22(tok->astOperand1()))
        return notvar(tok->astOperand2(), varid);
    const Token *vartok = astIsVariableComparison(tok, "==", "0");
    return vartok && (vartok->varId() == varid);
}

static bool ifvar(const Token *tok, nonneg int varid, const std::string &comp, const std::string &rhs)
{
    if (!match23(tok))
        return false;
    const Token *condition = tok->next()->astOperand2();
    if (condition && condition->str() == MatchCompiler::makeConstString("(") && match22(condition->astOperand1()))
        condition = condition->astOperand2();
    if (!condition || condition->str() == MatchCompiler::makeConstString("&&"))
        return false;

    const Token *vartok = astIsVariableComparison(condition, comp, rhs);
    return (vartok && vartok->varId() == varid);
}

//---------------------------------------------------------------------------
// Check for memory leaks due to improper realloc() usage.
//   Below, "a" may be set to null without being freed if realloc() cannot
//   allocate the requested memory:
//     a = malloc(10); a = realloc(a, 100);
//---------------------------------------------------------------------------

void CheckMemoryLeakInFunction::checkReallocUsage()
{
    logChecker("CheckMemoryLeakInFunction::checkReallocUsage");

    // only check functions
    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();
    for (const Scope * scope : symbolDatabase->functionScopes) {

        // Search for the "var = realloc(var, 100" pattern within this function
        for (const Token *tok = scope->bodyStart->next(); tok != scope->bodyEnd; tok = tok->next()) {
            if (tok->varId() > 0 && match24(tok)) {
                // Get the parenthesis in "realloc("
                const Token* parTok = tok->next()->astOperand2();
                // Skip casts
                while (parTok && parTok->isCast())
                    parTok = parTok->astOperand1();
                if (!parTok)
                    continue;

                const Token *const reallocTok = parTok->astOperand1();
                if (!reallocTok)
                    continue;
                const Library::AllocFunc* f = mSettings->library.getReallocFuncInfo(reallocTok);
                if (!(f && f->arg == -1 && mSettings->library.isnotnoreturn(reallocTok)))
                    continue;

                const AllocType allocType = getReallocationType(reallocTok, tok->varId());
                if (!((allocType == Malloc || allocType == OtherMem)))
                    continue;
                const Token* arg = getArguments(reallocTok).at(f->reallocArg - 1);
                while (arg && arg->isCast())
                    arg = arg->astOperand1();
                const Token* tok2 = tok;
                while (arg && arg->isUnaryOp("*") && tok2 && tok2->astParent() && tok2->astParent()->isUnaryOp("*")) {
                    arg = arg->astOperand1();
                    tok2 = tok2->astParent();
                }

                if (!arg || !tok2)
                    continue;

                if (!(tok->varId() == arg->varId() && tok->variable() && !tok->variable()->isArgument()))
                    continue;

                // Check that another copy of the pointer wasn't saved earlier in the function
                if (findmatch25(scope->bodyStart, tok, tok->varId())  ||
                    findmatch26(scope->bodyStart, tok, tok->varId()) )
                    continue;

                // Check if the argument is known to be null, which means it is not a memory leak
                if (arg->hasKnownIntValue() && arg->getKnownIntValue() == 0) {
                    continue;
                }

                const Token* tokEndRealloc = reallocTok->linkAt(1);
                // Check that the allocation isn't followed immediately by an 'if (!var) { error(); }' that might handle failure
                if (match27(tokEndRealloc->next()) &&
                    notvar(tokEndRealloc->tokAt(3)->astOperand2(), tok->varId())) {
                    const Token* tokEndBrace = tokEndRealloc->linkAt(3)->linkAt(1);
                    if (tokEndBrace && mTokenizer->isScopeNoReturn(tokEndBrace))
                        continue;
                }

                memleakUponReallocFailureError(tok, reallocTok->str(), tok->str());
            }
        }
    }
}
//---------------------------------------------------------------------------

void CheckMemoryLeakInFunction::runChecks(const Tokenizer &tokenizer, ErrorLogger *errorLogger)
{
    CheckMemoryLeakInFunction checkMemoryLeak(&tokenizer, &tokenizer.getSettings(), errorLogger);
    checkMemoryLeak.checkReallocUsage();
}

void CheckMemoryLeakInFunction::getErrorMessages(ErrorLogger *e, const Settings *settings) const
{
    CheckMemoryLeakInFunction c(nullptr, settings, e);
    c.memleakError(nullptr, "varname");
    c.resourceLeakError(nullptr, "varname");
    c.deallocuseError(nullptr, "varname");
    const std::list<const Token *> callstack;
    c.mismatchAllocDealloc(callstack, "varname");
    c.memleakUponReallocFailureError(nullptr, "realloc", "varname");
}

//---------------------------------------------------------------------------
// Checks for memory leaks in classes..
//---------------------------------------------------------------------------


void CheckMemoryLeakInClass::check()
{
    logChecker("CheckMemoryLeakInClass::check");

    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();

    // only check classes and structures
    for (const Scope * scope : symbolDatabase->classAndStructScopes) {
        for (const Variable &var : scope->varlist) {
            if (!var.isStatic() && (var.isPointer() || var.isPointerArray())) {
                // allocation but no deallocation of private variables in public function..
                const Token *tok = var.typeStartToken();
                // Either it is of standard type or a non-derived type
                if (tok->isStandardType() || (var.type() && var.type()->derivedFrom.empty())) {
                    if (var.isPrivate())
                        checkPublicFunctions(scope, var.nameToken());

                    variable(scope, var.nameToken());
                }
            }
        }
    }
}


void CheckMemoryLeakInClass::variable(const Scope *scope, const Token *tokVarname)
{
    const std::string& varname = tokVarname->str();
    const int varid = tokVarname->varId();
    const std::string& classname = scope->className;

    // Check if member variable has been allocated and deallocated..
    CheckMemoryLeak::AllocType memberAlloc = CheckMemoryLeak::No;
    CheckMemoryLeak::AllocType memberDealloc = CheckMemoryLeak::No;

    bool allocInConstructor = false;
    bool deallocInDestructor = false;

    // Inspect member functions
    for (const Function &func : scope->functionList) {
        const bool constructor = func.isConstructor();
        const bool destructor = func.isDestructor();
        if (!func.hasBody()) {
            if (destructor && !func.isDefault()) { // implementation for destructor is not seen and not defaulted => assume it deallocates all variables properly
                deallocInDestructor = true;
                memberDealloc = CheckMemoryLeak::Many;
            }
            continue;
        }
        bool body = false;
        const Token *end = func.functionScope->bodyEnd;
        for (const Token *tok = func.arg->link(); tok != end; tok = tok->next()) {
            if (tok == func.functionScope->bodyStart)
                body = true;
            else {
                if (!body) {
                    if (!match28(tok, varid))
                        continue;
                }

                // Allocate..
                if (!body || match29(tok, varid)) {
                    // var1 = var2 = ...
                    // bail out
                    if (tok->strAt(-1) == MatchCompiler::makeConstString("="))
                        return;

                    // Foo::var1 = ..
                    // bail out when not same class
                    if (tok->strAt(-1) == MatchCompiler::makeConstString("::") &&
                        tok->strAt(-2) != scope->className)
                        return;

                    const Token* allocTok = tok->tokAt(body ? 2 : 3);
                    if (tok->astParent() && tok->astParent()->str() == MatchCompiler::makeConstString("[") && tok->astParent()->astParent())
                        allocTok = tok->astParent()->astParent()->astOperand2();

                    AllocType alloc = getAllocationType(allocTok, 0);
                    if (alloc != CheckMemoryLeak::No) {
                        if (constructor)
                            allocInConstructor = true;

                        if (memberAlloc != No && memberAlloc != alloc)
                            alloc = CheckMemoryLeak::Many;

                        if (alloc != CheckMemoryLeak::Many && memberDealloc != CheckMemoryLeak::No && memberDealloc != CheckMemoryLeak::Many && memberDealloc != alloc) {
                            mismatchAllocDealloc({tok}, classname + "::" + varname);
                        }

                        memberAlloc = alloc;
                    }
                }

                if (!body)
                    continue;

                // Deallocate..
                AllocType dealloc = getDeallocationType(tok, varid);
                // some usage in the destructor => assume it's related
                // to deallocation
                if (destructor && tok->str() == varname)
                    dealloc = CheckMemoryLeak::Many;
                if (dealloc != CheckMemoryLeak::No) {
                    if (destructor)
                        deallocInDestructor = true;

                    if (dealloc != CheckMemoryLeak::Many && memberAlloc != CheckMemoryLeak::No && memberAlloc != Many && memberAlloc != dealloc) {
                        mismatchAllocDealloc({tok}, classname + "::" + varname);
                    }

                    // several types of allocation/deallocation?
                    if (memberDealloc != CheckMemoryLeak::No && memberDealloc != dealloc)
                        dealloc = CheckMemoryLeak::Many;

                    memberDealloc = dealloc;
                }

                // Function call .. possible deallocation
                else if (match30(tok->previous()) && !tok->isKeyword() && !mSettings->library.isLeakIgnore(tok->str())) {
                    return;
                }
            }
        }
    }

    if (allocInConstructor && !deallocInDestructor) {
        unsafeClassError(tokVarname, classname, classname + "::" + varname /*, memberAlloc*/);
    } else if (memberAlloc != CheckMemoryLeak::No && memberDealloc == CheckMemoryLeak::No) {
        unsafeClassError(tokVarname, classname, classname + "::" + varname /*, memberAlloc*/);
    }
}

void CheckMemoryLeakInClass::unsafeClassError(const Token *tok, const std::string &classname, const std::string &varname)
{
    if (!mSettings->severity.isEnabled(Severity::style) && !mSettings->isPremiumEnabled("unsafeClassCanLeak"))
        return;

    reportError(tok, Severity::style, "unsafeClassCanLeak",
                "$symbol:" + classname + "\n"
                "$symbol:" + varname + "\n"
                "Class '" + classname + "' is unsafe, '" + varname + "' can leak by wrong usage.\n"
                "The class '" + classname + "' is unsafe, wrong usage can cause memory/resource leaks for '" + varname + "'. This can for instance be fixed by adding proper cleanup in the destructor.", CWE398, Certainty::normal);
}


void CheckMemoryLeakInClass::checkPublicFunctions(const Scope *scope, const Token *classtok)
{
    // Check that public functions deallocate the pointers that they allocate.
    // There is no checking how these functions are used and therefore it
    // isn't established if there is real leaks or not.
    if (!mSettings->severity.isEnabled(Severity::warning))
        return;

    const int varid = classtok->varId();

    // Parse public functions..
    // If they allocate member variables, they should also deallocate
    for (const Function &func : scope->functionList) {
        if ((func.type == FunctionType::eFunction || func.type == FunctionType::eOperatorEqual) &&
            func.access == AccessControl::Public && func.hasBody()) {
            const Token *tok2 = func.functionScope->bodyStart->next();
            if (match16(tok2, varid)) {
                const CheckMemoryLeak::AllocType alloc = getAllocationType(tok2->tokAt(2), varid);
                if (alloc != CheckMemoryLeak::No)
                    publicAllocationError(tok2, tok2->str());
            } else if (match31(tok2, varid) &&
                       tok2->str() == scope->className) {
                const CheckMemoryLeak::AllocType alloc = getAllocationType(tok2->tokAt(4), varid);
                if (alloc != CheckMemoryLeak::No)
                    publicAllocationError(tok2, tok2->strAt(2));
            }
        }
    }
}

void CheckMemoryLeakInClass::publicAllocationError(const Token *tok, const std::string &varname)
{
    reportError(tok, Severity::warning, "publicAllocationError", "$symbol:" + varname + "\nPossible leak in public function. The pointer '$symbol' is not deallocated before it is allocated.", CWE398, Certainty::normal);
}

void CheckMemoryLeakInClass::runChecks(const Tokenizer &tokenizer, ErrorLogger *errorLogger)
{
    if (!tokenizer.isCPP())
        return;

    CheckMemoryLeakInClass checkMemoryLeak(&tokenizer, &tokenizer.getSettings(), errorLogger);
    checkMemoryLeak.check();
}

void CheckMemoryLeakInClass::getErrorMessages(ErrorLogger *e, const Settings *settings) const
{
    CheckMemoryLeakInClass c(nullptr, settings, e);
    c.publicAllocationError(nullptr, "varname");
    c.unsafeClassError(nullptr, "class", "class::varname");
}


void CheckMemoryLeakStructMember::check()
{
    if (mSettings->clang)
        return;

    logChecker("CheckMemoryLeakStructMember::check");

    const SymbolDatabase* symbolDatabase = mTokenizer->getSymbolDatabase();
    for (const Variable* var : symbolDatabase->variableList()) {
        if (!var || (!var->isLocal() && !(var->isArgument() && var->scope())) || var->isStatic())
            continue;
        if (var->isReference() || (var->valueType() && var->valueType()->pointer > 1))
            continue;
        if (var->typeEndToken()->isStandardType())
            continue;
        checkStructVariable(var);
    }
}

bool CheckMemoryLeakStructMember::isMalloc(const Variable *variable) const
{
    if (!variable)
        return false;
    const int declarationId(variable->declarationId());
    bool alloc = false;
    for (const Token *tok2 = variable->nameToken(); tok2 && tok2 != variable->scope()->bodyEnd; tok2 = tok2->next()) {
        if (match32(tok2, declarationId))
            return false;
        if (match33(tok2, declarationId) && mSettings->library.getAllocFuncInfo(tok2->tokAt(2)))
            alloc = true;
    }
    return alloc;
}

void CheckMemoryLeakStructMember::checkStructVariable(const Variable* const variable) const
{
    if (!variable)
        return;
    // Is struct variable a pointer?
    if (variable->isArrayOrPointer()) {
        // Check that variable is allocated with malloc
        if (!isMalloc(variable))
            return;
    } else if (!mTokenizer->isC() && (!variable->typeScope() || variable->typeScope()->getDestructor())) {
        // For non-C code a destructor might cleanup members
        return;
    }

    // Check struct..
    int indentlevel2 = 0;

    auto deallocInFunction = [this](const Token* tok, int structid) -> bool {
        // Calling non-function / function that doesn't deallocate?
        if (tok->isKeyword() || mSettings->library.isLeakIgnore(tok->str()))
            return false;

        // Check if the struct is used..
        bool deallocated = false;
        const Token* const end = tok->linkAt(1);
        for (const Token* tok2 = tok; tok2 != end; tok2 = tok2->next()) {
            if (match34(tok2, structid)) {
                /** @todo check if the function deallocates the memory */
                deallocated = true;
                break;
            }

            if (match35(tok2, structid)) {
                /** @todo check if the function deallocates the memory */
                deallocated = true;
                break;
            }
        }

        return deallocated;
    };

    // return { memberTok, rhsTok }
    auto isMemberAssignment = [](const Token* varTok, int varId) -> std::pair<const Token*, const Token*> {
        if (varTok->varId() != varId)
            return {};
        const Token* top = varTok;
        while (top->astParent()) {
            if (match36(top->astParent()))
                return {};
            top = top->astParent();
        }
        if (!match37(top) || !precedes(varTok, top))
            return {};
        const Token* dot = top->astOperand1();
        while (dot && dot->str() != MatchCompiler::makeConstString("."))
            dot = dot->astOperand1();
        if (!dot)
            return {};
        return { dot->astOperand2(), top->next() };
    };
    std::pair<const Token*, const Token*> assignToks;

    const Token* tokStart = variable->nameToken();
    if (variable->isArgument() && variable->scope())
        tokStart = variable->scope()->bodyStart->next();
    for (const Token *tok2 = tokStart; tok2 && tok2 != variable->scope()->bodyEnd; tok2 = tok2->next()) {
        if (tok2->str() == MatchCompiler::makeConstString("{"))
            ++indentlevel2;

        else if (tok2->str() == MatchCompiler::makeConstString("}")) {
            if (indentlevel2 == 0)
                break;
            --indentlevel2;
        }

        // Unknown usage of struct
        /** @todo Check how the struct is used. Only bail out if necessary */
        else if (match18(tok2, variable->declarationId()))
            break;

        // Struct member is allocated => check if it is also properly deallocated..
        else if ((assignToks = isMemberAssignment(tok2, variable->declarationId())).first && assignToks.first->varId()) {
            const AllocType allocType = getAllocationType(assignToks.second, assignToks.first->varId());
            if (allocType == AllocType::No)
                continue;

            if (variable->isArgument() && variable->valueType() && variable->valueType()->type == ValueType::UNKNOWN_TYPE && assignToks.first->astParent()) {
                const Token* accessTok = assignToks.first->astParent();
                while (match38(accessTok->astOperand1()))
                    accessTok = accessTok->astOperand1();
                if (match38(accessTok) && accessTok->originalName() == MatchCompiler::makeConstString("->"))
                    continue;
            }

            const int structid(variable->declarationId());
            const int structmemberid(assignToks.first->varId());

            // This struct member is allocated.. check that it is deallocated
            int indentlevel3 = indentlevel2;
            for (const Token *tok3 = tok2; tok3; tok3 = tok3->next()) {
                if (tok3->str() == MatchCompiler::makeConstString("{"))
                    ++indentlevel3;

                else if (tok3->str() == MatchCompiler::makeConstString("}")) {
                    if (indentlevel3 == 0) {
                        memoryLeak(tok3, variable->name() + "." + tok2->strAt(2), allocType);
                        break;
                    }
                    --indentlevel3;
                }

                // Deallocating the struct member..
                else if (getDeallocationType(tok3, structmemberid) != AllocType::No) {
                    // If the deallocation happens at the base level, don't check this member anymore
                    if (indentlevel3 == 0)
                        break;

                    // deallocating and then returning from function in a conditional block =>
                    // skip ahead out of the block
                    bool ret = false;
                    while (tok3) {
                        if (tok3->str() == MatchCompiler::makeConstString("return"))
                            ret = true;
                        else if (tok3->str() == MatchCompiler::makeConstString("{") || tok3->str() == MatchCompiler::makeConstString("}"))
                            break;
                        tok3 = tok3->next();
                    }
                    if (!ret || !tok3 || tok3->str() != MatchCompiler::makeConstString("}"))
                        break;
                    --indentlevel3;
                    continue;
                }

                // Deallocating the struct..
                else if (match39(tok3, structid) && mSettings->library.getDeallocFuncInfo(tok3)) {
                    if (indentlevel2 == 0)
                        memoryLeak(tok3, variable->name() + "." + tok2->strAt(2), allocType);
                    break;
                }

                // failed allocation => skip code..
                else if (match23(tok3) &&
                         notvar(tok3->next()->astOperand2(), structmemberid)) {
                    // Goto the ")"
                    tok3 = tok3->linkAt(1);

                    // make sure we have ") {".. it should be
                    if (!match40(tok3))
                        break;

                    // Goto the "}"
                    tok3 = tok3->linkAt(1);
                }

                // succeeded allocation
                else if (ifvar(tok3, structmemberid, "!=", "0")) {
                    // goto the ")"
                    tok3 = tok3->linkAt(1);

                    // check if the variable is deallocated or returned..
                    int indentlevel4 = 0;
                    for (const Token *tok4 = tok3; tok4; tok4 = tok4->next()) {
                        if (tok4->str() == MatchCompiler::makeConstString("{"))
                            ++indentlevel4;
                        else if (tok4->str() == MatchCompiler::makeConstString("}")) {
                            --indentlevel4;
                            if (indentlevel4 == 0)
                                break;
                        } else if (match41(tok4, structmemberid) && mSettings->library.getDeallocFuncInfo(tok4)) {
                            break;
                        }
                    }

                    // was there a proper deallocation?
                    if (indentlevel4 > 0)
                        break;
                }

                // Returning from function..
                else if ((tok3->scope()->type != ScopeType::eLambda || tok3->scope() == variable->scope()) && tok3->str() == MatchCompiler::makeConstString("return")) {
                    // Returning from function without deallocating struct member?
                    if (!match42(tok3, structid) &&
                        !match43(tok3, structid) &&
                        !(match44(tok3, structid) && tok3->tokAt(3)->varId() == structmemberid) &&
                        !(match45(tok3) && tok3->astOperand1() && deallocInFunction(tok3->astOperand1(), structid))) {
                        memoryLeak(tok3, variable->name() + "." + tok2->strAt(2), allocType);
                    }
                    break;
                }

                // struct assignment..
                else if (match17(tok3, structid)) {
                    break;
                } else if (match46(tok3, structmemberid)) {
                    break;
                }

                // goto isn't handled well.. bail out even though there might be leaks
                else if (tok3->str() == MatchCompiler::makeConstString("goto"))
                    break;

                // using struct in a function call..
                else if (match7(tok3)) {
                    if (deallocInFunction(tok3, structid))
                        break;
                }
            }
        }
    }
}

void CheckMemoryLeakStructMember::runChecks(const Tokenizer &tokenizer, ErrorLogger *errorLogger)
{
    CheckMemoryLeakStructMember checkMemoryLeak(&tokenizer, &tokenizer.getSettings(), errorLogger);
    checkMemoryLeak.check();
}

void CheckMemoryLeakStructMember::getErrorMessages(ErrorLogger * /*errorLogger*/, const Settings * /*settings*/) const
{}


void CheckMemoryLeakNoVar::check()
{
    logChecker("CheckMemoryLeakNoVar::check");

    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();

    // only check functions
    for (const Scope * scope : symbolDatabase->functionScopes) {

        // Checks if a call to an allocation function like malloc() is made and its return value is not assigned.
        checkForUnusedReturnValue(scope);

        // Checks to see if a function is called with memory allocated for an argument that
        // could be leaked if a function called for another argument throws.
        checkForUnsafeArgAlloc(scope);

        // Check for leaks where a the return value of an allocation function like malloc() is an input argument,
        // for example f(malloc(1)), where f is known to not release the input argument.
        checkForUnreleasedInputArgument(scope);
    }
}

//---------------------------------------------------------------------------
// Checks if an input argument to a function is the return value of an allocation function
// like malloc(), and the function does not release it.
//---------------------------------------------------------------------------
void CheckMemoryLeakNoVar::checkForUnreleasedInputArgument(const Scope *scope)
{
    // parse the executable scope until tok is reached...
    for (const Token *tok = scope->bodyStart; tok != scope->bodyEnd; tok = tok->next()) {
        // allocating memory in parameter for function call..
        if (tok->varId() || !match7(tok))
            continue;

        // check if the output of the function is assigned
        const Token* tok2 = tok->next()->astParent();
        while (tok2 && (tok2->isCast() || match47(tok2)))
            tok2 = tok2->astParent();
        if (match48(tok2)) // TODO: check if function returns allocated resource
            continue;
        if (match49(tok->astTop()))
            continue;

        const std::string& functionName = tok->str();
        if ((tok->isCpp() && functionName == MatchCompiler::makeConstString("delete")) ||
            functionName == MatchCompiler::makeConstString("return"))
            continue;

        if (match50(tok->next()->astParent())) // passed to another function
            continue;
        if (!tok->isKeyword() && !tok->function() && !mSettings->library.isLeakIgnore(functionName))
            continue;

        const std::vector<const Token *> args = getArguments(tok);
        int argnr = -1;
        for (const Token* arg : args) {
            ++argnr;
            if (arg->isOp() && !(tok->isKeyword() && arg->str() == MatchCompiler::makeConstString("*"))) // e.g. switch (*new int)
                continue;
            while (arg->astOperand1()) {
                if (arg->isCpp() && match51(arg))
                    break;
                arg = arg->astOperand1();
            }
            const AllocType alloc = getAllocationType(arg, 0);
            if (alloc == No)
                continue;
            if (alloc == New || alloc == NewArray) {
                const Token* typeTok = arg->next();
                bool bail = !typeTok->isStandardType() &&
                            !mSettings->library.detectContainerOrIterator(typeTok) &&
                            !mSettings->library.podtype(typeTok->expressionString());
                if (bail && typeTok->type() && typeTok->type()->classScope &&
                    typeTok->type()->classScope->numConstructors == 0 &&
                    typeTok->type()->classScope->getDestructor() == nullptr) {
                    bail = false;
                }
                if (bail)
                    continue;
            }
            if (isReopenStandardStream(arg))
                continue;
            if (tok->function()) {
                const Variable* argvar = tok->function()->getArgumentVar(argnr);
                if (!argvar || !argvar->valueType())
                    continue;
                const MathLib::bigint argSize = argvar->valueType()->typeSize(mSettings->platform, /*p*/ true);
                if (argSize <= 0 || argSize >= mSettings->platform.sizeof_pointer)
                    continue;
            }
            functionCallLeak(arg, arg->str(), functionName);
        }

    }
}

//---------------------------------------------------------------------------
// Checks if a call to an allocation function like malloc() is made and its return value is not assigned.
//---------------------------------------------------------------------------
void CheckMemoryLeakNoVar::checkForUnusedReturnValue(const Scope *scope)
{
    for (const Token *tok = scope->bodyStart; tok != scope->bodyEnd; tok = tok->next()) {
        const bool isNew = tok->isCpp() && tok->str() == MatchCompiler::makeConstString("new");
        if (!isNew && !match7(tok))
            continue;

        if (tok->varId())
            continue;

        const AllocType allocType = getAllocationType(tok, 0);
        if (allocType == No)
            continue;

        if (tok != tok->next()->astOperand1() && !isNew)
            continue;

        if (isReopenStandardStream(tok))
            continue;
        if (isOpenDevNull(tok))
            continue;

        // get ast parent, skip casts
        const Token *parent = isNew ? tok->astParent() : tok->next()->astParent();
        while (parent && parent->isCast())
            parent = parent->astParent();

        bool warn = true;
        if (isNew) {
            const Token* typeTok = tok->next();
            warn = typeTok && (typeTok->isStandardType() || mSettings->library.detectContainer(typeTok));
        }

        if (!parent && warn) {
            // Check if we are in a C++11 constructor
            const Token * closingBrace = findmatch52(tok) ;
            if (closingBrace->str() == MatchCompiler::makeConstString("}") && match53(closingBrace->link()->tokAt(-1)) && (!isNew && precedes(tok, closingBrace->link())))
                continue;
            returnValueNotUsedError(tok, tok->str());
        } else if (match54(parent)) {
            if (parent->astParent() && parent->str() == MatchCompiler::makeConstString(","))
                continue;
            if (parent->str() == MatchCompiler::makeConstString(":")) {
                if (!(match55(parent->astParent()) && !parent->astParent()->astParent()))
                    continue;
            }
            if (tok->str() == MatchCompiler::makeConstString("freopen"))
                continue;
            returnValueNotUsedError(tok, tok->str());
        }
    }
}

//---------------------------------------------------------------------------
// Check if an exception could cause a leak in an argument constructed with
// shared_ptr/unique_ptr. For example, in the following code, it is possible
// that if g() throws an exception, the memory allocated by "new int(42)"
// could be leaked. See stackoverflow.com/questions/19034538/
// why-is-there-memory-leak-while-using-shared-ptr-as-a-function-parameter
//
// void x() {
//    f(shared_ptr<int>(new int(42)), g());
// }
//---------------------------------------------------------------------------
void CheckMemoryLeakNoVar::checkForUnsafeArgAlloc(const Scope *scope)
{
    // This test only applies to C++ source
    if (!mTokenizer->isCPP())
        return;

    if (!mSettings->isPremiumEnabled("leakUnsafeArgAlloc") && (!mSettings->certainty.isEnabled(Certainty::inconclusive) || !mSettings->severity.isEnabled(Severity::warning)))
        return;

    logChecker("CheckMemoryLeakNoVar::checkForUnsafeArgAlloc");

    for (const Token *tok = scope->bodyStart; tok != scope->bodyEnd; tok = tok->next()) {
        if (match7(tok)) {
            const Token *endParamToken = tok->linkAt(1);
            const Token* pointerType = nullptr;
            const Token* functionCalled = nullptr;

            // Scan through the arguments to the function call
            for (const Token *tok2 = tok->tokAt(2); tok2 && tok2 != endParamToken; tok2 = tok2->nextArgument()) {
                const Function *func = tok2->function();
                const bool isNothrow = func && (func->isAttributeNothrow() || func->isThrow());

                if (match56(tok2) && match57(tok2->linkAt(1))) {
                    pointerType = tok2;
                } else if (!isNothrow) {
                    if (match7(tok2))
                        functionCalled = tok2;
                    else if (tok2->isName() && match58(tok2->linkAt(1)))
                        functionCalled = tok2;
                }
            }

            if (pointerType && functionCalled) {
                std::string functionName = functionCalled->str();
                if (functionCalled->strAt(1) == MatchCompiler::makeConstString("<")) {
                    functionName += '<';
                    for (const Token* tok2 = functionCalled->tokAt(2); tok2 != functionCalled->linkAt(1); tok2 = tok2->next())
                        functionName += tok2->str();
                    functionName += '>';
                }
                std::string objectTypeName;
                for (const Token* tok2 = pointerType->tokAt(2); tok2 != pointerType->linkAt(1); tok2 = tok2->next())
                    objectTypeName += tok2->str();

                unsafeArgAllocError(tok, functionName, pointerType->str(), objectTypeName);
            }
        }
    }
}

void CheckMemoryLeakNoVar::functionCallLeak(const Token *loc, const std::string &alloc, const std::string &functionCall)
{
    reportError(loc, Severity::error, "leakNoVarFunctionCall", "Allocation with " + alloc + ", " + functionCall + " doesn't release it.", CWE772, Certainty::normal);
}

void CheckMemoryLeakNoVar::returnValueNotUsedError(const Token *tok, const std::string &alloc)
{
    reportError(tok, Severity::error, "leakReturnValNotUsed", "$symbol:" + alloc + "\nReturn value of allocation function '$symbol' is not stored.", CWE771, Certainty::normal);
}

void CheckMemoryLeakNoVar::unsafeArgAllocError(const Token *tok, const std::string &funcName, const std::string &ptrType, const std::string& objType)
{
    const std::string factoryFunc = ptrType == MatchCompiler::makeConstString("shared_ptr") ? "make_shared" : "make_unique";
    reportError(tok, Severity::warning, "leakUnsafeArgAlloc",
                "$symbol:" + funcName + "\n"
                "Unsafe allocation. If $symbol() throws, memory could be leaked. Use " + factoryFunc + "<" + objType + ">() instead.",
                CWE401,
                Certainty::inconclusive); // Inconclusive because funcName may never throw
}

void CheckMemoryLeakNoVar::runChecks(const Tokenizer &tokenizer, ErrorLogger *errorLogger)
{
    CheckMemoryLeakNoVar checkMemoryLeak(&tokenizer, &tokenizer.getSettings(), errorLogger);
    checkMemoryLeak.check();
}

void CheckMemoryLeakNoVar::getErrorMessages(ErrorLogger *e, const Settings *settings) const
{
    CheckMemoryLeakNoVar c(nullptr, settings, e);
    c.functionCallLeak(nullptr, "funcName", "funcName");
    c.returnValueNotUsedError(nullptr, "funcName");
    c.unsafeArgAllocError(nullptr, "funcName", "shared_ptr", "int");
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
