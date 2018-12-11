#!/bin/bash
######
###
# Lab3 installer
###
######


##

function downloadDeps {
    python get-pip.py
    pip install -r requirements.txt --no-index --find-links file:///tmp/packages
    exit
}


downloadDeps