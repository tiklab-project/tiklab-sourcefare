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
// pattern: sizeof ( %num% )
MAYBE_UNUSED static inline bool match1(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
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
// pattern: sizeof %num%
MAYBE_UNUSED static inline bool match2(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isNumber())
        return false;
    return true;
}
// pattern: sizeof ( %var% )
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    return true;
}
// pattern: sizeof %var% !![
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (tok && tok->str() == MatchCompiler::makeConstString("["))
        return false;
    return true;
}
// pattern: %name% (
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: %var% =
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: > ( %name% (
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
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
// pattern: memset (
MAYBE_UNUSED static inline bool match8(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("memset")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: memcpy|memcmp|memmove|strncpy|strncmp|strncat (
MAYBE_UNUSED static inline bool match9(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("memcpy")) || (tok->str() == MatchCompiler::makeConstString("memcmp")) || (tok->str() == MatchCompiler::makeConstString("memmove")) || (tok->str() == MatchCompiler::makeConstString("strncpy")) || (tok->str() == MatchCompiler::makeConstString("strncmp")) || (tok->str() == MatchCompiler::makeConstString("strncat"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: / sizeof
MAYBE_UNUSED static inline bool match10(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("/")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    return true;
}
// pattern: sizeof (
MAYBE_UNUSED static inline bool match11(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: (
MAYBE_UNUSED static inline bool match12(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: sizeof
MAYBE_UNUSED static inline bool match13(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    return true;
}
// pattern: %var% ::|.
MAYBE_UNUSED static inline bool match14(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("::")) || (tok->str() == MatchCompiler::makeConstString("."))))
        return false;
    return true;
}
// pattern: sizeof ( &
MAYBE_UNUSED static inline bool match15(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")))
        return false;
    return true;
}
// pattern: sizeof (|&
MAYBE_UNUSED static inline bool match16(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&"))))
        return false;
    return true;
}
// pattern: %var% [|(
MAYBE_UNUSED static inline bool match17(const Token* tok) {
    if (!tok || !(tok->varId() != 0))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: sizeof (| sizeof
MAYBE_UNUSED static inline bool match18(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    tok = tok->next();
    if (tok && (((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    return true;
}
// pattern: ( void )
MAYBE_UNUSED static inline bool match19(const Token* tok) {
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
// pattern: static_cast < void >
MAYBE_UNUSED static inline bool match20(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("static_cast")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword || tok->tokType() == Token::eType) && tok->str() == MatchCompiler::makeConstString("void")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">")))
        return false;
    return true;
}
// pattern: [|*
MAYBE_UNUSED static inline bool match21(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eExtendedOp || tok->tokType() == Token::eLambda) && tok->str() == MatchCompiler::makeConstString("[")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*"))))
        return false;
    return true;
}
// pattern: ) * sizeof
MAYBE_UNUSED static inline bool match22(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(")")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
        return false;
    return true;
}
// pattern: sizeof ( void )
MAYBE_UNUSED static inline bool match23(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eKeyword) && tok->str() == MatchCompiler::makeConstString("sizeof")))
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
// pattern: +|++|--|+=|-=
MAYBE_UNUSED static inline bool match24(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("++")) || ((tok->tokType() == Token::eIncDecOp) && tok->str() == MatchCompiler::makeConstString("--")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("+=")) || ((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("-="))))
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/checksizeof.cpp"
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
#include "checksizeof.h"

#include "errortypes.h"
#include "library.h"
#include "settings.h"
#include "symboldatabase.h"
#include "token.h"
#include "tokenize.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>

//---------------------------------------------------------------------------

// Register this check class (by creating a static instance of it)
namespace {
    CheckSizeof instance;
}

// CWE IDs used:
static const CWE CWE467(467U);   // Use of sizeof() on a Pointer Type
static const CWE CWE682(682U);   // Incorrect Calculation
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void CheckSizeof::checkSizeofForNumericParameter()
{
    if (!mSettings->severity.isEnabled(Severity::warning))
        return;

    logChecker("CheckSizeof::checkSizeofForNumericParameter"); // warning

    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();
    for (const Scope * scope : symbolDatabase->functionScopes) {
        for (const Token* tok = scope->bodyStart->next(); tok != scope->bodyEnd; tok = tok->next()) {
            if (match1(tok) ||
                match2(tok)) {
                sizeofForNumericParameterError(tok);
            }
        }
    }
}

void CheckSizeof::sizeofForNumericParameterError(const Token *tok)
{
    reportError(tok, Severity::warning,
                "sizeofwithnumericparameter", "Suspicious usage of 'sizeof' with a numeric constant as parameter.\n"
                "It is unusual to use a constant value with sizeof. For example, 'sizeof(10)'"
                " returns 4 (in 32-bit systems) or 8 (in 64-bit systems) instead of 10. 'sizeof('A')'"
                " and 'sizeof(char)' can return different results.", CWE682, Certainty::normal);
}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void CheckSizeof::checkSizeofForArrayParameter()
{
    if (!mSettings->severity.isEnabled(Severity::warning))
        return;

    logChecker("CheckSizeof::checkSizeofForArrayParameter"); // warning

    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();
    for (const Scope * scope : symbolDatabase->functionScopes) {
        for (const Token* tok = scope->bodyStart->next(); tok != scope->bodyEnd; tok = tok->next()) {
            if (match3(tok) ||
                match4(tok)) {
                const Token* varTok = tok->next();
                if (varTok->str() == MatchCompiler::makeConstString("(")) {
                    varTok = varTok->next();
                }

                const Variable *var = varTok->variable();
                if (var && var->isArray() && var->isArgument() && !var->isReference())
                    sizeofForArrayParameterError(tok);
            }
        }
    }
}

void CheckSizeof::sizeofForArrayParameterError(const Token *tok)
{
    reportError(tok, Severity::warning,
                "sizeofwithsilentarraypointer", "Using 'sizeof' on array given as function argument "
                "returns size of a pointer.\n"
                "Using 'sizeof' for array given as function argument returns the size of a pointer. "
                "It does not return the size of the whole array in bytes as might be "
                "expected. For example, this code:\n"
                "     int f(char a[100]) {\n"
                "         return sizeof(a);\n"
                "     }\n"
                "returns 4 (in 32-bit systems) or 8 (in 64-bit systems) instead of 100 (the "
                "size of the array in bytes).", CWE467, Certainty::normal
                );
}

void CheckSizeof::checkSizeofForPointerSize()
{
    if (!mSettings->severity.isEnabled(Severity::warning))
        return;

    logChecker("CheckSizeof::checkSizeofForPointerSize"); // warning

    const SymbolDatabase *symbolDatabase = mTokenizer->getSymbolDatabase();
    for (const Scope * scope : symbolDatabase->functionScopes) {
        for (const Token* tok = scope->bodyStart; tok != scope->bodyEnd; tok = tok->next()) {
            const Token* tokSize;
            const Token* tokFunc;
            const Token *variable = nullptr;
            const Token *variable2 = nullptr;

            // Find any function that may use sizeof on a pointer
            // Once leaving those tests, it is mandatory to have:
            // - variable matching the used pointer
            // - tokVar pointing on the argument where sizeof may be used
            if (match5(tok->tokAt(2)) && mSettings->library.getAllocFuncInfo(tok->tokAt(2))) {
                if (match6(tok))
                    variable = tok;
                else if (tok->strAt(1) == MatchCompiler::makeConstString(")") && match6(tok->linkAt(1)->tokAt(-2)))
                    variable = tok->linkAt(1)->tokAt(-2);
                else if (tok->link() && match7(tok) && mSettings->library.getAllocFuncInfo(tok->tokAt(2)) && match6(tok->link()->tokAt(-3)))
                    variable = tok->link()->tokAt(-3);
                tokSize = tok->tokAt(4);
                tokFunc = tok->tokAt(2);
            } else if (match8(tok) && tok->strAt(-1) != MatchCompiler::makeConstString(".")) {
                variable = tok->tokAt(2);
                tokSize = variable->nextArgument();
                if (tokSize)
                    tokSize = tokSize->nextArgument();
                tokFunc = tok;
            } else if (match9(tok) && tok->strAt(-1) != MatchCompiler::makeConstString(".")) {
                variable = tok->tokAt(2);
                variable2 = variable->nextArgument();
                if (!variable2)
                    continue;
                tokSize = variable2->nextArgument();
                tokFunc = tok;
            } else {
                continue;
            }

            if (tokSize && tokFunc->str() == MatchCompiler::makeConstString("calloc"))
                tokSize = tokSize->nextArgument();

            if (tokSize) {
                const Token * const paramsListEndTok = tokFunc->linkAt(1);
                for (const Token* tok2 = tokSize; tok2 != paramsListEndTok; tok2 = tok2->next()) {
                    if (match10(tok2)) {
                        // Allow division with sizeof(char)
                        if (match11(tok2->next())) {
                            const Token *sztok = tok2->tokAt(2)->astOperand2();
                            const ValueType *vt = ((sztok != nullptr) ? sztok->valueType() : nullptr);
                            if (vt && vt->type == ValueType::CHAR && vt->pointer == 0)
                                continue;
                        }
                        auto hasMultiplication = [](const Token* parTok) -> bool {
                            while (parTok) { // Allow division if followed by multiplication
                                if (parTok->isArithmeticalOp() && parTok->str() == MatchCompiler::makeConstString("*")) {
                                    const Token* szToks[] = { parTok->astOperand1(), parTok->astOperand2() };
                                    if (std::any_of(std::begin(szToks), std::end(szToks), [](const Token* szTok) {
                                        return match12(szTok) && match13(szTok->previous());
                                    }))
                                        return true;
                                }
                                parTok = parTok->astParent();
                            }
                            return false;
                        };
                        if (hasMultiplication(tok2->astParent()))
                            continue;

                        divideBySizeofError(tok2, tokFunc->str());
                    }
                }
            }

            if (!variable || !tokSize)
                continue;

            while (match14(variable))
                variable = variable->tokAt(2);

            while (match14(variable2))
                variable2 = variable2->tokAt(2);

            if (!variable)
                continue;

            // Ensure the variables are in the symbol database
            // Also ensure the variables are pointers
            // Only keep variables which are pointers
            const Variable *var = variable->variable();
            if (!var || !var->isPointer() || var->isArray()) {
                variable = nullptr;
            }

            if (variable2) {
                var = variable2->variable();
                if (!var || !var->isPointer() || var->isArray()) {
                    variable2 = nullptr;
                }
            }

            // If there are no pointer variable at this point, there is
            // no need to continue
            if (variable == nullptr && variable2 == nullptr) {
                continue;
            }

            // Jump to the next sizeof token in the function and in the parameter
            // This is to allow generic operations with sizeof
            for (; tokSize && tokSize->str() != MatchCompiler::makeConstString(")") && tokSize->str() != MatchCompiler::makeConstString(",") && tokSize->str() != MatchCompiler::makeConstString("sizeof"); tokSize = tokSize->next()) {}

            if (tokSize->str() != MatchCompiler::makeConstString("sizeof"))
                continue;

            // Now check for the sizeof usage: Does the level of pointer indirection match?
            const Token * const tokLink = tokSize->linkAt(1);
            if (tokLink && tokLink->strAt(-1) == MatchCompiler::makeConstString("*")) {
                if (variable && variable->valueType() && variable->valueType()->pointer == 1 && variable->valueType()->type != ValueType::VOID)
                    sizeofForPointerError(variable, variable->str());
                else if (variable2 && variable2->valueType() && variable2->valueType()->pointer == 1 && variable2->valueType()->type != ValueType::VOID)
                    sizeofForPointerError(variable2, variable2->str());
            }

            if (match15(tokSize))
                tokSize = tokSize->tokAt(3);
            else if (match16(tokSize))
                tokSize = tokSize->tokAt(2);
            else
                tokSize = tokSize->next();

            while (match14(tokSize))
                tokSize = tokSize->tokAt(2);

            if (match17(tokSize))
                continue;

            // Now check for the sizeof usage again. Once here, everything using sizeof(varid) or sizeof(&varid)
            // looks suspicious
            if (variable && tokSize->varId() == variable->varId())
                sizeofForPointerError(variable, variable->str());
            if (variable2 && tokSize->varId() == variable2->varId())
                sizeofForPointerError(variable2, variable2->str());
        }
    }
}

void CheckSizeof::sizeofForPointerError(const Token *tok, const std::string &varname)
{
    reportError(tok, Severity::warning, "pointerSize",
                "Size of pointer '" + varname + "' used instead of size of its data.\n"
                "Size of pointer '" + varname + "' used instead of size of its data. "
                "This is likely to lead to a buffer overflow. You probably intend to "
                "write 'sizeof(*" + varname + ")'.", CWE467, Certainty::normal);
}

void CheckSizeof::divideBySizeofError(const Token *tok, const std::string &memfunc)
{
    reportError(tok, Severity::warning, "sizeofDivisionMemfunc",
                "Division by result of sizeof(). " + memfunc + "() expects a size in bytes, did you intend to multiply instead?", CWE682, Certainty::normal);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CheckSizeof::sizeofsizeof()
{
    if (!mSettings->severity.isEnabled(Severity::warning))
        return;

    logChecker("CheckSizeof::sizeofsizeof"); // warning

    for (const Token *tok = mTokenizer->tokens(); tok; tok = tok->next()) {
        if (match18(tok)) {
            sizeofsizeofError(tok);
            tok = tok->next();
        }
    }
}

void CheckSizeof::sizeofsizeofError(const Token *tok)
{
    reportError(tok, Severity::warning,
                "sizeofsizeof", "Calling 'sizeof' on 'sizeof'.\n"
                "Calling sizeof for 'sizeof looks like a suspicious code and "
                "most likely there should be just one 'sizeof'. The current "
                "code is equivalent to 'sizeof(size_t)'", CWE682, Certainty::normal);
}

//-----------------------------------------------------------------------------

void CheckSizeof::sizeofCalculation()
{
    if (!mSettings->severity.isEnabled(Severity::warning))
        return;

    logChecker("CheckSizeof::sizeofCalculation"); // warning

    const bool printInconclusive = mSettings->certainty.isEnabled(Certainty::inconclusive);

    for (const Token *tok = mTokenizer->tokens(); tok; tok = tok->next()) {
        if (!match11(tok))
            continue;

        // ignore if the `sizeof` result is cast to void inside a macro, i.e. the calculation is
        // expected to be parsed but skipped, such as in a disabled custom ASSERT() macro
        if (tok->isExpandedMacro() && tok->previous()) {
            const Token *cast_end = (tok->strAt(-1) == MatchCompiler::makeConstString("(")) ? tok->previous() : tok;
            if (match19(cast_end->tokAt(-3)) ||
                match20(cast_end->tokAt(-4))) {
                continue;
            }
        }

        const Token *argument = tok->next()->astOperand2();
        if (!argument || !argument->isCalculation())
            continue;

        bool inconclusive = false;
        if (argument->isExpandedMacro())
            inconclusive = true;
        else if (tok->next()->isExpandedMacro())
            inconclusive = true;

        if (!inconclusive || printInconclusive)
            sizeofCalculationError(argument, inconclusive);
    }
}

void CheckSizeof::sizeofCalculationError(const Token *tok, bool inconclusive)
{
    reportError(tok, Severity::warning,
                "sizeofCalculation", "Found calculation inside sizeof().", CWE682, inconclusive ? Certainty::inconclusive : Certainty::normal);
}

//-----------------------------------------------------------------------------

void CheckSizeof::sizeofFunction()
{
    if (!mSettings->severity.isEnabled(Severity::warning) && !mSettings->isPremiumEnabled("sizeofFunctionCall"))
        return;

    logChecker("CheckSizeof::sizeofFunction"); // warning

    for (const Token *tok = mTokenizer->tokens(); tok; tok = tok->next()) {
        if (match11(tok)) {

            // ignore if the `sizeof` result is cast to void inside a macro, i.e. the calculation is
            // expected to be parsed but skipped, such as in a disabled custom ASSERT() macro
            if (tok->isExpandedMacro() && tok->previous()) {
                const Token *cast_end = (tok->strAt(-1) == MatchCompiler::makeConstString("(")) ? tok->previous() : tok;
                if (match19(cast_end->tokAt(-3)) ||
                    match20(cast_end->tokAt(-4))) {
                    continue;
                }
            }

            if (const Token *argument = tok->next()->astOperand2()) {
                const Token *checkToken = argument->previous();
                if (checkToken->tokType() == Token::eName)
                    continue;
                const Function * fun = checkToken->function();
                // Don't report error if the function is overloaded
                if (fun && fun->nestedIn->functionMap.count(checkToken->str()) == 1) {
                    sizeofFunctionError(tok);
                }
            }
        }
    }
}

void CheckSizeof::sizeofFunctionError(const Token *tok)
{
    reportError(tok, Severity::warning,
                "sizeofFunctionCall", "Found function call inside sizeof().", CWE682, Certainty::normal);
}

//-----------------------------------------------------------------------------
// Check for code like sizeof()*sizeof() or sizeof(ptr)/value
//-----------------------------------------------------------------------------
void CheckSizeof::suspiciousSizeofCalculation()
{
    if (!mSettings->severity.isEnabled(Severity::warning) || !mSettings->certainty.isEnabled(Certainty::inconclusive))
        return;

    logChecker("CheckSizeof::suspiciousSizeofCalculation"); // warning,inconclusive

    for (const Token *tok = mTokenizer->tokens(); tok; tok = tok->next()) {
        if (match11(tok)) {
            const Token* lPar = tok->astParent();
            if (lPar && lPar->str() == MatchCompiler::makeConstString("(")) {
                const Token* const rPar = lPar->link();
                const Token* varTok = lPar->astOperand2();
                int derefCount = 0;
                while (match21(varTok)) {
                    ++derefCount;
                    varTok = varTok->astOperand1();
                }
                if (lPar->astParent() && lPar->astParent()->str() == MatchCompiler::makeConstString("/")) {
                    const Variable* var = varTok ? varTok->variable() : nullptr;
                    if (var && var->isPointer() && !var->isArray() && !(var->valueType() && var->valueType()->pointer <= derefCount))
                        divideSizeofError(tok);
                }
                else if (match22(rPar) && rPar->next()->astOperand1() == tok->next())
                    multiplySizeofError(tok);
            }
        }
    }
}

void CheckSizeof::multiplySizeofError(const Token *tok)
{
    reportError(tok, Severity::warning,
                "multiplySizeof", "Multiplying sizeof() with sizeof() indicates a logic error.", CWE682, Certainty::inconclusive);
}

void CheckSizeof::divideSizeofError(const Token *tok)
{
    reportError(tok, Severity::warning,
                "divideSizeof", "Division of result of sizeof() on pointer type.\n"
                "Division of result of sizeof() on pointer type. sizeof() returns the size of the pointer, "
                "not the size of the memory area it points to.", CWE682, Certainty::inconclusive);
}

void CheckSizeof::sizeofVoid()
{
    if (!mSettings->severity.isEnabled(Severity::portability))
        return;

    logChecker("CheckSizeof::sizeofVoid"); // portability

    for (const Token *tok = mTokenizer->tokens(); tok; tok = tok->next()) {
        if (match23(tok)) {
            sizeofVoidError(tok);
        } else if (match11(tok) && tok->next()->astOperand2()) {
            const ValueType *vt = tok->next()->astOperand2()->valueType();
            if (vt && vt->type == ValueType::Type::VOID && vt->pointer == 0U)
                sizeofDereferencedVoidPointerError(tok, tok->strAt(3));
        } else if (tok->str() == MatchCompiler::makeConstString("-")) {
            // only warn for: 'void *' - 'integral'
            const ValueType *vt1  = tok->astOperand1() ? tok->astOperand1()->valueType() : nullptr;
            const ValueType *vt2  = tok->astOperand2() ? tok->astOperand2()->valueType() : nullptr;
            const bool op1IsvoidPointer = (vt1 && vt1->type == ValueType::Type::VOID && vt1->pointer == 1U);
            const bool op2IsIntegral    = (vt2 && vt2->isIntegral() && vt2->pointer == 0U);
            if (op1IsvoidPointer && op2IsIntegral)
                arithOperationsOnVoidPointerError(tok, tok->astOperand1()->expressionString(), vt1->str());
        } else if (match24(tok)) { // Arithmetic operations on variable of type "void*"
            const ValueType *vt1 = tok->astOperand1() ? tok->astOperand1()->valueType() : nullptr;
            const ValueType *vt2 = tok->astOperand2() ? tok->astOperand2()->valueType() : nullptr;

            const bool voidpointer1 = (vt1 && vt1->type == ValueType::Type::VOID && vt1->pointer == 1U);
            const bool voidpointer2 = (vt2 && vt2->type == ValueType::Type::VOID && vt2->pointer == 1U);

            if (voidpointer1)
                arithOperationsOnVoidPointerError(tok, tok->astOperand1()->expressionString(), vt1->str());

            if (!tok->isAssignmentOp() && voidpointer2)
                arithOperationsOnVoidPointerError(tok, tok->astOperand2()->expressionString(), vt2->str());
        }
    }
}

void CheckSizeof::sizeofVoidError(const Token *tok)
{
    const std::string message = "Behaviour of 'sizeof(void)' is not covered by the ISO C standard.";
    const std::string verbose = message + " A value for 'sizeof(void)' is defined only as part of a GNU C extension, which defines 'sizeof(void)' to be 1.";
    reportError(tok, Severity::portability, "sizeofVoid", message + "\n" + verbose, CWE682, Certainty::normal);
}

void CheckSizeof::sizeofDereferencedVoidPointerError(const Token *tok, const std::string &varname)
{
    const std::string message = "'*" + varname + "' is of type 'void', the behaviour of 'sizeof(void)' is not covered by the ISO C standard.";
    const std::string verbose = message + " A value for 'sizeof(void)' is defined only as part of a GNU C extension, which defines 'sizeof(void)' to be 1.";
    reportError(tok, Severity::portability, "sizeofDereferencedVoidPointer", message + "\n" + verbose, CWE682, Certainty::normal);
}

void CheckSizeof::arithOperationsOnVoidPointerError(const Token* tok, const std::string &varname, const std::string &vartype)
{
    const std::string message = "'$symbol' is of type '" + vartype + "'. When using void pointers in calculations, the behaviour is undefined.";
    const std::string verbose = message + " Arithmetic operations on 'void *' is a GNU C extension, which defines the 'sizeof(void)' to be 1.";
    reportError(tok, Severity::portability, "arithOperationsOnVoidPointer", "$symbol:" + varname + '\n' + message + '\n' + verbose, CWE467, Certainty::normal);
}

void CheckSizeof::runChecks(const Tokenizer& tokenizer, ErrorLogger* errorLogger)
{
    CheckSizeof checkSizeof(&tokenizer, &tokenizer.getSettings(), errorLogger);

    // Checks
    checkSizeof.sizeofsizeof();
    checkSizeof.sizeofCalculation();
    checkSizeof.sizeofFunction();
    checkSizeof.suspiciousSizeofCalculation();
    checkSizeof.checkSizeofForArrayParameter();
    checkSizeof.checkSizeofForPointerSize();
    checkSizeof.checkSizeofForNumericParameter();
    checkSizeof.sizeofVoid();
}

void CheckSizeof::getErrorMessages(ErrorLogger* errorLogger, const Settings* settings) const
{
    CheckSizeof c(nullptr, settings, errorLogger);
    c.sizeofForArrayParameterError(nullptr);
    c.sizeofForPointerError(nullptr, "varname");
    c.divideBySizeofError(nullptr, "memset");
    c.sizeofForNumericParameterError(nullptr);
    c.sizeofsizeofError(nullptr);
    c.sizeofCalculationError(nullptr, false);
    c.sizeofFunctionError(nullptr);
    c.multiplySizeofError(nullptr);
    c.divideSizeofError(nullptr);
    c.sizeofVoidError(nullptr);
    c.sizeofDereferencedVoidPointerError(nullptr, "varname");
    c.arithOperationsOnVoidPointerError(nullptr, "varname", "vartype");
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
