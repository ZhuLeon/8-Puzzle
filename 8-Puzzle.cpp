#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm> //swap, max
#include <math.h> //abs
#include <utility> //pair do i even need this anymore?
#include <tuple> //tuple
#include <chrono> //time

using namespace std;

//custom compare for my priority queue
class compareh
{
public:
	bool operator()(tuple<int, int, vector<vector<int>>> matrix1, tuple<int, int, vector<vector<int>>> matrix2)
	{
		return get<0>(matrix1) + get<1>(matrix1) > get<0>(matrix2) + get<1>(matrix2);
	}
};

void general_search(vector< vector<int> > matrix, int choice_num);
int manhat(vector<vector<int>> node);
int misplace(vector<vector<int>> node);
bool goalcheck(vector< vector<int> > matrix);
void expand(tuple<int, int, vector<vector<int>>> node, priority_queue< tuple<int, int, vector<vector<int>>>, vector<tuple<int, int, vector<vector<int>>>>, compareh > &nodes, int choice_num);

int total;

void general_search(vector< vector<int> > matrix, int choice_num)
{
	int h_n = 0;
	if (choice_num == 1)
	{
		h_n = 0;
	}
	else if (choice_num == 2)
	{
		h_n = misplace(matrix);
	}
	else if (choice_num == 3)
	{
		h_n = manhat(matrix);
	}
	tuple< int, int, vector<vector<int>> > node (h_n, 0, matrix); //creates initial node
	//create queue storing matrix
	priority_queue< tuple<int, int, vector<vector<int>>>, vector<tuple<int, int, vector<vector<int>>>>, compareh > nodes;
	nodes.push(node); //puts node in queue

	//print queue
	cout << "Expanding state" << endl;
	//vector<vector<int>> temp = nodes.top().second;
	tuple<int, int, vector<vector<int>>> temp = nodes.top();
	vector<vector<int>> temp1 = get<2>(temp);
	for (int y = 0; y<3; y++)
	{
		for (int x = 0; x<3; x++)
			cout << temp1[y][x] << " ";
		cout << endl;
	}

	int counter = -1;
	int max_size = 0;
	while (counter != 0 && counter != 1)
	{
		if (nodes.empty())
		{
			cout << "Failure: No solution found" << endl;
			counter = 0;
			return;
		}
		temp = nodes.top();
		get<2>(node) = get<2>(temp);
		nodes.pop();
		if (goalcheck(get<2>(node)) == true)
		{
			cout << "Goal reached" << endl;
			temp1 = get<2>(node);
			for (int y = 0; y<3; y++)
			{
				for (int x = 0; x<3; x++)
					cout << temp1[y][x] << " ";
				cout << endl;
			}
			cout << total << " nodes were expanded." << endl;
			cout << "The maximum number of nodes in the queue at any one time was " << max_size << endl;
			cout << "Depth of goal node was " << get<1>(temp) << endl;
			counter = 1;
			return;
		}
		expand(temp, nodes, choice_num);
		//cout << "size of queue " << nodes.size() << endl;
		int curr_size = nodes.size();
		max_size = max(max_size, curr_size);

		temp = nodes.top();
		temp1 = get<2>(temp);
		cout << "The best state to expand with a g(n) = " << get<1>(temp) << " and h(n) = " << get<0>(temp) << " is..." << endl;
		for (int y = 0; y<3; y++)
		{
			for (int x = 0; x<3; x++)
				cout << temp1[y][x] << " ";
			cout << endl;
		}
	}
}

bool goalcheck(vector< vector<int> > matrix)
{
	vector< vector<int> > goal;
	int num_col = 3;
	int num_row = 3;
	int init_val = 0;
	goal.resize(num_col, vector<int>(num_row, init_val));
	goal[0][0] = 1;
	goal[0][1] = 2;
	goal[0][2] = 3;
	goal[1][0] = 4;
	goal[1][1] = 5;
	goal[1][2] = 6;
	goal[2][0] = 7;
	goal[2][1] = 8;
	goal[2][2] = 0;
	if (matrix == goal)
	{
		//cout << "true" << endl;
		return true;
	}
	else if (matrix != goal)
	{
		//cout << "false" << endl;
		return false;
	}
}

