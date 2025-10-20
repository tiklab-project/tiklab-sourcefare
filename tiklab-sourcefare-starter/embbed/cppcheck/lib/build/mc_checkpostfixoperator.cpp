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
// pattern: %var% ++|--
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--"))))
        return false;
    return true;
}
// pattern: ::
MAYBE_UNUSED static inline bool match2(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: %name% ::|<
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<"))))
        return false;
    return true;
}
// pattern: iterator|const_iterator|reverse_iterator|const_reverse_iterator
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("iterator")) || (tok->str() == MatchCompiler::makeConstString("const_iterator")) || (tok->str() == MatchCompiler::makeConstString("reverse_iterator")) || (tok->str() == MatchCompiler::makeConstString("const_reverse_iterator"))))
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/checkpostfixoperator.cpp"
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
// You should use ++ and -- as prefix whenever possible as these are more
// efficient than postfix operators
//---------------------------------------------------------------------------

#include "checkpostfixoperator.h"

#include "errortypes.h"
#include "settings.h"
#include "symboldatabase.h"
#include "token.h"
#include "tokenize.h"

#include <vector>

//---------------------------------------------------------------------------


// Register this check class (by creating a static instance of it)
namespace {
    CheckPostfixOperator instance;
}


// CWE ids used
static const CWE CWE398(398U);   // Indicator of Poor Code Quality


void CheckPostfixOperator::postfixOperator()
{
    if (!mSettings->severity.isEnabled(Severity::performance))
        return;

    logChecker("CheckPostfixOperator::postfixOperator"); // performance

    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();

    for (const Scope * scope : symbolDatabase->functionScopes) {
        for (const Token* tok = scope->bodyStart->next(); tok != scope->bodyEnd; tok = tok->next()) {
            const Variable *var = tok->variable();
            if (!var || !match1(tok))
                continue;

            const Token* parent = tok->next()->astParent();
            if (!parent || parent->str() == MatchCompiler::makeConstString(";") || (parent->str() == MatchCompiler::makeConstString(",") && (!parent->astParent() || parent->astParent()->str() != MatchCompiler::makeConstString("(")))) {
                if (var->isPointer() || var->isArray())
                    continue;

                const Token* typeEndTok = var->typeStartToken();
                if (match2(typeEndTok))
                    typeEndTok = typeEndTok->next();
                while (match3(typeEndTok)) {
                    if (typeEndTok->linkAt(1)) {
                        typeEndTok = typeEndTok->linkAt(1)->next();
                        if (match2(typeEndTok))
                            typeEndTok = typeEndTok->next();
                    }
                    else
                        typeEndTok = typeEndTok->tokAt(2);
                }
                if (match4(typeEndTok)) {
                    // the variable is an iterator
                    postfixOperatorError(tok);
                } else if (var->type()) {
                    // the variable is an instance of class
                    postfixOperatorError(tok);
                }
            }
        }
    }
}
//---------------------------------------------------------------------------


void CheckPostfixOperator::postfixOperatorError(const Token *tok)
{
    reportError(tok, Severity::performance, "postfixOperator",
                "Prefer prefix ++/-- operators for non-primitive types.\n"
                "Prefix ++/-- operators should be preferred for non-primitive types. "
                "Pre-increment/decrement can be more efficient than "
                "post-increment/decrement. Post-increment/decrement usually "
                "involves keeping a copy of the previous value around and "
                "adds a little extra code.", CWE398, Certainty::normal);
}

void CheckPostfixOperator::runChecks(const Tokenizer &tokenizer, ErrorLogger *errorLogger)
{
    if (tokenizer.isC())
        return;

    CheckPostfixOperator checkPostfixOperator(&tokenizer, &tokenizer.getSettings(), errorLogger);
    checkPostfixOperator.postfixOperator();
}

void CheckPostfixOperator::getErrorMessages(ErrorLogger *errorLogger, const Settings *settings) const
{
    CheckPostfixOperator c(nullptr, settings, errorLogger);
    c.postfixOperatorError(nullptr);
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
