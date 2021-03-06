# Makefile for BayRate
#
# Program requires the following libraries:
#   - MySql development libraries
#   - MySql++ library
#   - GNU Scientific Library
#   - Boost Library

LIBS=-lm -lgsl -lgslcblas -lmysqlpp -lboost_date_time
LIBS_MAIN=-lm -lgsl -lgslcblas -lboost_date_time

INC=-I/usr/include/mysql
FLAGS=-g -Wall

all: bayrate_csv bayrate check basicrate copyMembership syncDBs

bayrate_csv: bayrate_csv.cpp collection.o game.o player.o
	g++ $(FLAGS) -static collection.o game.o bayrate_csv.cpp player.o $(LIBS_MAIN) -o bayrate_csv

bayrate: bayrate.cpp db.o collection.o game.o player.o
	g++ $(FLAGS) db.o collection.o game.o bayrate.cpp player.o $(INC) $(LIBS) -o bayrate

check: check.cpp db.o collection.o game.o player.o
	g++ $(FLAGS) db.o collection.o game.o check.cpp player.o $(INC) $(LIBS) -o check

basicrate: GSLSimplex.cpp db.o collection.o test-game.o player.o
	g++ $(FLAGS) db.o collection.o game.o GSLSimplex.cpp player.o $(INC) $(LIBS) -o basicrate

copyMembership: memUpdate.cpp db.o
	g++ ${FLAGS} -o copyMembership memUpdate.cpp $(INC) $(LIBS)

syncDBs: syncDBs.cpp db.o
	g++ ${FLAGS} db.o collection.o game.o player.o -o syncDBs syncDBs.cpp $(INC) $(LIBS)

db.o: db.cpp tdListEntry.h
	g++ $(FLAGS) -c db.cpp -o db.o $(INC) $(LIBS)

game.o: game.cpp
	g++ $(FLAGS) -c game.cpp -o game.o $(INC) $(LIBS)

test-game.o: test-game.cpp
	g++ $(FLAGS) -c test-game.cpp -o test-game.o $(INC) $(LIBS)

player.o: player.cpp
	g++ $(FLAGS) -c player.cpp -o player.o $(INC) $(LIBS)

collection.o: collection.cpp tdListEntry.h
	g++ $(FLAGS) -c collection.cpp -o collection.o $(INC) $(LIBS)

clean:
	rm -f *.o
	rm -f bayrate
	rm -f bayrate_csv
	rm -f check
	rm -f basicrate
	rm -f copyMembership

archive:
	tar zcvf BayRate.tgz *.cpp *.h makefile COPYING RankChanges.pl
