#pragma once
#include "../Engine_SOURCE/jkSceneManager.h"
#include "Monster.h"
#include "Monster_warrior.h"
#include "Stone_wizard.h"
#include "Monster_GreenTree.h"
#include "Monster_BlossomEnt.h"
#include "Monster_BigEnt.h"
#include "Monster_Hammer.h"
#include "Monster_Goldwarrior.h"
#include "Monster_GoldHammer.h"
#include "Monster_LionSpear.h"
#include "Monster_LionWarrior.h"
#include "Monster_LionWizard.h"

namespace jk
{
    class Monster_ObjManager
    {
    public:
        Monster_ObjManager(int StageSelect, int NumberofMonsters, int Lots_of_monsters, int Number_of_Big_Monsters)
            : capacity1(Lots_of_monsters), capacity2(NumberofMonsters), capacity3(Number_of_Big_Monsters)
        {          
            if (StageSelect == 1)
            {
                //많은 몬스터
                for (int i = 0; i < Lots_of_monsters; ++i)
                {
                    Monster_warrior* newMonster = new Monster_warrior();   
                    newMonster->Initialize();
                    SceneManager::GetInitializeScene()->AddMonster(newMonster);
                    newMonster->SetState(GameObject::eState::Paused);
                    warrior_pool.push_back(newMonster);
                }
              
                //작은 몬스터
                for (int i = 0; i < NumberofMonsters; ++i)
                {
                    Stone_wizard* newMonster = new Stone_wizard();
                    newMonster->Initialize();
                    SceneManager::GetInitializeScene()->AddMonster(newMonster);
                    newMonster->SetState(GameObject::eState::Paused);
                    wizard_pool.push_back(newMonster);
                }
                for (int i = 0; i < NumberofMonsters; ++i)
                {
                    Monster_GreenTree* newMonster = new Monster_GreenTree();
                    newMonster->Initialize();
                    SceneManager::GetInitializeScene()->AddMonster(newMonster);
                    newMonster->SetState(GameObject::eState::Paused);
                    GreenTree_pool.push_back(newMonster);
                }
                for (int i = 0; i < NumberofMonsters; ++i)
                {
                    Monster_BlossomEnt* newMonster = new Monster_BlossomEnt();
                    newMonster->Initialize();
                    SceneManager::GetInitializeScene()->AddMonster(newMonster);
                    newMonster->SetState(GameObject::eState::Paused);
                    Blossom_pool.push_back(newMonster);
                }

                //큰몬스터들
                for (int i = 0; i < Number_of_Big_Monsters; ++i)
                {
                    Monster_BigEnt* newMonster = new Monster_BigEnt();
                    newMonster->Initialize();
                    SceneManager::GetInitializeScene()->AddMonster(newMonster);
                    newMonster->SetState(GameObject::eState::Paused);
                    BigEnt_pool.push_back(newMonster);
                }
                for (int i = 0; i < Number_of_Big_Monsters; ++i)
                {
                    Monster_Hammer* newMonster = new Monster_Hammer();
                    newMonster->Initialize();
                    SceneManager::GetInitializeScene()->AddMonster(newMonster);
                    newMonster->SetState(GameObject::eState::Paused);
                    Hammer_pool.push_back(newMonster);
                }
      
            }

            if (StageSelect == 2)
            {

                for (int i = 0; i < Lots_of_monsters; ++i)
                {
                    Monster_Goldwarrior* newMonster = new Monster_Goldwarrior();
                    newMonster->Initialize();
                    SceneManager::GetInitializeScene()->AddMonster(newMonster);
                    newMonster->SetState(GameObject::eState::Paused);
                    Goldwarrior_pool.push_back(newMonster);
                }

                //작은 몬스터
                for (int i = 0; i < NumberofMonsters; ++i)
                {
                    Stone_wizard* newMonster = new Stone_wizard();
                    newMonster->Initialize();
                    SceneManager::GetInitializeScene()->AddMonster(newMonster);
                    newMonster->SetState(GameObject::eState::Paused);
                    wizard_pool.push_back(newMonster);
                }

                //덩어리몬스터
                for (int i = 0; i < Number_of_Big_Monsters; ++i)
                {
                    Monster_GoldHammer* newMonster = new Monster_GoldHammer();
                    newMonster->Initialize();
                    SceneManager::GetInitializeScene()->AddMonster(newMonster);
                    newMonster->SetState(GameObject::eState::Paused);
                    GoldHammer_pool.push_back(newMonster);
                }

                for (int i = 0; i < Number_of_Big_Monsters; ++i)
                {
                    Monster_LionSpear* newMonster = new Monster_LionSpear();
                    newMonster->Initialize();
                    SceneManager::GetInitializeScene()->AddMonster(newMonster);
                    newMonster->SetState(GameObject::eState::Paused);
                    LionSpear_pool.push_back(newMonster);
                }

                for (int i = 0; i < Number_of_Big_Monsters; ++i)
                {
                    Monster_LionWarrior* newMonster = new Monster_LionWarrior();
                    newMonster->Initialize();
                    SceneManager::GetInitializeScene()->AddMonster(newMonster);
                    newMonster->SetState(GameObject::eState::Paused);
                    LionWarrior_pool.push_back(newMonster);
                }
                for (int i = 0; i < Number_of_Big_Monsters; ++i)
                {
                    Monster_LionWizard* newMonster = new Monster_LionWizard();
                    newMonster->Initialize();
                    SceneManager::GetInitializeScene()->AddMonster(newMonster);
                    newMonster->SetState(GameObject::eState::Paused);
                    LionWizard_pool.push_back(newMonster);
                }

            }
        }

