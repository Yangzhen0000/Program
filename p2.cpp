//21 points.cpp
//A game to get a larger number less than 21 between player and computer
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

void shuffleCard(int array1[], int array2[], int array3[]);                         //initialize the card, user's cards and computer's cards
double dealCard(int array[],int card[], int i);                                     //give one card at random per time to user or computer
void displayCard(int array[]);                                                      //display the card with number and type
double userTime(int user_card[], int card[]);                                       //the stages for user to play
double computerTime(int computer_card[], int card[], int user_card[], double u_sum);//the stages for computer to play
void judgeResult(int sum1, int sum2, int user_card[], int computer_card[]);         //judge the result when two paticipants' number are both less than 21

int main()
{
	int card[52] = {0}, user_card[20] = {0}, computer_card[20] = {0};
	double u_sum, c_sum;
	char choice;
	
	do{
		shuffleCard(card, user_card, computer_card);                                
		u_sum = userTime(user_card, card);
		if(u_sum != 0){                                                             //do the computer stage when player did not lose
			c_sum = computerTime(computer_card, card, user_card, u_sum);            //do the compare stage when the computer did not lose or win
			if(c_sum != 0)	judgeResult(u_sum, c_sum, user_card, computer_card);
		}
		cout << "\nDo you want to play again?(y/n)" << endl;
		cin >> choice;
		
		while(true){
			try{if(choice != 'y' && choice != 'n')    throw 1;                      //judge whether the input is legal
			    else throw 0.5;
			}
			catch(int){
				cout << "Your input is ilegal! Please input y/n: ";
				cin >> choice;
			}
			catch(double){
				break;
			}
	    }
	}while(choice == 'y');
	return 0;
}

void shuffleCard(int array1[], int array2[], int array3[])                           //initialize the card, user's card and computer's card
{
	for(int i = 0; i < 52; ++i)    array1[i] = i + 1;
	for(int i = 0; array2[i] != 0; ++i)    array2[i] = 0;
	for(int i = 0; array3[i] != 0; ++i)    array3[i] = 0;
}

double dealCard(int array[],int card[],int i)                                        //deal the card
{
	srand(time(NULL));
	int card_num;
	
	do{
	card_num = rand() % 52;
	}while(card[card_num] == 0);
	array[i] = card_num + 1;
	card[card_num] = 0;
    switch(array[i] % 13){                                                           //transform card number into concrete score
		case 0:   
		case 11:   
		case 12:    return 0.5;    
		default:    return array[i] % 13;  
	}
}

void displayCard(int array[])                                                         //transform card index into type and number
{   
	int i = 0;
    while(true){
    	switch(array[i] / 13){
    	    case 0: cout << "spade ";    break; 
    		case 1: cout << "heart ";    break;
    		case 2: cout << "club " ;    break;
    		default: cout << "diamond ";    break;
		}
		switch(array[i] % 13){
			case 1:    cout << "A  ";    break;
			case 0:    cout << "K  ";    break;
			case 11:    cout << "J  ";    break;
			case 12:    cout << "Q  ";    break;
			default:    cout << array[i] % 13 << "  " ; 
		}
		++i;
		if(array[i] == 0)	break;
	}
	cout << endl;			
}

double userTime(int user_card[], int card[])                                            //played by user and calculate the sum
{   
    char choice;
    double u_sum = 0;
    int i=2;
	u_sum += dealCard(user_card, card, 0);
    u_sum += dealCard(user_card, card, 1);
	cout << "Player get the card: " ;
	displayCard(user_card);
	
	do{
	    cout << "Do you want one more card?(y/n) ";
	    cin >> choice;
		while(true){
			try{
			    if(choice != 'y' && choice != 'n')    throw 1;
			    else throw 0.5;
			}
			catch(int){
				cout << "Your input is ilegal! Please input y/n: ";
				cin >> choice;
			}
			catch(double){
				break;
			}
		    } 
	    if(choice == 'y'){
		    u_sum += dealCard(user_card, card, i);
		    cout << "Player get the card: ";
			displayCard(user_card);
		}
		else break;
	    ++i;
	}while(u_sum <= 21);
	if(u_sum > 21){
	    cout << "The player lose!";
	    return 0;
	}
	else return u_sum;
}

double computerTime(int computer_card[], int card[], int user_card[], double u_sum)    //played by computer and calculate the sum
{
	double c_sum = 0;
	int i = 2;

	cout << "It's the computer's time.\nComputer get the card: ";
	c_sum = dealCard(computer_card, card, 0);    
	c_sum += dealCard(computer_card, card, 1);
	displayCard(computer_card);
	while(c_sum < u_sum ){
		cout << "Get one more card: ";
		c_sum += dealCard(computer_card, card, i);
		displayCard(computer_card);
		if(c_sum > 21){
		    cout << "The player win!";
		    return 0;
	    }
		++i;	
	}
	return c_sum;
}

void judgeResult(int sum1,int sum2, int user_card[], int computer_card[])                  //decide which one is the winner by score and number of cards
{
	int u_num = 0, c_num = 0;
	if(sum2 > sum1)    cout << "The computer win!";
	else{
	    for(int i = 0; user_card[i] > 0; ++i)    ++u_num;
	    for(int i = 0; computer_card[i] > 0; ++i)    ++c_num;
	    if(u_num > c_num)    cout << "The player win!";
	    else{
		    if (u_num < c_num )cout << "The computer win!";
	        else cout << "You and the computer both win!";
	    }
	}
}






