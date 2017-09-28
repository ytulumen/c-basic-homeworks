/*##########################################################################*/
/*          HW03_Meltem_Cetiner_part1.c                                     */
/*_________________________________                                         */
/*                      Author    Meltem Çetiner                            */
/*                                                                          */
/*Descriptions:                                                             */
/*___________                                                               */
/*A complete C program for “Guessing An Integer Number” game.               */
/*Inputs:                                                                   */
/*	-take a character from console “p” or “P” for play and “e” or “E”   */
/*to exit). The game will continue with another random number as long as the*/
/* user wants to play.                                                      */
/* Player has infinitive chances to guess (name the variable as “guess”;    */
/*each time only one guess  should be entered)                              */
/*
/*Outputs:                                                                  */
/*An output of the function warn_the_player :                               */
/*If the difference is greater than or equal to 5 of the number             */
/*     – Program should warn the player as “You are too far from the number”*/
/*If the difference is greater than or equal to 3 of the number             */
/*     – Program should warn the player as “You are far from the number”    */
/*If the difference is smaller than or equal to 2 of the number             */
/*     – Program should warn the player as “You are close to the number”    */
/*If it is equal to the number print the number of guesses.                 */
/*##########################################################################*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*                         Includes                                         */
/*--------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*--------------------------------------------------------------------------*/
/*                        Prototypes                                        */
/*--------------------------------------------------------------------------*/

int RNG();
int calculate_the_difference(int number,int guess);
void warn_the_player(int diff);
void winner(int times);

int main (void)
{
    int number,       /*the wanted number                     */
        guess,        /*the number the player guesses         */
        difference=9, /*the difference of the number and guess*/
        times=1;   
    char choise;      /*(e,E) for exit, (p,P) for play        */

    
    number = RNG();   /*takes the random number*/
    
    printf("\nDo u want to play a guess number play:[p_P(Play)|e_E(Exit)]  :\n");
    scanf(" %c",&choise);
    
    while(choise=='p' || choise=='P')
    {
	do{
	    printf("\nGuess the number :\n");
	    scanf(" %d",&guess);
	    difference = calculate_the_difference(number,guess);
	    if(difference) warn_the_player(difference);
            else  winner(times);
            times++;
	}while(difference!= 0);
	
       printf("\nDo u want to play a guess number play:[p_P(Play)|e_E(Exit)]  :\n");
       scanf(" %c",&choise);
       number = RNG();   /*takes the random number*/
       times=0; 
    }
    
    if( choise!='e' || choise!='E')
         printf("\nThe game over ...\n");
        
    return 0;
/*------------------------------------------END_OF_MAIN-------------------------------------*/
}

/*--------------------------------------------------------------------------*/
/*                        Implementations                                   */
/*--------------------------------------------------------------------------*/
/* To generate the random number*/
int RNG()
{
    srand(time(NULL));
    return ( rand()%10+1);
    
}

/*To calculate and returns the difference between guess and the number*/
int calculate_the_difference(int number,int guess)
{ 
   return abs(guess - number) ;
}

/*To print a warning in order to guide the player.*/
void warn_the_player(int diff)
{
    if (diff >= 5)
        printf("\nYou are too far from the number.\n");
    
    else if (diff >= 3 )
        printf("\nYou are far from the number.....\n");
    
    else if (diff > 0 && diff <= 2)
        printf("\nYou are close to the number.....\n");
    else
        winner(1);
   
}

/*To print the winner and the number of guessing*/
void winner(int times)
{
	printf("You win the game on your %d .th guess ..",times);
}

/*##########################################################################*/
/*                   End of sample code part1                               */
/*##########################################################################*/
