/*
 * File:   Message.c
 * Author: Jose Luis Santiago   jlsantia@ucsc.edu
 *
 * Created on August 23, 2018, 4:45 PM
 */

//include user libraries
#include "Message.h"
#include "BOARD.h"

#include <stdio.h>

//macros
#define INITIAL_INDEX 0
#define ZERO_ASCII_VALUE 48
#define NINE_ASCII_VALUE 57
#define A_ASCII_VALUE 65
#define F_ASCII_VALUE 70

//variables
static int decodePayloadIndex;
static int decodeChecksumIndex;

typedef enum{
    WAITING, //in this state we are waiting to receive the start delimiter: '$'
    RECORDING_PAYLOAD,
    RECORDING_CHECKSUM
} decodeStates;

//static variable to hold our decode states
static decodeStates decodeState = WAITING; //initial value for decodeState

//helper function definitions
uint8_t ctob(const char * string); //string converts a char from a string to a binary
uint8_t ChecksumStringToBinary(const char * string);
uint8_t AsciiHexToBin(uint8_t ascii_hex_value); //formula that translates ascii hex into decimal binary

uint8_t Message_CalculateChecksum(const char* payload)
{
    uint8_t checksum = 0b00000000;
    while (1) { //while 1
        while (*payload == ',') { //if we get a dollar sign or comma we want to skip these chars
            payload++; //skip via incrementing address
        }
        uint8_t convert; //variable to store char to binary conversion
        convert = ctob(payload); //conversion
        checksum ^= convert; //checksum via XOR
        payload++;
        if ((*payload == '*') || (*payload == NULL)) { //valid string is over return value
            return checksum;
        }
    }
    return checksum; //return checksum
}

//helper function

uint8_t ctob(const char * string)
{ //string converts a char from a string to a binary
    uint8_t binary = 0b00000000; //clear variable
    int i; //declare index variable
    for (i = 0; i <= 7; i++) { //iterate through 8 bits
        uint8_t mask = (1 << i); //save mask
        if ((*string & mask) == mask) { //check to see if the mask and string match up
            binary |= mask; //set the appropriate bits from the mask to the return variable
        }
    }
    return binary; //return binary value
}

void ChecksumStringGenerator(uint8_t checksum, char * checksumString)
{
    char firstHalfString[2]; //holds first hex char
    char secondHalfString[2]; //holds second hex char
    uint8_t checksum1 = checksum >> 4; //checksum storage for two seperate hex values
    uint8_t checksum2 = checksum << 4; //store top 4 bits in checksum1 and bottom 4 in checksum2
    checksum2 = checksum2 >> 4;

    sprintf(firstHalfString, "%X", checksum1); //save values  as hex via sprintf

    sprintf(secondHalfString, "%X", checksum2);

    sprintf(checksumString, "%s%s\0", firstHalfString, secondHalfString); //combine both hex chars

}

