#pragma once
#include <SFML/Graphics.hpp>
#include "GUI/Theme.hpp"
#include "GUI/GameGUI.hpp"
#include "../Music/GameMusic.h"
#include "../GameEngine.hpp"
#include "OptionsMenu.h"
#include "GameDisplayController.h"


class MultiplayerMenu {
	GameGUI::Menu* menu;

	bool EsqPressed = false;

	GameGUI::Slider* mapSlider;
	GameGUI::Label* mapText;
	const int mapQuantum = 50;
	int map = 1;

	GameGUI::Slider* livesSlider;
	GameGUI::Label* livesText;
	const int livesQuantum = 11;
	int lives = 3;

	GameGUI::Slider* sizeMapSlider;
	GameGUI::Label* sizeMapText;
	const int sizeMapQuantum = 50;
	int sizeMAp = 2;

	GameGUI::Slider* percentageBrickWallsSlider;
	GameGUI::Label* percentageBrickWallsText;
	const int percentageBrickWallsQuantum = 1;
	int percentageBrickWalls = 66;

	GameGUI::Slider* startingAbilitySlider;
	GameGUI::Label* startingAbilityText;
	const int startingAbilityQuantum = 25;
	ActionsAvalible startingAbility = NONE_ACTION;

	GameGUI::Slider* difficultyIASlider;
	GameGUI::Label* difficultyIAText;
	const int difficultyIAQuantum = 50;
	int difficultyLevel = 1;

	// Bombs
	GameGUI::Slider* numStartingBombsSlider;
	GameGUI::Label* numStartingBombsText;
	const int numStartingBombsQuantum = 11;
	int numStartingBombs = 1;

	// Fire
	GameGUI::Slider* numStartingFireSlider;
	GameGUI::Label* numStartingFireText;
	const int numStartingFireQuantum = 11;
	int numStartingFire = 1;

	// Speed
	GameGUI::Slider* numStartingSpeedSlider;
	GameGUI::Label* numStartingSpeedText;
	const int numStartingSpeedQuantum = 11;
	int numStartingSpeed = 1;

	// Objects per box
	GameGUI::Slider* percentageObjectsPerBrickWallSlider;
	GameGUI::Label* percentageObjectsPerBrickWallText;
	const int percentageObjectsPerBrickWallQuantum = 1;
	int percentageObjectsPerBrickWall = 60;

	// Time
	GameGUI::Slider* totalTimeSlider;
	GameGUI::Label* totalTimeText;
	const int totalTimeQuantum = 11;
	int totalTime = 300;

	enum ButtonActions {
		//NUmJUGADORES
		TWOPLAYERS,
		THREEPLAYERS,
		FOURPLAYERS,

		//TIPO DE JUEGO
		ALLVSALL,
		TEAM,

		//VERSUS
		//Dos jugadores
		//Dos jugadores
		PLVSIA,
		PLVSPL,
		//Tres jugadores
		PL12IA,
		PL21IA,
		//Cuatro jugadores
		PL13IA,
		PL22IA,

		//TEAM

		//Tres jugadores
		PL1VS2IA,
		PLVSPLIA,
		PL2VS1IA,
		//Cuatro jugadores
		PL1VS3IA,
		PLVSPL2IA,
		PL2VS2IA,
		PLIAVSPLIA,
		//Maps
		
		MAP,
		MAPSIZE,
		LIVES,
		TIME,
		IA_DIFFICULTY,

		BOMBS,
		SPEED,
		FIRE,
		ABILITY,
		PERCENTAGE_BRICK_WALL,
		PERCENTAGE_OBJECTS_IN_BRICK_WALL,

		ADVANCED_OPTIONS,
		BACK_FROM_ADVANCED_OPTIONS,

		CONTINUE,
		BACK,
		QUIT
	};

	enum MenuState {
		MAIN = 1,
		NUM_PLAYERS_SEL = 2,
		TYPE_OF_GAME = 3,
		PICK_MAP_ALL_VS_ALL = 4,
		PICK_MAP_TEAMS = 5
	};

