/* 
 * File:   serial.h
 * Author: Rijk
 *
 * Created on 4 juni 2013, 13:30
 */

#ifndef SERIAL_H
#define	SERIAL_H

int readByte( char *buffRead);
int writeByte( char *buffWrite);
void initSerial(char* comport);
void cleanUp(void);
#endif	/* SERIAL_H */

