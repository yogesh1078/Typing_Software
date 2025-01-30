#include"login_signup.h"

// Function to check if credentials are correct
bool checkCredentials(const string& username, const string& password) {
    ifstream file("credentials.txt");
    string line, fileUsername, filePassword;

    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream iss(line);
            if (iss >> fileUsername >> filePassword) {
                if (fileUsername == username && filePassword == password) {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
    } else {
        cout << "Unable to open credentials file." << endl;
    }
    return false;
   }

// Function to handle login
void login(bool &isLogged,string &username, string &password) {
   

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Clear the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Check if the credentials are correct
    if (checkCredentials(username, password)) {
        cout << "Login successful!" << endl;
        cout<<"----------------------------------------------------------------------------------"<<endl;
        isLogged = true;
       
    } else {
        cout << "Invalid username or password. Please try again." << endl;
        cout<<"-----------------------------------------------------------------------------------"<<endl;
    }
}

// check password validation

bool isValidPassword(const string& password) {
    // Regex pattern to check for at least one digit and one special character,
    // with a minimum length of 7
    regex pattern("^(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{7,}$");

    // Check if the password matches the pattern
    return regex_match(password, pattern);
}

 bool isValidName(const string& name) {
    // Regular expression to match alphabetic names only
    regex pattern("^[A-Za-z]+$");
    
    // Return true if the name matches the pattern
    return regex_match(name, pattern);
 }

bool isUsernameValid(const string& username) {
    // Regular expression to check:
    // - The first two characters should be alphabetic.
    // - The entire username should have at least four characters.
    regex pattern("^[A-Za-z]{2}.*");
    
    // Check if the username has at least four characters
    if (username.length() < 4) {
        return false;
    }
    
    // Check if the username matches the pattern
    return regex_match(username, pattern);
}


// Function to handle signup
void signup() {
    string username, password, confirmPassword;
    string FirstName, LastName, FullName;
    int signup_option;
     
    cout << "Enter Your First Name(It should not contain any other symbol accept alphabets): ";
            cin >> FirstName;
     
            cout << "Enter Your Last Name (If No last Name then enter first name as "
                 "last name) And (It should not contain any other symbol accept name  : ";
           cin >> LastName;

           FullName = FirstName + '#' + LastName;

             if(!isValidName(FirstName) && !isValidName(LastName)){
              cout<<"Name does not satisfy the condition"<<endl;
              return;
              }
  

      do {

           cout << "Enter a new username (Username contains minimum Four characters and first two character only alphabets) :  ";
           cin >> username;

        if (!isUsernameValid(username)) {

           cout << "Username does not satisfy condition Try again!" << endl;
          return;
        }



        cout << "Enter a new password: (Password contains minimum 7 characters "
                "and has minimum 1 number and 1 special symbol(@$!%*?&) )"
             << endl;
        cin >> password;

        if (isValidPassword(password)) {
            cout << "Confirm your password: ";
            cin >> confirmPassword;

            // Clear the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (password != confirmPassword) {
                cout << "Passwords do not match. Please try again." << endl;
                cout<<"-----------------------------------------------------------------------"<<endl;
                return;
            }

            // Check if the username already exists
            ifstream file("credentials.txt");
            string line, fileUsername;

            while (getline(file, line)) {
                istringstream iss(line);
                if (iss >> fileUsername) {
                    if (fileUsername == username) {
                        cout << "Username already exists. Please choose a "
                                "different username."
                             << endl;
                             
                             cout<<"-----------------------------------------------------------"<<endl;
                        file.close();
                        return;
                    }
                }
            }
            file.close();

            // Add new user to the file
            ofstream outfile("credentials.txt", ios::app);
            if (outfile.is_open()) {
                outfile << username << " " << password << " "
                        << "0"
                        << " " << FullName << endl;
                outfile.close();
                cout << "Signup successful! You can now log in with your new "
                        "credentials."
                     << endl;
                     
                cout<<"------------------------------------------------------------------"<<endl;
                break;
            } else {
                cout << "Unable to open credentials file for writing." << endl;
            }

        } else {
            cout << "Password does not satisfy the conditions." << endl;
        }

        // Prompt to exit or continue signup
        cout << endl
             << "If you want to leave the signup page, press 1. Otherwise, "
                "press another numeric key."
             << endl;
        cin >> signup_option;

        // If input is invalid, clear the input stream
        if (cin.fail()) {
            cin.clear(); // clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(),
                       '\n');  // discard the invalid input
            signup_option = 0; // assume the user wants to continue by default
        }

    } while (signup_option != 1);
}




