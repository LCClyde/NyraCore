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
#ifndef __NYRA_CORE_STRING_UTILS_H__
#define __NYRA_CORE_STRING_UTILS_H__

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ios>

namespace nyra
{
namespace core
{
/*
 *  \func - split
 *  \brief - Splits a string be a deliminator.
 *
 *  \param s - The string to split
 *  \param delim - The string to split at.
 *  \param ret [OUTPUT] - The output vector.
 */
void split(const std::string& s,
           const std::string& delim,
           std::vector<std::string>& ret);

/*
 *  \func - split
 *  \brief - Splits a string be a deliminator.
 *
 *  \param s - The string to split
 *  \param delim - The string to split at.
 *  \return - The output vector.
 */
inline std::vector<std::string> split(const std::string& s,
                                      const std::string& delim)
{
    std::vector<std::string> ret;
    split(s, delim, ret);
    return ret;
}

/*
 *  \func toUpper
 *  \brief Converts a string to an all uppercase string.
 *
 *  \param input The string to convert. This will destroy
 *               the original string.
 */
inline void toUpper(std::string& input)
{
    std::transform(input.begin(),
                   input.end(),
                   input.begin(),
                   ::toupper);
}

/*
 *  \func toUpper
 *  \brief Converts a string to an all uppercase string.
 *
 *  \param input The string to convert.
 *  \return The all uppercase string.
 */
inline std::string toUpper(const std::string& input)
{
    std::string ret(input);
    toUpper(ret);
    return ret;
}

/*
 *  \func - pad
 *  \brief - Pads a string either left or right with a character.
 *
 *  \param input - The starting string
 *  \param character - The character to pad.
 *  \param stringSize - The desired final string size. If the string is
 *         already greater than or equal to this size, nothing will change.
 *  \param padRight - Pass in true to have the characters go to the end of
 *         the string. Otherwise they go on the beginning.
 *  \return - The padded string.
 */
inline std::string pad(const std::string& input,
                       char character,
                       size_t stringSize,
                       bool padRight = false)
{
    std::ostringstream buffer;
    auto op = padRight ? std::left : std::right;
    buffer << std::setfill(character)
           << op
           << std::setw(stringSize) << input;
    return buffer.str();
}
}
}
#endif