#include <iostream>
#include <cstdlib>
#include <ctime>
#include "world.h"
#include "playerentity.h"
#include "enemyEntity.h"
#include "station/portalEntity.h"
#include "station/extendedRangeStation.h"
#include "station/powerStation.h"
#include "station/healingStation.h"
#include "Station/speedStation.h"
#include "pubsub.h"
#include "raylib.h"

World::World()
{
	srand(time(NULL));
}

void World::EnemyCount(int enemyBaseHealth) {
	int enemyCount = 0;
	for (Entity* entity : entities) {
		if (entity->getType() == enemy) {
			enemyCount++;
		};

	}
	if (enemyCount == 0) {
		this->setWorldLevel(this->getWorldLevel() + 1);
			for (int i = 0; i < 5 * this->getWorldLevel(); i++) {
				int topBottomLeftOrRight = GetRandomValue(1, 4);
				switch (topBottomLeftOrRight) {
				case 1: //Enemy will spawn in on the left side
					addEnemy(1+ (16 * scale), GetRandomValue(1 + (16 * scale), screenHeight - (16 * scale) - 1), 16, 16, enemy, "", enemyBaseHealth);
					break;
				case 2: //Enemy will spawn on the right side
					addEnemy(screenWidth - (16 * scale) - 1, GetRandomValue(1 + (16 * scale), screenHeight - (16 * scale) - 1), 16, 16, enemy, "", enemyBaseHealth);
					break;
				case 3: //Enemy will spawn in on the top
					addEnemy(GetRandomValue(1 + (16 * scale), screenWidth - (16 * scale) - 1), 1 + (16 * scale), 16, 16, enemy, "", enemyBaseHealth);
					break;
				case 4: //Enemy will spawn on the bottom
					addEnemy(GetRandomValue(1 + (16 * scale), screenWidth - (16 * scale) - 1), screenHeight - (16 * scale) - 1, 16, 16, enemy, "", enemyBaseHealth);
					break;
				}
			};
			
			for (Entity* entity : entities) {
				if (entity->getType() == enemy) {
					entity->setMaxHealth(entity->getMaxHealth() + (1.5 * this->getWorldLevel()));
					entity->setHealth(entity->getMaxHealth());
					entity->setPower(entity->getPower() + (1.25 * this->getWorldLevel()));
				}
			}
	}

}

void World::tick()
{
	for (Entity* entity : entities) {
		entity->tick();
	}


	//Detect collisions
	collisions.clear();
	for (Entity* entity : entities) {
		if (entity->getMoving() || (entity->getType() != jerry && entity->getType() != enemy) ) {
			for (Entity* entity2 : entities) {
				if (entity != entity2) {
					checkCollision(entity, entity2);
				}
			}
		}
	}


	//Handle Collisions
	deletions.clear();
	for (Entity* entity : collisions) {
		if (entity->handleCollision()) {
			deletions.push_back(entity);
			
		}
	}
	//Handing 0 Health entities.
	for (Entity* entity : entities) {
		if (entity->getHealth() <= 0) {
			deletions.push_back(entity);
		}
	}
	// Remove deleted entities
	for (Entity* entity : deletions)
	{
		// Remove from the entities array
		vector<Entity*>::iterator result = find(entities.begin(),
			entities.end(), entity);
		if (result != entities.end())
			entities.erase(result);
		// Tell the views about the deletion
		PubSub::publish("entity", "delete", entity);
		delete entity;
		// Delete memory

	}
}

void World::increaseDeletedEnemies(int number)
{
	this->deletedEnemiesCount += number;
}

int World::getDeletedEnemiesCount()
{
	return this->deletedEnemiesCount;
}

void World::setCoins(int coinNumber)
{
	this->coins = coinNumber;
}
int World::getCoins() {
	return this->coins;
}
bool World::getAliveState()
{
	return stillAlive;
}
void World::setAliveState(bool stillAlive) {
	this->stillAlive = stillAlive;
}
void World::checkCollision(Entity* entity, Entity* entity2) {
	//This code will make it so dead enemies can not hurt me, until they are removed from the game.
	if ((entity->getHealth() <= 0 || entity2->getHealth() <= 0) && entity->getType() == enemy || entity2->getType() == enemy) {
		return; // Skip dead entities
	}
	Rectangle rec1 = { entity->getXPos(),entity->getYPos(), entity->getWidth(), entity->getHeight() };
	Rectangle rec2 = { entity2->getXPos(),entity2->getYPos(), entity2->getWidth(), entity2->getHeight() };
	if (CheckCollisionRecs(rec1, rec2)) {
		entity->addCollision(entity);
		entity->addCollision(entity2);


		if (find(collisions.begin(), collisions.end(), entity) == collisions.end()) {
			collisions.push_back(entity);
			collisions.push_back(entity2);
		}
	}
}

void World::clearWorld()
{
	for (Entity* entity : entities)
	{
		// Let everyone know we're deleting this entity
		PubSub::publish("entity", "delete", entity);
		delete entity;
	}

	entities.clear();
}

void World::addEntity(int x, int y, int width, int height, EntityType type, string EntityName)
{
	Entity* entity = new Entity(x, y, width, height, type, EntityName);

	// Let everyone know the entity has been created
	PubSub::publish("entity", "new", entity);

	entities.push_back(entity);
}

void World::addStation(int x, int y, int width, int height, EntityType type, string stationName, int price)
{
	Entity* entity;
	switch (type) {
	case portal:
		entity = new PortalEntity(x, y, width, height, type, stationName, price);
		break;
	case extendedRangeStation:
		entity = new ExtendedRangeStation(x, y, width, height, type, stationName, price);
		break;
	case healingStation:
		entity = new HealingStation(x, y, width, height, type, stationName, price);
		break;
	case powerStation:
		entity = new PowerStation(x, y, width, height, type, stationName, price);
		break;
	case speedStation:
		entity = new SpeedStation(x, y, width, height, type, stationName, price);
		break;
	}
	PubSub::publish("entity", "new", entity);
	entities.push_back(entity);
}

void World::setWorldLevel(int worldLevel)
{
	this->worldLevel = worldLevel;
}

int World::getWorldLevel()
{
	return this->worldLevel;
}


void World::addPlayer(int x, int y, int width, int height, EntityType type, string playerName, float health)
{
	Entity* entity = new PlayerEntity(x, y, width, height, type, playerName, health);

	// Let everyone know the entity has been created
	PubSub::publish("entity", "new", entity);

	entities.push_back(entity);
	
}

void World::addEnemy(int x, int y, int width, int height, EntityType type, string playerName, float health)
{
	Entity* player;
	for (Entity* entity : entities) {
		if (entity->getType() == jerry){
			player = entity;
			break;
		}
	}
	
	Entity* entity = new EnemyEntity(x, y, width, height, type, playerName, health,player);

	// Let everyone know the entity has been created
	PubSub::publish("entity", "new", entity);

	entities.push_back(entity);
}

vector<Entity*> World::getWorldEntities()
{
	return this->entities;
}


