#include <stdio.h>
#include "AVL.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



history_sh(char file_name[],int user_id);

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
    }else{
        printf("username or password is not valid.");
    }

}

int history_sh(char file_name[],int user_id){
    FILE* fp = fopen(file_name,"r");
    if(fp == NULL){
        return 0;
    }
    //ส่วนที่เอาไว้วนลูปเเสดง history
    //user_id เป็นเงื่อนไขในการเเสดง history 

    fclose(fp);
    return 1;
}