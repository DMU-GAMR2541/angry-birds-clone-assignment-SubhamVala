#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "DynamicObject.h"
#include "ContactListener.h"
#pragma once

class Pig : public DynamicObject, public Enemy, public ContactListener {
private:
	int health = 50;
	bool markedForDeletion = false;

public:
	Pig() = default;

	// passing Pig parameters into DynamicObject.h / DynamicObject.cpp for the creation of the pig.
	Pig(b2World& world, float xPos, float yPos, float radius, int health, std::string pigTexture, DynamicObjectType pigtype) : DynamicObject(world, b2Vec2(xPos, yPos), pigTexture), Enemy(health) {

		this->health = health;

		// creates the dynamic pig 

		switch (pigtype) {
			case DynamicObjectType::pig:
				b2_PigFixture.density = 1.0f;
				b2_PigFixture.restitution = 0.5f; // Bounciness
				sp_sprites.setTextureRect(sf::IntRect(53, 70, 47, 44));
				sp_sprites.setOrigin(47 / 2.0f, 44 / 2.0f);
				sp_sprites.setScale(1.0f, 1.0f);
				break;
			case DynamicObjectType::helmpig:
				b2_PigFixture.density = 1.1f;
				b2_PigFixture.restitution = 0.45f; // Bounciness
				sp_sprites.setTextureRect(sf::IntRect(53, 210, 93, 84));
				sp_sprites.setOrigin(93 / 2.0f, 84 / 2.0f);
				sp_sprites.setScale(0.6f, 0.6f);
				break;
			case DynamicObjectType::bigpig:
				b2_PigFixture.density = 1.3f;
				b2_PigFixture.restitution = 0.4f; // Bounciness
				sp_sprites.setTextureRect(sf::IntRect(64, 415, 110, 98));
				sp_sprites.setOrigin(110 / 2.0f, 98 / 2.0f);
				sp_sprites.setScale(0.5f, 0.5f);
				break;
			case DynamicObjectType::kingpig:
				b2_PigFixture.density = 1.5f;
				b2_PigFixture.restitution = 0.3f; // Bounciness
				sp_sprites.setTextureRect(sf::IntRect(47, 526, 126, 153));
				sp_sprites.setOrigin(126 / 2.0f, 153 / 2.0f);
				sp_sprites.setScale(0.47f, 0.47f);
				break;

		}

		b2_circleShape.m_radius = radius / SCALE;

		b2_body->CreateFixture(&b2_PigFixture);
		

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

	void markForDeletion() {
		markedForDeletion = true;
	}

	bool isMarkedForDeletion() const {
		return markedForDeletion;

	}

	void resetDeletionMark() {
		markedForDeletion = false;
	}
	
};