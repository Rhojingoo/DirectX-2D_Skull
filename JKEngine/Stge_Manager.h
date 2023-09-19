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
        ~Stage_Manager() 
        {
            while (!monsterGroups.empty()) 
            {
                std::vector<Monster*>& monsterGroup = monsterGroups.front();
                // 모든 몬스터를 메모리에서 해제
                for (Monster* monster : monsterGroup) 
                {
                    if (monster == nullptr)
                        continue;

                    delete monster;
                }
                // 해당 몬스터 그룹을 큐에서 제거
                monsterGroups.pop();
            }
        };
        
        void addMonsterGroup(const std::vector<Monster*>& group)   { monsterGroups.push(group);  }

        void spawnNextGroup() 
        {
            if (!monsterGroups.empty())
            {
                std::vector<Monster*> currentGroup = monsterGroups.front();          

                for (Monster* monster : currentGroup)
                {
                    monster->SetState(GameObject::eState::Active);
                }
                monsterGroups.pop();
            }
            else
            {
                //currentState = StageState::StageFinished;  
            }       
        }

        //enum class StageState 
        //{
        //    SpawningMonsters,
        //    InCombat,
        //    WaitingForNextGroup,
        //    StageFinished
        //};
        //void update() 
        //{
        //    switch (currentState) 
        //    {
        //        case StageState::SpawningMonsters:
        //            spawnNextGroup();
        //            currentState = StageState::InCombat;
        //            break;
        //        case StageState::InCombat:
        //            // 몬스터와의 전투 로직...
        //            break;
        //        case StageState::WaitingForNextGroup:
        //            currentState = StageState::SpawningMonsters;
        //            break;
        //        case StageState::StageFinished:
        //            // 스테이지 완료 로직...
        //            break;
        //    }
        //}


    private:
        std::queue<std::vector<Monster*>> monsterGroups;
        Monster_ObjPool* _OBJ_POOL = nullptr;
       // StageState currentState = StageState::SpawningMonsters;
    };
}
