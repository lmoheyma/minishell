Commande qui marche pas :
ECHO ->
	echo "-n" Hola
	echo \n Hola
	echo "       " | cat -e
	""''echo hola""'''' que""'' tal""''

	echo $
	echo $?
	echo $?$
	echo " $ " | cat -e
	echo ' $ ' | cat -e
	echo \$HOME
	echo my shit terminal is [$TERM4
	echo my shit terminal is [$TERM4]
	echo $UID (?)
	echo $HOME9
	echo $9HOME
	echo $SHLVL$HOME

	echo > <    => bash: syntax error near unexpected token `<''
	echo 
	>echo>
	<echo<
	>>echo>>
	|echo|
	|echo -n hola

$ ->
	$?
	$?$?
	$
	$HOME        => bash: /home/lmoheyma: Is a directory
	$HOMEdskjhfkdshfsd
	$DONTEXIST

SIGNAUX ->
	cat + Ctrl-C
	cat | rev + Ctrl-C
	cat + Ctrl-\   => ^\Quit (core dumped)
	sleep 3 | sleep 3 | sleep 3 + Ctrl-C (after 1s)
	sleep 3 | sleep 3 | sleep 3 + Ctrl-\ (after 1s)

ENV & EXPORT & UNSET ->
	export      => retirer le declare -x, ordre alpha et quote ?
	export | grep HOME   => car pas fork => Fork export ?
	export ""   => not a valid identifier => parsing des quotes
	export $?   => expander du $?
	export HOLA="bonjour        "   => parsing des quotes
	export HOLA="   -n bonjour  "   => parsing des quotes
	export HOLA="bonjour   "/   => parsing des quotes
	export HOLA='""' + echo " $HOLA " | cat -e 
	export HOLA="cat Makefile | grep NAME"

	A TESTER DE 300 A 330 APRES LE PARSING

	
	


