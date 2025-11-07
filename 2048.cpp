#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <cstdio>

using namespace std;

char getch() {
    char buf = 0;
    struct termios old = {0};
    
    if (tcgetattr(0, &old) < 0) {
        cout << "Error getting terminal attributes" << endl;
        return 0;
    }
    
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    
    if (tcsetattr(0, TCSANOW, &old) < 0) {
        cout << "Error setting terminal attributes" << endl;
        return 0;
    }
    
    if (read(0, &buf, 1) < 0) {
        cout << "Error reading character" << endl;
    }
    
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    
    if (tcsetattr(0, TCSADRAIN, &old) < 0) {
        cout << "Error restoring terminal attributes" << endl;
    }
    
    return buf;
}

class Game2048 {
private:
    vector<vector<int>> board;
    int score;
    bool gameOver;
    bool won;

public:
    Game2048() : board(4, vector<int>(4, 0)), score(0), gameOver(false), won(false) {
        srand(time(0));
        addRandomTile();
        addRandomTile();
    }

    void display() {
        // پاک کردن صفحه برای لینوکس/مک
        cout << "\033[2J\033[1;1H";
        
        cout << "Score: " << score << endl;
        cout << "=========================" << endl;
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 0) {
                    cout << "    .";
                } else {
                    printf("%5d", board[i][j]);
                }
            }
            cout << endl;
        }
        cout << "=========================" << endl;
        cout << "Controls: W (Up), S (Down), A (Left), D (Right), Q (Quit)" << endl;
        
        if (won) {
            cout << "Congratulations! You won!" << endl;
        }
        if (gameOver) {
            cout << "Game Over!" << endl;
        }
    }

    void addRandomTile() {
        vector<pair<int, int>> emptyCells;
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 0) {
                    emptyCells.push_back({i, j});
                }
            }
        }
        
        if (emptyCells.empty()) return;
        
        int randomIndex = rand() % emptyCells.size();
        int row = emptyCells[randomIndex].first;
        int col = emptyCells[randomIndex].second;
        
        board[row][col] = (rand() % 10 == 0) ? 4 : 2;
    }

    bool isGameOver() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 0) return false;
            }
        }
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == board[i][j + 1]) return false;
            }
        }
        
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 3; i++) {
                if (board[i][j] == board[i + 1][j]) return false;
            }
        }
        
        return true;
    }

    void moveLeft() {
        bool moved = false;
        
        for (int i = 0; i < 4; i++) {
            vector<int> temp;
            for (int j = 0; j < 4; j++) {
                if (board[i][j] != 0) {
                    temp.push_back(board[i][j]);
                }
            }
            
            for (int j = 0; j < (int)temp.size() - 1; j++) {
                if (temp[j] == temp[j + 1]) {
                    temp[j] *= 2;
                    score += temp[j];
                    if (temp[j] == 2048) won = true;
                    temp.erase(temp.begin() + j + 1);
                }
            }
            
            while (temp.size() < 4) {
                temp.push_back(0);
            }
            
            for (int j = 0; j < 4; j++) {
                if (board[i][j] != temp[j]) {
                    moved = true;
                }
                board[i][j] = temp[j];
            }
        }
        
        if (moved) {
            addRandomTile();
            gameOver = isGameOver();
        }
    }

    void moveRight() {
        for (int i = 0; i < 4; i++) {
            reverse(board[i].begin(), board[i].end());
        }
        
        moveLeft();
        
        for (int i = 0; i < 4; i++) {
            reverse(board[i].begin(), board[i].end());
        }
    }

    void moveUp() {
        rotateBoard();
        moveLeft();
        rotateBoard();
        rotateBoard();
        rotateBoard();
    }

    void moveDown() {
        rotateBoard();
        moveRight();
        rotateBoard();
        rotateBoard();
        rotateBoard();
    }

    void rotateBoard() {
        vector<vector<int>> newBoard(4, vector<int>(4));
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                newBoard[j][3 - i] = board[i][j];
            }
        }
        
        board = newBoard;
    }

    void run() {
        char input;
        
        while (!gameOver) {
            display();
            input = getch();
            
            switch (tolower(input)) {
                case 'a':
                    moveLeft();
                    break;
                case 'd':
                    moveRight();
                    break;
                case 'w':
                    moveUp();
                    break;
                case 's':
                    moveDown();
                    break;
                case 'q':
                    cout << "Thanks for playing!" << endl;
                    return;
                default:
                    cout << "Invalid input! Use W, A, S, D or Q to quit." << endl;
                    break;
            }
        }
        
        display();
    }
};

int main() {
    Game2048 game;
    game.run();
    return 0;
}
