//Welcome to the ai powered tic tac toe game.
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <ctime>
using namespace std;

class TicTacToe {
    const int size = 3;
    const char AI_MOVE = 'O';
    const char HUMAN_MOVE = 'X';
    vector<vector<char>> board; // 3x3 game board
    int playerScore = 0; // Player win count
    int aiScore = 0;     // AI win count

public:
    TicTacToe() {
        board.resize(size, vector<char>(size, ' ')); // Initialize empty board
    }

    void showInstructions() {
        // Display instructions for how to choose a cell
        cout << "\nChoose a cell numbered from 1 to 9 as below and play\n\n";
        cout << "\t\t\t 1 | 2 | 3 \n";
        cout << "\t\t\t-----------\n";
        cout << "\t\t\t 4 | 5 | 6 \n";
        cout << "\t\t\t-----------\n";
        cout << "\t\t\t 7 | 8 | 9 \n\n";
    }

    void showBoard() {
        // Display the current board
        for (int i = 0; i < size; ++i) {
            cout << "\t\t\t ";
            for (int j = 0; j < size; ++j) {
                cout << board[i][j];
                if (j < size - 1) cout << " | ";
            }
            cout << "\n";
            if (i < size - 1) cout << "\t\t\t-----------\n";
        }
        cout << "\n";
    }

    void resetBoard() {
        // Reset all cells to blank
        for (auto& row : board)
            fill(row.begin(), row.end(), ' ');
    }

    bool rowCrossed() {
        // Check if any row is completed
        for (int i = 0; i < size; i++)
            if (board[i][0] == board[i][1] &&
                board[i][1] == board[i][2] &&
                board[i][0] != ' ')
                return true;
        return false;
    }

    bool columnCrossed() {
        // Check if any column is completed
        for (int i = 0; i < size; i++)
            if (board[0][i] == board[1][i] &&
                board[1][i] == board[2][i] &&
                board[0][i] != ' ')
                return true;
        return false;
    }

    bool diagonalCrossed() {
        // Check both diagonals
        if (board[0][0] == board[1][1] &&
            board[1][1] == board[2][2] &&
            board[0][0] != ' ')
            return true;
        if (board[0][2] == board[1][1] &&
            board[1][1] == board[2][0] &&
            board[0][2] != ' ')
            return true;
        return false;
    }

    bool gameOver() {
        // Check if the game is won
        return rowCrossed() || columnCrossed() || diagonalCrossed();
    }

    int minimax(int depth, bool isAI, int alpha, int beta) {
        // Minimax algorithm with alpha-beta pruning
        if (gameOver()) return isAI ? -1 : 1;
        if (depth == size * size) return 0;

        if (isAI) {
            int bestScore = -999;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = AI_MOVE;
                        int score = minimax(depth + 1, false, alpha, beta);
                        board[i][j] = ' ';
                        bestScore = max(score, bestScore);
                        alpha = max(alpha, score);
                        if (beta <= alpha)
                            return bestScore;
                    }
                }
            }
            return bestScore;
        } else {
            int bestScore = 999;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = HUMAN_MOVE;
                        int score = minimax(depth + 1, true, alpha, beta);
                        board[i][j] = ' ';
                        bestScore = min(score, bestScore);
                        beta = min(beta, score);
                        if (beta <= alpha)
                            return bestScore;
                    }
                }
            }
            return bestScore;
        }
    }

    int bestMove(int moveIndex) {
        // Determine the best move using minimax
        int bestScore = -999, move = -1;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = AI_MOVE;
                    int score = minimax(moveIndex + 1, false, -999, 999);
                    board[i][j] = ' ';
                    if (score > bestScore) {
                        bestScore = score;
                        move = i * size + j;
                    }
                }
            }
        }
        return move;
    }

    void playSingleGame(bool playerStarts) {
        // Play a single game
        resetBoard();
        int moveIndex = 0;
        bool isAITurn = !playerStarts;
        showBoard();

        while (!gameOver() && moveIndex < size * size) {
            if (isAITurn) {
                int move = bestMove(moveIndex);
                int x = move / size, y = move % size;
                board[x][y] = AI_MOVE;
                cout << "AI has put a " << AI_MOVE << " in cell " << (move + 1) << "\n\n";
            } else {
                int cell;
                cout << "Available positions: ";
                for (int i = 0; i < size * size; ++i)
                    if (board[i / size][i % size] == ' ')
                        cout << i + 1 << " ";
                cout << "\nEnter position: ";
                cin >> cell;
                cell--;
                int x = cell / size, y = cell % size;
                if (cell >= 0 && cell < size * size && board[x][y] == ' ')
                    board[x][y] = HUMAN_MOVE;
                else {
                    cout << "Invalid or occupied cell. Try again.\n";
                    continue;
                }
            }
            moveIndex++;
            showBoard();
            if(gameOver()) break;
            isAITurn = !isAITurn;
        }

        if (!gameOver())
            cout << "It's a draw\n";
        else {
            bool aiWon = isAITurn; // Last move was by winner
            if (aiWon) {
                aiScore++;
                cout << "AI has won this match.\n";
            } else {
                playerScore++;
                cout << "You have won this match.\n";
            }
        }
    }

    string currentDateTime() {
        // Get current time as string
        time_t now = time(0);
        char* dt = ctime(&now);
        return string(dt);
    }

    void logTournamentResult(int player, int ai, int totalMatches) {
        // Save tournament result to file
        ofstream logFile("game_log.txt", ios::app);
        if (!logFile) {
            cout << "Error opening log file.\n";
            return;
        }
        logFile << "Tournament Started: " << currentDateTime();
        logFile << "Match Format: Best of " << totalMatches << "\n";
        logFile << "Final Score => You: " << player << " | AI: " << ai << "\n";
        logFile << "Winner: " << (player > ai ? "You" : (player < ai) ? "AI" : "Draw") << "\n";
        logFile << "----------------------------------------\n";
        logFile.close();
    }

    void playTournament() {
        // Handle multiple games as a tournament
        cout << "\nChoose tournament format (best of 3/5/7/10 or a single match): ";
        int totalMatches;
        cin >> totalMatches;

        showInstructions();

        int originalMatches = totalMatches;
        while (totalMatches--) {
            char first;
            cout << "\nDo you want to start first this match? (y/n): ";
            cin >> first;
            playSingleGame(first == 'y');
            cout << "Score => You: " << playerScore << " | AI: " << aiScore << "\n";
        }

        if (playerScore > aiScore)
            cout << "\nCongratulations! You won the tournament.\n";
        else if(playerScore == aiScore)
            cout << "\nSurprised right! Tournament ends in a draw.\n";
        else
            cout << "\nAI won the tournament. Better luck next time!\n";

        logTournamentResult(playerScore, aiScore, originalMatches);

        playerScore = aiScore = 0; // Reset scores for next tournament
    }
};

int main() {
    cout << "\n-------------------------------------------------------------------\n\n";
    cout << "\t\tWelcome to Tic-Tac-Toe Tournament\n";
    cout << "\n-------------------------------------------------------------------\n\n";

    TicTacToe game;
    char playAgain = 'y';
    while (playAgain == 'y') {
        game.playTournament();
        cout << "\nDo you want to play another tournament? (y/n): ";
        cin >> playAgain;
    }

    cout << "\nThanks for playing!\n";
    return 0;
}
