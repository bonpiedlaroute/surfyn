#!/usr/bin/env python
# -*- coding: utf-8 -*- 
# (c) Copyright 2017-2018 
# author(s): Noel Tchidjo
# All rights reserved

import scrapy
import json
import urllib
import os

from hash_id import *
from search_features import *
from url_builder import *
from Serializer import *

IMAGES_FOLDER_NAME='images'


class SelogerSpider(scrapy.Spider):
   
   name = "seloger"

   def __init__(self):
      if not os.path.exists(IMAGES_FOLDER_NAME):
         os.mkdir(IMAGES_FOLDER_NAME)

      self.mapping_url_ptype = dict()
      self.mapping_url_stype = dict()
      self.announces_cnt = 0
      self.announce_title = dict()

      self.serializer = Serializer('localhost', 5050)

   def start_requests(self):
      prop_list = [(APART_ID, BUY_ID), (HOUSE_ID, BUY_ID), (APART_ID, RENT_ID), (HOUSE_ID, RENT_ID)]
            
      for ptype, stype in prop_list:
         announcers_id = getSeLogerPropertiesId(ptype)
         search_id = getSeLogerSearchTypeId(stype)        

         url = buildselogerurl(announcers_id, search_id)
         self.mapping_url_ptype[url] = ptype
         self.mapping_url_stype[url] = stype
         yield scrapy.Request(url=url, callback=self.parse)

   def parse(self, response):
      original_request = str(response.request)
      all_links = announces = response.xpath('//section[@class="liste_resultat"]').xpath('.//a[contains(@href, "annonces")]/@href').extract()
      links = set(all_links)
      id_prop = 0
      id_search = 0
      for url in links:
         id_prop = self.mapping_url_ptype[urllib.unquote(original_request[5:-1])]
         id_search = self.mapping_url_stype[urllib.unquote(original_request[5:-1])] 

         yield scrapy.Request(url, callback= lambda r, url = url, id_prop = id_prop, id_search = id_search :self.parse_announce_title(r, url, id_prop, id_search)) 

      following_link = response.xpath('//a[@title="Page suivante"]/@href').extract()

      if following_link:
         new_link = following_link[0]
         self.mapping_url_ptype['https:'+new_link] = self.mapping_url_ptype[urllib.unquote(original_request[5:-1])]
         self.mapping_url_stype['https:'+new_link] = self.mapping_url_stype[urllib.unquote(original_request[5:-1])]

         yield response.follow(new_link, self.parse)

   def parse_prop_description(self, response, announce_url, id_property, ID, id_search, announce_image, img_cnt):
      self.announces_cnt += 1

      self.serializer.send(ID, id_property, response.text, "Colombes","ile de france", announce_url, announce_url[12:19], self.announce_title[ID], id_search, announce_image, img_cnt)
            
   def parse_announce_title(self, response, announce_url, id_property, id_search):

      ID = hash_id(announce_url)

      title = response.xpath('//h1[@class="detail-title title1"]/text()').extract()
      image_divs = response.xpath('//div[@class="carrousel_slide"]/img/@src').extract()
      image_divs2 = response.xpath('//div[@class="carrousel_slide"]/div/@data-lazy').extract()
      for image_div in image_divs2:
         image_divs.append(json.loads(image_div)['url'])

      image_count = 1
      announce_image = ""
      if image_divs:
         announce_image = 'http:'+ image_divs[0]

      for image_div in image_divs:
         image_url  = 'http:' + image_div
         image_name = os.path.join(IMAGES_FOLDER_NAME, str(ID) + '_' + str(image_count) + '.jpg')
         urllib.urlretrieve(image_url, image_name)
         image_count = image_count + 1

      img_cnt = image_count - 1
      if not title:
         self.announce_title[ID] = ""
      else:
         self.announce_title[ID] = title[0].strip()
      

      yield scrapy.Request(buildselogerdescriptionurl(announce_url), callback= lambda r, url = announce_url, id_prop = id_property, ID = ID, id_search = id_search, announce_image=announce_image, img_cnt=img_cnt:self.parse_prop_description(r,url, id_prop, ID, id_search, announce_image, img_cnt))

   def closed(self, reason):
      print("Announces found: %d " + self.announces_cnt + "\n")
      self.serializer.close()




