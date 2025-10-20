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
// pattern: (|{
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: } else {
MAYBE_UNUSED static inline bool match2(const Token* tok) {
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
// pattern: ) {
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: do {
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: :
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: %oror%|&&|?
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")) || ((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("?"))))
        return false;
    return true;
}
// pattern: return|break|continue
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("break")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("continue"))))
        return false;
    return true;
}
// pattern: %name% :
MAYBE_UNUSED static inline bool match8(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(":")))
        return false;
    return true;
}
// pattern: %assign%
MAYBE_UNUSED static inline bool match9(const Token* tok) {
    if (!tok || !tok->isAssignmentOp())
        return false;
    return true;
}
// pattern: for|while (
MAYBE_UNUSED static inline bool match10(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: goto|break
template<class T> MAYBE_UNUSED static inline T * findmatch11(T * start_tok, const Token * end) {
    for (; start_tok && start_tok != end; start_tok = start_tok->next()) {

    T * tok = start_tok;
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("goto")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("break"))))
        continue;
    return start_tok;
    }
    return nullptr;
}
// pattern: do
MAYBE_UNUSED static inline bool match12(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("do")))
        return false;
    return true;
}
// pattern: )|}
MAYBE_UNUSED static inline bool match13(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}"))))
        return false;
    return true;
}
// pattern: )|>
MAYBE_UNUSED static inline bool match14(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    return true;
}
// pattern: <
MAYBE_UNUSED static inline bool match15(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/reverseanalyzer.cpp"
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

#include "reverseanalyzer.h"

#include "analyzer.h"
#include "astutils.h"
#include "errortypes.h"
#include "forwardanalyzer.h"
#include "mathlib.h"
#include "settings.h"
#include "symboldatabase.h"
#include "token.h"
#include "valueptr.h"

#include <algorithm>
#include <cstddef>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace {
    struct ReverseTraversal {
        ReverseTraversal(const ValuePtr<Analyzer>& analyzer, const TokenList& tokenlist, ErrorLogger& errorLogger, const Settings& settings)
            : analyzer(analyzer), tokenlist(tokenlist), errorLogger(errorLogger), settings(settings)
        {}
        ValuePtr<Analyzer> analyzer;
        const TokenList& tokenlist;
        ErrorLogger& errorLogger;
        const Settings& settings;

        std::pair<bool, bool> evalCond(const Token* tok) const {
            std::vector<MathLib::bigint> result = analyzer->evaluate(tok);
            // TODO: We should convert to bool
            const bool checkThen = std::any_of(result.cbegin(), result.cend(), [](MathLib::bigint x) {
                return x == 1;
            });
            const bool checkElse = std::any_of(result.cbegin(), result.cend(), [](MathLib::bigint x) {
                return x == 0;
            });
            return std::make_pair(checkThen, checkElse);
        }

        bool update(Token* tok) {
            Analyzer::Action action = analyzer->analyze(tok, Analyzer::Direction::Reverse);
            if (action.isInconclusive() && !analyzer->lowerToInconclusive())
                return false;
            if (action.isInvalid())
                return false;
            if (!action.isNone())
                analyzer->update(tok, action, Analyzer::Direction::Reverse);
            return true;
        }

        static Token* getParentFunction(Token* tok)
        {
            if (!tok)
                return nullptr;
            if (!tok->astParent())
                return nullptr;
            int argn = -1;
            if (Token* ftok = getTokenArgumentFunction(tok, argn)) {
                while (!match1(ftok)) {
                    if (!ftok)
                        return nullptr;
                    if (ftok->index() >= tok->index())
                        return nullptr;
                    if (!ftok->link() || ftok->str() == MatchCompiler::makeConstString(")"))
                        ftok = ftok->next();
                    else
                        ftok = ftok->link()->next();
                }
                if (ftok == tok)
                    return nullptr;
                return ftok;
            }
            return nullptr;
        }

        static Token* getTopFunction(Token* tok)
        {
            if (!tok)
                return nullptr;
            if (!tok->astParent())
                return tok;
            Token* parent = tok;
            Token* top = tok;
            while ((parent = getParentFunction(parent)))
                top = parent;
            return top;
        }

        static Token* jumpToStart(Token* tok)
        {
            if (match2(tok->tokAt(-2)))
                tok = tok->linkAt(-2);
            if (match3(tok->previous()))
                return tok->linkAt(-1);
            if (match4(tok->previous()))
                return tok->previous();
            return tok;
        }

        bool updateRecursive(Token* start) {
            bool continueB = true;
            visitAstNodes(start, [&](Token* tok) {
                const Token* parent = tok->astParent();
                while (match5(parent))
                    parent = parent->astParent();
                if (isUnevaluated(tok) || isDeadCode(tok, parent))
                    return ChildrenToVisit::none;
                continueB &= update(tok);
                if (continueB)
                    return ChildrenToVisit::op1_and_op2;
                return ChildrenToVisit::done;
            });
            return continueB;
        }

        Analyzer::Action analyzeRecursive(const Token* start) const {
            Analyzer::Action result = Analyzer::Action::None;
            visitAstNodes(start, [&](const Token* tok) {
                result |= analyzer->analyze(tok, Analyzer::Direction::Reverse);
                if (result.isModified())
                    return ChildrenToVisit::done;
                return ChildrenToVisit::op1_and_op2;
            });
            return result;
        }

        Analyzer::Action analyzeRange(const Token* start, const Token* end) const {
            Analyzer::Action result = Analyzer::Action::None;
            for (const Token* tok = start; tok && tok != end; tok = tok->next()) {
                Analyzer::Action action = analyzer->analyze(tok, Analyzer::Direction::Reverse);
                if (action.isModified())
                    return action;
                result |= action;
            }
            return result;
        }

        Token* isDeadCode(Token* tok, const Token* end = nullptr) const {
            int opSide = 0;
            for (; tok && tok->astParent(); tok = tok->astParent()) {
                if (tok == end)
                    break;
                Token* parent = tok->astParent();
                if (match5(parent)) {
                    if (astIsLHS(tok))
                        opSide = 1;
                    else if (astIsRHS(tok))
                        opSide = 2;
                    else
                        opSide = 0;
                }
                if (tok != parent->astOperand2())
                    continue;
                if (match5(parent))
                    parent = parent->astParent();
                if (!match6(parent))
                    continue;
                const Token* condTok = parent->astOperand1();
                if (!condTok)
                    continue;
                bool checkThen, checkElse;
                std::tie(checkThen, checkElse) = evalCond(condTok);

                if (parent->str() == MatchCompiler::makeConstString("?")) {
                    if (checkElse && opSide == 1)
                        return parent;
                    if (checkThen && opSide == 2)
                        return parent;
                }
                if (!checkThen && parent->str() == MatchCompiler::makeConstString("&&"))
                    return parent;
                if (!checkElse && parent->str() == MatchCompiler::makeConstString("||"))
                    return parent;
            }
            return nullptr;
        }

        void traverse(Token* start, const Token* end = nullptr) {
            if (start == end)
                return;
            std::size_t i = start->index();
            for (Token* tok = start->previous(); succeeds(tok, end); tok = tok->previous()) {
                if (tok->index() >= i)
                    throw InternalError(tok, "Cyclic reverse analysis.");
                i = tok->index();
                if (tok == start || (tok->str() == MatchCompiler::makeConstString("{") && (tok->scope()->type == ScopeType::eFunction ||
                                                           tok->scope()->type == ScopeType::eLambda))) {
                    const Function* f = tok->scope()->function;
                    if (f && f->isConstructor()) {
                        if (const Token* initList = f->constructorMemberInitialization())
                            traverse(tok->previous(), tok->tokAt(initList->index() - tok->index()));
                    }
                    break;
                }
                if (match7(tok))
                    break;
                if (match8(tok))
                    break;
                if (match5(tok))
                    continue;
                // Evaluate LHS of assignment before RHS
                if (Token* assignTok = assignExpr(tok)) {
                    // If assignTok has broken ast then stop
                    if (!assignTok->astOperand1() || !assignTok->astOperand2())
                        break;
                    Token* assignTop = assignTok;
                    bool continueB = true;
                    while (assignTop->isAssignmentOp()) {
                        if (!match9(assignTop->astOperand1())) {
                            continueB &= updateRecursive(assignTop->astOperand1());
                        }
                        if (!assignTop->astParent())
                            break;
                        assignTop = assignTop->astParent();
                    }
                    // Is assignment in dead code
                    if (Token* parent = isDeadCode(assignTok)) {
                        tok = parent;
                        continue;
                    }
                    // Simple assign
                    if (assignTok->str() == MatchCompiler::makeConstString("=") && (assignTok->astParent() == assignTop || assignTok == assignTop)) {
                        Analyzer::Action rhsAction =
                            analyzer->analyze(assignTok->astOperand2(), Analyzer::Direction::Reverse);
                        Analyzer::Action lhsAction =
                            analyzer->analyze(assignTok->astOperand1(), Analyzer::Direction::Reverse);
                        // Assignment from
                        if (rhsAction.isRead() && !lhsAction.isInvalid() && assignTok->astOperand1()->exprId() > 0) {
                            const std::string info = "Assignment from '" + assignTok->expressionString() + "'";
                            ValuePtr<Analyzer> a = analyzer->reanalyze(assignTok->astOperand1(), info);
                            if (a) {
                                valueFlowGenericForward(nextAfterAstRightmostLeaf(assignTok->astOperand2()),
                                                        assignTok->astOperand2()->scope()->bodyEnd,
                                                        a,
                                                        tokenlist,
                                                        errorLogger,
                                                        settings);
                            }
                            // Assignment to
                        } else if (lhsAction.matches() && !assignTok->astOperand2()->hasKnownIntValue() &&
                                   assignTok->astOperand2()->exprId() > 0 &&
                                   isConstExpression(assignTok->astOperand2(), settings.library)) {
                            const std::string info = "Assignment to '" + assignTok->expressionString() + "'";
                            ValuePtr<Analyzer> a = analyzer->reanalyze(assignTok->astOperand2(), info);
                            if (a) {
                                valueFlowGenericForward(nextAfterAstRightmostLeaf(assignTok->astOperand2()),
                                                        assignTok->astOperand2()->scope()->bodyEnd,
                                                        a,
                                                        tokenlist,
                                                        errorLogger,
                                                        settings);
                                valueFlowGenericReverse(assignTok->astOperand1()->previous(), end, a, tokenlist, errorLogger, settings);
                            }
                        }
                    }
                    if (!continueB)
                        break;
                    if (!updateRecursive(assignTop->astOperand2()))
                        break;
                    tok = previousBeforeAstLeftmostLeaf(assignTop)->next();
                    continue;
                }
                if (tok->str() == MatchCompiler::makeConstString(")") && !isUnevaluated(tok)) {
                    if (Token* top = getTopFunction(tok->link())) {
                        if (!updateRecursive(top))
                            break;
                        Token* next = previousBeforeAstLeftmostLeaf(top);
                        if (next && precedes(next, tok))
                            tok = next->next();
                    }
                    continue;
                }
                if (tok->str() == MatchCompiler::makeConstString("}")) {
                    Token* condTok = getCondTokFromEnd(tok);
                    if (!condTok)
                        break;
                    Analyzer::Action condAction = analyzeRecursive(condTok);
                    const bool inLoop = match10(condTok->astTop()->previous());
                    // Evaluate condition of for and while loops first
                    if (inLoop) {
                        if (findmatch11(tok->link(), tok) )
                            break;
                        if (condAction.isModified())
                            break;
                        valueFlowGenericForward(condTok, analyzer, tokenlist, errorLogger, settings);
                    }
                    Token* thenEnd;
                    const bool hasElse = match2(tok->link()->tokAt(-2));
                    if (hasElse) {
                        thenEnd = tok->link()->tokAt(-2);
                    } else {
                        thenEnd = tok;
                    }

                    Analyzer::Action thenAction = analyzeRange(thenEnd->link(), thenEnd);
                    Analyzer::Action elseAction = Analyzer::Action::None;
                    if (hasElse) {
                        elseAction = analyzeRange(tok->link(), tok);
                    }
                    if (thenAction.isModified() && inLoop)
                        break;
                    if (thenAction.isModified() && !elseAction.isModified())
                        analyzer->assume(condTok, hasElse);
                    else if (elseAction.isModified() && !thenAction.isModified())
                        analyzer->assume(condTok, !hasElse);
                    // Bail if one of the branches are read to avoid FPs due to over constraints
                    else if (thenAction.isIdempotent() || elseAction.isIdempotent() || thenAction.isRead() ||
                             elseAction.isRead())
                        break;
                    if (thenAction.isInvalid() || elseAction.isInvalid())
                        break;

                    if (!thenAction.isModified() && !elseAction.isModified())
                        valueFlowGenericForward(condTok, analyzer, tokenlist, errorLogger, settings);
                    else if (condAction.isRead())
                        break;
                    // If the condition modifies the variable then bail
                    if (condAction.isModified())
                        break;
                    tok = jumpToStart(tok->link());
                    continue;
                }
                if (tok->str() == MatchCompiler::makeConstString("{")) {
                    if (tok->previous() &&
                        (match12(tok->previous()) ||
                         (tok->strAt(-1) == MatchCompiler::makeConstString(")") && match10(tok->linkAt(-1)->previous())))) {
                        Analyzer::Action action = analyzeRange(tok, tok->link());
                        if (action.isModified())
                            break;
                    }
                    Token* condTok = getCondTokFromEnd(tok->link());
                    if (condTok) {
                        Analyzer::Result r = valueFlowGenericForward(condTok, analyzer, tokenlist, errorLogger, settings);
                        if (r.action.isModified())
                            break;
                    }
                    tok = jumpToStart(tok);
                    continue;
                }
                if (Token* next = isUnevaluated(tok)) {
                    tok = next;
                    continue;
                }
                if (Token* parent = isDeadCode(tok)) {
                    tok = parent;
                    continue;
                }
                if (tok->str() == MatchCompiler::makeConstString("case")) {
                    const Scope* scope = tok->scope();
                    while (scope && scope->type != ScopeType::eSwitch)
                        scope = scope->nestedIn;
                    if (!scope || scope->type != ScopeType::eSwitch)
                        break;
                    tok = tok->tokAt(scope->bodyStart->index() - tok->index() - 1);
                    continue;
                }
                if (!update(tok))
                    break;
            }
        }

        static Token* assignExpr(Token* tok) {
            if (match13(tok))
                tok = tok->link();
            while (tok->astParent() && (astIsRHS(tok) || !tok->astParent()->isBinaryOp())) {
                if (tok->astParent()->isAssignmentOp())
                    return tok->astParent();
                tok = tok->astParent();
            }
            return nullptr;
        }

        static Token* isUnevaluated(Token* tok) {
            if (match14(tok) && tok->link()) {
                Token* start = tok->link();
                if (::isUnevaluated(start->previous()))
                    return start->previous();
                if (match15(start))
                    return start;
            }
            return nullptr;
        }
    };
}

void valueFlowGenericReverse(Token* start, const Token* end, const ValuePtr<Analyzer>& a, const TokenList& tokenlist, ErrorLogger& errorLogger, const Settings& settings)
{
    if (a->invalid())
        return;
    ReverseTraversal rt{a, tokenlist, errorLogger, settings};
    rt.traverse(start, end);
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
