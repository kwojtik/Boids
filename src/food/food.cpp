#include "food.h"

Food::Food()
{
    return;
}

Food::Food(sf::Vector2f position)
{
    setRadius(3);   
    setFillColor(sf::Color::Green);
    setPosition(position);

    m_satiety = 50 + (rand()%500);
}

sf::Vector2f Food::get_position()
{
    return getPosition();
}

float Food::get_radius()
{
    return getRadius();
}

int Food::eat()
{
    return m_satiety;
}
