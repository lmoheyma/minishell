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

	export hola | unset hola | echo $? ou 0

CD & PWD ->
	cd ./././.  => cd .. au lieu de cd .
	cd src obj   => bash: cd: too many arguments
	cd 'src/' && cd "src/"  => pasing des quotes
	cd '/'
	gerer le - (?)
	cd $HOME $HOME
	cd "$PWD/minishell"
	cd '$PWD/minishell'
	si HOME=   => cd fait rien
	unset HOME, export HOME, cd   => SEGFAULT => HOME not set
	cd minishell pipex   => too many arguments
	cd / | echo $?   => dont change repo, but print $?

	mkdir a
	mkdir a/b
	cd a/b
	rm -r ../../a   me=> pwd error  bash=> no error
	cd ..   me=>pwd error   bash=> bash: cd: ..: No such file or directory

	mkdir a
	mkdir a/b
	cd a/b
	rm -r ../../a   me=> pwd error  bash=> no error
	pwd   me=>pwd error   bash=> pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
	pwd error en trop vient de l'affichage du prompt ?'

BATARDS ->
	Gerer les fichiers executables

	touch hola
	./hola

	env|"wc" -l   => parsing des quotes
	env|"wc "-l   => parsing des quotes
	expr $? + $?

	env -i
	env

EXIT ->
	exit exit   => bash: exit: exit: numeric argument required
	exit hola
	arg > 2     => bash: exit: too many arguments
	exit hola 666 666   => bash: exit: hola: numeric argument required

	A TESTER DE 473 A 518 APRES LE PARSING

PIPE ->
	echo | echo   => print un \n
	echo hola | echo que tal
	pwd | echo hola
	env | echo hola
	cd .. | echo "hola"
	cd / | echo "hola"
	cd .. | pwd
	ls | hola    => bash: hola: command not found
	ls | ls | hola
	ls | hola | ls   => bash: hola: command not found + ls
	ls | ls | hola | rev
	ls -la | grep "'.'"   => A retester
	echo hola ||| cat   => bash: syntax error near unexpected token `|''
	ech|o hola | cat   => command not found
	cat Makefile | grep pr | head -n 5 | cd rgrger   => bash: cd: file_not_exist: No such file or directory
	cat Makefile | grep pr | head -n 5 | hello   => command not found
	export HOLA | echo hola   => hola
	export | echo hola
	time sleep 3 | sleep 3   => affichage bug ?
	sleep 3 | exit  => apparait au bout de 3sec
	cat a | <b cat | cat > c | cat   => SEGFAULT  => parsing des quotes
	
