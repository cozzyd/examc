
prog = examc_example

.DUMMY: clean test

test: $(prog) 
	@./$(prog) 

clean:
	rm -f prog
