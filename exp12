#include <stdio.h>
#include <stdbool.h>

#define MAX 10
int count = 0;

bool isSafe(int row, int col, int n, int board[]) {
	for (int i = 0; i < row; i++) {
		if (board[i] == col || 
			board[i] - i == col - row || 
			board[i] + i == col + row) {
			return false;
		}
	}
	return true;
}

void solveNQueen(int row, int n, int board[]) {
	if (row == n) {
		count++;
		return;
	}

	for (int col = 0; col < n; col++) {
		if (isSafe(row, col, n, board)) {
			board[row] = col;
			solveNQueen(row + 1, n, board);
		}
	}
}
int nQueen(int n) {
	count = 0;
	int board[MAX];
	solveNQueen(0, n, board);
	return count;
}
