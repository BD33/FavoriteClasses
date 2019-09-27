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
	char **listOfTitles;
	char ***listOfFavorites;	
	int numOfBooks;
	int favNum;
	int answer;
	int a;

	/*Asks the user for the amount of book titles*/
	printf("How many library book titles do you plan to enter? \n");
	scanf("%d", &numOfBooks);
	
	/*Pass the array for book titles and the number of books to the function*/
	bookList(&listOfTitles, numOfBooks);

	/*Asks the user how many books will be on the favorites list */
	printf("Of those %d books , how many do you plan to put on your favorites list ?", numOfBooks);
	scanf("%d", &favNum); 
	

	/*passes the Array of book titles , List of favorites, number of books and length of favorites list*/
	favoriteList(&listOfTitles, &listOfFavorites, numOfBooks, favNum);	
	
	/*askes the user if they want to save to a file */
	printf("Do you want to save them (1=yes, 2=no): ");
	scanf("%d", &answer);

	/*if the users answers yes then the variables are passed to the writeToFile Function */
	if(answer == 1){
		writeToFile(listOfTitles,&listOfFavorites,numOfBooks,favNum);
	}
	/*Frees the allocated Memory */
	if(listOfTitles != NULL){
	for(a = 0; a < numOfBooks; a++){
	 free(*(listOfTitles + a));
	}
	free(listOfTitles);			
	}

	free(listOfFavorites);
}


	
void bookList(char*** listOfTitles, int books){

	/*A function that populates the List of Book titles*/
	/*Declared variables */
	int i;
	char *temp;
	int count;	
	/*Allocated Memory for the Title Array */
	*listOfTitles = malloc(books * sizeof(char*));
	if(*listOfTitles != NULL){
	/*Allocates memory for each book title and asks the user for the titles one by one*/
	for( i = 0; i<books; i++){
		*(*listOfTitles + i) = malloc(61*sizeof(char));
		printf("Enter the %d  book titles one to a line \n", books);
		scanf(" %61[^\n]", *(*listOfTitles + i));
	}

	/*Prints out what books the user has entered */
	printf("You've entered: \n");
	count = 1;
	for(i=0; i<books; i++){
		printf("%d. %s \n", count, *(*listOfTitles + i));
		count++;
		}
	} else{
	printf("There was an error allocating memory.");
	exit(0);
	}
		
}


void favoriteList(char*** booklist,char**** favoritelist, int books,int favNum){
	/*Function that populates array of favorite book list and prints out favorite book list */
	
	int temp1;
	int z;

	*favoritelist = malloc(favNum * sizeof(char**));

	/*Checks for allocation failure*/
	if(*favoritelist != NULL){
	
	printf("Enter the number next to each book title you want on your favorite list: ");
	
	/*Takes in what books the user wants to be on the list and add the pointers  */
	for (z = 0; z < favNum; z++){
		scanf(" %d", &temp1);
		*(*favoritelist + z) = (*booklist + temp1 -1); 
	}
	
	/*Prints out what books are on the favorites list */
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

void writeToFile(char** bookList,char**** favoritelist, int books,  int favNum){

	/*Function that writes the users book list and favorite book list to their file */	

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
	
	/* prints out books the user has read */
	fprintf(out, "Books I've Read: \n");
	for (q =0; q < books; q++){
		fprintf(out, "%s \n" , *(bookList + q)); 
	}

	/*prints out users favorite books */
	fprintf(out,  "\n My Favorites are: \n");
	for( q = 0; q < favNum; q++){
		fprintf(out,"%s \n" , *(*(*favoritelist + q))); 
	}
	printf("Your booklist and favorites have been saved to the file %s  \n", fileName);
	} else{
		printf("Unable to allocate memory");
		exit(0);
	}
	/*Closes file and frees memory */
	fclose(out);
	free(fileName);
}	


