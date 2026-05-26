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
	game.playGame(game);

	ALLEGRO_THREAD* create1 = NULL, * create2 = NULL; //used for return value from thread creation

	create1 = al_create_thread(input, NULL);
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
	if (finished)
		cout << "\n\tUser entered input and that ended the program\n";
	else
		cout << "\n\tTime ran out and that ended the program1\n";
	system("pause");
	return 0;
}

//constructor
Logic::Logic() {
	numCorrect = 0;
	smallWordLength = 0;
	mediumWordLength = 0;
	largeWordLength = 0;
}

//prints out game instructions
void Logic::introduction() {
	printf("Welcome to scramble!\nYou will be shown a scambled word, you will have 30 seconds to \nunscamble the word, but you have unlimited chances.");
}
void Logic::end() {
	printf("game over");
}

//reads in file and puts into lists
bool Logic::createLists() {
	std::string word;
	
	std::ifstream file("dictionary.txt");

	if (!file) {
		return false;
	}

	while (file >> word) {
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

//plays the game
bool Logic::playGame(Logic game) {
	bool roundDone = false;
	printf("GET READY FOR LEVEL 1\n");
	for (int i = 0; i < 2; i++) {
		std::string temp = smallWords[0];
		std::cout << "The word to guess is: " << scrambler(smallWords[0]) << std::endl;
		std::string ans;
		while (!roundDone) {
			std::cout << "guess ";
			std::cin >> ans;
			if (ans.compare(temp) == 0) {
				std::cout << "good\n";
				roundDone = true;
			}
		}
		roundDone = false;
	}
	for (int i = 0; i < 2; i++) {
		std::string temp = mediumWords[0];
		std::cout << "The word to guess is: " << scrambler(mediumWords[0]) << std::endl;
		std::string ans;
		while (!roundDone) {
			std::cout << "guess ";
			std::cin >> ans;
			if (ans.compare(temp) == 0) {
				std::cout << "good\n";
				roundDone = true;
			}
		}
		roundDone = false;
	}
	for (int i = 0; i < 2; i++) {
		std::string temp = largeWords[0];
		std::cout << "The word to guess is: " << scrambler(largeWords[0]) << std::endl;
		std::string ans;
		while (!roundDone) {
			std::cout << "guess ";
			std::cin >> ans;
			if (ans.compare(temp) == 0) {
				std::cout << "good\n";
				roundDone = true;
			}
		}
		roundDone = false;
	}
	return true;
}

//scrambles words in the arrays
std::string Logic::scrambler(std::string word) {

	std::string newWord = word;
	std::shuffle(newWord.begin(), newWord.end(), std::default_random_engine());

	return newWord;
}

// A pointer to a function that prompts the user for input
void* input(ALLEGRO_THREAD* ptr, void* arg)
{
	finished = false;
	cout << "what's yer guess?\n";
	cin >> finished;
	finished = true;
	return NULL;
}
// A pointer to a function that starts the timer and checks the change in
// finished, which is in the input thread.
void* timer(ALLEGRO_THREAD* ptr, void* arg)
{
	time_t startTime, currentTime; //times used to measure elapsed time
	startTime = time(NULL);
	currentTime = time(NULL);
	while (currentTime - startTime < 10 && !finished)
	{
		currentTime = time(NULL);
	}
	timeOut = true;
	return NULL;
}
