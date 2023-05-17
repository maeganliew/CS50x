#def to define function!!

words = set()  #collection of values, without duplicates

def check(word): #define a function called check, "word" is passed as argument
    if word.lower() in words:
        return True #CAPITAL!!!!!!
    return False

def load(dictionary):
    file = open(dictionary, "r")
    for line in file:
        word = line.rstrip() #rstrip to get rid of \n in every line (only get word)
        words.add(word) #add(function) to words
    close(file)
    return True

def size():
    return len(words) #len to get length