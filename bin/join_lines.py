# coding: utf-8
"""
合并相邻的空行

用pandoc生成的rst文件经常有过多的空行，需要合并一下
"""

import sys
with open(sys.argv[1], "r") as f:
    ls = f.readlines()

vv = [v.rstrip() for v in ls]
rst = []
rst.append(vv[0])
for i in range(1, len(vv)):
    if vv[i] or vv[i-1]:
        rst.append(vv[i])

print("\n".join(rst))
