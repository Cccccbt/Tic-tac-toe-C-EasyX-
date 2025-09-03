#include <graphics.h>
#include <iostream>
using namespace std;

struct Mouse
{
	int x = 0;
	int y = 0;
};

void drawBoard();
void drawPiece();
void setPiece(Mouse);
void gameCheck();
void messageBox();

bool running = true;
char player = 'o';

char board[3][3];

int main()
{
	Mouse mouse;
	ExMessage msg;
	initgraph(600, 600);
	BeginBatchDraw();

	while (running)
	{
		while (peekmessage(&msg))
		{
			mouse.x = msg.x / 200;
			mouse.y = msg.y / 200;

			if (msg.lbutton)
			{
				setPiece(mouse);
			}
		}


		cleardevice();
		drawBoard();
		drawPiece();
		messageBox();
		FlushBatchDraw();
		gameCheck();
	}

	EndBatchDraw();

	return 0;
}

void drawBoard()
{
	for (int i = 0; i < 2; i++)
	{
		line(200 + 200 * i, 0, 200 + 200 * i, 600);
		line(0, 200 + 200 * i, 600, 200 + 200 * i);
	}
}

void drawPiece()
{
	for (int c = 0; c < 3; c++)
	{
		for (int r = 0; r < 3; r++)
		{
			if (board[r][c] == 'o')
			{
				circle(200 * c + 100, 200 * r + 100, 100);
			}

			else if (board[r][c] == 'x')
			{
				line(200 * c, 200 * r, 200 * c + 200, 200 * r + 200);
				line(200 * c + 200, 200 * r, 200 * c, 200 * r + 200);
			}
		}
	}
}

void setPiece(Mouse m)
{
	if (board[m.y][m.x] == '\0')
	{
		board[m.y][m.x] = player;
		if (player == 'o')
		{
			player = 'x';
		}

		else
		{
			player = 'o';
		}
	}
}

void gameCheck()
{
	bool full = true;
	bool end = false;
	char winner = '\0';

	for (int c = 0; c < 3; c++)
	{
		if (board[0][c] != '\0' && board[0][c] == board[1][c] && board[1][c] == board[2][c])
		{
			cout << "c End.";
			if (player == 'x')
			{
				winner = 'o';
			}

			else
			{
				winner = 'x';
			}

		}
	}

	for (int r = 0; r < 3; r++)
	{
		if (board[r][0] != '\0' && board[r][0] == board[r][1] && board[r][1] == board[r][2])
		{
			cout << "r End.";
			if (player == 'x')
			{
				winner = 'o';
			}

			else
			{
				winner = 'x';
			}

		}
	}

	if (board[1][1] != '\0' && ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[0][2] == board[1][1] && board[1][1] == board[2][0])))
	{
		if (player == 'x')
		{
			winner = 'o';
		}

		else
		{
			winner = 'x';
		}

	}

	for (int c = 0; c < 3 && full; c++)
	{
		for (int r = 0; r < 3 && full; r++)
		{
			if (board[r][c] == '\0')
			{
				full = false;
			}
		}
	}

	if (winner == 'x')
	{
		MessageBox(GetHWnd(), _T("X win."), _T("Game Over"), MB_OK);
		running = false;
	}

	else if (winner == 'o')
	{
		MessageBox(GetHWnd(), _T("O win."), _T("Game Over"), MB_OK);
		running = false;
	}

	else if (full)
	{
		MessageBox(GetHWnd(), _T("Draw."), _T("Game Over"), MB_OK);
		running = false;
	}
}

void messageBox()
{
	settextcolor(RGB(200, 200, 200));
	if (player == 'o')
	{
		outtextxy(20, 20, _T("Now: O"));
	}

	else
	{
		outtextxy(20, 20, _T("Now: X"));
	}
}

