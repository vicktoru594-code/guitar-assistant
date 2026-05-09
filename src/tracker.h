#ifndef TRACKER_H
#define TRACKER_H

#include <string>

struct PracticeSession{
    std::string date;
    int durationMitutes;
    std::string notes;
};

void showTrackerMenu();

#endif

