
#pragma once
#include "Player.h"
#include "../Utils/OmittedAreas.hpp"
#include "../PseudoPPDL/ParserPPDL.hpp"
#include "../PseudoPPDL/Estados.hpp"
#include "../Utils/IAglobal.hpp"


class PlayerIAEntity : public PlayerEntity
{
	sf::Color colorPath;
public:
	
	ANode_Ptr currentMovement;
	std::list<ANode_Ptr> movements;
	sf::Vector2i currentObjetive;
	StateGenerator sg;
	StateIA currentState = StateIA::NON_OBJETIVE;
	sf::Vector2f lastPositionKnowed;
	PatrolState p;
	LookingAt objetiveTo;
	int IAPlayer;
	bool justActionDone = false;
	double lastActionDone = 0;
	const double prob=0.5;

	/*,pos
	Constructor of Entity
	*/
	PlayerIAEntity(PlayerControls &playerControls,int posX,int posY, int _team,int IA) : PlayerEntity(playerControls, _team,posX,posY){
		colorPath = sf::Color(Random::getIntNumberBetween(0, 255), Random::getIntNumberBetween(0, 255), Random::getIntNumberBetween(0, 255));
		IAPlayer=IA;
		cout<<"POS DE LA IA: "<<posX<<" "<<posY<<endl;
	}

	void createStateGenerator(string path){
		sg.readIA(path);
	}
//	sf::FloatRect getGlobalBounds() const override; Modificar??
	void setExpiredEntity() override;
//	void update() override;
	void setCollision(std::shared_ptr<Entity> e) override;
	void drawMovements(sf::RenderWindow &w);
//	void realizeActions();
	//void generateMovements();
	bool updateVelocity();
	void updateMovement();
	bool playerActions() override;
	/*
	 * Update player position.
	 */
	bool updatePlayer() override;

//	void invertControls(); ??


	////////IA FUNCTION
	void AssignBomb(std::shared_ptr<Entity> b) override{
		BombsAsociated.push_back(b);
	}
	void startStates();
	void seekAndDestroyEnemy();
	void updateState();
	void generatePathStates();
	bool updatePatrolState();
	bool updateKillState();
	bool updatePerseguirState();
	bool updateRunawayState();
	void updateFarm();
	void updateCathPU();
	void putABomb();
	void decildetState();
	void checkExploteRemote();

	float getIntersetActionPU(){
		return sg._SeekPEStruct.interActionPU;
	}
	float getIntersetNerfPU(){
		return sg._SeekPEStruct.interNerfPU;
	}
	float getIntersetBuffPE(){
		return sg._SeekPEStruct.interBuffPU;
	}

	float getIntersetDestroyWalls(){
		return sg.bonusDestroyWalls;
	}

	bool avanzaAtravesDelFuego(double scoreCamino){
		return ((scoreCamino/sg._KillStruct.imprudencia) > prob);
	}

	bool canKickBomb(sf::Vector2i &lookinCell);
	bool canGrabBombIA(sf::Vector2i &lookinCell);
	bool canThrowBomb();
	bool TryGrabBomb();
	bool TryKickBomb();
	bool TryThrowBomb();
	void ThrowingState();
	void kickingState();
	bool useAvility();
	bool isObjetiveOnRange();
	bool isObjetiveFarmOnRange();
	bool objetiveOnExactlyThrowBomb();
	bool canArraiveBombKickinExactly();
	void updatePanicMode();
	bool canArraiveBombKickin();
};