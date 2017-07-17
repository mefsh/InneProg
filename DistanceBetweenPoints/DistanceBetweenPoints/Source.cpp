/******************************************/
/*
 * Check distance between each point in array
 * and find the lowest one. Added conflict
 * exception. if there is the same distance 
 * between more than two points, then show
 * them all.
 * 
 * Creator: Bartosz Stasiak
 */
/******************************************/
#include <iostream>
#include <vector>

struct two_points
{
	int x1, y1, x2, y2;

	two_points(int x1=0, int y1=0, int x2=0, int y2=0) //default vaules with initializing
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
	
};

class points_arr
{

	int *tab;	//tab for coords of points
	int t_size;	//t_size/2
	int id;		//just id to easy add new elements to array

public:
	points_arr(int t_size = 0);
	~points_arr();

	void addData(int, int);		//add elements to array
	void lowestDist() const;	//find and show lowest dist between points, and their coordinates
};

int main()
{
	int t_size;
	std::cin >> t_size;		//standard input get array size
	points_arr myarr(t_size);

	int i = 0, x, y;
	while (i++ < t_size)
	{
		std::cin >> x >> y;
		myarr.addData(x, y);
	}

	myarr.lowestDist();
	return 0;
}

points_arr::points_arr(int t_size)
{
	this->id = 0;
	this->t_size = t_size;
	tab = new int[t_size + t_size];
}

points_arr::~points_arr()
{
	delete[] tab;
}

void points_arr::addData(int x, int y)
{
	tab[this->id] = x;
	tab[this->id + 1] = y;
	this->id += 2;
}

void points_arr::lowestDist() const
{
	
	two_points points(tab[0], tab[1], tab[2], tab[3]);
	double min_dist = sqrt(((tab[2] - tab[0])*(tab[2] - tab[0])) + ((tab[3] - tab[1])*(tab[3] - tab[1])));	//we have to add first minimum dist
	std::vector<two_points> minDistPoints;	//vector array with coordinates
	minDistPoints.push_back(points);		//push_back data about coordinates

	for (int i = 0; i < t_size + t_size - 1; i += 2)
	{
		for (int j = 2; j < t_size + t_size - 1; j += 2)
		{
			if (j > i)
			{
				int x1 = tab[i];
				int y1 = tab[i + 1];
				int x2 = tab[j];
				int y2 = tab[j + 1];

				int distX = ((x2 - x1)*(x2 - x1));
				int distY = ((y2 - y1)*(y2 - y1));
				double calcdist = sqrt(distX + distY);

				if (calcdist <= min_dist)
				{
					if (calcdist < min_dist)
						minDistPoints.clear();	//if calculated distance is lower than minimum dist, then clear whole array

					two_points temp_points;
					min_dist = calcdist;
					temp_points.x1 = x1;
					temp_points.y1 = y1;
					temp_points.x2 = x2;
					temp_points.y2 = y2;
					minDistPoints.push_back(temp_points);
				}

			}
		}
	}
		std::cout << "Lowest Distance: " << min_dist << std::endl;
		std::cout << "--------------------" << std::endl;
		std::cout << "Coords: " << std::endl;
		std::cout << "--------------------" << std::endl;

		int i = 0;
		for (auto x : minDistPoints)
		{
			std::cout << "x1: " << x.x1 << " y1: " << x.y1 << std::endl;
			std::cout << "x2: " << x.x2 << " y2: " << x.y2 << std::endl;

			if(i++<(minDistPoints.size()-1))
				std::cout << std::endl;
		}
		std::cout << "--------------------" << std::endl;
}
