#!/bin/bash

is_palindrome() {
    local num=$1
    local reverse=0
    local temp=$num
    while [ $temp -gt 0 ]; do
        digit=$((temp % 10))
        reverse=$((reverse * 10 + digit))
        temp=$((temp / 10))
    done
    if [ $num -eq $reverse ]; then
        echo "$num is a palindrome."
    else
        echo "$num is not a palindrome."
    fi
}

is_prime() {
    local num=$1
    if [ $num -le 1 ]; then
        echo "$num is not prime."
        return
    fi
    for ((i = 2; i * i <= num; i++)); do
        if [ $((num % i)) -eq 0 ]; then
            echo "$num is not prime."
            return
        fi
    done
    echo "$num is prime."
}

fibonacci_series() {
    local n=$1
    a=0
    b=1
    echo "Fibonacci series up to $n terms:"
    for ((i = 0; i < n; i++)); do
        echo -n "$a "
        fn=$((a + b))
        a=$b
        b=$fn
    done
    echo
}

is_armstrong() {
    local num=$1
    local sum=0
    local temp=$num
    local digits=$(echo -n "$num" | wc -c)
    while [ $temp -gt 0 ]; do
        digit=$((temp % 10))
        sum=$((sum + digit *  digit* digit))
        temp=$((temp / 10))
    done
    if [ $sum -eq $num ]; then
        echo "$num is an Armstrong number."
    else
        echo "$num is not an Armstrong number."
    fi
}


menu() {
    echo "Select an operation:"
    echo "1. Check if a number is a palindrome"
    echo "2. Check if a number is prime"
    echo "3. Generate Fibonacci series"
    echo "4. Check if a number is an Armstrong number"
    echo "5. Exit"
}

# Main program
while true; do
    menu
    read -p "Enter your choice (1-5): " choice
    case $choice in
        1)
            read -p "Enter a number: " num
            is_palindrome $num
            ;;
        2)
            read -p "Enter a number: " num
            is_prime $num
            ;;
        3)
            read -p "Enter the number of terms for Fibonacci series: " n
            fibonacci_series $n
            ;;
        4)
            read -p "Enter a number: " num
            is_armstrong $num
            ;;
        5)
            echo "Exiting..."
            exit 0
            ;;
        *)
            echo "Invalid choice! Please enter a number between 1 and 5."
            ;;
    esac
    echo ""
done
