#include "../pattern.h++"
#include <iostream>
#include <cmath>
#include <queue>
#include <string>
#include <psk.h++>
#include <cassert>
#include <algorithm>


using namespace drg::knitting;
using namespace drg::modulation;
using namespace std;

stitch k("Knit", "k");
stitch p("Purl", "p");
stitch c2l("Cable 2 left", "\\\\");
stitch c2r("Cable 2 right", "//");
stitch c3l("Cable 3 left", "-\\-");
stitch c3r("Cable 3 right", "-/-");
stitch c4l("Cable 4 left", "-\\\\-");
stitch c4r("Cable 4 right", "-//-");
stitch c5l("Cable 5 left", "-\\\\\\-");
stitch c5r("Cable 5 right", "-///-");
stitch c6l("Cable 6 left", "-\\\\\\\\-");
stitch c6r("Cable 6 right", "-////-");
stitch c7l("Cable 7 left", "-\\\\\\\\\\-");
stitch c7r("Cable 7 right", "-/////-");
stitch s("Slip", "s");




void cable_from_to(pattern &p,
		   unsigned int r1, unsigned int c1,
		   unsigned int r2, unsigned int c2) {
  //DRG TODO change so it doesn't assume r1 and r2 are adjacent.

  switch (c1 - c2) {
    //  case (6)  : p[r2][c2] = c7l;
    //    break;
  case (5)  : p[r2][c2] = c6l;
    break; 
  case (4)  : p[r2][c2] = c5l;
    break;
  case (3)  : p[r2][c2] = c4l;
    break;
  case (2)  : p[r2][c2] = c3l;
    break;
  case (1)  : p[r2][c2] = c2l;
    break;
  case (0)  : p[r2][c1] = (p[r2-1][c2] == s) ? k : s;
    break;
  case (-1) : p[r2][c1] = c2r;
    break;
  case (-2) : p[r2][c1] = c3r;
    break;
  case (-3) : p[r2][c1] = c4r;
    break;
  case (-4) : p[r2][c1] = c5r;
    break;
  case (-5) : p[r2][c1] = c6r;
    break;
    //  case (-6) : p[r2][c1] = c7r;
    //    break;
  default   : for (unsigned int i = min(c1, c2) ; i < max(c1, c2) ; i++) 
                p[r2][i] = s;
      
  }


}


int main(int argc, char ** argv) {
  cout << "start" << endl;

  // Initialize out pattern in plain garter stitch!
  pattern p(800, 40, k);

  // Our library of encodings (as consellation)
  constellations con;

  /* Initialise our PSK modulator.
     With interval 1 and frequency 1 each baud takes 1 second. thereby the 
     length of our signal will be <length> * 4 seconds */
  psk mod(1, 2, 1, con.get("4qam"));
  
  string msg("PSK Modulation");

  cout << "foo" << endl;

  /* Generate our signal. We want this to take approximataly 700 samples to
     complete. Thereby the sample rate should be:
     msg.length() * 4 / 700 */ 
  cout << msg.length() << ", " << (msg.length() * 4.0) / 700 << endl;

  vector<pair<double, double> > signal = mod.generate(msg, (msg.length() * 4.0) / 700);
  
  cout << "foo" << endl;
  

  // Allow for rounding error in our assert!
  //  assert(0 <= (700 - signal.size()) && (700 - signal.size()) <= 1);
  cout << "signal length = " << signal.size() << endl;


  //Add to pattern!
  unsigned int r = 5;
  
  vector<pair<double, double> >::iterator i = signal.begin();


  cout << "foo" << endl;
  
  unsigned int c_ = 20 + ((*i).second * 10);
  i++;
  for ( ; i < signal.end() ; i++) {
    unsigned int c = 20 + ((*i).second * 10);
    cable_from_to(p, r-1, c_, r, c);
    r++;
    c_ = c;
  }
  
  cout << p << endl;

  return 0;
}

  
