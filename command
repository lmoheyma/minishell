
https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit#gid=0


derniere choses a faire ou qui bug :
	Les exitcodes de Ctrl\ dans cat
	Les heredocs
	# echo hola ||| cat => erreur ! + exitcode
	ech|o hola | cat  => exitcode | J ai teste on a la meme que le bash ?
	echo hola > > bonjour => exitcode | tokens.c l: 103

	rm -rf a
	minishell:/home/aleite-b/Documents/minishell-git/a/b$ unset PWD
	minishell:/home/aleite-b/Documents/minishell-git/a/b$ cd reyetyet
	cd: No such file or directory
	[1]    201318 segmentation fault (core dumped)  ./minishell

		echo hola > ../bonjour
	echo hey > ../hello
	>../bonjour >../hello <prout
	cat ../bonjour ../hello
	 	=> Des fd restent ouvert
	
	# Le echo $? ou echo$VAR leak

	exit 9223372036854775808   => numeric arg required ?
	exit -9223372036854775809

Commande qui marche pas :
ECHO ->

	echo $?$
	echo $9HOME


$ ->
	$HOME        => bash: /home/lmoheyma: Is a directory

ENV & EXPORT & UNSET ->
	EXEC ->
		export | grep HOME   => car pas fork => Fork export ?
	PARSING ->
		export HOLA='""' + echo " $HOLA " | cat -e 
		echo $HOLA$HOLA$HOLA=hey$HOLA

		# export HOLA="  bonjour  hey  "
		# echo """$HOLA""" | cat -e
		# echo wesh"$HOLA" | cat -e
		# echo wesh""$HOLA.
		# echo wesh$"HOLA HOLA".

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


PIPE ->
	PARSING ->
		cat a | <b cat | cat > c | cat  => mauvaise sortie d'erreur'
	
REDIRECTIONS ->
	>bonjour echo > hola>bonjour>hola>>bonjour>hola hey >bonjour hola >hola  => execve: text file busy
	echo hola > bonjour hey   => execve: text file busy
	>bonjour <prout hello     => execve: text file busy

\	export HOLA="bonjour hello"
	>$"HOLA"
	ls
	>$HOLA>hey
	>hey>$HOLA>hey>hey


SAVE


	while (minishell->tokens)
	{
		printf("Token : %s - %s\n", minishell->tokens->content,
			minishell->tokens->type);
		minishell->tokens = minishell->tokens->next;
	}