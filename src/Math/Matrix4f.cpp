#include "Matrix4f.h"

namespace Math {

Matrix4f operator*(const Matrix4f& l, const Matrix4f& r)
{
    auto res = l;

    res *= r;
    return res;
}

}