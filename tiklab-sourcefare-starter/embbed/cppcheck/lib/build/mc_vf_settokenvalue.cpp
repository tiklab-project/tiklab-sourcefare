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
// pattern: . %name% (
MAYBE_UNUSED static inline bool match1(const Token* tok) {
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
// pattern: %name% (
MAYBE_UNUSED static inline bool match2(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: {|(
MAYBE_UNUSED static inline bool match3(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: %type% (|{
MAYBE_UNUSED static inline bool match4(const Token* tok) {
    if (!tok || !(tok->isName() && tok->varId() == 0U))
        return false;
    tok = tok->next();
    if (!tok || !(((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")) || ((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{"))))
        return false;
    return true;
}
// pattern: ( %name%|::
MAYBE_UNUSED static inline bool match5(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->isName() || (tok->str() == MatchCompiler::makeConstString("::"))))
        return false;
    return true;
}
// pattern: ::
MAYBE_UNUSED static inline bool match6(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: %name% ::
MAYBE_UNUSED static inline bool match7(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    return true;
}
// pattern: const_cast|dynamic_cast|reinterpret_cast|static_cast <
MAYBE_UNUSED static inline bool match8(const Token* tok) {
    if (!tok || !((tok->str() == MatchCompiler::makeConstString("const_cast")) || (tok->str() == MatchCompiler::makeConstString("dynamic_cast")) || (tok->str() == MatchCompiler::makeConstString("reinterpret_cast")) || (tok->str() == MatchCompiler::makeConstString("static_cast"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("<")))
        return false;
    return true;
}
// pattern: +|-
MAYBE_UNUSED static inline bool match9(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-"))))
        return false;
    return true;
}
// pattern: {|%str%
MAYBE_UNUSED static inline bool match10(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")) || (tok->tokType() == Token::eString)))
        return false;
    return true;
}
// pattern: ,
MAYBE_UNUSED static inline bool match11(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString(",")))
        return false;
    return true;
}
// pattern: %name%|> (
MAYBE_UNUSED static inline bool match12(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eBracket || tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString(">"))))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    return true;
}
// pattern: {
MAYBE_UNUSED static inline bool match13(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: ( %name%
MAYBE_UNUSED static inline bool match14(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("(")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: %name%|(
MAYBE_UNUSED static inline bool match15(const Token* tok) {
    if (!tok || !(tok->isName() || ((tok->tokType() == Token::eExtendedOp) && tok->str() == MatchCompiler::makeConstString("("))))
        return false;
    return true;
}
// pattern: *
MAYBE_UNUSED static inline bool match16(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("*")))
        return false;
    return true;
}
// pattern: =
MAYBE_UNUSED static inline bool match17(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    return true;
}
// pattern: +|==|!=
MAYBE_UNUSED static inline bool match18(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("+")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("==")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("!="))))
        return false;
    return true;
}
// pattern: %comp%
MAYBE_UNUSED static inline bool match19(const Token* tok) {
    if (!tok || !tok->isComparisonOp())
        return false;
    return true;
}
// pattern: ==
MAYBE_UNUSED static inline bool match20(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("==")))
        return false;
    return true;
}
// pattern: !=
MAYBE_UNUSED static inline bool match21(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("!=")))
        return false;
    return true;
}
// pattern: . %var%
MAYBE_UNUSED static inline bool match22(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(".")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->varId() != 0))
        return false;
    return true;
}
// pattern: dynamic_cast
MAYBE_UNUSED static inline bool match23(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("dynamic_cast")))
        return false;
    return true;
}
// pattern: %name%
MAYBE_UNUSED static inline bool match24(const Token* tok) {
    if (!tok || !tok->isName())
        return false;
    return true;
}
// pattern: [&*]
MAYBE_UNUSED static inline bool match25(const Token* tok) {
    if (!tok || tok->str().size() != 1U || !strchr("&*", tok->str()[0]))
        return false;
    return true;
}
// pattern: &&
MAYBE_UNUSED static inline bool match26(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eLogicalOp) && tok->str() == MatchCompiler::makeConstString("&&")))
        return false;
    return true;
}
// pattern: ||
MAYBE_UNUSED static inline bool match27(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("||")))
        return false;
    return true;
}
// pattern: &|^|%|<<|>>|==|!=|%or%
MAYBE_UNUSED static inline bool match28(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("&")) || ((tok->tokType() == Token::eBitOp) && tok->str() == MatchCompiler::makeConstString("^")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("%")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("<<")) || ((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString(">>")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("==")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("!=")) || (tok->tokType() == Token::eBitOp && tok->str() == MatchCompiler::makeConstString("|") )))
        return false;
    return true;
}
// pattern: ==|!=
MAYBE_UNUSED static inline bool match29(const Token* tok) {
    if (!tok || !(((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("==")) || ((tok->tokType() == Token::eComparisonOp) && tok->str() == MatchCompiler::makeConstString("!="))))
        return false;
    return true;
}
// pattern: %str%
MAYBE_UNUSED static inline bool match30(const Token* tok) {
    if (!tok || !(tok->tokType() == Token::eString))
        return false;
    return true;
}
// pattern: %op%
MAYBE_UNUSED static inline bool match31(const Token* tok) {
    if (!tok || !tok->isOp())
        return false;
    return true;
}
// pattern: -
MAYBE_UNUSED static inline bool match32(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eArithmeticalOp) && tok->str() == MatchCompiler::makeConstString("-")))
        return false;
    return true;
}
// pattern: = {
MAYBE_UNUSED static inline bool match33(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eAssignmentOp) && tok->str() == MatchCompiler::makeConstString("=")))
        return false;
    tok = tok->next();
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("{")))
        return false;
    return true;
}
// pattern: } ;
MAYBE_UNUSED static inline bool match34(const Token* tok) {
    if (!tok || !((tok->tokType() == Token::eBracket) && tok->str() == MatchCompiler::makeConstString("}")))
        return false;
    tok = tok->next();
    if (!tok || !(tok->str() == MatchCompiler::makeConstString(";")))
        return false;
    return true;
}
// pattern: :: %name%
MAYBE_UNUSED static inline bool match35(const Token* tok) {
    if (!tok || !(tok->str() == MatchCompiler::makeConstString("::")))
        return false;
    tok = tok->next();
    if (!tok || !tok->isName())
        return false;
    return true;
}
#line 1 "/opt/cppcheck/cppcheck-main/lib/vf_settokenvalue.cpp"
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

