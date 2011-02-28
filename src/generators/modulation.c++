#include "../pattern.h++"
#include <iostream>
#include <cmath>
#include <queue>
#include <string>

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



queue<unsigned int> split_message(string mesg, unsigned int chunk_size) {
  queue<unsigned int> split_mesg;
  for (string::iterator i = mesg.begin() ; i < mesg.end() ; i++) {
    char c = *i;
    unsigned int mask = pow(2, chunk_size);
    split_mesg.push(c^mask);
    c >>= 2;
    split_mesg.push(c^mask);
    c >>= 2;
    split_mesg.push(c^mask);
    c >>= 2;
    split_mesg.push(c^mask);
  }
  return split_mesg;
}

double calc_phase_shift(unsigned int chunk, unsigned int order) {
  return chunk * 2 * M_PI / pow(2, order);
}

void cable_from_to(pattern &p,
		   unsigned int r1, unsigned int c1,
		   unsigned int r2, unsigned int c2) {
  //DRG TODO change so it doesn't assume r1 and r2 are adjacent.

  switch (c1 - c2) {
  case (3)  : p[r2][c2] = c4r;
    break;
  case (2)  : p[r2][c2] = c3r;
    break;
  case (1)  : p[r2][c2] = c2r;
    break;
  case (-1) : p[r2][c1] = c2l;
    break;
  case (-2) : p[r2][c1] = c3l;
    break;
  case (-3) : p[r2][c1] = c4l;
    break;
  default   : p[r2][c1] = (p[r2-1][c2] == s) ? k : s;
  }


}


pattern modulate_message(string mesg,
			 unsigned int rows, unsigned int columns,
			 unsigned int amplitide,
			 unsigned int y_zero, unsigned int x_zero,
			 unsigned int wave_length, unsigned int chunk_length) {
  pattern p(rows, columns, k);

  unsigned int y;
  unsigned int y_;

  double dx = M_PI * 2 / wave_length;

  queue<unsigned int> split_mesg = split_message(mesg, 2);
  
  y_ = 20;

  for (unsigned int x = 1 ; x < (rows - chunk_length)  && !split_mesg.empty() ; x += chunk_length) {
    cout << x << ", " << flush;
    double phase = calc_phase_shift(split_mesg.front(), 2);
    
    split_mesg.pop();


    for (unsigned int x_ = x ; x_ < (x + chunk_length) ; x_++) {
      y = round(10 + ((sin(((x_-1)*dx) + phase) + 1) * 10)); 
  
      cable_from_to(p, x_ - 1, y_, x_, y);
    
      y_ = y;
    }
  }
  return p;
}


int main(int argc, char ** argv) {
  pattern p;
  vector<unsigned char> m;

  p = modulate_message("modulation", 800, 40, 10, 20, 1, 20, 20);

    
  std::cout << p.concise() << endl
	    << p;
  
  return 0;
}

  
