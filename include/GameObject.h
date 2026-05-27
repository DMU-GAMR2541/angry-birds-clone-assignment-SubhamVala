#pragma once
#include <SFML/Graphics.hpp>

// pure abstract class 
// virtual class for draw, inherited classes must take.

class GameObject {

public:

	GameObject() = default;
	virtual ~GameObject() {
		std::cout << "GameObject.h, deconstructor called." << std::endl;
	}

	virtual void draw(sf::RenderWindow& window) = 0;
};
