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
  
  pattern pat;
  row r(5);
  stitch k("knit", "k");
  stitch p("purl", "p");

  pat.add_row(r);
  pat.add_row(r);
  for (unsigned int i = 0 ; i < r.length ; i++) {
    r[i] = k;
  }
  pat.add_row(r);

  for (unsigned int i = 0 ; i < r.length ; i++) {
    r[i] = p;
  }
  pat.add_row(r);
  

  cout << k << endl
       << r << endl
       << pat
       << pat.concise() << endl;
  
}
