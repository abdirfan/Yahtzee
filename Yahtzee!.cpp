/****************************
 * HEADER
 * Class: CS 141
 * Name: Abdullah Irfan
 * Project # 5: Yahtzee!
 * Starter code provided by: Dr. Sara Riazi
 * ***************************/


#include <string>
#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <iomanip>

using namespace std;

//#################################################################################################

void test_case();

class Dice {
private:
	int value;
	bool grabDice;

public:

	//Randomly assigns a value between from 1 to 6 to the dice.
	void roll();
	void keepDice();                                    
	void loseDice();
	bool isDiceRollable();
	int reveal() { return value; }

	//The autograder will set the values directly instead of calling roll() to avoid randomness!
	void setValue(int value) { this->value = value; }

};

void Dice::keepDice() {            //this function will drop or select depending on whether grabDice is true or false 
	this->grabDice = true;
}
void Dice::loseDice() {
	this->grabDice = false;
}

void Dice::roll() {                  //this function is going to roll the dice for upt value 6
	this->value = rand()%6+1;
}
bool Dice::isDiceRollable() {        //checking to see if dice is rollable or not 
	return !this->grabDice;
}
//#################################################################################################

const int HAND_SIZE = 5;

class Hand {
public:

	//Display the value of the five dice
	void show();
	void play();
Dice* getDice(int diceNum);

	//selection is the string of dice numbers that the player wants to keep.
	//For example, "125" means that player wants to keep the first, second, and fifth dice, and roll the rest.
	void setSelection(string selection);

	Hand();

private:
	Dice dice[HAND_SIZE];
};

Dice* Hand::getDice(int diceNum) {
	return &dice[diceNum];
}

Hand :: Hand() {                                     //rolling the dice and losing 
	for (int i = 0;i < HAND_SIZE; i++) { 
		dice[i].roll();
		dice[i].loseDice();
	}

}
void Hand::setSelection(string selection) {           //selects the dices that user ask to select for second chance 
	for (int i = 0; i < selection.size();i++) {
		int dice_id = selection[i] - '0' - 1;
		if (dice_id >= HAND_SIZE) {
			continue;
		}
		dice[dice_id].keepDice();
	}
}
void Hand::show() {                                  //displays the hand function
	cout << "Hand: ";
	for (int i = 0;i < HAND_SIZE; i++) {
		cout << dice[i].reveal() << " ";
	}
	cout << endl;

}
void Hand::play() {                                   //if dice is rollable then it rolls the dice otherwise gets rid of it
	for (int i = 0;i < HAND_SIZE; i++) {              //with the loseDice function
		if (dice[i].isDiceRollable()) {
			dice[i].roll();
		}
		dice[i].loseDice();

		
	}

}
//######################################################################

//List of rows in the board
const int ONES = 0;
const int TWOS = 1;
const int THREES = 2;
const int FOURS = 3;
const int FIVES = 4;
const int SIXES = 5;
const int THREE_OF_KIND = 6;
const int FOUR_OF_KIND = 7;
const int FULL_HOUSE = 8;
const int SMALL_STRAIGHT = 9;
const int LARGE_STRAIGHT = 10;
const int CHANCE = 11;
const int YAHTZEE = 12;

const int BOARD_SIZE = 13;

class Game {

public:
	//calcScore returns a score of a hand (5 dice) for given row in the board. 
	//Note the rows are indexed from zero. 
	//For example if the hand is 2 1 1 5 1 then calcScore(hand, ONES) returns 3 and  calcScore(hand, TWOS) returns 2.
	int calcScore(Hand* hand, int row);


	//Display the board
	void show();


	//Returns the score of the upper part of the board
	int getUpperScore();

	//Returns the score of the lower part of the board
	int getLowerScore();


	//Returns the bonus points
	int getBonusScore();

	//Returns the total score
	int getTotalScore();

	//Play a hand based on the selected row
	void play(Hand* hand, int row);


	//Check to see if a row has been played or not (returns true if a row has been played)
	bool isPlayed(int row);

	
	//Check to see if all rows haven been played or not (returns true if all rows have been played)
	bool isFinished();

	
	void setScore(int row, int scoreValue) {      //sets the score 
		score[row] = scoreValue;
		played[row] = true;
	}
	
	Game();

	int getScore(int row);

private:
	int score[BOARD_SIZE];
	bool played[BOARD_SIZE];
};

Game::Game() {
	for (int i = 0; i < BOARD_SIZE; i++) {   
		score[i] = 0;
		played[i] = false;
	}
}

int Game::getScore(int row) {        //returns the score in the specifie row
	return score[row];
}

