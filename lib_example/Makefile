
lib_objs=lib_example1.o lib_example2.o 
.DUMMY: test all


all: lib_example.so test 

test: lib_example_test
	@LD_LIBRARY_PATH+=. ./$^


lib_example_test: lib_example_test.c $(lib_objs) 
	cc -o $@ $^ -I../ 

lib_%.o: lib_%.c lib_example.h 
	cc -c -fPIC -I../ $<

lib_example.so: $(lib_objs) 
	cc -o $@ -shared  $^ 

clean:
	rm -f lib_example_test *.o *.so 








