NAME
	myshell

OVERVIEW
	Description - A brief introduction to the shell
	Supported Commands - A list and short description of internal commands
	Other Commands - A description of how external commands are taken
	Batch Mode - How the shell takes in batch files
	I/O Redirection - How the shell's I/O redirection works
	Background Execution - How background execuation can be used for the shell's other commands
	
Description
	This is a simple shell written in the c language. It supports eight internal commands while
	while all other external commands are preformed using the exec() function. The shell is
	able to take its command line inputs from a batchfile which contains a set of commands
	to be completed by the shell. The shell is also capable of supporting i/o redirection
	on stdin or/and stdout. Finally the shell supports the background execution of programs.

Supported Commands
	The shell supports the following internal commands:
		cd - changes the current directory to the supplied directory. If the directory
		is not present or a directory is not supplied it is reported to the user. The
		command also changes the environment variable PWD to the new path.
		It is used as follows:
		cd <directory>

		clr - The clr command will clear the sceen of all text
		It is used as follows:
		clr

		dir - The dir command will list the contents of the current directory or if a
		directory is supplied it will list the contents of that directory. If the supplied
		directory does not exis an error will be reported.
		It is used as follows:
		dir <directory>

		environ - The environ command will list all the environment strings
		It is used as follows:
		environ

		echo - The echo command will return the following supplied string from the user
		followed by a newline character. multiple spaces and tab characters will be reduced
		to a single space.
		It is used as follows:
		echo <string>

		help - Displays this user manual to the size of the user's screen and asks the user
		to press space to continue to see the rest of the manual or q to quit. The user
		can also press the enter key to see the next line.

		pause - The pause command will pause the operation of the shell and wait until the
		enter key is pressed
		It is used as follows:
		pasue

		quit - The quit command will quit the shell.
		is is used as follows:
		quit

Other Commands
	These are commands that are not in the shell but are still supported through the use of
	fork and exec. These commands can be written in the same way as they would be written on
	the parent shell and will produce the same output.

Batch Mode
	The shell is able to take its command line input from a file (batch file) such that,
	./myshell batchfile
	where batchfile contains a set of command lines for the shell to process, will produce the
	output for those individual command lines. When the end of the file has been reached the
	shell will exit. If a batchfile is not supplied the shell will take input from the user
	as usual.

I/O Redirection
	The shell supports i/o redirection on both or either stdin stdout. For example the command
	line:
	programname < inputfile > outputfile
	will execute the programname taking the input from the inputfile and then sending the output
	into the output file.
	for output redirection if the redirection character is > then the output file is created if
	it does not exist or is truncated if it does. If the redirection character is >> then the
	output file is created if it does not exist or is appended with the output if it does.

Background Execution
	The shell supports background execution on non-internal commands only. an & character
	supplied at the end of the command line indicates that the shell should return to the 
	command line straight away after launching the program such that the program will continue
	to run in the background.


