#!/bin/bash
######
###
# Lab3 installer
###
######


##

function downloadDeps {
    python get-pip.py
    psql -u postgres
    CREATE ROLE user LOGIN PASSWORD postgres;
    CREATE DATABASE db;
    ALTER DATABASE db OWNER TO user;
    \q
    psql -u myusername -d myowndb
    pip install -r requirements.txt --no-index --find-links file:///tmp/packages
    exit
}


downloadDeps