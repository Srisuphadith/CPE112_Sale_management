#include <stdio.h>
#include "AVL.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    int userChoice , adminChoice;

    if(/*registerfunction == True*/1){

        //user part
        if(/*user*/1){
            
            switch (userChoice)
            {
            case 1:
                /* search */
                break;

            case 2:
                /* shop */
                break;

            case 3:
                /*history*/
                break;
            
            case -1:
                /*exit*/
                break;
            
            default:
                printf("please enter number between 1-3");
            }
            /*shop function*/
        
        //admin part
        }else/*admin*/{

            switch (adminChoice)
            {
            case 1:
                /* stock manage */
                break;

            case 2:
                /*report ***optional*/
                break;

            case -1:
                /*exit*/
                break;
            
            default:
                printf("please enter number between 1-2");
            }

        }
    }

}