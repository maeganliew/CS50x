from cs50 import SQL

db = SQL("sqlite:///favorites.db")

favorite = input("Favorite problem: ")

rows = db.execute("SELECT * FROM favorites WHERE problem = ?", favorite)  #treat SQL command as string, pass it into python funtion 'execute'

for row in rows
    print(row["xxx" ])