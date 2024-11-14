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

main() {
    local str1="  Hello World  "
    local str2="hello"
    local str3="HELLO"
    local str4="World"

    string_length "$str1"
    concatenate_strings "$str2" "$str4"
    compare_strings "$str2" "$str3"
    to_uppercase "$str2"
    to_lowercase "$str3"
}

main
