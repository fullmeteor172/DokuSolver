#include"raylib.h"
#include<iostream>

using namespace std;

static const int APP_SCALE = 2; //Increase if too small on your display

static const int SCREEN_SIZE = APP_SCALE * 180;
static const int UI_BUFFER = SCREEN_SIZE/6;
static const int N = 9;


int gui(int qdoku[N][N], int doku[N][N])
{

	InitWindow(SCREEN_SIZE, SCREEN_SIZE + UI_BUFFER, "Sudoku Game");
	SetTargetFPS(60);
	
	Color empty_color = WHITE;
	Color filled_color = RAYWHITE;
	Color cell_outline = LIGHTGRAY;
	Color big_outline = DARKGRAY;
	Color selected_box_color = RED;
	Color selected_input_color = RED;
	
	int rect_size = SCREEN_SIZE / N;
	int draw_loc_x = NULL;
	int draw_loc_y = NULL;
	int text_shift_x = NULL;
	int text_shift_y = NULL;
	int ch_size = NULL;
	int font_size = SCREEN_SIZE/18;
	
	int mouse_x = NULL;
	int mouse_y = NULL;
	
	int selected_x = NULL;
	int selected_y = NULL;

	int immediate_input = NULL;
	int key_input = NULL;

	int no_mistakes = NULL;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(empty_color);

		//Drawing grid and centering numbers
		for (int i = 0; i < N; i++)
		{
			draw_loc_y = i * rect_size;

			for (int j = 0; j < N; j++)
			{
				draw_loc_x = j * rect_size;
				
				if(qdoku[i][j] == 0)
				{
					DrawRectangle(draw_loc_x, draw_loc_y, rect_size, rect_size, empty_color);
					DrawRectangleLines(draw_loc_x, draw_loc_y, rect_size, rect_size, cell_outline);
				}
				else
				{
					DrawRectangle(draw_loc_x, draw_loc_y, rect_size, rect_size, filled_color);
					DrawRectangleLines(draw_loc_x, draw_loc_y, rect_size, rect_size, cell_outline);
					//Formatting vars
					ch_size = MeasureText(TextFormat("%i", qdoku[i][j]), font_size);
					text_shift_x = (rect_size / 2) - (ch_size / 2);
					text_shift_y = (rect_size / 2) - (font_size / 2);

					DrawText(TextFormat("%i", qdoku[i][j]), draw_loc_x + text_shift_x, draw_loc_y + text_shift_y, font_size, big_outline);
				}
				
			}
		}
		
		//Drawing 3x3 Dark outline		
		for (int i = 0; i < N/3 ; i++)
		{
			draw_loc_y = i * SCREEN_SIZE/3;
			for (int j = 0; j < N / 3; j++)
			{
				draw_loc_x = j * SCREEN_SIZE/3;
				DrawRectangleLines(draw_loc_x, draw_loc_y, SCREEN_SIZE/3, SCREEN_SIZE/3, big_outline);
			}
		}
		
		//Getting mouse input
		int cell = 0; //Fuck knows what this var does but we need it.
		if (IsMouseButtonPressed(cell))
		{
			mouse_x = GetMouseX();
			mouse_y = GetMouseY();
			key_input = NULL;
		}

		// constraintes for the selection box
		selected_x = (mouse_x / rect_size) * rect_size; 
		selected_y = (mouse_y / rect_size) * rect_size;
		
		//If click is in bounds
		if (mouse_y < SCREEN_SIZE && qdoku[mouse_y / rect_size][mouse_x / rect_size] == 0)
		{
			//Drawing a outline around the selected cell
			DrawRectangleLines(selected_x, selected_y, rect_size, rect_size, selected_box_color);
			
			//get input from keyboard
			immediate_input = GetKeyPressed();
			if (immediate_input != 0)
				key_input = immediate_input - 48;
			
			//Checking if the input is valid and making changes if it is
			if (doku[mouse_y / rect_size][mouse_x / rect_size] == key_input)
				qdoku[mouse_y / rect_size][mouse_x / rect_size] = key_input;
			
			else if (immediate_input != 0 && doku[mouse_y / rect_size][mouse_x / rect_size] != key_input)
				no_mistakes++;
			
			if (key_input > 0 && key_input <= 9)
			{
				ch_size = MeasureText(TextFormat("%i", key_input), font_size);
				text_shift_x = (rect_size / 2) - (ch_size / 2);
				text_shift_y = (rect_size / 2) - (font_size / 2);

				DrawText(TextFormat("%i", key_input), selected_x + text_shift_x, selected_y + text_shift_y, font_size, selected_input_color);
			}
		}

		//Timer
		DrawText(TextFormat("Time Elapsed: %d", (int)GetTime()), rect_size/2, SCREEN_SIZE + UI_BUFFER / 2 - font_size / 2, font_size, big_outline);
		
		//Mistakes
		DrawText(TextFormat("%d",no_mistakes), SCREEN_SIZE-rect_size/2- MeasureText(TextFormat("%i", no_mistakes), font_size) , SCREEN_SIZE + UI_BUFFER / 2 - font_size / 2, font_size, selected_input_color);

		EndDrawing();
	}
	CloseWindow();

	return 0;
}

