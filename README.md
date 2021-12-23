Created by: adi-joshi <br />
Date: 28 Dec 2020 <br />
Enjoy! <br />


# Hi!

Welcome to my Typing Test. This is a simple version of the typing test program. It uses the in-built clock provided in the time.h module in C.

## **Download:**
You can clone the repository onto your local device by using the command: ``` git clone https://github.com/adi-joshi/Typing-Test-Simple```

## **Using the Typing Test:**
You will need a C compiler (preferrably gcc) to compile project. You will also need the ncurses library. If you have these, follow the steps:
- Open your Terminal window.
- Navigate to your "typetest" folder on terminal (you can type the command ```cd **PATH/NAME/**```, or you can type ```cd ``` and drag and drop the folder into your terminal window)
- Type ```make``` into your terminal. This will generate a binary file called "typetest".
- To start the typing test, type ```./typetest``` into your terminal and press enter.
- The program will start running in a terminal window.

## **How it works:**
The typing test uses a wordlist. It prints out random words from that list. You can then type the words on your terminal window. After you press enter, it will output your WPM, and your mistakes.

## **Wordlist:**
If you want to use your own wordlist, it must follow the following rules:
- 1 word/quote per line
- A newline after every word/quote

_In practice, any wordlist that follows the above rules will work._

## **Customizing:**
You can customize the typing test with the following command line switches:
- ```-w=path/to/wordlist.txt```: This switch changes the wordlist used for the typing test from the default one to the one you specify. An example use is ```-w=words2.txt```.

- ```-t=[n]```: This switch changes the number of words that appear in the test. An example use is ```-t=20```. 

A typical example of customizing would be to create the typing test binary, and
then run in a manner similar to the following: ```./typetest -t=20 -w=words2.txt```

## **Resources:**
- 1000\_most\_common\_words.txt: Words in file taken from github gist gist.github.com/deekayen/4148741 by user deekayen.

Any and all feedback is appreciated!.
