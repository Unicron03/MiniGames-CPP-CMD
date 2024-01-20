#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/time.h>
#include <list>
#include <iomanip>

using namespace std;

class Speed {
public:
    static void speedGame() {
        system("clear");
        ifstream speedWiki("text/speedDico.txt");
        if (speedWiki) {
            affTitle();
            affRegles();

            cout<<endl;
            leadRead();
            cout<<endl;

            string pseudo = createPseudo();
            list<string> lstMot = lstIncrement();
            int score = 0, nbMot = 10;
            double moyenne = 0.0;
            
            struct timeval start{};
            struct timeval end{};
            string motToFind;

            for(int i = 1; i <= nbMot; i++) {
                system("clear");
                gettimeofday(&start, nullptr);
                motToFind = giveMotToFind(lstMot);
                string motPlayer = "";
                writeMot(motPlayer, motToFind, i);

                while(!checkMot(motPlayer, motToFind)) {
                    system("clear");
                    cout<<"Mot mal écrit ! Réessayer"<<endl;
                    writeMot(motPlayer, motToFind, i);
                }
                score++;
                gettimeofday(&end, nullptr);
                moyenne = (moyenne + time_diff(&start, &end));
            }
            moyenne = moyenne / nbMot;

            system("clear");
            cout<<fixed<<setprecision(2)<<"Vous avez une moyenne de "<<moyenne<<"sec par mot !"<<endl;
            leadWrite(pseudo, moyenne);
            cout<<endl;
            leadRead();
            cout<<endl;
        } else {
            cout<<"\nImpossible d'ouvrir le fichier"<<endl;
        }
    }

private:
    static string createPseudo() {
        string pseudo = "";
        cout<<"Saisissez votre pseudo : ";
        cin>>pseudo;
        system("clear");

        return pseudo;
    }

    static void writeMot(string & motPlayer, string motToFind, int i) {
        cout<<"Mot "<<i<<" à écrire : "<<motToFind<<endl<<"Zone d'écriture : ";
        cin>>motPlayer;
    }

    static float time_diff(struct timeval *start, struct timeval *end){
        return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
    }

    static bool checkMot(string motPlayer, string motToFind) {
        if(motPlayer == motToFind) {
            return true;
        } else {
            return false;
        }
    }

    static list<string> lstIncrement() {
        ifstream speedWiki("text/speedDico.txt");
        if (speedWiki) {
            list<string> lstMot = {};
            speedWiki.clear();
            speedWiki.seekg(0, ios::beg);
            string mot;
            while (speedWiki >> mot) {
                lstMot.push_back(mot);
            }
            
            return lstMot;
        }
    }

    static string giveMotToFind(list<string> lstMot) {
        string motToFind = "";

        srand(static_cast<unsigned>(time(nullptr)));
        int indice = rand() % lstMot.size();
        auto it = lstMot.begin();
        advance(it, indice);
        motToFind = *it;

        return motToFind;
    }

    static void leadWrite(const string & playerName, double moyenne) {
        // Lire les données actuelles du leaderboard
        vector<pair<string, double>> leaderboardData = readLeaderboard();  // Utilisez double pour la moyenne

        // Vérifier si le joueur existe déjà dans le leaderboard
        bool playerExists = false;
        for(auto& entry : leaderboardData) {
            if(entry.first == playerName) {
                // Le joueur existe, mettre à jour sa moyenne
                if(moyenne < entry.second) {
                    entry.second = moyenne;
                }
                playerExists = true;
                break;
            }
        }

        // Si le joueur n'existe pas, ajoutez-le au leaderboard
        if (!playerExists) {
            leaderboardData.push_back(make_pair(playerName, moyenne));
        }

        // Écrire les données mises à jour dans le fichier
        ofstream leaderboardFile("text/leaderboard_speed.txt");
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
        vector<pair<string, double>> leaderboardData = readLeaderboard();  // Utilisez double pour la moyenne

        cout << "\x1b[38;5;208mLEADERBOARD (records) : \x1b[0m" << endl;
        
        if (leaderboardData.empty()) {
            cout << "Aucunes données" << endl;
        } else {
            cout << fixed << setprecision(2);  // Affichage avec 2 décimales
            for (const auto& entry : leaderboardData) {
                cout << entry.first << " : " << entry.second << " sec" << endl;
            }
        }
    }

    static vector<pair<string, double>> readLeaderboard() {
        vector<pair<string, double>> leaderboardData;
        ifstream leaderboardFile("text/leaderboard_speed.txt");

        if(leaderboardFile) {
            string line;
            while(getline(leaderboardFile, line)) {
                stringstream ss(line);
                string playerName;
                double score;
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
        cout<<"Le joueur doit saisir le plus rapidement possible 10 mots choisit aléatoirement."<<endl;
        cout<<"Si le mot saisi n'est pas le bon ou s'il est mal écrit, le joueur doit le resaisir et perds donc du temps !"<<endl;
        cout<<"Le joueur gagne une fois qu'il à écrit les 10 mots correctements et voit son score."<<endl;
        cout<<"Attention, le jeu se lance dès que le joueur à rentré son pseudo !"<<endl;
    }

    static void affTitle() {
        cout<<endl;
        cout<<"  ____    ____    _____   _____   ____     __        __   ___    ____    ____    ____  "<<endl;
        cout<<" / ___|  |  _ \\  | ____| | ____| |  _ \\    \\ \\      / /  / _ \\  |  _ \\  |  _ \\  / ___| "<<endl;
        cout<<" \\___ \\  | |_) | |  _|   |  _|   | | | |    \\ \\ /\\ / /  | | | | | |_) | | | | | \\___ \\ "<<endl;
        cout<<"  ___) | |  __/  | |___  | |___  | |_| |     \\ V  V /   | |_| | |  _ <  | |_| |  ___) |"<<endl;
        cout<<" |____/  |_|     |_____| |_____| |____/       \\_/\\_/     \\___/  |_| \\_\\ |____/  |____/ "<<endl;
        cout<<endl;
    }
};