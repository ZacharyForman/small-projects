package main

import (
	"image"
	"image/color"
	"image/png"
	"log"
	"math/cmplx"
	"os"
	"runtime"
	"sync"
)

var (
	plt []color.Color
	max_iter int
)

/*
const (
	x_min       = -1.9
	y_min       = -1.2
	x_max       = 0.7
	y_max       = 1.2
	scale       = 10000
	max_workers = 9
)
*/

const (
	x_min       = -1.5
	y_min       = -0.5
	x_max       = -0.7
	y_max       = 0.5
	scale       = 30000
	max_workers = 9
)

type mandelrow struct {
	m *image.RGBA
	y int
}

func extract_palette(imagename string) {
	reader, err := os.Open(imagename)
	if err != nil {
		log.Fatal(err)
	}
	m, err := png.Decode(reader)
	if err != nil {
		log.Fatal(err)
	}
	b := m.Bounds()
	plt = make([]color.Color, b.Max.Y-b.Min.Y)
    for i := b.Min.Y; i < b.Max.Y; i++ {
        plt[i] = m.At(b.Min.X, i)
    }
    max_iter = len(plt) - 1
}

func work(w <-chan mandelrow, wg *sync.WaitGroup) {
	defer wg.Done()
	for {
		mr, cl := <-w
		if !cl {
			return
		}
		m := mr.m
		b := m.Bounds()
		y := mr.y
		for x := b.Min.X; x < b.Max.X; x++ {
			//calculate iterations taken
			z := complex(0, 0)
			c := complex(float64(x)/scale, float64(y)/scale)
			iter := 0
			for iter = 0; iter < max_iter && cmplx.Abs(z) <= 2; iter++ {
				z = z*z + c
			}
			color := plt[iter]
			m.Set(x, y, color)
			m.Set(x, (b.Max.Y+b.Min.Y)/2-y, color)
		}
	}
}

func mandelbrot(m *image.RGBA) {
	mrchan := make(chan mandelrow)
	b := m.Bounds()
	var wg sync.WaitGroup
	for i := 0; i < max_workers; i++ {
		wg.Add(1)
		go work(mrchan, &wg)
	}
	for y := b.Min.Y; y <= (b.Max.Y+b.Min.Y)/2; y++ {
		mrchan <- mandelrow{m, y}
	}
	log.Print("Finished allocating work.")
	close(mrchan)
	wg.Wait()
}

func main() {
	runtime.GOMAXPROCS(7)
	log.Print("Starting.")
    extract_palette("gradient2.png")
	m := image.NewRGBA(image.Rect(x_min*scale, y_min*scale, x_max*scale, y_max*scale))
	//populate workers
	mandelbrot(m)
	out_filename := "mandelbrot.png"
	out_file, err := os.Create(out_filename)
	if err != nil {
		log.Fatal(err)
	}
	defer out_file.Close()
	log.Print("Saving image to: ", out_filename)
	png.Encode(out_file, m)
	log.Print("Done")
}
