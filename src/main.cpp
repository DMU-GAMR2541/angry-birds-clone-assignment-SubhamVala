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
    
    ContactListener contactlister;
    world.SetContactListener(&contactlister);

    // Inherited classes, setting parameter values.
    Catapult catapult(world, 150.0f, 520.0f, 10.0f, 60.0f, "../assets/Ang_Birds/Slingshot.png");
    Plank plank(world, 500.0f, 550.0f, 10.0f, 60.0f, "../assets/Ang_Birds/Plank.png");;

    // stores the different bird types into a vector to iterate through.
    std::vector<std::string> birdTextures = { "../assets/Ang_Birds/BlueBird.png", "../assets/Ang_Birds/MainBird.png",  "../assets/Ang_Birds/YellowBird.png", "../assets/Ang_Birds/BlackBird.png" };

    // creates the STL sequence containers.
    std::vector<std::shared_ptr<Pig>> pigPtr;
    std::vector<std::shared_ptr<NonInteractable>> Noninteractable;
    std::list<std::shared_ptr<Bird>> birdPtr;

    DynamicObject::DynamicObjectType birdtype;

    Noninteractable.push_back(std::make_shared<NonInteractable>(world, 750.0f, 500.0f, 10.0f, 80.0f, sf::Color::Red));
    Noninteractable.push_back(std::make_shared<NonInteractable>(world, 400.0f, 590.0f, 400.0f, 10.0f, sf::Color(34, 139, 34)));

    // adds the birds into the shared_pointer vector using a for loop.
    for (int i = 0; i < 4; i++) {
        if (i == 0) { birdtype = DynamicObject::DynamicObjectType::bluebird; }
        else if (i == 1) { birdtype = DynamicObject::DynamicObjectType::redbird; }
        else if (i == 2) { birdtype = DynamicObject::DynamicObjectType::yellowbird; }
        else { birdtype = DynamicObject::DynamicObjectType::blackbird; }

        birdPtr.push_back(std::make_shared<Bird>(world, 100.0f + (i * -20.0f), 500.0f, 15.0f, 5.0f, birdTextures[i], birdtype));
    }

    
    // adds the pigs into the shared_pointer vector using a for loop.
    for (int i = 0; i < 4; i++) {
        DynamicObject::DynamicObjectType pigtype;

        if (i == 0) { pigtype = DynamicObject::DynamicObjectType::pig; }
        else if (i == 1) { pigtype = DynamicObject::DynamicObjectType::helmpig; }
        else if (i == 2) { pigtype = DynamicObject::DynamicObjectType::bigpig; }
        else { pigtype = DynamicObject::DynamicObjectType::kingpig; }
        // gives each pig a different position
        auto& pig = pigPtr.emplace_back(std::make_shared<Pig>(world, (500.0f + (i * 45.0f)), 400.0f, (15.0f + (i * 3)), (6 + (i * 2)), "../assets/Ang_Birds/Pigs.png", pigtype));
        pig->getBody()->GetUserData().pointer = 3 + i;
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
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    birdPtr.front()->dragging();
                }

            }

            if (event.type == sf::Event::MouseButtonReleased) {

                // once LMB is released, shoots bird depending on how much it was dragged.
                if (event.mouseButton.button == sf::Mouse::Left) {

                    birdPtr.front()->launch(catapult.getShotPos());
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                auto& currentBird = birdPtr.front();
                if (event.key.code == sf::Keyboard::L)
                {
                    // destroys the birds body and sprite in the vector so the next bird can get shot.
                    world.DestroyBody(birdPtr.front()->getBody());

                    birdPtr.pop_front();
                    

                    for (auto& pig : pigPtr) {
                        pig->resetDeletionMark();
                    }

                    contactlister.s_ptr.clear();
                    
                }

                    
            

                if (event.key.code == sf::Keyboard::Space) {
                    
                    std::vector<std::shared_ptr<Bird>> newBirds;
                    std::vector<std::shared_ptr<Bird>> Bomb;
                    if (currentBird->getBirdType() == DynamicObject::DynamicObjectType::yellowbird && !currentBird->hasUsedAbility()) {
                        currentBird->yellowBirdAbility(b2Vec2(5, 0));
                    }

                    if (currentBird->getBirdType() == DynamicObject::DynamicObjectType::bluebird) {
                        
                        auto newBirds = currentBird->blueBirdAbility(world);

                        for (auto& bird : newBirds) {
                            birdPtr.push_back(bird);
                        }

                        std::cout << "ability used" << std::endl;;
                    }

                    if (currentBird->getBirdType() == DynamicObject::DynamicObjectType::blackbird && !currentBird->hasUsedAbility()) {

                        auto Bomb = currentBird->blackBirdAbility(world);

                        currentBird->blackBirdAbility(world);

                        world.DestroyBody(birdPtr.front()->getBody());
                        
                        for (auto& bird : Bomb) {
                            birdPtr.push_back(bird);
                        }
                    }
                }
            }
                
        }

        if (birdPtr.front()->getDragging()) {

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

            // stops player dragging upwards
            if (dragVec.y < 0) {
                dragVec.y = 0;
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

        std::set<uintptr_t> s_p = contactlister.getPointer(); //Set of pointers to the pig ID's
        for (auto pigIt = pigPtr.begin(); pigIt != pigPtr.end() && !(*pigIt)->isMarkedForDeletion(); ) {


            uintptr_t currentPigID = (*pigIt)->getBody()->GetUserData().pointer;

            // Check if this pig's ID exists in the hit list
            if (s_p.find(currentPigID) != s_p.end()) { //Check through all of the container for specific Id's

                std::cout << currentPigID << " Destroyed" << std::endl;

                
                

                std::cout << "Pig has: " << (*pigIt)->getHealth() << "  Health" << std::endl;

                (*pigIt)->takeDamage(10);
                (*pigIt)->markForDeletion();

                if ((*pigIt)->checkIfPopped()) {
                    // Remove from Box2D world first
                    world.DestroyBody((*pigIt)->getBody()); //Remove the pig body from the world.

                    // Update the iterator by catching the return value of erase()
                    pigIt = pigPtr.erase(pigIt); //Erase the pig from the set.
                }

            }
            else {
                // Only increment if we didn't erase anything
                ++pigIt;
            }
        }

        catapult.update();
        plank.update();

        // goes through all pigs in the pointer and updates its physics using an iterator.
        for (auto it = pigPtr.begin(); it != pigPtr.end(); ++it) {
            (*it)->update();

        }

        // goes through all birds in the pointer and updates its physics using an iterator.
        for (auto it = birdPtr.begin(); it != birdPtr.end(); ++it) {
            (*it)->update();
        }

        for (auto it = Noninteractable.begin(); it != Noninteractable.end(); ++it) {
            (*it)->start();
        }


        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue


                                // draws the objects to the window.
 
        // goes through all pigs using an iterator and draws them to the window.
        for (auto it = pigPtr.begin(); it != pigPtr.end(); ++it) {
            (*it)->draw(window);
        }

        // goes through all birds using an iterator and draws them to the window.
        for (auto it = birdPtr.begin(); it != birdPtr.end(); ++it) {
            (*it)->draw(window);
        }

        for (auto it = Noninteractable.begin(); it != Noninteractable.end(); ++it) {
            (*it)->draw(window);
        }

        catapult.draw(window);
        plank.draw(window);
        window.display();
    }

    return 0;
}