#!/bin/bash
read -p "Enter C++ file name to compile: " filename

g++ $filename -o test -lmariadb
