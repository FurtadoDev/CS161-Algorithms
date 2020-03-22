//============================================================================
// Name        : kargersmincut.cpp
// Author      : Veinstin Furtado
// Version     :
// Copyright   : Your copyright notice
// Description : Karger Min-Cut Problem in C++, Ansi-style
// Reference	: David R. Karger, Clifford R. Stein, "A New Approach to the Min Cut Problem"
//============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <unordered_map>
#include <vector>
#include <time.h>

using namespace std;


int no_of_nodes;
unordered_map<int, int> nodeWeightMap; 
unordered_map<int, unordered_map<int,int>> connected_nodeWeightMapForNodes;
//unordered_map<int, vector<int>> adjacency_vector_map;  Keep this for Testing purposes
vector<int> nodes; //TODO: should be cleared
vector<int> weights_nodes; //TODO: should be cleared
vector<int> cumulative_weights_nodes; //TODO: should be cleared

vector<int> connectedNodes; //TODO: should be cleared
vector<int> weights_connectedNodes; //TODO: should be cleared
vector<int> cumulative_weights_connectedNodes; //TODO: should be cleared

int binarySearch(vector<int> cumulativeWeights, int l, int r, int x);
int random_bin_select(vector<int> cumulativeWeightVector);
pair<vector<int>, vector<int>> getNodesAndWeightsFromMap(unordered_map<int, int> node_weight_map);
vector<int> getCumulativeWeightVectorFromWeightVector(vector<int> weightVector);
vector<int> getCumulativeWeightVectorFromNodeWeightMap(unordered_map<int, int> nodeweightmap);
int main() {
	srand(time(NULL)); //It is important to only invoke the srand call ONCE at the beginning of the program.

	for(int a = 0; a < 150; a++){
		stringstream str_strm;
		string line;
		int len;
		int i = 1; //Node number 1
		ifstream myfile("C:\\Users\\veins\\OneDrive\\Desktop\\data_set_week4.txt"); //data_set_week4
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				//nodes.push_back(i); //initializing the vector which contains all of the nodes
				len = line.length();
				while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
				while (line[0] == ' ') { line.erase(0, 1); } //left trim
				str_strm << line; //output the entire line into the string stream
				string temp_str;
				int temp_int;
				nodeWeightMap[i] = 0;
				while (str_strm >> temp_str) {
					stringstream(temp_str) >> temp_int;
					if (temp_int != i) {
						//adjacency_vector_map[i].push_back(temp_int);  Keep this for Testing Purposes
						nodeWeightMap[i]++;
						connected_nodeWeightMapForNodes[i][temp_int]++; //TODO : Test this out
					}
				}
				str_strm.clear();
				//weights_nodes.push_back(nodeWeightMap[i]);
				i++;
			}

			//cumulative_weights_nodes = getCumulativeWeightVectorFromWeightVector(weights_nodes);
			myfile.close();
		}
		else {
			cout << "Unable to open file";
		}

		no_of_nodes = i - 1;
		//cout << "no of nodes " << no_of_nodes << endl;
		int u_idx;
		int u_nodeid;
		int v_idx;
		int v_nodeid;
		//int nodes_size = nodes.size(); //nodes, weights_nodes & cumulative_weights_nodes have the same size
		int temp_weight;
		int start_idx;
		pair<vector<int>, vector<int>> nodes_weights_temp;
		int tempnode;
		int testsize1, testsize2, testsize3;
	
	
		nodes_weights_temp = getNodesAndWeightsFromMap(nodeWeightMap);
		nodes = nodes_weights_temp.first;
		weights_nodes = nodes_weights_temp.second;
		nodes_weights_temp.first.clear();
		nodes_weights_temp.second.clear();
		cumulative_weights_nodes = getCumulativeWeightVectorFromNodeWeightMap(nodeWeightMap);

		//TEST CODE:
		/*
		cout << "The ajacency list before update -" << endl;
		for (auto& x : connected_nodeWeightMapForNodes) {
			cout << x.first << "  ";
			for (auto& y : connected_nodeWeightMapForNodes[x.first]) {
				cout << y.first << "  ";
			}
			cout << endl;
		}
		cout << endl;
		*/
		while (no_of_nodes > 2) {
			//Step 1 : choose and edge
			u_idx = random_bin_select(cumulative_weights_nodes);
			u_nodeid = nodes[u_idx];
			nodes_weights_temp = getNodesAndWeightsFromMap(connected_nodeWeightMapForNodes[u_nodeid]);
			connectedNodes = nodes_weights_temp.first;
			weights_connectedNodes = nodes_weights_temp.second;
			nodes_weights_temp.first.clear();
			nodes_weights_temp.second.clear();
			cumulative_weights_connectedNodes = getCumulativeWeightVectorFromWeightVector(weights_connectedNodes);
			v_idx = random_bin_select(cumulative_weights_connectedNodes);
			v_nodeid = connectedNodes[v_idx];
			connectedNodes.clear();
			weights_connectedNodes.clear();
			//cout << "The selected Edge is : " << u_nodeid << "   " << v_nodeid << endl; //TEST CODE

			//Step 2: contract the graph
			for (auto& x : connected_nodeWeightMapForNodes[v_nodeid]) {
				//find all the nodes that v is connected to and add them to u along 
				if (x.first != u_nodeid) { //eliminates self loops
					connected_nodeWeightMapForNodes[u_nodeid][x.first] += x.second;
					nodeWeightMap[u_nodeid] += x.second;
					nodeWeightMap[u_nodeid] = nodeWeightMap[u_nodeid] - connected_nodeWeightMapForNodes[u_nodeid][v_nodeid];
					connected_nodeWeightMapForNodes[u_nodeid].erase(v_nodeid);
				
					//update the each of the nodes that v is connected to with the new weight
					nodeWeightMap[x.first] = nodeWeightMap[x.first] - connected_nodeWeightMapForNodes[x.first][v_nodeid];
					connected_nodeWeightMapForNodes[x.first].erase(v_nodeid);

					//if u is getting new nodes, the nodes get u as well
					connected_nodeWeightMapForNodes[x.first][u_nodeid] = connected_nodeWeightMapForNodes[u_nodeid][x.first];
					nodeWeightMap[x.first] = connected_nodeWeightMapForNodes[x.first][u_nodeid];
				}
				else {
					nodeWeightMap[u_nodeid] = nodeWeightMap[u_nodeid] - connected_nodeWeightMapForNodes[u_nodeid][v_nodeid];
					connected_nodeWeightMapForNodes[u_nodeid].erase(v_nodeid);
				}
			}
			//erase v from the adjacency list and the node-weight map
			connected_nodeWeightMapForNodes[v_nodeid].clear();
			connected_nodeWeightMapForNodes.erase(v_nodeid);
			nodeWeightMap.erase(v_nodeid);
			//update cumlative weights for nodes, nodes, weights_nodes
			nodes.clear();
			weights_nodes.clear();
			cumulative_weights_nodes.clear();
			nodes_weights_temp = getNodesAndWeightsFromMap(nodeWeightMap);
			nodes = nodes_weights_temp.first;
			weights_nodes = nodes_weights_temp.second;
			cumulative_weights_nodes = getCumulativeWeightVectorFromNodeWeightMap(nodeWeightMap);
			nodes_weights_temp.first.clear();
			nodes_weights_temp.second.clear();
		
			no_of_nodes--;
			//TODO : try and see if you can generate nodes, weights_nodes, and cumulative_weights_nodes using the same function since both functions take the same map as an input. Saves time.

			//TEST CODE
			/*
			testsize1 = nodes.size();
			testsize2 = weights_nodes.size();
			testsize3 = cumulative_weights_nodes.size();
			cout << "testsize1 : " << testsize1 << endl;
			cout << "testsize2 : " << testsize2 << endl;
			cout << "testsize3 : " << testsize3 << endl;

			if ((testsize1 == testsize2) && (testsize2 == testsize3)) {
				cout << "The size of nodes, weights_nodes and cumulative_weights_nodes are all equal." << endl;
			}
			else {
				cout << "ERROR : The size of nodes, weights_nodes and cumulative_weights_nodes are NOT equal." << endl;
			}
			for (int i = 0; i < nodes.size(); i++) {
				cout << nodes[i] << "   " << weights_nodes[i] << "   " << cumulative_weights_nodes[i] << endl;
			}
			*/
			/*
			cout << "The ajacency list after update -" << endl;
			for (auto& x : connected_nodeWeightMapForNodes) {
				cout << x.first << "  ";
				for (auto& y : connected_nodeWeightMapForNodes[x.first]) {
					cout << y.first << "  ";
				}
				cout << endl;
			}
			cout << endl;
			*/
		}

		for (auto& x : connected_nodeWeightMapForNodes) {
			cout << x.first << "  ";
			for (auto& y : connected_nodeWeightMapForNodes[x.first]) {
				cout << y.second << "  ";
			}
			cout << endl;
		}
		cout << endl << endl;

		nodes.clear();
		weights_nodes.clear();
		cumulative_weights_nodes.clear();
		nodeWeightMap.clear();
		connected_nodeWeightMapForNodes.clear();

	}
	return 0;
}