int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event)
{
    // Given a payload and its checksum, verify that the payload matches the checksum
    uint8_t payloadChecksum;
    uint8_t checksumString;

    payloadChecksum = Message_CalculateChecksum(payload);

    checksumString = ChecksumStringToBinary(checksum_string);

    if (payloadChecksum == checksumString) { //if we receive a valid checksum and message delimiter
        if (*payload == 'C') { //challenge received
            payload++;
            if (*payload == 'H') {
                payload++;
                if (*payload == 'A') {
                    message_event->type = BB_EVENT_CHA_RECEIVED;
                    payload++;
                    int j = 0; //counter to know how many chars we have in our string
                    while ((*payload != NULL) || (*payload != '*')) {
                        if (*payload == ',') {
                            payload++;
                        }
                        if (j == 0) { //only one parameter possible w/ this message
                            message_event->param0 = ctob(payload);
                            return SUCCESS;
                        } else if (j > 0) { //invalid amount of chars return error
                            message_event->type = BB_EVENT_ERROR;
                            return STANDARD_ERROR;
                        }
                        payload++;
                        j++;
                    }
                }
            }
        }
        if (*payload == 'S') { //shot guess message
            payload++;
            if (*payload == 'H') {
                payload++;
                if (*payload == 'O') {
                    payload++; //just left MESSAGE string 'SHO'
                    message_event->type = BB_EVENT_SHO_RECEIVED;
                    int j = 0; //counter to know how many chars we have in our string
                    while ((*payload != NULL) || (*payload != '*')) {
                        if (*payload == ',') {
                            payload++;
                        }
                        if (j == 0) { //only one parameter possible w/ this message
                            message_event->param0 = ctob(payload);
                            message_event->param0 = AsciiHexToBin(message_event->param0);
                        }
                        if (j == 1) { //invalid amount of chars return error
                            message_event->param1 = ctob(payload);
                            message_event->param1 = AsciiHexToBin(message_event->param1);
                            return SUCCESS;
                        } else if (j > 1) {
                            message_event->type = BB_EVENT_ERROR;
                            return STANDARD_ERROR;
                        }

                        payload++;
                        j++;
                    }
                }
            }
        }
        if (*payload == 'A') { //accept message
            payload++;
            if (*payload == 'C') {
                payload++;
                if (*payload == 'C') {
                    payload++; //iterated through acc string, should be at ,"ACC,1"
                    message_event->type = BB_EVENT_ACC_RECEIVED;
                    int j = 0;
                    while ((*payload != '*') || (*payload != NULL)) {
                        if (*payload == ',') {
                            payload++;
                        }
                        if (j == 0) {
                            message_event->param0 = ctob(payload); //want to save the data 
                            message_event->param0 = AsciiHexToBin(message_event->param0);
                            return SUCCESS;
                        } else if (j > 0) { //invalid amount of chars return error
                            message_event->type = BB_EVENT_ERROR;
                            return STANDARD_ERROR;
                        }
                        payload++;
                        j++;
                    }
                }
            }
        }
        if (*payload == 'R') {
            payload++;
            if (*payload == 'E') {
                payload++;
                if (*payload == 'V') { //reveal message
                    payload++;
                    message_event->type = BB_EVENT_REV_RECEIVED;
                    int j = 0; //counter to know how many chars we have in our string
                    while ((*payload != '*') || (*payload != NULL)) {
                        if (*payload == ',') {
                            payload++;
                        }
                        if (j == 0) { //only one parameter possible w/ this message
                            message_event->param0 = ctob(payload);
                            message_event->param0 = AsciiHexToBin(message_event->param0);
                            return SUCCESS;
                        } else if (j > 0) { //invalid amount of chars return error
                            message_event->type = BB_EVENT_ERROR;
                            return STANDARD_ERROR;
                        }
                        payload++;
                        j++;
                    }

                } else if (*payload == 'S') { //result message
                    payload++;
                    message_event->type = BB_EVENT_RES_RECEIVED;
                    int j = 0;
                    while ((*payload != '*') || (*payload != NULL)||(*payload != '\n')) { //when payload ends
                        if (*payload == ',') {
                            payload++;
                        }
                        if (j == 0) { //only one parameter possible w/ this message
                            message_event->param0 = ctob(payload);
                            message_event->param0 = AsciiHexToBin(message_event->param0);
                        }
                        if (j == 1) {
                            message_event->param1 = ctob(payload);
                            message_event->param1 = AsciiHexToBin(message_event->param1);
                        }
                        if (j == 2) {
                            message_event->param2 = ctob(payload);
                            message_event->param2 = AsciiHexToBin(message_event->param2);
                            
                            return SUCCESS;
                        } else if (j > 2) {
                            message_event->type = BB_EVENT_ERROR;
                            return STANDARD_ERROR;
                        }
                        payload++;
                        j++;
                    }
                }
            }
        } else {
            message_event->type = BB_EVENT_ERROR;
            return STANDARD_ERROR;
        }
    }else{
        return STANDARD_ERROR;
    }
}

uint8_t ChecksumStringToBinary(const char * checksumString)
{
    uint8_t checksum;
    uint8_t decimal;
    int counter = 0; //counts how many chars have been passed in
    while (*checksumString != NULL) { //while string still valid
        counter++; //increment counter here to tell me if i have to shift the bits
        if (*checksumString > 64) { //if receive char A-F, subtract by 55 to get decimal value of hex char
            decimal = *checksumString - 55;
        } else if (*checksumString > ZERO_ASCII_VALUE) { //if receive char 0-9, subtract by 48 to get proper decimal value
            decimal = *checksumString - ZERO_ASCII_VALUE;
        }
        if (counter < 2) { //if we are in our first iteration, shift our bits to be top 4
            checksum = decimal << 4;
        } else {
            checksum |= decimal; //add in the second half of bits
        }
        checksumString++;
    }
    return checksum;
}

//helper function converts ascii hex value to binary uint8_t value

uint8_t AsciiHexToBin(uint8_t ascii_hex_value) //formula that translates ascii hex into decimal binary
{
    if (ascii_hex_value > 64) {
        ascii_hex_value = ascii_hex_value - 55;
        return ascii_hex_value;
    } else if (ascii_hex_value > 48) {
        ascii_hex_value = ascii_hex_value - 48;
        return ascii_hex_value;
    }
}

