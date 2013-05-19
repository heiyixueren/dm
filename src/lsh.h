/*
 * =====================================================================================
 *
 *       Filename:  lsh.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年05月13日 22时05分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef _LSH_
#define _LSH_
#include<ext/hash_map>
#include<vector>
#include"hashfun.h"
#include<set>
typedef  __gnu_cxx::hash_multimap<int,int>  hash_map_t;
class LocalSenHash
{
	public:
		LocalSenHash(int fun_size, int row_in_band);
		LocalSenHash(){};
		void insert(std::vector<int>& signature, int item);
		void test();
		void getSimItem(std::vector<int>&signature, std::set<int>&item_set, int itermid);
	private:
		int m_funSize;
		int m_rowInBand;
		HashFun m_hashFun;
		std::vector<hash_map_t> m_hash_map;
};
#include"lsh.cpp"
#endif
