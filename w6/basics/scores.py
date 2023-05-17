scores = [10, 20, 30]   #initialising the list to some values

average = sum(scores) / len(scores)  #len(scores) is to find length of the list i.e. number of elements in the list
print(f"Average: {average:.0f}"). #zero decimal points


#using append function to edit a list
scores = []                #define scores as a list
for i in range(3):
    score = get_int("Score: ")
    scores.append(score) #will auto change the size of list, add elements to list, no need realloc

    scores += [scores] #line 11 and 13 does the same thing