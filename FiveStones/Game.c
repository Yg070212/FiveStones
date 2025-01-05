#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>

#define UP 72
#define LEFT 75
#define DOWN 80
#define RIGHT 77
#define SPACE 32
#define ENTER 13
#define X 0
#define Y 1

#define WITDH_SIZE 15
#define HEIGHT_SIZE 15

char turn = 0,
bwin = 0,
wwin = 0;
int check = 0;
int board[WITDH_SIZE + 2][HEIGHT_SIZE + 2] = { 0 };
int cursor[2] = { WITDH_SIZE / 2, HEIGHT_SIZE / 2 };

void draw_board(void);
void wincheck(void);
void move_cursor(void);
void reset_quit(void);
void clear_board(void);

void SetConsole()
{
	system("title FiveStones");
	system("mode con:cols=34 lines=20");

	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

int main(void)
{
	SetConsole();

	while (1)
	{
		if (check == 1) clear_board();
		draw_board();
		wincheck();
		if (bwin > 0 || wwin > 0)
		{
			while (check == 0)
			{
				cursor[X] = 99;
				draw_board();
				if (wwin == 99 && bwin == 99) printf("　　　◎ 승부가 나지 않았습니다.\n\n");

				else if (turn == 1) printf("　　　　　○ 흑의 승리! ○\n\n");
				else printf("　　　　　● 백의 승리! ●\n\n");
				printf("　　　 ◆다시 시작 : r, R◆\n　　　 ◆종료 　　 : q, Q◆\n");

				reset_quit();
				if (check > 0) break;
			}
			clear_board();
			draw_board();
		}
		if (check == 2) break;
		check = 0;

		if (turn == 0) printf("　　　　　○ 흑의 차례 ○\n\n");
		else printf("　　　　　● 백의 차례 ●\n\n");
		printf("　　　 ◆다시 시작 : r, R◆\n　　　 ◆종료 　　 : q, Q◆\n");
		move_cursor();
	}
	return 0;
}

#pragma region 바둑판 그리기, 돌 그리기

void draw_board(void)
{
	int bx, by, i;

	system("cls");
	for (by = 1; by <= HEIGHT_SIZE; by++)
	{
		printf("　");
		for (bx = 1; bx <= WITDH_SIZE; bx++)
		{
			if (cursor[X] == bx && cursor[Y] == by)
			{
				if (by != 1 && by != HEIGHT_SIZE)
				{
					switch (board[by][bx])
					{
					case 0:
						printf("▒");
						break;
					case 1:
						printf("□");
						break;
					case 2:
						printf("■");
						break;
					}
				}
				else if (by == HEIGHT_SIZE) {
					switch (board[by][bx])
					{
					case 0:
						printf("▒");
						break;
					case 1:
						printf("□");
						break;
					case 2:
						printf("■");
						break;
					}
				}
				else {
					switch (board[by][bx])
					{
					case 0:
						printf("▒");
						break;
					case 1:
						printf("□");
						break;
					case 2:
						printf("■");
						break;
					}
				}
			}
			else {
				if (by != 1 && by != HEIGHT_SIZE)
				{
					switch (board[by][bx]) // 오목알 표시
					{
					case 0:
						if (bx == 1) printf("┠");
						else if (bx == WITDH_SIZE)  printf("┨");
						else printf("┼");
						break;
					case 1:
						printf("○");
						break;
					case 2:
						printf("●");
						break;
					}
				}
				else if (by == HEIGHT_SIZE) {
					switch (board[by][bx])
					{
					case 0:
						if (bx == 1) printf("┗");
						else if (bx == WITDH_SIZE)  printf("┛");
						else printf("┷");
						break;
					case 1:
						printf("○");
						break;
					case 2:
						printf("●");
						break;
					}
				}
				else {
					switch (board[by][bx])
					{
					case 0:
						if (bx == 1) printf("┏");
						else if (bx == WITDH_SIZE)  printf("┓");
						else printf("┯");
						break;
					case 1:
						printf("○");
						break;
					case 2:
						printf("●");
						break;
					}
				}
			}
		}
		printf("\n");
	}
}

#pragma endregion

#pragma region 승리 조건

void wincheck(void)
{
	int fullcount = 0;
	int i, j;

	bwin = 0;
	wwin = 0;

	// 무승부(오목판 꽉 참)
	for (j = 1; j < HEIGHT_SIZE + 1; j++) 
	{
		for (i = 1; i < WITDH_SIZE + 1; i++)
		{
			if (board[j][i] != 0) fullcount++;
		}
	}

	if (fullcount == WITDH_SIZE * HEIGHT_SIZE)
	{
		bwin = 99;
		wwin = 99;
	}

	// ㅡ 모양 승리
	for (j = 1; j < HEIGHT_SIZE + 1; j++) 
	{
		for (i = 1; i < WITDH_SIZE - 3; i++)
		{
			if (board[j][i] == 1
				&& board[j][i + 1] == 1
				&& board[j][i + 2] == 1
				&& board[j][i + 3] == 1
				&& board[j][i + 4] == 1

				&& board[j][i - 1] != 1
				&& board[j][i + 5] != 1) bwin = 1;

			else if (board[j][i] == 2
				&& board[j][i + 1] == 2
				&& board[j][i + 2] == 2
				&& board[j][i + 3] == 2
				&& board[j][i + 4] == 2

				&& board[j][i - 1] != 2
				&& board[j][i + 5] != 2) wwin = 1;
		}
	}

	// | 모양 승리
	for (i = 1; i < WITDH_SIZE + 1; i++) 
	{
		for (j = 1; j < HEIGHT_SIZE - 3; j++)
		{
			if (board[j][i] == 1
				&& board[j + 1][i] == 1
				&& board[j + 2][i] == 1
				&& board[j + 3][i] == 1
				&& board[j + 4][i] == 1

				&& board[j - 1][i] != 1
				&& board[j + 5][i] != 1) bwin = 1;

			else if (board[j][i] == 2
				&& board[j + 1][i] == 2
				&& board[j + 2][i] == 2
				&& board[j + 3][i] == 2
				&& board[j + 4][i] == 2

				&& board[j - 1][i] != 2
				&& board[j + 5][i] != 2) wwin = 1;
		}
	}

	// ＼ 모양 승리
	for (j = 1; j < HEIGHT_SIZE - 3; j++)
	{
		for (i = 1; i < WITDH_SIZE - 3; i++)
		{
			if (board[j][i] == 1
				&& board[j + 1][i + 1] == 1
				&& board[j + 2][i + 2] == 1
				&& board[j + 3][i + 3] == 1
				&& board[j + 4][i + 4] == 1

				&& board[j - 1][i - 1] != 1
				&& board[j + 5][i + 5] != 1) bwin = 1;

			else if (board[j][i] == 2
				&& board[j + 1][i + 1] == 2
				&& board[j + 2][i + 2] == 2
				&& board[j + 3][i + 3] == 2
				&& board[j + 4][i + 4] == 2

				&& board[j - 1][i - 1] != 2
				&& board[j + 5][i + 5] != 2) wwin = 1;
		}
	}

	// / 모양 승리
	for (i = 1; i < WITDH_SIZE - 3; i++)
	{
		for (j = 5; j < HEIGHT_SIZE + 1; j++)
		{
			if (board[j][i] == 1
				&& board[j - 1][i + 1] == 1
				&& board[j - 2][i + 2] == 1
				&& board[j - 3][i + 3] == 1
				&& board[j - 4][i + 4] == 1

				&& board[j - 5][i + 5] != 1
				&& board[j + 1][i - 1] != 1) bwin = 1;

			else if (board[j][i] == 2
				&& board[j - 1][i + 1] == 2
				&& board[j - 2][i + 2] == 2
				&& board[j - 3][i + 3] == 2
				&& board[j - 4][i + 4] == 2

				&& board[j - 5][i + 5] != 2
				&& board[j + 1][i - 1] != 2) wwin = 1;
		}
	}
}

#pragma endregion

#pragma region 돌 이동, 돌 놓기

void move_cursor(void)
{
	char key;

	key = _getch();
	switch (key)
	{
	case UP:
		if (cursor[Y] != 1) cursor[Y]--;
		else cursor[Y] = HEIGHT_SIZE;
		break;
	case LEFT:
		if (cursor[X] != 1) cursor[X]--;
		else cursor[X] = WITDH_SIZE;
		break;
	case RIGHT:
		if (cursor[X] != WITDH_SIZE) cursor[X]++;
		else cursor[X] = 1;
		break;
	case DOWN:
		if (cursor[Y] != HEIGHT_SIZE) cursor[Y]++;
		else cursor[Y] = 1;
		break;
	case ENTER:
		if (turn == 0 && board[cursor[Y]][cursor[X]] == 0)
		{
			board[cursor[Y]][cursor[X]] = 1;
			turn = 1;
		}
		else if (turn == 1 && board[cursor[Y]][cursor[X]] == 0)
		{
			board[cursor[Y]][cursor[X]] = 2;
			turn = 0;
		}
		break;
	case SPACE:
		if (turn == 0 && board[cursor[Y]][cursor[X]] == 0)
		{
			board[cursor[Y]][cursor[X]] = 1;
			turn = 1;
		}
		else if (turn == 1 && board[cursor[Y]][cursor[X]] == 0)
		{
			board[cursor[Y]][cursor[X]] = 2;
			turn = 0;
		}
		break;
	case 'r':
		check = 1;
		break;
	case 'R':
		check = 1;
		break;
	case 'q':
		check = 2;
		break;
	case 'Q':
		check = 2;
		break;
	default:
		check = 0;
		break;
	}
}

#pragma endregion

#pragma region 게임 리셋, 종료 버튼

void reset_quit(void)
{
	char key;

	key = _getch();
	switch (key)
	{
	case 'r':
		check = 1;
		break;
	case 'R':
		check = 1;
		break;
	case 'q':
		check = 2;
		break;
	case 'Q':
		check = 2;
		break;
	default:
		check = 0;
		break;
	}
}

#pragma endregion

#pragma region 게임 리셋

void clear_board(void)
{
	int i, j;

	turn = 0;
	wwin = 0;
	bwin = 0;
	cursor[X] = WITDH_SIZE / 2;
	cursor[Y] = HEIGHT_SIZE / 2;
	for (i = 1; i < WITDH_SIZE; i++)
	{
		for (j = 1; j < HEIGHT_SIZE; j++) board[j][i] = 0;
	}
}

#pragma endregion