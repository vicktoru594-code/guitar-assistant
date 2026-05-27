#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Подключаем заголовки вашего проекта
// Важно: так как мы используем -I./src, пишем просто имя файла
#include "song.h"
#include "chord.h"
#include "tracker.h"

// Объявляем внешние переменные, которые используются в src/
// Это нужно, чтобы тесты видели глобальный вектор песен
extern std::vector<Song> songsDatabase;

// ============================================================
// SECTION: Helpers
// ============================================================

int init_suite(void) {
#ifdef _WIN32
    _mkdir("test_data");
#else
    mkdir("test_data", 0755);
#endif
    return 0;
}

int clean_suite(void) {
    remove("test_data/songs.txt");
    remove("test_data/chords.txt");
    remove("test_data/practice_tracker.txt");
    return 0;
}

// ============================================================
// SECTION: Tests
// ============================================================

// 1. Проверка структуры Песни
void test_song_struct_and_chords(void) {
    Song s;
    s.name = "Test Song";
    s.author = "Artist";
    s.chords.push_back("Em");
    s.chords.push_back("C");
    
    // Для std::string нельзя использовать CU_ASSERT_STRING_EQUAL напрямую без .c_str()
    // Но лучше использовать стандартные проверки C++ для надежности
    CU_ASSERT(s.name == "Test Song");
    CU_ASSERT(s.author == "Artist");
    CU_ASSERT_EQUAL(s.chords.size(), 2);
    CU_ASSERT(s.chords[0] == "Em");
}

void test_song_persistence_logic(void) {
    songsDatabase.clear();
    
    Song s;
    s.name = "SaveTest";
    s.author = "Author";
    s.chords.push_back("Am");
    songsDatabase.push_back(s);
    
    CU_ASSERT_EQUAL(songsDatabase.size(), 1);
    CU_ASSERT(songsDatabase[0].name == "SaveTest");
}

void test_chord_struct(void) {
    Chord c;
    c.name = "G";
    c.frets = {3, 2, 0, 0, 0, 3};
    
    CU_ASSERT(c.name == "G");
    CU_ASSERT_EQUAL(c.frets[0], 3);
}

void test_practice_session(void) {
    PracticeSession sess;
    sess.date = "2026-05-28";
    sess.durationMinutes = 45;
    
    CU_ASSERT(sess.date == "2026-05-28");
    CU_ASSERT_EQUAL(sess.durationMinutes, 45);
}

void test_metronome_logic(void) {
    int bpm = 120;
    int expected_ms = 500;
    int calculated_ms = 60000 / bpm;
    
    CU_ASSERT_EQUAL(calculated_ms, expected_ms);
}


int main() {
    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();
    
    CU_pSuite pSuite = CU_add_suite("Core Modules Tests", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test_song_struct_and_chords", test_song_struct_and_chords) ||
        NULL == CU_add_test(pSuite, "test_song_persistence_logic", test_song_persistence_logic) ||
        NULL == CU_add_test(pSuite, "test_chord_struct", test_chord_struct) ||
        NULL == CU_add_test(pSuite, "test_practice_session", test_practice_session) ||
        NULL == CU_add_test(pSuite, "test_metronome_logic", test_metronome_logic)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_ErrorCode result = CU_basic_run_tests();
    
    printf("\n========================================\n");
    printf("Tests completed.\n");
    printf("========================================\n");
    
    CU_cleanup_registry();
    return result;
}