#!/bin/bash
./s21_grep -e '111' -e 'qwe' ../common/1.txt >> s21_grep_test.txt
grep -e '111' -e 'qwe' ../common/1.txt >> grep_test.txt
[ -z "$(diff s21_grep_test.txt grep_test.txt)" ]&& echo e-flag OK || echo e-flag FAIL!;
rm -f *.txt

./s21_grep -i 'qwe' ../common/1.txt ../common/3.txt >> s21_grep_test.txt
grep -i 'qwe' ../common/1.txt ../common/3.txt >> grep_test.txt
[ -z "$(diff s21_grep_test.txt grep_test.txt)" ]&& echo i-flag OK || echo i-flag FAIL!;
rm -f *.txt

./s21_grep -v 'qwe' ../common/1.txt >> s21_grep_test.txt
grep -v 'qwe' ../common/1.txt >> grep_test.txt
[ -z "$(diff s21_grep_test.txt grep_test.txt)" ]&& echo v-flag OK || echo v-flag FAIL!;
rm -f *.txt

./s21_grep -c '111' ../common/1.txt >> s21_grep_test.txt
grep -c '111' ../common/1.txt >> grep_test.txt
[ -z "$(diff s21_grep_test.txt grep_test.txt)" ]&& echo c-flag OK || echo c-flag FAIL!;
rm -f *.txt

./s21_grep -l '111' ../common/1.txt ../common/3.txt >> s21_grep_test.txt
grep -l '111' ../common/1.txt ../common/3.txt >> grep_test.txt
[ -z "$(diff s21_grep_test.txt grep_test.txt)" ]&& echo l-flag OK || echo l-flag FAIL!;
rm -f *.txt

./s21_grep -n '111' ../common/1.txt >> s21_grep_test.txt
grep -n '111' ../common/1.txt >> grep_test.txt
[ -z "$(diff s21_grep_test.txt grep_test.txt)" ]&& echo n-flag OK || echo n-flag FAIL!;
rm -f *.txt

./s21_grep -h '111' ../common/1.txt ../common/3.txt >> s21_grep_test.txt
grep -h '111' ../common/1.txt ../common/3.txt >> grep_test.txt
[ -z "$(diff s21_grep_test.txt grep_test.txt)" ]&& echo h-flag OK || echo h-flag FAIL!;
rm -f *.txt

./s21_grep -f ../common/2.txt ../common/1.txt >> s21_grep_test.txt
grep -f ../common/2.txt ../common/1.txt >> grep_test.txt
[ -z "$(diff s21_grep_test.txt grep_test.txt)" ]&& echo f-flag OK || echo f-flag FAIL!;
rm -f *.txt

./s21_grep -o '1111' ../common/1.txt >> s21_grep_test.txt
grep -o 'qwe' ../common/1.txt >> grep_test.txt
[ -z "$(diff s21_grep_test.txt grep_test.txt)" ]&& echo o-flag OK || echo o-flag FAIL!;
rm -f *.txt

./s21_grep -s '111' ../common/1.txt ../common/5.txt >> s21_grep_test.txt
grep -s '111' ../common/1.txt ../common/5.txt >> grep_test.txt
[ -z "$(diff s21_grep_test.txt grep_test.txt)" ]&& echo s-flag OK || echo s-flag FAIL!;
rm -f *.txt
