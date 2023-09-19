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
        ~Stage_Manager() {
            while (!monsterGroups.empty()) 
            {
                std::vector<Monster*>& monsterGroup = monsterGroups.front();

                // ��� ���͸� �޸𸮿��� ����
                for (Monster* monster : monsterGroup) 
                {
                    delete monster;
                }
                // �ش� ���� �׷��� ť���� ����
                monsterGroups.pop();
            }
        };
        
        void addMonsterGroup(const std::vector<Monster*>& group)   { monsterGroups.push(group);  }

        void spawnNextGroup() 
        {
            if (!monsterGroups.empty())
            {
                std::vector<Monster*> currentGroup = monsterGroups.front();
                monsterGroups.pop();
                // currentGroup�� ���� ȯ�濡 ��ġ�ϴ� ���� �߰�...
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
                    // ���Ϳ��� ���� ����...
                    break;

                case StageState::WaitingForNextGroup:
                    currentState = StageState::SpawningMonsters;
                    break;

                case StageState::StageFinished:
                    // �������� �Ϸ� ����...
                    break;
            }
        }


    private:
        std::queue<std::vector<Monster*>> monsterGroups;
        StageState currentState = StageState::SpawningMonsters;
        Monster_ObjPool* _OBJ_POOL = nullptr;
    };
}
