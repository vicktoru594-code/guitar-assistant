#include "song.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream> 

using namespace std;

vector<Song> songsDatabase;

void showSongMenu(){
    cout << "\n----  МОИ ПЕСНИ ----" << endl;
    cout << "1. Добавить песню" << endl;
    cout << "2. Список песен" << endl;
    cout << "3. Просмотреть детали песни" << endl;
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

        file << "---COMMENT_START---" << endl;
        file << song.comment << endl;
        file << "---COMMENT_END---" << endl;
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

    cout << "Комментарий (каподастр, рекомендуемый бой, нюансы): " << endl;
    getline(cin, newSong.comment);
    
    songsDatabase.push_back(newSong);
    saveSongsToFile();
    cout << "✅ Песня '" << newSong.name << "' добавлена и сохранена!" << endl;
}

void loadSongsFromFile() {
    ifstream file("data/songs.txt");
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line == "---SONG_START---") {
            Song newSong;

            if (getline(file, line) && line == "---NAME---") {
                getline(file, newSong.name);
            }

            if (getline(file, line) && line == "---AUTHOR---") {
                getline(file, newSong.author);
            }

            if (getline(file, line) && line == "---CHORDS_START---") {
                while (getline(file, line)) {
                    if (line == "---CHORDS_END---") break;
                    newSong.chords.push_back(line);
                }
            }

            if (getline(file, line) && line == "---COMMENT_START---") {
                string commentLine;
                while (getline(file, commentLine)) {
                    if (commentLine == "---COMMENT_END---") break;
                    if (!newSong.comment.empty()) newSong.comment += "\n"; 
                    newSong.comment += commentLine;
                }
            }

            songsDatabase.push_back(newSong);
        }
    }
    file.close();
}

void listAllSongs() {
    if (songsDatabase.empty()) {
        cout << "\n📂 Список пуст. Добавьте первую песню!" << endl;
        return;
    }

    cout << "\n ВАША БИБЛИОТЕКА ПЕСЕН:" << endl;
    cout << "----------------------------------------" << endl;

    for (size_t i = 0; i < songsDatabase.size(); ++i) {
        const Song& s = songsDatabase[i];
        
        cout << "[" << (i + 1) << "] " << s.name << " — " << s.author << endl;
        
        cout << "   Аккорды: ";
        if (!s.chords.empty()) {
            int linesToShow = min((int)s.chords.size(), 3);
            for (int j = 0; j < linesToShow; ++j) {
                cout << s.chords[j] << " ";
            }
            if (s.chords.size() > 3) cout << "...";
        } else {
            cout << "(нет аккордов)";
        }
        cout << endl;

        if (!s.comment.empty()) {
            cout << "   💬 " << s.comment.substr(0, 50);
            if (s.comment.length() > 50) cout << "...";
            cout << endl;
        }
        cout << "----------------------------------------" << endl;
    }
    
}

void viewSongDetails(int index){
    if (index < 0 || index >= static_cast<int>(songsDatabase.size())) {
        cout << "\n❌ Ошибка: Песни с таким номером не существует." << endl;
        return;
    }

    const Song& s = songsDatabase[index];

    cout << "\n========================================" << endl;
    cout << "🎵 ПОДРОБНОСТИ ПЕСНИ #" << (index + 1) << endl;
    cout << "========================================" << endl;
    
    cout << "Название:   " << s.name << endl;
    cout << "Исполнитель: " << s.author << endl;
    
    cout << "\n--- АККОРДЫ ---" << endl;
    if (s.chords.empty()) {
        cout << "(Аккорды не указаны)" << endl;
    } else {
        for (const auto& chordLine : s.chords) {
            cout << chordLine << endl;
        }
    }

    if (!s.comment.empty()) {
        cout << "\n--- КОММЕНТАРИЙ ---" << endl;
        cout << s.comment << endl;
    }

    cout << "========================================" << endl;
}

