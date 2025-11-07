#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 10;
const char EMPTY = '.';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';

class BattleshipGame {
private:
    vector<vector<char>> playerBoard;
    vector<vector<char>> computerBoard;
    vector<vector<char>> playerGuessBoard;
    vector<vector<char>> computerGuessBoard;
    
    int playerShips;
    int computerShips;

public:
    BattleshipGame() {
        // Initialize boards
        playerBoard.resize(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY));
        computerBoard.resize(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY));
        playerGuessBoard.resize(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY));
        computerGuessBoard.resize(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY));
        
        playerShips = 5;  // Total ships for each player
        computerShips = 5;
        
        srand(time(0));  // Seed for random number generation
    }

    void printBoard(const vector<vector<char>>& board, bool showShips = false) {
        cout << "  ";
        for (int i = 0; i < BOARD_SIZE; i++) {
            cout << i << " ";
        }
        cout << endl;
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            cout << i << " ";
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (!showShips && board[i][j] == SHIP) {
                    cout << EMPTY << " ";
                } else {
                    cout << board[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    bool placeShip(vector<vector<char>>& board, int row, int col, int size, bool horizontal) {
        // Check if ship can be placed
        if (horizontal) {
            if (col + size > BOARD_SIZE) return false;
            for (int i = 0; i < size; i++) {
                if (board[row][col + i] != EMPTY) return false;
            }
            // Place the ship
            for (int i = 0; i < size; i++) {
                board[row][col + i] = SHIP;
            }
        } else {
            if (row + size > BOARD_SIZE) return false;
            for (int i = 0; i < size; i++) {
                if (board[row + i][col] != EMPTY) return false;
            }
            // Place the ship
            for (int i = 0; i < size; i++) {
                board[row + i][col] = SHIP;
            }
        }
        return true;
    }

    void placePlayerShips() {
        int shipSizes[] = {5, 4, 3, 3, 2};  // Carrier, Battleship, Cruiser, Submarine, Destroyer
        string shipNames[] = {"Carrier (5)", "Battleship (4)", "Cruiser (3)", "Submarine (3)", "Destroyer (2)"};
        
        cout << "Place your ships!\n";
        
        for (int i = 0; i < 5; i++) {
            bool placed = false;
            while (!placed) {
                cout << "\nPlace your " << shipNames[i] << ":\n";
                printBoard(playerBoard, true);
                
                int row, col;
                char direction;
                cout << "Enter row (0-9): ";
                cin >> row;
                cout << "Enter column (0-9): ";
                cin >> col;
                cout << "Horizontal (H) or Vertical (V)? ";
                cin >> direction;
                
                bool horizontal = (direction == 'H' || direction == 'h');
                
                if (placeShip(playerBoard, row, col, shipSizes[i], horizontal)) {
                    placed = true;
                    cout << "Ship placed successfully!\n";
                } else {
                    cout << "Cannot place ship there! Try again.\n";
                }
            }
        }
    }

    void placeComputerShips() {
        int shipSizes[] = {5, 4, 3, 3, 2};
        
        for (int i = 0; i < 5; i++) {
            bool placed = false;
            while (!placed) {
                int row = rand() % BOARD_SIZE;
                int col = rand() % BOARD_SIZE;
                bool horizontal = rand() % 2 == 0;
                
                if (placeShip(computerBoard, row, col, shipSizes[i], horizontal)) {
                    placed = true;
                }
            }
        }
        cout << "Computer has placed its ships.\n";
    }

    bool makeGuess(vector<vector<char>>& targetBoard, vector<vector<char>>& guessBoard, int row, int col) {
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
            return false;  // Invalid coordinates
        }
        
        if (guessBoard[row][col] != EMPTY) {
            return false;  // Already guessed
        }
        
        if (targetBoard[row][col] == SHIP) {
            guessBoard[row][col] = HIT;
            targetBoard[row][col] = HIT;
            return true;  // Hit
        } else {
            guessBoard[row][col] = MISS;
            return true;  // Miss
        }
    }

    void playerTurn() {
        cout << "\n=== YOUR TURN ===\n";
        cout << "Your guess board:\n";
        printBoard(playerGuessBoard);
        
        int row, col;
        bool validGuess = false;
        
        while (!validGuess) {
            cout << "Enter row to attack (0-9): ";
            cin >> row;
            cout << "Enter column to attack (0-9): ";
            cin >> col;
            
            if (makeGuess(computerBoard, playerGuessBoard, row, col)) {
                validGuess = true;
                if (computerBoard[row][col] == HIT) {
                    cout << "HIT!\n";
                    computerShips--;
                } else {
                    cout << "MISS!\n";
                }
            } else {
                cout << "Invalid guess! Try again.\n";
            }
        }
    }

    void computerTurn() {
        cout << "\n=== COMPUTER'S TURN ===\n";
        
        int row, col;
        bool validGuess = false;
        
        while (!validGuess) {
            row = rand() % BOARD_SIZE;
            col = rand() % BOARD_SIZE;
            
            if (makeGuess(playerBoard, computerGuessBoard, row, col)) {
                validGuess = true;
                if (playerBoard[row][col] == HIT) {
                    cout << "Computer HIT your ship at (" << row << "," << col << ")!\n";
                    playerShips--;
                } else {
                    cout << "Computer MISSED at (" << row << "," << col << ")!\n";
                }
            }
        }
    }

    void play() {
        cout << "=== WELCOME TO BATTLESHIP ===\n\n";
        
        placePlayerShips();
        placeComputerShips();
        
        while (playerShips > 0 && computerShips > 0) {
            // Player's turn
            playerTurn();
            
            // Check if game over
            if (computerShips == 0) {
                cout << "\n*** CONGRATULATIONS! YOU WIN! ***\n";
                break;
            }
            
            // Computer's turn
            computerTurn();
            
            // Check if game over
            if (playerShips == 0) {
                cout << "\n*** GAME OVER! COMPUTER WINS! ***\n";
                break;
            }
            
            // Show status
            cout << "\n=== STATUS ===\n";
            cout << "Your ships remaining: " << playerShips << endl;
            cout << "Computer ships remaining: " << computerShips << endl;
            
            cout << "\nYour board:\n";
            printBoard(playerBoard, true);
            cout << "\nYour guess board:\n";
            printBoard(playerGuessBoard);
        }
        
        cout << "\n=== FINAL BOARDS ===\n";
        cout << "Your final board:\n";
        printBoard(playerBoard, true);
        cout << "\nComputer's final board:\n";
        printBoard(computerBoard, true);
    }
};

int main() {
    BattleshipGame game;
    game.play();
    return 0;
}