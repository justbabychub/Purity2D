#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Purity
{
    class Renderer
    {
    public:
        Renderer(sf::RenderWindow* window);

        void update(const sf::Drawable* drawable);

    private:
        sf::RenderWindow* mWindow;
        int calculateFPS();
        int mFrameCounter;
    };
}

#endif // RENDERER_H