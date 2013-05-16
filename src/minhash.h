/*
 * =====================================================================================
 *
 *       Filename:  minhash.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年05月13日 10时26分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 *
 */

#ifndef _MIN_HASH_
#define _MIN_HASH_
#include<vector>
#include<map>
#include"hashfun.h"
#define FUNCTION_SIZE 50

class MinHash{
	public:
		//void setMatrix(int userid, int itemid, int rate);
		MinHash(int, int);
		MinHash(){};
		~MinHash();
		int hash(int, int);
		std::vector<int>& computeMinHash(std::map<int, char>vec, int id);
		void initMinHashSlot();
		void work();
		int predict(int, int);
		int getRate(int, int);
		std::vector<int>& getSignature(int itemid);
	private:
		//DBmanager m_dbmanager;
		//int m_MinHashSlots[ITEM_SIZE+1][FUNCTION_SIZE];
		std::vector<std::vector<int> >m_MinHashSlots;
		//float m_average[ITEM_SIZE+1];
		HashFun m_hashFun;
		int m_itemSize;
		int m_funSize;
};

#include"minhash.cpp"
#endif
