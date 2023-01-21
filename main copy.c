/*
 * main.c
 *
 *  Created on: Jun 15, 2015
 *      Author: dchiu
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "defs.h"
#include "stats.h"
#include "menu.h"

/**
* @brief allows user to input more strings
* @param newStrings array and strings array for user input
* @return char
*/
char stringGetter(char newStrings[], char strings[]){
	while (strncmp(strings, "#", 1) != 0){ //while user did not type #...
		fgets(strings, MAX_INPUT_LEN, stdin); //get the strings
		strcat(newStrings, strings); //copy what is in strings into an array newStrings
	}

	//if strings is between the correct ASCII values, put them into newStrings (ignore non-number chars)
	int x = 0;
	printf("length is %ld", strlen(newStrings));
	for (int i = 0; i < strlen(newStrings); i++){ //go through and cast each char
		x = (int) newStrings[i]; //cast char into an int

		printf("x = %d\n", x);

		if ((x >= 36 && x <= 64) || (x >= 91 && x <= 96) || (x >= 123 && x <= 127) || x == 33 || x == 34){ //if chars are not upper or lowercase letters...
			printf("i = %d\n", i);
			newStrings[i] = '\0'; //change non-numbers to null characters
		}
	}
	
	printf("\nstrings array AFTER method call: %s\n", strings);
	printf("\nnewStrings array AFTER method call: %s\n", newStrings);

	char result = '#';
	return result;
}

/**
 * @brief Main function
 *
 * @param argc Ignore
 * @param argv Ignore
 * @return int
 */

int main(int argc, char *argv[]) {
	// declare and initialize the histogram
	//int histogram[ALPHABET_SIZE];

	// TODO: start by getting strings from users until # is input

	char strings[MAX_INPUT_LEN]; //array to store line of user input
	char newStrings[MAX_INPUT_LEN]; //new array to hold total strings of user input
	char split[MAX_INPUT_LEN]; //array to hold strings split on spaces
	//char copy[MAX_INPUT_LEN]; //temp array to reset newStrings 
	int stats[27]; //array for histogram stats
	fillStats(stats); //fills stats with 0s

	char *token;

	printf("Please enter some strings: "); //prompts user for strings
	while (strncmp(strings, "#", 1) != 0){ //while user did not type #...
		fgets(strings, MAX_INPUT_LEN, stdin); //get the strings
		strcat(newStrings, strings); //copy what is in strings into an array newStrings
	}

	//get non-number characters out of newStrings
	int x = 0;
	printf("length is %ld", strlen(newStrings));
	for (int i = 0; i < strlen(newStrings); i++){ //go through and cast each char
		x = (int) newStrings[i]; //cast char into an int
		//if chars are not upper or lowercase letters...
		if ((x >= 36 && x <= 64) || (x >= 91 && x <= 96) || (x >= 123 && x <= 127) || x == 33 || x == 34){ 
			printf("i = %d\n", i);
			newStrings[i] = '\0'; //change non-numbers to null characters
		}
	}

	//make sure there are no uppercase chars in split
	for (int i = 0; i < strlen(split); i++){
		if (split[i] >= 'A' && split[i] <= 'Z'){ //if the char is uppercase...
			split[i] += 32; //convert to lowercase
		}
	}

	// //puts chars of newStrings into copy array
	// for (int w = 0; w < strlen(newStrings); w++){
	// 	copy[w] = newStrings[w];
	// }

	token = strtok(newStrings, "# \n"); //want to split newStrings based on spaces, enter, #
	while (token != NULL){
		strcat(split, token); //take tokens and put them into a new array without spaces
		token = strtok(NULL, "# \n");
	}

	for (int w = 0; w < strlen(split); w++){
		printf("%c", split[w])
	}

	// //put back the original values of newStrings
	// for (int w = 0; w < strlen(copy); w++){
	// 	newStrings[w] = copy[w];
	// }

	//TODO: after # is input, print menu options
	int opt = getMenuOption(); //gets the user's option

	while (opt != 4){ //while user has not quit...
		if (opt < 1 || opt > 4){ //if option is out of bounds print unknown
			printf("Unknown option %d\n", opt);
		}
		if (opt == 1){ //vowels and consonants
			int vCount = 0; //counter to keep track of vowels
			for (int i = 0; i < strlen(split); i++){ //checks a, e, o, u, i
				if (split[i] == 'a' || split[i] == 'A'){
					vCount++;
				}
				if (split[i] == 'o' || split[i] == 'O'){
					vCount++;
				}
				if (split[i] == 'e' || split[i] == 'E'){
					vCount++;
				}
				if (split[i] == 'u' || split[i] == 'U'){
					vCount++;
				}
				if (split[i] == 'i' || split[i] == 'I'){
					vCount++;
				}
			}

			double total = strlen(split); //total number of characters
			double vowels = vCount/total; //number of vowels
			vowels = vowels * 100; //vowels changed into percent form
			int consonants = total - vCount; //number of consonants
			double consPer = (consonants/total) * 100; //consonants as a percent
		
			printf("\nVowels = %d (%0.2lf %%), Consonants = %d (%0.2lf %%), Total = %.2f\n", vCount, vowels, consonants, consPer, total);
		}
		if (opt == 2){ //
		
			//TEST
			printf("newStrings:");
			for (int i=0; i < strlen(newStrings); i++){
        		printf("%c", newStrings[i]);
    		}
			printf("\n");

			printf("split:");
			for (int i=0; i < strlen(split); i++){
        		printf("%c", split[i]);
    		}
			printf("\n");

			printf("\n");
			printLetters(); //prints alphabet 
			updateStats(split, stats);

			for (int i = 0; i < strlen(split); i++){
				split[i] = '\0'; //clear split
			}

			printf("split:");
			for (int i=0; i < strlen(split); i++){
        		printf("%c", split[i]);
    		}
			printf("\n");
		}
		if (opt == 3){ //more strings

			// printf("\nstrings array BEFORE method call: %s\n", strings);
			// printf("\nnewStrings array BEFORE method call: %s\n", newStrings);

			printf("Please enter some more strings: "); //prompts user for strings
			strings[0] = ' '; //set strings back to empty

			
			// //char result = stringGetter(newStrings, strings);
			// if (result == '#'){
			// 	//need to clear original split array to have an updated version of the user's input
			// 	for (int q = 0; q < strlen(split);q++){
			// 		split[q] = '\0'; //fill split with null operator to clear
			// 	}
			// }
		}
		
		opt = getMenuOption(); //print the option menu until 5 is pressed
	}

	printf("Exiting...\n");
	return 0;
}
