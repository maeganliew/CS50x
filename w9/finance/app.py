import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime, timezone

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

db.execute("CREATE TABLE IF NOT EXISTS transactions (id INTEGER, user_id NUMERIC NOT NULL, symbol TEXT NOT NULL, shares NUMERIC NOT NULL, price NUMERIC NOT NULL, timestamp TEXT, PRIMARY KEY(id))")  #primary key is to avoid repeatinf? causse evry order is unique

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required  #ensures that user is logged in before visiting these sites
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    data = db.execute("SELECT symbol, SUM(shares) AS shares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)  #returning lists of dicts
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]  #after select are left with dicts, ["cash"] to retrive the value of key:cash
    for row in data:
        dict = lookup(row["symbol"])  #returns a dict with company name, symbol, price
        row["company"] = dict["name"]
        row["price"] = dict["price"]
    return render_template("index.html", data=data, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    symbol = request.form.get("symbol")
    shares = int(request.form.get("shares")) #VERY IMPORTANT typecast number of shares from str to int
    if not symbol or not lookup(symbol):
        return apology("Input is blank or share does not exist")
    if shares < 1:
        return apology("Invalid number of shares")

    data = lookup(symbol)  #data is a dict!!
    price = data["price"]
    symbol = data["symbol"]
    cash = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])[0]["cash"]  #last 2 square brackets is to only select one cash value, instead of a list
    if price*shares > cash:
        return apology("Insufficient balance. Failed to purchase.")

    db.execute("INSERT INTO transactions (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)", session["user_id"], symbol, shares, price, datetime.now())
    db.execute("UPDATE users SET cash = ? WHERE id = ?", cash-price*shares, session["user_id"])

    flash("Bought!")
    return redirect("/")  #main route, shows portfolio of stocks


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    data = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", data = data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    # Forget any user_id
    session.clear()
    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    symbol = request.form.get("symbol")
    result = lookup(symbol)  #use lookup function to search for the stock
    if not result:
        return render_template("quote.html")
    return render_template("quoted.html", name=result["name"], price=usd(result["price"]), symbol=result["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username or len(db.execute("SELECT * FROM users where username == ?", username))>0:  #use len of db.execute's return to check for repeated users
            return apology("Username blank, or already exists")
        if not password or confirmation != password:
            return apology("Password blank, or does not match")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]  #remember the user logged in
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "GET":
        dicts = db.execute("SELECT symbol FROM transactions WHERE user_id = ?", user_id)  #HAVING SUM(shares)>0 avoid sending symbols with negative share numbers
        return render_template("sell.html", symbol = [row["symbol"] for row in dicts])  #dicts is a list of dicts as per previous line, row is iterating through every dict. "symbol" is the key of the dict

    else:
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        if not symbol or not lookup(symbol):
            return apology("Input is blank or share does not exist")
        if shares < 1:
            return apology("Invalid number of shares")

        owned = db.execute("SELECT shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)[0]["shares"]  #check current number of shares owned. remember that SELECT returns a dict, [0]["shares"] locates the value in dict
        if owned < shares:
            return apology("Insufficient number of shares")

        data = lookup(symbol)
        price = data["price"]
        symbol = data["symbol"]
        cash = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])[0]["cash"]  #last 2 square brackets is to only select one cash value, instead of a list

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)", session["user_id"], symbol, (-1)*shares, price, datetime.now())
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash+price*shares, session["user_id"])  #selling shares, cash will increase

        flash("Sold!") #pop-up message
        return redirect("/")


@app.route("/topup", methods=["GET", "POST"])
@login_required
def topup():
    user_id = session["user_id"]
    if request.method == "GET":
        return render_template("topup.html")
    else:
        amount = int(request.form.get("amount"))
        if amount < 1:
            return apology("Invalid amount.")
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        total = cash + amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", total, user_id)
        return redirect("/topup")