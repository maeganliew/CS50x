from cs50 import get_string

text = get_string("Text: ")
word = len(text.split())    #.split() returns a list of strings, len to find size of list i.e. how many words

lett: int = 0
for i in text:
    if i.isalpha():
        lett += 1

sent: int = 0
for i in text:
    if i == "!" or i == "."or i == "?":
        sent += 1

L: float = 0
S: float = 0
R: int = 0
L = lett / word * 100
S = sent / word * 100
R = round(0.0588 * L - 0.296 * S - 15.8)
if R < 1:
    print("Before Grade 1")
elif R > 15:
    print("Grade 16+")
else:
    print(f"Grade {R}")