

#include <iostream>
using namespace std;

enum enLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enOperation { Add = 1 , Sub = 2 , Malt = 3 , Div = 4 , MixOp = 5 };




struct stQuestion
{
	int number1;
	int number2;
	enLevel levelQuestion;
	enOperation operationQuestion;
	int correctAnswer;
	int plyerAnswer;
	bool resultQuestion;

};

struct stQuizz
{
	stQuestion questionList[100];
	short questionNumber;
	enLevel levelOfQuestion;
	enOperation operationOfQuestion;
	short rigthAnswer = 0;
	short rongAnswer = 0;
	bool resultGame;


};

short readQuestionNumber()
{
	short QuestionNumber;

	do
	{
		cout << "Please entre the number of question you want to answer :";
		cin >> QuestionNumber;
	} while (QuestionNumber < 1 || QuestionNumber > 10);

	return QuestionNumber;
}

enLevel readLevelQuestion()
{
	short level;
	do
	{
		cout << "choose the level : Easy [1],Med [2], Hard [3] ,MixLevel [4] :";
		cin >> level;
	} while (level < 1 || level > 4);
	return (enLevel)level;
 }

enOperation readOperation()
{
	short operation;
	do
	{
		cout << "choose operation : Add [1], Sub [2], Mul [3], Div [4], MixOp [5] :";
		cin >> operation;
	} while (operation < 1 || operation > 5);
	return (enOperation)operation;
}

int randomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;

	return randNum;
}

int calculator(stQuestion Question)
{
	switch (Question.operationQuestion)
	{
	case enOperation::Add:
		return Question.number1 + Question.number2;
	case enOperation::Sub:
		return Question.number1 - Question.number2;
	case enOperation::Malt:
		return Question.number1 * Question.number2;
	case enOperation::Div:
		return Question.number1 / Question.number2;
	default:
		return Question.number1 + Question.number2;
	}
}

stQuestion  generateQuestion(enLevel level, enOperation operation)
{
	stQuestion Question;

	if (level == enLevel::MixLevel)
	{
		level = (enLevel)randomNumber(1,3);
	}

	if (operation == enOperation::MixOp)
	{
		operation = (enOperation) randomNumber(1, 4);
	}

	Question.operationQuestion = operation;

	switch (level)
	{
	case enLevel::Easy:
		Question.number1 = randomNumber(1, 10);
		Question.number2 = randomNumber(1, 10);
		 
		// give me the correct result
		Question.correctAnswer = calculator(Question);
		Question.levelQuestion = level;
		return Question;

	case enLevel::Med:
		Question.number1 = randomNumber(10, 50);
		Question.number2 = randomNumber(10, 50);

		// give me the correct result
		Question.correctAnswer = calculator(Question);
		Question.levelQuestion = level;
		return Question;

	case enLevel::Hard:
		Question.number1 = randomNumber(50, 100);
		Question.number2 = randomNumber(50, 100);

		// give me the correct result
		Question.correctAnswer = calculator(Question);
		Question.levelQuestion = level;
		return Question;
	}

	return Question;
}

void generateQuestionList(stQuizz &Quizz)
{
	for (short Question = 0; Question < Quizz.questionNumber; Question++)
	{
		Quizz.questionList[Question] = generateQuestion(Quizz.levelOfQuestion,Quizz.operationOfQuestion);
	}
}

string symbolOperation(enOperation OpType)
{
	string arrOperation[4] = {"+","-","*","/"};
	return arrOperation[OpType - 1];
}
void printQuestion(stQuizz Quizz,int Question)
{
	cout << "\n Question : [" << Question + 1 << " / " << Quizz.questionNumber << "]" << endl;
	cout << Quizz.questionList[Question].number1 << endl;
	cout << Quizz.questionList[Question].number2 << " ";
	cout << symbolOperation(Quizz.questionList[Question].operationQuestion) << endl;
	cout << "-------------------\n";
}

int readPlayerAnswer()
{
	int answer;
	cin >> answer;
	return answer;
}
// validation the respone of player
void getResultQuestion(stQuizz &Quizz,short Question)
{
	if (Quizz.questionList[Question].plyerAnswer == Quizz.questionList[Question].correctAnswer)
	{
		 Quizz.questionList[Question].resultQuestion = true;
		 Quizz.rigthAnswer++;
		cout << "Rigth answer :-)";
		system("color 2F");
		
	}
	else
	{
		 Quizz.questionList[Question].resultQuestion = false;
		 Quizz.rongAnswer++;
		cout << "Rong answer :-(" << endl;
		cout << "the rigth answer is :" << Quizz.questionList[Question].correctAnswer << endl;
		system("color 4F");
		cout << "\a";
		
	}
}

string getResultGame(bool result)
{
	if (result)
	{
		return "Pass :-)";
		
	}
	else
	{
		return "Fail :-(";
		
	}
}
// get the answer of player and final result of questions
void answerplayerAndResultQuestions(stQuizz &Quizz)
{
	for (short Question = 0; Question < Quizz.questionNumber; Question++)
	{
		printQuestion(Quizz,Question);
		Quizz.questionList[Question].plyerAnswer = readPlayerAnswer();
		 getResultQuestion(Quizz,Question);
	}
	Quizz.resultGame = (Quizz.rigthAnswer >= Quizz.rongAnswer);
	if (Quizz.rigthAnswer >= Quizz.rongAnswer)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
	}
}
string printLevel(enLevel level)
{
	string arrLevel[4] = { "Easy","Med","Hard","MixLevel"};
	return arrLevel[level - 1];
}

string printOperation(enOperation operation)
{
	string arrOperation[5] = { "Add","Sub","Malt","Div","MixOperation"};
	return arrOperation[operation - 1];
}

void printFinalResult(stQuizz Quizz)
{
	cout << "\n-------------------------------------\n";
	cout << "The final result is :" << getResultGame(Quizz.resultGame) << endl;
	cout << "---------------------------------------\n";
	cout << "the number of Question :" << Quizz.questionNumber << endl;
	cout << "the level of Question :" << printLevel(Quizz.levelOfQuestion) << endl;;
	cout << "the operation of Question :" << printOperation(Quizz.operationOfQuestion) << endl;
	cout << "the rigth answers :" << Quizz.rigthAnswer << endl;
	cout << "the rong answers :" << Quizz.rongAnswer << endl;
}
void playMath()
{
	stQuizz    Quizz;

	Quizz.questionNumber = readQuestionNumber();
	Quizz.levelOfQuestion = readLevelQuestion();
	Quizz.operationOfQuestion = readOperation();

	generateQuestionList(Quizz);
	answerplayerAndResultQuestions(Quizz);
	printFinalResult(Quizz);

}
void resetScreen()
{
	system("cls");
	system("color 0F");
}
void startGame()
{
	string playAgain = "yes";
	do
	{
		resetScreen();
		playMath();
		cout << endl;
		cout << "do you want to play again yes/ no ? :";
		cin >> playAgain;
	} while (playAgain == "yes" || playAgain == "YES");
}


int main()
{
	srand((unsigned)time(NULL));
	startGame();
	 
	return 0;
}