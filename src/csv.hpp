#ifndef CSV_H
#define CSV_H

#include <string>
#include <vector>

class csvRecord 
{
   public:
      csvRecord(const std::string& str) : record(str) {}
      int countFields();
      std::string getField(int);
      std::vector<std::string> getFields();
   private:
      std::string record;
};

#endif
