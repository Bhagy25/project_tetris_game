#include <iostream>// used for standard i/p and o/p
#include <vector>
#include <conio.h>//console i/p & o/p _kbit() & _getch()
#include <windows.h>//used to implement system related functions like sleep() beep()
#include <ctime>//used in rand() to implement different tetrimino positions
#include <sstream>//string functions

using namespace std;
// grid dimensions
const int WIDTH = 10;
const int HEIGHT = 20;

vector<string> colors = {"\033[34m#\033[0m", "\033[33m#\033[0m", "\033[35m#\033[0m", "\033[32m#\033[0m", "\033[31m#\033[0m", "\033[36m#\033[0m", "\033[37m#\033[0m"};// colors generated

vector<vector<vector<int>>> tetrominoes = {
    // teriminos shape
    {{1, 1, 1, 1}}, // i 
    {{1, 1}, {1, 1}}, //o
    {{0, 1, 0}, {1, 1, 1}}, //t
    {{1, 1, 0}, {0, 1, 1}}, // z
    {{0, 1, 1}, {1, 1, 0}}, //s
    {{1, 0, 0}, {1, 1, 1}},//l 
    {{0, 0, 1}, {1, 1, 1}}//j
};

class Tetris {
private:
    vector<vector<int>> grid; // for grid
    vector<vector<int>> colorGrid;// for color grid
    int score, level;
    int fallInterval;// time of falling of tetris in ms // controls fall speed
    pair<int, int> pos;// initial pos with centre and top spawning it keeps changing with respect to time /in form of coordinates
    vector<vector<int>> currentPiece;// stores shape of falling tetrimino / changes continuosly
    int currentColor;// changed with change in falling tetrimino
    HANDLE hConsole;// faster rendering
    bool gameOver;// checking if the game is over or not

public:
    Tetris() : gameOver(false) {
        grid = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0));// assigns 0 and checks if the grid is occupied 0 or 1
        colorGrid = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, -1));//stores color of each falling tetromino
        score = 0;
        level = 1;
        fallInterval = 500;// checks how fast termino falls
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        spawnPiece();
    }

    void spawnPiece() {
        int index = rand() % tetrominoes.size();// generate index from the given tetromino ex.7 formation
        currentPiece = tetrominoes[index];// choose that tetromino
        currentColor = index;// choose color of that teromino
        pos = {0, WIDTH / 2 - (int)currentPiece[0].size() / 2};// this places the teromino at the top of grid and center of the grid

        if (!isValidMove(pos.first, pos.second, currentPiece)) {// checking if it fits the position
            gameOver = true;
            Beep(400, 500); // Game over sound
        }
    }

    bool isValidMove(int newRow, int newCol, const vector<vector<int>> &piece) {
        // checking if the move is valid or doesnt hit any wall 
        for (int i = 0; i < piece.size(); i++) {
            for (int j = 0; j < piece[i].size(); j++) {
                if (piece[i][j]) {
                    int r = newRow + i, c = newCol + j;
                    if (r >= HEIGHT || c < 0 || c >= WIDTH || (r >= 0 && grid[r][c]))
                        return false;
                }
            }
        }
        return true;
    }

    vector<vector<int>> rotatePiece(const vector<vector<int>> &piece) {
        // rotating piece 90 degree clockwise
        int rows = piece.size(), cols = piece[0].size();
        vector<vector<int>> rotated(cols, vector<int>(rows, 0));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rotated[j][rows - 1 - i] = piece[i][j];
            }
        }
        return rotated;
    }

    void rotate() {
        // for checking if it can be rotated
        vector<vector<int>> rotated = rotatePiece(currentPiece);
        if (isValidMove(pos.first, pos.second, rotated)) {
            currentPiece = rotated;
            Beep(500, 100); // Rotation sound
        }
    }

    void movePiece(int dx) {
        // moves the tetromino to left or right
        if (isValidMove(pos.first, pos.second + dx, currentPiece)) {
            pos.second += dx;
            Beep(300, 50); // Move sound
        }
    }

    bool moveDown() {
        // moving down
        if (isValidMove(pos.first + 1, pos.second, currentPiece)) {
            pos.first++;
            return true;
        }
        return false;
    }

    void dropPiece() {
        // by pressing shift
        // move down till it reaches to end or mix with grid
        while (isValidMove(pos.first + 1, pos.second, currentPiece))
            pos.first++;
        Beep(600, 100); // Hard drop sound
    }

    void lockPiece() {

        for (int i = 0; i < currentPiece.size(); i++) {
            for (int j = 0; j < currentPiece[i].size(); j++) {
                if (currentPiece[i][j] && pos.first + i >= 0) {
                    grid[pos.first + i][pos.second + j] = 1;// marking main grid as occupied
                    colorGrid[pos.first + i][pos.second + j] = currentColor;
                }
            }
        }
        clearLines();
        spawnPiece();
    }

    void clearLines() {
        // when the row is full checking from bottom of grid it is removed and replaced with new empty row
        for (int i = HEIGHT - 1; i >= 0; i--) {
            bool full = true;
            for (int j = 0; j < WIDTH; j++) {
                if (!grid[i][j]) {
                    full = false;
                    break;
                }
            }
            if (full) {
                grid.erase(grid.begin() + i);
                grid.insert(grid.begin(), vector<int>(WIDTH, 0));
                colorGrid.erase(colorGrid.begin() + i);
                colorGrid.insert(colorGrid.begin(), vector<int>(WIDTH, -1));
                score += 100;
                Beep(800, 100); // Line clear sound
            }
        }

        int newLevel = (score / 200) + 1;  // Increase level every 200 points
        if (newLevel > level) {
            level = newLevel;
            fallInterval = max(100, 500 - (level * 50)); // Speed up the game
            Beep(1000, 150); // Level up sound
        }
    }

    void render() {
        ostringstream screen;//avoiding flickering
        screen << "\n";

        for (int i = 0; i < HEIGHT; i++) {
            screen << "| ";
            for (int j = 0; j < WIDTH; j++) {
                bool isPiece = false;
                for (int pi = 0; pi < currentPiece.size(); pi++) {// for checking the falling tetromino
                    for (int pj = 0; pj < currentPiece[pi].size(); pj++) {
                        if (currentPiece[pi][pj] && pos.first + pi == i && pos.second + pj == j)
                            isPiece = true;
                    }
                }
                if (isPiece)
                    screen << colors[currentColor] << " ";
                else if (grid[i][j])
                    screen << colors[colorGrid[i][j]] << " ";
                else
                    screen << ". ";
            }
            screen << "|\n";
        }

        screen << "Score: " << score << "  Level: " << level << "\n"; // ✅ Fixed Level Display

        if (gameOver) {
            screen << "GAME OVER!\n";
        }

        SetConsoleCursorPosition(hConsole, {0, 0});
        cout << screen.str();
    }

    void play() {
        DWORD lastFallTime = GetTickCount();// returns no. of ms since system started
        while (!gameOver) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 75) movePiece(-1);//left
                else if (key == 77) movePiece(1);//right
                else if (key == 80) { if (!moveDown()) lockPiece(); }
                else if (key == 32) { dropPiece(); lockPiece(); }// space bar
                else if (key == 72) rotate();// up
            }
            DWORD currentTime = GetTickCount();
            if (currentTime - lastFallTime >= (DWORD)fallInterval) {
                if (!moveDown()) lockPiece();
                lastFallTime = currentTime;
            }
            render();
            Sleep(16);// 60 fps
        }
    }
};

int main() {
    srand((unsigned int)time(0));
    Tetris game;
    game.play();
    return 0;
}

