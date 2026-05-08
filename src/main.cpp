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
    Catapult catapult(world, 150.0f, 520.0f, 10.0f, 60.0f, "../assets/Ang_Birds/Catapult_1.png");
    Plank plank(world, 500.0f, 550.0f, 10.0f, 60.0f, "../assets/Ang_Birds/Plank.png");
    Wall wall(world, 750.0f, 500.0f, 10.0f, 80.0f);
    Ground ground(world, 400.0f, 590.0f, 400.0f, 10.0f);

    // creates the STL sequence containers.
    std::vector<std::shared_ptr<Pig>> pigPtr;
    std::list<std::shared_ptr<Bird>> birdPtr;


    // stores the different bird types into a vector
    std::vector<std::string> birdTextures = { "../assets/Ang_Birds/BlueBird.png", "../assets/Ang_Birds/MainBird.png",  "../assets/Ang_Birds/YellowBird.png", "../assets/Ang_Birds/BlackBird.png" };
    
   

    // adds the pigs into the shared_pointer vector using a for loop.
    for (int i = 0; i < 3; i++) {

        // gives each pig a different position
        pigPtr.emplace_back(std::make_shared<Pig>(world, (500.0f + (i * 40.0f)), 400.0f, 15.0f, 5.0f, "../assets/Ang_Birds/Pig.png"));
    }

    // adds the birds into the shared_pointer vector using a for loop.
    for (int i = 0; i < 4; i++) {

        // gives the birds, different positions, bounciness, speed and textures.
        birdPtr.push_back(std::make_shared<Bird>(world, 100.0f + (i * -20.0f), 500.0f, 15.0f, (1.0f + (i * 0.05)), (0.5f + (i * -0.05)), 5.0f, birdTextures[i]));
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

                if (event.key.code == sf::Keyboard::L)
                {
                    // destroys the birds body and sprite in the vector so the next bird can get shot.
                    auto& currentBird = birdPtr.front();
                    world.DestroyBody(birdPtr.front()->getBody());
                    birdPtr.pop_front();
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

        


        // Update Physics
        world.Step(1.0f / 60.0f, 8, 3);

        catapult.update();
        ground.start();
        wall.start();
        plank.update();

        // goes through all pigs in the pointer and updates its physics using an iterator.
        for (auto it = pigPtr.begin(); it != pigPtr.end(); ++it) {
            auto& pig = *it;
            pig->update();

        }

        // goes through all birds in the pointer and updates its physics using an iterator.
        for (auto it = birdPtr.begin(); it != birdPtr.end(); ++it) {
            auto& bird = *it;
            bird->update();
        }

        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue


                                // draws the objects to the window.
 
        // goes through all pigs using an iterator and draws them to the window.
        for (auto it = pigPtr.begin(); it != pigPtr.end(); ++it) {
            auto& pig = *it;
            pig->draw(window);
        }

        // goes through all birds using an iterator and draws them to the window.
        for (auto it = birdPtr.begin(); it != birdPtr.end(); ++it) {
            auto& bird = *it;
            bird->draw(window);
        }


        catapult.draw(window);
        plank.draw(window);
        ground.draw(window);
        wall.draw(window);
   


        window.display();
    }

    return 0;
}