#pragma once

#include "Utensils/Object.h"

class Level
{
public:
	int LevelWidth = 15;
	int LevelHeight = 15;

	std::vector<Object*> m_LevelObjects;

	Level();
	~Level();

	void PlaceObject(sf::RenderWindow* _Window); // Passing in RenderWindow to make sure mouse relative to window and not desktop
};