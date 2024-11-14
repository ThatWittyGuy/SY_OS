#!/bin/bash

calculate_results() {
    local eng=$1
    local math=$2
    local sci=$3

    total=$((eng + math + sci))
    percentage=$((total * 100 / 300)) 

    echo "Total Marks: $total / 300"
    echo "Percentage: $percentage%"

    if (( percentage >= 90 )); then
        grade="A"
    elif (( percentage >= 80 )); then
        grade="B"
    elif (( percentage >= 70 )); then
        grade="C"
    elif (( percentage >= 50 )); then
        grade="D"
    elif (( percentage >= 40 )); then
        grade="E"
    else
        grade="FAIL"
    fi

    echo "Grade: $grade"
}

read -p "Enter marks for English (0-100): " english
read -p "Enter marks for Maths (0-100): " maths
read -p "Enter marks for Science (0-100): " science

if (( english >= 0 && english <= 100 )) && (( maths >= 0 && maths <= 100 )) && (( science >= 0 && science <= 100 )); then
    calculate_results "$english" "$maths" "$science"
else
    echo "Invalid marks entered. Please enter marks between 0 and 100."
fi
