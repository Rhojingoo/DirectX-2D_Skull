#pragma once
#include "Include_Common.h"
#include "Mini_Boss.h"
#include <iostream>
#include <random>

namespace jk
{
    class MiniBoss_ObjCreate
    {
    public:
        MiniBoss_ObjCreate(int Number_of_mBoss)
        {
            for (int i = 0; i < Number_of_mBoss; ++i)
            {
                _Knight_male_pool.push_back(new Knight_male());
            }
            for (int i = 0; i < Number_of_mBoss; ++i)
            {
                _Archer_pool.push_back(new Archer());
            }
            for (int i = 0; i < Number_of_mBoss; ++i)
            {
                _Mage_pool.push_back(new Mage());
            }
            for (int i = 0; i < Number_of_mBoss; ++i)
            {
                _Cleric_pool.push_back(new Cleric());
            }
        }
        virtual ~MiniBoss_ObjCreate()
        {      
            for (Knight_male* mBoss : _Knight_male_pool)
            {
                if (mBoss == nullptr)
                    continue;

                delete mBoss;
                mBoss = nullptr;
            }
            for (Archer* mBoss : _Archer_pool)
            {
                if (mBoss == nullptr)
                    continue;

                delete mBoss;
                mBoss = nullptr;
            }
            for (Mage* mBoss : _Mage_pool)
            {
                if (mBoss == nullptr)
                    continue;

                delete mBoss;
                mBoss = nullptr;
            }
            for (Cleric* mBoss : _Cleric_pool)
            {
                if (mBoss == nullptr)
                    continue;

                delete mBoss;
                mBoss = nullptr;
            }
        }
        int random(int a, int b)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> distribution(a, b);
            int answer_random = distribution(gen);
            return answer_random;
        }

#pragma region GetMiniBoss

        Knight_male* Get_Knight_male()
        {
            if (!_Knight_male_pool.empty())
            {
                Knight_male* mBoss = _Knight_male_pool.back();
                _Knight_male_pool.pop_back();
                return mBoss;
            }
            return nullptr;
        }
        Archer* Get_Archer()
        {
            if (!_Archer_pool.empty())
            {
                Archer* mBoss = _Archer_pool.back();
                _Archer_pool.pop_back();
                return mBoss;
            }
            return nullptr;
        }
        Mage* Get_Mage()
        {
            if (!_Mage_pool.empty())
            {
                Mage* mBoss = _Mage_pool.back();
                _Mage_pool.pop_back();
                return mBoss;
            }
            return nullptr;
        }
        Cleric* Get_Cleric()
        {
            if (!_Cleric_pool.empty())
            {
                Cleric* mBoss = _Cleric_pool.back();
                _Cleric_pool.pop_back();
                return mBoss;
            }
            return nullptr;
        }
#pragma endregion  


#pragma region ReturnMiniBoss
        void Return_Knight_male(Knight_male* mBoss)
        {
            if (_Knight_male_pool.size() < capacity)
                _Knight_male_pool.push_back(mBoss);
            else
                delete mBoss;
        }       
        void Return_Archer(Archer* mBoss)
        {
            if (_Archer_pool.size() < capacity)
                _Archer_pool.push_back(mBoss);
            else
                delete mBoss;
        }
        void Return_Mage(Mage* mBoss)
        {
            if (_Mage_pool.size() < capacity)
                _Mage_pool.push_back(mBoss);
            else
                delete mBoss;
        }
        void Return_Cleric(Cleric* mBoss)
        {
            if (_Cleric_pool.size() < capacity)
                _Cleric_pool.push_back(mBoss);
            else
                delete mBoss;
        }
#pragma endregion  


    private:
        std::vector<Knight_male*> _Knight_male_pool;
        std::vector<Archer*> _Archer_pool;
        std::vector<Mage*> _Mage_pool;
        std::vector<Cleric*> _Cleric_pool;

        int capacity = 0;
        int _Randomcheck = 0;
    };
}
