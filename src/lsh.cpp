/*
 * =====================================================================================
 *
 *       Filename:  lsh.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年05月13日 22时42分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include"lsh.h"
#include<stdio.h>
#include<assert.h>

LocalSenHash::LocalSenHash(int fun_size, int row_in_band):
	m_funSize(fun_size), 
	m_rowInBand(row_in_band),
	m_hashFun(fun_size),
	m_hash_map(fun_size)
{
}

void LocalSenHash::insert(std::vector<int>&signature, int itermid)
{
	for(register  int i = 0; i < m_funSize; i++ )
	{
		int j =  i * m_rowInBand;
		int sum = 0;
		for(register int  k = 0; k < m_rowInBand; k++ )
		{
			sum += signature[j + k];
		}
		int hashValue = m_hashFun.getHashValue(sum, i);
		m_hash_map[i].insert(hash_map_t::value_type(hashValue, itermid));
		//postcondition can find the itermid int the hash table
		std::pair<hash_map_t::const_iterator, hash_map_t::const_iterator>p = m_hash_map[i].equal_range(hashValue);
		bool insert_ok = false;
		for (hash_map_t::const_iterator it = p.first; it != p.second; ++it)
		{
			int id = (*it).second;
			if( id == itermid )
			{
				insert_ok = true;
				break;
			}
		}
		assert(insert_ok);
	}
}

void LocalSenHash::test()
{
	for( int i = 0; i < m_funSize; i++ )
	{
		for( hash_map_t::iterator it = m_hash_map[i].begin(); it!=m_hash_map[i].end() ; it++ )
		{
			printf("key %d value %d\n", (*it).first, (*it).second);
		}
	}
}

void LocalSenHash::getSimItem(std::vector<int>& signature, std::set<int>&item_set, int itermid)
{
	for(register  int i = 0; i < m_funSize; i++ )
	{
		int j =  i * m_rowInBand;
		int sum = 0;
		for(register int  k = 0; k < m_rowInBand; k++ )
			sum += signature[j + k];
		int hashValue = m_hashFun.getHashValue(sum, i);
		//m_hash_map[i][hashValue] = itermid; 
		std::pair<hash_map_t::const_iterator, hash_map_t::const_iterator>p;
	    p = m_hash_map[i].equal_range(hashValue);
		for (hash_map_t::const_iterator it = p.first; it != p.second; ++it)
		{
			int id = (*it).second;
			if( itermid != id )
				item_set.insert(id);
		}
	}
}
