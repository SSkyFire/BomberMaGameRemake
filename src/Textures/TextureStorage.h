#pragma once
#include "BombTexture.h"
#include "EnemyTexture.h"
#include "PlayerTexture.hpp"
#include "WallTexture.h"
#include "FireTexture.h"
#include "PowerUpTexture.h"
#include "TeleporterTexture.h"

class TextureStorage {
	static PlayerTexture playerTexture;
	static PlayerColor playerColor;
	static EntityShadowTexture entityShadowTexture;
	static WallTexture level1WallTexture;
	static WallShadowTexture wallShadowTexture;
	static BombTexture bombTexture;
	static FireTexture fireTexture;
	static EnemyTexture enemyTexture; 
	static PowerUpTexture powerUpTexture;
	static TeleporterTexture teleporterTexture;


public:

	TextureStorage();

	static PlayerTexture& getPlayerTexture();

	static PlayerColor& getPlayerColor();

	static EntityShadowTexture& getEntityShadowTexture();

	static WallTexture& getlevel1WallTexture();

	static WallShadowTexture& getWallShadowTexture();

	static BombTexture& getBombTexture();

	static FireTexture& getFireTexture();

	static EnemyTexture& getEnemyTexture();

	static PowerUpTexture& getPowerUpTexture();

	static TeleporterTexture& getTeleporterTexture();

	
};