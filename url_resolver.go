package main

import "net/http"
import "fmt"
import "net"
import "os"
import "bufio"
import "runtime"
import "net/url"
import "time"

func resolve(urlString string, client http.Client, responses chan<- string) {
	response, err := client.Get(urlString)
	host := "N/A"
	if err != nil {
		if dnsErr, ok := err.(*net.DNSError); ok {
			host = dnsErr.Name
		}
		if urlError, ok := err.(*url.Error); ok {
			if urlError.URL != urlString {
				requestUrl, err := url.Parse(urlError.URL)
				if err == nil {
					host = requestUrl.Host
				}
			}
		}
	}
	if response != nil {
		host = response.Request.URL.Host
	}
	responses <- fmt.Sprintf("%s: %v", urlString, host)
}

func main() {
	runtime.GOMAXPROCS(4)
	scanner := bufio.NewScanner(os.Stdin)
	hosts := make(chan string)
	count := 0
	client := http.Client{}
	client.Timeout = 2 * time.Second
	seen := make(map[string]struct{})
	for scanner.Scan() {
		targetUrl := scanner.Text()
		if _, there := seen[targetUrl]; !there {
			count++
			go resolve(targetUrl, client, hosts)
			seen[targetUrl] = struct{}{}
		}
	}

	for count > 0 {
		host := <-hosts
		fmt.Println(host)
		count--
	}
}
