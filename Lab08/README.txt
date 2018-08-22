Jose Santiago jlsantia@ucsc.edu
Collaborator: Karla
Magic Number: 89

In this lab we used the abstract data type the binary tree to 
make a Morse decoder. A dash would indicate a rightward traversal of 
the tree while a dot would be a leftward traversal. This was the method
we used to decode the sequence of dots and dashes in morse code. We used
the relationship between the length of the button4Down event to 
let us know if a dot or a dash event occurs. Then from there we set seperate
events depending if it's waiting for a new letter or new word.

MorseDecodewas tricky to get because I didn't know how to use the MorseTree
that I created in MorseInit(); in my MorseDecode(); function. But after making
my morseTree node static it let me use it throughout the file. After that it 
was only a matter of checking for the proper edge cases and returning the 
appropriate events as they happened. My MorseCheckEvents(); function worked
when it received input for a DOT and a DASH via a press shorter and longer
than a half second. The only thing that might be an issue is that it kept
returning a MORSE_EVENT_NONE and never returned the new letter or new word
events. I couldn't get it to return that, but it should  be working properly 
otherwise. 

For this lab I used the manual to get a general idea about what I was supposed
to do. Then I used whatever resources available to me to get BinaryTreeCreate 
because that function was really hard. Other than that I just needed help 
figuring out how to traverse my MorseTree in other functions but once I set the
root node pointer to static it fixed everything. The lab manual was the most 
vague it's been all year but it makes sense since this lab was so conceptual.


