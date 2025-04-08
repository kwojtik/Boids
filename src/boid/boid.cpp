#include "boid.h"

Boid::Boid()
{
    return;
}

Boid::Boid(sf::Vector2f position, sf::Angle rotation, float range, float separation, float aligment, float cohesion)
{
    setPointCount(3);
    setPoint(0, sf::Vector2f(0.f, -50.f));
    setPoint(1, sf::Vector2f(50.f, 50.f));
    setPoint(2, sf::Vector2f(-50.f, 50.f));

    setOrigin(sf::Vector2f(0.f, 0.f));
    setPosition(position);
    rotate(rotation);
    scale({0.15f, 0.15f});

    m_visual_range = range;
    m_desired_separation = separation;
    m_desired_aligment = aligment;
    m_desired_cohesion = cohesion;

    sf::Vector2f test({15.0f, 15.0f});
    m_velocity = test;
    m_acceleration = test;
}

float Boid::distance(sf::Vector2f boid_position)
{
    return sqrt((get_position().x-boid_position.x)*(get_position().x-boid_position.x)+
    (get_position().y-boid_position.y)*(get_position().y-boid_position.y));
}

sf::Vector2f Boid::get_position()
{
    return getPosition();
}

sf::Vector2f Boid::calculate_separation(std::vector<Boid> boids)
{
    sf::Vector2f separation({0.0f, 0.0f});
    int in_distance = 0;

    for(Boid boid : boids)
    {
        float dist = distance(boid.get_position());

        if((dist < m_visual_range) && (dist < m_desired_separation) && (dist > 0))
        {
            sf::Vector2f difference({0.0f, 0.0f});
            difference = get_position() - boid.get_position();
            difference.normalized();
            difference = difference / dist;
            separation.x += difference.x;
            separation.y += difference.y;
            in_distance++;
        }

    }

    if(in_distance > 0)
    {
        separation.x /= in_distance;
        separation.y /= in_distance;
    }
    if(separation.lengthSquared() > 0)
    {
        separation.normalized();
        separation.x *= m_velocity.x;
        separation.y *= m_velocity.y;
    }

    return separation;
}

sf::Vector2f Boid::calculate_aligment(std::vector<Boid> boids)
{
    sf::Vector2f aligment({0.0f, 0.0f});

    // for(Boid boid : boids)
    // {

    // }

    return aligment;
}

sf::Vector2f Boid::calculate_cohesion(std::vector<Boid> boids)
{
    sf::Vector2f cohesion({0.0f, 0.0f});

    return cohesion;
}

sf::Vector2f Boid::calculate_position(std::vector<Boid> boids)
{
    sf::Vector2f separation = calculate_separation(boids);
    sf::Vector2f aligment = calculate_aligment(boids);
    sf::Vector2f cohesion = calculate_cohesion(boids);

    m_acceleration = m_acceleration + separation + aligment + cohesion;
    
    sf::Vector2f position(get_position());
    position.x += m_acceleration.x;
    position.y += m_acceleration.y;

    return position;
}

void Boid::avoid_edges(int height, int width)
{
    sf::Vector2f tmp_position = get_position();

    if(tmp_position.y > height)
    {
        tmp_position.y = height;
    }
    else if(tmp_position.y < 0)
    {
        tmp_position.y = 0;
    }
    if(tmp_position.x > width)
    {
        tmp_position.x = width;
    }
    else if(tmp_position.x < 0)
    {
        tmp_position.x = 0;
    }

    setPosition(tmp_position);
}

void Boid::update_position(std::vector<Boid> boids, int height, int width)
{
    setPosition(calculate_position(boids));
    avoid_edges(height, width);
}
