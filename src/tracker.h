#ifndef TRACKER_H
#define TRACKER_H

#include <string>
#include <vector>
#include <fstream>

struct PracticeSession{
    std::string date;
    int durationMinutes;
    std::string notes;
};

void showTrackerMenu();
void addPracticeSession(std::vector<PracticeSession>& sessions);
void printHistory(const std::vector<PracticeSession>& sessions);
void savePracticeToFile(const std::vector<PracticeSession>& sessions, const std::string& filename);
std::vector<PracticeSession> loadPracticeFromFile(const std::string& filename);

#endif

