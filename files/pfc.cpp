#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Pfc {
public:
    static int pfcGame(){
        system("clear");
        affTitle();
        affRegles();

        cout<<endl;
        leadRead();
        cout<<endl;

        int nombreJoueur = 0;
        int nombreVictoirej1 = 0;
        int nombreVictoirej2 = 0;
        string signe1 ="";
        string signe2 ="";
        string pseudoj1 = "";
        string pseudoj2 = "";

        saisiModJeu(nombreJoueur);

        if (nombreJoueur == 1){
            cout<<endl;
            pseudoj1 = saisiPseudo(1);
            jouerSeul(pseudoj1, signe1, nombreVictoirej1);
        } else {
            pseudoj1 = saisiPseudo(1);
            pseudoj2 = saisiPseudo(2);
            jouer1v1(signe1,signe2,pseudoj1,pseudoj2,nombreVictoirej1,nombreVictoirej2);
        }
    }

private:
    static string saisiPseudo(int joueur) {
        string pseudo = "";
        cout<<"Joueur "<<joueur<<" saisisser votre pseudo : ";
        cin>>pseudo;

        while(pseudo=="ordi" || pseudo=="ordinateur") {
            cout<<"VOUS NE POUVEZ PAS VOUS APPELEZ COMME ÇA !"<<endl;
            cout<<"Joueur "<<joueur<<" saisisser votre pseudo : ";
            cin>>pseudo;
        }
        system("clear");

        return pseudo;
    }

    static void saisiModJeu(int & nombreJoueur) {
        cout<<"Voulez vous jouer tous seul ou à deux ? (1/2) : ";
        cin>>nombreJoueur;

        while ((nombreJoueur != 1)&&(nombreJoueur != 2)){
            cout<<"Vous ne pouver pas jouer a plus de deux !"<<endl;
            cout<<"Voulez vous jouer tous seul ou à deux ? (1/2) : ";
            cin>>nombreJoueur;
        }
    }

    // Fait choisir au joueur un signe.
    static string choixSigne(string pseudo){
        string signe="";
        cout<<pseudo<<", saisisser votre signe parmi pierre, feuille, ou ciseau : ";
        cin>>signe;
        while ((signe != "pierre")&&(signe != "feuille")&&(signe != "ciseau")){
            cout<<"Saisi incorrect, vous devez saisir 'pierre', 'papier', ou 'ciseau' !"<<endl;
            cout<<pseudo<<", saisisser votre signe parmi pierre, feuille, ou ciseau : ";
            cin>>signe;
        }
        system("clear");
        return signe;
    }

    // Donne le signe du bot aléatoirement
    static string signeBot(){
        int nombreSigne;
        string signe = "";
        srand(time(0));
        nombreSigne = rand() % 4;
        if (nombreSigne == 1){
            signe = "pierre";
            return signe;
        } else if (nombreSigne == 2){
            signe = "feuille";
            return signe;
        } else {
            signe = "ciseau";
            return signe;
        }
    }

    // Détermine le gagnant s'il y en a un.
    static int testVictoire(string signe1, string signe2){
        int gagnant = 0;
        if(((signe1 == "feuille")&&(signe2 == "pierre"))||
        ((signe1 == "pierre")&&(signe2 == "ciseau"))||
        ((signe1 == "ciseau")&&(signe2 == "feuille"))){
            gagnant = 1;
            return gagnant;
        } else if (((signe2 == "feuille")&&(signe1 == "pierre"))||
        ((signe2 == "pierre")&&(signe1 == "ciseau"))||
        ((signe2 == "ciseau")&&(signe1 == "feuille"))){
            gagnant = 2;
            return gagnant;
        } else {
            return 0;
        }
    }

    //Permet de jouer et rejouer et annonce le gagnant s'il y en a un, et met à jour les scores.
    static void jouer1v1(string signe1,string signe2,string pseudoj1,string pseudoj2,int & nombreVictoirej1,int & nombreVictoirej2){
        string jouer1v1 = "oui";
        while (jouer1v1 =="oui"){
            system("clear");
            signe1 = choixSigne(pseudoj1);
            signe2 = choixSigne(pseudoj2);
            cout<<pseudoj1<<" à joué "<<signe1<<" !"<<endl;
            cout<<pseudoj2<<" à joué "<<signe2<<" !"<<endl;
            cout<<endl;
            if (testVictoire(signe1,signe2)==1){
                nombreVictoirej1++;
                cout<<pseudoj1<<" à gagné ! Il a actuellement "<<nombreVictoirej1<<" victoires à son actif !"<<endl;
                leadWrite(pseudoj1, 1);
                leadWrite(pseudoj2, 0);
            } else if (testVictoire(signe1,signe2)==2){
                nombreVictoirej2++;
                cout<<pseudoj2<<" à gagné ! Il a actuellement "<<nombreVictoirej2<<" victoires à son actif !"<<endl;
                leadWrite(pseudoj2, 1);
                leadWrite(pseudoj1, 0);
            } else {
                cout<<"Egalité !"<<endl;
            }
            cout<<endl;
            leadRead();

            cout<<endl;
            cout<<"Voulez vous rejouer ? (oui/non) : ";
            cin>>jouer1v1;
        }
    }

    static void jouerSeul(string pseudoj1, string signe1, int & nombreVictoirej1){
        string jouerSeul = "oui";
        string signe2 = "";
        while (jouerSeul =="oui"){
            system("clear");
            signe1 = choixSigne(pseudoj1);
            signe2 = signeBot();
            cout<<"Vous avez joué "<<signe1<<" !"<<endl;
            cout<<endl;
            if (testVictoire(signe1,signe2)==1){
                nombreVictoirej1++;
                cout<<"Vous avez gagné ! Vous avez actuellement "<<nombreVictoirej1<<" victoires à votre actif !"<<endl;
                leadWrite(pseudoj1, 1);
            } else if (testVictoire(signe1,signe2)==2){
                cout<<"Vous avez perdu !"<<endl;
                leadWrite("ordi", 1);
            } else {
                cout<<"Egalité !"<<endl;
            }

            cout<<endl;
            leadRead();

            cout<<endl;
            cout<<"Voulez vous rejouer ? (oui/non) : ";
            cin>>jouerSeul;
        }
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
        ofstream leaderboardFile("text/leaderboard_pfc.txt");
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
                if(entry.first=="ordi") {
                    cout<<"\x1b[34m"<<entry.first<<"\x1b[0m"<< " : " << entry.second << " victoires" << endl;
                } else {
                    cout<<entry.first<< " : " << entry.second << " victoires" << endl;
                }
            }
        }
    }

    static vector<pair<string, int>> readLeaderboard() {
        vector<pair<string, int>> leaderboardData;
        ifstream leaderboardFile("text/leaderboard_pfc.txt");

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
        cout<<"  ____    _                                  __  _____                  _   _   _             __   ____   _                              "<<endl;
        cout<<" |  _ \\  (_)   ___   _ __   _ __    ___     / / |  ___|   ___   _   _  (_) | | | |   ___     / /  / ___| (_)  ___    ___    __ _   _   _ "<<endl;
        cout<<" | |_) | | |  / _ \\ | '__| | '__|  / _ \\   / /  | |_     / _ \\ | | | | | | | | | |  / _ \\   / /  | |     | | / __|  / _ \\  / _` | | | | |"<<endl;
        cout<<" |  __/  | | |  __/ | |    | |    |  __/  / /   |  _|   |  __/ | |_| | | | | | | | |  __/  / /   | |___  | | \\__ \\ |  __/ | (_| | | |_| |"<<endl;
        cout<<" |_|     |_|  \\___| |_|    |_|     \\___| /_/    |_|      \\___|  \\__,_| |_| |_| |_|  \\___| /_/     \\____| |_| |___/  \\___|  \\__,_|  \\__,_|"<<endl;
        cout<<endl;
    }

    static void affRegles() {
        cout<<endl;
        cout<<"\n\x1b[31mVOICI LES REGLES :\x1b[0m"<<endl;
        cout<<"Si vous joué à 2, le joueur qui attent son tour détourne le regard."<<endl;
        cout<<"Pendant ce temps, le joueur qui joue choisit un signe parmis la pierre, la feuille ou le ciseau."<<endl;
        cout<<"Ensuite, les joueurs inverse les rôles !"<<endl;
        cout<<endl;
    }
    
    //ignorer la casse
};