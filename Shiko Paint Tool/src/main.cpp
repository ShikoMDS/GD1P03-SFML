#include "GUI/Level.h"

// ALWAYS BUILD IN RELEASE AT LEAST ONCE A DAY

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    Object Player(ObjectType::Type_Player, sf::Vector2f(400, 300));

    Object Trap(ObjectType::Type_Trap, sf::Vector2f(430, 300));

    window.setFramerateLimit(60); // Sets to 60 fps
    //window.setVerticalSyncEnabled(true); // NOT RECOMMENDED - Sets to monitor refresh rate

    Level m_Level;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        Player.Input();

        if (Player.m_ObjShape.getGlobalBounds().intersects(Trap.m_ObjShape.getGlobalBounds()))
        {
            window.close();
        }

        if (sf::Mouse::isButtonPressed((sf::Mouse::Left)))
        {
            m_Level.PlaceObject(&window);
        }

        window.clear();

        window.draw(Player.m_ObjShape);
        window.draw(Trap.m_ObjShape);

        for (int i = 0; i < m_Level.m_LevelObjects.size(); i++)
        {
            window.draw(m_Level.m_LevelObjects[i]->m_ObjShape);
        }

        window.display();
    }

    return 0;
}