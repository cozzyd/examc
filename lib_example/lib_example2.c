#define EXAMC_NO_MAIN
#include "examc.h" 

#include "lib_example.h"


EXAMC_TEST(test_bar)
{
  EXAMC_CHECK(bar() == 42); 
}


int bar() 
{
  return 42; 
}
