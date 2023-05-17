from pyfiglet import Figlet
import sys
import random

figlet = Figlet()

if len(sys.argv)==1:  #random font
        f = random.choice(figlet.getFonts())
        figlet.setFont(font=f)
        s = input("Text: ")
        print(figlet.renderText(s))

elif len(sys.argv)==3:
    if sys.argv[1] in ["-f", "--font"]: #and sys.argv[2] in random.choice(figlet.getFonts()):
        figlet.setFont(font=sys.argv[2])
        s = input("Text: ")
        print(figlet.renderText(s))
    else:
        sys.exit("Invalid Usage")

else:
    sys.exit("Invalid Usage")