
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

	
	

public:

	Bird() = default;

	Bird(b2World& world, float xPos, float yPos, float radius, float density, float restitution, std::string birdTexture) : DynamicObject(world, b2Vec2(xPos, yPos), birdTexture) {



		this->xPos = xPos;
		this->yPos = yPos;
		this->radius = radius;

		//Creates a dynamic ball.

		b2_circleShape.m_radius = radius / SCALE;
		b2_ballFixture.density = density;
		b2_ballFixture.restitution = restitution; // Bounciness

		b2_body->CreateFixture(&b2_ballFixture);

		sp_sprites.setScale(0.045, 0.045);
	


	
	}

	void draw(sf::RenderWindow& window) override {
		window.draw(sp_sprites);

	}

	void update() {


		sp_sprites.setPosition(b2_body->GetPosition().x * SCALE, b2_body->GetPosition().y * SCALE);
		sp_sprites.setRotation(b2_body->GetAngle() * (180.0f / PI));

	}

	void destroy() {
		
	}

	void launch() {

		// Reset position of the ball so that it can be fired again from its original poisition.
		b2_body->SetTransform(b2Vec2(100.0f / SCALE, 500.0f / SCALE), 0);
		b2_body->SetLinearVelocity(b2Vec2(0, 0));
		b2_body->SetAngularVelocity(0);

		// Apply impulse (X-axis, Y-axis) Negative Y is UP in Box2D because gravity is positive.
		b2_body->ApplyLinearImpulse(b2Vec2(5.0f, -5.0f), b2_body->GetWorldCenter(), true);



		std::cout << "Firing!!!!" << std::endl;
	}
		
};