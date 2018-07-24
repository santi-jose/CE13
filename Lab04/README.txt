Jose Santiago (jlsantia@ucsc.edu)
In this lab we used an array of structs to build the Abstract data type known
as the stack. We implemented the library for stack operations such as StackPush
and StackPop. After this we created RPN_Evaluate to parse the string and 
determine which operation to perform. After that I tesed the functions and 
then used the main to see how the calculator works. I got it to work, but I 
couildn't figure out how to handle the error messages. I would get two different
error messages in one rpn calculation.

I read the lab manual first. And then from there I just went in and started
trying out the stack functions. The stack functions didn't take too long. The
rpn function took the longest. I couldn't figure out how to determine if a token
was an operator, but I found that they shared the value 0, but only the ascii '0'
would be pushed onto the stack. That means all else would have to be an invalid
operator or an invalid operand. I wish there were more lab times to ask questions.

In the end the rpn calculator works as it should, it just can't output the 
proper messages for the different errors possible. I tested all my stack and rpn'
functions twice. I'm satisfied with the final product even if I didn't finish. 
I feel like i learned a lot.
