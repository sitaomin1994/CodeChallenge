# Eluvio Challenge Core Engineering - Longest Strand

## Questions
Given a large number of binary files, write a program that finds the
longest strand of bytes that is identical between two or more files

Use the test set attached (files sample.*)

The program should display:
- the length of the strand
- the file names where the largest strand appears
- the offset where the strand appears in each file

## Execution

Run on Ubuntu 20.04, using cmake 3.16, g++ 9.3.0
```shell
/usr/bin/cmake "CodeBlocks - Unix Makefiles" "./"
make
cd ./bin/
./CodeChallenge_longestStrand
```
Or directly run executable file
```shell
cd ./bin/
./CodeChallenge_longestStrand
```
## Result

Maximum common strands is between sample.2 and sample.3:
- length of common strands:27648
- offset of sample.2 : 3072
- offset of sample.3 : 17408

Execution time 48s in intel core i7