#include "Approximator.h"

#include <cmath>
#include <algorithm>

#ifndef PI
#define PI 3.14159f
#endif

namespace tlr
{

Approximator::Approximator(float length, float newtonQuotient, bool isNeutralVelocity) : LENGTH(length), NEWTON_QUOTIENT(newtonQuotient), _IS_NEUTRAL_VELOCITY(isNeutralVelocity)
{
    UpdateQ();
}

float Approximator::GetApproximation(float x, float t, int precision)
{
    float result = 0.0f;

    for (int n = 1; n <= precision; ++n)
    {
        float a_n = -1;
        float b_n = _IS_NEUTRAL_VELOCITY ? 0.0f : LENGTH / (n * std::sqrt(NEWTON_QUOTIENT) * PI);
        float d_n = (4.0f * LENGTH * _Q * (((n % 2 == 0) ? 1 : -1) - 1)) / (static_cast<float>(std::pow(PI, 3)) * static_cast<float>(std::pow(n, 3)));

        result += d_n * std::sin(PI * n * x / LENGTH) * 
                 (a_n * std::cos(n * std::sqrt(NEWTON_QUOTIENT) * PI * t / LENGTH) + 
                  b_n * std::sin(PI * std::sqrt(NEWTON_QUOTIENT) * n * t / LENGTH));
    }

    return result * std::clamp((1.0f / std::log(t + 2)), 0.0f, 1.0f);
}

void Approximator::SetHeight(float height)
{
    _height = height;
    UpdateQ();
}

float Approximator::GetHeight()
{
    return _height;
}

float Approximator::GetQ()
{
    return _Q;
}

void Approximator::UpdateQ()
{
    _Q = (4.0f * _height) / LENGTH;
}

} // namespace tlr