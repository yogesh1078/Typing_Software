#include"User_choice.h"

void printDecorativeLine(int width, char cornerChar = '+',char fillChar = '-') {
    cout << "   " << cornerChar;
    for (int i = 0; i < width - 2; ++i) {
        cout << fillChar;
    }
    cout << cornerChar << endl;
}

void printLineWithStars(int width, char borderChar = '|', char fillChar = ' ',int numStars = 4) {
    int starsPosition = (width - numStars) / 2;
    cout << "   " << borderChar;
    for (int i = 0; i < starsPosition - 1; ++i)
        cout << fillChar;
    for (int i = 0; i < numStars; ++i)
        cout << "*";
    for (int i = starsPosition + numStars - 1; i < width - 2; ++i)
        cout << fillChar;
    cout << borderChar << endl;
}

void printCenteredText(int width, string text) {
    int padding = (width - text.length()) / 2;
    cout << "   |";
    cout << string(padding, ' ') << text
         << string(width - text.length() - padding - 2, ' ') << "|" << endl;
}

void printWelcomeBox() {
    int width = 60; // Width of the box

    // Top border with decoration
    printDecorativeLine(width, '+', '-');

    // Decorative lines with stars
    printLineWithStars(width);
    printLineWithStars(width);

    // Welcome message
    printCenteredText(width, "Welcome to Typing Software");

    // Decorative lines with stars
    printLineWithStars(width);
    printLineWithStars(width);

    // Bottom border with decoration
    printDecorativeLine(width, '+', '-');

    cout << endl;
}

void choices() {
    int choice = 0;
    int restart;
    bool isLogged = false;
    string username = "nul";
    string password = "nul";
   

      do {
           // Clear the terminal before showing the menu
           system("clear"); // For Linux/Unix/MacOS
      
         printWelcomeBox();
         
          if(!isLogged){
        cout << "Choose the Features of software: " << endl;
        cout << "1. Practice purpose" << endl;
        cout << "2. Login" << endl;
        cout << "3. Signup" << endl;
        cout << "4. Exit" << endl;
        cout << "-----------------------------------------------"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "-----------------------------------------------"<<endl;
        // Clear the newline character left in the buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
       
            bool testCompleted = false; 
        switch (choice) {
        case 1:
            cout << "Page redirected for practice" << endl;

            practice("nul", "nul");
            break;
        case 2:
            cout << "Page redirected for Login" << endl;
            login(isLogged,username,password);
             
            break;
        case 3:
            cout << "Page redirected for Signup" << endl;
            signup();
            break;
        case 4:
            exit(1);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            choices(); // Retry if invalid choice
            break;
            }
       }
          else{
             cout << "Choose the Features of software: " << endl;
        
        cout << "1. Logout" << endl;
        cout << "2. Show leaderboard" << endl;
        cout << "3. practice " <<endl;
        cout << "4. Instant Timing Test " <<endl;
        cout << "5. Exit" << endl;
        cout << "-----------------------------------------------"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "-----------------------------------------------"<<endl;
        // Clear the newline character left in the buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
         
             
        switch (choice) {
        case 1:
                isLogged = false;
                username = "nul";
                password = "nul";
                cout<<"LogOut successfully"<<endl;
                cout<<"-------------------------------------------------------------"<<endl;
                break;

        case 2:
            cout << endl << "Page redirected for Userboard" << endl;
            leaderboard();
            break;
        case 3:
                  practice(username,password);
                  break;       
         
        case 4:         
                        int time_choice ;
                        int time_choice_restart; 
                      do {
                            cout << "Choose the Time for Typing: " << endl;
                            cout << "1.  15 seconds" << endl;
                            cout << "2. 30 Seconds " << endl;
                            cout << "3. 1 minute"  << endl;
                            cout << "4. 2 minutes " << endl;
                            cout << "5. Exit" <<endl;
                           
                            cout << "-----------------------------------------------"<<endl;
                            cout << "Enter your choice: ";
                            cin >> time_choice;
                            cout << "-----------------------------------------------"<<endl;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                         

                         
                         switch(time_choice){
                         
                          case 1:
                                    test(15);
                                    break;
                          case 2:
                                    test(30);
                                    break;
                         case 3:
                                    test(60);
                                    break;
                         case 4:
                                    test(120);
                                    break;
                         case 5:
                                    exit(0);
                         default:
                                   break;
                      }
                               
                       cout << "Thank you for arranging the test. Here are the results of your test:" << endl;
                         show_results_from_file("result.txt");
                   
                       cout<<"------------------------------------------------------------------------------------"<<endl;
                         cout<<endl<<"Enter 1 for exit here and press any numeric key for retaking test"<<endl;
                       
                         // Input handling for retake choice
                      while (!(cin >> time_choice_restart)) {
                         cout << "Invalid input! Please enter a valid numeric key: ";
                         cin.clear(); // Clear error flag
                         cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                       }

                               // Clear the buffer again
                              cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

                 }while(time_choice_restart != 1);
                 break;

        
        case 5:
            exit(1);
            break;
        
          }
          
          
           }
       
            cout << endl
             << "Enter 1 for exit or enter other numeric value for Repeat the "
                "process "
             << endl;
             
        cin >> restart;
    } while (restart != 1);
}
