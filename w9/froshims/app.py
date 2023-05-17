from flask import Flask, render_template, request

app = Flask(__name__)

REGISTRANTS = {} #define an empty dictionary

SPORTS = [
    "Basketball",
    "Soccer",
    "Frisbee"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    sport = request.form.get("sport")
    if not name or sport not in SPORTS:
        return render_template("failure.html")
    REGISTRANTS[name] = sport  #filling the dict with key values
    return render_template("success.html")


@app.route("/registrants")
def registrants():
    return render_template("registrants.html", registrants=REGISTRANTS)