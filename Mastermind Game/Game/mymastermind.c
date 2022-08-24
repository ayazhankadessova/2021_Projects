#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Convert string to an integer
long my_atoi(const char *S)
{
	long num = 0;

	int i = 0;
	while (S[i] && (S[i] >= '0' && S[i] <= '9'))
	{
		num = num * 10 + (S[i] - '0');
		i++;
	}

	return num;
}

//check if the secret code equals to the guess
int strequal(char arr[], char arr2[])
{
	int isequal = 1;
	int i = 0;

	while (arr[i] != '\0')
	{
		if (arr2[i] != arr[i])
		{
			isequal = 0;
		}
		i++;
	}
	return isequal;
}

//check misplaced and well-placed pieces
int contains(char arr[], char letter)
{
	int condition = 0;
	int i = 0;

	while (i < 4)
	{
		if (letter == arr[i])
		{
			condition = 1;
		}
		i++;
	}
	return condition;
}

//check the number of each piece in guess and code...
int numberof(char arr[], char number)
{
	int i = 0;
	int count = 0;
	while (arr[i] != '\0')
	{
		if (number == arr[i])
		{
			count++;
		}
		i++;
	}
	return count;
}

//to see if any pieces are repeated
int isDuplicate(char arr[])
{
	int conditiond = 1;
	for (int i = 0; i < 4; i++)
	{

		if (numberof(arr, arr[i]) > 1)
		{
			conditiond = 0;
		}
	}
	return conditiond;
}

//check if any pieces are non-integers through their ascii values
int isInteger(char arr[])
{
	int condition = 1;
	for (int i = 0; i < 4; i++)
	{
		int d = (int)arr[i];
		if ((d < 48) | (d > 55))
		{
			condition = 0;
		}
	}
	return condition;
}

//check if input is too long or shorts (needs to be exactly 4)

int isTooLong(char arr[])
{
	int conditionL = 1;
	if ((strlen(arr)) != 4)
	{
		conditionL = 0;
	}
	return conditionL;
}

//Generating a randon 4-digit number from 0 to 7
void assignRandom(char numbertoassign[])
{
	char n1 = rand() % 8 + '0';
	numbertoassign[0] = n1;
	char n2 = rand() % 8 + '0';
	char n3 = rand() % 8 + '0';
	char n4 = rand() % 8 + '0';
	while (numbertoassign[0] == n2)
	{
		n2 = rand() % 8 + '0'; // added '0' to make it a string
	}
	numbertoassign[1] = n2;

	while (contains(numbertoassign, n3) == 1)
	{
		n3 = rand() % 8 + '0';
	}
	numbertoassign[2] = n3;

	while (contains(numbertoassign, n4) == 1)
	{
		n4 = rand() % 8 + '0';
	}
	numbertoassign[3] = n4;

	numbertoassign[4] = '\0';
}

void mastermind(int trials, char *code) // trials given through -t command, code through -c command
{

	char num[5]; //Initializing the default secret code

	if (code[0] != '\0') // if the secret code was intered...
	{
		int i = 0;
		while (code[i] != '\0') //then make num = code
		{
			num[i] = code[i];
			i++;
		}
		if (isTooLong(num) == 0) // if the secret code format has a wrong format (too long)...
		{
			printf("\nWrong format! Assigning a random number... ");
			assignRandom(num); // assign a random number instead
		}
		if (isDuplicate(num) == 0) // if the secret code format has a wrong format (contains duplicates)...
		{
			printf("Function parameter code contains duplicate integers. Assigning a random number... ");
			assignRandom(num); // assign a random number instead
		}
		if (isInteger(num) == 0) // // if the secret code format has a wrong format (contains non-integers)...
		{
			printf("\nInput is not within the range. Assigning a random number... ");
			assignRandom(num); // assign a random number instead
		}
	}
	else
	{
		assignRandom(num);
	}
	num[4] = '\0';

	int turn = 0;		  // Initializing turns..
	int chances = trials; // and trials (10 is defaults, unless changed by the mastermind through -t command)

	printf("Will you find the secret code? Guess the 4 digit number: "); // Starting the game

	char guessarr[5];	   // Initializing guess code
	scanf("%s", guessarr); // Scanning the guess

	// Checking the format of the guess guess input
	// if wrong, asking to try again.
	// No turns are added for wrong inputs.
	while (isDuplicate(guessarr) == 0)
	{
		printf("\nDo not repeat the numbers. Try again: ");
		scanf("%s", guessarr);
	}
	while (isInteger(guessarr) == 0)
	{
		printf("\nOnly use integers from 0 to 7. Try again: ");
		scanf("%s", guessarr);
	}
	while (isTooLong(guessarr) == 0)
	{
		printf("\nTou number is either too long or short. Try again: ");
		scanf("%s", guessarr);
	}

	// While turn is less than the available number of chances,
	// the game is played
	while (turn < chances + 1)
	{
		turn += 1;
		printf("\nRound %d\n", turn);
		if (turn == chances)
		{
			printf("Game over!");
			break;
		}

		// if guess = secret code, the player wins, and the game ends.
		if (strequal(guessarr, num) == 1)
		{
			printf("Great! You guessed the number! You're a Mastermind!");
			break;
		}

		// else, the game is played, and turns are added
		else
		{
			//initializing well and misplaced
			int wellplaced = 0;
			int misplaced = 0;

			for (int i = 0; i < 4; i++)
			{
				// if the piece from guess is in the right position
				if (guessarr[i] == num[i])
				{

					wellplaced++;
				}
			}
			for (int i = 0; i < 4; i++)
			{
				// // if the piece from guess is present in the secret code, but in the wrong position
				if (guessarr[i] != num[i] && (contains(num, guessarr[i]) == 1))
				{
					misplaced++;
				}
			}
			// Print feedback, and ask for input for the next round
			if (wellplaced < 4)
			{
				printf("Your results are \nMisplaced: %d\nWell-Placed: %d\nReady for a new round? Guess again!", misplaced, wellplaced);
				scanf("%s", guessarr);
			}

			// If the input format is wrong, ask to try again, and scan the input, and check it again.
			for (int i = 0; i < 4; i++)
			{
				if (guessarr[i] == '\0')
				{
					printf("Do it again. But now use better numbers: ");
					scanf("%s", guessarr);
				}
			}
			while (isDuplicate(guessarr) == 0)
			{
				printf("Do not repeat the numbers. Try again: ");
				scanf("%s", guessarr);
			}
			while (isTooLong(guessarr) == 0)
			{
				printf("\nYour number is either too long or short. Try again: ");
				scanf("%s", guessarr);
			}
			while (isInteger(guessarr) == 0)
			{
				printf("\nOnly use integers from 0 to 7. Try again:  ");
				scanf("%s", guessarr);
			}
		}
	}
}

// Building the program
int main(int argc, char **argv)
{
	char *pcode = malloc(5); // allocate memory for code that will be written through -c
	int trials = 10;		 // Initializing trials to default 10
	for (int i = 1; i < argc; ++i)
	{
		if (contains(argv[i], 'c')) // // if -c ..., make the code in the next index the secret code
		{
			pcode = argv[i + 1];
		}
		if (contains(argv[i], 't')) // if -t ..., change default 10 trials to the specified amount in the net index
		{
			trials = my_atoi(argv[i + 1]); // convert string to integer
		}
	}
	srand(time(0));			   //set the starting point for producing a series of random integers
	mastermind(trials, pcode); // run the game with given trials and the code
}