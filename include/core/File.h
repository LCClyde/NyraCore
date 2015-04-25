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
#ifndef __NYRA_CORE_FILE_H__
#define __NYRA_CORE_FILE_H__

#include <stdint.h>
#include <vector>
#include <string>
#include <fstream>

namespace nyra
{
namespace core
{
/*
 *  \func - getFileSize
 *  \brief - A fast and resuable way to get the size of a file.
 *
 *  \param pathname - The pathname to the file on disk. This can be
 *         relative or absolute.
 *  \throw - If the file fails to open.
 */
size_t getFileSize(const std::string& pathname);

/*
 *  \func - readFile
 *  \brief - Reads the entire contents of a file into a single string.
 *           This function does not focus on efficiency so it is not
 *           recommended for very large files.
 *
 *  \param pathname - The pathname to the file on disk. This can be
 *         relative or absolute.
 *  \throw - If the file fails to open.
 */
std::string readFile(const std::string& pathname);

/*
 *  \func - readBinary
 *  \brief - Reads the entire contents of a file into a buffer.
 *           This version is better for reading binary files as a
 *           \0 will not cause issues.
 *           This function does not focus on efficiency so it is not
 *           recommended for very large files.
 *
 *  \param pathname - The pathname to the file on disk. This can be
 *         relative or absolute.
 *  \throw - If the file fails to open.
 */
std::vector<uint8_t> readBinary(const std::string& pathname);
}
}

#endif
