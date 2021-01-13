#include "Vertex.h"

Vertex::Vertex(int index, int color)
{
	this->index = index;
	this->color = color;
}

void Vertex::new_neighbour(int index)
{
	neighbours.push_back(index);
}

void Vertex::set_color(int color)
{
	this->color = color;
}

int Vertex::get_edges_number()
{
	return neighbours.size();
}

int Vertex::neighbour_at_i(int position)
{
	return neighbours[position];
}

void Vertex::show_neighbours()
{
	cout << index << ": ";
	for (int neighbour : neighbours) {
		cout << neighbour << " ";
	}
	cout << "\n";
}

int Vertex::get_color()
{
	return color;
}