	sf::RectangleShape menuBackground;
	sf::RectangleShape menuBackgroundShadow;
	sf::RectangleShape menuBackgroundShadow1;
	sf::RectangleShape menuBackgroundShadow2;
	MultiplayerMenu::MenuState previousMenu;
	static GameDisplayController::GameState lastGameStateOptionsMenu;

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
	MultiplayerMenu(sf::RenderWindow& window, GameDisplayController& gameDisplay) {
		previousMenu = MenuState::MAIN;
		createNumPlaySelection(window, gameDisplay);
	}

private:
	void fillPlayersAndTeamsArray(Game& game, int player1, int player2, int player3, int player4, int numTeams) {
		game.gameOptions.playersAndTeams[0] = player1;
		game.gameOptions.playersAndTeams[1] = player2;
		game.gameOptions.playersAndTeams[2] = player3;
		game.gameOptions.playersAndTeams[3] = player4;
		game.gameOptions.numTeams = numTeams;
	}

	void userActions(sf::Event& event, sf::RenderWindow*& window, GameDisplayController& gameDisplay, Game& game) {
		int id = menu->onEvent(event);
		switch (id) {
		case ButtonActions::TWOPLAYERS:
			game.gameOptions.numPlayers = 2;
			previousMenu = MenuState::NUM_PLAYERS_SEL;
			createAllVSAllMenu(*window, gameDisplay, game.gameOptions.numPlayers);
			break;

		case ButtonActions::THREEPLAYERS:

			game.gameOptions.numPlayers = 3;
			previousMenu = MenuState::NUM_PLAYERS_SEL;
			createGameTypeMenu(*window, gameDisplay);

			break;

		case ButtonActions::FOURPLAYERS:

			game.gameOptions.numPlayers = 4;
			previousMenu = MenuState::NUM_PLAYERS_SEL;
			//OptionsMenu::lastGameStateOptionsMenu = GameDisplayController::GameState::MULTIPLAYER_MENU;
			createGameTypeMenu(*window, gameDisplay);
			break;

		case ButtonActions::ALLVSALL:
			previousMenu = MenuState::TYPE_OF_GAME;
			createAllVSAllMenu(*window, gameDisplay, game.gameOptions.numPlayers);
			fillPlayersAndTeamsArray(game, 0, 1, 2, 3, 0);
			break;

		case ButtonActions::TEAM:
			previousMenu = MenuState::TYPE_OF_GAME;
			createTeamVSTeamMenu(*window, gameDisplay, game.gameOptions.numPlayers);
			break;

		case ButtonActions::PLVSIA:
			game.gameOptions.numPlayers = 1;
			game.gameOptions.numIAPlayers = 1;
			fillPlayersAndTeamsArray(game, 0, 1, 2, 3, 0);
			previousMenu = MenuState::PICK_MAP_ALL_VS_ALL;
			pickMap(*window, gameDisplay);
			break;

		case ButtonActions::PLVSPL:
			game.gameOptions.numPlayers = 2;
			game.gameOptions.numIAPlayers = 0;
			fillPlayersAndTeamsArray(game, 0, 1, 2, 3, 0);
			previousMenu = MenuState::PICK_MAP_ALL_VS_ALL;
			pickMap(*window, gameDisplay);

			break;

		case ButtonActions::PL12IA:
			game.gameOptions.numPlayers = 1;
			game.gameOptions.numIAPlayers = 2;
			fillPlayersAndTeamsArray(game, 0, 1, 2, 3, 3);
			previousMenu = MenuState::PICK_MAP_ALL_VS_ALL;
			pickMap(*window, gameDisplay);
			break;

		case ButtonActions::PL21IA:
			game.gameOptions.numPlayers = 2;
			game.gameOptions.numIAPlayers = 1;
			fillPlayersAndTeamsArray(game, 0, 1, 2, 3, 3);
			previousMenu = MenuState::PICK_MAP_ALL_VS_ALL;
			pickMap(*window, gameDisplay);
			break;

		case ButtonActions::PL13IA:
			game.gameOptions.numPlayers = 1;
			game.gameOptions.numIAPlayers = 3;
			previousMenu = MenuState::PICK_MAP_ALL_VS_ALL;
			fillPlayersAndTeamsArray(game, 0, 1, 2, 3, 4);
			pickMap(*window, gameDisplay);
			break;
		case ButtonActions::PL22IA:
			game.gameOptions.numPlayers = 2;
			game.gameOptions.numIAPlayers = 2;
			fillPlayersAndTeamsArray(game, 0, 1, 2, 3, 4);
			previousMenu = MenuState::PICK_MAP_ALL_VS_ALL;
			pickMap(*window, gameDisplay);
			break;


		case ButtonActions::PL1VS2IA:
			game.gameOptions.numPlayers = 1;
			game.gameOptions.numIAPlayers = 2;
			previousMenu = MenuState::PICK_MAP_TEAMS;
			pickMap(*window, gameDisplay);
			fillPlayersAndTeamsArray(game, 0, 1, 1, 1, 2);
			break;

		case ButtonActions::PLVSPLIA:
			game.gameOptions.numPlayers = 2;
			game.gameOptions.numIAPlayers = 1;
			previousMenu = MenuState::PICK_MAP_TEAMS;
			pickMap(*window, gameDisplay);
			fillPlayersAndTeamsArray(game, 0, 1, 1, 1, 2);
			break;

		case ButtonActions::PL2VS1IA:
			game.gameOptions.numPlayers = 2;
			game.gameOptions.numIAPlayers = 1;
			previousMenu = MenuState::PICK_MAP_TEAMS;
			pickMap(*window, gameDisplay);
			fillPlayersAndTeamsArray(game, 0, 0, 1, 1, 2);
			break;

			//4 players

		case ButtonActions::PL1VS3IA:
			game.gameOptions.numPlayers = 1;
			game.gameOptions.numIAPlayers = 3;
			previousMenu = MenuState::PICK_MAP_TEAMS;
			pickMap(*window, gameDisplay);
			fillPlayersAndTeamsArray(game, 0, 1, 1, 1, 2);
			break;
		case ButtonActions::PLVSPL2IA:
			game.gameOptions.numPlayers = 2;
			game.gameOptions.numIAPlayers = 1;
			previousMenu = MenuState::PICK_MAP_TEAMS;
			pickMap(*window, gameDisplay);
			fillPlayersAndTeamsArray(game, 0, 1, 1, 1, 2);
			break;

		case ButtonActions::PL2VS2IA:
			game.gameOptions.numPlayers = 2;
			game.gameOptions.numIAPlayers = 2;
			previousMenu = MenuState::PICK_MAP_TEAMS;
			pickMap(*window, gameDisplay);
			fillPlayersAndTeamsArray(game, 0, 0, 1, 1, 2);
			break;
		case ButtonActions::PLIAVSPLIA:
			game.gameOptions.numPlayers = 2;
			game.gameOptions.numIAPlayers = 2;
			previousMenu = MenuState::PICK_MAP_TEAMS;
			pickMap(*window, gameDisplay);
			fillPlayersAndTeamsArray(game, 0, 1, 0, 1, 2);
			break;

		case ButtonActions::CONTINUE:
			previousMenu = MenuState::MAIN;
			createNumPlaySelection(*window, gameDisplay);
			gameDisplay.setGameState(GameDisplayController::GameState::PICK_COLOR);
			gameDisplay.notifyChangeDisplay();

			// Pass the settings
			game.gameOptions.selectedStage = map;
			game.gameOptions.percentageOfWalls = percentageBrickWalls;
			game.gameOptions.startingLives = lives;
			game.gameOptions.selectedSizeStage = sizeMAp;
			game.gameOptions.startingAbility = startingAbility;
			game.gameOptions.IADifficulty = difficultyLevel;

			game.gameOptions.startingBombs = numStartingBombs;
			game.gameOptions.startingFire = numStartingFire;
			game.gameOptions.startingSpeed = numStartingSpeed;
			game.gameOptions.totalTime = totalTime;
			game.gameOptions.percentageObjectsFromWalls = percentageObjectsPerBrickWall;

			break;

		case ButtonActions::MAP:
			map = mapSlider->getValue() / mapQuantum;
			mapText->setText(mapToString(map), false);
			break;

		case ButtonActions::MAPSIZE:
			sizeMAp = sizeMapSlider->getValue() / sizeMapQuantum;
			sizeMapText->setText(mapSizeToString(sizeMAp), false);
			break;

		case ButtonActions::ABILITY:
			startingAbility = abilityToAbility(startingAbilitySlider->getValue() / startingAbilityQuantum);
			startingAbilityText->setText(abilityToString(startingAbilitySlider->getValue() / startingAbilityQuantum), false);
			break;

		case ButtonActions::LIVES:
			lives = livesSlider->getValue() / livesQuantum + 1;
			livesText->setText(to_string(lives), false);
			break;
		
		case ButtonActions::TIME:
			totalTime = totalTimeSlider->getValue() / totalTimeQuantum * 30 + 30;
			totalTimeText->setText(getTimeString(totalTime), false);
			break;

		case ButtonActions::BOMBS:
			numStartingBombs = numStartingBombsSlider->getValue() / numStartingBombsQuantum + 1;
			numStartingBombsText->setText(to_string(numStartingBombs), false);
			break;

		case ButtonActions::SPEED:
			numStartingSpeed = numStartingSpeedSlider->getValue() / numStartingSpeedQuantum + 1;
			numStartingSpeedText->setText(to_string(numStartingSpeed), false);
			break;

		case ButtonActions::FIRE:
			numStartingFire = numStartingFireSlider->getValue() / numStartingFireQuantum + 1;
			numStartingFireText->setText(to_string(numStartingFire), false);
			break;

		case ButtonActions::PERCENTAGE_BRICK_WALL:
			percentageBrickWalls = percentageBrickWallsSlider->getValue() / percentageBrickWallsQuantum;
			percentageBrickWallsText->setText(to_string(percentageBrickWalls), false);
			break;

		case ButtonActions::PERCENTAGE_OBJECTS_IN_BRICK_WALL:
			percentageObjectsPerBrickWall = percentageObjectsPerBrickWallSlider->getValue() / percentageObjectsPerBrickWallQuantum;
			percentageObjectsPerBrickWallText->setText(to_string(percentageObjectsPerBrickWall), false);
			break;

		case ButtonActions::IA_DIFFICULTY:
			difficultyLevel = difficultyIASlider->getValue() / difficultyIAQuantum;
			difficultyIAText->setText(difficultyIAToString(difficultyLevel), false);
			break;



		/*case ButtonActions::MAP_2:
			previousMenu = MenuState::MAIN;
			createNumPlaySelection(*window, gameDisplay);
			gameDisplay.setGameState(GameDisplayController::GameState::PICK_COLOR);
			gameDisplay.notifyChangeDisplay();
			game.gameOptions.selectedStage = 2;
			break;


		case ButtonActions::MAP_3:
			previousMenu = MenuState::MAIN;
			createNumPlaySelection(*window, gameDisplay);
			gameDisplay.setGameState(GameDisplayController::GameState::PICK_COLOR);
			gameDisplay.notifyChangeDisplay();
			game.gameOptions.selectedStage = 3;
			break;*/


		case ButtonActions::ADVANCED_OPTIONS:
			advancedOptions(*window, gameDisplay);
			break;
		case ButtonActions::BACK_FROM_ADVANCED_OPTIONS:
			pickMap(*window, gameDisplay);
			break;
		case ButtonActions::BACK:
			switch (previousMenu) {
			case MAIN:
				gameDisplay.setGameState(GameDisplayController::GameState::MAIN_MENU);
				break;

			case NUM_PLAYERS_SEL:
				previousMenu = MenuState::MAIN;
				createNumPlaySelection(*window, gameDisplay);
				break;

			case TYPE_OF_GAME:
				previousMenu = MenuState::NUM_PLAYERS_SEL;
				createGameTypeMenu(*window, gameDisplay);
				break;

			case PICK_MAP_ALL_VS_ALL:
				previousMenu = MenuState::TYPE_OF_GAME;
				createAllVSAllMenu(*window, gameDisplay, game.gameOptions.numPlayers + game.gameOptions.numIAPlayers);
				break;

			case PICK_MAP_TEAMS:
				previousMenu = MenuState::TYPE_OF_GAME;
				createTeamVSTeamMenu(*window, gameDisplay, game.gameOptions.numPlayers + game.gameOptions.numIAPlayers);
				break;

			default:
				break;
			}
			break;


		case ButtonActions::QUIT:
			window->close();
			break;
		}
		if (id != -1) {
			GameSounds::buttonPress();
		}
	}

