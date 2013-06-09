#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

int i=0;
int verbose=0; //0 for no outputs

int main(int argc, char *argv[])
{


    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        checkpoints[0]= atoi(argv[1]);
        checkpoints[1]= atoi(argv[2]);
        checkpoints[2]= atoi(argv[3]);
    }
    else
    {
        printf("error");
    }

    int start;


    curr_position[0] = 1;
    curr_position[1] = 0;

    //scanf("%d %d %d",&checkpoints[0],&checkpoints[1],&checkpoints[2]);
    //scanf("%d %d",&start,&checkpoints[0]);

//curr_position[0] = uitgangen[start-1][0];
//curr_position[1] = uitgangen[start-1][1];

    if(verbose)
    {
        printf("First checkpoint:%d @(%d,%d)\n",checkpoints[0],uitgangen[checkpoints[0]-1][0],uitgangen[checkpoints[0]-1][1]);
        printf("Second checkpoint:%d @(%d,%d)\n",checkpoints[1],uitgangen[checkpoints[1]-1][0],uitgangen[checkpoints[1]-1][1]);
        printf("Third checkpoint:%d @(%d,%d)\n\n",checkpoints[2],uitgangen[checkpoints[2]-1][0],uitgangen[checkpoints[2]-1][1]);
    }

    // printf("drive(12)\n");
    //drive_exit(0);//Drive from start point to (1,0)
    print_data();
    if(verbose)
    {
        printf("Start opdracht!----------------------------------------------------\n\n\n");
    }


    //drive_exit(curr_direction);
    drive_to_intersection(checkpoints[i]-1);
    drive_exit(direction_exit[checkpoints[i]-1]);
    if(verbose)
    {
        printf("Checkpoint %d reached!!<<<<<<<<<<<<<<<<<<<<<<\n\n\n",i+1);
    }
    res[curr_command] = GOALDATA;
    curr_direction = (curr_direction+2) % 4;// omgedraaid
    curr_command++;




    i++;
    //drive_exit((curr_direction+2 )%4);
    drive_to_intersection(checkpoints[i]-1);
    drive_exit(direction_exit[checkpoints[i]-1]);

    if(verbose)
    {
        printf("Checkpoint %d reached!!<<<<<<<<<<<<<<<<<<<<<<\n\n\n",i+1);
    }

    res[curr_command] = GOALDATA;
     curr_direction = (curr_direction+2) % 4;// omgedraaid
    curr_command++;




    i++;


    //drive_exit((curr_direction+2 )%4);

    drive_to_intersection(checkpoints[i]-1);
    drive_exit(direction_exit[checkpoints[i]-1]);

    if(verbose)
    {
        printf("Checkpoint %d reached!!<<<<<<<<<<<<<<<<<<<<<<\n",i+1);

    }
    res[curr_command] = GOALDATA;
    curr_direction = (curr_direction+2) % 4;// omgedraaid
    curr_command++;
    print_data();

    print_commands();

    if(verbose)
    {
        send_commands();
    }

    return 1;
}
