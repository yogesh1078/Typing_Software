#ifndef USER_CHOICE_H
#define USER_CHOICE_H

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib> // for system("clear")

// Assuming you have other header files for login, signup, practice, leaderboard, and test functionality.
#include "login_signup.h"
#include "practice_option.h"
#include "leaderboard.h"
#include "Timing_test_option.h"

using namespace std;

// Function declarations for the features used in choices function
void printDecorativeLine(int, char, char);
void printLineWithStars(int, char, char, int);
void printCenteredText(int, string);
void printWelcomeBox();
void choices(); // This will manage user interactions

#endif // USER_CHOICE_H

