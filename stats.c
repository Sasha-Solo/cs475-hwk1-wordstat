/*
 * histo.c
 */

#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "stats.h"

// TODO: function definitions for dealing with histogram below

/**
 * @brief prints letters of alphabet for histogram
 */
void printLetters(){
    char alphabet[ALPHABET_SIZE] = {'a','b','c','d','e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for (int i=0; i < strlen(alphabet); i++){
        printf("%c ", alphabet[i]);
    }
    printf("\n");
}

/**
 * @brief fills histogram with zeros 
 * @param histogram holds character frequency data
 */
void fillStats(int histogram[]){
    for (int j=0; j < ALPHABET_SIZE;j++){
        histogram[j] = 0;
    }
}

/**
 * @brief updates and fills the histogram based on character frequency
 * @param histogram holds character frequency data
 * @param split holds words split on spaces
 */
void updateStats(char split[], int histogram[]){
	for (int k = 0; k < strlen(split); k++){
		int y = (int) split[k]; //gets ascii value of user input characters
		int x = y - 97; //get the 0th value of ascii
        histogram[x]++;
	}

    //find the max value
    int max = histogram[0]; //temporary max value
    for (int i = 1; i < ALPHABET_SIZE; i++){
        if (histogram[i] > max){
            max = histogram[i];
        }
    }

    //go through stats array and print out stars
    //for (int i = 0; i < ALPHABET_SIZE; i++){
        int i = 0;
        while(i != max){
        for (int j = 0; j < ALPHABET_SIZE; j++){
            if (histogram[j] <= max && histogram[j] >= (max-i)){ //if max value is found print out a star
                printf("* ");
            }
            else{
                printf("  ");
            }   
            if (j == ALPHABET_SIZE-1){ //move on to next row after end of row is reached
                printf("\n");
            }
        }
        i++;
   }

    //print stats
    for (int i=0; i < 26; i++){
        printf("%d ", histogram[i]);
    }

    printf("\n");
}

