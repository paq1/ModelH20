#include "type_atomiques.hpp"

// region split

std::string* copie_tab(std::string* tab, int taille) {
    std::string* res = new std::string[taille];

    for (int i = 0; i < taille; i++) {
        res[i] = tab[i];
    }

    return res;
}
void add_mot(tab_string& tab, std::string mot) {
    if (!mot.empty()) {
        // etape 1 : on recopie l'ancien tableau
        //           dans temp
        std::string *temp = nullptr;
        if (tab.tab != nullptr) {
            temp = copie_tab(tab.tab, tab.taille);
        } else {
            // le tableau est vide
        }

        // etape 2 : on supprime tab
        if (tab.tab != nullptr) {
            delete [] tab.tab;
            tab.tab = nullptr;
        }

        // etape 3 : on incremente la taille de res.tab
        tab.taille++;
        tab.tab = new std::string[tab.taille];

        // etape 4 : on remplace par temp + mot
        if (temp != nullptr) {
            for (int j = 0; j < tab.taille - 1; j++) {
                tab.tab[j] = temp[j];
            }
        }
        delete [] temp;
        tab.tab[tab.taille - 1] = mot;

        // mot = "";
    }
}
tab_string split(std::string chaine, char separateur) {
    tab_string res;
    // on l'intialise a vide
    res.tab = nullptr; res.taille = 0;

    int taille_chaine = chaine.length();
    std::string mot = "";

    for (int i = 0; i < taille_chaine; i++) {
        char caractere_courant = chaine[i];

        if (caractere_courant != separateur) {
            mot += caractere_courant;
        } else {
            add_mot(res, mot);
            mot = "";
        }
    }

    if (!mot.empty()) {
        add_mot(res, mot);
    }

    return res;
}

void affiche_tab_string(tab_string tab) {
    for (int i = 0; i < tab.taille; i++) {
        std::cout << "element " << i << " : "
                  << tab.tab[i] << std::endl;
    }
}

void delete_tab_string(tab_string& tab) {
    delete tab.tab;
    tab.tab = nullptr;
}
// endregion

// region vecteur3d

vecteur3d cons_v3d_zero() {
    vecteur3d res;

    res.x = 0.0;
    res.y = 0.0;
    res.z = 0.0;

    return res;
}
vecteur3d cons_v3d(double x, double y, double z) {
    vecteur3d res;

    res.x = x;
    res.y = y;
    res.z = z;

    return res;
}

std::string v3d_to_string(vecteur3d v) {
    std::string str = "";

    str +=  "("  + std::to_string(v.x) +
            ", " + std::to_string(v.y) +
            ", " + std::to_string(v.z) +
            ")";

    return str;
}

void affiche_v3d(vecteur3d v) {
    std::cout << v3d_to_string(v) << std::endl;
}

double norme_v3d(vecteur3d v){
    return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
// endregion

// region atome

atome cons_atome(vecteur3d v, std::string type, double rayon) {
    atome resultat;

    resultat.pos = v;
    resultat.type = type;
    resultat.rayon = rayon;

    return resultat;
}

std::string atome_to_string(atome a) {
    std::string str = "";

    str +=  "pos : " + v3d_to_string(a.pos) +
            ", type : " + a.type +
            ", rayon : " + std::to_string(a.rayon);

    return str;
}

void affiche_atome(atome a) {
    std::cout << atome_to_string(a) << std::endl;
}

// endregion

// region molecule

molecule cons_molecule(int taille, atome* atomes) {
    // on copie les atomes
    molecule mol;

    mol.taille = taille;
    // on alloue la mémoire
    mol.atomes = new atome[mol.taille];
    // on recopie ce qu'il y a dans atomes
    for (int i = 0; i < taille; i++) {
        // todo verifier que c ok
        mol.atomes[i] = atomes[i];
    }

    return mol;
}

std::string molecule_to_string(molecule mol) {
    std::string str = "";

    // on affiche le nombre d'atomes
    str += "molecule de taille : " + std::to_string(mol.taille)
        +  "\n";

    for (int i = 0; i < mol.taille; i++) {
        str += "atome num : " + std::to_string(i + 1)
            +  " : " + atome_to_string(mol.atomes[i]) + "\n";
    }

    return str;
}

void affiche_molecule(molecule mol) {
    std::cout << molecule_to_string(mol) << std::endl;
}

void supprimer_molecule(molecule* mol) {
    delete [] mol->atomes;
    mol->atomes = nullptr;
}

bool est_dans_rayon(vecteur3d centre, double rayon, molecule mol){
    vecteur3d vec = cons_v3d(mol.atomes[0].pos.x - centre.x,
                             mol.atomes[0].pos.y - centre.y,
                             mol.atomes[0].pos.z - centre.z);
    double norme = norme_v3d(vec);
    return norme < rayon;
}
// endregion

// region chargement atome fichier

atome charge_un_atome(std::ifstream& fichier, std::string type, double rayon) {
    atome a;
    // on suppose que le fichier existe.

    // on recupere une ligne du fichier
    std::string ligne_atome;
    std::getline(fichier, ligne_atome);


    // a ce niveau on a :
    // ligne_atome = "0.989.. 0.6... 0.080 0.989.. 0.6... 0.080"
    // on veut decoupere cette ligne avec les separateur espace
    tab_string mots_ligne = split(ligne_atome, ' ');
    // on recupere les trois premier mot (x y z)
    double  x = std::stod(mots_ligne.tab[0]),
            y = std::stod(mots_ligne.tab[1]),
            z = std::stod(mots_ligne.tab[2]);
    vecteur3d vecteur = cons_v3d(x, y, z);

    a = cons_atome(vecteur, type, rayon);

    return a;
}

// endregion

// region chargement molecule fichier

molecule charge_une_molecule(std::ifstream& fichier) {
    molecule mol;

    atome atomes[3];

    atomes[0] = charge_un_atome(fichier, "O", RAYON_OXYGENE);
    atomes[1] = charge_un_atome(fichier, "H", RAYON_HYDROGENE);
    atomes[2] = charge_un_atome(fichier, "H", RAYON_HYDROGENE);

    mol = cons_molecule(3, atomes);

    return mol;
}

// endregion

// region echantillon

echantillon cons_vide(){
    echantillon ech;
    ech.lst = nullptr;
    ech.taille = 0;
    return ech;
}

void add_echantillon(echantillon& ech, molecule mol){
    molecule* new_lst = new molecule[ech.taille + 1];
    if (ech.taille != 0){
        for (int i = 0; i < ech.taille; i++){
            // new_lst[i] = cons_molecule(ech.lst[i].taille,
            //                           ech.lst[i].atomes);
            // supprimer_molecule(&ech.lst[i]);
            new_lst[i] = ech.lst[i];
        }
    }
    new_lst[ech.taille] = cons_molecule(mol.taille, mol.atomes);

    ech.taille += 1;
    if (ech.lst != nullptr) delete [] ech.lst;
    ech.lst = new_lst;
}

echantillon charge_echantillon(std::string file_name, int nb_iteration){
    echantillon res = cons_vide();
    std::ifstream fichier(file_name, std::ios::in);
    if (fichier.is_open()){
        std::string ligne = "";
        while(!fichier.eof()){
            add_echantillon(res, charge_une_molecule(fichier));
        }
    }
    return res;
}

void supprime_echantillon(echantillon& ech) {
    for (int i = 0; i < ech.taille; i++) {
        supprimer_molecule(&ech.lst[i]);
    }

    delete [] ech.lst;
    ech.lst = nullptr;
}

// endregion