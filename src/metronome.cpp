#include "metronome.h"
#include <iostream>
#include <chrono>
#include <limits>
#include <thread>

using namespace std;

void sleep_ms(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void showMetronomeMenu(){
    cout << "\n---- Метроном ----" << endl;
    cout << "1. Запустить метроном" << endl;
    // cout << "2. Посмотреть историю" << endl;
    cout << "0. Назад в главное меню" << endl;
    cout << "Ваш выбор: ";
}

void startMetronome(){
    int bpm=60;
    int timeSignature = 4;

    cout << "\n--- Настройка метронома ---" << endl;
    
    cout << "Введите темп (BPM, ударов в минуту) [60-200]: ";
    cin >> bpm;

     if (bpm < 40) bpm = 40;
    if (bpm > 240) bpm = 240;

    cout << "Введите размер такта (число долей в такте) [2, 3, 4, 5...]: ";
    cin >> timeSignature;
    if (timeSignature < 1) timeSignature = 4;

    cout << "\nЗапуск метронома ([ X ] - сильная доля, [ . ] - слабая доля): " << bpm << " BPM, размер " << timeSignature << "/4" << endl;

    int beatDurationMs = (60000 / bpm);
    int currentBeat = 1;
    bool isRunning = true;

      cout << "Метроном отработает 10 тактов и остановится." << endl;
    cout << "----------------------------------------" << endl;

    for (int measure = 0; measure < 10; ++measure) {
        for (int beat = 1; beat <= timeSignature; ++beat) {
            if (beat == 1) {
                cout << "\r[ X ] "; 
            } else {
                cout << "\r[ . ] "; 
            }
            
            cout.flush();
            
            sleep_ms(beatDurationMs);
            
        }
        cout << endl;
    }

    cout << "\nМетроном остановлен." << endl;
}