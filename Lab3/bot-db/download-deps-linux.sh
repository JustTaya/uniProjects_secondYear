#!/bin/bash
######
###
# Lab3 installer
###
######


##

function downloadDeps {
    sudo apt-get update && sudo apt-get -y upgrade
    sudo apt-get install python-pip
    pip install -r requirements.txt --no-index --find-links file:///tmp/packages
    exit
}


downloadDeps