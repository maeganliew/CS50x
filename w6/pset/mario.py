while True:
    height = input("Height:")
    if height.isdigit():
        if int(height) > 0 and int(height) < 9:
            break

for n in range(int(height)):
    for space in range(0, int(height) -1 -n, +1):          #from 0 to height -1 -n, by +1. remember to typecast height!!!!!
        print(" ", end = "")
    for hash in range(n+1):
        print("#", end = "")

    print("  ", end = "")

    for hash in range(n+1):
        print("#", end = "")
    print()