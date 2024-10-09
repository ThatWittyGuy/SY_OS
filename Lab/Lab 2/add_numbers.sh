#!/bin/bash

add_numbers() {
  local sum=$(( $1 + $2 ))
  echo "The sum of $1 and $2 is: $sum"
}

if [ $# -eq 2 ]; then
  add_numbers "$1" "$2"
else
  echo "Enter the first number: "
  read num1
  echo "Enter the second number: "
  read num2
  add_numbers "$num1" "$num2"
fi
