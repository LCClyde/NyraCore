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
#include <sstream>
#include <fstream>
#include <core/File.h>
#include <core/Exception.h>

namespace nyra
{
namespace core
{
/*****************************************************************************/
size_t getFileSize(const std::string& pathname)
{
    std::ifstream stream(pathname, std::ios::ate | std::ios::binary);
    if (!stream.good())
    {
        throw Exception("Failed to open file: " + pathname);
    }
    return static_cast<size_t>(stream.tellg());
}

/*****************************************************************************/
std::string readFile(const std::string& pathname)
{
    const std::ifstream stream(pathname);
    if (!stream.good())
    {
        throw Exception("Failed to open file: " + pathname);
    }

    std::stringstream buffer;
    buffer << stream.rdbuf();
    return buffer.str();
}

/*****************************************************************************/
std::vector<uint8_t> readBinary(const std::string& pathname)
{
    // TODO: Is it better to just use the existing stream here even
    //       thought we would rewrite some code?
    const size_t bufferSize = getFileSize(pathname);

    // Return an empty vector if there is nothing to read.
    if (bufferSize == 0)
    {
        return std::vector<uint8_t>();
    }

    // Open the file in binary mode.
    std::ifstream stream(pathname, std::ios::binary);
    if (!stream.good())
    {
        throw Exception("Failed to open file: " + pathname);
    }

    // Go to the end of the stream to figure out how large it is.
    std::vector<uint8_t> ret(bufferSize);

    stream.read(reinterpret_cast<char*>(&ret[0]), bufferSize);

    return ret;
}
}
}

