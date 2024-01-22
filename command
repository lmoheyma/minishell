
https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit#gid=0


Commande qui marche pas :
ECHO ->

	echo $?
	echo $?$
	echo $9HOME


$ ->$DONTEXIST
	$HOME        => bash: /home/lmoheyma: Is a directory
	$HOMEdskjhfkdshfsd
	$DONTEXIST

ENV & EXPORT & UNSET ->
	EXEC ->
		export | grep HOME   => car pas fork => Fork export ?
	PARSING ->
		export ""   => not a valid identifier => if a rajouter
		export $?   => expander du $?
		export HOLA='""' + echo " $HOLA " | cat -e 
		echo $HOLA$HOLA$HOLA=hey$HOLA

		export HOLA="  bonjour  hey  "
		echo """$HOLA""" | cat -e
		echo wesh"$HOLA" | cat -e
		echo wesh""$HOLA.
		echo wesh$"HOLA HOLA".

		export HOLA=bonjour
		export HOLA=" hola et $HOLA"
		echo $HOLA

		export HOLA=bonjour
		export HOLA=' hola et $HOLA'
		echo $HOLA

		export HOLA=bonjour
		export HOLA=" hola et $HOLA"$HOLA
		echo $HOLA

		export HOLA="l" 
		$HOLAs   => mauvaise sortie d'erreur'

		export HOLA="l" 
		"$HOLA"s    => execve: permission denied ??

		export HOL=A=""
		env      => strlcpy de export, prblm de len

		$HOLA"BYE"d  => mauvaise sortie d'erreur'

		"$HOLA"'$BYE'd  => permission denied ??
		"$HOLA""$BYE"d
		$"HOLA"$"BYE"d  => mauvaise sortie d'erreur'
		$'HOLA'$'BYE'd

		export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8
		echo "$A'$B"'$C"$D'$E'"$F'"'$G'$H"

BATARDS ->
	EXEC ->
		Gerer les fichiers executables
		touch hola
		./hola
		env -i
		env
	PARSING ->
		env|"wc" -l   => parsing des quotes
		env|"wc "-l   => parsing des quotes
		expr $? + $?

EXIT ->
	EXEC ->
		exit 9223372036854775808   => numeric arg required ?
		exit -9223372036854775809
	PARSING ->
		A TESTER DE 502 A 514 APRES LE PARSING

PIPE ->
	EXEC ->
		cd .. | pwd
		cat Makefile | grep pr | head -n 5 | cd rgrger   => bash: cd: file_not_exist: No such file or directory
		time sleep 3 | sleep 3   => affichage bug ?
		sleep 3 | exit  => apparait au bout de 3sec
	PARSING ->
		cat a | <b cat | cat > c | cat  => mauvaise sortie d'erreur'
	
REDIRECTIONS ->
	