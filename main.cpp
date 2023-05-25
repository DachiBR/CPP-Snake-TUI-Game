#include <iostream> //This library provides input/output stream objects such as std::cout and std::cin for console input and output.
#include <ncurses.h> //This library provides functions for creating text-based user interfaces. It allows the program to control the terminal screen, handle keyboard input, and display text in a more flexible way.
#include <fstream> //This library is used for file input/output operations. It provides classes and functions to read from and write to files.
#include <cstdlib> //This library provides several general-purpose functions, including system(), which is used to execute shell commands.
#include <cstring> //This library provides various functions for manipulating strings, such as strlen() for getting the length of a string.

int main()
{
    char name[20]; //It declares a character array name with a size of 20 to hold the player's name.

    //Initializes the ncurses library using initscr() and sets up color pairs for text using start_color() and init_pair().
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    //Gets the dimensions of the terminal screen using getmaxyx().
    int screen_x, screen_y;
    getmaxyx(stdscr, screen_y, screen_x);

    //Calculates the coordinates for displaying the welcome message and name prompt at the center of the screen.
    const char* welcome_message = "Welcome to Snake TUI Game!";
    int welcome_message_len = strlen(welcome_message);
    int welcome_message_x = (screen_x - welcome_message_len) / 2;
    int welcome_message_y = screen_y / 2 - 1;

    const char* name_prompt = "Please enter your name:";
    int name_prompt_len = strlen(name_prompt);
    int name_prompt_x = (screen_x - name_prompt_len) / 2;
    int name_prompt_y = screen_y / 2 + 1;

    //Draws a box on the screen using box() and displays the welcome message and name prompt using mvprintw().
    box(stdscr, 0, 0);
    mvprintw(welcome_message_y, welcome_message_x, "%s", welcome_message);
    mvprintw(name_prompt_y, name_prompt_x, "%s", name_prompt);

    //Enables echoing of user input and reads the player's name using echo() and mvgetstr().
    echo();
    mvgetstr(name_prompt_y + 2, name_prompt_x, name);

    //Clears the screen and displays a start message with the player's name using mvprintw().
    clear();
    //using * because of the safety, it's a good practice to use const and * to prevent unintentional modifications and ensure code safety.
    const char* start_message = "Hello, %s! Press any key to start the game...";
    int start_message_len = strlen(start_message) + strlen(name) - 2;
    int start_message_x = (screen_x - start_message_len) / 2;
    int start_message_y = screen_y / 2;
    mvprintw(start_message_y, start_message_x, start_message, name);
    getch(); //Waits for a key press using getch() , The getch() function is part of the <ncurses.h> library. It is used to read a single character of input from the user without waiting for the user to press the Enter key. 

    //Opens a file named "usernames.txt" in append mode and writes the player's name to the file.
    std::ofstream file("usernames.txt", std::ios_base::app); //std::ofstream: This is a class from the <fstream> library used for writing data to files. 
    if (file.is_open()) {
        file << name << std::endl;
        file.close();
    } else {
        std::cerr << "Error opening file" << std::endl; //std::cerr: This is an object of the std::ostream class from the <iostream> library. It is the standard error stream used to display error messages. In the code, it is used to output an error message if there is a problem opening the file.
        return 1; //exit program with error code
    }
        //Closes the file and turns off the color pair using attroff().
    attroff(COLOR_PAIR(1));
    endwin(); //Closes the ncurses window using endwin().


    //Executes the shell command "./snake_game" using system() to run the Snake game.
    system("./snake_game");

    return 0; //Returns 0 to indicate successful execution of the program.
}
