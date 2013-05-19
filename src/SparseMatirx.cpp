/*
 * =====================================================================================
 *
 *       Filename:  SparseMatirx.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年05月15日 21时48分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include<fstream>
#include<string>
#include<sstream>
#include<assert.h>
#include<stdio.h>

SparseMatirx::SparseMatirx(int x, int y, char* srcFile)
{
	m_row_num = x;
	m_col_num = y;
	m_row_matrix.resize(m_row_num + 1);
	m_col_matrix.resize(m_col_num + 1);
	initFrom10kMovie(srcFile);
}

void SparseMatirx::initFromPy(char* srcFile)
{
	std::ifstream ifs(srcFile);
	std::string line;
	int userid = 1;
	while( std::getline(ifs, line ))
	{
		std::istringstream strstream(line);
		for( int itermid = 1; itermid <= m_col_num ; itermid++ )
		{
			int rate; char ch;
			strstream >> rate >> ch;
			if( rate == 0 )
				continue;
			m_row_matrix[userid][itermid] = (unsigned char)rate;
			m_col_matrix[itermid][userid] = (unsigned char)rate;
		}
		userid++;
		//int userid; int itermid; int rate;
		//strstream >> userid >> itermid >> rate;

		//assert(userid >=1 && userid <= m_row_num);
		//assert(itermid >=1 && itermid <= m_col_num);
		//m_row_matrix[userid][itermid] = (unsigned char)rate;
		//m_col_matrix[itermid][userid] = (unsigned char)rate;
		//assert(m_row_matrix[userid][itermid] == rate);
		//printf("read %d %d %d\n", userid, itermid, rate);
		line.clear();
	}
}

SparseMatirx::~SparseMatirx()
{
}
void SparseMatirx::initFrom10kMovie(char* srcFile)
{
	std::ifstream ifs(srcFile);
	std::string line;
	while( std::getline(ifs, line ))
	{
		std::istringstream strstream(line);
		int userid; int itermid; int rate;
		strstream >> userid >> itermid >> rate;

		assert(userid >=1 && userid <= m_row_num);
		assert(itermid >=1 && itermid <= m_col_num);
		m_row_matrix[userid][itermid] = (unsigned char)rate;
		m_col_matrix[itermid][userid] = (unsigned char)rate;
		assert(m_row_matrix[userid][itermid] == rate);
		printf("read %d %d %d\n", userid, itermid, rate);
		line.clear();
	}
	ifs.close();
}

void SparseMatirx::initFrom10MMovie(char* srcFile)
{
	std::ifstream ifs(srcFile);
	std::string line;
	while( std::getline(ifs, line ))
	{
		std::istringstream strstream(line);
		int userid; int itermid; float rate; char ch;
		strstream >> userid >>ch>>ch>> itermid >> ch>>ch>>rate;
		if( userid > m_row_num || itermid > m_col_num)
			continue;
		assert(userid >=1 && userid <= m_row_num);
		assert(itermid >=1 && itermid <= m_col_num);
		m_row_matrix[userid][itermid] = (unsigned char)(int)rate;
		assert(m_row_matrix[userid][itermid] == (unsigned char)(int)rate);
		m_col_matrix[itermid][userid] = (unsigned char)(int)rate;
		printf("read %d %d %f\n", userid, itermid, rate);
		line.clear();
	}
	ifs.close();
}

int SparseMatirx::getRowNum()
{
	return m_row_num;
}

int SparseMatirx::getColNum()
{
	return m_col_num;
}

std::map<int, char>& SparseMatirx::getVecByCol(int index)
{
	assert(index <= m_col_num);
	return m_col_matrix[index];
}

std::map<int, char>& SparseMatirx::getVecByRow(int index)
{
	assert(index <= m_row_num);
	return m_row_matrix[index];
}

double SparseMatirx::getColAverage(int colIndex)
{
	std::map<int, char>::iterator it;
	int size = 0;
	double sum = 0;
	for( it = m_col_matrix[colIndex].begin(); it != m_col_matrix[colIndex].end() ; it++ )
	{
		sum += (*it).second;
		size++;
	}
	if( sum > 0 )
		return sum / size;
	else
		return 0;
}

int SparseMatirx::getElement(int row, int col)
{
	if( m_row_matrix[row].find(col) == m_row_matrix[row].end() )
		return -1;
	return m_row_matrix[row][col];
}
