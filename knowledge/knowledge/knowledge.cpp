// knowledge.cpp : Defines the entry point for the console application.
//
//
//Assignment 1: Show Me The Knowledge!
//Megan Carlton 
//submitted ?? MAR 17 
//


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Questions.h"

using namespace std;


void outputMenu();
bool binarySearch(vector<string>& sorted_vec, const string &keyword);
void searchWord(vector<Questions>arrQues);
void dynamicArray();
void randomAccess();
void displayQuestions(vector<Questions>arrQues);

const int arrRows = 10;
const int arrCols = 2;
const int fileLines = 20;


int main()
{
	//declare variables
	vector <Questions> arrQues{};

	int rows = 0;
	int cols = 0;
	string my2dArray[arrRows][arrCols];
	
	string question, answer;
	


	//read txt file into 2d array

	ifstream myfile("questions2.dat", ios::in | ios::binary);

	if (myfile.is_open())
	{
		string line;
			

		while (getline(myfile, line))
		{
			my2dArray[rows][cols] = line;
			cols++;

		}
		rows++;
		


		myfile.close();
	}


	else
	{
		cout << "Unable to open file";
		exit(EXIT_FAILURE);

	}



	//sorting array by first col alphabetically
	//numbRows = rows from 2dArray

	int numbRows = arrRows;
	auto ptr = (pair<string, string>*) my2dArray;
	sort(ptr, ptr + numbRows);



	//2d array to object vector 

	int count = 0;

	for (int i = 0; i < arrRows; ++i)//arrRows = number of rows in 2dArray
	{

		Questions newQ;
		newQ.set_question(my2dArray[i][0]);
		newQ.set_answer(my2dArray[i][1]);
		arrQues.push_back(newQ);
		count++;

	}


	//output menu

	bool quit = false;
	int menuChoice;

	while (!quit)
	{
		outputMenu();

		cin >> menuChoice;

		switch (menuChoice)
		{
			case 1:
				displayQuestions(arrQues);
				break;

			case 2:
				searchWord(arrQues);
				break;

			case 3:
				randomAccess();
				break;

			case 4:
				dynamicArray();
				break;

			case 5:
				quit = true;
				break;

			default:
				cout << "Oops! Please enter a number 1-5" << endl;
				break;

		}

	}
	

	return 0;

}





void outputMenu()
{
	//output menu

	cout << "Ready for some knowledge?" << endl;
	cout << "Would you like to: " << endl;
	cout << "1 - Display the questions" << endl;
	cout << "2 - Search for a keyword" << endl;
	cout << "3 - Read text file randomly" << endl;
	cout << "4 - Dynamic Array Demo" << endl;
	cout << "5 - Exit" << endl;


}



void displayQuestions(vector<Questions> arrQues)
{
	//function to display questions

	string next;

	for (int i = 0; i < arrQues.size(); i++)
	{
		cout << "Question: " << endl;
		cout << arrQues[i].get_question() << endl;
		cout << "\nAnswer: " << endl;
		cout << arrQues[i].get_answer() << endl;
		cout << "\nPress any key for next question...." << endl;
		cin >> next;
		cout << endl;
	}
}



void searchWord(vector<Questions> arrQues)
{
	//input from user for keyword to search
	string keyword;
	cout << "Enter keyword: " << endl;
	cin >> keyword;


	string strQA[fileLines]; //fileLines = number of lines of text in txt file
	int count = 0;

	//object vector to string array
	for (int i = 0; i < arrQues.size(); i++)
	{
		stringstream convertQA;
		convertQA.str(arrQues[i].get_question() + "\n" + arrQues[i].get_answer());
		strQA[count] = convertQA.str();
		count++;

	}


	vector<string> words{};

	//string array to single word string vector
	for (int i = 0; i < fileLines; i++)
	{
		istringstream each(strQA[i]);
		string word;
		while (each >> word)
		{
			//cout << word << endl;
			words.push_back(word);
		}


	}


	//sorting word vector for binary search
	sort(words.begin(), words.end());

	//binarySearch method for keyword input 
	bool found = binarySearch(words, keyword);

	if (found == true)
	{
		cout << "found" << endl;
	}

	else
	{
		cout << "not found" << endl;
	}

	cin.get();



}



void randomAccess()
{
	int numEntered;
	string show;

	cout << "Read a line from anywhere in the text file" << endl;
	cout << "Enter number lower than 2500:" << endl;
	cin >> numEntered;

	ifstream myfile("questions2.dat", ios::in | ios::binary);

	if (myfile.is_open())
	{
		myfile.seekg(numEntered);
		getline(myfile, show);

		cout << show << endl;

		myfile.close();

	}

	else
	{
		cout << "Unable to open file";
		exit(EXIT_FAILURE);

	}


	cin.get();


}



void dynamicArray()
{
	int arrLength;

	cout << "Let's create an array!" << endl;
	cout << "Enter a number 1-6: " << endl;
	cin >> arrLength;
	cout << "List the Top " << arrLength << " places you want to go on holiday" << endl;

	string *holidays = new string[arrLength];


	for (int i = 0; i < arrLength; ++i)
	{
		cin >> holidays[i];

	}

	cout << "I want to go to " << holidays[0] << " as well!\n" << endl;
	cout << "You want to travel to: " << endl;

	for (int i = 0; i < arrLength; ++i)
	{
		cout << holidays[i] << ", " << endl;

	}

	delete[] holidays;

}





bool binarySearch(vector<string>& sorted_vec, const string &keyword)
{
	//binary search incl pass by reference

	size_t mid, left = 0;
	size_t right = sorted_vec.size();

	while (left < right)
	{
		mid = (left + right) / 2;

		if (keyword > sorted_vec[mid])
		{
			left = mid + 1;
		}

		else if (keyword < sorted_vec[mid])
		{
			right = mid - 1;
		}

		else
		{
			return mid;
		}
	}

	return false;
}



