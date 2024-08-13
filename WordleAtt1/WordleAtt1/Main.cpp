#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>

#include <chrono>
#include <thread>


#include <time.h>

using namespace std;

ifstream inFile;

void Dialogue1();

string Guess1();
string GuessN();
string GuessLast();

string GetWord(int RandVal);
void RandomNumberGen(int rows);
int MTRandomNumberGen(int rows);
int Comparison(string input);
int Validity(string inputarray, string inputword);

string Wordle;
string guess;
string inWords;

//int maxRows = 2000000;
//string* Data = new string[maxRows]; // Dynamically allocate memory on the heap
int stage = 1;
int check = 0;

enum STATE {
    ONE,
    TWO,
    THREE,
    FOUR, 
    FIVE,
    COMPLETE, 
    FAIL,
};

int main() {

    
    bool correct = false;

    Dialogue1();
    
    //Random word generator
    int Val = MTRandomNumberGen(6819);
    Wordle = GetWord(Val);
    cout << Wordle << endl;

    while (stage == 1) {
        string one = Guess1();
        Comparison(one);
    }
    while (stage == 2 && (check == 0)) {
        string two = GuessN();
        Comparison(two);
    }
    while (stage == 3 && (check == 0)) {
        string three = GuessN();
        Comparison(three);
    }
    while (stage == 4 && (check == 0)) {
        string four = GuessN();
        Comparison(four);
    }
    while (stage == 5 && (check == 0)) {
        string five = GuessLast();
        Comparison(five);
    }

    if (check == 1) {
        return 0;
    }
    if ((stage == 5) && (check == 0)) {
        cout << "No wind for you, restard to try again" << endl;
        return 0;
    }


    return 0;
}


void Dialogue1() {
    cout << "Welcome to Dyl's Wordle " << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "It's only for worrds beginning with 'A'" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Please do bear with" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Press ENTER to generate word" << endl;
}


string Guess1() {
    string guess1;
    cout << "Enter your First guess" << endl;
    cin >> guess1;

    return guess1;
}

string GuessN() {
    string guess1;
    cout << "Enter your next guess" << endl;
    cin >> guess1;

    return guess1;
}

string GuessLast() {
    string guess1;

    cout << "This is your last guess" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Choose wisely" << endl;
    cin >> guess1;
    
    return guess1;

}

void RandomNumberGen(int rows) {

    //Rand Way
    const int s = time(0); //Setting the seed, Initialises the sequence of random numbers
    srand(s);  //Sets the seed
    for (int i = 0; i < 20; i++) {
        cout << rand() % rows << endl;
    }

}

int MTRandomNumberGen(int rows) {
    const int s = time(0);
    int N;

    mt19937 mtrand(s);

    N = mtrand() % rows;
    cout << N << endl;

    return N;

} 

string GetWord(int RandVal) {

   
    string outWord;
    string line = "";
    int row = 0;
    string* data = new string[10000];

    inFile.open("AZRefined.csv");
    if (inFile.is_open()) {
        cout << "File Opened, good day" << endl;
    }
    else {
        cout << "NO FILE OPENED" << endl;
    }

    while (getline(inFile, line)) {
        stringstream inputString(line);

        getline(inputString, inWords, ' ');
        if (row < 10000) {
            data[row] = inWords;
            row++;
        }
        else {
            cout << "Warning: Data array size exceeded, some lines were ignored." << endl;
            break;
        }
    }
    //delete[] data;
    inFile.close();

    outWord = data[RandVal];
    return outWord;
}

int Comparison(string input) {
    char storage[5] = { '_', '_', '_', '_', '_' };

    //Validity
    if (input.length() != 5) {
        cout << "Word is not 5 letters, enter again" << endl;
        stage = stage;
        return 0;
    }
    /*else if (Validity(inWords, input) == 1) {
        cout << "Word not in database" << endl;
        stage = stage;
        return;
    } */
    else {
        stage++;
    }
    //Function to check it's a real word.


    //Same Letter, Same Place
    for (int i = 0; i < 5; i++) {
        if (input[i] == Wordle[i]) {
            storage[i] = input[i];
        }
        cout << storage[i];
    }
    cout << endl;

    //Same letter, Different place
    bool foundDifferentPlace = false;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i != j && input[i] == Wordle[j]) {
                cout << input[i];
                foundDifferentPlace = true;
                break;
            }
        }
    }

    if (foundDifferentPlace) {
        cout << " -- Matching letters in different places" << endl;
    }

    if (!foundDifferentPlace) {
        cout << "No matching letters in different places" << endl;
    }

    if (Wordle == input) {
        check = 1;
        cout << "Congrats you've got the Word!!!" << endl;
        return 1;
    }
    
    return 2;
}

int Validity(string inputarray, string inputword) {
    if (inputarray.empty()) {
        cout << "ERROR: input array not read" << endl;
    }
    else {
        cout << "inWords read" << endl;
    }

    for (int i = 0; i <= inputarray.length() - inputword.length(); i++) {
        if (inputarray.substr(i, inputword.length()) == inputword) {
            cout << "Input word found: " << inputword << endl;
            return 0; // Word found
        }
    }
    
    return 1;


}