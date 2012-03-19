#!/usr/bin/python -O

'''
List all solar eclipses in the 21st century (from Wikipedia). Requires
Python 2.7 and BeautifulSoup 4.

Usage: python load_eclipses.py > eclipses.txt
'''

# Import 'print' function so we can use it as an argument to 'map'
from __future__ import print_function

from bs4 import BeautifulSoup as beautiful  # HTML parser
from urllib2 import build_opener            # Download web page
import re                                   # Regular expressions

URL = 'https://en.wikipedia.org/wiki/' +\
    'List_of_solar_eclipses_in_the_21st_century'
RE = re.compile(r'^\d{4}-\d{2}-\d{2}$')     # Format 2008-08-01

def load_html (url):
    '''
    Download url and return BeautifulSoup-parsed HTML
    '''
    opener = build_opener()
    # Pretend to be Mozilla
    opener.addheaders = [('User-agent', 'Mozilla/5.0')]
    # Download and parse
    return beautiful(opener.open(url))

def date_filter (tag):
    '''
    Tag filter function
    '''
    return tag.get('class') == [u'sortkey'] \
      and RE.match(tag.string.strip())

def print_eclipses ():
    '''
    Print a list of all solar eclipses in the 21st century.
    '''
    eclipses = load_html(URL).find_all(date_filter)
    map(print, [tag.string.strip() for tag in eclipses])

if __name__ == '__main__':
    print_eclipses()
