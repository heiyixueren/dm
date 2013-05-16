/*
 * =====================================================================================
 *
 *       Filename:  hashfun.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年05月13日 22时23分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef _FUN_GEN_
#define _FUN_GEN_
#define MAX_FUN 200
class HashFun
{
	public:
		HashFun(){};
		HashFun(int);
		int getHashValue(int, int);
	private:
		int fun_size;
		int a[MAX_FUN];
		int b[MAX_FUN];
		int c[MAX_FUN];
};

#include"hashfun.cpp"
#endif
