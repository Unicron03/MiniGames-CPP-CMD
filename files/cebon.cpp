#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/time.h>

using namespace std;

class CEBon {
public:
    static void cebonGame() {
        system("clear");
        affTitle();
        affRegles();

        cout<<endl;
        leadRead();
        cout<<endl;

        struct timeval start{};
        struct timeval end{};
        int nbToFind = generateNb(), choix = 0, nbTry = 0, timer = 0;

        string pseudo = "";
        inputPseudo(pseudo);
        system("clear");

        gettimeofday(&start, nullptr);
        while (timer <= 120) {
            inputChoix(choix, nbTry);

            if(choix == nbToFind) {
                system("clear");
                cout<<"Vous avez gagné ! Il vous a fallu "<<timer<<"sec pour trouver le nombre "<<nbToFind<<" !"<<endl;
                leadWrite(pseudo, timer);
                cout<<endl;
                leadRead();
                return;
            } else if(choix > nbToFind) {
                cout<<"C'est moins !"<<endl;
            } else {
                cout<<"C'est plus !"<<endl;
            }
            gettimeofday(&end, nullptr);
            timer = time_diff(&start, &end);
        }

        system("clear");
        cout<<"Vous n'avez plus de temps ! Le nombre à trouver était "<<nbToFind<<" !"<<endl;
        cout<<endl;
        leadRead();
        cout<<endl;
    }

private:
    static void inputChoix(int & choix, int & nbTry) {
        cout<<"Saisissez votre nombre : ";
        cin>>choix;
        nbTry++;

        system("clear");
        cout<<"Actuel : "<<choix<<endl;
    }

    static void inputPseudo(string & pseudo) {
        cout<<"Saisissez votre pseudo : ";
        cin>>pseudo;
    }

    static int generateNb() {
        srand(time(nullptr));

        // Génération d'un nombre aléatoire entre 0 et 100000
        int randomNumber = rand() % 100001;

        return randomNumber;
    }

    static float time_diff(struct timeval *start, struct timeval *end){
        return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
    }

    static void leadWrite(const string & playerName, int score) {
        // Lire les données actuelles du leaderboard
        vector<pair<string, int>> leaderboardData = readLeaderboard();

        // Vérifier si le joueur existe déjà dans le leaderboard
        bool playerExists = false;
        for(auto& entry : leaderboardData) {
            if(entry.first == playerName) {
                // Le joueur existe, mettre à jour son score
                if(score < entry.second) {
                    entry.second = score;
                }
                playerExists = true;
                break;
            }
        }

        // Si le joueur n'existe pas, ajoutez-le au leaderboard
        if (!playerExists) {
            leaderboardData.push_back(make_pair(playerName, score));
        }

        // Écrire les données mises à jour dans le fichier
        ofstream leaderboardFile("text/leaderboard_cebon.txt");
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

        cout << "\x1b[38;5;208mLEADERBOARD (records) : \x1b[0m" << endl;
        
        if (leaderboardData.empty()) {
            cout << "Aucunes données" << endl;
        } else {
            for (const auto& entry : leaderboardData) {
                cout << entry.first << " : " << entry.second << "sec" << endl;
            }
        }
    }


    static vector<pair<string, int>> readLeaderboard() {
        vector<pair<string, int>> leaderboardData;
        ifstream leaderboardFile("text/leaderboard_cebon.txt");

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

    static void affTitle() {
        cout<<endl;
        cout<<"   ____    ___    __  __   ____    _____   _____     _____   ____    _____     ____     ___    _   _ "<<endl;
        cout<<"  / ___|  / _ \\  |  \\/  | |  _ \\  |_   _| | ____|   | ____| / ___|  |_   _|   | __ )   / _ \\  | \\ | |"<<endl;
        cout<<" | |     | | | | | |\\/| | | |_) |   | |   |  _|     |  _|   \\___ \\    | |     |  _ \\  | | | | |  \\| |"<<endl;
        cout<<" | |___  | |_| | | |  | | |  __/    | |   | |___    | |___   ___) |   | |     | |_) | | |_| | | |\\  |"<<endl;
        cout<<"  \\____|  \\___/  |_|  |_| |_|       |_|   |_____|   |_____| |____/    |_|     |____/   \\___/  |_| \\_|"<<endl;
        cout<<endl;
    }

    static void affRegles() {
        cout<<endl;
        cout<<"\n\x1b[31mVOICI LES REGLES :\x1b[0m"<<endl;
        cout<<"Vous devez trouver un nombre aléatoire entre 0 et 100 000."<<endl;
        cout<<"Pour ce faire, vous disposez de 3 minutes et autant de propositions que vous voulez !"<<endl;
        cout<<"Le jeu s'arrêtte quand le joueur à trouvé le nombre ou quand le timer à atteint les 3 minutes."<<endl;
        cout<<endl;
    }
};