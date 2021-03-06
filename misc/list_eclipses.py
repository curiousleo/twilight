#!/usr/bin/python3

# Twilight
#
# list_eclipses.py
# Download, parse and print Wikipedia's list of 21st century solar
# eclipses.

'''
List all solar eclipses in the 21st century (from Wikipedia).
Requires Python 3 and lxml (lxml.de).

Usage: python list_eclipses.py > eclipses.txt
'''

from lxml import html, etree                # HTML & XPath
from urllib import request                  # Download web page

URL = 'https://en.wikipedia.org/wiki/' +\
    'List_of_solar_eclipses_in_the_21st_century'
XPATH = r'//span[@class="sortkey" and ' +\
    r're:test(., "^\d{4}-\d{2}-\d{2}$")]/text()'
RE_NS = 'http://exslt.org/regular-expressions'

def load_html (url):
    '''
    Download url and return lxml-parsed HTML
    '''
    # Pretend to be Mozilla
    req = request.Request(
        url=url, headers={'User-agent' : 'Mozilla/5.0'})
    # Download and parse
    return html.parse(request.urlopen(req)).getroot()

def list_eclipses ():
    '''
    Print a list of all solar eclipses in the 21st century.
    '''
    # Compile XPath expression
    matches = etree.XPath(XPATH, namespaces={'re' : RE_NS})
    # Return matches
    return matches(load_html(URL))

# Running as a program?
if __name__ == '__main__':
    for el in list_eclipses(): print(el)
