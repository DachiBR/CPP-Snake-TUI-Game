#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <cstdlib> // for the system() function
#include <cstring> // for strlen

int main()
{
    char name[20]; // define a buffer to hold the player's name

    // Initialize ncurses
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    // Calculate screen dimensions
    int screen_x, screen_y;
    getmaxyx(stdscr, screen_y, screen_x);

    // Center the welcome message
    const char* welcome_message = "Welcome to Snake TUI Game!";
    int welcome_message_len = strlen(welcome_message);
    int welcome_message_x = (screen_x - welcome_message_len) / 2;
    int welcome_message_y = screen_y / 2 - 1;

    // Center the name prompt message
    const char* name_prompt = "Please enter your name:";
    int name_prompt_len = strlen(name_prompt);
    int name_prompt_x = (screen_x - name_prompt_len) / 2;
    int name_prompt_y = screen_y / 2 + 1;

    // Draw the box and messages
    box(stdscr, 0, 0);
    mvprintw(welcome_message_y, welcome_message_x, "%s", welcome_message);
    mvprintw(name_prompt_y, name_prompt_x, "%s", name_prompt);

    // Enable echoing of input and read the player's name
    echo();
    mvgetstr(name_prompt_y + 2, name_prompt_x, name);

    // Clear the screen and display the start message
    clear();
    const char* start_message = "Hello, %s! Press any key to start the game...";
    int start_message_len = strlen(start_message) + strlen(name) - 2;
    int start_message_x = (screen_x - start_message_len) / 2;
    int start_message_y = screen_y / 2;
    mvprintw(start_message_y, start_message_x, start_message, name);
    getch(); // wait for a key press

    // Save player's name to file
    std::ofstream file("usernames.txt", std::ios_base::app);
    if (file.is_open()) {
        file << name << std::endl;
        file.close();
    } else {
        std::cerr << "Error opening file" << std::endl;
        return 1; // exit program with error code
    }

    attroff(COLOR_PAIR(1));
    endwin(); // close ncurses window

    // Run the Snake Game executable
    system("./snake_game");

    return 0;
}
