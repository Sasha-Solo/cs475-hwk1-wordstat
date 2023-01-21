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
 * @brief Main function
 *
 * @param argc Ignore
 * @param argv Ignore
 * @return int
 */

int main(int argc, char *argv[]) {
	// declare and initialize the histogram
	int histogram[ALPHABET_SIZE];

	// TODO: start by getting strings from users until # is input

	char strings[MAX_INPUT_LEN]; //array to store line of user input
	char newStrings[MAX_INPUT_LEN]; //new array to hold total strings of user input
	char split[MAX_INPUT_LEN]; //array to hold strings split on spaces
	fillStats(histogram); //fills stats with 0s

	char *token;

	printf("Please enter some strings: "); //prompts user for strings
	while (strncmp(strings, "#", 1) != 0){ //while user did not type #...
		fgets(strings, MAX_INPUT_LEN, stdin); //get the strings
		strcat(newStrings, strings); //copy what is in strings into an array newStrings
	}

	//get non-number characters out of newStrings
	int x = 0;
	for (int i = 0; i < strlen(newStrings); i++){ //go through and cast each char
		x = (int) newStrings[i]; //cast char into an int
		//if chars are not upper or lowercase letters...
		if ((x >= 36 && x <= 64) || (x >= 91 && x <= 96) || (x >= 123 && x <= 127) || x == 33 || x == 34){ 
			newStrings[i] = '\0'; //change non-numbers to null characters
		}
	}

	//make sure there are no uppercase chars in split
	for (int i = 0; i < strlen(newStrings); i++){
		if (newStrings[i] >= 'A' && newStrings[i] <= 'Z'){ //if the char is uppercase...
			newStrings[i] += 32; //convert to lowercase
		}
	}

	token = strtok(newStrings, "# \n"); //want to split newStrings based on spaces, enter, #
	while (token != NULL){
		strcat(split, token); //take tokens and put them into a new array without spaces
		token = strtok(NULL, "# \n");
	}

	//clear newStrings and fill with split
	for(int i = 0; i < strlen(newStrings); i++){
		newStrings[i] = '\0';
	}
	strcat(newStrings, split);

	//TODO: after # is input, print menu options
	int opt = getMenuOption(); //gets the user's option
	
	while (opt != 4){ //while user has not quit...
		if (opt < 1 || opt > 4){ //if option is out of bounds print unknown
			printf("Unknown option %d\n", opt);
		}
		if (opt == 1){ //vowels and consonants
			int vCount = 0; //counter to keep track of vowels
			for (int i = 0; i < strlen(split); i++){ //checks a, e, o, u, i
				if (split[i] == 'a'){
					vCount++;
				}
				if (split[i] == 'o'){
					vCount++;
				}
				if (split[i] == 'e'){
					vCount++;
				}
				if (split[i] == 'u'){
					vCount++;
				}
				if (split[i] == 'i'){
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
		if (opt == 2){ //histogram
	
			printf("newStrings = %s\n", newStrings);
			printf("strings = %s\n", strings);
			printf("split = %s\n", split);

			printf("\n"); 
			updateStats(split, histogram); //updates the char frequency 
			printLetters(); //prints alphabet
			//and returns the max freq value


			for (int i = 0; i < strlen(split); i++){
				split[i] = '\0'; //clear split
			}

			//set histo to 0
			for (int i = 0; i < ALPHABET_SIZE; i++){
				histogram[i] = '\0'; //clear stats
			}

		}

		if (opt == 3){ //more strings
			printf("Please enter some more strings: "); //prompts user for strings
			strings[0] = ' '; //set strings back to empty

			while (strncmp(strings, "#", 1) != 0){ //while user did not type #...
				fgets(strings, MAX_INPUT_LEN, stdin); //get the strings
				strcat(newStrings, strings); //copy what is in strings into an array newStrings
			}

			//get non-number characters out of newStrings
			int x = 0;
			//printf("length is %ld", strlen(newStrings));
			for (int i = 0; i < strlen(newStrings); i++){ //go through and cast each char
				x = (int) newStrings[i]; //cast char into an int
				//if chars are not upper or lowercase letters...
				if ((x >= 36 && x <= 64) || (x >= 91 && x <= 96) || (x >= 123 && x <= 127) || x == 33 || x == 34){ 
					newStrings[i] = '\0'; //change non-numbers to null characters
				}
			}

			//clear split to have an updated version of the user's input
			for (int q = 0; q < strlen(split);q++){
				split[q] = '\0'; //fill split with null operator to clear
			}

			token = strtok(newStrings, "# \n"); //want to split newStrings based on spaces, enter, #
			while (token != NULL){
				strcat(split, token); //take tokens and put them into a new array without spaces
				token = strtok(NULL, "# \n");
			}

			//put split into newStrings
			//clear newStrings
			for (int w = 0; w < strlen(newStrings); w++){
				newStrings[w] = '\0';
			}
			strcat(newStrings, split);

			//make sure there are no uppercase chars in split
			for (int i = 0; i < strlen(split); i++){
				if (split[i] >= 'A' && split[i] <= 'Z'){ //if the char is uppercase...
				split[i] += 32; //convert to lowercase
				}
			}
		}
		
		opt = getMenuOption(); //print the option menu until 5 is pressed
	}

	printf("Exiting...\n");
	return 0;
}