bool Game::isFinished() {           //isFinished is checking to see if the game has finshed running 
	bool playedOrNot = true;
	for (int i = 0; i < BOARD_SIZE&&playedOrNot; i++) {
		playedOrNot = played[i] && playedOrNot;
	}
	return playedOrNot;
}
int Game::getUpperScore() {        //sums all the upper level scores 
	return score[ONES] + score[TWOS] + score[THREES] + score[FOURS] + score[FIVES] + score[SIXES];
}
int Game::getBonusScore() {       //adds bonus of 35 points to the total if upper score is greater than 63
	int bonus = 0;
	int currentScore = getUpperScore();
	if (currentScore >= 63) {
		bonus = 35;
	}
	return bonus;
}
int Game::getLowerScore() {       //sums all the lower level scores 
	return score[THREE_OF_KIND] + score[FOUR_OF_KIND] + score[FULL_HOUSE] + score[SMALL_STRAIGHT] + score[LARGE_STRAIGHT] + score[CHANCE] + score[YAHTZEE];
}
int Game::getTotalScore() {
	return getBonusScore() + getLowerScore() + getUpperScore();
}
void Game::show() {               //this function is alligning the output and creating aligned columns and and rows 
	cout << left << setw(25) << "1. Ones: ";
	if (played[ONES]) {
		cout << score[ONES]<<endl;
	}
	else {
		cout << "_"<<endl;
	}

	cout << setw(25) << "2. Twos: ";
	if (played[TWOS]) {
		cout << score[TWOS] << endl;
	}
	else {
		cout << "_" << endl;
	}

	cout << setw(25) << "3. Threes: ";
	if (played[THREES]) {
		cout << score[THREES] << endl;
	}
	else {
		cout << "_" << endl;
	}

	cout << setw(25) << "4. Fours: ";
	if (played[FOURS]) {
		cout << score[FOURS] << endl;
	}
	else {
		cout << "_" << endl;
	}

	cout << setw(25) << "5. Fives: ";
	if (played[FIVES]) {
		cout << score[FIVES] << endl;
	}
	else {
		cout << "_" << endl;
	}
	cout << setw(25) << "6. Sixes: ";
	if (played[SIXES]) {
		cout << score[SIXES] << endl;
	}
	else {
		cout << "_" << endl;
	}
	
	cout << setw(25) << "  Sum: " <<  getUpperScore() << endl;

	cout << setw(25) << "  Bonus: " << getBonusScore() << endl;
	
	cout << setw(25) << "7. Three of a kind: ";
	if (played[THREE_OF_KIND]) {
		cout << score[THREE_OF_KIND] << endl;
	}
	else {
		cout << "_" << endl;
	}

	cout << setw(25) << "8. Four of a kind: ";
	if (played[FOUR_OF_KIND]) {
		cout << score[FOUR_OF_KIND] << endl;
	}
	else {
		cout << "_" << endl;
	}

	cout << setw(25) << "9. Full House: ";
	if (played[FULL_HOUSE]) {
		cout << score[FULL_HOUSE] << endl;
	}
	else {
		cout << "_" << endl;
	}

	cout << setw(25) << "10. Small Straight: ";
	if (played[SMALL_STRAIGHT]) {
		cout << score[SMALL_STRAIGHT] << endl;
	}
	else {
		cout << "_" << endl;
	}

	cout << setw(25) << "11. Large Straight: ";
	if (played[LARGE_STRAIGHT]) {
		cout << score[LARGE_STRAIGHT] << endl;
	}
	else {
		cout << "_" << endl;
	}

	cout << setw(25) << "12. Chance: ";
	if (played[CHANCE]) {
		cout << score[CHANCE] << endl;
	}
	else {
		cout << "_" << endl;
	}

	cout << setw(25) << "13. Yahtzee: ";
	if (played[YAHTZEE]) {
		cout << score[YAHTZEE] << endl;
	}
	else {
		cout << "_" << endl;
	}

	cout << setw(15) << "Total: " << getTotalScore() << endl;

}

