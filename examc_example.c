
#include "examc.h" 

/* Don't define a main, examc.h does it for you! */ 


// this is a really basic test. The argument to EXAMC_TEST needs to be a legal identifier (i.e. no spaces and such)
EXAMC_TEST(should_pass)
{
  EXAMC_CHECK(2+2 == 4) ; //the semicolon is optional 
}

EXAMC_TEST(should_fail)
{
  EXAMC_CHECK(2+2 == 5) 
}

// If you want to use a fancier name for your test, you can, but it still needs an identifier (which is useful for debugging your test anyway). 
// It would be possible to use fancy macro magic to autogenerate an identifier, but meh.
EXAMC_NAMED_TEST(fancy_test,"This test has a fancy name!") 
{
  EXAMC_CHECK(1); 
}
