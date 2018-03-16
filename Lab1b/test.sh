printf '***** Testing sort *****\n'
touch input output error
printf '%d\n' '3' '2' '1' '0' > input
./simpsh --rdonly input --wronly output --wronly error --command 0 1 2 sort
printf '\nsort worked if you see 0 1 2 3 below:\n'
cat output
rm input output error
printf '\n'

printf '***** Testing tr *****\n'
touch input output error
printf 'abcdefg' > input
./simpsh --rdonly input --wronly output --wronly error --command 0 1 2 tr a-z A-Z
printf '\ntr worked if the text below is in all caps:\n'
cat output
printf '\n\n'
rm input output error

printf '***** Testing cat *****\n'
touch a input output error
printf ' SUCCESSFUL' > input
printf 'cat' > a
./simpsh --rdonly input --wronly output --wronly error --command 0 1 2 cat a -
printf '\n'
cat output
printf '\n\n'
rm input output error a

printf '***** Testing oflags *****\n'
./simpsh --append --cloexec --creat --dsync --excl --nofollow --nonblock --rsync --sync --trunc --rdonly a
printf '\nFlags successful if there is no error saying "Could not open file a" \n\n'
rm a

printf '***** Testing pipes + commands + wait *****\n'
touch a b c
printf '%s\n' 'D' 'C' 'B' 'A' > a
./simpsh --rdonly a --pipe --wronly b --wronly c --command 0 2 4 sort --command 1 3 4 tr A-Z a-z --wait
printf 'Test successful if you see sort and tr above, "a b c d" below\n\n'
cat b
printf '\n\n'
rm a b c

printf '***** Testing multiple pipes + wait *****\n'
touch a b c
printf '%s\n' 'G' 'F' 'E' > a
./simpsh --rdonly a --pipe --pipe --wronly b --wronly c --command 0 2 6 cat --command 1 4 6 sort --command 3 5 6 tr A-Z a-z --wait
printf 'Test successful if you see cat,sort,tr above and "e f g" below\n\n'
cat b
printf '\n\n'
rm a b c

printf '***** Testing catch *****\n\n'
touch a b c
./simpsh --rdonly a --wronly b --wronly c --command 0 1 2 cat a --catch 11 --abort
printf 'Test successful if 11 caught\n\n'
rm a b c

printf '***** Testing abort *****\n\n'
./simpsh --abort
printf 'Test successful if segmentation fault above\n\n'

printf '***** Testing ignore *****\n'
./simpsh --ignore 11 --abort
printf '\nTest successful\n\n'

printf '***** Testing default *****\n\n'
./simpsh --catch 11 --default 11 --abort
printf '\nTest successful is segmentation fault above\n\n'


printf '***** Testing close *****\n\n'
touch a
./simpsh --rdonly a --close 0 --command 0 0 0 sort
printf 'Test successful if error message: attempt to reuse closed fd above\n\n'
rm a

printf '***** Testing rdwr *****\n\n'
touch a
./simpsh --rdwr a --command 0 0 0 sort
printf 'Test successful\n\n'
rm a

printf '***** Testing verbose *****\n\n'
touch a b c
./simpsh --verbose --verbose --rdonly a --wronly b --rdwr c --pipe --command 0 1 2 sort --close 0 --catch 11 --ignore 11 --default 11 --abort
printf 'Test successful if --verbose -> --abort\n\n'
rm a b c




