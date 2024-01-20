#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class MasterMind {
public:
    static void msMGame(){
        system("clear");
        affTitle();
        affRegles();

        cout<<endl;
        leadRead();
        cout<<endl;

        int points = 12;
        int victoire = 0;
        int nombreBonnePlace = 0;
        int nombreBonneCouleur = 0;
        string couleur1 = "";
        string couleur2 = "";
        string couleur3 = "";
        string couleur4 = "";
        string pseudo = "";
        string choixCouleur1 = "";
        string choixCouleur2 = "";
        string choixCouleur3 = "";
        string choixCouleur4 = "";
        cout<<"Saisissez votre pseudo : ";
        cin>>pseudo;
        couleur1 = codeSecret();
        couleur2 = codeSecret();
        while (couleur2 == couleur1){
            couleur2 = codeSecret();
        }
        couleur3 = codeSecret();
        while (couleur3 == couleur2){
            couleur3 = codeSecret();
        }
        couleur4 = codeSecret();
        while (couleur4 == couleur3){
            couleur4 = codeSecret();
        }
        while((victoire!=1)&&(points != 0)){
            cout<<endl;
            saisirCouleur(pseudo,choixCouleur1);
            saisirCouleur(pseudo,choixCouleur2);
            saisirCouleur(pseudo,choixCouleur3);
            saisirCouleur(pseudo,choixCouleur4);
            nombreBonnePlace = bonnePlace(couleur1, couleur2, couleur3,
                couleur4, choixCouleur1, choixCouleur2,
                choixCouleur3, choixCouleur4);
            nombreBonneCouleur = bonneCouleur(couleur1, couleur2,
                couleur3, couleur4, choixCouleur1, choixCouleur2,
                choixCouleur3, choixCouleur4);
            points--;
            cout<<"Vous avez "<<nombreBonneCouleur<<" bonne couleur(s) dont "<<nombreBonnePlace<<" bien placée(s) !"<<endl;
            if ((nombreBonneCouleur==4)&&(nombreBonnePlace==4)){
                victoire = 1;
                cout<<"\nVous avez gagné "<<points<<" points !"<<endl;
            }
        }
        leadWrite(pseudo, points);

        cout<<endl;
        leadRead();
        cout<<endl;
    }

