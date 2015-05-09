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
#ifndef __NYRA_GRAPHICS_WINDOW_SDL_H__
#define __NYRA_GRAPHICS_WINDOW_SDL_H__

#include <SDL.h>
#include <graphics/Window.h>

namespace nyra
{
namespace graphics
{
class WindowSDL : public Window
{
public:
    WindowSDL(const std::string& title,
              const core::Vector2UI& size,
              const core::Vector2I& position);

    ~WindowSDL();

    virtual void setSize(const core::Vector2UI& size);

    virtual void setPosition(const core::Vector2I& position);

    virtual core::Vector2UI getSize() const;

    virtual core::Vector2I getPosition() const;

    virtual bool update();

    virtual void showBuffer(const void* buffer, size_t size);

private:
    SDL_Window* mWindow;
    SDL_Event mEvent;
};
}
}

#endif
