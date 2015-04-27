/******************************************************************************
 * The MIT License(MIT)
 *
 * Copyright(c) 2015 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/
#ifndef __NYRA_CORE_STRING_CONVERT_H__
#define __NYRA_CORE_STRING_CONVERT_H__

#include <stdint.h>
#include <string>
#include <sstream>
#include <limits>
#include <core/Exception.h>
#include <core/StringUtils.h>

namespace nyra
{
namespace core
{
/*
 *  \func - getPrecision
 *  \brief - Returns the amount of precision for converting to a string for
 *           a datatype. This is specialized for floating point values.
 *
 *  \param T - The data type to consider the precision of.
 */
template<typename T> size_t getPrecision(const T&)
{
    return 0;
}

/*
 *  \func - toHexString
 *  \brief - Converts a value to a hexadecimal based string. This will 0 pad
 *           numbers on the left to fill the number of bytes in the datatype.
 *
 *  \param T - The datatype of the value.
 *  \param value - The value to convert.
 *  \return - The 0 padded formatted string.
 */
template<typename T> std::string toHexString(const T& value)
{
    std::ostringstream buffer;
    buffer << std::hex << static_cast<size_t>(value);
    return pad(toUpper(buffer.str()), '0', sizeof(T) * 2);
}

/*
 *  \func toString
 *  \brief Converts a value to a string.
 *
 *  \param value The value to turn into a string.
 *  \param precision The precision of the value, used for real numbers.
 *                   If you do not need custom precision, you should call
 *                   the version without this parameter.
 *  \return The string of the value.
 */
template<typename T> std::string toString(const T& value,
                                          size_t precision)
{
    std::ostringstream buffer;
    buffer.precision(precision);
    buffer << std::boolalpha << value;
    return buffer.str();
}

/*
 *  \func toString
 *  \brief Converts a value to a string.
 *
 *  \param value The value to turn into a string.
 *  \return The string of the value.
 */
template<typename T> std::string toString(const T& value)
{
    return toString<T>(
            value,
            getPrecision<T>(value));
}

/*
 *  \func toType
 *  \brief Converts a string to a value.
 *
 *  \param s The string you want to convert.
 *  \return The value the string contained.
 *  \throw Exception if the string is empty.
 *  \throw Exception if the string cannot be converted to this data type.
 */
template<typename T> T toType(const std::string& s)
{
    if (s.empty())
        throw Exception("Trying to covert an empty string.");

    T value;

    std::stringstream buffer(s);
    buffer.precision(getPrecision<T>(value));
    buffer >> value;

    if (buffer.fail())
        throw Exception("Failed to convert: " + s);

    return value;
}
}
}

#endif
