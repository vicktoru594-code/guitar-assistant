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
    cout << "\nАккорд: " << c.name << endl;
    cout << "E A D G C E" << endl;
    cout << "| | | | | |" << endl;

    for (int f : c.frets){
        cout << f << " ";
    }
    cout << endl;
}