/*
 * File:   MessageTest.c
 * Author:Karla Alvarado            email: kaaalvar@ucsc.edu
 *
 * Created on August 24, 2018, 5:27 PM
 */

#include <stdio.h>

#include "Message.h"
#include "BOARD.h"
#include "BattleBoats.h"

int main(void)
{
    //string that holds our string version of our hex format checksum
    char checksumString[3];

    //8 bit integers used to store chceksums
    uint8_t testChecksum1;
    uint8_t testChecksum2;
    uint8_t testChecksum3;

//testPayload with invalid message*****************************************************
    char testPayload1[] = "HIT,1,1,1"; //test payload with HIT message and basic coordinates: our expected checksum is decimal value 100

    //testing Message_CalculateChecksum
    testChecksum1 = Message_CalculateChecksum(testPayload1);

    if (testChecksum1 == 100) {
        printf("Proper checksum of 100 returned: %d\n", testChecksum1);
    } else {
        printf("Wrong checksum returned\n");
    }

    //first test for HexString generator
    ChecksumStringGenerator(testChecksum1, checksumString);

    printf("Checksum in hex string format: %s\n", checksumString);
    
/*****testing MessageParsing function****************************************************/
    BB_Event *testEvents1 = (BB_Event *) malloc(sizeof (BB_Event));
    int parseCheck;
    
    parseCheck = Message_ParseMessage(testPayload1,checksumString,testEvents1);
    
    if(parseCheck){
        printf("Message_ParseMessage FAILED\n");
    }else{
        printf("Failure returned by Message_ParseMessage, testPayload1 checksum and checksumString match, but HIT is an invalid message\n");
    }
    
/*****MessageParsing testing TBC: Commence second round of testing********************/

    //new payload
    char testPayload2[] = "RES,4,7,2";  

//testing checksum again****************************************************************
    testChecksum2 = Message_CalculateChecksum(testPayload2);

    if (testChecksum2 == 117) { //if we get the appropriate checksum from our second payload
        printf("Proper checksum of 117 returned: %d\n", testChecksum2);
    } else {
        printf("Checksum2 failed\n");
    }

//testing our ChecksumHex to String converter again*********************************************
    ChecksumStringGenerator(testChecksum2, checksumString);

    printf("Checksum displayed as string in hex format: %s\n", checksumString);

//******testing for helper function CheckumStringToBinary which converts a hex string to binary format
    testChecksum3 = ChecksumStringToBinary(checksumString);

    if (testChecksum3 == testChecksum2) {
        printf("Success ChecksumStringToBinary helper functioning properly\n");
    } else {
        printf("Failure,something wrong with ChecksumStringToBinary\n");
    }
        
    //testing Message_ParseMessage again*******************************************
    BB_Event *testEvents2=(BB_Event *)malloc(sizeof(BB_Event));
    
    parseCheck = Message_ParseMessage(testPayload2, checksumString, testEvents2);

    if (parseCheck) {
        printf("Success returned by Message_ParseMessage, testPayload2 checksum and checksumString match\n");
    } else {
        printf("FAILURE something went wrong with Message_ParseMessage\n");
    }

    printf("This was the data collected from our testPayload2(RES,4,7,2):\n");
    printf("%d,%d,%d\n", testEvents2->param0, testEvents2->param1, testEvents2->param2);
    
//*******start MessageEncode testing ****************************************************
    Message testMessage1;  //pointer to our message data
    
    testMessage1.param0=4;
    testMessage1.param1=7;
    testMessage1.param2=2;
    testMessage1.type = MESSAGE_RES;
    
    int encodeTest1;
    char encodedMessage1[MESSAGE_MAX_PAYLOAD_LEN];   //space to save message
    
    encodeTest1=Message_Encode(encodedMessage1,testMessage1);

    printf("Message_Encode returned:%safter being fed(RES,4,7,2). Checksum should be 75.\n",encodedMessage1);
    
    printf("Length of encodedMessage1 = %d\n",encodeTest1);
    
    //new testMessage variable with new values to test Message_Encode again
    Message testMessage2;
    
    testMessage2.param0 = 2;
    testMessage2.param1 = 5;
    testMessage2.type = MESSAGE_SHO;
    
    int encodeTest2;
    char encodedMessage2[MESSAGE_MAX_PAYLOAD_LEN];
    
    encodeTest2 = Message_Encode(encodedMessage2,testMessage2);
    
    printf("Message_Encode returned:%safter being fed (SHO,2,5). Checksum should be 53.\n",encodedMessage2);
    
    printf("Length of encodedMessage2 = %d\n",encodeTest2);
    
//********BEGIN MESSAGE_DECODE TESTING***************************************************
    BB_Event *decodeData = (BB_Event *)malloc(sizeof(BB_Event));
    int decodeTest;
    decodeTest = Message_Decode('$',decodeData);
    
    if(decodeTest){
        printf("Success, Message_Decode returned SUCCESS\n");
    }else{
        printf("Failure\n");
    }
    
    //pass in our payload
    
    decodeTest = Message_Decode('R',decodeData);
    
    decodeTest = Message_Decode('E',decodeData);
    
    decodeTest = Message_Decode('S',decodeData);
    
    decodeTest = Message_Decode(',',decodeData);
    
    decodeTest = Message_Decode('4',decodeData);
    
    decodeTest = Message_Decode(',',decodeData);
    
    decodeTest = Message_Decode('7',decodeData);
    
    decodeTest = Message_Decode(',',decodeData);
    
    decodeTest = Message_Decode('2',decodeData);
    
    decodeTest = Message_Decode('*',decodeData);
    
    decodeTest = Message_Decode('7',decodeData);
    
    decodeTest = Message_Decode('5',decodeData);
    
    decodeTest = Message_Decode('\n',decodeData);

    if((decodeData->type == BB_EVENT_RES_RECEIVED)){
        printf("MessageDecode successfully decoded message\n");
    }else{
        printf("MessageDecode failed\n");
    }
    
    while (1);
    
}
