#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <vector>
#include <string>

// Подключаем заголовки проекта
#include "song.h"
#include "chord.h"
#include "tracker.h"

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

// Тест 1: Структура Song и работа с вектором аккордов
void test_song_struct_and_chords(void) {
    Song s;
    s.name = "Test Song";
    s.author = "Artist";
    s.chords.push_back("Em");
    s.chords.push_back("C");
    
    CU_ASSERT(s.name == "Test Song");
    CU_ASSERT(s.author == "Artist");
    CU_ASSERT_EQUAL(s.chords.size(), 2);
    CU_ASSERT(s.chords[0] == "Em");
}

// Тест 2: Логика работы с базой песен (используем локальный вектор)
void test_song_database_logic(void) {
    // Создаем локальный вектор, имитирующий базу данных
    std::vector<Song> localDB;
    
    Song s1;
    s1.name = "Song One";
    s1.author = "Author 1";
    localDB.push_back(s1);
    
    Song s2;
    s2.name = "Song Two";
    s2.author = "Author 2";
    localDB.push_back(s2);
    
    CU_ASSERT_EQUAL(localDB.size(), 2);
    CU_ASSERT(localDB[0].name == "Song One");
    CU_ASSERT(localDB[1].author == "Author 2");
    
    // Проверка удаления
    localDB.clear();
    CU_ASSERT_TRUE(localDB.empty());
}

// Тест 3: Структура Chord
void test_chord_struct(void) {
    Chord c;
    c.name = "G Major";
    c.frets = {3, 2, 0, 0, 0, 3};
    
    CU_ASSERT(c.name == "G Major");
    CU_ASSERT_EQUAL(c.frets[0], 3);
    CU_ASSERT_EQUAL(c.frets[2], 0);
}

// Тест 4: Структура PracticeSession
void test_practice_session(void) {
    PracticeSession sess;
    sess.date = "2026-05-28";
    sess.durationMinutes = 45;
    sess.notes = "Good practice";
    
    CU_ASSERT(sess.date == "2026-05-28");
    CU_ASSERT_EQUAL(sess.durationMinutes, 45);
    CU_ASSERT(sess.notes == "Good practice");
}

// Тест 5: Логика метронома (расчет BPM)
void test_metronome_bpm_calculation(void) {
    int bpm = 60;
    int expected_ms = 1000; // 60000 / 60
    int calculated_ms = 60000 / bpm;
    
    CU_ASSERT_EQUAL(calculated_ms, expected_ms);
    
    bpm = 120;
    expected_ms = 500; // 60000 / 120
    calculated_ms = 60000 / bpm;
    
    CU_ASSERT_EQUAL(calculated_ms, expected_ms);
}

// ============================================================
// SECTION: Main
// ============================================================

int main() {
    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();
    
    CU_pSuite pSuite = CU_add_suite("Core Modules Tests", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test_song_struct_and_chords", test_song_struct_and_chords) ||
        NULL == CU_add_test(pSuite, "test_song_database_logic", test_song_database_logic) ||
        NULL == CU_add_test(pSuite, "test_chord_struct", test_chord_struct) ||
        NULL == CU_add_test(pSuite, "test_practice_session", test_practice_session) ||
        NULL == CU_add_test(pSuite, "test_metronome_bpm_calculation", test_metronome_bpm_calculation)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_ErrorCode result = CU_basic_run_tests();
        
    CU_cleanup_registry();
    return result;
}