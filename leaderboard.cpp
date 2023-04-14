#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// function to read usernames and scores from files
void readFiles(vector<string>& names, vector<int>& scores)
{
    ifstream namesFile("usernames.txt");
    ifstream scoresFile("scores.txt");

    if (namesFile.is_open() && scoresFile.is_open()) {
        string name;
        int score;

        while (getline(namesFile, name) && scoresFile >> score) {
            names.push_back(name);
            scores.push_back(score);
        }
        namesFile.close();
        scoresFile.close();
    }
}

// function to display the leaderboard table
void displayLeaderboard(vector<string>& names, vector<int>& scores)
{
    sort(scores.begin(), scores.end(), greater<int>()); // sort scores in descending order

    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax); // get screen dimensions

    int tableWidth = 30;
    int tableHeight = min(20, (int)scores.size() + 2);

    int tableX = (xMax - tableWidth) / 2;
    int tableY = (yMax - tableHeight) / 2;



     // set color pairs
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    // display table header
    mvprintw(tableY, tableX + 10, "LEADERBOARD");

    // display table rows
    for (int i = 0; i < tableHeight - 2; i++) {
        int rank = i + 1;
        if (i < scores.size()) {
            mvprintw(tableY + 2 + i, tableX, "%d. %s", rank, names[i].c_str());
            mvprintw(tableY + 2 + i, tableX + 20, "%d", scores[i]);
        }
        else {
            mvprintw(tableY + 2 + i, tableX, "%d.", rank);
        }
    }

    attroff(COLOR_PAIR(1));
}

int main()
{
    initscr();
    cbreak();
    noecho();

    vector<string> names;
    vector<int> scores;

    readFiles(names, scores);
    displayLeaderboard(names, scores);

    getch();
    endwin();

    return 0;
}