#include <iostream>
#include <vector>
#include <ncurses.h>
#include <game.h>

extern const int newBoardRows =24;
extern const int newBoardCols=85;

typedef std::vector<int> Vec;
typedef std::vector<Vec> Matrix;

Matrix board(newBoardRows, Vec(newBoardCols, 0));

//
int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
  
    mousemask(ALL_MOUSE_EVENTS, NULL);

    
    MEVENT event;
    
    inputGliderGun();
    int gen;
    std::cout << " "<<'\n';
    std::cout << "How many generations would you like: ";
    std::cin >> gen;


    for (int generation = 0; generation <= gen; ++generation) {

        printGrid();
        nextGeneration();
        int c = getch();
      
        if (c == 'q') {
            break;  // Exit the loop if 'q' is pressed
        }
    }


    endwin();
    return 0;
}