	void createNumPlaySelection(sf::RenderWindow& window, GameDisplayController& gameDisplay) {
		menu = new GameGUI::Menu(window);
		GameGUI::HorizontalBoxLayout* hboxQuit = menu->addHorizontalBoxLayout();


		menu->addButton("                2 jugadores                 ", ButtonActions::TWOPLAYERS);
		menu->addButton("                3 jugadores                 ", ButtonActions::THREEPLAYERS);
		menu->addButton("                4 jugadores                 ", ButtonActions::FOURPLAYERS);
		//	menu->addButton("                   Atras       ", ButtonActions::BACK);
		menu->addButton("    Atras    ", ButtonActions::BACK);


		createBackgroundMenu(window);
	}

	void createGameTypeMenu(sf::RenderWindow& window, GameDisplayController& gameDisplay) {

		menu = new GameGUI::Menu(window);
		GameGUI::HorizontalBoxLayout* hboxQuit = menu->addHorizontalBoxLayout();

		menu->addButton("                Todos contra todos                  ", ButtonActions::ALLVSALL);
		menu->addButton("                Batalla por equipos                 ", ButtonActions::TEAM);
		//menu->addButton("            		    Atras      ", ButtonActions::BACK);

		menu->addButton("    Atras    ", ButtonActions::BACK);

		createBackgroundMenu(window);

	}


