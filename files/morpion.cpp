#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Morpion {
public:
    static void morpionGame() {
        system("clear");
        affTitle();
        affRegles();

        cout<<endl;
        leadRead();
        cout<<endl;

        string pseudoJX = "", pseudoJO = "";
        pseudoJX = saisiPseudo("X");
        pseudoJO = saisiPseudo("O");

        int taille = saisiTailleBoard();

        vector<vector<char>> plateau(taille, vector<char>(taille, ' '));
        char joueur = 'X';
        char joueurStart = joueur;

        bool jeuFini = false;
        int nbCoups = 0, winJX = 0, winJO = 0;

        while(!jeuFini) {
            affPlateau(plateau);

            int ligne, colonne;
            saisiPos(joueur, taille, ligne, colonne);

            //Coup valide
            while(!checkCoupValid(plateau, taille, ligne, colonne)) {
                affPlateau(plateau);
                saisiPos(joueur, taille, ligne, colonne);
            }
            
            plateau[ligne][colonne] = joueur;
            nbCoups++;

            if(checkWin(plateau, joueur)) {
                affPlateau(plateau);
                if(joueur=='X') {
                    winJX++;
                    if(winJX==3) {
                        affWin(pseudoJX, 'X', winJO, pseudoJO);
                        leadWrite(pseudoJX, 1);
                        jeuFini = true;
                    } else {
                        affWinRound(pseudoJX, 'X', winJX, winJO, pseudoJO);
                    }
                } else {
                    winJO++;
                    if(winJO==3) {
                        affWin(pseudoJO, 'O', winJX, pseudoJX);
                        leadWrite(pseudoJO, 1);
                        jeuFini = true;
                    } else {
                        affWinRound(pseudoJO, 'O', winJO, winJX, pseudoJX);
                    }
                }
                resetPlateau(plateau);
                switchJoueurs(joueurStart, joueur, nbCoups);
            } else if(nbCoups==taille*taille) {
                affEgalite();
                resetPlateau(plateau);
                switchJoueurs(joueurStart, joueur, nbCoups);
            } else {
                if(joueur=='X') {
                    joueur='O';
                } else {
                    joueur='X';
                }
            }
        }

        cout<<endl;
        leadRead();
        cout<<endl;
    }

