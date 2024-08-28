import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError

from helpers import apology, login_required, lookup, usd

from datetime import datetime, timezone

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Create new table, and index (for efficient search later on) to keep track of stock orders, by each user
db.execute("CREATE TABLE IF NOT EXISTS stocks (stockid INTEGER, user_id NUMERIC NOT NULL, symbol TEXT NOT NULL, \
            shares NUMERIC NOT NULL, price NUMERIC NOT NULL, timestamp TEXT, PRIMARY KEY(stockid), \
            FOREIGN KEY(user_id) REFERENCES users(id))")
db.execute("CREATE INDEX IF NOT EXISTS orders_by_user_id_index ON stocks (user_id)")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # calls a function that will get all the users current shares owned
    owns = own_shares(session["user_id"])

    total = 0
    for symbol, shares in owns.items():
        result = lookup(symbol)
        name, price = result["name"], result["price"]
        stock_value = shares * price
        total += stock_value
        owns[symbol] = (name, shares, usd(price), usd(stock_value))

    # get the total cash left from the users table
    cash = db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])[0]['cash']

    # total cash
    total += cash

    if owns != "":
        return render_template("home.html", owns=owns, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    try:
        shares = int(request.form.get("shares"))
    except:
        return apology("Number must be an integer", 400)

    if shares <= 0:
        return apology("Shares must be a posative number", 400)

    # check the stock symbol sent from the form
    stocks = lookup(request.form.get("symbol"))

    # if the stocks symbol doesnt match flag an error
    if not stocks:
        return apology("Missing Symbol", 400)

    user_id = session["user_id"]
    price = stocks["price"]
    symbol = stocks["symbol"]
    usrid = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", usrid)[0]['cash']

    # check if the user has enough cash to buy the new shares
    remain = cash - price * shares
    if remain < 0:
        return apology("Insufficient Cash Transaction Declined", 400)

    # update the users cash amount
    db.execute("UPDATE users SET cash = ? WHERE id = ?", remain, usrid)

    # insert a new row for the stocks that have bought
    db.execute("INSERT INTO stocks (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)",
               user_id, symbol, shares, price, time_now())

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # run the sql to get the current users shares and send to display in a table
    data = db.execute("SELECT symbol, shares, price, timestamp FROM stocks WHERE user_id = ?", session["user_id"])
    return render_template("history.html", data=data)


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

    # User reached route via GET (as by clicking a link or via redirect)
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

    # if the get method is used then go to the quote page
    if request.method == "GET":
        return render_template("quote.html")
    symbol = request.form.get("symbol")
    result = lookup(symbol)

    # if no results or the symbol is blank flag an error message
    if symbol == "":
        return apology("Symbol can not be blank", 400)
    if not result:
        return apology("Missing Symbol", 400)

    # else go to the quoted page
    return render_template("quoted.html", name=result["name"], price=usd(result["price"]), symbol=result["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    # check username and password
    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    if username == "" or len(db.execute('SELECT username FROM users WHERE username = ?', username)) > 0:
        return apology("Invalid Username: Blank, or already exists")
    if password == "" or password != confirmation:
        return apology("Invalid Password: Blank, or does not match")

    # Add new user to users db (includes: username and HASH of password)
    db.execute('INSERT INTO users (username, hash) \
            VALUES(?, ?)', username, generate_password_hash(password))

    # Query database for username
    rows = db.execute("SELECT * FROM users WHERE username = ?", username)

    # Log user in, i.e. Remember that this user has logged in
    session["user_id"] = rows[0]["id"]

    # Redirect user to home page
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    owns = own_shares(session["user_id"])

    if request.method == "GET":
        return render_template("sell.html", owns=owns.keys())

    symbol = request.form.get("symbol")
    # change the string into a int
    shares = int(request.form.get("shares"))

    if owns[symbol] < shares or shares > owns[symbol]:
        return apology("Invalid number of shares", 400)

    result = lookup(symbol)
    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
    price = result["price"]
    remain = cash + price * shares
    total = price * shares
    # update the users cash
    db.execute("UPDATE users SET cash = ? WHERE id = ?", remain, user_id)

    # log the transaction of the sale
    db.execute("INSERT INTO stocks (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)",
               user_id, symbol, -shares, price, time_now())
    return redirect("/")


@app.route("/Addfunds", methods=["GET", "POST"])
@login_required
def Addfunds():
    if request.method == "GET":
        return render_template("Addfunds.html")

    try:
        cash = int(request.form.get("cash"))
    except:
        return apology("Number must be an integer", 400)

    if cash <= 0:
        return apology("Shares must be a posative number", 400)

    usercash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']

    dbcash = usercash + cash
    db.execute("UPDATE users SET cash = ? WHERE id = ?", dbcash, session["user_id"])

    return redirect("/")


def errorhandler(e):
    # Handles all the errors
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)

# Listen for errors


for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

# function to get the users currently owned shares


def own_shares(user_id):
    owns = {}
    query = db.execute("SELECT symbol, shares FROM stocks WHERE user_id = ?", user_id)
    for q in query:
        symbol, shares = q["symbol"], q["shares"]
        owns[symbol] = owns.setdefault(symbol, 0) + shares
    owns = {k: v for k, v in owns.items() if v != 0}
    return owns

# function for the current time and date used when buying the shares


def time_now():
    now_utc = datetime.now(timezone.utc)
    return str(now_utc.date()) + ' @time ' + now_utc.time().strftime("%H:%M:%S")