#pragma once
#include <SFML/Graphics.hpp>

enum ToolOptions
{
	Tool_None,
	Tool_Rect
};

class CanvasManager
{
public:
	CanvasManager(sf::RenderTexture* _CanvasRef, sf::RenderWindow* _WindowRef);
	~CanvasManager();

	void InitShape();
	void DrawRect();
	void EndDraw();

	void ShapeCleanup();

	void DrawUpdate();
	void SwapTool();

	void UpdateColour(sf::Color _NewColour);

	sf::Vector2f m_MouseStartPos;
	bool m_IsDrawing = false;

	sf::Color m_CurrentShapeColour;

private:
	ToolOptions m_CurrentTool;

	sf::RenderTexture* m_CanvasRef;
	sf::RenderWindow* m_WindowRef;

	sf::RectangleShape m_CurrentRect;
	sf::Vector2f m_RectSize;

	sf::Vector2f m_CurrentMousePosf;
};

