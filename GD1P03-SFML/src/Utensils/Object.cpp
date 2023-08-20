#include "Utensils/Object.h"

// Constructor. Each object has a type and position
Object::Object(ObjectType _Type, sf::Vector2f _Position)
{
	m_ObjShape.setSize(sf::Vector2f(30, 30));
	m_ObjShape.setPosition(_Position);

	// Switch statement allows colour change based on the object type, part of the object constructor above
	switch (_Type)
	{
	case Type_Trap:
		m_ObjShape.setFillColor(sf::Color::Red);
		break;

	case Type_Player:
		m_ObjShape.setFillColor(sf::Color::Blue);
		break;

	case Type_Goal:
		m_ObjShape.setFillColor(sf::Color::Yellow);
		break;

	case Type_Wall:
		m_ObjShape.setFillColor(sf::Color::White);
		break;

	default:
		break;
	}
}

Object::~Object()
{

}

void Object::Update()
{

}

void Object::Input(float _dt)
{
	m_ObjSpeed = sf::Vector2f(0, 0); // Comment out for acceleration
	
	if(sf::Keyboard::isKeyPressed((sf::Keyboard::W)))
	{
		m_ObjSpeed.y += -1.0f; // Use += for acceleration
	}

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::S)))
	{
		m_ObjSpeed.y += 1.0f;
	}

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::A)))
	{
		m_ObjSpeed.x += -1.0f;
	}

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::D)))
	{
		m_ObjSpeed.x += 1.0f;
	}

	m_ObjShape.move(m_ObjSpeed * m_SpeedScalar * _dt);
}