#include "vf_settokenvalue.h"

#include "astutils.h"
#include "calculate.h"
#include "config.h"
#include "library.h"
#include "mathlib.h"
#include "platform.h"
#include "settings.h"
#include "symboldatabase.h"
#include "token.h"
#include "utils.h"
#include "valueflow.h"
#include "vfvalue.h"

#include "vf_common.h"

#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace ValueFlow
{
    static Library::Container::Yield getContainerYield(Token* tok, const Settings& settings, Token*& parent)
    {
        if (match1(tok) && tok->astParent() == tok->tokAt(2) && tok->astOperand1() &&
            tok->astOperand1()->valueType()) {
            const Library::Container* c = getLibraryContainer(tok->astOperand1());
            parent = tok->astParent();
            return c ? c->getYield(tok->strAt(1)) : Library::Container::Yield::NO_YIELD;
        }
        if (match2(tok->previous())) {
            parent = tok;
            if (const Library::Function* f = settings.library.getFunction(tok->previous())) {
                return f->containerYield;
            }
        }
        return Library::Container::Yield::NO_YIELD;
    }

    static Value truncateImplicitConversion(Token* parent, const Value& value, const Settings& settings)
    {
        if (!value.isIntValue() && !value.isFloatValue())
            return value;
        if (!parent)
            return value;
        if (!parent->isBinaryOp())
            return value;
        if (!parent->isConstOp())
            return value;
        if (!astIsIntegral(parent->astOperand1(), false))
            return value;
        if (!astIsIntegral(parent->astOperand2(), false))
            return value;
        const ValueType* vt1 = parent->astOperand1()->valueType();
        const ValueType* vt2 = parent->astOperand2()->valueType();
        // If the sign is the same there is no truncation
        if (vt1->sign == vt2->sign)
            return value;
        const size_t n1 = getSizeOf(*vt1, settings, ValueFlow::Accuracy::ExactOrZero);
        const size_t n2 = getSizeOf(*vt2, settings, ValueFlow::Accuracy::ExactOrZero);
        ValueType::Sign sign = ValueType::Sign::UNSIGNED;
        if (n1 < n2)
            sign = vt2->sign;
        else if (n1 > n2)
            sign = vt1->sign;
        Value v = castValue(value, sign, std::max(n1, n2) * 8);
        v.wideintvalue = value.intvalue;
        return v;
    }

    static const Token *getCastTypeStartToken(const Token *parent, const Settings& settings)
    {
        // TODO: This might be a generic utility function?
        if (!match3(parent))
            return nullptr;
        // Functional cast
        if (parent->isBinaryOp() && match4(parent->astOperand1()) &&
            parent->astOperand1()->tokType() == Token::eType && astIsPrimitive(parent))
            return parent->astOperand1();
        if (parent->str() != MatchCompiler::makeConstString("("))
            return nullptr;
        if (!parent->astOperand2() && match5(parent)) {
            const Token* ftok = parent->next();
            if (ftok->isStandardType())
                return ftok;
            if (match6(ftok))
                ftok = ftok->next();
            while (match7(ftok))
                ftok = ftok->tokAt(2);
            if (settings.library.isNotLibraryFunction(ftok))
                return parent->next();
        }
        if (parent->astOperand2() && match8(parent->astOperand1()))
            return parent->astOperand1()->tokAt(2);
        return nullptr;
    }

    static bool isNumeric(const Value& value) {
        return value.isIntValue() || value.isFloatValue();
    }

    static void setTokenValueCast(Token *parent, const ValueType &valueType, const Value &value, const Settings &settings)
    {
        if (valueType.pointer || value.isImpossible())
            setTokenValue(parent,value,settings);
        else if (valueType.type == ValueType::Type::CHAR)
            setTokenValue(parent, castValue(value, valueType.sign, settings.platform.char_bit), settings);
        else if (valueType.type == ValueType::Type::SHORT)
            setTokenValue(parent, castValue(value, valueType.sign, settings.platform.short_bit), settings);
        else if (valueType.type == ValueType::Type::INT)
            setTokenValue(parent, castValue(value, valueType.sign, settings.platform.int_bit), settings);
        else if (valueType.type == ValueType::Type::LONG)
            setTokenValue(parent, castValue(value, valueType.sign, settings.platform.long_bit), settings);
        else if (valueType.type == ValueType::Type::LONGLONG)
            setTokenValue(parent, castValue(value, valueType.sign, settings.platform.long_long_bit), settings);
        else if (valueType.isFloat() && isNumeric(value)) {
            Value floatValue = value;
            floatValue.valueType = Value::ValueType::FLOAT;
            if (value.isIntValue())
                floatValue.floatValue = static_cast<double>(value.intvalue);
            setTokenValue(parent, std::move(floatValue), settings);
        } else if (value.isIntValue()) {
            const long long charMax = settings.platform.signedCharMax();
            const long long charMin = settings.platform.signedCharMin();
            if (charMin <= value.intvalue && value.intvalue <= charMax) {
                // unknown type, but value is small so there should be no truncation etc
                setTokenValue(parent,value,settings);
            }
        }
    }

    // does the operation cause a loss of information?
    static bool isNonInvertibleOperation(const Token* tok)
    {
        return !match9(tok);
    }

    static bool isComputableValue(const Token* parent, const Value& value)
    {
        const bool noninvertible = isNonInvertibleOperation(parent);
        if (noninvertible && value.isImpossible())
            return false;
        if (!value.isIntValue() && !value.isFloatValue() && !value.isTokValue() && !value.isIteratorValue())
            return false;
        if (value.isIteratorValue() && !match9(parent))
            return false;
        if (value.isTokValue() && (!parent->isComparisonOp() || !match10(value.tokvalue)))
            return false;
        return true;
    }

    /** Set token value for cast */
    static bool isCompatibleValueTypes(Value::ValueType x, Value::ValueType y)
    {
        static const std::unordered_map<Value::ValueType,
                                        std::unordered_set<Value::ValueType, EnumClassHash>,
                                        EnumClassHash>
        compatibleTypes = {
            {Value::ValueType::INT,
             {Value::ValueType::FLOAT,
              Value::ValueType::SYMBOLIC,
              Value::ValueType::TOK}},
            {Value::ValueType::FLOAT, {Value::ValueType::INT}},
            {Value::ValueType::TOK, {Value::ValueType::INT}},
            {Value::ValueType::ITERATOR_START, {Value::ValueType::INT}},
            {Value::ValueType::ITERATOR_END, {Value::ValueType::INT}},
        };
        if (x == y)
            return true;
        auto it = compatibleTypes.find(x);
        if (it == compatibleTypes.end())
            return false;
        return it->second.count(y) > 0;
    }

    static bool isCompatibleValues(const Value& value1, const Value& value2)
    {
        if (value1.isSymbolicValue() && value2.isSymbolicValue() && value1.tokvalue->exprId() != value2.tokvalue->exprId())
            return false;
        if (!isCompatibleValueTypes(value1.valueType, value2.valueType))
            return false;
        if (value1.isKnown() || value2.isKnown())
            return true;
        if (value1.isImpossible() || value2.isImpossible())
            return false;
        if (value1.varId == 0 || value2.varId == 0)
            return true;
        if (value1.varId == value2.varId && value1.varvalue == value2.varvalue && value1.isIntValue() && value2.isIntValue())
            return true;
        return false;
    }

    /** set ValueFlow value and perform calculations if possible */
    void setTokenValue(Token* tok,
                       Value value,
                       const Settings& settings,
                       SourceLocation loc)
    {
        // Skip setting values that are too big since its ambiguous
        if (!value.isImpossible() && value.isIntValue() && value.intvalue < 0 && astIsUnsigned(tok)
            && getSizeOf(*tok->valueType(), settings, ValueFlow::Accuracy::LowerBound)
            >= sizeof(MathLib::bigint))
            return;

        if (!value.isImpossible() && value.isIntValue())
            value = truncateImplicitConversion(tok->astParent(), value, settings);

        if (settings.debugnormal)
            setSourceLocation(value, loc, tok);

        if (!tok->addValue(value))
            return;

        if (value.path < 0)
            return;

        Token *parent = tok->astParent();
        if (!parent)
            return;

        if (match11(parent) && !parent->isInitComma() && astIsRHS(tok)) {
            const Token* callParent = findParent(parent, [](const Token* p) {
                return !match11(p);
            });
            // Ensure that the comma isn't a function call
            if (!callParent || (!match12(callParent->previous()) && !match13(callParent) &&
                                (!match14(callParent) || settings.library.isNotLibraryFunction(callParent->next())) &&
                                !(callParent->str() == MatchCompiler::makeConstString("(") && (match16(callParent->astOperand1()) || match15(callParent->astOperand1()))))) {
                setTokenValue(parent, std::move(value), settings);
                return;
            }
        }

        if (match17(parent) && astIsRHS(tok)) {
            setTokenValue(parent, value, settings);
            if (!value.isUninitValue())
                return;
        }

        if (value.isContainerSizeValue() && astIsContainer(tok)) {
            // .empty, .size, +"abc", +'a'
            if (match18(parent) && parent->astOperand1() && parent->astOperand2()) {
                for (const Value &value1 : parent->astOperand1()->values()) {
                    if (value1.isImpossible())
                        continue;
                    for (const Value &value2 : parent->astOperand2()->values()) {
                        if (value2.isImpossible())
                            continue;
                        if (value1.path != value2.path)
                            continue;
                        Value result;
                        if (match19(parent))
                            result.valueType = Value::ValueType::INT;
                        else
                            result.valueType = Value::ValueType::CONTAINER_SIZE;

                        if (value1.isContainerSizeValue() && value2.isContainerSizeValue())
                            result.intvalue = calculate(parent->str(), value1.intvalue, value2.intvalue);
                        else if (value1.isContainerSizeValue() && value2.isTokValue() && value2.tokvalue->tokType() == Token::eString)
                            result.intvalue = calculate(parent->str(), value1.intvalue, MathLib::bigint(Token::getStrLength(value2.tokvalue)));
                        else if (value2.isContainerSizeValue() && value1.isTokValue() && value1.tokvalue->tokType() == Token::eString)
                            result.intvalue = calculate(parent->str(), MathLib::bigint(Token::getStrLength(value1.tokvalue)), value2.intvalue);
                        else
                            continue;

                        combineValueProperties(value1, value2, result);

                        if (match20(parent) && result.intvalue)
                            continue;
                        if (match21(parent) && !result.intvalue)
                            continue;

                        setTokenValue(parent, std::move(result), settings);
                    }
                }
            }
            Token* next = nullptr;
            const Library::Container::Yield yields = getContainerYield(parent, settings, next);
            if (yields == Library::Container::Yield::SIZE) {
                value.valueType = Value::ValueType::INT;
                setTokenValue(next, std::move(value), settings);
            } else if (yields == Library::Container::Yield::EMPTY) {
                Value v(value);
                v.valueType = Value::ValueType::INT;
                v.bound = Value::Bound::Point;
                if (value.isImpossible()) {
                    if (value.intvalue == 0)
                        v.setKnown();
                    else if ((value.bound == Value::Bound::Upper && value.intvalue > 0) ||
                             (value.bound == Value::Bound::Lower && value.intvalue < 0)) {
                        v.intvalue = 0;
                        v.setKnown();
                    } else
                        v.setPossible();
                } else {
                    v.intvalue = !v.intvalue;
                }
                setTokenValue(next, std::move(v), settings);
            }
            return;
        }

        if (value.isLifetimeValue()) {
            if (!isLifetimeBorrowed(parent, settings))
                return;
            if (value.lifetimeKind == Value::LifetimeKind::Iterator && astIsIterator(parent)) {
                setTokenValue(parent,std::move(value),settings);
            } else if (astIsPointer(tok) && astIsPointer(parent) && !parent->isUnaryOp("*") &&
                       (parent->isArithmeticalOp() || parent->isCast())) {
                setTokenValue(parent,std::move(value),settings);
            }
            return;
        }

        if (value.isUninitValue()) {
            if (match22(tok))
                setTokenValue(tok->next(), value, settings);
            if (parent->isCast()) {
                setTokenValue(parent, std::move(value), settings);
                return;
            }
            Value pvalue = value;
            if (!value.subexpressions.empty() && match22(parent)) {
                if (contains(value.subexpressions, parent->strAt(1)))
                    pvalue.subexpressions.clear();
                else
                    return;
            }
            if (parent->isUnaryOp("&")) {
                pvalue.indirect++;
                setTokenValue(parent, std::move(pvalue), settings);
            } else if (match22(parent) && parent->astOperand1() == tok && parent->astOperand2()) {
                if (parent->originalName() == MatchCompiler::makeConstString("->") && pvalue.indirect > 0)
                    pvalue.indirect--;
                setTokenValue(parent->astOperand2(), std::move(pvalue), settings);
            } else if (match22(parent->astParent()) && parent->astParent()->astOperand1() == parent) {
                if (parent->astParent()->originalName() == MatchCompiler::makeConstString("->") && pvalue.indirect > 0)
                    pvalue.indirect--;
                setTokenValue(parent->astParent()->astOperand2(), std::move(pvalue), settings);
            } else if (parent->isUnaryOp("*") && pvalue.indirect > 0) {
                pvalue.indirect--;
                setTokenValue(parent, std::move(pvalue), settings);
            }
            return;
        }

        // cast..
        if (const Token *castType = getCastTypeStartToken(parent, settings)) {
            if (contains({Value::ValueType::INT, Value::ValueType::SYMBOLIC}, value.valueType) &&
                match23(parent->astOperand1()))
                return;
            const ValueType &valueType = ValueType::parseDecl(castType, settings);
            if (value.isImpossible() && value.isIntValue() && value.intvalue < 0
                && astIsUnsigned(tok) && valueType.sign == ValueType::SIGNED && tok->valueType()
                && getSizeOf(*tok->valueType(), settings, ValueFlow::Accuracy::ExactOrZero)
                >= getSizeOf(valueType, settings, ValueFlow::Accuracy::ExactOrZero))
                return;
            setTokenValueCast(parent, valueType, value, settings);
        }

        else if (parent->str() == MatchCompiler::makeConstString(":")) {
            setTokenValue(parent,std::move(value),settings);
        }

        else if (parent->str() == MatchCompiler::makeConstString("?") && tok->str() == MatchCompiler::makeConstString(":") && tok == parent->astOperand2() && parent->astOperand1()) {
            // is condition always true/false?
            if (parent->astOperand1()->hasKnownValue()) {
                const Value &condvalue = parent->astOperand1()->values().front();
                const bool cond(condvalue.isTokValue() || (condvalue.isIntValue() && condvalue.intvalue != 0));
                if (cond && !tok->astOperand1()) { // true condition, no second operator
                    setTokenValue(parent, condvalue, settings);
                } else {
                    const Token *op = cond ? tok->astOperand1() : tok->astOperand2();
                    if (!op) // #7769 segmentation fault at setTokenValue()
                        return;
                    const std::list<Value> &values = op->values();
                    if (std::find(values.cbegin(), values.cend(), value) != values.cend())
                        setTokenValue(parent, std::move(value), settings);
                }
            } else if (!value.isImpossible()) {
                // is condition only depending on 1 variable?
                // cppcheck-suppress[variableScope] #8541
                nonneg int varId = 0;
                bool ret = false;
                visitAstNodes(parent->astOperand1(),
                              [&](const Token *t) {
                    if (t->varId()) {
                        if (varId > 0 || value.varId != 0)
                            ret = true;
                        varId = t->varId();
                    } else if (t->str() == MatchCompiler::makeConstString("(") && match24(t->previous()))
                        ret = true; // function call
                    return ret ? ChildrenToVisit::done : ChildrenToVisit::op1_and_op2;
                });
                if (ret)
                    return;

                Value v(std::move(value));
                v.conditional = true;
                v.changeKnownToPossible();

                setTokenValue(parent, std::move(v), settings);
            }
        }

        else if (parent->str() == MatchCompiler::makeConstString("?") && value.isIntValue() && tok == parent->astOperand1() && value.isKnown() &&
                 parent->astOperand2() && parent->astOperand2()->astOperand1() && parent->astOperand2()->astOperand2()) {
            const std::list<Value> &values = (value.intvalue == 0
                ? parent->astOperand2()->astOperand2()->values()
                : parent->astOperand2()->astOperand1()->values());

            for (const Value &v : values)
                setTokenValue(parent, v, settings);
        }

        // Offset of non null pointer is not null also
        else if (astIsPointer(tok) && match9(parent) &&
                 (parent->astOperand2() == nullptr || !astIsPointer(parent->astOperand2())) &&
                 value.isIntValue() && value.isImpossible() && value.intvalue == 0) {
            setTokenValue(parent, std::move(value), settings);
        }

        // Calculations..
        else if ((parent->isArithmeticalOp() || parent->isComparisonOp() || (parent->tokType() == Token::eBitOp) ||
                  (parent->tokType() == Token::eLogicalOp)) &&
                 parent->astOperand1() && parent->astOperand2()) {

            const bool noninvertible = isNonInvertibleOperation(parent);

            // Skip operators with impossible values that are not invertible
            if (noninvertible && value.isImpossible())
                return;

            if (!value.isImpossible() && value.isIntValue() &&
                ((match25(parent) && astIsIntegral(parent, true) && value.intvalue == 0) ||
                 (match26(parent) && value.intvalue == 0) ||
                 (match27(parent) && value.intvalue != 0))) {
                value.bound = Value::Bound::Point;
                setTokenValue(parent, std::move(value), settings);
                return;
            }

            for (const Value &value1 : parent->astOperand1()->values()) {
                if (!isComputableValue(parent, value1))
                    continue;
                for (const Value &value2 : parent->astOperand2()->values()) {
                    if (value1.path != value2.path && value1.path != 0 && value2.path != 0)
                        continue;
                    if (!isComputableValue(parent, value2))
                        continue;
                    if (value1.isIteratorValue() && value2.isIteratorValue())
                        continue;
                    if (!isCompatibleValues(value1, value2))
                        continue;
                    Value result(0);
                    combineValueProperties(value1, value2, result);
                    if (astIsFloat(parent, false)) {
                        if (!result.isIntValue() && !result.isFloatValue())
                            continue;
                        result.valueType = Value::ValueType::FLOAT;
                    }
                    const bool isFloat = value1.isFloatValue() || value2.isFloatValue();
                    if (isFloat && match28(parent))
                        continue;
                    const auto intValue1 = [&]() -> MathLib::bigint {
                        return value1.isFloatValue() ? static_cast<MathLib::bigint>(value1.floatValue) : value1.intvalue;
                    };
                    const auto intValue2 = [&]() -> MathLib::bigint {
                        return value2.isFloatValue() ? static_cast<MathLib::bigint>(value2.floatValue) : value2.intvalue;
                    };
                    if (match29(parent)) {
                        if ((value1.isIntValue() && value2.isTokValue()) || (value1.isTokValue() && value2.isIntValue())) {
                            if (parent->str() == MatchCompiler::makeConstString("=="))
                                result.intvalue = 0;
                            else if (parent->str() == MatchCompiler::makeConstString("!="))
                                result.intvalue = 1;
                        } else if (value1.isIntValue() && value2.isIntValue()) {
                            bool error = false;
                            result.intvalue = calculate(parent->str(), intValue1(), intValue2(), &error);
                            if (error)
                                continue;
                        } else if (value1.isTokValue() && value2.isTokValue() &&
                                   (astIsContainer(parent->astOperand1()) || astIsContainer(parent->astOperand2()))) {
                            const Token* tok1 = value1.tokvalue;
                            const Token* tok2 = value2.tokvalue;
                            bool equal = false;
                            if (match30(tok1) && match30(tok2)) {
                                equal = tok1->str() == tok2->str();
                            } else if (match13(tok1) && match13(tok2)) {
                                std::vector<const Token*> args1 = getArguments(tok1);
                                std::vector<const Token*> args2 = getArguments(tok2);
                                if (args1.size() == args2.size()) {
                                    if (!std::all_of(args1.begin(), args1.end(), std::mem_fn(&Token::hasKnownIntValue)))
                                        continue;
                                    if (!std::all_of(args2.begin(), args2.end(), std::mem_fn(&Token::hasKnownIntValue)))
                                        continue;
                                    equal = std::equal(args1.begin(),
                                                       args1.end(),
                                                       args2.begin(),
                                                       [&](const Token* atok, const Token* btok) {
                                        return atok->getKnownIntValue() ==
                                               btok->getKnownIntValue();
                                    });
                                } else {
                                    equal = false;
                                }
                            } else {
                                continue;
                            }
                            result.intvalue = parent->str() == MatchCompiler::makeConstString("==") ? equal : !equal;
                        } else {
                            continue;
                        }
                        setTokenValue(parent, std::move(result), settings);
                    } else if (match31(parent)) {
                        if (match19(parent)) {
                            if (!isFloat && !value1.isIntValue() && !value2.isIntValue())
                                continue;
                        } else {
                            if (value1.isTokValue() || value2.isTokValue())
                                break;
                        }
                        bool error = false;
                        if (isFloat) {
                            const double floatValue1 = value1.isFloatValue() ? value1.floatValue : static_cast<double>(value1.intvalue);
                            const double floatValue2 = value2.isFloatValue() ? value2.floatValue : static_cast<double>(value2.intvalue);
                            auto val = calculate(parent->str(), floatValue1, floatValue2, &error);
                            if (result.isFloatValue()) {
                                result.floatValue = val;
                            } else {
                                result.intvalue = static_cast<MathLib::bigint>(val);
                            }
                        } else {
                            auto val = calculate(parent->str(), intValue1(), intValue2(), &error);
                            if (result.isFloatValue()) {
                                result.floatValue = static_cast<double>(val);
                            } else {
                                result.intvalue = val;
                            }
                        }
                        if (error)
                            continue;
                        // If the bound comes from the second value then invert the bound when subtracting
                        if (match32(parent) && value2.bound == result.bound &&
                            value2.bound != Value::Bound::Point)
                            result.invertBound();
                        setTokenValue(parent, std::move(result), settings);
                    }
                }
            }
        }

        // !
        else if (parent->str() == MatchCompiler::makeConstString("!")) {
            for (const Value &val : tok->values()) {
                if (!val.isIntValue())
                    continue;
                if (val.isImpossible() && val.intvalue != 0)
                    continue;
                Value v(val);
                if (val.isImpossible())
                    v.setKnown();
                else
                    v.intvalue = !v.intvalue;
                setTokenValue(parent, std::move(v), settings);
            }
        }

        // ~
        else if (parent->str() == MatchCompiler::makeConstString("~")) {
            for (const Value &val : tok->values()) {
                if (!val.isIntValue())
                    continue;
                Value v(val);
                v.intvalue = ~v.intvalue;
                std::uint8_t bits = 0;
                if (tok->valueType() &&
                    tok->valueType()->sign == ValueType::Sign::UNSIGNED &&
                    tok->valueType()->pointer == 0) {
                    if (tok->valueType()->type == ValueType::Type::INT)
                        bits = settings.platform.int_bit;
                    else if (tok->valueType()->type == ValueType::Type::LONG)
                        bits = settings.platform.long_bit;
                }
                if (bits > 0 && bits < MathLib::bigint_bits)
                    v.intvalue &= (1ULL<<bits) - 1;
                setTokenValue(parent, std::move(v), settings);
            }
        }

        // unary minus
        else if (parent->isUnaryOp("-")) {
            for (const Value &val : tok->values()) {
                if (!val.isIntValue() && !val.isFloatValue())
                    continue;
                Value v(val);
                if (v.isIntValue()) {
                    if (v.intvalue == LLONG_MIN)
                        // Value can't be inverted
                        continue;
                    v.intvalue = -v.intvalue;
                } else
                    v.floatValue = -v.floatValue;
                v.invertBound();
                setTokenValue(parent, std::move(v), settings);
            }
        }

        // increment
        else if (parent->str() == MatchCompiler::makeConstString("++")) {
            for (const Value &val : tok->values()) {
                if (!val.isIntValue() && !val.isFloatValue() && !val.isSymbolicValue())
                    continue;
                Value v(val);
                if (parent == tok->previous()) {
                    if (v.isIntValue() || v.isSymbolicValue()) {
                        const ValueType *dst = tok->valueType();
                        if (dst) {
                            const size_t sz = ValueFlow::getSizeOf(*dst,
                                                                   settings,
                                                                   ValueFlow::Accuracy::ExactOrZero);
                            MathLib::bigint newvalue = ValueFlow::truncateIntValue(v.intvalue + 1, sz, dst->sign);
                            if (v.bound != ValueFlow::Value::Bound::Point) {
                                if (newvalue < v.intvalue) {
                                    v.invertBound();
                                    newvalue -= 2;
                                }
                            }
                            v.intvalue = newvalue;
                        } else {
                            v.intvalue = v.intvalue + 1;
                        }
                    }
                    else
                        v.floatValue = v.floatValue + 1.0;
                }
                setTokenValue(parent, std::move(v), settings);
            }
        }

        // decrement
        else if (parent->str() == MatchCompiler::makeConstString("--")) {
            for (const Value &val : tok->values()) {
                if (!val.isIntValue() && !val.isFloatValue() && !val.isSymbolicValue())
                    continue;
                Value v(val);
                if (parent == tok->previous()) {
                    if (v.isIntValue() || v.isSymbolicValue()) {
                        const ValueType *dst = tok->valueType();
                        if (dst) {
                            const size_t sz = ValueFlow::getSizeOf(*dst,
                                                                   settings,
                                                                   ValueFlow::Accuracy::ExactOrZero);
                            MathLib::bigint newvalue = ValueFlow::truncateIntValue(v.intvalue - 1, sz, dst->sign);
                            if (v.bound != ValueFlow::Value::Bound::Point) {
                                if (newvalue > v.intvalue) {
                                    v.invertBound();
                                    newvalue += 2;
                                }
                            }
                            v.intvalue = newvalue;
                        } else {
                            v.intvalue = v.intvalue - 1;
                        }
                    }
                    else
                        v.floatValue = v.floatValue - 1.0;
                }
                setTokenValue(parent, std::move(v), settings);
            }
        }

        // C++ init
        else if (parent->str() == MatchCompiler::makeConstString("{") && match33(parent->previous()) &&
                 match34(parent->link())) {
            const Token* lhs = parent->previous()->astOperand1();
            if (lhs && lhs->valueType()) {
                if (lhs->valueType()->isIntegral() || lhs->valueType()->isFloat() || (lhs->valueType()->pointer > 0 && value.isIntValue())) {
                    setTokenValue(parent, std::move(value), settings);
                }
            }
        }

        else if (match35(parent) && parent->astOperand2() == tok) {
            setTokenValue(parent, std::move(value), settings);
        }

        // Calling std::size or std::empty on an array
        else if (value.isTokValue() && match13(value.tokvalue) && tok->variable() &&
                 tok->variable()->isArray() && match2(parent->previous()) && astIsRHS(tok)) {
            std::vector<const Token*> args = getArguments(value.tokvalue);
            if (const Library::Function* f = settings.library.getFunction(parent->previous())) {
                if (f->containerYield == Library::Container::Yield::SIZE) {
                    Value v(std::move(value));
                    v.valueType = Value::ValueType::INT;
                    v.intvalue = args.size();
                    setTokenValue(parent, std::move(v), settings);
                } else if (f->containerYield == Library::Container::Yield::EMPTY) {
                    Value v(std::move(value));
                    v.intvalue = args.empty();
                    v.valueType = Value::ValueType::INT;
                    setTokenValue(parent, std::move(v), settings);
                }
            }
        }

        // C++ constructor
        else if (value.isIntValue() && parent->str() == MatchCompiler::makeConstString("{") && parent->valueType() && (parent->valueType()->isIntegral() || parent->valueType()->pointer > 0)) {
            setTokenValue(parent, std::move(value), settings);
        }
    }
}
#if defined(__clang__)
SUPPRESS_WARNING_CLANG_POP
#endif
#undef MAYBE_UNUSED
