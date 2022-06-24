#! /bin/sh

#########Echo#########
echo bonjour
        echo echo hey
echo bonjourheybonjour salut
echo lalalala                lalalalal      alalalalal alalalala
echo -n lalalala                lalalalal      alalalalal alalalala
                        echo       -n            bonjour
echo -n bonjour coucou
echo -n
echo -n-n
echo "-n     mdr"
echo - n
echo '-     n'
echo  Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem...
echo a '' b '' c '' d
echo a "" b "" c "" d
echo -n -n lol -n  # erreur !!!! les doubles flags ne sont pas pris en compte
echo -n -n -n test tout # same mistake
echo
echo -n -n # erreur same mistake
echo -n a '' b '' c '' d
echo -n a "" b "" c "" d
echo '' '' ''
echo ''
echo -nnnnnnnnnnnnnnnnnnnnn bonjour #erreur ! -nnnnnnnnnnn doit fonctionner comme -n
echo -nnnnnnnnnnnnnnnnnnnnn -n -n -n bonjour -n -n # erreur same mistake
Echo bonjour
eCho bonjour
ecHo bonjour
echO bonjour
EchO bonjour
eCHo bonjour
EcHo bonjour
eChO bonjour
echo "$wfjwefielwhfhlwefkhwefwe" a
echo '$wfjwefielwhfhlwefkhwefwe' a
'$wfjwefielwhfhlwefkhwefwe' a
"$wfjwefielwhfhlwefkhwefwe" a

#########Cd#########
cd .. # affiche le path, bash non
cd..
cd ./srcs
cd . # cause un retour en arriere dans le path
cd ../
cd ../../../
cd / # segfault !!!!!
cd
cd /Users
Cd . # cause un retour en arriere dans le path
cD . # cause un retour en arriere dans le path
cd /.
cd /./
cd /././././
cd //
cd ///
cd ////
cd //////////////////////////////////////////////////////
cd $HOME
cd '' # segfault !!!!
cd '' ''
cd '' '' ''
cd ' '
cd ' // '
cd ' /'
cd '                  /'
cd d ''
cd d d
cd ~ 

#########Export#########
export emma="cc" yohann="cava"
export "mdr"=hey
export A='   bonjour   je   suis  splited ' # error probleme de quote removal
export A='   bonjour   je   suis  splited ' # error probleme de quote removal
export A='   bonjour   je   suis  splited ' # error probleme de quote removal
export A='   bonjour   je   suis  splited ' # error probleme de quote removal
export A='   bonjour     je     suis    splited   ' # error probleme de quote removal
export A='   bonjour   je   suis  splited ' # error probleme de quote removal
export A='fi le' # error probleme de quote removal
export "ceci"="cela"
export lol=""
export lol=" " # error probleme de quote removal
export lol2=''
export lol2=' ' # error probleme de quote removal
export lol2="'"
export lol2="'"
export lol2='$'
export lol2='\t'
export test=hello hello="poulette"
export test2=
export test1 # should not print anything in env, but no err msg
export test= o # if empty space should printf test= in env
export test=$test"coucou"
export zz zzz= zzzz=asd #error : should not expand zz
export A=a B=b C=c D=d E=e F=f G=g H=h I=i J=j K=k L=l M=m N=n O=o P=p Q=q R=r
Export B=bonjour # should be minimized ?
exporT B=bonjour # should be minimized ?
export test=$COLORTERM=coucou
export # should not print additionnal ~ at the end
export test="   a   " # another quote removal problem
export ?=42
export $ # cause an infinite loop
export 1=a
export BONJOURJESUIS =a # should not print anything in env
export 'AH\'=nop # not a valid identifier
export 'AH@'=nop
export 'AH"'=nop
export 'AH!'=nop
export A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C # should not print anything in env, lack of error msgs
export "  a"=coucou