int Message_Encode(char *message_string, Message message_to_encode)
{
    char payload[MESSAGE_MAX_PAYLOAD_LEN];
    char message[MESSAGE_MAX_LEN];
    if (message_to_encode.type == MESSAGE_RES) {
        uint8_t checksum; //variable to store checksum

        //wrap payload with PAYLOAD_RES template
        sprintf(payload, PAYLOAD_TEMPLATE_RES, message_to_encode.param0, message_to_encode.param1, message_to_encode.param2); //3 data fields in RES
        checksum = Message_CalculateChecksum(payload); //calculate checksum of payload
        sprintf(message, MESSAGE_TEMPLATE, payload, checksum);

        //get size of string
        int i = 0;
        while (message[i] != NULL) { //while there are still contents in the array
            *message_string = message[i]; //store them into the pointer
            message_string++; //increment pointer address
            if (message[i + 1] == NULL) { //return i when we have counted the last valid character in the string
                return i;
            }
            i++; //increment counter
        }
        //return i;
    }
    if (message_to_encode.type == MESSAGE_REV) {
        uint8_t checksum; //variable to store checksum

        //wrap payload with PAYLOAD_REV template
        sprintf(payload, PAYLOAD_TEMPLATE_REV, message_to_encode.param0); //only one param possible with REV
        checksum = Message_CalculateChecksum(payload); //calculate checksum of payload
        sprintf(message, MESSAGE_TEMPLATE, payload, checksum);

        //get size of string
        int i = 0;
        while (message[i] != NULL) { //while there are still contents in the array
            *message_string = message[i]; //store them into the pointer
            message_string++; //increment pointer address
            if (message[i + 1] == NULL) { //return i when we have counted the last valid character in the string
                return i;
            }
            i++; //increment counter
        }
    }
    if (message_to_encode.type == MESSAGE_CHA) {
        uint8_t checksum; //variable to store checksum

        //wrap payload with PAYLOAD_CHA template
        sprintf(payload, PAYLOAD_TEMPLATE_CHA, message_to_encode.param0); //only one data field available
        checksum = Message_CalculateChecksum(payload); //calculate checksum of payload
        sprintf(message, MESSAGE_TEMPLATE, payload, checksum);

        //get size of string
        int i = 0;
        while (message[i] != NULL) { //while there are still contents in the array
            *message_string = message[i]; //store them into the pointer
            message_string++; //increment pointer address
            if (message[i + 1] == NULL) { //return i when we have counted the last valid character in the string
                return i;
            }
            i++; //increment counter
        }
    }
    if (message_to_encode.type == MESSAGE_ACC) {
        uint8_t checksum; //variable to store checksum

        //wrap payload with PAYLOAD_ACC template
        sprintf(payload, PAYLOAD_TEMPLATE_ACC, message_to_encode.param0); //only one data field possible
        checksum = Message_CalculateChecksum(payload); //calculate checksum of payload
        sprintf(message, MESSAGE_TEMPLATE, payload, checksum);

        //get size of string
        int i = 0;
        while (message[i] != NULL) { //while there are still contents in the array
            *message_string = message[i]; //store them into the pointer
            message_string++; //increment pointer address
            if (message[i + 1] == NULL) { //return i when we have counted the last valid character in the string
                return i;
            }
            i++; //increment counter
        }
    }
    if (message_to_encode.type == MESSAGE_SHO) {
        uint8_t checksum; //variable to store checksum

        //wrap payload with PAYLOAD_SHO template
        sprintf(payload, PAYLOAD_TEMPLATE_SHO, message_to_encode.param0, message_to_encode.param1); //2 possible data fields
        checksum = Message_CalculateChecksum(payload); //calculate checksum of payload
        sprintf(message, MESSAGE_TEMPLATE, payload, checksum);

        //get size of string
        int i = 0;
        while (message[i] != NULL) { //while there are still contents in the array
            *message_string = message[i]; //store them into the pointer
            message_string++; //increment pointer address
            if (message[i + 1] == NULL) { //return i when we have counted the last valid character in the string
                return i;
            }
            i++; //increment counter
        }
    } else if (message_to_encode.type == MESSAGE_NONE) {
        return 0;
    }
}

int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event)
{
    switch (decodeState) {
        static char payload[MESSAGE_MAX_PAYLOAD_LEN];  //array to store payload
        static char checksum[3];   //checksum array to store checksum string
        
    case WAITING:
        if (char_in == '$') { //start delimiter received
            decodePayloadIndex = INITIAL_INDEX; //set indecex for arrays
            decodeState = RECORDING_PAYLOAD;
            return SUCCESS;
        }else{
            decodeState = WAITING;
        }
        break;
    case RECORDING_PAYLOAD:
        
        if (char_in == '*') {   //if we receive our payload delimiter
            decodeChecksumIndex = INITIAL_INDEX;
            decodeState = RECORDING_CHECKSUM;   //go to chceksum recording
            return SUCCESS;
        } else {
            payload[decodePayloadIndex] = char_in; //store valid payload char
            decodePayloadIndex++;   //increment payload array address
            decodeState = RECORDING_PAYLOAD;    //return to state RECORDING_PAYLOAD
            return SUCCESS;
        }


        break;
    case RECORDING_CHECKSUM:
        if(char_in == '\n'){    //if we receive our null delimiter
            int payloadLength;
            payloadLength = Message_ParseMessage(payload,checksum,decoded_message_event);
            
            if(payloadLength){  //if the payload checksum and the checksum string match, and theMessage was parsed successfully
                decodeState = WAITING;
                return SUCCESS;
            }else{
                return STANDARD_ERROR;
                decodeState = WAITING;
            }
            return SUCCESS;
        }else if(((char_in >= ZERO_ASCII_VALUE)&&(char_in<=NINE_ASCII_VALUE))||((char_in>=A_ASCII_VALUE)&&(char_in<=F_ASCII_VALUE))){   //if we receive a valid hex value
            checksum[decodeChecksumIndex] = char_in;    //store checksum value from input
            decodeChecksumIndex++; //increment checksum string address
            decodeState = RECORDING_CHECKSUM;
            return SUCCESS;
        }
        break;
    }
}
