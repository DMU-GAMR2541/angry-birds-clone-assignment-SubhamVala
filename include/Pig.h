#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "DynamicObject.h"
#pragma once

class Pig : public DynamicObject, Enemy {

public:
	Pig() = default;

	Pig(b2World& world, float xPos, float yPos, float radius, std::string birdTexture) : DynamicObject(world, b2Vec2(xPos, yPos), birdTexture) {

		b2_circleShape.m_radius = radius / SCALE;
		b2_PigFixture.density = 1.0f;
		b2_PigFixture.restitution = 0.5f; // Bounciness

		b2_body->CreateFixture(&b2_PigFixture);
		sp_sprites.setScale(0.1, 0.1);

		


	}

	void draw(sf::RenderWindow& window) override {
		window.draw(sp_sprites);

	}

	void update() {
		sp_sprites.setPosition(b2_body->GetPosition().x * SCALE, b2_body->GetPosition().y * SCALE);
		sp_sprites.setRotation(b2_body->GetAngle() * (180.0f / PI));
	}
};