	void createAllVSAllMenu(sf::RenderWindow& window, GameDisplayController& gameDisplay, int numPlayers) {
		menu = new GameGUI::Menu(window);
		GameGUI::HorizontalBoxLayout* hboxQuit = menu->addHorizontalBoxLayout();
		cout << "TODOS CONTRA TODOS. NUM PLAYERS: " << numPlayers << endl;
		switch ((numPlayers)) {
		case 2:
			menu->addButton("                      Jugador vs IA                       ", ButtonActions::PLVSIA);
			menu->addButton("                  Jugador vs Jugador                ", ButtonActions::PLVSPL);
			menu->addButton("    Atras    ", ButtonActions::BACK);
			break;

		case 3:
			menu->addButton("                1  Jugador , 2 IA                   ", ButtonActions::PL12IA);
			menu->addButton("               2  Jugadores , 1 IA                 ", ButtonActions::PL21IA);
			menu->addButton("    Atras    ", ButtonActions::BACK);
			break;

		case 4:
			menu->addButton("                 1 Jugador , 3 IA                   ", ButtonActions::PL13IA);
			menu->addButton("                2 Jugadores , 2 IA                 ", ButtonActions::PL22IA);
			menu->addButton("    Atras    ", ButtonActions::BACK);
			break;

		default:
			break;
		}
		createBackgroundMenu(window);
	}



