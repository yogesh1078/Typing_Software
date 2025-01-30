#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// User struct to store user details
struct User {
    string username;
    int maxWpm;
    string User_FullName;
};

// Function prototypes
bool compareWpm(const User& a, const User& b);
void leaderboard();

#endif // LEADERBOARD_H

