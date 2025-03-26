#include "game.h"

void Game::Game()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    m_window_width = desktop.width;
    m_window_height = desktop.height;

    m_window.create(sf::VideoMode(m_window_width, m_window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);
    m_window.setFramerateLimit(60);
}

void Game::Game(int width, int height)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    m_window_width = width;
    m_window_height = height;

    m_window.create(sf::VideoMode(m_window_width, m_window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);
}

void Game::run(int boids_number)
{
    for(int i = 0; i < boids_number; i++)
    {
        Boid boid((m_window_width/2, m_window_height/2), 0.f);

        m_boids.push_back(boid);
    }

    while(m_window.isOpen())
    {
        render();
    }
}

void Game::render()
{
    m_window.clear();
    for(Boid boid : m_boids)
    {
        window.draw(boid);
    }
}