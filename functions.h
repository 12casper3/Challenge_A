#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED



extern int uitgangen[12][2];
extern int direction_exit[12];

extern int curr_direction;
extern int curr_position[2];
extern int checkpoints[3];

extern int res[50];
extern int curr_command;

enum CONTROL {
	CCLOCKWISE = 0,
	UTURN,
	CLOCKWISE
};

enum DIRECTIONS {
	NORTH = 0,
	EAST,
	SOUTH,
	WEST
};

#define MSIZE (5*5)

#define BLACKDATA   0x42
#define LEFTDATA    0x31
#define FORWARDDATA 0x33
#define RIGHTDATA   0x32
#define MINECRAFT   0x39


int mod(int a,int b);
void turn(int control);
void drive_exit(int direction);
void drive(int distance);
void drive_to_intersection(int uitgang);
void print_curr_position();
void print_data();
void print_commands();

//For Serial:
void cleanUp(void);
void initSerial(char*);

#endif // FUNCTIONS_H_INCLUDED
