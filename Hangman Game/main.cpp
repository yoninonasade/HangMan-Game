#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>

void PrintMessage(std::string message,bool b_printTop=true,bool b_printBottom=true);
void DrawHangman(int guessCount = 0);
void PrintLetters(std::string input , char from , char to);
void PrintAviableLetters(std::string userInput);
bool PrintWordAndCheckWin(std::string word,std::string userGuess);
std::string LoadRandomWord(std::string filePath);
int triesLeft(std::string word,std::string guess);

int main() {

	srand(time(0));
	std::string userGuess = "" ;
	std::string wordToGuess = LoadRandomWord("Words.txt");
	int tries = 0;
	bool win = false;
	do {
	
		system("cls");
		PrintMessage("HANG MAN");
		DrawHangman(tries);
		PrintAviableLetters(userGuess);
		PrintMessage("Guess the Movie");
		win = PrintWordAndCheckWin(wordToGuess, userGuess);

		if (win) {
		
			break;
		}

		char x;
		std::cout << ">";
		std::cin >> x;
		if (userGuess.find(x) == std::string::npos) {

			userGuess += x;
		}

		tries = triesLeft(wordToGuess,userGuess);

	} while (tries<10);

	
	if (win) {
	
		PrintMessage("CONGRATULATIONS - SOLVE IT !!");
	}
	else {
	
		PrintMessage("GAME OVER !!\n");
	}

	system("pause");
	
	

	std::getchar();
	return 1;
}

void PrintMessage(std::string message, bool b_printTop, bool b_printBottom) {

	bool front = true;

	if (b_printTop){

		std::cout << "+---------------------------------+" << std::endl;
		std::cout << "|";
	}
	else {
		std::cout << '|';
	}

	for (int i = message.length(); i < 33; i++) {
	
		if (front) {
		
			message = " " + message;
		}
		else {
		
			message = message + " ";
		}
		front = !front;
	}

	std::cout << message.c_str();

	
	if (b_printBottom) {

		std::cout << "|\n";
		std::cout << "+---------------------------------+" << std::endl;
	}
	else {
		std::cout << '|' << std::endl;
	}


}

void DrawHangman(int guessCount) {

	// Draw User Hanging Man Status according to number of his trys // 

	if (guessCount >= 1){

		PrintMessage("|", false, false);
	}else { PrintMessage("", false, false); }
	if (guessCount >= 2) {

		PrintMessage("|", false, false);
	}else { PrintMessage("", false, false); }
	if (guessCount >= 3) {

		PrintMessage("O", false, false);
	}else { PrintMessage("", false, false); }
	if (guessCount == 4) {

		PrintMessage("/ ", false, false);
	}
	if (guessCount == 5) {

		PrintMessage("/O ", false, false);
	}
	if (guessCount >= 6) {

		PrintMessage("/O\\", false, false);
	}else{PrintMessage("", false, false);}
	if (guessCount >= 7) {

		PrintMessage("|", false, false);
	}else { PrintMessage("", false, false); }
	if (guessCount == 8) {

		PrintMessage("/", false, false);
	}
	if (guessCount >= 9) {

		PrintMessage("/ \\", false, false);
	}else { PrintMessage("", false, false); }
}

void PrintLetters(std::string input, char from, char to) {

	std::string localString;

	for (char i = from; i <= to; i++)
	{

		if (input.find(i) == std::string::npos)
		{
			localString += i;
			localString += " ";
		}
		else {
			localString += "-";
			localString += " ";
		}

	}

	PrintMessage(localString,false,false);
}

void PrintAviableLetters(std::string userInput) {

	PrintMessage("Available Letters");
	PrintLetters(userInput, 'A', 'M');
	PrintLetters(userInput, 'N', 'Z');

}

bool PrintWordAndCheckWin(std::string word, std::string userGuess) {

	bool won = true;
	std::string localString; 

	for (int i = 0; i < word.length(); i++)
	{
		if (userGuess.find(word[i]) == std::string::npos)
		{
			won = false;
			localString += "_ ";
		}
		else {
		
			localString += word[i];
			localString += " ";
		}
	}
	PrintMessage(localString, false);
	return won;
}

std::string LoadRandomWord(std::string filePath) {

	int lineCount = 0;
	std::string l_Word;
	std::vector <std::string> word_arr;
	std::ifstream myFile(filePath);

	if (myFile.is_open()) {
	
		while (std::getline(myFile, l_Word)) {
		
			word_arr.push_back(l_Word);
		}

		int randomLine = rand() % word_arr.size();
		l_Word = word_arr.at(randomLine);
		myFile.close();
	}
	else {
	
		std::cout << "Failed to open Words File .. \n ";
		exit(1);
	}

	return l_Word;;

}

int triesLeft(std::string word, std::string guess) {

	int l_error = 0;
	for (int i = 0; i < guess.length(); i++) {

		if (word.find(guess[i]) == std::string::npos)
		{
			l_error++;
		}
	}
	return l_error;
}