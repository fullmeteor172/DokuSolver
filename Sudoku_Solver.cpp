#include<iostream>
#include<windows.h>
#include<conio.h>



using namespace std;

#define N 9

int print(int doku[N][N])
{
	cout << endl << "*********************" << endl << endl;
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			cout << doku[i][j] <<" ";
			if (j == 2 || j == 5)
				cout << "  ";
		}
		cout << endl;
		if (i == 2 || i == 5)
		{
			cout << endl;
		}
	}
	cout << endl << "*********************";
	return 0;
}

bool empty_finder(int& r, int& c, int doku[9][9])
{
	for (r = 0; r < 9; r++)
	{
		for (c = 0; c < 9; c++)
		{
			if (doku[r][c] == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool check(int y, int x, int n, int doku[N][N]) // 1 -> The number can be inserted else 0
{

	for (int i = 0; i < N; i++)
	{
		if (n == doku[y][i]) // Column Checker
			return false;

		if (n == doku[i][x]) // Row Checker
			return false;

	}

	//Square checker

	int xrs = 0, xre = 0; //xrs -> x co-ordinate range start || yre -> co - ordinate range end
	int yrs = 0, yre = 0; //yrs -> y co-ordinate range start || yre -> y co - ordinate range end

	if (y >= 0 && y <= 2)
	{
		yrs = 0;
		yre = 2;
	}
	else if (y > 2 && y <= 5)
	{
		yrs = 3;
		yre = 5;
	}
	else if (y > 5 && y <= 8)
	{
		yrs = 6;
		yre = 8;
	}

	if (x >= 0 && x <= 2)
	{
		xrs = 0;
		xre = 2;
	}
	else if (x > 2 && x <= 5)
	{
		xrs = 3;
		xre = 5;
	}
	else if (x > 5 && x <= 8)
	{
		xrs = 6;
		xre = 8;
	}

	for (int j = yrs; j <= yre; j++)//Moving Vertically
	{
		for (int k = xrs; k <= xre; k++)//Move Horizontally to check
		{
			if (doku[j][k] == n) //Checking if the number exists
			{

				return false;
			}
		}
	}

	return true; //If it gets this far it can be inserted
}

bool solver(int doku[N][N])
{
	int r, c;
	
	if (empty_finder(r, c, doku) == false)
	{
		return true;
	}

	for (int num = 1; num <= 9; num++)
	{
		if (check(r, c, num, doku))
		{
			doku[r][c] = num;
			//print(doku);
			//Sleep(15);
			//system("CLS");
			if (solver(doku))
			{
				return true;
			}

			doku[r][c] = 0;

		}

	}
	return false;

}

int main()
{

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	system("color 0A");
	//_getch();
	/*int doku[N][N] =     { { 2, 9, 7, 6, 1, 4, 8, 5, 3 },
						   { 0, 0, 0, 8, 0, 0, 0, 0, 4 },
						   { 0, 0, 8, 2, 0, 3, 0, 6, 9 },
						   { 5, 7, 4, 0, 0, 2, 0, 0, 0 },
						   { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						   { 0, 0, 0, 9, 0, 0, 6, 3, 7 },
						   { 9, 4, 0, 1, 0, 8, 5, 0, 0 },
						   { 7, 0, 0, 0, 0, 6, 0, 0, 0 },
						   { 6, 8, 2, 0, 0, 0, 0, 9, 0 } };*/

						   int doku[N][N] =     { { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
												  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
												  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
												  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
												  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
												  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
												  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
												  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
												  { 0, 0, 0, 0, 0, 0, 0, 0, 0 } };



	solver(doku);
	print(doku);
	//_getch();
	return 0;
}