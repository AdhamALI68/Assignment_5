/*
------------------------------------------------------------------
*
* Author: Adham Ahmed Ali
* ID: 900223243
* Assignment: CSCE 2211 / assignment 5
* Due Date: 26/11/2023
* Description: main.cpp
*
------------------------------------------------------------------
*/

// Here are the libraries we used
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Node.h"
using namespace std;

// Function to find the maximum subsequence sum
double maximum_subsequence_sum(vector<double>& differences, int& start, int& end) {
    double maximum_sum = 0;
    double current_sum = 0;
    start = 0;

    for (int i = 0; i < differences.size(); ++i) {
        // Incrementally calculate the sum of the subsequence
        current_sum += differences[i];

        // If the current sum becomes negative, reset and update the start index
        if (current_sum < 0) {
            current_sum = 0;
            start = i + 1;
        }

        // Update the end index when a new maximum sum is found
        if (current_sum > maximum_sum) {
            maximum_sum = current_sum;
            end = i;
        }
    }

    return maximum_sum;
}

// Function to heapify the max heap
void heapify_max(vector<Node>& heap_array, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Find the largest element among the root, left child, and right child
    if (left < n && heap_array[left].data > heap_array[largest].data) {
        largest = left;
    }

    if (right < n && heap_array[right].data > heap_array[largest].data) {
        largest = right;
    }

    // Swap the largest element with the root if needed, then recursively heapify the affected subtree
    if (largest != i) {
        swap(heap_array[i], heap_array[largest]);
        heapify_max(heap_array, n, largest);
    }
}

// Function to build the max heap
void build_max_heap(vector<Node>& heap_array) {
    int n = heap_array.size();

    // Start from the last non-leaf node and perform heapify operation on each node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_max(heap_array, n, i);
    }
}

// Function to heapify the min heap
void heapify_min(vector<Node>& heap_array, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Find the smallest element among the root, left child, and right child
    if (left < n && heap_array[left].data < heap_array[smallest].data) {
        smallest = left;
    }

    if (right < n && heap_array[right].data < heap_array[smallest].data) {
        smallest = right;
    }

    // Swap the smallest element with the root if needed, then recursively heapify the affected subtree
    if (smallest != i) {
        swap(heap_array[i], heap_array[smallest]);
        heapify_min(heap_array, n, smallest);
    }
}

// Function to build the min heap
void build_min_heap(vector<Node>& heap_array) {
    int n = heap_array.size();

    // Start from the last non-leaf node and perform heapify operation on each node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_min(heap_array, n, i);
    }
}

// Function to remove the root of the heap (max or min)
Node remove(vector<Node>& heap_array, int p) {
    Node T;
    if (p == 1) {
        // Remove the root for max heap, then rebuild the max heap
        T = heap_array[0];
        heap_array.erase(heap_array.begin());
        build_max_heap(heap_array);
    } else if (p == 2) {
        // Remove the root for min heap, then rebuild the min heap
        T = heap_array[0];
        heap_array.erase(heap_array.begin());
        build_min_heap(heap_array);
    }
    return T;
}

// Function to tokenize a string into words
vector<string> tokens(string x) {
    vector<string> word;
    string w = "";
    x += ' ';

    for (int i = 0; i < x.length(); i++) {
        // Separate the string into words based on spaces or tabs
        if (((x[i] != ' ') && (x[i] != '\t'))) {
            w += x[i];
        } else {
            if (!(w == "")) {
                word.push_back(w);
                w = "";
            }
        }
    }
    return word;
}

int main() {
    ifstream in;
    string x;
    // Open the input file
    in.open("Input_data.txt");
    vector<string> z;
    vector<vector<string>> vector_tokens;
    vector<Node> vector_of_nodes;
    vector<Node> vector_of_nodes_2;
    vector<Node> vector_of_dates;

    if (in.fail()) {
        // Print an error message if the file opening fails
        cout << "Error" << endl;
    } else {
        // Read input data from the file
        while (getline(in, x)) {
            // Skip lines starting with 'd', to skip the first line in the file
            if (x[0] == 'd') {
                continue;
            }
            // Tokenize the string and convert it into a Node
            z = tokens(x);
            vector_tokens.push_back(z);
            Node G;
            G.key = z[0];
            // Remove the last character (newline) and convert to double
            string f = z[1].erase(z[1].length() - 1);
            G.data = stod(z[1]);

            // Store Nodes in two vectors
            vector_of_nodes.push_back(G);
            vector_of_nodes_2.push_back(G);
        }
    }
    // Copy vector_of_nodes to vector_of_dates for using it to get the start and end periods of the maximum subseuence sum
    vector_of_dates = vector_of_nodes;

    // Build max heap using the data values
    build_max_heap(vector_of_nodes);

    // Display the top 10 maximum values
    cout << "HERE ARE THE MAXIMUM VALUES" << endl;
    for (int i = 0; i < 10; i++) {
        Node retrieve;
        retrieve = remove(vector_of_nodes, 1);
        cout << i + 1 << ") Date: " << retrieve.key << "    Value: " << retrieve.data << endl;
    }

    // Build min heap using the data values
    build_min_heap(vector_of_nodes_2);
    cout << endl
         << endl;
    // Display the top 10 minimum values
    cout << "HERE ARE THE MINIMUM VALUES" << endl;
    for (int i = 0; i < 10; i++) {
        Node retrieve;
        retrieve = remove(vector_of_nodes_2, 2);
        cout << i + 1 << ") Date: " << retrieve.key << "    Value: " << retrieve.data << endl;
    }

    // Calculate differences between consecutive data values
    vector<double> diff;
    for (int i = 0; i < vector_of_dates.size() - 1; i++) {
        double differences = vector_of_dates[i + 1].data - vector_of_dates[i].data;
        diff.push_back(differences);
    }

    int start, end;

    // Find the maximum subsequence sum and its indices
    double k = maximum_subsequence_sum(diff, start, end);
    cout << endl
         << endl;
    // Display the contiguous period with maximum subsequence sum
    cout << "This is the contiguous period and it starts from " << vector_of_dates[start].key << " and ends at " << vector_of_dates[end + 1].key << endl;
    cout << "The maximum subsequence sum will be equal to = " << k << endl;

    return 0;
}
