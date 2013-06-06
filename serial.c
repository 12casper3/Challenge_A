#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <Windows.h>
#include <string.h>


#include <conio.h> /*win32-specific library, necessary from reading directly from input instead of from buffered stdin*/
#include "serial.h"
#define BAUDRATE CBR_9600


enum ROBOT_DIR
{
    ROBOT_LEFT,
    ROBOT_RIGHT,
    ROBOT_AHEAD
};

HANDLE hSerial;


void doLeft(void)
{
}

void initSerial(char* comport)
{
    /* The following is from the PuTTY source code (c) 1997-2011 Simon Tatham.
     * Munge the string supplied by the user into a Windows filename.
     *
     * Windows supports opening a few "legacy" devices (including
     * COM1-9) by specifying their names verbatim as a filename to
     * open.
     * However, this doesn't let you get at devices COM10 and above.
     * For that, you need to specify a filename like "\\.\COM10".
     * This is also necessary for special serial and serial-like
     * devices such as \\.\WCEUSBSH001. It also works for the "legacy"
     * names, so you can do \\.\COM1 (verified as far back as Win95).
     * See <http://msdn2.microsoft.com/en-us/library/aa363858.aspx>
     * (CreateFile() docs).
     * So, we believe that prepending "\\.\" should always be the
     * Right Thing. However, just in case someone finds something to
     * talk to that doesn't exist under there, if the serial line
     * contains a backslash, we use it verbatim. (This also lets
     * existing configurations using \\.\ continue working.)
     */
    int length = strlen(comport);
    char *serfilename = calloc(sizeof (char), length + 5);
    snprintf(serfilename, length + 5, "%s%s",
             strchr(comport, '\\') ? "" : "\\\\.\\",
             comport);

    /*----------------------------------------------------------
    // Open COMPORT for reading and writing
    //----------------------------------------------------------*/
    hSerial = CreateFile(serfilename,
                         GENERIC_READ | GENERIC_WRITE,
                         0,
                         NULL,
                         OPEN_EXISTING,
                         FILE_ATTRIBUTE_NORMAL,
                         NULL
                        );

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            /*serial port does not exist. Inform user.*/
            printf(" serial port does not exist \n");
        }
        /*some other error occurred. Inform user.*/
        printf(" some other error occured. Inform user.\n");
        exit(1);
    }

    COMMTIMEOUTS timeouts = {0};
    DCB dcbSerialParams = {0};

    dcbSerialParams.DCBlength = sizeof (dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        /*error getting state*/
        printf("error getting state \n");
    }

    /*Set ALL the values!
    Intializes the parameters as Baudrate, Bytesize,
    Stopbits, Parity and Timeoutparameters of
    the COM port
    */
    dcbSerialParams.BaudRate = BAUDRATE;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        /*error setting serial port state*/
        printf("error setting state \n");
    }

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts))
    {
        /*error occureed. Inform user*/
        printf("error setting timeout state \n");
    }
}

/*--------------------------------------------------------------
// Function: readByte
// Description: reads a single byte from the COM port into
//              buffer buffRead
//--------------------------------------------------------------*/

int readByte( char* buffRead)
{

    DWORD dwBytesRead = 0;

    if (!ReadFile(hSerial, buffRead, 1, &dwBytesRead, NULL))
    {
        printf("error reading byte from input buffer \n Error code %d \n", GetLastError());
    }

    /* printf("Byte read from read buffer is: %X \n", (uint8_t)buffRead[0]); */
    return(0);
}

/*--------------------------------------------------------------
// Function: writeByte
// Description: writes a single byte stored in buffRead to
//              the COM port
//--------------------------------------------------------------*/
int writeByte( char *buffWrite)
{

    DWORD dwBytesWritten = 0;

    if (!WriteFile(hSerial, buffWrite, 1, &dwBytesWritten, NULL))
    {
        printf("%x\n", GetLastError());
        printf("error writing byte to output buffer \n");
    }
    /* printf("Byte written to write buffer is: 0x%X \n", buffWrite[0]); */

    return (0);
}

void cleanUp(void)
{

    printf("MEMORY FREED\n");
    CloseHandle(hSerial);
    printf("ZIGBEE I/O DONE, SERIAL HANDLE CLOSED\n");
}
