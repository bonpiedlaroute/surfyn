/**
* TODO: This file is created at base of sf_classifier/Classifier.cpp
* Should refactory with it later on
*/


#include "TransformTable.h"
#include <algorithm>
#include "sf_services/sf_utils/inc/Config.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;


#ifdef _WIN32
using std::shared_ptr;
#else
using boost::shared_ptr;
#endif

using Log = surfyn::utils::Logger;

#define ADD_STRING_FIELD_TO_PUT(fieldName, fieldValue) \
   ValueType fieldName##Value;   \
   fieldName##Value.field = fieldValue;  \
   fieldName##Value.fieldtype = Type::type::STRING;   \
   valuesToPut[fieldName] = fieldName##Value;

#define CHECK_SIMILAR_ANNOUNCE_ATTRIBUTE_AS_INT(attribute, filedName) \
   std::string left##attribute##Str = leftAnnounce.getDescription(filedName); \
   std::string right##attribute##Str = rightAnnounce.getDescription(filedName); \
   if (!left##attribute##Str.empty() && !right##attribute##Str.empty()) \
   { \
      int left##attribute##Nb = atoi(left##attribute##Str.c_str()); \
      int right##attribute##Nb = atoi(right##attribute##Str.c_str()); \
      if (left##attribute##Nb != right##attribute##Nb) \
      { \
         logStream << leftAnnounce.getId() << " ##attribute##[" << left##attribute##Nb << "] and " << rightAnnounce.getId() << " ##attribute##[" \
            << right##attribute##Nb << "] are not similar as their ##attribute## differ"; \
         Log::getInstance()->info(logStream.str()); \
         return false; \
      } \
   }

#define CHECK_SIMILAR_ANNOUNCE_ATTRIBUTE_AS_STRING(attribute, filedName) \
   std::string left##attribute##Str = leftAnnounce.getDescription(filedName); \
   std::string right##attribute##Str = rightAnnounce.getDescription(filedName); \
   if (!left##attribute##Str.empty() && !right##attribute##Str.empty()) \
   { \
      if (left##attribute##Str != right##attribute##Str) \
      { \
         logStream << leftAnnounce.getId() << " ##attribute##[" << left##attribute##Str << "] and " << rightAnnounce.getId() << " ##attribute##[" \
            << right##attribute##Str << "] are not similar as their ##attribute## differ"; \
         Log::getInstance()->info(logStream.str()); \
         return false; \
      } \
   }

namespace surfyn
{
   // Fields copied from sf_classifier
   const std::string ID = "ID";
   const std::string ANNOUNCE_LINK = "ANNOUNCE_LINK";
   const std::string ANNOUNCE_SOURCE = "ANNOUNCE_SOURCE";
   const std::string ANNOUNCE_TITLE = "ANNOUNCE_TITLE";
   const std::string CITY = "CITY";
   const std::string PROPERTY_DESCRIPTION = "PROPERTY_DESCRIPTION";
   const std::string PROPERTY_TYPE = "PROPERTY_TYPE";
   const std::string REGION = "REGION";
   const std::string SEARCH_TYPE = "SEARCH_TYPE";
   const std::string TIMESTAMP = "TIMESTAMP";
   const std::string SIMILAR_ANNOUNCE = "TF_SIMILAR_ANNOUNCE";
   const std::string ANNOUNCE_IMAGE = "ANNOUNCE_IMAGE";


   const char* RealEstatePrice = "PRICE";
   const char* RealEstateSurface = "SURFACE";
   const char* RealEstateConstructionYear = "CONSTRUCTION_YEAR";
   const char* RealEstateTimeToPublicTransport = "TIME_TO_PUBLICTRANSPORT";
   const char* RealEstateBeds = "BEDS";
   const char* RealEstateCity = "CITY";
   const char* RealEstateType = "PROPERTY_TYPE";
   const char* RealEstateRooms = "ROOMS";
   const char* RealEstateTypeOfHeating = "TYPE_OF_HEATING";
   const char* RealEstateCellar = "CELLAR";
   const char* RealEstateFloor = "FLOOR";
   const char* RealEstateParking = "PARKING";
   const char* RealEstateBox = "BOX";
   const char* RealEstateSearchType = "SEARCH_TYPE";
   const char* RealEstateLandSurface = "LAND_SURFACE";
   const char* RealEstateLift = "LIFT";
   const char* RealEstateBalcony = "BALCONY";
   const char* RealEstateKey = "ID";
   const char* RealEstateSimilarAd = "SIMILAR_AD";
   const char* RealEstateLocation = "LOCATION";

   // Fields for table FR_SUMMARY
   const std::string HISTORY = "HISTORY";
   const std::string IMAGE = "IMAGE";
   const std::string IMAGE_COUNT = "IMAGE_COUNT";
   const std::string SOURCES = "SOURCES";
   const std::string LOCATION = "LOCATION";
   const std::string SOURCE_LOGO = "SOURCE_LOGO";
   const std::string TRANSPORT = "TRANSPORT";
   const std::string CELLAR = "CELLAR";
   const std::string DUPLICATES = "DUPLICATES";

   void RemoveElementFromVectorString(std::string& output, std::string toRemove)
   {
      std::vector<std::string> elements;
      boost::split(elements, output, [](char c) { return c == ','; });
      std::set<std::string> tmp;
      for (auto e : elements)
      {
         if (e != toRemove)
         {
            tmp.insert(e);
         }
      }
      output = std::accumulate(std::begin(tmp),
         std::end(tmp),
         std::string{},
         [](const std::string& a, const std::string &b)
      {
         return a.empty() ? b : a + ',' + b;
      });
   }

   ValueType BuildValueType(const std::string& fieldName, const std::string& fieldValue)
   {
      ValueType fieldNameValue;
      if(fieldName == RealEstatePrice || fieldName == RealEstateRooms || fieldName == RealEstateSurface)
      {
         std::string number_value = fieldValue;
         boost::erase_all(number_value, " ");
         fieldNameValue.field = number_value;
         fieldNameValue.fieldtype = Type::type::NUMBER;
      }
      else
      {
         fieldNameValue.field = fieldValue;
         fieldNameValue.fieldtype = Type::type::STRING;
      }

      return fieldNameValue;
   }

   bool IsSimilarAnnounces(const classifier::RealEstateAd& leftAnnounce, const classifier::RealEstateAd& rightAnnounce)
   {
      if( leftAnnounce.getId() == rightAnnounce.getId())
         return false;
      std::stringstream logStream;
      std::string leftPriceStr = leftAnnounce.getDescription(RealEstatePrice);
      std::string rightPriceStr = rightAnnounce.getDescription(RealEstatePrice);
      if (!leftPriceStr.empty() && !rightPriceStr.empty())
      {
         double leftPrice = atof(leftPriceStr.c_str());
         double rightPrice = atof(rightPriceStr.c_str());
         if (abs(leftPrice - rightPrice) / leftPrice > 0.05)
         {
            logStream << leftAnnounce.getId() << " price[" << leftPrice << "] and " << rightAnnounce.getId() << " price[" 
               << rightPrice << "] are not similar as their prices differ";
            Log::getInstance()->info(logStream.str());
            return false;
         }
      }
      std::string leftSurfaceStr = leftAnnounce.getDescription(RealEstateSurface);
      std::string rightSurfaceStr = rightAnnounce.getDescription(RealEstateSurface);
      if (!leftSurfaceStr.empty() && !rightSurfaceStr.empty())
      {
         double leftSurface = atof(leftSurfaceStr.c_str());
         double rightSurface = atof(rightSurfaceStr.c_str());
         if (abs(leftSurface - rightSurface) / leftSurface > 0.05)
         {
            logStream << leftAnnounce.getId() << " surface[" << leftSurface << "] and " << rightAnnounce.getId() << " surface["
               << rightSurface << "] are not similar as their surfaces differ";
            Log::getInstance()->info(logStream.str());
            return false;
         }
      }
      CHECK_SIMILAR_ANNOUNCE_ATTRIBUTE_AS_INT(Room, RealEstateRooms);
      CHECK_SIMILAR_ANNOUNCE_ATTRIBUTE_AS_INT(Bed, RealEstateBeds);
      CHECK_SIMILAR_ANNOUNCE_ATTRIBUTE_AS_INT(Floor, RealEstateFloor);
      CHECK_SIMILAR_ANNOUNCE_ATTRIBUTE_AS_STRING(RealEstateType, RealEstateType); 
      CHECK_SIMILAR_ANNOUNCE_ATTRIBUTE_AS_STRING(RealEstateSearchType, RealEstateSearchType);
      return true;
   }

   DataFormater::DataFormater()
   {
      m_ReaderBySources["seloger"] = [this](const std::string& json, classifier::RealEstateAd& realEstate) { ReadSelogerJSON(json, realEstate);};
      m_ReaderBySources["leboncoin"] = [this](const std::string& json, classifier::RealEstateAd& realEstate) { ReadLeboncoinJSON(json, realEstate);};
      m_ReaderBySources["bienici"] = [this](const std::string& json, classifier::RealEstateAd& realEstate) { ReadBienIciJSON(json, realEstate);};
      m_ReaderBySources["laforet"] = [this](const std::string& json, classifier::RealEstateAd& realEstate) { ReadLaForetJSON(json, realEstate);};
      m_ReaderBySources["orpi"] = [this](const std::string& json, classifier::RealEstateAd& realEstate) { ReadOrpiJSON(json, realEstate);};
      m_ReaderBySources["stephaneplazaimo"] = [this](const std::string& json, classifier::RealEstateAd& realEstate) { ReadStephanePlazaImoJSON(json, realEstate);};
      m_ReaderBySources["foncia"] = [this](const std::string& json, classifier::RealEstateAd& realEstate) { ReadFonciaJSON(json, realEstate);};
      m_ReaderBySources["century21"] = [this](const std::string& json, classifier::RealEstateAd& realEstate) { ReadCentury21JSON(json, realEstate);};
   }
   void DataFormater::ReadSelogerJSON(const std::string& json, classifier::RealEstateAd& realEstate)
   {
      std::locale::global(std::locale(""));

      rapidjson::Document document;
      document.Parse(json.c_str());

      if(document.HasParseError())
      {
         std::stringstream error;
         error << "failed to parse seloger json: error code [";
         error << document.GetParseError();
         error << "] error offset :[";
         error << document.GetErrorOffset();
         error << "]";
         Log::getInstance()->error(error.str());

         return;
      }
      if (document.HasMember("infos_acquereur"))
      {
         const rapidjson::Value& info_acquereur = document["infos_acquereur"];
         if (info_acquereur.HasMember("prix"))
         {
            const rapidjson::Value& prix = info_acquereur["prix"];
            if (prix.HasMember("prix"))
            {
               double price = prix["prix"].GetDouble();
               realEstate.setDescription(RealEstatePrice, std::to_string((int)price));
            }
         }
      }

      if (document.HasMember("categories"))
      {
         const rapidjson::Value& categories = document["categories"];

         for (rapidjson::SizeType i = 0; i < categories.Size(); i++)
         {
            const rapidjson::Value& category = categories[i];
            if (category.HasMember("id") && category.HasMember("criteria"))
            {
               const int id = category["id"].GetInt();
               const rapidjson::Value& criteria = category["criteria"];
               if (1 == id)
               {
                  for (rapidjson::SizeType j = 0; j < criteria.Size(); ++j)
                  {
                     const rapidjson::Value& object = criteria[j];
                     if (object.HasMember("order") && object.HasMember("value"))
                     {
                        const int order = object["order"].GetInt();
                        std::string value = object["value"].GetString();
                        if (order == 2430)
                        {
                           realEstate.setDescription(RealEstateCellar, "1");
                        }
                        else if (order == 2410)
                        {
                           realEstate.setDescription(RealEstateLift, "1");
                        }
                        else if (order == 2450)
                        {
                           auto index = value.find_first_of(' ');
                           if (index != std::string::npos)
                           {
                              std::string balcony = value.substr(0, index);
                              realEstate.setDescription(RealEstateLift, balcony);
                           }
                        }
                     }
                  }
               }
               else if (2 == id)
               {
                  std::string surface="", floor="";
                  int bedroomNb = 0, pieceNb = 0, constructionYear = 0, buildingTotalFloor = 1;
                  for (rapidjson::SizeType j = 0; j < criteria.Size(); j++)
                  {
                     const rapidjson::Value& object = criteria[j];
                     if (object.HasMember("order") && object.HasMember("value"))
                     {
                        const int order = object["order"].GetInt();
                        std::string value = object["value"].GetString();
                        if (2090 == order)
                        {
                           auto it = value.find_last_of(' ');
                           surface = value.substr(10, it - 10);
                           std::replace(surface.begin(), surface.end(), ',', '.');
                        }
                        else if (2092 == order)
                        {
                           sscanf(value.c_str(), "Année de construction %d", &constructionYear);
                        }
                        else if (2094 == order)
                        {
                           sscanf(value.c_str(), "Bâtiment de %d étages", &buildingTotalFloor);
                        }
                        else if (2096 == order)
                        {
                           auto it = value.find_last_of(' ');
                           floor = value.substr(3, it - 3);
                        }
                        else if (2140 == order)
                        {
                           sscanf(value.c_str(), "%d", &pieceNb);
                        }
                        else if (2165 == order)
                        {
                           sscanf(value.c_str(), "%d", &bedroomNb);
                        }
                     }
                  }

                  if(!surface.empty())
                  realEstate.setDescription(RealEstateSurface, surface);

                  if(constructionYear != 0)
                  realEstate.setDescription(RealEstateConstructionYear, std::to_string(constructionYear));

                  if(bedroomNb != 0)
                  realEstate.setDescription(RealEstateBeds, std::to_string(bedroomNb));

                  if(pieceNb != 0)
                  realEstate.setDescription(RealEstateRooms, std::to_string(pieceNb));

                  if(!floor.empty())
                  realEstate.setDescription(RealEstateFloor, floor);

               }
               else if (3 == id)
               {
                  for (rapidjson::SizeType j = 0; j < criteria.Size(); ++j)
                  {
                     const rapidjson::Value& object = criteria[j];
                     if (object.HasMember("order") && object.HasMember("value"))
                     {
                        const int order = object["order"].GetInt();
                        const std::string value = object["value"].GetString();
                        if (order == 2540)
                        {
                           realEstate.setDescription(RealEstateTypeOfHeating, value);
                        }
                     }
                  }
               }
               else if (4 == id)
               {
                  for (rapidjson::SizeType j = 0; j < criteria.Size(); ++j)
                  {
                     const rapidjson::Value& object = criteria[j];
                     if (object.HasMember("order") && object.HasMember("value"))
                     {
                        const int order = object["order"].GetInt();
                        const std::string value = object["value"].GetString();
                        if (order == 2430)
                        {
                           auto index = value.find_first_of(' ');
                           if (index != std::string::npos)
                           {
                              std::string parking = value.substr(0, index);
                              realEstate.setDescription(RealEstateParking, parking);
                           }
                        }
                        else if (order == 2470)
                        {
                           auto index = value.find_first_of(' ');
                           if (index != std::string::npos)
                           {
                              std::string box = value.substr(0, index);
                              realEstate.setDescription(RealEstateBox, box);
                           }
                        }
                        else if (order == 3250)
                        {
                           float landSurface = 0;
                           sscanf(value.c_str(), "Terrain de %f m2", &landSurface);
                           realEstate.setDescription(RealEstateLandSurface, std::to_string(landSurface));
                        }
                     }
                  }
               }
            }
         }

      }
      realEstate.setDescription(SOURCE_LOGO, "data/SL0.svg");
   }

   void DataFormater::ReadLeboncoinJSON(const std::string& json, classifier::RealEstateAd& realEstate)
   {
      std::locale::global(std::locale(""));

      rapidjson::Document document;
      document.Parse(json.c_str());

      if(document.HasParseError())
      {
         std::stringstream error;
         error << "failed to parse leboncoin json: error code [";
         error << document.GetParseError();
         error << "] error offset :[";
         error << document.GetErrorOffset();
         error << "]";
         Log::getInstance()->error(error.str());

         return;
      }

      if (document.HasMember("price"))
      {
         double price = document["price"][0].GetDouble();
         realEstate.setDescription(RealEstatePrice, std::to_string((int)price));
      }
      if (document.HasMember("attributes"))
      {
         const rapidjson::Value& attributes = document["attributes"];

         std::string surface, pieceNb;
         for (rapidjson::SizeType j = 0; j < attributes.Size(); j++)
         {
            const rapidjson::Value& attribute = attributes[j];
            if (attribute.HasMember("key") && attribute.HasMember("value"))
            {
               const std::string key = attribute["key"].GetString();
               const std::string value = attribute["value"].GetString();
               if ("square" == key)
               {
                  surface = value;
                  std::replace(surface.begin(), surface.end(), ',', '.');
               }
               else if ("rooms" == key)
               {
                  pieceNb = value;
               }
            }
         }

         realEstate.setDescription(RealEstateSurface, surface);
         realEstate.setDescription(RealEstateRooms, pieceNb);
      }
      /*if (document.HasMember("images"))
      {
         const rapidjson::Value& images = document["images"];
         if (images.HasMember("nb_images"))
         {
            int imageCount = images["nb_images"].GetInt();
            realEstate.setDescription(IMAGE_COUNT, std::to_string(imageCount));
         }
         if (images.HasMember("urls"))
         {
            std::stringstream ss;
            //bool first = true;
            const rapidjson::Value& imageUrls = images["urls"];
            //for (rapidjson::SizeType j = 0; j < imageUrls.Size(); j++)
            //{
            //   if (!first) ss << ',';
               //ss << "\"" << imageUrls[j].GetString() << "\"";
            ss << imageUrls[0].GetString();

            //}
            realEstate.setDescription(IMAGE, ss.str());
         }
      }*/
      realEstate.setDescription(SOURCE_LOGO, "data/lbc0.svg");
   }


   void DataFormater::ReadLogicImmoJSON(const std::string& json, classifier::RealEstateAd& realEstate)
   {
      std::locale::global(std::locale(""));

      rapidjson::Document document;
      document.Parse(json.c_str());

      if(document.HasParseError())
      {
         std::stringstream error;
         error << "failed to parse logicimmo json: error code [";
         error << document.GetParseError();
         error << "] error offset :[";
         error << document.GetErrorOffset();
         error << "]";
         Log::getInstance()->error(error.str());

         return;
      }

      if (document.HasMember("price"))
      {
         std::string price = document["price"].GetString();
         auto pos = price.find_last_of(' ');
         price = price.substr(0, pos);
         realEstate.setDescription(RealEstatePrice, price);
      }
      if (document.HasMember("surface"))
      {
         std::string surface = document["surface"].GetString();
         realEstate.setDescription(RealEstateSurface, surface);
      }
      if (document.HasMember("nb_room"))
      {
         std::string nb_room = document["nb_room"].GetString();
         realEstate.setDescription(RealEstateRooms, nb_room);
      }
   }

   void DataFormater::ReadBienIciJSON(const std::string& json, classifier::RealEstateAd& realEstate)
   {
      std::locale::global(std::locale(""));

      rapidjson::Document document;
      document.Parse(json.c_str());

      if(document.HasParseError())
      {
         std::stringstream error;
         error << "failed to parse logicimmo json: error code [";
         error << document.GetParseError();
         error << "] error offset :[";
         error << document.GetErrorOffset();
         error << "]";
         Log::getInstance()->error(error.str());

         return;
      }

      if (document.HasMember("price"))
      {
         std::string price = std::to_string(document["price"].GetDouble());
         std::replace(price.begin(), price.end(), ',', '.');
         realEstate.setDescription(RealEstatePrice, price);
      }
      if (document.HasMember("surfaceArea"))
      {
         std::string surface = std::to_string(document["surfaceArea"].GetDouble());
         std::replace(surface.begin(), surface.end(), ',', '.');
         realEstate.setDescription(RealEstateSurface, surface);
      }
      if (document.HasMember("roomsQuantity"))
      {
         std::string nb_room = std::to_string(document["roomsQuantity"].GetUint());

         realEstate.setDescription(RealEstateRooms, nb_room);
      }
      if (document.HasMember("floor"))
      {
         std::string floor;
         auto nb_floor = document["floor"].GetUint();

         if( nb_floor == 0 )
            floor = "rez-de-chaussée";
         else
         {
            if( nb_floor == 1)
            {
               floor = "1er";
            }
            else
            {
               floor = std::to_string(nb_floor) + "ème";
            }
         }

         realEstate.setDescription(RealEstateFloor, floor);
      }
      if (document.HasMember("hasCellar"))
      {
         if(document["hasCellar"].GetBool())
            realEstate.setDescription(RealEstateCellar, "1");
         else
            realEstate.setDescription(RealEstateCellar, "0");
      }
      if (document.HasMember("blurInfo"))
      {
         const auto& blurInfo = document["blurInfo"];
         if(blurInfo.HasMember("position"))
         {
            const auto& position = blurInfo["position"];

            if(position.HasMember("lat") && position.HasMember("lon"))
            {
               std::string location = "lat=";
               location += std::to_string(position["lat"].GetDouble());
               location += ";";
               location += "lon=";
               location += std::to_string(position["lon"].GetDouble());
               realEstate.setDescription(RealEstateLocation, location);
            }
         }
      }
      realEstate.setDescription(SOURCE_LOGO, "data/bienici.png");
   }

void DataFormater::ReadLaForetJSON(const std::string& json, classifier::RealEstateAd& realEstate)
{
   std::locale::global(std::locale(""));
   static std::unordered_map<std::string, std::string> heatingTranslation;
   if(heatingTranslation.empty())
   {
      heatingTranslation["gas"] = "gaz";
      heatingTranslation["electric"] = "electrique";
      heatingTranslation["city_gas"] = "gaz de ville";
   }

   rapidjson::Document document;
   document.Parse(json.c_str());

   if(document.HasParseError())
   {
      std::stringstream error;
      error << "failed to parse laforet json: error code [";
      error << document.GetParseError();
      error << "] error offset :[";
      error << document.GetErrorOffset();
      error << "]";
      Log::getInstance()->error(error.str());

      return;
   }

   if( document.HasMember("rooms"))
   {
      std::string nb_room = std::to_string(document["rooms"].GetUint());

      realEstate.setDescription(RealEstateRooms, nb_room);
   }

   if( document.HasMember("surface"))
   {
      std::string area = std::to_string(document["surface"].GetDouble());
      std::replace(area.begin(), area.end(), ',', '.');
      realEstate.setDescription(RealEstateSurface, area);
   }

   if (document.HasMember("floor") && !document["floor"].IsNull())
   {
      std::string floor;
      auto nb_floor = document["floor"].GetUint();

      if( nb_floor == 0 )
         floor = "rez-de-chaussée";
      else
      {
         if( nb_floor == 1)
         {
            floor = "1er";
         }
         else
         {
            floor = std::to_string(nb_floor) + "ème";
         }
      }

      realEstate.setDescription(RealEstateFloor, floor);
   }

   if (document.HasMember("price"))
   {
      std::string price = std::to_string(document["price"].GetDouble());
      std::replace(price.begin(), price.end(), ',', '.');
      realEstate.setDescription(RealEstatePrice, price);
   }

   if (document.HasMember("has_lift"))
   {

      if( document["has_lift"].GetBool())
         realEstate.setDescription(RealEstateLift, "1");
      else
         realEstate.setDescription(RealEstateLift, "0");
   }

   if(document.HasMember("lat") && document.HasMember("lng"))
   {
      std::string location = "lat=";
      location += std::to_string(document["lat"].GetDouble());
      location += ";";
      location += "lon=";
      location += std::to_string(document["lng"].GetDouble());
      realEstate.setDescription(RealEstateLocation, location);

   }

   if (document.HasMember("heating_nature") && document["heating_nature"].IsString())
   {
      std::string heating = "Chauffage ";
      std::string laforetheating = document["heating_nature"].GetString();
      auto iter = heatingTranslation.find(laforetheating);

      if(iter != heatingTranslation.end())
         heating += iter->second;
      else
         heating += laforetheating;

      realEstate.setDescription(RealEstateTypeOfHeating, heating);
   }

   if (document.HasMember("parkings") && !document["parkings"].IsNull())
   {
      std::string parking = std::to_string(document["parkings"].GetUint());
      realEstate.setDescription(RealEstateParking, parking);
   }

   if(document.HasMember("year_of_construction") && !document["year_of_construction"].IsNull())
   {
      std::string year = std::to_string(document["year_of_construction"].GetUint());
      realEstate.setDescription(RealEstateConstructionYear, year);
   }

   if(document.HasMember("cellars") && !document["cellars"].IsNull() )
   {
      std::string cellar = std::to_string(document["cellars"].GetUint());
      realEstate.setDescription(RealEstateCellar, cellar);
   }

   realEstate.setDescription(SOURCE_LOGO, "data/laforet.jpg");
}

void DataFormater::ReadOrpiJSON(const std::string& json, classifier::RealEstateAd& realEstate)
{
   std::locale::global(std::locale(""));

   rapidjson::Document document;
   document.Parse(json.c_str());

   if(document.HasParseError())
   {
      std::stringstream error;
      error << "failed to parse orpi json: error code [";
      error << document.GetParseError();
      error << "] error offset :[";
      error << document.GetErrorOffset();
      error << "]";
      Log::getInstance()->error(error.str());

      return;
   }
   if (document.HasMember("price"))
   {
      std::string price = std::to_string(document["price"].GetDouble());
      std::replace(price.begin(), price.end(), ',', '.');
      realEstate.setDescription(RealEstatePrice, price);
   }

   if( document.HasMember("surface"))
   {
     std::string area = std::to_string(document["surface"].GetDouble());
     std::replace(area.begin(), area.end(), ',', '.');
     realEstate.setDescription(RealEstateSurface, area);
   }
   if( document.HasMember("nbRooms"))
   {
      std::string nb_room = std::to_string(document["nbRooms"].GetUint());

      realEstate.setDescription(RealEstateRooms, nb_room);
   }
   if( document.HasMember("constructionYear"))
   {
      std::string year = std::to_string(document["constructionYear"].GetUint());

      realEstate.setDescription(RealEstateConstructionYear, year);
   }
   if (document.HasMember("cellar"))
   {
      if(document["cellar"].GetBool())
         realEstate.setDescription(RealEstateCellar, "1");
      else
         realEstate.setDescription(RealEstateCellar, "0");
   }
   if (document.HasMember("nbParkingSpaces"))
   {
      std::string parking = std::to_string(document["nbParkingSpaces"].GetUint());
      realEstate.setDescription(RealEstateParking, parking);
   }
   if (document.HasMember("storyLocation"))
   {
      std::string floor;
      auto nb_floor = document["storyLocation"].GetUint();

      if( nb_floor == 0 )
         floor = "rez-de-chaussée";
      else
      {
         if( nb_floor == 1)
         {
            floor = "1er";
         }
         else
         {
            floor = std::to_string(nb_floor) + "ème";
         }
      }

      realEstate.setDescription(RealEstateFloor, floor);
   }


   if (document.HasMember("elevator"))
   {

      if(document["elevator"].GetBool())
         realEstate.setDescription(RealEstateLift, "1");
      else
         realEstate.setDescription(RealEstateLift, "0");
   }
   if(document.HasMember("latitude") && document.HasMember("longitude"))
   {
      std::string location = "lat=";
      location += document["latitude"].GetString();
      location += ";";
      location += "lon=";
      location += document["longitude"].GetString();
      realEstate.setDescription(RealEstateLocation, location);

   }
   /*if (document.HasMember("heatingNature") && document["heatingNature"].IsString())
   {
      std::string heating = "Chauffage ";
      heating += document["heatingNature"].GetString();

      realEstate.setDescription(RealEstateTypeOfHeating, heating);
   }*/


   realEstate.setDescription(SOURCE_LOGO, "data/orpi.jpg");
}

void DataFormater::ReadStephanePlazaImoJSON(const std::string& json, classifier::RealEstateAd& realEstate)
{
   std::locale::global(std::locale(""));

   rapidjson::Document document;
   document.Parse(json.c_str());

   if(document.HasParseError())
   {
      std::stringstream error;
      error << "failed to parse stephaneplazaimo json: error code [";
      error << document.GetParseError();
      error << "] error offset :[";
      error << document.GetErrorOffset();
      error << "]";
      Log::getInstance()->error(error.str());

      return;
   }
   if (document.HasMember("price"))
   {
      std::string price = document["price"].GetString();

      realEstate.setDescription(RealEstatePrice, price);
   }
   if(document.HasMember("lat") && document.HasMember("lon"))
   {
      std::string location = "lat=";
      location += std::to_string(document["lat"].GetDouble());
      location += ";";
      location += "lon=";
      location += std::to_string(document["lon"].GetDouble());
      realEstate.setDescription(RealEstateLocation, location);
   }

   if(document.HasMember("properties"))
   {
      const auto& properties = document["properties"];
      if( properties.HasMember("anneeConstruction"))
      {
         std::string year = std::to_string(properties["anneeConstruction"].GetInt());
         realEstate.setDescription(RealEstateConstructionYear, year);
      }

      if( properties.HasMember("lift"))
      {
         std::string lift = properties["lift"].GetBool()? "1":"0";
         realEstate.setDescription(RealEstateLift, lift);
      }

      if( properties.HasMember("floor"))
      {
         std::string floor;
         auto nb_floor = properties["floor"].GetUint();

         if( nb_floor == 0 )
            floor = "rez-de-chaussée";
         else
         {
            if( nb_floor == 1)
            {
               floor = "1er";
            }
            else
            {
               floor = std::to_string(nb_floor) + "ème";
            }
         }

         realEstate.setDescription(RealEstateFloor, floor);
      }
      if (properties.HasMember("heating-mode"))
      {
         std::string heating = "Chauffage ";
         heating += properties["heating-mode"].GetString();

         realEstate.setDescription(RealEstateTypeOfHeating, heating);
      }
      if( properties.HasMember("room"))
      {
         std::string nb_room = std::to_string(properties["room"].GetUint());

         realEstate.setDescription(RealEstateRooms, nb_room);
      }
      if( properties.HasMember("surface") )
      {
         std::string value = properties["surface"].GetString();
         auto pos = value.find_first_of(' ');
         if( pos != std::string::npos)
         {
            std::string area = value.substr(0, pos);
            realEstate.setDescription(RealEstateSurface, area);
         }
      }
      if (properties.HasMember("cellar"))
      {
        std::string cellar = std::to_string(properties["cellar"].GetUint());

        realEstate.setDescription(RealEstateCellar, cellar);
      }
      if (properties.HasMember("parking-spot"))
      {
        std::string parking = std::to_string(properties["parking-spot"].GetUint());

        realEstate.setDescription(RealEstateParking, parking);
      }
   }

   realEstate.setDescription(SOURCE_LOGO, "data/stephaneplazaimo.png");
}

void DataFormater::ReadFonciaJSON(const std::string& json, classifier::RealEstateAd& realEstate)
{
   std::locale::global(std::locale(""));

   rapidjson::Document document;
   document.Parse(json.c_str());

   if(document.HasParseError())
   {
      std::stringstream error;
      error << "failed to parse foncia json: error code [";
      error << document.GetParseError();
      error << "] error offset :[";
      error << document.GetErrorOffset();
      error << "]";
      Log::getInstance()->error(error.str());

      return;
   }
   if (document.HasMember(RealEstatePrice))
   {
      realEstate.setDescription(RealEstatePrice, document[RealEstatePrice].GetString());
   }

   if( document.HasMember(RealEstateSurface))
   {
     std::string area = document[RealEstateSurface].GetString();
     auto pos = area.find_first_of(' ');
     if( pos != std::string::npos)
     {
       std::string real_area = area.substr(0, pos);
       realEstate.setDescription(RealEstateSurface, real_area);
     }

   }
   if( document.HasMember(RealEstateRooms))
   {
      realEstate.setDescription(RealEstateRooms, document[RealEstateRooms].GetString());
   }
   if( document.HasMember(RealEstateConstructionYear))
   {
      realEstate.setDescription(RealEstateConstructionYear, document[RealEstateConstructionYear].GetString());
   }
   if (document.HasMember(RealEstateCellar))
   {
      realEstate.setDescription(RealEstateCellar, document[RealEstateCellar].GetString());
   }
   if (document.HasMember(RealEstateParking))
   {
      realEstate.setDescription(RealEstateParking, document[RealEstateParking].GetString());
   }
   if (document.HasMember(RealEstateFloor))
   {
      std::string floor;
      std::string nb_floor = document[RealEstateFloor].GetString();

      if( nb_floor == "RDC" )
         floor = "rez-de-chaussée";
      else
      {
         if( atoi(nb_floor.c_str()) == 1)
         {
            floor = "1er";
         }
         else
         {
            floor = nb_floor + "ème";
         }
      }

      realEstate.setDescription(RealEstateFloor, floor);
   }


   if (document.HasMember(RealEstateLift))
   {
      realEstate.setDescription(RealEstateLift, document[RealEstateLift].GetString());
   }

   if (document.HasMember(RealEstateTypeOfHeating))
   {
      std::string heating = "Chauffage ";
      heating += document[RealEstateTypeOfHeating].GetString();

      realEstate.setDescription(RealEstateTypeOfHeating, heating);
   }

   if (document.HasMember(RealEstateBalcony))
    {
       realEstate.setDescription(RealEstateBalcony, document[RealEstateBalcony].GetString());
    }

   realEstate.setDescription(SOURCE_LOGO, "data/foncia.png");
}

void DataFormater::ReadCentury21JSON(const std::string& json, classifier::RealEstateAd& realEstate)
{
   std::locale::global(std::locale(""));

   rapidjson::Document document;
   document.Parse(json.c_str());

   if(document.HasParseError())
   {
      std::stringstream error;
      error << "failed to parse century21 json: error code [";
      error << document.GetParseError();
      error << "] error offset :[";
      error << document.GetErrorOffset();
      error << "]";
      Log::getInstance()->error(error.str());

      return;
   }
   if (document.HasMember(RealEstatePrice))
   {
      realEstate.setDescription(RealEstatePrice, document[RealEstatePrice].GetString());
   }

   if( document.HasMember(RealEstateSurface))
   {
     std::string area = document[RealEstateSurface].GetString();
     auto pos = area.find_first_of(' ');
     if( pos != std::string::npos)
     {
       std::string real_area = area.substr(0, pos);
       std::replace(real_area.begin(), real_area.end(), ',', '.');
       realEstate.setDescription(RealEstateSurface, real_area);
     }

   }
   if( document.HasMember(RealEstateRooms))
   {
      realEstate.setDescription(RealEstateRooms, document[RealEstateRooms].GetString());
   }
   if( document.HasMember(RealEstateConstructionYear))
   {
      realEstate.setDescription(RealEstateConstructionYear, document[RealEstateConstructionYear].GetString());
   }

   if (document.HasMember(RealEstateLift))
   {
      realEstate.setDescription(RealEstateLift, document[RealEstateLift].GetString());
   }

   if (document.HasMember(RealEstateTypeOfHeating))
   {
      std::string heating = "Chauffage ";
      std::string value = document[RealEstateTypeOfHeating].GetString();
      auto pos = value.find_last_of(' ');

      if( pos !=  std::string::npos)
      {
         auto heating_type = value.substr(pos+1);
         heating += heating_type == "electricite"? "electrique": heating_type;
      }
      else
      {
         heating += value;
      }

      realEstate.setDescription(RealEstateTypeOfHeating, heating);
   }

   if( document.HasMember(RealEstateConstructionYear))
   {
      realEstate.setDescription(RealEstateConstructionYear, document[RealEstateConstructionYear].GetString());
   }

   realEstate.setDescription(SOURCE_LOGO, "data/century21.png");
}


void DataFormater::ReadTableAndFormatEntries(const std::shared_ptr<dynamodb_accessClient>& client, const std::string& tableName)
   {
      std::locale::global(std::locale(""));

      std::map<std::string, ValueType> attributestoget;

      ValueType value;
      value.field = "";
      value.fieldtype = Type::type::NUMBER;
      attributestoget[ID] = value;

      value.fieldtype = Type::type::STRING;

      attributestoget[ANNOUNCE_LINK] = value;
      attributestoget[ANNOUNCE_SOURCE] = value;
      attributestoget[ANNOUNCE_TITLE] = value;
      attributestoget[CITY] = value;
      attributestoget[PROPERTY_DESCRIPTION] = value;
      attributestoget[PROPERTY_TYPE] = value;
      attributestoget[REGION] = value;
      attributestoget[SEARCH_TYPE] = value;
      attributestoget[TIMESTAMP] = value;
      attributestoget[SIMILAR_ANNOUNCE] = value;
      attributestoget[IMAGE_COUNT] = value;
      attributestoget[ANNOUNCE_IMAGE] = value;

      bool scanend = false;
      do
      {
         ScanReqResult scanReturn;
         client->scan(scanReturn, tableName, attributestoget, "", std::map<std::string, ValueType>());

         std::stringstream logstream;
         logstream << "Adapt model: " << scanReturn.values.size() << " elements scan\n";

         Log::getInstance()->info(logstream.str());

         // TODO find a way to scan a part of entries into memories. Now we import all
         /*std::unordered_map<int64_t, std::map<std::string, std::string>> scanValuesByID;
         for (auto scanValue : scanReturn.values)
         {
            int64_t id = atol(scanValue[RealEstateKey].c_str());
            scanValuesByID[id] = scanValue;
         }*/

         for (auto iter = scanReturn.values.begin(); iter != scanReturn.values.end(); ++iter)
         {
            int64_t id = atol((*iter)[RealEstateKey].c_str());

            classifier::RealEstateAd realEstate(id);
            std::string CurrentImageCount = "", CurrentAnnounceImage="";

            /*std::map<std::string, ValueType> valuesToPut;
            ValueType IDValue;
            IDValue.field = std::to_string(id);
            IDValue.fieldtype = Type::type::NUMBER;
            valuesToPut[ID] = IDValue;*/

            std::map<std::string, std::string>::const_iterator it_field;
            if ((it_field = iter->find(ANNOUNCE_LINK)) != iter->end())
            {
               realEstate.setDescription(ANNOUNCE_LINK, it_field->second);
            }
            if ((it_field = iter->find(RealEstateCity)) != iter->end())
            {
               realEstate.setDescription(RealEstateCity, it_field->second);
            }
            if ((it_field = iter->find(RealEstateType)) != iter->end())
            {
               realEstate.setDescription(RealEstateType, it_field->second);
            }
            if ((it_field = iter->find(RealEstateSearchType)) != iter->end())
            {
               realEstate.setDescription(RealEstateSearchType, it_field->second);
            }
            if ((it_field = iter->find(IMAGE_COUNT)) != iter->end())
            {
               CurrentImageCount = it_field->second;

            }
            if ((it_field = iter->find(ANNOUNCE_IMAGE)) != iter->end())
            {
               CurrentAnnounceImage = it_field->second;
            }
            std::string announceSource;
            if ((it_field = iter->find(ANNOUNCE_SOURCE)) != iter->end())
            {
               announceSource = it_field->second;
               realEstate.setDescription(ANNOUNCE_SOURCE, announceSource);
            }
            if ((it_field = iter->find(PROPERTY_DESCRIPTION)) != iter->end())
            {
               std::string json = it_field->second;
               if (!announceSource.empty())
               {
                  auto it_reader = m_ReaderBySources.find(announceSource);
                  if( it_reader != m_ReaderBySources.end())
                  {
                     it_reader->second(json, realEstate);
                  }
                  realEstate.setDescription(IMAGE_COUNT, CurrentImageCount);
                  realEstate.setDescription(IMAGE, CurrentAnnounceImage);
               }
               else
               {
                  std::stringstream errorstream;
                  errorstream << "Announce id [" << id << "] has no source !";

                  Log::getInstance()->error(errorstream.str());
               }
               
            }

            //TODO to add more fields
            /*if ((it_field = iter->find(RealEstateTimeToPublicTransport)) != iter->end())
            {
               ADD_STRING_FIELD_TO_PUT(RealEstateTimeToPublicTransport, it_field->second);
            }*/
            if ((it_field = iter->find(TIMESTAMP)) != iter->end())
            {
               realEstate.setDescription(TIMESTAMP, it_field->second);
            }
            if ((it_field = iter->find(SIMILAR_ANNOUNCE)) != iter->end())
            {
               //std::string similarAnnouces = it_field->second;
               realEstate.setDescription(SIMILAR_ANNOUNCE, it_field->second);
               //ADD_STRING_FIELD_TO_PUT(DUPLICATES, similarAnnouces);

               /*std::vector<std::string> annoucesIDs;
               boost::split(annoucesIDs, similarAnnouces, [](char c) { return c == ','; });
               std::set<std::string> sources;
               for (std::string similarIDStr : annoucesIDs)
               {
                  int64_t otherID = atol(similarIDStr.c_str());
                  std::map<std::string, std::string> otherAnnounceValues = scanValuesByID[otherID];
                  auto it_other = otherAnnounceValues.find(ANNOUNCE_SOURCE);
                  if (it_other != otherAnnounceValues.end())
                  {
                     sources.insert(it_other->second);
                  }

                  
               }
               if (!sources.empty())
               {
                  std::string annouceSources = std::accumulate(std::begin(sources),
                     std::end(sources),
                     std::string{},
                     [](const std::string& a, const std::string &b)
                        {
                        return a.empty() ? b : a + ',' + b;
                        });
                  ADD_STRING_FIELD_TO_PUT(SOURCES, annouceSources);
               }*/
            }


            //ADD_STRING_FIELD_TO_PUT(SOURCE_LOGO, "data/SL0.svg");

            /*OperationResult result;
            client->put(result, destTable, valuesToPut);
            if (!result.success)
            {
               Log::getInstance()->error("Failed to put " + std::to_string(id) + " into table " + destTable + " error : " + result.error);
            }*/
            m_AnnouncesByID[id] = realEstate;
         }
         scanend = scanReturn.scanend;
      } while (!scanend);


      Log::getInstance()->info("Read table contents finished");
   }

   void DataFormater::CheckSimilarAnnounces()
   {
      for (auto it = m_AnnouncesByID.begin(); it != m_AnnouncesByID.end(); ++it)
      {
         classifier::RealEstateAd& realEstate = it->second;
         const std::string& similarAnnouces = realEstate.getDescription(SIMILAR_ANNOUNCE);
         if (!similarAnnouces.empty())
         {
            std::vector<std::string> annoucesIDs;
            boost::split(annoucesIDs, similarAnnouces, [](char c) { return c == ','; });
            std::vector<std::string> sources;
            std::vector<std::string> checkedSimilarIDs;
            sources.push_back(realEstate.getDescription(ANNOUNCE_SOURCE));
            for (std::string similarIDStr : annoucesIDs)
            {
               int64_t otherID = atol(similarIDStr.c_str());
               classifier::RealEstateAd& otherRealEstate = m_AnnouncesByID[otherID];

               if (IsSimilarAnnounces(realEstate, otherRealEstate))
               {
                  std::string otherAnnounceSource = otherRealEstate.getDescription(ANNOUNCE_SOURCE);
                  if (!otherAnnounceSource.empty())
                  {
                     sources.push_back(otherAnnounceSource);
                  }
                  checkedSimilarIDs.push_back(similarIDStr);
               }
               else
               {
                  std::string otherSimilarAnnounces = otherRealEstate.getDescription(SIMILAR_ANNOUNCE);
                  RemoveElementFromVectorString(otherSimilarAnnounces, std::to_string(realEstate.getId()));
                  otherRealEstate.setDescription(SIMILAR_ANNOUNCE, otherSimilarAnnounces);
               }
            }
            if (!checkedSimilarIDs.empty())
            {
               std::string duplicates = std::accumulate(std::begin(checkedSimilarIDs),
                  std::end(checkedSimilarIDs),
                  std::string{},
                  [](const std::string& a, const std::string &b)
               {
                  return a.empty() ? b : a + ',' + b;
               });
               realEstate.setDescription(DUPLICATES, duplicates);
            }
            if (!sources.empty())
            {
               std::string annouceSources = std::accumulate(std::begin(sources),
                  std::end(sources),
                  std::string{},
                  [](const std::string& a, const std::string &b)
                     {
                     return a.empty() ? b : a + ',' + b;
                     });
               realEstate.setDescription(SOURCES, annouceSources);
            }
         }
         else
         {
            realEstate.setDescription(SOURCES, realEstate.getDescription(ANNOUNCE_SOURCE));
         }
      } // end of for
   } // end of CheckSimilarAnnounces

   void DataFormater::PutTargetTable(const std::shared_ptr<dynamodb_accessClient>& client, const std::string& tableName)
   {
      for (auto it = m_AnnouncesByID.begin(); it != m_AnnouncesByID.end(); ++it)
      {
         std::map<std::string, ValueType> valuesToPut;
         int64_t id = it->first;
         ValueType IDValue;
         IDValue.field = std::to_string(id);
         IDValue.fieldtype = Type::type::NUMBER;
         valuesToPut[ID] = IDValue;

         const auto& descriptions = it->second.GetAllDescriptions();
         for (auto iter = descriptions.begin(); iter != descriptions.end(); ++iter)
         {
            const std::string& fieldName = iter->first;
            const std::string& fieldValue = iter->second;
            if (!fieldValue.empty())
            {
               ValueType value = BuildValueType(fieldName, iter->second);
               valuesToPut[fieldName] = value;
            }
         }
         if (valuesToPut.empty())
         {
            Log::getInstance()->error("ValuesToPut is empty for item " + std::to_string(id));
         }

         OperationResult result;
         client->put(result, tableName, valuesToPut);
         if (!result.success)
         {
            Log::getInstance()->error("Failed to put " + std::to_string(id) + " into table " + tableName + " error : " + result.error);
         }
         // TODO manage bandwith limit
         // work-around
         std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }
   }

}

int main(int argc, char* argv[])
{
   Log::Init("adapt_model");
   Log::getInstance()->info("Starting adapt model ...");

   std::string input_tablename = "", output_tablename = "";
   std::string host = "";
   int port = 0;
   if(argc == 2)
   {
      surfyn::utils::Config conf(argv[1]);
      conf.loadconfig();
      input_tablename = conf.getStringValue("input_tablename");
      output_tablename = conf.getStringValue("output_tablename");
      host = conf.getStringValue("host");
      port = conf.getIntValue("port");
   }
   else
   {
      Log::getInstance()->error("No config file set! you need to set the host/port/input_tablename/target_tablename in the config file");
      return 1;
   }

   shared_ptr<TTransport> socket(new TSocket(host, port));
   shared_ptr<TTransport> transport(new TBufferedTransport(socket));
   shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
   auto client = std::make_shared<dynamodb_accessClient>(protocol);

   transport->open();

   surfyn::DataFormater dataFormater;
   dataFormater.ReadTableAndFormatEntries(client, input_tablename);
   dataFormater.CheckSimilarAnnounces();
   dataFormater.PutTargetTable(client, output_tablename);

   return 0;
}
