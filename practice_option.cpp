#include"practice_option.h"

void checkAndUpdateCredentials(const string& username, const string& password,
                               int currentWPM) {
    // Open the file to read and write
    fstream file("credentials.txt", ios::in | ios::out);
    string line, fileUsername, filePassword,FullName;
    int fileWPM;
    vector<string> fileContents;

    if (!file.is_open()) {
        cout << "Unable to open credentials file." << endl;
    }

    // Read the file line by line
    while (getline(file, line)) {
        istringstream iss(line);
        if (iss >> fileUsername >> filePassword >>  fileWPM >> FullName ) {
            // Check if username and password match
            if (fileUsername == username && filePassword == password) {
                if (currentWPM > fileWPM) {
                    // Update the WPM if the current one is greater
                    fileWPM = currentWPM;
                    // Replace the line with the updated WPM value
                    stringstream updatedLine;
                    updatedLine << fileUsername << " " << filePassword << " " << fileWPM <<FullName;
                    fileContents.push_back(updatedLine.str());
                } else {
                    // Keep the original line if no update is needed
                    fileContents.push_back(line);
                }
            } else {
                // Keep the original line if the username/password don't match
                fileContents.push_back(line);
            }
        }
    }

    // Close the file after reading
    file.close();

    // Open the file again for writing
    ofstream outFile("credentials.txt", ios::trunc);
    if (!outFile.is_open()) {
        cout << "Unable to open credentials file for writing." << endl;
    }

    // Write the updated content back to the file
    for (const string& contentLine : fileContents) {
        outFile << contentLine << endl;
    }

    outFile.close();
}

void field_choosen(string file_name, string& stored) {
    // Step 1: Read all lines from file_name
    vector<string> lines;
    string line;
    ifstream file(file_name);

    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
        return;
    }

    // Step 2: Check if there are lines to practice
    if (lines.empty()) {
        cout << "No lines to practice." << endl;
        return;
    }

    int words_num;
    int num_choice;

    cout << endl;
    cout << "How many words do you want type? And choose the words number in "
            "integer positive multiple of 10.(Maximum Limit around 500)"
         << endl;
    cout << "If you have entered positive integer which is non multiple of 10  "
            "so that will be connverted in near ceil value of mutiple 10(int)"
         << endl;
    cout << "If you have typed less than 1 or greater than 500 that is not "
            "valid so no words assign for typing"
         << endl;
    cout << "----------------------------------------------------------------------------------------------------"<<endl;
    cin >> words_num;
    cin.ignore();

    if (words_num > 500 || words_num < 1) {
        cout << "You have entered either less than 1 word or greater than 500 "
             << endl;
        stored = "";
        return;
    }

    srand(static_cast<unsigned int>(time(0)));
    random_shuffle(lines.begin(), lines.end());

    int lines_num = words_num / 10;
    int line_num_remainder = words_num % 10;

    if (line_num_remainder) {
        lines_num += 1;
    }

    for (int i = 0; i < lines_num; i++) {
        stored += lines[i];
    }
}

