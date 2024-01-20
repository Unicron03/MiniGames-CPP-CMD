#include<iostream>
#include<string>
#include<ctime>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

class Perudo{
public:
    static void perudoGame(){
        system("clear");
        int dee1j1,dee2j1,dee3j1,dee4j1,dee5j1,dee1j2,dee2j2,dee3j2,dee4j2,dee5j2;
        int nombreDeej1 = 5, nombreDeej2 = 5;
        int valeurDeej1 = 0, valeurDeej2 = 0;
        int nombreValeurDeej1 = 0, nombreValeurDeej2 = 0;
        int joueurmenteur = 0;
        int joueur = 1 ;
        string pseudoj1 = "", pseudoj2 = "";
        string j1menteur = "", j2menteur = "";

        affTitle();
        affRegles();

        cout<<endl;
        leadRead();
        cout<<endl;

        saisirPseudo(pseudoj1, 1);
        saisirPseudo(pseudoj2, 2);
        dee(dee1j1,dee2j1,dee3j1,dee4j1,dee5j1,dee1j2,dee2j2,dee3j2,dee4j2,dee5j2);
        while ((nombreDeej1 != 0) && ( nombreDeej2 != 0)){
            if (joueurmenteur == 1){
                dee(dee1j1,dee2j1,dee3j1,dee4j1,dee5j1,dee1j2,dee2j2,dee3j2,dee4j2,dee5j2);
                joueurmenteur = 0;
                valeurDeej1 = 0;
                valeurDeej2 = 0;
                nombreValeurDeej1 = 0;
                nombreValeurDeej2 = 0;
            }
            if (joueur == 1){
                jeu(dee1j1, dee2j1, dee3j1, dee4j1, dee5j1, pseudoj1,
                pseudoj2,nombreDeej1, valeurDeej1, valeurDeej2, nombreValeurDeej1,
                nombreValeurDeej2, j1menteur);
                if (j1menteur != "oui"){
                    jeu(dee1j2, dee2j2, dee3j2, dee4j2, dee5j2, pseudoj2,
                    pseudoj1, nombreDeej2, valeurDeej2, valeurDeej1, nombreValeurDeej2,
                    nombreValeurDeej1, j2menteur);
                }
                joueur = 2;
            } else if (joueur == 2) {
                jeu(dee1j2, dee2j2, dee3j2, dee4j2, dee5j2, pseudoj2,
                    pseudoj1, nombreDeej2, valeurDeej2, valeurDeej1, nombreValeurDeej2,
                    nombreValeurDeej1, j2menteur);
                if (j2menteur != "oui"){
                    jeu(dee1j1, dee2j1, dee3j1, dee4j1, dee5j1, pseudoj1,
                    pseudoj2, nombreDeej1, valeurDeej1, valeurDeej2, nombreValeurDeej1,
                    nombreValeurDeej2, j1menteur);
                }
                joueur = 1;
            }
            if (j1menteur == "oui"){
                testMenteur(dee1j1,dee2j1, dee3j1, dee4j1, dee5j1, valeurDeej1, nombreValeurDeej1,
                pseudoj1, pseudoj2, joueurmenteur, nombreDeej1, nombreDeej2);
                j1menteur = "non";
            }
            if(j2menteur == "oui"){
                testMenteur(dee1j2,dee2j2, dee3j2, dee4j2, dee5j2, valeurDeej2, nombreValeurDeej2,
                pseudoj2, pseudoj1, joueurmenteur, nombreDeej2, nombreDeej1);
                j2menteur = "non";
            }
            if (nombreDeej1 == 0){
                cout<<endl;
                cout<<pseudoj2<<" à gagné !"<<endl;
                leadWrite(pseudoj1, 1);
                leadWrite(pseudoj2, 0);
            }
            if (nombreDeej2 == 0){
                cout<<endl;
                cout<<pseudoj1<<" à gagné !"<<endl;
                leadWrite(pseudoj2, 1);
                leadWrite(pseudoj1, 0);
            }
        }

        cout<<endl;
        leadRead();
        cout<<endl;
    }

private:
    static void saisirPseudo(string & joueur, int joueurPos) {
        cout<<"Joueur "<<joueurPos<<", saisisser votre pseudo : ";
        cin>>joueur;
    }

