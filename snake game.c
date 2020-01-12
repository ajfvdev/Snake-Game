#include <stdio.h>
#include <time.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <windows.h> 
#include <conio.h> 
#define V 21
#define H 75
#define N 100

#define V 21
#define H 75
#define N 100

/*
	@author: Alfredo Flores
	@email: alfredojose20001@outlook.es
	
*/

typedef struct
{

	int x, y; // initial position
	int movX, movY;

	char imagen;

} snake;

typedef struct
{

	int x, y;

} fruit;

snake snk[N]; // maximun size
fruit frt;

void begin(int *size, char map[V][H]);
void intro(char map[V][H]);
void intro_data(char map[V][H], int *size);
void loop(char map[V][H], int size);
void input(char map[V][H], int *size, int *dead);
void update(char map[V][H], int size);
void intro_data2(char map[V][H], int size);

void gotoxy(int x, int y); // This function was suggested by a friend to get better performance

void show(char map[V][H]);

int main()
{

	int size;

	char map[V][H];

	begin(&size, map);
	show(map);
	system("pause");
	loop(map, size);

	system("pause");
	return 0;
}

// Initialized in a initial position
void begin(int *size, char map[V][H])
{
	int i;
	// snake head
	snk[0].x = 32;
	snk[0].y = 10; // V
	// snake body
	*size = 4;

	srand(time(NULL));

	frt.x = rand() % (H - 2) + 1; // automatic position of fruit
	frt.y = rand() % (V - 2) + 1;

	for (i = 0; i < *size; i++)
	{

		snk[i].movX = 1;
		snk[i].movY = 0;

	} // snake only move on X

	intro(map);
	intro_data(map, size);
}

// Show everything
void show(char map[V][H])
{

	int i, j;

	for (i = 0; i < V; i++)
	{

		for (j = 0; j < H; j++)
		{

			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

// The camp (map).
void intro(char map[V][H])
{
	int i, j;

	for (i = 0; i < V; i++)
	{

		for (j = 0; j < H; j++)
		{

			if (i == 0 || i == V - 1)
			{

				map[i][j] = '-';
			}
			else if (j == 0 || j == H - 1)
			{

				map[i][j] = '|';
			}
			else
			{
				map[i][j] = ' ';
			}
		}
	}
}

// Introduce every data inIT
void intro_data(char map[V][H], int *size)
{

	int i;

	for (i = 1; i < *size; i++)
	{

		snk[i].x = snk[i - 1].x - 1;
		snk[i].y = snk[i - 1].y;

		snk[i].imagen = 'X'; // body
	}
	snk[0].imagen = 'O'; // head

	// Introduce snake into our camp

	for (i = 0; i < *size; i++)
	{

		map[snk[i].y][snk[i].x] = snk[i].imagen;
	}

	map[frt.y][frt.x] = 'M'; // fruit
}

void loop(char map[V][H], int size)
{

	int dead;

	dead = 0;

	do
	{
		gotoxy(0, 0);

		show(map);
		input(map, &size, &dead);
		update(map, size); // automatic

	} while (dead == 0);
}

void input(char map[V][H], int *size, int *dead)
{
	int i;
	char key;

	// Only two ways to die, collision with map or body, every part of the snake is an diferent structure

	// CHECK GAME CONDITIONS

	if (snk[0].x == 0 || snk[0].x == H - 1 || snk[0].y == 0 || snk[0].y == V - 1)
	{ // 0 es la cabeza de la serpiente, solo evaluaremos cuando la cabeza choque.

		*dead = 1;
	}

	for (i = 1; i < *size && *dead == 0; i++)
	{

		if (snk[0].x == snk[i].x && snk[0].y == snk[i].y)
		{
			*dead = 1;
		}
	}

	// CHECK FRUIT, IF HEAD GET CLOSE, EAT IT!

	if (snk[0].x == frt.x && snk[0].y == frt.y)
	{

		*size += 1;

		snk[*size - 1].imagen = 'X';

		// Regenerated fruit position in a random position

		frt.x = rand() % (H - 2) + 1;
		frt.y = rand() % (V - 2) + 1;
	}

	// IF DEAD IS ZERO WE CAN KEEP GOING

	if (*dead == 0)
	{

		if (kbhit() == 1)
		{

			key = getch();

			if (key == 's' && snk[0].movY != -1)
			{

				snk[0].movX = 0;
				snk[0].movY = 1;
			}

			if (key == 'w' && snk[0].movY != 1)
			{

				snk[0].movX = 0;
				snk[0].movY = -1;
			}

			if (key == 'a' && snk[0].movX != 1)
			{

				snk[0].movX = -1;
				snk[0].movY = 0;
			}

			if (key == 'd' && snk[0].movX != -1)
			{

				snk[0].movX = 1;
				snk[0].movY = 0;
			}
		}
	}
}

void update(char map[V][H], int size)
{

	// Everytime this function is called, the map is overwriting

	intro(map);

	intro_data2(map, size);
}

void intro_data2(char map[V][H], int size)
{

	int i;

	// Body following the head

	for (i = size - 1; i > 0; i--)
	{ // 0 is the head. so we going decresing until extremities

		snk[i].x = snk[i - 1].x;
		snk[i].y = snk[i - 1].y;
	}

	snk[0].x += snk[0].movX; // plus movemenrts
	snk[0].y += snk[0].movY;

	// now introduce the values in the camp

	for (i = 0; i < size; i++)
	{

		map[snk[i].y][snk[i].x] = snk[i].imagen;
	}

	map[frt.y][frt.x] = 'M';
}

void gotoxy(int x, int y)
{ // tbh idk what the hell this function is, originally i used another but this works fine (thought) :)
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
