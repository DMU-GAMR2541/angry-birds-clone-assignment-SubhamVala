#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

class StaticObject : public GameObject{
public:

	const float SCALE = 30.0f;
	const float PI = 3.1415927;

	StaticObject() = default;
	~StaticObject();

	StaticObject(b2World& b2_WorldPos, b2Vec2 b2_GroundPos, b2Vec2 WallPos, b2Vec2 b2_GroundScale, b2Vec2 WallScale, std::string str_sprite);


	b2BodyDef b2_groundBodyDef;
	b2PolygonShape b2_groundBox;

	b2BodyDef b2_wallDef;
	b2PolygonShape b2_wallBox;



	sf::RectangleShape& sf_groundVisual() { return Rectangle; }
	sf::RectangleShape& sf_WallVisual() { return Rectangle2; }


	void Render(sf::RenderWindow* sf_window);

protected:
	b2Body* b2_groundBody;
	b2Body* b2_wallBody;
	sf::RectangleShape Rectangle;
	sf::RectangleShape Rectangle2;
};