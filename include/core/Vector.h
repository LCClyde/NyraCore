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
#ifndef __NYRA_MATH_VECTOR_H__
#define __NYRA_MATH_VECTOR_H__

#include <ostream>
#include <algorithm>
#include <array>
#include <cmath>
#include <core/Types.h>
#include <core/Exception.h>

namespace nyra
{
namespace core
{
/*
 *  \class VectorElements
 *  \brief Base class for Vector. This is used to give simple variables
 *         to allow easy access to common sizes.
 */
template <typename TypeT, size_t SizeT>
struct VectorElements
{
    /*
     *  \func Constructor
     *  \brief Here for compatibility.
     */
    VectorElements(const std::array<TypeT, SizeT>& array)
    {
    }
};

template <typename TypeT>
struct VectorElements<TypeT, 2>
{
    VectorElements(std::array<TypeT, 2>& array) :
        x(array[0]),
        y(array[1])
    {
    }

    template <typename ThirdPartyT>
    ThirdPartyT toThirdParty() const
    {
        return ThirdPartyT(x, y);
    }

    TypeT& x;
    TypeT& y;
};

template <typename TypeT, size_t SizeT>
struct Vector : public VectorElements<TypeT, SizeT>
{
    typedef TypeT Type;

    Vector() :
        VectorElements<TypeT, SizeT>(mArray)
    {
        std::fill(mArray.begin(), mArray.end(), 0);
    }

    Vector(const Vector<TypeT, SizeT>& other) :
        VectorElements<TypeT, SizeT>(mArray)
    {
        std::copy(other.getData().begin(),
                          other.getData().end(),
                          mArray.begin());
    }

    template <typename OtherT>
    Vector(const Vector<OtherT, SizeT>& other) :
        VectorElements<TypeT, SizeT>(mArray)
    {
        std::copy(other.getData().begin(),
                  other.getData().end(),
                  mArray.begin());
    }

    Vector(const TypeT& x, const TypeT& y) :
        VectorElements<TypeT, SizeT>(mArray)
    {
        std::fill(mArray.begin(), mArray.end(), 0);
        operator[](0) = x;
        operator[](1) = y;
    }

    Vector(const TypeT& x, const TypeT& y, const TypeT& z) :
        VectorElements<TypeT, SizeT>(mArray)
    {
        std::fill(mArray.begin(), mArray.end(), 0);
        operator[](0) = x;
        operator[](1) = y;
        operator[](2) = z;
    }

    Vector(const TypeT& x, const TypeT& y, const TypeT& z, const TypeT& w) :
        VectorElements<TypeT, SizeT>(mArray)
    {
        std::fill(mArray.begin(), mArray.end(), 0);
        operator[](0) = x;
        operator[](1) = y;
        operator[](2) = z;
        operator[](3) = w;
    }

    Vector& operator=(const Vector<TypeT, SizeT>& rhs)
    {
        mArray = rhs.mArray;
        return *this;
    }

    TypeT& operator[](size_t index)
    {
        if (index >= SizeT)
        {
            throw core::Exception("Invalid index.");
        }
        return mArray[index];
    }

    const TypeT& operator[](size_t index) const
    {
        if (index >= SizeT)
        {
            throw core::Exception("Invalid index.");
        }
        return mArray[index];
    }

