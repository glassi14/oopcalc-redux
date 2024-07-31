# Order of Operations Calculator Redux
This is just a personal project of mine that I'm using to learn C++.
This program is to be run in the terminal and will solve any expression in proper order of operations, and can be ran with a few arguments.
There is basic error handling and the program supports the operations: addition, subtraction, multiplication, division, modulo and exponents.
The program also successfully handles parenthesis, however, does not understand that two statements in parenthesis are meant to be multiplied.

# Arguments
Call the built .exe into your terminal. Type your expression in quotes to prevent the terminal from unsuccessfully passing the expression. From there you can call:


"-help" or "--help" to bring up the help menu and terminate the program.

"-i" to print the infix notation form of your expression.

"-p" to print the postfix notation form of your expression.


For arguments passed that aren't the ones listed above, the program will assume that the arguemnt is your expression.

# Operators
+: Addition

-: Subtraction

*: Multiplication

/: Division

%: Modulo

^: Exponent

Parenthesis "(" and ")" are valid inputs. Floats inputted with "." are supported inputs, however, currently floats are converted into ints so it isn't of much use yet.

# Examples
Input: ./oopcalc-redux.exe "(5+5)\*5+5" -i -p

Result: "Infix: (5+5)\*5+5 Postfix: 55+5\*5+ Result: 55"

Input: ./oopcalc-redux.exe "5^5+(10/2)-5000" -p

Result: "Postfix: 55^102/+5000- Result: -1870"

# Planned Features
Support for inputted negative numbers.

Support for float results.

Support for parenthesis multiplication. (Allowing (5)(5) to return 25 instead of throwng an error)

# Known Bugs
???
