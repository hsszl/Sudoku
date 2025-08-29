//
// Created by hsszl on 2025/8/29.
// 输入相同目录Q.txt
//

#include <fstream>
#include <iostream>
#include <windows.h>

// ai写的
void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // 清屏 + 光标移到 (1,1)
}

void SetColor(int textColor, int bgColor) {
    WORD color = (bgColor << 4) + textColor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void print_board(char board[][9], int i, int j) {
    for (int m = 0; m < 9; m++) {
        if (m % 3 == 0 and m != 0) std::cout << "------+-------+------\n";
        for (int n = 0; n < 9; n++) {
            if (n % 3 == 0 and n != 0) std::cout << "| ";
            // 变色 让他好看点 同时醒目
            if (m == i and n == j) {
                SetColor(2, 15);
                std::cout << board[m][n];
                SetColor(15, 0);
                std::cout << " ";
            }
            else std::cout << board[m][n] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool isValid(char board[][9], int i, int j, char c) {
    // 横向, 纵向1*9
    for (int k = 0; k < 9; k++) {
        if (board[i][k] == c) return false;
        if (board[k][j] == c) return false;
    }
    // 3*3
    for (int k = i / 3 * 3; k < i / 3 * 3 + 3; k++) {
        for (int l = j / 3 * 3; l < j / 3 * 3 + 3; l++) {
            if (board[k][l] == c) return false;
        }
    }
    return true;
}

bool Sudoku(char board[][9], int i, int j) {

    // 找到一个可行解
    if (i == 9 and j == 0) return true;
    // 换行
    if (j == 9) return Sudoku(board, i + 1, 0);

    // 逐个尝试
    if (board[i][j] == '.') {
        for (int k = 1; k <= 9; k++) {
            if (isValid(board, i, j, k + '0')) {
                board[i][j] = k + '0';

                // 动画效果
                // clearScreen();
                // print_board(board, i, j);
                // Sleep(1);

                if (Sudoku(board, i, j + 1)) return true;
                board[i][j] = '.';
            }
        }
    }
    else return Sudoku(board, i, j + 1);

    // 回溯
    return false;
}

int main() {

    std::ifstream infile;
    infile.open("Q.txt", std::ios::in);
    if (!infile.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }\

    char board[9][9] = {
        {'5', '.', '.', '.', '3', '2', '.', '.', '.'},
        {'.', '.', '.', '7', '.', '.', '.', '.', '.'},
        {'.', '.', '4', '.', '.', '.', '3', '5', '.'},
        {'4', '.', '.', '6', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '2', '5', '.', '9', '.', '6'},
        {'7', '.', '.', '9', '.', '.', '1', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'2', '.', '8', '5', '.', '.', '.', '7', '.'},
        {'.', '.', '3', '.', '.', '9', '.', '8', '.'}
    };
    std::pmr::string buf;
    int i = 0, j = 0;
    while (getline(infile, buf)) {
        j = 0;
        for (char s: buf) {
            board[i][j] = s;
            j += 1;
        }
        i += 1;
    }
    print_board(board, 8, 8);
    system("pause");


    if (Sudoku(board, 0, 0)) {
        // print_board(board, 8, 8);
        // system("pause");
        return 0;
    }
    else {
        std::cout << "No solution" << std::endl;
        return 1;
    }
}