    //modify les dés des 2 joueurs
    static void dee(int & dee1j1,int & dee2j1,int & dee3j1,int & dee4j1,int & dee5j1,
    int & dee1j2,int & dee2j2,int & dee3j2,int & dee4j2,int & dee5j2){
        srand(time(0));
        dee1j1 = 1 + rand() % 6;
        dee2j1 = 1 + rand() % 6;
        dee3j1 = 1 + rand() % 6;
        dee4j1 = 1 + rand() % 6;
        dee5j1 = 1 + rand() % 6;
        dee1j2 = 1 + rand() % 6;
        dee2j2 = 1 + rand() % 6;
        dee3j2 = 1 + rand() % 6;
        dee4j2 = 1 + rand() % 6;
        dee5j2 = 1 + rand() % 6;
    }


    static int jeu(int dee1, int & dee2, int & dee3, int & dee4, int & dee5, string pseudoj1,
    string pseudoj2, int nombreDee, int & valeurDeej1, int valeurDeej2, int & nombreValeurDeej1,
    int nombreValeurDeej2, string & menteur){
        string joueurOk;
        string affichedee1 = "", affichedee2 = "", affichedee3 = "", affichedee4 = "", affichedee5 = "";
        if(dee1 == 1){
            affichedee1 = "PACO";
        } else if(dee1 != 1){
            affichedee1 = to_string(dee1);
        }
        if(dee2 == 1){
            affichedee2 = "PACO";
        } else if(dee2 != 1){
            affichedee2 = to_string(dee2);
        }
        if(dee3 == 1){
            affichedee3 = "PACO";
        } else if(dee3 != 1){
            affichedee3 = to_string(dee3);
        }
        if(dee4 == 1){
            affichedee4 = "PACO";
        } else if(dee4 != 1){
            affichedee4 = to_string(dee4);
        }
        if(dee5 == 1){
            affichedee5 = "PACO";
        } else if(dee5 != 1){
            affichedee5 = to_string(dee5);
        }
        
        cout<<endl;
        if (nombreDee == 5){
            cout<<"Vos dés sont : ["<<affichedee1<<","<<affichedee2<<","<<affichedee3<<","<<affichedee4<<","<<affichedee5<<"]"<<endl;
        } else if (nombreDee == 4){
            cout<<"Vos dés sont : ["<<affichedee1<<","<<affichedee2<<","<<affichedee3<<","<<affichedee4<<"]"<<endl;
            dee5 = -1;
        } else if (nombreDee == 3){
            cout<<"Vos dés sont : ["<<affichedee1<<","<<affichedee2<<","<<affichedee3<<"]"<<endl;
            dee5 = -1;
            dee4 = -1;
        } else if (nombreDee == 2){
            cout<<"Vos dés sont : ["<<affichedee1<<","<<affichedee2<<"]"<<endl;
            dee5 = -1;
            dee4 = -1;
            dee3 = -1;
        } else if (nombreDee == 1){
            cout<<"Vos dés sont : ["<<affichedee1<<"]"<<endl;
            dee5 = -1;
            dee4 = -1;
            dee3 = -1;
            dee2 = -1;
        }
        cout<<pseudoj1<<", donnez la valeur d'un dé : ";
        cin>>valeurDeej1;
        cout<<pseudoj1<<", donnez le nombre de dé ayant cette valeur : ";
        cin>>nombreValeurDeej1;
        while (((valeurDeej1 <= valeurDeej2)&&(nombreValeurDeej1 <= nombreValeurDeej2))||
        ((valeurDeej1 > 7)||(nombreValeurDeej1 > 7))||(valeurDeej1 < 1)){
            cout<<pseudoj1<<" il faut soit augmenter la valeur du dé, soit le nombre de dé (rapelle : interdit de parier des PACO) ou ne pas prendre des nombres trop grand !"<<endl;
            cout<<pseudoj1<<", donnez la valeur d'un dé : ";
            cin>>valeurDeej1;
            cout<<pseudoj1<<", donnez le nombre de dé ayant cette valeur : ";
            cin>>nombreValeurDeej1;
        }
        system("clear");
        cout<<pseudoj2<<" es tu pret ? (oui/non) : ";
        cin>>joueurOk;
        while (joueurOk!="oui"){
            cout<<"Maintenant "<<pseudoj2<<" es tu pret ? (oui/non) : ";
            cin>>joueurOk;
        }
        cout<<pseudoj1<<" dit avoir "<<nombreValeurDeej1<<" dés de "<<valeurDeej1<<"."<<endl;
        cout<<pseudoj2<<", est ce que "<<pseudoj1<<" est un menteur ? (oui/non) : ";
        cin>>menteur;
        return 0;
    }

