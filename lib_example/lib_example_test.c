#include "examc.h" 
#include "lib_example.h" 

//other tests are defined throughout the library, but we can add some here too 
//otherwise it would be sufficient to just include exam.h 

EXAMC_TEST(foobar_test)
{
  EXAMC_CHECK(foo() != bar()) 
}