#########Unset#########
unset emma yohann
export test1 test2= test3="coucou" ; unset test1 test2
export A='a' ; unset 'A'; echo $A
Unset TERM
unseT TERM
unset
export A='a' ; unset 'A '; echo $A
export A='a' B='b' C='c' ; unset 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C
export A='a' B='b' C='c' ; unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf '; echo $A$B$C
export A='a' B='b' C='c' ; unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C 
unset 'AH@'=nop
unset "AH'"=nop
unset 'AH"'=nop
unset 'AH$'=nop
unset 'AH!'=nop
unset 'AH|'=nop
unset 'AH;'=nop
unset 'AH&'=nop
unset 'AH\'=nop
export A='a' ; unset 'A='; echo $A
export A='a' B='b' C='c' ; unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C
export PATH='/bin:/usr/bin' ; unset TERM ; echo $TERM
unset TERM ; echo $TERM

#########Env#########
env
Env # need to capitalize
enV
export PATH='/bin:/usr/bin' ; Env
export PATH='/bin:/usr/bin' ; enV  
export A=a ; env
export A=a B=b C=c ; env
export A=a B=b C=c ; env

#########Pwd#########
pwd
pwd mdr #should display an error msg
pwd coucou ne rien imprimer
[SETUP cd ..] pwd
[SETUP cd ../..] pwd
[SETUP cd ../../..] pwd
[SETUP cd /] pwd
[SETUP cd $HOME] pwd
pwd | cat -e
unset PWD; pwd; echo $PWD
Pwd
pwD
export PWD='/etc' ; pwd # pwd should not be moved by pwd variable
export PWD=foo; pwd; echo $PWD

#########Pipes#########
cat test.sh | grep arcu | cat -e
echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e
cat /dev/random | head -c 100 | wc -c
>lol echo > test>lol>test>>lol>test mdr >lol test >test
ls asdfasdf | echo a
echo a | ls asdfasdf

#Boucle infinie :
cat -e /dev/random | head -c 10
cat -e /dev/random | cat -e | head -c 10
cat -e /dev/random | cat -e | cat -e | head -c 10

#########Erreurs A renvoyer#########
asdf | echo bonjour
"$PATH"
$PWD$PATH$COLORTERM
./srcs
> test
>> test
$COLORTERMcoucou

##########Protections#########
'echo' "bonjour" "wesh"
e"ch"o bonjour
       'ech'o bonjour
#doubles quotes
"" "" echo minishell
""echo minishell
"ec''ho" bonjour
"ec'''ho" bonjour
echo "\\"
echo "" coucou | cat -e
echo bon""jour
echo """""mdrr"
echo ''""
echo ''""''
echo """"bonjour"" "" | cat -e
"echo bonjou"""r
"echo""" ''bonjour
echo "$wfjwefielwhfhlwefkhwefwe" a
ls "-lR""-a"
echo bonjour 1>"hey" pas normal
echo bonjour 1> "wesh alors" hey
echo "" mdr "" | cat -e
echo bonjour 1>'"' pas normal
echo bonjour 1> "hey""" pas normal
echo bonjour 1> "hey"'' pas normal
echo bon"jo\"u"r
echo bon"jo\\"u"r"
echo bon"jo\"''\"\"\'$u\\'\$"r
echo b"\ \ \ onjour"
echo "b\on\j\our"
echo "b\\onjour\\"
"$'PATH'"
"echo '\$HOME'"
"echo ' \"\$HOME\" '"
"echo \"'\$HOME'\""
"echo \" '\$PWD' \\\"\$PWD\\\" '\$PWD' \"" "echo \"\\\$HOME\""
"echo \"'\$'\""
"echo \\\\\n"
echo\" bonjour\"
echo "mdrrr >coucou >> ceci n'est pas une redirection"
echo a;
#simples quotes
'$PATH'
'$\PATH'
'' echo minishell
'echo "$HOME"'
echo co'c"o"u'
'echo" bonjour"'
echo 'cou""c""ou"'
echo bo'njou\r'
echo 'cou\"\"\\c""ou"'
echo '      cou    "cou"'
echo bo'njou\$r'
e'ch\\o' 'bonj'\o\u'r'
echo '' '' 'bonjour' | cat -e
echo '''''' | cat -e

