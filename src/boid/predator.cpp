#include "predator.h"

Predator::Predator(sf::Vector2f positon, sf::Angle rotation, float range)
    : Boid(positon, rotation, range)
{
    setFillColor(sf::Color::Red);

    m_neutral = true;
}

void Predator::attack()
{
    return;
}

void Predator::walk_around()
{
    return;
}
