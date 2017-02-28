#include "stdafx.h"
#include "Questions.h"

Questions::Questions()
{

}


Questions::Questions(string question, string answer)
{
	set_question(question);
	set_answer(answer);

}



void Questions::set_question(string quest)
{
	question = quest;

}

void Questions::set_answer(string answ)
{
	answer = answ;
}



