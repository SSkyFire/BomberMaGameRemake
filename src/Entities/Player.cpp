#include "../Map/Level.hpp"
#include "../Utils/IAFunctions.hpp"
#include "../Music/GameSounds.h"
PlayerEntity::PlayerEntity(PlayerControls& pControls, int _team, float posX,float posY) : Entity(), playerControls(pControls) {

	team = _team;
	respownPosition = sf::Vector2f(posX, posY);
	lastRespawnTime = 0;
	isFireDestroyable = true;
	fireCanGoThroght = true;
	collisioner = false;
	animLastTic = GameTime::getTimeNow();
	lastMovementTime = GameTime::getTimeNow();
	baseSpeed = 2.5;
	lastMovement = LookingAt::down;
	lives = 3;
	scoreValue = 150;
	// Texture Controller
	playerTexture = &TextureStorage::getPlayerTexture();
	// Set starting sprite
	setTextureRect(playerTexture->getDefaultIntRect());
	// Set sprite Sheet texture
	setTexture(playerTexture->getTexture());
	// Texture Controller
	playerColor = &TextureStorage::getPlayerColor();
	// Set starting sprite
	playerColorEntity.setTextureRect(playerColor->getDefaultIntRect());
	// Set sprite Sheet texture
	playerColorEntity.setTexture(playerColor->getTexture());
	playerColorColor = sf::Color(Random::getIntNumberBetween(0, 255), Random::getIntNumberBetween(0, 255), Random::getIntNumberBetween(0, 255), 225);
	playerColorEntity.setColor(playerColorColor);

	playerHead.setTexture(playerColor->getTexture());
	playerHead.setColor(playerColorColor);
	playerHead.setTextureRect(sf::IntRect(sf::Vector2i(9, 0), sf::Vector2i(39, 39)));

	playerHead2.setTexture(playerTexture->getTexture());
	playerHead2.setTextureRect(sf::IntRect(sf::Vector2i(9, 0), sf::Vector2i(39, 39)));

	if (posX > 150) {
		posX -= 50;
	}
	setPosition(posX,posY);
	initialPos = sf::Vector2f(posX, posY);
	cout<<"INITIAL POS X "<<posX<<" INITIAL POS Y "<<posY<<endl;

	shadow.setTexture(TextureStorage::getEntityShadowTexture().getTexture());
	shadow.setColor(sf::Color(255, 255, 255, 200));

	//actionAvaible = ActionsAvalible::KICK_BOM;
	//numOfBombs = 3;
	//powerOfBombs = 3;
}

int PlayerEntity::getPowerOfBombs() {
	return powerOfBombs;
}

void PlayerEntity::drawShadow(sf::RenderWindow& window) {
	if (!expiredEntity) {
		shadow.setPosition(this->getPosition().x + 6, this->getPosition().y + 53);
		window.draw(shadow);
	}
}

void PlayerEntity::setExpiredEntity() {
	if (GameTime::getTimeNow() - lastInvencibleTime < invencibleTime) {
		return;
	}
	//
	if (!expiredEntity) {
		if (storyMode) {
			while (BombsAsociated.size() > 0) {
				BombsAsociated.front()->setExpiredEntity();
			}
			resetStats();
		}

		GameSounds::playerDead();

		if(BombTaked != nullptr){
			BombTaked->setExpiredEntity();
		}
		this->BombTaked = nullptr;
		expiredEntity = true;
		//if(!dead){
		    currentFrame = 0;
		    animLastTic = GameTime::getTimeNow();
		//}
	}
}

inline Entity& PlayerEntity::getPlayerColorEntity() {
	return playerColorEntity;
}

void PlayerEntity::changeColor(sf::Color newColor) {
	playerColorColor = newColor;
	playerColorEntity.setColor(sf::Color(playerColorColor.r, playerColorColor.g, playerColorColor.b, 225));
	playerHead.setColor(sf::Color(playerColorColor.r, playerColorColor.g, playerColorColor.b, 225));
}


