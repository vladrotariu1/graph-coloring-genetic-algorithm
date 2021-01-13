#include "DNA.h"

void DNA::generate_genes()
{
	for (int i = 0; i < size; i++) 
		genes.push_back(random_int(max_color));
}

DNA::DNA(int size, int max_color)
{
	this->size = size;
	this->max_color = max_color;
	generate_genes();
}

DNA::DNA(vector<int> genes, int max_color)
{
	this->genes = genes;
	this->size = genes.size();
	this->max_color = max_color;
}

void DNA::mutate(int position)
{

	int color = genes[position];
	int new_color = random_int(max_color);
	
	while (new_color == color) {
		new_color = random_int(max_color);
	}

	genes[position] = new_color;

}

int DNA::color_number()
{
	
	bool * color_exists = (bool *)malloc(max_color * sizeof(bool));
	int p = 0;

	for (int i = 0; i < max_color; i++) {
		color_exists[i] = false;
	}

	for (int i = 0; i < size; i++) {
		if (color_exists[genes[i]] == false) {
			p++;
			color_exists[genes[i]] = true;
		}
	}

	return p;

}

void DNA::set_fitness(float fitness)
{
	this->fitness = fitness;
}

float DNA::get_fitness()
{
	return fitness;
}

void DNA::set_fitness_probability(float fitness_probability)
{
	this->fitness_probability = fitness_probability;
}

float DNA::get_fitness_probability()
{
	return fitness_probability;
}

vector<int> DNA::get_DNA()
{
	return genes;
}

void DNA::show_DNA()
{
	for (int i = 0; i < size; i++) {
		cout << genes[i] << " ";
	}
	cout << '\n';
}
