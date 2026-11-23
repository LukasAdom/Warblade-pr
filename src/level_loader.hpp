#pragma once                        

#include <string>                  
#include <vector>                   

struct LevelEvent {                
    float timestamp = 0.0f;         
    std::string action;      // can add actions here like spawning      
    std::string target;      // Name or id of enemy       
    float x = 0.0f;                 
    float y = 0.0f;                 
    float statSpeed = 0.0f;
    int statDamage = 0;
    int statHealth = 0;      // Maybe change statNames ? Also can add movement types


    LevelEvent() = default;
};


std::vector<LevelEvent> LoadLevelEvents(const std::string& filePath); 
