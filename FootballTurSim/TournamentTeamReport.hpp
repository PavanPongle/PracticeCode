#ifndef _TournamentTeamReport_
#define _TournamentTeamReport_

#include <memory>

class TournamentTeamReport
{
    std::string m_teamName;
    uint32_t m_points = 0;
    uint32_t m_gamesWonCount = 0;
    uint32_t m_gamesDrawnCount = 0;
    uint32_t m_gamesLostCount = 0;
    uint32_t m_totalGoalsScored = 0;
    uint32_t m_totalGoalsConceded = 0;
    std::map<uint32_t, double> m_mapGoalDistribution;

public:
    ~TournamentTeamReport() noexcept
    {
    }

    inline std::string GetTeamName() { return m_teamName; };
    inline uint32_t GetPoints() {
        return m_points;
    }
    inline uint32_t GetGamesWonCount() {
        return m_gamesWonCount;
    }
    inline uint32_t GetGamesDrawnCount() {
        return m_gamesDrawnCount;
    }
    inline uint32_t GetGamesLostCount() {
        return m_gamesLostCount;
    }
    inline uint32_t GetTotalGoalsScored() {
        return m_totalGoalsScored;
    }
    inline uint32_t GetTotalGoalsConceded() {
        return m_totalGoalsConceded;
    }
    inline std::map<uint32_t, double> GetGoalDistribution() {
        return m_mapGoalDistribution;
    }

    inline void SetTeamName(const std::string& val) { m_teamName.assign(val); };
    inline void AddPoints(uint32_t val) {
        m_points += val;
    }
    inline void IncGamesWonCount() {
        ++m_gamesWonCount;
    }
    inline void IncGamesDrawnCount() {
        ++m_gamesDrawnCount;
    }
    inline void IncGamesLostCount() {
        ++m_gamesLostCount;
    }
    inline void AddTotalGoalsScored(uint32_t val) {
        m_totalGoalsScored += val;
    }
    inline void AddTotalGoalsConceded(uint32_t val) {
        m_totalGoalsConceded += val;
    }

    TournamentTeamReport(std::string& name, const std::map<uint32_t, double>& gd) : m_teamName(name), m_mapGoalDistribution(gd) {}

    TournamentTeamReport(const TournamentTeamReport& rhs) = delete;

    TournamentTeamReport& operator= (const TournamentTeamReport& rhs) = delete;

    TournamentTeamReport& operator= (TournamentTeamReport&& rhs) noexcept
    {
        std::cout << "move assig called" << std::endl;
		return *this;
    }

    TournamentTeamReport(TournamentTeamReport&& rhs) noexcept
    {
        std::cout << "move const called" << std::endl;
    }

    constexpr bool operator < (const TournamentTeamReport& r) const
    {
        return r.m_points < m_points;
    }

    //bool operator==(const TournamentTeamReport& rhs)
    //{
    //    if (m_teamName == rhs.m_teamName)
    //        return true;
    //    else
    //        return false;
    //}
};

template <>
struct std::greater<std::shared_ptr<TournamentTeamReport>>
{
    bool operator()(const std::shared_ptr<TournamentTeamReport>& lhs, const std::shared_ptr<TournamentTeamReport>& rhs) const
    {
        return lhs->GetPoints() > rhs->GetPoints();
    }
};

std::ofstream& operator<< (std::ofstream& fileStream, const std::shared_ptr<TournamentTeamReport>& obj)
{
    fileStream << obj->GetTeamName() << "," << obj->GetPoints() << "," << obj->GetGamesWonCount() << "," << obj->GetGamesDrawnCount() << "," << obj->GetGamesLostCount() << "," << obj->GetTotalGoalsScored() << "," << obj->GetTotalGoalsConceded() << std::endl;

    return fileStream;
}

std::ofstream& operator<< (std::ofstream& fileStream, const std::vector<std::shared_ptr<TournamentTeamReport>>& obj)
{
    for (auto it : obj)
        fileStream << it;

    return fileStream;
}

#endif