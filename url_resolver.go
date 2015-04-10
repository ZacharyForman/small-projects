package main

import "net/http"
import "fmt"
import "time"

func resolve(url string, client http.Client) {
	response, err := client.Get(url)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(response)
}

func main() {

	urls := []string{"http://bit.ly/a5aJTN", "http://ow.ly/179rAK", "http://bit.ly/dBOZBX",
		"http://bit.ly/c2vsrm", "http://bit.ly/cBNpft", "http://www.twitter.com",
		"http://www.tweeplesay.com", "http://www.pinay-chicken-heart.com",
		"http://wwe.com"}

	for _, url := range urls {
		go resolve(url, http.Client{})
	}
	time.Sleep(5 * time.Second)
}
