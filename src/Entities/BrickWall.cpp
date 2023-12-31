#include "../Include/EntitiesInclude.hpp"


BrickWall::BrickWall(int &xloc, int &yloc, int stage) : Entity()
{
	isFireDestroyable = true;
	this->stage = stage;
	scoreValue=10;

	// Set coordinates:
	setPosition(xloc * SIZE_PILLAR, yloc * SIZE_PILLAR);

	// Texture Controller
	wallTexture = &TextureStorage::getlevel1WallTexture();
	// Set starting sprite
	setTextureRect(wallTexture->getRectWall(1, stage));
	// Set sprite Sheet texture
	setTexture(wallTexture->getTexture());

	shadow.setTexture(TextureStorage::getWallShadowTexture().getTexture());
	shadow.setColor(sf::Color(255,255,255,150));
}

void BrickWall::update()
{
	if (isDestroyed)
	{ 
		if (GameTime::getTimeNow() - spriteStartTime > expiredTime) {
			expiredEntity = true;
		}
		else if (GameTime::getTimeNow() - spriteLastFrameTime > spriteSpeed) {
			spriteLastFrameTime = GameTime::getTimeNow();
			currentFrame = (currentFrame + 1) % spriteFrames;
			setTextureRect(wallTexture->getRectWall(currentFrame, stage));
			int alfa = shadow.getColor().a;
			alfa = alfa - 40 < 0 ? 0 : alfa - 40;

			shadow.setColor(sf::Color(255, 255, 255, alfa));
		}	
	}
}

void BrickWall::drawShadow(sf::RenderWindow& window) {
	shadow.setPosition(this->getPosition().x, this->getPosition().y + 45);
	window.draw(shadow);
}
 

bool BrickWall::isColliderWith(std::shared_ptr<Entity> eCollisioning) {
	return !eCollisioning->CanThroughWall();
}

void BrickWall::onCollission(std::shared_ptr<Entity> eCollisioning, std::shared_ptr<Entity> eCollisioner, CollisionType colT)
{
	if (std::dynamic_pointer_cast<EnemyEntity>(eCollisioning))
	{
		//Puede atravesar????
		Entity::onCollission(eCollisioning, eCollisioner ,colT);
	}
	else
	{
		Entity::onCollission(eCollisioning, eCollisioner,colT);
	}
}

void BrickWall::setExpiredEntity()
{
	spriteStartTime = GameTime::getTimeNow();
	spriteLastFrameTime = GameTime::getTimeNow();
	isDestroyed = true;
}

void BrickWall::deleteWall()
{
	setTextureRect(sf::IntRect(0,0,0,0));
	expiredEntity=true;
}
