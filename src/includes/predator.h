#pragma once

#include <SFML/Graphics.hpp>

#include "boid.h"


class Predator : public Boid
{
    private:
    bool m_neutral;
    int m_attack_time;
    int m_neutral_time;
    int m_attack_frames;
    int m_neutral_frames;

    public:
    Predator(sf::Vector2f positon, sf::Angle rotation, float range=300, int attack_time=40);
    void attack(std::vector<Boid> boids, int height, int width);
    void walk_around(std::vector<Boid> boids, int height, int width, int acceleration_limit);
    void update_position(std::vector<Boid> boids, int height, int width);
};