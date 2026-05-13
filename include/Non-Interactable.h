#pragma once
#include "StaticObject.h"

class NonInteractable : public StaticObject {
private:



public:
	NonInteractable() = default;

	// passing Ground parameters into StaticObject.h / StaticObject.cpp for the creation of the NonInteractables.
	NonInteractable(b2World& world,float xPos, float yPos,float Width, float Height, sf::Color color) :
		StaticObject(world, b2Vec2(xPos, yPos), b2Vec2(Width, Height)) {


		// creates the ground
		Rectangle.setSize(sf::Vector2(Width * 2, Height * 2));
		Rectangle.setOrigin(Width, Height);
		Rectangle.setFillColor(sf::Color(color));

	}

	// draw function from pure virtual class GameObject.h
	void draw(sf::RenderWindow& window) override {
		window.draw(Rectangle);
	}

	// gives it the start position.
	void start() {
		Rectangle.setPosition(b2_body->GetPosition().x * SCALE, b2_body->GetPosition().y * SCALE);
	}
};