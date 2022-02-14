//this is important, it keeps it from generating main here! 
#define EXAMC_NO_MAIN
#include "examc.h" 


#include "lib_example.h" 

EXAMC_TEST(test_foo)
{
  EXAMC_CHECK(foo() == 2); 
}



int foo() 
{
  return 2; 
}
