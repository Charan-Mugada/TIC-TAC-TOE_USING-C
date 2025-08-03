#include<stdio.h>
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

void initialize_board(char board[3][3])
{
	int k='1';
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			board[i][j]=k++;
		}
	}
}

void print_board(char board[3][3])
{
	printf("\n");
	for(int i=0;i<3;i++)
	{
		printf(" ");
		for(int j=0;j<3;j++)
		{
			if(board[i][j] == 'X')
				printf(GREEN " %c " RESET, board[i][j]);
			else if(board[i][j] == 'O')
				printf(RED " %c " RESET, board[i][j]);
			else
				printf(YELLOW " %c " RESET, board[i][j]);

			if(j<2) printf(CYAN "|" RESET);
		}
		printf("\n");
		if(i<2) printf(CYAN "---|---|---\n" RESET);
	}
	printf("\n");
}

char check_winner(char board[3][3])
{
	for(int i=0;i<3;i++)
	{
		if(board[i][0]==board[i][1] && board[i][1]==board[i][2])
		{
			return board[i][0];
		}
		if(board[0][i]==board[1][i] && board[1][i]==board[2][i])
		{
			return board[0][i];
		}
	}
	
	if(board[0][0]==board[1][1] && board[1][1]==board[2][2])
	{
		return board[0][0];
	}
	if(board[0][2]==board[1][1] && board[1][1]==board[2][0])
	{
		return board[0][2];
	}
	
	return 'N';
}

void player_input(char board[3][3],int turn)
{
	int pos=0,row,col;
	row=col=-1;
	char symbol=(turn%2==1)?'X':'O';
	while(1)
	{
		printf(CYAN "\n->* Player %d has to play, assigned symbol is %c\n" RESET,(turn%2==1)?1:2,symbol);
		printf("Enter a position(1-9): ");
		scanf("%d",&pos);
		
		if(pos<1 || pos>9)
		{
			printf(RED "\n-->Invalid position. Try again.\n" RESET);
			continue;
		}
		row=(pos-1)/3;
		col=(pos-1)%3;
		
		if(board[row][col]!='X' && board[row][col]!='O')
		{
			board[row][col]=symbol;
			break;
		}
		else
		{
			printf(RED "Cell already taken. Try again.\n" RESET);
		}
	}
}

void bot(char board[3][3], int turn)
{
	int pos = 0, row, col;
	row = col = -1;

	if (turn % 2 == 1)
	{
		printf(GREEN "Human has to play, assigned symbol is 'X': " RESET);
		printf("Enter a position(1-9): ");
		scanf("%d", &pos);

		if (pos < 1 || pos > 9)
		{
			printf(RED "\n-->Invalid position. Try again.\n" RESET);
			bot(board, turn);  // retry
			return;
		}
		row = (pos - 1) / 3;
		col = (pos - 1) % 3;

		if (board[row][col] != 'X' && board[row][col] != 'O')
		{
			board[row][col] = 'X';
		}
		else
		{
			printf(RED "Cell already taken. Try again.\n" RESET);
			bot(board, turn);  // retry
		}
	}
	else
	{
		printf(CYAN "Bot is playing...\n" RESET);

		char bot = 'O', human = 'X';

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] != 'X' && board[i][j] != 'O')
				{
					char temp = board[i][j];
					board[i][j] = bot;
					if (check_winner(board) == bot)
						return;
					board[i][j] = temp;
				}
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] != 'X' && board[i][j] != 'O')
				{
					char temp = board[i][j];
					board[i][j] = human;
					if (check_winner(board) == human)
					{
						board[i][j] = bot;
						return;
					}
					board[i][j] = temp;
				}
			}
		}

		if (board[1][1] != 'X' && board[1][1] != 'O')
		{
			board[1][1] = bot;
			return;
		}

		int corners[4][2] = { {0,0}, {0,2}, {2,0}, {2,2} };
		for (int i = 0; i < 4; i++)
		{
			int r = corners[i][0], c = corners[i][1];
			if (board[r][c] != 'X' && board[r][c] != 'O')
			{
				board[r][c] = bot;
				return;
			}
		}

		int sides[4][2] = { {0,1}, {1,0}, {1,2}, {2,1} };
		for (int i = 0; i < 4; i++)
		{
			int r = sides[i][0], c = sides[i][1];
			if (board[r][c] != 'X' && board[r][c] != 'O')
			{
				board[r][c] = bot;
				return;
			}
		}
	}
}

int main()
{
	char board[3][3],winner;
	int turn=1,play;
	initialize_board(board);
	
	printf(CYAN "Want to play with Friend(press 1) or with Bot(press 2): " RESET);
	scanf("%d",&play);
	while(turn<=9)
	{
		print_board(board);
		winner=check_winner(board);
		if(winner=='N')
		{
			if(play==1)
			{
				player_input(board,turn);
				turn++;
			}
			else if(play==2)
			{
				bot(board,turn);
				turn++;
			}
			else
			{
				printf(RED "invalid input" RESET);
				continue;
			}
		}
		else
		{
			printf(GREEN "*******-> Player '%c' Won! <-*******\n\n" RESET,winner);
			break;
		} 
	}

	if(winner=='N')
		printf(YELLOW "It's a draw!\n" RESET);
	
	print_board(board);
	
	char play_again;
	printf(CYAN "Do you want to play again? (y/n): " RESET);
	scanf(" %c", &play_again);
	
	if(play_again == 'y' || play_again == 'Y') 
	{
		main(); 
	}
	else
	{
		printf(RED "Busy people\n" RESET);
	}
}
