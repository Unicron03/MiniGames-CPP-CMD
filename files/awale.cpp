#include<iostream>
#include<math.h>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

class Awale {
public:
    static void awaleGame() {
        system("clear");
        affHistorique();
        affRegles();

        cout<<endl;
        leadRead();
        cout<<endl;

        /* Déclaration des variables*/
        int table_awale[12];
        int valeur_dep = 4,c,gain_j1,num_Joueur,gain_j2,calculateur,contenu;
        char A;
        string pseudo_j1 = "", pseudo_j2 = "";

        /*Incrementation du tableau au départ*/
        for (int i=0;i<=11;i++) {
            table_awale[i]= valeur_dep;
        }

        saisiPseudo(pseudo_j1, 1);
        saisiPseudo(pseudo_j2, 2);
        system("clear");

        affTab(table_awale);
        gain_j1=0;
        gain_j2=0;
        contenu=0;

        /*condition pour jouer*/
        while ((calculateur>=gain_j1)||(calculateur>=gain_j2)) {
            calculateur=0;
            contenu=0;

            joueur_1(table_awale,c,gain_j1,num_Joueur,pseudo_j1);
            joueur_2(table_awale,c, gain_j2,num_Joueur,pseudo_j2);
            
            for (int i=0;i<=11;i++) {
                contenu=table_awale[i];
                calculateur=contenu+calculateur;
            }
        }

        /*Calcule des graines restantes*/
        if (gain_j1>gain_j2) {
            affWin(pseudo_j1, gain_j1);
            leadWrite(pseudo_j1, 1);
            leadWrite(pseudo_j2, 0);
        } else if (gain_j1<gain_j2) {
            affWin(pseudo_j2, gain_j2);
            leadWrite(pseudo_j2, 1);
            leadWrite(pseudo_j1, 0);
        } else {
            cout<<"-----------------------------"<<endl;
            cout<<"Egalité !"<<endl;
            cout<<"Le joueur 1 ("<<pseudo_j1<<") a cumuler "<<gain_j1<< " graine(s)"<<endl;
            cout<<"Le joueur 2 ("<<pseudo_j2<<") a cumuler "<<gain_j2<< " graine(s)"<<endl;
            cout<<"-----------------------------"<<endl;
        }

        cout<<endl;
        leadRead();
        cout<<endl;
    }

private:
    static void saisiPseudo(string & pseudo, int joueur) {
        cout<<"Saisissez votre pseudo joueur "<<joueur<<" : ";
        cin>>pseudo;
    }

    static void affWin(string pseudo, int gain_joueur) {
        cout<<"-----------------------------"<<endl;
        cout<<"Le gagnant est "<<pseudo<<" avec "<<gain_joueur<< " graine(s) !"<<endl;
        cout<<"-----------------------------"<<endl;
    }

    static void affTab(int table_awale[]) {
        /*Affichage du tableau et passage à la ligne*/
        cout<<"-----------------------------"<<endl;
        for (int i=0;i<=11;i++) {
            cout<<table_awale[i];
            if (i==5) {
                cout<<""<<endl;
            }
        }
        cout<<""<<endl;
    }

    static int joueur_1(int table_awale[], int &c, int &gain_j1,int &num_Joueur, string pseudo_j1) {
        int i,courant;
        cout<<"-----------------------------"<<endl;
        cout <<"A vous "<<pseudo_j1<<" ! Entrez le numero de la case a prélever : ";
        cin>>c;

        while ((c<1)||(c>6)) {
            cout<<"-----------------------------"<<endl;
            cout<<"Refaire la saisie entre 1 et 6 : ";
            cin>>c;
        }
        system("clear");
        cout<<"La case "<<c<<" à était prélevée !"<<endl;

        c=c-1;
        courant = c;
        /*contrôle du crédit des cases et crédit*/
        for (i=1;i<=table_awale[c];i++) {
            if(courant == 0) courant = 6;
            else if(courant<6) courant--;
            else if (courant == 11) courant = 5;
            else courant++;
            table_awale[courant]+=1;
        }

        if ((courant>=6)&&(table_awale[(courant)]<=3)) {
            gain_j1= table_awale[courant]+gain_j1;
            table_awale[courant]=0;
        }
        table_awale[c]=0;
        cout<<"-----------------------------"<<endl;

        for (i=0;i<=11;i++) {
            cout <<table_awale[i];
            if (i==5) {
                cout<<""<<endl;
            }
        }
        cout<<""<<endl;
        cout<<"-----------------------------"<<endl;
        cout<<"Le gain de "<<pseudo_j1<<" est actuellement de : " <<gain_j1<<" graine(s)"<<endl;

        return gain_j1;
    }

