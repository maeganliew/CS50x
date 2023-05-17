before = input("Before: ")
after0 = before.capitalize()   #only capitalizes FIRST character
after1 = before.upper()  #capitalizes everything

print(f"After: {after0}")
print(f"After: {after1}")

#after0 is the result of capitalizing before, not changing the actual before string. before string cannot be changed