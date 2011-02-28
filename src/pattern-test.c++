/// File: pattern-test.c++
/// Author: Gregory Rickeard
/// Data: 26/02/2011
///
/// Simple test case for pattern library



#include "pattern.h++"
#include <iostream>

using namespace drg::knitting;
using namespace std;

int main(int argc, char **argv) {
  unsigned int i;
  pattern pat;
  row r(5);
  stitch k("knit", "k");
  stitch p("purl", "p");
  stitch s("Slip", "s");

  pat.add_row(r);
  pat.add_row(r);
  for (i = 0 ; i < r.length ; i++) {
    r[i] = k;
  }
  pat.add_row(r);

  for (i = 0 ; i < r.length - 2 ; i++) {
    r[i] = p;
  }
  for ( ; i < r.length - 2 ; i++) {
    r[i] = k;
  }

  pat.add_row(r);
  
  pat[1][4] = s;


  cout << k << endl
       << r << endl
       << r.concise() << endl
       << r.simple() << endl;
  
  cout << pat << endl;
  cout << pat.concise() << endl;
  
}