int PlayerEntity::getLives() {
	return lives;
}

void PlayerEntity::resetStats() {
	speedBoost = 1;
	numOfBombs = 1;
	powerOfBombs = 1;
	actionAvaible = ActionsAvalible::NONE_ACTION;
}

void PlayerEntity::setStats(double speedBoost, int numOfBombs, int powerOfBombs, int lives, ActionsAvalible action) {
	this->speedBoost = speedBoost;
	this->numOfBombs = numOfBombs;
	this->powerOfBombs = powerOfBombs;
	this->lives = lives; 
	this->actionAvaible = action;

}

/*
	Animate Entity by changing the actual sprite.
	*/
void PlayerEntity::animate(sf::Vector2f velocity) {
	// If the player has died:
	if (!expiredEntity) {
		if (!bombThrowed) {
			if (BombTaked == nullptr) {
				if (velocity.x == 0 && velocity.y == 0) {
					// If there is not speed set idle sprite
					setTextureRect(playerTexture->getIdleSprite(lastMovement));
					playerColorEntity.setTextureRect(playerTexture->getIdleSprite(lastMovement));
				}
				else {
					// If there is speed we must update animation sprite every X time
					if (GameTime::getTimeNow() - animLastTic > frameSpeed) {
						setTextureRect(playerTexture->getMoveSprite(lastMovement, currentFrame));
						playerColorEntity.setTextureRect(playerTexture->getMoveSprite(lastMovement, currentFrame));
						currentFrame = (currentFrame + 1) % walkFrames;
						animLastTic = GameTime::getTimeNow();
					}
				}
			}
			else {
				if (velocity.x == 0 && velocity.y == 0) {
					// If there is not speed set idle sprite
					setTextureRect(playerTexture->getIdleSpriteWithBomb(lastMovement));
					playerColorEntity.setTextureRect(playerTexture->getIdleSpriteWithBomb(lastMovement));
				}
				else {
					// If there is speed we must update animation sprite every X time
					if (GameTime::getTimeNow() - animLastTic > frameSpeed) {
						setTextureRect(playerTexture->getMoveSpriteWithBomb(lastMovement, currentFrame));
						playerColorEntity.setTextureRect(playerTexture->getMoveSpriteWithBomb(lastMovement, currentFrame));
						currentFrame = (currentFrame + 1) % walkFrames;
						animLastTic = GameTime::getTimeNow();
					}
				}
			}
		}
		else {
			if (GameTime::getTimeNow() - lastThrowedTime > frameSpeed) {
				setTextureRect(playerTexture->getThrowBomb(lastMovement, currentFrame));
				playerColorEntity.setTextureRect(playerTexture->getThrowBomb(lastMovement, currentFrame));
				lastThrowedTime = GameTime::getTimeNow();
				currentFrame = (currentFrame + 1) % walkFrames;
				if (currentFrame > 1) {
					bombThrowed = false;
				}
			}
		}
			
	}
	else {
		if (!respawning) {
			if (GameTime::getTimeNow() - animLastTic > frameSpeed) {
				if (currentFrame == 7) {
					currentFrame = 0;
					lives--;
					if (lives > 0) {
						lastRespawnTime = GameTime::getTimeNow();
						respawning = true;
					}
					else {
						lives = 0;
						dead = true;
						// setExpiredEntity();
						//dead=true;
					}

					/*else{
						gameDisplay.setGameState(GameDisplayController::GameState::GAME_OVER);
					}*/
					//Else mostrar fin de partida
					/*else{}
						expiredEntity = false;
					setPosition(100, 100);*/
				}
				else {
					setTextureRect(playerTexture->getDeathSprite(currentFrame));
					playerColorEntity.setTextureRect(playerTexture->getDeathSprite(currentFrame));
					currentFrame = (currentFrame + 1) % deathFrames;
					animLastTic = GameTime::getTimeNow();
				}
			}
		}
	
		else if (GameTime::getTimeNow() - lastRespawnTime > respawnTime) {
			expiredEntity = false;
			respawning = false;
			lastInvencibleTime = GameTime::getTimeNow();
			isInvicible = true;
			if (storyMode) {
				resetStats();
			}
			setPosition(initialPos);
			//cout<<"INITIAL POS X "<<initialPos.x<<" INITIAL POS Y "<<initialPos.y<<endl;
		}
	}

	if (isInvicible) {
		if (GameTime::getTimeNow() - lastInvencibleTime < invencibleTime) {
			if (GameTime::getTimeNow() - lastTransparentTime > 0.25) {
				transparent = !transparent;
				if (transparent) {
					setColor(sf::Color(255, 255, 255, 255));
					playerColorEntity.setColor(sf::Color(playerColorColor.r, playerColorColor.g, playerColorColor.b, 225));
				}
				else {
					setColor(sf::Color(255,255,255,80));
					playerColorEntity.setColor(sf::Color(playerColorColor.r, playerColorColor.g, playerColorColor.b, 120));
				}
				lastTransparentTime = GameTime::getTimeNow();
			}
			
		}
		else {
			isInvicible = false;
			transparent = false;
			setColor(sf::Color(255, 255, 255, 255));
			playerColorEntity.setColor(sf::Color(playerColorColor.r, playerColorColor.g, playerColorColor.b, 225));
		}
	}
	


	if (controlsInverted) {
		if (GameTime::getTimeNow() - lastControlInvertedTime > 20) {
			controlsInverted = false;
		}
	}
}


