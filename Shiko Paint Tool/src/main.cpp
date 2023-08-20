#include <iostream>

#include "GUI/Level.h"
#include "GUI/UIElement.h"
#include "GUI/Camera.h"
#include "Utensils/CanvasManager.h"
#include "Utensils/FileManager.h"

// ALWAYS BUILD IN RELEASE AT LEAST ONCE A DAY

int main()
{
    sf::Color ColourPickerColour;


    // Main window creation
    sf::RenderWindow Window(sf::VideoMode(800, 600), "SFML works!");
    Window.setFramerateLimit(60); // Sets to 60 fps

    FileManager g_FileManager(Window.getSystemHandle());

	// Secondary window creation
    sf::RenderWindow OptionsWindow(sf::VideoMode(400, 400), "Options Window");
    OptionsWindow.setVerticalSyncEnabled(true); // Sets to monitor refresh rate

    sf::RectangleShape OptionsShape;
    OptionsShape.setSize(sf::Vector2f(OptionsWindow.getSize().x, OptionsWindow.getSize().y));
    sf::Texture OptionsTexture;
    OptionsTexture.loadFromFile("Resources/Images/Colours.png");
    if (!OptionsTexture.loadFromFile("Resources/Images/Colours.png"))
    {
        std::cout << "Failed to load colour selection tool!" << std::endl;
    }

    OptionsShape.setTexture(&OptionsTexture);

    sf::Image ColourPickerImage;
    ColourPickerImage.loadFromFile("Resources/Images/Colours.png");
    //

    Camera MainCamera(sf::Vector2f(Window.getSize().x / 2, Window.getSize().y / 2), sf::Vector2f(Window.getSize().x, Window.getSize().y));
    Object Player(ObjectType::Type_Player, sf::Vector2f(400, 300));
    Object Trap(ObjectType::Type_Trap, sf::Vector2f(430, 300));

    Level m_Level;

    // Canvas stuff
    sf::RenderTexture* g_Canvas = new sf::RenderTexture();
    g_Canvas->create(Window.getSize().x, Window.getSize().y);
    g_Canvas->clear(sf::Color::White);

    sf::RectangleShape g_CanvasObject;
    g_CanvasObject.setSize(sf::Vector2f(Window.getSize().x, Window.getSize().y));
    g_CanvasObject.setTexture(&g_Canvas->getTexture());
    //

    // Canvas manager init
    CanvasManager g_CanvasManager(g_Canvas, &Window);
    //

    // Delta time stuff
    float DeltaTime = 0.0f;
    sf::Time CurrentTime;
    sf::Clock DeltaClock;

    //

    sf::Font* UIElementFont = new sf::Font;
    if (!UIElementFont->loadFromFile("Resources/Fonts/Inkfree.ttf"))
    {
        std::cout << "Error loading file" << std::endl;
    }

    std::vector <UIElement> UIElements;
    // for (int i = 0; i < 3; i++)
    // {
    //     UIElement NewElement(sf::Vector2f(50, 50 + (i * 55)), sf::Vector2f(100, 50), std::string("Button " + std::to_string(i + 1)), UIElementFont);
    //     UIElements.push_back(NewElement);
    // }

    while (Window.isOpen())
    {
        CurrentTime = DeltaClock.restart();
        DeltaTime = CurrentTime.asSeconds();

        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                g_CanvasManager.InitShape();
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                g_CanvasManager.EndDraw();
            }

            if (event.type == sf::Event::KeyPressed)
            {
	            if (event.key.code == sf::Keyboard::F5)
	            {
                    // Saving
                    g_Canvas->getTexture().copyToImage().saveToFile(g_FileManager.SaveFile() += ".png");
	            }

            	if (event.key.code == sf::Keyboard::F9)
	            {
                    // Loading
                    sf::Texture NewTexture;
                    NewTexture.loadFromFile(g_FileManager.OpenFile());

                    sf::RectangleShape NewShape;
                    NewShape.setSize(sf::Vector2f(NewTexture.getSize().x, NewTexture.getSize().y));
                    NewShape.setTexture(&NewTexture);

                    g_Canvas->draw(NewShape);
	            }
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
                    ColourPickerColour = ColourPickerImage.getPixel(sf::Mouse::getPosition(OptionsWindow).x, sf::Mouse::getPosition(OptionsWindow).y);

                    g_CanvasManager.UpdateColour(ColourPickerColour);
		            // for (int i = 0; i < UIElements.size(); i++)
		            // {
                    //     if (UIElements[i].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(OptionsWindow))))
                    //     {
                    //         UIElements[i].ButtonReact();/           }
		            // }
	            }
            }
        }

        Player.Input(DeltaTime);
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

        g_CanvasManager.SwapTool();
        g_Canvas->display();

        Window.draw(g_CanvasObject);

        g_CanvasManager.DrawUpdate();

        if (!g_CanvasManager.m_IsDrawing)
        {
            g_CanvasManager.ShapeCleanup();
        }

    	// Window.draw(Player.m_ObjShape);
        // Window.draw(Trap.m_ObjShape);
        //
        // for (int i = 0; i < m_Level.m_LevelObjects.size(); i++)
        // {
        //     Window.draw(m_Level.m_LevelObjects[i]->m_ObjShape);
        // }

        Window.display();
        //

        // Options window render loop
        OptionsWindow.clear(sf::Color::Blue); // Sets window colour

        // for (int i = 0; i < UIElements.size(); i++)
        // {
        //     UIElements[i].Draw(&OptionsWindow);
        // }

        OptionsWindow.draw(OptionsShape);

        OptionsWindow.display();
        //
    }

    return 0;
}