#!/bin/bash
./s21_cat -s ../common/text.txt >> s21_cat_test.txt
cat -s ../common/text.txt >> cat_test.txt
[ -z "$(diff s21_cat_test.txt cat_test.txt)" ]&& echo s-flag OK || echo s-flag FAIL!;
rm -f *.txt

./s21_cat -n ../common/text.txt >> s21_cat_test.txt
cat -n ../common/text.txt >> cat_test.txt
[ -z "$(diff s21_cat_test.txt cat_test.txt)" ]&& echo n-flag OK || echo n-flag FAIL!;
rm -f *.txt

./s21_cat -b ../common/text.txt >> s21_cat_test.txt
cat -b ../common/text.txt >> cat_test.txt
[ -z "$(diff s21_cat_test.txt cat_test.txt)" ]&& echo b-flag OK || echo b-flag FAIL!;
rm -f *.txt

./s21_cat -e ../common/text.txt >> s21_cat_test.txt
cat -e ../common/text.txt >> cat_test.txt
[ -z "$(diff s21_cat_test.txt cat_test.txt)" ]&& echo e-flag OK || echo e-flag FAIL!;
rm -f *.txt

./s21_cat -t ../common/text.txt >> s21_cat_test.txt
cat -t ../common/text.txt >> cat_test.txt
[ -z "$(diff s21_cat_test.txt cat_test.txt)" ]&& echo t-flag OK || echo t-flag FAIL!;
rm -f *.txt