# AGA-Ratings-Program
AGA Ratings Program

## What If...
What if you could instantly get an updated rating after your tournament? What if it were as simple as making an api call?

## Why
Might there be better ways to rate games? Maybe (*cough* Whole History Rating, Glicko-2 (OGS), etc *cough*). But many people specifically want to know their AGA rating. While the AGA owns their database of "members", it is possible to calculate for anyone an "unofficial" rating that would exactly match what the AGA would reward. However, where the AGA is resicted by various factors and considerations, the general public is not. I am particularly thinking of the ~80 people who came to my tournament in January of 2020 with the promise of rating and which to this day (2020/8/3) the AGA has not provided.

## The Math
Paul Matthews was one of the lead authors of the rating system. He published an "easy" to understand explanation of the system
Simple Version - https://www.usgo.org/sites/default/files/pdf/AGARatings-Simple.pdf

Phil Waldron had a role I have not yet unearthed, but he has provided an detailed mathematical explanation of the system.
Detailed Version - https://www.usgo.org/sites/default/files/pdf/AGARatings-Math.pdf

## The Code
The code for the ratings were written by Jonathan Bresler of which this repositor is forked from. This is the code the AGA currently uses to calculate ratings.

Andrew Jackson has done some work on this. Particularily in updating the sigma value for how your rating decays over time so that people are able to advance more true to their actaul ability.
He has a forked version of this code here (https://github.com/amj/AGA-Ratings-Program/tree/myfork)

I also found online some code written by Philip Waldron. I think it is written in perl and it has some good notes in it
https://metacpan.org/source/REID/Games-Go-AGA-BayRate-0.119/lib/Games/Go/AGA/BayRate/Collection.pm#PGames::Go::AGA::BayRate::Collection

## The Goal
Does this have to be done in C++? Heck no.
The goal of this project is simply to make an API which takes the input of a game result along with two payers, their ratings, and their sigma, and then returns a new rating and new sigma for each player. Ideally in json.

### Who am I?
I am a currently (2019-2021) a board member of the American Go Association, but this project is currently not affiliated with them.
I am also the founder of the Ohio Go Assiciation, the Columbus Go Center, and the lead organizer for the Columbus Go Club and the regional tournament The Midwest Open.
But most importantly, I spend most of my time working to help the worlds Go players connect with eachother. To carry this mission forward I created BadukClub where I hope to work with others to provide assistance to club organizers so that they have an easier time organizing their local communties. One part of that is our map, easily accesible via https://wheretoplaygo.com and I am working on lots of other neat things to come (*cough* import and distribution of equipement, various forms or media for organizers such as podcasts and video, and club/tournament management tools available for free online)

If you  choose to help me with this. I thank you.
