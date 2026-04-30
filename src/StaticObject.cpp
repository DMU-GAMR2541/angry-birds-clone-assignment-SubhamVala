
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "StaticObject.h"

StaticObject::~StaticObject()
{
}

StaticObject::StaticObject(b2World& b2_WorldPos, b2Vec2 b2_GroundPos, b2Vec2 b2_WallPos, b2Vec2 b2_GroundScale, b2Vec2 WallScale, std::string str_sprite)
{

	b2_groundBodyDef.position.Set(b2_GroundPos.x / SCALE, b2_GroundPos.y / SCALE);
	b2_wallDef.position.Set(b2_WallPos.x / SCALE, b2_WallPos.y / SCALE);

	b2_groundBody = b2_WorldPos.CreateBody(&b2_groundBodyDef);
	b2_wallBody = b2_WorldPos.CreateBody(&b2_wallDef);

	b2_groundBox.SetAsBox(b2_GroundScale.x / SCALE, b2_GroundScale.y / SCALE);
	b2_wallBox.SetAsBox(WallScale.x / SCALE, WallScale.y / SCALE);

	b2_groundBody->CreateFixture(&b2_groundBox, 0.0f);
	b2_wallBody->CreateFixture(&b2_wallBox, 0.0f);


}

void StaticObject::Update() 
{


}

