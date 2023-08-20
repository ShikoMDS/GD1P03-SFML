#include "GUI/Level.h"
#include <iostream>

Level::Level()
{
	if (!m_TrapTexture.loadFromFile("Resources/Images/Man Mage.png"))
	{
		std::cout << "Image loading failed" << std::endl;
	}

	for (int x = 0; x < LevelWidth; x++)
	{
		for (int y = 0; y < LevelHeight; y++)
		{
			if (x == 0 || x == LevelWidth - 1 || y == 0 || y == LevelHeight - 1)
			{
				// Create an object
				Object* newWallTile = new Object(ObjectType::Type_Wall, sf::Vector2f(250 + x * 30, 150 + y * 30));
				m_LevelObjects.push_back(newWallTile);
			}
		}
	}
}

Level::~Level()
{

}

void Level::PlaceObject(sf::RenderWindow* _Window)
{
	sf::Color Grey;
	Grey.r = 89;
	Grey.g = 89;
	Grey.b = 89;

	// Don't need, using world position now
	// sf::Vector2f ObjectPosition;
	//
	// ObjectPosition.x = sf::Mouse::getPosition(*_Window).x;
	// ObjectPosition.y = sf::Mouse::getPosition(*_Window).y;

	sf::Vector2i WindowPosition = sf::Mouse::getPosition(*_Window);
	sf::Vector2f WorldPosition = _Window->mapPixelToCoords(WindowPosition);

	Object* newTrap = new Object(ObjectType::Type_Trap, WorldPosition);
	newTrap->m_ObjShape.setFillColor(sf::Color::White);
	newTrap->m_ObjShape.setTexture(&m_TrapTexture);

	m_LevelObjects.push_back(newTrap);
}
