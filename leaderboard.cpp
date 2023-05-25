#include <ncurses.h> //This library provides functions for creating text-based user interfaces. It allows the program to control the terminal screen, handle keyboard input, and display text in a more flexible way.
#include <iostream> //This library provides input/output stream objects such as std::cout and std::cin for console input and output.
#include <fstream>//This library is used for file input/output operations. It provides classes and functions to read from and write to files.
#include <vector> //This library provides the vector container class, which is a dynamic array that can grow or shrink in size. It allows you to store and manipulate a collection of elements. In the code, vector is used to store the usernames and scores read from the files, as well as the sorted pairs of names and scores for the leaderboard.
#include <algorithm> //This library provides various algorithms for manipulating collections of elements. It includes functions like sort, min, max, and others. In the code, algorithm is used to sort the pairs of names and scores in descending order based on the scores, using the sort function and the greater comparator.

using namespace std;

//The readFiles function takes two parameters by reference: names (a vector of strings) and scores (a vector of integers). These parameters will be used to store the usernames and scores read from the files.
void readFiles(vector<string>& names, vector<int>& scores)
{
    //The two input file stream objects named namesFile and scoresFile are created and associated with the files "usernames.txt" and "scores.txt" respectively, using the ifstream class. This allows the function to read data from these files.
    ifstream namesFile("usernames.txt");
    ifstream scoresFile("scores.txt");


    //The if statement checks if both file streams (namesFile and scoresFile) were successfully opened. If the files were opened successfully, the code inside the if block is executed.
    if (namesFile.is_open() && scoresFile.is_open()) {  //The is_open() function is a member function of the std::ifstream class, which is part of the <fstream> library
        string name;
        int score;

        while (getline(namesFile, name) && scoresFile >> score) { //Within the while loop, data is read from the files line by line. getline(namesFile, name) reads a line from the namesFile and stores it in the name string. scoresFile >> score reads an integer from the scoresFile and stores it in the score variable.
            names.push_back(name);
            scores.push_back(score);
        } //The name and score values are appended to the names and scores vectors respectively, using the push_back function.
        //For example, if name is "John" and score is 70, then names.push_back(name) will add "John" to the names vector, and scores.push_back(score) will add 70 to the scores vector.
        namesFile.close();
        scoresFile.close();
        //After reading all the data from the files, the file streams (namesFile and scoresFile) are closed using the close function.
    }
}

//function to display the leaderboard table
//First, the function creates a vector of pairs named nameScorePairs, where each pair consists of an integer (score) and a string (name). 
void displayLeaderboard(vector<string>& names, vector<int>& scores)
{
    //sort both names and scores vectors in descending order of scores
    vector<pair<int, string>> nameScorePairs;
    for (int i = 0; i < scores.size(); i++) {
        nameScorePairs.push_back(make_pair(scores[i], names[i]));
        //The scores and names from the scores and names vectors are combined into these pairs using the make_pair() function.
        //The make_pair() function takes two arguments and returns a pair object.
    }
    //Then, the nameScorePairs vector is sorted in descending order based on the scores using the sort() function, with the help of the greater<pair<int, string>>() comparison function.
    sort(nameScorePairs.begin(), nameScorePairs.end(), greater<pair<int, string>>());
     

    //The code obtains the dimensions of the screen using the getmaxyx() function, which stores the maximum number of rows in yMax and the maximum number of columns in xMax. It then calculates the width and height of the leaderboard table, ensuring that the height is at most 20 or the size of the nameScorePairs vector plus 2 (for the table header and extra row).
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax); //get screen dimensions

    int tableWidth = 30;
    int tableHeight = min(20, (int)nameScorePairs.size() + 2);

    int tableX = (xMax - tableWidth) / 2;
    int tableY = (yMax - tableHeight) / 2;

    //set color pairs
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    //display table header
    mvprintw(tableY, tableX + 10, "LEADERBOARD");
    //The code uses mvprintw() to print the "LEADERBOARD" header at the top of the table. mvprintw() prints a formatted string at the specified position, with the position given by tableY (row) and tableX + 10 (column).

    //display table rows
    for (int i = 0; i < tableHeight - 2; i++) {
        int rank = i + 1;
        if (i < nameScorePairs.size()) {
            mvprintw(tableY + 2 + i, tableX, "%d. %s", rank, nameScorePairs[i].second.c_str());
            mvprintw(tableY + 2 + i, tableX + 20, "%d", nameScorePairs[i].first);
        }
        else {
            mvprintw(tableY + 2 + i, tableX, "%d.", rank);
        }
    }

    attroff(COLOR_PAIR(1));
}


int main()
{
    initscr(); //The initscr() function initializes the ncurses library and sets up the terminal for text-based user interfaces.
    cbreak(); //cbreak() is a function that disables line buffering, allowing input characters to be processed immediately without waiting for a newline character.
    noecho(); //noecho() is a function that turns off character echoing, preventing typed characters from being displayed on the screen.


    //Here, two empty vectors, names and scores, are declared. These vectors will be used to store the usernames and scores read from the files.
    vector<string> names; 
    vector<int> scores;

    //The readFiles(names, scores) function is called to read the data from the files "usernames.txt" and "scores.txt" and populate the names and scores vectors with the read data.
    readFiles(names, scores);
    //Next, the displayLeaderboard(names, scores) function is called. This function takes the names and scores vectors as parameters and displays the leaderboard table on the terminal using the ncurses library.
    displayLeaderboard(names, scores);

    getch(); //getch() is a function from the ncurses library that waits for a keypress from the user. It pauses the program execution until a key is pressed.
    endwin(); //endwin() is a function that cleans up and restores the terminal settings after using the ncurses library. It should be called before the program exits.

    return 0;
}
