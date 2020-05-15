
//==================================================================================================================
// Name        : scc.cpp
// Author      : Veinstin Furtado
// Version     :
// Copyright   : Your copyright notice
// Description : Strongly Connected Componenents of a directed graph in C++, Ansi-style
// References	: Tim Roughgarden, "Algorithms Illuminated - Part 2"
//				  Mark Nelon, "https://marknelson.us/posts/2011/09/03/hash-functions-for-c-unordered-containers.html"
//====================================================================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <time.h>
#include <stack>

using namespace std;

int sccsize = 0;
int total_nodes = 0;
unordered_map<int, vector<int>> adjacencyList_global;
unordered_map<int, vector<int>> adjacencyList_forward;
unordered_map<int, vector<int>> adjacencyList_reverse;
unordered_map<int, int> explored;
stack<int> stack_global;
stack<int> stack_forward_dfs;
stack<int> stack_reverse_dfs;

std::list<int> finalResult;

/*
struct Node {
	int nodenumber;
	bool explored;

	Node(int num, bool explr)
	{
		this->nodenumber = num;
		this->explored = explr;
	}

	bool operator==(const Node& n) const
	{
		return this->nodenumber == n.nodenumber;
	}
};

namespace std {
	template <>
	class hash<Node> {
	public:
		size_t operator()(const Node& node) const
		{
			return hash<int>()(node.nodenumber);
		}
	};
};

unordered_map<struct Node, std::vector< struct Node>> adjacencyList;
*/


void dfs_recursive(int node);


int main() {
	for (int i = 1; i <= 5; ++i) finalResult.push_back(0);
	std::list<int>::iterator it;

	int len;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\veins\\OneDrive\\Desktop\\scctestcases\\test30.txt"); //data_set_week5.txt
	int from_node;
	int to_node;
	int last_node = 0;
	int column_number;
	if (myfile.is_open())
	{
		//int node_number = 1;
		while (getline(myfile, line))
		{
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //output the entire line into the string stream
			string temp_str;
			int temp_int;

			column_number = 0;
			from_node;
			while (str_strm >> temp_str) {
				stringstream(temp_str) >> temp_int;
				//Handle orphaned nodes.
				if (column_number == 0) {
					from_node = temp_int; //for the original graph
					to_node = temp_int;	//for the reverse graph
					last_node = from_node > last_node ? from_node: last_node;
				}
				else {
					adjacencyList_forward[from_node].push_back(temp_int);
					adjacencyList_reverse[temp_int].push_back(to_node);
				}

				column_number++;
			}
			cout << endl;
			str_strm.clear();
		}


		//DRIVER CODE
		//Step 1 : Call dfs on reverse graph 
		adjacencyList_global = adjacencyList_reverse;
		for (int i = last_node; i > 0; i--) {
			//If the node is not explored, call dfs on the node
			if (explored[i] == 0) {
				dfs_recursive(i);
			}
		}

		//TEST CODE : PRINT RESULTS FROM THE FIRST DFS
		stack_reverse_dfs = stack_global;
		/*
		while (!stack_global.empty())
		{
			cout << ' ' << stack_global.top();
			stack_global.pop();
		}
		cout << endl;
		*/
		while (!stack_global.empty())
		{
			stack_global.pop();
		}

		adjacencyList_global.clear();
		adjacencyList_global = adjacencyList_forward;
		explored.clear();
		
		//Step 2 : Call dfs on original graph in decreasing order of finsihing times
		int selectednode;
		while (!stack_reverse_dfs.empty())
		{
			selectednode = stack_reverse_dfs.top();
			stack_reverse_dfs.pop();
			if (explored[selectednode] == 0) {
				sccsize = 0;
				//cout << "Leader Node : " << selectednode << endl;
				dfs_recursive(selectednode);
				//cout << "scc size : " << sccsize << endl;
				finalResult.push_back(sccsize);
			}
		}

		while (!stack_global.empty())
		{
			//cout << ' ' << stack_global.top();
			stack_global.pop();
		}


		finalResult.sort(std::greater<int>());
		std::cout << "Final Result : " << endl;
		it = finalResult.begin();
		for (int i = 0; i < 5; i++) {
			std::cout << ' ' << *it;
			++it;
		}
			

		//TEST CODE FOR THE INITIALIZATION STEP
		/*
		cout << "Initialization Test (Forward): " << endl;
		unordered_map<int, std::vector<int>>::iterator it;
		int temp_vector_size;
		for (it = adjacencyList_forward.begin(); it != adjacencyList_forward.end(); it++) {
			cout << "Key Value : " << it->first << endl;
			temp_vector_size = adjacencyList_forward[it->first].size();
			for (int i = 0; i < temp_vector_size; i++) {
				cout << adjacencyList_forward[it->first][i]<< endl;
			}
		}
		cout << "Initialization Test (Reverse): " << endl;
		unordered_map<int, std::vector<int>>::iterator it1;
		int temp_vector_size1;
		for (it1 = adjacencyList_reverse.begin(); it1 != adjacencyList_reverse.end(); it1++) {
			cout << "Key Value : " << it1->first << endl;
			temp_vector_size1 = adjacencyList_reverse[it1->first].size();
			for (int i = 0; i < temp_vector_size1; i++) {
				cout << adjacencyList_reverse[it1->first][i] << endl;
			}
		}
		*/
		
	}
	else {
		cout << "Unable to open file";
	}
}


/*
 * Recursive implementation of the DFS algorithm
 *
 */
void dfs_recursive(int selectednode) {
	if (explored[selectednode] == 0) {
		sccsize++;
		explored[selectednode] = 1;
		int len = adjacencyList_global[selectednode].size();
		//TODO : Handle orphaned nodes
		if(len == 0) {
			stack_global.push(selectednode);
		}
		else {
			//Call dfs on each of the selected node's neighbours
			for (int i = 0; i < len; i++) {
				//if (explored[adjacencyList_global[selectednode][i]] == 0) {
					dfs_recursive(adjacencyList_global[selectednode][i]);
				//}
			}
			stack_global.push(selectednode);
		}
	}
}