	void createTeamVSTeamMenu(sf::RenderWindow& window, GameDisplayController& gameDisplay, int numPlayers) {
		menu = new GameGUI::Menu(window);
		GameGUI::HorizontalBoxLayout* hboxQuit = menu->addHorizontalBoxLayout();
		cout << "EQUIPOS. NUM PLAYERS: " << numPlayers << endl;
		switch ((numPlayers)) {

		case 3:
			menu->addButton("                     1 Jugador Vs 2 IA                      ", ButtonActions::PL1VS2IA);
			menu->addButton("                    2 Jugadores Vs 1 IA                    ", ButtonActions::PL2VS1IA);
			menu->addButton("                1 Jugador vs Jugador IA                ", ButtonActions::PLVSPLIA);
			menu->addButton("    Atras    ", ButtonActions::BACK);

			break;

		case 4:
			menu->addButton("                    1 Jugador Vs  3 IA                      ", ButtonActions::PL1VS3IA);
			menu->addButton("          	     2 Jugadores Vs 2 IA                     ", ButtonActions::PL2VS2IA);
			menu->addButton("             Jugador IA  Vs Jugador IA                 ", ButtonActions::PLIAVSPLIA);
			menu->addButton("    Atras    ", ButtonActions::BACK);
			break;

		default:
			break;
		}
		createBackgroundMenu(window);

	}

