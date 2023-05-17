import csv
from cs50 import SQL

db = SQL("sqlite:///roster.db")

def fill_houses(house, house_list, head):
    count = 0
    for h in house_list: #only access and compare the house key, not the head key
        if h["house"] == house:
            count += 1
    if count == 0:
        house_list.append({"house": house, "head": head})  #append a whole dictionary into house_list. so house_list is a list of dicts. one dict for one house&head


def fill_students(name, students_list):
    students_list.append({"name": name})  #a list of dicts, each dict for one student


def fill_relationships(name, house, relationships):
    relationships.append({"name": name, "house":house})


students_list = []
house_list = []
relationships = []


with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        name = row["student_name"]
        house = row["house"]
        head = row["head"]
        fill_houses(house, house_list, head)
        fill_students(name, students_list)
        fill_relationships(name, house, relationships)

    #print(house_list)


for i in students_list:
    db.execute("INSERT INTO students_new(student_name) VALUES (?)", i["name"])

for i in house_list:
    db.execute("INSERT INTO houses(house, head) VALUES (?, ?)", i["house"], i["head"])

for i in relationships:
    db.execute("INSERT INTO relationships(student_name, house) VALUES (?,?)", i["name"], i["house"])