#include <stdio.h>
#include <stdbool.h>

bool quit = false;
int board[4][4];
int start_game;

int max(int a, int b) {
	if (a >= b) return a;
	return b;
}

int min(int a, int b) {
	if (a <= b) return a;
	return b;
}

int checkWin(int a) {
	for (int row = 1; row <= 3; row++) {
		if (board[row][1] == board[row][2] && board[row][2] == board[row][3] && board[row][1] == a) {
			return a;
		}
		if (board[1][row] == board[2][row] && board[2][row] == board[3][row] && board[1][row] == a) {
			return a;
		}
	}
	if (board[1][1] == board[2][2] && board[2][2] == board[3][3] && board[1][1] == a) return a;
	if (board[3][1] == board[2][2] && board[2][2] == board[1][3] && board[1][3] == a) return a;
	return 0;
}

int evaluate() {
	for (int row = 1; row <= 3; row++) {
		if (board[row][1] == board[row][2] && board[row][2] == board[row][3]) {
			if (board[row][1] == 1) return -10;
			if (board[row][1] == 2) return 10;
		}
		if (board[1][row] == board[2][row] && board[2][row] == board[3][row]) {
			if (board[1][row] == 1) return -10;
			if (board[1][row] == 2) return 10;
		}
	}
	if (board[1][1] == board[2][2] && board[2][2] == board[3][3]) {
		if (board[1][1] == 1) return -10;
		if (board[1][1] == 2) return 10;
	}
	if (board[3][1] == board[2][2] && board[2][2] == board[1][3]) {
		if (board[3][1] == 1) return -10;
		if (board[3][1] == 2) return 10;
	}
	return 0;
}

bool checkTie() {
	for (int row = 1; row <= 3; row++) {
		for (int col = 1; col <= 3; col++) {
			if (board[row][col] == 0) return false;
		}
	}
	return true;
}

int minimax(int depth, int isMaximizing) {
	int score = evaluate();
	if (score == 10) return score;
	if (score == -10) return score;
	if (checkTie()) return 0;
	if (isMaximizing) {
		int best = -1000;
		for (int row = 1; row <= 3; row++) {
			for (int col = 1; col <= 3; col++) {
				if (board[row][col] == 0) {
					board[row][col] = 2;
					best = max(best, minimax(depth + 1, false));
					board[row][col] = 0;
				}
			}
		}
		return best;
	}
	else {
		int best = 1000;
		for (int row = 1; row <= 3; row++) {
			for (int col = 1; col <= 3; col++) {
				if (board[row][col] == 0) {
					board[row][col] = 1;
					best = min(best, minimax(depth + 1, true));
					board[row][col] = 0;
				}
			}
		}
		return best;
	}
}

void aiMove() {
	if (checkTie()) return;
	int best_move = -1000;
	int choice_row, choice_col;
	for (int row = 1; row <= 3; row++) {
		for (int col = 1; col <= 3; col++) {
			if (board[row][col] == 0) {
				board[row][col] = 2;
				int move_score = minimax(0, false);
				board[row][col] = 0;
				if (move_score > best_move) {
					choice_row = row;
					choice_col = col;
					best_move = move_score;
				}
			}
		}
	}
	board[choice_row][choice_col] = 2;
}

void printBoard() {
	printf("\n");
	printf("---+---+---\n");
	printf("    1  2  3\n");
	for (int row = 1; row <= 3; row++) {
		printf("%d : ", row);
		for (int col = 1; col <= 3; col++) {
			int cell = board[row][col];
			if (cell == 1)	printf("X |");
			else if (cell == 2) printf("O |");
			else printf("  |");
		}
		printf("\n");
	}
}

void init() {
	for (int row = 1; row <= 3; row++) {
		for (int col = 1; col <= 3; col++) board[row][col] = 0;
	}
	printf("Start the game!\n");
	printf("Yes (1)       No (2)\n");
	printf("Your option: ");
	scanf("%d", &start_game);
	if (start_game == 2) {
		printf("See u next time!\n");
		quit = true;
		return;
	}
}

void process() {
	while (!quit) {
		printBoard();
		int row, col;
		printf("Your row: ");
		scanf("%d", &row);
		printf("Your column: ");
		scanf("%d", &col);
		if (row < 1 || row > 3 || col < 1 || col > 3 || board[row][col] != 0) {
			printf("Invalid move, try again!\n");
			continue;
		}
		board[row][col] = 1;
		if (evaluate() == -10) {
			printBoard();
			printf("You win!\n");
			quit = true;
			return;
		}
		aiMove();
		if (evaluate() == 10) {
			printBoard();
			printf("You lose!\n");
			quit = true;
			return;
		}
		if (checkTie()) {
			printBoard();
			printf("Tie!\n");
			quit = true;
			return;
		}
	}
}

int main(int argc, char **argv) {
	init();
	process();
	// printf("%d", max(2, 5));
	return 0;
}
