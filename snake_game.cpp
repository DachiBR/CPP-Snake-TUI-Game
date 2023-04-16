#include <iostream>
#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

const int MAX_X = 160;
const int MAX_Y = 40;

class Point
{
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

class Snake
{
public:
    Snake(int x, int y) : direction('d')
    {
        body.push_back(Point(x, y));
        body.push_back(Point(x - 1, y));
        body.push_back(Point(x - 2, y));
    }

    void move()
    {
        Point new_head = get_new_head();
        body.insert(body.begin(), new_head);
        body.pop_back();
    }

    bool has_collision()
    {
        Point head = body.front();
        if (head.x < 0 || head.x >= MAX_X || head.y < 0 || head.y >= MAX_Y)
        {
            return true;
        }
        for (auto it = body.begin() + 1; it != body.end(); ++it)
        {
            if (head.x == it->x && head.y == it->y)
            {
                return true;
            }
        }
        return false;
    }

    void change_direction(char new_direction)
    {
        if ((new_direction == 'w' && direction != 's') ||
            (new_direction == 'a' && direction != 'd') ||
            (new_direction == 's' && direction != 'w') ||
            (new_direction == 'd' && direction != 'a'))
        {
            direction = new_direction;
        }
    }

    Point get_new_head()
    {
        Point head = body.front();
        if (direction == 'w')
        {
            return Point(head.x, head.y - 1);
        }
        else if (direction == 'a')
        {
            return Point(head.x - 1, head.y);
        }
        else if (direction == 's')
        {
            return Point(head.x, head.y + 1);
        }
        else if (direction == 'd')
        {
            return Point(head.x + 1, head.y);
        }
        return head;
    }
    void grow()
    {
        Point tail = body.back();
        body.push_back(tail);
    }

    std::vector<Point> body;

private:
    char direction;
};
class Apple
{
public:
    Apple()
    {
        generate_new_location();
    }

    void generate_new_location()
    {
        x = rand() % MAX_X;
        y = rand() % MAX_Y;
    }

    Point get_location()
    {
        return Point(x, y);
    }

private:
    int x, y;
};

class Game
{
public:
    Game()
    {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);
        timeout(100);

        start_color();

        init_pair(1, COLOR_BLACK, COLOR_GREEN);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_BLACK, COLOR_YELLOW);
        snake = new Snake(MAX_X / 2, MAX_Y / 2);
        apple = new Apple();

        score = 0;
    }

    ~Game()
    {
        delete snake;
        delete apple;
        endwin();
    }
    void play()
    {
        while (!game_over)
        {
            process_input();
            update();
            draw();
        }
        // Create an ofstream object to write to the scores.txt file
        std::ofstream outfile("scores.txt", std::ios_base::app);

        // Write the final score to the file
        outfile << score << std::endl;

        // Close the file
        outfile.close();
    }
    void process_input()
    {
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            snake->change_direction('w');
            break;
        case KEY_DOWN:
            snake->change_direction('s');
            break;
        case KEY_LEFT:
            snake->change_direction('a');
        case KEY_RIGHT:
            snake->change_direction('d');
            break;
        case 'q':
            game_over = true;
            break;
        default:
            break;
        }
    }

    void update()
    {
        snake->move();
        if (snake->has_collision())
        {
            game_over = true;
            return;
        }

        Point head = snake->body.front();
        if (head.x == apple->get_location().x && head.y == apple->get_location().y)
        {
            snake->grow();
            score += 10;
            apple->generate_new_location();
        }
    }
    void draw()
    {
        clear();

        // draw the border

        wbkgd(stdscr, COLOR_PAIR(3));

        for (int x = 0; x < MAX_X + 2; ++x)
        {
            attron(COLOR_PAIR(4));
            mvprintw(0, x, " ");
            mvprintw(MAX_Y + 1, x, " ");
            attroff(COLOR_PAIR(4));
        }
        for (int y = 0; y < MAX_Y + 2; ++y)
        {
            attron(COLOR_PAIR(4));
            mvprintw(y, 0, " ");
            mvprintw(y, MAX_X + 1, " ");
            attroff(COLOR_PAIR(4));
        }

        // draw the snake

        for (auto &p : snake->body)
        {
            attron(COLOR_PAIR(1));
            mvprintw(p.y + 1, p.x + 1, " ");
            attroff(COLOR_PAIR(1));
        }

        // draw the apple
        Point apple_loc = apple->get_location();
        attron(COLOR_PAIR(2));
        mvprintw(apple_loc.y + 1, apple_loc.x + 1, "O");
        attroff(COLOR_PAIR(2));
        // draw the score
        mvprintw(MAX_Y + 3, 0, "Score: %d", score);
        refresh();
    }

private:
    Snake *snake;
    Apple *apple;
    int score;
    bool game_over = false;
};

int main()
{

    srand(time(NULL));

    Game game;
    game.play();

    system("./leaderboard");

    return 0;
}
