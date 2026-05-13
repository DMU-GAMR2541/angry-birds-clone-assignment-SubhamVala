
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "StaticObject.h"

StaticObject::~StaticObject()
{
}

StaticObject::StaticObject(b2World& b2_WorldPos, b2Vec2 b2_Pos, b2Vec2 b2_Scale)
{
	// creates its position in world and adds the body and fixture using the parameters.
	b2_BodyDef.position.Set(b2_Pos.x / SCALE, b2_Pos.y / SCALE);

	b2_body = b2_WorldPos.CreateBody(&b2_BodyDef);

	b2_PolygonShape.SetAsBox(b2_Scale.x / SCALE, b2_Scale.y / SCALE);

	b2_body->CreateFixture(&b2_PolygonShape, 0.0f);


}

void StaticObject::Update() 
{


}

