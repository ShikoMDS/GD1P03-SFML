#include "Utensils/CanvasManager.h"

CanvasManager::CanvasManager(sf::RenderTexture* _CanvasRef, sf::RenderWindow* _WindowRef)
{
	m_CanvasRef = _CanvasRef;
	m_WindowRef = _WindowRef;

	m_CurrentShapeColour.r = 89;
	m_CurrentShapeColour.g = 89;
	m_CurrentShapeColour.b = 89;

	m_CurrentRect.setFillColor(m_CurrentShapeColour);
}

CanvasManager::~CanvasManager()
{

}

//sf::Vector2i WindowPosition = sf::Mouse::getPosition(*_Window);
//sf::Vector2f WorldPosition = _Window->mapPixelToCoords(WindowPosition);
void CanvasManager::InitShape()
{
	m_MouseStartPos = m_WindowRef->mapPixelToCoords(sf::Mouse::getPosition(*m_WindowRef));
	m_CurrentRect.setPosition(m_MouseStartPos);

	m_IsDrawing = true;
}

void CanvasManager::DrawRect()
{
	m_CurrentMousePosf = m_WindowRef->mapPixelToCoords(sf::Mouse::getPosition(*m_WindowRef));
	sf::Vector2f Distance = -(m_MouseStartPos - m_CurrentMousePosf);

	m_CurrentRect.setSize(Distance);

	m_WindowRef->draw(m_CurrentRect);
}

void CanvasManager::EndDraw()
{
	m_CanvasRef->draw(m_CurrentRect);
	m_CanvasRef->display();

	// Add extra line for flickering

	m_IsDrawing = false;
}

void CanvasManager::ShapeCleanup()
{
	// Add extra line for flickering

	m_CurrentRect.setSize(sf::Vector2f(0.0f, 0.0f));
	m_CurrentRect.setPosition(-10000, -10000);
}

void CanvasManager::DrawUpdate()
{
	switch (m_CurrentTool)
	{
	case Tool_None:
		break;
	case Tool_Rect:
		DrawRect();
		break;
	default:
		break;
	}
}

void CanvasManager::SwapTool()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_CurrentTool = ToolOptions::Tool_None;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_CurrentTool = ToolOptions::Tool_Rect;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		// Free draw
	}
}

void CanvasManager::UpdateColour(sf::Color _NewColour)
{
	m_CurrentRect.setFillColor(_NewColour);
}
