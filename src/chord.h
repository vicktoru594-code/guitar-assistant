#ifndef CHORD_H
#define CHORD_H

#include <string>
#include <vector>

struct Chord{
    std::string name;
    std::vector<int> frets;
};

void showChordMenu();
void printChord(const Chord& c);
Chord addChordInteractive();

#endif