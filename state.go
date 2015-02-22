package main

import "time"
import "fmt"

type state func(e string)

type Light interface {
	TurnOn()
	Dim()
	TurnOff()
}

type ApartmentLight struct {
	Light
	handle  state
	timer   time.Duration
	timeOn  time.Duration
	timeDim time.Duration
}

func NewApartmentLight(l Light, to time.Duration, td time.Duration) *ApartmentLight {
	var ret ApartmentLight
	ret.timeDim = td
	ret.timeOn = to
	ret.Light = l
	off_state(&ret)
	return &ret
}

func (a *ApartmentLight) Press() {
	a.handle("press")
}

func (a *ApartmentLight) Tick() {
	a.handle("tick")
}

func off_state(a *ApartmentLight) {
	//Entry event
	a.TurnOff()
	//Exit events
	a.handle = func(e string) {
		if e == "press" {
			on_state(a)
		}
	}
}

func dim_state(a *ApartmentLight) {
	//Entry event
	a.Dim()
	a.timer = a.timeDim - time.Second
	//Exit events
	a.handle = func(e string) {
		switch {
		case e == "press":
			on_state(a)
		case e == "tick" && a.timer > 0:
			a.timer -= time.Second
		case e == "tick":
			off_state(a)
		}
	}
}

func on_state(a *ApartmentLight) {
	//Entry event
	a.TurnOn()
	a.timer = a.timeOn - time.Second
	//Exit events
	a.handle = func(e string) {
		switch {
		case e == "press":
			on_state(a)
		case e == "tick" && a.timer > 0:
			a.timer -= time.Second
		case e == "tick":
			dim_state(a)
		}
	}
}

//Example usage:

type MyLight struct {
	intensity float32
}

func (l *MyLight) TurnOn() {
	l.intensity = 1.0
}

func (l *MyLight) Dim() {
	l.intensity = 0.7
}

func (l *MyLight) TurnOff() {
	l.intensity = 0
}

func (l *MyLight) Brightness() float32 {
	return l.intensity
}

func main() {
	var l MyLight
	apt := NewApartmentLight(&l, time.Second*5, time.Second*10)
	fmt.Printf("Lightbulb is currently: %1.2f bright\n", l.Brightness())
	apt.Press()
	fmt.Printf("Lightbulb is currently: %1.2f bright\n", l.Brightness())
	for i := 0; i < 5; i++ {
		apt.Tick()
	}
	fmt.Printf("Lightbulb is currently: %1.2f bright\n", l.Brightness())
	for i := 0; i < 10; i++ {
		apt.Tick()
	}
	fmt.Printf("Lightbulb is currently: %1.2f bright\n", l.Brightness())
}
