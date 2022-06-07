# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tests.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 12:54:17 by cjulienn          #+#    #+#              #
#    Updated: 2022/06/06 19:04:58 by cjulienn         ###   ########.fr        #
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
	TEST_MINI=$(echo $@ | ./minishell >> test_output.txt) # execute minishell with provided args
	EXIT_MINI=$? # minishell exit status
	TEST_BASH=$(echo $@"; exit" | bash >> test_output.txt) # execute bash with provided args
	EXIT_BASH=$? # bash exit status
	
	printf "$CYAN%s$RESET" "$@" # print args of the current test
	if ["$TEST_MINI" == "$TEST_BASH"] && ["$EXIT_MINI" == "$EXIT_BASH"]; then # we check if results are the same, giving feedback
		printf "$GREEN%s\n$RESET" "   [✅]"
	else
		printf "$RED%s\n$RESET" "   [❌]"
	fi

	if ["$TEST_MINI" != "$TEST_BASH"]; then # printf expected vs current minishell result
		echo "$RED------------------------------------------------------------------------$RESET"
		printf "${RED}your output is        : %s\n$RESET" "$TEST_MINI"
		printf "${GREEN}your output should be : %s\n$RESET" "$TEST_BASH"
	fi
	if ["$EXIT_MINI" != "$EXIT_BASH"]; then # printf expected vs current minishell exit code
		echo "$RED------------------------------------------------------------------------$RESET"
		printf "${RED}your exit code is        : %s\n$RESET" "$EXIT_MINI"
		printf "${GREEN}your exit code should be : %s\n$RESET" "$EXIT_BASH"
	fi
	echo "$BLUE------------------------------------------------------------------------$RESET"
	echo
	killall minishell # find a way to exit minishell ?
	sleep 1 # is that really useful ?
}

# WELCOMING MESSAGE

echo   "$YELLOW------------------------------------------------------------------------"
printf "WELCOME TO THE MINISHELL TESTER !!!                                     \n"
echo   "------------------------------------------------------------------------$RESET"

# TESTS BATTERY

# this test battery use the test_and_compare function to assess if both results (minishell and bash) are equivalent
# to add a test, just use the following syntax : test_and_compare '[user input to give to the shell]'

# basic test to test the script



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

make -C fclean ../ # trigger minishell make fclean
rm ./minishell     # rm minishell program
