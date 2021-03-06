#include "scene.h"

Purity::Scene::Scene(const boost::filesystem::path& sceneDir)
{
    boost::filesystem::path mapFilePath(sceneDir.string() + DEFAULT_MAP_FILENAME);

    mLuaEventHandlerFile = sceneDir.string() + DEFAULT_EVENT_HANDLER_FILENAME;
	mLuaPhysicsUpdateFile = sceneDir.string() + DEFAULT_ON_PHYSICS_UPDATE_SCRIPT;

    mTmxMap = std::unique_ptr<Tmx::Map>(new Tmx::Map);
    
    mTmxMap->ParseFile(mapFilePath.string());

    mMap = std::unique_ptr<GameMap>(new GameMap(mTmxMap.get(), sceneDir));
}

void Purity::Scene::initializePhysics(b2World * world)
{
    mMutex.lock();

    initializeTiles(world);
    mObjectManager = std::unique_ptr<ObjectManager>(new ObjectManager(mTmxMap.get(), world));

    mMutex.unlock();
}

std::string Purity::Scene::getLuaEventHandlerPath() const
{
    return mLuaEventHandlerFile.string();
}

std::string Purity::Scene::getLuaEventHandlerFunctionName() const
{
    return DEFAULT_EVENT_HANDLER_FUNCTION_NAME;
}

std::string Purity::Scene::getLuaPhysicsUpdatePath() const
{
    return mLuaPhysicsUpdateFile.string();
}


void Purity::Scene::initializeTiles(b2World * world)
{
    mMap->initializeTilePhysics(world);
}

void Purity::Scene::initializeObjects(b2World* world)
{

}

void Purity::Scene::updatePhysics()
{    
    mMutex.lock();

    mObjectManager->updatePhysics();

    mMutex.unlock();
}

void Purity::Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    mMutex.lock();

    target.draw(*mMap, states);

    target.draw(*mObjectManager, states);

    mMutex.unlock();
}