int print(int doku[N][N]) //Prints to console
{
	cout << endl << "=====================" << endl << endl;
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			cout << doku[i][j] << " ";
			if (j == 2 || j == 5)
				cout << "  ";
		}
		cout << endl;
		if (i == 2 || i == 5)
		{
			cout << endl;
		}
	}
	cout << endl << "=====================" << endl << endl;
	return 0;
}

bool empty_finder(int& r, int& c, int doku[9][9])//Looks for empty cells in the grid
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

bool check(int y, int x, int n, int doku[N][N]) // 1 -> The number can be inserted; else 0
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
		return true; //The sudoku is solved!
	}

	for (int num = 1; num <= 9; num++)
	{
		if (check(r, c, num, doku))
		{
			doku[r][c] = num;

			if (solver(doku))
			{
				return true;
			}

			doku[r][c] = 0; //Wrong choice so fallback

		}

	}
	return false;

}

int main()
{
// File parser thing comes here
	int qdoku[N][N] =
	{
		// 0 1 2  3 4 5  6 7 8 <--x
		  {0,0,0, 0,0,0, 0,0,0}, // 0 y
		  {0,0,0, 0,0,0, 0,5,1}, // 1 |
		  {0,0,0, 0,0,0, 0,7,3}, // 2 v
		  {3,9,1, 7,0,0, 0,6,8}, // 3
		  {0,0,0, 0,1,0, 0,4,2}, // 4
		  {4,0,0, 0,8,6, 0,0,0}, // 5
		  {9,4,7, 0,3,0, 0,0,0}, // 6
		  {0,1,6, 0,9,5, 0,3,0}, // 7
		  {8,0,0, 0,6,7, 0,0,9}  // 8
	};
  
  int doku[N][N] =
	{
		// 0 1 2  3 4 5  6 7 8 <--x
		  {0,0,0, 0,0,0, 0,0,0}, // 0 y
		  {0,0,0, 0,0,0, 0,5,1}, // 1 |
		  {0,0,0, 0,0,0, 0,7,3}, // 2 v
		  {3,9,1, 7,0,0, 0,6,8}, // 3
		  {0,0,0, 0,1,0, 0,4,2}, // 4
		  {4,0,0, 0,8,6, 0,0,0}, // 5
		  {9,4,7, 0,3,0, 0,0,0}, // 6
		  {0,1,6, 0,9,5, 0,3,0}, // 7
		  {8,0,0, 0,6,7, 0,0,9}  // 8
	};
	solver(doku);
	//print(doku);
	gui(qdoku,doku);
	return 0;
}
