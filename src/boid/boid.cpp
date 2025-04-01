#include "boid.h"

Boid::Boid()
{
    return;
}

Boid::Boid(sf::Vector2f position, sf::Angle rotation)
{
    setPointCount(3);
    setPoint(0, sf::Vector2f(0.f, -50.f));
    setPoint(1, sf::Vector2f(50.f, 50.f));
    setPoint(2, sf::Vector2f(-50.f, 50.f));

    setOrigin(sf::Vector2f(0.f, 0.f));
    setPosition(position);
    rotate(rotation);
}