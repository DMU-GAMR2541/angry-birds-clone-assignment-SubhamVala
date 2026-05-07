#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "DynamicObject.h"
#include "StaticObject.h"
#include "Bird.h"
#include "Plank.h"
#include "Non-Interactable.h"
#include <vector>
#include <list>
#include "Pig.h"

#include <iostream>

int main() {


    // --- 1. WINDOW SETUP ---
    sf::RenderWindow window(sf::VideoMode(800, 600), "Annoyed_Flocks");
    window.setFramerateLimit(60);

    //Box2D works in meters. SFML works in pixels.
    const float SCALE = 30.0f;

    //Can set a definition for PI.
    const float PI = 3.1415927;
    bool isDestroyed = false;

    //setup world.
    
    b2Vec2 b2_gravity(0.0f, 9.8f); // Earth-like gravity
    b2World world(b2_gravity);
    
    // Inherited classes, setting parameter values.

    Bird bird(world, 100.0f, 500.0f, 15.0f, "../assets/Ang_Birds/MainBird.png");
    //Pig pig(world, 500.0f, 420.0f, 15.0f, "../assets/Ang_Birds/Pig.png");
    Plank plank(world, 500.0f, 550.0f, 10.0f, 60.0f, "../assets/Ang_Birds/Plank.png");
    Wall wall(world, 750.0f, 500.0f, 10.0f, 80.0f);
    Ground ground(world, 400.0f, 590.0f, 400.0f, 10.0f);

    std::vector<std::shared_ptr<Pig>> pigPtr;


    std::list<std::shared_ptr<Bird>> birdPtr;
    //std::list<Bird> currentBird;


    for (int i = 0; i < 3; i++) {
        pigPtr.emplace_back(std::make_shared<Pig>(world, (500.0f + (i * 40.0f)), 400.0f, 15.0f, "../assets/Ang_Birds/Pig.png"));
    }

    for (int i = 0; i < 3; i++) {
        birdPtr.push_back(std::make_shared<Bird>(world, 100.0f + (i * -20.0f), 500.0f, 15.0f, "../assets/Ang_Birds/MainBird.png"));
    }


    // --- 7. MAIN LOOP ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            // INPUT HANDLING: Press SPACE to launch

            if (event.type == sf::Event::KeyPressed) {

                auto &currentBird = birdPtr.front();


                if (event.key.code == sf::Keyboard::Space) {
                    
                    std::vector<Pig>::iterator pigIt;
                    for (auto it = birdPtr.begin(); it != birdPtr.end(); ++it) {
                        auto& bird = *it;
                        
                        currentBird->launch();
                        
                    }
                   


                }

                if (event.key.code == sf::Keyboard::L ) 
                {
                    
                    //birdPtr.erase(birdPtr.begin());
                    world.DestroyBody(birdPtr.front()->getBody());
                    birdPtr.pop_front();
                    isDestroyed = true;

                }
                 
            }
        }

        // Update Physics
        world.Step(1.0f / 60.0f, 8, 3);

        ground.update();
        wall.update();
        bird.update();
        plank.update();

        // goes through all pigs in the pointer and updates its physics
        for (auto it = pigPtr.begin(); it != pigPtr.end(); ++it) {
            auto& pig = *it;
            pig->update();

        }

        for (auto it = birdPtr.begin(); it != birdPtr.end(); ++it) {
            auto& bird = *it;
            bird->update();

            if (isDestroyed == true) {
                break;
            }
        }

        
        
           

        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue

        //window.draw(sf_groundVisual);
        //window.draw(sf_wallVisual);

        // goes through all pigs in the pointer and draws them.
        for (auto it = pigPtr.begin(); it != pigPtr.end(); ++it) {
            auto& pig = *it;
            pig->draw(window);
        }

        for (auto it = birdPtr.begin(); it != birdPtr.end(); ++it) {
            auto& bird = *it;
            bird->draw(window);
        }

        plank.draw(window);
        //bird.draw(window);
        ground.draw(window);
        wall.draw(window);
        window.display();
    }

    return 0;
}