#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
using namespace std;

void checkWord(const std::string& guess, const std::string& answer) {

    // pair of letter and color
    std::vector<std::pair<char, std::string> > result(guess.length());  

    // keeps track of all occurrences of each letter
    std::vector<std::set<int> > letter_positions(26); 

    // store the positions of each letter in the answer
    for (size_t i = 0; i < answer.length(); ++i) {
        letter_positions[answer[i] - 'a'].insert(i);
    }

    // check for letters in the right spot and mark them in the result vector
    for (size_t i = 0; i < guess.length(); ++i) {
        if (guess[i] == answer[i]) {
            if (!letter_positions[guess[i] - 'a'].empty()) {
                // If the letter exists in the letter_positions vector
                result[i] = std::make_pair(guess[i], "\033[1;32m");
                letter_positions[guess[i] - 'a'].erase(letter_positions[guess[i] - 'a'].begin());
            }
        }
    }

    // Check for letters in the guess that are not in the right spot and mark them in the result vector
    for (size_t i = 0; i < guess.length(); ++i) {
        if (result[i].first == '\0') {
            std::set<int>::iterator it = letter_positions[guess[i] - 'a'].begin();
            if (it != letter_positions[guess[i] - 'a'].end()) {
                result[i] = std::make_pair(guess[i], "\033[1;33m"); // Yellow letter for correct letter in the wrong spot
                letter_positions[guess[i] - 'a'].erase(it);
            } else {
                result[i] = std::make_pair(guess[i], "\033[1;30m"); // Gray letter for letters not in the word
            }
        }
    }

    // Print the color-coded version of the guess
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i].second << result[i].first << "\033[0m"; // Print letter with color code
    }

    std::cout << std::endl;
}



int main()
{
    // declaring the variables for the word to be guessed, the amount of guesses the player should have, and the last guess they made. 
    string answer;
    int num_guess;
    string guess;

    // printing text to the console instructing the first user to enter a five letter word, and then storing it in the variable answer
    cout << "First, we will need to set the word to figure out. Give me a five letter word: ";
    cin >> answer;
    cout << endl;

    //while loop checks the length of the string and rejects words that are not 5 charachters long
    while (answer.size() != 5) {
        cout << "That is not a five letter word. \n Give me a five letter word: ";
        cin >> answer;
        cout << endl;
     }

    // prompt the first user to input how many guesses they would like the second user to get and save the value to the num_guess variable
    while (true) {
        cout << "How many guesses should the player get? ";
        string input;
        getline(cin, input);

        // Check if the input is empty (only a newline character)
        if (input.empty()) {
            continue;
        }

        // checks to make sure the number of guesses entered is a valid input (an integer)
        try {
            size_t pos;
            num_guess = stoi(input, &pos);

            if (pos != input.length()) {
                throw invalid_argument("Invalid input. Not an integer.");
            }

            break;
        } catch (const invalid_argument& e) {
            cout << "Number of guesses must be an integer. Try again: ";
        }
    }

    cout << endl;

    //printing 100 new lines to the console, clearing the screen
    for (int i = 0; i < 100; i++) {
        cout << endl;
    }
    
    //prints the games color code to the console
    cout << "Okay, now for the game! \n\033[38;2;0;0;0m This color in my response means that the letter is not in the word. \n\033[38;2;255;255;0m This color in my response means that the letter is in the word, but in the wrong position. \n\033[38;2;0;255;0m This color in my response means that the letter is in the word in its correct position." << endl;

    int correct_letters = 0;
    int guesses_left = num_guess;

    //keeps track of the number of guess compared to the total number allowed
    for (int i = 1; i <= num_guess; i++) {
        cout << " \033[m Guess " << i << "/" << num_guess << ": ";
        cin >> guess;
        cout << endl;

        //checks for a valid five letter input from the user 
        while (guess.size() != 5) {
            cout << "Your guess must be a five-letter word. Try again: ";
            cin >> guess;
            cout << endl;
        }

        //passing guess through the checkWord function
        checkWord(guess, answer);

        // Count the number of correct letters in the right spot (green letters)
        for (size_t j = 0; j < guess.length(); ++j) {
            if (guess[j] == answer[j]) {
                correct_letters++;
            }
        }

        // Check if all letters are correct (player wins)
        if (correct_letters == 5) {
            cout << "CONGRATULATIONS! YOU WIN!" << endl;
            break;
        }

        //updates the guesses_left variable 
        guesses_left--;

        // Check if the player ran out of guesses
        if (guesses_left == 0) {
            cout << "SORRY! BETTER LUCK NEXT TIME!" << endl;
            break;
        }

        // Reset the correct_letters count for the next guess
        correct_letters = 0;
    }

    return 0;
}
        