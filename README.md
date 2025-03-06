Word Definition Storage

Requirements:
needs a separate file named "WordSave.txt" to read and write from
uses 'windows.h' header to clear the terminal

Compilation:
with a c++ compiler - "g++ -o wordDef wordDef.cpp"

Execution:
for windows - "wordDef.exe"

Commands:
Program_exit - saves all current words and definitions, then exits the Program
Progam_List - lists all words currently saved
<word> - will list definitions and start a separate loop. if no definitions, it will prompt for definitions then return to main loop
While in a selected word loop:
    exit - returns to the main loop
    erase <index> - erases the definition at the given index
    erase all - erases all definitions for the word
    list - Lists all definition for the word
    add <number> - starts a loop to add <number> definitions

Example:
    'Hello'
    //prompts for definition/s
    'def 1'
    'def 2'
    'def 3'
    'done'
    'Hello'
    //lists definitions and starts separate loop
    'erase all'
    //erases all definitions
    'exit'
    //returns to main loop
    'Program_exit'
    //closes Program

Author - Ian Danforth