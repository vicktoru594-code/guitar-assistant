#include "chord.h"
#include <iostream>

using namespace std;

void showChordMenu(){
    cout << "\n----  БИБЛИОТЕКА АККОРДОВ ----" << endl;
    cout << "1. Показать популярные аккорды" << endl;
    cout << "2. Добавить свой аккорд" << endl;
    cout << "0. Назад в главное меню" << endl;
    cout << "Ваш выбор: ";
}

void printChord(const Chord& c){
    cout << "\n Аккорд: " << c.name << endl;
    cout << " ------------------" << endl;
    
    vector<string> stringNames = {"E", "B", "G", "D", "A", "E"};

    for (int i=5;i>=0;i--){
        int fret = c.frets[i];
        string symbol = "-";

        if (fret == 0) symbol = "0";
        else if (fret == -1) symbol = "X";
        else symbol = to_string(fret);

        cout << "  " << stringNames[5-i] << " | " << symbol << endl;
    }
    
    cout << " ------------------" << endl;
}