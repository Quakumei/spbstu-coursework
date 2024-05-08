all: run_main

run_main: main test/testfiles/1.txt
	out/main.exe test/testfiles/1.txt

main: out/main.exe

run_test: out/test.exe
	out/test.exe

out/test.exe: test/tests.cpp
	g++ $^ -o $@

out/main.exe: src/main.cpp src/utility.cpp src/Logger.cpp
	g++ $^ -o $@

clean:
	rm -rf out/*
