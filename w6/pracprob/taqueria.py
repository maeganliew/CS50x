import sys

menu: dict[str, float] = {    #declare stuff that youre storing in dict!!
    "baja taco": 4.00,
    "burrito": 7.50,
    "bowl": 8.50,
    "nachos": 11.00,
    "quesadilla": 8.50,
    "super burrito": 8.50,
    "super quesadilla": 9.50,
    "taco": 3.00,
    "tortilla salad": 8.00
}

price: int = 0   #initialisng int

while True:
    try:
        item = input("Order: ").lower()
        if item in menu:
            price += menu[item]   #square bracket to find keys in dict
            print(f"Total: ${price:.2f}")
    except EOFError:
        print()
        break