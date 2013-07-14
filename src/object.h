#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace Purity
{
    const float32 PIXELS_PER_METER = 30.0f;
    const float32 DEFAULT_HITBOX_WIDTH_METERS = 0.5;
    const float32 DEFAULT_HITBOX_HEIGHT_METERS = 1.5;

    const float32 DEFAULT_HITBOX_WIDTH_PIXELS  = PIXELS_PER_METER * DEFAULT_HITBOX_WIDTH_METERS; 
    const float32 DEFAULT_HITBOX_HEIGHT_PIXELS = PIXELS_PER_METER * DEFAULT_HITBOX_HEIGHT_METERS;


    const float DEFAULT_HITBOX_OUTLINE_THICKNESS = 2.0;
    const sf::Color DEFAULT_HITBOX_OUTLINE_COLOR = sf::Color::Yellow;
    const sf::Color DEFAULT_HITBOX_FILL_COLOR = sf::Color::Transparent;

    class Object : public sf::Drawable
    {
    public:
        Object(float x, float y, b2World* world);

        virtual void createBody(b2World* world);
        void setName(std::string name);
        std::string getName() const;

        void setSize(float width, float height);

        void setX(float x);
        void setY(float y);
        float getX() const;
        float getY() const;

        void update();

    protected:
        b2BodyDef mHitboxBodyDef;
        b2Body* mHitboxBody;     
        
        // visual representation of hitbox
        sf::RectangleShape mHitboxShape;

    private:
        float mPositionX;
        float mPositionY;

        std::string mName;

        void initializeHitboxShape();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

}

#endif // OBJECT_H