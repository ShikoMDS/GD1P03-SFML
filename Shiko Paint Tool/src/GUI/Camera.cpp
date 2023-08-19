#include "GUI/Camera.h"

Camera::Camera(sf::Vector2f _CameraPosition, sf::Vector2f _CameraSize)
{
	m_CameraView.setCenter(_CameraPosition);
	m_CameraView.setSize(_CameraSize);
}

Camera::~Camera()
{

}

void Camera::CameraMove()
{
	m_CameraSpeed = sf::Vector2f(0, 0); // Comment out for acceleration

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Up)))
	{
		m_CameraSpeed.y += -1.0f; // Use += for acceleration
	}

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Down)))
	{
		m_CameraSpeed.y += 1.0f;
	}

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Left)))
	{
		m_CameraSpeed.x += -1.0f;
	}

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Right)))
	{
		m_CameraSpeed.x += 1.0f;
	}

	m_CameraView.move(m_CameraSpeed);
}
