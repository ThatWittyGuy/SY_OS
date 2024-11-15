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

# If Asked extra

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

reverse_string() {
    local str="$1"
    echo "Reversed string: $(echo "$str" | rev)"
}

trim_string() {
    local str="$1"
    echo "Trimmed string: $(echo "$str" | sed 's/^[ \t]*//;s/[ \t]*$//')"
}

replace_substring() {
    local str="$1"
    local old="$2"
    local new="$3"
    echo "Replaced string: ${str//$old/$new}"
}

string_contains() {
    local str="$1"
    local substring="$2"
    if [[ "$str" == *"$substring"* ]]; then
        echo "The string contains the substring."
    else
        echo "The string does not contain the substring."
    fi
}

substring_extract() {
    local str="$1"
    local start="$2"
    local length="$3"
    echo "Substring: ${str:start:length}"
}

menu() {
    echo "Select a string operation:"
    echo "1. Find length of string"
    echo "2. Concatenate two strings"
    echo "3. Compare two strings"
    echo "4. Convert string to uppercase"
    echo "5. Convert string to lowercase"
    echo "6. Reverse the string"
    echo "7. Trim leading/trailing spaces"
    echo "8. Replace a substring"
    echo "9. Check if string contains a substring"
    echo "10. Extract a substring"
    echo "11. Exit"
}

main() {
    while true; do
        menu
        read -p "Enter your choice (1-11): " choice
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
                read -p "Enter a string: " str
                reverse_string "$str"
                ;;
            7)
                read -p "Enter a string: " str
                trim_string "$str"
                ;;
            8)
                read -p "Enter the string: " str
                read -p "Enter the old substring: " old
                read -p "Enter the new substring: " new
                replace_substring "$str" "$old" "$new"
                ;;
            9)
                read -p "Enter the string: " str
                read -p "Enter the substring to check: " substring
                string_contains "$str" "$substring"
                ;;
            10)
                read -p "Enter the string: " str
                read -p "Enter the starting index: " start
                read -p "Enter the length of the substring: " length
                substring_extract "$str" "$start" "$length"
                ;;
            11)
                echo "Exiting..."
                exit 0
                ;;
            *)
                echo "Invalid choice! Please enter a number between 1 and 11."
                ;;
        esac
        echo ""
    done
}

main
