from cs50 import get_float

while True:
    change = get_float("Change owed: ") * 100
    if change >= 0:
        break

n: int = 0
while change >= 25:
    change -= 25
    n += 1
while change >= 10:
    change -= 10
    n += 1
while change >= 5:
    change -= 5
    n += 1
while change >= 1:
    change -= 1
    n += 1
print(f"{n}")