#!/usr/bin/python3

# Twilight
#
# csv_merge.py
# Merge two or more text files into one CSV file

'''
Usage: python csv_merge.py 1.txt 2.txt 3.txt > merge.csv
'''

from os.path import split

def merge (fnames):
  '''
  Merge text files into CSV format and print the output.
  '''
  total = set()
  sets = [set(readlines(f)) for f in fnames]
  for s in sets: total.update(s)
  total.discard('')

  total = list(total)
  total.sort()

  # Print first row: File names
  print(*[split(f)[1] for f in fnames], sep=',')

  for v in total:
    print(*[v if v in s else '' for s in sets], sep=',')

def readlines (fname):
  '''
  Read the lines of a file, discarding those starting with a hash (#).
  '''
  return [line.strip()
      for line in open(fname).readlines()
      if not line.startswith('#')]

# Running as a program?
if __name__ == '__main__':
  from sys import argv
  merge(argv[1:])
