#!/bin/bash

bubble_sort() {
    arr=("$@")
    n=${#arr[@]}
    for ((i = 0; i < n-1; i++)); do
        for ((j = 0; j < n-i-1; j++)); do
            if [ ${arr[j]} -gt ${arr[j+1]} ]; then
                temp=${arr[j]}
                arr[j]=${arr[j+1]}
                arr[j+1]=$temp
            fi
        done
    done
    echo "Sorted Array (Bubble Sort): ${arr[*]}"
}

quick_sort() {
    arr=("$@")
    if [ ${#arr[@]} -le 1 ]; then
        echo "${arr[*]}"
        return
    fi
    pivot=${arr[0]}
    left=()
    right=()
    for i in "${arr[@]:1}"; do
        if [ $i -le $pivot ]; then
            left+=($i)
        else
            right+=($i)
        fi
    done
    echo "$(quick_sort "${left[@]}") $pivot $(quick_sort "${right[@]}")"
}

selection_sort() {
    arr=("$@")
    n=${#arr[@]}
    for ((i = 0; i < n-1; i++)); do
        min_index=$i
        for ((j = i + 1; j < n; j++)); do
            if [ ${arr[j]} -lt ${arr[min_index]} ]; then
                min_index=$j
            fi
        done
        # Swap
        temp=${arr[i]}
        arr[i]=${arr[min_index]}
        arr[min_index]=$temp
    done
    echo "Sorted Array (Selection Sort): ${arr[*]}"
}

insertion_sort() {
    arr=("$@")
    n=${#arr[@]}
    for ((i = 1; i < n; i++)); do
        key=${arr[i]}
        j=$((i-1))
        while [ $j -ge 0 ] && [ ${arr[j]} -gt $key ]; do
            arr[$((j+1))]=${arr[j]}
            j=$((j-1))
        done
        arr[$((j+1))]=$key
    done
    echo "Sorted Array (Insertion Sort): ${arr[*]}"
}

echo "Select a sorting algorithm:"
echo "1. Bubble Sort"
echo "2. Quick Sort"
echo "3. Selection Sort"
echo "4. Insertion Sort"
read -p "Enter your choice (1-4): " choice

read -p "Enter numbers in array separated by space: " -a array

case $choice in
    1)
        bubble_sort "${array[@]}"
        ;;
    2)
        sorted_array=$(quick_sort "${array[@]}")
        echo "Sorted Array (Quick Sort): $sorted_array"
        ;;
    3)
        selection_sort "${array[@]}"
        ;;
    4)
        insertion_sort "${array[@]}"
        ;;
    *)
        echo "Invalid choice!"
        ;;
esac