void expand(tuple<int, int, vector<vector<int>>> node, priority_queue< tuple<int, int, vector<vector<int>>>, vector<tuple<int, int, vector<vector<int>>>>, compareh > &nodes, int choice_num)
{
	//find the blank position
	vector<vector<int>> mat = get<2>(node);
	int blank_x = -1;
	int blank_y = -1;
	for (int y = 0; y<3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (mat[y][x] == 0)
			{
				blank_x = x;
				blank_y = y;
			}
		}
	}
	//cout << "pos: " << blank_x << ", " << blank_y << endl;

	//move up
	vector<vector<int>> copy = mat;
	int h_n = 0;
	tuple< int, int, vector<vector<int>> > new_node;
	if (blank_y != 0)
	{
		swap(copy[blank_y][blank_x], copy[blank_y - 1][blank_x]);
		if (choice_num == 1)
		{
			h_n = 0;
		}
		else if (choice_num == 2)
		{
			h_n = misplace(copy);
		}
		else if (choice_num == 3)
		{
			h_n = manhat(copy);
		}
		get<0>(new_node) = h_n;
		get<1>(new_node) = get<1>(node) + 1;
		get<2>(new_node) = copy;
		total++;
		//cout << "move up: " << get<0>(new_node) + get<1>(new_node) << endl;
		nodes.push(new_node); //push children into queue
	}

	//move down
	copy = mat;
	if (blank_y != 2)
	{
		swap(copy[blank_y][blank_x], copy[blank_y + 1][blank_x]);
		if (choice_num == 1)
		{
			h_n = 0;
		}
		else if (choice_num == 2)
		{
			h_n = misplace(copy);
		}
		else if (choice_num == 3)
		{
			h_n = manhat(copy);
		}
		get<0>(new_node) = h_n;
		get<1>(new_node) = get<1>(node) +1;
		get<2>(new_node) = copy;
		total++;
		//cout << "move down: " << get<0>(new_node) + get<1>(new_node) << endl;
		nodes.push(new_node);
	}

	//move right
	copy = mat;
	if (blank_x != 2)
	{
		swap(copy[blank_y][blank_x], copy[blank_y][blank_x + 1]);
		if (choice_num == 1)
		{
			h_n = 0;
		}
		else if (choice_num == 2)
		{
			h_n = misplace(copy);
		}
		else if (choice_num == 3)
		{
			h_n = manhat(copy);
		}
		get<0>(new_node) = h_n;
		get<1>(new_node) = get<1>(node) +1;
		get<2>(new_node) = copy;
		total++;
		//cout << "move right: " << get<0>(new_node) + get<1>(new_node) << endl;
		nodes.push(new_node);
	}
	//move left
	copy = mat;
	if (blank_x != 0)
	{
		swap(copy[blank_y][blank_x], copy[blank_y][blank_x - 1]);
		if (choice_num == 1)
		{
			h_n = 0;
		}
		else if (choice_num == 2)
		{
			h_n = misplace(copy);
		}
		else if (choice_num == 3)
		{
			h_n = manhat(copy);
		}
		get<0>(new_node) = h_n;
		get<1>(new_node) = get<1>(node) +1;
		get<2>(new_node) = copy;
		total++;
		//cout << "move left: " << get<0>(new_node) + get<1>(new_node) << endl;
		nodes.push(new_node);
	}
}

int manhat(vector<vector<int>> node)
{
	int sum = 0;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			int value = node[y][x];
			if (value != 0)
			{
				int goal_x = (value - 1) % 3;
				int goal_y = (value - 1) / 3;
				sum = sum + abs(x - goal_x) + abs(y - goal_y);
			}
		}
	}
	return sum;
}

int misplace(vector<vector<int>> node)
{
	int sum = 0;
	if (node[0][0] != 1)
		sum++;
	if (node[0][1] != 2)
		sum++;
	if (node[0][2] != 3)
		sum++;
	if (node[1][0] != 4)
		sum++;
	if (node[1][1] != 5)
		sum++;
	if (node[1][2] != 6)
		sum++;
	if (node[2][0] != 7)
		sum++;
	if (node[2][1] != 8)
		sum++;
	return sum;
}

int main()
{
	vector< vector<int> > matrix; //creates 2d matrix
	cout << "Enter your puzzle, use a zero to represent the blank " << endl;
	cout << "Enter the first row, use space between numbers ";
	int input1, input2, input3;
	cin >> input1 >> input2 >> input3;
	vector<int> input; //rows
	input.push_back(input1);
	input.push_back(input2);
	input.push_back(input3);
	matrix.push_back(input);//add row to matrix
	input.clear();

	cout << "Enter the second row, use space between numbers ";
	cin >> input1 >> input2 >> input3;
	input.push_back(input1);
	input.push_back(input2);
	input.push_back(input3);
	matrix.push_back(input);//add row to matrix
	input.clear();

	cout << "Enter the third row, use space between numbers ";
	cin >> input1 >> input2 >> input3;
	input.push_back(input1);
	input.push_back(input2);
	input.push_back(input3);
	matrix.push_back(input);//add row to maatrix
	input.clear();

	cout << "Enter your choice of algorithm" << endl;
	cout << "1. Uniform Cost Search" << endl;
	cout << "2. A* with the Misplaced Tile heuristic" << endl;
	cout << "3. A* with the Manhattan distance heuristic" << endl;
	int choice_num = 0;
	cin >> choice_num;

	auto starttime = chrono::steady_clock().now();
	general_search(matrix, choice_num);
	auto endtime = chrono::steady_clock().now();
	auto timetook = endtime - starttime;
	cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(timetook).count() << " ms" << endl;

	system("pause");
	return 0;
}