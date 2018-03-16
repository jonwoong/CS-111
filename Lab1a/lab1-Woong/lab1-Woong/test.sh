printf '***** Testing sort *****\n'
touch input
printf '%d\n' '3' '2' '1' '0' > input
touch output
touch error
./simpsh --rdonly input --wronly output --wronly error --command 0 1 2 sort
printf '\n'
printf 'Sort worked if you see 0 1 2 3 below:\n'
cat output
rm input
rm output
rm error
printf '\n'

touch input
touch output
touch error
printf '***** Testing tr *****\n'
printf 'abcdefg' > input
./simpsh --rdonly input --wronly output --wronly error --command 0 1 2 tr a-z A-Z
printf '\n'
printf 'tr worked if the text below is in all caps:\n'
cat output
printf '\n'
printf '\n'
rm input
rm output
rm error

touch input
touch cat
touch output
touch error
printf '***** Testing cat *****\n'
printf ' SUCCESSFUL' > input
printf 'CAT' > cat
./simpsh --rdonly input --wronly output --wronly error --command 0 1 2 cat cat -
printf '\n'
cat output
printf '\n'
printf '\n'
rm input
rm output
rm error
rm cat
