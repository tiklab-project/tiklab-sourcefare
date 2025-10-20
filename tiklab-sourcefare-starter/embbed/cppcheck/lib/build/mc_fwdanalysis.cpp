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
// pattern: %name% (
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) {
MAYBE_UNUSED static inline bool match2(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ( {
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ( volatile
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("volatile")))
        return false;
    return true;
}
// pattern: try {
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("try")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: break ;
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("break")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: goto
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("goto")))
        return false;
    return true;
}
// pattern: return|throw
MAYBE_UNUSED static inline bool match8(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("throw"))))
        return false;
    return true;
}
// pattern: do {
MAYBE_UNUSED static inline bool match9(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } while (
MAYBE_UNUSED static inline bool match10(const Token* tok) {
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
// pattern: else {
MAYBE_UNUSED static inline bool match11(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("else")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: asm (
MAYBE_UNUSED static inline bool match12(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("asm")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: while|for (
MAYBE_UNUSED static inline bool match13(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: if (
MAYBE_UNUSED static inline bool match14(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: } else {
MAYBE_UNUSED static inline bool match15(const Token* tok) {
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
// pattern: ;
MAYBE_UNUSED static inline bool match16(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: (
MAYBE_UNUSED static inline bool match17(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: for (
MAYBE_UNUSED static inline bool match18(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: *|.|::|[|(|%cop%
MAYBE_UNUSED static inline bool match19(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")) || (tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || tok->isConstOp()))
        return false;
    return true;
}
// pattern: . %var%
MAYBE_UNUSED static inline bool match20(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    return true;
}
// pattern: [
MAYBE_UNUSED static inline bool match21(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
// pattern: =
MAYBE_UNUSED static inline bool match22(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: .
MAYBE_UNUSED static inline bool match23(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    return true;
}
// pattern: %assign%
MAYBE_UNUSED static inline bool match24(const Token* tok) {
    if (!tok || !tok->isAssignmentOp())
        return false;
    return true;
}
// pattern: [,(]
MAYBE_UNUSED static inline bool match25(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr(",(", tok->str()[0]))
        return false;
    return true;
}
// pattern: ,
MAYBE_UNUSED static inline bool match26(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: )|do {
MAYBE_UNUSED static inline bool match27(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: switch (
MAYBE_UNUSED static inline bool match28(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("switch")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %var% [=(]
MAYBE_UNUSED static inline bool match29(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || tok->str().size() != 1U || !strchr("=(", tok->str()[0]))
        return false;
    return true;
}
// pattern: . *
MAYBE_UNUSED static inline bool match30(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: if|while|for
MAYBE_UNUSED static inline bool match31(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for"))))
        return false;
    return true;
}
// pattern: %name%|.|::
MAYBE_UNUSED static inline bool match32(const Token* tok) {
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString(".")) || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: & %name% =
MAYBE_UNUSED static inline bool match33(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: std :: ref (
MAYBE_UNUSED static inline bool match34(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("std")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("ref")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %var% = %var% ;
MAYBE_UNUSED static inline bool match35(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
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
// pattern: %var% {|( %var% }|)
MAYBE_UNUSED static inline bool match36(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")"))))
        return false;
    return true;
}
// pattern: %varid% [
MAYBE_UNUSED static inline bool match37(const Token* tok, const int varid) {
    if (varid==0U)
        throw InternalError(tok, "Internal error. Token::Match called with varid 0. Please report this to Cppcheck developers");
    if (!tok || !(tok->isName() && tok->varId() == varid))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")))
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/fwdanalysis.cpp"
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

#include "fwdanalysis.h"

#include "astutils.h"
#include "config.h"
#include "library.h"
#include "settings.h"
#include "symboldatabase.h"
#include "token.h"
#include "vfvalue.h"

#include <list>
#include <string>
#include <utility>

static bool isUnchanged(const Token *startToken, const Token *endToken, const std::set<nonneg int> &exprVarIds, bool local)
{
    for (const Token *tok = startToken; tok != endToken; tok = tok->next()) {
        if (!local && match1(tok) && !match2(tok->linkAt(1)))
            // TODO: this is a quick bailout
            return false;
        if (tok->varId() == 0 || exprVarIds.find(tok->varId()) == exprVarIds.end())
            continue;
        const Token *parent = tok;
        while (parent->astParent() && !parent->astParent()->isAssignmentOp() && parent->astParent()->tokType() != Token::Type::eIncDecOp) {
            if (parent->str() == MatchCompiler::makeConstString(",") || parent->isUnaryOp("&"))
                // TODO: This is a quick bailout
                return false;
            parent = parent->astParent();
        }
        if (parent->astParent()) {
            if (parent->astParent()->tokType() == Token::Type::eIncDecOp)
                return false;
            if (parent->astParent()->isAssignmentOp() && parent == parent->astParent()->astOperand1())
                return false;
        }
    }
    return true;
}

static bool hasFunctionCall(const Token *tok)
{
    if (!tok)
        return false;
    if (match1(tok))
        // todo, const/pure function?
        return true;
    return hasFunctionCall(tok->astOperand1()) || hasFunctionCall(tok->astOperand2());
}

static bool hasGccCompoundStatement(const Token *tok)
{
    if (!tok)
        return false;
    if (tok->str() == MatchCompiler::makeConstString("{") && match3(tok->previous()))
        return true;
    return hasGccCompoundStatement(tok->astOperand1()) || hasGccCompoundStatement(tok->astOperand2());
}

static bool nonLocal(const Variable* var, bool deref)
{
    return !var || (!var->isLocal() && !var->isArgument()) || (deref && var->isArgument() && var->isPointer()) || var->isStatic() || var->isExtern();
}

static bool hasVolatileCastOrVar(const Token *expr)
{
    bool ret = false;
    visitAstNodes(expr,
                  [&ret](const Token *tok) {
        if (tok->variable() && tok->variable()->isVolatile())
            ret = true;
        else if (match4(tok))
            ret = true;
        return ret ? ChildrenToVisit::none : ChildrenToVisit::op1_and_op2;
    });
    return ret;
}

FwdAnalysis::Result FwdAnalysis::checkRecursive(const Token *expr, const Token *startToken, const Token *endToken, const std::set<nonneg int> &exprVarIds, bool local, bool inInnerClass, int depth)
{
    // Parse the given tokens
    if (++depth > 1000)
        return Result(Result::Type::BAILOUT);

    for (const Token* tok = startToken; precedes(tok, endToken); tok = tok->next()) {
        if (match5(tok)) {
            // TODO: handle try
            return Result(Result::Type::BAILOUT);
        }

        if (match6(tok)) {
            return Result(Result::Type::BREAK, tok);
        }

        if (match7(tok))
            return Result(Result::Type::BAILOUT);

        if (!inInnerClass && tok->str() == MatchCompiler::makeConstString("{") && tok->scope()->isClassOrStruct()) {
            // skip returns from local class definition
            FwdAnalysis::Result result = checkRecursive(expr, tok, tok->link(), exprVarIds, local, true, depth);
            if (result.type != Result::Type::NONE)
                return result;
            tok=tok->link();
        }

        if (tok->str() == MatchCompiler::makeConstString("continue"))
            // TODO
            return Result(Result::Type::BAILOUT);

        if (const Token *lambdaEndToken = findLambdaEndToken(tok)) {
            tok = lambdaEndToken;
            const Result lambdaResult = checkRecursive(expr, lambdaEndToken->link()->next(), lambdaEndToken, exprVarIds, local, inInnerClass, depth);
            if (lambdaResult.type == Result::Type::READ || lambdaResult.type == Result::Type::BAILOUT)
                return lambdaResult;
        }

        if (match8(tok)) {
            // TODO: Handle these better
            // Is expr variable used in expression?

            const Token* opTok = tok->astOperand1();
            if (!opTok)
                opTok = tok->next();
            std::pair<const Token*, const Token*> startEndTokens = opTok->findExpressionStartEndTokens();
            FwdAnalysis::Result result =
                checkRecursive(expr, startEndTokens.first, startEndTokens.second->next(), exprVarIds, local, true, depth);
            if (result.type != Result::Type::NONE)
                return result;

            // #9167: if the return is inside an inner class, it does not tell us anything
            if (!inInnerClass) {
                if (!local && mWhat == What::Reassign)
                    return Result(Result::Type::BAILOUT);

                return Result(Result::Type::RETURN);
            }
        }

        if (tok->str() == MatchCompiler::makeConstString("}")) {
            // Known value => possible value
            if (tok->scope() == expr->scope())
                mValueFlowKnown = false;

            if (tok->scope()->isLoopScope()) {
                // check condition
                const Token *conditionStart = nullptr;
                const Token *conditionEnd = nullptr;
                if (match2(tok->link()->previous())) {
                    conditionEnd = tok->link()->previous();
                    conditionStart = conditionEnd->link();
                } else if (match9(tok->link()->previous()) && match10(tok)) {
                    conditionStart = tok->tokAt(2);
                    conditionEnd = conditionStart->link();
                }
                if (conditionStart && conditionEnd) {
                    bool used = false;
                    for (const Token *condTok = conditionStart; condTok != conditionEnd; condTok = condTok->next()) {
                        if (exprVarIds.find(condTok->varId()) != exprVarIds.end()) {
                            used = true;
                            break;
                        }
                    }
                    if (used)
                        return Result(Result::Type::BAILOUT);
                }

                // check loop body again..
                const FwdAnalysis::Result &result = checkRecursive(expr, tok->link(), tok, exprVarIds, local, inInnerClass, depth);
                if (result.type == Result::Type::BAILOUT || result.type == Result::Type::READ)
                    return result;
            }
        }

        if (match11(tok))
            tok = tok->linkAt(1);

        if (match12(tok))
            return Result(Result::Type::BAILOUT);

        if (mWhat == What::ValueFlow && (match13(tok) || match9(tok))) {
            const Token *bodyStart = nullptr;
            const Token *conditionStart = nullptr;
            if (match9(tok)) {
                bodyStart = tok->next();
                if (match10(bodyStart->link()))
                    conditionStart = bodyStart->link()->tokAt(2);
            } else {
                conditionStart = tok->next();
                if (match2(conditionStart->link()))
                    bodyStart = conditionStart->link()->next();
            }

            if (!bodyStart || !conditionStart)
                return Result(Result::Type::BAILOUT);

            // Is expr changed in condition?
            if (!isUnchanged(conditionStart, conditionStart->link(), exprVarIds, local))
                return Result(Result::Type::BAILOUT);

            // Is expr changed in loop body?
            if (!isUnchanged(bodyStart, bodyStart->link(), exprVarIds, local))
                return Result(Result::Type::BAILOUT);
        }

        if (mWhat == What::ValueFlow && match14(tok) && match2(tok->linkAt(1))) {
            const Token *bodyStart = tok->linkAt(1)->next();
            const Token *conditionStart = tok->next();
            const Token *condTok = conditionStart->astOperand2();
            if (const ValueFlow::Value* v = condTok->getKnownValue(ValueFlow::Value::ValueType::INT)) {
                const bool cond = !!v->intvalue;
                if (cond) {
                    FwdAnalysis::Result result = checkRecursive(expr, bodyStart, bodyStart->link(), exprVarIds, local, true, depth);
                    if (result.type != Result::Type::NONE)
                        return result;
                } else if (match15(bodyStart->link())) {
                    bodyStart = bodyStart->link()->tokAt(2);
                    FwdAnalysis::Result result = checkRecursive(expr, bodyStart, bodyStart->link(), exprVarIds, local, true, depth);
                    if (result.type != Result::Type::NONE)
                        return result;
                }
            }
            tok = bodyStart->link();
            if (isReturnScope(tok, mSettings.library))
                return Result(Result::Type::BAILOUT);
            if (match15(tok))
                tok = tok->linkAt(2);
            if (!tok)
                return Result(Result::Type::BAILOUT);

            // Is expr changed in condition?
            if (!isUnchanged(conditionStart, conditionStart->link(), exprVarIds, local))
                return Result(Result::Type::BAILOUT);

            // Is expr changed in condition body?
            if (!isUnchanged(bodyStart, bodyStart->link(), exprVarIds, local))
                return Result(Result::Type::BAILOUT);
        }

        if (!local && match1(tok) && !match2(tok->linkAt(1))) {
            // TODO: this is a quick bailout
            return Result(Result::Type::BAILOUT);
        }

        if (mWhat == What::Reassign &&
            match16(tok) &&
            match16(tok->astParent()) &&
            match17(tok->astParent()->astParent()) &&
            match18(tok->astParent()->astParent()->previous()) &&
            !isUnchanged(tok, tok->astParent()->astParent()->link(), exprVarIds, local))
            // TODO: This is a quick bailout to avoid FP #9420, there are false negatives (TODO_ASSERT_EQUALS)
            return Result(Result::Type::BAILOUT);

        if (expr->isName() && match1(tok) && tok->str().find('<') != std::string::npos && tok->str().find(expr->str()) != std::string::npos)
            return Result(Result::Type::BAILOUT);

        if (exprVarIds.find(tok->varId()) != exprVarIds.end()) {
            const Token *parent = tok;
            bool other = false;
            bool same = tok->astParent() && isSameExpression(false, expr, tok, mSettings, true, false, nullptr);
            while (!same && match19(parent->astParent())) {
                parent = parent->astParent();
                if (parent->str() == MatchCompiler::makeConstString("(") && !parent->isCast())
                    break;
                if (isSameExpression(false, expr, parent, mSettings, true, false, nullptr)) {
                    same = true;
                    if (mWhat == What::ValueFlow) {
                        KnownAndToken v;
                        v.known = mValueFlowKnown;
                        v.token = parent;
                        mValueFlow.push_back(v);
                    }
                }
                if (match20(parent) && parent->next()->varId() && exprVarIds.find(parent->next()->varId()) == exprVarIds.end() &&
                    isSameExpression(false, expr->astOperand1(), parent->astOperand1(), mSettings, true, false, nullptr)) {
                    other = true;
                    break;
                }
            }
            if (mWhat != What::ValueFlow && same && match21(parent->astParent()) && parent == parent->astParent()->astOperand2()) {
                return Result(Result::Type::READ);
            }
            if (other)
                continue;
            if (match22(parent->astParent()) && parent == parent->astParent()->astOperand1()) {
                if (!local && hasFunctionCall(parent->astParent()->astOperand2())) {
                    // TODO: this is a quick bailout
                    return Result(Result::Type::BAILOUT);
                }
                if (hasOperand(parent->astParent()->astOperand2(), expr)) {
                    if (mWhat == What::Reassign)
                        return Result(Result::Type::READ);
                    continue;
                }
                const auto startEnd = parent->astParent()->astOperand2()->findExpressionStartEndTokens();
                for (const Token* tok2 = startEnd.first; tok2 != startEnd.second; tok2 = tok2->next()) {
                    if (tok2->tokType() == Token::eLambda)
                        return Result(Result::Type::BAILOUT);
                    // TODO: analyze usage in lambda
                }
                // ({ .. })
                if (hasGccCompoundStatement(parent->astParent()->astOperand2()))
                    return Result(Result::Type::BAILOUT);
                // cppcheck-suppress shadowFunction - TODO: fix this
                const bool reassign = isSameExpression(false, expr, parent, mSettings, false, false, nullptr);
                if (reassign)
                    return Result(Result::Type::WRITE, parent->astParent());
                return Result(Result::Type::READ);
            }
            if (mWhat == What::Reassign) {
                if (parent->variable() && parent->variable()->type() && parent->variable()->type()->isUnionType() && parent->varId() == expr->varId()) {
                    while (parent && match23(parent->astParent()))
                        parent = parent->astParent();
                    if (parent && parent->valueType() && match22(parent->astParent()) && !match24(parent->astParent()->astParent()) && parent->astParent()->astOperand1() == parent) {
                        const Token * assignment = parent->astParent()->astOperand2();
                        while (match23(assignment) && assignment->varId() != expr->varId())
                            assignment = assignment->astOperand1();
                        if (assignment && assignment->varId() != expr->varId()) {
                            if (assignment->valueType() && assignment->valueType()->pointer) // Bailout
                                return Result(Result::Type::BAILOUT);
                            return Result(Result::Type::WRITE, parent->astParent());
                        }
                    }
                    return Result(Result::Type::READ);
                }
                if (parent->valueType() && parent->valueType()->pointer && match24(parent->astParent()))
                    return Result(Result::Type::READ);
            }

            if (match24(parent->astParent()) && !parent->astParent()->astParent() && parent == parent->astParent()->astOperand1()) {
                if (mWhat == What::Reassign)
                    return Result(Result::Type::BAILOUT, parent->astParent());
                if (mWhat == What::UnusedValue && (!parent->valueType() || parent->valueType()->reference != Reference::None))
                    return Result(Result::Type::BAILOUT, parent->astParent());
                continue;
            }
            if (mWhat == What::UnusedValue && parent->isUnaryOp("&") && match25(parent->astParent())) {
                // Pass variable to function the writes it
                const Token *ftok = parent->astParent();
                while (match26(ftok))
                    ftok = ftok->astParent();
                if (ftok && match1(ftok->previous())) {
                    const std::vector<const Token *> args = getArguments(ftok);
                    int argnr = 0;
                    while (argnr < args.size() && args[argnr] != parent)
                        argnr++;
                    if (argnr < args.size()) {
                        if (mSettings.library.getArgDirection(ftok->astOperand1(), argnr + 1) == Library::ArgumentChecks::Direction::DIR_OUT)
                            continue;
                    }
                }
                return Result(Result::Type::BAILOUT, parent->astParent());
            }
            // TODO: this is a quick bailout
            return Result(Result::Type::BAILOUT, parent->astParent());
        }

        if (match27(tok)) {
            if (tok->str() == MatchCompiler::makeConstString(")") && match28(tok->link()->previous()))
                // TODO: parse switch
                return Result(Result::Type::BAILOUT);
            const Result &result1 = checkRecursive(expr, tok->tokAt(2), tok->linkAt(1), exprVarIds, local, inInnerClass, depth);
            if (result1.type == Result::Type::READ || result1.type == Result::Type::BAILOUT)
                return result1;
            if (mWhat == What::UnusedValue && result1.type == Result::Type::WRITE && expr->variable() && expr->variable()->isReference())
                return result1;
            if (mWhat == What::ValueFlow && result1.type == Result::Type::WRITE)
                mValueFlowKnown = false;
            if (mWhat == What::Reassign && result1.type == Result::Type::BREAK) {
                const Token *scopeEndToken = findNextTokenFromBreak(result1.token);
                if (scopeEndToken) {
                    const Result &result2 = checkRecursive(expr, scopeEndToken->next(), endToken, exprVarIds, local, inInnerClass, depth);
                    if (result2.type == Result::Type::BAILOUT)
                        return result2;
                }
            }
            if (match15(tok->linkAt(1))) {
                const Token *elseStart = tok->linkAt(1)->tokAt(2);
                const Result &result2 = checkRecursive(expr, elseStart, elseStart->link(), exprVarIds, local, inInnerClass, depth);
                if (mWhat == What::ValueFlow && result2.type == Result::Type::WRITE)
                    mValueFlowKnown = false;
                if (result2.type == Result::Type::READ || result2.type == Result::Type::BAILOUT)
                    return result2;
                if (result1.type == Result::Type::WRITE && result2.type == Result::Type::WRITE)
                    return result1;
                tok = elseStart->link();
            } else {
                tok = tok->linkAt(1);
            }
        }
    }

    return Result(Result::Type::NONE);
}

std::set<nonneg int> FwdAnalysis::getExprVarIds(const Token* expr, bool* localOut, bool* unknownVarIdOut) const
{
    // all variable ids in expr.
    std::set<nonneg int> exprVarIds;
    bool local = true;
    bool unknownVarId = false;
    visitAstNodes(expr,
                  [&](const Token *tok) {
        if (tok->str() == MatchCompiler::makeConstString("[") && mWhat == What::UnusedValue)
            return ChildrenToVisit::op1;
        if (tok->varId() == 0 && tok->isName() && tok->strAt(-1) != MatchCompiler::makeConstString(".")) {
            // unknown variable
            unknownVarId = true;
            return ChildrenToVisit::none;
        }
        if (tok->varId() > 0) {
            exprVarIds.insert(tok->varId());
            if (!match23(tok->previous())) {
                const Variable *var = tok->variable();
                if (var && var->isReference() && var->isLocal() && match29(var->nameToken()) && !isGlobalData(var->nameToken()->next()->astOperand2()))
                    return ChildrenToVisit::none;
                const bool deref = tok->astParent() && (tok->astParent()->isUnaryOp("*") || (tok->astParent()->str() == MatchCompiler::makeConstString("[") && tok == tok->astParent()->astOperand1()));
                local &= !nonLocal(tok->variable(), deref);
            }
        }
        return ChildrenToVisit::op1_and_op2;
    });
    if (localOut)
        *localOut = local;
    if (unknownVarIdOut)
        *unknownVarIdOut = unknownVarId;
    return exprVarIds;
}

FwdAnalysis::Result FwdAnalysis::check(const Token* expr, const Token* startToken, const Token* endToken)
{
    // all variable ids in expr.
    bool local = true;
    bool unknownVarId = false;
    std::set<nonneg int> exprVarIds = getExprVarIds(expr, &local, &unknownVarId);

    if (unknownVarId)
        return Result(FwdAnalysis::Result::Type::BAILOUT);

    if (mWhat == What::Reassign && isGlobalData(expr))
        local = false;

    // In unused values checking we do not want to check assignments to
    // global data.
    if (mWhat == What::UnusedValue && isGlobalData(expr))
        return Result(FwdAnalysis::Result::Type::BAILOUT);

    Result result = checkRecursive(expr, startToken, endToken, exprVarIds, local, false);

    // Break => continue checking in outer scope
    while (mWhat!=What::ValueFlow && result.type == FwdAnalysis::Result::Type::BREAK) {
        const Token *scopeEndToken = findNextTokenFromBreak(result.token);
        if (!scopeEndToken)
            break;
        result = checkRecursive(expr, scopeEndToken->next(), endToken, exprVarIds, local, false);
    }

    return result;
}

bool FwdAnalysis::hasOperand(const Token *tok, const Token *lhs) const
{
    if (!tok)
        return false;
    if (isSameExpression(false, tok, lhs, mSettings, false, false, nullptr))
        return true;
    return hasOperand(tok->astOperand1(), lhs) || hasOperand(tok->astOperand2(), lhs);
}

const Token *FwdAnalysis::reassign(const Token *expr, const Token *startToken, const Token *endToken)
{
    if (hasVolatileCastOrVar(expr))
        return nullptr;
    mWhat = What::Reassign;
    Result result = check(expr, startToken, endToken);
    return result.type == FwdAnalysis::Result::Type::WRITE ? result.token : nullptr;
}

bool FwdAnalysis::unusedValue(const Token *expr, const Token *startToken, const Token *endToken)
{
    if (isEscapedAlias(expr))
        return false;
    if (hasVolatileCastOrVar(expr))
        return false;
    if (match21(expr) && astIsContainerView(expr->astOperand1()))
        return false;
    mWhat = What::UnusedValue;
    Result result = check(expr, startToken, endToken);
    return (result.type == FwdAnalysis::Result::Type::NONE || result.type == FwdAnalysis::Result::Type::RETURN) && !possiblyAliased(expr, startToken);
}

bool FwdAnalysis::possiblyAliased(const Token *expr, const Token *startToken) const
{
    if (expr->isUnaryOp("*") && !expr->astOperand1()->isUnaryOp("&"))
        return true;
    if (match30(expr))
        return true;
    if (expr->str() == MatchCompiler::makeConstString("(") && match23(expr->astOperand1()))
        return true;

    const bool macro = false;
    const bool pure = false;
    const bool followVar = false;
    for (const Token *tok = startToken; tok; tok = tok->previous()) {

        if (match1(tok) && !match31(tok)) {
            // Is argument passed by reference?
            const std::vector<const Token*> args = getArguments(tok);
            for (int argnr = 0; argnr < args.size(); ++argnr) {
                if (!match32(args[argnr]))
                    continue;
                if (tok->function() && tok->function()->getArgumentVar(argnr) && !tok->function()->getArgumentVar(argnr)->isReference() && !tok->function()->isConst())
                    continue;
                for (const Token *subexpr = expr; subexpr; subexpr = subexpr->astOperand1()) {
                    if (isSameExpression(macro, subexpr, args[argnr], mSettings, pure, followVar)) {
                        const Scope* scope = expr->scope(); // if there is no other variable, assume no aliasing
                        if (scope->varlist.size() > 1)
                            return true;
                    }
                }
            }
            continue;
        }

        const Token *addrOf = nullptr;
        if (match33(tok))
            addrOf = tok->tokAt(2)->astOperand2();
        else if (tok->isUnaryOp("&"))
            addrOf = tok->astOperand1();
        else if (match34(tok))
            addrOf = tok->tokAt(3)->astOperand2();
        else if (tok->valueType() && tok->valueType()->pointer &&
                 (match35(tok) || match36(tok)) &&
                 match37(expr->previous(), tok->tokAt(2)->varId()))
            addrOf = tok->tokAt(2);
        else
            continue;

        for (const Token *subexpr = expr; subexpr; subexpr = subexpr->astOperand1()) {
            if (subexpr != addrOf && isSameExpression(macro, subexpr, addrOf, mSettings, pure, followVar))
                return true;
        }
    }
    return false;
}

bool FwdAnalysis::isEscapedAlias(const Token* expr)
{
    for (const Token *subexpr = expr; subexpr; subexpr = subexpr->astOperand1()) {
        for (const ValueFlow::Value &val : subexpr->values()) {
            if (!val.isLocalLifetimeValue())
                continue;
            const Variable* var = val.tokvalue->variable();
            if (!var)
                continue;
            if (!var->isLocal())
                return true;
            if (var->isArgument())
                return true;

        }
    }
    return false;
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
