# Makefile variables
CC = g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11

# All Targets
all: cTrace

# Tool invocations
cTrace: bin/Agent.o bin/Graph.o bin/Session.o bin/Tree.o bin/main.o
	@echo 'Building all targets'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/cTrace bin/Agent.o bin/Graph.o bin/Session.o bin/Tree.o bin/main.o
	@echo 'Finished building target'
	@echo ' '

# Depends on the source and header files
bin/Agent.o: src/Agent.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Agent.o src/Agent.cpp

# Depends on the source and header files 
bin/Graph.o: src/Graph.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Graph.o src/Graph.cpp

# Depends on the source and header files 
bin/Session.o: src/Session.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Session.o src/Session.cpp

# Depends on the source and header files 
bin/Tree.o: src/Tree.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Tree.o src/Tree.cpp

# Depends on the source and header files 
bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp

#Clean the build directory
clean: 
	rm -f bin/*