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
// pattern: sizeof
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    return true;
}
// pattern: %var% . release ( )
MAYBE_UNUSED static inline bool match2(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("release")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: %var% =
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: %var% [=({] new
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("=({", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    return true;
}
// pattern: =
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: %var% {|(
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: [;{},]
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{},", tok->str()[0]))
        return false;
    return true;
}
// pattern: [;{},] %var% [
MAYBE_UNUSED static inline bool match8(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(";{},", tok->str()[0]))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: %name% (
MAYBE_UNUSED static inline bool match9(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: const %type%
MAYBE_UNUSED static inline bool match10(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("const")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: %name% ::|. %name% !!(
MAYBE_UNUSED static inline bool match11(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    return true;
}
// pattern: %name% :: %name%
MAYBE_UNUSED static inline bool match12(const Token* tok) {
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
// pattern: (|*|&|.
MAYBE_UNUSED static inline bool match13(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    return true;
}
// pattern: = %var% +|;|?|%comp%
MAYBE_UNUSED static inline bool match14(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || (tok->str() == MatchCompiler::makeConstString(";")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?")) || tok->isComparisonOp()))
        return false;
    return true;
}
// pattern: %type% (
MAYBE_UNUSED static inline bool match15(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: new !!(
MAYBE_UNUSED static inline bool match16(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("("))
        return false;
    return true;
}
// pattern: (|{
MAYBE_UNUSED static inline bool match17(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: %num% ;
MAYBE_UNUSED static inline bool match18(const Token* tok) {
    if (!tok || !tok->isNumber())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: - %type% ;
MAYBE_UNUSED static inline bool match19(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: if (
MAYBE_UNUSED static inline bool match20(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) {
MAYBE_UNUSED static inline bool match21(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ,
MAYBE_UNUSED static inline bool match22(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: UNLIKELY|LIKELY
MAYBE_UNUSED static inline bool match23(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("UNLIKELY")) || (tok->str() == MatchCompiler::makeConstString("LIKELY"))))
        return false;
    return true;
}
// pattern: } else {
MAYBE_UNUSED static inline bool match24(const Token* tok) {
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
// pattern: do {
MAYBE_UNUSED static inline bool match25(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: .
MAYBE_UNUSED static inline bool match26(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: [ ]
MAYBE_UNUSED static inline bool match27(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    return true;
}
// pattern: %name% ::|.
MAYBE_UNUSED static inline bool match28(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    return true;
}
// pattern: %name% ,
MAYBE_UNUSED static inline bool match29(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: ) ; }
MAYBE_UNUSED static inline bool match30(const Token* tok) {
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
// pattern: ( )
MAYBE_UNUSED static inline bool match31(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: continue|break ;
MAYBE_UNUSED static inline bool match32(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("continue")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("break"))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: %name% <
MAYBE_UNUSED static inline bool match33(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: > %var% {|( %var% ,|)|}
MAYBE_UNUSED static inline bool match34(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: [ ]
template<class T> MAYBE_UNUSED static inline T * findmatch35(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        continue;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: unique_ptr < %type% ,
MAYBE_UNUSED static inline bool match36(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("unique_ptr")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: > %var% {|( %var% ,
MAYBE_UNUSED static inline bool match37(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: & %name%
template<class T> MAYBE_UNUSED static inline T * findmatch38(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        continue;
    tok = tok->next();
    if (!tok || !tok->isName())
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: ] (
MAYBE_UNUSED static inline bool match39(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("]")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %type%
template<class T> MAYBE_UNUSED static inline T * findmatch40(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: %var% .
MAYBE_UNUSED static inline bool match41(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: = &
MAYBE_UNUSED static inline bool match42(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    return true;
}
// pattern: & %name% = %var% ;
MAYBE_UNUSED static inline bool match43(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: return
MAYBE_UNUSED static inline bool match44(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")))
        return false;
    return true;
}
// pattern: * new
MAYBE_UNUSED static inline bool match45(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("new")))
        return false;
    return true;
}
// pattern: ( std :: nothrow )
MAYBE_UNUSED static inline bool match46(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("std")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("nothrow")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: %name% .|:: %name%
MAYBE_UNUSED static inline bool match47(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %var% [-,)] !!.
MAYBE_UNUSED static inline bool match48(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("-,)", tok->str()[0]))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("."))
        return false;
    return true;
}
// pattern: & %var% !!.
MAYBE_UNUSED static inline bool match49(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("."))
        return false;
    return true;
}
// pattern: %name% < %type%
MAYBE_UNUSED static inline bool match50(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    return true;
}
// pattern: > {|( %var% ,|)|}
MAYBE_UNUSED static inline bool match51(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: > {|( %var% ,
MAYBE_UNUSED static inline bool match52(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: return|(|{|,|*
MAYBE_UNUSED static inline bool match53(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: & %varid% . %name%
MAYBE_UNUSED static inline bool match54(const Token* tok, const int varid) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
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
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: *
MAYBE_UNUSED static inline bool match55(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: [});,+]
MAYBE_UNUSED static inline bool match56(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("});,+", tok->str()[0]))
        return false;
    return true;
}
// pattern: [|.|*
MAYBE_UNUSED static inline bool match57(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || (tok->str() == MatchCompiler::makeConstString(".")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: %comp%
MAYBE_UNUSED static inline bool match58(const Token* tok) {
    if (!tok || !tok->isComparisonOp())
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/checkleakautovar.cpp"
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
// Leaks when using auto variables
//---------------------------------------------------------------------------

#include "checkleakautovar.h"

#include "astutils.h"
#include "checkmemoryleak.h"  // <- CheckMemoryLeak::memoryLeak
#include "checknullpointer.h" // <- CheckNullPointer::isPointerDeRef
#include "mathlib.h"
#include "platform.h"
#include "settings.h"
#include "errortypes.h"
#include "symboldatabase.h"
#include "token.h"
#include "tokenize.h"
#include "tokenlist.h"
#include "utils.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <list>
#include <vector>

//---------------------------------------------------------------------------

// Register this check class (by creating a static instance of it)
namespace {
    CheckLeakAutoVar instance;
}

static const CWE CWE672(672U);
static const CWE CWE415(415U);

// Hardcoded allocation types (not from library)
static constexpr int NEW_ARRAY = -2;
static constexpr int NEW = -1;

static const std::array<std::pair<std::string, std::string>, 4> alloc_failed_conds {{{"==", "0"}, {"<", "0"}, {"==", "-1"}, {"<=", "-1"}}};
static const std::array<std::pair<std::string, std::string>, 5> alloc_success_conds {{{"!=", "0"}, {">", "0"}, {"!=", "-1"}, {">=", "0"}, {">", "-1"}}};

static bool isAutoDeallocType(const Type* type) {
    if (!type || !type->classScope)
        return true;
    if (type->classScope->numConstructors > 0)
        return true;
    const std::list<Variable>& varlist = type->classScope->varlist;
    if (std::any_of(varlist.begin(), varlist.end(), [](const Variable& v) {
        return !v.valueType() || (!v.valueType()->isPrimitive() && !v.valueType()->container);
    }))
        return true;
    if (std::none_of(type->derivedFrom.cbegin(), type->derivedFrom.cend(), [](const Type::BaseInfo& bi) {
        return isAutoDeallocType(bi.type);
    }))
        return false;
    return true;
}

/**
 * @brief Is variable type some class with automatic deallocation?
 * @param var variable token
 * @return true unless it can be seen there is no automatic deallocation
 */
static bool isAutoDealloc(const Variable *var)
{
    if (var->valueType() && var->valueType()->type != ValueType::Type::RECORD && var->valueType()->type != ValueType::Type::UNKNOWN_TYPE)
        return false;

    // return false if the type is a simple record type without side effects
    // a type that has no side effects (no constructors and no members with constructors)
    /** @todo false negative: check constructors for side effects */
    return isAutoDeallocType(var->type());
}

template<std::size_t N>
static bool isVarTokComparison(const Token * tok, const Token ** vartok,
                               const std::array<std::pair<std::string, std::string>, N>& ops)
{
    return std::any_of(ops.cbegin(), ops.cend(), [&](const std::pair<std::string, std::string>& op) {
        return astIsVariableComparison(tok, op.first, op.second, vartok);
    });
}

//---------------------------------------------------------------------------

void VarInfo::possibleUsageAll(const std::pair<const Token*, Usage>& functionUsage)
{
    possibleUsage.clear();
    for (auto it = alloctype.cbegin(); it != alloctype.cend(); ++it)
        possibleUsage[it->first] = functionUsage;
}


void CheckLeakAutoVar::leakError(const Token *tok, const std::string &varname, int type) const
{
    const CheckMemoryLeak checkmemleak(mTokenizer, mErrorLogger, mSettings);
    if (Library::isresource(type))
        checkmemleak.resourceLeakError(tok, varname);
    else
        checkmemleak.memleakError(tok, varname);
}

void CheckLeakAutoVar::mismatchError(const Token *deallocTok, const Token *allocTok, const std::string &varname) const
{
    const CheckMemoryLeak c(mTokenizer, mErrorLogger, mSettings);
    const std::list<const Token *> callstack = { allocTok, deallocTok };
    c.mismatchAllocDealloc(callstack, varname);
}

void CheckLeakAutoVar::deallocUseError(const Token *tok, const std::string &varname) const
{
    const CheckMemoryLeak c(mTokenizer, mErrorLogger, mSettings);
    c.deallocuseError(tok, varname);
}

void CheckLeakAutoVar::deallocReturnError(const Token *tok, const Token *deallocTok, const std::string &varname)
{
    const std::list<const Token *> locations = { deallocTok, tok };
    reportError(locations, Severity::error, "deallocret", "$symbol:" + varname + "\nReturning/dereferencing '$symbol' after it is deallocated / released", CWE672, Certainty::normal);
}

void CheckLeakAutoVar::configurationInfo(const Token* tok, const std::pair<const Token*, VarInfo::Usage>& functionUsage)
{
    if (mSettings->checkLibrary && functionUsage.second == VarInfo::USED &&
        (!functionUsage.first || !functionUsage.first->function() || !functionUsage.first->function()->hasBody())) {
        std::string funcStr = functionUsage.first ? mSettings->library.getFunctionName(functionUsage.first) : "f";
        if (funcStr.empty())
            funcStr = "unknown::" + functionUsage.first->str();
        reportError(tok,
                    Severity::information,
                    "checkLibraryUseIgnore",
                    "--check-library: Function " + funcStr + "() should have <use>/<leak-ignore> configuration");
    }
}

void CheckLeakAutoVar::doubleFreeError(const Token *tok, const Token *prevFreeTok, const std::string &varname, int type)
{
    const std::list<const Token *> locations = { prevFreeTok, tok };

    if (Library::isresource(type))
        reportError(locations, Severity::error, "doubleFree", "$symbol:" + varname + "\nResource handle '$symbol' freed twice.", CWE415, Certainty::normal);
    else
        reportError(locations, Severity::error, "doubleFree", "$symbol:" + varname + "\nMemory pointed to by '$symbol' is freed twice.", CWE415, Certainty::normal);
}


void CheckLeakAutoVar::check()
{
    if (mSettings->clang)
        return;

    logChecker("CheckLeakAutoVar::check"); // notclang

    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();

    // Local variables that are known to be non-zero.
    const std::set<int> notzero;

    // Check function scopes
    for (const Scope * scope : symbolDatabase->functionScopes) {
        if (scope->hasInlineOrLambdaFunction())
            continue;

        // Empty variable info
        VarInfo varInfo;

        checkScope(scope->bodyStart, varInfo, notzero, 0);
    }
}

static bool isVarUsedInTree(const Token *tok, nonneg int varid)
{
    if (!tok)
        return false;
    if (tok->varId() == varid)
        return true;
    if (tok->str() == MatchCompiler::makeConstString("(") && match1(tok->astOperand1()))
        return false;
    return isVarUsedInTree(tok->astOperand1(), varid) || isVarUsedInTree(tok->astOperand2(), varid);
}

static bool isPointerReleased(const Token *startToken, const Token *endToken, nonneg int varid)
{
    for (const Token *tok = startToken; tok && tok != endToken; tok = tok->next()) {
        if (tok->varId() != varid)
            continue;
        if (match2(tok))
            return true;
        if (match3(tok))
            return false;
    }
    return false;
}

static bool isLocalVarNoAutoDealloc(const Token *varTok)
{
    // not a local variable nor argument?
    const Variable *var = varTok->variable();
    if (!var)
        return true;
    if (!var->isArgument() && (!var->isLocal() || var->isStatic()))
        return false;

    // Don't check reference variables
    if (var->isReference() && !var->isArgument())
        return false;

    // non-pod variable
    if (varTok->isCpp()) {
        // Possibly automatically deallocated memory
        if (isAutoDealloc(var) && match4(varTok))
            return false;
        if (!var->isPointer() && !var->typeStartToken()->isStandardType())
            return false;
    }
    return true;
}

/** checks if nameToken is a name of a function in a function call:
 *     func(arg)
 * or
 *     func<temp1_arg>(arg)
 * @param nameToken Function name token
 * @return opening parenthesis token or NULL if not a function call
 */

static const Token * isFunctionCall(const Token * nameToken)
{
    if (!nameToken->isStandardType() && nameToken->isName()) {
        nameToken = nameToken->next();
        // check if function is a template
        if (nameToken && nameToken->link() && nameToken->str() == MatchCompiler::makeConstString("<")) {
            // skip template arguments
            nameToken = nameToken->link()->next();
        }
        // check for '('
        if (nameToken && nameToken->link() && !nameToken->isCast() && nameToken->str() == MatchCompiler::makeConstString("(")) {
            // returning opening parenthesis pointer
            return nameToken;
        }
    }
    return nullptr;
}

static const Token* getOutparamAllocation(const Token* tok, const Settings& settings)
{
    if (!tok)
        return nullptr;
    int argn{};
    const Token* ftok = getTokenArgumentFunction(tok, argn);
    if (!ftok)
        return nullptr;
    if (const Library::AllocFunc* allocFunc = settings.library.getAllocFuncInfo(ftok)) {
        if (allocFunc->arg == argn + 1)
            return ftok;
    }
    return nullptr;
}

static const Token* getReturnValueFromOutparamAlloc(const Token* alloc, const Settings& settings)
{
    if (const Token* ftok = getOutparamAllocation(alloc, settings)) {
        if (match5(ftok->astParent()->astParent()))
            return ftok->next()->astParent()->astOperand1();
    }
    return nullptr;
}

bool CheckLeakAutoVar::checkScope(const Token * const startToken,
                                  VarInfo &varInfo,
                                  std::set<int> notzero,
                                  nonneg int recursiveCount)
{
#if ASAN
    static const nonneg int recursiveLimit = 300;
#elif defined(__MINGW32__)
    // testrunner crashes with stack overflow in CI
    static constexpr nonneg int recursiveLimit = 600;
#else
    static constexpr nonneg int recursiveLimit = 1000;
#endif
    if (++recursiveCount > recursiveLimit)    // maximum number of "else if ()"
        throw InternalError(startToken, "Internal limit: CheckLeakAutoVar::checkScope() Maximum recursive count of 1000 reached.", InternalError::LIMIT);

    std::map<int, VarInfo::AllocInfo> &alloctype = varInfo.alloctype;
    auto& possibleUsage = varInfo.possibleUsage;
    const std::set<int> conditionalAlloc(varInfo.conditionalAlloc);

    // Parse all tokens
    const Token * const endToken = startToken->link();
    for (const Token *tok = startToken; tok && tok != endToken; tok = tok->next()) {
        if (!tok->scope()->isExecutable()) {
            tok = tok->scope()->bodyEnd;
            if (!tok) // Ticket #6666 (crash upon invalid code)
                break;
        }

        // check each token
        {
            const bool isInit = match6(tok) && tok->variable() && tok == tok->variable()->nameToken() && tok->variable()->isPointer();
            const Token * nextTok = isInit ? nullptr : checkTokenInsideExpression(tok, varInfo);
            if (nextTok) {
                tok = nextTok;
                continue;
            }
        }


        // look for end of statement
        const bool isInit = match6(tok->tokAt(-1)) && tok->tokAt(-1)->variable() && tok->tokAt(-1) == tok->tokAt(-1)->variable()->nameToken();
        if ((!match7(tok) || match7(tok->next())) && !(isInit && tok->str() == MatchCompiler::makeConstString("(")))
            continue;

        if (match8(tok))
            continue;

        if (!isInit)
            tok = tok->next();
        if (!tok || tok == endToken)
            break;

        if (match9(tok) && isUnevaluated(tok)) {
            tok = tok->linkAt(1);
            continue;
        }

        if (match10(tok))
            tok = tok->tokAt(2);

        while (!isInit && tok->str() == MatchCompiler::makeConstString("("))
            tok = tok->next();
        while (tok->isUnaryOp("*") && tok->astOperand1()->isUnaryOp("&"))
            tok = tok->astOperand1()->astOperand1();

        // parse statement, skip to last member
        const Token* varTok = isInit ? tok->tokAt(-1) : tok;
        while (match11(varTok))
            varTok = varTok->tokAt(2);

        const Token *ftok = tok;
        if (ftok->str() == MatchCompiler::makeConstString("::"))
            ftok = ftok->next();
        while (match12(ftok))
            ftok = ftok->tokAt(2);

        // bailout for variable passed to library function with out parameter
        if (const Library::Function *libFunc = mSettings->library.getFunction(ftok)) {
            using ArgumentChecks = Library::ArgumentChecks;
            using Direction = ArgumentChecks::Direction;
            const std::vector<const Token *> args = getArguments(ftok);
            const std::map<int, ArgumentChecks> &argChecks = libFunc->argumentChecks;
            bool hasOutParam = std::any_of(argChecks.cbegin(), argChecks.cend(), [](const std::pair<int, ArgumentChecks> &pair) {
                return std::any_of(pair.second.direction.cbegin(), pair.second.direction.cend(), [](const Direction dir) {
                    return dir == Direction::DIR_OUT;
                });
            });
            if (hasOutParam) {
                for (int i = 0; i < args.size(); i++) {
                    if (!argChecks.count(i + 1))
                        continue;
                    const ArgumentChecks argCheck = argChecks.at(i + 1);
                    const bool isInParam = std::any_of(argCheck.direction.cbegin(), argCheck.direction.cend(), [&](const Direction dir) {
                        return dir == Direction::DIR_IN;
                    });
                    if (!isInParam)
                        continue;
                    const Token *inTok = args[i];
                    int indirect = 0;
                    while (inTok->isUnaryOp("&")) {
                        inTok = inTok->astOperand1();
                        indirect++;
                    }
                    if (inTok->isVariable() && indirect) {
                        varInfo.erase(inTok->varId());
                    }
                }
            }
        }

        if (tok->isCpp11init() == Token::Cpp11init::CPP11INIT) {
            const Token *newTok = tok->astOperand1();
            const Token *oldTok = tok->astOperand2();
            if (newTok && newTok->varId() && oldTok && oldTok->varId()) {
                leakIfAllocated(newTok, varInfo);
                // no multivariable checking currently => bail out for rhs variables
                varInfo.erase(oldTok->varId());
            }
        }

        auto isAssignment = [](const Token* varTok) -> const Token* {
            if (varTok->varId()) {
                const Token* top = varTok;
                while (top->astParent()) {
                    top = top->astParent();
                    if (!match13(top))
                        break;
                }
                if (top->str() == MatchCompiler::makeConstString("=") && succeeds(top, varTok))
                    return top;
            }
            return nullptr;
        };

        // assignment..
        if (const Token* const tokAssignOp = isInit ? varTok : isAssignment(varTok)) {

            // taking address of another variable..
            if (match14(tokAssignOp)) {
                if (varTok->tokAt(2)->varId() != varTok->varId()) {
                    // If variable points at allocated memory => error
                    leakIfAllocated(varTok, varInfo);

                    // no multivariable checking currently => bail out for rhs variables
                    for (const Token *tok2 = varTok; tok2; tok2 = tok2->next()) {
                        if (tok2->str() == MatchCompiler::makeConstString(";")) {
                            break;
                        }
                        if (tok2->varId()) {
                            varInfo.erase(tok2->varId());
                        }
                    }
                }
            }

            // right ast part (after `=` operator)
            const Token* tokRightAstOperand = tokAssignOp->astOperand2();
            while (tokRightAstOperand && tokRightAstOperand->isCast())
                tokRightAstOperand = tokRightAstOperand->astOperand2() ? tokRightAstOperand->astOperand2() : tokRightAstOperand->astOperand1();

            // is variable used in rhs?
            if (isVarUsedInTree(tokRightAstOperand, varTok->varId()))
                continue;

            // Variable has already been allocated => error
            if (conditionalAlloc.find(varTok->varId()) == conditionalAlloc.end())
                leakIfAllocated(varTok, varInfo);
            varInfo.erase(varTok->varId());

            if (!isLocalVarNoAutoDealloc(varTok))
                continue;

            // allocation?
            const Token *const fTok = tokRightAstOperand ? tokRightAstOperand->previous() : nullptr;
            if (match15(fTok)) {
                const Library::AllocFunc* f = mSettings->library.getAllocFuncInfo(fTok);
                if (f && f->arg == -1) {
                    VarInfo::AllocInfo& varAlloc = alloctype[varTok->varId()];
                    varAlloc.type = f->groupId;
                    varAlloc.status = VarInfo::ALLOC;
                    varAlloc.allocTok = fTok;
                }

                changeAllocStatusIfRealloc(alloctype, fTok, varTok);
            } else if (varTok->isCpp() && match16(varTok->tokAt(2))) {
                const Token* tok2 = varTok->tokAt(2)->astOperand1();
                const bool arrayNew = (tok2 && (tok2->str() == MatchCompiler::makeConstString("[") || (match17(tok2) && tok2->astOperand1() && tok2->astOperand1()->str() == MatchCompiler::makeConstString("["))));
                VarInfo::AllocInfo& varAlloc = alloctype[varTok->varId()];
                varAlloc.type = arrayNew ? NEW_ARRAY : NEW;
                varAlloc.status = VarInfo::ALLOC;
                varAlloc.allocTok = varTok->tokAt(2);
            }

            // Assigning non-zero value variable. It might be used to
            // track the execution for a later if condition.
            if (match18(varTok->tokAt(2)) && MathLib::toBigNumber(varTok->tokAt(2)) != 0)
                notzero.insert(varTok->varId());
            else if (match19(varTok->tokAt(2)) && varTok->tokAt(3)->isUpperCaseName())
                notzero.insert(varTok->varId());
            else
                notzero.erase(varTok->varId());
        }

        // if/else
        else if (match20(tok)) {

            bool skipIfBlock = false;
            bool skipElseBlock = false;
            const Token *condTok = tok->astSibling();

            if (condTok && condTok->hasKnownIntValue()) {
                skipIfBlock = !condTok->getKnownIntValue();
                skipElseBlock = !skipIfBlock;
            }

            // Parse function calls inside the condition

            const Token * closingParenthesis = tok->linkAt(1);
            for (const Token *innerTok = tok->tokAt(2); innerTok && innerTok != closingParenthesis; innerTok = innerTok->next()) {
                if (isUnevaluated(innerTok)) {
                    innerTok = innerTok->linkAt(1);
                    continue;
                }
                // TODO: replace with checkTokenInsideExpression()
                const Token* const openingPar = isFunctionCall(innerTok);
                if (!openingPar)
                    checkTokenInsideExpression(innerTok, varInfo);

                if (!isLocalVarNoAutoDealloc(innerTok))
                    continue;

                // Check assignments in the if-statement. Skip multiple assignments since we don't track those
                if (match3(innerTok) && innerTok->astParent() == innerTok->next() &&
                    !(innerTok->next()->astParent() && innerTok->next()->astParent()->isAssignmentOp())) {
                    // allocation?
                    // right ast part (after `=` operator)
                    const Token* tokRightAstOperand = innerTok->next()->astOperand2();
                    while (tokRightAstOperand && tokRightAstOperand->isCast())
                        tokRightAstOperand = tokRightAstOperand->astOperand2() ? tokRightAstOperand->astOperand2() : tokRightAstOperand->astOperand1();
                    if (tokRightAstOperand && match15(tokRightAstOperand->previous())) {
                        const Token * fTok = tokRightAstOperand->previous();
                        const Library::AllocFunc* f = mSettings->library.getAllocFuncInfo(fTok);
                        if (f && f->arg == -1) {
                            VarInfo::AllocInfo& varAlloc = alloctype[innerTok->varId()];
                            varAlloc.type = f->groupId;
                            varAlloc.status = VarInfo::ALLOC;
                            varAlloc.allocTok = fTok;
                        } else {
                            // Fixme: warn about leak
                            alloctype.erase(innerTok->varId());
                        }
                        changeAllocStatusIfRealloc(alloctype, fTok, varTok);
                    } else if (innerTok->isCpp() && match16(innerTok->tokAt(2))) {
                        const Token* tok2 = innerTok->tokAt(2)->astOperand1();
                        const bool arrayNew = (tok2 && (tok2->str() == MatchCompiler::makeConstString("[") || (tok2->str() == MatchCompiler::makeConstString("(") && tok2->astOperand1() && tok2->astOperand1()->str() == MatchCompiler::makeConstString("["))));
                        VarInfo::AllocInfo& varAlloc = alloctype[innerTok->varId()];
                        varAlloc.type = arrayNew ? NEW_ARRAY : NEW;
                        varAlloc.status = VarInfo::ALLOC;
                        varAlloc.allocTok = innerTok->tokAt(2);
                    }
                }

                // check for function call
                if (openingPar) {
                    const Library::AllocFunc* allocFunc = mSettings->library.getDeallocFuncInfo(innerTok);
                    // innerTok is a function name
                    const VarInfo::AllocInfo allocation(0, VarInfo::NOALLOC);
                    functionCall(innerTok, openingPar, varInfo, allocation, allocFunc);
                    innerTok = openingPar->link();
                }
            }

            if (match21(closingParenthesis)) {
                VarInfo varInfo1(varInfo);  // VarInfo for if code
                VarInfo varInfo2(varInfo);  // VarInfo for else code

                // Skip expressions before commas
                const Token * astOperand2AfterCommas = tok->next()->astOperand2();
                while (match22(astOperand2AfterCommas))
                    astOperand2AfterCommas = astOperand2AfterCommas->astOperand2();

                // Recursively scan variable comparisons in condition
                visitAstNodes(astOperand2AfterCommas, [&](const Token *tok3) {
                    if (!tok3)
                        return ChildrenToVisit::none;
                    if (tok3->str() == MatchCompiler::makeConstString("&&") || tok3->str() == MatchCompiler::makeConstString("||")) {
                        // FIXME: handle && ! || better
                        return ChildrenToVisit::op1_and_op2;
                    }
                    if (tok3->str() == MatchCompiler::makeConstString("(") && match23(tok3->astOperand1())) {
                        return ChildrenToVisit::op2;
                    }
                    if (tok3->str() == MatchCompiler::makeConstString("(") && tok3->previous()->isName()) {
                        const std::vector<const Token *> params = getArguments(tok3->previous());
                        for (const Token *par : params) {
                            if (!par->isComparisonOp())
                                continue;
                            const Token *vartok = nullptr;
                            if (isVarTokComparison(par, &vartok, alloc_success_conds) ||
                                (isVarTokComparison(par, &vartok, alloc_failed_conds))) {
                                varInfo1.erase(vartok->varId());
                                varInfo2.erase(vartok->varId());
                            }
                        }
                        return ChildrenToVisit::none;
                    }

                    const Token *vartok = nullptr;
                    if (isVarTokComparison(tok3, &vartok, alloc_success_conds)) {
                        varInfo2.reallocToAlloc(vartok->varId());
                        varInfo2.erase(vartok->varId());
                        if (astIsVariableComparison(tok3, "!=", "0", &vartok) &&
                            (notzero.find(vartok->varId()) != notzero.end()))
                            varInfo2.clear();

                        if (std::any_of(varInfo1.alloctype.begin(), varInfo1.alloctype.end(), [&](const std::pair<int, VarInfo::AllocInfo>& info) {
                            if (info.second.status != VarInfo::ALLOC)
                                return false;
                            const Token* ret = getReturnValueFromOutparamAlloc(info.second.allocTok, *mSettings);
                            return ret && vartok && ret->varId() && ret->varId() == vartok->varId();
                        })) {
                            varInfo1.clear();
                        }
                    } else if (isVarTokComparison(tok3, &vartok, alloc_failed_conds)) {
                        varInfo1.reallocToAlloc(vartok->varId());
                        varInfo1.erase(vartok->varId());
                    }
                    return ChildrenToVisit::none;
                });

                if (!skipIfBlock && !checkScope(closingParenthesis->next(), varInfo1, notzero, recursiveCount)) {
                    varInfo.clear();
                    continue;
                }
                closingParenthesis = closingParenthesis->linkAt(1);
                if (match24(closingParenthesis)) {
                    if (!skipElseBlock && !checkScope(closingParenthesis->tokAt(2), varInfo2, notzero, recursiveCount)) {
                        varInfo.clear();
                        return false;
                    }
                    tok = closingParenthesis->linkAt(2)->previous();
                } else {
                    tok = closingParenthesis->previous();
                }

                VarInfo old;
                old.swap(varInfo);

                for (auto it = old.alloctype.cbegin(); it != old.alloctype.cend(); ++it) {
                    const int varId = it->first;
                    if (old.conditionalAlloc.find(varId) == old.conditionalAlloc.end())
                        continue;
                    if (varInfo1.alloctype.find(varId) == varInfo1.alloctype.end() ||
                        varInfo2.alloctype.find(varId) == varInfo2.alloctype.end()) {
                        varInfo1.erase(varId);
                        varInfo2.erase(varId);
                    }
                }

                // Conditional allocation in varInfo1
                for (auto it = varInfo1.alloctype.cbegin(); it != varInfo1.alloctype.cend(); ++it) {
                    if (varInfo2.alloctype.find(it->first) == varInfo2.alloctype.end() &&
                        old.alloctype.find(it->first) == old.alloctype.end()) {
                        varInfo.conditionalAlloc.insert(it->first);
                    }
                }

                // Conditional allocation in varInfo2
                for (auto it = varInfo2.alloctype.cbegin(); it != varInfo2.alloctype.cend(); ++it) {
                    if (varInfo1.alloctype.find(it->first) == varInfo1.alloctype.end() &&
                        old.alloctype.find(it->first) == old.alloctype.end()) {
                        varInfo.conditionalAlloc.insert(it->first);
                    }
                }

                // Conditional allocation/deallocation
                for (auto it = varInfo1.alloctype.cbegin(); it != varInfo1.alloctype.cend(); ++it) {
                    if (it->second.managed() && conditionalAlloc.find(it->first) != conditionalAlloc.end()) {
                        varInfo.conditionalAlloc.erase(it->first);
                        varInfo2.erase(it->first);
                    }
                }
                for (auto it = varInfo2.alloctype.cbegin(); it != varInfo2.alloctype.cend(); ++it) {
                    if (it->second.managed() && conditionalAlloc.find(it->first) != conditionalAlloc.end()) {
                        varInfo.conditionalAlloc.erase(it->first);
                        varInfo1.erase(it->first);
                    }
                }

                alloctype.insert(varInfo1.alloctype.cbegin(), varInfo1.alloctype.cend());
                alloctype.insert(varInfo2.alloctype.cbegin(), varInfo2.alloctype.cend());

                possibleUsage.insert(varInfo1.possibleUsage.cbegin(), varInfo1.possibleUsage.cend());
                possibleUsage.insert(varInfo2.possibleUsage.cbegin(), varInfo2.possibleUsage.cend());
            }
        }

        // unknown control.. (TODO: handle loops)
        else if ((match15(tok) && match21(tok->linkAt(1))) || match25(tok)) {
            varInfo.clear();
            return false;
        }

        // return
        else if (tok->str() == MatchCompiler::makeConstString("return")) {
            ret(tok, varInfo);
            varInfo.clear();
        }

        // throw
        else if (tok->isCpp() && tok->str() == MatchCompiler::makeConstString("throw")) {
            bool tryFound = false;
            const Scope* scope = tok->scope();
            while (scope && scope->isExecutable()) {
                if (scope->type == ScopeType::eTry)
                    tryFound = true;
                scope = scope->nestedIn;
            }
            // If the execution leaves the function then treat it as return
            if (!tryFound)
                ret(tok, varInfo);
            varInfo.clear();
        }

        // delete
        else if (tok->isCpp() && tok->str() == MatchCompiler::makeConstString("delete")) {
            const Token * delTok = tok;
            if (match26(delTok->astOperand1()))
                continue;
            const bool arrayDelete = match27(tok->next());
            if (arrayDelete)
                tok = tok->tokAt(3);
            else
                tok = tok->next();
            bool startparen;
            if ((startparen = (tok->str() == MatchCompiler::makeConstString("("))))
                tok = tok->next();
            while (match28(tok) || (startparen && match29(tok)))
                tok = tok->tokAt(2);
            const bool isnull = tok->hasKnownIntValue() && tok->getKnownIntValue() == 0;
            if (!isnull && tok->varId() && tok->strAt(1) != MatchCompiler::makeConstString("[")) {
                const VarInfo::AllocInfo allocation(arrayDelete ? NEW_ARRAY : NEW, VarInfo::DEALLOC, delTok);
                changeAllocStatus(varInfo, allocation, tok, tok);
            }
        }

        // Function call..
        else if (const Token* openingPar = isFunctionCall(ftok)) {
            const Library::AllocFunc* af = mSettings->library.getDeallocFuncInfo(ftok);
            VarInfo::AllocInfo allocation(af ? af->groupId : 0, VarInfo::DEALLOC, ftok);
            if (allocation.type == 0)
                allocation.status = VarInfo::NOALLOC;

            functionCall(ftok, openingPar, varInfo, allocation, af);

            tok = ftok->linkAt(1);

            // Handle scopes that might be noreturn
            if (allocation.status == VarInfo::NOALLOC && match30(tok)) {
                if (ftok->isKeyword())
                    continue;
                bool unknown = false;
                if (mTokenizer->isScopeNoReturn(tok->tokAt(2), &unknown)) {
                    if (!unknown)
                        varInfo.clear();
                    else {
                        if (ftok->function() && !ftok->function()->isAttributeNoreturn() &&
                            !(ftok->function()->functionScope && mTokenizer->isScopeNoReturn(ftok->function()->functionScope->bodyEnd))) // check function scope
                            continue;
                        const std::string functionName(mSettings->library.getFunctionName(ftok));
                        if (!mSettings->library.isLeakIgnore(functionName) && !mSettings->library.isUse(functionName)) {
                            const VarInfo::Usage usage = match31(openingPar) ? VarInfo::NORET : VarInfo::USED; // TODO: check parameters passed to function
                            varInfo.possibleUsageAll({ ftok, usage });
                        }
                    }
                }
            }

            continue;
        }

        // goto => weird execution path
        else if (tok->str() == MatchCompiler::makeConstString("goto")) {
            varInfo.clear();
            return false;
        }

        // continue/break
        else if (match32(tok)) {
            varInfo.clear();
        }

        // Check smart pointer
        else if (match33(ftok) && mSettings->library.isSmartPointer(tok)) {
            const Token * typeEndTok = ftok->linkAt(1);
            if (!match34(typeEndTok))
                continue;

            tok = typeEndTok->linkAt(2);

            const int varid = typeEndTok->next()->varId();
            if (isPointerReleased(typeEndTok->tokAt(2), endToken, varid))
                continue;

            bool arrayDelete = false;
            if (findmatch35(ftok->next(), typeEndTok) )
                arrayDelete = true;

            // Check deleter
            const Token * deleterToken = nullptr;
            const Token * endDeleterToken = nullptr;
            const Library::AllocFunc* af = nullptr;
            if (match36(ftok)) {
                deleterToken = ftok->tokAt(4);
                endDeleterToken = typeEndTok;
            } else if (match37(typeEndTok)) {
                deleterToken = typeEndTok->tokAt(5);
                endDeleterToken = typeEndTok->linkAt(2);
            }
            if (deleterToken) {
                // Skip the decaying plus in expressions like +[](T*){}
                if (deleterToken->str() == MatchCompiler::makeConstString("+")) {
                    deleterToken = deleterToken->next();
                }
                // Check if its a pointer to a function
                const Token * dtok = findmatch38(deleterToken, endDeleterToken) ;
                if (dtok) {
                    dtok = dtok->next();
                    af = mSettings->library.getDeallocFuncInfo(dtok);
                }
                if (!dtok || !af) {
                    const Token * tscopeStart = nullptr;
                    const Token * tscopeEnd = nullptr;
                    // If the deleter is a lambda, check if it calls the dealloc function
                    if (deleterToken->str() == MatchCompiler::makeConstString("[") &&
                        match39(deleterToken->link()) &&
                        // TODO: Check for mutable keyword
                        match21(deleterToken->link()->linkAt(1))) {
                        tscopeStart = deleterToken->link()->linkAt(1)->tokAt(1);
                        tscopeEnd = tscopeStart->link();
                        // check user-defined deleter function
                    } else if (dtok && dtok->function()) {
                        const Scope* tscope = dtok->function()->functionScope;
                        if (tscope) {
                            tscopeStart = tscope->bodyStart;
                            tscopeEnd = tscope->bodyEnd;
                        }
                        // If the deleter is a class, check if class calls the dealloc function
                    } else if ((dtok = findmatch40(deleterToken, endDeleterToken) ) && dtok->type()) {
                        const Scope * tscope = dtok->type()->classScope;
                        if (tscope) {
                            tscopeStart = tscope->bodyStart;
                            tscopeEnd = tscope->bodyEnd;
                        }
                    }

                    if (tscopeStart && tscopeEnd) {
                        for (const Token *tok2 = tscopeStart; tok2 != tscopeEnd; tok2 = tok2->next()) {
                            af = mSettings->library.getDeallocFuncInfo(tok2);
                            if (af)
                                break;
                        }
                    } else { // there is a deleter, but we can't check it -> assume that it deallocates correctly
                        varInfo.clear();
                        continue;
                    }
                }
            }

            const Token * vtok = typeEndTok->tokAt(3);
            const VarInfo::AllocInfo allocation(af ? af->groupId : (arrayDelete ? NEW_ARRAY : NEW), VarInfo::OWNED, ftok);
            changeAllocStatus(varInfo, allocation, vtok, vtok);
        } else if (match41(tok))
            checkTokenInsideExpression(tok, varInfo);
    }
    ret(endToken, varInfo, true);
    return true;
}


const Token * CheckLeakAutoVar::checkTokenInsideExpression(const Token * const tok, VarInfo &varInfo, bool inFuncCall)
{
    // Deallocation and then dereferencing pointer..
    if (tok->varId() > 0) {
        // TODO : Write a separate checker for this that uses valueFlowForward.
        const auto var = utils::as_const(varInfo.alloctype).find(tok->varId());
        if (var != varInfo.alloctype.end()) {
            bool unknown = false;
            if (var->second.status == VarInfo::DEALLOC && tok->valueType() && tok->valueType()->pointer &&
                CheckNullPointer::isPointerDeRef(tok, unknown, *mSettings, /*checkNullArg*/ false) && !unknown) {
                deallocUseError(tok, tok->str());
            } else if (match42(tok->tokAt(-2))) {
                varInfo.erase(tok->varId());
            } else {
                // check if tok is assigned into another variable
                const Token *rhs = tok;
                bool isAssignment = false;
                while (rhs->astParent()) {
                    if (rhs->astParent()->str() == MatchCompiler::makeConstString("=")) {
                        isAssignment = true;
                        break;
                    }
                    rhs = rhs->astParent();
                }
                while (rhs->isCast()) {
                    rhs = rhs->astOperand2() ? rhs->astOperand2() : rhs->astOperand1();
                }
                if ((rhs->str() == MatchCompiler::makeConstString(".") || rhs->varId() == tok->varId()) && isAssignment) {
                    // simple assignment
                    varInfo.erase(tok->varId());
                } else if (rhs->astParent() && rhs->str() == MatchCompiler::makeConstString("(") && !mSettings->library.returnValue(rhs->astOperand1()).empty()) {
                    // #9298, assignment through return value of a function
                    const std::string &returnValue = mSettings->library.returnValue(rhs->astOperand1());
                    if (startsWith(returnValue, "arg")) {
                        int argn;
                        const Token *func = getTokenArgumentFunction(tok, argn);
                        if (func) {
                            const std::string arg = "arg" + std::to_string(argn + 1);
                            if (returnValue == arg) {
                                varInfo.erase(tok->varId());
                            }
                        }
                    }
                }
            }
        } else if (match43(tok->previous())) {
            varInfo.referenced.insert(tok->tokAt(2)->varId());
        }
    }

    // check for function call
    const Token * const openingPar = inFuncCall ? nullptr : isFunctionCall(tok);
    if (openingPar) {
        const Library::AllocFunc* allocFunc = mSettings->library.getDeallocFuncInfo(tok);
        VarInfo::AllocInfo alloc(allocFunc ? allocFunc->groupId : 0, VarInfo::DEALLOC, tok);
        if (alloc.type == 0)
            alloc.status = VarInfo::NOALLOC;
        functionCall(tok, openingPar, varInfo, alloc, nullptr);
        const std::string &returnValue = mSettings->library.returnValue(tok);
        if (startsWith(returnValue, "arg"))
            // the function returns one of its argument, we need to process a potential assignment
            return openingPar;
        return isCPPCast(tok->astParent()) ? openingPar : openingPar->link();
    }

    return nullptr;
}


void CheckLeakAutoVar::changeAllocStatusIfRealloc(std::map<int, VarInfo::AllocInfo> &alloctype, const Token *fTok, const Token *retTok) const
{
    const Library::AllocFunc* f = mSettings->library.getReallocFuncInfo(fTok);
    if (f && f->arg == -1 && f->reallocArg > 0 && f->reallocArg <= numberOfArguments(fTok)) {
        const Token* argTok = getArguments(fTok).at(f->reallocArg - 1);
        if (alloctype.find(argTok->varId()) != alloctype.end()) {
            VarInfo::AllocInfo& argAlloc = alloctype[argTok->varId()];
            if (argAlloc.type != 0 && argAlloc.type != f->groupId)
                mismatchError(fTok, argAlloc.allocTok, argTok->str());
            argAlloc.status = VarInfo::REALLOC;
            argAlloc.allocTok = fTok;
        }
        VarInfo::AllocInfo& retAlloc = alloctype[retTok->varId()];
        retAlloc.type = f->groupId;
        retAlloc.status = VarInfo::ALLOC;
        retAlloc.allocTok = fTok;
        retAlloc.reallocedFromType = argTok->varId();
    }
}


void CheckLeakAutoVar::changeAllocStatus(VarInfo &varInfo, const VarInfo::AllocInfo& allocation, const Token* tok, const Token* arg)
{
    std::map<int, VarInfo::AllocInfo> &alloctype = varInfo.alloctype;
    const auto var = alloctype.find(arg->varId());
    if (var != alloctype.end()) {
        // bailout if function is also allocating, since the argument might be moved
        // to the return value, such as in fdopen
        if (allocation.allocTok && mSettings->library.getAllocFuncInfo(allocation.allocTok)) {
            varInfo.erase(arg->varId());
            return;
        }
        if (allocation.status == VarInfo::NOALLOC) {
            // possible usage
            varInfo.possibleUsage[arg->varId()] = { tok, VarInfo::USED };
            if (var->second.status == VarInfo::DEALLOC && arg->strAt(-1) == MatchCompiler::makeConstString("&"))
                varInfo.erase(arg->varId());
        } else if (var->second.managed()) {
            doubleFreeError(tok, var->second.allocTok, arg->str(), allocation.type);
            var->second.status = allocation.status;
        } else if (var->second.type != allocation.type && var->second.type != 0) {
            // mismatching allocation and deallocation
            mismatchError(tok, var->second.allocTok, arg->str());
            varInfo.erase(arg->varId());
        } else {
            // deallocation
            var->second.status = allocation.status;
            var->second.type = allocation.type;
            var->second.allocTok = allocation.allocTok;
        }
    } else if (allocation.status != VarInfo::NOALLOC && allocation.status != VarInfo::OWNED && !match44(tok->astTop())) {
        auto& allocInfo = alloctype[arg->varId()];
        allocInfo.status = VarInfo::DEALLOC;
        allocInfo.allocTok = tok;
        allocInfo.type = allocation.type;
    }
}

void CheckLeakAutoVar::functionCall(const Token *tokName, const Token *tokOpeningPar, VarInfo &varInfo, const VarInfo::AllocInfo& allocation, const Library::AllocFunc* af)
{
    // Ignore function call?
    const bool isLeakIgnore = mSettings->library.isLeakIgnore(mSettings->library.getFunctionName(tokName));
    if (mSettings->library.getReallocFuncInfo(tokName))
        return;
    if (tokName->next()->valueType() && tokName->next()->valueType()->container && tokName->next()->valueType()->container->stdStringLike)
        return;

    const Token * const tokFirstArg = tokOpeningPar->next();
    if (!tokFirstArg || tokFirstArg->str() == MatchCompiler::makeConstString(")")) {
        // no arguments
        return;
    }

    int argNr = 1;
    for (const Token *funcArg = tokFirstArg; funcArg; funcArg = funcArg->nextArgument()) {
        const Token* arg = funcArg;
        if (arg->isCpp()) {
            int tokAdvance = 0;
            if (arg->str() == MatchCompiler::makeConstString("new"))
                tokAdvance = 1;
            else if (match45(arg))
                tokAdvance = 2;
            if (tokAdvance > 0) {
                arg = arg->tokAt(tokAdvance);
                if (match46(arg))
                    arg = arg->tokAt(5);
            }
        }

        // Skip casts
        if (arg->isKeyword() && arg->astParent() && arg->astParent()->isCast())
            arg = arg->astParent();
        while (arg && arg->isCast())
            arg = arg->astOperand2() ? arg->astOperand2() : arg->astOperand1();
        const Token * const argTypeStartTok = arg;

        if (match26(arg))
            arg = arg->next();

        while (match47(arg))
            arg = arg->tokAt(2);

        if ((match48(arg) && !(arg->variable() && arg->variable()->isArray())) ||
            (match49(arg) && !(arg->next()->variable() && arg->next()->variable()->isArray()))) {
            // goto variable
            const bool isAddressOf = arg->str() == MatchCompiler::makeConstString("&");
            if (isAddressOf)
                arg = arg->next();

            const bool isnull = !isAddressOf && (arg->hasKnownIntValue() && arg->getKnownIntValue() == 0);

            // Is variable allocated?
            if (!isnull && (!af || af->arg == argNr)) {
                const Library::AllocFunc* deallocFunc = mSettings->library.getDeallocFuncInfo(tokName);
                VarInfo::AllocInfo dealloc(deallocFunc ? deallocFunc->groupId : 0, VarInfo::DEALLOC, tokName);
                if (const Library::AllocFunc* allocFunc = mSettings->library.getAllocFuncInfo(tokName)) {
                    if (mSettings->library.getDeallocFuncInfo(tokName)) {
                        changeAllocStatus(varInfo, dealloc.type == 0 ? allocation : dealloc, tokName, arg);
                    }
                    if (allocFunc->arg == argNr &&
                        !(arg->variable() && arg->variable()->isArgument() && arg->valueType() && arg->valueType()->pointer > 1) &&
                        (isAddressOf || (arg->valueType() && arg->valueType()->pointer == 2))) {
                        leakIfAllocated(arg, varInfo);
                        VarInfo::AllocInfo& varAlloc = varInfo.alloctype[arg->varId()];
                        varAlloc.type = allocFunc->groupId;
                        varAlloc.status = VarInfo::ALLOC;
                        varAlloc.allocTok = arg;
                    }
                }
                else if (isLeakIgnore)
                    checkTokenInsideExpression(arg, varInfo);
                else
                    changeAllocStatus(varInfo, dealloc.type == 0 ? allocation : dealloc, tokName, arg);
            }
        }
        // Check smart pointer
        else if (match50(arg) && mSettings->library.isSmartPointer(argTypeStartTok)) {
            const Token * typeEndTok = arg->linkAt(1);
            const Token * allocTok = nullptr;
            if (!match51(typeEndTok))
                continue;

            bool arrayDelete = false;
            if (findmatch35(arg->next(), typeEndTok) )
                arrayDelete = true;

            // Check deleter
            const Token * deleterToken = nullptr;
            const Token * endDeleterToken = nullptr;
            const Library::AllocFunc* sp_af = nullptr;
            if (match36(arg)) {
                deleterToken = arg->tokAt(4);
                endDeleterToken = typeEndTok;
            } else if (match52(typeEndTok)) {
                deleterToken = typeEndTok->tokAt(4);
                endDeleterToken = typeEndTok->linkAt(1);
            }
            if (deleterToken) {
                // Check if its a pointer to a function
                const Token * dtok = findmatch38(deleterToken, endDeleterToken) ;
                if (dtok) {
                    sp_af = mSettings->library.getDeallocFuncInfo(dtok->tokAt(1));
                } else {
                    // If the deleter is a class, check if class calls the dealloc function
                    dtok = findmatch40(deleterToken, endDeleterToken) ;
                    if (dtok && dtok->type()) {
                        const Scope * tscope = dtok->type()->classScope;
                        for (const Token *tok2 = tscope->bodyStart; tok2 != tscope->bodyEnd; tok2 = tok2->next()) {
                            sp_af = mSettings->library.getDeallocFuncInfo(tok2);
                            if (sp_af) {
                                allocTok = tok2;
                                break;
                            }
                        }
                    }
                }
            }

            const Token * vtok = typeEndTok->tokAt(2);
            const VarInfo::AllocInfo sp_allocation(sp_af ? sp_af->groupId : (arrayDelete ? NEW_ARRAY : NEW), VarInfo::OWNED, allocTok);
            changeAllocStatus(varInfo, sp_allocation, vtok, vtok);
        } else {
            const Token* const nextArg = funcArg->nextArgument();
            while (arg && ((nextArg && arg != nextArg) || (!nextArg && arg != tokOpeningPar->link()))) {
                checkTokenInsideExpression(arg, varInfo, /*inFuncCall*/ isLeakIgnore);

                if (isLambdaCaptureList(arg))
                    break;
                arg = arg->next();
            }
        }
        // TODO: check each token in argument expression (could contain multiple variables)
        argNr++;
    }
}


void CheckLeakAutoVar::leakIfAllocated(const Token *vartok,
                                       const VarInfo &varInfo)
{
    const std::map<int, VarInfo::AllocInfo> &alloctype = varInfo.alloctype;
    const auto& possibleUsage = varInfo.possibleUsage;

    const auto var = utils::as_const(alloctype).find(vartok->varId());
    if (var != alloctype.cend() && var->second.status == VarInfo::ALLOC) {
        const auto use = possibleUsage.find(vartok->varId());
        if (use == possibleUsage.end()) {
            leakError(vartok, vartok->str(), var->second.type);
        } else {
            configurationInfo(vartok, use->second);
        }
    }
}

void CheckLeakAutoVar::ret(const Token *tok, VarInfo &varInfo, const bool isEndOfScope)
{
    const std::map<int, VarInfo::AllocInfo> &alloctype = varInfo.alloctype;
    const auto& possibleUsage = varInfo.possibleUsage;
    std::vector<int> toRemove;

    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();
    for (auto it = alloctype.cbegin(); it != alloctype.cend(); ++it) {
        // don't warn if variable is conditionally allocated, unless it leaves the scope
        if (!isEndOfScope && !it->second.managed() && varInfo.conditionalAlloc.find(it->first) != varInfo.conditionalAlloc.end())
            continue;

        // don't warn if there is a reference of the variable
        if (varInfo.referenced.find(it->first) != varInfo.referenced.end())
            continue;

        const int varid = it->first;
        const Variable *var = symbolDatabase->getVariableFromVarId(varid);
        if (var) {
            // don't warn if we leave an inner scope
            if (isEndOfScope && var->scope() && tok != var->scope()->bodyEnd)
                continue;
            enum class PtrUsage : std::uint8_t { NONE, DEREF, PTR } used = PtrUsage::NONE;
            for (const Token *tok2 = tok; tok2; tok2 = tok2->next()) {
                if (tok2->str() == MatchCompiler::makeConstString(";"))
                    break;
                if (!match53(tok2))
                    continue;

                const Token* tok3 = tok2->next();
                while (tok3 && tok3->isCast() && tok3->valueType() &&
                       (tok3->valueType()->pointer ||
                        (tok3->valueType()->typeSize(mSettings->platform) == 0) ||
                        (tok3->valueType()->typeSize(mSettings->platform) >= mSettings->platform.sizeof_pointer)))
                    tok3 = tok3->astOperand2() ? tok3->astOperand2() : tok3->astOperand1();
                if (tok3 && tok3->varId() == varid)
                    tok2 = tok3->next();
                else if (match54(tok3, varid))
                    tok2 = tok3->tokAt(4);
                else if (match55(tok3) && tok3->next()->varId() == varid)
                    tok2 = tok3;
                else
                    continue;
                if (match56(tok2) && (!astIsBool(tok) || tok2->str() != MatchCompiler::makeConstString(";"))) {
                    used = PtrUsage::PTR;
                    break;
                }
                if (match57(tok2)) {
                    used = PtrUsage::DEREF;
                    break;
                }
            }

            // don't warn when returning after checking return value of outparam allocation
            const Token* outparamFunc{};
            if ((tok->scope()->type == ScopeType::eIf || tok->scope()->type== ScopeType::eElse) &&
                (outparamFunc = getOutparamAllocation(it->second.allocTok, *mSettings))) {
                const Scope* scope = tok->scope();
                if (scope->type == ScopeType::eElse) {
                    scope = scope->bodyStart->tokAt(-2)->scope();
                }
                const Token* const ifEnd = scope->bodyStart->previous();
                const Token* const ifStart = ifEnd->link();
                const Token* const alloc = it->second.allocTok;
                if (precedes(ifStart, alloc) && succeeds(ifEnd, alloc)) { // allocation and check in if
                    if (outparamFunc->next()->astParent() == ifStart || match58(outparamFunc->next()->astParent()))
                        continue;
                } else { // allocation result assigned to variable
                    const Token* const retAssign = outparamFunc->next()->astParent();
                    if (match5(retAssign) && retAssign->astOperand1()->varId()) {
                        bool isRetComp = false;
                        for (const Token* tok2 = ifStart; tok2 != ifEnd; tok2 = tok2->next()) {
                            if (tok2->varId() == retAssign->astOperand1()->varId()) {
                                isRetComp = true;
                                break;
                            }
                        }
                        if (isRetComp)
                            continue;
                    }
                }
            }

            // return deallocated pointer
            if (used != PtrUsage::NONE && it->second.status == VarInfo::DEALLOC)
                deallocReturnError(tok, it->second.allocTok, var->name());

            else if (used != PtrUsage::PTR && !it->second.managed() && !var->isReference()) {
                const auto use = possibleUsage.find(varid);
                if (use == possibleUsage.end()) {
                    leakError(tok, var->name(), it->second.type);
                } else if (!use->second.first->variable()) { // TODO: handle constructors
                    configurationInfo(tok, use->second);
                }
            }
            toRemove.push_back(varid);
        }
    }
    for (const int varId : toRemove)
        varInfo.erase(varId);
}

void CheckLeakAutoVar::runChecks(const Tokenizer &tokenizer, ErrorLogger *errorLogger)
{
    CheckLeakAutoVar checkLeakAutoVar(&tokenizer, &tokenizer.getSettings(), errorLogger);
    checkLeakAutoVar.check();
}

void CheckLeakAutoVar::getErrorMessages(ErrorLogger *errorLogger, const Settings *settings) const
{
    CheckLeakAutoVar c(nullptr, settings, errorLogger);
    c.deallocReturnError(nullptr, nullptr, "p");
    c.configurationInfo(nullptr, { nullptr, VarInfo::USED });  // user configuration is needed to complete analysis
    c.doubleFreeError(nullptr, nullptr, "varname", 0);
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
