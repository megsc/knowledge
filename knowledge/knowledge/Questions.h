#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;


class Questions
{
	string question;
	string answer;


public:
	void set_question(string);
	void set_answer(string);

	string get_question() { return question; }
	string get_answer() { return answer; }

	Questions();
	Questions(string a, string b);

};

