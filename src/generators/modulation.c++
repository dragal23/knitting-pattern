#include "../pattern.h++"
#include <iostream>
#include <cmath>

using namespace drg::knitting;
using namespace std;

stitch k("Knit", "k");
stitch p("Purl", "p");
stitch c2l("Cable 2 left", "\\\\");
stitch c2r("Cable 2 right", "//");
stitch c3l("Cable 3 left", "-\\-");
stitch c3r("Cable 3 right", "-/-");
stitch c4l("Cable 4 left", "-\\\\-");
stitch c4r("Cable 4 right", "-//-");
stitch s("Slip", "s");



int main(int argc, char ** argv) {
  pattern p(40, 800);
  
  /// First just a sign wave!
  unsigned int y;
  unsigned int y_;

  double dx = .25;

  // initialize pattern as all knit!
  for (unsigned int x = 0 ; x < 800 ; x++) {
    for (unsigned int y = 0 ; y < 40 ; y++) {
      p[x][y] = k;
    }
  }

  y_ = round(10 + ((sin(0) + 1) * 10));
  for (unsigned int x = 1 ; x < 800 ; x++) {
    y = round(10 + ((sin(x*dx) + 1) * 10));
    switch (y - y_) {
    case (3)  : p[x][y_] = c4r;
                break;
    case (2)  : p[x][y_] = c3r;
                break;
    case (1)  : p[x][y_] = c2r;
                break;
    case (-1) : p[x][y] = c2l;
                break;
    case (-2) : p[x][y] = c3l;
                break;
    case (-3) : p[x][y] = c4l;
                break;
    default   : p[x][y] = (p[x-1][y] == s) ? k : s;
    }
    y_ = y;
  }
    
  std::cout << p.concise() << endl
	    << p;
  
  return 0;
}

  
