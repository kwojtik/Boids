#include "predator.h"

Predator::Predator(sf::Vector2f positon, sf::Angle rotation, float range, int attack_time)
    : Boid(positon, rotation, range)
{
    m_predator = true;
    setFillColor(sf::Color::Red);

    m_neutral = true;

    m_attack_time = attack_time;
    m_attack_frames = 0;

    m_neutral_time = 300;
    m_neutral_frames = 0;
}

void Predator::attack(std::vector<Boid> boids, int height, int width)
{
    m_desired_aligment *= 3;
    m_desired_cohesion *= 3;

    walk_around(boids, height, width, 10);

    m_desired_aligment /= 3;
    m_desired_cohesion /= 3;
}

void Predator::walk_around(std::vector<Boid> boids, int height, int width, int acceleration_limit)
{
    sf::Vector2f aligment = calculate_aligment(boids);
    sf::Vector2f cohesion = calculate_cohesion(boids);

    
    m_acceleration = m_acceleration + aligment + cohesion;

    if(m_acceleration.length() > acceleration_limit)
    {
        m_acceleration = m_acceleration.normalized();
    }
    
    sf::Vector2f position(get_position());
    
    position.x += m_acceleration.x;
    position.y += m_acceleration.y;
    setPosition(position);

    avoid_edges(height, width);

    float look_angle = std::atan2(m_acceleration.x, m_acceleration.y);
    setRotation(sf::radians(look_angle));
}

void Predator::update_position(std::vector<Boid> boids, int height, int width)
{
    if(m_neutral)
    {
        walk_around(boids, height, width, 3);
        m_neutral_frames++;

        if(m_neutral_frames > m_neutral_time)
        {
            m_neutral = false;
            m_neutral_frames = 0;
        }
    }
    else
    {
        attack(boids, height, width);
        m_attack_frames++;

        if(m_attack_frames > m_attack_time)
        {
            m_neutral = true;
            m_attack_frames = 0;
        }
    }
}
