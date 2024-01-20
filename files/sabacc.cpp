#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<ctime>
#include<stdlib.h>
#include<algorithm>
#include<random>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

class jeuSabacc{
public:
    static void JeuSabacc(){
        system("clear");
        string pseudoj1 = "", pseudoj2 = "";

        affTitle();
        affRegles();

        cout<<endl;
        leadRead();
        cout<<endl;

        saisirPseudo(pseudoj1, 1);
        saisirPseudo(pseudoj2, 2);

        srand(time(0));
        int creditj1 = 50, creditj2 = 50;
        if (partie(creditj1, creditj2, pseudoj1, pseudoj2) == 1){
            cout<<pseudoj1<<" a gagné le jeu !";
            leadWrite(pseudoj1, 1);
            leadWrite(pseudoj2, 0);
        } else {
            cout<<pseudoj2<<" a gagné le jeu !";
            leadWrite(pseudoj2, 1);
            leadWrite(pseudoj1, 0);
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

    // fonction qui s'assure que chaque carte est présente le nombre de fois qu'il faut
    static int testCarteDisponible(int cartejoueur,vector <int> & packet){
        for(int i = 0;i<62;i++){
            if(cartejoueur == packet[i]){
                packet[i]=-99;
                return 1;
            }
        }
        return 0;
    }


    // fonction qui va ajouter un nombre de cartes défini à un joueur défini
    static void remplissagePacket(vector <int>  & packetj,vector <int> & packet){
        int couleurCarte;
        int cartejoueur;
        
        couleurCarte = 1 + rand() % 2;
        if (couleurCarte == 1){
            cartejoueur = -10 + rand() % 10;
            testCarteDisponible(cartejoueur,packet);
            while (testCarteDisponible(cartejoueur,packet)==0){
                cartejoueur = -10 + rand() % 10;
            }
            packetj.push_back(cartejoueur);
        } else {
            cartejoueur =  rand() % 11;
            testCarteDisponible(cartejoueur,packet);
            while (testCarteDisponible(cartejoueur,packet)==0){
                cartejoueur = rand() % 11;
            }
            packetj.push_back(cartejoueur);
        }
        
    }


    // Échange une carte du joueur avec l'une du paquet
    static int echange(vector <int> & packetj,vector <int> & packet){
        vector <int> carteCachee = {};
        remplissagePacket(carteCachee,packet);
        int carteechange = 0;
        cout<<"Quelle carte voulez-vous échanger ? : ";
        cin>>carteechange;
        for(int i = 0;i<packetj.size();i++){
            if (carteechange == packetj[i]){
                packetj[i] = carteCachee[0];
                cout<<"Vous avez pioché "<<packetj[i]<<endl;
                return 1;
            }
        } 
        return 0;
    }

    // Échange une carte du joueur avec la carte visible
    static int echangeCarteVisible(vector <int> & packetj, vector <int> & carteFaceVisible){
        int temporaire = 0;
        int carteechange = 0;
        cout<<"Quelle carte voulez-vous échanger ? : ";
        cin>>carteechange;
        for(int i = 0;i<packetj.size();i++){
            if (carteechange == packetj[i]){
                temporaire = packetj[i];
                packetj[i] = carteFaceVisible[0];
                carteFaceVisible[0] = temporaire;
                return 1;
            }
        } 
        return 0;
    }

    // permet au joueur de voir le gagnant 
    static void gagnantVu(){
        string gagnantVu;
        cout<<"Avez-vous bien vu le gagnant ? (oui/non) : ";
        cin>>gagnantVu;
        while(gagnantVu!="oui"){
            cout<<"Et maintenant avez-vous vu le gagnant ? (oui/non) : ";
            cin>>gagnantVu;
        }
    }

    // permet au joueur de voir les dés
    static void deeVu(){
        string deeVu;
        cout<<"Avez-vous bien vu les dés ? (oui/non) : ";
        cin>>deeVu;
        while(deeVu!="oui"){
            cout<<"Et maintenant avez-vous vu les dés ? (oui/non) : ";
            cin>>deeVu;
        }
    }

    // Fais gagner le joueur qui ne s'est pas couché
    static void coucher(int & joueurcoucher,string pseudoj1,string pseudoj2, int & pot,int & creditj1,int & creditj2){
        system("clear");
        if(joueurcoucher==1){
            cout<<pseudoj1<<" s'est couché !, c'est donc "<<pseudoj2<<" qui gagne "<<pot<<"!"<<endl;
            creditj2=creditj2+pot;
        } else {
            cout<<pseudoj2<<" s'est couché !, c'est donc "<<pseudoj1<<" qui gagne "<<pot<<"!"<<endl;
            creditj1=creditj1+pot;
        }
        gagnantVu();
        joueurcoucher = 0;
        pot = 0;
    }
    
    // Permets au joueur de miser est de s'assurer que chaque joueur met la même mise
    static void mise(int & misej1,int misej2,int & allinj,int & pot,int & creditj,int misej1ajoutee,string pseudoj1,string & seCoucher){
        int arret = 0;
        while(((misej1ajoutee+misej1<misej2)||(misej1ajoutee>creditj))&&(arret==0)&&(seCoucher!="oui")){
            cout<<pseudoj1<<" vous deviez miser au moins : "<<misej2-misej1<<endl;
            cout<<"Voulez-vous vous coucher ? (oui/non) : ";
            cin>>seCoucher;
            if (seCoucher!="oui"){
                cout<<pseudoj1<<" vous avez "<<creditj<<" credits."<<endl;
                cout<<pseudoj1<<" vous deviez miser au moins : "<<misej2-misej1<<endl;
                cout<<"Vous avez déjà misé "<<misej1<<endl;
                cout<<"Il faut soit suivre soit enchérir !"<<endl;
                cout<<"Il ne faut pas miser plus que vous possédez !"<<endl;
                cout<<"Combien voulez vous miser ? ";
                cin>>misej1ajoutee;
                if((misej1ajoutee+misej1<misej2)&&(creditj+misej1<misej2)){
                    allinj = 1;
                    pot = pot + creditj;
                    misej1ajoutee=0;
                    misej1=misej2;
                    arret = 1;
                    creditj = 0;
                }
            }
        }
        if (seCoucher!="oui"){
            misej1=misej1ajoutee+misej1;
            if (misej1ajoutee>=creditj){
                cout<<"ALL IN"<<endl;
                allinj = 1;
                pot = pot + creditj; 
                creditj = 0;
            } else {
                pot = pot + misej1ajoutee;
                creditj = creditj-misej1ajoutee;
            }
        }
    }

    // tris les cartes d'un packet dans l'ordre décroissant
    static void triPacket(vector <int> packetj){
        int temporaire = 0;
        for(int i = 0;i<5;i++){
            for (int j = 1;j<packetj.size();j++){
                if ((packetj[j]=!0)&&(packetj[j-1]!=0)){
                    if (packetj[j]*packetj[j]/packetj[j]>packetj[j-1]*packetj[j-1]/packetj[j-1]){
                    temporaire = packetj[j-1];
                    packetj[j-1]=packetj[j]; 
                    packetj[j]=temporaire;      
                    }
                } else if (packetj[j-1]==0){
                    temporaire = packetj[j-1];
                    packetj[j-1]=packetj[j]; 
                    packetj[j]=temporaire;
                }    
            }
        }
    }

    // permet au joueur suivant de ne pas voir les cartes du précédent
    static void joueurOK(string pseudoj){
        string joueurok;
        system("clear");
        cout<<pseudoj<<" c'est à vous de jouer, êtes-vous prêt ? (oui/non) : ";
        cin>>joueurok;
        while (joueurok!="oui"){
            cout<<pseudoj<<" vous êtes prêt maintenant ? (oui/non) : ";
            cin>>joueurok;
        }
    }

    // ensemble des testes permettant de connaitre le gagnant
    static void testGagnant(vector <int> packetj1,vector <int> packetj2,int & creditj1,int & creditj2,int & pot, int & potSabacc,
    string pseudoj1,string pseudoj2){
        int totalj1 = 0, totalj2 = 0, gagnant=0;
        
        for (int i = 0;i<packetj1.size();i++){
            totalj1 = totalj1+packetj1[i];
        }
        for (int j = 0;j<packetj2.size();j++){
            totalj2 = totalj1+packetj1[j];
        }

        if ((totalj1*totalj1)/totalj1<(totalj2*totalj2)/totalj2){
            gagnant=1;
        } else if ((totalj1*totalj1)/totalj1>(totalj2*totalj2)/totalj2){
            gagnant=2;
        } else if ((totalj1*totalj1)/totalj1==(totalj2*totalj2)/totalj2){
            if (totalj1>totalj2){
                gagnant=1;
            } else if (totalj1<totalj2){
                gagnant=2;
            } else if (totalj1==totalj2){
                if(packetj1.size()>packetj2.size()){
                    gagnant=1;
                } else if(packetj1.size()<packetj2.size()){
                    gagnant=2;
                } else if (packetj1.size()==packetj2.size()){

                    triPacket(packetj1);
                    triPacket(packetj2);

                    for(int k=0;k<packetj1.size();k++){
                        if ((packetj1[k]!=0)&&(packetj2[k]!=0)){
                            if(packetj1[k]*packetj1[k]/packetj1[k]>packetj2[k]*packetj2[k]/packetj2[k]){
                                gagnant=1;
                                k=5;
                            } else if (packetj1[k]*packetj1[k]/packetj1[k]<packetj2[k]*packetj2[k]/packetj2[k]){
                                gagnant=2;
                                k=5;
                            } else {
                                if (packetj1[k]>packetj2[k]){
                                    gagnant=1;
                                    k=5;
                                } else if (packetj1[k]>packetj2[k]){
                                    gagnant=2;
                                    k=5;
                                }
                            }
                        }
                    }

                    if ((gagnant==1)&&(totalj1 == 0)){
                        gagnant=3;
                    }
                    if ((gagnant==2)&&(totalj1 == 0)){
                        gagnant=4;
                    }
                }
            }
        }
        if (gagnant==0){
            cout<<"Vous avez les mêmes cartes on vas donc diviser les gains entre vous !";
            creditj1=creditj1+pot/2;
            creditj2=creditj2+pot/2;
        } else if (gagnant==1){
            creditj1=creditj1+pot;
            cout<<pseudoj1<<" a gagné "<<pot<<"!"<<endl;
        } else if (gagnant==2){
            creditj2=creditj2+pot;
            cout<<pseudoj2<<" a gagné "<<pot<<"!"<<endl;
        } else if (gagnant=3){
            creditj1=creditj1+pot+potSabacc;
            cout<<pseudoj1<<" a gagné "<<pot+potSabacc<<"!"<<endl;
            potSabacc=0;
        } else {
            creditj2=creditj2+pot+potSabacc;
            cout<<pseudoj2<<" a gagné "<<pot+potSabacc<<"!"<<endl;
            potSabacc=0;
        }
        gagnantVu();
    }

    // fonction qui est dans tour et qui permet d'initialiser la mise du joueur, sans elle on ne peut plus miser a la fin du tour
    static void tourMise(int & misej1,int misej2,int & allinj,int & pot,int & creditj,int misej1ajoutee,string pseudoj1,string & seCoucher){
        cout<<"Mise minimum : "<<misej2<<endl;
        cout<<"Voulez-vous vous coucher ? (oui/non) : ";
        cin>>seCoucher;
        if(seCoucher!="oui"){
            cout<<pseudoj1<<" vous avez "<<creditj<<" !"<<endl;
            cout<<"Combien voulez-vous miser ? ";
            cin>>misej1ajoutee;
            mise(misej1,misej2,allinj,pot,creditj,misej1ajoutee,pseudoj1,seCoucher);
        }
    }

    // le joueur dit ce qu'il fait, contre quoi
    static void tour(vector <int> packet,int & creditj,int & allinj, int & potSabacc,int & pot,int & misej1,
    int & misej2,vector <int>  & packetj,vector <int> & carteFaceVisible,int misej1ajoutee,string pseudoj1,string & seCoucher){
        string cequeveutfairelejoueur, cequepayelejoueur;
        cout<<pseudoj1<<" vos cartes sont : ";
        for(int i=0; i<packetj.size(); i++){
            cout <<packetj[i] << "/";
        }
        cout<<endl;
        cout<<pseudoj1<<" vous avez "<<creditj<<" !"<<endl;
        cout<<"La carte visible est : "<<carteFaceVisible[0]<<endl;
        cout<<pseudoj1<<" que voulez-vous faire ? (cartecachee/cartevisible/rien) : ";
        cin>>cequeveutfairelejoueur;
        while((cequeveutfairelejoueur!="rien")&&(cequeveutfairelejoueur!="cartecachee")&&
        (cequeveutfairelejoueur!="cartevisible")){
            cout<<"Syntaxe incorrecte !"<<endl;
            cout<<pseudoj1<<" que voulez-vous faire ? (cartecachee/cartevisible/rien) : ";
            cin>>cequeveutfairelejoueur;
        }
        if (cequeveutfairelejoueur=="cartecachee"){
            cout<<pseudoj1<<" comment voulez-vous obtenir cette carte ? (echange/credit) : ";
            cin>>cequepayelejoueur;
            while((cequepayelejoueur!="credit")&&(cequepayelejoueur!="echange")){
                cout<<"Syntaxe incorrecte !"<<endl;
                cout<<pseudoj1<<" comment voulez-vous obtenir cette carte ? (echange/credit) : ";
                cin>>cequepayelejoueur;
            }
            if ( cequepayelejoueur == "credit"){
                if (allinj == 0){
                    if (creditj<3){
                        cout<<"ALL IN";
                        allinj = 1;
                        creditj = 0;
                        potSabacc = potSabacc + 1;
                        remplissagePacket(packetj,packet);
                        cout<<pseudoj1<<" vous avez pioché un "<<packetj.back()<<endl;
                    } else {
                        remplissagePacket(packetj,packet);
                        cout<<pseudoj1<<" vous avez pioché un "<<packetj.back()<<endl;
                        creditj = creditj - 2;
                        potSabacc++;
                        pot++;
                        tourMise(misej1,misej2,allinj,pot,creditj,misej1ajoutee,pseudoj1,seCoucher);
                    }
                } else {
                    cout<<pseudoj1<<" vous avez ALL IN !"<<endl;
                }
            } else if (cequepayelejoueur=="echange"){
                while (echange(packetj,packet)==0){
                    cout<<pseudoj1<<" vous devez posséder la carte !"<<endl;
                }
                if (allinj == 0){
                    tourMise(misej1,misej2,allinj,pot,creditj,misej1ajoutee,pseudoj1,seCoucher);
                } else {
                    cout<<pseudoj1<<" vous avez ALL IN !"<<endl;
                }
            }
        } else if (cequeveutfairelejoueur=="cartevisible"){
            cout<<"Comment voulez-vous obtenir cette carte ? (echange/credit) : ";
            cin>>cequepayelejoueur;
            while((cequepayelejoueur!="credit")&&(cequepayelejoueur!="echange")){
                cout<<"Syntaxe incorrecte !"<<endl;
                cout<<"Comment voulez-vous obtenir cette carte ? (echange/credit) : ";
                cin>>cequepayelejoueur;
            }
            if ( cequepayelejoueur == "credit"){
                if (allinj == 0){
                    if (creditj<4){
                        cout<<"ALL IN";
                        allinj = 1;
                        creditj = 0;
                        potSabacc = potSabacc + 1;
                        pot = pot + 2;
                        packetj.push_back(carteFaceVisible[0]);
                        remplissagePacket(carteFaceVisible,packet);
                        cout<<"La nouvelle carte visible est : "<<carteFaceVisible[0]<<endl;
                    } else {
                        packetj.push_back(carteFaceVisible[0]);
                        remplissagePacket(carteFaceVisible,packet);
                        cout<<"La nouvelle carte visible est : "<<carteFaceVisible[0]<<endl;
                        creditj = creditj - 3;
                        potSabacc ++;
                        tourMise(misej1,misej2,allinj,pot,creditj,misej1ajoutee,pseudoj1,seCoucher);
                    }
                } else {
                    cout<<"Vous n'avez pas assez d'argent !"<<endl;
                }
            } else if (cequepayelejoueur=="echange"){
                while (echangeCarteVisible(packetj, carteFaceVisible)==0){
                    cout<<"Vous devez posséder la carte !"<<endl;
                }
                if (allinj == 0){
                    tourMise(misej1,misej2,allinj,pot,creditj,misej1ajoutee,pseudoj1,seCoucher);
                } else {
                    cout<<"Vous avez ALL IN !"<<endl;
                }
            }
        } else if (cequeveutfairelejoueur=="rien"){
            if (allinj == 0){
                    tourMise(misej1,misej2,allinj,pot,creditj,misej1ajoutee,pseudoj1,seCoucher);
                } else {
                    cout<<"Vous avez ALL IN !"<<endl;
                }
        }
    }  

    // c'est 3 fois les tours des 2 joueurs jusqu'un des 2 joueur n'est plus d'argent
    static int partie(int & creditj1, int & creditj2, string pseudoj1, string pseudoj2){
        int JoueurPerdant = 0;
        int potSabacc = 0 ,joueurCommence = 1;
    
        while((JoueurPerdant!=1)&&(JoueurPerdant!=2)){

            int allinj1 = 0, allinj2 = 0, pot = 0, joueur = 2, joueurcoucher=0,dee1,dee2;

            string seCoucher;

            vector <int> packet {0,0,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,
            -1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10};
            int misej1ajoutee = 0;

            vector <int> packetj1 = {};
            vector <int> packetj2 = {};
            vector <int> carteFaceVisible {};

            remplissagePacket(packetj1,packet);
            remplissagePacket(packetj1,packet);

            remplissagePacket(packetj2,packet);
            remplissagePacket(packetj2,packet);
            
            remplissagePacket(carteFaceVisible,packet);


            for(int i=0;i<3;i++){
                int misej1 = 0, misej2 = 0;
                string joueurok;

                if (seCoucher!="oui"){
                    if(joueurCommence==1){
                        joueurOK(pseudoj1);
                        tour(packet,creditj1,allinj1,potSabacc,pot,misej1,misej2,packetj1,carteFaceVisible,misej1ajoutee,pseudoj1,seCoucher);
                        if(seCoucher!="oui"){
                            joueurOK(pseudoj2);
                            tour(packet,creditj2,allinj2,potSabacc,pot,misej2,misej1,packetj2,carteFaceVisible,misej1ajoutee,pseudoj2,seCoucher);
                            joueurCommence=2;
                            system("clear");
                            if (seCoucher=="oui"){
                                joueurcoucher=2;
                            }
                        } else {
                            joueurcoucher=1;
                        }
                    } else {
                        joueurOK(pseudoj2);
                        tour(packet,creditj2,allinj2,potSabacc,pot,misej2,misej1,packetj2,carteFaceVisible,misej1ajoutee,pseudoj2,seCoucher);
                        if(seCoucher!="oui"){
                            joueurOK(pseudoj1);
                            tour(packet,creditj1,allinj1,potSabacc,pot,misej1,misej2,packetj1,carteFaceVisible,misej1ajoutee,pseudoj1,seCoucher);
                            joueurCommence=1;
                            system("clear");
                            if (seCoucher=="oui"){
                                joueurcoucher=1;
                            }
                        } else {
                            joueurcoucher=2;
                        }
                    }
                }

                while((misej1!=misej2)&&(seCoucher!="oui")){
                    if(joueur==2){
                        mise(misej2, misej1, allinj2,pot,creditj2,misej1ajoutee,pseudoj2,seCoucher);
                        joueur = 1;
                        if (seCoucher=="oui"){
                            joueurcoucher=2;
                        }
                        system("clear");
                    } else if(joueur==1){
                        mise(misej1, misej2, allinj1,pot,creditj1,misej1ajoutee,pseudoj1,seCoucher);
                        joueur = 2;
                        if (seCoucher=="oui"){
                            joueurcoucher=1;
                        }
                    }
                }
                
                if (seCoucher!="oui"){
                    dee1= 1 + rand() % 6;
                    dee2= 1 + rand() % 6;
                    cout<<"Les dés sont : "<<dee1<<","<<dee2<<endl;
                    deeVu();
                    vector <int> carteDessusPacketj1 = {};
                    vector <int> carteDessusPacketj2 = {};
                    if(dee1==dee2){
                        cout<<"Les cartes vont être redistribuées"<<endl;
                        for(int j=0;j<packetj1.size();j++){
                            remplissagePacket(carteDessusPacketj1,packet);
                            packetj1[j] = carteDessusPacketj1[j];
                        }
                        for(int j=0;j<packetj2.size();j++){
                            remplissagePacket(carteDessusPacketj2,packet);
                            packetj2[j] = carteDessusPacketj2[j];
                        }
                    }
                }

            }

            if (seCoucher!="oui"){
                testGagnant(packetj1,packetj2,creditj1,creditj2,pot,potSabacc,pseudoj1,pseudoj2);
            } else if (seCoucher=="oui"){
                coucher(joueurcoucher,pseudoj1,pseudoj2,pot,creditj1,creditj2);
                seCoucher="non";
            }
            if (creditj1==0){
                JoueurPerdant=1;
            } else if (creditj2==0){
                JoueurPerdant=2;
            }
        }
        if (JoueurPerdant==1){
            JoueurPerdant=0;
            return 2;
        } else {
            JoueurPerdant=0;
            return 1;
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
        ofstream leaderboardFile("text/leaderboard_sabacc.txt");
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
        ifstream leaderboardFile("text/leaderboard_sabacc.txt");

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
        cout<<"           _                    "<<endl;
        cout<<" ___  __ _| |__   __ _  ___ ___ "<<endl;
        cout<<"/ __|/ _` | '_ \\ / _` |/ __/ __|"<<endl;
        cout<<"\\__ \\ (_| | |_) | (_| | (_| (__ "<<endl;
        cout<<"|___/\\__,_|_.__/ \\__,_|\\___\\___|"<<endl<<endl;
    }

    static void affRegles(){
        cout<<"\n\x1b[31mVOICI LES REGLES :\x1b[0m"<<endl;
        cout<<"Les joueurs doivent gagner le plus de credit possible, le jeu se finit quand l'un des 2 joueurs n'a plus de credits."<<endl;
        cout<<"Pour prendre des credits à l'autre ils vont faire trois manches, dans une manche chaque joueur peut soit prendre la carte visible,";
        cout<<"soit la carte cacher au-dessus du paquet ne soit rien, s'il prend une carte il peut soit l'échanger, soit l'acheter,";
        cout<<"si il l'achète il paye 1 credit sauf si c'est la carte visible qu'il paye 2, il y a 2 pots, un pour le sabbat un autre pour les mises."<<endl;
        cout<<"A la fin d'une manche les joueurs peuvent enchérir, ou ce coucher, une fois les mises des 2 joueurs égual la manche se termine";
        cout<<"et on tire 2 dés si ils font le même score les cartes de chaque joueur sont redistribué."<<endl;
        cout<<"à la fin des 3 manches ont vérifié qui a gagné, c'est celui dont la somme de ses cartes est le plus proche de 0,";
        cout<<"sinon c'est celui qui a un score positif, sinon c'est celui qui a le plus de cartes, sinon c'est celui qui a les plus grandes cartes";
        cout<<"sinon égalité on divise les gains en 2."<<endl;
        
        string affReglesVu = "";
        while (affReglesVu!="oui"){
            cout<<endl<<"Avez vous bien vu les règles ? (oui/non) : ";
            cin>>affReglesVu;
        }
    }
};