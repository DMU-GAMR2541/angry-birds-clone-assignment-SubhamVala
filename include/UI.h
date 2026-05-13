#pragma once
#include "DynamicObject.h"
#include "StaticObject.h"

class UI : public DynamicObject,  public StaticObject {
private:
	sf::Texture StartScreenTexture;

	bool isGameStarted = false;

public:
	UI() = default;
	~UI() = default;

	UI(b2World& world, std::string String, std::string StartScreenTexture) : DynamicObject(world, b2Vec2(), StartScreenTexture) {

		sp_sprites.setOrigin(te_Texture.getSize().x / 2.0f, te_Texture.getSize().y / 2.0f);

		sp_sprites.setPosition(400.0f, 300.0f);
	}

	void setGameStarted(bool isgameStarted) {
		isGameStarted = isgameStarted;	
	}

	bool getGameStarted() const { return isGameStarted; }

	void draw(sf::RenderWindow& window) override {
		window.draw(sp_sprites);
	}
};