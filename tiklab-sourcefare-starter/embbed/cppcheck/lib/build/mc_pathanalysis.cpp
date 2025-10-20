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
// pattern: %assign%
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !tok->isAssignmentOp())
        return false;
    return true;
}
// pattern: asm|goto|break|continue
MAYBE_UNUSED static inline bool match2(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("asm")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("goto")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("break")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("continue"))))
        return false;
    return true;
}
// pattern: return|throw
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("return")) || (tok->str() == MatchCompiler::makeConstString("throw"))))
        return false;
    return true;
}
// pattern: if|while|for (
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("if")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: }
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    return true;
}
// pattern: ) {
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: for|while (
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")) || ((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("while"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ; ++|--|%var% %var%|++|-- ) {
MAYBE_UNUSED static inline bool match8(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--")) || (tok->varId() != 0)))
        return false;
    tok = tok->next();
    if (!tok || !((tok->varId() != 0) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: for
MAYBE_UNUSED static inline bool match9(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("for")))
        return false;
    return true;
}
// pattern: } else {
MAYBE_UNUSED static inline bool match10(const Token* tok) {
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
#line 1 "/opt/cppcheck/cppcheck-main/lib/pathanalysis.cpp"
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

#include "pathanalysis.h"

#include "astutils.h"
#include "symboldatabase.h"
#include "token.h"
#include "vfvalue.h"

#include <algorithm>
#include <string>
#include <tuple>

const Scope* PathAnalysis::findOuterScope(const Scope * scope)
{
    if (!scope)
        return nullptr;
    if (scope->isLocal() && scope->type != ScopeType::eSwitch)
        return findOuterScope(scope->nestedIn);
    return scope;
}

static const Token* assignExpr(const Token* tok)
{
    while (tok->astParent() && astIsLHS(tok)) {
        if (match1(tok->astParent()))
            return tok->astParent();
        tok = tok->astParent();
    }
    return nullptr;
}

std::pair<bool, bool> PathAnalysis::checkCond(const Token * tok, bool& known)
{
    if (const ValueFlow::Value* v = tok->getKnownValue(ValueFlow::Value::ValueType::INT)) {
        known = true;
        return std::make_pair(!!v->intvalue, !v->intvalue);
    }
    auto it = std::find_if(tok->values().cbegin(), tok->values().cend(), [](const ValueFlow::Value& v) {
        return v.isIntValue();
    });
    // If all possible values are the same, then assume all paths have the same value
    if (it != tok->values().cend() && std::all_of(it, tok->values().cend(), [&](const ValueFlow::Value& v) {
        if (v.isIntValue())
            return v.intvalue == it->intvalue;
        return true;
    })) {
        known = false;
        return std::make_pair(!!it->intvalue, !it->intvalue);
    }
    return std::make_pair(true, true);
}

PathAnalysis::Progress PathAnalysis::forwardRecursive(const Token* tok, Info info, const std::function<PathAnalysis::Progress(const Info&)>& f)
{
    if (!tok)
        return Progress::Continue;
    if (tok->astOperand1() && forwardRecursive(tok->astOperand1(), info, f) == Progress::Break)
        return Progress::Break;
    info.tok = tok;
    if (f(info) == Progress::Break)
        return Progress::Break;
    if (tok->astOperand2() && forwardRecursive(tok->astOperand2(), std::move(info), f) == Progress::Break)
        return Progress::Break;
    return Progress::Continue;
}

PathAnalysis::Progress PathAnalysis::forwardRange(const Token* startToken, const Token* endToken, Info info, const std::function<PathAnalysis::Progress(const Info&)>& f) const
{
    for (const Token *tok = startToken; precedes(tok, endToken); tok = tok->next()) {
        if (match2(tok))
            return Progress::Break;
        if (match3(tok)) {
            forwardRecursive(tok, std::move(info), f);
            return Progress::Break;
            // Evaluate RHS of assignment before LHS
        }
        if (const Token* assignTok = assignExpr(tok)) {
            if (forwardRecursive(assignTok->astOperand2(), info, f) == Progress::Break)
                return Progress::Break;
            if (forwardRecursive(assignTok->astOperand1(), info, f) == Progress::Break)
                return Progress::Break;
            tok = nextAfterAstRightmostLeaf(assignTok);
            if (!tok)
                return Progress::Break;
        } else if (match5(tok) && match6(tok->link()->previous()) && match4(tok->link()->linkAt(-1)->previous())) {
            const Token * blockStart = tok->link()->linkAt(-1)->previous();
            const Token * condTok = getCondTok(blockStart);
            if (!condTok)
                continue;
            info.errorPath.emplace_back(condTok, "Assuming condition is true.");
            // Traverse a loop a second time
            if (match7(blockStart)) {
                const Token* endCond = blockStart->linkAt(1);
                bool traverseLoop = true;
                // Only traverse simple for loops
                if (match9(blockStart) && !match8(endCond->tokAt(-3)))
                    traverseLoop = false;
                // Traverse loop a second time
                if (traverseLoop) {
                    // Traverse condition
                    if (forwardRecursive(condTok, info, f) == Progress::Break)
                        return Progress::Break;
                    // TODO: Should we traverse the body: forwardRange(tok->link(), tok, info, f)?
                }
            }
            if (match10(tok)) {
                tok = tok->linkAt(2);
            }
        } else if (match4(tok) && match6(tok->linkAt(1))) {
            const Token * endCond = tok->linkAt(1);
            const Token * endBlock = endCond->linkAt(1);
            const Token * condTok = getCondTok(tok);
            if (!condTok)
                continue;
            // Traverse condition
            if (forwardRange(tok->next(), tok->linkAt(1), info, f) == Progress::Break)
                return Progress::Break;
            Info i = info;
            i.known = false;
            i.errorPath.emplace_back(condTok, "Assuming condition is true.");

            // Check if condition is true or false
            bool checkThen = false;
            bool checkElse = false;
            std::tie(checkThen, checkElse) = checkCond(condTok, i.known);

            // Traverse then block
            if (checkThen) {
                if (forwardRange(endCond->next(), endBlock, i, f) == Progress::Break)
                    return Progress::Break;
            }
            // Traverse else block
            if (match10(endBlock)) {
                if (checkElse) {
                    i.errorPath.back().second = "Assuming condition is false.";
                    const Progress result = forwardRange(endCond->next(), endBlock, std::move(i), f);
                    if (result == Progress::Break)
                        return Progress::Break;
                }
                tok = endBlock->linkAt(2);
            } else {
                tok = endBlock;
            }
        } else if (match10(tok)) {
            tok = tok->linkAt(2);
        } else {
            info.tok = tok;
            if (f(info) == Progress::Break)
                return Progress::Break;
        }
        // Prevent infinite recursion
        if (tok->next() == mStart)
            break;
    }
    return Progress::Continue;
}

void PathAnalysis::forward(const std::function<Progress(const Info&)>& f) const
{
    const Scope * endScope = findOuterScope(mStart->scope());
    if (!endScope)
        return;
    const Token * endToken = endScope->bodyEnd;
    Info info{mStart, ErrorPath{}, true};
    forwardRange(mStart, endToken, std::move(info), f);
}

bool reaches(const Token * start, const Token * dest, ErrorPath* errorPath)
{
    PathAnalysis::Info info = PathAnalysis{start}.forwardFind([&](const PathAnalysis::Info& i) {
        return (i.tok == dest);
    });
    if (!info.tok)
        return false;
    if (errorPath)
        errorPath->insert(errorPath->end(), info.errorPath.cbegin(), info.errorPath.cend());
    return true;
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
