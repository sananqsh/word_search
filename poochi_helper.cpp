// We enter a text file (matrix of letters) as a command-line argument, enter the word we are looking for, and finally, the size of that square matrix;
// and if the target word exists in the matrix, the program prints the path of how it would be found;
// if it can`t be found in the letters, the program prints: "No"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//start moving from going to left and search clockwise around
const int POSSIBLE_MOVES = 8;
int ROW_DELTA[POSSIBLE_MOVES] = {0, -1, -1, -1, 0, 1, 1, 1};
int COL_DELTA[POSSIBLE_MOVES] = {-1, -1, 0, 1, 1, 1, 0, -1};
vector<vector<int> > answer_board;

//G vars:
string given_word;
int table_size;
vector<vector<char> > table;

//funks:
void build_table(string fileAddress);
void build_answer_board();
bool find_word();
bool find_letter(int move_no, int init_row, int init_col);
void print_answer_board();
vector<vector<int> > find_initial(string w); // searches for the first letter

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		cout << "Correct format: ./a.out ./<fileNAme>\n";
		return 1;
	}
	
	cout << "word: ";
	getline(cin, given_word);
	cout << "table size: ";
	cin >> table_size;

	build_table(argv[1]);
	build_answer_board();
	
	if (find_word())
	{
		cout << "Yes\n";
		print_answer_board();
	}
	else
		cout << "No\n";

	return 0;
}

void build_table(string fileAddress) {
	vector<vector<char> > t_table(table_size);
	table = t_table;

	fstream table_file(fileAddress);
	vector<string> lines;
	string l;
	if(table_file.is_open())
	{
		while(getline(table_file, l))
			lines.push_back(l);
		
		for (int i = 0; i < table_size; ++i)
		{
			for (int j = 0; j < 2 * table_size; ++j)//considering spaces betw chars --> 2 * size
			{
				if(lines[i][j] != ' ')
					table[i].push_back(lines[i][j]);
			}
		}
	}
	else
		cout << "Unable to open the file.\n";
}

bool find_word() {
	vector<vector<int> > initial_coordinates = find_initial(given_word);
	for (int i = 0; i < initial_coordinates.size(); ++i)
	{
		int init_row = initial_coordinates[i][0];
		int init_col = initial_coordinates[i][1];
		if (find_letter(1, init_row, init_col))
		{
			return true;
		}
		answer_board[init_row][init_col] = 0;
	}
	return false;
}

bool find_letter(int move_no, int init_row, int init_col) {
	answer_board[init_row][init_col] = move_no;
	if (move_no == given_word.size())
		return true;
	for (int move = 0; move < POSSIBLE_MOVES; ++move)
	{
		int new_row = init_row + ROW_DELTA[move];
		int new_col = init_col + COL_DELTA[move];

		//handling possible missteps
		//out of bounds
		if (new_row < 0 || new_col < 0 || new_row >= table_size || new_col >= table_size)
			continue;
		//already stepped on
		if (answer_board[new_row][new_col] != 0)
			continue;
		//not matching
		if (table[new_row][new_col] != given_word[move_no])
			continue;

		if (find_letter(move_no + 1, new_row, new_col))
			return true;
	}
	answer_board[init_row][init_col] = 0;
	return false;
}

vector<vector<int> > find_initial(string w) {
	vector<vector<int> > in_co(table_size * table_size, {-1, -1}); //in_co: initial coordinates
	int ic_idx = 0;
	for (int i = 0; i < table_size; ++i)
		for (int j = 0; j < table[i].size(); ++j)
			if (table[i][j] == w[0])
			{
				in_co[ic_idx][0] = i;	//row
				in_co[ic_idx][1] = j;	//col
				ic_idx++;
			}

	for (int i = 0; i < table_size * table_size - ic_idx; ++i)
		in_co.pop_back();

	return in_co;
}

void build_answer_board() {
	vector<int> zeros;
	for (int i = 0; i < table_size; ++i)
	{
		zeros.push_back(0);
	}
	vector<vector<int> > t_answer_board(table_size,zeros);
	answer_board = t_answer_board;
}

void print_answer_board() {
	for (int i = 0; i < table_size; ++i)
	{
		for (int j = 0; j < table_size; ++j)
		{
			cout << answer_board[i][j] << ' ';
		}
		cout << endl;
	}
}