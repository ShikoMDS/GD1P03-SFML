#include "GUI/Level.h"
#include "GUI/UIElement.h"
#include "GUI/Camera.h"

#include <iostream>

// ALWAYS BUILD IN RELEASE AT LEAST ONCE A DAY

int main()
{
    // Main window creation
    sf::RenderWindow Window(sf::VideoMode(800, 600), "SFML works!");
    Window.setFramerateLimit(60); // Sets to 60 fps

	// Secondary window creation
    sf::RenderWindow OptionsWindow(sf::VideoMode(400, 400), "Options Window");
    OptionsWindow.setVerticalSyncEnabled(true); // Sets to monitor refresh rate

    Camera MainCamera(sf::Vector2f(Window.getSize().x / 2, Window.getSize().y / 2), sf::Vector2f(Window.getSize().x, Window.getSize().y));

    Object Player(ObjectType::Type_Player, sf::Vector2f(400, 300));
    Object Trap(ObjectType::Type_Trap, sf::Vector2f(430, 300));

    Level m_Level;

    sf::Font* UIElementFont = new sf::Font;
    if (!UIElementFont->loadFromFile("Resources/Fonts/Inkfree.ttf"))
        std::cout << "Error loading file" << std::endl;

    std::vector <UIElement> UIElements;
    for (int i = 0; i < 3; i++)
    {
        UIElement newElement(sf::Vector2f(50, 50 + (i * 55)), sf::Vector2f(100, 50), std::string("Button " + std::to_string(i + 1)), UIElementFont);
        UIElements.push_back(newElement);
    }

    while (Window.isOpen())
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Window.close();
            }
        }

        // Options window event loop
        sf::Event OptionsEvent;
        while (OptionsWindow.pollEvent(OptionsEvent))
        {
	        if (OptionsEvent.type == sf::Event::Closed)
	        {
	        	// Closes on X click - sometimes modified for close confirmation
                OptionsWindow.close();
	        }

            // This is useful for stamping
            if (OptionsEvent.type == sf::Event::MouseButtonPressed)
            {
	            if (OptionsEvent.mouseButton.button == sf::Mouse::Left)
	            {
		            for (int i = 0; i < UIElements.size(); i++)
		            {
                        if (UIElements[i].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                        {
                            UIElements[i].ButtonReact();
                        }
		            }
	            }
            }
        }

        Player.Input();
        MainCamera.CameraMove();

        if (Player.m_ObjShape.getGlobalBounds().intersects(Trap.m_ObjShape.getGlobalBounds()))
        {
            Window.close();
        }

        if (sf::Mouse::isButtonPressed((sf::Mouse::Left)))
        {
            m_Level.PlaceObject(&Window);
        }

        // Set view
        Window.setView(MainCamera.m_CameraView);


        // Main window render loop
        Window.clear();
        Window.draw(Player.m_ObjShape);
        Window.draw(Trap.m_ObjShape);

        for (int i = 0; i < m_Level.m_LevelObjects.size(); i++)
        {
            Window.draw(m_Level.m_LevelObjects[i]->m_ObjShape);
        }

        Window.display();
        //

        // Options window render loop
        OptionsWindow.clear(sf::Color::Blue); // Sets window colour

        for (int i = 0; i < UIElements.size(); i++)
        {
            UIElements[i].Draw(&OptionsWindow);
        }

        OptionsWindow.display();
        //
    }

    return 0;
}