import os

lines = open('lumis.txt').readlines()

for line in lines:
  words = line.split()
  print '    else if(trig=="'+words[0]+'"){'
  print '      return '+words[1]+';'
  print '    }'
