#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Pendu {
public:
    static void penduGame() {
        system("clear");
        ifstream penduWiki("text/penduDico.txt");
        if (penduWiki) {
            list<string> lstMot = {};
            string motToFind = "";
            string motMasque = "";
            string lstLettre = "";
            string pseudo = "";
            char lettrePlayer = 'a';
            int nbErreur = 0;

            lstIncrement(lstMot);
            motToFind = getRandomMot(lstMot);
            motMasque = string(motToFind.size(), '_');

            affTitle();
            affRegles(motToFind);

            cout<<endl;
            leadRead();
            cout<<endl;

            inputPseudo(pseudo);

            while (nbErreur < 10 && motMasque != motToFind) {
                inputMot(motToFind, nbErreur, motMasque, lstLettre, lettrePlayer);
                testLettreInMot(lstLettre, lettrePlayer, motToFind, motMasque, nbErreur);
            }

            affResultat(motMasque, motToFind, pseudo, nbErreur);
        } else {
            cout<<"Une erreur s'est produite lors de l'ouverture du fichier"<<endl;
        }
        cout<<endl;
        leadRead();
        cout<<endl;
    }

private:
    static string getRandomMot(list<string> lstMot) {
        srand(static_cast<unsigned>(time(nullptr)));
        int indice = rand() % lstMot.size();
        auto it = lstMot.begin();
        advance(it, indice);
        string motTemp = *it;

        return motTemp;
    }

    static void lstIncrement(list<string> & lstMot) {
        ifstream penduWiki("text/penduDico.txt");
        if (penduWiki) {
            penduWiki.clear();
            penduWiki.seekg(0, ios::beg);
            string mot;
            while (penduWiki >> mot) {
                lstMot.push_back(mot);
            }
        }
    }

    static void inputPseudo(string & pseudo) {
        cout<<"Saisissez votre pseudo : ";
        cin>>pseudo;
    }

    static void testLettreInMot(string & lstLettre, char lettrePlayer, string & motToFind, string & motMasque, int & nbErreur) {
        size_t positionLettre = lstLettre.find(lettrePlayer);
        if (positionLettre != string::npos) {
            cout<<"Vous avez déjà proposé la lettre "<<lettrePlayer<<" !"<<endl;
        } else {
            lstLettre.push_back(lettrePlayer);
            size_t position = motToFind.find(lettrePlayer);
            if (position != string::npos) {
                for (size_t i = 0; i < motToFind.size(); i++) {
                    if (motToFind[i] == lettrePlayer) {
                        motMasque[i] = lettrePlayer;
                    }
                }
                cout<<"La lettre "<<lettrePlayer<<" est présente !"<<endl;
            } else {
                nbErreur++;
                cout<<"Vous avez "<<nbErreur<<" erreurs !"<<endl;
            }
        }
        if (nbErreur>=1) {
            afficherPendu(nbErreur);
        }
    }

    static void inputMot(string motToFind, int nbErreur, string motMasque, string lstLettre, char & lettrePlayer) {
        cout<<"\nLe mot est en "<<motToFind.size()<<" lettres, et il vous reste "<<10-nbErreur<<" erreurs possibles !"<<endl;
        cout<<"Mot masqué : "<<motMasque<<endl;
        cout<<"Lettres proposées : "<<lstLettre<<endl;
        cout<<"Donner une lettre : ";
        cin>>lettrePlayer;
        
        system("clear");
    }

    static void affResultat(string motMasque, string motToFind, string pseudo, int nbErreur) {
        system("clear");
        if (motMasque == motToFind) {
            cout<<"Bravo, vous avez trouvé le mot : "<<motToFind<<" ! Vous vous appelez surement Robert..."<<endl;
            leadWrite(pseudo, 10 - nbErreur/2);
        } else {
            cout<<"Vous avez dépassé le nombre maximal d'erreurs ! Le mot était : "<<motToFind<<endl;
            leadWrite(pseudo, -5);
        }
    }

    static void afficherPendu(int erreurs) {
        cout << "\n";
        switch (erreurs) {
            case 1:
                cout << "_______" << endl;
                break;
            case 2:
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|_______" << endl;
                break;
            case 3:
                cout << " ____" << endl; 
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|_______" << endl;
                break;
            case 4:
                cout << " ____" << endl; 
                cout << "|    |" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|_______" << endl;
                break;
            case 5:
                cout << " ____" << endl; 
                cout << "|/   |" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|_______" << endl;
                break;
            case 6:
                cout << " ____" << endl;
                cout << "|/   |" << endl;
                cout << "|    O" << endl;
                cout << "|    |" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|_______" << endl;
                break;
            case 7:
                cout << " ____" << endl;
                cout << "|/   |" << endl;
                cout << "|    O" << endl;
                cout << "|   /|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|_______" << endl;
                break;
            case 8:
                cout << " ____" << endl;
                cout << "|/   |" << endl;
                cout << "|    O" << endl;
                cout << "|   /|\\" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|_______" << endl;
                break;
            case 9:
                cout << " ____" << endl;
                cout << "|/   |" << endl;
                cout << "|    O" << endl;
                cout << "|   /|\\" << endl;
                cout << "|   /" << endl;
                cout << "|" << endl;
                cout << "|_______" << endl;
                break;
            default:
                cout << " ____" << endl;
                cout << "|/   |" << endl;
                cout << "|    O" << endl;
                cout << "|   /|\\" << endl;
                cout << "|   / \\" << endl;
                cout << "|" << endl;
                cout << "|_______" << endl;
                break;
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
        ofstream leaderboardFile("text/leaderboard_pendu.txt");
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
        ifstream leaderboardFile("text/leaderboard_pendu.txt");

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
        cout<<"  ____    _____   _   _   ____    _   _ "<<endl;
        cout<<" |  _ \\  | ____| | \\ | | |  _ \\  | | | |"<<endl;
        cout<<" | |_) | |  _|   |  \\| | | | | | | | | |"<<endl;
        cout<<" |  __/  | |___  | |\\  | | |_| | | |_| |"<<endl;
        cout<<" |_|     |_____| |_| \\_| |____/   \\___/ "<<endl;
        cout<<endl;
    }

    static void affRegles(string supp) {
        cout<<endl;
        cout<<"\n\x1b[31mVOICI LES REGLES :\x1b[0m"<<endl;
        cout<<"Le mot à trouver est en "<<supp.size()<<" lettres !"<<endl;
        cout<<"Vous avez le droit à 10 erreurs !"<<endl;
        cout<<"Attention, certains mots comportent des accents mais il ne faut pas les mettres ! Exemple : résumé deviens resume."<<endl;
    }
};