int Game::calcScore(Hand* hand, int row) {         //main function of the program calulates the dice value and assigns it to 
	int scoreSum = 0;    //calculate sum           //the respective row
	int value = 0;       //calculating score value
	int diceCount[6];    //setting dice size in array

	for (int i = 0; i < 6; i++) {
		diceCount[i] = 0;
	}

	bool gotTwoOfKind = false;
	bool gotThreeOfKind = false;
	bool gotFourOfKind = false;
	bool gotFullHouse = false;
	bool gotYahtzee = false;
	bool gotSmallStraight = false;
	bool gotLargeStraight = false;

	bool gotOne = false;
	bool gotTwo = false;
	bool gotThree = false;
	bool gotFour = false;
	bool gotFive = false;
	bool gotSix = false;
	
	for (int i = 0; i < HAND_SIZE; i++) {
		int diceValue = hand->getDice(i)->reveal();
		scoreSum += diceValue;
		diceCount[diceValue - 1]++;
		switch (diceValue) {
			case 1: gotOne = true;
					break;
			case 2: gotTwo = true;
					break;
			case 3: gotThree = true;
					break;
			case 4: gotFour = true;
					break;
			case 5: gotFive = true;
					break;
			case 6: gotSix = true;
					break;
		}
	}

	for (int i = 0;i < 6;i++) {
		if (diceCount[i] == 2) {
			gotTwoOfKind = true;
		}
		else if (diceCount[i] == 3) {
			gotThreeOfKind = true;
		}
		else if (diceCount[i] == 4) {
			gotFourOfKind = true;
		}
		else if (diceCount[i] == 5) {
			gotYahtzee = true;
		}
	}

	if (gotTwoOfKind && gotThreeOfKind) {
		gotFullHouse = true;
	}
	if (gotOne && gotTwo && gotThree && gotFour) {
		gotSmallStraight = true;
		if (gotFive) {
			gotLargeStraight = true;
		}
	}
	if (gotTwo && gotThree && gotFour && gotFive) {
		gotSmallStraight = true;
		if (gotSix||gotOne) {
			gotLargeStraight = true;
		}
	}
	if (gotThree && gotFour && gotFive && gotSix) {
		gotSmallStraight = true;
		if (gotTwo) {
			gotLargeStraight = true;
		}
	}

	switch (row) {
		case ONES:
		case TWOS:
		case THREES:
		case FOURS:
		case FIVES:
		case SIXES:
			value = diceCount[row] * (row + 1);
			break;
		case THREE_OF_KIND:
			if (gotThreeOfKind || gotFourOfKind || gotYahtzee) {
				value = scoreSum;
			}
			break;
		case FOUR_OF_KIND:
			if (gotFourOfKind || gotYahtzee) {
				value = scoreSum;
			}
			break;
		case FULL_HOUSE: 
			if (gotFullHouse || gotYahtzee) {
				value = 25;
			}
			break;
		case SMALL_STRAIGHT:
			if (gotSmallStraight) {
				value = 30;
			}
			break;
		case LARGE_STRAIGHT:
			if (gotLargeStraight) {
				value = 40;
			}
			break;
		case CHANCE:
			value = scoreSum;
			break;
		case YAHTZEE:
			if (gotYahtzee) {
				value = 50;
			}
			break;
	}
	return value;
}
                                            
bool Game::isPlayed(int row) {   
	return played[row];
}
void Game:: play(Hand* hand, int row) {      //sets current score to the calculated new score
	int currScore = calcScore(hand,row);
	setScore(row, currScore);
}

//#######################################################################################

//The run function is the main loop of your program
void run() {
	Game game;
	Hand* hand = new Hand();
	string selection;
	int row;

	game.show();
	while (!game.isFinished()) {
		hand->play();
		for (int i = 0; i < 2; i++) {            //running tow give the player total of three two additional tries to roll the dice
			hand->show();
			cout << "Keep Dice(s to stop rolling): ";
			cin >> selection;
			if (selection == "s") {
				break;
			}
			hand->setSelection(selection);
			hand->play();
		}
		game.show();
		hand->show();
		cout << "Select a combination to play: ";
		cin >> row;                             //gets the user input for which row they want to play
		while (game.isPlayed(row - 1) || row>BOARD_SIZE) {
			if (row > BOARD_SIZE) {
				cout << "Select rows between 1-13";
			}
			else {
				cout << "This combination has been played. Select another one: ";
			}

		}
		game.play(hand, row - 1);
		game.show();
	}
}


//For these types of programs there exists many combinations that you might have missed. 
//The best way to check them all is to write test cases for your program. 
//Here I give you an example of checking large straight. You can design your own test cases for different parts.

void test_case() {
	Game game;
	Hand* hand = new Hand();
	hand->getDice(0)->setValue(1);
	hand->getDice(1)->setValue(2);
	hand->getDice(2)->setValue(3);
	hand->getDice(3)->setValue(4);
	hand->getDice(4)->setValue(5);

	bool check1 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 40) {
		check1 = false;
	}
	if (check1) {
		cout << "check 1 passed\n";
	}

	hand->getDice(0)->setValue(2);
	hand->getDice(1)->setValue(6);
	hand->getDice(2)->setValue(4);
	hand->getDice(3)->setValue(3);
	hand->getDice(4)->setValue(5);

	bool check2 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 40) {
		check2 = false;
	}

	if (check2) {
		cout << "check 2 passed\n";
	}

	hand->getDice(0)->setValue(3);
	hand->getDice(1)->setValue(2);
	hand->getDice(2)->setValue(5);
	hand->getDice(3)->setValue(6);
	hand->getDice(4)->setValue(3);

	bool check3 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 0) {
		check3 = false;
	}

	if (check3) {
		cout << "check 3 passed\n";
	}

	hand->getDice(0)->setValue(1);
	hand->getDice(1)->setValue(2);
	hand->getDice(2)->setValue(3);
	hand->getDice(3)->setValue(4);
	hand->getDice(4)->setValue(6);

	bool check4 = true;
	if (game.calcScore(hand, SMALL_STRAIGHT) != 0) {
		check4 = false;
	}

	if (check4) {
		cout << "check 4 passed\n";
	}


}

// THE AUTOGRADER WILL REPLACE THE MAIN FUNCTION. 
// DO NOT ADD ANY LOGIC OF YOUR PROGRAM HERE.
int main() {

	srand(time(0));
	run();
	//test_case();
	return 0;
}
