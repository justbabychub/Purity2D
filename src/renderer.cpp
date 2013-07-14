#include "renderer.h"

Purity::Renderer::Renderer(sf::RenderWindow* window)
{
    mWindow = window;
    mFrameCounter = 0;
}

void Purity::Renderer::update(const sf::Drawable* drawable)
{
    mWindow->clear();
    mWindow->draw(*drawable);
    mWindow->display();
    std::cout << calculateFPS() << std::endl;
}

int Purity::Renderer::calculateFPS()
{
    static sf::Clock timer;
    static int fps = 0;

    mFrameCounter++;

    if (timer.getElapsedTime().asMilliseconds() >= 1000)
    {
        timer.restart();
        fps = mFrameCounter;
        mFrameCounter = 0;
    }

    return fps;
}