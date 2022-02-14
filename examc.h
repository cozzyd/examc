/**

examc - Crappy C unit test library, header-only. This is mostly a proof of
concept experiment to generate one using linker sections. This is probably
horribly unportable and broken. Don't use. 


Copyright 2022 Cosmin Deaconu <cozzyd@kicp.uchicago.edu> 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:


The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef _EXAMC_H
#define _EXAMC_H
#include <stdio.h> 


#define EXAMC_VERSION "0.1"
#define EXAMC_SECTION __attribute__((section("examc")))


struct examc_q
{
  const char * name; 
  void (*fn)(); 
}; 


#define EXAMC_NAMED_TEST(what,nm) \
static void what(); \
static struct examc_q what##_s = { .name = nm, .fn = &what }; \
static struct examc_q * what##_s_ptr EXAMC_SECTION = &what##_s;  \
void what()

#define EXAMC_TEST(what) EXAMC_NAMED_TEST(what,#what) 


//EXAMC_TEST(dummy) { ; }

extern struct examc_q* __start_examc;
extern struct examc_q* __stop_examc;

#ifdef EXAMC_NO_MAIN
extern int examc_npass;
extern int examc_nfail;
#else
int examc_npass;
int examc_nfail;
#endif


#define EXAMC_FAIL(file,line,expr) printf("\n     failing check:  %s (%s:%d) ",expr,  file ,line)

#define EXAMC_CHECK(condition) \
 do \
 {\
   if (condition) examc_npass++;\
   else\
   {\
     EXAMC_FAIL(__FILE__,__LINE__, #condition);\
     examc_nfail++; \
   }\
 }\
 while (0); 


#ifndef EXAMC_NO_MAIN
int main(int nargs, char ** args) 
{

  struct examc_q ** q =  &__start_examc; 
  struct examc_q ** qend  =  &__stop_examc; 
  int itest = 0; 
  int npass = 0;
  int ntotal = 0; 
  int ntotal_parts = 0;
  printf("Running tests (examc %s)...\n---\n", EXAMC_VERSION);
  while (q!=qend) 
  {
    int current_npass = examc_npass; 
    int current_nfail = examc_nfail; 
    printf("[%d] %s: ", itest++, (*q)->name); 
    (*q)->fn(); 
    int total_parts = examc_npass + examc_nfail - current_npass - current_nfail; 
    if (!total_parts) 
    {
      printf("  !WARNING: test \"%s\" has no check! Skipping.", (*q)->name); 
    }
    int failed = examc_nfail - current_nfail;
    npass+= !failed; 
    ntotal_parts+= total_parts; 
    ntotal++; 
    
    printf("\n  %s (%d/%d parts passed) \n-----\n", failed ? "FAILED" : "PASSED", total_parts - failed, total_parts); 

    q++; 
  } 
  printf ("SUMMARY:  %d/%d tests passed (%d/%d parts) \n", npass, ntotal, examc_npass, ntotal_parts); 
  return examc_nfail; 
}
#endif
  
  

#endif 




