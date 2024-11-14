#!/bin/bash

calculate_results() {
    local eng=$1
    local math=$2
    local sci=$3

    total=$((eng + math + sci))
    percentage=$(echo "scale=2; ($total / 300) * 100" | bc)

    echo "Total Marks: $total / 300"
    echo "Percentage: $percentage%"

    if (( $(echo "$percentage >= 90" | bc -l) )); then
        grade="A"
    elif (( $(echo "$percentage >= 80" | bc -l) )); then
        grade="B"
    elif (( $(echo "$percentage >= 70" | bc -l) )); then
        grade="C"
    elif (( $(echo "$percentage >= 50" | bc -l) )); then
        grade="D"
    elif (( $(echo "$percentage >= 40" | bc -l) )); then
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
