Jose Santiago jlsantia@ucsc.edu
Partner: Karla
*My repo contains the final version

I wrote :
Message.c 
FieldTest.c

I didn't get to learn how the battleboats architecture worked at the top level.
I wrote the full message module though. The message module pretty much just
encoded and decoded messages. The function Message_CalculateChecksum was not 
too difficult i just made a helper function that converted converted the ascii
characters from the payload string to their 8bit integer equivalent. I did this
by masking the ascii character with every single digit of the possible 8. I used
a for loop with an increment variable i to keep track of what bit I was storing. 
The mask was shifted according the the bit that was being stored. I stored them
by setting the bits(ORing). After converting every character in the string, the
function returned the 8 bit representation of the asciis in a uint8_t variable.
Then within My Checksum function I XO'red every 8 bit number the conversion 
function would return as I fed it characters from the payload string. 
checksum function was pretty useful for the parsing message function.
The Message_Parsing function was used to compare the payload string and the checksum
string. For this function I had to make another helper function. One to convert
the ascii hex representation of the checksum string to its 8 bit representation
and one to generate a ascii hex string for my functions. In the conversion
it was simply subtract a certain amount from the 8 bit number if its greater than the 
ascii value of 0(48) but less than the ascii value of 9(57). Those numbers would
be subtracted by 48 to be converted to their int decimal values. I did this for
characters between the values of the ascii characters A through F the same way
I did it with the ascii chars 0-9. The main purpose of the function is to see
if the payload string and checksum string match. I take the checksum of the payload 
with my previous helper function, then I convert my checksum string into it's 
8 bit value as well and see if they are equal. If they are I continue to see if
the string contains a valid message. For that I checked every single char one at
a time. If it matches one of the valid first chars of a message, if at any moment
an invalid char that does not lead to a valid message is fed, the function exits
and returns a STANDARD_ERROR. This function just reads the message and returns
a coresponding boat event after, as well as storing the data that the message
contained. The encode function takes in a BB_Event to convert into a message 
string. For this I needed to use the wrappers defined in the .h file. I used
sprintf() to wrap my messages in this function. I made local arrays to hold the
seperate payload info and checksum info. Then I used sprinf() again to store them
all together using the message template. After figuring out the helper functions, 
this function was not too bad. Then I did MessageDecode which i was confused about.
I wasn't so sure about the input and output. But it made sense when I saw that 
it took in a different data type from encode. Encode used BB_Events while Decode
used the Message datatype. For decode i didn't have to think as much about the 
structure of the code. With the picture of the state machine I was able to complete
the function without much trouble. I ran out of time for this project but I am happy
with the work I did get done. 