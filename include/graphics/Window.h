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
#ifndef __NYRA_GRAPHICS_WINDOW_H__
#define __NYRA_GRAPHICS_WINDOW_H__

#include <string>
#include <core/Vector.h>

namespace nyra
{
namespace graphics
{
class Window
{
public:
    virtual ~Window();

    inline void setSize(size_t width, size_t height)
    {
        setSize(core::Vector2UI(width, height));
    }

    virtual void setSize(const core::Vector2UI& size) = 0;

    inline void setPosition(ssize_t width, ssize_t height)
    {
        setSize(width, height);
    }

    virtual void setPosition(const core::Vector2I& position) = 0;

    virtual core::Vector2UI getSize() const = 0;

    virtual core::Vector2I getPosition() const = 0;

    virtual bool update() = 0;

    virtual void showBuffer(const void* buffer, size_t size) = 0;
};
}
}

#endif
