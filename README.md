# aga-ratings
REST Interface to run AGA ratings via  https://aga-ratings.herokuapp.com/run

Usage
--------

$ curl -X POST -H "Content-Type: application/json" -d @results.json https://aga-ratings.herokuapp.com/run

Deploying
-----------

Any push to the mster branch of this repo will automatically deploy to heroku.

Compiling the C++ part
-------------------------

The ratings are computed by C++ code taken from https://github.com/Fraze/AGA-Ratings-Program,
which is the code used by the AGA to pull tournament results from their DB, compute new ratings,
and upload the the new ratings to the DB. There is now a new binary bayrate_csv which we use
to read csv input and write csv output. The Python endpoint converts JSON to csv, runs bayrate_csv, 
and converts the output back to JSON.

If you want to change how the ratings work, you need to compile bayrate_csv on a 64-bit Ubuntu box.
In detail:

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


=== The End ===



