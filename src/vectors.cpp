#include "libs.hpp"

sf::Vector2f v2uToV2f(sf::Vector2u vector)
{
    return sf::Vector2f(vector.x, vector.y);
}

sf::Vector2u v2fToV2u(sf::Vector2f vector)
{
    return sf::Vector2u(vector.x, vector.y);
}

sf::Vector2i v2fToV2i(sf::Vector2f vector)
{
    return sf::Vector2i(vector.x, vector.y);
}

sf::Vector2f v2iToV2f(sf::Vector2i vector)
{
    return sf::Vector2f(vector.x, vector.y);
}

sf::Vector2f vectAdd(sf::Vector2f v1, sf::Vector2f v2)
{
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

sf::Vector2f vectSub(sf::Vector2f v1, sf::Vector2f v2)
{
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

float vectMag(sf::Vector2f v)
{
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

sf::Vector2f vectMult(sf::Vector2f v, float n)
{
    v.x *= n;
    v.y *= n;
    return v;
}

sf::Vector2f vectUnit(sf::Vector2f v)
{
    if (vectMag(v) == 0) {
        v.x = 0;
        v.y = 0;
        return v;
    }
    v.x = v.x / vectMag(v);
    v.y = v.y / vectMag(v);
    return v;
}

sf::Vector2f vectFmult(sf::Vector2f v, sf::Vector2f v2)
{
    v.x *= v2.x;
    v.y *= v2.y;
    return v;
}

sf::Vector2f vectNorm(sf::Vector2f v)
{
    sf::Vector2f norm;

    norm.x = -v.y;
    norm.y = v.x;
    v = vectUnit(norm);
    return v;
}

float vectDot(sf::Vector2f v1, sf::Vector2f v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

float vectCross(sf::Vector2f v1, sf::Vector2f v2)
{
    return (v1.x * v2.y - v1.y * v2.x);
}

float distFrom(sf::Vector2f p1, sf::Vector2f p2)
{
    float distance = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));

    return (distance);
}

sf::Vector2f closestPointSeg(sf::Vector2f a, sf::Vector2f b, sf::Vector2f p)
{
    sf::Vector2f a_to_p = vectSub(p, a);
    sf::Vector2f a_to_b = vectSub(b, a);
    float atb2 = a_to_b.x * a_to_b.x + a_to_b.y * a_to_b.y;
    float atp_dot_atb = vectDot(a_to_p, a_to_b);
    float t = atp_dot_atb / atb2;

    if (t > 1)
        t = 1;
    if (t < 0)
        t = 0;
    return sf::Vector2f(a.x + a_to_b.x * t, a.y + a_to_b.y * t);
}
