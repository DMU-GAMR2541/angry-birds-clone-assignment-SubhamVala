
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
	~Bird() = default;
	Bird(b2World& world, float xPos, float yPos, float radius) : DynamicObject(world, b2Vec2(xPos / SCALE, yPos / SCALE), "") {

		this->xPos = xPos;
		this->yPos = yPos;
		this->radius = radius;

		//Create a ball that is fired when space is pressed. We need to first have a dynamic ball to do it.

		//b2_bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
		//b2_bodyDef.type = b2_dynamicBody;

		//b2_body = world.CreateBody(&b2_bodyDef);


		b2_circleShape.m_radius = radius / SCALE;

		b2_ballFixture.shape = &b2_circleShape;
		b2_ballFixture.density = 1.0f;
		b2_ballFixture.restitution = 0.5f; // Bounciness

		b2_body->CreateFixture(&b2_ballFixture);
	
		circle.setOrigin(radius, radius);
		circle.setFillColor(sf::Color::Yellow);
		circle.setRadius(radius);



	}

	void draw(sf::RenderWindow& window) override {
		window.draw(circle);

	}

	void Update() {
		
		circle.setPosition(b2_body->GetPosition().x * SCALE, b2_body->GetPosition().y * SCALE);
		circle.setRotation(b2_body->GetAngle() * (180.0f / PI));
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