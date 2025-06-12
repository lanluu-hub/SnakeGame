/// @file SnakeGame.cpp
/// @brief Console-based implementation of the classic Snake game in C++.
///        The player controls a snake to collect food while avoiding collisions
///        with walls and its own tail. The game features real-time movement,
///        score tracking, and adjustable difficulty levels.
/// @date June 12th, 2025
/// @author Lan Luu
#include <conio.h>      // Non-Standard Library that contains console commands.
#include <iostream>     // Standard Input and Output Library of C++.
#include <string>
#include <cstdlib>
#include <windows.h>    // Windows API Library.

using namespace std;

/// DEFINE GLOBAL VARIABLES FOR THE GAME ///
// height and width of the boundary
const int width = 80;
const int height = 20;

// Snakes head coordinates of snake (x-axis, y-axis)
int x, y;

// Food Coordinates
int fruitCordX, fruitCordY;

// variable to store the score of the player
int playerScore;

// Array to store the coordinates of snake tail (x-axis, y-axis)
int snakeTailX[100], snakeTailY[100];

// Variable to store the length of snake's tail
int snakeTailLen;

// for storing snake's moving SnakeDirection
enum snakeDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

// snakeDirection vaiable
snakeDirection sDir;

// bool variable for checking game is over or not
bool isGameOver;
/// END OF GLOBAL VARIABLE ///


/// FUNCTION PROTOTYPE ///

/// @brief initializing the game variables.
void GameInit();

/// @brief Function for creating the game board & rendering
/// @param playerName Name of the player
void GameRender(const string & playerName);

/// @brief Function for updating the game state
void UpdateGame();

/// @brief  Function to set the game difficulty level 
/// @return difficulty level
int SetDifficulty();

/// @brief Function to handle user UserInput
void UserInput();

int
main() 
{
    string playerName;
    cout << "Enter Your name: ";
    getline(cin, playerName);
    int dfc = SetDifficulty();

    GameInit();
    while (!isGameOver) {
        GameRender(playerName);
        UserInput();
        UpdateGame();
        // creating a delay for according to the chosen
        // difficulty
        Sleep(dfc);
    }

    return 0;
}

/// FUNCION DEFINITION ///
void GameInit()
{
    isGameOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    playerScore = 0;
}

void GameRender(const string & playerName)
{
    system("cls");  // clear the console

    // Creating the top wall with '-'
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            // Creating a side walls with '|'
            if (j == 0 || j == width)
                cout << "|";

            // Creating snake's head with 'O'
            if (i == y && j == x)
                cout << "O";
            // Creating the snake's food with "#"
            else if (i == fruitCordY && j == fruitCordX)
                cout << "#";
            // Creating snake tail with "o"
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j
                        && snakeTailY[k] == i) {
                            cout << "o";
                            prTail = true;
                        }
                }

                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    // Creating bottom walls with '-'
    for (int i = 0; i < width; i++)
        cout << "-";
    cout << endl;

    // Display player's score
    cout << playerName << "'s Score: " << playerScore
         << endl;
}

void UpdateGame()
{
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (sDir)
    {
    case LEFT:
        --x;
        break;

    case RIGHT:
        ++x;
        break;

    case UP:
        --y;
        break;

    case DOWN:
        ++y;
        break;
    }

    // Checks for snake's collision with the wall (|)
    if (x >= width || x < 0 || y >= height || y < 0)
        isGameOver = true;

    // Checks for collision with the tail (o)
    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            isGameOver = true;
    }

    // Checks for snake's collision with the food (#)
    if (x == fruitCordX && y == fruitCordY) {
        playerScore += 10;  // increase player point
        fruitCordX = rand() % width;    // generate new fruit coord x
        fruitCordY = rand() % height;   // generate new fruit coord y
        ++snakeTailLen;
    }
}

int SetDifficulty()
{
    int dfc, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard "
            "\nNOTE: if not chosen or pressed any other "
            "key, the difficulty will be automatically set "
            "to medium\nChoose difficulty level: ";
    cin >> choice;
    switch (choice)
    {
    case '1':
        dfc = 50;
        break;
    
    case '2':
        dfc = 100;
        break;

    case '3':
        dfc = 150;
        break;
    
    default:
        dfc = 100;
    }
    return dfc;
}

/* 
    NOTE:
    1._kbhit() function checks the console for a recent keystroke. 
    If the function returns a nonzero value, a keystroke is waiting in the buffer. 
    The program can then call _getch() or _getche() to get the 
    keystroke.

    2. getch()is a nonstandard function and is present in file which is 
    mostly used by. It is not part of the C standard library or ISO C, nor 
    is it defined by POSIX
*/
void UserInput()
{
    // Checks if a key is pressed or not
    if (_kbhit()) {
        // Getting the pressed key
        switch (_getch())
        {
        case 'a':
            sDir = LEFT;
            break;
        case 'd':
            sDir = RIGHT;
            break;
        case 'w':
            sDir = UP;
            break;
        case 's':
            sDir = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}
