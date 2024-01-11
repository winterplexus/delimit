#!/bin/sh

echo delimit 9.8.0 release 1
echo delimit test script - open systems environments
echo ================================================================================

if [ -d out ]; then
    rm -rf out
fi

mkdir out

cp test-l.dat out/output-overwrite-01.dat

echo
echo test case 01: comma delimited, single qouted field
echo --------------------------------------------------------------------------------
echo

./delimit -c -s -f test.d -i test-l.dat -o out/output01.dat -r -v

echo
echo test case 02: comma delimited, double qouted field
echo --------------------------------------------------------------------------------
echo

./delimit -c -d -f test.d -i test-l.dat -o out/output02.dat -r -v

echo
echo test case 03: tab delimited, single qouted field
echo --------------------------------------------------------------------------------
echo

./delimit -t -s -f test.d -i test-l.dat -o out/output03.dat -r -v

echo
echo test case 04: tab delimited, double qouted field
echo --------------------------------------------------------------------------------
echo

./delimit -t -d -f test.d -i test-l.dat -o out/output04.dat -r -v

echo
echo test case 05: space delimited, single qouted field
echo --------------------------------------------------------------------------------
echo

./delimit -x -s -f test.d -i test-l.dat -o out/output05.dat -r -v

echo
echo test case 06: space delimited, double qouted field
echo --------------------------------------------------------------------------------
echo

./delimit -x -d -f test.d -i test-l.dat -o out/output06.dat -r -v

echo
echo test case 07: no specified delimiter, single qouted field
echo --------------------------------------------------------------------------------
echo

./delimit -s -f test.d -i test-l.dat -o out/output07.dat -r -v

echo
echo test case 08: no specified delimiter, double qouted field
echo --------------------------------------------------------------------------------
echo

./delimit -d -f test.d -i test-l.dat -o out/output08.dat -r -v

echo
echo test case 09: unique character delimited 0x08, single qouted field
echo --------------------------------------------------------------------------------
echo

./delimit -u 0xff -s -f test.d -i test-l.dat -o out/output09.dat -r -v

echo
echo test case 10: unique character delimited 0x08, double qouted field
echo --------------------------------------------------------------------------------
echo

./delimit -u 0xff -d -f test.d -i test-l.dat -o out/output10.dat -r -v

echo
echo test case 11: comma delimited, double qouted field with over-write
echo --------------------------------------------------------------------------------
echo

./delimit -c -d -f test.d -i out/output-overwrite-01.dat -r -v -w
