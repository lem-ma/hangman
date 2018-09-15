# Hangman #
This is an implementation of the traditional hangman game.
### Install ###
Simply compile ```hangman.c``` to obtain the executable. Just beware that you must have put a wordlist in your current directory as for the program to choose words from. Every line in the word list file must be in the following form:

```<Single word with or without hyphen><space><definition of the word>```

If you do not have such a file, then you may download as well the ```wordlist.txt``` in the repository.

### Usage ###
If your word list is called ```wordlist.txt```, then simply run the program suffices. If not, you could also type ```hangman myfile``` (replace ```hangman``` with the executable name that you compiled, and replace ```myfile``` with the name of your word list file) to start the game.

You will have 6 chances to (wrongly) guess a character in the word. The remained number of chances and unveiled letters, as well as the letters you have guessed will be shown before you are prompted to guess. During each time of input, only the first character that you typed will be treated as your input, and others will be discarded. Anytime during the game, typing ```<Tab><Enter>``` shall end the game.

After the end of game, the word and definition will be shown, during which time you will be prompted to decide whether or not you want to play a new game.
