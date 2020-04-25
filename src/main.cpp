#include <iostream>
#include "SDD/type_atomiques.hpp"
#include <SFML/Graphics.hpp>
#include "SDD/viewer.hpp"
#include <cmath>

void draw_1_mol(const View_mol& vue_mol, sf::RenderWindow& window);


int main(int argc, char* argv[]) {

    const double height = 1000;
    const double width = 2000;
    const double z_near = 0.1;
    const double z_far = 1000.0;
    const double theta = 10.0;

    const double a = height / width;
    const double f = 1 / std::tan(theta*3.14159/180./2.);
    const double q = z_far / (z_far - z_near);

    // echantillon mon_echantillon = charge_echantillon("../data/POSNVIT.dat", 100);

    Matrix_4x4 projection_matrix;

    // Initialisation de la matrice de projection
    std::vector<std::vector<double>>& grid = projection_matrix.get_modif_grid();
    grid[0][0] = a*f;
    grid[1][1] = f;
    grid[2][2] = q;
    grid[3][2] = -z_near*q;
    grid[2][3] = 1;

    // Modèle d'entrée
    // Model_mol model_mol(mon_echantillon.lst[1]);
    // Vue
    // View_mol vue_mol(model_mol, projection_matrix);

    // region test
    vecteur3d   v1 = cons_v3d(0,0,0),
                v2 = cons_v3d(0,1,5),
                v3 = cons_v3d(1,1,0);
    atome       a1 = cons_atome(v1, "O", 15),
                a2 = cons_atome(v2, "H", 20),
                a3 = cons_atome(v3, "H", 20);
    atome* lst = new atome[3];
    lst[0] = a1;
    lst[1] = a2;
    lst[2] = a3;
    molecule mol_test = cons_molecule(3, lst);

    Model_mol testModelMol(mol_test);

    View_mol testViewMol(testModelMol, projection_matrix);

    testViewMol.get_vue_O()[0] += 1.0; testViewMol.get_vue_O()[1] += 1.0;
    testViewMol.get_vue_H1()[0] += 1.0; testViewMol.get_vue_H1()[1] += 1.0;
    testViewMol.get_vue_H2()[0] += 1.0; testViewMol.get_vue_H2()[1] += 1.0;

    double div(0.25);

    testViewMol.get_vue_O()[ 0] *= div * width;
    testViewMol.get_vue_O()[ 1] *= div * height;
    testViewMol.get_vue_H1()[0] *= div * width;
    testViewMol.get_vue_H1()[1] *= div * height;
    testViewMol.get_vue_H2()[0] *= div * width;
    testViewMol.get_vue_H2()[1] *= div * height;




    // endregion

    // region sfml

    sf::RenderWindow window(sf::VideoMode(width, height), "model H20 -- eva mocchetti");



    sf::CircleShape shape(20.0f);
    shape.setOrigin(20, 20);

    sf::Clock clock;

    double z(0.0);

    while (window.isOpen())
    {

        double dt = clock.getElapsedTime().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // maj
        z += 0.001 * dt;

        // region test
        vecteur3d   v1 = cons_v3d(0,0,0),
                v2 = cons_v3d(0,1,z),
                v3 = cons_v3d(1,1,0);
        atome       a1 = cons_atome(v1, "O", 15),
                a2 = cons_atome(v2, "H", 20),
                a3 = cons_atome(v3, "H", 20);
        atome* lst = new atome[3];
        lst[0] = a1;
        lst[1] = a2;
        lst[2] = a3;
        molecule mol_test = cons_molecule(3, lst);

        Model_mol testModelMol(mol_test);

        View_mol testViewMol(testModelMol, projection_matrix);

        testViewMol.get_vue_O()[0] += 1.0; testViewMol.get_vue_O()[1] += 1.0;
        testViewMol.get_vue_H1()[0] += 1.0; testViewMol.get_vue_H1()[1] += 1.0;
        testViewMol.get_vue_H2()[0] += 1.0; testViewMol.get_vue_H2()[1] += 1.0;

        double div(0.25);

        testViewMol.get_vue_O()[ 0] *= div * width;
        testViewMol.get_vue_O()[ 1] *= div * height;
        testViewMol.get_vue_H1()[0] *= div * width;
        testViewMol.get_vue_H1()[1] *= div * height;
        testViewMol.get_vue_H2()[0] *= div * width;
        testViewMol.get_vue_H2()[1] *= div * height;


        // affichage
        window.clear();

        // draw_1_mol(vue_mol, window);
        draw_1_mol(testViewMol, window);
        // window.draw(shape);

        window.display();
    }

    // endregion

    // supprime_echantillon(mon_echantillon);

    return 0;
}

void draw_1_mol(const View_mol& vue_mol, sf::RenderWindow& window){
    sf::Vertex ligne_OH1[] =
    {
        sf::Vertex(sf::Vector2f(vue_mol.get_vue_O()[0], vue_mol.get_vue_O()[1])),
        sf::Vertex(sf::Vector2f(vue_mol.get_vue_H1()[0], vue_mol.get_vue_H1()[1]))
    };

    window.draw(ligne_OH1, 2, sf::Lines);

    sf::Vertex ligne_OH2[] =
    {
            sf::Vertex(sf::Vector2f(vue_mol.get_vue_O()[0], vue_mol.get_vue_O()[1])),
            sf::Vertex(sf::Vector2f(vue_mol.get_vue_H2()[0], vue_mol.get_vue_H2()[1]))
    };

    window.draw(ligne_OH2, 2, sf::Lines);

    sf::Vertex ligne_H1H2[] =
    {
            sf::Vertex(sf::Vector2f(vue_mol.get_vue_H2()[0], vue_mol.get_vue_H2()[1])),
            sf::Vertex(sf::Vector2f(vue_mol.get_vue_H1()[0], vue_mol.get_vue_H1()[1]))
    };

    window.draw(ligne_H1H2, 2, sf::Lines);
}
