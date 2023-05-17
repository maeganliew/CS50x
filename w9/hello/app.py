from flask import Flask, render_template, request #flask library has three things

app = Flask(__name__)   #passing this file to the Flask function. __name__ just means current file


@app.route("/", methods=["GET", "POST"])   #/ is the main route. if it's designed to return "index.html" then the page asking for name input will be run first
def index():  #define function called index
    if request.method == "GET":   #if form didnt get submitted(user didnt click submit, action is still default "get")
        return render_template("index.html")
    elif request.method == "POST":
        return render_template("greet.html", name=request.form.get("name", "world"))    #render function will find the files in templates folder, spit everything out. right click "view page source" to look at index.
