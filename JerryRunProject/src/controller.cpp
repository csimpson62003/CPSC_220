#include "raylib.h"
#include "controller.h"

#include <math.h>

int main(void)
{

    Controller c;
    c.gameLoop();

    return 0;
}
void Controller::gameLoop() {

    SetTargetFPS(60);
    map<KeyboardKey, userAction> keyMapping;

    keyMapping[KEY_W] = PlayerUp;
    keyMapping[KEY_A] = PlayerLeft;
    keyMapping[KEY_S] = PlayerDown;
    keyMapping[KEY_D] = PlayerRight;
    

    PubSub::subscribe("entity", this);
    
        InitWindow(GetScreenWidth(), GetScreenHeight(),"JerryRun");
        SetTargetFPS(60);
        ToggleFullscreen();
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        // Load the level

        float x = 320;
        float y = 320;
        WorldView worldView;

        world.addStation(100, 10, 16, 16, portal, "Portal", 10); //Draws the portal
        world.addStation(300, 10, 16, 16, extendedRangeStation, "ExtendedRange", 15); //Draws the ExtendedRangeStation
        world.addStation(500, 10, 16, 16, healingStation, "Healing", 10); //Draws the HealingStation
        world.addStation(700, 10, 16, 16, powerStation, "Power", 10);
        world.addStation(900, 10, 16, 16, speedStation, "speedStation", 10);
        world.addPlayer(screenWidth / 2, screenHeight / 2, 16, 16, jerry, "Jerry", 40);

        while (!WindowShouldClose() && world.getAliveState())
        {
            world.EnemyCount(10);
            worldView.draw(world.getCoins(), world.getWorldLevel(), world.getDeletedEnemiesCount());


            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                userAction action = PlayerHit;
                PubSub::publish("action", "player", &action);
            }
            // Handle user input
            for (auto& i : keyMapping)
            {
                if (IsKeyDown(i.first))
                {
                    userAction action = i.second;
                    PubSub::publish("action", "player", &action);
                }
            }


            // Give the world a chance to progress
            world.tick();

            BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw the views
            for (EntityView* view : views)
                view->draw();

            EndDrawing();


        }
        while (!WindowShouldClose() && world.getAliveState() == false) {

         
            worldView.deathScreenDraw(world.getWorldLevel(), world.getDeletedEnemiesCount());
            BeginDrawing();

            ClearBackground(RAYWHITE);
            EndDrawing();
        }
        world.clearWorld();

    
    CloseWindow();
}

void Controller::receiveMessage(string channel, string message, void* data)
{

    if (channel == "entity" && message == "hit") {
        Entity* entity = (Entity*)data;
        entity->setHealth(entity->getHealth() - (2*world.getWorldLevel()));
    }
   //See if user can afford station. If he can, buy it, decrease the coins, increase the cost&level of the station, and continue
    if (channel == "entity" && message == "buyStation") {
        Entity* station = (Entity*)data;
        if (station->getPrice() <= world.getCoins()) {
            world.setCoins(world.getCoins() - station->getPrice()); //Buy the station, subtract user coins.
            station->setLevel(station->getLevel() + 1); //Adds one level to the station level
            station->setPrice(station->getPrice() * 1.5); //Sets the price, (the current price * 1.5)
            PubSub::publish("stations", "bought", station);
        }
    }
    if (channel == "entity" && message == "new")
    {
        // Create a view for the entity
        EntityView* view = new EntityView((Entity*)data);
        views.push_back(view);
    }

    if (channel == "entity" && message == "delete")
    {
        

        

        // Try to find the view for the entity that's being deleted
        for (int i = 0; i < views.size(); i++)
        {

     
            if (views[i]->isViewFor((Entity*)data))
            {
                delete views[i];
                // Delete it from the vector
                views.erase(views.begin() + i);
                // and stop looking, since we found the right view
                break;
            }
        }

        Entity* entity = (Entity*)data;
        if (entity->getType() == jerry) {
            world.setAliveState(false);
            return;
        }

        world.setCoins(world.getCoins() + GetRandomValue(3, 5));

        world.increaseDeletedEnemies(1);
    }
}
