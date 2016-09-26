#!/usr/bin/python

import os, sys


def GenOutput(f):
  cmd = "./build/{0} > output/{0}.output 2>&1".format(f)
  print cmd
  os.system(cmd)

def GenAllOutput():
  for root, dirs, files in os.walk('./build'):
    for afile in files:
      GenOutput(afile)


param_file = 'graphviz_shower.cpp'
faild = []
def MakeAFile(f, param_file):
    cmd = 'g++-4.8 -o build/{0} --std=c++0x source/{1} source/{2}'.format(f[0:-4], f, param_file) 
    print cmd
    if os.system(cmd) != 0:
        faild.append(f)


if len(sys.argv) <= 1:
    for dp, dn, fn in os.walk('./source'):
        if dp == './source':
            for f in fn:
                if f != param_file and f.endswith('cpp'):
                    MakeAFile(f, param_file)

    if len(faild) > 0:
      print "Build Failed: ", faild
    else:
      print "Build Successed!"
else:
  if sys.argv[1] == "output":
    GenAllOutput()
  else:
    MakeAFile(sys.argv[1][sys.argv[1].find('source/') + len('source/'):], param_file)






