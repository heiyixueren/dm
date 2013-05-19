#include"SparseMatirx.h" 
#include"minhash.h"
#include"lsh.h"
#include<assert.h>
#include<stdio.h>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
const int row_10m =  71567 ;
const int row_100k=  943;
const int py_row = 5000;
const int col_10m = 10681;
const int col_100k = 1682;
const int py_col = 1000; 


SparseMatirx matrix;
MinHash minHash;
LocalSenHash lsh;

double predict(const int& userid, const int& itemid);
double myround(double num);

//configuration 
int minHash_sigature_size = 50; //minhash sigle signature size
int lsh_band_num = 10;
int lsh_row_in_band =  5;
int row = row_100k;
int col = col_100k;


int main(int argc, char *argv[])
{
	assert(argv[1] != NULL);
	matrix = SparseMatirx(row, col, argv[1]);
	minHash = MinHash(col, minHash_sigature_size);
	lsh = LocalSenHash(lsh_band_num, lsh_row_in_band);
	int has_signature = 0;

	for( int i = 1; i <= col; i++ )
	{
		std::map<int, char> item_vec =  matrix.getVecByCol(i);
		std::vector<int>signature = minHash.computeMinHash(item_vec, i);
		lsh.insert(signature, i);
		printf("the signature for item %d\n", i);
		for( int j = 0; j < signature.size() ; j++ )
			printf("%d ", signature[j]);

		if( signature[0] != std::numeric_limits<int>::max() )
			has_signature++;
		printf("\n");
		printf("signature %d\n", has_signature);
	}
	lsh.test();

	//now predict
	assert(argv[2] != NULL);
	std::ifstream ifs(argv[2]);
	std::string line;
	int line_count = 0;
	double mse = 0.0;

#ifdef _PY_
	assert(argv[3] != NULL);
	std::ofstream ofs(argv[3]);
#endif
	while( std::getline(ifs, line))
	{
		std::istringstream istream(line);
		int userid;
		int itemid;
		int rate;
		char ch;
#ifndef _PY_
		istream >> userid >> itemid >> rate;
		if( itemid > col )
			continue;
		printf("now predict rate for %d\n", itemid);
		line_count++;
		int predict_rate = myround(predict(userid, itemid));
		mse += (predict_rate - rate)*(predict_rate - rate);
		printf("the rate is %d\n", predict_rate);
#else
		istream >> userid >> ch >> itemid;
		printf("now predict rate for %d\n", itemid);
		int predict_rate = myround(predict(userid, itemid));
		printf("the rate is %d\n", predict_rate);
		ofs << predict_rate << std::endl;
#endif
		line.clear();
	}
	printf("the mse is %lf\n", sqrt(mse/line_count));
	ifs.close();
#ifdef _PY_
	ofs.close();
#endif
	return 0;
}


double myround(double num)
{
	double num1 = num - floor(num);
	double num2 = ceil(num) - num;

	if (num1 > num2)
		return ceil(num);
	else
		return floor(num);

}

double predict(const int& userid, const int& itemid)
{
	std::set<int>sim_itemset;
	std::vector<int>srcSignature = minHash.getSignature(itemid);
	if( sim_itemset.size() == 0 || srcSignature[1] == std::numeric_limits<int>::max() )
		return  matrix.getColAverage(itemid);
	lsh.getSimItem(srcSignature, sim_itemset, itemid);
	double sim_sum = 0;
	double rate_sum = 0;
	std::set<int>::iterator it;
	for( it = sim_itemset.begin(); it != sim_itemset.end() ; it++ )
	{
		int count = 0;
		std::vector<int>cmpSigature = minHash.getSignature(*it);
		for( int i = 0; i < minHash_sigature_size; i++ )
		{
			if( srcSignature[i] == cmpSigature[i])
				count++;
		}
		double sim = (double)count / minHash_sigature_size;
		sim_sum += sim;
		int rate = matrix.getElement(userid, itemid);
		rate_sum += rate * sim;
	}
	return rate_sum / sim_sum;
}
