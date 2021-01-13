#pragma once
#include <iostream>
#include "Randomgen.h"
#include "Vertex.h"


class DNA
{

private:
	int size;
	float fitness;
	float fitness_probability;
	int max_color;
	vector<int> genes;
	void generate_genes ();

public:
	DNA (int size, int max_color);
	DNA (vector<int> genes, int max_color);
	void mutate (int position);
	int color_number ();
	void set_fitness (float fitness);
	float get_fitness ();
	void set_fitness_probability (float fitness_probability);
	float get_fitness_probability ();
	vector<int> get_DNA();
	void show_DNA();

};

