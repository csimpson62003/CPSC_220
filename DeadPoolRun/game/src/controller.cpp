#include "raylib.h"
#include "controller.h"

#include <math.h>

int main(void)
{

    Controller c;
    c.gameLoop();

    return 0;
}
int viewportWidth = 0;
int viewportHeight = 0;
int viewportX = 0;
int viewportY = 0;
int viewportDrawX;
int viewportDrawY = 0;

void Controller::gameLoop() {

    SetTargetFPS(60);
    map<KeyboardKey, userAction> keyMapping;

    keyMapping[KEY_W] = PlayerUp;
    keyMapping[KEY_A] = PlayerLeft;
    keyMapping[KEY_S] = PlayerDown;
    keyMapping[KEY_D] = PlayerRight;


    PubSub::subscribe("entity", this);
    PubSub::subscribe("particle", this);
    PubSub::subscribe("action", this);
    PubSub::subscribe("player", this);

   InitWindow(GetScreenWidth(), GetScreenHeight(), "DeadpoolRun");
   InitAudioDevice();
   // InitWindow(700, 500, "DeadpoolRun");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
   ToggleFullscreen();
    
   

  

    viewportWidth = GetScreenWidth();
    viewportHeight = GetScreenHeight();
    world.addPlayer((worldWidth / 2)-8, (worldHeight/ 2)-8, 16, 16, Deadpool, "Deadpool", 40);
    screen.addPowerUp(healthType, 10, 10, 32, 32, 10, 1);
    screen.addPowerUp(speedType, 10, 200, 32, 32, 10, 1);
    screen.addPowerUp(powerType, 10, 390, 32, 32, 10, 1);
    screen.addPowerUp(extendedRangeType, 10, 580, 32, 32, 10, 1);
    ScreenView screenView(screen.getPowerUps());
    //Background Sound
    string backgroundMusic = "resources/ByeByeBye.mp3";
    Sound deadPoolByeByeBye = LoadSound(backgroundMusic.c_str());
    int step = 1;
    //Intro Text
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            step++;
            if (step > 5) {
                break;
            }
        }
        BeginDrawing();
        screenView.drawBackground(viewportX, viewportY, viewportWidth, viewportHeight);
        screenView.drawIntroText(step);
        
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    
    while (!WindowShouldClose() && world.getAliveState())
    {
        world.EnemyCount(10);
        if (!IsSoundPlaying(deadPoolByeByeBye)) {
            PlaySound(deadPoolByeByeBye);
       }



        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
           for (PowerUps* power : screen.getPowerUps()) {
                Rectangle hitPowerUp = {
                power->getXPos(),power->getYPos(),power->getWidth(),power->getHeight()
                };

                Vector2 mouse = GetMousePosition();
                if ((mouse.x > hitPowerUp.x) && (mouse.x < hitPowerUp.width + hitPowerUp.x) && (mouse.y > hitPowerUp.y) && (mouse.y < hitPowerUp.height + hitPowerUp.y)) {
                    if (power->getCost() <= world.getCoins()) {
                        world.setCoins(world.getCoins() - power->getCost());
                        PubSub::publish("power_up", "buy", power);
                        power->setLevel(power->getLevel() + 1);
                        power->setCost(power->getCost() * 1.5);
                    }
                }
            }
           
         
        }
        // Handle user input

        if (IsKeyPressed(KEY_SPACE)) {
            userAction action = PlayerHit;
            PubSub::publish("action", "player", &action);
        }
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
        screenView.drawBackground(viewportX, viewportY, viewportWidth, viewportHeight);

        // Draw the views
        for (EntityView* view : views)
            view->draw(viewportX, viewportY, viewportDrawX, viewportDrawY,viewportWidth, viewportHeight);
        for (ParticleView* pView : particleViews) {
            pView->draw(viewportX, viewportY, viewportDrawX, viewportDrawY);
        }

        screenView.draw(world.getCoins(), world.getWorldLevel(), world.getDeletedEnemiesCount(), viewportX, viewportY, viewportDrawX, viewportDrawY, viewportWidth, viewportHeight);

        EndDrawing();


    }
    while (!WindowShouldClose() && world.getAliveState() == false) {

        StopSound(deadPoolByeByeBye);
        screenView.deathScreenDraw(world.getWorldLevel(), world.getDeletedEnemiesCount(), viewportDrawX, viewportDrawY, viewportWidth, viewportHeight);
        BeginDrawing();

        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    world.clearWorld();


    CloseWindow();
}

void Controller::receiveMessage(string channel, string message, void* data)
{
    if (channel == "action" && message == "attack") {
        Entity* entity = (Entity*)data;
        world.addParticle(attackParticle, entity->getXPos(), entity->getYPos(), entity, 20);
    }
    if (channel == "player" && message == "location")
    {
        Vector2* position = (Vector2*)data;
        if ((position->x - viewportWidth / 2) >=0 && position->x + viewportWidth / 2 <= worldWidth){
            viewportX = position->x - viewportWidth / 2;
            
        }
        if ((position->y - viewportHeight / 2) >= 0 && position->y + viewportHeight / 2 <= worldHeight) {
            viewportY = position->y - viewportHeight / 2;
        }
    }
    if (channel == "entity" && message == "hit") {
        Entity* entity = (Entity*)data;
        entity->setHealth(entity->getHealth() - (2 * world.getWorldLevel()));
    }
    //See if user can afford station. If he can, buy it, decrease the coins, increase the cost&level of the station, and continue
   
    if (channel == "entity" && message == "new")
    {
        // Create a view for the entity
        EntityView* view = new EntityView((Entity*)data);
        views.push_back(view);
    }

    if (channel == "particle" && message == "new")
    {
        // Create a view for the entity
        ParticleView* view = new ParticleView((Particles*)data);
        particleViews.push_back(view);
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
        if (entity->getType() == Deadpool) {
            world.setAliveState(false);
            return;
        }





        if (channel == "particle" && message == "delete")
        {




            // Try to find the view for the entity that's being deleted
            for (int i = 0; i < particleViews.size(); i++)
            {


                if (particleViews[i]->isViewFor((Particles*)data))
                {
                    delete particleViews[i];
                    // Delete it from the vector
                    particleViews.erase(particleViews.begin() + i);
                    // and stop looking, since we found the right view
                    break;
                }
            }
        }

        world.setCoins(world.getCoins() + GetRandomValue(3, 5));

        world.increaseDeletedEnemies(1);
    }
}