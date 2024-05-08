main: out/main.exe
	out/main.exe
test-containers: out/test-containers.out
	out/test-containers.out

out/main.exe: src/main.cpp out/ExpressionCalculator.o
	g++ $^ -o $@

out/ExpressionCalculator.o: src/ExpressionCalculator.cpp
	g++ -c $< -o $@

out/test-containers.out: test/test-containers.cpp src/Stack.hpp src/Queue.hpp src/List.hpp
	g++ $< -o $@

clean:
	rm -rf out/*.o
