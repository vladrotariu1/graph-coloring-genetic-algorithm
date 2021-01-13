#pragma once
#include "Vertex.h"
#include "DNA.h"

class Population
{

private:
	int max_color;
	int population_size;
	float (*fitness_function)(int);
	float mutation_probability;
	int vertex_number;

	vector<Vertex> graph;
	vector<DNA> population;

	float total_fitness ();
	void color_graph (vector<int> color_scheme);
	vector<float> fitness_probability();
	int probabilistic_position_select(vector<float> probabilities);
	vector<DNA> wheel_of_fortune ();
	DNA crossover (DNA d1, DNA d2);

public:
	Population (vector<Vertex> graph, int population_size, int max_color, float mutation_probability, float (*fitness_function)(int));
	void fitness ();
	float fitness_at_i(int position);
	void new_generation ();
	DNA best_individual ();
	int best_individual_position ();
	bool no_conflicts ();
	void print_generation ();

};
