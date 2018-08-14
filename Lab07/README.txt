Jose Santiago jlsantia@ucsc.edu
Collaborator: Karla
Magic Number: 192.168.1.1

In this lab we had to implement the logic to implement an oven display onto our
Uno32 OLED's. We had to use a Finite State Machine to continuously poll for our 
STATES dependent on the value my switch()case: statement had. These states
were SETUP, COOKING, SELECTOR_CHANGE_PENDING, and RESET_PENDING. Within my 
states I set up flags which are continuously checking for hardware input from
our Uno32. Whenever our button or ADC events are triggered we transition to 
the appropriate state. We save our user input and dependent on TIME and TEMP we
convert our value from the ADC read using the top 8 bits. We also use this value
to get our LED's to countdown. I have yet to implement this, but I have a good
idea of how to get it done so I'll try using some late hours to perfect it. I was
going to store the eight of the cookTime input by the user and mod it by my 
eighth I stored earlier and if it was equal to 0 I know an eighth has passed. 
Therefore counting the LED's down. I think the most important aspect of this
lab was to stay organized and not get lost. It was beneficial to me to 
compartmentalize my state machine with helper functions. 

I wrote this lab as I read the manual. I feel for me I learn the best as I go.
Taking time to read distracts me and makes the work flow slow. Talking and asking
questions helps me more. It was a fun lab. If I were to do anything different for
this lab I would simply ask for some help with the time countdown  because I 
can't seem to find out why my time is counting down so fast. 

In the end I was pleased with how neat my code ended up. I didn't implement 
everything but I was happy with how it turned out. I'll try to use late hours 
to fix it. The lab manual was very vague. There was a lot that was left out that
was very confusing. What I felt was most challenging was following your code and
not getting lost when debugging. I alleviated this problem by making neat 
helper functions. 