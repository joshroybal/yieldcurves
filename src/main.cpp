#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include "csv.hpp"

void printHTML();
void printHTML(std::vector<std::string>&);
std::string makeJSArr(std::vector<std::string>&);

int main()
{
   const int RECSIZ = 256;
   const std::string headers[] = { "date", "1mo", "2mo", "3mo", "6mo", "1yr", 
      "2yr", "3yr", "5yr", "7yr", "10yr", "20yr", "30yr" };
   char buf[RECSIZ];
   
   std::cout << "Content-Type:text/html;charset=utf-8\n\n";
   std::cin.read(buf, RECSIZ);

   // binary search
   std::string target(buf+5);
   std::ifstream ifstr("yields.dat", std::ifstream::binary | std::ifstream::in);
   ifstr.seekg(ifstr.beg, ifstr.end);
   int filesize = ifstr.tellg();
   ifstr.seekg(ifstr.beg);
   int norecs = filesize / RECSIZ;
   int hi = norecs - 1;
   int lo = 0;
   int mid = hi / 2;
   while ( lo <= hi ) {
      ifstr.seekg(mid * RECSIZ);
      ifstr.read(buf, RECSIZ);
      std::string recstr(buf);
      csvRecord record(recstr);
      std::string date_field( record.getField(1) );
      if ( date_field < target ) {
         lo = mid + 1;
      }
      else if ( date_field > target ) {
         hi = mid - 1;
      }
      else {   // target found - print results and return success
         ifstr.close();
         std::vector<std::string> fields = record.getFields();
         printHTML(fields);
         return 0;
      }
      mid = (lo + hi) / 2;
   }
   ifstr.close();
   printHTML();
   return 0;
}

void printHTML(std::vector<std::string>& fields)
{
   const std::string headers[] = { "date", "1mo", "2mo", "3mo", "6mo", "1yr", 
      "2yr", "3yr", "5yr", "7yr", "10yr", "20yr", "30yr" };
   const int n = fields.size();

   std::cout << "<!DOCTYPE html>\n";
   std::cout << "<html>\n";
   std::cout << "<head>\n";
   std::cout << "<meta charset='utf-8'>\n";
   std::cout << "<title>U. S. Treasury Yields</title>\n";
   std::cout << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
   std::cout << "<link id='stylesheet' media='all'>\n";
   std::cout << "<script src='/yield_search.js' defer></script>\n";
   // std::cout << "<script src='/yield_curve.js' defer></script>\n";
   std::cout << "</head>\n";
   std::cout << "<body>\n";
   std::cout << "<header><p>U. S. Treasury Yields</p></header>\n";
   std::cout << "<div><a href='/index.php'>Home</a> | <a href='/yield_search.html'>Back</a></div>\n";
   std::cout << "<br>\n";
   std::cout << "<form action='yield_search.cgi' method='POST' accept-charset='utf-8'>\n";
   std::cout << "date : \n";
   std::cout << "<input type='text' name='date' value='" << fields[0] << "' size='12'>\n";
   std::cout << "<input type='submit' value='search'>\n";
   std::cout << "</form>\n";
   std::cout << "<br>\n";
   std::cout << "<table id='yieldTable'>\n";
   std::cout << "<tr>";
   for (int i = 0; i < n; i++) {
      if ( fields[i] != "" ) {
         std::cout << "<th>" << headers[i] << "</th>";
      }
   }
   std::cout << "<tr>\n";
   std::cout << "<td>" << fields[0] << "</td>";
   std::cout << std::fixed << std::setprecision(2);
   for (int i = 1; i < n; i++) {
      if ( fields[i] != "" ) {
         std::istringstream isstr(fields[i]);
         float yield;
         isstr >> yield;
         std::cout << "<td>" << yield << "</td>";
      }
   }
   std::cout << "</tr>\n";
   std::cout << "</table>\n";
   std::cout << "<canvas id='testCanvas' width='550' height='450'></canvas>\n";
   std::string JSArr = makeJSArr(fields);
   std::cout<< "<script>\n";
   std::cout << JSArr << '\n';
   std::cout << "</script>\n";
   std::cout << "<script src='/yield_curve.js'></script>\n";
   std::cout << "<br>\n";
   std::cout << "<div><a href='/index.php'>Home</a> | <a href='/yield_search.html'>Back</a></div>\n";
   std::cout << "<footer><p>Copyright &#xa9; Josh Roybal 2019, all rights reserved.</p></footer>\n";
   std::cout << "</body>\n";
   std::cout << "</html>\n";
}

void printHTML()
{
   std::cout << "<!DOCTYPE html>\n";
   std::cout << "<html>\n";
   std::cout << "<head>\n";
   std::cout << "<meta charset='utf-8'>\n";
   std::cout << "<title>U. S. Treasury Yields</title>\n";
   std::cout << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
   std::cout << "<link id='stylesheet' media='all'>\n";
   std::cout << "<script src='/yield_search.js' defer></script>\n";
   std::cout << "</head>\n";
   std::cout << "<body>\n";
   std::cout << "<header><p>U. S. Treasury Yields</p></header>\n";
   std::cout << "<div><a href='/index.php'>Home</a> | <a href='/yield_search.html'>Back</a></div>\n";
   std::cout << "<br>\n";
   std::cout << "<form action='yield_search.cgi' method='POST' accept-charset='utf-8'>\n";
   std::cout << "date : \n";
   std::cout << "<input type='text' name='date' value='1990-01-02' size='12'>\n";
   std::cout << "<input type='submit' value='search'>\n";
   std::cout << "</form>\n";
   std::cout << "<p>search target not found</p>\n";
   std::cout << "<br>\n";
   std::cout << "<div><a href='/index.php'>Home</a> | <a href='/yield_search.html'>Back</a></div>\n";
   std::cout << "<footer><p>Copyright &#xa9; Josh Roybal 2019, all rights reserved.</p></footer>\n";
   std::cout << "</body>\n";
   std::cout << "</html>\n";
}

// lame work-around - that's why I'm an unemployable 'MacGyver' programmer!
std::string makeJSArr(std::vector<std::string>& fields)
{
   std::string JSarr("var testValues = [ ");
   for (int i = 1; i < fields.size(); i++) {
      if ( fields[i] != "" ) {
         JSarr += ' ' + fields[i] + ',';
      }
   }
   JSarr += " ];";
   return JSarr;
}
