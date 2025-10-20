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
// pattern: Token :: Match (
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("Token")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("Match")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: Token :: findmatch (
MAYBE_UNUSED static inline bool match2(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("Token")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("findmatch")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: && Token :: simpleMatch|Match|findsimplematch|findmatch (
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("Token")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("simpleMatch")) || (tok->str() == MatchCompiler::makeConstString("Match")) || (tok->str() == MatchCompiler::makeConstString("findsimplematch")) || (tok->str() == MatchCompiler::makeConstString("findmatch"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: &&
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")))
        return false;
    return true;
}
// pattern: %oror% ! Token :: simpleMatch|Match|findsimplematch|findmatch (
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !(tok->tokType() == Token::eLogicalOp && tok->str() == MatchCompiler::makeConstString("||")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("Token")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("simpleMatch")) || (tok->str() == MatchCompiler::makeConstString("Match")) || (tok->str() == MatchCompiler::makeConstString("findsimplematch")) || (tok->str() == MatchCompiler::makeConstString("findmatch"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ||
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("||")))
        return false;
    return true;
}
// pattern: !
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("!")))
        return false;
    return true;
}
// pattern: Token :: simpleMatch (
MAYBE_UNUSED static inline bool match8(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("Token")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("simpleMatch")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: Token :: findsimplematch (
MAYBE_UNUSED static inline bool match9(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("Token")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("findsimplematch")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: previous ( ) . previous|next|tokAt|str|strAt|link|linkAt (
MAYBE_UNUSED static inline bool match10(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("previous")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("previous")) || (tok->str() == MatchCompiler::makeConstString("next")) || (tok->str() == MatchCompiler::makeConstString("tokAt")) || (tok->str() == MatchCompiler::makeConstString("str")) || (tok->str() == MatchCompiler::makeConstString("strAt")) || (tok->str() == MatchCompiler::makeConstString("link")) || (tok->str() == MatchCompiler::makeConstString("linkAt"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: next ( ) . previous|next|tokAt|str|strAt|link|linkAt (
MAYBE_UNUSED static inline bool match11(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("next")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("previous")) || (tok->str() == MatchCompiler::makeConstString("next")) || (tok->str() == MatchCompiler::makeConstString("tokAt")) || (tok->str() == MatchCompiler::makeConstString("str")) || (tok->str() == MatchCompiler::makeConstString("strAt")) || (tok->str() == MatchCompiler::makeConstString("link")) || (tok->str() == MatchCompiler::makeConstString("linkAt"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: ) . previous|next|tokAt|strAt|linkAt|str|link (
MAYBE_UNUSED static inline bool match12(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("previous")) || (tok->str() == MatchCompiler::makeConstString("next")) || (tok->str() == MatchCompiler::makeConstString("tokAt")) || (tok->str() == MatchCompiler::makeConstString("strAt")) || (tok->str() == MatchCompiler::makeConstString("linkAt")) || (tok->str() == MatchCompiler::makeConstString("str")) || (tok->str() == MatchCompiler::makeConstString("link"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: tokAt (
MAYBE_UNUSED static inline bool match13(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("tokAt")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: Token :: simpleMatch|findsimplematch|Match|findmatch (
MAYBE_UNUSED static inline bool match14(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("Token")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("simpleMatch")) || (tok->str() == MatchCompiler::makeConstString("findsimplematch")) || (tok->str() == MatchCompiler::makeConstString("Match")) || (tok->str() == MatchCompiler::makeConstString("findmatch"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/checkinternal.cpp"
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

#ifdef CHECK_INTERNAL

#include "checkinternal.h"

#include "astutils.h"
#include "errortypes.h"
#include "settings.h"
#include "symboldatabase.h"
#include "token.h"
#include "tokenize.h"

#include <cstring>
#include <set>
#include <vector>

// Register this check class (by creating a static instance of it).
// Disabled in release builds
namespace {
    CheckInternal instance;
}

void CheckInternal::checkTokenMatchPatterns()
{
    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();
    for (const Scope *scope : symbolDatabase->functionScopes) {
        for (const Token* tok = scope->bodyStart->next(); tok != scope->bodyEnd; tok = tok->next()) {
            if (!match1(tok) && !match2(tok))
                continue;

            const std::string& funcname = tok->strAt(2);

            // Get pattern string
            const Token *patternTok = tok->tokAt(4)->nextArgument();
            if (!patternTok || patternTok->tokType() != Token::eString)
                continue;

            const std::string pattern = patternTok->strValue();
            if (pattern.empty()) {
                simplePatternError(tok, pattern, funcname);
                continue;
            }

            if (pattern.find("||") != std::string::npos || pattern.find(" | ") != std::string::npos || pattern[0] == '|' || (pattern[pattern.length() - 1] == '|' && pattern[pattern.length() - 2] == ' '))
                orInComplexPattern(tok, pattern, funcname);

            // Check for signs of complex patterns
            if (pattern.find_first_of("[|") != std::string::npos)
                continue;
            if (pattern.find("!!") != std::string::npos)
                continue;

            bool complex = false;
            size_t index = pattern.find('%');
            while (index != std::string::npos) {
                if (pattern.length() <= index + 2) {
                    complex = true;
                    break;
                }
                if (pattern[index + 1] == 'o' && pattern[index + 2] == 'r') // %or% or %oror%
                    index = pattern.find('%', index + 1);
                else {
                    complex = true;
                    break;
                }
                index = pattern.find('%', index + 1);
            }
            if (!complex)
                simplePatternError(tok, pattern, funcname);
        }
    }
}

void CheckInternal::checkRedundantTokCheck()
{
    for (const Token *tok = mTokenizer->tokens(); tok; tok = tok->next()) {
        if (match3(tok)) {
            // in code like
            // if (tok->previous() && Token::match(tok->previous(), "bla")) {}
            // the first tok->previous() check is redundant
            const Token *astOp1 = tok->astOperand1();
            const Token *astOp2 = getArguments(tok->tokAt(3))[0];
            if (match4(astOp1)) {
                astOp1 = astOp1->astOperand2();
            }
            if (astOp1->expressionString() == astOp2->expressionString()) {
                checkRedundantTokCheckError(astOp2);
            }
            // if (!tok || !Token::match(tok, "foo"))
        } else if (match5(tok)) {
            const Token *negTok = tok->next()->astParent()->astOperand1();
            if (match6(negTok)) {
                negTok = negTok->astOperand2();
            }
            // the first tok condition is negated
            if (match7(negTok)) {
                const Token *astOp1 = negTok->astOperand1();
                const Token *astOp2 = getArguments(tok->tokAt(4))[0];

                if (astOp1->expressionString() == astOp2->expressionString()) {
                    checkRedundantTokCheckError(astOp2);
                }
            }
        }
    }
}


void CheckInternal::checkRedundantTokCheckError(const Token* tok)
{
    reportError(tok, Severity::style, "redundantTokCheck",
                "Unnecessary check of \"" + (tok? tok->expressionString(): "") + "\", match-function already checks if it is null.");
}

void CheckInternal::checkTokenSimpleMatchPatterns()
{
    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();
    for (const Scope* scope : symbolDatabase->functionScopes) {
        for (const Token* tok = scope->bodyStart->next(); tok != scope->bodyEnd; tok = tok->next()) {
            if (!match8(tok) && !match9(tok))
                continue;

            const std::string& funcname = tok->strAt(2);

            // Get pattern string
            const Token *patternTok = tok->tokAt(4)->nextArgument();
            if (!patternTok || patternTok->tokType() != Token::eString)
                continue;

            const std::string pattern = patternTok->strValue();
            if (pattern.empty()) {
                complexPatternError(tok, pattern, funcname);
                continue;
            }

            // Check for [xyz] usage - but exclude standalone square brackets
            unsigned int char_count = 0;
            for (const char c : pattern) {
                if (c == ' ') {
                    char_count = 0;
                } else if (c == ']') {
                    if (char_count > 0) {
                        complexPatternError(tok, pattern, funcname);
                        continue;
                    }
                } else {
                    ++char_count;
                }
            }

            // Check | usage: Count characters before the symbol
            char_count = 0;
            for (const char c : pattern) {
                if (c == ' ') {
                    char_count = 0;
                } else if (c == '|') {
                    if (char_count > 0) {
                        complexPatternError(tok, pattern, funcname);
                        continue;
                    }
                } else {
                    ++char_count;
                }
            }

            // Check for real errors
            if (pattern.length() > 1) {
                for (size_t j = 0; j < pattern.length() - 1; j++) {
                    if (pattern[j] == '%' && pattern[j + 1] != ' ')
                        complexPatternError(tok, pattern, funcname);
                    else if (pattern[j] == '!' && pattern[j + 1] == '!')
                        complexPatternError(tok, pattern, funcname);
                }
            }
        }
    }
}

namespace {
    const std::set<std::string> knownPatterns = {
        "%any%"
        , "%assign%"
        , "%bool%"
        , "%char%"
        , "%comp%"
        , "%num%"
        , "%op%"
        , "%cop%"
        , "%or%"
        , "%oror%"
        , "%str%"
        , "%type%"
        , "%name%"
        , "%var%"
        , "%varid%"
    };
}

void CheckInternal::checkMissingPercentCharacter()
{
    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();
    for (const Scope* scope : symbolDatabase->functionScopes) {
        for (const Token* tok = scope->bodyStart->next(); tok != scope->bodyEnd; tok = tok->next()) {
            if (!match1(tok) && !match2(tok))
                continue;

            const std::string& funcname = tok->strAt(2);

            // Get pattern string
            const Token *patternTok = tok->tokAt(4)->nextArgument();
            if (!patternTok || patternTok->tokType() != Token::eString)
                continue;

            const std::string pattern = patternTok->strValue();

            for (auto knownPattern = knownPatterns.cbegin(); knownPattern != knownPatterns.cend(); ++knownPattern) {
                const std::string brokenPattern = knownPattern->substr(0, knownPattern->size() - 1);

                std::string::size_type pos = 0;
                while ((pos = pattern.find(brokenPattern, pos)) != std::string::npos) {
                    // Check if it's the full pattern
                    if (pattern.find(*knownPattern, pos) != pos) {
                        // Known whitelist of substrings
                        if ((brokenPattern == MatchCompiler::makeConstString("%var") && pattern.find("%varid%", pos) == pos) ||
                            (brokenPattern == MatchCompiler::makeConstString("%or") && pattern.find("%oror%", pos) == pos)) {
                            ++pos;
                            continue;
                        }

                        missingPercentCharacterError(tok, pattern, funcname);
                    }

                    ++pos;
                }
            }
        }
    }
}

void CheckInternal::checkUnknownPattern()
{
    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();
    for (const Scope* scope : symbolDatabase->functionScopes) {
        for (const Token* tok = scope->bodyStart->next(); tok != scope->bodyEnd; tok = tok->next()) {
            if (!match1(tok) && !match2(tok))
                continue;

            // Get pattern string
            const Token *patternTok = tok->tokAt(4)->nextArgument();
            if (!patternTok || patternTok->tokType() != Token::eString)
                continue;

            const std::string pattern = patternTok->strValue();
            bool inBrackets = false;

            for (std::string::size_type j = 0; j < pattern.length() - 1; j++) {
                if (pattern[j] == '[' && (j == 0 || pattern[j - 1] == ' '))
                    inBrackets = true;
                else if (pattern[j] == ']')
                    inBrackets = false;
                else if (pattern[j] == '%' && pattern[j + 1] != ' ' && pattern[j + 1] != '|' && !inBrackets) {
                    const std::string::size_type end = pattern.find('%', j + 1);
                    if (end != std::string::npos) {
                        const std::string s = pattern.substr(j, end - j + 1);
                        if (knownPatterns.find(s) == knownPatterns.end())
                            unknownPatternError(tok, s);
                    }
                }
            }
        }
    }
}

void CheckInternal::checkRedundantNextPrevious()
{
    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();
    for (const Scope* scope : symbolDatabase->functionScopes) {
        for (const Token* tok = scope->bodyStart->next(); tok != scope->bodyEnd; tok = tok->next()) {
            if (tok->str() != MatchCompiler::makeConstString("."))
                continue;
            tok = tok->next();

            if (match10(tok) || match11(tok) ||
                (match13(tok) && match12(tok->linkAt(1)))) {
                const std::string& func1 = tok->str();
                const std::string& func2 = tok->linkAt(1)->strAt(2);

                if ((func2 == MatchCompiler::makeConstString("previous") || func2 == MatchCompiler::makeConstString("next") || func2 == MatchCompiler::makeConstString("str") || func2 == MatchCompiler::makeConstString("link")) && tok->linkAt(1)->strAt(4) != MatchCompiler::makeConstString(")"))
                    continue;

                redundantNextPreviousError(tok, func1, func2);
            }
        }
    }
}

void CheckInternal::checkExtraWhitespace()
{
    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();
    for (const Scope* scope : symbolDatabase->functionScopes) {
        for (const Token* tok = scope->bodyStart->next(); tok != scope->bodyEnd; tok = tok->next()) {
            if (!match14(tok))
                continue;

            const std::string& funcname = tok->strAt(2);

            // Get pattern string
            const Token *patternTok = tok->tokAt(4)->nextArgument();
            if (!patternTok || patternTok->tokType() != Token::eString)
                continue;

            const std::string pattern = patternTok->strValue();
            if (!pattern.empty() && (pattern[0] == ' ' || *pattern.crbegin() == ' '))
                extraWhitespaceError(tok, pattern, funcname);

            // two whitespaces or more
            if (pattern.find("  ") != std::string::npos)
                extraWhitespaceError(tok, pattern, funcname);
        }
    }
}

void CheckInternal::multiComparePatternError(const Token* tok, const std::string& pattern, const std::string &funcname)
{
    reportError(tok, Severity::error, "multiComparePatternError",
                "Bad multicompare pattern (a %cmd% must be first unless it is %or%,%op%,%cop%,%name%,%oror%) inside Token::" + funcname + "() call: \"" + pattern + "\""
                );
}

void CheckInternal::simplePatternError(const Token* tok, const std::string& pattern, const std::string &funcname)
{
    reportError(tok, Severity::warning, "simplePatternError",
                "Found simple pattern inside Token::" + funcname + "() call: \"" + pattern + "\""
                );
}

void CheckInternal::complexPatternError(const Token* tok, const std::string& pattern, const std::string &funcname)
{
    reportError(tok, Severity::error, "complexPatternError",
                "Found complex pattern inside Token::" + funcname + "() call: \"" + pattern + "\""
                );
}

void CheckInternal::missingPercentCharacterError(const Token* tok, const std::string& pattern, const std::string& funcname)
{
    reportError(tok, Severity::error, "missingPercentCharacter",
                "Missing percent end character in Token::" + funcname + "() pattern: \"" + pattern + "\""
                );
}

void CheckInternal::unknownPatternError(const Token* tok, const std::string& pattern)
{
    reportError(tok, Severity::error, "unknownPattern",
                "Unknown pattern used: \"" + pattern + "\"");
}

void CheckInternal::redundantNextPreviousError(const Token* tok, const std::string& func1, const std::string& func2)
{
    reportError(tok, Severity::style, "redundantNextPrevious",
                "Call to 'Token::" + func1 + "()' followed by 'Token::" + func2 + "()' can be simplified.");
}

void CheckInternal::orInComplexPattern(const Token* tok, const std::string& pattern, const std::string &funcname)
{
    reportError(tok, Severity::error, "orInComplexPattern",
                "Token::" + funcname + "() pattern \"" + pattern + "\" contains \"||\" or \"|\". Replace it by \"%oror%\" or \"%or%\".");
}

void CheckInternal::extraWhitespaceError(const Token* tok, const std::string& pattern, const std::string &funcname)
{
    reportError(tok, Severity::warning, "extraWhitespaceError",
                "Found extra whitespace inside Token::" + funcname + "() call: \"" + pattern + "\""
                );
}

void CheckInternal::runChecks(const Tokenizer &tokenizer, ErrorLogger *errorLogger)
{
    if (!tokenizer.getSettings().checks.isEnabled(Checks::internalCheck))
        return;

    CheckInternal checkInternal(&tokenizer, &tokenizer.getSettings(), errorLogger);

    checkInternal.checkTokenMatchPatterns();
    checkInternal.checkTokenSimpleMatchPatterns();
    checkInternal.checkMissingPercentCharacter();
    checkInternal.checkUnknownPattern();
    checkInternal.checkRedundantNextPrevious();
    checkInternal.checkExtraWhitespace();
    checkInternal.checkRedundantTokCheck();
}

void CheckInternal::getErrorMessages(ErrorLogger *errorLogger, const Settings *settings) const
{
    CheckInternal c(nullptr, settings, errorLogger);
    c.multiComparePatternError(nullptr, ";|%type%", "Match");
    c.simplePatternError(nullptr, "class {", "Match");
    c.complexPatternError(nullptr, "%type% ( )", "Match");
    c.missingPercentCharacterError(nullptr, "%num", "Match");
    c.unknownPatternError(nullptr, "%typ");
    c.redundantNextPreviousError(nullptr, "previous", "next");
    c.orInComplexPattern(nullptr, "||", "Match");
    c.extraWhitespaceError(nullptr, "%str% ", "Match");
    c.checkRedundantTokCheckError(nullptr);
}

#endif // #ifdef CHECK_INTERNAL
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
