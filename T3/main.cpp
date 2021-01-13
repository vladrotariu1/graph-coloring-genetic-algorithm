#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <string>
#include "Vertex.h"
#include "DNA.h"
#include "Population.h"

using namespace std;


float fitness(int x) {
	
	float C = 0.01;
	float fitness = 1.0 / (C + float(x));
	return fitness;

}


int main () {


	for (int p_num = 10; p_num <= 10; p_num++) {
		// Initialize file input and random generator

		string file_name = "Testsets/g" + to_string(p_num);
		file_name += ".txt";
		cout << file_name;

		string output_file_name = "Testsets/g" + to_string(p_num);
		output_file_name += "res.txt";

		ifstream fin(file_name);
		ofstream fout(output_file_name);
		srand(time(NULL));


		// Get the number of vertces and the number of edges
		int vertices_number = 0;
		fin >> vertices_number;
		int edges_number = 0;
		fin >> edges_number;


		// Initialize the vector of vertices
		vector<Vertex> graph;
		for (int i = 0; i < vertices_number; i++) {
			graph.push_back(Vertex(i, -1));
		}


		// Add the neighbours in the vector
		for (int i = 0; i < edges_number; i++) {

			int vertex;
			int edge;

			fin >> vertex >> edge;
			graph[vertex - 1].new_neighbour(edge - 1);

		}

		int color_number = vertices_number;
		int population_number = 100;
		float mutation_probability = 0.9;

		Population p = Population(graph, population_number, color_number, mutation_probability, fitness);

		clock_t begin = clock();

		for (int i = 0; i < 1000; i++) {
			cout << i + 1 << " : " << '\n' << "Color number: " << color_number << "\n" << "Top Fitness: " << p.fitness_at_i(p.best_individual_position()) << "\n\n";
			//p.print_generation();
			p.fitness();
			if (p.no_conflicts()) {
				if (color_number == p.best_individual().color_number()) {
					color_number--;
					p = Population(graph, population_number, color_number, mutation_probability, fitness);
					p.fitness();
				}
				else {
					color_number = p.best_individual().color_number();
					//p.print_generation();
					p = Population(graph, population_number, color_number, mutation_probability, fitness);
					p.fitness();
				}
			}
			p.new_generation();
		}

		clock_t end = clock(); 
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		fout << color_number << " ---- " << time_spent << '\n';

	}
	return 0;
}