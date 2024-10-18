extern const int newBoardRows;
extern const int newBoardCols;

typedef std::vector<int> Vec;
typedef std::vector<Vec> Matrix;

extern Matrix board;

void printGrid();            // Function to print the current state of the grid
int getLiveNeighbors(int x, int y);  // Function to count live neighbors of a cell
void nextGeneration();       // Function to calculate the next generation
void inputGliderGun();       // Function to allow the user to input a glider gun configuration
