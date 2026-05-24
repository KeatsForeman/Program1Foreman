#include <cstdlib>
#include <iostream>
#include <allegro5/allegro.h>


using namespace std;


bool finished = false;
bool timeOut = false;

void* input(ALLEGRO_THREAD* ptr, void* arg);
void* timer(ALLEGRO_THREAD* ptr, void* arg);

// Creates two threads and joins them so they run at the same time
int main(int argc, char* argv[])
{
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