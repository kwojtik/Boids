#pragma once

#include <SFML/Graphics.hpp>


class Boid : public sf::ConvexShape
{
    private:
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
    sf::Color m_color;

    public:
    Boid();
    Boid(sf::Vector2f positon, sf::Angle rotation);
    void calculate_separation();
    void calculate_aligment();
    void calculate_cohesion();
};