#ifndef CHORD_H
#define CHORD_H

#include <string>
#include <vector>
#include <fstream>

struct Chord{
    std::string name;
    std::vector<int> frets;
};

void showChordMenu();
void printChord(const Chord& c);
Chord addChordInteractive();
void saveChordToFile(const std::vector<Chord>& chords, const std::string& filename);
std::vector<Chord> leadChordsFromFile(const std::string& filename);

#endif