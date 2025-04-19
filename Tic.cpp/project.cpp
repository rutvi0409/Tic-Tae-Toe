#include <iostream>
#include <fstream> // For file handling
#include <cstring> // For using char arrays (like strings without STL)

using namespace std;

//
// 🧑‍🏫 Base class for all players
//
class Player {
protected:
    char name[50];     // Player's name
    char marker;       // 'X' or 'O'
    int wins;          // Number of games won

public:
    // Constructor to initialize the player
    Player(const char* n, char m) {
        strcpy(name, n);
        marker = m;
        wins = 0;
    }

    // Virtual function to be defined in derived class
    virtual void makeMove(char board[3][3]) = 0;

    // Getters
    const char* getName() { return name; }
    char getMarker() { return marker; }
    int getWins() { return wins; }

    // Increase win count
    void addWin() { wins++; }

    // 👉 Operator Overloading to compare wins between two players
    bool operator > (Player& p) {
        return this->wins > p.getWins();
    }
};

//
// 🧍 Derived class for a human player
//
class HumanPlayer : public Player {
public:
    // Constructor that just calls the base one
    HumanPlayer(const char* n, char m) : Player(n, m) {}

    // Function to take user input and place marker on board
    void makeMove(char board[3][3]) override {
        int slot;
        bool valid = false;

        // Keep asking until the player makes a valid move
        while (!valid) {
            cout << name << " (" << marker << "), enter your move (1-9): ";
            cin >> slot;

            // Basic input check
            if (slot < 1 || slot > 9) {
                cout << "Oops! Invalid input. Try again.\n";
                continue;
            }

            // Convert 1-9 into board row & column
            int row = (slot - 1) / 3;
            int col = (slot - 1) % 3;

            // Check if the chosen spot is empty
            if (board[row][col] == ' ') {
                board[row][col] = marker;
                valid = true;
            } else {
                cout << "That spot is already taken! Choose another one.\n";
            }
        }
    }
};

//
// 🕹 Game class that manages the board and gameplay
//
class TicTacToe {
    char board[3][3];   // 3x3 board
    Player* p1;
    Player* p2;

public:
    // Constructor to initialize the game board and players
    TicTacToe(Player* player1, Player* player2) {
        p1 = player1;
        p2 = player2;
        initBoard();
    }

    // Fill board with blank spaces
    void initBoard() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = ' ';
    }

    // Nicely display the current board
    void displayBoard() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            cout << " ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << "---|---|---\n";
        }
        cout << "\n";
    }

    // Check if a player has won
    bool checkWin(char m) {
        for (int i = 0; i < 3; i++)
            if ((board[i][0] == m && board[i][1] == m && board[i][2] == m) ||
                (board[0][i] == m && board[1][i] == m && board[2][i] == m))
                return true;

        if ((board[0][0] == m && board[1][1] == m && board[2][2] == m) ||
            (board[0][2] == m && board[1][1] == m && board[2][0] == m))
            return true;

        return false;
    }

    // Save the game result to a text file
    void saveResult(const char* result) {
        ofstream file("game_results.txt", ios::app);
        if (file.is_open()) {
            file << result << endl;
            file.close();
        }
    }

    // Read and show previous game results from the file
    void showGameHistory() {
        ifstream file("game_results.txt");
        char line[100];
        cout << "\n📜 Game History:\n";
        while (file.getline(line, 100)) {
            cout << line << endl;
        }
        file.close();
    }

    // The full game logic (play once)
    void play() {
        displayBoard();

        for (int turn = 0; turn < 9; turn++) {
            Player* current = (turn % 2 == 0) ? p1 : p2;
            current->makeMove(board);
            displayBoard();

            if (checkWin(current->getMarker())) {
                cout << "🎉 " << current->getName() << " wins the game!\n";
                current->addWin();

                char result[100];
                sprintf(result, "%s won the game!", current->getName());
                saveResult(result);
                return;
            }
        }

        cout << "🤝 It's a draw!\n";
        saveResult("Game ended in a draw.");
    }
};

//
// 🌟 MAIN FUNCTION – where everything starts
//
int main() {
    cout << "=============================\n";
    cout << "     Advanced Tic Tac Toe    \n";
    cout << "=============================\n";

    // Take names from the users
    char name1[50], name2[50];
    cout << "Enter Player 1 Name: ";
    cin >> name1;
    cout << "Enter Player 2 Name: ";
    cin >> name2;

    // Create two players
    HumanPlayer p1(name1, 'X');
    HumanPlayer p2(name2, 'O');

    // Create and start the game
    TicTacToe game(&p1, &p2);
    game.play();

    // Compare player wins
    cout << "\n🏆 Comparing Wins:\n";
    if (p1 > p2)
        cout << p1.getName() << " is the champion so far!\n";
    else if (p2 > p1)
        cout << p2.getName() << " is the champion so far!\n";
    else
        cout << "Both players are equally strong!\n";

    // Show past games
    game.showGameHistory();

    return 0;
}