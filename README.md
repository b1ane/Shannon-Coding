Problem:
 
For this assignment, you will create a multithreaded program using the Shannon coding data compression algorithm (https://en.wikipedia.org/wiki/Shannon_coding).
 
Given an input string representing the message to encode using the Shannon coding technique (the input string can have any symbol from the ASCII alphabet):
 
AAABAAABAAAAMMAAAAAU
 
The expected output is:
 
Message: AAABAAABAAAAMMAAAAAU

Alphabet: 
Symbol: A, Frequency: 15, Shannon code: 0
Symbol: M, Frequency: 2, Shannon code: 1100
Symbol: B, Frequency: 2, Shannon code: 1101
Symbol: U, Frequency: 1, Shannon code: 11110

Encoded message: 000110100011010000110011000000011110
 
Process:
 
Your solution must execute the following steps:
 
Read the n lines from STDIN, where each line has an input string to encode using the Shannon coding algorithm.
Create n POSIX threads (where n is the number of input strings). Each child thread executes the following tasks:
- Receives the input string used to encode the values.
- Creates the alphabet based on the received input string.
- Sorts the alphabet in decreasing order based on the symbols' frequency. If two or more symbols have the same frequency, you must sort them in decreasing order based on their ASCII value.
- Determines the Shannon codes for the symbols in the alphabet.
- Generates the encoded message by using the Shannon codes.
- Stores the alphabet (with the Shannon codes) and the encoded message on a memory location accessible by the main thread.
 
Print the information from the child threads into STDOUT.
 
Given the following input:

COSC 3360 COSC 1437
COSC 1336 COSC 2436
COSC 3320 COSC 3380
The expected output is:

Message: COSC 3360 COSC 1437

Alphabet: 
Symbol: C, Frequency: 4, Shannon code: 000
Symbol: 3, Frequency: 3, Shannon code: 001
Symbol:  , Frequency: 3, Shannon code: 010
Symbol: S, Frequency: 2, Shannon code: 1000
Symbol: O, Frequency: 2, Shannon code: 1010
Symbol: 7, Frequency: 1, Shannon code: 10111
Symbol: 6, Frequency: 1, Shannon code: 11001
Symbol: 4, Frequency: 1, Shannon code: 11010
Symbol: 1, Frequency: 1, Shannon code: 11100
Symbol: 0, Frequency: 1, Shannon code: 11110

Encoded message: 00010101000000010001001110011111001000010101000000010111001101000110111

Message: COSC 1336 COSC 2436

Alphabet: 
Symbol: C, Frequency: 4, Shannon code: 000
Symbol: 3, Frequency: 3, Shannon code: 001
Symbol:  , Frequency: 3, Shannon code: 010
Symbol: S, Frequency: 2, Shannon code: 1000
Symbol: O, Frequency: 2, Shannon code: 1010
Symbol: 6, Frequency: 2, Shannon code: 1011
Symbol: 4, Frequency: 1, Shannon code: 11010
Symbol: 2, Frequency: 1, Shannon code: 11100
Symbol: 1, Frequency: 1, Shannon code: 11110

Encoded message: 000101010000000101111000100110110100001010100000001011100110100011011

Message: COSC 3320 COSC 3380

Alphabet: 
Symbol: C, Frequency: 4, Shannon code: 000
Symbol: 3, Frequency: 4, Shannon code: 001
Symbol:  , Frequency: 3, Shannon code: 011
Symbol: S, Frequency: 2, Shannon code: 1001
Symbol: O, Frequency: 2, Shannon code: 1010
Symbol: 0, Frequency: 2, Shannon code: 1100
Symbol: 8, Frequency: 1, Shannon code: 11100
Symbol: 2, Frequency: 1, Shannon code: 11110

Encoded message: 0001010100100001100100111110110001100010101001000011001001111001100
 
