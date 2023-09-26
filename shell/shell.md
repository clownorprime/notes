## Shell Scripts
$0 - Name of the script
$1 to $9 - Arguments to the script. $1 is the first argument.
$@ - All arguments.
$# - The number of the arguments.
$? - Return code of the previous command.
$$ - PID of the current script.
!! - Entire last command.
$_ - Last argument from the last command.
$! - The PID of the last executed command.

## why use shebang
Bash is just one kinds of shell scripts, different scripts have different syntaxes. For example, array index starts at 1 in Zsh instead of 0 in bash. To avoid unpleasant results, you should use shebang.

## Command substitute
Command substitute is the process of storing the output of a command into a variable.   
Such as name=$(whoami).

## Command cut
Cut is a useful command for processing text. For example, you can the first item of the entry in the /etc/passwd by running "cat /etc/passwd | cut -d ":" -f 1".

## Arrays in bash
You can create an array in bash using "array\_name=(value1 value2 value3 ... )".
And you can access the inner element by using index, such as array\_name[1] for value2.
An example:
```sh
    array_name=("1.txt" "2.txt" "3.txt")
    echo ${array_name[1]}   # the output is "2.txt"
    echo ${array_name[*]}   # the output is "1.txt 2.txt 3.txt"
    echo ${array_name[@]}   # the output is "1.txt 2.txt 3.txt"
    echo $array_name        # error
    echo ${#array_name[@]}  # the number of the elments in the array.
    array_name[1]="4.txt"   # update the array.
    array_name+=("5.txt")   # add an element to the array.
    unset array_name[2]     # delete element of array[2]
    echo ${array_name[*]}   # the output is "1.txt 4.txt 5.txt"
    unset array_name        # delete the whole array
```
And it's ok for a array in the shell to have element of different types .  
```sh
    arrary=("usr" 1234 "hello,gsh")

```
## String in bash
You can get the length of a string by using the command : $(#string}.  
And to concatenate two strings, typing $str1$str2.  
To find the position of a word or letter in a string, type 'expr index "$str" $word"'
And note if the word or substring doesn't contains in a string, the upper command will return the result of the smallest index for the letter in the word or substring contains in the string.
To extracted word or letter from a string, using "${str:index1:index2}"
To replace word or substring from a string, using "${str/substr1/substr2}"
To remove word or substring from a string, using "${str/$substr1}"
To remove all words or substrings from a string, using double forward slashes , such as "${str//substr1}"
To convert all letters of a string to UPPERCASE, using "${str^^}"  
To convert all letters of a string to LOWERCASE, using "$str,,}:
To convert the first letter of a string to UPPERCASE, using "${str^}"  
To convert the first letter of a string to LOWERCASE, using "${str,}"
To convert a specific letter of a string to UPPERCASE, using "${str^^[$l1$l2]}", where $l1 and $l2 is the specific two letters.
So do with the LOWERCASE, just replacing "^^" into ",,"


For example :   
```sh
    str1="hello"; 
    echo ${#str1}          # echo the length of str1, in that case : 5
    str2=" world"
    str3=$str1$str2        # concatenate two strings
    echo $str3             # the output is "hello world"
    str="Bash is Cool"  
    word="Cool"
    # note you can't use "expr index $str $word";
    # That means "expr index Bash is Cool Cool;
    expr index "$str" "$word"   # the output is : 9
    echo ${str:1:3}        # output : ash. note the index starts from 0
    echo ${str:3}          # output : h is Cool.
    # the following two commands are equal.
    # And the replace doesn't change the original string.
    echo ${str/Bash/Shell} # output : Shell is Cool.
    echo ${str/"Bash"/"Shell"}  # output: Shell is Cool.
    echo $str              # output : Bash is Cool. 
    echo ${str/is}         # output : Bash Cool
    str="Bash is Cool, is Cool"
    echo ${str//is}        # output : Bash Cool,  Cool.
    str="Bash is a kind of shell"
    echo ${str^^[ash]}     # output : BASH iS A kind of SHell.
    echo ${str,,[B]}       # output : bash is a kind of shell.

```
## if else and case statement
The synax of if is 
```sh
    if [ condition ]; then
        command
    elif [ condition1 ]; then
        comand1
    else 
        comand2
    fi
```
Note there must be a space between the opening and closing brackets and condition. Also, space before and after the conditional operator(=, ==, <=, etc).  

The synax of case is:
```sh
case 'variable' in 
    "pattern1" )
        command ... ;;
    "pattern2" )
        command ... ;;
    "pattern3" )
        command ... ;;
esac
```
For example:
```sh
    CHAR=$1
    case $CHAR in
        [a-z])
            echo "Small Alphabet." ;;
        [A-Z]) 
            echo "Big Alphabet." ;;
        [0-9])
            echo "Number." ;;
        *)
            echo "Special Character." ;;
    esac
```
## Test conditions in bash
    $a -lt $b       --      $a < $b
    $a -gt $b       --      $a > $b
    $a -ge $b       --      $a >= $b
    $a -ne $b       --      $a != $b
    -e $FILE        --      $FILE exists
    -d $FILE        --      $FILE exists and is a directory
    -f $FILE        --      $FILE exists and is a file
    -L $FILE        --      $FILE exists and is a softlink
    -z $STRING      --      $STRING is empty
To obtain more information, use man test.

## the difference between () [] {} [[]] (())
