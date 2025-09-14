#!/bin/bash

CUR_SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

MSG_NO_ARG="No argument was provided!"
MSG_EMPTY_ARG="Argument is empty!"
MSG_ONLY_ONE="Only one argument should be passed!"
MSG_NO_DIR_FOUND="No directories found!"

dir_num=${1}

if [[ $# == 0 ]]
then
    echo "${MSG_NO_ARG}"
    exit 1
elif [[ $# > 1 ]]
then
    echo "${MSG_ONLY_ONE}"
elif [[ ${#dir_num} == 0 ]]
then
    echo "${MSG_EMPTY_ARG}"
    exit 2
elif [[ $(ls ${CUR_SCRIPT_DIR} | grep ${dir_num}_* | wc -l) == 0 ]]
then
    echo "${MSG_NO_DIR_FOUND}"
    exit 3
fi

echo "Compiling all files in $(ls ${CUR_SCRIPT_DIR} | grep ${dir_num}_*)"

for file in $(ls ${CUR_SCRIPT_DIR}/${dir_num}_*/*.cpp)
do
    g++ -g ${file} -lncurses -lpanel -o ${file%cpp}exe
    echo "Generated ${file%cpp}exe"
done