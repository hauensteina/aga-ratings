#ifndef HELPERS_H
#define HELPERS_H

#include <csignal>
#include <fstream>
#include <vector>
#include <map>

// gdb will break on this
#define BP raise(SIGINT)
// Size of whatever, as a signed int
#define SZ(x) int(x.size())
// Loop across array or some such
#define ISLOOP(x) for (int i=0; i < SZ(x); i++ )
// Loop for n
#define ILOOP(n) for (int i=0; i < (n); i++ )

// trim from start (in place)
//--------------------------------------------
static inline void ltrim(std::string &s)
{
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
      }));
} // ltrim()

// trim from end (in place)
//---------------------------------------
static inline void rtrim(std::string &s)
{
  s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
      }).base(), s.end());
} // rtrim()

// trim from both ends (in place)
//-----------------------------------------
static inline void trim(std::string &s)
{
  ltrim(s);
  rtrim(s);
} // trim()

//----------------------------------------------------------------------------
static inline void tokenize( string &str, char delim, vector<string> &out)
{
  size_t start;
  size_t end = 0;

  while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
      end = str.find( delim, start);
      auto token = str.substr(start, end - start);
      trim( token);
      out.push_back( token);
    } // while
} // tokenize()

// Read csv into array of dicts
//-------------------------------------------------------------------------
static inline vector<map<string,string>> read_csv( string fname, string &error)
{
  error = "";
  fstream inf;
  vector<map<string,string>> res;
  inf.open( fname, ios::in);
  if (!inf.is_open()) {
    error =  "read_csv(): Could not read file ";
    return( res);
  }
  string line;
  vector<string> header;
  while( getline( inf, line)) {
    trim( line);
    if (!line.length()) { continue; }
    if (line.at(0) == '#') { continue; }

    if (!header.size()) { // Parse the header
      tokenize( line, ',', header);
      continue;
    }
    vector<string> token_arr;
    map<string,string> token_dict;
    tokenize( line, ',', token_arr);
    ISLOOP( header) {
      if (i >= SZ(token_arr)) break;
      token_dict.insert( pair<string,string>( header.at(i), token_arr.at(i)));
    }
    res.push_back( token_dict);
  }
  inf.close();
  return( res);
} // read_csv()

#endif
