package main

import (
	"fmt"
	"github.com/jaytaylor/html2text"
	"golang.org/x/net/html"
	"io"
	"net/http"
	"os"
	"strings"
	"sync"
	"time"
)

const problemListPrefix = "http://codeforces.com/problemset/page/"
const problemPrefix = "http://codeforces.com"
const firstPage = 1
const lastPage = 33
const problemsPerPage = 100
// Delay ~= ping from us to codeforces.com
const delayBetweenRequests = 350 * time.Millisecond

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

func ScrapePage(url string, wg *sync.WaitGroup) {
	defer wg.Done()
	resp, err := http.Get(url)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		return
	}
	defer resp.Body.Close()
	root, err := html.Parse(resp.Body)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		return
	}
	var f func(*html.Node, bool) string
	f = func(n *html.Node, statement bool) string {
		if n.Type == html.ElementNode && n.Data == "div" && IsStatementDiv(n) {
			res, err := html2text.FromHtmlNode(n)
			if err != nil {
				fmt.Fprintf(os.Stderr, "%s\n", err)
				return ""
			}
			return res
		}
		for c := n.FirstChild; c != nil; c = c.NextSibling {
			if s := f(c, statement); s != "" {
				return s
			}
		}
		return ""
	}
	fmt.Println(f(root, false), "\n")
}

func PrintProblems(urls []string) {
	wg := sync.WaitGroup{}
	for _, url := range urls {
		wg.Add(1)
		go ScrapePage(url, &wg)
	}
	wg.Wait()
}

func ScrapeSite(prefix string, low int, high int) {
	wg := sync.WaitGroup{}
	for i := low; i <= high; i++ {
		wg.Add(1)
		inner := i
		go func() {
			defer wg.Done()
			url := fmt.Sprintf("%s%d", prefix, inner)
			resp, err := http.Get(url)
			defer resp.Body.Close()
			if err != nil {
				fmt.Fprintf(os.Stderr, "%s\n", err)
				return
			}
			fmt.Fprintf(os.Stderr, "Parsing batch %d of URLs\n", inner)
			urls := ParseUrlsFromPage(resp.Body)
			fmt.Fprintf(os.Stderr, "Printing problems for batch %d of URLs\n", inner)
			PrintProblems(urls)
		}()
		time.Sleep(delayBetweenRequests)
	}
	wg.Wait()
}

func main() {
	ScrapeSite(problemListPrefix, firstPage, lastPage)
}
