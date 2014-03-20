package main

import "fmt"
import "math/rand"
import "time"

type sort func([]int)

func requireSorted(arr []int) {
	for i := 1; i < len(arr); i++ {
		if arr[i] < arr[i-1] {
			fmt.Printf("Not sorted.\n")
			fmt.Println(arr)
			return
		}
	}
}

//selectionsort
func selectionsort(arr []int) {
	for i := 0; i < len(arr); i++ {
		mpos := i
		for j := i; j < len(arr); j++ {
			if arr[j] < arr[mpos] {
				mpos = j
			}
		}
		arr[i], arr[mpos] = arr[mpos], arr[i]
	}
}

//insertionsort
func insertionsort(arr []int) {
	for i := 0; i < len(arr); i++ {
		iPos := i
		iVal := arr[i]
		for iPos > 0 && iVal < arr[iPos-1] {
			arr[iPos] = arr[iPos-1]
			iPos--
		}
		arr[iPos] = iVal
	}
}

//bubblesort
func bubblesort(arr []int) {
	swap := true
	for swap {
		swap = false
		for i := 0; i < len(arr)-1; i++ {
			if arr[i] > arr[i+1] {
				swap = true
				arr[i], arr[i+1] = arr[i+1], arr[i]
			}
		}
	}
}

//heapsort
type heap struct {
	arr []int
	n   int
}

func (h *heap) siftdown(pos int) {
	left := 2*pos + 1
	right := 2*pos + 2
	largest := pos
	if left <= h.n && h.arr[left] > h.arr[largest] {
		largest = left
	}
	if right <= h.n && h.arr[right] > h.arr[largest] {
		largest = right
	}
	if largest != pos {
		h.arr[pos], h.arr[largest] = h.arr[largest], h.arr[pos]
		h.siftdown(largest)
	}
}

func (h *heap) siftup(pos int) {
	if pos == 0 {
		return
	}
	if h.arr[pos] > h.arr[(pos-1)/2] {
		h.arr[pos], h.arr[(pos-1)/2] = h.arr[(pos-1)/2], h.arr[pos]
		h.siftup((pos - 1) / 2)
	}
}

func (h *heap) insert(val int) {
	h.arr[h.n] = val
	h.siftup(h.n)
	h.n++
}

func (h *heap) removemin() int {
	min := h.arr[0]
	h.n--
	h.arr[0] = h.arr[h.n]
	h.siftdown(0)
	return min
}

func makeheap(arr []int) heap {
	var h heap
	h.arr = arr
	for i := 0; i < len(arr); i++ {
		h.insert(arr[i])
	}
	return h
}

func heapsort(arr []int) {
	h := makeheap(arr)
	for _ = range arr {
		arr[h.n] = h.removemin()
	}
}

//mergesort
func mergesort(arr []int) {

}

//quicksort
func quicksort(arr []int) {
	if len(arr) <= 1 {
		return
	}
	last := 0
	for i := 1; i < len(arr); i++ {
		if arr[i] < arr[0] {
			last++
			arr[i], arr[last] = arr[last], arr[i]
		}
	}
	arr[0], arr[last] = arr[last], arr[0]
	quicksort(arr[:last])
	quicksort(arr[last+1:])
}

func testcase(s sort, n int) {
	arr := make([]int, n)
	for i := 0; i < n; i++ {
		arr[i] = rand.Int() % n
	}
	t := time.Now()
	s(arr)
	fmt.Printf("%d : %v\n", n, time.Since(t))
	requireSorted(arr)
}

func testsort(s sort, name string) {
	fmt.Printf("%s\n", name)
	for i := 2 << 10; i < 2<<25; i = i << 1 {
		testcase(s, i)
	}
}

func main() {
	rand.Seed(time.Now().Unix())
	fmt.Println("Starting tests!")
	//testsort(selectionsort, "selectionsort")
	//testsort(insertionsort, "insertionsort")
	//testsort(bubblesort, "bubblesort")
	testsort(quicksort, "quicksort")
	testsort(heapsort, "heapsort")
	//testsort(mergesort, "mergesort")
	fmt.Println("Finished tests!")
}
