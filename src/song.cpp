#include "song.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

vector<Song> songsDatabase;

void showSongMenu(){
    cout << "\n----  МОИ ПЕСНИ ----" << endl;
    cout << "1. Добавить песню" << endl;
    cout << "2. Список песен" << endl;
    cout << "0. Назад в главное меню" << endl;
    cout << "Ваш выбор: ";
}

void saveSongsToFile() {
    ofstream file("data/songs.txt");
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось сохранить песни." << endl;
        return;
    }

    for (const auto& song : songsDatabase) {
        file << "---SONG_START---" << endl;
        file << "---NAME---" << endl;
        file << song.name << endl;
        file << "---AUTHOR---" << endl;
        file << song.author << endl;
        file << "---CHORDS_START---" << endl;
        for (const auto& chordLine : song.chords) {
            file << chordLine << endl;
        }
        file << "---CHORDS_END---" << endl;
    }
    file.close();
}

void addSong() {
    Song newSong;
    
    cout << "\n--- Добавление новой песни ---" << endl;
    
    cout << "Название песни: ";
    cin.ignore();
    getline(cin, newSong.name);
    
    cout << "Исполнитель: ";
    getline(cin, newSong.author);
    
    cout << "Введите аккорды (построчно). Для завершения введите пустую строку:" << endl;
    string line;
    while (true) {
        getline(cin, line);
        if (line.empty()) break;
        newSong.chords.push_back(line);
    }
    
    songsDatabase.push_back(newSong);
    saveSongsToFile();
    cout << "✅ Песня '" << newSong.name << "' добавлена и сохранена!" << endl;
}




