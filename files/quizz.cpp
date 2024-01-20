#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>

using namespace std;

class Quizz {
public:
    static void quizzGame() {
        system("clear");
        affTitle();
        affRegles();
        
        cout<<endl;
        leadRead();
        cout<<endl;

        string pseudo = "";
        saisiPseudo(pseudo);

        // Ouvrir le fichier contenant les questions et les réponses
        ifstream quizzWiki("text/quizzDico.txt");
        if (quizzWiki) {
            // Créer un dictionnaire pour stocker les questions et les réponses (Vrai/Faux)
            map<string, bool> quizz;

            incQuizz(quizz);

            // Fermer le fichier
            quizzWiki.close();
            system("clear");

            // Variables pour compter les erreurs et les réponses
            int nbErreurs = 0;
            int nbReponses = 0;

            // Poser chaque question au joueur
            saisiReponse(nbErreurs, nbReponses, quizz);

            // Afficher le résultat final
            affResultat(nbErreurs, nbReponses);
            
            leadWrite(pseudo, nbReponses - nbErreurs);
            cout<<endl;
            leadRead();
        } else {
            cout<<"Erreur lors de l'ouverture du fichier"<<endl;
        }
    }

private:
    static void affResultat(int nbErreurs, int nbReponses) {
        system("clear");
        cout<<"Nombre total de questions : "<<nbReponses<<endl;
        cout<<"Nombre d'erreurs : "<<nbErreurs<<endl;
        cout<<"Nombre de bonnes réponses : "<<nbReponses - nbErreurs<<endl;
    }
    
    static void saisiReponse(int nbErreurs, int nbReponses, map<string, bool> quizz) {
        for (const auto &pair : quizz) {
            const string &question = pair.first;
            bool answer = pair.second;

            // Afficher la question et obtenir la réponse du joueur (Vrai ou Faux)
            cout<<question<<endl;
            string playerAnswer;
            cout<<"Répondez avec 'Vrai' ou 'Faux' : ";
            cin>>playerAnswer;
            
            system("clear");

            // Vérifier si la réponse du joueur est correcte
            if(((playerAnswer == "Vrai" || playerAnswer == "vrai") && answer) || ((playerAnswer == "Faux" || playerAnswer == "faux") && !answer)) {
                cout<<"Bonne réponse !"<<endl;
            } else {
                cout<<"Mauvaise réponse."<<endl;
                nbErreurs++;
            }

            cout<<endl;
            nbReponses++;
        }
    }

    static void incQuizz(map<string, bool> & quizz) {
        ifstream quizzWiki("text/quizzDico.txt");
        if (quizzWiki) {
            string line;
            bool isQuestion = true;
            string currentQuestion;
            
            // Lire le fichier ligne par ligne
            while(getline(quizzWiki, line)) {
                if(isQuestion) {
                    // Stocker la question actuelle
                    currentQuestion = line;
                } else {
                    // Stocker la réponse (Vrai ou Faux)
                    bool isTrue = (line == "Vrai");
                    quizz[currentQuestion] = isTrue;
                }
                isQuestion = !isQuestion;
            }
        }
    }

    static void saisiPseudo(string & pseudo) {
        cout<<"Saisissez votre pseudo : ";
        cin>>pseudo;
    }

    static void leadWrite(const string & playerName, int score) {
        // Lire les données actuelles du leaderboard
        vector<pair<string, int>> leaderboardData = readLeaderboard();

        // Vérifier si le joueur existe déjà dans le leaderboard
        bool playerExists = false;
        for(auto& entry : leaderboardData) {
            if(entry.first == playerName) {
                // Le joueur existe, mettre à jour son score
                if(score>entry.second) {
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
        ofstream leaderboardFile("text/leaderboard_quizz.txt");
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

        cout << "\x1b[38;5;208mLEADERBOARD (notes) : \x1b[0m" << endl;
        
        if (leaderboardData.empty()) {
            cout << "Aucunes données" << endl;
        } else {
            for (const auto& entry : leaderboardData) {
                cout << entry.first << " : " << entry.second << " / 20" << endl;
            }
        }
    }

    static vector<pair<string, int>> readLeaderboard() {
        vector<pair<string, int>> leaderboardData;
        ifstream leaderboardFile("text/leaderboard_quizz.txt");

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
        cout<<"Le joueur fait face à un questionnaire de 20 questions auquels ils doit répondre par vrai ou faux."<<endl;
        cout<<"Si la réponse est juste, il gagne un point. Dans le cas inverse il ne perds ni gagne de points."<<endl;
        cout<<"La partie s'arrête quand le questionnaire est finit."<<endl;
    }

    static void affTitle() {
        cout<<endl;
        cout<<"   ___    _   _   ___   _____  _____"<<endl;
        cout<<"  / _ \\  | | | | |_ _| |__  / |__  /"<<endl;
        cout<<" | | | | | | | |  | |    / /    / / "<<endl;
        cout<<" | |_| | | |_| |  | |   / /_   / /_ "<<endl;
        cout<<"  \\__\\_\\  \\___/  |___| /____| /____|"<<endl;
        cout<<endl;
    }
};