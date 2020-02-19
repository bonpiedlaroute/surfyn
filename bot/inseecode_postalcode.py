#!/usr/bin/env python
# -*- coding: utf-8 -*- 
# (c) Copyright 2020 Noel Tchidjo
# All rights reserved


import csv

postalcodeByCity = dict()
inseecodeByCity = dict()
with open('spiders/data/inseecode_postalcode_bycity.csv') as csv_file:
    csv_reader = csv.DictReader(csv_file, delimiter=';')
    for row in csv_reader:
            inseecodeByCity[row["Commune"].lower()] = row["Code INSEE"]
            postalcodeByCity[row["Commune"].lower()] = row["Code Postal"]

osmidByInseeCode = dict()
with open('spiders/data/osm_id_insee.csv') as csv_file:
    csv_reader = csv.DictReader(csv_file, delimiter=';')
    for row in csv_reader:
            osmidByInseeCode[row["Code INSEE"]] = row["OSM_ID"]