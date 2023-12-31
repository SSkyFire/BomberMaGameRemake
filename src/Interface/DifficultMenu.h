#pragma once
#include <SFML/Graphics.hpp>
#include "GUI/Theme.hpp"
#include "GUI/GameGUI.hpp"
#include "../Music/GameMusic.h"
#include "../GameEngine.hpp"
#include "OptionsMenu.h"
#include "GameDisplayController.h"


class DifficultyMenu {
	GameGUI::Menu* menu;

	bool EsqPressed = false;

	enum ButtonActions {
		EASYLEVEL,
		NORMALLEVEL,
		HARDLEVEL,
        BACK,
		QUIT
	};

	sf::RectangleShape menuBackground;
	sf::RectangleShape menuBackgroundShadow;
	sf::RectangleShape menuBackgroundShadow1;
	sf::RectangleShape menuBackgroundShadow2;

	void createBackgroundMenu(sf::RenderWindow& window) {
		menu->setPosition(sf::Vector2f((int)window.getSize().x / 2 - (int)menu->getSize().x / 2, (int)window.getSize().y / 2 - (int)menu->getSize().y / 2));

		float menuBackgroundPadding = 50;
		menuBackground.setSize(sf::Vector2f(menu->getSize().x + 2 * menuBackgroundPadding, menu->getSize().y + 2 * menuBackgroundPadding));
		menuBackground.setPosition(menu->getPosition().x - menuBackgroundPadding, menu->getPosition().y - menuBackgroundPadding);
		menuBackground.setFillColor(sf::Color(255, 255, 153, 200));

		menuBackgroundShadow.setSize(sf::Vector2f(menu->getSize().x + 2 * menuBackgroundPadding - 4, menu->getSize().y + 2 * menuBackgroundPadding - 4));
		menuBackgroundShadow.setPosition(menu->getPosition().x - menuBackgroundPadding + 12, menu->getPosition().y - menuBackgroundPadding + 12);
		menuBackgroundShadow.setFillColor(sf::Color(15, 35, 35, 60));

		menuBackgroundShadow1.setSize(sf::Vector2f(menu->getSize().x + 2 * menuBackgroundPadding - 2, menu->getSize().y + 2 * menuBackgroundPadding - 2));
		menuBackgroundShadow1.setPosition(menu->getPosition().x - menuBackgroundPadding + 11, menu->getPosition().y - menuBackgroundPadding + 11);
		menuBackgroundShadow1.setFillColor(sf::Color(15, 35, 35, 20));

		menuBackgroundShadow2.setSize(sf::Vector2f(menu->getSize().x + 2 * menuBackgroundPadding, menu->getSize().y + 2 * menuBackgroundPadding));
		menuBackgroundShadow2.setPosition(menu->getPosition().x - menuBackgroundPadding + 10, menu->getPosition().y - menuBackgroundPadding + 10);
		menuBackgroundShadow2.setFillColor(sf::Color(15, 35, 35, 20));
	}

public:
	DifficultyMenu(sf::RenderWindow& window) {
		menu = new GameGUI::Menu(window);

		menu->addButton("                Facil               ", ButtonActions::EASYLEVEL);
		menu->addButton("                Normal                 ", ButtonActions::NORMALLEVEL);
		menu->addButton("                Dificil                ", ButtonActions::HARDLEVEL);
		menu->addButton("            Atras       ", ButtonActions::BACK);
		// menu->addButton("                    Salir                    ", ButtonActions::QUIT);

		createBackgroundMenu(window);
	}

private:
	void userActions(sf::Event& event, sf::RenderWindow*& window, GameDisplayController& gameDisplay, Game& game) {
		int id = menu->onEvent(event);
		switch (id) {
		case ButtonActions::EASYLEVEL:

            game.gameOptions.difLevel=1;
			gameDisplay.setGameState(GameDisplayController::GameState::LOADING);
			break;

		case ButtonActions::NORMALLEVEL:
            game.gameOptions.difLevel=1.5;
        	gameDisplay.setGameState(GameDisplayController::GameState::LOADING);
					
			break;
				
		case ButtonActions::HARDLEVEL:
            game.gameOptions.difLevel=2;
			//OptionsMenu::lastGameStateOptionsMenu = GameDisplayController::GameState::MULTIPLAYER_MENU;
			gameDisplay.setGameState(GameDisplayController::GameState::LOADING);
			break;
				
		case ButtonActions::BACK:
			gameDisplay.setGameState(GameDisplayController::GameState::MAIN_MENU);
			break;
				
		case ButtonActions::QUIT:
			window->close();
			break;
		}
	}

	void draw(sf::RenderWindow& window, GameDisplayController& gameDisplay) {
		window.draw(gameDisplay.backgroundBomberman);
		window.draw(gameDisplay.getSquaresBackground());

		window.draw(menuBackgroundShadow2);
		window.draw(menuBackgroundShadow1);
		window.draw(menuBackgroundShadow);
		window.draw(menuBackground);

		window.draw(*menu);
	}

public:
	void menuActions(GameDisplayController& gameDisplay, Game& game) {
		if (gameDisplay.pauseMenuReprocessDisplay) {
			gameDisplay.pauseMenuReprocessDisplay = false;
			createBackgroundMenu(*gameDisplay.getWindow());
		}
		draw(*gameDisplay.getWindow(), gameDisplay);

		// Manage window events and pass a callback to manage this menu buttons
		gameDisplay.manageGameInterface(gameDisplay, std::bind(&DifficultyMenu::userActions, this, std::placeholders::_1, std::ref(gameDisplay.getWindow()), std::ref(gameDisplay), std::ref(game)));
	}

	
};

