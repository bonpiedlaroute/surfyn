/*
   (c) copyright 2018
   All rights reserved

   author(s): Noel Tchidjo
*/
#include "DBaccess.h"


#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include "sf_services/sf_utils/inc/Str.h"
#include "sf_services/sf_utils/inc/Logger.h"


using Log = surfyn::utils::Logger;

const int port = 5050;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

#ifdef _WIN32
using std::shared_ptr;
#else
using boost::shared_ptr;
#endif

namespace surfyn
{
namespace rest_server
{
const std::string id_field = "ID";
const std::string id_city = "CITY";
const std::string id_property_type = "PROPERTY_TYPE";
const std::string id_surface = "SURFACE";
const std::string id_nbrooms = "NB_ROOMS";
const std::string id_history = "HISTORY";
const std::string id_price = "PRICE";
const std::string id_image = "IMAGE";
const std::string id_source = "SOURCES";
const std::string id_announcelink = "ANNOUNCE_LINK";
const std::string id_imagecount = "IMAGE_COUNT";
const std::string id_transport = "TRANSPORT";
const std::string id_location = "LOCATION";
const std::string id_sourcelogo = "SOURCE_LOGO";
const std::string id_floor = "FLOOR";
const std::string id_cellar = "CELLAR";

const std::string details_table = "FR_DETAILS_TEST";

   DBaccess::DBaccess()
   {
      shared_ptr<TTransport> socket(new TSocket("localhost", port));
      shared_ptr<TTransport> transport(new TBufferedTransport(socket));
      shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
      m_client = std::make_shared<dynamodb_accessClient>(protocol);

      transport->open();
   }
   void DBaccess::fetchSummary(utility::stringstream_t& sstream, const std::map<utility::string_t,  utility::string_t>& query )
   {
      std::map<std::string, ValueType> attributestoget;

      ValueType value;
      value.field = "";
      value.fieldtype = Type::type::NUMBER;
      attributestoget[id_field] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_city] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_property_type] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_surface] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_nbrooms] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_history] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_price] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_image] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_source] = value;


      bool scanend = false;

      sstream << U("[\n");
      // search anounces on summary table
      // and construct a json string
      do
      {
         ScanReqResult scanReturn;
         ///TODO enter the filter in the last parameter depending on the user query
         m_client->scan(scanReturn, "FR_SUMMARY_TEST", attributestoget, "");

         time_t current_time = time(nullptr);

         std::stringstream logstream;
         logstream << "fetchSummary: " << scanReturn.values.size() << " elements scan\n";

         Log::getInstance()->info(logstream.str());




         for(auto table_entry_iter = scanReturn.values.begin(); table_entry_iter != scanReturn.values.end();++table_entry_iter)
         {
            if(table_entry_iter != scanReturn.values.begin())
            {
               sstream << U(",\n");
            }
            sstream << U("{\n");
            for(auto attribute_iter = table_entry_iter->begin(); attribute_iter != table_entry_iter->end(); ++attribute_iter)
            {

               if(attribute_iter != table_entry_iter->begin() )
               {
                  sstream << ",\n";
               }

               if(attribute_iter->first !=  "SOURCES")
               {
                  sstream << "\"";
                  sstream << attribute_iter->first;
                  sstream << "\":\"";
                  sstream << attribute_iter->second;
                  sstream << "\"";
               }
               else
               {
                  sstream <<  U("\"SOURCES\": [\n");
                  std::vector<std::string> sources;
                  surfyn::utils::split(attribute_iter->second, ",", sources);
                  for(auto item_iter = sources.begin(); item_iter != sources.end(); ++item_iter)
                  {
                     if(item_iter != sources.begin())
                     {
                        sstream << U(",\n");
                     }
                     sstream << U("\"");
                     sstream << U(*item_iter);
                     sstream << U("\"");
                  }
                  sstream << U("]");
               }

            }
            sstream << U("\n}");
         }
         scanend = scanReturn.scanend;
      }while(!scanend);
      sstream << U("\n]\n");

   }
   void DBaccess::fetchDetails(utility::stringstream_t& sstream, const std::map<utility::string_t,  utility::string_t>& query )
   {
      auto iter_id = query.find("id");
      if( iter_id == query.end())
      {
         Log::getInstance()->error("fetchDetails : no id found");
         return;
      }
      std::map<std::string, ValueType> attributestoget;

      ValueType value;
      value.field = "";
      value.fieldtype = Type::type::NUMBER;
      attributestoget[id_field] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_announcelink] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_imagecount] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_surface] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_nbrooms] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_transport] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_location] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_image] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_sourcelogo] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_floor] = value;

      value.fieldtype = Type::type::STRING;
      attributestoget[id_cellar] = value;

      GetResult _return;
      KeyValue key;
      key.key = "ID";
      key.value.fieldtype = Type::type::NUMBER;
      key.value.field  = iter_id->second;

      m_client->get(_return, details_table,key , attributestoget);


      std::map<std::string, std::string>::iterator iter_duplicate_ad = _return.values.end();
      sstream << U("[\n");
      sstream << U("{\n");
      for(auto iter_item = _return.values.begin(); iter_item != _return.values.end(); ++iter_item)
      {
         if(iter_item->first != "DUPLICATES")
         {
            if( iter_item != _return.values.begin())
            {
               sstream << U(",\n");
            }
            sstream << "\"";
            sstream << U(iter_item->first.c_str());
            sstream << "\":\"";
            sstream << U(iter_item->second.c_str());
            sstream << "\"";
         }
         else
         {
            iter_duplicate_ad = iter_item;
         }

      }
      sstream << U("}");

      if( iter_duplicate_ad != _return.values.end())
      {
         std::vector<std::string> id_duplicates;
         surfyn::utils::split(iter_duplicate_ad->second, ",", id_duplicates);

         for(auto item : id_duplicates)
         {
            key.value.field = item;
            m_client->get(_return, details_table,key , attributestoget);

            sstream << U(",\n{\n");
            for(auto iter_item = _return.values.begin(); iter_item != _return.values.end(); ++iter_item)
            {
               if(iter_item->first != "DUPLICATES")
               {
                  if( iter_item != _return.values.begin())
                  {
                     sstream << U(",\n");
                  }
                  sstream << "\"";
                  sstream << U(iter_item->first.c_str());
                  sstream << "\":\"";
                  sstream << U(iter_item->second.c_str());
                  sstream << "\"";
               }

            }
            sstream << U("\n}");
         }

      }
      sstream << U("\n]\n");

   }
}
}
