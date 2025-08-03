#include<stdio.h>

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
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf(" %c ",board[i][j]);
			if(j<2) printf("|");
		}
		printf("\n");
		if(i<2) printf("---|---|---\n");
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
		printf("\n->* Player %d has to play, assigned symbol is %c\n",(turn%2==1)?1:2,symbol);
		printf("Enter a position(1-9): ");
		scanf("%d",&pos);
		
		if(pos<1 || pos>9)
		{
			printf("\n-->Invalid position. Try again.\n");
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
			printf("Cell already taken. Try again.\n");
		}
	}
}
void bot(char board[3][3], int turn)
{
	int pos = 0, row, col;
	row = col = -1;

	if (turn % 2 == 1)
	{
		printf("Human has to play, assigned symbol is 'X': ");
		printf("Enter a position(1-9): ");
		scanf("%d", &pos);

		if (pos < 1 || pos > 9)
		{
			printf("\n-->Invalid position. Try again.\n");
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
			printf("Cell already taken. Try again.\n");
			bot(board, turn);  // retry
		}
	}
	else
	{
		printf("Bot is playing...\n");

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
	
	printf("Want to play with Friend(press 1) or with Bot(press 2): ");
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
				printf("invalid input");
				continue;
			}
		}
		else
		{
			printf("*******-> Player '%c' Won! <-*******\n\n",winner);
			break;
		}	
	}

	if(winner=='N')
	printf("It's a draw!\n");
	
	print_board(board);
	
	char play_again;
	printf("Do you want to play again? (y/n): ");
	scanf(" %c", &play_again);
	
	if(play_again == 'y' || play_again == 'Y') 
	{
		main(); 
	}
	else
	{
		printf("Busy people\n");
	}

}