##########Redirections#########
#stdin
cat < test.txt
cat <test.txt >>hello<bonjour
cat "<test.txt"
#stdout stderr
echo bonjour1>test1
echo bonjour 1>test2
echo bonjour > "     test1"
echo bonjour 2>hey test2
#double redirection
echo bonjour >> test3
echo bonjour>>test3>>test4
1>test1 2>test2 echo bonjour
1>test12>test2 echo bonjour
>test1 2>test2 echo bonjour
>> e
#multi redirections
echo >mdr>hey>>sarace\sal"hehe"
echo bonjour 2>\wes\\hh
echo bonjour <\weshh
echo <hey1<h'ey2'
echo >hey1>h'ey2'
>coucou >hey >lol>mdr haha
echo bonjour >hey >>hey2 >>hey3
echo mdr <hello >>wesh>alors2>error
echo mdr >>wesh>alors2>error
echo "\"" >>a"b""c"
echo b > foo ; echo a | cat -e < foo
echo > test'sticked' bonjour
> test'sticked' echo bonjour
echo >> test'sticked' bonjour
>> test'sticked' echo bonjour
echo bonjour > test; echo salut > je ; cat<test<je
echo bonjour 1> "$PATHH"
echo bonjour 1> "$PAT\H"
echo bonjour 2> "$PAT\H"

#########Environnement#########
echo "$'PATH'"
echo $"coucou"
echo $PATH
ls $HOME/Desktop
echo "$PATH""" coucou
echo $PATH"coucou"
echo "hello"$PWD"coucou"
coucou$PWD test$COLORTERMlol lol$HOME
echo "bonjour$PATH$PWD"
echo "bonjour\$PATH$PWD"
echo $PATH"coucou"
echo $\PATH
echo $\c
$\PATH
echo $cou\cou
$cou\cou
echo $coucou"hey"
$coucou"hey"
echo bonjour 1>$"COLORTERM"
echo $PATH >$COLORTERM
echo bonjour 1>$hey"lol"
echo hey > coucou$COLORTERM
echo "$LOL" 2>"$COLORTERM"
echo $cnwvwevlvlk a
echo $COLORTERM$$hey
echo $COLORTERM$hey
echo $$$$$$$$
$$$
$
echo "$PAT\H"
echo $PAT\H
echo $cnwvwevlvlk a
echo $A$B
echo $coucou\"
echo "|$TEST\""
echo "|$TEST|"

#########Erreurs A renvoyer#########
#syntax error near unexpected token `|'
| < a
|echo
|cat
| cat
    | cat
< | a
> | a
>> | a
echo|
echo |
echo a ||| echo b
echo bonjour | | cat -e
echo ' | ' "" "|" |
# files dans les redirections
echo <njwajkxw<n<j<   an
cat < ''
cat < coucou
#syntax error near unexpected token `newline'
echo <
> 
>>
<
#syntax error near unexpected token `>'
echo foo >>> bar
#syntax error near unexpected token `>>'
echo foo >>>> bar 
echo foo >>>>> bar
#syntax error near unexpected token `<'
echo bonjour > bar ; cat << < bar 

#Erreurs Quotes
echo ''#enlever une simple quote
echo '\'''#enlever une simple quote
echo ""#enlever une double quote
echo ''''''''''''''''''''''''''''''''''''''''''''#enlever une simple quote NON !!!!
echo "\\"""#enlever une double quote
echo "AH\""#enlever une double quote
echo """" #enlever une double quote : boucle infinie
echo co'c'o'u' #enlever une simple quote
echo c'o\'u'cou' #enlever une simple quote
echo "bon"jour"" #enlever une double quote
echz #command not found, 127
echo foo >>>>> bar # pb syntaxe, 258
echo <coucou # No such file or directory, 1
testlol: Permission denied # où test lol chmod 000, 1
yes #arret avec un Ctrl-C, 130
