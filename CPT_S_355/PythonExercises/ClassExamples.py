#CptS 355 class examples
debugging = True
def debug(*s): 
    if debugging: 
        print(*s)

# histogram
def histo(s):
    """ Computes the histogram of a given string. The histogram returned by the function is a list of characters in the input string s each paired with its frequency. 
    Characters must appear in the list ordered from most frequent to least frequent """
    d = {}
    for c in s:
        if c in d.keys():
            d[c] = d[c] + 1
        else: # we see the character c for the first time
            d[c] = 1
    return sorted(sorted(list(d.items())), key = lambda item: item[1],reverse=True)

def histo2(s):
    """Alternative implementation of histo using get function (loop solution)."""
    d = {}
    for c in s:
        d[c] = d.get(c,0) + 1
    return sorted(sorted(list(d.items())), key = lambda item: item[1],reverse=True)

def histo3(s):
    """ Alternative implementation of histo using comprehension. """
    return sorted(sorted(list(set([(c,s.count(c)) for c in s]))), key = lambda item: item[1],reverse=True)

def histo4(sentence):
    get_tuple = lambda c: (c,sentence.count(c))
    output = list(set(map(get_tuple,sentence)))
    return output

# Expected output for histo("implemented")
[('e', 3), ('m', 2), ('d', 1), ('i', 1), ('l', 1), ('n', 1), ('p', 1), ('t', 1)]

#------------------------------------------------------------------------------------
"""The following dictionary stores WSU’s college football game scores for the past 4 years. In 2020, WSU played only 4 games due to pandemic.  """
wsu_games = {
    2018: {"WYO":(41,19), "SJSU":(31,0),  "EWU":(59,24), "USC":(36,39), "UTAH":(28,24), 
          "ORST":(56,37), "ORE":(34,20), "STAN":(41,38), "CAL":(19,13), "COLO":(31,7), 
          "ARIZ":(69,28), "WASH":(15,28), "ISU":(28,26)},
    2019: {"NMSU":(58,7), "UNCO":(59,17), "HOU":(31,24), "UCLA":(63,67), "UTAH":(13,38), 
            "ASU":(34,38), "COLO":(41,10), "ORE":(35,37), "CAL":(20,33), "STAN":(49,22), 
            "ORST":(54,53), "WASH":(13,31), "AFA":(21,31) },
    2020: {"ORST":(38,28), "ORE":(29,43), "USC":(13,38), "UTAH":(28,45)},
    2021: {"USU":(23,26), "PORT ST.":(44,24), "USC":(14,45), "UTAH":(13,24), "CAL":(21,6),
          "ORST":(31,24), "STAN":(34,31), "BYU":(19,21), "ASU":(34,21), "ORE":(24,38), 
          "ARIZ":(44,18), "WASH":(40,13), "CMU":(21,24)} }

#(a)

def game_scores(games,opponent):
    """game_scores  takes the game list (similar to wsu_games above) and an opponent team name (e.g., “USC” ) as input and returns the list of the game scores that WSU played against the given opponent team. """
    scores = []
    # iterate over game logs for each year
    for log in games.values():
        #iterate over team,score pairs
        for (team,score) in log.items():
            #if the team is same as the given opponent team, add the score to output
            if team == opponent:
                scores.append(score)
    return scores

from functools import reduce

def game_scores2(games,opponent):
    """Alternative implementation of game_scores using higher order functions."""
    #helper functions
    get_second = lambda t : t[1]
    helper_filter = lambda t : ( t[0] == opponent)
    get_score = lambda log :  list(map(get_second, filter(helper_filter,log.items())))
    return reduce(lambda x,y: x+y ,map(get_score , wsu_games.values()))

#Step 1 - Write a helper function (get_score) that will take a log and return the score for the opponent team from that log. 
# Example: 
#   get_score({"WYO":(41,19), "SJSU":(31,0),  "EWU":(59,24), "USC":(36,39), "UTAH":(28,24), "ORST":(56,37), "ORE":(34,20), "STAN":(41,38), "CAL":(19,13), "COLO":(31,7), "ARIZ":(69,28), "WASH":(15,28), "ISU":(28,26)})
# will return
# (36,39) for "USC"

#Step 2 - get score from each log in the data using get_score function and map. 


def game_scores3(games,opponent):
    """Alternative implementation of game_scores using higher order functions."""
    #helper functions
    get_score = lambda log :  log.get(opponent)
    return list(filter(lambda t: t is not None, map(get_score , wsu_games.values())))

#(b) wins_by_year

def wins_by_year(games):
    """ Assume you would like to find the number of games WSU won each year.  “wins_by_year” takes the WSU game data as input, 
    and it returns a list of tuples where each tuple includes the year and the number wins (of WSU team) in that year."""
    #initialize the dictionary for storing the counts.
    win_counts = {}
    # iterate over year, log pairs
    for year,log in games.items():
        # iterate over each score in a log
        for score in log.values():
            # if score is a winning score, increment the count for the current year in the dictionary
            if score[0] > score[1]:
                win_counts[year] = win_counts.get(year,0) + 1
    # convert the dictionary to a list of tuples
    return list(win_counts.items())   


from functools import reduce
def wins_by_year(wsu_games):
    # helper functions
    # given a score tuple returns True is it is a winning score, otherwise it returns False.
    winner = lambda t : t[0] > t[1]
    # combining function for reduce; increments the base if t is a winning score. 
    fold_helper = lambda base,t : base+1 if winner(t) else base
    # helper for map; counts the winning games in the log part of a (year,log) tuple. 
    map_helper = lambda d : (d[0], reduce(fold_helper, d[1].values(), 0))

    return list(map(map_helper, wsu_games.items()))


    


