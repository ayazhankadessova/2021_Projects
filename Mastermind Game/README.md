# Mastermind Game Guide:

Mastermind works by having one player, the code maker, create a 4-digit code from 8 available digits ('0' '1' '2' '3' '4' '5' '6' '7') through -c command. 

If the mastermind chooses not to create a code themselves, the computer will generate a random code. 

The second player, or codebreaker, tries to break the code in the number of turns specified by the code maker through -t command. 

If the code is not specified, the player gets 10 attempts by default. 
if the function parameters are wrong inputs, such as '01234' - too long, random parameters are generated.

The codebreaker makes a guess, and the code maker gives them feedback after each guess. 
The feedbacks contains two parts: the number of well-placed pieces and the number of misplaced pieces.

If the codebreaker inserts a wrong type of input, such as '12345' – too long, '12' - too shorts, '1123' - contains repeated integers, '12y3' – includes a non-integer, '1238' – contains integers that are not within the range of 0 to 7, the computer shows the type of error and asks the player to use better numbers. 
Such input errors are not added to the attempts count. 

If the player finds the code in the available number of turns, they win, and the game stops. 
Otherwise, the player loses, and the code maker wins.

* Example:

```
PROMPT>./my_mastermind -c "0123"
Will you find the secret code? Guess the 4 digit number: ?
---
Round 0
>1456
Your results are:
Well-placed pieces: 0
Misplaced pieces: 1
---
Round 1
>tata
Wrong input!
>4132
Well-placed pieces: 1
Misplaced pieces: 2
---
Round 2
>0123
Great! You guessed the number! You're a Mastermind!
```