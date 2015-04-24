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
#ifndef __NYRA_CORE_EXCEPTION_H__
#define __NYRA_CORE_EXCEPTION_H__

#include <string>
#include <stdexcept>

namespace nyra
{
namespace core
{
/*
 *  \class Exception
 *  \brief Base exception class for nyra code. All nyra based code will
 *         throw this or an inherited version of this class. This allows
 *         the caller to catch the exception using std::exception or to
 *         specialize their code and catch a nyra::core::Exception.
 */
class Exception : std::exception
{
public:
    /*
     *  \func Constructor (string)
     *  \brief Sets up the internal structure of an exception based on a
     *         STL string.
     *
     *  \param message - A description of the exception.
     */
    explicit Exception(const std::string& message);

    /*
     *  \func Destructor
     *  \brief Used for proper inheritance.
     */
    virtual ~Exception();

    /*
     *  \func what
     *  \brief Used to retrieve the stored message. The string is owned
     *         internally by the exception object and should not be modified
     *         or freed externally.
     */
    virtual const char* what() const
    {
        return mMessage.c_str();
    }

protected:
    std::string mMessage;
};
}
}

#endif
