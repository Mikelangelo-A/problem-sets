# Problem sets

A short run-down of the problem sets I completed during the CS50 course. There were plenty more, but those were fairly simple programs, which I didn't feel were important enough to showcase here.

Easyfilter problem set taught me how image filters work and how to create simple filters of my own.
Created filters were : Sepia, Grayscale, Reverse and Blur filters.

Plurality and runoff are programs for determining the winner in different types of voting systems.
Plurality is a simple system where the person with the highest amount of votes is the winner.

Runoff features a ranked-choice system, where the voter can vote for their top 3 candidates in order of preference.
In short, if a candidate has more than half of votes from people as their main candidate, then he is the winner. If not, the candidate with the lowest amount of votes gets eliminated,
and then anyone who voted for that candidate will have their next choice evaluated. This continues on until one candidate gains a majority of the votes.

The speller problem set is one of my favorites. It is a program which spell-checks a given text, returing the amount of words and misspelled words in the text. The program takes in two text files, the first one being a dictionary of words, with one word per each line, and the second text file being the text to be spell-checked.
The program first loads in the dictionary into a hash table. It reads the dictionary, then, using a hash function, determines the index for the word in the hash table. If a word has already been placed at that index, the new word is attached to that index using a pointer from the previous word, making a linked list for each index.
Afterwards, the program goes through the given text file, reading every word(any combination of letters that ends with a space.) and checks, whether or not the given word is in the dictionary. It does so by firstly, making the word lower-case, then hashing the word, and seeing if the same word exists at that index of the array. It checks until the word is found(true), or the pointer in the linked list at the index is pointing to NULL, in which case, it returns false.
The program consists of a few files. Most of the code in the file "speller.c" was distributed as part of the CS50 course, and it is primarily for benchmark purposes. This was not written by me. The main functions of the program are written in the file "dictionary.c" which has been writted by solely me. Other files are for declaring the functions used in the program. 