        virtual ~Monster_ObjManager()
        {      
            for (Monster_warrior* monster : warrior_pool)
            {
                if (monster == nullptr)
                    continue;


                //delete monster;
                //monster = nullptr;
                warrior_pool.clear();
            }

            for (Stone_wizard* monster : wizard_pool)
            {
                if (monster == nullptr)
                    continue;

                //delete monster;
                wizard_pool.clear();
            }

            for (Monster_GreenTree* monster : GreenTree_pool)
            {
                if (monster == nullptr)
                    continue;

                GreenTree_pool.clear();

                //delete monster;
            }

            for (Monster_BlossomEnt* monster : Blossom_pool)
            {
                if (monster == nullptr)
                    continue;

               Blossom_pool.clear();

               //delete monster;
            }

            for (Monster_BigEnt* monster : BigEnt_pool)
            {
                if (monster == nullptr)
                    continue;

               BigEnt_pool.clear();

                //delete monster;
            }

            for (Monster_Hammer* monster : Hammer_pool)
            {
                if (monster == nullptr)
                    continue;

               Hammer_pool.clear();

                //delete monster;
            }

            for (Monster_Goldwarrior* monster : Goldwarrior_pool)
            {
                if (monster == nullptr)
                    continue;

                Goldwarrior_pool.clear();

               //delete monster;
            }

            for (Monster_GoldHammer* monster : GoldHammer_pool)
            {
                if (monster == nullptr)
                    continue;

               GoldHammer_pool.clear();

                //delete monster;
            }
            //
            for (Monster_LionSpear* monster : LionSpear_pool)
            {
                if (monster == nullptr)
                    continue;


                LionSpear_pool.clear();

               //delete monster;
            }

            for (Monster_LionWarrior* monster : LionWarrior_pool)
            {
                if (monster == nullptr)
                    continue;

              LionWarrior_pool.clear();

              // delete monster;
            }

            for (Monster_LionWizard* monster : LionWizard_pool)
            {
                if (monster == nullptr)
                    continue;

              LionWizard_pool.clear();

              // delete monster;
            }
        }


        #pragma region 몬스터 받기함수

                #pragma region stage1
                   Monster_warrior* Get_Monster_warrior()
                   {
                       if (!warrior_pool.empty())
                       {
                           Monster_warrior* monster = warrior_pool.back();
                           warrior_pool.pop_back();
                           return monster;
                       }
                       return nullptr;
                   }

                   Stone_wizard* Get_wizard()
                   {
                       if (!wizard_pool.empty())
                       {
                           Stone_wizard* monster = wizard_pool.back();
                           wizard_pool.pop_back();
                           return monster;
                       }
                       return nullptr;
                   }


                   Monster_GreenTree* Get_GreenTree()
                   {
                       if (!GreenTree_pool.empty())
                       {
                           Monster_GreenTree* monster = GreenTree_pool.back();
                           GreenTree_pool.pop_back();
                           return monster;
                       }
                       return nullptr;
                   }


                   Monster_BlossomEnt* Get_Blossom()
                   {
                       if (!Blossom_pool.empty())
                       {
                           Monster_BlossomEnt* monster = Blossom_pool.back();
                           Blossom_pool.pop_back();
                           return monster;
                       }
                       return nullptr;
                   }

                   Monster_BigEnt* Get_BigEnt()
                   {
                       if (!BigEnt_pool.empty())
                       {
                           Monster_BigEnt* monster = BigEnt_pool.back();
                           BigEnt_pool.pop_back();
                           return monster;
                       }
                       return nullptr;
                   }

