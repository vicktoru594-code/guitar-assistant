#include "chord.h"
#include <iostream>
#include <vector>
#include <string>

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

Chord addChordInteractive(){
    Chord newChord;

    cout << "\n----- Добавление нового аккорда -----" << endl;
    cout << "Введите название аккорда: ";
    cin.ignore();
    getline(cin, newChord.name);

    cout << "Введите лады для струн (от 6-ой к 1-ой):" << endl;
    cout << "(Используйте 0, если струна открыта, и -1, если струна не звучит)" << endl;

    vector<int> tempFrets(6);
    string strings[]= {"E", "A", "D", "G", "B", "E"};

    for (int i=0;i<6;i++){
        cout << "Струна " << strings[i] << ": ";
        cin >> tempFrets[i];
    }

    newChord.frets = tempFrets;

    cout << "Аккорд '" << newChord.name << "' создан!" << endl;
    return newChord;
}