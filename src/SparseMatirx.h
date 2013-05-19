/*
 * =====================================================================================
 *
 *       Filename:  SparseMatirx.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年05月15日 21时34分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef _MATIRX_
#define _MATIRX_
#include<iostream>
#include<vector>
#include<map>
class SparseMatirx
{
	public:
		SparseMatirx(int x, int y, char* srcFile);
		SparseMatirx(){};
		void initFrom10kMovie(char* srcFile);
		void initFrom10MMovie(char* srcFile);
		void initFromPy(char* srcFile);
		~SparseMatirx();
		int getColNum();
		int getRowNum();
		std::map<int, char>& getVecByCol(int index);
		std::map<int, char>& getVecByRow(int index);
		double getColAverage(int colIndex);
		int getElement(int row, int col);
	private:
		std::vector<std::map<int, char> > m_row_matrix;
		std::vector<std::map<int, char> > m_col_matrix;
		int m_row_num;
		int m_col_num;
};
#include"SparseMatirx.cpp"
#endif
