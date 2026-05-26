#include <string>
#include <stdio.h>
class Logic {
public:
    Logic();
    //constructor
    void introduction();
    //Provides a basic introduction to the user
    bool createLists();
    //Opens a file and reads in the list of words that can be scrambled
    //Returns: true if words inserted and false if not
    bool playGame(Logic game);
    //Carries out the actual word scrambling
    //Returns: true if user wins and false if not
    std::string scrambler(std::string word);
    //Takes in a word and scrambles it
    //Returns a scrambled version of the parameter
    void end();
    //Displays the endgame information
    
private:
    int numCorrect,             //the number of correct words
        smallWordLength,       //length of word arrays
        mediumWordLength,
        largeWordLength;
    std::string smallWords[50];   //array of words of length 4-5
    std::string mediumWords[50];   //array of words of length 6-7
    std::string largeWords[50];   //array of words of length 8+ 
};
