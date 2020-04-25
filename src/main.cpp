#include <iostream>
#include "SDD/type_atomiques.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {

    echantillon mon_echantillon = charge_echantillon("../data/POSNVIT.dat", 100);

    // region sfml

    sf::RenderWindow window(sf::VideoMode(200, 200), "model H20 -- eva mocchetti");


    sf::CircleShape shape(20.0f);
    shape.setOrigin(20, 20);
    double x = 0, y = 0.0;
    // shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // maj
        shape.setPosition(x, y);
        x += 0.1;

        // affichage
        window.clear();

        window.draw(shape);

        window.display();
    }

    // endregion

    supprime_echantillon(mon_echantillon);

    return 0;
}