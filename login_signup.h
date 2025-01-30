#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <limits>
#include <string>

using namespace std;

// Function prototypes
void login(bool &, string &, string &);
bool checkCredentials(const string&, const string& ); 
bool isValidPassword(const string&);
void signup();

#endif // AUTHENTICATION_H