    static int testMenteur (int dee1,int dee2,int dee3,int dee4,int dee5,int valeurDee,
    int nombreValeurDee,string pseudoj1,
    string pseudoj2, int & joueurmenteur,int & nombreDeej1,int & nombreDeej2){
        int nombrebondee = 0;
        if ((dee1 == valeurDee)||(dee1 == 1)){
            nombrebondee++;
            }
        if ((dee2 == valeurDee)||(dee2 == 1)){
            nombrebondee++;
        }
        if ((dee3 == valeurDee)||(dee3 == 1)){
            nombrebondee++;
        }
        if ((dee4 == valeurDee)||(dee4 == 1)){
            nombrebondee++;
        }
        if ((dee5 == valeurDee)||(dee5 == 1)){
            nombrebondee++;
        }
        if (nombrebondee < nombreValeurDee) {
            cout<<pseudoj1<<" est un menteur, il perd un dé !"<<endl;
            nombreDeej1--;
            joueurmenteur = 1;
        } else if (nombrebondee >= nombreValeurDee){
            cout<<pseudoj1<<" n'est pas un menteur, "<<pseudoj2<<" perd un dé !"<<endl;
            nombreDeej2--;
            joueurmenteur = 1;
        }
        return 0;
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
        ofstream leaderboardFile("text/leaderboard_perudo.txt");
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
        ifstream leaderboardFile("text/leaderboard_perudo.txt");

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

    static void affTitle(){
        cout<<"                            _       "<<endl;
        cout<<"                           | |      "<<endl;
        cout<<"  _ __   ___ _ __ _   _  __| | ___  "<<endl;
        cout<<" | '_ \\ / _ \\ '__| | | |/ _` |/ _ \\ "<<endl;
        cout<<" | |_) |  __/ |  | |_| | (_| | (_) |"<<endl;
        cout<<" | .__/ \\___|_|   \\__,_|\\__,_|\\___/ "<<endl;
        cout<<" | |                                "<<endl;
        cout<<" |_|                                "<<endl<<endl;
    }

    static void affRegles(){
        cout<<"\n\x1b[31mVOICI LES REGLES :\x1b[0m"<<endl;
        cout<<"Le but du jeu et d'être le dernier à avoir des dés, chaque joueur commence avec 5 dés, chaque joueur devra dire une valeur de dé,";
        cout<<"et un nombre de dés, il peut mentir mais il est obligé de donner soit un plus grosse valeur de dé soit un plus gros nombre,";
        cout<<"exemple : si je dis que j'ai 3 dés de 5 il peut dire qu'il a 4 dés de 2, ou 2 dés 6, ..."<<endl;
        cout<<"Le joueur perd un dé si il ment quand il est accusé de menteur, ou quand il accuse quelqu'un qui ne ment pas."<<endl;
        cout<<"Les pacos prennent n'importe quelle valeur."<<endl;
    }
};