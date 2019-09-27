//
//  FavoriteClasses.c
//  FavoriteClasses
//
//  Created by William Deniro on 9/27/19.
//  Copyright © 2019 William Deniro. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include "FavoriteClasses.h"

int main(void)
{
	/*Variables for the program*/
	char **listOfcourses;
	char ***listOfFavorites;	
	int numOfcourses;
	int favNum;
	int answer;
	int a;

	/*Asks the user for the amount of course titles*/
	printf("How many course do you plan to enter? \n");
	scanf("%d", &numOfcourses);
	
	/*Pass the array for courses titles and the number of courses to the function*/
	bookList(&listOfcourses, numOfcourses);

	/*Asks the user how many courses will be on the favorites list */
	printf("Of those %d course, how many do you plan to put on your favorites list ?", numOfcourses);
	scanf("%d", &favNum); 
	

	/*passes the Array of course names, List of favorites, number of course and length of favorites list*/
	favoriteList(&listOfcourses, &listOfFavorites, numOfcourses, favNum);
	
	/*askes the user if they want to save to a file */
	printf("Do you want to save them (1=yes, 2=no): ");
	scanf("%d", &answer);

	/*if the users answers yes then the variables are passed to the writeToFile Function */
	if(answer == 1){
		writeToFile(listOfcourses,&listOfFavorites,numOfcourses,favNum);
	}
	/*Frees the allocated Memory */
	if(listOfcourses != NULL){
	for(a = 0; a < numOfcourses; a++){
	 free(*(listOfcourses + a));
	}
	free(listOfcourses);
	}

	free(listOfFavorites);
}


	
void courseList(char*** listOfcourses, int numbers){

	/*A function that populates the List of course titles*/
	/*Declared variables */
	int i;
	char *temp;
	int count;	
	/*Allocated Memory for the course Array */
	*listOfcourses = malloc(numbers * sizeof(char*));
	if(*listOfcourses != NULL){
	/*Allocates memory for each book title and asks the user for the titles one by one*/
	for( i = 0; i<books; i++){
		*(*listOfcourse + i) = malloc(61*sizeof(char));
		printf("Enter the %d course titles one to a line \n", numbers);
		scanf(" %61[^\n]", *(*listOfcourse + i));
	}

	/*Prints out what courses the user has entered */
	printf("You've entered: \n");
	count = 1;
	for(i=0; i<numbers; i++){
		printf("%d. %s \n", count, *(*listOfcourses + i));
		count++;
		}
	} else{
	printf("There was an error allocating memory.");
	exit(0);
	}
		
}


void favoriteList(char*** courselist,char**** favoritelist, int numbers,int favNum){
	/*Function that populates array of favorite course list and prints out favorite book list */
	
	int temp1;
	int z;

	*favoritelist = malloc(favNum * sizeof(char**));

	/*Checks for allocation failure*/
	if(*favoritelist != NULL){
	
	printf("Enter the number next to each book title you want on your favorite list: ");
	
	/*Takes in what courses the user wants to be on the list and add the pointers  */
	for (z = 0; z < favNum; z++){
		scanf(" %d", &temp1);
		*(*favoritelist + z) = (*courselist + temp1 -1);
	}
	
	/*Prints out what courses are on the favorites list */
	printf("The books on your favorites list are: \n");
	for(z = 0; z < favNum; z++){
		printf("%d. %s \n",z+1 , *(*(*favoritelist + z)));
	}
	}else{
	/*Error Message */
	printf("Error Could not allocate memort");
	exit(0);
	}

}

void writeToFile(char** courseList,char**** favoritelist, int numbers,  int favNum){

	/*Function that writes the users courses list and favorite course list to their file */

	int q;
	FILE *out;
	int MAX = 256;
	char *fileName;
	/* Allocates Memory for file name */
	fileName = malloc(MAX * sizeof(char));

	if(fileName != NULL){
	printf("What file name do you want to use? ");
	scanf("%s", fileName);
	out = fopen(fileName, "w");
	
	/* prints out courses the user has read */
	fprintf(out, "Classes I've taken: \n");
	for (q =0; q < books; q++){
		fprintf(out, "%s \n" , *(courseList + q));
	}

	/*prints out users favorite courses */
	fprintf(out,  "\n My Favorites are: \n");
	for( q = 0; q < favNum; q++){
		fprintf(out,"%s \n" , *(*(*favoritelist + q))); 
	}
	printf("Your Classes and favorites have been saved to the file %s  \n", fileName);
	} else{
		printf("Unable to allocate memory");
		exit(0);
	}
	/*Closes file and frees memory */
	fclose(out);
	free(fileName);
}	