private:
    static bool checkCoupValid(const vector<vector<char>> & plateau, int taille, int ligne, int colonne) {
        if(ligne>=0 && ligne<taille && colonne>=0 && colonne<taille && plateau[ligne][colonne]==' ') {
            return true;
        } else {
            // system("clear");
            cout<<"Format non respecté ! Réessayez au format X X"<<endl;
            cout<<endl;
            return false;
        }
    }

    static void affEgalite() {
        system("clear");
        cout<<"Le plateau est complet, match nul !"<<endl;
        cout<<"Nouvelle manche !"<<endl;
        cout<<endl;
    }

    static void affWinRound(string pseudo, char signe, int win, int winOponent, string pseudoOponent) {
        char signeOponent = ' ';
        if(signe=='X') {signeOponent = 'O';}
        if(signe=='O') {signeOponent = 'X';}
        system("clear");
        cout<<"Le joueur "<<signe<<" ("<<pseudo<<") à gagné cette manche ! Les scores sont de "<<win<<" pour X ("<<pseudo<<") et "<<winOponent<<" pour O ("<<pseudoOponent<<")."<<endl;
        cout<<"Nouvelle manche !"<<endl;
        cout<<endl;
    }

    static void affWin(string pseudo, char signe, int winOponent, string pseudoOponent) {
        char signeOponent = ' ';
        if(signe=='X') {signeOponent = 'O';}
        if(signe=='O') {signeOponent = 'X';}
        cout<<"Le joueur "<<signe<<" ("<<pseudo<<") à gagné avec 3 victoires contre "<<winOponent<<" pour "<<signeOponent<<" ("<<pseudoOponent<<") !"<<endl;
    }

    static int saisiPos(char joueur, int taille, int & ligne, int & colonne) {
        cout<<"Joueur "<<joueur<<", entrez la ligne (0-"<<taille-1<<") et la colonne (0-"<<taille-1<<") où vous voulez jouer (Exemple 1 3) : ";
        cin>>ligne>>colonne;
        system("clear");
    }

    static int saisiTailleBoard() {
        int taille = 0;
        cout<<"\nSaisissez la taille du plateau (par exemple, 3 pour un plateau 3x3) : ";
        cin>>taille;

        while (taille<3) {
            cout << "La taille du plateau doit être d'au moins 3x3 !" << endl;
            cout << "Saisissez la taille du plateau : ";
            cin >> taille;
        }
        system("clear");

        return taille;
    }

    static string saisiPseudo(string signe) {
        string pseudo = "";
        cout<<"Joueur "<<signe<<", saisissez votre pseudo : ";
        cin>>pseudo;

        return pseudo;
    }

    static void affPlateau(const vector<vector<char>> & plateau) {
        int taille = plateau.size();

        // Afficher les indices des colonnes en haut
        cout<<"   ";
        for(int j=0; j<taille; j++) {
            cout<<" "<<j<<"  ";
        }
        cout<<endl;

        for(int i=0; i<taille; i++) {
            // Afficher l'indice de la ligne à gauche
            cout<<i<<" |";

            for(int j=0; j<taille; j++) {
                cout<<" "<<plateau[i][j]<<" |";
            }
            cout<<endl;

            if(i<taille-1) {
                cout<<"   ";
                for(int j=0; j<taille-1; j++) {
                    cout<<"----";
                }
                cout<<"---"<<endl;
            }
        }
        cout<<endl;
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

    static void resetPlateau(vector<vector<char>> & plateau) {
        int taille = plateau.size();
        for(int i=0; i<taille; i++) {
            for(int j=0; j<taille; j++) {
                plateau[i][j] = ' ';
            }
        }
    }

    // Fonction pour vérifier s'il y a un gagnant
    static bool checkWin(const vector<vector<char>> & tableau, char joueur) {
        int taille = tableau.size();

        // Vérification des lignes
        for(int i=0; i<taille; i++) {
            bool victoire = true;
            for(int j=0; j<taille; j++) {
                if(tableau[i][j] != joueur) {
                    victoire = false;
                    break;
                }
            }
            if(victoire) {
                return true;
            }
        }

        // Vérification des colonnes
        for(int j=0; j<taille; j++) {
            bool victoire = true;
            for(int i=0; i<taille; i++) {
                if(tableau[i][j] != joueur) {
                    victoire = false;
                    break;
                }
            }
            if(victoire) {
                return true;
            }
        }

        // Vérification de la diagonale principale
        bool victoireDiagonalePrincipale = true;
        for(int i=0; i<taille; i++) {
            if(tableau[i][i] != joueur) {
                victoireDiagonalePrincipale = false;
                break;
            }
        }
        if(victoireDiagonalePrincipale) {
            return true;
        }

        // Vérification de la diagonale opposée
        bool victoireDiagonaleOpposee = true;
        for(int i=0; i<taille; i++) {
            if(tableau[i][taille-1-i] != joueur) {
                victoireDiagonaleOpposee = false;
                break;
            }
        }
        if(victoireDiagonaleOpposee) {
            return true;
        }

        return false;
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
        ofstream leaderboardFile("text/leaderboard_morpion.txt");
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
        ifstream leaderboardFile("text/leaderboard_morpion.txt");

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
        cout<<"Les joueurs inscrivent tour à tour leur symbole sur un plateau dont la limite sera choisi par les joueurs."<<endl;
        cout<<"Le premier qui parvient à aligner trois de ses symboles horizontalement, verticalement ou en diagonale gagne un point."<<endl;
        cout<<"Le premier à inscrire 3 points gagne !"<<endl;
    }

    static void affTitle() {
        cout<<endl;
        cout<<"  __  __    ___    ____    ____    ___    ___    _   _ "<<endl;
        cout<<" |  \\/  |  / _ \\  |  _ \\  |  _ \\  |_ _|  / _ \\  | \\ | |"<<endl;
        cout<<" | |\\/| | | | | | | |_) | | |_) |  | |  | | | | |  \\| |"<<endl;
        cout<<" | |  | | | |_| | |  _ <  |  __/   | |  | |_| | | |\\  |"<<endl;
        cout<<" |_|  |_|  \\___/  |_| \\_\\ |_|     |___|  \\___/  |_| \\_|"<<endl;
        cout<<endl;
    }
};