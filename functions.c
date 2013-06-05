#include "functions.h"
#include<stdio.h>
#include <stdlib.h>
#include <math.h>


int uitgangen[12][2] =
{
    {1,0}, //1
    {2,0}, //2
    {3,0}, //3
    {4,1}, //4
    {4,2}, //5
    {4,3}, //6
    {3,4}, //
    {2,4}, //
    {1,4}, //9
    {0,3}, //
    {0,2}, //
    {0,1}  //12
};

int direction_exit[12] = {2,2,2,1,1,1,0,0,0,3,3,3};

int curr_direction = 0; //0 = north
int curr_position[2]= {1,0};
int checkpoints[3];


int mod (int a, int b)
{
    int ret = a % b;
    if(ret < 0)
        ret+=b;
    return ret;
}

void turn(int control)
{
//control:
//1 counter clockwise
//2 U turn
//3 clockwise

    switch(control)
    {
    case CCLOCKWISE :
        printf("turn(%d) ccw (rightwheel only)\n",control);
        curr_direction--;
        break;
    case UTURN :
        printf("turn(%d) U-turn",control);
        curr_direction += 2;
        break;
    case CLOCKWISE  :
        printf("turn(%d) cw (leftwheel only)\n",control);
        curr_direction++;
        break;
    }

    curr_direction = mod(curr_direction,3);
    print_data();
}

void drive(int distance)
{
    //int temp = distance;

    distance = abs(distance);
    switch(curr_direction)
    {
    case NORTH :
        curr_position[1] +=distance;
        break;
    case EAST:
        curr_position[0] +=distance;
        break;
    case SOUTH :
        curr_position[1] -=distance;
        break;
    case WEST :
        curr_position[0] -=distance;
        break;

    }

    //printf("drive(%d)\t(%d)\n", distance,temp);
    printf("drive(%d)\n", distance);

    print_data();
}

void print_curr_position()
{
    printf("curr_position:(%d,%d)\n\n",curr_position[0],curr_position[1]);

}

void print_data()
{
    printf("\tcurr_position:(%d,%d)\tcurr_direction:%d\n\n\n\n",curr_position[0],curr_position[1],curr_direction);
}

void drive_exit(int direction)
{
    printf("Direction exit: %d\t curr_direction:%d\n",direction,curr_direction);

//Need a turn
    if(curr_direction%2 != direction%2)
    {
        //printf("Make a turn for Exit!\n");
        if(curr_direction<direction)
        {
            turn(3); // Right
        }
        else
        {
            turn(1); // Left
        }
    }
    else
    {
        //printf("Else\n");
        if(curr_direction == (direction+2) % 4)
        {
            turn(2); // U-turn
        }
    }
    printf("Drove 12cm for an exit\n");
    print_data();
}

void drive_to_intersection(int uitgang)
{
    // uitgang is # in array
    int driveX,driveY;

    if(curr_direction%2)
    {
        //HORIZONTAL
        driveX = uitgangen[uitgang][0] - curr_position[0];

        if(driveX==0)
        {
            printf("drive(NULL)\n\n");
            return;
        }
        else
        {
            drive(driveX);
        }

        driveY = uitgangen[uitgang][1]- curr_position[1];

        if(driveY==0)
        {
            printf("drive(NULL)\n\n");
            return;
        }

        if(driveY >0)
        {
            if(curr_direction==3) turn(3);
            if(curr_direction==1) turn(1);
            drive(driveY);

        }
        else
        {
            if(curr_direction==3) turn(1);
            if(curr_direction==1) turn(3);
            drive(-driveY);
        }

    }
    else
    {
        //VERTICAL:

        driveY = uitgangen[uitgang][1]- curr_position[1];

        if(driveY==0)
        {
            printf("drive(NULL)\n\n");
            //return;
        }
        else
        {
            drive(driveY);
        }

        driveX = uitgangen[uitgang][0] - curr_position[0];

        if(driveX==0)
        {
            printf("drive(NULL)\n\n");
            //return;
        }

        if(driveX >0)
        {
            if(curr_direction==0) turn(3);
            if(curr_direction==2) turn(1);
            drive(driveX);

        }
        else
        {

            if(curr_direction==0) turn(1);
            if(curr_direction==2) turn(3);
            drive(-driveX);
        }

    }
}