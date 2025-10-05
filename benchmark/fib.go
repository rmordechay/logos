package main

import "fmt"

func main() {
    n := 50000000
    arr := make([]int, n)
    for i := 0; i < n; i++ {
        arr[i] = i
    }
    sum := int64(0)
    for i := 0; i < n; i++ {
        sum += int64(arr[i])
    }
    fmt.Printf("Sum: %d\n", sum)
}