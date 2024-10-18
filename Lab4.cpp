#include <iostream>
#include <vector>
#include <ncurses.h>
#include "game.h"

const int newBoardRows = 24;
const int newBoardCols = 85;

Matrix board(newBoardRows, Vec(newBoardCols, 0));

// Function to print the current state of the grid
void printGrid() {
    for (int i = 0; i < newBoardRows; i++) {
        for (int j = 0; j < newBoardCols; j++) {
            if (board[i][j] == 1) {
                mvprintw(i, j, "x");  // 'x' represents a live cell
            }
            else {
                mvprintw(i, j, " ");  // ' ' represents a dead cell
            }
        }
    }
    refresh();  // Refresh to display changes
}

// Function to count live neighbors of a cell
int getLiveNeighbors(int x, int y) {
    int liveNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;  // Skip the cell itself
            int newX = x + i;
            int newY = y + j;  // Check the 8 surrounding cells
            if (newX >= 0 && newX < newBoardRows && newY >= 0 && newY < newBoardCols)
                liveNeighbors += board[newX][newY];
        }
    }
    return liveNeighbors;
}

// Update the board for the next generation
void nextGeneration() {
    Matrix newBoard(newBoardRows, Vec(newBoardCols, 0));  // Create a new board for the next generation

    for (int i = 0; i < newBoardRows; i++) {
        for (int j = 0; j < newBoardCols; j++) {
            int liveNeighbors = getLiveNeighbors(i, j);

            if (board[i][j] == 1) {  // Cell is currently alive
                if (liveNeighbors < 2) {
                    newBoard[i][j] = 0;  // Cell dies due to underpopulation 
                }
                if (liveNeighbors > 3) {
                    newBoard[i][j] = 0;  // Cell dies due to overpopulation
                }
                else {
                    newBoard[i][j] = 1;  // Cell survives with 2 or 3 neighbors
                }
            }
            else {  // Cell is currently dead
                if (liveNeighbors == 3) {
                    newBoard[i][j] = 1;  // Dead cell becomes alive with exactly 3 neighbors
                }
            }
        }
    }
    board = newBoard;  // Replace the old board with the new one
}

// Let the user manually create their glider gun setup using mouse clicks
void inputGliderGun() {
    MEVENT event;
    bool editing = true;
    printGrid();

    while (editing) {
        int c = getch();  // Wait for key press
        if (c == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_PRESSED) {
                   
                    if (event.y >= 0 && event.y < newBoardRows && event.x >= 0 && event.x < newBoardCols) {
                        board[event.y][event.x] = !board[event.y][event.x]; // Toggle live/dead state of the clicked cell
                        printGrid();  // Reprint the board with the changes
                    }
                }
            }
        }
        else if (c == 'd') {
            editing = false;  // User has pressed 'd', indicating they are done
        }
    }
}

int main() {
    initscr();              
    noecho();              
    cbreak();               
    keypad(stdscr, TRUE);   
    mousemask(ALL_MOUSE_EVENTS, NULL);  /

    inputGliderGun();  // Let the user input the initial glider gun configuration

    int gen;
    std::cout << " " << '\n';
    std::cout << "How many generations would you like: ";
    std::cin >> gen;

    for (int generation = 0; generation <= gen; ++generation) {
        printGrid();      // Display the current board
        nextGeneration(); // Calculate the next generation

        int c = getch();  // Wait for user input

        if (c == 'q') {
            break;  // Exit the loop if 'q' is pressed
        }
    }

    endwin(); 
    return 0;
}