	string mapToString(int num) {
		switch (num) {
		case 0:
			return "Prision  ";
			break;
		case 1:
			return "Tesoreria";
			break;
		default:
			return "Cristales";
			break;
		}
	}

	string mapSizeToString(int num) {
		switch (num) {
		case 0:
			return "Diminuto";
			break;
		case 1:
			return "Mediano";
			break;
		default:
			return "Grande";
			break;
		}
	}

	string difficultyIAToString(int num) {
		switch (num) {
		case 0:
			return "Facil";
			break;
		case 1:
			return "Normal";
			break;
		default:
			return "Dificil";
			break;
		}
	}

	string abilityToString(int num) {
		switch (num) {
		case 0:
			return "Ninguna";
			break;
		case 1:
			return "Guante";
			break;
		case 2:
			return "B Remota";
			break;
		case 3:
			return "Travesia";
			break;
		default:
			return "Patear";
			break;
		}
	}

	ActionsAvalible abilityToAbility(int num) {
		switch (num) {
		case 0:
			return ActionsAvalible::NONE_ACTION;
			break;
		case 1:
			return ActionsAvalible::GRAB_BOMB;
			break;
		case 2:
			return ActionsAvalible::REMOTE_BOMB;
			break;
		case 3:
			return ActionsAvalible::THROUGH_BOMB;
			break;
		default:
			return ActionsAvalible::KICK_BOM;
			break;
		}
	}

	void centerElement(GameGUI::Widget* e) {
		sf::Vector2f eSize = e->getSize();
		sf::Vector2f mSize = menu->getSize();
		e->setPosition(e->getPosition() + sf::Vector2f(mSize.x / 2 - eSize.x / 2, 0));
	}

	string getTimeString(int num) {
		string seconds = num % 60 > 9 ? to_string(num % 60) : "0" + to_string(num % 60);
		return to_string(num / 60) + ":" + seconds;
	}

