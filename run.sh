
if [ $1 == "log" ]
then
	valgrind --leak-check=full --show-reachable=yes --error-limit=no --suppressions=./valgrind-readline.supp --gen-suppressions=all --log-file=minishell.log --track-fds=yes ./minishell
else
	valgrind --leak-check=full --show-reachable=yes --error-limit=no --suppressions=./valgrind-readline.supp --gen-suppressions=all --track-fds=yes ./minishell
fi