void practice(const string& username, const string& password) {

    int field_choice;
    // vector<int>wrong_characters(26);
    vector<int> wrong_characters(55, 0);

    cout << "Which field have you preferred for typing" << endl;
    cout << "1 Sports" << endl;
    cout << "2 Technology" << endl;
    cout << "3 Novel" << endl;
    cout << "4 Environment" << endl;
    cout << "Choose any number except 1,2,3,4  for random text" << endl;
    cout << "---------------------------------------------------------------"<<endl;
    cin >> field_choice;
    cin.ignore();

    string stored;
    switch (field_choice) {
    case 1:
        field_choosen("sports.txt", stored);
        break;
    case 2:
        field_choosen("tech.txt", stored);
        break;
    case 3:
        field_choosen("novel.txt", stored);
        break;
    case 4:
        field_choosen("environment.txt", stored);
        break;
    default:
        field_choosen("random.txt", stored);
        break;
    }
    // Step 1 & 2 in field_choosen function
    //  Step 3: Display the stored line for typing practice

    if (stored.size() == 0) {
        cout << "NO typing line assigned " << endl;
    } else {
        cout << "Type the following line:\n" << stored << endl;
        cout<< "---------------------------------------------------------------------------------------------"<<endl;
        // Step 4: Start timing and get user input
        string typed;

        auto start = chrono::high_resolution_clock::now();
        getline(cin, typed); // Read the input from the user
        auto stop = chrono::high_resolution_clock::now();

        // Step 5: Calculate the total time taken
        auto duration =
            chrono::duration_cast<chrono::microseconds>(stop - start);
        double seconds = duration.count() / 1000000.0;

        // Step 6: Tokenize stored and typed strings into words
        vector<string> storedWords, typedWords;
        istringstream storedStream(stored), typedStream(typed);
        string word;
        while (storedStream >> word)
            storedWords.push_back(word);
        while (typedStream >> word)
            typedWords.push_back(word);

        // Step 7: Compare words and identify incorrect ones
        int correct_characters = 0;
        int total_characters = stored.length();
        int wrong_word_count = 0;
        /*for (int i = 0; i < stored.length(); i++) {
            if (stored[i] != ' ') {
                total_characters++;
            }
        }*/

        cout << "\nComparison Table:\n";
        cout << setw(10) << left << "Word #" << setw(20) << "Stored Word"
             << setw(20) << "Typed Word" << setw(15) << "Status" << setw(25)
             << "Character Comparison" << endl;
        cout << "--------------------------------------------------------------"
                "-------------------------------"
             << endl;

        int minLength = min(storedWords.size(), typedWords.size());
        for (int i = 0; i < minLength; i++) {
            string charComparison;
            if (storedWords[i] == typedWords[i]) {
                cout << setw(10) << left << (i + 1) << setw(20)
                     << storedWords[i] << setw(20) << typedWords[i] << setw(15)
                     << "Correct" << endl;
                correct_characters += storedWords[i].length();
            } else {
                cout << setw(10) << left << (i + 1) << setw(20)
                     << storedWords[i] << setw(20) << typedWords[i] << setw(15)
                     << "Incorrect";

                // Compare characters
                int minLengthWord =
                    min(storedWords[i].length(), typedWords[i].length());
                for (int j = 0; j < minLengthWord; j++) {
                    if (storedWords[i][j] == typedWords[i][j]) {
                        charComparison +=
                            storedWords[i][j]; // Correct character
                        correct_characters++;
                    } else {
                        charComparison += "*"; // Incorrect character
                        char typedChar = typedWords[i][j];

                        if (islower(typedChar)) {
                            // Count lowercase letters
                            wrong_characters[typedChar - 'a']++;
                        } else if (isupper(typedChar)) {
                            // Count uppercase letters
                            wrong_characters[typedChar - 'A' +
                                             26]++; // Offset by 26 for
                                                    // uppercase
                        } else {
                            // Handle non-alphabet characters if needed
                            if (typedChar == ',') {
                                wrong_characters[54]++; // Comma
                            } else if (typedChar == '.') {
                                wrong_characters[52]++; // dot
                            } else if (typedChar == '\'') {
                                wrong_characters[53]++; // Apostrophe
                            }
                        }
                    }
                }

                // Handle extra characters in stored or typed words
                if (storedWords[i].length() > minLengthWord) {
                    charComparison += storedWords[i].substr(
                        minLengthWord); // Remaining correct characters in
                                        // stored
                } else if (typedWords[i].length() > minLengthWord) {
                    charComparison +=
                        string(typedWords[i].length() - minLengthWord,
                               '*'); // Extra wrong characters in typed
                }

                cout << setw(25) << charComparison << endl;
                wrong_word_count++;
            }
        }

        // Handle cases where typedWords has more words than storedWords
        if (typedWords.size() > storedWords.size()) {
            for (size_t i = storedWords.size(); i < typedWords.size(); i++) {
                cout << setw(10) << left << (i + 1) << setw(20) << "(None)"
                     << setw(20) << typedWords[i] << setw(15) << "Extra"
                     << endl;
                wrong_word_count++;
            }
        }
         
        // Step 8: Calculate Words Per Minute (WPM)
        int word_count = typedWords.size();
        correct_characters  += (word_count-wrong_word_count-1);
        double minutes = seconds / 60.0;
         double raw = (minutes > 0) ? (word_count  / minutes)
                                   : 0; // Prevent division by zero
         double wpm = (minutes > 0) ? ((word_count - wrong_word_count) / minutes)
                                   : 0; // Prevent division by zero

        // Step 9: Calculate typing efficiency
        double efficiency =
            (total_characters > 0)
                ? (static_cast<double>(correct_characters) / total_characters) *
                      100
                : 0;

        cout << "Correct Characters: " << correct_characters << endl;
        cout << "Total Characters : " << total_characters << endl;
        // Step 10: Display Results in Tabular Format
        cout << "\nResults:\n";
        cout << setw(15) << left << "Metric" << setw(15) << "Value" << endl;
        cout << "---------------------------------" << endl;
        cout << setw(15) << left << "Total Time" << setw(15) << seconds
             << "seconds" << endl;
        cout << setw(15) << left << "Words Typed" << setw(15) << word_count
             << "words" << endl;
        cout << setw(15) << left << "Raw WPM" << setw(15) << raw << "words/min"
             << endl;
        cout << setw(15) << left << "wpm" << setw(15) << wpm << "words/min"
             << endl;
        cout << setw(15) << left << "Efficiency" << setw(15) << efficiency
             << "%" << endl;
        cout << setw(15) << left << "Wrong Words" << setw(15)
             << wrong_word_count << endl;

        // Write wrong character data to CSV
        int graph_choice;
        cout << "If you want to show graph representation between incorrect "
                "character and their respective count"
             << endl;
        cout << "Press 1 otherwise any numeric value " << endl;

        cin >> graph_choice;
        cin.clear();

        if (graph_choice == 1) {

            ofstream file("counts.csv");
            if (!file.is_open()) {
                cerr << "Error opening file!" << endl;
                return;
            }
            // Write data to CSV
            file << "Character,Wrong Count\n"; // Header

            // Write lowercase characters
            for (size_t i = 0; i < 26; ++i) {
                file << static_cast<char>('a' + i) << "," << wrong_characters[i]
                     << "\n";
            }

            // Write uppercase characters
            for (size_t i = 0; i < 26; ++i) {
                file << static_cast<char>('A' + i) << ","
                     << wrong_characters[i + 26] << "\n";
            }

            // Write special counts

            file << ".," << wrong_characters[52] << "\n";
            file << "'," << wrong_characters[53] << "\n";
            file << "co," << wrong_characters[54] << "\n";

            file.close();

            // Write GNUplot script
            ofstream script("count.gp");
            if (!script.is_open()) {
                cerr << "Error opening count.gp!" << endl;
                return;
            }
            script << "set datafile separator ','\n";
            script << "set xlabel 'Character'\n";
            script << "set ylabel 'Count'\n";
            script << "set ytics 1\n";              // Set ytics at every 1 unit
            script << "set style data histogram\n"; // Set the style for
                                                    // histogram (discrete bars)
            script
                << "set style histogram clustered gap 1\n"; // Set gap between
                                                            // the bars
            script << "set boxwidth 0.9\n";                 // Set width of bars
            script << "set style fill solid border -1\n"; // Solid fill for bars
                                                          // without border

            // Plot both lower and uppercase letters
            script << "plot 'counts.csv' using 2:xticlabels(1) with boxes "
                      "title 'Character Counts'\n";

            // script << "pause -1\n";  // Keep the plot open until the user
            // presses a key

            script.close();

            // Execute GNUplot with the script
            int result = system(
                "gnuplot -p count.gp 2>/dev/null && sleep 10 && pkill gnuplot");

            if (result != 0) {
                cerr << "Error executing GNUplot!" << endl;
                return;
            }

            cout << "Plot has been generated." << endl;
        }
        // Step 11: If credentials are not null, update the leaderboard
        if (username != "nul" && password != "nul") {
            // Call function to check and update credentials based on the
            // current WPM
            checkAndUpdateCredentials(username, password, wpm);
        }
    }
  }
