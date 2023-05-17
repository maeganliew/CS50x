from sys import argv

if len(argv) == 2:
    print(f"Hello {argv[1]}")
else:
    print("Hello")



#printing CLIs
for arg in argv:   #arg for argument
    print(arg)

for arg in argv[1:]:  #argv[1:] will start from first arg and continue until the end
    print(arg)



#exit status
import sys

if len(sys.argv) != 2
    print("Missing argument")
    sys.exit(1)  #means failed

print(f"Hello {argv[1]}")
sys.exit(0)  #means succeed