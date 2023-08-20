#pragma once

#include  <SFML/Graphics.hpp>

enum ObjectType
{
	Type_Trap,
	Type_Player,
	Type_Goal,
	Type_Wall
};

class Object
{
public:
	sf::RectangleShape m_ObjShape;
	ObjectType m_OjectType;
	sf::Vector2f m_ObjSpeed;

	float m_SpeedScalar = 60.0f;

	Object(ObjectType _Type, sf::Vector2f _Position);
	~Object();

	void Update();
	void Input(float _dt);
};