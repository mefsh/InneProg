/***********************************/
/*
 * Author: Bartosz Stasiak
 * Description: Program to designate
 * the longest road throught matrix 
 * by choosing the highest value
 * without repetition.
 */
/***********************************/
#include <iostream>

int** createArray(int x_size = 0, int y_size = 0);	//Create an two-dim array
void freeMemory(int**, int);		//deallocate memory
void fillArray(int**, int, int);	//fill array with random numbers
void showArray(int**, int, int);	//show array
int findMaxVal(int**, int**, int, int, int, int);	//find max val by looking left,right,up,down from current one positon
int** createLongestRoad(int**, int, int, int&, int&);	//create the longest road throught matrix
void showLengthOfRoad(int**, const int &, const int &);	//show the lenght of the longest road throught matrix

int main()
{
	int x_size;	//number of rows
	int y_size;	//number of columns

	std::cout << "Please secify matrix size[MxN]" << std::endl;
	std::cout << "M: ";
	std::cin >> x_size;
	std::cout << "N: ";
	std::cin >> y_size;
	std::cout << "-------------------" << std::endl;

	std::cout << "Matrix with random numbers: " << std::endl;
	int** matrix = createArray(x_size, y_size);	//create array
	fillArray(matrix, x_size, y_size);	//fill array
	showArray(matrix, x_size, y_size);	//show array

	int point_x; //starting coord x
	int point_y; //starting coord y

	std::cout << "-------------------" << std::endl;
	std::cout << "Please secify coordinates of starting element [X][Y]" << std::endl;
	std::cout << "X: ";
	std::cin >> point_x;
	std::cout << "Y: ";
	std::cin >> point_y;
	std::cout << "-------------------" << std::endl;

	int** LongestRoadMatrix = createLongestRoad(matrix, x_size, y_size, point_x, point_y);	//Create an array with the longest road
	std::cout << "Road preview: " << std::endl;
	showArray(LongestRoadMatrix, x_size, y_size);	//show an array with the longest road
	std::cout << "-------------------" << std::endl;
	showLengthOfRoad(LongestRoadMatrix, point_x, point_y);	//show the lenght of the longest road


	//deallocate memory
	freeMemory(LongestRoadMatrix, x_size);
	freeMemory(matrix, x_size);
	return 0;
}

int** createArray(int x_size, int y_size)
{
	int** arr = new int *[x_size];
	for (int i = 0; i < x_size; i++)
		arr[i] = new int[y_size];

	for (int i = 0; i < x_size; i++)
		for (int j = 0; j < y_size; j++)
			arr[i][j] = 0;

	return arr;
}

void freeMemory(int** arr, int x_size)
{
	for (int i = 0; i < x_size; i++)
		delete[] arr[i];
	delete[] arr;
}

void fillArray(int** arr, int x_size, int y_size)
{
	for (int i = 0; i < x_size; i++)
		for (int j = 0; j < y_size; j++)
			arr[i][j] = rand() % 51;
}

void showArray(int** arr, int x_size, int y_size)
{
	std::cout.width(7);
	std::cout << std::endl << "";
	for (int j = 0; j < y_size; j++)
	{
		std::cout.width(3);
		std::cout << "[" << j << "]";
	}
	std::cout << std::endl;
	for (int i = 0; i < x_size; i++)
	{
		std::cout.width(5);
		std::cout << "[" << i << "]";
		for (int j = 0; j < y_size; j++)
		{
			std::cout.width(5);
			std::cout << arr[i][j];
		}
		std::cout << std::endl;
	}
}

int findMaxVal(int** arr, int** temp_array, int x_size, int y_size, int x_start, int y_start)
{
	int id = 0;

	int left = x_start - 1;
	int right = x_start + 1;
	int up = y_start - 1;
	int down = y_start + 1;

	int max_val = 0;

	if (left >= 0)
	{
		if (temp_array[left][y_start] == 0)
			if (arr[left][y_start] > max_val)
			{
				max_val = arr[left][y_start];
				id = 1;
			}
	}

	if (right < x_size)
	{
		if (temp_array[right][y_start] == 0)
			if (arr[right][y_start] > max_val)
			{
				max_val = arr[right][y_start];
				id = 2;
			}
	}
	if (up >= 0)
	{
		if (temp_array[x_start][up] == 0)
			if (arr[x_start][up] > max_val)
			{
				max_val = arr[x_start][up];
				id = 3;
			}
	}
	if (down < y_size)
	{
		if (temp_array[x_start][down] == 0)
			if (arr[x_start][down] > max_val)
				id = 4; //don't need to set max_val at last if case
	}

	return id;
}

int** createLongestRoad(int** arr, int x_size, int y_size, int& x_start, int& y_start)
{
	int** temp_array = createArray(x_size, y_size);
	bool no_way = false;
	int increment = 0;

	while (!no_way)
	{
		int id = findMaxVal(arr, temp_array, x_size, y_size, x_start, y_start);

		switch (id)
		{
		case 1: //left
			{
				temp_array[x_start][y_start] = ++increment;
				x_start -= 1;
				break;
			}
		case 2: //right
			{
				temp_array[x_start][y_start] = ++increment;
				x_start += 1;
				break;
			}
		case 3: //up
			{
				temp_array[x_start][y_start] = ++increment;
				y_start -= 1;
				break;
			}
		case 4: //down
			{
				temp_array[x_start][y_start] = ++increment;
				y_start += 1;
				break;
			}
		default: //no_change
			{
				no_way = true;
			}
		}
	}
	temp_array[x_start][y_start] = ++increment;

	return temp_array;
}

void showLengthOfRoad(int** arr, const int &x_start, const int &y_start)
{
	std::cout << "Lenght of the longest road throught matrix: " << arr[x_start][y_start] << std::endl;
}