@echo off

echo.delimit 9.6.0 release 1
echo.delimit test script - Microsoft Windows OS environment
echo.================================================================================

if not exist "out" mkdir out

copy test-d.dat out\output-overwrite-01.dat

echo.
echo.test case 01: comma delimited, single qouted field
echo.--------------------------------------------------------------------------------
echo.

delimit.exe -c -s -f test.d -i test-d.dat -o out\output01.dat -r -v

echo.
echo.test case 02: comma delimited, double qouted field
echo.--------------------------------------------------------------------------------
echo.

delimit.exe -c -d -f test.d -i test-d.dat -o out\output02.dat -r -v

echo.
echo.test case 03: tab delimited, single qouted field
echo.--------------------------------------------------------------------------------
echo.

delimit.exe -t -s -f test.d -i test-d.dat -o out\output03.dat -r -v

echo.
echo.test case 04: tab delimited, double qouted field
echo.--------------------------------------------------------------------------------
echo.

delimit.exe -t -d -f test.d -i test-d.dat -o out\output04.dat -r -v

echo.
echo.test case 05: space delimited, single qouted field
echo.--------------------------------------------------------------------------------
echo.

delimit.exe -x -s -f test.d -i test-d.dat -o out\output05.dat -r -v

echo.
echo.test case 06: space delimited, double qouted field
echo.--------------------------------------------------------------------------------
echo.

delimit.exe -x -d -f test.d -i test-d.dat -o out\output06.dat -r -v

echo.
echo.test case 07: no specified delimiter, single qouted field
echo.--------------------------------------------------------------------------------
echo.

delimit.exe -s -f test.d -i test-d.dat -o out\output07.dat -r -v

echo.
echo.test case 08: no specified delimiter, double qouted field
echo.--------------------------------------------------------------------------------
echo.

delimit.exe -d -f test.d -i test-d.dat -o out\output08.dat -r -v

echo.
echo.Test case 09: unique character delimited 0x08, single qouted field
echo.--------------------------------------------------------------------------------
echo.

delimit.exe -u 0xff -s -f test.d -i test-d.dat -o out\output09.dat -r -v

echo.
echo.test case 10: unique character delimited 0x08, double qouted field
echo.--------------------------------------------------------------------------------
echo.

delimit.exe -u 0xff -d -f test.d -i test-d.dat -o out\output10.dat -r -v

echo.
echo.test case 11: comma delimited, double qouted field with over-write
echo.--------------------------------------------------------------------------------
echo.

delimit.exe -c -d -f test.d -i out\output-overwrite-01.dat -r -v -w