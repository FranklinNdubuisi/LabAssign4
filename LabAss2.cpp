#include <iostream>
#include <cstdlib>
#include <ctime>

int add;
int point = 0;
int wager = 100;
int wage;
char user;

int dice() {
    int d = (rand() % 6) + 1;
    return d;
}

int adddice() {
    int d1 = dice();
    int d2 = dice();
    add = d1 + d2;
    std::cout << "Die one is (" << d1 << ") + Die two is (" << d2 << ") = " << add << '\n';
    return add;
}

void checkwin() {
    if (point == 0) {  // First roll
        if (add == 7 || add == 11) {
            std::cout << "Player wins!\n";
            wager += (wage * 2);
            point = 0;
        }
        else if (add == 2 || add == 3 || add == 12) {
            std::cout << "Craps! Player loses.\n";
            wager -= wage;
            point = 0;
        }
        else {
            point = add;
            std::cout << "Points :You have " << point << ". Keep rolling until you match the point or roll a 7.\n";
            while (true) {
                adddice();
                if (add == point) {
                    std::cout << "Player wins by making the point!\n";
                    wager += (wage * 2);
                    point = 0;
                    break;
                }
                else if (add == 7) {
                    std::cout << "Player loses by rolling a 7.\n";
                    wager -= wage;
                    point = 0;
                    break;
                }
            }
        }
        std::cout << "You have " << wager << " credits\n";
    }
}

void playgame() {
    do {
        std::cout << "You have " << wager << " credits. How much would you like to wager? ";
        std::cin >> wage;
        if (wage > wager || wage <= 0)
            std::cout << "Enter a valid wage\n";
    } while (wage > wager || wage <= 0);

    adddice();
    checkwin();
}

int main() {
    srand(time(NULL));

    do {
        playgame();
        if (wager <= 0) {  // Game over if credits are zero or negative
            std::cout << "You are out of credits - game over!\n";
            break;
        }
        if (point == 0) {
            do {
                std::cout << "Would you like to play again? (y/n): ";
                std::cin >> user;
            } while (user != 'y' && user != 'Y' && user != 'n' && user != 'N');
        }
    } while ((user == 'y' || user == 'Y') && wager > 0);

    std::cout << "Game ends.\n";
    return 0;
}
