#include <iostream>
#include <vector>

void drawBord(const std::vector<char>& board) {
    std::cout << "\n+---+---+---+\n";
    std::cout << "| " << board[0] << " | " << board[1] << " | " << board[2] << " |\n";
    std::cout << "+---+---+---+\n";
    std::cout << "| " << board[3] << " | " << board[4] << " | " << board[5] << " |\n";
    std::cout << "+---+---+---+\n";
    std::cout << "| " << board[6] << " | " << board[7] << " | " << board[8] << " |\n";
    std::cout << "+---+---+---+\n\n";
}

bool watchWin(const std::vector<char>& board, char player) {
    const int winCombinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (int i = 0; i < 8; ++i) {
        if (board[winCombinations[i][0]] == player &&
            board[winCombinations[i][1]] == player &&
            board[winCombinations[i][2]] == player) {
            return true;
        }
    }
    return false;
}

bool checkDraw(const std::vector<char>& board) {
    for (char c : board) {
        if (c != 'X' && c != 'O') return false;
    }
    return true;
}

int main6() {
    char playAgain = 'y';

    do {
        std::vector<char> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char currentPlayer = 'X';
        bool gameOver = false;

        while (!gameOver) {
            drawBord(board);
            std::cout << "Ігрок [" << currentPlayer << "], оберіть номер клітинки (1-9): ";

            int choice;
            if (!(std::cin >> choice) || choice < 1 || choice > 9) {
                std::cout << "Нізя! Введіть число від 1 до 9.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            int index = choice - 1;

            if (board[index] == 'X' || board[index] == 'O') {
                std::cout << "Ця клітинка вже зайнята!\n";
                continue;
            }

            board[index] = currentPlayer;

            if (watchWin(board, currentPlayer)) {
                drawBord(board);
                std::cout << "Переміг ігрок " << currentPlayer << "!\n";
                gameOver = true;
            } else if (checkDraw(board)) {
                drawBord(board);
                std::cout << "Нічия!\n";
                gameOver = true;
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        std::cout << "Зіграти ще раз? (y/n): ";
        std::cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
