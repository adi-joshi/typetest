Created by: adi-joshi <br />
Date: 28 Dec 2020 <br />
Enjoy! <br />


# Hi!

Welcome to my Typing Test. This is a simple version of the typing test program. It uses the in-built clock provided in the time.h module in C.

## **Download:**
You can clone the repository onto your local device by using the command: ``` git clone https://github.com/adi-joshi/Typing-Test-Simple```

## **Using the Typing Test:**
You will need a C compiler (preferrably either gcc or clang) to compile the typing\_test.c file. After you have a compiler, follow the steps:
- Open your Terminal window.
- Navigate to your "Typing-Test-Simple" folder on terminal (you can type the command ```cd **PATH/NAME/**```, or you can type ```cd ``` and drag and drop the folder into your terminal window)
- Compile the "typing\_test.c" file (example: if you are using the gcc compiler, you can type ```gcc typing\_test.c -o ttc```. This will compile the typing\_test\_copy.cto an executable named "ttc")
- Type the command ```./ttc``` or double click on the ttc executable to run the program.
- The program will start running in a terminal window. Follow the instructions on the screen to start the test. 

## **How it works:**
The typing test uses a wordlist/quotelist. It prints out random words/quotes from that list. You can then type the words on your terminal window. After you press enter, it will output your WPM, and your mistakes.

## **Wordlist:**
The wordlist I used will be uploaded shortly.

If you want to use your own wordlist, it must follow the following rules:
- 1 word/quote per line
- A newline after every word/quote

_The above wordlist was the one used in testing. In practice, any wordlist/quotelist that follows the above rules will work._

## **Customizing:**
You can customize the program to your liking. The following are some ways you can change the typing-test.
- Number of words: You can change this by changing the global constant TIMES to the number of words that you would like. (_If you are using quotes, change this constant to 1_) As the timer can only count seconds (not milliseconds), I would suggest to keep the number of words high (>20) to have a relatively accurate test result.
- Different wordlist/quotelist: If you are using another wordlist/quotelist, make sure that the longest line is less than 50 characters (if it is, then change the global constant MAX\_WORD\_LEN to the appropriate number of characters). Also, change the variable "dir" in the main function to the path to your new wordlist/quotelist. 

Any and all feedback is appreciated!.
