main: out/main.exe
	out/main.exe
test-containers: out/test-containers.exe
	out/test-containers.exe

out/main.exe: out/main.o out/ExprCalc.a
	g++ $^ -o $@

out/main.o: src/main.cpp 
	g++ -c $< -o $@

out/ExprCalc.a:  out/Tokenize.o out/ExpressionCalculator.o
	ar rcs $@ $^

out/Tokenize.o: src/Tokenize.cpp 
	g++ -c $< -o $@

out/ExpressionCalculator.o: src/ExpressionCalculator.cpp 
	g++ -c $< -o $@


out/test-containers.exe: test/test-containers.cpp src/Stack.hpp src/Queue.hpp src/List.hpp 
	g++ $< -o $@

clean:
	rm -rf out/*
