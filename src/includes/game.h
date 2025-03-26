#pragma once
#include <SFML/Graphics.hpp>
#include "boid.h"

class Game
{
    private:
    sf::RenderWindow m_window;
    int m_window_width;
    int m_window_height;
    vector<Boid> m_boids;

    public:
    Game();
    Game(int width, int height);
    void run();
    void render();
}