sf::FloatRect PlayerEntity::getGlobalBounds() const {
	sf::FloatRect dim = sf::Sprite::getGlobalBounds();
	return sf::FloatRect(dim.left + 15, dim.top + 45, 27, 27);
}

Entity &PlayerEntity::playerUpdateColor()
{
	playerColorEntity.setPosition(getPosition());
	return playerColorEntity;
}

void PlayerEntity::drawEntity(sf::RenderWindow& w) {
	// Draw the player if they are not dead
	if (!dead && !respawning) {
		w.draw(*this);
		w.draw(playerUpdateColor());
	}

	// Draw the bomb if they are carrying one
	if (getBomb() != nullptr) {
		auto bombpos = getBomb()->getPosition();
		auto playerPos = getCenterPosition();

		getBomb()->setPosition(playerPos.x, playerPos.y - getTextureRect().height + 10);
		w.draw(*getBomb());
		getBomb()->setPosition(bombpos);
	}
}


void PlayerEntity::update() {
	return;
}

void PlayerEntity::onCollission(std::shared_ptr<Entity> eCollisioning, std::shared_ptr<Entity> eCollisioner, CollisionType colT) {
	return;
}

void PlayerEntity::realizeActions()
{
	if (BombTaked != nullptr)
	{
		//lanzar
		Level::ThrowBomb(me, std::dynamic_pointer_cast<Bomb>(BombTaked));
		BombTaked.reset();
		bombThrowed = true;
		lastThrowedTime = GameTime::getTimeNow();
		currentFrame = 0;
	}
	else
	{
		switch (this->actionAvaible)
		{
		case ActionsAvalible::GRAB_BOMB:
			Level::canTakeBomb(me);
			break;
		case ActionsAvalible::KICK_BOM:
			Level::canKickBomb(me);
			break;
		case ActionsAvalible::REMOTE_BOMB:
			if(BombsAsociated.size() > 0)
				BombsAsociated.front()->setExpiredEntity();
			break;
		default:
			break;
		}
	}
}

/**
	 * 
	 */

