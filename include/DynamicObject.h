#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <ctime>

class DynamicObject : public GameObject {

public:

	DynamicObject() = default;
	~DynamicObject();

	DynamicObject(b2World& b2_WorldPos, b2Vec2 b2_Pos, std::string str_sprite);

	const float SCALE = 30.0f;
	const float PI = 3.1415927;

	b2Vec2 b2_pos;
	b2BodyDef b2_bodyDef;

	b2PolygonShape b2_plankBox;
	b2CircleShape b2_circleShape;

	b2FixtureDef b2_ballFixture;
	b2FixtureDef b2_PigFixture;
	b2FixtureDef b2_plankFixture;

	sf::Sprite sp_sprites;
	sf::Texture te_Texture;


	bool isCollided = false;
	bool isDamaged = false;

	void Render(sf::RenderWindow* sf_window);

	void Update(float gravity, b2Vec2 b2_impule, bool b_make);

	sf::CircleShape& sf_ballVisual() { return circle; }

	sf::RectangleShape& sf_plankVisual() { return rectangle; }

	b2Body* getBody() { return b2_body; }

protected:

	b2FixtureDef b2_fixtureDef;
	b2Body* b2_body;
	sf::CircleShape circle;
	sf::RectangleShape rectangle;
	

};

