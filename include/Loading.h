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

		Font.loadFromFile(Textfont);
		text.setFont(Font);
		
		text.setCharacterSize(size);
		text.setPosition(b2_pos.x, b2_pos.y);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2.0f);
		
		m_assetsFuture = std::async(std::launch::async, &Loading::setupAssets, this);
		m_physicsThread = std::thread(&Loading::setupPhysics, this);	
	}

	void draw(sf::RenderWindow& window) override {
		mtx.lock();
		text.setString("Loading... " + std::to_string(loadingPercent) + "%");
		if (!isPhysicsLoading && !isAssetsLoading) {
			text.setString(" ");
		}

		mtx.unlock();
		window.draw(text);
	}

	void setupPhysics() {

		if (isPhysicsLoading) {
			for (int i = 0; i < WorkingTime; i++) {
				std::cout << "Loading Physics... :  " << i << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				mtx.lock();
				loadingPercent = i;
				mtx.unlock();
			}
		}

		isPhysicsLoading = false;
	}

	void setupAssets() {
		if (isAssetsLoading) {
			for (int i = 0; i < WorkingTime; i++) {
				std::cout << "Loading Assets... " << i << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(65));
				mtx.lock();
				loadingPercent = i;
				mtx.unlock();
			}
		}
		
		isAssetsLoading = false;
	}

	bool isGameLoading() {
		if (isPhysicsLoading && isAssetsLoading) {
			return true;
		}
		else if (!isPhysicsLoading && !isAssetsLoading) {
			return false;
		}	
	}

};