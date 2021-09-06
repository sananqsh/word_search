// Word search program!
//Algorithm: unless the size of words in the dict is much much more than the size of the grid, it`s logical to search for each word in the dict, and NOT vice versa...

#include <iostream>
#include <cctype>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> dict;
int grid_size;
vector<vector<char> > grid;
vector<vector<int> > answer_board;

const int POSSIBLE_MOVES = 8;
int ROW_DELTA[POSSIBLE_MOVES] = {0, -1, -1, -1, 0, 1, 1, 1};
int COL_DELTA[POSSIBLE_MOVES] = {-1, -1, 0, 1, 1, 1, 0, -1};

void build_dict(string fileAddress);
void lower_case_dict();
void build_answer_board();
void build_grid(string fileAddress);
void print_answer_board();	//for debugging

bool find_word(string target);
bool find_letter(string target, int move_no, int init_row, int init_col);
vector<vector<int> > find_initial(string w); // searches for the first letter

int main(int argc, char const *argv[])
{
	// Handle input errors:
	if (argc != 3)
	{
		cout << "Usage: ./a.out	dictionary_file grid_file\n";
		return 1;
	}

	// Take a dictionary and a grid, then convert them to vectors
	build_dict(argv[1]);
	build_grid(argv[2]);

	// Canonacalizing all data:
	lower_case_dict();

	vector<string> answer;
	// Iterating through dictionary and performing the search process for each word; if matched, add word to answer
	for (int i = 0; i < dict.size(); ++i)
	{
		build_answer_board();
		if (find_word(dict[i]))
			answer.push_back(dict[i]);

		// Uncomment for debugging:
		// print_answer_board()		
	}

	// We want to print the found words in alphabetic order;
	sort(answer.begin(), answer.end());

	for (int i = 0; i < answer.size(); ++i)
	{
		cout << answer[i];
		if (i < answer.size() - 1)
			cout << ',';
	}
	cout << endl;
}

bool find_word(string target)
{
	vector<vector<int> > initial_coordinates = find_initial(target);
	for (int i = 0; i < initial_coordinates.size(); ++i)
	{
		int init_row = initial_coordinates[i][0];
		int init_col = initial_coordinates[i][1];
		if (find_letter(target, 1, init_row, init_col))
			return true;
		answer_board[init_row][init_col] = 0;
	}
	return false;
}

bool find_letter(string target, int move_no, int init_row, int init_col)
{
	answer_board[init_row][init_col] = move_no;
	if (move_no == target.size())
		return true;
	for (int move = 0; move < POSSIBLE_MOVES; ++move)
	{
		int new_row = init_row + ROW_DELTA[move];
		int new_col = init_col + COL_DELTA[move];

		// Handling possible missteps
		// Out of bounds
		if (new_row < 0 || new_col < 0 || new_row >= grid_size || new_col >= grid_size)
			continue;
		// Already stepped on
		if (answer_board[new_row][new_col] != 0)
			continue;
		// Not matching
		if (grid[new_row][new_col] != target[move_no])
			continue;

		if (find_letter(target, move_no + 1, new_row, new_col))
			return true;
	}
	answer_board[init_row][init_col] = 0;
	return false;
}

vector<vector<int> > find_initial(string w)
{
	vector<vector<int> > initial_coordinates(grid_size * grid_size, {-1, -1});
	int ic_idx = 0;
	for (int i = 0; i < grid_size; ++i)
		for (int j = 0; j < grid[i].size(); ++j)
		{
			if (grid[i][j] == w[0])
			{
				initial_coordinates[ic_idx][0] = i;	//row
				initial_coordinates[ic_idx][1] = j;	//col
				ic_idx++;
			}
		}

	for (int i = 0; i < grid_size * grid_size - ic_idx; ++i)
		initial_coordinates.pop_back();

	return initial_coordinates;
}

void build_dict(string fileAddress)
{
	fstream dict_file(fileAddress);
	string line;
	if (dict_file.is_open())
	{
		while(getline(dict_file, line, ','))
		{
			dict.push_back(line);
		}
		dict_file.close();
	}
	else
		cout << "Unable to open the file.\n";
}

void lower_case_dict()
{
	for (int i = 0; i < dict.size(); ++i)
	{
		for (int j = 0; j < dict[i].size(); ++j)
		{
			dict[i][j] = tolower(dict[i][j]);
		}
	}
}

void build_grid(string fileAddress)
{
	cout << "Grid size: ";
	cin >> grid_size;

	vector<vector<char> > temp_grid(grid_size);
	grid = temp_grid;

	fstream grid_file(fileAddress);
	vector<string> lines;
	string l;
	if(grid_file.is_open())
	{
		while(getline(grid_file, l))
			lines.push_back(l);
		
		for (int i = 0; i < grid_size; ++i)
		{
			for (int j = 0; j < grid_size; ++j)
			{
				if(lines[i][j] != ' ')
					grid[i].push_back(lines[i][j]);
			}
		}
	}
	else
		cout << "Unable to open the file.\n";
}

void build_answer_board()
{
	vector<int> zeros;
	for (int i = 0; i < grid_size; ++i)
		zeros.push_back(0);

	vector<vector<int> > t_answer_board(grid_size,zeros);
	answer_board = t_answer_board;
}

void print_answer_board()
{
	for (int i = 0; i < grid_size; ++i)
	{
		for (int j = 0; j < grid_size; ++j)
			cout << answer_board[i][j] << ' ';

		cout << endl;
	}
}