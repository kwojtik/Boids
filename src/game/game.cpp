#include "game.h"

Game::Game()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    m_window_width = 1024;
    m_window_height = 1024;

    m_window.create(sf::VideoMode({m_window_width, m_window_height}, desktop.bitsPerPixel), "Boids", sf::Style::None);
    m_window.setFramerateLimit(60);
}

Game::Game(unsigned int width, unsigned int height)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    m_window_width = width;
    m_window_height = height;

    m_window.create(sf::VideoMode({m_window_width, m_window_height}, desktop.bitsPerPixel), "Boids", sf::Style::None);
}

sf::Vector2f Game::random_within_bounds()
{
    sf::Vector2f random({float(rand()%m_window_width), float(rand()%m_window_height)});

    return random;
}

void Game::run(int boids_number, int predator_number)
{
    srand(time(0));
    for(int i = 0; i < boids_number; i++)
    {
        Boid boid(random_within_bounds(), sf::Angle());

        m_boids.push_back(boid);
    }
    for(int i = 0; i < predator_number; i++)
    {
        Predator predator(random_within_bounds(), sf::Angle());

        m_boids.push_back(predator);
    }

    while(m_window.isOpen())
    {
        render();
    }
}

void Game::render()
{
    m_window.clear();

    for(Boid& boid : m_boids)
    {
        boid.update_position(m_boids, m_window_height, m_window_width);
        m_window.draw(boid);
    }

    m_window.display();
}
