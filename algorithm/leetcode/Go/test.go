package main

import "fmt"

func main() {
	animals := []string{"dog", "cat", "mouse"}
	for _, a := range animals {
		func() {
			fmt.Println(a)
		}()
	}
}
