# aga-ratings
REST Interface to run AGA ratings via  https://aga-ratings.herokuapp.com/run

Usage
--------

```
$ curl -X POST -H "Content-Type: application/json" -d @results.json https://aga-ratings.herokuapp.com/run
```

For the JSON format, look at results.json in this repository.

Deploying
-----------

Any push to the master branch of this repository will automatically deploy to heroku.
If you want to run locally, you need to be on Ubuntu and have python3 installed.

Then:
```
$ cd aga-ratings
$ python -m venv venv
$ source venv/bin/activate
$ pip install -r requirements.txt
$ python heroku_app.py
```

Test with
```
$ curl -X POST -H "Content-Type: application/json" -d @results.json http://127.0.0.1:8000/run
```
Compiling the C++ Executable
--------------------------------

The ratings are computed by C++ code taken from https://github.com/Fraze/AGA-Ratings-Program,
which is the code used by the AGA to pull tournament results from their DB, compute new ratings,
and upload the the new ratings to the DB. There is now a new binary bayrate_csv which reads csv input 
and writes csv output. No DB connection is needed. The Python endpoint converts JSON to csv, runs bayrate_csv, 
and converts the output back to JSON.

If you want to change how the ratings work, you need to compile bayrate_csv on a 64-bit Ubuntu box.
In detail:
```
$ cd bayrate
$ sudo apt-get install libgsl0ldbl
$ sudo apt-get install libgsl23 libgslcblas0
$ sudo apt-get install libgsl-dev
$ sudo apt-get install libboost-all-dev
// Edit some cpp files to make improvements
$ make clean bayrate_csv
$ git add -u
$ git commit -m 'c++ is much better now'
$ git push origin master
```

=== The End ===



