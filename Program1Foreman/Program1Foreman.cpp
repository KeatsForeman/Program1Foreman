#include <cstdlib>
#include <iostream>
#include <allegro5/allegro.h>
#include "Logic.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <cstring>


using namespace std;

bool finished = false;
bool timeOut = false;

void* input(ALLEGRO_THREAD* ptr, void* arg);
void* timer(ALLEGRO_THREAD* ptr, void* arg);

// Creates two threads and joins them so they run at the same time
int main(int argc, char* argv[]) {

	Logic game;

	game.introduction();
	game.createLists();

	ALLEGRO_THREAD* create1 = NULL, * create2 = NULL; //used for return value from thread creation

	create1 = al_create_thread(input, &game);
	create2 = al_create_thread(timer, NULL);

	

	while (!finished && !timeOut)
	{


		if (!finished && !timeOut)
		{
			al_start_thread(create1);

			al_start_thread(create2);

		}
		else
		{
			al_destroy_thread(create1);
			al_destroy_thread(create2);
		}


	}
	//when thread that is running game finishes
	if (finished) {
		cout << "You WON! :D\n";
		game.end();
	}
	//when timer ends
	else {
		cout << "\n\tTime ran out\n";
		game.end();
		}	
	system("pause");
	return 0;
}

//One line describing function
//one line describing param
// one line describing return

//constructor
Logic::Logic() {
	numCorrect = 0;
	smallWordLength = 0;
	mediumWordLength = 0;
	largeWordLength = 0;
}

//prints out game instructions
void Logic::introduction() {
	printf("Welcome to scramble!\nYou will be shown a scambled word, you will have 60 seconds to \nunscamble the word, but you have unlimited chances.");
}

//prints out the result of the game, different output based on score
void Logic::end() {
	std::string score = to_string(numCorrect);
	cout << "game over\nYour score was " << score.c_str() << " out of 5. ";
	if (numCorrect <= 1) {
		cout << "You have no mind : (\n";
	}
	if (numCorrect == 2) {
		cout << "You have a bit of a mind :|\n";
	}
	if (numCorrect == 3) {
		cout << "Your mind is alright\n";
	}
	if (numCorrect == 4) {
		cout << "You have a great mind : )\n";
	}
	if (numCorrect == 5) {
		cout << "YOUR MIND IS INCREDIBEL\n";
	}
}

//reads in file and puts into lists
//outputs true if successful, false if not
bool Logic::createLists() {
	std::string word;
	
	//get file
	std::ifstream file("dictionary.txt");
	//check if it worked
	if (!file) {
		return false;
	}
	//for each word in the file
	while (file >> word) {
		//check lengths and insert into appropriate array
		if (word.length() == 4 || word.length() == 5) {
			smallWords[smallWordLength] = word;
			smallWordLength += 1;
		}
		if (word.length() == 6 || word.length() == 7) {
			mediumWords[mediumWordLength] = word;
			mediumWordLength += 1;
		}
		if (word.length() >= 8) {
			largeWords[largeWordLength] = word;
			largeWordLength += 1;
		}
	}
	return true;
}

//runs the game by pulling random words from arrays and scrambling them, then asking the user to guess
//takes Logic instance as parameter
//returns true if the player wins
bool Logic::playGame(Logic game) {
	bool roundDone = false;
	int randNum;
	std::string temp;
	std::srand(time(0));
	cout << "\nGET READY FOR LEVEL 1\n";
	//two small words in this loop
	for (int i = 0; i < 2; i++) {
		if (i == 1) {
			cout << "GET READY FOR LEVEL 2\n";
		}
		//get a random number
		randNum = rand() % smallWordLength - 1;
		temp = smallWords[randNum];
		//call scrambler on the word
		std::cout << "The word to guess is: " << scrambler(smallWords[randNum]) << std::endl;
		std::string ans;
		//while the user has not guessed
		while (!roundDone) {
			std::cout << "guess ";
			std::cin >> ans;
			if (ans.compare(temp) == 0) {
				std::cout << "good\n";
				//exit while loop
				roundDone = true;
				//increment score
				numCorrect += 1;
			}
		}
		roundDone = false;
	}
	cout << "GET READY FOR LEVEL 3\n";
	//two medium words in this loop
	for (int i = 0; i < 2; i++) {
		if (i == 1) {
			cout << "GET READY FOR LEVEL 4\n";
		}
		//get a random number
		randNum = rand() % mediumWordLength - 1;
		temp = mediumWords[randNum];
		//call scrambler on the word
		std::cout << "The word to guess is: " << scrambler(mediumWords[randNum]) << std::endl;
		std::string ans;
		//while the user has not guessed
		while (!roundDone) {
			std::cout << "guess ";
			std::cin >> ans;
			if (ans.compare(temp) == 0) {
				std::cout << "good\n";
				//exit while loop
				roundDone = true;
				//increment score
				numCorrect += 1;
			}
		}
		roundDone = false;
	}
	//once for large words
	cout << "GET READY FOR LEVEL 5\n";
	randNum = rand() % largeWordLength - 1;
	temp = largeWords[randNum];
	std::cout << "The word to guess is: " << scrambler(largeWords[randNum]) << std::endl;
	std::string ans;
	while (!roundDone) {
		std::cout << "guess ";
		std::cin >> ans;
		if (ans.compare(temp) == 0) {
			std::cout << "good\n";
			roundDone = true;
			numCorrect += 1;
			finished = true;
		}
	}
	return true;
}

//scrambles each word in the arrays
//takes a string as a parameter
//return the string scrambled
std::string Logic::scrambler(std::string word) {

	std::string newWord = word;
	std::shuffle(newWord.begin(), newWord.end(), std::default_random_engine());

	return newWord;
}

// A pointer to a function that prompts the user for input
void* input(ALLEGRO_THREAD* ptr, void* arg)
{
	Logic* game = (Logic*)arg;
	game->playGame(*game);
	return NULL;
}
// A pointer to a function that starts the timer and checks the change in
// finished, which is in the input thread.
void* timer(ALLEGRO_THREAD* ptr, void* arg)
{
	time_t startTime, currentTime; //times used to measure elapsed time
	startTime = time(NULL);
	currentTime = time(NULL);
	while (currentTime - startTime < 20 && !finished)
	{
		currentTime = time(NULL);
	}
	timeOut = true;
	return NULL;
}
