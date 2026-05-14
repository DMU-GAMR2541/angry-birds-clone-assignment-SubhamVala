#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <iostream>

#include "DynamicObject.h"
#include "StaticObject.h"
#include "Bird.h"
#include "Plank.h"
#include "Pig.h"
#include "Non-Interactable.h"
#include "Catapult.h"
#include "ContactListener.h"
#include "UI.h"






int main() {

    // --- 1. WINDOW SETUP ---
    sf::RenderWindow window(sf::VideoMode(800, 600), "Annoyed_Flocks");
    window.setFramerateLimit(60);

    //Box2D works in meters. SFML works in pixels.
    const float SCALE = 30.0f;

    //Can set a definition for PI.
    const float PI = 3.1415927;

    //setup world.
    
    b2Vec2 b2_gravity(0.0f, 9.8f); // Earth-like gravity
    b2World world(b2_gravity);
    
    // creates the Listener instnance.
    ContactListener contactlistener;
    // Registers it with the world.
    world.SetContactListener(&contactlistener);

    // Inherited classes, setting parameter values.
    Catapult catapult(world, 150.0f, 520.0f, 10.0f, 60.0f, "../assets/Ang_Birds/Slingshot.png");
    UI ui(world, "../assets/fonts/angry-birds.ttf", "../assets/Ang_Birds/AngryBirds_StartScreen.jpg", 50, b2Vec2(625, 25));
    UI CompleteLevel(world, "../assets/fonts/angry-birds.ttf", "../assets/Ang_Birds/AngryBirds_StartScreen.jpg", 50, b2Vec2(300, 300));
    UI StartLevel(world, "../assets/fonts/angry-birds.ttf", "../assets/Ang_Birds/AngryBirds_StartScreen.jpg", 50, b2Vec2(140, 480));

    // stores the different bird types into a vector to iterate through.
    std::vector<std::string> birdTextures = { "../assets/Ang_Birds/BlueBird.png", "../assets/Ang_Birds/MainBird.png",  "../assets/Ang_Birds/YellowBird.png", "../assets/Ang_Birds/BlackBird.png" };

    // stores the different pig positions into a vector to iterate through.
    std::vector<sf::Vector2f> pigPositions = {
        {522.0f, 590.0f},
        {520.0f, 400.0f},
        {665.0f, 400.0f},
        {575.0f, 200.0f}
    };

    // stores the different plank positions into a vector to iterate through.
    std::vector<sf::Vector2f> plankPositions = {
        {500.0f, 530.0f},
        {570.0f, 530.0f},
        {630.0f, 530.0f},
        {680.0f, 530.0f},
        {550.0f, 380.0f},
        {630.0f, 380.0f},
        {560.0f, 200.0f},
        {630.0f, 200.0f},
        {530.0f, 430.0f},
        {650.0f, 430.0f},
        {590.0f, 320.0f},

    };

    

    // creates the STL sequence containers.
    std::vector<std::shared_ptr<Pig>> pigPtr;
    std::vector<std::shared_ptr<Plank>> plankPtr;
    std::vector<std::shared_ptr<NonInteractable>> Noninteractable;
    std::list<std::shared_ptr<Bird>> birdPtr;

    // creates an instance of DynamicObjectType for birdsType.
    DynamicObject::DynamicObjectType birdtype;

    // adds the Non-interactables into the shared_pointer.
    Noninteractable.push_back(std::make_shared<NonInteractable>(world, 750.0f, 500.0f, 10.0f, 600.0f, sf::Color::Red)); // Wall
    Noninteractable.push_back(std::make_shared<NonInteractable>(world, 400.0f, 590.0f, 400.0f, 10.0f, sf::Color(34, 139, 34))); // Ground

    // adds the birds into the shared_pointer vector using a for loop.
    for (int i = 0; i < 4; i++) {
        if (i == 0) { birdtype = DynamicObject::DynamicObjectType::bluebird; }
        else if (i == 1) { birdtype = DynamicObject::DynamicObjectType::redbird; }
        else if (i == 2) { birdtype = DynamicObject::DynamicObjectType::yellowbird; }
        else { birdtype = DynamicObject::DynamicObjectType::blackbird; }

        birdPtr.push_back(std::make_shared<Bird>(world, 100.0f + (i * -20.0f), 500.0f, 15.0f, 5.0f, birdTextures[i], birdtype));
    }

    // adds the planks into the shared_pointer vector using a for loop, and giving them a type of either vertical or horizontal.
    for (int i = 0; i < plankPositions.size(); i++) {
        DynamicObject::DynamicObjectType plankType;
        if (i < 8) { plankType = DynamicObject::DynamicObjectType::VerticalPlank; }
        else { plankType = DynamicObject::DynamicObjectType::HorizontalPlank; }

        auto& plank = plankPtr.emplace_back(std::make_shared<Plank>(world, plankPositions[i].x, plankPositions[i].y, 10.0f, 60.0f, "../assets/Ang_Birds/Plank.png", 1, plankType));
        plank->getBody()->GetUserData().pointer = 10 + static_cast<uintptr_t>(i);

    }

    // adds the pigs into the shared_pointer vector using a for loop.
    for (int i = 0; i < 4; i++) {
        DynamicObject::DynamicObjectType pigtype;

        if (i == 0) { pigtype = DynamicObject::DynamicObjectType::pig; }
        else if (i == 1) { pigtype = DynamicObject::DynamicObjectType::helmpig; }
        else if (i == 2) { pigtype = DynamicObject::DynamicObjectType::bigpig; }
        else { pigtype = DynamicObject::DynamicObjectType::kingpig; }
        // gives each pig a different position, size and health.
        auto& pig = pigPtr.emplace_back(std::make_shared<Pig>(world, pigPositions[i].x, pigPositions[i].y, (15.0f + (i * 3)), (9 + (i * 2)), "../assets/Ang_Birds/Pigs.png", pigtype));
        pig->getBody()->GetUserData().pointer = 3 + static_cast<uintptr_t>(i);
    }

    

    // --- 7. MAIN LOOP ---
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            // INPUT HANDLING: Press SPACE to launch

            if (event.type == sf::Event::MouseButtonPressed) {
                // once LMB is pressed, stops gravity and rotation
                if (event.mouseButton.button == sf::Mouse::Left && ui.getGameStarted())
                {
                    // check if the bird has not been launched. preventing the same bird from being launched twice.
                    if (!birdPtr.front()->hasLaunched()) {
                        // calls dragging function from bird.h for the front bird.
                        birdPtr.front()->dragging();

                    }
                    
                }

            }

            if (event.type == sf::Event::MouseButtonReleased) {

                // once LMB is released, shoots bird depending on how much it was dragged.
                if (event.mouseButton.button == sf::Mouse::Left && ui.getGameStarted()) {

                    // check if the bird has not been launched. preventing the same bird from being launched twice.
                    if (!birdPtr.front()->hasLaunched() && !birdPtr.empty()) {
                        // calls launch function from bird.h for the front bird.
                        birdPtr.front()->launch(catapult.getShotPos());

                    }
                    
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                auto& currentBird = birdPtr.front();
                
                if (event.key.code == sf::Keyboard::Enter) {
                    ui.setGameStarted(true);
                }

                if (event.key.code == sf::Keyboard::Space && ui.getGameStarted()) {
                    
                    // creates shared_pointers for blues ability and Bombs ability.
                    std::vector<std::shared_ptr<Bird>> newBirds;
                    std::vector<std::shared_ptr<Bird>> Bomb;

                    // if the current bird is yellow and has not already used its ability, then uses ability if space is pressed.
                    if (currentBird->getBirdType() == DynamicObject::DynamicObjectType::yellowbird && !currentBird->hasUsedAbility() && ui.getGameStarted() && currentBird->hasLaunched()) {
                        currentBird->yellowBirdAbility(b2Vec2(5, 0));
                    }

                    // if the current bird is blue and has not already used its ability, then uses ability if space is pressed.
                    if (currentBird->getBirdType() == DynamicObject::DynamicObjectType::bluebird && currentBird->hasLaunched() && ui.getGameStarted()) {
                        
                        // adds the clone birds.
                        auto newBirds = currentBird->blueBirdAbility(world);

                        for (auto& bird : newBirds) {
                            birdPtr.push_back(bird);
                        }
                    }

                    // if the current bird is blackBird and has not already used its ability, then uses ability if space is pressed.
                    if (currentBird->getBirdType() == DynamicObject::DynamicObjectType::blackbird && !currentBird->hasUsedAbility() && ui.getGameStarted() && currentBird->hasLaunched()) {

                        // destroys the bird body and creates the bombEffect sprite/body.
                        auto Bomb = currentBird->blackBirdAbility(world, 1.5f, 50, pigPtr);

                        

                        //world.DestroyBody(birdPtr.front()->getBody());
                        birdPtr.front()->BirdMarkedforDeletion(0.1f);
                        
                        for (auto& bird : Bomb) {
                            birdPtr.push_back(bird);
                        }
                    }
                }
            }
                
        }

        
        if (birdPtr.front()->getDragging() && !birdPtr.front()->hasLaunched() && ui.getGameStarted() && !birdPtr.empty()) {

            // gets position of the mouse in sfml pixels.
            sf::Vector2i mousePxl = sf::Mouse::getPosition(window);
            // takes x and y position of the mouse.
            sf::Vector2f mouseWorld(mousePxl.x, mousePxl.y);

            // stores the drag of the mouse position and the start position.
            sf::Vector2f dragVec(mouseWorld - catapult.getShotPos());

            // stops player dragging towards the right
            if (dragVec.x > 0) {
                dragVec.x = 0;
            }

            // makes a distance for how much you can drag, preventing player from dragging out of the screen.
            float length = std::sqrt(dragVec.x * dragVec.x + dragVec.y * dragVec.y);
            float maxDrag = 100.0f;

            if (length > maxDrag) {
                dragVec /= length;
                dragVec *= maxDrag;
            }

            // moves the bird to the catapults position when dragging.
            sf::Vector2f finalPos = catapult.getShotPos() + dragVec;

            birdPtr.front()->getBody()->SetTransform(b2Vec2(finalPos.x / SCALE, finalPos.y / SCALE), 0);
            birdPtr.front()->dragging();
        }

        
        for (auto& bird : birdPtr) {
            bird->getBody()->GetUserData().pointer = 100;
        }

        // Update Physics
        world.Step(1.0f / 60.0f, 8, 3);

        // gets the speed of the current bird and checks if its slower than 2.0f, if its been launched and if its not been marked for deletion.
        for (auto& bird : birdPtr) {
            b2Vec2 birdVelocity = bird->getBody()->GetLinearVelocity();

            float speed = std::sqrt(birdVelocity.x * birdVelocity.x + birdVelocity.y * birdVelocity.y);

            if (bird->hasLaunched() && speed < 10.0f && !bird->BirdDeletionStarted()) {
                // deletes bird after 3s of collision.
                bird->BirdMarkedforDeletion(3.0f);


            }
        }

        //Destroys birds after the three seconds.
        for (auto it = birdPtr.begin(); it != birdPtr.end(); ) {

            if ((*it)->shouldDelete()) {

                world.DestroyBody((*it)->getBody());

                it = birdPtr.erase(it);

                std::cout << "Bird Removed" << std::endl;

                for (auto& pig : pigPtr) {
                    pig->resetDeletionMark();
                }

                contactlistener.s_ptr.clear();
            }
            else {
                ++it;
            }
        }

        if (birdPtr.empty()) {
            ui.setGameEnded(true);
        }
            
        for (auto plankIt = plankPtr.begin(); plankIt != plankPtr.end() && !(*plankIt)->isMarkedForDeletion(); ) {
            std::set<uintptr_t> h_h = contactlistener.getPointer(); //Set of pointers to the plank ID's

            uintptr_t currentPlankID = (*plankIt)->getBody()->GetUserData().pointer;

            // Check if this plank's ID exists in the hit list
            if (h_h.find(currentPlankID) != h_h.end()) { //Check through all of the container for specific Id's

                std::cout << currentPlankID << " Destroyed" << std::endl;

                std::cout << "Plank has: " << (*plankIt)->getHealth() << "  Health" << std::endl;

                // if collided with bird, takes 10 damage and marks it to prevent multiple damages.
                (*plankIt)->takeDamage(10);
                (*plankIt)->markForDeletion();

                if ((*plankIt)->checkIfPopped()) {
                    // Remove from Box2D world first
                    world.DestroyBody((*plankIt)->getBody()); //Remove the plank body from the world.

                    // Update the iterator by catching the return value of erase()
                    plankIt = plankPtr.erase(plankIt); //Erase the plank from the set.
                }

            }
            else {
                // Only increment if we didn't erase anything
                ++plankIt;
            }
        }
        

        for (auto pigIt = pigPtr.begin(); pigIt != pigPtr.end() && !(*pigIt)->isMarkedForDeletion(); ) {
            std::set<uintptr_t> s_p = contactlistener.getPointer(); //Set of pointers to the pig ID's

            uintptr_t currentPigID = (*pigIt)->getBody()->GetUserData().pointer;

            // Check if this pig's ID exists in the hit list
            if (s_p.find(currentPigID) != s_p.end()) { //Check through all of the container for specific Id's

                std::cout << currentPigID << " Destroyed" << std::endl;

                std::cout << "Pig has: " << (*pigIt)->getHealth() << "  Health" << std::endl;

                // if collided with bird, takes 10 damage and marks it to prevent multiple damages.
                (*pigIt)->takeDamage(10);
                (*pigIt)->markForDeletion();

                if ((*pigIt)->checkIfPopped()) {
                    // Remove from Box2D world first
                    world.DestroyBody((*pigIt)->getBody()); //Remove the pig body from the world.

                    // Update the iterator by catching the return value of erase()
                    pigIt = pigPtr.erase(pigIt); //Erase the pig from the set.
                    ui.getText(pigPtr.size());
                }

            }
            else {
                // Only increment if we didn't erase anything
                ++pigIt;
            }
        }

        

        


        catapult.update();


        if (ui.getGameStarted()) {

            // goes through all pigs in the pointer and updates its physics using an iterator.
            for (auto it = pigPtr.begin(); it != pigPtr.end(); it++) {
                (*it)->update();

            }

            // goes through all birds in the pointer and updates its physics using an iterator.
            for (auto it = birdPtr.begin(); it != birdPtr.end(); it++) {
                (*it)->update();
            }

            // goes through all NonInteractables in the pointer and updates it physics using an iterator.
            for (auto it = Noninteractable.begin(); it != Noninteractable.end(); it++) {
                (*it)->start();
            }

            // goes through all planks in the pointer and updates its physics using an iterator.
            for (auto it = plankPtr.begin(); it != plankPtr.end(); it++) {

                (*it)->update();

            }
        
        }


        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue

        ui.getText(pigPtr.size());


        if (!ui.getGameStarted()) {
            ui.draw(window);

        }

        

        if (ui.getGameStarted()) {

            // draws the objects to the window.
            // goes through all pigs using an iterator and draws them to the window.
            for (auto it = pigPtr.begin(); it != pigPtr.end(); it++) {
                (*it)->draw(window);
            }

            // goes through all birds using an iterator and draws them to the window.
            for (auto it = birdPtr.begin(); it != birdPtr.end(); it++) {
                (*it)->draw(window);
            }

            // goes through all noninteractables using an iterator and draws them to the window.
            for (auto it = Noninteractable.begin(); it != Noninteractable.end(); it++) {
                (*it)->draw(window);
            }

            // goes through all planks using an iterator and draws them to the window.
            for (auto it = plankPtr.begin(); it != plankPtr.end(); it++) {
                (*it)->draw(window);
            }

            catapult.draw(window);
            ui.render(window);
        }
        
        // once no pigs are on screen game won.
        if (pigPtr.empty()) {

            CompleteLevel.endText("Pigs Defeated!!!");
            CompleteLevel.render(window);
        }

        // when game starts tells user to press enter
        else if (!ui.getGameStarted()) {
            StartLevel.endText("Press Enter to start game");
            StartLevel.render(window);
        }

        // once no birds are ready to launch then game lost.
        else if (birdPtr.empty() && !pigPtr.empty()) {
            CompleteLevel.endText("You Lost!!!");
            CompleteLevel.render(window);
        }

        window.display();
    }

    return 0;
}