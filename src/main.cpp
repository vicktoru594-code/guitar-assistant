#include <iostream>
#include "chord.h"
#include "tracker.h"
#include "song.h"

using namespace std;

int main(){
    int mainChoice;

    do{
        cout <<"\n🎸 GUITAR MASTER v1.0 🎸" << endl;
        cout << "1. Аккорды" << endl;
        cout << "2. Трекер практики" << endl;
        cout << "3. Песни" << endl;
        cout << "4. Метроном" << endl;
        cout << "0. Выход" << endl;
        cout << ">> ";

        cin >> mainChoice;

        switch (mainChoice){
            case 1:
                int subChoice1;
                do{
                    showChordMenu();
                    cin >> subChoice1;
                    if (subChoice1 == 1){
                        Chord testChord = {"Am", {-1, 0, 2, 2, 1, 0}};
                        printChord(testChord);
                    } else if (subChoice1 == 2){
                        Chord myChord = addChordInteractive();
                        printChord(myChord);
                    
                    }else if (subChoice1 != 0){
                        cout << "Функция в разработке..." << endl;
                    }
                }while (subChoice1 != 0);
                break;
        
            case 2:
                int subChoice2;
                do{
                    showTrackerMenu();
                    cin >> subChoice2;
                    if (subChoice2 != 0) cout << "Функция в разработке..." << endl;
                }while (subChoice2 != 0);
                break;

            case 3:
                int subChoice3;
                do{
                    showSongMenu();
                    cin >> subChoice3;
                    if (subChoice3 != 0) cout << "Функция в разработке..." << endl;
                }while (subChoice3 != 0);
                break;
            
            case 4:
                cout << "Метроном в разработке..." << endl;
                break;
            
            case 0:
                cout << "До встречи! 🎶" << endl;
                break;
            default:
                cout << "Неверный ввод." << endl;
                break;
        }
    }while (mainChoice != 0);

    return 0;
}