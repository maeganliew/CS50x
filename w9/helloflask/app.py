from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        return render_template("index.html")
    else:
        print("Form Submitted.")
        colour = request.form.get("colour")
        if colour == "red" or colour == "blue":
            return render_template("colour.html", colour=colour)
        else:
            return render_template("index.html")
