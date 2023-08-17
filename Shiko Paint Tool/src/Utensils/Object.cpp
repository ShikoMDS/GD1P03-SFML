#include "Utensils/Object.h"

Object::Object(ObjectType _Type, sf::Vector2f _Position)
{
	m_ObjShape.setSize(sf::Vector2f(30, 30));
	m_ObjShape.setPosition(_Position);

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

void Object::Input()
{
	m_ObjSpeed = sf::Vector2f(0, 0);
	if(sf::Keyboard::isKeyPressed((sf::Keyboard::Up)))
	{
		m_ObjSpeed.y = -1.0f;
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Down)))
	{
		m_ObjSpeed.y = 1.0f;
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Left)))
	{
		m_ObjSpeed.x = -1.0f;
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Right)))
	{
		m_ObjSpeed.x = 1.0f;
	}
	m_ObjShape.move(m_ObjSpeed);
}
