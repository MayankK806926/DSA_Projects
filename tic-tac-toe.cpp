#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

// Player structure
struct Player {
    string name;
    char symbol;
};

// Print the current game grid
void printGrid(const vector<vector<char>>& grid) {
    cout << "\nCurrent Grid:\n";
    for (const auto& row : grid) {
        for (char cell : row) cout << cell << " ";
        cout << endl;
    }
}

// Validate move order (optional but included for integrity)
bool isValidMove(const vector<vector<char>>& grid, char currentSymbol) {
    int countCurrent = 0, countOther = 0;
    for (const auto& row : grid) {
        for (char cell : row) {
            if (cell == currentSymbol) countCurrent++;
            else if (cell != '.' && cell != currentSymbol) countOther++;
        }
    }
    return abs(countCurrent - countOther) <= 1;
}

// Check if a player has won
bool checkWinner(const vector<vector<char>>& grid, char symbol) {
    for (int i = 0; i < 3; ++i) {
        if (grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) return true;
        if (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol) return true;
    }
    if (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) return true;
    if (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol) return true;
    return false;
}

// Play a full game session
bool playGame(vector<vector<char>>& grid, Player players[2], int startingPlayerIndex) {
    for (int turn = 0; turn < 9; ++turn) {
        int currentIndex = (turn % 2 == 0) ? startingPlayerIndex : 1 - startingPlayerIndex;
        Player current = players[currentIndex];

        cout << "\nTurn " << turn + 1 << " - " << current.name << " (" << current.symbol << "): Enter row and column (1-3): ";
        int row, col;
        cin >> row >> col;

        if (row < 1 || row > 3 || col < 1 || col > 3) {
            cout << "Invalid input. Try again.\n";
            turn--;
            continue;
        }

        row--; col--;
        if (grid[row][col] != '.') {
            cout << "Cell already filled. Try again.\n";
            turn--;
            continue;
        }

        grid[row][col] = current.symbol;

        if (!isValidMove(grid, current.symbol)) {
            cout << "Invalid move. Turn violation.\n";
            return false;
        }

        printGrid(grid);

        if (checkWinner(grid, current.symbol)) {
            cout << "\n🏆 Winner is: " << current.name << endl;
            return true;
        }
    }

    cout << "\nIt's a Draw! Try Again.\n";
    return false;
}

int main() {
    Player players[2];
    vector<vector<char>> grid(3, vector<char>(3, '.'));

    // Player 1 input
    cout << "Enter name for Player 1: ";
    getline(cin, players[0].name);
    while (true) {
        cout << players[0].name << ", choose your symbol (non-dot character): ";
        cin >> players[0].symbol;
        if (players[0].symbol != '.' && !isspace(players[0].symbol)) break;
        cout << "Invalid symbol. Try again.\n";
    }

    cin.ignore(); // Clear newline for getline
    cout << "Enter name for Player 2: ";
    getline(cin, players[1].name);
    while (true) {
        cout << players[1].name << ", choose your symbol (different from " << players[0].symbol << "): ";
        cin >> players[1].symbol;
        if (players[1].symbol != players[0].symbol && players[1].symbol != '.' && !isspace(players[1].symbol)) break;
        cout << "Invalid or duplicate symbol. Try again.\n";
    }

    // Ask who goes first
    cin.ignore();
    string starterName;
    int startingPlayerIndex = -1;
    while (true) {
        cout << "\nWho will start first? (" << players[0].name << " or " << players[1].name << "): ";
        getline(cin, starterName);
        if (starterName == players[0].name) {
            startingPlayerIndex = 0;
            break;
        } else if (starterName == players[1].name) {
            startingPlayerIndex = 1;
            break;
        } else {
            cout << "Invalid name. Please type exactly as entered earlier.\n";
        }
    }

    printGrid(grid);

    // Play the game
    while (!playGame(grid, players, startingPlayerIndex)) {
        grid = vector<vector<char>>(3, vector<char>(3, '.'));
        printGrid(grid);
    }

    return 0;
}