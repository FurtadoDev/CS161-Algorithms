#include "Kdtree.h"
#include <algorithm>


Kdtree::Kdtree(vector<pair<size_t, pair<double, double>>> dataset)
{
    this->dataset = dataset;
	size_t dataset_size = this->dataset.size();
	parent_node = (Kdtree::Node*)malloc((dataset_size) * sizeof(Kdtree::Node));
	address_tracker = parent_node;
    buildtree(0, dataset_size-1, parent_node, 0);//base case if size is 0 or 1
    
    visited_vertices.reserve(dataset_size);
}

Kdtree::~Kdtree() {
    visited_vertices.clear();
    free(this->parent_node);
}


Kdtree::Node* Kdtree::buildtree(size_t l_idx, size_t r_idx, Kdtree::Node* root, size_t level) {
    // 1. choose axis

    // 2. sort the data points according to the axis

    // 3. find the median

    // 4. assign root as the median

    // 5. build the left sub tree

    // 6. build the right sub tree
    pair<size_t, pair<double, double>> median;
    size_t median_idx;
    if (l_idx < r_idx) {

        if (level % 2 == 0) {
            sort(dataset.begin() + l_idx, dataset.begin() + r_idx + 1, xcompObj);   //sort according to x-coordinate
            median_idx = l_idx + ((r_idx - l_idx) + 1) / 2;;
            median = dataset[median_idx];
            root->index = median.first;
            root->data_point.first = median.second.first;
            root->data_point.second = median.second.second;
            address_tracker = address_tracker + 1;
            root->left = address_tracker;
            root->left = buildtree(l_idx, median_idx - 1, root->left, level + 1);

            if ((median_idx + 1) <= r_idx) {
                address_tracker = address_tracker + 1;
                root->right = address_tracker;
                root->right = buildtree(median_idx + 1, r_idx, root->right, level + 1);
            }
            else {
                root->right = nullptr;
            }
        }
        else {
            sort(dataset.begin() + l_idx, dataset.begin() + r_idx + 1, ycompObj);   //sort according to y-coordinate
            median_idx = l_idx + ((r_idx - l_idx) + 1) / 2;;
            median = dataset[median_idx];
            root->index = median.first;
            root->data_point.first = median.second.first;
            root->data_point.second = median.second.second;
            address_tracker = address_tracker + 1;
            root->left = address_tracker;
            root->left = buildtree(l_idx, median_idx - 1, root->left, level + 1);

            if ((median_idx + 1) <= r_idx) {
                address_tracker = address_tracker + 1;
                root->right = address_tracker;
                root->right = buildtree(median_idx + 1, r_idx, root->right, level + 1);
            }
            else {
                root->right = nullptr;
            }
        }
    }

    if (l_idx == r_idx) {
        median_idx = l_idx;
        median = dataset[median_idx];
        root->index = median.first;
        root->data_point.first = median.second.first;
        root->data_point.second = median.second.second;
        root->left = nullptr;
        root->right = nullptr;
        if (root->index == 1) first_city = root;
        return root;
    }

    if (root->index == 1) first_city = root;
    return root;
}


Kdtree::Node* Kdtree::getParentNode() {
    return this->parent_node;
}

void Kdtree::recurse(struct Node* input_node, struct Node* parent_node, size_t level) {
    if (level == 0) {
        best_city_current = parent_node;
        best_distance_current = getDist(input_node->data_point, parent_node->data_point);
    }
    pair<struct Node*, double> answer;

    if (parent_node == nullptr) {
        return;
    }
    else {
        double temp_dist = getDist(input_node->data_point, parent_node->data_point);
        pair<double, double> limit;
        double limit_dist;
        unordered_set<size_t>::const_iterator got;

        if (temp_dist < best_distance_current) {
            got = visited_vertices.find(parent_node->index);
            if (got == visited_vertices.end()) { //update the best distance and the best city if the city has not been visisted
                best_distance_current = temp_dist;
                best_city_current = parent_node;
            }
        }

        if (temp_dist == best_distance_current) {
            got = visited_vertices.find(parent_node->index);
            if (got == visited_vertices.end()) { //update the best distance and the best city if the city has not been visisted
                if (parent_node->index < best_city_current->index) { //update only if the index of the new node is lesser than the curren best city index
                    best_distance_current = temp_dist;
                    best_city_current = parent_node;
                }
            }

        }

        if (temp_dist > best_distance_current) {
            got = visited_vertices.find(best_city_current->index);
            if (got != visited_vertices.end()) {
                best_distance_current = temp_dist;
                best_city_current = parent_node;
            }
        }


        if (level % 2 == 0) {//x-axis
            if (input_node->data_point.first <= parent_node->data_point.first) {
                //1. search the good side(left side)
                //2. search the bad side(right side if necessary according to nn algorithm or the current best city has already been visited)
                recurse(input_node, parent_node->left, level + 1);
                limit = make_pair(parent_node->data_point.first, input_node->data_point.second);
                limit_dist = getDist(limit, input_node->data_point);
                got = visited_vertices.find(best_city_current->index);
                if ((got != visited_vertices.end()) || (limit_dist <= best_distance_current)) {//current best city has already been visited or the limit dist is lesser than or equal to the current best dist
                    recurse(input_node, parent_node->right, level + 1);
                }
            }
            else {
                //1. search the good side(right side)
                //2. search the bad side(left side if necessary according to nn algorithm or the current best city has already been visited)
                recurse(input_node, parent_node->right, level + 1);
                limit = make_pair(parent_node->data_point.first, input_node->data_point.second);
                limit_dist = getDist(limit, input_node->data_point);
                got = visited_vertices.find(best_city_current->index);
                if ((got != visited_vertices.end()) || (limit_dist <= best_distance_current)) {//current best city has already been visited or the limit dist is lesser than or equal to the current best dist
                    recurse(input_node, parent_node->left, level + 1);
                }
            }
        }
        else { //y-axis
            if (input_node->data_point.second <= parent_node->data_point.second) {
                //1. search the good side(left side)
                //2. search the bad side(right side if necessary according to nn algorithm or the current best city has already been visited)
                recurse(input_node, parent_node->left, level + 1);
                limit = make_pair(input_node->data_point.first, parent_node->data_point.second);
                limit_dist = getDist(limit, input_node->data_point);
                got = visited_vertices.find(best_city_current->index);
                if ((got != visited_vertices.end()) || (limit_dist <= best_distance_current)) {//current best city has already been visited or the limit dist is lesser than or equal to the current best dist
                    recurse(input_node, parent_node->right, level + 1);
                }
            }
            else {
                //1. search the good side(right side)
                //2. search the bad side(left side if necessary according to nn algorithm or the current best city has already been visited)
                recurse(input_node, parent_node->right, level + 1);
                limit = make_pair(input_node->data_point.first, parent_node->data_point.second);
                limit_dist = getDist(limit, input_node->data_point);
                got = visited_vertices.find(best_city_current->index);
                if ((got != visited_vertices.end()) || (limit_dist <= best_distance_current)) {//current best city has already been visited or the limit dist is lesser than or equal to the current best dist
                    recurse(input_node, parent_node->left, level + 1);
                }
            }
        }
    }
    
}

double Kdtree::getDist(pair<double, double> input_city1, pair<double, double> input_city2) {

    return sqrt(pow(input_city1.first - input_city2.first, 2) + pow(input_city1.second - input_city2.second, 2));

}