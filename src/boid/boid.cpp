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
    scale({0.08f, 0.08f});

    m_visual_range = range;
    m_desired_separation = separation;
    m_desired_aligment = aligment;
    m_desired_cohesion = cohesion;

    sf::Vector2f test({1.0f, 1.0f});
    m_velocity = test;
    m_acceleration = test;

    m_predator = false;

    m_hunger = 50 + (rand()%1000);
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

sf::Vector2f Boid::get_velocity()
{
    return m_velocity;
}

bool Boid::is_predator()
{
    return m_predator;
}

sf::Vector2f Boid::look_for_food(std::vector<Food>* food)
{
    float shortest_dist = 1e6;
    auto shortest_dist_it = food->begin();

    int in_distance = 0;

    sf::Vector2f food_direction({0.0f, 0.0f});

    for(auto it = food->begin(); it != food->end();)
    {
        float dist = distance(it->get_position());
        in_distance++;

        if(dist < it->get_radius())
        {
            m_hunger += it->eat();

            it = food->erase(it);
        }
        else if(dist < m_visual_range)
        {
            if(dist < shortest_dist)
            {
                shortest_dist_it = it;
            }

            it++;
        }
        else
        {
            it++;
        }
    }

    if(in_distance > 0)
    {
        food_direction.x = shortest_dist_it->get_position().x - get_position().x;
        food_direction.y = shortest_dist_it->get_position().y - get_position().y;
    }

    return food_direction;
}

sf::Vector2f Boid::calculate_separation(std::vector<Boid> boids)
{
    sf::Vector2f separation({0.0f, 0.0f});
    int in_distance = 0;
    int min_distance = 10;

    int avoid_predator = 1;

    for(Boid boid : boids)
    {
        float dist = distance(boid.get_position());

        if((dist < m_visual_range) && (dist > 0))
        {
            if(boid.is_predator())
            {
                avoid_predator = 3;
            }
            else
            {
                avoid_predator = 1;
            }
            sf::Vector2f difference({0.0f, 0.0f});
            difference = get_position() - boid.get_position();
            separation.x += avoid_predator*m_desired_separation*(1 - (min_distance/dist))*difference.x;
            separation.y += avoid_predator*m_desired_separation*(1 - (min_distance/dist))*difference.y;
        }

    }

    if(in_distance > 0)
    {
        separation.x /= in_distance;
        separation.y /= in_distance;
    }
    if(separation.lengthSquared() > 0)
    {
        separation = separation.normalized();
    }

    return separation;
}

sf::Vector2f Boid::calculate_aligment(std::vector<Boid> boids)
{
    sf::Vector2f aligment({0.0f, 0.0f});
    int in_distance = 0;

    for(Boid boid : boids)
    {
        float dist = distance(boid.get_position());

        if((dist < m_visual_range) && (dist > 0) && !boid.is_predator())
        {
            aligment.x += boid.get_position().x;
            aligment.y += boid.get_position().y;

            in_distance++;
        }
    }

    if(in_distance > 0)
    {
        aligment.x /= in_distance;
        aligment.y /= in_distance;

        aligment.x = m_desired_aligment*(aligment.x - get_position().x);
        aligment.y = m_desired_aligment*(aligment.y - get_position().y);
    }
    if(aligment.lengthSquared() > 0)
    {
        aligment = aligment.normalized();
    }

    return aligment;
}

sf::Vector2f Boid::calculate_cohesion(std::vector<Boid> boids)
{
    sf::Vector2f cohesion({0.0f, 0.0f});
    sf::Vector2f average_velocity({0.0f, 0.0f});
    int in_distance = 0;

    for(Boid boid : boids)
    {
        float dist = distance(boid.get_position());

        if((dist < m_visual_range) && (dist > 0) && !boid.is_predator())
        {
            average_velocity += boid.get_velocity();
            in_distance++;
        }
    }

    if(in_distance > 0)
    {
        average_velocity.x /= in_distance;
        average_velocity.y /= in_distance;
        
        cohesion.x = m_desired_cohesion*(get_velocity().x - average_velocity.x);
        cohesion.y = m_desired_cohesion*(get_velocity().y - average_velocity.y);
    }
    if(cohesion.lengthSquared() > 0)
    {
        cohesion = cohesion.normalized();
    }

    return cohesion;
}

sf::Vector2f Boid::calculate_position(std::vector<Boid> boids, std::vector<Food>* food)
{
    sf::Vector2f separation = calculate_separation(boids);
    sf::Vector2f aligment = calculate_aligment(boids);
    sf::Vector2f cohesion = calculate_cohesion(boids);

    sf::Vector2f food_direction({0.0f, 0.0f});

    if(m_hunger < 0)
    {
        food_direction = look_for_food(food);
    }

    m_acceleration = m_acceleration + separation + aligment + cohesion + food_direction;

    if(m_acceleration.length() > 3)
    {
        m_acceleration = m_acceleration.normalized();
    }
    
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
        tmp_position.y = 0;
    }
    else if(tmp_position.y < 0)
    {
        tmp_position.y = height;
    }
    if(tmp_position.x > width)
    {
        tmp_position.x = 0;
    }
    else if(tmp_position.x < 0)
    {
        tmp_position.x = width;
    }

    setPosition(tmp_position);
}

void Boid::update_position(std::vector<Boid> boids, int height, int width, std::vector<Food>* food)
{
    setPosition(calculate_position(boids, food));
    avoid_edges(height, width);

    float look_angle = std::atan2(m_acceleration.x, m_acceleration.y);
    setRotation(sf::radians(look_angle));

    m_hunger--;
}
