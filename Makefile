
all: build

build-space:
	g++ space.cpp -o space --std=c++11 -O2

build-earth:
	g++ earth.cpp -o earth --std=c++11 -O2

build: build-space build-earth
    
run-p1:
	./space
	
run-p2:
	./earth

clean:
	rm -f space earth *.out