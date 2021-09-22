#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;


/**
 * retreives info from specified text file, creating a vector of file names that correspond to possible user choices,
 * then prints the user prompt
 * @param file_name name of the file to retreive data from
 * @return file_names a vector consisting of file names that the user can jump to depending on their input
 */
vector<string> show_prompt_and_get_choices(string file_name)
{
	
	ifstream file;
	file.open("game_files\\" + file_name + ".txt"); //don't have to convert to c string with any c++ version that's c++11 and up
	
	int num_of_choices; 
	file >> num_of_choices; //sets num_of_choices equal to the number present in the first line of the file
	vector<string> file_names(num_of_choices); //make vector of room_names of size choices
	
	//get file names from the file, add them to the vector
	for(int i = 0; i < num_of_choices; i++) 
	{ 
		file >> file_names[i];
	}
	
	//print the rest of the file, which consists of the user prompt and choices they can make
	string output;
	while (getline(file, output))
	{
		cout << output << endl;
	}
	file.close();
	
	return file_names;
}

/**
 * asks for and validates the user's input, making sure that it is between num_1 and num_2, inclusive
 * @param num_1 beginning of the acceptable range 
 * @param num_2 end of the acceptable range
 * @return choice the user's validated input
 */
int get_and_validate_input(int num_1, int num_2)
{
	int choice;
	cout << "Input a number: ";
	cin >> choice; 
	
	while(cin.fail() || !(choice >= num_1 && choice <= num_2))
	{
		//if the user doesn't enter a number
		if (cin.fail())
		{
			cin.clear(); //clear fail state
			cin.ignore(1000, '\n');
			cout << endl << "That's not a number." << endl << "Please enter a number: ";
		}
		//if they enter a number, but it's not in range
		else
		{
			cout << endl << "The number you entered is not a valid choice." << endl << "Please input a valid number: ";
		}
		
		cin >> choice;
		
	}
	
	return choice;
}

int main()
{
	
	string cur_file = "title_screen"; //begin the game on the title screen
	string starting_file = "jail"; //starting file for the actual game
	
	string checkpoint_file = "illuminate"; //if the user gets to this file, they've reached the checkpoint
	bool checkpoint = false; //to mark if the checkpoint is achieved or not
	
	bool game_over = false;
	
	//game loop
	while(!game_over)
	{
		cout << endl;
		vector<string> file_names = show_prompt_and_get_choices(cur_file);
		cout << endl;
		
		if(cur_file == checkpoint_file)
		{
			checkpoint = true;
		}
		
		if(file_names.size() == 0) //unique to files indicating the end of the game
		{ 
			
			system("pause"); //pauses the program, prompts user to press any key to continue
			
			cout << endl << endl << endl << "What would you like to do next?" << endl;
			cout << "(1) Start over from the beginning\n" << "(2) Begin from the last checkpoint \n" << "(3) Exit the game" << endl;
			
			int choice = get_and_validate_input(1, 3);
			cout << endl;
			
			if (choice == 1) 
			{
				cout << "Starting over from the beginning . . .";
				cur_file = starting_file;
				checkpoint = false; //reset the checkpoint marker to false since the user has restarted the game
			}
			else if (choice == 2 && checkpoint)
			{
				cout << "Starting from the last checkpoint . . .";
				cur_file = checkpoint_file;
			}
			else if (choice == 2 && !checkpoint)
			{
				cout << "No checkpoint found, starting over from the beginning . . .";
				cur_file = starting_file;
			}
			else 
			{
				cout << "Exiting the game . . .";
				game_over = true;
			}
			
			cout << endl;
			Sleep(2069); //add a delay for when the next message pops up, in milliseconds
			
		}
		else if (file_names.size() == 1) //no choices for the user to make, just text
		{
			cur_file = file_names[0];
			//cout << "running " << cur_file << endl; //for testing, hide from user later
			system("pause"); //pauses the program, allows user to press any key to continue (so they can read the text before the program continues)
			
		}
		else 
		{
			int choice = get_and_validate_input(1, file_names.size());
			
			cur_file = file_names[choice - 1]; //jump to a new file based on user choice
			//cout << "running " << cur_file << endl; //for testing, hide from user later
			
		}
	
	}
	
}

