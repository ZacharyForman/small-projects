package main

import "net/http"
import "fmt"
import "net"
import "os"
import "bufio"
import "runtime"
import "net/url"
import "time"
import "sync"

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
	client := http.Client{}
	client.Timeout = 2 * time.Second
	seen := make(map[string]struct{})
	wg := sync.WaitGroup{}
	go func() {
		for host := range hosts {
			fmt.Println(host)
		}
	}()
	for scanner.Scan() {
		targetUrl := scanner.Text()
		if _, there := seen[targetUrl]; !there {
			wg.Add(1)
			go func() {
				defer wg.Done()
				resolve(targetUrl, client, hosts)
			}()
			seen[targetUrl] = struct{}{}
		}
	}
	wg.Wait()
}
