#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>

struct Song{
    std::string name;
    std::string autor;
    std::vector<std::string> chords;
};

void showSongMenu();


#endif