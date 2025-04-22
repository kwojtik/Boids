#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>


class Boid : public sf::ConvexShape
{
    protected:
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
    sf::Color m_color;
    float m_visual_range;
    float m_desired_separation;
    float m_desired_aligment;
    float m_desired_cohesion;
    bool m_predator;

    public:
    Boid();
    Boid(sf::Vector2f positon, sf::Angle rotation, float range=200, float separation=0.5, float aligment=1, float cohesion=1);
    float distance(sf::Vector2f boid_position);
    sf::Vector2f get_velocity();
    sf::Vector2f get_position();
    bool is_predator();
    sf::Vector2f calculate_separation(std::vector<Boid> boids);
    sf::Vector2f calculate_aligment(std::vector<Boid> boids);
    sf::Vector2f calculate_cohesion(std::vector<Boid> boids);
    sf::Vector2f calculate_position(std::vector<Boid> boids);
    void avoid_edges(int height, int width);
    void update_position(std::vector<Boid> boids, int height, int width);
};
