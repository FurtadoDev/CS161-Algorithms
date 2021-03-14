#pragma once

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Kdtree
{

public:
	struct xAxisComparator {
		bool operator() (pair<size_t, pair<double, double>> i, pair<size_t, pair<double, double>> j) { return (i.second.first < j.second.first); }
	} xcompObj;

	struct yAxisComparator {
		bool operator() (pair<size_t, pair<double, double>> i, pair<size_t, pair<double, double>> j) { return (i.second.second < j.second.second); }
	} ycompObj;

	struct Node {
		size_t index;
		pair<double, double> data_point;
		struct Node* left;
		struct Node* right;
	};

	struct Node* address_tracker;
	struct Node* parent_node;
	vector<pair<size_t, pair<double, double>>> dataset;
	
	/*For the NN search algorithm*/
	struct Node* first_city;
	unordered_set<size_t> visited_vertices;
	struct Node* best_city_current;
	double best_distance_current;
	pair<double, double> input_city;

	/**
	 * Constructor
	 *
	 */
	Kdtree(vector<pair<size_t, pair<double, double>>> dataset);

	/**
	 * Destructor
	 *
	 */
	~Kdtree();

	/**
	 * Build a Kd-Tree
	 *
	 * @returns void
	 */
	struct Node* buildtree(size_t l_idx, size_t r_idx, struct Node* root, size_t level);


	/**
	 * Get tree
	 *
	 * @returns parent node of the kd-tree
	 */
	struct Node* getParentNode();

	/**
	 * Given an input_node, find the closest city node(that is not visisted) and the correspoding distance(Global variables: best_city_current and best_distance_current)
	 *
	 * @returns void
	 */
	void recurse(struct Node* input_node, struct Node* parent_node, size_t level);


	/**
	 * Given two data points, find Euclidean distance between them
	 *
	 * @returns double
	 */
	double getDist(pair<double, double> input_city1, pair<double, double> input_city2);
};
