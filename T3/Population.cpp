
#include "Population.h"


float Population::fitness_at_i(int position)
{
	color_graph(population[position].get_DNA());

	int conflict_edges = 0;

	for (int i = 0; i < vertex_number; i++) {
		Vertex current_vertex = graph[i];
		for (int j = 0; j < current_vertex.get_edges_number(); j++) {
			Vertex neighbour = graph[current_vertex.neighbour_at_i(j)];
			if (current_vertex.get_color() == neighbour.get_color()) {
				conflict_edges++;
			}
		}
	}

	float f = fitness_function(conflict_edges);

	return f;
}

float Population::total_fitness()
{
	float tf = 0;
	for (int i = 0; i < population_size; i++) {
		tf += population[i].get_fitness();
	}

	return tf;
}

void Population::color_graph(vector<int> color_scheme)
{
	for (int i = 0; i < vertex_number; i++) {
		graph[i].set_color(color_scheme[i]);
	}
}

vector<float> Population::fitness_probability()
{
	vector<float> fitness_probability;
	float tfitness = total_fitness();

	fitness_probability.push_back(float(fitness_at_i(0)) / float(tfitness));
	for (int i = 1; i < population_size; i++) {
		float probability = fitness_at_i(i) / tfitness;
		fitness_probability.push_back(probability + fitness_probability[i - 1]);
	}

	return fitness_probability;
}

int Population::probabilistic_position_select(vector<float> probabilities)
{
	int position = 0;
	float probability = random_uniform();

	for (int i = 0; i < probabilities.size(); i++) {
		if (probability <= probabilities[i]) return i;
	}

	return 0;
}

vector<DNA> Population::wheel_of_fortune()
{
	vector<float> fp = fitness_probability();
	float probability = random_uniform();

	vector<DNA> parents;

	for (int i = 0; i < population_size; i++) {

		int position = probabilistic_position_select(fp);
		//cout << position << " ";
		parents.push_back(population[position]);

	}

	vector<DNA> new_generation;
	new_generation.push_back(best_individual());
	for (int i = 1; i < population_size; i++) {

		int parent1_index = 0;
		int parent2_index = 0;

		while (parents[parent1_index].get_DNA() == parents[parent2_index].get_DNA()) {
			parent1_index = random_int(population_size);
			parent2_index = random_int(population_size);
		}

		DNA child = parents[parent1_index];
		if (random_uniform() <= 0.2) {
			child = crossover(parents[parent1_index], parents[parent2_index]);
		}
		if (random_uniform() <= mutation_probability) {
			child.mutate(random_int(vertex_number));
		}

		new_generation.push_back(child);
	}

	return new_generation;
}

DNA Population::crossover(DNA d1, DNA d2)
{
	vector<int> DNA1 = d1.get_DNA();
	vector<int> DNA2 = d2.get_DNA();
	vector<int> cross_over_DNA;

	int crossover_position = random_int(vertex_number);

	for (int i = 0; i < crossover_position; i++) {
		cross_over_DNA.push_back(DNA1[i]);
	}

	for (int i = crossover_position; i < vertex_number; i++) {
		cross_over_DNA.push_back(DNA2[i]);
	}

	return DNA(cross_over_DNA, max_color);
}

Population::Population(vector<Vertex> graph, int population_size, int max_color, float mutation_probability, float(*fitness_function)(int))
{
	this->graph = graph;
	this->population_size = population_size;
	this->max_color = max_color;
	this->fitness_function = fitness_function;
	this->mutation_probability = mutation_probability;
	this->vertex_number = graph.size();

	for (int i = 0; i < population_size; i++) {
		population.push_back(DNA(vertex_number, max_color));
	}
}

void Population::fitness()
{
	for (int i = 0; i < population_size; i++) {
		population[i].set_fitness(fitness_at_i(i));
	}
}

void Population::new_generation()
{
	population = wheel_of_fortune();
}

DNA Population::best_individual()
{
	DNA best = population[0];
	float best_fitness = best.get_fitness();

	for (DNA d : population) {
		
		float current_fitness = d.get_fitness();
		if (current_fitness > best_fitness) {
			best = d;
			best_fitness = current_fitness;
		}

	}

	return best;
}

int Population::best_individual_position()
{
	int best_position = 0;
	float best_fitness = population[0].get_fitness();

	for (int i = 0; i < population_size; i++) {

		float current_fitness = population[i].get_fitness();
		if (current_fitness > best_fitness) {
			best_position = i;
			best_fitness = current_fitness;
		}

	}

	return best_position;
}

bool Population::no_conflicts()
{
	return fitness_at_i(best_individual_position()) == fitness_function(0) ? true : false;
}

void Population::print_generation()
{
	for (int i = 0; i < population_size; i++) {
		population[i].show_DNA();
		cout << '\n';
	}
}
