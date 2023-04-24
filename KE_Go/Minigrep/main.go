package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"regexp"
)

func main() {
	os_args := os.Args[1:]
	switch len(os_args) {
	case 0:
		log.Fatalln("You need to pass in a file as the first argument.")
	case 1:
		log.Fatalln("You need to pass in a pattern to look for as the second argument.")
	}

	pattern := regexp.MustCompile(os_args[1])

	file, err := os.Open(os_args[0])
	if err != nil {
		log.Fatalln(err)
	}
	defer file.Close()

	ebv := new_ebv(256)
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()

		if match := pattern.FindAllStringSubmatchIndex(line, -1); match != nil {
			for _, match := range match {
				for ebv_i := match[0]; ebv_i < match[1]; ebv_i++ {
					ebv.set(ebv_i, true)
				}
			}
		}

		for i := 0; i < len(line); i++ {
			if ebv.index(i) {
				fmt.Printf("\x1B[32m%c\x1B[97m", line[i])
			} else {
				fmt.Printf("%c", line[i])
			}
		}

		fmt.Println("")
		ebv.clear()

	}
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
