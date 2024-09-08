#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int SIZE = 4; // Size of the game board

class Game2048 {
private:
    int board[SIZE][SIZE]; // 4x4 game board

    // Helper functions
    void initializeBoard(); // Initialize the game board with zeros
    void addRandomTile(); // Add a random tile (2 or 4) to the board
    bool canMove(); // Check if any moves are possible
    void moveLeft(); // Move tiles to the left
    void moveRight(); // Move tiles to the right
    void moveUp(); // Move tiles up
    void moveDown(); // Move tiles down
    void mergeLeft(); // Merge tiles to the left
    void mergeRight(); // Merge tiles to the right
    void mergeUp(); // Merge tiles up
    void mergeDown(); // Merge tiles down
    void printBoard(); // Print the current state of the board
    bool boardChanged(int oldBoard[SIZE][SIZE]); // Check if the board has changed after a move

public:
    Game2048(); // Constructor to initialize the game
    void play(); // Function to start the game
};

// Constructor to initialize the game
Game2048::Game2048() {
    initializeBoard();
    addRandomTile();
    addRandomTile();
}

// Initialize the game board with zeros
void Game2048::initializeBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = 0;
        }
    }
}

// Add a random tile (2 or 4) to the board
void Game2048::addRandomTile() {
    vector<pair<int, int>> emptyTiles;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                emptyTiles.push_back(make_pair(i, j));
            }
        }
    }

    if (!emptyTiles.empty()) {
        srand(time(0));
        int randomIndex = rand() % emptyTiles.size();
         // Generate a 2 with higher probability than 4
        int value = (rand() % 10 < 8) ? 2 : 4;
        // int value = (rand() % 2 + 1) * 2;
        board[emptyTiles[randomIndex].first][emptyTiles[randomIndex].second] = value;
    }
}

// Print the current state of the board
void Game2048::printBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// Check if any moves are possible
bool Game2048::canMove() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) return true;
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return true;
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return true;
        }
    }
    return false;
}

// Check if the board has changed after a move
bool Game2048::boardChanged(int oldBoard[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] != oldBoard[i][j]) {
                return true;
            }
        }
    }
    return false;
}

// Move tiles to the left
void Game2048::moveLeft() {
    for (int i = 0; i < SIZE; ++i) {
        int index = 0;
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] != 0) {
                board[i][index] = board[i][j];
                if (index != j) board[i][j] = 0;
                index++;
            }
        }
    }
}

// Merge tiles to the left
void Game2048::mergeLeft() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                board[i][j] *= 2;
                board[i][j + 1] = 0;
            }
        }
    }
}

// Move tiles to the right
void Game2048::moveRight() {
    for (int i = 0; i < SIZE; ++i) {
        int index = SIZE - 1;
        for (int j = SIZE - 1; j >= 0; --j) {
            if (board[i][j] != 0) {
                board[i][index] = board[i][j];
                if (index != j) board[i][j] = 0;
                index--;
            }
        }
    }
}

// Merge tiles to the right
void Game2048::mergeRight() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = SIZE - 1; j > 0; --j) {
            if (board[i][j] != 0 && board[i][j] == board[i][j - 1]) {
                board[i][j] *= 2;
                board[i][j - 1] = 0;
            }
        }
    }
}

// Move tiles up
void Game2048::moveUp() {
    for (int j = 0; j < SIZE; ++j) {
        int index = 0;
        for (int i = 0; i < SIZE; ++i) {
            if (board[i][j] != 0) {
                board[index][j] = board[i][j];
                if (index != i) board[i][j] = 0;
                index++;
            }
        }
    }
}

// Merge tiles up
void Game2048::mergeUp() {
    for (int j = 0; j < SIZE; ++j) {
        for (int i = 0; i < SIZE - 1; ++i) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j]) {
                board[i][j] *= 2;
                board[i + 1][j] = 0;
            }
        }
    }
}

// Move tiles down
void Game2048::moveDown() {
    for (int j = 0; j < SIZE; ++j) {
        int index = SIZE - 1;
        for (int i = SIZE - 1; i >= 0; --i) {
            if (board[i][j] != 0) {
                board[index][j] = board[i][j];
                if (index != i) board[i][j] = 0;
                index--;
            }
        }
    }
}

// Merge tiles down
void Game2048::mergeDown() {
    for (int j = 0; j < SIZE; ++j) {
        for (int i = SIZE - 1; i > 0; --i) {
            if (board[i][j] != 0 && board[i][j] == board[i - 1][j]) {
                board[i][j] *= 2;
                board[i - 1][j] = 0;
            }
        }
    }
}

// Function to start the game
void Game2048::play() {
    char move;
    while (true) {
        printBoard();
        if (!canMove()) {
            cout << "Game Over!" << endl;
            break;
        }
        // l->left
        // r->right
        // u->up
        // d->down
        cout << "Enter move (l/r/u/d/e): ";
        cin >> move;
        int oldBoard[SIZE][SIZE];
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                oldBoard[i][j] = board[i][j];
            }
        }
        switch (move) {
            case 'l':
                moveLeft();
                mergeLeft();
                moveLeft();
                break;
            case 'r':
                moveRight();
                mergeRight();
                moveRight();
                break;
            case 'u':
                moveUp();
                mergeUp();
                moveUp();
                break;
            case 'd':
                moveDown();
                mergeDown();
                moveDown();
                break;
            case 'e':
                cout<<"Exiting from game"<<endl;
                exit(0);
            default:
                cout << "Invalid move!" << endl;
                continue;
        }
        if (boardChanged(oldBoard)) {
            addRandomTile();
        }
        else
        cout<<"Please select other move"<<endl;
    }
}

int main() {
    Game2048 game;
    game.play();
    return 0;
}
