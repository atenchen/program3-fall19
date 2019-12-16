flags = -Wall -Werror -g -std=c++1z
name = program3
file1 = Planet
file2 = Galaxy

all: $(name).o $(file1).o $(file2).o
	g++ $(flags) $(name).o $(file1).o $(file2).o -o $(name)

$(name).o: $(name).cpp
	g++ -c $(flags) $(name).cpp

$(file1).o: $(file1).cpp
	g++ -c $(flags) $(file1).cpp

$(file2).o: $(file2).cpp
	g++ -c $(flags) $(file2).cpp

run: all
	./$(name)
memcheck: all
	valgrind ./$(name)
clean:
	rm -rf *.o $(name)
