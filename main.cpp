//word search program!
	////algorithm: unless the size of words in the dict is much much more than the size of the grid, it`s logical to search for each word in the dict, and NOT vice versa...
	//take a dictionary and a grid as cmd args
	//run seach algorithms for all the words in the dict, on the grid
	//print all the matchin words

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<char> > grid;
vector<string> dict; 

const int POSSIBLE_MOVES = 8;
int ROW_DELTA[POSSIBLE_MOVES] = {0, -1, -1, -1, 0, 1, 1, 1};
int COL_DELTA[POSSIBLE_MOVES] = {-1, -1, 0, 1, 1, 1, 0, -1};

void build_grid(string fileAddress);
void build_dict(string fileAddress);
vector<string> line_to_words(string line);

bool find_word();
bool find_letter(int move_no, int init_row, int init_col);
vector<vector<int> > find_initial(string w); // searches for the first letter


int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		cout << "Usage: ./a.out	dictionary_file grid_file\n";
		return 1;
	}

	build_dict(argv[1]);
	build_grid(argv[2]);

}

// Each line will break down to individual words
vector<string> line_to_words(string line)
{
	vector<string> words;

	int beg_of_word = 0;

	for (int i = 0; i <= line.size(); ++i)
	{
		if (line[i] == ',' || i == line.size())
		{
			words.push_back(line.substr(beg_of_word, i - beg_of_word));
			beg_of_word = i + 1;
		}
	}
	beg_of_word = 0;

	return words;
}

void build_dict(string fileAddress)
{
	ifstream dict_file(fileAddress);
	string line;
	if (dict_file.is_open())
	{
		getline(dict_file, line);
		dict = line_to_words(line);
	}
	else
		cout << "Unable to open the file.\n";
}

void build_grid(string fileAddress)
{
	int grid_size;
	cout << "grid size: ";
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

	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid[i].size(); ++j)
		{
			cout << grid[i][j];
		}
		cout << endl;
	}
}

