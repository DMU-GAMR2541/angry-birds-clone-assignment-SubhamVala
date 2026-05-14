#pragma once
#include "DynamicObject.h"
#include "StaticObject.h"

class UI : public DynamicObject,  public StaticObject {
private:
	sf::Texture StartScreenTexture;
	sf::Texture endScreenTexture;
	sf::Font font;

	bool isGameStarted = false;
	bool hasGameEnded = false;

public:
	UI() = default;
	~UI() = default;

	UI(b2World& world, std::string String, std::string StartScreenTexture) : DynamicObject(world, b2Vec2(), StartScreenTexture) {

		sp_sprites.setOrigin(te_Texture.getSize().x / 2.0f, te_Texture.getSize().y / 2.0f);
		sp_sprites.setScale(1.0f, 1.2f);

		sp_sprites.setPosition(400.0f, 300.0f);

	}

	void setGameStarted(bool isgameStarted) {
		isGameStarted = isgameStarted;	
	}

	void setGameEnded(bool hasgameEnded) {
		hasGameEnded = hasgameEnded;
	}

	bool getGamedEnded() const { return hasGameEnded; }

	bool getGameStarted() const { return isGameStarted; }

	void draw(sf::RenderWindow& window) override {
		window.draw(sp_sprites);
	}
};