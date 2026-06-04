#pragma once
#include "DynamicObject.h"
#include "UI.h"
#include "SFML/System.hpp"

#include <iostream>
#include <thread>
#include <future>
#include <cstdlib>
#include <chrono>
#include <mutex>

class Loading : public DynamicObject {
private:
	sf::Font Font;
	sf::Text text;
	int WorkingTime = 0;
	bool isPhysicsLoading = true;
	bool isAssetsLoading = true;
	int loadingPercent = 0;
	std::thread m_physicsThread;
	std::future<void> m_assetsFuture;
	std::mutex mtx;

public:

	Loading() = default;

	// joins the threads on destructor
	~Loading() {
		if (m_physicsThread.joinable()) {
			m_physicsThread.join();
			
		}

		if (m_assetsFuture.valid()) {
			m_assetsFuture.get();
		}
	}



	Loading(b2World& world, sf::String Textfont, int size, b2Vec2 b2_pos, int LoadingTime) : DynamicObject(world, b2Vec2(b2_pos.x, b2_pos.y), std::string()){

		this->WorkingTime = LoadingTime;

		// loads the font.
		Font.loadFromFile(Textfont);
		text.setFont(Font);
		
		// values for the text.
		text.setCharacterSize(size);
		text.setPosition(b2_pos.x, b2_pos.y);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2.0f);
		
		m_assetsFuture = std::async(std::launch::async, &Loading::setupAssets, this);
		m_physicsThread = std::thread(&Loading::setupPhysics, this);	
	}

	// draw function which will lock before doing the text, so threads dont intefere with each other,
	void draw(sf::RenderWindow& window) override {
		mtx.lock();
		text.setString("Loading... " + std::to_string(loadingPercent) + "%");
		// once loading is complete the text is gone and replaced with "press enter to play"
		if (!isPhysicsLoading && !isAssetsLoading) {
			text.setString(" ");
		}

		mtx.unlock();
		window.draw(text);
	}

	// thread to load physics
	void setupPhysics() {

		// as long as the physics is true, it will load.
		if (isPhysicsLoading) {
			// loads till it reaches 100%
			for (int i = 0; i < WorkingTime; i++) {
				std::cout << "Loading Physics... :  " << i << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(40));
				// locks so the other async thread cannot intefere.
				mtx.lock();
				loadingPercent = i;
				mtx.unlock();
			}
		}

		isPhysicsLoading = false;
	}
	
	// async thread to load assets.
	void setupAssets() {
		// as long as the assets is true, it loads.
		if (isAssetsLoading) {
			// loads till it reaches 100%
			for (int i = 0; i < WorkingTime; i++) {
				std::cout << "Loading Assets... " << i << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(55));
				// locks so other threads cant intefere.
				mtx.lock();
				loadingPercent = i;
				mtx.unlock();
			}
		}
		
		isAssetsLoading = false;
	}

	// used to add "press enter to start" once loading is finished
	bool isGameLoading() {
		if (isPhysicsLoading && isAssetsLoading) {
			return true;
		}
		else if (!isPhysicsLoading && !isAssetsLoading) {
			return false;
		}	
	}

};