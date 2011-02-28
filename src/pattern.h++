/// File: pattern.h++
/// Author: Gregory Rickeard
/// Data: 26/02/2011
///
/// Header files for my knitting pattern library.


#if !defined __DRG_KNITTING_PATTERN
#define __DRG_KNITTING_PATTERN

#include <string>
#include <ostream>
#include <stdexcept>
#include <vector>



namespace drg {
  namespace knitting {

    
    class stitch {
      std::string name;
      std::string abbrv;
    public:
      stitch() 
	: name(), abbrv() { }
      stitch(const std::string &n, const std::string &a)
	: name(n), abbrv(a) { }

      const std::string &get_name();
      const std::string &get_abbrv();
      bool operator==(const stitch &s) const;
      bool operator!=(const stitch &s) const;
      stitch &operator=(const stitch &s);
      friend std::ostream &operator<<(std::ostream &o, const stitch &s);
      
    };


    class row {
    private:
      stitch *s;
    public:
      const unsigned int length;

      row()
	: s(), length(0) { }
      row(const unsigned int l) 
	: length(l) {
	s = new stitch[length];
      }
      row(const row &r) 
	: length(r.length) {
	s = new stitch[length];
	for (unsigned int i = 0 ; i < length ; i++) {
	  s[i] = r.s[i];

	}
      }


      stitch &operator[](unsigned int i) throw(std::out_of_range);
      std::string simple() const;
      std::string concise() const;

      bool operator==(const row &r) const;
      bool operator!=(const row &s) const;
      row &operator=(const row &r);

      friend std::ostream &operator<<(std::ostream & o, const row &r);
    };


    class pattern {
    private:
      std::vector<row> rows;
    public:
      
      pattern()
	: rows() { }
      pattern(const unsigned int rows_, const unsigned int columns_) {
	for (unsigned int i = 0 ; i < rows_ ; i++) {
	  add_row(row(columns_));
	}
      }
      pattern(const unsigned int rows_, const unsigned int columns_, stitch &s) {
	for (unsigned int i = 0 ; i < rows_ ; i++) {
	  add_row(row(columns_));
	}
	for (unsigned int r = 0 ; r < rows_ ; r++) {
	  for (unsigned int c = 0 ; c < columns_ ; c++) {
	    rows[r][c] = s;
	  }
	}

      }
     
      void add_row(const row &r);
      
      std::string simple() const;
      std::string concise() const;

      row &operator[](const unsigned int i);
      bool operator==(const pattern &p) const;
      bool operator!=(const pattern &p) const;
      pattern &operator=(const pattern &p);
      
      friend std::ostream &operator<<(std::ostream &o, const pattern &p);

    };
  }
}
      


#endif // #if !defined __DRG_KNITTING_PATTERN
