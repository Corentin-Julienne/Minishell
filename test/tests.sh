#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tests.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 12:54:17 by cjulienn          #+#    #+#              #
#    Updated: 2022/06/06 20:57:57 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MINISHELL AUTOMATIC TESTING PROGRAM

# This program is designed to automatically test the input of minishell by comparing the output with the 
# output of bash
# NOT TO BE INCLUDED IN THE FINAL REPOSITORY !!! 

# COLORS (BOLD)
GREEN="\033[1m\033[32m"
RED="\033[1m\033[31m"
YELLOW="\033[1m\033[33m"
CYAN="\033[1m\033[36m"
BLUE="\033[1m\033[34m"

# reset and end
RESET="\033[m"
END="\e[0m"

# SCRIPT PREPARATION

make -C ../ # trigger minishell make
cp ../minishell . # make a copy of minishell in the current directory
chmod 777 minishell # make sure we are not bother by access restrictions

# DEFINING TEST FUNCTION

function test_and_compare()
{
	TEST_BASH=$(echo $@ | bash 2>>err_log.txt 1> bash_output.txt)
	TEST_BASH_EXIT=$(echo "exit" | bash)
	ES_BASH=$? # exit should give the last exit code
	TEST_MINI=$(echo $@ | ./minishell 2>>err_log.txt 1> mini_output.txt)
	TEST_MINI_EXIT=$(echo "exit" | ./minishell)
	ES_MINI=$? # exit should give the last exit code
	
	echo $BLUE"-----------------------------------------------------------------\n"$RESET
	printf "$CYAN ==> input tested : [$@]$RESET\n"
	echo $BLUE"comparing exit status..."$RESET
	if ! [ "$ES_MINI" -eq "$ES_BASH" ]; then # check if exit status is the same
		printf $RED"Your exit status     : $ES_MINI$RESET\n"
		printf $GREEN"Expected exit status : $ES_BASH$RESET\n"
	else
		printf $GREEN"Minishell exit status OK !\n"$RESET
	fi
	echo $BLUE"comparing error messages (if any)..."$RESET

	echo $BLUE"comparing outputs..."$RESET

	if [diff bash_output.txt mini_output.txt]; then
		echo $RED"Output of minishell and bash are different"$RESET
	else
		echo $GREEN"Output of minishell is equal to bash"$RESET
	fi
	
	# echo $BLUE"Summary of results..."$RESET
	# if ! [ "$ES_MINI" -eq "$ES_BASH" ]; then
	# 	printf "" ""
	# else
	# 	printf "" ""
	# fi
	echo $BLUE"Testing procedure finished for this input"$RESET
	
	# rm ./err_log.txt # remove err_log file when not needed



	# if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
	# 	printf " $BOLDGREEN%s$RESET" "✓ "
	# else
	# 	printf " $BOLDRED%s$RESET" "✗ "
	# fi
	# printf "$CYAN \"$@\" $RESET"
	# if [ "$TEST1" != "$TEST2" ]; then
	# 	echo
	# 	echo
	# 	printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	# 	printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	# fi
	# if [ "$ES_1" != "$ES_2" ]; then
	# 	echo
	# 	echo
	# 	printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
	# 	printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	# fi
	# echo
	# sleep 0.1
	# RES_MINI="echo $@ | ./minishell" # execute minishell with provided args
	# EXIT_MINI=$? # minishell exit status
	# echo "$EXIT_MINI"
	# RES_BASH="echo $@ | bash" # execute bash with provided args
	# EXIT_BASH=$? # bash exit status
	# echo "$EXIT_BASH"
	
	# printf "$CYAN%s\n$RESET" "$@" # print args of the current test
	
	# # if [diff outfile_mini.txt outfile_bash.txt] && [$EXIT_MINI == $EXIT_BASH]; then
	# # 	printf "$GREEN%s\n$RESET" "result = [✅]"
	# # else
	# # 	printf "$RED%s\n$RESET"   "result = [❌]"

	# # # if [$TEST_MINI != $TEST_BASH]; then # printf expected vs current minishell result
	# # # 	echo "$RED------------------------------------------------------------------------$RESET"
	# # # 	printf "${RED}your output is        : %s\n$RESET" "$TEST_MINI"
	# # # 	printf "${GREEN}your output should be : %s\n$RESET" "$TEST_BASH"
	# # # fi

	# if ["$EXIT_MINI" != "$EXIT_BASH"]; then # printf expected vs current minishell exit code
	# 	echo "$RED------------------------------------------------------------------------$RESET"
	# 	printf "${RED}your exit code is        : %s\n$RESET" "$EXIT_MINI"
	# 	printf "${GREEN}your exit code should be : %s\n$RESET" "$EXIT_BASH"
	# fi
	# echo "$BLUE------------------------------------------------------------------------$RESET"
	# echo
	# sleep 1 # is that really useful ?
}

# WELCOMING MESSAGE

echo   "$YELLOW------------------------------------------------------------------------"
printf "WELCOME TO THE MINISHELL TESTER !!!                                     \n"
echo   "------------------------------------------------------------------------$RESET"

# TESTS BATTERY

# this test battery use the test_and_compare function to assess if both results (minishell and bash) are equivalent
# to add a test, just use the following syntax : test_and_compare '[user input to give to the shell]'

# basic test to test the script

test_and_compare 'stub cred'

# [BASIC ONE COMMAND INPUT TESTS]

# [REDIRS TESTS]

# [PIPES TESTS]

# [REDIRS AND PIPES TESTS]

# [BULTINS SPECIFIC TESTS]

# 1) echo

# 2) pwd

# ENDING TEST GOODBYE

echo   "$YELLOW------------------------------------------------------------------------"
printf "THANKS TO HAVE USED THE MINISHELL TESTER !!!  GOODBYE !!!               \n"
echo   "------------------------------------------------------------------------\n$RESET"

# CLEANING MINISHELL USING MAKE FCLEAN

make -C ../ fclean  # trigger minishell make fclean
rm minishell        # rm minishell program
