#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

class DevinePets {
public:
    static void petsGame() {
        system("clear");
        affTitle();
        affRegles();

        cout<<endl;
        leadRead();
        cout<<endl;

        vector<vector<string>> tab(3, vector<string>(3));
        vector<vector<bool>> tab2(3, vector<bool>(3));
        string choix = "";
        string pseudo = saisiPseudo();
        system("clear");
        int nbTry = 0;
        incTabAnimals(tab);
        affTab(tab, tab2);

        while(!testWin(tab2)) {
            cout<<"\nSaisisser un animal : ";
            cin>>choix;
            nbTry++;

            system("clear");
            choixValid(tab, tab2, choix);
            affTab(tab, tab2);
        }
        cout<<"\nBRAVO, VOUS AVEZ GAGNE ! Il vous a fallu "<<nbTry<<" essais pour gagner !"<<endl;;

        leadWrite(pseudo, nbTry);
        cout<<endl;
        leadRead();
        cout<<endl;
    }

private:
    static string saisiPseudo() {
        string pseudo = "";
        cout<<"Saisissez votre pseudo : ";
        cin>>pseudo;

        return pseudo;
    }

    static void incTabAnimals(vector<vector<string>> & tab) {
        tab[0][0] = "chat"; tab[0][1] = "chien"; tab[0][2] = "tortue"; 
        tab[1][0] = "canard"; tab[1][1] = "rhinocéros"; tab[1][2] = "serpent";
        tab[2][0] = "abeille"; tab[2][1] = "lion"; tab[2][2] = "crabe";
    }

    static void affTab(vector<vector<string>> & tab, vector<vector<bool>> & tab2) {
        cout<<"AFFICHAGE TABLEAU : "<<endl;
        for(int i=0; i<tab.size(); i++) {
            for(int j=0; j<tab.size(); j++) {
                if(tab2[i][j]) {
                    cout<<tab[i][j]<<" | ";
                } else {
                    cout<<" | ";
                }
            }
            cout<<endl;
        }
    }

    static bool testWin2(vector<vector<bool>> & tab2) {
        for(int i=0; i<tab2.size(); i++) {
            for(int j=0; j<tab2.size(); j++) {
                if(!tab2[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    static bool testWin(vector<vector<bool>> & tab2) {
        for(int i=0; i<tab2.size(); i++) {
            vector<bool> temp(3);
            for(int j=0; j<tab2.size(); j++) {
                temp[j] = tab2[i][j];
            }
            if(temp[0] && temp[1] && temp[2]) {
                return true;
            }
        }

        for(int j=0; j<tab2.size(); j++) {
            vector<bool> temp(3);
            for(int i=0; i<tab2.size(); i++) {
                temp[i] = tab2[i][j];
            }
            if(temp[0] && temp[1] && temp[2]) {
                return true;
            }
        }

        return false;
    }

    static void choixValid(vector<vector<string>> & tab, vector<vector<bool>> & tab2, string choix) {
        bool choixOk = false;

        for(int i=0; i<tab.size(); i++) {
            for(int j=0; j<tab.size(); j++) {
                if(choix==tab[i][j]) {
                    tab2[i][j] = true;
                    choixOk = true;
                }
            }
        }

        if(choixOk){
            cout<<"Le mot "<<choix<<" est valide !"<<endl<<endl;
        } else {
            cout<<"Le mot "<<choix<<" n'est pas valide !"<<endl<<endl;
        }
    }

    static void leadWrite(const string & playerName, int nbTry) {
        // Lire les données actuelles du leaderboard
        vector<pair<string, int>> leaderboardData = readLeaderboard();

        // Vérifier si le joueur existe déjà dans le leaderboard
        bool playerExists = false;
        for(auto& entry : leaderboardData) {
            if(entry.first == playerName) {
                // Le joueur existe, mettre à jour sa moyenne
                if(nbTry < entry.second) {
                    entry.second = nbTry;
                }
                playerExists = true;
                break;
            }
        }

        // Si le joueur n'existe pas, ajoutez-le au leaderboard
        if (!playerExists) {
            leaderboardData.push_back(make_pair(playerName, nbTry));
        }

        // Écrire les données mises à jour dans le fichier
        ofstream leaderboardFile("text/leaderboard_pets.txt");
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
        vector<pair<string, int>> leaderboardData = readLeaderboard();  // Utilisez double pour la moyenne

        cout << "\x1b[38;5;208mLEADERBOARD (records) : \x1b[0m" << endl;
        
        if (leaderboardData.empty()) {
            cout << "Aucunes données" << endl;
        } else {
            for (const auto& entry : leaderboardData) {
                cout << entry.first << " : " << entry.second << " essais" << endl;
            }
        }
    }

    static vector<pair<string, int>> readLeaderboard() {
        vector<pair<string, int>> leaderboardData;
        ifstream leaderboardFile("text/leaderboard_pets.txt");

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
        cout<<"Le joueur doit saisir des noms d'animaux (certain comporte des accents)."<<endl;
        cout<<"Si le mot saisi fait partit du tableau, le mot apparaît à l'endroit du tableau où il se trouve."<<endl;
        cout<<"Le joueur gagne quand il arrive à créer une ligne ou une colonne complète d'animaux !"<<endl;
    }

    static void affTitle() {
        cout<<endl;
        cout<<"  ____    _____  __     __  ___   _   _   _____     ____    _____   _____   ____  "<<endl;
        cout<<" |  _ \\  | ____| \\ \\   / / |_ _| | \\ | | | ____|   |  _ \\  | ____| |_   _| / ___| "<<endl;
        cout<<" | | | | |  _|    \\ \\ / /   | |  |  \\| | |  _|     | |_) | |  _|     | |   \\___ \\ "<<endl;
        cout<<" | |_| | | |___    \\ V /    | |  | |\\  | | |___    |  __/  | |___    | |    ___) |"<<endl;
        cout<<" |____/  |_____|    \\_/    |___| |_| \\_| |_____|   |_|     |_____|   |_|   |____/ "<<endl;
        cout<<endl;
    }
};