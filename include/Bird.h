#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "DynamicObject.h"
#include "ContactListener.h"

class Bird : public DynamicObject, public ContactListener {
private:
	float xPos = 100.0f;
	float yPos = 500.0f;
	float radius = 15.0f;
	float shotPower = 5.0f;
	bool isDragging = false;
	bool abilityUsed = false;
	bool collided = false;
	bool launched = false;
	sf::Vector2f startPos;
	DynamicObjectType birdType;
	sf::Clock cTimer;
	float fTime = -1.0f;
	
	

public:

	Bird() = default;

	// passing bird parameters into DynamicObject.h / DynamicObject.cpp for the creation of the bird.
	Bird(b2World& world, float xPos, float yPos, float radius, float shotPower, std::string birdTexture, DynamicObjectType birdtype) 
		: DynamicObject(world, b2Vec2(xPos, yPos), birdTexture) {


		// gives default values to parameters
		this->xPos = xPos;
		this->yPos = yPos;
		this->radius = radius;
		this->shotPower = shotPower;
		//creates the start position using paramters.
		this->startPos = sf::Vector2f(xPos, yPos);
		this->birdType = birdtype;


		
		// creates different density and bounciness depending on which bird it is.

		switch(birdtype) {
			case DynamicObjectType::redbird:
				b2_ballFixture.density = 1.0f;
				b2_ballFixture.restitution = 0.5f; // Bounciness
				sp_sprites.setScale(0.045, 0.045);
				break;
			case DynamicObjectType::blackbird:
				b2_ballFixture.density = 1.4f;
				b2_ballFixture.restitution = 0.3f; // Bounciness
				sp_sprites.setScale(0.045, 0.045);
				break;
			case DynamicObjectType::yellowbird:
				b2_ballFixture.density = 0.85f;
				b2_ballFixture.restitution = 0.5f; // Bounciness
				sp_sprites.setScale(0.045, 0.045);
				break;
			case DynamicObjectType::bluebird:
				b2_ballFixture.density = 0.9f;
				b2_ballFixture.restitution = 0.5f; // Bounciness
				sp_sprites.setScale(0.025, 0.025);
				break;
			case DynamicObjectType::bombeffect:
				// scales the bombEffect.
				sp_sprites.setScale(1.3f, 1.3f);

		}

		b2_circleShape.m_radius = radius / SCALE;

		b2_body->CreateFixture(&b2_ballFixture);
	
	}

	// setter for dragging
	void setDragging(bool dragging) {
		isDragging = dragging;
	}

	// getter for dragging
	bool getDragging() const { return isDragging; }

	// getter for start position
	sf::Vector2f getStartPos() const { return startPos; }

	// getter for birdType
	DynamicObjectType getBirdType() const { return birdType; }

	//Getter for collision
	bool BirdDeletionStarted() const { return collided; }

	//Getter for if the bird is launched
	bool hasLaunched() const { return launched; }

	//setter for if an ability is used.
	void setUsedAbility(bool abilityused) {
		abilityUsed = abilityused;
	}
	
	// getter for if an ability is used
	bool hasUsedAbility() const { return abilityUsed; }

	// setter for marking a bird for deletion.
	void BirdMarkedforDeletion(float seconds) {

		if (!collided) {
			collided = true;
			fTime = seconds;
			cTimer.restart();
		}
	}

	// setter for how long till deletion
	void DestructionTime(float seconds) {
		fTime = seconds;
		cTimer.restart();
	}

	// setter for if timer is ready for deletion.
	bool shouldDelete() {
		if (fTime < 0) return false;
		
		return cTimer.getElapsedTime().asSeconds() >= fTime;
	}

	
	// function for the yellow birds ability.
	void yellowBirdAbility(b2Vec2 impulse) {
		b2_body->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), true);
		abilityUsed = true;
	}



	// updates its position and rotation since its a dynamic object.
	void update() {
		sp_sprites.setPosition(b2_body->GetPosition().x * SCALE, b2_body->GetPosition().y * SCALE);
		sp_sprites.setRotation(b2_body->GetAngle() * (180.0f / PI));
	}

	// draw function from virtual class gameObject
	void draw(sf::RenderWindow& window) override {
		window.draw(sp_sprites);

	}

	// stops bird from falling and rotating once dragging.
	void dragging() {

		isDragging = true;

		b2_body->SetGravityScale(0);

		b2_body->SetLinearVelocity(b2Vec2(0, 0));
		b2_body->SetAngularVelocity(0);

	}

	// calculates launch velocity using the targets position and start position. 
	// Resetting gravity once launched.
	void launch(sf::Vector2f shotPos) {

		abilityUsed = false;
		isDragging = false;
		launched = true;

		b2_body->SetGravityScale(1.0f);

		sf::Vector2f targetPos{b2_body->GetPosition().x * SCALE, b2_body->GetPosition().y * SCALE };

		sf::Vector2f launchVector = (targetPos - shotPos) / SCALE;

		b2Vec2 impulseMagnitude(-launchVector.x * shotPower, -launchVector.y * shotPower);

		b2_body->ApplyLinearImpulseToCenter(impulseMagnitude, true);
		
		std::cout << "Firing!!!!" << std::endl;
	}
		

	// function for the blues ability.
	// creates two clones with the same velocity above and below the original.
	std::vector<std::shared_ptr<Bird>> blueBirdAbility(b2World& world) {
		std::vector<std::shared_ptr<Bird>> newBirds;

		if (abilityUsed) return newBirds;
		abilityUsed = true;

		b2Vec2 vel = b2_body->GetLinearVelocity();

		if (vel.x == 0 && vel.y == 0) return newBirds;

		if (birdType == DynamicObjectType::bluebird) {
			float Pos[2] = { -2.5f, 2.5f };

			for (float offset : Pos) {
				float bx = b2_body->GetPosition().x * SCALE;
				float by = b2_body->GetPosition().y * SCALE;

				auto otherBirds = std::make_shared<Bird>(world, bx, by, radius, shotPower, "../assets/Ang_Birds/BlueBird.png", DynamicObjectType::bluebird);
				otherBirds->getBody()->GetUserData().pointer = 100;
				otherBirds->abilityUsed = true;
				otherBirds->launched = true;

				otherBirds->getBody()->SetLinearVelocity(b2Vec2(vel.x, vel.y + offset));

				newBirds.push_back(otherBirds);
			}
		}

		return newBirds;
	}


	// function for the bomb birds ability
	// gets the Bombeffect sprite body so when called removes bird and creates bomb effect.
	std::vector<std::shared_ptr<Bird>> blackBirdAbility(b2World& world, float DestuctionTime) {
		std::vector<std::shared_ptr<Bird>> Bomb;

		if (abilityUsed) return Bomb;
		abilityUsed = true;

		float bx = b2_body->GetPosition().x * SCALE;
		float by = b2_body->GetPosition().y * SCALE;
		auto BombEffect = std::make_shared<Bird>(world, bx, by, 50, shotPower, "../assets/Ang_Birds/BombEffect.png", DynamicObjectType::bombeffect);
		BombEffect->DestructionTime(DestuctionTime);
		BombEffect->getBody()->GetUserData().pointer = 100;
		abilityUsed = true;
		Bomb.push_back(BombEffect);

		return Bomb;

	}

};