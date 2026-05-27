#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>

struct Song{
    std::string name;
    std::string author;
    std::vector<std::string> chords;
    std::string comment;
};

extern std::vector<Song> songsDatabase;

void showSongMenu();
void addSong();
void saveSongsToFile();

#endif