import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from functools import wraps

app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///pigeon.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/1.1.x/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function



@app.route("/")
@login_required
def index():
    return render_template("index.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    #forget previous user
    session.clear()

    if request.method == "POST":
        if not request.form.get("username") or not request.form.get("password"):
            return render_template("login.html")
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return render_template("login.html")

        session["user_id"] = rows[0]["id"]  #remember current logged in user
        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username or len(db.execute("SELECT * FROM users where username == ?", username))>0:  #use len of db.execute's return to check for repeated users
             return render_template("register.html")
        if not password or confirmation != password:
             return render_template("register.html")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]  #remember the user logged in
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/send", methods=["GET", "POST"])
@login_required
def send():
    if request.method == "POST":
        receiver = request.form.get("receiver")
        sender = request.form.get("sender")
        text = request.form.get("text")
        if not receiver or not sender or not text:
            return render_template("send.html")
        db.execute("INSERT INTO storage (sender_id, sender, receiver, message) VALUES (?, ?, ?, ?)", session["user_id"], sender, receiver, text)
        flash("Message sent.")
        return redirect("/send")
    else:
        return render_template("send.html")


@app.route("/receive", methods=["GET", "POST"])
@login_required
def receive():
    if request.method == "POST":
        name = request.form.get("name")
        if not name:
            return render_template("receive.html")
        data = db.execute("SELECT * FROM storage WHERE receiver = ?", name)
        if not data:
            return render_template("receive.html")
        return render_template("receive2.html", data=data)

    else:
        return render_template("receive.html")

@app.route("/history")
@login_required
def history():
    data = db.execute("SELECT * FROM storage WHERE sender_id = ?", session["user_id"])
    return render_template("history.html", data=data)
