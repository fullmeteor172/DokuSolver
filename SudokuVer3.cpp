/*
 _____ _   _______ _____ _   ___   _   _____  _____ _     _   _ ___________
/  ___| | | |  _  \  _  | | / / | | | /  ___||  _  | |   | | | |  ___| ___ \
\ `--.| | | | | | | | | | |/ /| | | | \ `--. | | | | |   | | | | |__ | |_/ /
 `--. \ | | | | | | | | |    \| | | |  `--. \| | | | |   | | | |  __||    /
/\__/ / |_| | |/ /\ \_/ / |\  \ |_| | /\__/ /\ \_/ / |___\ \_/ / |___| |\ \
\____/ \___/|___/  \___/\_| \_/\___/  \____/  \___/\_____/\___/\____/\_| \_|

By Dhruv Jha
If somethings broken let me know at u/fullmeteor172  ^.^
*/



#include<iostream>
using namespace std;

// ENTER THE SUDOKU VALUES HERE :-

int doku[9][9] =
{
  // 0 1 2  3 4 5  6 7 8 <--x
	{0,3,0, 0,0,0, 9,0,6}, // 0 y
	{6,0,2, 9,4,3, 8,5,1}, // 1 |
	{0,0,0, 0,0,0, 0,7,3}, // 2 v
	{3,9,1, 7,0,0, 0,6,8}, // 3
	{0,0,0, 0,1,0, 0,4,2}, // 4
	{4,0,0, 0,8,6, 0,0,0}, // 5
	{9,4,7, 0,3,0, 0,0,0}, // 6
	{0,1,6, 0,9,5, 0,3,0}, // 7
	{8,0,0, 0,6,7, 0,0,9}  // 8
};

int x=0, y=0; // Global position in the Sudoku

int solved = 0; //Number of non-empty cells, when = 81, the answer will be printed

