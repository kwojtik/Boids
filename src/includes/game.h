#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>

#include "boid.h"
#include "predator.h"
#include "food.h"

class Game
{
    private:
    sf::RenderWindow m_window;
    unsigned int m_window_width;
    unsigned int m_window_height;
    std::vector<Boid> m_boids;
    std::vector<Food> m_food;

    public:
    Game();
    Game(unsigned int width, unsigned int height);
    sf::Vector2f random_within_bounds();
    void run(int boids_number, int predator_number);
    void render();
};