                   Monster_Hammer* Get_Hammer()
                   {
                       if (!Hammer_pool.empty())
                       {
                           Monster_Hammer* monster = Hammer_pool.back();
                           Hammer_pool.pop_back();
                           return monster;
                       }
                       return nullptr;
                   }
            #pragma endregion  

                #pragma region stage2
                   Monster_Goldwarrior* Get_Goldwarrior()
                   {
                       if (!Goldwarrior_pool.empty())
                       {
                           Monster_Goldwarrior* monster = Goldwarrior_pool.back();
                           Goldwarrior_pool.pop_back();
                           return monster;
                       }
                       return nullptr;
                   }

                   Monster_GoldHammer* Get_GoldHammer()
                   {
                       if (!GoldHammer_pool.empty())
                       {
                           Monster_GoldHammer* monster = GoldHammer_pool.back();
                           GoldHammer_pool.pop_back();
                           return monster;
                       }
                       return nullptr;
                   }    

                   Monster_LionSpear* Get_LionSpear()
                   {
                       if (!LionSpear_pool.empty())
                       {
                           Monster_LionSpear* monster = LionSpear_pool.back();
                           LionSpear_pool.pop_back();
                           return monster;
                       }
                       return nullptr;
                   }

                   Monster_LionWarrior* Get_LionWarrior()
                   {
                       if (!LionWarrior_pool.empty())
                       {
                           Monster_LionWarrior* monster = LionWarrior_pool.back();
                           LionWarrior_pool.pop_back();
                           return monster;
                       }
                       return nullptr;
                   }

                   Monster_LionWizard* Get_LionWizard()
                   {
                       if (!LionWizard_pool.empty())
                       {
                           Monster_LionWizard* monster = LionWizard_pool.back();
                           LionWizard_pool.pop_back();
                           return monster;
                       }
                       return nullptr;
                   }

                #pragma endregion  
        #pragma endregion  
     private:

        #pragma region 몬스터 리턴함수
                     void Return_Monster_warrior(Monster_warrior* monster)
                     {
                         if (warrior_pool.size() < capacity1)
                             warrior_pool.push_back(monster);
                         else
                             delete monster;
                     }

                     void Return_wizard(Stone_wizard* monster)
                     {
                         if (wizard_pool.size() < capacity2)
                             wizard_pool.push_back(monster);
                         else
                             delete monster;
                     }

                     void Return_GreenTree(Monster_GreenTree* monster)
                     {
                         if (GreenTree_pool.size() < capacity2)
                             GreenTree_pool.push_back(monster);
                         else
                             delete monster;
                     }

                     void Return_Blossom(Monster_BlossomEnt* monster)
                     {
                         if (Blossom_pool.size() < capacity2)
                             Blossom_pool.push_back(monster);
                         else
                             delete monster;
                     }

                     void Return_BigEnt(Monster_BigEnt* monster)
                     {
                         if (BigEnt_pool.size() < capacity2)
                             BigEnt_pool.push_back(monster);
                         else
                             delete monster;
                     }

                     void Return_Hammer(Monster_Hammer* monster)
                     {
                         if (Hammer_pool.size() < capacity2)
                             Hammer_pool.push_back(monster);
                         else
                             delete monster;
                     }

                     void Return_Goldwarrior(Monster_Goldwarrior* monster)
                     {
                         if (Goldwarrior_pool.size() < capacity2)
                             Goldwarrior_pool.push_back(monster);
                         else
                             delete monster;
                     }

                     void Return_GoldHammer(Monster_GoldHammer* monster)
                     {
                         if (GoldHammer_pool.size() < capacity2)
                             GoldHammer_pool.push_back(monster);
                         else
                             delete monster;
                     }
        #pragma endregion  

    private:
        std::vector<Monster*> pool;
        std::vector<Monster_warrior*> warrior_pool;
        std::vector<Stone_wizard*> wizard_pool;
        std::vector<Monster_GreenTree*> GreenTree_pool;
        std::vector<Monster_BlossomEnt*> Blossom_pool;
        std::vector<Monster_BigEnt*> BigEnt_pool;
        std::vector<Monster_Hammer*> Hammer_pool;


    private:
        std::vector<Monster_Goldwarrior*> Goldwarrior_pool;
        std::vector<Monster_GoldHammer*> GoldHammer_pool;
        std::vector<Monster_LionSpear*> LionSpear_pool;
        std::vector<Monster_LionWarrior*> LionWarrior_pool;
        std::vector<Monster_LionWizard*> LionWizard_pool;
        int capacity1;
        int capacity2;
        int capacity3;
    };
}
