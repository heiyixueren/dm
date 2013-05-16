/*
 * =====================================================================================
 *
 *       Filename:  hashfun.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年05月13日 22时28分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include"hashfun.h"
#include<stdlib.h>
#include<time.h>

HashFun::HashFun(int size)
{
	fun_size = size;
	srand((unsigned)time(NULL));
	for( int i = 0; i < fun_size; i++ )
	{
		a[i] = random()%11 + 1;
		b[i] = random()%11 + 1;
		c[i] = random()%11 + 1;
	}

}

int HashFun::getHashValue(int x, int i)
{
	int hashValue = (int)((a[i] * (x >> 4) + b[i] * x + c[i]) & 131071);
}
