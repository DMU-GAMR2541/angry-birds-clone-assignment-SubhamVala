
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "DynamicObject.h"
#include "Bird.h"


DynamicObject::~DynamicObject()
{
}

DynamicObject::DynamicObject(b2World& b2_WorldPos, b2Vec2 b2_Pos, std::string str_sprite)
{
	b2_bodyDef.position.Set(b2_Pos.x / SCALE, b2_Pos.y / SCALE);
	

	b2_bodyDef.type = b2_dynamicBody;


	b2_body = b2_WorldPos.CreateBody(&b2_bodyDef);

	b2_ballFixture.shape = &b2_circleShape;



	if (!te_Texture.loadFromFile(str_sprite)) {
		return;
	}

	sp_sprites.setTexture(te_Texture);
	sp_sprites.setOrigin(te_Texture.getSize().x / 2.0f, te_Texture.getSize().y / 2.0f);
	sp_sprites.setPosition(b2_bodyDef.position.x * SCALE, b2_bodyDef.position.y * SCALE);
	sp_sprites.setScale(0.65, 0.65);
			

}




void DynamicObject::Render(sf::RenderWindow* sf_window)
{
}




void DynamicObject::Update(float gravity, b2Vec2 b2_impule, bool b_make)
{
	
}
