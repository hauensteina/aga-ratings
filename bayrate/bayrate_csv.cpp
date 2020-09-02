/*************************************************************************************

Run ratings from a csv input file and dump new ratings
to a csv output file. Runs stand-alone, no access to any db required.

Andreas Hauenstein (AHN), Sep 2020

***************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "tdListEntry.h"
#include "collection.h"
#include "helpers.h"

using namespace std;
namespace bg = boost::gregorian;

//-------------
void usage()
{
    std::string msg =
        "Usage: bayrate_main --in results.csv --out new_ratings.csv --tournament_date <yyyy-mm-dd>";
    cerr << msg << endl;
    exit(1);
} // usage()

//----------------------------------------------------------------------
tuple <string, string, bg::date> parse_args( int argc, char *argv[])
{
    if (argc != 7) {
        usage();
    }
    string infile, outfile;
    bg::date tournament_date;
    for (int i = 1; i < argc; i++) {
        if (strcmp( argv[i], "--in") == 0) {
            i++;
            infile = argv[i];
        }
        else if (strcmp( argv[i], "--out") == 0) {
            i++;
            outfile = argv[i];
        }
        else if (strcmp( argv[i], "--tournament_date") == 0) {
            i++;
            tournament_date = bg::date( bg::from_string( argv[i]));
        }
        else {
            cerr << "Error: unknown option " << argv[i] << endl;
            usage();
        }
    } // for
    return make_tuple( infile, outfile, tournament_date);
} // parse_args()

//---------------------------------
int main(int argc, char *argv[])
{
    string infname, outfname;
    bg::date tournament_date;
    tie( infname, outfname, tournament_date) = parse_args( argc, argv);
    // Read tournament results and player data. Look at results_example.csv .
    collection games( infname);
    // Fiddle with initial rating, rank, and sigma .
    games.initSeeding( tournament_date);

    // Compute new ratings from game results.
    // Start with the fast rating algorithm. If it fails, then go for the simplex method as a backup.
    if (games.calc_ratings_fdf() != 0) {
        if (games.calc_ratings() != 0) {
            cerr << "ERROR: Fatal error computing ratings" << endl;
            exit(1);
        }
    }
    // Dump results as json
    string error;
    games.dump_new_ratings( outfname, error);
    if (error != "") {
        cerr << error << endl;
        exit(1);
    }

    cout << "New ratings computed using " << games.getFdfIterations() << " fdf iterations and "
         << games.getSimplexIterations() << " simplex iterations..." << endl;

} // main()
