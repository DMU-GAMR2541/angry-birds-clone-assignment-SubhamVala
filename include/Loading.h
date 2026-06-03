#pragma once
#include "DynamicObject.h"
#include "UI.h"
#include "SFML/System.hpp"

#include <iostream>
#include <thread>
#include <future>
#include <cstdlib>

class Loading : public DynamicObject {
private:
	sf::Font Font;
	sf::Text text;
	int WorkingTime;

public:

	Loading() = default;
	~Loading() = default;

	Loading(b2World& world, sf::String Textfont, int size, b2Vec2 b2_pos, int LoadingTime) : DynamicObject(world, b2Vec2(b2_pos.x, b2_pos.y), std::string()){

		this->WorkingTime = LoadingTime;

		Font.loadFromFile(Textfont);
		text.setFont(Font);
		
		text.setCharacterSize(size);
		text.setPosition(b2_pos.x, b2_pos.y);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2.0f);
		text.setString("Loading... ");

		std::thread m_assetThread(&Loading::setupPhysics, this, LoadingTime);

		if (m_assetThread.joinable()) {
			m_assetThread.join();
		}
	}


	void draw(sf::RenderWindow& window) override {
		window.draw(text);
	}

	void setupPhysics(int Time) {
		for (int i = 0; i < Time; i++) {
			std::cout << "Loading!!!:  " << i << std::endl;
			
		}

		//text.setString("Loading Complete!!!");
		sf::sleep(sf::milliseconds(Time));
	}
};