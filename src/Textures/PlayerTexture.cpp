#include "PlayerTexture.hpp"

	
	PlayerTexture::PlayerTexture() {
		if (!this->texture.loadFromFile("../textures/Entities/BombermanSpriteSheet.png")) {
			throw ExceptionLoadImage("Imagen no cargada: ../textures/Entities/BombermanSpriteSheet.png");
		}
		
		// Save sprites positions in a array
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				sf::IntRect frame(FRAME_SIZE_X * x, FRAME_SIZE_Y * y, FRAME_SIZE_X, FRAME_SIZE_Y);
				frames.push_back(frame);
			}
		}
		for (int y = 4; y < 9; y++) {
			for (int x = 0; x < 7; x++) {
				sf::IntRect frame(FRAME_SIZE_X * x, FRAME_SIZE_Y * y, FRAME_SIZE_X, FRAME_SIZE_Y);
				frames.push_back(frame);
			}
		}
	}

	sf::IntRect& PlayerTexture::getIdleSprite(LookingAt lookat) {
		return frames[lookat * 4];
	}

	sf::IntRect& PlayerTexture::getMoveSprite(LookingAt lookat, int i) {
		return frames[lookat * 4 + i];
	}

	sf::IntRect& PlayerTexture::getIdleSpriteWithBomb(LookingAt lookat) {
		return frames[16 + lookat * 7];
	}

	sf::IntRect& PlayerTexture::getMoveSpriteWithBomb(LookingAt lookat, int i) {
		return frames[16 + lookat * 7 + i];
	}

	sf::IntRect& PlayerTexture::getThrowBomb(LookingAt lookat, int i) {
		return frames[20 + lookat * 7 + i];
	}

	sf::IntRect& PlayerTexture::getDeathSprite(int i) {
		return frames[44 + i];
	}


	PlayerColor::PlayerColor() {
		if (!this->texture.loadFromFile("../textures/Entities/BombermanSpriteSheetColors.png")) {
			throw ExceptionLoadImage("Imagen no cargada: ../textures/Entities/BombermanSpriteSheet.png");
		}

		// Save sprites positions in a array
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				sf::IntRect frame(FRAME_SIZE_X * x, FRAME_SIZE_Y * y, FRAME_SIZE_X, FRAME_SIZE_Y);
				frames.push_back(frame);
			}
		}
		for (int y = 4; y < 9; y++) {
			for (int x = 0; x < 7; x++) {
				sf::IntRect frame(FRAME_SIZE_X * x, FRAME_SIZE_Y * y, FRAME_SIZE_X, FRAME_SIZE_Y);
				frames.push_back(frame);
			}
		}
	}

	sf::IntRect& PlayerColor::getIdleSprite(LookingAt lookat) {
		return frames[lookat * 4];
	}

	sf::IntRect& PlayerColor::getMoveSprite(LookingAt lookat, int i) {
		return frames[lookat * 4 + i];
	}

	sf::IntRect& PlayerColor::getDeathSprite(int i) {
		return frames[44 + i];
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//											SHADOW
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	EntityShadowTexture::EntityShadowTexture() {
		if (!this->texture.loadFromFile("../textures/Entities/moveEntityShadow.png")) {
			throw ExceptionLoadImage("Imagen no cargada: ../textures/Entities/moveEntityShadow.png");
		}

		this->frames.push_back(sf::IntRect(0, 0, 45, 15));
	}