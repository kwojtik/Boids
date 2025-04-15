#pragma once

#include <SFML/Graphics.hpp>

#include "boid.h"


class Predator : public Boid
{
    private:
    bool m_neutral;
    int m_attack_time;

    public:
    Predator(sf::Vector2f positon, sf::Angle rotation, float range=300);
    void attack();
    void walk_around();
};