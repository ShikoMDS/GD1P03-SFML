#include "GUI/Level.h"

Level::Level()
{
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

	sf::Vector2f ObjectPosition;

	ObjectPosition.x = sf::Mouse::getPosition(*_Window).x;
	ObjectPosition.y = sf::Mouse::getPosition(*_Window).y;

	Object* newTrap = new Object(ObjectType::Type_Trap, ObjectPosition);
	newTrap->m_ObjShape.setFillColor(Grey);
	m_LevelObjects.push_back(newTrap);
}
