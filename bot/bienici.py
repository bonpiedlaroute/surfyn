#!/usr/bin/env python
# -*- coding: utf-8 -*- 
# (c) Copyright 2019 
# author(s): Noel Tchidjo
# All rights reserved

import scrapy
import json
import urllib
import os
import configparser

from hash_id import *
from search_features import *
from url_builder import *
from Serializer import Serializer

search_base_url = "https://www.bienici.com/realEstateAds.json?filters="

base_filter = "{\"size\":24,\"from\":0,\"filterType\":\"buy\",\"propertyType\":[\"flat\"],\"newProperty\":false,\"page\":1,\"resultsPerPage\":24,\"maxAuthorizedResults\":2400,\"sortBy\":\"relevance\",\"sortOrder\":\"desc\",\"onTheMarket\":[true],\"mapMode\":\"enabled\",\"showAllModels\":false,\"zoneIdsByTypes\":{\"zoneIds\":[\"-91738\"]}}"


ad_flat_base_url = 'https://www.bienici.com/annonce/vente/colombes/appartement/'
ad_house_base_url = 'https://www.bienici.com/annonce/vente/colombes/maison/'


config_bienici = configparser.ConfigParser()
config_bienici.read('spiders/config.ini')

IMAGES_FOLDER_NAME=config_bienici['COMMON']['images']
city = config_bienici['COMMON']['city']
region = config_bienici['COMMON']['region']
ip = config_bienici['COMMON']['db_access_ip']
port = int(config_bienici['COMMON']['db_access_port'])
tablename = config_bienici['COMMON']['tablename']

class BieniciSpider(scrapy.Spider):
   
   name = "bienici"

   def __init__(self): 
      if not os.path.exists(IMAGES_FOLDER_NAME):
         os.mkdir(IMAGES_FOLDER_NAME)

      self.mapping_url_ptype = dict()
      self.mapping_url_stype = dict()
      self.announces_cnt = 0
      self.serializer = Serializer(ip, port, tablename)

   def start_requests(self):
      prop_list = [(APART_ID, BUY_ID), (HOUSE_ID, BUY_ID), (APART_ID, RENT_ID), (HOUSE_ID, RENT_ID)]
      filter_object = json.loads(base_filter)
      filter_object['zoneIdsByTypes']['zoneIds'][0] = '-91738'

      for ptype, stype in prop_list:
         prop_id = getBienIciPropertiesId(ptype)
         search_id = getBienIciSearchTypeId(stype)        

         filter_object['propertyType'][0] = prop_id
         filter_object['filterType'] = search_id

         filter_str = json.dumps(filter_object)
         url = search_base_url + filter_str

         self.mapping_url_ptype[url] = ptype
         self.mapping_url_stype[url] = stype
         yield scrapy.Request(url=url, callback= lambda r, nextpage = 2: self.parse(r, nextpage))


   def parse(self, response, nextpage):
      data = json.loads(response.text)
      ad_url = ""
      property_type = 0
      search_type = 0

      
      for ad in data['realEstateAds']:
         if ad['propertyType'] == 'flat':
            ad_url = ad_flat_base_url + ad['id']
            property_type = APART_ID
         else:
            ad_url = ad_house_base_url + ad['id']
            property_type = HOUSE_ID
      

         if ad['adType'] == 'buy':
            search_type = BUY_ID
         else:
            search_type = RENT_ID

         ID = hash_id(ad_url)


         # store images on disk
         images = ad['photos']

         if images:
            announce_image = images[0]['url']

         image_cnt = 1

         for img in images:
            image_name = os.path.join(IMAGES_FOLDER_NAME, str(ID) + '_' + str(image_cnt) + '.jpg')
            urllib.urlretrieve(img['url'], image_name)
            image_cnt += 1


         self.announces_cnt += 1
         announce_title = ""
         if not ad['title']:
            announce_title = "Appartement" if property_type == APART_ID else "Maison"
         else:
            announce_title = ad['title']

         # send data to db
         ret = self.serializer.send(ID, property_type, json.dumps(ad), city, region, ad_url, 'bienici', announce_title, search_type, announce_image, image_cnt-1)
         print (ret)
      if (data['perPage'] + data['from']) < data['total'] :
         # check for next data   
         original_request = str(response.request)
         filter_str = urllib.unquote(original_request[56:-1])
         filter_object = json.loads(filter_str)

         filter_object['size'] =  data['total'] - data['from'] if  data['from'] + 24 > data['total'] else 24
         filter_object['from'] = data['from'] + data['perPage']
         filter_object['page'] = nextpage + 1

         url = search_base_url + json.dumps(filter_object)

         yield scrapy.Request(url=url, callback=lambda r, nextpage=nextpage+1: self.parse(r, nextpage))
     
 
   def closed(self, reason):
      print("Announces found: " + str(self.announces_cnt) + "\n")
      self.serializer.close()




