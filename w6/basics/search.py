import sys

names = ["abc", "efg", "fgh", "ijk"]
name = input("Names: ")

if name in names:
    sys.exit(0) #found
sys.exit(1)