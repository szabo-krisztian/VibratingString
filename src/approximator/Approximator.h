namespace tlr
{

class Approximator
{
public:
    Approximator(float length, float newtonQuotient, bool isNeutralVelocity = true);
    float GetApproximation(float x, float t, int precision);
    void SetHeight(float height);
    float GetHeight();
    float GetQ();

    const float LENGTH;
    const float NEWTON_QUOTIENT;

private:
    const bool _IS_NEUTRAL_VELOCITY;
    float _height = 0.0f;
    float _Q;

    void UpdateQ();
};

} // namespace tlr