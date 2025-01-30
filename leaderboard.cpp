#include"leaderboard.h"

bool compareWpm(const User& a, const User& b) {
    return a.maxWpm > b.maxWpm; // Sort in descending order
}

void leaderboard() {
    ifstream file("credentials.txt");
    string line;

    vector<User> users;

    // Read the file and parse each line
    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream iss(line);
            string username, password, FullName, FirstName, LastName;
            int maxWpm;

            if (iss >> username >> password >> maxWpm >> FullName) {

                int i = 0;
                while (i < FullName.length()) {
                    if (FullName[i] == '#') {
                        i++;
                        break;
                    }
                    FirstName += FullName[i];
                    i++;
                }
                while (i < FullName.length()) {
                    LastName += FullName[i];
                    i++;
                }

                if (FirstName == LastName) {
                    FullName = FirstName;
                } else {
                    FullName = FirstName + " " + LastName;
                }

                users.push_back({username, maxWpm, FullName});
            }
        }
        file.close();
    } else {
        cout << "Unable to open file." << std::endl;
        return;
    }

    // Sort the users by maxWpm in descending order
    sort(users.begin(), users.end(), compareWpm);

    // Display the leaderboard
    // cout << "Rank\tUsername\tMax WPM" << std::endl;
    // cout << "---------------------------------" << std::endl;
    cout << setw(10) << left << "Rank #" << setw(20) << "FullName" << setw(20)
         << "Username" << setw(20) << "Max WPM" << endl;
    cout << "------------------------------------------------------------------"
            "---------------------------"
         << endl;

    int rank = 1;
    for (const auto& user : users) {
        cout << setw(10) << left << (rank++) << setw(20) << user.User_FullName
             << setw(20) << user.username << setw(20) << user.maxWpm << endl;
    }
}

