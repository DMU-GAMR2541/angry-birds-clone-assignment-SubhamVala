#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

class StaticObject : virtual public GameObject{
public:

	const float SCALE = 30.0f;
	const float PI = 3.1415927;

	StaticObject() = default;
	~StaticObject();

	// creates parameters that will take in values from inherited classes.
	StaticObject(b2World& b2_WorldPos, b2Vec2 b2_GroundPos, b2Vec2 WallPos, b2Vec2 b2_GroundScale, b2Vec2 WallScale);

	// creates variables for the ground and wall.
	b2BodyDef b2_groundBodyDef;
	b2PolygonShape b2_groundBox;

	b2BodyDef b2_wallDef;
	b2PolygonShape b2_wallBox;


	// RectangleShape getter for both ground and wall.
	sf::RectangleShape& sf_groundVisual() { return GroundRectangle; }
	sf::RectangleShape& sf_WallVisual() { return WallRectangle; }


	void Render(sf::RenderWindow* sf_window);

	void Update();

protected:
	// body variables.
	b2Body* b2_groundBody;
	b2Body* b2_wallBody;
	sf::RectangleShape GroundRectangle;
	sf::RectangleShape WallRectangle;
};