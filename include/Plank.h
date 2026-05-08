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

	// passing Plank parameters into DynamicObject.h / DynamicObject.cpp for the creation of the Plank.
	Plank(b2World& world, float xPos, float yPos, float halfX, float halfY, std::string plankTexture) : DynamicObject(world, b2Vec2(xPos, yPos), plankTexture) {

		// gives default values to the parameters.
		this->xPos = xPos;
		this->yPos = yPos;

		// Rather than having an immovable wall, we can use the dynamic body type to create one that can have velocity etc.
		b2_bodyDef.position.Set(xPos / SCALE, yPos / SCALE);

		b2_polygonShape.SetAsBox(halfX / SCALE, halfY / SCALE);

		b2_plankFixture.shape = &b2_polygonShape;
		b2_plankFixture.density = 1.5f;   // Light wood
		b2_plankFixture.friction = 0.3f;

		b2_body->CreateFixture(&b2_plankFixture);

		sp_sprites.setScale(0.73, 1.0f);
	}

	// draw function from virtual class gameObject
	void draw(sf::RenderWindow& window) override {
		window.draw(sp_sprites);

	}

	// updates its position and rotation.
	void update() {
		sp_sprites.setPosition(b2_body->GetPosition().x * SCALE, b2_body->GetPosition().y * SCALE);
		sp_sprites.setRotation(b2_body->GetAngle() * (180.0f / PI) + 90.0f);
	}

};