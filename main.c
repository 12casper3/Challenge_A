#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

int i=0;


int main(int argc, char ** argv)
{
int start;
checkpoints[0]= 1;
checkpoints[1]= 1;
checkpoints[2]= 1;

curr_position[0] = 1;
curr_position[1] = 0;

    //scanf("%d %d %d",&checkpoints[0],&checkpoints[1],&checkpoints[2]);
    scanf("%d %d",&start,&checkpoints[0]);

curr_position[0] = uitgangen[start-1][0];
curr_position[1] = uitgangen[start-1][1];

    printf("First checkpoint:%d @(%d,%d)\n",checkpoints[0],uitgangen[checkpoints[0]-1][0],uitgangen[checkpoints[0]-1][1]);
    printf("Second checkpoint:%d @(%d,%d)\n",checkpoints[1],uitgangen[checkpoints[1]-1][0],uitgangen[checkpoints[1]-1][1]);
    printf("Third checkpoint:%d @(%d,%d)\n\n",checkpoints[2],uitgangen[checkpoints[2]-1][0],uitgangen[checkpoints[2]-1][1]);


    // printf("drive(12)\n");
    //drive_exit(0);//Drive from start point to (1,0)

    print_data();

    printf("Start opdracht!----------------------------------------------------\n\n\n");


   //drive_exit(curr_direction);
    drive_to_intersection(checkpoints[i]-1);
    drive_exit(direction_exit[checkpoints[i]-1]);

    printf("Checkpoint %d reached!!<<<<<<<<<<<<<<<<<<<<<<\n\n\n",i+1);
    i++;
    drive_exit((curr_direction+2 )%4);
    drive_to_intersection(checkpoints[i]-1);
    drive_exit(direction_exit[checkpoints[i]-1]);

    printf("Checkpoint %d reached!!<<<<<<<<<<<<<<<<<<<<<<\n\n\n",i+1);
    i++;
    drive_exit((curr_direction+2 )%4);
    drive_to_intersection(checkpoints[i]-1);
    drive_exit(direction_exit[checkpoints[i]-1]);

    printf("Checkpoint %d reached!!<<<<<<<<<<<<<<<<<<<<<<\n",i+1);
    print_data();

    print_commands();
    send_commands();


    printf("END!");
    return 1;
}
