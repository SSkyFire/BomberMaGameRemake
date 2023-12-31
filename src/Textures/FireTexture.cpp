#include "FireTexture.h"

FireTexture::FireTexture()
{
	if (!this->texture.loadFromFile("../textures/Entities/fires.png"))
	{
		throw ExceptionLoadImage("Imagen no cargada: ../textures/Entities/fires.png");
	}

	frames.reserve(5 * 7);
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			this->frames.push_back(sf::IntRect(0 + 51 * x, 0 + 51 * y, 48, 48));
		}
	}
}

sf::IntRect &FireTexture::getFrame(int stage, int i)
{
	return this->frames[7 * stage + i];
}