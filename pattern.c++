/// File: pattern.c++
/// Author: Gregory Rickeard
/// Data: 26/02/2011
///
/// Implementation of knitting pattern library.



#include "pattern.h++"
#include <iomanip>
#include <sstream>

namespace drg {
  namespace knitting {
    
    ////////////////////////////////////////////////////////////////////////////////
    //////////////////// stitch
    ////////////////////////////////////////////////////////////////////////////////

    const std::string &stitch::get_name() {
      return name;
    }
    const std::string &stitch::get_abbrv() {
      return abbrv;
    }




    bool stitch::operator==(const stitch &s) const {
      return name == s.name && abbrv == s.abbrv;
    }
    bool stitch::operator!=(const stitch &s) const {
      return name != s.name || abbrv != s.abbrv;
    }
    stitch &stitch::operator=(const stitch &s) {
      name = s.name;
      abbrv = s.abbrv;
      return *this;
    }

    std::ostream &operator<<(std::ostream &o, const stitch &s) {
      o << s.abbrv;
      return o;
    }
    

    ////////////////////////////////////////////////////////////////////////////////
    //////////////////// row
    ////////////////////////////////////////////////////////////////////////////////

    stitch &row::operator[](unsigned int i) throw(std::out_of_range) {
      if (i > length) {
	throw std::out_of_range("Index i out of range");
      } else {
	return s[i];
      }
    }
    std::string row::simple() const {
      std::stringstream r;
      for (unsigned int i = 0 ; i < length ; i++) {
	r << s[i].get_abbrv();
      }
      return r.str();
    }
    std::string row::concise() const {
      std::stringstream r;
      if (length == 0) {
	return r.str();
      } else {
	stitch last = s[0];
	unsigned int count = 1;
	r << s[0].get_abbrv();
	for (unsigned int i = 1 ; i < length ; i++) {
	  if (s[i] != last) {
	    r << "(" << count << "), "<< s[i].get_abbrv();
	    count = 1;
	    last = s[i];
	  } else {
	    count++;
	  }
	}
	r << "(" << count << ")";
      }
      return r.str();
    }
    

    bool row::operator==(const row& r) const {
      bool result = true;
      for (unsigned int i = 0 ; i < length ; i++) {
	if (s[i] != r.s[i]) {
	  result = false;
	  break;
	}
      }
      return result;
    }
    bool row::operator!=(const row& r) const {
      return !(operator==(r));
    }

    row &row::operator=(const row &r) {
      for (unsigned int i = 0 ; i < length ; i++) {
	s[i] = r.s[i];
      }
      return *this;
    }


    std::ostream &operator<<(std::ostream & o, const row &r) {
      o << r.simple();
      return o;
    }

    void pattern::add_row(const row &r) {
      rows.push_back(r);
      return;
    }
   
    ////////////////////////////////////////////////////////////////////////////////
    //////////////////// pattern
    ////////////////////////////////////////////////////////////////////////////////



    std::string pattern::simple() const {
      std::stringstream p;
      //for (std::vector<row>::iterator i = rows.begin() ; i < rows.end() ; i++) {
      for (unsigned int i = 0 ; i < rows.size() ; i++) {
	p << rows[i] << std::endl;
      }
      return p.str();
    }
    
    std::string pattern::concise() const {
      std::stringstream p;
      unsigned int row = 1;
      //for (std::vector<row>::iterator i = rows.begin() ; i < rows.end() ; i++) {
      for (int i = rows.size() - 1 ; i >= 0 ; i--) {
	p << std::setw(5) << row++ << ": " << rows[i].concise() << std::endl;

      }
      return p.str();
    }
    
    row &pattern::operator[](const unsigned int i) {
      try {
	return rows[i];
      } catch (std::exception &e) {
	throw;
      }
    }
    bool pattern::operator==(const pattern &p) const {
      bool result = true;
      if (rows.size() != p.rows.size()) {
	result = false;
      } else {	
	for (unsigned int i = 0 ; i < rows.size() ; i++) {
	  if (rows[i] != p.rows[i]) {
	    result = false;
	  }
	}
      }
      return result;
    }
    bool pattern::operator!=(const pattern &p) const {
      return !operator==(p);
    }

    pattern &pattern::operator=(const pattern &p) {
      rows = p.rows;
      return *this;
    }
    
    std::ostream &operator<<(std::ostream &o, const pattern &p) {
      unsigned int r = p.rows.size();
      // Following doesn't work easily with const patterns!
      // for (std::vector<row>::iterator i = p.rows.rbegin() ; i < p.rows.rend() ; i++) {
      for (unsigned int i = 0 ; i < p.rows.size() ; i++) {
	o << std::setw(5) << r << ": " << p.rows[i] << std::endl;
	r--;
      }
      return o;
    }
  }
}



