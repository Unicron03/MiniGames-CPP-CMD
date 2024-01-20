#include <iostream>
#include <conio.h> // Pour _getch()
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <locale>

#include "files/pfc.cpp"
#include "files/pendu.cpp"
#include "files/morpion.cpp"
#include "files/mastermind.cpp"
#include "files/puissance4.cpp"
#include "files/quizz.cpp"
#include "files/cebon.cpp"
#include "files/speed.cpp"
#include "files/devinePets.cpp"
#include "files/perudo.cpp"
#include "files/sabacc.cpp"
#include "files/awale.cpp"

using namespace std;

// Fonction pour afficher une bordure horizontale
void afficherBordureHorizontale(int largeur) {
    for (int i = 0; i < largeur; i++) {
        cout << "-";
    }
    cout << endl;
}

void affJeux(string & choix) {
    // Options de jeux avec des bordures
    string jeux[] = { "Le pierre/feuille/ciseaux ('pfc')", "Le morpion", "Le pendu", "Le mastermind", "Le puissance4", "Le quizz", "Le compte est bon ('ceb')", "Test de rapidité ('speed')", "Devine Pets ('pets')", "Le perudo", "Le sabacc", "L'awale", "L'arrêt du programme ('arret')" };
    int nombreJeux = sizeof(jeux) / sizeof(jeux[0]);

    for (int i = 0; i < nombreJeux; i++) {
        // Afficher une bordure horizontale avant chaque option de jeu
        afficherBordureHorizontale(jeux[i].length() + 4);  // +4 pour les espaces de chaque côté

        // Afficher l'option de jeu avec une bordure de chaque côté
        cout<<"| "<<jeux[i]<<" |"<<endl;
    }

    // Afficher une bordure horizontale en bas du menu
    afficherBordureHorizontale(jeux[0].length() + 4);

    cout<<"A quel jeu voulez-vous jouer ? ";
    cin>>choix;
}

string gameChoice() {
    string choix = "";
    bool choixValid = false;

    affJeux(choix);

    while (choixValid == false) {
        if (choix == "pfc") {
            Pfc::pfcGame();
            choixValid = true;
        } else if (choix == "morpion") {
            Morpion::morpionGame();
            choixValid = true;
        } else if (choix == "pendu") {
            Pendu::penduGame();
            choixValid = true;
        } else if (choix == "mastermind") {
            MasterMind::msMGame();
            choixValid = true;
        } else if (choix == "puissance4") {
            Puissance4::puissance4Game();
            choixValid = true;
        } else if (choix == "quizz") {
            Quizz::quizzGame();
            choixValid = true;
        } else if (choix == "ceb") {
            CEBon::cebonGame();
            choixValid = true;
        } else if (choix == "speed") {
            Speed::speedGame();
            choixValid = true;
        } else if (choix == "pets") {
            DevinePets::petsGame();
            choixValid = true;
        } else if (choix == "perudo") {
            Perudo::perudoGame();
            choixValid = true;
        } else if (choix == "sabacc") {
            jeuSabacc::JeuSabacc();
            choixValid = true;
        } else if (choix == "awale") {
            Awale::awaleGame();
            choixValid = true;
        } else if (choix == "arret") {
            cout<<"\nMerci d'avoir joué, à bientôt !\n"<<endl;
            return 0;
            choixValid = true;
        } else {
            system("clear");
            cout<<"Vous devez saisir 'pfc', 'morpion', 'pendu', 'mastermind', 'puissance4', 'quizz', 'ceb', 'speed', 'pets', 'perudo', 'sabacc', 'awale' ou 'arret' !"<<endl;
            cout<<endl;
            affJeux(choix);
        }
    }

    cout<<(gameChoice())<<endl;
}

int main() {
    // Test appui bouton mais ne fonctionne que sous powershell
    // while(true)
    // {
    //     // printf("Press any key to continue…");
    //     if(getch()){
    //         cout<<"testing"<<endl;
    //     }
    // }
    
    system("clear");
    cout<<(gameChoice())<<endl;

    return 0;
}