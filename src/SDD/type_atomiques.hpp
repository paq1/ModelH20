#ifndef MODELH2O_TYPE_ATOMIQUES_HPP
#define MODELH2O_TYPE_ATOMIQUES_HPP

#define RAYON_OXYGENE 15
#define RAYON_HYDROGENE 10

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

// region split

struct tab_string {
    std::string* tab;
    int taille;
};

std::string* copie_tab(std::string* tab, int taille);

void add_mot(tab_string& tab, std::string mot);

tab_string split(std::string chaine, char separateur);

void affiche_tab_string(tab_string tab);

void delete_tab_string(tab_string& tab);
// endregion

// region vecteur3d

struct vecteur3d {
    double x, y, z;
};


vecteur3d cons_v3d_zero();
vecteur3d cons_v3d(double x, double y, double z);

std::string v3d_to_string(vecteur3d v);

void affiche_v3d(vecteur3d v);

double norme_v3d(vecteur3d v);

// endregion

// region atome

struct atome {
    vecteur3d pos;
    std::string type;
    double rayon;
};

atome cons_atome(vecteur3d v, std::string type, double rayon);
// atome cons_copie_atome(atome a);

std::string atome_to_string(atome a);

void affiche_atome(atome a);

// endregion

// region molecule

struct molecule {
    int taille;
    atome* atomes;
};

molecule cons_molecule(int taille, atome* atomes);
std::string molecule_to_string(molecule mol);

void affiche_molecule(molecule mol);

/////////////////
// suppression //
/////////////////
void supprimer_molecule(molecule* mol);

bool est_dans_rayon(vecteur3d centre, double rayon, molecule mol);
// endregion

// region chargement atome fichier

atome charge_un_atome(std::ifstream& fichier, std::string type, double rayon);

// endregion

// region chargement molecule fichier

molecule charge_une_molecule(std::ifstream& fichier);

// endregion

// region echantillon

struct echantillon {
    molecule* lst;
    int taille;
};

echantillon cons_vide();

echantillon charge_echantillon(std::string file_name, int nb_iteration);

void supprime_echantillon(echantillon& ech);
// endregion

#endif //MODELH2O_TYPE_ATOMIQUES_HPP