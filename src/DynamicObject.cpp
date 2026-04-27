
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "DynamicObject.h"


DynamicObject::~DynamicObject()
{
}

DynamicObject::DynamicObject(b2World& b2_WorldPos, b2Vec2 b2_Pos, std::string str_sprite)
{
	b2_bodyDef.type = b2_dynamicBody;
	b2_bodyDef.position = b2_Pos;

	b2_body = b2_WorldPos.CreateBody(&b2_bodyDef);

	b2_ballFixture.shape = &b2_circleShape;
			


}




void DynamicObject::Render(sf::RenderWindow* sf_window)
{
}




void DynamicObject::Update(float gravity, b2Vec2 b2_impule, bool b_make)
{
	
}
