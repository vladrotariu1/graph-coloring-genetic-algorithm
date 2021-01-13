#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Vertex
{

private:

	int index;
	int color;
	vector<int> neighbours;

public:

	Vertex (int index, int color);
	void new_neighbour (int index);
	void set_color (int color);
	int get_edges_number ();
	int neighbour_at_i (int position);
	void show_neighbours ();
	int get_color ();

};