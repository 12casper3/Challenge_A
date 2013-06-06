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

int res[50];
int curr_command = 0;

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
        //todo
        res[curr_command] = LEFTDATA;
        curr_command++;

        curr_direction--;
        break;
    case UTURN :
        printf("turn(%d) U-turn",control);
        //todo
        res[curr_command] = RIGHTDATA;
        curr_command++;
        res[curr_command] = RIGHTDATA;
        curr_command++;

        curr_direction += 2;
        break;
    case CLOCKWISE  :
        printf("turn(%d) cw (leftwheel only)\n",control);
        //todo
        res[curr_command] = RIGHTDATA;
        curr_command++;

        curr_direction++;
        break;
    }

    curr_direction = mod(curr_direction,3);
    print_data();
}

void drive(int distance)
{
    int temp_distance = 0;

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
    //todo
    temp_distance = distance *2;
    while(temp_distance){
    res[curr_command] = FORWARDDATA;
    curr_command++;
    temp_distance--;
    }
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

void send_commands()
{
int i =0;
    //initSerial(globalArgs.comport);
    initSerial("COM3");
    char byteBuffer[32] = {0};
    for (i = 0; res[i] != 0; i++)
    {
        while (byteBuffer[0] != BLACKDATA)
        {
            readByte(byteBuffer);
            printf("waiting for data. byteBuffer[0] = %x\n", byteBuffer[0]);
        }
        while (byteBuffer[0] == BLACKDATA)
        {
            writeByte(&res[i]);
            printf("Written data = %x\n", res[i]);
            memset(byteBuffer, 0, sizeof(byteBuffer));
            readByte(byteBuffer);
        }
    }
}

void print_commands()
{
    //TODO
    for(curr_command = 0 ; res[curr_command]!=0 ; curr_command++)
    {

        printf("%x \n", res[curr_command]);
    }

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
            turn(CLOCKWISE); // Right
        }
        else
        {
            turn(CCLOCKWISE); // Left
        }
    }
    else
    {
        //printf("Else\n");
        if(curr_direction == (direction+2) % 4)
        {
            turn(UTURN); // U-turn
        }
    }
    printf("Drove 12cm for an exit\n");
     res[curr_command] = FORWARDDATA;
        curr_command++;
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
            if(curr_direction==3) turn(CLOCKWISE);
            if(curr_direction==1) turn(CCLOCKWISE);
            drive(driveY);

        }
        else
        {
            if(curr_direction==3) turn(CCLOCKWISE);
            if(curr_direction==1) turn(CLOCKWISE);
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
            if(curr_direction==0) turn(CLOCKWISE);
            if(curr_direction==2) turn(CCLOCKWISE);
            drive(driveX);

        }
        else
        {

            if(curr_direction==0) turn(CCLOCKWISE);
            if(curr_direction==2) turn(CLOCKWISE);
            drive(-driveX);
        }

    }
}
