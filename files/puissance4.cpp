#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>

using namespace std;

class Puissance4 {
public:
    static void puissance4Game() {
        system("clear");
        affTitle();
        affRegles();

        cout<<endl;
        leadRead();
        cout<<endl;

        const int lignes = 6;
        const int colonnes = 7;
        char plateau[lignes][colonnes];
        resetPlateau(plateau, lignes, colonnes);

        string pseudo1 = "", pseudo2 = "";
        inputPseudo(pseudo1, "X");
        inputPseudo(pseudo2, "O");

        system("clear");

        char joueur = 'X';
        char joueurStart = joueur;

        bool jeuFini = false;
        int nbCoups = 0, winJX = 0, winJO = 0;

        while (!jeuFini) {
            affPlateau(plateau, lignes, colonnes);

            int colonne;
            inputColonne(joueur, colonnes, colonne);
            system("clear");

            if (colonne >= 0 && colonne < colonnes && estColonneValide(plateau, colonne, lignes)) {
                int ligne = trouverDerniereLigne(plateau, colonne, lignes);
                plateau[ligne][colonne] = joueur;
                nbCoups++;

                if (estVictoire(plateau, joueur, lignes, colonnes, ligne, colonne) || nbCoups == lignes * colonnes) {
                    system("clear");
                    affPlateau(plateau, lignes, colonnes);
                    if (estVictoire(plateau, joueur, lignes, colonnes, ligne, colonne)) {
                        system("clear");
                        if(joueur=='X') {
                            winJX++;
                            if(winJX==3) {
                                cout<<"Le joueur X ("<<pseudo1<<") à gagné avec 3 victoires contre "<<winJO<<" pour O ("<<pseudo2<<") !"<<endl;
                                leadWrite(pseudo1, 1);
                                leadWrite(pseudo2, 0);
                                jeuFini = true;
                            } else {
                                system("clear");
                                cout<<"Le joueur X ("<<pseudo1<<") à gagné cette manche ! Les scores sont de "<<winJX<<" pour X ("<<pseudo1<<") et "<<winJO<<" pour O ("<<pseudo2<<") !"<<endl;
                                cout<<"Nouvelle manche !"<<endl;
                                cout<<endl;
                                resetPlateau(plateau, lignes, colonnes);
                                switchJoueurs(joueurStart, joueur, nbCoups);
                            }
                        } else {
                            winJO++;
                            if(winJO==3) {
                                cout<<"Le joueur O ("<<pseudo2<<") à gagné avec 3 victoires contre "<<winJX<<" pour X ("<<pseudo1<<") !"<<endl;
                                leadWrite(pseudo2, 1);                                
                                leadWrite(pseudo1, 0);
                                jeuFini = true;
                            } else {
                                system("clear");
                                cout<<"Le joueur O ("<<pseudo2<<") à gagné cette manche ! Les scores sont de "<<winJO<<" pour O ("<<pseudo2<<") et "<<winJX<<" pour X ("<<pseudo1<<") !"<<endl;
                                cout<<"Nouvelle manche !"<<endl;
                                cout<<endl;
                                resetPlateau(plateau, lignes, colonnes);
                                switchJoueurs(joueurStart, joueur, nbCoups);
                            }
                        }
                    } else {
                        cout<<"Match nul !" <<endl;
                    }
                    nbCoups = 0;
                } else {
                    joueur = (joueur == 'X') ? 'O' : 'X'; // Changer de joueur
                }
            } else {
                system("clear");
                if(colonne>=0 && colonne<colonnes) {
                    cout<<"Colonne pleine ! Choisissez une autre colonne.\n"<<endl;
                } else {
                    cout<<"Colonne invalide. Veuillez choisir une autre colonne.\n"<<endl;
                }
            }
        }
        cout<<endl;
        leadRead();
    }

private:
    static void inputPseudo(string & pseudo, string signe) {
        cout<<"Joueur "<<signe<<", saisissez votre pseudo : ";
        cin>>pseudo;
    }

    static void inputColonne(char joueur, const int colonnes, int & colonne) {
        cout<<"Joueur "<<joueur <<", entrez la colonne (0-" <<colonnes - 1 <<") où vous voulez jouer : ";
        cin>>colonne;

        // Tentative pour éviter boucle infinis si joueur rentre autre chose qu'un entier
        // while(typeid(colonne).name() != typeid(0).name()) {
        //     cout<<"Saisi invalide. Reessayer en inscrivant un entier entre 0 et "<<colonnes<<"."<<endl;
        //     inputColonne(joueur, colonnes, colonne);
        // }
    }

    static void resetPlateau(char plateau[][7], int lignes, int colonnes) {
        for (int i = 0; i < lignes; i++) {
            for (int j = 0; j < colonnes; j++) {
                plateau[i][j] = ' ';
            }
        }
    }

    static void affPlateau(char plateau[][7], int lignes, int colonnes) {        
        // Afficher les indices des colonnes en haut
        for (int j = 0; j < colonnes; j++) {
            cout<<"  " <<j <<" ";
        }
        cout<<endl;

        // Afficher le plateau
        for (int i = 0; i < lignes; i++) {
            cout<<"|";
            for (int j = 0; j < colonnes; j++) {
                cout<<" " <<plateau[i][j] <<" |";
            }
            cout<<endl;

            if (i < lignes - 1) {
                for (int j = 0; j < colonnes; j++) {
                    cout<<"----";
                }
                cout<<"-" <<endl;
            }
        }
        cout<<endl;
    }

    static bool estColonneValide(char plateau[][7], int colonne, int lignes) {
        return plateau[0][colonne] == ' ';
    }

