#pragma once
#include "../Textures/WallTexture.h"
#include "../Textures/TextureStorage.h"
#include "Entity.h"
#include "Enemy.h"

class BrickWall : public Entity {
public:
	WallTexture* wallTexture;
	Sprite shadow;
	int stage;

	double spriteStartTime;
	double spriteLastFrameTime;

	double spriteSpeed = 0.1;
	int currentFrame = 1;
	int spriteFrames = 7;

	double expiredTime = 0.6;

	bool isDestroyed = false;
	
	BrickWall(int &xloc, int &yloc, int stage);
	void update() override;

	void drawShadow(sf::RenderWindow& window) override;

	bool isColliderWith(std::shared_ptr<Entity> eCollisioning) override;
	void onCollission(std::shared_ptr<Entity> eCollisioning, std::shared_ptr<Entity> eCollisioner, CollisionType colT) override;
	void setExpiredEntity() override;
	void deleteWall();
};