    bool operator==(const Vector<TypeT, SizeT>& rhs)
    {
        for (size_t ii = 0; ii < SizeT; ++ii)
        {
            if (mArray[ii] != rhs[ii])
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Vector<TypeT, SizeT>& rhs)
    {
        return !operator==(rhs);
    }

    Vector<TypeT, SizeT>& operator+=(const Vector<TypeT, SizeT>& rhs)
    {
        for (size_t ii = 0; ii < SizeT; ++ii)
        {
            mArray[ii] += rhs[ii];
        }
        return *this;
    }

    Vector<TypeT, SizeT>& operator-=(const Vector<TypeT, SizeT>& rhs)
    {
        for (size_t ii = 0; ii < SizeT; ++ii)
        {
            mArray[ii] -= rhs[ii];
        }
        return *this;
    }

    Vector<TypeT, SizeT>& operator*=(const Vector<TypeT, SizeT>& rhs)
    {
        for (size_t ii = 0; ii < SizeT; ++ii)
        {
            mArray[ii] *= rhs[ii];
        }
        return *this;
    }

    Vector<TypeT, SizeT>& operator/=(const Vector<TypeT, SizeT>& rhs)
    {
        for (size_t ii = 0; ii < SizeT; ++ii)
        {
            mArray[ii] /= rhs[ii];
        }
        return *this;
    }

    template <typename ScalarT>
    Vector<TypeT, SizeT>& operator+=(const ScalarT& rhs)
    {
        for (size_t ii = 0; ii < SizeT; ++ii)
        {
            mArray[ii] += rhs;
        }
        return *this;
    }

    template <typename ScalarT>
    Vector<TypeT, SizeT>& operator-=(const ScalarT& rhs)
    {
        for (size_t ii = 0; ii < SizeT; ++ii)
        {
            mArray[ii] -= rhs;
        }
        return *this;
    }

    template <typename ScalarT>
    Vector<TypeT, SizeT>& operator*=(const ScalarT& rhs)
    {
        for (size_t ii = 0; ii < SizeT; ++ii)
        {
            mArray[ii] *= rhs;
        }
        return *this;
    }

    template <typename ScalarT>
    Vector<TypeT, SizeT>& operator/=(const ScalarT& rhs)
    {
        for (size_t ii = 0; ii < SizeT; ++ii)
        {
            mArray[ii] /= rhs;
        }
        return *this;
    }

    TypeT productOfElements() const
    {
        return std::accumulate(mArray.begin(),
                               mArray.end(),
                               1,
                               std::multiplies<TypeT>());
    }

    TypeT sumOfElements() const
    {
        return std::accumulate(mArray.begin(),
                               mArray.end(),
                               0);
    }

    TypeT sumOfSquares() const
    {
        return std::inner_product(mArray.begin(),
                                  mArray.end(),
                                  mArray.begin(),
                                  0);
    }

    double length() const
    {
        return std::sqrt(lengthSquared());
    }

    double lengthSquared() const
    {
        return static_cast<double>(sumOfSquares());
    }

    void normilize()
    {
        *this /= length();
    }

    const std::array<TypeT, SizeT>& getData() const
    {
        return mArray;
    }

private:
    std::array<TypeT, SizeT> mArray;
};

template <typename TypeT, size_t SizeT>
inline Vector<TypeT, SizeT> operator+(
        Vector<TypeT, SizeT> lhs,
        const Vector<TypeT, SizeT>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <typename TypeT, size_t SizeT>
inline Vector<TypeT, SizeT> operator-(
        Vector<TypeT, SizeT> lhs,
        const Vector<TypeT, SizeT>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <typename TypeT, size_t SizeT>
inline Vector<TypeT, SizeT> operator*(
        Vector<TypeT, SizeT> lhs,
        const Vector<TypeT, SizeT>& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <typename TypeT, size_t SizeT>
inline Vector<TypeT, SizeT> operator/(
        Vector<TypeT, SizeT> lhs,
        const Vector<TypeT, SizeT>& rhs)
{
    lhs /= rhs;
    return lhs;
}

template <typename TypeT, size_t SizeT, typename ScalarT>
inline Vector<TypeT, SizeT> operator+(
        Vector<TypeT, SizeT> lhs,
        const ScalarT& rhs)
{
    lhs += rhs;
    return lhs;
}
template <typename TypeT, size_t SizeT, typename ScalarT>
inline Vector<TypeT, SizeT> operator-(
        Vector<TypeT, SizeT> lhs,
        const ScalarT& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <typename TypeT, size_t SizeT, typename ScalarT>
inline Vector<TypeT, SizeT> operator*(
        Vector<TypeT, SizeT> lhs,
        const ScalarT& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <typename TypeT, size_t SizeT, typename ScalarT>
inline Vector<TypeT, SizeT> operator/(
        Vector<TypeT, SizeT> lhs,
        const ScalarT& rhs)
{
    lhs /= rhs;
    return lhs;
}

template <typename TypeT, size_t SizeT>
std::ostream& operator<<(std::ostream& os,
                         const Vector<TypeT, SizeT>& vector)
{
    if (!SizeT)
    {
        return os;
    }

    os << "(" << vector[0];
    for (size_t ii = 1; ii < SizeT; ++ii)
    {
        os << ", " << vector[ii];
    }
    os << ")";
    return os;
}

typedef Vector<float, 2> Vector2F;
typedef Vector<size_t, 2> Vector2UI;
typedef Vector<ssize_t, 2> Vector2I;

}
}
#endif
