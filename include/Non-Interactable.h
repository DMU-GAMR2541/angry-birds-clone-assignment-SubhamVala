#pragma once
#include "StaticObject.h"

class Ground : public StaticObject {
private:

	float GroundXPos = 400.0f;
	float GroundYPos = 590.0f;
	float GroundWidth = 400.0f;
	float GroundHeight = 10.0f;


public:
	Ground() = default;

	Ground(b2World& world,float GroundXPos, float GroundYPos,float GroundWidth, float GroundHeight) :
		StaticObject(world, b2Vec2(GroundXPos, GroundYPos), b2Vec2(), b2Vec2(GroundWidth, GroundHeight), b2Vec2(), "") {

		this->GroundXPos = GroundXPos;
		this->GroundYPos = GroundYPos;
		this->GroundWidth = GroundWidth;
		this->GroundHeight = GroundHeight;

		GroundRectangle.setSize(sf::Vector2(800.0f, 20.0f));
		GroundRectangle.setOrigin(GroundWidth, GroundHeight);
		GroundRectangle.setFillColor(sf::Color(34, 139, 34));



	}

	void draw(sf::RenderWindow& window) override {
		window.draw(GroundRectangle);
	}
};


class Wall : public StaticObject {
private:

	float WallXPos = 750.0f;
	float WallYPos = 500.0f;
	float WallWidth = 10.0f;
	float WallHeight = 80.0f;

public:
	Wall() = default;

	Wall(b2World& world, float WallXPos, float WallYPos, float WallWidth, float WallHeight) : 
		StaticObject(world, b2Vec2(), b2Vec2(WallXPos, WallYPos), b2Vec2(), b2Vec2(WallWidth, WallHeight), "") {

		this->WallXPos = WallXPos;
		this->WallYPos = WallYPos;
		this->WallWidth = WallWidth;
		this->WallHeight = WallHeight;

		WallRectangle.setSize(sf::Vector2(20.0f, 160.0f));
		WallRectangle.setOrigin(WallWidth, WallHeight);
		WallRectangle.setFillColor(sf::Color::Red);



	}

	void draw(sf::RenderWindow& window) override {
		window.draw(WallRectangle);

	}
};