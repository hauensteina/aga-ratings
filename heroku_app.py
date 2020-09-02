#!/usr/bin/env python

# /********************************************************************
# Filename: aga_ratings/heroku_app.py
# Author: AHN
# Creation Date: Sep 2, 2020
# **********************************************************************/
#
# A REST Api to compute new AGA ratings after a tournament
#

from pdb import set_trace as BP
import os, sys, re, json
from subprocess import Popen, PIPE
from flask import Flask, jsonify, request, redirect, url_for

app = Flask( __name__)

@app.route('/run', methods=['POST'])
#-----------------------------------------------
def run():
    """ Compute new ratings from tournament results """
    try:
        required_cols = set(['pb_id', 'pb_name', 'pb_rank', 'pb_rating', 'pb_sigma', 'pb_rating_date',
                             'pw_id', 'pw_name', 'pw_rank', 'pw_rating', 'pw_sigma', 'pw_rating_date',
                             'komi', 'handicap', 'result'])
        tournament = request.json
        if not 'tournament_date' in tournament:
            resp = {'error': 'tournament_date missing'}
            return jsonify( resp)
        if not 'games' in tournament:
            resp = {'error': 'no games'}
            return jsonify( resp)
        games = tournament['games']
        cols = list(games[0].keys())
        if not set(cols) == required_cols:
            resp = {'error': 'game keys must be: %s' % str(required_cols)}
            return jsonify( resp)
        tournament_date = tournament['tournament_date']

        # Dump games to csv
        infname = 'results.csv'
        with open( infname, 'w') as outf:
            # Header
            for idx,col in enumerate(cols):
                if idx: outf.write(',')
                outf.write( col)
            outf.write('\n')
            for game in games:
                for idx,key in enumerate(game):
                    if not key == cols[idx]:
                        resp = {'error': 'bad game: %s' % str(game)}
                        return jsonify( resp)
                    if idx: outf.write(',')
                    outf.write( str(game[key]))
                outf.write('\n')

        # Run ratings
        outfname = 'new_ratings.csv'
        cmd = 'bayrate/bayrate_csv --in %s --out %s --tournament_date %s' % (infname, outfname, tournament_date)
        p = Popen(cmd, shell=True, stdout=PIPE, stderr=PIPE, close_fds=True)
        stdout, stderr = p.communicate()

        if stderr:
            resp = {'error': 'bayesrate failed: %s' % stderr}
            return jsonify( resp)

        lines = []
        with open( outfname) as inf:
            for lnum, line in enumerate( inf):
                lines.append(line)
        rows = csv2dict( lines)
        return jsonify( {'new_ratings': rows })

    except Exception as e:
        resp = {'error': 'Exception: %s' % str(e)}
        return jsonify( resp)

# Transform csv format to a list of dicts.
# Takes a list of lines.
#-------------------------------------------
def csv2dict( lines):
    res = []
    colnames = []
    for idx, line in enumerate( lines):
        line = line.strip()
        if len(line) == 0: continue
        if line[0] == '#': continue
        words = line.split(',')
        words = [w.strip() for w in words]
        if not colnames:
            colnames = words
            continue
        ddict = { col:number(words[idx]) for idx,col in enumerate(colnames) }
        res.append(ddict)
    return res

# Convert a string to a float, if it is a number
#--------------------------------------------------
def number( tstr):
    try:
        res = float( tstr)
        return res
    except ValueError:
        return tstr

# Check whether string is numeric
#----------------------------------------
def isnum( tstr):
    try:
        res = float( tstr)
        return True
    except ValueError:
        return False

#----------------------------
if __name__ == '__main__':
    app.run( host='0.0.0.0', port=8000, debug=True)
