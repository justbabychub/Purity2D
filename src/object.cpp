#include "object.h"

Purity::Object::Object(float x, float y, b2World* world)
{
    mHitboxBodyDef.type = b2_dynamicBody;

    mHitboxBodyDef.position.Set(14, 3);

    createBody(world);
    setX(x);
    setY(y);
    initializeHitboxShape();
    setSize(DEFAULT_HITBOX_WIDTH_METERS, DEFAULT_HITBOX_HEIGHT_METERS);
}

std::string Purity::Object::getName() const
{
    return mName;
}

void Purity::Object::setX(float x)
{
    this->mPositionX = x;
    b2Vec2 pos;
    pos.Set(x, getY());

    mHitboxBody->SetTransform(pos, mHitboxBody->GetAngle());
}

void Purity::Object::setY(float y)
{
    this->mPositionY = y;
    b2Vec2 pos;
    pos.Set(getX(), y);

    mHitboxBody->SetTransform(pos, mHitboxBody->GetAngle());
}

float Purity::Object::getX() const
{
    return mPositionX;
}

float Purity::Object::getY() const
{
    return mPositionY;
}

void Purity::Object::update()
{
    float posX, posY;

    posX = (mHitboxBody->GetPosition().x * PIXELS_PER_METER) - (mHitboxShape.getSize().x/2);
    posY = (mHitboxBody->GetPosition().y * PIXELS_PER_METER) - (mHitboxShape.getSize().y/2);

    mHitboxShape.setPosition(posX, posY);
}

void Purity::Object::createBody(b2World* world)
{
    mHitboxBody = world->CreateBody(&mHitboxBodyDef);
    mHitboxBody->SetUserData( this );
}

void Purity::Object::setSize(float width, float height)
{
    b2PolygonShape hitboxBox;

    hitboxBox.SetAsBox(width/2, height/2);

    b2FixtureDef hitboxFixtureDef;
    hitboxFixtureDef.shape = &hitboxBox;

    hitboxFixtureDef.density = 0.0f;
    mHitboxBody->CreateFixture(&hitboxFixtureDef);

    b2Vec2 vertices[4];
    int verticeCount = 4;

    vertices[0].Set(-width * 1.25, height / -2);
    vertices[1].Set(width * 1.25, height / -2);
    vertices[2].Set(width * 1.25, 0);
    vertices[3].Set(-width * 1.25,  0);

    mHitboxShape.setPosition(0, 0);
    sf::Vector2f hitboxSize(width*PIXELS_PER_METER, height*PIXELS_PER_METER);
    mHitboxShape.setSize(hitboxSize);
    mHitboxShape.setOutlineColor(DEFAULT_HITBOX_OUTLINE_COLOR);
    mHitboxShape.setOutlineThickness(DEFAULT_HITBOX_OUTLINE_THICKNESS);
    mHitboxShape.setFillColor(DEFAULT_HITBOX_FILL_COLOR);
}

void Purity::Object::initializeHitboxShape()
{
}

void Purity::Object::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mHitboxShape);
}