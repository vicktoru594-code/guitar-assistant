#include "tracker.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void showTrackerMenu(){
    cout << "\n----  ТРЕКЕР ПРАКТИКИ ----" << endl;
    cout << "1. Записать тренировку" << endl;
    cout << "2. Посмотреть историю" << endl;
    cout << "0. Назад в главное меню" << endl;
    cout << "Ваш выбор: ";
}

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
    return string(buffer);
}

void addPracticeSession(std::vector<PracticeSession>& sessions){
    PracticeSession session;
    
    cout << "\n--- Новая тренировка ---" << endl;
    
    session.date = getCurrentDate();
    cout << "Дата: " << session.date << endl;
    
    cout << "Длительность (минуты): ";
    cin >> session.durationMinutes;
    
    cout << "Комментарий (что учили/играли): ";
    cin.ignore();
    getline(cin, session.notes);
    
    sessions.push_back(session);
    
    cout << "✅ Тренировка записана!" << endl;
}

void printHistory(const std::vector<PracticeSession>& sessions){
    cout << "\n--- История практики ---" << endl;
    
    if (sessions.empty()) {
        cout << "История пуста. Начни практиковаться!" << endl;
        return;
    }
    
    int totalMinutes = 0;
    
    for (const auto& s : sessions) {
        cout << "📅 " << s.date 
             << " | ⏱️ " << s.durationMinutes << " мин" 
             << " | 📝 " << s.notes << endl;
        totalMinutes += s.durationMinutes;
    }
    
    cout << "--------------------------" << endl;
    cout << "Всего тренировок: " << sessions.size() << endl;
    cout << "Общее время: " << totalMinutes << " минут (" 
         << totalMinutes / 60 << " ч. " << totalMinutes % 60 << " мин.)" << endl;
}

void savePracticeToFile(const vector<PracticeSession>& sessions, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()){
        cerr << "Ошмбка: не удалось открыть файл для записи" <<endl;
        return;
    }

    for (const auto& s : sessions) {
        file << s.date << "|" << s.durationMinutes << "|" << s.notes << endl;
    }
    file.close();
}

vector<PracticeSession> loadPracticeFromFile(const string& filename) {
    vector<PracticeSession> sessions;
    ifstream file(filename);
    
    if (!file.is_open()) {
        return sessions;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        PracticeSession s;
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        
        if (pos1 != string::npos && pos2 != string::npos) {
            s.date = line.substr(0, pos1);
            s.durationMinutes = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            s.notes = line.substr(pos2 + 1);
            sessions.push_back(s);
        }
    }
    file.close();
    return sessions;
}