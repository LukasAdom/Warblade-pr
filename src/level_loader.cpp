#include "level_loader.hpp"
#include "raylib-cpp.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

static bool SortByTime(const LevelEvent& a, const LevelEvent& b)
{
    return a.timestamp < b.timestamp;
}

std::vector<LevelEvent> LoadLevelEvents(const std::string& filePath)
{
    std::vector<LevelEvent> events;
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        TraceLog(LOG_WARNING, "Could not open level file: %s", path.c_str());
        return events;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        if (line.back() == '\r') line.pop_back();

        std::stringstream ss(line);
        std::string cols[8];

        for (int i = 0; i < 8; i++)
        {
            std::getline(ss, cols[i], ',');
        }

        LevelEvent ev;
        ev.timestamp = std::stof(cols[0]);
        ev.action = cols[1];
        ev.target = cols[2];
        ev.x = std::stof(cols[3]);
        ev.y = std::stof(cols[4]);
        ev.statSpeed = std::stof(cols[5]);
        ev.statDamage = std::stoi(cols[6]);
        ev.statHealth = std::stoi(cols[7]); 

        events.push_back(ev);
    }

    std::sort(events.begin(), events.end(), SortByTime);
    return events;
}
