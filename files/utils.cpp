#include <iostream>

using namespace std;

class Utils {
public:
    static void affTitle(string game) {
        if(game == "pendu") {
            cout<<"\n  ____    _____   _   _   ____    _   _ "<<endl;
            cout<<" |  _ \\  | ____| | \\ | | |  _ \\  | | | |"<<endl;
            cout<<" | |_) | |  _|   |  \\| | | | | | | | | |"<<endl;
            cout<<" |  __/  | |___  | |\\  | | |_| | | |_| |"<<endl;
            cout<<" |_|     |_____| |_| \\_| |____/   \\___/ "<<endl;
        } else if(game == "pfc") {
            cout<<"\n  ____    _                                  __  _____                  _   _   _             __   ____   _                              "<<endl;
            cout<<" |  _ \\  (_)   ___   _ __   _ __    ___     / / |  ___|   ___   _   _  (_) | | | |   ___     / /  / ___| (_)  ___    ___    __ _   _   _ "<<endl;
            cout<<" | |_) | | |  / _ \\ | '__| | '__|  / _ \\   / /  | |_     / _ \\ | | | | | | | | | |  / _ \\   / /  | |     | | / __|  / _ \\  / _` | | | | |"<<endl;
            cout<<" |  __/  | | |  __/ | |    | |    |  __/  / /   |  _|   |  __/ | |_| | | | | | | | |  __/  / /   | |___  | | \\__ \\ |  __/ | (_| | | |_| |"<<endl;
            cout<<" |_|     |_|  \\___| |_|    |_|     \\___| /_/    |_|      \\___|  \\__,_| |_| |_| |_|  \\___| /_/     \\____| |_| |___/  \\___|  \\__,_|  \\__,_|"<<endl;
            cout<<endl;
        }
    }

    static void affRegles(string game, string supp) {
        if(game=="pendu") {
            cout<<"\nLe mot à trouver est en "<<supp.size()<<" lettres !"<<endl;
            cout<<"Vous avez le droit à 10 erreurs !"<<endl;
            cout<<"Attention, certains mots comportent des accents mais il ne faut pas les mettres ! Exemple : résumé deviens resume."<<endl;
        }
    }
};