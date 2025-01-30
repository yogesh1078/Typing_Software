#include "Timing_test_option.h"

//Test option FOr user and stores in Result library 


// Function to display results from result.txt file
void show_results_from_file(const string& fileName) {
    ifstream resultFile(fileName);
    if (!resultFile.is_open()) {
        cerr << "Error opening results file." <<endl;
        return;
    }
    
    string line;
    while (getline(resultFile, line)) {
        cout << line <<endl;
    }
    resultFile.close();
}

// Function to get system time as a string
string system_time() {
    auto currentTime = chrono::system_clock::now();
    time_t timeNow = chrono::system_clock::to_time_t(currentTime);
    return ctime(&timeNow);
}

// Function to calculate WPM
int calculate_wpm(int wordCount, double timeInSeconds) {
    return (wordCount / timeInSeconds) * 60;
}

// Function to split text into words
 vector<string>split_into_words(const string& line) {
    vector<string> words;
    string word = "";
    for (char ch : line) {
        if (ch == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word = "";
            }
        } else {
            word += ch;
        }
    }
    if (!word.empty()) words.push_back(word);
    return words;
 }

// Read lines from text.txt file
 vector<string> read_lines_from_file(const string& fileName) {
    vector<string> lines;
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

// Save results to result.txt file
void save_results_to_file(int wpm, int wrongWords, int correctWords, int totalWords, double timeTaken) {
     ofstream resultFile("result.txt");

        totalWords = wrongWords + correctWords;
    double accuracy = 0.0;
    if (totalWords > 0) {
        accuracy = (correctWords / static_cast<double>(totalWords)) * 100;
    }

    resultFile << "Results:\n";
    resultFile << "WPM: " << wpm << "\n";
    resultFile << "Wrong Words: " << wrongWords << "\n";
    resultFile << "Correct Words: " << correctWords << "\n";
    resultFile << "Accuracy: " << accuracy << "%\n";
    resultFile << "Time Taken: " << timeTaken << " seconds\n";
    resultFile.close();
}


// Function to wrap text according to window width
 vector<string> wrap_text(const string& text, int maxWidth) {
    vector<string> wrappedLines;
    istringstream stream(text);
    string word, line;
    
    while (stream >> word) {
        if (line.length() + word.length() + 1 > static_cast<size_t>(maxWidth)) {
            wrappedLines.push_back(line);
            line = word;
        } else {
            if (!line.empty()) line += " ";
            line += word;
        }
    }
    if (!line.empty()) wrappedLines.push_back(line);

    return wrappedLines;
}


void test(int time_limit) {
     initscr();    //Initializes ncurses and sets up the terminal for manipulation.
     noecho();      //Disables character echoing.
     cbreak();     //Disables line buffering,
     nodelay(stdscr, TRUE);  // Non-blocking input
     timeout(0);

    int maxWidth = 50;
    int height, width;
    getmaxyx(stdscr, height, width);  // Get terminal dimensions
    maxWidth = width - 2;  // Allow padding for borders

    WINDOW* topWin = newwin(3, width, 0, 0);         // Timer at the top
    WINDOW* typingWin = newwin(5, width, 4, 0);      // Typing area
    WINDOW* bottomWin = newwin(3, width, 10, 0);     // Information at the bottom

    // Read text lines from text.txt file
    vector<string> lines = read_lines_from_file("text.txt");

    // Randomize the lines
    random_device rd;
    mt19937 g(rd());
    shuffle(lines.begin(), lines.end(), g);

    string userInput;
    int xPos = 0;
    int currentLineIndex = 0;
    int wrongWords = 0;
    int correctWords = 0;
    int totalWords = 0;

    // Start time for the duration (initialized once)
    auto startTime = chrono::steady_clock::now();
    long elapsedTime = 0;

    // Main loop, run until time limit has passed
    while (true) {
        // Calculate elapsed time
        auto currentTime = chrono::steady_clock::now();
        elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();

        // If time_limit seconds have passed, break the loop
        if (elapsedTime >= time_limit) {
            break;
        }

        // Display the timer at the top
        werase(topWin);
        mvwprintw(topWin, 1, 1, "Time: %ld seconds", elapsedTime);
        wrefresh(topWin);

        // Display the current three lines, wrapping text to fit the width
        werase(typingWin);
        int lineCounter = 0;
        for (int i = currentLineIndex; i < currentLineIndex + 3 && i < lines.size(); ++i) {
             vector<string> wrappedLines = wrap_text(lines[i], maxWidth);
            for (const auto& wrappedLine : wrappedLines) {
                if (lineCounter < 3) {
                    mvwprintw(typingWin, lineCounter + 1, 1, "%s", wrappedLine.c_str());
                    lineCounter++;
                }
            }
        }
        wrefresh(typingWin);

        // Handle user input for the current line
        int ch = getch();
        if (ch != ERR) {
            if (ch == KEY_BACKSPACE || ch == 127) { // Handle backspace
                if (!userInput.empty()) {
                    userInput.pop_back();
                    xPos--;
                }
            } else if (ch == '\n') { // Handle enter (line completion)
                vector<string> typedWords = split_into_words(userInput);
                vector<string> actualWords = split_into_words(lines[currentLineIndex]);

                // Count correct and wrong words
                for (size_t i = 0; i < typedWords.size(); ++i) {
                    if (i < actualWords.size()) {
                        if (typedWords[i] == actualWords[i]) {
                            correctWords++;
                        } else {
                            wrongWords++;
                        }
                    } else {
                        wrongWords++; // Count extra typed words as wrong
                    }
                }

                // Count remaining words in the actual line that were not typed
                totalWords += actualWords.size(); // Count all words in the line
                wrongWords += actualWords.size() - typedWords.size(); // Count any skipped words

                // Move to the next line and reset input
                currentLineIndex++;
                userInput.clear();
                xPos = 0;

                // If all lines are done, stop
                if (currentLineIndex + 3 > lines.size()) {
                    break;
                }
            } else if (isprint(ch)) { // Handle regular character input
                userInput.push_back(ch);
                xPos++;
            }
        }

        // Display the user input
        werase(bottomWin);
        mvwprintw(bottomWin, 1, 1, "Input: %s", userInput.c_str());
        wrefresh(bottomWin);

        usleep(100000); // Sleep for 100ms to avoid high CPU usage
    }

    // Save Partial Input and Calculate Statistics** when the time is up
    if (!userInput.empty()) {
        // Handle the remaining user input if there's any
        vector<string> typedWords = split_into_words(userInput);
        vector<string> actualWords = split_into_words(lines[currentLineIndex]);

        // Count correct and wrong words for the partial input
        for (size_t i = 0; i < typedWords.size(); ++i) {
            if (i < actualWords.size()) {
                if (typedWords[i] == actualWords[i]) {
                    correctWords++;
                } else {
                    wrongWords++;
                }
            } else {
                wrongWords++; // Count extra typed words as wrong
            }
        }

        // Count remaining words in the actual line that were not typed
        totalWords += actualWords.size(); // Count total words
       // wrongWords += actualWords.size() - typedWords.size(); // Count any skipped words
    }

    // Calculate final statistics
    double totalTimeInSeconds = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - startTime).count();
    int wpm = calculate_wpm(correctWords, totalTimeInSeconds);

    // Save the final result to result.txt
    save_results_to_file(wpm, wrongWords, correctWords, totalWords, totalTimeInSeconds);

    // Display the final result
    werase(bottomWin);
    mvwprintw(bottomWin, 1, 1, "Time's up! Final Results saved to result.txt");

    // Wait before exit
    sleep(2);

    // Clean up
    delwin(topWin);
    delwin(typingWin);
    delwin(bottomWin);
    endwin();
}

 
