
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

SIGNAUX ->
	EXEC -> 
		cat + Ctrl-C
		cat | rev + Ctrl-C
		cat + Ctrl-\   => ^\Quit (core dumped)
		sleep 3 | sleep 3 | sleep 3 + Ctrl-C (after 1s)
		sleep 3 | sleep 3 | sleep 3 + Ctrl-\ (after 1s)

ENV & EXPORT & UNSET ->
	EXEC ->
		export      => retirer le declare -x, ordre alpha et quote ?
		export | grep HOME   => car pas fork => Fork export ?
	PARSING ->
		export ""   => not a valid identifier => parsing des quotes
		export $?   => expander du $?
		export HOLA="bonjour        "   => parsing des quotes
		export HOLA="   -n bonjour  "   => parsing des quotes
		export HOLA="bonjour   "/   => parsing des quotes
		export HOLA='""' + echo " $HOLA " | cat -e 
		export HOLA="cat Makefile | grep NAME"

	A TESTER DE 300 A 330 APRES LE PARSING

CD & PWD ->
	EXEC -> 
		rm lien de fichier -> chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
	PARSING->
		cd 'src/' && cd "src/"  => pasing des quotes
		cd '/'

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
		ls -la | grep "'.'"   => A retester
		cat a | <b cat | cat > c | cat
	
REDIRECTIONS ->
	