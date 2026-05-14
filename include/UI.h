#pragma once
#include "DynamicObject.h"
#include "StaticObject.h"

class UI : public DynamicObject,  public StaticObject {
private:
	sf::Texture StartScreenTexture;
	sf::Texture endScreenTexture;
	sf::Font font;
	sf::Text text;

	bool isGameStarted = false;
	bool hasGameEnded = false;

public:
	UI() = default;
	~UI() = default;

	UI(b2World& world, sf::String Textfont, std::string StartScreenTexture, int size, b2Vec2 b2_pos) : DynamicObject(world, b2Vec2(), StartScreenTexture) {

		sp_sprites.setOrigin(te_Texture.getSize().x / 2.0f, te_Texture.getSize().y / 2.0f);
		sp_sprites.setScale(1.0f, 1.2f);

		sp_sprites.setPosition(400.0f, 300.0f);
		font.loadFromFile(Textfont);
		text.setFont(font);
		
		text.setCharacterSize(size);
		text.setPosition(b2_pos.x, b2_pos.y);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2.0f);
		
	}

	void setGameStarted(bool isgameStarted) {
		isGameStarted = isgameStarted;	
	}

	void setGameEnded(bool hasgameEnded) {
		hasGameEnded = hasgameEnded;
	}


	void getText(int Text) {
		text.setString("Pig: " + std::to_string(Text)); }

	void endText(std::string txt) {
		text.setString(txt);
	}


	bool getGamedEnded() const { return hasGameEnded; }

	bool getGameStarted() const { return isGameStarted; }

	void draw(sf::RenderWindow& window) override {
		window.draw(sp_sprites);
	}

	void render(sf::RenderWindow& window) {
		window.draw(text);

	}
};