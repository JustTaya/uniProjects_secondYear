#!/bin/bash
######
###
# Lab3 installer
###
######


##

function downloadDeps {
    sudo apt-get update && sudo apt-get -y upgrade
    sudo apt-get install python3
    sudo apt-get install python-pip
    sudo apt-get install postgresql
    sudo -u postgres createuser user
    sudo -u postgres createdb db
    sudo -u postgres psql
    alter user user with encrypted password 'postgres';
    grant all privileges on database db to user;
    \q
    pip install -r requirements.txt --no-index --find-links file:///tmp/packages
    exit
}


downloadDeps