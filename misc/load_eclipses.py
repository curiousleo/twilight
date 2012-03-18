from __future__ import print_function

from bs4 import BeautifulSoup as beautiful
from urllib2 import build_opener
from codecs import open as copen
import re

URL = 'https://en.wikipedia.org/wiki/List_of_solar_eclipses_in_the_21st_century'
RE = re.compile(r'^\d{4}-\d{2}-\d{2}$')

def load_html (url):
    opener = build_opener()
# Pretend to be Mozilla
    opener.addheaders = [('User-agent', 'Mozilla/5.0')]
# Download and parse
    return beautiful(opener.open(url))

def date_filter (tag):
  return tag.get('class') == [u'sortkey'] \
    and RE.match(tag.string.strip())

eclipses = load_html(URL).find_all(date_filter)
map(print, [tag.string.strip() for tag in eclipses])
