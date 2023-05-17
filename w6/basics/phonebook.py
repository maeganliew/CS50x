import csv

with open("phonebook.csv", "a") as file:  #with opening of file, do as below and close file

    name = input("Name: ")
    number = input("Number: ")

    #below only writes in the order of name, number
    writer = csv.writer(file)
    writer.writerow([name, number])

    writer = csv.DictWriter(file, fieldnames = {"name", "number"})  #initialised the fields. LHS for name, RHS for number
    writer.writerow({"name": name, "number": number})