    static int trouverDerniereLigne(char plateau[][7], int colonne, int lignes) {
        for (int i = lignes - 1; i >= 0; i--) {
            if (plateau[i][colonne] == ' ') {
                return i;
            }
        }
        return -1; // La colonne est pleine
    }

    static void switchJoueurs(char & joueurStart, char & joueur, int & nbCoups) {
        nbCoups = 0;
        if(joueurStart=='X') {
            joueur = 'O';
        } else {
            joueur = 'X';
        }
        joueurStart = joueur;
    }

    static bool estVictoire(char plateau[][7], char joueur, int lignes, int colonnes, int ligne, int colonne) {
        // Vérifier la victoire horizontale
        int compte = 0;
        for (int j = 0; j < colonnes; j++) {
            if (plateau[ligne][j] == joueur) {
                compte++;
                if (compte == 4) {
                    return true;
                }
            } else {
                compte = 0;
            }
        }

        // Vérifier la victoire verticale
        compte = 0;
        for (int i = 0; i < lignes; i++) {
            if (plateau[i][colonne] == joueur) {
                compte++;
                if (compte == 4) {
                    return true;
                }
            } else {
                compte = 0;
            }
        }

        // Vérifier la victoire diagonale (de gauche à droite)
        compte = 0;
        int i = ligne, j = colonne;
        while (i < lignes && j < colonnes && plateau[i][j] == joueur) {
            compte++;
            i++;
            j++;
        }
        i = ligne - 1;
        j = colonne - 1;
        while (i >= 0 && j >= 0 && plateau[i][j] == joueur) {
            compte++;
            i--;
            j--;
        }
        if (compte >= 4) {
            return true;
        }

        // Vérifier la victoire diagonale (de droite à gauche)
        compte = 0;
        i = ligne, j = colonne;
        while (i < lignes && j >= 0 && plateau[i][j] == joueur) {
            compte++;
            i++;
            j--;
        }
        i = ligne - 1;
        j = colonne + 1;
        while (i >= 0 && j < colonnes && plateau[i][j] == joueur) {
            compte++;
            i--;
            j++;
        }
        if (compte >= 4) {
            return true;
        }

        return false; // Aucune victoire
    }

    static void leadWrite(const string & playerName, int score) {
        // Lire les données actuelles du leaderboard
        vector<pair<string, int>> leaderboardData = readLeaderboard();

        // Vérifier si le joueur existe déjà dans le leaderboard
        bool playerExists = false;
        for(auto& entry : leaderboardData) {
            if(entry.first == playerName) {
                // Le joueur existe, mettre à jour son score
                entry.second += score;
                playerExists = true;
                break;
            }
        }

        // Si le joueur n'existe pas, ajoutez-le au leaderboard
        if (!playerExists) {
            leaderboardData.push_back(make_pair(playerName, score));
        }

        // Écrire les données mises à jour dans le fichier
        ofstream leaderboardFile("text/leaderboard_puissance4.txt");
        if(leaderboardFile) {
            for(const auto& entry : leaderboardData) {
                leaderboardFile<<entry.first<<" "<<entry.second<<endl;
            }
            cout<<"Score mis à jour avec succès."<<endl;
        } else {
            cout<<"Une erreur s'est produite lors de l'ouverture du fichier."<<endl;
        }
    }

    static void leadRead() {
        vector<pair<string, int>> leaderboardData = readLeaderboard();

        cout << "\x1b[38;5;208mLEADERBOARD (victoires) : \x1b[0m" << endl;
        
        if (leaderboardData.empty()) {
            cout << "Aucunes données" << endl;
        } else {
            for (const auto& entry : leaderboardData) {
                cout << entry.first << " : " << entry.second << " victoires" << endl;
            }
        }
    }

    static vector<pair<string, int>> readLeaderboard() {
        vector<pair<string, int>> leaderboardData;
        ifstream leaderboardFile("text/leaderboard_puissance4.txt");

        if(leaderboardFile) {
            string line;
            while(getline(leaderboardFile, line)) {
                stringstream ss(line);
                string playerName;
                int score;
                if(ss>>playerName>>score) {
                    leaderboardData.push_back(make_pair(playerName, score));
                }
            }
        } else {
            cout<<"Une erreur s'est produite lors de l'ouverture du fichier."<<endl;
        }

        return leaderboardData;
    }

    static void affRegles() {
        cout<<"\n\x1b[31mVOICI LES REGLES :\x1b[0m"<<endl;
        cout<<"Le but du jeu est d'aligner 4 pions de la même couleur de manière horizontale, verticale ou diagonale avant votre adversaire."<<endl;
        cout<<"Il faut 3 manches pour gagner la partie !"<<endl;
    }

    static void affTitle() {
        cout<<endl;
        cout<<"  ____    _   _   ___   ____    ____       _      _   _    ____   _____     _  _   "<<endl;
        cout<<" |  _ \\  | | | | |_ _| / ___|  / ___|     / \\    | \\ | |  / ___| | ____|   | || | "<<endl;
        cout<<" | |_) | | | | |  | |  \\___ \\  \\___ \\    / _ \\   |  \\| | | |     |  _|     | || |_"<<endl;
        cout<<" |  __/  | |_| |  | |   ___) |  ___) |  / ___ \\  | |\\  | | |___  | |___    |__   _|"<<endl;
        cout<<" |_|      \\___/  |___| |____/  |____/  /_/   \\_\\ |_| \\_|  \\____| |_____|      |_|  "<<endl;
        cout<<endl;
    }
};