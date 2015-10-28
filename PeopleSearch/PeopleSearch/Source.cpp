#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//*************************************************
//This function merely reads the content of the   *
//name file into the array namelist for later use *
//*************************************************

int readfile(ifstream& lister, string namelist[], int& columnNumber)
{
	string trash;
	getline(lister, trash);
	while (getline(lister, namelist[columnNumber]))
	{
		columnNumber++;
	}
	return columnNumber;
}

//*****************************************************************
//the pivot just swaps greater than stuff over the pivotPoint     *
//for use within the qsort function                               *
//*****************************************************************

int pivot(string namelist[], int startingOffset, int closingOffset)
{
	int marker = startingOffset;
	string pivotElement = namelist[marker];

	for (int i = marker + 1; i <= closingOffset; i++) //i is a marker for the loop, so that it runs throughout the entire group provided
	{
		if (namelist[i] <= pivotElement)
		{
			marker++;
			swap(namelist[i], namelist[marker]);
		}
	}

	swap(namelist[marker], namelist[startingOffset]);
	return marker;
}

//************************************************
//This is a quicksort function that organizes    *
//the namelist array more efficiently than the   *
//selection sort algarithm:                      *
//takes left and irght of the "middle" of the    *
//array and puts larger in right and smaller in  *
//left, then does that over again (recurssion)   *
//************************************************

void qsort(string namelist[], int startingOffset, int closingOffset)
{
	int pivotPoint; //the "middle" around which everythng is shifted depending on if greater/lesser
	

	if (startingOffset < closingOffset)
	{
		pivotPoint = pivot(namelist, startingOffset, closingOffset);
		qsort(namelist, startingOffset, pivotPoint - 1);
		qsort(namelist, pivotPoint + 1, closingOffset);
	}
}

//*************************************************
//This is a selection sort function that takes the*
//namelist array and a temp string to organize in *
//alphabetical order the names within the array   *
//*************************************************

void sortarray(string namelist[], int listLength) //listLength is the number of names in the array +1
{
	string tempSwitcher;
	for (int index = 0; index < listLength; index++)
	{
		int location = index + 1;
		for (; location <= listLength; location++)
		{
			if (namelist[location] < namelist[index])
			{
				tempSwitcher = namelist[location];
				namelist[location] = namelist[index];
				namelist[index] = tempSwitcher;
			}
		}
	}
}

//*********************************
//This is a binary search function*
//for use on the namelist array   *
//*********************************

void searchlist(string namelist[], int listLength)
{
	string searchedName;
	do
	{
		int first = 0,
			last = listLength,
			middle,
			position = -1;
		bool found = false;
		cout << endl << "--Search List--" << endl << "Please input the name you're looking for: ";
		getline(cin, searchedName);

		while (!found && first <= last)
		{
			middle = (first + last) / 2;
			if (namelist[middle] == searchedName)
			{
				found = true;
				position = middle + 1;
			}
			else if (namelist[middle] > searchedName)
				last = middle - 1;
			else
				first = middle + 1;
		}
		cout << endl;
		if (found != true)
			cout << "The name you searched for was not found, our humblest apologies.";
		else
		{
			cout << "The name you searched for was found in position " << position << " of the array";
		}

		cout << endl << "-----------";
		cout << endl << endl << "Input another name to search for or enter Q to return to the menu: ";
		getline(cin, searchedName);
	} while (searchedName != "q" && searchedName != "Q");
}

//******************************************************
//This function prints out the array namelist in chunks*
//of 200 sorted names depending on the user selection  *
//******************************************************

void printlist(string namelist[], int listLength)
{
	string pageNumber;
	bool quit = false;

	cout  << endl << endl << "--Print List--" << endl;

	while (quit != true)
	{
		string looper = "T";
		
		cout << endl << "The name list is printed in 200 name increments. ";
		cout << "So " << (listLength + 199) / 200 << " pages for your list.";
		cout << endl << "-----------" << endl;
		cout << endl << "Please input a page number: ";
		getline(cin, pageNumber);
		while (atoi(pageNumber.c_str()) <= 0 || atoi(pageNumber.c_str()) > ((listLength + 199) / 200))
		{
			cout << "-----------" << endl;
			cout << "Invalid Input try again: ";
			getline(cin, pageNumber);
		}

		int startinglocation = (atoi(pageNumber.c_str()) - 1) * 200; //Convert the inputed pageNumber into a starting location in the array

		for (int counter = 0; counter <= 200 && (counter + startinglocation) <= listLength; counter++)
		{
			cout << (counter + startinglocation) << ". " << setw(35) << left << namelist[startinglocation + counter];
			counter++;
			if (counter + startinglocation <= listLength)
			{
				cout << (counter + startinglocation) << ". " << namelist[startinglocation + counter];
			}
			cout << endl;
		}
		
		cout << "-----------" << endl;
		cout << endl << "Input R to input another page number or Q to quit: ";
		getline(cin, looper);
		
		while (looper != "Q" && looper != "q" && looper != "R" && looper != "r")
		{
			cout << "-----------" << endl;
			cout << "Are you trying to break the internet? Your input was invalid try again: ";
			getline(cin, looper);
		}
		if (looper == "Q" || looper == "q")
			quit = true;
		else
			cout << endl << endl;
	}
}

//****************************************************
//The main function utilizes all the other functions *
//and allows the user to loop however many times they*
//want to before closing the program                 *
//****************************************************

int main()
{
	ifstream lister;                    //Variable Declarations for the main function: 
	string filename;                    //Lister(name file), filename(filename), namelist(taken from name file), columnNumber(tracker for array), fixed(for the do while loop for lister file name input), trash(just for throwing away unwanted content)
	string namelist[5000];
	int columnNumber = 0;
	bool fixed = false;

	cout << "Input the location of the file you wish to use: ";
	getline(cin, filename);

	do
	{
		lister.open(filename);
		if (!lister)
		{
			cout << "There was an error with the file you specified, please try again: ";
			getline(cin, filename);
		}
		else
			fixed = true;
	} while (!fixed);
	
	cout << "Loading and sorting the file------" << endl;

	readfile(lister, namelist, columnNumber);
	qsort(namelist, 0, columnNumber);

	string choice = "T";   //a quit variable for the while loop (loops for choices between search list or print sorted list)
	while (choice != "Q" && choice != "q")
	{
		cout << "\n\n\n\n\n";
		cout << endl << "--Main Menu--" << endl;
		cout << "Program Functions:" << endl << "___________________" << endl << "A. Search" << endl << "B. Print List" << endl << "Q. Quit" << endl << endl;
		cout << "Input the letter for the function you desire(input q to exit this program): ";
		getline(cin, choice);

		bool quit = false; //for a list loop
		while (quit != true)
		{
			if (choice == "A" || choice == "a")
			{
				searchlist(namelist, columnNumber);
				quit = true;
			}
			else if (choice == "B" || choice == "b")
			{
				printlist(namelist, columnNumber);
				quit = true;
			}
			else if (choice == "Q" || choice == "q")
			{
				quit = true;
			}
			else
			{
				cout << "-----------" << endl;
				cout << "Your input was not valid, try again: ";
				getline(cin, choice);
				break;
			}
		}
	} 

	/* // ---TEST FUNCTIONALITY---
	for (int counter = 0; counter < 2500; counter += 5)
		cout << namelist[counter] << endl;
	cout << columnNumber;
	int temp;
	cin >> temp;
	*/
	lister.close();
	return 0;
}