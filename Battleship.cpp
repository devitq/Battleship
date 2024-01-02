#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime> 

using namespace std;

const int BOARD_SIZE = 10;
const int SHIPS[5] = {0, 4, 3, 2, 1};

void placeShip(int board[BOARD_SIZE][BOARD_SIZE], int length) {
    int direction = rand() % 2;
    int x = rand() % BOARD_SIZE;
    int y = rand() % BOARD_SIZE;

    while ((direction == 0 && x + length > BOARD_SIZE) || (direction == 1 && y + length > BOARD_SIZE)) {
        direction = rand() % 2;
        x = rand() % BOARD_SIZE;
        y = rand() % BOARD_SIZE;
    }

    for (int i = 0; i < length; ++i) {
        if (direction == 0) {
            board[x + i][y] = 1;
        }
        else {
            board[x][y + i] = 1;
        }
    }
}

void generateBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = 0;
        }
    }

    for (int length = 0; length < sizeof(SHIPS) / sizeof(int); ++length) {
        for (int i = 0; i < SHIPS[length]; ++i) {
            placeShip(board, length);
        }
    }
}

void renderBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 0) {
                printf("\033[3%d;4%dm", 7, 7);
                cout << " ";
                printf("\033[00m");
            }
            else if (board[i][j] == 1) {
                printf("\033[3%d;4%dm", 7, 7);
                cout << " ";
                printf("\033[00m");
            }
            else if (board[i][j] == 2) {
                printf("\033[3%d;4%dm", 7, 2);
                cout << "+";
                printf("\033[00m");
            }
            else if (board[i][j] == 3) {
                printf("\033[3%d;4%dm", 7, 1);
                cout << ".";
                printf("\033[00m");
            }
            cout << " ";
        }
        cout << endl;
    }
}

void shot(int board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    if (board[row][col] == 1 or board[row][col] == 2) {
        board[row][col] = 2;
    }
    else {
        board[row][col] = 3;
    }
}

bool checkForWin(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 1) {
                return true;
            }
        }
    }
    return false;
}

void welcome() {
    string welcome_message = "Welcome to Battleship(v0.1)!";
    string start_message = "Press enter to start";

    for (char c : welcome_message) {
        cout << c << flush;
        Sleep(25);
    }
    cout << endl;
    Sleep(25);
    cout << endl << flush;
    Sleep(25);
    for (char c : start_message) {
        cout << c << flush;
        Sleep(25);
    }
    cin.ignore();
}

int main() {
    srand(time(NULL));
    string decision = "";
    
    while (decision != "q") {
        int board[BOARD_SIZE][BOARD_SIZE];

        generateBoard(board);
        welcome();

        while (checkForWin(board)) {
            system("cls");
            cout << "Battleship" << endl;
            renderBoard(board);
            int row = -1, col = -1;
            cout << "Enter coordinates:" << endl;
            cout << "Enter x: ";
            cin >> col;
            cout << "Enter y: ";
            cin >> row;
            while ((row > BOARD_SIZE - 1 || col > BOARD_SIZE - 1 || row < 0 || col < 0) || (board[row][col] == 2 || board[row][col] == 3)) {
                system("cls");
                cout << "Battleship" << endl;
                renderBoard(board);
                cout << "Incorrect coordinats!" << endl;
                cout << "Enter coordinates:" << endl;
                cout << "Enter x: ";
                cin >> col;
                cout << "Enter y: ";
                cin >> row;
            }
            shot(board, row, col);
        }

        system("cls");
        cout << "Battleship" << endl;
        renderBoard(board);
        cout << "You won!" << endl;
        cout << "Wanna play again? (q - to Quit, other - to play again)" << endl;
        cin >> decision;
        system("cls");
    }

    return 0;
}
