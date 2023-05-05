# Minishell

## 🗣️ About 

Minishell is part of the School 42 cursus. The goal is to create a fully functionnal shell looking like bash.

It includes the following features :

⇢ Parsing of the user input <br> 
⇢ History of user inputs <br>
⇢ Pipes (```|```) and Redirections (```<```, ```>```, ```>>``` and ```<<```) <br>
⇢ Launching command based on the PATH variable of the environment or builtins <br>
⇢ Launching command as a builtin <br>
⇢ Signals <br>
⇢ Miscellaneous <br>

More information can be found on the subject PDF.

## 🛠️ Description of features

### Parsing and History

Parsing uses the ```readline``` library. Readline contains the ```getline```function that will display a prompt and store the user input in a char**. Parsing is done using tokenisation, a method of that cut a string into various tokens, that are basically lexical units. In our approach, we 'cutted' every token based on spaces and/or metacharacters such as ```<``` or ```|```. Basically, ```echo something``` will be cutted into two tokens, ```echo``` and ```something```, because of the space between the two 'words'. However, ```echo something|cat truc``` and ```echo something | cat truc``` will both result in a total of 5 token (```echo```, ```something```, ```|```, ```cat``` and ```truc```) because ```|``` is a metacharacter and therefore need to be treated as such. Note that simple quotes inhibit all metacharacters and double quotes inhibit all metacharacters except ENV variables (the ```$``` sign).

Minishell also provides an history with the history function provided by readline that allows the user to access previously entered commands, like in bash.

### Pipes and redirection

Once the user command has been parsed, the program performs redirections and pipes. Pipes are tools that are made to enable communication between processes. Therefore, they allow a given process to send and receive data from another process, and vice versa. Pipes are useful when you want to send the output of a first command to another command. For instance, ```echo truc stuff | grep truc``` will send the output of ```echo truc stuff``` to ```grep```. Note that you can have several pipes in one command.

Redirections are quite similar to pipes as they modify the standard input and standard output. Operator ```>>``` wil redirect the standard output in append mode (i.e. will add something without suppressing previous content). Operator ```>``` will redirect the standard output, suppressing any kind of data present before. The operator ```<``` will redirect the standard input and ```<<``` will open an here-document. For an explication about what is an here-doc and how it works, please check this resource : https://linuxize.com/post/bash-heredoc/.   

### Command Launcher

Minishell can of course execute commands (it is its main purpose, after all !). There are two cases : 1) the command is an external program present in the OS file system, or 2) is a built-in. Built-ins are commands that are part of the Minishell program. In that case, it is quite simple : Minishell simply execute the function. Built-ins in Minishell includes :

◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options

Please check the manual (command ```man <command_name>``` in a terminal) to have more information. 

If the command is not a built-in, the program will parse the ENV variable named ```PATH``` that can be retrieved using the ```**envp``` variable present in the main function. Minishell will fork and spawn a child process that will execute ```execve``` to launch the command and retrieve its exit status using ```waitpid```. The ```access``` function is used to check every path and returns an error if the function does not exist or is not executable. Note that the exit status are the excactly the same as they are in Bash.

### Signals

Minishell handle signals just as bash does ! Therefore, Ctrl-D exits the shell, Ctrl-C display a new prompt on a new line and Ctrl-/ does nothing.

Note that our implementation of a shell is completely leak free (apart maybe for some third-parties librairies such as Readline) and therefore should not suffer from any performance issue, even in case of prolonged use. 

### Miscellaneous

Apart from the main features presented before, Minishell is able to retrurn the same error code as bash does, ranging from 0 to 128. Minishell is also able to return this error code using the ```$?```.

## 💿 Compilation and Execution

To compile the program, use ```make``` and the Makefile will create an executable named ```./minishell```. Simply execute ```./minishell```to launch the program. You can know use our fully functional custom shell !

## 🗑️ Deletion

To completely destroy any obj file and the executable, use the ```make fclean```command. To simply get rid off obj file without destroying the executable, use ```make clean```.

## ✅ Validation

This project has been validated with a mark of 101/100 (with bonus).

Thanks for reading us ! 
