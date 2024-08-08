# Makefile for CodeBreaker Java project

# Compile the Java program
compile:
	javac CodeBreaker.java

# Run the compiled Java program
run:
	java CodeBreaker

# Clean the directory by removing the class file
clean:
	rm -f *.class

# Default target to compile the program
default: compile
