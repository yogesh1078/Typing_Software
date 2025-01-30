#ifndef TIMING_TEST_OPTION_H
#define TIMING_TEST_OPTION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>
using namespace std;
// Function to display results from result.txt file
void show_results_from_file(const string& fileName);

// Function to get system time as a string
string system_time();

// Function to calculate WPM
int calculate_wpm(int wordCount, double timeInSeconds);

// Function to split text into words
vector<string> split_into_words(const string& line);

// Function to read lines from text.txt file
vector<string> read_lines_from_file(const string& fileName);

// Function to save the results to result.txt file
void save_results_to_file(int wpm, int wrongWords, int correctWords, int totalWords, double timeTaken);

// Function to wrap text according to window width
vector<string> wrap_text(const string& text, int maxWidth);

// Function to run the typing test with a time limit
void test(int time_limit);

#endif // TIMING_TEST_OPTION_H