int main()
{
	//Step 1: Finding an empty cell in the puzzle
	
	for (y = 0; y <= 8; y++) //Moving Across Vertically
	{
		for (x = 0; x <= 8; x++)// Moving Horizontally
		{
			if (doku[y][x] == 0) //Empty Cell Check
			{
				//Step 2: Checking for all the missing elements from the 3x3 of that empty cell
				
				//1) Finding which 3x3 this empty cell belongs too
				
				int xrs, xre; //xrs -> x co-ordinate range start || yre -> co - ordinate range end
				int yrs, yre; //yrs -> y co-ordinate range start || yre -> y co - ordinate range end
				
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

				//2) Finding missing elements from that 3x3
				
				int sqelements[10]; // Contains missing 3x3 numbers
				
				for (int ini = 0; ini <= 8; ini++)
					sqelements[ini] = 0; //Initializing with all 0'
				
				/*
					How this missing square element finder works:-
					-First a sample number is taken, starting from 1
					-This number is checked with every element in the square
					-If it doesn't match the flag value increases by 1
					-If the sample number gets 9 flags it means it doesn't exist in the square
					-This number is added to the array containing square missing numbers
					-If it does not get 9 strikes the number exists and sample number is inc by 1
					-This is repeated till all the numbers 1...9 are tried
				*/

				for (int sample = 1; sample <= 9; sample++)//Getting a checker number to see if it exists in 3x3
				{
					int flag = 0; // Flag is initialized with 0 strikes
					
					for (int j = yrs; j <= yre; j++)//Moving Vertically
					{
						for (int k = xrs; k <= xre; k++)//Move Horizontally to check
						{
							if (doku[j][k] != sample) //Checking if the number exists
							{
								flag++;
							}
						}
					}
					
					if (flag == 9) // When the flag is equal to 9 that means the number doesn't exist in the Square
					{
						sqelements[sample-1] = sample;
					}
					else
					{
						sqelements[sample-1] = 0;
					}
				}
				
				//Step 2: Checking for all the missing elements in the column of that empty cell
				
				int colelements[10]; //Will contains all the missing elements from Column
				
				for (int ini = 0; ini <= 8; ini++)
					colelements[ini] = 0; //Initializing with all 0's

				/*
					How this missing column element finder works:-
					-First a sample number is taken, starting from 1
					-This number is then checked with every element in the column
					-If the sample and the column element don't match, flag increases by 1
					-If the flag gets 9 strikes, the elment doesn't exist in the column
					-This number is then added to the array of missing column numbers
					-If this doesn't get 9 strikes, the sample number in increased by 1
					-This is repeated till numbers 1...9 are tried
				*/

				for (int sample = 1; sample <= 9; sample++)//Getting a checker number to see if it exists in the Column
				{
					int flag = 0; // Flag is initialized with 0 strikes
					
					for (int k = 0; k <= 8; k++)//Move Vertically to check
					{
						if (doku[k][x] != sample) //Checking if the number exists
						{
							flag++;
						}
						
						if (flag == 9) // When the flag is equal to 9 that means the number doesn't exist in the Column
						{
							colelements[sample-1] = sample;
						}
						else
						{
							colelements[sample-1] = 0;
						}
					}
				}


				//Step 3: Checking for all missing elements in the row of that empty cell
				
				int rowelements[10]; //Will contain missing elements from the row
				
				for (int ini = 0; ini <= 8; ini++)
					rowelements[ini] = 0; //Initializing with all 0's
						
		        /*
					How this missing row element finder works:-
					-First a sample number is taken, starting from 1
					-This number is then checked with every element in the row
					-If the sample and the row element don't match, flag increases by 1
					-If the flag gets 9 strikes, the elment doesn't exist in the row
					-This number is then added to the array of missing row numbers
					-If this doesn't get 9 strikes, the sample number in increased by 1
					-This is repeated till numbers 1...9 are tried
				*/

				for (int sample = 1; sample <= 9; sample++)//Getting a checker number to see if it exists in the Row
				{
					int flag = 0; // Flag is initialized with 0 strikes
					
					for (int k = 0; k <= 8; k++)//Move Horizontally to check
					{
						if (doku[y][k] != sample) //Checking if the number exists
						{
							flag++;
						}
						
						if (flag == 9) // When the flag is equal to 9 that means the number doesn't exist in the Row
						{
							rowelements[sample-1] = sample;
						}
						else
						{
							rowelements[sample-1] = 0;
						}
					}
				}
				
				/*	Row, Column, 3x3 missing finder print for debugging:-
					cout << endl;
					for (int i = 0; i <= 8; i++)
					{
						cout << rowelements[i];
					}
					cout << endl;
					for (int i = 0; i <= 8; i++)
					{
						cout << colelements[i];
					}
					cout << endl;
					for (int i = 0; i <= 8; i++)
					{
						cout << sqelements[i];
					}
					cout << endl;
					cout << endl;
				*/

				//Step 4: Finding the overlaps and substituting them in the Sudoku
				
				int tempans=0; //To store the answer if an overlap is found
				int ansflag = 0;
				for (int i = 0; i <= 8; i++)
				{
					if (rowelements[i] == colelements[i] && colelements[i] == sqelements[i] && rowelements[i]!=0)
					{
						tempans = rowelements[i];
						ansflag++;
						//cout << tempans << " " << ansflag << " " << x << " " << y <<endl;
					}
				}
				if (ansflag == 1) //If flag=1 that means only that number overlaps and it's the answer to that cell
					doku[y][x] = tempans;
				
			}
		}
	}
	
	//Step 5: Checking to see if there are still empty cells left
	for (int i = 0; i <= 8; i++) //Moving Across Vertically
	{
		for (int j = 0; j <= 8; j++)// Moving Horizontally
		{
			if (doku[i][j] == 0) //Empty Cell Check
			{
				main();
			}
			else
				solved++;
		}
	}
	
	//Step 6: Printing the solved sudoku:
	if (solved == 81)
	{
		cout << endl << "***DONE!***" << endl << endl;
		for (int i = 0; i <= 8; i++)
		{
			for (int j = 0; j <= 8; j++)
			{
				cout << doku[i][j];
				if (j == 2 || j == 5)
					cout << " ";
			}
			cout << endl;
			if (i == 2 || i == 5)
			{
				cout << endl;
			}
		}
		cout << endl << "***********";
	}
	return 0;
}