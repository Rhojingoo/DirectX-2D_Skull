#pragma once
#include <queue>
#include <vector>
#include "Monster.h"
#include "Monster_ObjPool.h"

namespace jk
{
    class Stage_Manager 
    {
    public:
        Stage_Manager(Monster_ObjPool* set) { _OBJ_POOL = set; }
        ~Stage_Manager() {};
        
        void addMonsterGroup(const std::vector<Monster*>& group)   { monsterGroups.push(group);  }

        void spawnNextGroup() 
        {
            if (!monsterGroups.empty())
            {
                std::vector<Monster*> currentGroup = monsterGroups.front();
                monsterGroups.pop();
                // currentGroup을 게임 환경에 배치하는 로직 추가...
            }
            else           
                currentState = StageState::StageFinished;         
        }

        enum class StageState 
        {
            SpawningMonsters,
            InCombat,
            WaitingForNextGroup,
            StageFinished
        };


        void update() 
        {
            switch (currentState) 
            {
                case StageState::SpawningMonsters:
                    spawnNextGroup();
                    currentState = StageState::InCombat;
                    break;

                case StageState::InCombat:
                    // 몬스터와의 전투 로직...
                    break;

                case StageState::WaitingForNextGroup:
                    currentState = StageState::SpawningMonsters;
                    break;

                case StageState::StageFinished:
                    // 스테이지 완료 로직...
                    break;
            }
        }


    private:
        std::queue<std::vector<Monster*>> monsterGroups;
        StageState currentState = StageState::SpawningMonsters;
        Monster_ObjPool* _OBJ_POOL = nullptr;
    };
}