private:
    //Génère aléatoirement les couleurs
    static string codeSecret(){
        int codeSecret;
        string couleur = "";
        srand(time(0));
        codeSecret = 1 + rand() % 8;
        if (codeSecret == 1){
            couleur = "rouge";
            return couleur;
        } else if (codeSecret == 2){
            couleur = "vert";
            return couleur;
        } else if (codeSecret == 3){
            couleur = "bleu";
            return couleur;
        } else if (codeSecret == 4){
            couleur = "jaune";
            return couleur;
        } else if (codeSecret == 5){
            couleur = "orange";
            return couleur;
        } else if (codeSecret == 6){
            couleur = "gris";
            return couleur;
        } else if (codeSecret == 7){
            couleur = "rose";
            return couleur;
        } else {
            couleur = "blanc";
            return couleur;
        }
    }

    static void saisirCouleur(string pseudo, string & choixCouleur){
        cout<<pseudo<<" saisissez la couleur parmi '\x1b[34mbleu\x1b[0m, \x1b[31mrouge\x1b[0m, \x1b[32mvert\x1b[0m, \x1b[97mblanc\x1b[0m, \x1b[38;5;206mrose\x1b[0m, \x1b[38;5;208morange\x1b[0m, \x1b[33mjaune\x1b[0m, \x1b[38;5;240mgris\x1b[0m' : ";
        cin>>choixCouleur;
        while ((choixCouleur != "blanc")&&(choixCouleur != "rose")&&
        (choixCouleur != "rouge")&&(choixCouleur != "orange")&&
        (choixCouleur != "vert")&&(choixCouleur != "gris")&&
        (choixCouleur != "bleu")&&(choixCouleur != "jaune")){
            cout<<pseudo<<"Vous avez fait une faute, veuillez retaper la couleur"<<endl;
            cout<<pseudo<<" saisissez  la couleur parmi '\x1b[34mbleu\x1b[0m,\x1b[31mrouge\x1b[0m,\x1b[32mvert\x1b[0m,\x1b[97mblanc\x1b[0m,\x1b[38;5;206mrose\x1b[0m,\x1b[38;5;208morange\x1b[0m,\x1b[33mjaune\x1b[0m,\x1b[38;5;240mgris\x1b[0m' : ";
            cin>>choixCouleur;
            cout<<choixCouleur;
        }
    }

    static int bonneCouleur(string couleur1,
    string couleur2,string couleur3,
    string couleur4, string choixCouleur1,
    string choixCouleur2, string choixCouleur3, 
    string choixCouleur4){
        int nombreBonneCouleur = 0;
        if (choixCouleur1 == couleur1){
            nombreBonneCouleur++;
            couleur1 = "0";
        } else if(choixCouleur1 == couleur2){
            nombreBonneCouleur++;
            couleur2 = "0";
        } else if (choixCouleur1 == couleur3){
            nombreBonneCouleur++;
            couleur3 = "0";
        } else if (choixCouleur1 == couleur4){
            nombreBonneCouleur++;
            couleur1 = "0";
        }
        if (choixCouleur2 == couleur1){
            nombreBonneCouleur++;
            couleur1 = "0";
        } else if(choixCouleur2 == couleur2){
            nombreBonneCouleur++;
            couleur2 = "0";
        } else if (choixCouleur2 == couleur3){
            nombreBonneCouleur++;
            couleur3 = "0";
        } else if (choixCouleur2 == couleur4){
            nombreBonneCouleur++;
            couleur1 = "0";
        }
        if (choixCouleur3 == couleur1){
            nombreBonneCouleur++;
            couleur1 = "0";
        } else if(choixCouleur3 == couleur2){
            nombreBonneCouleur++;
            couleur2 = "0";
        } else if (choixCouleur3 == couleur3){
            nombreBonneCouleur++;
            couleur3 = "0";
        } else if (choixCouleur3 == couleur4){
            nombreBonneCouleur++;
            couleur1 = "0";
        }
        if (choixCouleur4 == couleur1){
            nombreBonneCouleur++;
            couleur1 = "0";
        } else if(choixCouleur4 == couleur2){
            nombreBonneCouleur++;
            couleur2 = "0";
        } else if (choixCouleur4 == couleur3){
            nombreBonneCouleur++;
            couleur3 = "0";
        } else if (choixCouleur4 == couleur4){
            nombreBonneCouleur++;
            couleur1 = "0";
        }
        return nombreBonneCouleur;
        
    }

    static int bonnePlace(string couleur1,
    string couleur2,string couleur3,
    string couleur4, string choixCouleur1,
    string choixCouleur2, string choixCouleur3, 
    string choixCouleur4){
        int nombreBonnePlace = 0;
        if (couleur1 == choixCouleur1){
            nombreBonnePlace++;
        }
        if (couleur2 == choixCouleur2){
            nombreBonnePlace++;
        }
        if (couleur3 == choixCouleur3){
            nombreBonnePlace++;
        }
        if (couleur4 == choixCouleur4){
            nombreBonnePlace++;
        }
        return nombreBonnePlace;
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
        ofstream leaderboardFile("text/leaderboard_mastermind.txt");
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

        cout << "\x1b[38;5;208mLEADERBOARD (points) : \x1b[0m" << endl;
        
        if (leaderboardData.empty()) {
            cout << "Aucunes données" << endl;
        } else {
            for (const auto& entry : leaderboardData) {
                cout << entry.first << " : " << entry.second << " points" << endl;
            }
        }
    }

    static vector<pair<string, int>> readLeaderboard() {
        vector<pair<string, int>> leaderboardData;
        ifstream leaderboardFile("text/leaderboard_mastermind.txt");

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
        cout<<"Le jeu se joue avec un code secret composé de 4 couleurs. Chaque couleur peut être choisie parmi : '\x1b[34mbleu\x1b[0m', '\x1b[31mrouge\x1b[0m', '\x1b[32mvert\x1b[0m', '\x1b[97mblanc\x1b[0m', '\x1b[38;5;206mrose\x1b[0m', '\x1b[38;5;208morange\x1b[0m', '\x1b[33mjaune\x1b[0m' et '\x1b[38;5;240mgris\x1b[0m'."<<endl;
        cout<<"Le joueur doit deviner la combinaison secrète en proposant une séquence de 4 couleurs. Il possède 12 essaies pour deviner la combinaison secrète."<<endl;
        cout<<"Après chaque proposition, le jeu fournit des indications au joueur :"<<endl;
        cout<<"     • Le nombre de couleurs correctes et correctement placées."<<endl;
        cout<<"     • Le nombre de couleurs correctes mais mal placées."<<endl;
        cout<<"Le joueur continue à faire des propositions jusqu'à ce qu'il devine correctement la combinaison ou qu'il ait utilisé tous ses essais."<<endl;
        cout<<"Si le joueur parvient à deviner la combinaison secrète en moins de 12 essais, il remporte la partie !"<<endl;
    }

    static void affTitle() {
        cout<<endl;
        cout<<"  __  __      _      _   _   ____    _____   _____   ____    __  __   ___   _   _   ____  "<<endl;
        cout<<" |  \\/  |    / \\    | \\ | | / ___|  |_   _| | ____| |  _ \\  |  \\/  | |_ _| | \\ | | |  _ \\ "<<endl;
        cout<<" | |\\/| |   / _ \\   |  \\| | \\___ \\    | |   |  _|   | |_) | | |\\/| |  | |  |  \\| | | | | |"<<endl;
        cout<<" | |  | |  / ___ \\  | |\\  |  ___) |   | |   | |___  |  _ <  | |  | |  | |  | |\\  | | |_| |"<<endl;
        cout<<" |_|  |_| /_/   \\_\\ |_| \\_| |____/    |_|   |_____| |_| \\_\\ |_|  |_| |___| |_| \\_| |____/ "<<endl;
        cout<<endl;
    }
};