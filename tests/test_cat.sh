#!/bin/bash

FILE="tests/cat/test.txt tests/cat/test_2.txt"

echo "Running s21_cat tests..."

diff <(./s21_cat $FILE) <(cat $FILE) && echo "SUCCES! cat" || echo "FAIL! cat"
diff <(./s21_cat -e $FILE) <(cat -e $FILE) && echo "SUCCES! cat -e" || echo "FAIL! cat -e"
diff <(./s21_cat -n $FILE) <(cat -n $FILE) && echo "SUCCES! cat -n" || echo "FAIL! cat -n"
diff <(./s21_cat -b $FILE) <(cat -b $FILE) && echo "SUCCES! cat -b" || echo "FAIL! cat -b"
diff <(./s21_cat -s $FILE) <(cat -s $FILE) && echo "SUCCES! cat -s" || echo "FAIL! cat -s"
diff <(./s21_cat -t $FILE) <(cat -t $FILE) && echo "SUCCES! cat -t" || echo "FAIL! cat -t"
diff <(./s21_cat --number-nonblank $FILE) <(cat -b $FILE) && echo "SUCCES! cat --number-nonblank" || echo "FAIL! cat --number-nonblank"
diff <(./s21_cat --number $FILE) <(cat -n $FILE) && echo "SUCCES! cat --number" || echo "FAIL! cat --number"
diff <(./s21_cat --squeeze-blank $FILE) <(cat -s $FILE) && echo "SUCCES! cat --squeeze-blank" || echo "FAIL! cat --squeeze-blank"
