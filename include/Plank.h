#pragma once
#include "DynamicObject.h"

class Plank : public DynamicObject {
private:
	float xPos = 550.0f;
	float yPos = 450.0f;
	float halfX = 10.0f;
	float halfY = 60.0f;


public:
	Plank() = default;

	Plank(b2World& world, float xPos, float yPos, float halfX, float halfY) : DynamicObject(world, b2Vec2(xPos / SCALE, yPos / SCALE), "") {
		this->xPos = xPos;
		this->yPos = yPos;

		//Rather than having an immovable wall, we can use the dynamic body type to create one that can have velocity etc.
		b2_bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
		b2_bodyDef.type = b2_dynamicBody;

		b2_body = world.CreateBody(&b2_bodyDef);

		b2_plankBox.SetAsBox(halfX / SCALE, halfY / SCALE);

		b2_plankFixture.shape = &b2_plankBox;
		b2_plankFixture.density = 1.5f;   // Light wood
		b2_plankFixture.friction = 0.3f;

		b2_body->CreateFixture(&b2_plankFixture);

		rectangle.setSize(sf::Vector2(20.0f, 120.0f));
		rectangle.setOrigin(halfX, halfY);
		rectangle.setFillColor(sf::Color(139, 69, 19));
	}

	void draw(sf::RenderWindow& window) override {
		window.draw(rectangle);

	}

	void Update()
	{
		// Dynamic wall.
		rectangle.setPosition(b2_body->GetPosition().x * SCALE, b2_body->GetPosition().y * SCALE);
		rectangle.setRotation(b2_body->GetAngle() * (180.0f / PI));
	}

};