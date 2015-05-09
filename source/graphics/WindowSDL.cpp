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
#include <graphics/WindowSDL.h>
#include <core/Exception.h>

namespace nyra
{
namespace graphics
{
/*****************************************************************************/
WindowSDL::WindowSDL(const std::string& title,
                     const core::Vector2UI& size,
                     const core::Vector2I& position) :
    mWindow(nullptr)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw core::Exception("Failed to initalize SDL");
    }

    mWindow = SDL_CreateWindow(title.c_str(),
                               position.x,
                               position.y,
                               size.x,
                               size.y,
                               SDL_WINDOW_SHOWN);
    if (!mWindow)
    {
        throw core::Exception("Unable to create SDL window!");
    }
}

/*****************************************************************************/
WindowSDL::~WindowSDL()
{
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

/*****************************************************************************/
void WindowSDL::setSize(const core::Vector2UI& size)
{
    SDL_SetWindowSize(mWindow, size.x, size.y);
}

/*****************************************************************************/
void WindowSDL::setPosition(const core::Vector2I& position)
{
    SDL_SetWindowPosition(mWindow, position.x, position.y);
}

/*****************************************************************************/
core::Vector2UI WindowSDL::getSize() const
{
    return core::Vector2UI(0, 0);
}

/*****************************************************************************/
core::Vector2I WindowSDL::getPosition() const
{
    return core::Vector2I(0, 0);
}

/*****************************************************************************/
bool WindowSDL::update()
{
    while (SDL_PollEvent(&mEvent) != 0)
    {
        if (mEvent.type == SDL_QUIT)
        {
            return false;
        }
    }

    return true;
}

/*****************************************************************************/
void WindowSDL::showBuffer(const void* buffer, size_t size)
{
    SDL_Surface* screen = SDL_GetWindowSurface(mWindow);

    SDL_LockSurface(screen);

    const size_t pixels = std::min<size_t>(
            screen->h * screen->w * screen->format->BytesPerPixel, size);
    memcpy(screen->pixels, buffer, pixels);
    SDL_UpdateWindowSurface(mWindow);

    SDL_UnlockSurface(screen);
}
}
}
