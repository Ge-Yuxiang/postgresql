#!/bin/bash
shell_path=$(readlink -f  ${BASH_SOURCE[0]})
project_path=$(dirname $(dirname $(dirname $shell_path)))

function FindFile()
{
    read -p "Input your search file name: " file_name
    echo ${file_name}: 
    find $project_path -wholename *${file_name}*
}

function ShowCynosProcess()
{
    ps -ef | grep "postgres:" && ps -ef | grep "/usr/local/pgsql/"
}

if [ "$1" == "find" ];then
    FindFile
elif [ "$1" == "show" ];then
    ShowCynosProcess
fi