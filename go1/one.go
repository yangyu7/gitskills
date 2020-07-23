package main

import (
	"fmt"
	"time"
)

var sum int16 = 0

func add(i int16) {
	var j int16
	for j = 0; j < i; j++ {
		sum += j
		//	time.Sleep(time.Second)
	}
	fmt.Println(sum)
}
func goTest() {
	var count int16 = 1000
	var i int16
	for i = 0; i < count; i++ {
		go add(i)
		fmt.Println(sum)
	}
	time.Sleep(10 * time.Second)
}
func writeData(intChan chan int, num []int) {
	for i := 0; i < len(num); i++ {
		intChan <- num[i]
	}
	fmt.Println("write end")
}
func readData(intChan chan int, result *bool) {
	sum := 0
	for len(intChan) > 0 {
		outN := <-intChan
		sum += outN
		//		fmt.Println(outN)
	}
	fmt.Println(sum, "read end")
	*result = true
}
func main() {
	intChan := make(chan int, 1000)
	num := make([]int, 0)
	re := false
	for i := 0; i < 1000; i++ {
		num = append(num, i)
		//		fmt.Println(i)
	}
	fmt.Println("-------")
	go writeData(intChan, num)
	go readData(intChan, &re)
	for !re {
	}

}
