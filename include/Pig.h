#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "DynamicObject.h"
#include "ContactListener.h"
#pragma once

class Pig : public DynamicObject, public Enemy, public ContactListener {

public:
	Pig() = default;

	// passing Pig parameters into DynamicObject.h / DynamicObject.cpp for the creation of the pig.
	Pig(b2World& world, float xPos, float yPos, float radius, int health, std::string birdTexture) : DynamicObject(world, b2Vec2(xPos, yPos), birdTexture), Enemy(health) {

		// creates the dynamic pig 
		b2_circleShape.m_radius = radius / SCALE;
		b2_PigFixture.density = 1.0f;
		b2_PigFixture.restitution = 0.5f; // Bounciness

		b2_body->CreateFixture(&b2_PigFixture);
		sp_sprites.setScale(0.1, 0.1);

	}

	// function from virtual class GameObject
	void draw(sf::RenderWindow& window) override {
		window.draw(sp_sprites);

	}

	// updates its position and rotation since its a dynamic object.
	void update() {
		sp_sprites.setPosition(b2_body->GetPosition().x * SCALE, b2_body->GetPosition().y * SCALE);
		sp_sprites.setRotation(b2_body->GetAngle() * (180.0f / PI));
	}
};