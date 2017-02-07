package main

import (
	"bytes"
	"fmt"
	"golang.org/x/net/html"
	"io"
	"net/http"
	"os"
	"strings"
	"sync"
)

const problemListPrefix = "http://codeforces.com/problemset/page/"
const problemPrefix = "http://codeforces.com"
const firstPage = 1
const lastPage = 33
const problemsPerPage = 100

func ParseUrlsFromPage(r io.Reader) []string {
	urls := []string{}
	tok := html.NewTokenizer(r)
	for tt := tok.Next(); tt != html.ErrorToken; tt = tok.Next() {
		if tt == html.StartTagToken {
			if t := tok.Token(); t.Data == "a" {
				for _, a := range t.Attr {
					if a.Key == "href" {
						if strings.Contains(a.Val, "problemset/problem") {
							urls = append(urls, problemPrefix+a.Val)
						}
					}
				}
			}
		}
	}
	return urls
}

func IsStatementDiv(n *html.Node) bool {
	for _, a := range n.Attr {
		if a.Key == "class" && a.Val == "problem-statement" {
			return true
		}
	}
	return false
}

func ScrapePage(url string, res chan<- string, wg *sync.WaitGroup) {
	defer wg.Done()
	resp, err := http.Get(url)
	if err != nil {
		fmt.Println(err)
		return
	}
	root, err := html.Parse(resp.Body)
	if err != nil {
		fmt.Println(err)
		return
	}
	var f func(*html.Node, bool) string
	f = func(n *html.Node, statement bool) string {
		if n.Type == html.ElementNode && n.Data == "div" && IsStatementDiv(n) {
			var b bytes.Buffer
			html.Render(&b, n)
			return b.String()
		}
		for c := n.FirstChild; c != nil; c = c.NextSibling {
			if s := f(c, statement); s != "" {
				return s
			}
		}
		return ""
	}
	res <- f(root, false)
}

func PrintProblems(urls []string) {
	res := make(chan string, len(urls))
	wg := sync.WaitGroup{}
	for _, url := range urls {
		wg.Add(1)
		go ScrapePage(url, res, &wg)
	}
	wg.Wait()
	close(res)
	for s := range res {
		fmt.Println(s)
	}
}

func ScrapeSite(prefix string, low int, high int) {
	for i := low; i <= high; i++ {
		url := fmt.Sprintf("%s%d", prefix, low)
		resp, err := http.Get(url)
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Fprintf(os.Stderr, "Parsing batch %d of URLs\n", i)
		urls := ParseUrlsFromPage(resp.Body)
		fmt.Fprintf(os.Stderr, "Printing problems for batch %d of URLs\n", i)
		PrintProblems(urls)
	}
}

func main() {
	ScrapeSite(problemListPrefix, firstPage, lastPage)
}
