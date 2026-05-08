#pragma once
#include <SFML/Graphics.hpp>

// pure abstract class 
// virtual class for draw, inherited classes must take.

class GameObject {

public:

	GameObject() = default;
	~GameObject() = default;

	virtual void draw(sf::RenderWindow& window) = 0;
};
