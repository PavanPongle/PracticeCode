
#include "gtest/gtest.h"

#include "CSV.hpp"
#include "GameSim.hpp"
#include "TournamentTeamReport.hpp"

namespace my {
	namespace project {
		namespace {

			// The fixture for testing class Foo.
			class FooTest : public ::testing::Test {
			protected:
				// You can remove any or all of the following functions if their bodies would
				// be empty.
				CSVReadWrite<MeanGoalPerGame>* obj;
				std::vector<std::shared_ptr<TournamentTeamReport>> result;

				FooTest() {
					// You can do set-up work for each test here.

					obj = new CSVReadWrite<MeanGoalPerGame>("MeanGoalPerGame.csv/MeanGoalPerGame.csv", 20);
					obj->ReadCSV();
					result.reserve(obj->GetRowCounts());

					for (int i = 0; i < obj->GetRowCounts(); ++i)
					{
						result.emplace_back(std::make_shared<TournamentTeamReport>(obj->GetRowAt(i).GetTeamName(), GetGoalDistribution(obj->GetRowAt(i).GetMean())));
					}

					for (int i = 0; i < obj->GetRowCounts(); ++i)
					{
						for (int j = 0; j < obj->GetRowCounts() && i != j; ++j)
						{
							GameSim::PlayMatches(result[i], result[j]);
						}
					}

					std::sort(result.begin(), result.end(), std::greater<std::shared_ptr<TournamentTeamReport>>());

					CSVReadWrite<std::vector<std::shared_ptr<TournamentTeamReport>>> obj2(
						"TournamentRes.csv",
						{ "TeamName","Points", "GamesWonCount", "GamesDrawnCount", "GamesLostCount", "TotalGoalsScored", "TotalGoalsConceded" });
					obj2.WriteCSV(result);
				}

				~FooTest() override {
					// You can do clean-up work that doesn't throw exceptions here.
					delete obj;
				}

				// If the constructor and destructor are not enough for setting up
				// and cleaning up each test, you can define the following methods:

				void SetUp() override {
					// Code here will be called immediately after the constructor (right
					// before each test).
				}

				void TearDown() override {
					// Code here will be called immediately after each test (right
					// before the destructor).
				}
			};

			
			TEST_F(FooTest, TestCSVRead) {
				EXPECT_EQ(20, obj->GetRowCounts());
				EXPECT_TRUE("MeanGoalPerGame" == obj->GetColName().at(1));
				EXPECT_EQ(1.92105263157895, obj->GetRowAt(0).GetMean());
			}

			TEST_F(FooTest, TestGameSimGetPoints) {
				ASSERT_EQ(MatchStatus::Draw, GameSim::GetPoints(0, 0));
				ASSERT_EQ(MatchStatus::Win, GameSim::GetPoints(1, 0));
				ASSERT_EQ(MatchStatus::Loss, GameSim::GetPoints(0, 1));
			}

			TEST_F(FooTest, TestFileCreated) {

				ASSERT_EQ(MatchStatus::Draw, GameSim::GetPoints(0, 0));
				ASSERT_EQ(MatchStatus::Win, GameSim::GetPoints(1, 0));
				ASSERT_EQ(MatchStatus::Loss, GameSim::GetPoints(0, 1));

				std::ifstream infile;
				infile.open("TournamentRes.csv");
				ASSERT_EQ(true, infile.is_open());


			}

		}  // namespace
	}  // namespace project
}  // namespace my

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

