// Standard headers.
#include <iostream>
#include <algorithm>

#include "CSV.hpp"
#include "GameSim.hpp"
#include "TournamentTeamReport.hpp"

int main()
{
	CSVReadWrite<MeanGoalPerGame> obj("MeanGoalPerGame.csv/MeanGoalPerGame.csv", 20);
	if (!obj.ReadCSV())
		return EXIT_FAILURE;

	std::vector<std::shared_ptr<TournamentTeamReport>> result;
	result.reserve(obj.GetRowCounts());

	for (int i = 0; i < obj.GetRowCounts(); ++i)
	{
		result.emplace_back(std::make_shared<TournamentTeamReport>(obj.GetRowAt(i).GetTeamName(), GetGoalDistribution(obj.GetRowAt(i).GetMean())));
	}

	for (int i = 0; i < obj.GetRowCounts(); ++i)
	{
		for (int j = 0; j < obj.GetRowCounts() && i != j; ++j)
		{
			GameSim::PlayMatches(result[i], result[j]);
		}
	}

	std::sort(result.begin(), result.end(), std::greater<std::shared_ptr<TournamentTeamReport>>());

	for (auto& it : result)
		std::cout << it.get();

	CSVReadWrite<std::vector<std::shared_ptr<TournamentTeamReport>>> obj2(
		"TournamentRes.csv",
		{"TeamName","Points", "GamesWonCount", "GamesDrawnCount", "GamesLostCount", "TotalGoalsScored", "TotalGoalsConceded"});
	obj2.WriteCSV(result);

	return EXIT_SUCCESS;
}
