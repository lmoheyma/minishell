
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

	# Rajouter condition au debut de la creation de token pour faire passer les variables d'environnement qui existent et return celles qui sont vides et sans rien derriere

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
	PARSING ->
		env|"wc "-l   => "wc -l" command not found
		expr $? + $?  => non integer argument

EXIT ->
	EXEC ->
		exit 9223372036854775808   => numeric arg required ?
		exit -9223372036854775809

PIPE ->
	PARSING ->
		cat a | <b cat | cat > c | cat  => mauvaise sortie d'erreur'
	
REDIRECTIONS ->
	>bonjour echo > hola>bonjour>hola>>bonjour>hola hey >bonjour hola >hola  => execve: text file busy
	cat <pwd  => No such file or directory & return
	cat <src/pwd
	cat <../pwd
	cat < ls
	cat < ls > ls
	cat > ls1 < ls2
	echo hola > bonjour hey   => execve: text file busy
	>bonjour <prout hello     => execve: text file busy

\	export HOLA="bonjour hello"
	>$"HOLA"
	ls
	>$HOLA>hey
	>hey>$HOLA>hey>hey