	void pickMap(sf::RenderWindow& window, GameDisplayController& gameDisplay) {
		menu = new GameGUI::Menu(window);
		auto title = menu->add(new GameGUI::Label("Opciones de la partida"));
		GameGUI::FormLayout* f = menu->addFormLayout();
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		mapSlider = new GameGUI::Slider();
		mapSlider->setQuantum(mapQuantum);
		mapSlider->setValue(map * mapQuantum);

		
		GameGUI::HorizontalBoxLayout* mapLine = new GameGUI::HorizontalBoxLayout();
		mapLine->add(mapSlider, ButtonActions::MAP);
		mapText = mapLine->addLabel(mapToString(mapSlider->getValue() / mapQuantum));

		f->addRow("Mapa", mapLine);

		/////////////////////////////////////////////////////////////////////////////////////////////////
		livesSlider = new GameGUI::Slider();
		livesSlider->setQuantum(livesQuantum);
		livesSlider->setValue((lives - 1)* livesQuantum);

		
		GameGUI::HorizontalBoxLayout* livesLine = new GameGUI::HorizontalBoxLayout();
		livesLine->add(livesSlider, ButtonActions::LIVES);
		livesText = livesLine->addLabel(to_string(livesSlider->getValue() / livesQuantum + 1));

		f->addRow("Vidas", livesLine);

		/////////////////////////////////////////////////////////////////////////////////////////////////

		sizeMapSlider = new GameGUI::Slider();
		sizeMapSlider->setQuantum(sizeMapQuantum);
		sizeMapSlider->setValue(sizeMAp * sizeMapQuantum);


		GameGUI::HorizontalBoxLayout* sizeMapLine = new GameGUI::HorizontalBoxLayout();
		sizeMapLine->add(sizeMapSlider, ButtonActions::MAPSIZE);
		sizeMapText = sizeMapLine->addLabel(mapSizeToString(sizeMapSlider->getValue() / sizeMapQuantum));

		f->addRow("Dimension del mapa", sizeMapLine);

		/////////////////////////////////////////////////////////////////////////////////////////////////

		totalTimeSlider = new GameGUI::Slider();
		totalTimeSlider->setQuantum(totalTimeQuantum);
		totalTimeSlider->setValue(((totalTime - 30) / 30) * totalTimeQuantum);


		GameGUI::HorizontalBoxLayout* totalTimeLine = new GameGUI::HorizontalBoxLayout();
		totalTimeLine->add(totalTimeSlider, ButtonActions::TIME);
		totalTimeText = totalTimeLine->addLabel(getTimeString(totalTimeSlider->getValue() / totalTimeQuantum * 30 + 30));

		f->addRow("Tiempo Limite", totalTimeLine);

		/////////////////////////////////////////////////////////////////////////////////////////////////

		difficultyIASlider = new GameGUI::Slider();
		difficultyIASlider->setQuantum(difficultyIAQuantum);
		difficultyIASlider->setValue(difficultyLevel * difficultyIAQuantum);


		GameGUI::HorizontalBoxLayout* difficultyIALine = new GameGUI::HorizontalBoxLayout();
		difficultyIALine->add(difficultyIASlider, ButtonActions::IA_DIFFICULTY);
		difficultyIAText = difficultyIALine->addLabel(difficultyIAToString(difficultyIASlider->getValue() / difficultyIAQuantum));

		f->addRow("Dificultad IA", difficultyIALine);

		/////////////////////////////////////////////////////////////////////////////////////////////////
		auto advanceButton = menu->addButton("   Opciones Avanzadas   ", ButtonActions::ADVANCED_OPTIONS);
		auto continueButton = menu->addHorizontalBoxLayout();
		auto a1 = continueButton->addButton("          Atras          ", ButtonActions::BACK);
		a1->transformableOptions = false;
		a1->goDownDown = 2;
		auto a2 = continueButton->addButton("      Continuar      ", ButtonActions::CONTINUE);
		a2->transformableOptions = false;
		a2->goUpUp = 2;

		

		createBackgroundMenu(window);
		centerElement(title);
		centerElement(advanceButton);
		centerElement(continueButton);
		//centerElement(back);
	}


