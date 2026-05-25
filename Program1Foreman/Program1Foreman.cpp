#include <cstdlib>
#include <iostream>
#include <allegro5/allegro.h>
#include "Logic.h"
#include <fstream>
#include <algorithm>
#include <random>


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
	printf("GUess these darn words please\n");
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
			smallWords->append(word);
		}
		if (word.length() == 6 || word.length() == 7) {
			mediumWords->append(word);
		}
		if (word.length() >= 8) {
			largeWords->append(word);
		}
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
	cout << "Asking for user Input?";
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
