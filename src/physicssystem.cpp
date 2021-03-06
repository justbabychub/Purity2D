#include "physicssystem.h"

Purity::PhysicsSystem::PhysicsSystem(std::queue<sf::Event>* inputQueue)
{
    mWorld = std::unique_ptr<b2World>(new b2World(GRAVITY));

    mCurrentScene = nullptr;
    mLastTime = 0;
    mFrameTimeMilleseconds = 0;
    mFrameTimer.restart().asMicroseconds();

    mInputQueue = inputQueue;
}

void Purity::PhysicsSystem::update(Purity::Scene* scene) 
{
    if (scene != mCurrentScene)
    {
        mCurrentScene = scene;
        
        mCurrentScene->initializePhysics(mWorld.get());
    }
    step();
    mCurrentScene->updatePhysics();
}

void Purity::PhysicsSystem::step()
{
    static float acumulator = 0.0;

    mLastTime = mFrameTimeMilleseconds;
    mFrameTimeMilleseconds = mFrameTimer.getElapsedTime().asMilliseconds();

    acumulator += (mFrameTimeMilleseconds - mLastTime);
    
    while (acumulator >= (TIME_STEP * 1000))
    {
	    handleInput();
		runUpdateScripts();

        mWorld->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

        acumulator -= (TIME_STEP * 1000);
    }
}

void Purity::PhysicsSystem::handleInput()
{
    std::string luaEventHandlerFileName = mCurrentScene->getLuaEventHandlerPath();
    std::string luaEventHandlerFunction = mCurrentScene->getLuaEventHandlerFunctionName();
    LuaManager* luaManager = LuaManager::getManager();
    lua_State* luaState = luaManager->getState();
    
    while (!mInputQueue->empty())
    {
	    sf::Event event = mInputQueue->front();
	    mInputQueue->pop();
	
	    luaManager->doFile(luaEventHandlerFileName);

	    luabind::call_function<void>(luaState, luaEventHandlerFunction.c_str(), event);
    }
}

void Purity::PhysicsSystem::runUpdateScripts()
{
    LuaManager* luaManager = LuaManager::getManager();
	std::string physicsUpdateScript = mCurrentScene->getLuaPhysicsUpdatePath();

	luaManager->doFile(physicsUpdateScript);
}