#include <cerrno>
#include <iostream>
#include <map>
#include "protocol.hpp"

#ifndef _DB_CLIENT_H
#define _DB_CLIENT_H

namespace grone
{
  class time;
  class serializer;
  
  class client 
  {
  public:
    client();
    ~client();
    std::map<std::string,const char> reqMap_;  
  };
}

#endif