	void advancedOptions(sf::RenderWindow& window, GameDisplayController& gameDisplay) {
		menu = new GameGUI::Menu(window);
		auto title = menu->add(new GameGUI::Label("Opciones avanzadas de la partida"));
		GameGUI::FormLayout* f = menu->addFormLayout();

		/////////////////////////////////////////////////////////////////////////////////////////////////
		numStartingBombsSlider = new GameGUI::Slider();
		numStartingBombsSlider->setQuantum(numStartingBombsQuantum);
		numStartingBombsSlider->setValue((numStartingBombs - 1) * numStartingBombsQuantum);


		GameGUI::HorizontalBoxLayout* numStartingBombsLine = new GameGUI::HorizontalBoxLayout();
		numStartingBombsLine->add(numStartingBombsSlider, ButtonActions::BOMBS);
		numStartingBombsText = numStartingBombsLine->addLabel(to_string(numStartingBombsSlider->getValue() / numStartingBombsQuantum + 1));

		f->addRow("Bombas iniciales", numStartingBombsLine);

		/////////////////////////////////////////////////////////////////////////////////////////////////
		numStartingFireSlider = new GameGUI::Slider();
		numStartingFireSlider->setQuantum(numStartingFireQuantum);
		numStartingFireSlider->setValue((numStartingFire - 1) * numStartingFireQuantum );


		GameGUI::HorizontalBoxLayout* numStartingFireLine = new GameGUI::HorizontalBoxLayout();
		numStartingFireLine->add(numStartingFireSlider, ButtonActions::FIRE);
		numStartingFireText = numStartingFireLine->addLabel(to_string(numStartingFireSlider->getValue() / numStartingFireQuantum + 1));

		f->addRow("fuegos iniciales", numStartingFireLine);


		/////////////////////////////////////////////////////////////////////////////////////////////////
		numStartingSpeedSlider = new GameGUI::Slider();
		numStartingSpeedSlider->setQuantum(numStartingSpeedQuantum);
		numStartingSpeedSlider->setValue((numStartingSpeed - 1)* numStartingSpeedQuantum);


		GameGUI::HorizontalBoxLayout* numStartingSpeedLine = new GameGUI::HorizontalBoxLayout();
		numStartingSpeedLine->add(numStartingSpeedSlider, ButtonActions::SPEED);
		numStartingSpeedText = numStartingSpeedLine->addLabel(to_string(numStartingSpeedSlider->getValue() / numStartingSpeedQuantum + 1));

		f->addRow("Patines iniciales", numStartingSpeedLine);

		/////////////////////////////////////////////////////////////////////////////////////////////////

		startingAbilitySlider = new GameGUI::Slider();
		startingAbilitySlider->setQuantum(startingAbilityQuantum);
		startingAbilitySlider->setValue(startingAbility * startingAbilityQuantum);


		GameGUI::HorizontalBoxLayout* startingAbilityLine = new GameGUI::HorizontalBoxLayout();
		startingAbilityLine->add(startingAbilitySlider, ButtonActions::ABILITY);
		startingAbilityText = startingAbilityLine->addLabel(abilityToString(startingAbilitySlider->getValue() / startingAbilityQuantum));

		f->addRow("Habilidad inicial", startingAbilityLine);

		/////////////////////////////////////////////////////////////////////////////////////////////////

		percentageBrickWallsSlider = new GameGUI::Slider();
		percentageBrickWallsSlider->setQuantum(percentageBrickWallsQuantum);
		percentageBrickWallsSlider->setValue(percentageBrickWalls * percentageBrickWallsQuantum);


		GameGUI::HorizontalBoxLayout* percentageBrickWallsLine = new GameGUI::HorizontalBoxLayout();
		percentageBrickWallsLine->add(percentageBrickWallsSlider, ButtonActions::PERCENTAGE_BRICK_WALL);
		percentageBrickWallsText = percentageBrickWallsLine->addLabel(to_string(percentageBrickWallsSlider->getValue() / percentageBrickWallsQuantum));

		f->addRow("Porcentaje de muros", percentageBrickWallsLine);

		/////////////////////////////////////////////////////////////////////////////////////////////////

		percentageObjectsPerBrickWallSlider = new GameGUI::Slider();
		percentageObjectsPerBrickWallSlider->setQuantum(percentageObjectsPerBrickWallQuantum);
		percentageObjectsPerBrickWallSlider->setValue(percentageObjectsPerBrickWall * percentageObjectsPerBrickWallQuantum);


		GameGUI::HorizontalBoxLayout* percentageObjectsPerBrickWallLine = new GameGUI::HorizontalBoxLayout();
		percentageObjectsPerBrickWallLine->add(percentageObjectsPerBrickWallSlider, ButtonActions::PERCENTAGE_OBJECTS_IN_BRICK_WALL);
		percentageObjectsPerBrickWallText = percentageObjectsPerBrickWallLine->addLabel(to_string(percentageObjectsPerBrickWallSlider->getValue() / percentageObjectsPerBrickWallQuantum));

		f->addRow("Prob objeto por muro", percentageObjectsPerBrickWallLine);

		/////////////////////////////////////////////////////////////////////////////////////////////////

		

		auto back = menu->addButton("       Volver       ", ButtonActions::BACK_FROM_ADVANCED_OPTIONS);

		createBackgroundMenu(window);
		centerElement(title);
		centerElement(back);
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
		if (gameDisplay.multiplayerReprocessDisplay) {
			gameDisplay.multiplayerReprocessDisplay = false;
			createBackgroundMenu(*gameDisplay.getWindow());
		}
		draw(*gameDisplay.getWindow(), gameDisplay);

		// Manage window events and pass a callback to manage this menu buttons
		gameDisplay.manageGameInterface(gameDisplay, std::bind(&MultiplayerMenu::userActions, this, std::placeholders::_1, std::ref(gameDisplay.getWindow()), std::ref(gameDisplay), std::ref(game)));
	}


};

