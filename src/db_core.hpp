#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <functional>
#include "protocol.hpp"

#ifndef _DB_CORE_H
#define _DB_CORE_H

/* 
 * grone used to store time series as blobs nearly equal size
 * time series defined as pod data with id
 * 
 * each blob name holds index and time bounds of data
 * local cache keeps "rt" data of most recent time series,
 * partially dumping outdated branch as a new blob.
 * 
 * -------------------------------------------------------------------------
 * |       | id1 | len | data | id2 | len | data |       | id | len | data |
 * | time1 |------------------|------------------| time2 |-----------------|
 * |       |                block1               |       |      block2     |
 * |------------------------------------------------------------------------
 * |                                blob0001                               |
 * -------------------------------------------------------------------------
 *  
 * 
 * - cache is a key-value in-memory storage, 
 *   with time as keys and block as values 
 * 
 * - id is user-generated metric linked to data  
 * - len is data length in bytes
 * 
 * 
 * const char id1 = "device1";
 * int  a     = 5;
 * int  b     = 2324;
 * char c     = 'a';
 * double f   = 3.1415926535;
 * unsigned u = 0xff;
 * 
 * - serialize
 * - generate/read time 
 * - call cacheIt() to submit data to core 
 *
 * 
 */



namespace grone
{
  class time;
  class serializer;
  class device_factory;
  
  class core 
  {
  public:
    core();
    ~core();
    void fetch_device_data(const std::string& device_id);
    void cacheIt();
    void uncacheIt();
    void bm_walk();
    void dm_walk();
    device_factory* factory_;  

    /*************** public api ***************/
    void init();
    std::map<const char, std::function<void(grone::request&, grone::request&)> > dispatchMap_;    
    
    /* get some data now... */
    void get(grone::request& req, grone::request& resp);
    
    /* list registered devices */
    void device_list(grone::request& req, grone::request& resp);
    
  private:
    static bool instance_;
    /* bare map, holds chunks of memory detached from serializer */
    static std::map<time,std::pair<unsigned char*,int> > bmap_;
    /* device map, holds pointers to device data */ 
    static std::map<std::string,std::vector<std::pair<unsigned char*,time> > > dmap_;
  };
}





#endif


