
#dealing with ValueErrors
while True:
    try:
        n = int(input("Height of block: "))
        if n > 0:
            break
    except ValueError:
        print("Not an integer")
#try to get integer, but if value error occurs then print error message (when user types in CAT which is not int)
#program doesnt return value yet, so program will keep "trying", i.e ask for user input until user types integer

for i in range(n):
    print("#")


#trying to print horizontally
for i in range(4)
    print("#", end = "")   #overwriting the "\n" at everyline to be ""


print("#" * 4). #will print "#" four times


print() #will print \n automatically. print comes with \n