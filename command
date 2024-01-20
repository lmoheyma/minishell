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
	$HOME        => bash: /home/vietdu91: Is a directory
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
	export | grep HOME   => car pas fork
	export ""   => not a valid identifier
	export %    => not a valid identifier
	export $?
	export ?=2
	Bug de cmp pour remplacer le nom de env_var
	ex : export HOLA=bonjour
		 export HOLA9=
	export _HOLA=bonjour   => bug strcmp
	export ___HOLA=bonjour
	export HOL@=bonjour    => not a valid identifier
	export HOLA-=bonjour   => not a valid identifier
	export HO-LA=bonjour   => not a valid identifier
	export HOL.A-=bonjour   => not a valid identifier
	export HOL}A=bonjour   => not a valid identifier
	export HOL{A=bonjour   => not a valid identifier
	export HO*LA=bonjour   => not a valid identifier
	export HO#LA=bonjour   => not a valid identifier
	export HO@LA=bonjour   => not a valid identifier
	export HO!LA=bonjour    => event not found
	export HO$?LA=bonjour    => event not found
	export +HOLA=bonjour   => not a valid identifier
	export HOL+A=bonjour   => not a valid identifier
	export HOLA =bonjour   => not a valid identifier
	export HOLA=bon!jour   => bash: !jour: event not found
	export HOLA$USER=bonjour   => strcmp
	export HOLA="bonjour        "   => parsing des quotes
	export HOLA="   -n bonjour  "   => parsing des quotes
	export HOLA="bonjour   "/   => parsing des quotes
	export HOLA='""' + echo " $HOLA " | cat -e 
	export "" HOLA=bonjour   => print lerreur mais continuer
	export HOLA="cat Makefile | grep NAME"

	A TESTER DE 300 A 330 APRES LE PARSING

	
	


