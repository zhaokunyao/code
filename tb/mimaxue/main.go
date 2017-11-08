
package main

import(
	"fmt"
//	"runtime"
	"sync"
//	"time"
)

var (
	counter int
	wg sync.WaitGroup
	mutex sync.Mutex
)


func main(){
	court := make(chan int)

	wg.Add(1)
	court <- 10
	go test(court)
	//go incCounter(2)
	
	//counter := <-court
	counter := 9
	wg.Wait()
	fmt.Println("Final Counter:" , counter)
}


func test(court chan int){
	defer wg.Done()
	fmt.Println("waiting to receive data:" )
	tmp := <-court
	fmt.Println("receive data:" , tmp)
}
