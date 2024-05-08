main: out/main.exe

run_main: out/main.exe
	out/main.exe test/lists_1.txt

run_test: out/test.exe
	out/test.exe

out/test.exe: test/tests.cpp
	g++ $^ -o $@

out/main.exe: src/main.cpp src/utils.cpp
	g++ $^ -o $@

clean:
	rm -rf out/*