/*
 * Given a node-weight map, this function returns a vector of cumulative weights
 *
 */
vector<int> getCumulativeWeightVectorFromNodeWeightMap(unordered_map<int, int> nodeweightmap) {
	vector<int> cumulativeWeightVector;
	int sum = 0;
	for(auto& x : nodeweightmap){
		sum = sum + x.second;
		cumulativeWeightVector.push_back(sum);
	}
	return cumulativeWeightVector;
}


/*
 * Given a vector of weights, this function returns a vector of cumulative weights
 *
 */
vector<int> getCumulativeWeightVectorFromWeightVector(vector<int> weightVector) {
	vector<int> cumulativeWeightVector;
	int size_weightVector = weightVector.size();
	int sum = 0;
	for (int i = 0; i < size_weightVector; i++) {
		sum = sum + weightVector[i];
		cumulativeWeightVector.push_back(sum);
	}
	return cumulativeWeightVector;
}

/*
 * Given a map of vertices and weights as key-value pairs, this function returns a pair of vectors
 * for nodes and weights.
 *
 */
pair<vector<int>, vector<int>> getNodesAndWeightsFromMap(unordered_map<int, int> node_weight_map) {
	pair<vector<int>, vector<int>> vectors_nodesAndWeights;
	for (auto& x : node_weight_map) {
		vectors_nodesAndWeights.first.push_back(x.first);
		vectors_nodesAndWeights.second.push_back(x.second);
	}
	return vectors_nodesAndWeights;
}


/*
 * Given a vector of cumulative weights, this function returns an index.
 *
 */
int random_bin_select(vector<int> cumulativeWeightVector) {
	int size = cumulativeWeightVector.size();
	int totalWeight = cumulativeWeightVector[size-1];
	int randomWeight = (rand() % (totalWeight));
	return binarySearch(cumulativeWeightVector, 0, size - 1, randomWeight);
}

/*
 * Returns an index of the selected edge using binary search. The method is based on the paper by Karger and Stein
 *
 */
int binarySearch(vector<int> cumulativeWeights, int l, int r, int x)
{
	if (r-l > 1) {
		int mid = l + ((r - l) / 2);
		if (x < cumulativeWeights[mid])
			return binarySearch(cumulativeWeights, l, mid, x);

		if (x >= cumulativeWeights[mid])
			return binarySearch(cumulativeWeights, mid, r, x);
	}
	else {
		if ((x >= cumulativeWeights[l]) && (x < cumulativeWeights[r]))
			return r;
		else if (x < cumulativeWeights[l])
			return l;
	}
}



