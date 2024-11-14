#!/bin/bash

string_length() {
    local str="$1"
    echo "Length of the string: ${#str}"
}

concatenate_strings() {
    local str1="$1"
    local str2="$2"
    echo "Concatenated string: $str1$str2"
}

compare_strings() {
    local str1="$1"
    local str2="$2"
    if [ "$str1" == "$str2" ]; then
        echo "The strings are equal."
    else
        echo "The strings are not equal."
    fi
}

to_uppercase() {
    local str="$1"
    echo "Uppercase: $(echo "$str" | tr 'a-z' 'A-Z')"
}

to_lowercase() {
    local str="$1"
    echo "Lowercase: $(echo "$str" | tr 'A-Z' 'a-z')"
}

menu() {
    echo "Select a string operation:"
    echo "1. Find length of string"
    echo "2. Concatenate two strings"
    echo "3. Compare two strings"
    echo "4. Convert string to uppercase"
    echo "5. Convert string to lowercase"
    echo "6. Exit"
}

main() {
    while true; do
        menu
        read -p "Enter your choice (1-6): " choice
        case $choice in
            1)
                read -p "Enter a string: " str
                string_length "$str"
                ;;
            2)
                read -p "Enter first string: " str1
                read -p "Enter second string: " str2
                concatenate_strings "$str1" "$str2"
                ;;
            3)
                read -p "Enter first string: " str1
                read -p "Enter second string: " str2
                compare_strings "$str1" "$str2"
                ;;
            4)
                read -p "Enter a string: " str
                to_uppercase "$str"
                ;;
            5)
                read -p "Enter a string: " str
                to_lowercase "$str"
                ;;
            6)
                echo "Exiting..."
                exit 0
                ;;
            *)
                echo "Invalid choice! Please enter a number between 1 and 6."
                ;;
        esac
        echo ""
    done
}

main
