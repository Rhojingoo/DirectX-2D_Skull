#pragma once
#include "Include_Common.h"
#include "Monster.h"

namespace jk
{
    class Monster_ObjPool
    {
    public:
        Monster_ObjPool(int StageSelect, int NumberofMonsters, int Lots_of_monsters, int Number_of_Big_Monsters)
            : capacity1(Lots_of_monsters), capacity2(NumberofMonsters), capacity3(Number_of_Big_Monsters)
        {          
            if (StageSelect == 1)
            {
                //���� ����
                for (int i = 0; i < Lots_of_monsters; ++i)
                {
                    Monster_warrior* _warrior = new Monster_warrior();
                    _warrior->SetName(L"Monster");
                    warrior_pool.push_back(_warrior);
                }
              
                //���� ����
                for (int i = 0; i < NumberofMonsters; ++i)
                {
                    wizard_pool.push_back(new Stone_wizard());
                }
                for (int i = 0; i < NumberofMonsters; ++i)
                {
                    GreenTree_pool.push_back(new Monster_GreenTree());
                }
                for (int i = 0; i < NumberofMonsters; ++i)
                {
                    Blossom_pool.push_back(new Monster_BlossomEnt());
                }

                //ū���͵�
                for (int i = 0; i < Number_of_Big_Monsters; ++i)
                {
                    BigEnt_pool.push_back(new Monster_BigEnt());
                }
                for (int i = 0; i < Number_of_Big_Monsters; ++i)
                {
                    Hammer_pool.push_back(new Monster_Hammer());
                }
      
            }

            if (StageSelect == 2)
            {
                for (int i = 0; i < Lots_of_monsters; ++i)
                {
                    Goldwarrior_pool.push_back(new Monster_Goldwarrior());
                }

                //���� ����
                for (int i = 0; i < NumberofMonsters; ++i)
                {
                    wizard_pool.push_back(new Stone_wizard());
                }


                for (int i = 0; i < Number_of_Big_Monsters; ++i)
                {
                    GoldHammer_pool.push_back(new Monster_GoldHammer());
                }
            }
        }

        virtual ~Monster_ObjPool()
        {      
            //for (Monster* monster : warrior_pool)
            //{
            //    if (monster == nullptr)
            //        continue;

            //    delete monster;
            //}

            int a = 0;
            for (Monster_warrior* monster : warrior_pool)
            {
                if (monster == nullptr)
                    continue;
                a++;
                delete monster;
                monster = nullptr;
            }

            for (Stone_wizard* monster : wizard_pool)
            {
                if (monster == nullptr)
                    continue;
                delete monster;
            }

            for (Monster_GreenTree* monster : GreenTree_pool)
            {
                if (monster == nullptr)
                    continue;
                delete monster;
            }

            for (Monster_BlossomEnt* monster : Blossom_pool)
            {
                if (monster == nullptr)
                    continue;
                delete monster;
            }

            for (Monster_BigEnt* monster : BigEnt_pool)
            {
                if (monster == nullptr)
                    continue;
                delete monster;
            }

            for (Monster_Hammer* monster : Hammer_pool)
            {
                if (monster == nullptr)
                    continue;
                delete monster;
            }

            for (Monster_Goldwarrior* monster : Goldwarrior_pool)
            {
                if (monster == nullptr)
                    continue;
                delete monster;
            }

            for (Monster_GoldHammer* monster : GoldHammer_pool)
            {
                if (monster == nullptr)
                    continue;
                delete monster;
            }
        }

        #pragma region ���� �ޱ��Լ�

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
        #pragma endregion  

        #pragma region ���� �����Լ�
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
        int capacity1;
        int capacity2;
        int capacity3;


    };
}