bool PlayerEntity::playerActions() {
	bool playerBOMB = sf::Keyboard::isKeyPressed(playerControls.UseBomb);
	bool actionButton = sf::Keyboard::isKeyPressed(playerControls.MakeAction);
if(!respawning && !this->dead && !this->expiredEntity){
	if (!playerBOMB)
	{
		isBombKeyPresed = false;
	}
	else if (numOfBombs > 0 && !isBombKeyPresed)
	{
		if (Level::addBomb(this->me))
		{
			numOfBombs--;
		}
		isBombKeyPresed = true;
	}

	if (!actionButton)
	{
		this->isActionKeyPresed = false;
	}
	else if (!isActionKeyPresed)
	{ //Si el boton accion y no se acaba de pulsar
		this->isActionKeyPresed = true;
		realizeActions();
	}

	return isBombKeyPresed;
}
}


/*
	 * Update player position.
	 */
bool PlayerEntity::updatePlayer() {

	// Player movement
	bool playerRight = (sf::Keyboard::isKeyPressed(playerControls.goRight));
	bool playerLeft = (sf::Keyboard::isKeyPressed(playerControls.goLeft));
	bool playerUp = (sf::Keyboard::isKeyPressed(playerControls.goUp));
	bool playerDown = (sf::Keyboard::isKeyPressed(playerControls.goDown));

	double moveTime = 0;
	if (lastMovementTime) {
		moveTime = (GameTime::getTimeNow() - lastMovementTime) * 60;
	
	}
	lastMovementTime = GameTime::getTimeNow();

	velocity.x = 0;
	velocity.y = 0;

	sf::FloatRect body = getGlobalBounds();
	if (playerDown) {
		velocity.y = baseSpeed * speedBoost * moveTime;
		if(velocity.y > body.height/2){
			velocity.y = body.height/2;
		}

	}
	if (playerUp) {
		velocity.y = -baseSpeed * speedBoost * moveTime;
		if(velocity.y < -body.height/2){
			velocity.y = -body.height/2;
		}
	}
	if (playerLeft) {
		velocity.x = -baseSpeed * speedBoost * moveTime;
		if(velocity.x > body.width/2){
			velocity.x = body.width/2;
		}
	}
	if (playerRight) {
		velocity.x = baseSpeed * speedBoost * moveTime;
		//lives--;
		if(velocity.x < -body.width/2){
			velocity.x = -body.width/2;
		}
	}

	// If bomberman has dizzy debuff
	if (controlsInverted) {
		velocity = -velocity;
	}

	// Look dir whit velocity
	if (velocity.x != 0) {
		if (velocity.x > 0) {
			lastMovement = LookingAt::right;
		}
		else {
			lastMovement = LookingAt::left;
		}
	}
	else if (velocity.y != 0) {
		if (velocity.y > 0) {
			lastMovement = LookingAt::down;
		}
		else {
			lastMovement = LookingAt::up;
		}
	}

	// Call animate function to change current sprite if needed.
	animate(velocity);
	//cout<<"velocity Normal: "<<velocity.x<<" "<<velocity.y<<endl;

	// Move Entity position
	if (!expiredEntity) {
		Interst_ptr i = PointsDestroyMap::getIntersetZone(getEntityMapCoordinates());
		if(i != nullptr){
			//std::cout<< "interes " <<  i->intersest() << "\n";
		}else{
			//std::cout<< "interes 0\n";
		}
		move(velocity.x, velocity.y);
		if (BombTaked != nullptr) {//Si tiene bomba, actualizar a la posicion del jugador (centrado segun cuadricula)
			BombTaked->setPosition(Level::getMapCellCorner(this->getCenterPosition()));
		}
	}

	return false;
}


void PlayerEntity::setJumpingBomb() {
	//Actializar frames
	return;
}

void PlayerEntity::invertControls() {
	controlsInverted = true;
	lastControlInvertedTime = GameTime::getTimeNow();
}

std::shared_ptr<Entity> PlayerEntity::getBomb() {
	return BombTaked;
}


void PlayerEntity::bombExploted(Entity_ptr b){
	BombsAsociated.remove(b);
	numOfBombs++;
}

