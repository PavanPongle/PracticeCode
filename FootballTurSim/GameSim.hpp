#ifndef _GameSim_
#define _GameSim_

#include <set>
#include <vector>
#include <string>
#include <random>
#include <map>

#include "TournamentTeamReport.hpp"

/**
 * Computes the goal cumulative probability distribution.
 * Note:
 * - Allowed goals per match vary in the range [0, 5] (inclusive)
 * - std::map::key ----> Goal count
 * - std::map::value --> Cumulative probability
 *
 * @param meanGoalPerMatch   Arithmetic mean goal per match.
 * @return                   Probability distribution map.
 */
std::map<uint32_t, double> GetGoalDistribution(const double meanGoalPerMatch)
{
	constexpr auto lbdFactorial{ [](const uint32_t factorial)
								{
								  auto result{1u};
								  for (uint32_t idx = 1u; idx <= factorial; ++idx)
								  {
									result *= idx;
								  }
								  return result;
								} };

	constexpr auto maxGoals{ 5u };

	auto prevProbability{ 0.0 };
	std::map<uint32_t, double> goalDist;
	for (uint32_t i = 0u; i < maxGoals; ++i)
	{
		const auto probPoisson{ (std::pow(meanGoalPerMatch, i) * std::exp(-1 * meanGoalPerMatch)) / lbdFactorial(i) };

		goalDist.emplace(std::make_pair(i, (probPoisson + prevProbability)));
		prevProbability += probPoisson;
	}

	goalDist.emplace(std::make_pair(maxGoals, 1.0));

	return goalDist;
}

std::random_device rand_dev;
std::mt19937 generator(rand_dev());
std::uniform_real_distribution<double> dist(0.0, 1.0);
double randNum[] = { dist(generator), dist(generator) };

enum class MatchStatus
{
	Loss = 0u,
	Draw = 1u,
	Win = 3u
};

class GameSim
{
public:
	static auto SimAlgo(double randNum, const std::map< uint32_t, double>& mapGoalDistribution)
	{
		for (auto itr = mapGoalDistribution.cbegin(); itr != mapGoalDistribution.cend(); ++itr)
		{
			if (randNum < itr->second)
				return itr->first;
		}

		return 5u;
	}

	static enum MatchStatus GetPoints(uint32_t goalsScored1, uint32_t goalsScored2)
	{
		if (goalsScored1 == goalsScored2)
			return MatchStatus::Draw;
		if (goalsScored1 > goalsScored2)
			return MatchStatus::Win;
		return MatchStatus::Loss;
	}

	static void WinBy(std::shared_ptr<TournamentTeamReport>& itr, uint32_t goalsScored1, uint32_t goalsScored2)
	{
		itr->IncGamesWonCount();
		itr->AddPoints((uint32_t)MatchStatus::Win);
		itr->AddTotalGoalsScored(goalsScored1);
		itr->AddTotalGoalsConceded(goalsScored2);
	}

	static void LossBy(std::shared_ptr<TournamentTeamReport>& itr, uint32_t goalsScored1, uint32_t goalsScored2)
	{
		itr->IncGamesLostCount();
		itr->AddPoints((uint32_t)MatchStatus::Loss);
		itr->AddTotalGoalsScored(goalsScored1);
		itr->AddTotalGoalsConceded(goalsScored2);
	}

	static void DrawBy(std::shared_ptr<TournamentTeamReport>& itr, uint32_t goalsScored)
	{
		itr->IncGamesDrawnCount();
		itr->AddPoints((uint32_t)MatchStatus::Draw);
		itr->AddTotalGoalsScored(goalsScored);
		itr->AddTotalGoalsConceded(goalsScored);
	}

	static void Update(std::shared_ptr<TournamentTeamReport>& team1, uint32_t goalsScored1, std::shared_ptr<TournamentTeamReport>& team2, uint32_t goalsScored2)
	{
		MatchStatus status = GetPoints(goalsScored1, goalsScored2);

		if (MatchStatus::Win == status)
		{
			WinBy(team1, goalsScored1, goalsScored2);
			LossBy(team2, goalsScored2, goalsScored1);
		}
		else if (MatchStatus::Loss == status)
		{
			WinBy(team2, goalsScored2, goalsScored1);
			LossBy(team1, goalsScored1, goalsScored2);
		}
		else
		{
			DrawBy(team1, goalsScored1);
			DrawBy(team2, goalsScored2);
		}
	}

	static void PlayMatches(std::shared_ptr<TournamentTeamReport>& team1, std::shared_ptr<TournamentTeamReport>& team2)
	{
		for (int i = 0; i < 2; ++i)
		{
			auto goalsScored1 = SimAlgo(randNum[i], team1->GetGoalDistribution());
			auto goalsScored2 = SimAlgo(randNum[i], team2->GetGoalDistribution());

			Update(team1, goalsScored1, team2, goalsScored2);
		}
	}

};

std::ostream& operator << (std::ostream& os, TournamentTeamReport* const obj)
{
	std::cout.fill(' ');
	std::cout.width(35);
	os << obj->GetTeamName() << " ";
	std::cout.width(4);
	os << obj->GetPoints() << " ";
	std::cout.width(4);
	os << obj->GetGamesWonCount() << " ";
	std::cout.width(4);
	os << obj->GetGamesDrawnCount() << " ";
	std::cout.width(4);
	os << obj->GetGamesLostCount() << " ";
	std::cout.width(4);
	os << obj->GetTotalGoalsScored() << " ";
	std::cout.width(4);
	os << obj->GetTotalGoalsConceded();
	os << std::endl;
	return os;
}


#endif
