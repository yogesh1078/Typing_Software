#ifndef PRACTICE_OPTION_H
#define PRACTICE_OPTION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "login_signup.h"

using namespace std;

// Function to check and update credentials in the credentials file
void checkAndUpdateCredentials(const string& username, const string& password, int currentWPM);

// Function to choose a text file for typing practice and return the chosen lines
void field_choosen(string file_name, string& stored);

// Main function to handle typing practice, compare typed and stored words, and display results
void practice(const string& username, const string& password);

#endif // PRACTICE_OPTION_H

