#!/bin/bash
python3 f_maker.py;
gcc main.c -o main;
./main A B;
gzip -c A > A.gz;
gzip -c B > B.gz;
gunzip -cd B.gz | ./main C;
./main A D -b 100;
stat A;
stat A.gz;
stat B;
stat B.gz;
stat C;
stat D;