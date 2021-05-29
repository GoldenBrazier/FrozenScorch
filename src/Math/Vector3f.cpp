#include "Vector3f.h"

namespace Math {

Vector3f operator*(const Vector3f& vector, float value)
{
    auto cp_vec = vector;
    cp_vec *= value;
    return cp_vec;
}

Vector3f operator+(const Vector3f& l, const Vector3f& r)
{
    auto cp_vec = l;
    cp_vec += r;
    return cp_vec;
}

Vector3f operator-(const Vector3f& l, const Vector3f& r)
{
    auto cp_vec = l;
    cp_vec -= r;
    return cp_vec;
}

}
