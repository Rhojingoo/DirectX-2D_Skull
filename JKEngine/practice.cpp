//#pragma once
//#include "Include_Common.h"
//#include "Monster.h"
//
//namespace jk
//{
//    class Monster_ObjManager
//    {
//    public:
//        Monster_ObjManager(int totalSize, int NumberofMonsters, int Number_of_Big_Monsters)
//            : capacity(totalSize)
//        {
//            for (int i = 0; i < NumberofMonsters; ++i)
//            {
//                pool.push_back(new Monster_warrior());
//            }
//            for (int i = 0; i < NumberofMonsters; ++i)
//            {
//                pool.push_back(new Stone_wizard());
//            }
//            for (int i = 0; i < NumberofMonsters; ++i)
//            {
//                pool.push_back(new Monster_GreenTree());
//            }
//            for (int i = 0; i < NumberofMonsters; ++i)
//            {
//                pool.push_back(new Monster_BlossomEnt());
//            }
//            for (int i = 0; i < NumberofMonsters; ++i)
//            {
//                pool.push_back(new Monster_Goldwarrior());
//            }
//
//
//            //큰몬스터들
//            for (int i = 0; i < Number_of_Big_Monsters; ++i)
//            {
//                pool.push_back(new Monster_BigEnt());
//            }
//            for (int i = 0; i < Number_of_Big_Monsters; ++i)
//            {
//                pool.push_back(new Monster_Hammer());
//            }
//            for (int i = 0; i < Number_of_Big_Monsters; ++i)
//            {
//                pool.push_back(new Monster_GoldHammer());
//            }
//        }
//
//        virtual ~Monster_ObjManager()
//        {
//            for (Monster* monster : pool)
//            {
//                delete monster;
//            }
//        }
//
//        Monster* Get_Monster()
//        {
//            if (!pool.empty())
//            {
//                Monster* monster = pool.back();
//                pool.pop_back();
//                return monster;
//            }
//            return nullptr;
//        }
//
//        void Return_Monster(Monster* monster)
//        {
//            if (pool.size() < capacity)
//                pool.push_back(monster);
//            else
//                delete monster;
//        }
//
//
//    private:
//        std::vector<Monster*> pool;
//        //std::vector<Monster_warrior*> warrior_pool;
//        //std::vector<Stone_wizard*> wizard_pool;
//        //std::vector<Monster_GreenTree*> GreenTree_pool;
//        //std::vector<Monster_BlossomEnt*> Blossom_pool;
//        //std::vector<Monster_BigEnt*> BigEnt_pool;
//        //std::vector<Monster_Hammer*> Hammer_pool;
//
//    private:
//        //std::vector<Monster_Goldwarrior*> Goldwarrior_pool;
//        //std::vector<Monster_GoldHammer*> GoldHammer_pool;
//        int capacity;
//
//    };
//}
