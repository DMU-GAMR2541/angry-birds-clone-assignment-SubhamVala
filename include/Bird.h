
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "DynamicObject.h"
#pragma once

class Bird : public DynamicObject {
private:
	float xPos = 100.0f;
	float yPos = 500.0f;
	float radius = 15.0f;
	float shotPower = 5.0f;
	bool isDragging = false;
	sf::Vector2f startPos;
	

public:

	Bird() = default;

	// passing bird parameters into DynamicObject.h / DynamicObject.cpp for the creation of the bird.
	Bird(b2World& world, float xPos, float yPos, float radius, float density, float restitution, float shotPower, std::string birdTexture) : DynamicObject(world, b2Vec2(xPos, yPos), birdTexture) {


		// gives default values to parameters
		this->xPos = xPos;
		this->yPos = yPos;
		this->radius = radius;
		this->shotPower = shotPower;
		//creates the start position using paramters.
		this->startPos = sf::Vector2f(xPos, yPos);


		//Creates a dynamic ball.

		b2_circleShape.m_radius = radius / SCALE;
		b2_ballFixture.density = density;
		b2_ballFixture.restitution = restitution; // Bounciness

		b2_body->CreateFixture(&b2_ballFixture);
		sp_sprites.setScale(0.045, 0.045);
	


	
	}

	// setter for dragging
	void setDragging(bool dragging) {
		isDragging = dragging;
	}

	// getter for dragging
	bool getDragging() { return isDragging; }

	// getter for start position
	sf::Vector2f getStartPos() { return startPos; }
	

	// draw function from virtual class gameObject
	void draw(sf::RenderWindow& window) override {
		window.draw(sp_sprites);

	}

	// updates its position and rotation since its a dynamic object.
	void update() {
		sp_sprites.setPosition(b2_body->GetPosition().x * SCALE, b2_body->GetPosition().y * SCALE);
		sp_sprites.setRotation(b2_body->GetAngle() * (180.0f / PI));
	}


	// stops bird from falling and rotating once dragging.
	void dragging() {

		isDragging = true;

		b2_body->SetGravityScale(0);


		b2_body->SetLinearVelocity(b2Vec2(0, 0));
		b2_body->SetAngularVelocity(0);



	}

	// calculates launch velocity using the targets position and start position. 
	// Resetting gravity once launched.
	void launch() {

		isDragging = false;

		b2_body->SetGravityScale(1.0f);

		sf::Vector2f targetPos{b2_body->GetPosition().x * SCALE, b2_body->GetPosition().y * SCALE };

		sf::Vector2f launchVector = (targetPos - startPos) / SCALE;

		b2Vec2 impulseMagnitude(-launchVector.x * shotPower, -launchVector.y * shotPower);

		b2_body->ApplyLinearImpulseToCenter(impulseMagnitude, true);
		
		std::cout << "Firing!!!!" << std::endl;
	}
		
};