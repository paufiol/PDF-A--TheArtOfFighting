#include <stdio.h>
#include <stdlib.h>


void isDraw(char board[3][3]) {
	int fullboard = 0;
	
	for(int i = 0; i <= 3; i++) {
		for(int j = 0; j <= 3; j++) {
			if (board[i][j] == 0) {
				break;
			}
			else {
				fullboard++;
			}
		}
	}
	
	if(fullboard == 9) {
		printf("The game has ended in a draw!\n");
		system("pause");
		system("end");
	}
}

void isWin(char board[3][3]) {

	for (int i = 0; i < 3; i++) { //HORIZONTAL WIN	
		if ((board[i][0] == board[i][1]) && (board[i][2] == board[i][0])) {
			if (board[i][1] == 'x') {
				printf("Player 1 wins\n");
				system("pause");
				//system("end");
			}
			if (board[i][1] == 'o') {
				printf("Player 2 wins\n");
				system("pause");
				//system("end");
			}
		}

	}

	for (int i = 0; i < 3; i++) { // VERTICAL WIN
		if ((board[0][i] == board[1][i]) && (board[2][i] == board[0][i])) {
			if (board[1][i] == 'x') {
				printf("Player 1 wins\n");
				system("pause");
				system("end");
			}
			if (board[1][i] == 'o') {
				printf("Player 2 wins\n");
				system("pause");
				system("end");
			}
		}

	}

	//DIAGONAL WIN 1
	if ((board[0][0] == board[2][2]) && (board[0][0] == board[1][1])) {
		if (board[1][1] == 'x') {
			printf("Player 1 wins\n");
			system("pause");
			system("end");
		}
		if (board[1][1] == 'o') {
			printf("Player 2 wins\n");
			system("pause");
			system("end");
		}
	} 
	
	//DIAGONAL WIN 2
	if ((board[0][2] == board[1][1]) && (board[2][0] == board[0][2])) {
		if (board[2][2] == 'x') {
			printf("Player 1 wins\n");
			system("pause");
			system("end");
		}
		if (board[2][2] == 'o') {
			printf("Player 2 wins\n");
			system("pause");
			system("end");
		}
	}
}

void Play(char board[3][3], int player) {
	while (0 < 1) {
		int row = 0, col = 0;
		printf("   Where do you want to play your piece? (row, column): ");
		scanf_s("%d %d", &row, &col);
		if (board[row - 1][col - 1] == 0) {
			if ( player == 1 ) {
				board[row - 1][col - 1] = 'x';
			}
			if (player == 2) {
				board[row - 1][col - 1] = 'o';
			}
			break;
		}
		else {
			printf("You can't play a token in an ocuppied space. Try in a different place\n");
		}
	}
}



int main() {
	char board[3][3] = { {}, {}, {}, };
	int player;

	while (0 < 1) {
		printf("\n");
	
		printf("PLAYER 1's TURN: \n");
		player = 1; // This defines whose turn is it.
		Play(board, player);

		printf("PLAYER 2's TURN: \n");
		player = 2; 
		Play(board, player);

		printf("\n");
		printf("\n -------------\n |");

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				printf(" %c |", board[i][j]);
			}
			if ( i == 2 ){
				printf("\n -------------\n");
			}
			else{
				printf("\n -------------\n |");
			}
		}

		isDraw(board);

		isWin(board);

	}
	system("pause");
	return 0;
}