#include "objectmanager.h"

Purity::ObjectManager::ObjectManager(const Tmx::Map* tmxMap, b2World* world)
{
    mTmxMap = tmxMap;
    mWorld = world;

    initializeObjects();

    luabind::globals(LuaManager::getManager()->getState())["GObjectManager"] = this;
}

const Purity::Object* Purity::ObjectManager::getObjectByName(const std::string& objectName)
{

    for (int i = 0; i < mObjectList.size(); i++)
    {
        if (mObjectList.at(i).getName() == objectName)
        {
            return &mObjectList.at(i);
        }
    }

    return nullptr;
}

Purity::MovableObject* Purity::ObjectManager::getMovableObjectByName(const std::string& objectName)
{

    for (int i = 0; i < mMovableObjectList.size(); i++)
    {
        if (mMovableObjectList.at(i).getName() == objectName)
        {
            return &mMovableObjectList.at(i);
        }
    }

    return nullptr;
}

void Purity::ObjectManager::initializeObjects()
{
    int numOfGroups = mTmxMap->GetNumObjectGroups();
   

    for (int groupNum = 0; groupNum < numOfGroups; groupNum++)
    {
        const Tmx::ObjectGroup* currentGroup;
        int numOfObjectsInGroup;

        currentGroup = mTmxMap->GetObjectGroup(groupNum);
        numOfObjectsInGroup = currentGroup->GetNumObjects();

        for (int objectNum = 0; objectNum < numOfObjectsInGroup; objectNum++)
        {
            const Tmx::Object* currentObject;

            currentObject = currentGroup->GetObject(objectNum);

            if (currentObject->GetType() == "Movable")
            {
                MovableObject object(currentObject, mWorld);
                mMovableObjectList.push_back(object);
                
            }
            else
            {
                Object object(currentObject, mWorld);
                mObjectList.push_back(object);
            }
            
        }
    }
}

void Purity::ObjectManager::updatePhysics()
{
    for (int i = 0; i < mObjectList.size(); i++)
    {
        mObjectList.at(i).update();
    }
    for (int i = 0; i < mMovableObjectList.size(); i++)
    {
        mMovableObjectList.at(i).update();
    }
}

void Purity::ObjectManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i = 0; i < mObjectList.size(); i++)
    {
        target.draw(mObjectList.at(i));
    }
    for (int i = 0; i < mMovableObjectList.size(); i++)
    {
        target.draw(mMovableObjectList.at(i));
    }
}

luabind::scope Purity::ObjectManager::luaBindings()
{
    return luabind::class_<ObjectManager>("ObjectManager")
        .def("getObjectByName", &ObjectManager::getObjectByName)
        .def("getMovableObjectByName", &ObjectManager::getMovableObjectByName)
    ;
}