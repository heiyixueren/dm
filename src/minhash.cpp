/*
 * =====================================================================================
 *
 *       Filename:  minhash.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年05月13日 10时32分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<limits>
#include<assert.h>
#include"minhash.h"
#include<math.h>
#define MIN_RATE 1
#define MAX_RATE 5
#define SPLIT_LINE 3

/*  
static double myround(double num)
{
	double num1 = num - floor(num);
	double num2 = ceil(num) - num;

	if (num1 > num2)
		return ceil(num);
	else
		return floor(num);

}
*/

//constructor
MinHash::MinHash(int item_size, int function_size = FUNCTION_SIZE):
	m_itemSize(item_size),
	m_funSize(function_size),
	m_hashFun(function_size),
	m_MinHashSlots(item_size+1, std::vector<int>(function_size))
{
	for( int i = 1; i <= item_size; i++ )
	{
		for( int j = 0; j <= function_size; j++ )
		{
			m_MinHashSlots[i][j] = std::numeric_limits<int>::max();
		}
	}
}

MinHash::~MinHash()
{
}

std::vector<int>& MinHash::computeMinHash(std::map<int, char> item_vec, int itemid)
{
	bool is_zero_vector = true;
	std::map<int, char>::iterator it;
	for( it = item_vec.begin(); it != item_vec.end() ; it++ )
	{
		int userid = (*it).first;
		int rate = (*it).second;
		if( rate > 2.5 )
		{
			is_zero_vector = false;
			for( int i = 0; i < m_funSize; i++ )
			{
				int hashValue = m_hashFun.getHashValue(userid, i);
				assert(itemid < m_MinHashSlots.size());
				if( hashValue < m_MinHashSlots[itemid][i] )
					m_MinHashSlots[itemid][i] = hashValue;
			}
		}
	}
	return m_MinHashSlots[itemid];
}

std::vector<int>& MinHash::getSignature(int itemid)
{
	return m_MinHashSlots[itemid];
}
	/*  
void MinHash::work()
{
	for( int i = 1 ; i <=ITEM_SIZE; i++ )
		computeMinHash(i);
	for( int i = 1; i <= ITEM_SIZE ; i++ )
	{
		if( m_MinHashSlots[i][0] == std::numeric_limits<int>::max())
			continue;
		fprintf(stdout,"sim item for %d: ", i);
		std::set<int>item_set;
		m_lsh.getSimItem(m_MinHashSlots[i], item_set, i);
		std::set<int>::iterator it;
		for( it = item_set.begin(); it != item_set.end() ; it++ )
			printf("%d ", *it);
		printf("\n");
	}
}
*/
/*  
int MinHash::predict(int userid, int itemid)
{
	//get the similarity item;
	std::set<int>sim_item_set;
	assert(itemid>=1 && itemid<=ITEM_SIZE);
	m_lsh.getSimItem(m_MinHashSlots[itemid], sim_item_set, itemid );
	//note
	if( sim_item_set.empty() || m_MinHashSlots[itemid][0] == std::numeric_limits<int>::max())
		return myround(m_average[itemid]);
	std::set<int>::iterator it;
	double sim_sum = 0.0;
	double rate_sum = 0.0;
	for( it = sim_item_set.begin(); it != sim_item_set.end() ; it++ )
	{
		//count the sim
		int temp= 0;
		for( int i = 0; i < FUNCTION_SIZE ; i++ )
		{
			if( m_MinHashSlots[itemid][i] == m_MinHashSlots[*it][i] )
				temp++;
		}
		double sim = (double)temp/FUNCTION_SIZE;
		int rate = getRate(userid, *it);
		if( rate != 0 )
		{
			sim_sum += sim;
			rate_sum += sim*rate;
		}
	}
	if( rate_sum < 1e-6 )
	{
		return myround(m_average[itemid]);
	}
	return myround(rate_sum/sim_sum);
}*/

/*  
int MinHash::getRate(int userid, int itermid)
{
	bson query[1];
	mongo_cursor cursor[1];

	bson_init( query );
	bson_append_start_array(query, "$and");
	bson_append_start_object(query, "0");
	bson_append_int( query,USERID,userid);
	bson_append_finish_object(query);
	bson_append_start_object(query, "1");
	bson_append_int( query,ITEMID,itermid);
	bson_append_finish_object(query);
	bson_append_finish_array(query);
	bson_finish( query );
	bson_iterator iterator[1];
	mongo_cursor_init( cursor, m_conn, NS);
	mongo_cursor_set_query( cursor, query );
	double rate = 0.0;
	while( mongo_cursor_next( cursor ) == MONGO_OK ) {
		if ( bson_find( iterator, mongo_cursor_bson( cursor ), RATE)) 
			rate = bson_iterator_double( iterator); 
	}
	bson_destroy( query );
	mongo_cursor_destroy( cursor );	
	printf("read rate %f\n", rate);
	return myround(rate);
}*/
