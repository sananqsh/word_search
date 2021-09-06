//Fs and Vars
	#include <iostream>
	#include <cstring>
	#include <vector>
	#include <fstream>
	#include <sstream>

	using namespace std;

	vector<string> dict;
	int grid_size;
	vector<vector<char> > grid;
	vector<vector<int> > answer_board;

// void build_table(string fileAddress) {
// 	vector<vector<char> > t_table(table_size);
// 	table = t_table;

// 	fstream table_file(fileAddress);
// 	vector<string> lines;
// 	string l;
// 	if(table_file.is_open())
// 	{
// 		while(getline(table_file, l))
// 			lines.push_back(l);
		
// 		for (int i = 0; i < table_size; ++i)
// 		{
// 			for (int j = 0; j < 2 * table_size; ++j)//considering spaces betw chars --> 2 * size
// 			{
// 				if(lines[i][j] != ' ')
// 					table[i].push_back(lines[i][j]);
// 			}
// 		}
// 	}
// 	else
// 		cout << "Unable to open the file.\n";
// }

void build_dict(string fileAddress)
{
	fstream dict_file(fileAddress);
	string line;
	if (dict_file.is_open())
	{
		while(getline(dict_file, line, ','))
		{
			// cout << "line: " << line << ", " << line.size() << endl;
			dict.push_back(line);
		}
		dict_file.close();
	}
	else
		cout << "Unable to open the file.\n";
}

int main(int argc, char const *argv[])
{
	build_dict(argv[1]);

	for (int i = 0; i < dict.size(); ++i)
	{
		// for (int j = 0; j < dict[i].size(); ++j)
		// {
		string x = dict[i];
			// cout << x ;
			// cout << x.size();
		// }
		cout << endl;
	}
//
	// vector<string> answer;
	// for (int i = 0; i < 1; ++i)
	// {
	// 	build_answer_board();
	// 	if (find_word(dict[i]))
	// 	{
	// 		cout << "FOUND\n!";
	// 		answer.push_back(dict[i]);
	// 		answer.push_back(",");
	// 	}
	// 	// print_answer_board();
	// }

	// for (int i = 0; i < answer.size(); ++i)
	// {
	// 	cout << answer[i] << endl;
	// }
}