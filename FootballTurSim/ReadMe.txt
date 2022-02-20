Problem description:
--------------------

- Football tournament simulation based on data extracted from the English Premiere League season
  2018/2019 (Ref.: MeanGoalPerGame.csv)

- Simulate a complete football tournament and compute the resulting table containing the below data
  for each team:
  + Total points
  + Total games won
  + Total games drawn
  + Total games lost
  + Total goals scored
  + Total goals conceded

- Football table format reference: https://www.premierleague.com/tables
----------------------------------------------------------------------------------------------------

Rules:
------

- One complete football tournament season is made up of a total of 38 games played per team, i.e.
  each team plays against each other twice

- Points per match:
  + Win ---> 3 points
  + Draw --> 1 point
  + Loss --> 0 points

- Football match simulation methodology:
  1. Load the accompanying MeanGoalPerGame.csv file, this provides the arithmetic mean of goals per
     match per team, based on the English Premiere League season 2018/2019
  2. For each team, based on the associated goal mean, compute the team goal distribution using the
     provided GetGoalDistribution(..) method (Ref.: main.cpp)
  3. The GetGoalDistribution(..) method will return an std::map<uint32_t, double> where:
    + The key represents the goals scored
    + The value represents the cumulative probability
    + For simplicity, we will limit the allowed goals per match between 0 and 5, inclusive
    + Therefore, for a mean goal per match of 1.5, the resulting goal distribution map will be:
      key | value
      ---------------
      0   | 0.223130
      1   | 0.557825
      2   | 0.808847
      3   | 0.934358
      4   | 0.981424
      5   | 1.000000
  4. In order to simulate a match between TeamA vs TeamB:
    4.1. Generate TeamA's goal distribution std::map
    4.2. Generate a uniform random number in the range [0.0, 1.0)
      * Hint: Use --> std::uniform_real_distribution<double> dist(0.0, 1.0);
    4.3. Making use of the generated random number (Rand_Num_X) and the team's goal distribution
         std::map, determine the number of goals scored. Using the above goal distribution std::map,
         the simulation alogorithm should follow the below pseudocode:
         if Rand_Num_X < 0.223130:
           goalsScored = 0
         else if Rand_Num_X < 0.557825:
           goalsScored = 1
         else if Rand_Num_X < 0.808847:
           goalsScored = 2
         else if Rand_Num_X < 0.934358:
           goalsScored = 3
         else if Rand_Num_X < 0.981424:
           goalsScored = 4
         else:
           goalsScored = 5
     4.4. Repeat steps 4.1 to 4.3 for TeamB
     4.5. Compute the resulting score
----------------------------------------------------------------------------------------------------

Expected output:
----------------

- CSV file with the below columns:
  + TeamName
  + Points
  + GamesWonCount
  + GamesDrawnCount
  + GamesLostCount
  + TotalGoalsScored
  + TotalGoalsConceded

- Teams should be sorted by their associated points in descending order, i.e. the first record
  should highlight the team who won the tournament
----------------------------------------------------------------------------------------------------

Expected deliverables:
----------------------

- Solution compilable via CMake. Kindly provide accompanying instructions, if necessary.

- Accompanying unit-tests using the test framework of your choice.
----------------------------------------------------------------------------------------------------
