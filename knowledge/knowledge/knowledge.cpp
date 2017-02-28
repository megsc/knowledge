// knowledge.cpp : Defines the entry point for the console application.
//
//read txt file to 2d array
//sort 2d array alphabetically for 1st col only
//2d array to object vector
//output to display questions or search for keyword
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


void outputMenu(vector<Questions>arrQues);
bool binarySearch(vector<string>& sorted_vec, const string &keyword);

int main()
{
	//declare variables
	vector <Questions> arrQues{};

	int rows = 0;
	int cols = 0;
	string my2dArray[6][2];
	
	string question, answer;
	

	//read txt file into 2d array
	ifstream myfile("questions.txt");
	
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
	//n = rows from 2dArray
	int n = 6;
	auto ptr = (pair<string, string>*) my2dArray;
	sort(ptr, ptr + n);



	//2d array to object vector 

	int count = 0;

	for (int i = 0; i < 6; ++i)//6 = number of rows in 2dArray
	{

		Questions newQ;
		newQ.set_question(my2dArray[i][0]);
		newQ.set_answer(my2dArray[i][1]);
		arrQues.push_back(newQ);
		count++;

	}


	//output menu
	outputMenu(arrQues);

	return 0;

}





void outputMenu(vector<Questions> arrQues)
{
	//output menu

	string menuChoice;
	string next;

	cout << "Ready for some knowledge?" << endl;
	cout << "Would you like to: " << endl;
	cout << "1 - Display the questions" << endl;
	cout << "2 - Search for a keyword" << endl;
	cout << "3 - Exit" << endl;

	cin >> menuChoice;


	//output questions 
	if (menuChoice == "1")
	{
		for (int i = 0; i < arrQues.size(); i++)
		{
			cout << "Question: " << endl;
			cout << arrQues[i].get_question() << endl;
			cout << "\nAnswer: " << endl;
			cout << arrQues[i].get_answer() << endl;
			cout << "\nPress N for next question...." << endl;
			cin >> next;
			cout << endl;
		}

	}


	//binary search for entered keyword
	if (menuChoice == "2")
	{

		//input from user for keyword to search
		string keyword;
		cout << "Enter keyword: " << endl;
		cin >> keyword;


		string strQA[12]; //12 = number of lines in txt file
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
		for (int i = 0; i < 6; i++)
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


	//exit program
	if (menuChoice == "3")
	{
		exit(0);
	}


	cin.get();




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



