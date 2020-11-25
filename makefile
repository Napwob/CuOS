all: build/ bin/ bin/lab5
build/:
	mkdir build/ -p
bin/:
	mkdir bin/ -p
bin/lab5: bin/libcookie.so bin/libclearcookie.so
	g++ -Wall -w -o bin/client src/lab4c.cpp -ldl
	g++ -Wall -w -o bin/server src/lab4s.cpp -ldl
bin/libcookie.so: build/cookie.o
	g++ -shared -o bin/libcookie.so build/cookie.o
bin/libclearcookie.so: build/clearcookie.o
	g++ -shared -o bin/libclearcookie.so build/clearcookie.o
build/cookie.o: src/cookie.cpp
	g++ -Wall -c -fPIC -o build/cookie.o src/cookie.cpp
build/clearcookie.o: src/clearcookie.cpp
	g++ -Wall -c -fPIC -o build/clearcookie.o src/clearcookie.cpp