    /*fonction du deuxième joueur*/
    static int joueur_2(int table_awale[], int &c, int &gain_j2,int &num_Joueur, string pseudo_j2){
        int i,courant;
        cout<<"-----------------------------"<<endl;
        cout <<"A vous "<<pseudo_j2<<" ! Entrez le numéro de la case a prélever : ";
        cin>>c;

        while ((c>12)||(c<7)) {
            cout<<"-----------------------------"<<endl;
            cout<<"Refaire la saisie entre 7 et 12 : ";
            cin>>c;
        }
        system("clear");
        cout<<"La case "<<c<<" à était prélevée !"<<endl;

        c=c-1;
        courant = c;
        int nombreGraine = table_awale[c];
        table_awale[c] = 0;

        /*contrôle du crédit des cases et crédit*/
        for (i=1;i<= nombreGraine;i++) {
            if (courant == 11) courant = 5;
            else if (courant == 0) courant = 6;
            else if(courant<=5) courant --;
            else courant ++;
            table_awale[courant]+=1;
        }

        if ((courant<6)&&(table_awale[(courant)]<=3)){
            gain_j2= table_awale[courant]+gain_j2;
            table_awale[courant]=0;
        }

        cout<<"-----------------------------"<<endl;
        for (i=0;i<=11;i++) {
            cout <<table_awale[i];
            if (i==5) {
                cout<<""<<endl;
            }
        }
        cout<<""<<endl;
        cout<<"-----------------------------"<<endl;
        cout<<"Le gain de "<<pseudo_j2<<" est actuellement de : " <<gain_j2<<" graine(s)"<<endl;

        return gain_j2;
    }

    static void leadWrite(const string & playerName, int points) {
        // Lire les données actuelles du leaderboard
        vector<pair<string, int>> leaderboardData = readLeaderboard();

        // Vérifier si le joueur existe déjà dans le leaderboard
        bool playerExists = false;
        for(auto& entry : leaderboardData) {
            if(entry.first == playerName) {
                entry.second = entry.second + points;
                playerExists = true;
                break;
            }
        }

        // Si le joueur n'existe pas, ajoutez-le au leaderboard
        if (!playerExists) {
            leaderboardData.push_back(make_pair(playerName, points));
        }

        // Écrire les données mises à jour dans le fichier
        ofstream leaderboardFile("text/leaderboard_awale.txt");
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
        ifstream leaderboardFile("text/leaderboard_awale.txt");

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

    static void affHistorique() {
        cout<<"  BIENVENUE SUR LE JEU AFRICA_AWALE"<<endl<<endl;
        cout<<"         ----------- "<<endl;
        cout<<"  --------------------------- "<<endl;
        cout<<"------------------------------- "<<endl;
        cout<<" ----------------------------- "<<endl;
        cout<<"  --------------------------- "<<endl;
        cout<<" ----------------------------------- "<<endl;
        cout<<"    -------------------------------- "<<endl;
        cout<<"           ---------------------- "<<endl;
        cout<<"           ----------------------- "<<endl;
        cout<<"             --------------- "<<endl;
        cout<<"             ---------------- "<<endl;
        cout<<"            --------------- "<<endl;
        cout<<"            --------------- "<<endl;
        cout<<"             --------------- "<<endl;
        cout<<"             --------------- "<<endl;
        cout<<"              ---------- "<<endl;
        cout<<"              ---------- "<<endl;
        cout<<"              --------- "<<endl;
        cout<<"              --------- "<<endl<<endl;

        cout<<"\n\x1b[31mBREF HISTORIQUE :\x1b[0m"<<endl;
        cout<<"L'Awale est un jeu qui fait reference a l'agriculture.L'origine veritable du jeu se situerait vers le Ve-VIe siecle de notre ere";
        cout<<"Le plus ancien jeu d'Awale connu est un mancala Ethiopien du VIIe siecle";
        cout<<"Le jeu s'est peu a peu diffuse au Moyen-Orient ainsi que sur tout le continent Africain."<<endl<<endl;
    }

    static void affRegles() {
        cout<<"\n\x1b[31mVOICI LES REGLES :\x1b[0m"<<endl;
        cout<<"1- Il y a deux camps avec 6 trous de chaque cote remplis de graines. On joue chacun a son tour."<<endl;
        cout<<"2- Le premier joueur prend toutes les graines contenues dans l'un des trous de son territoire et les seme, une par trou, en se deplacant dans le sens inverse des aiguilles d'une montre."<<endl;
        cout<<"3- Au fur et a mesure de la partie, des trous vont se vider et d'autres se remplir. Lorsqu'un joueur, en semant sa derniere graine tombe dans un trou ou il ne reste qu'une ou deux graines  dans le camp adverse, il recolte toutes les graines de ce trou qui reste vide. Cette recolte est donc son Gain."<<endl;
        cout<<"4- Le jeu s'arrete des que l'un des joueurs possede plus de graine en Gain qu'il y en a sur le plateur. On compare donc le nombre de gain des deux joueurs. Le gagnant est celui qui possède le plus de graines comme gain."<<endl<<endl;
    }
};