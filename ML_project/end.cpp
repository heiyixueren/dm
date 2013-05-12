#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

const int user_size = 5000;						//�����û���
const int item_size = 1000;						//��������
double sim[item_size][item_size] = {0};			//������Ŀ֮������ƶ�
const int question_num = 145081;				//������Ҫ�Ƽ����û����ļ��е�����
char user[user_size][item_size] = {NULL};		//�����û���Ϣ�����û�����ÿ����Ӱ������
vector<double> ex,ex2;							//������ÿһ���е��������/��ֵ


/*
	���彫Ҫ�����Ƽ����û�����
	�����û���index.csv�е�λ��
	����һ���û�
	�Լ�����һ����Ӱ��������
	�Լ������������������
*/
struct user_question{
	int positionInIndex;
	int whichUser;
	int whichMovie;
	char theWantScore;
};

/*����һ���ṹ�壬��ʾ���ǵ�Ӱid�������ƶ�*/
struct simStruct{
	int movie_id;
	double sim_level;
};

/*���û������ļ�*/
void readDataFile(){
	FILE *inFile;
	fopen_s(&inFile,"data.csv","r");

	char score = NULL;
	
	for (int i=0;i<user_size;i++){
		for (int j=0;j<item_size;j++){
			fscanf_s(inFile,"%c",&score);
			user[i][j] = score;
			fscanf_s(inFile,"%c",&score);
		}
	}

	fclose(inFile);
}

/*
	�Դ�index.csv�ж�ȡ�����ݽ�������ĺ���
	���û�id��С�ķ���ǰ��
	��ͬһ�û��Ľ�С��Ӱid��ǰ��
*/
bool cmp(user_question a,user_question b){
	bool result = true;
	if ((a.whichUser > b.whichUser) || (a.whichUser == b.whichUser && a.whichMovie > b.whichMovie) )
		result = false;
	return result;
}

/*
	��index.csv�ж�ȡ��Ҫ���ȵ��û�����
	�����ս�������
*/
void read_question_set(vector<user_question> &indexContent){
	FILE *infile;
	fopen_s(&infile,"index.csv","r");

	int temp = 0;
	char ch = NULL;
	user_question question;

	for (int i=0;i<question_num;i++){
		question.positionInIndex = i;

		fscanf_s(infile,"%d",&temp);
		fscanf_s(infile,"%c",&ch);
		question.whichUser = temp-1;				//�û�id�Ǵ�0��ʼ�����

		fscanf_s(infile,"%d",&temp);
		fscanf_s(infile,"%c",&ch);
		question.whichMovie = temp-1;				//��Ӱid�Ǵ�0��ʼ�����

		indexContent.push_back(question);
	}

	sort(indexContent.begin(),indexContent.end(),cmp);

	fclose(infile);
}

/*�������Эͬ����*/

/*�������ƶ�*/
void getSim(){
	//��ȡÿһ����ľ�ֵ���Լ�ƽ����ľ�ֵ����E(x),E(x2)
	for (int i=0;i<item_size;i++){
		double sum1 = 0.00,sum2 = 0.00,temp = 0.00;
		for (int j=0;j<user_size;j++){
			temp = (double) (user[j][i]-'0');
			sum1+= temp;
			sum2 += pow(temp,2);
		}
		ex.push_back(sum1/user_size);
		ex2.push_back(sum2/user_size);
	}
	FILE *outfile;
	fopen_s(&outfile,"exy.csv","w");

	for (int i=0;i<item_size;i++){
		for (int j=i+1;j<item_size;j++){
			double sum1 = 0.00,exy = 0.00;
			for (int k=0;k<user_size;k++){
				sum1 += (user[k][i]-'0')*(user[k][j]-'0');
			}
			exy = sum1/user_size;

			sim[i][j] = (exy-ex[i]*ex[j])/(sqrt((ex2[i]-pow(ex[i],2))*(ex2[j]-pow(ex[j],2))));
			sim[j][i] = sim[i][j];
			fprintf(outfile,"%lf,",exy);
		}
		fprintf(outfile,"\n");
	}

	fclose(outfile);
}

/*�����ƶ�д�����*/
void writeSimToDisk(){
	FILE *outFile;
	fopen_s(&outFile,"sim.csv","w");

	for (int i=0;i<item_size;i++){
		for (int j=0;j<item_size-1;j++)
			fprintf_s(outFile,"%lf,",sim[i][j]);
		fprintf_s(outFile,"%lf\n",sim[i][item_size-1]);
	}

	fclose(outFile);

	fopen_s(&outFile,"ex.csv","w");

	for (int i=0;i<item_size;i++){
		fprintf_s(outFile,"%lf\n",ex[i]);
	}

	fclose(outFile);

	fopen_s(&outFile,"ex2.csv","w");

	for (int i=0;i<item_size;i++){
		fprintf_s(outFile,"%lf\n",ex2[i]);
	}

	fclose(outFile);
}

/*�������ƶȵ�����*/
bool cmpp(simStruct a,simStruct b){
	return a.sim_level - b.sim_level > 0.0000001;
}

/*���ڽ��������*/
bool cmpp1(user_question a,user_question b){
	return a.positionInIndex < b.positionInIndex;
}
void getNeighbor(vector<user_question> &indexContent){
	FILE *infile;
	char ch = NULL;
	double temp = 0.00;

	vector<simStruct> simSet[item_size];
	simStruct tempSim;
	fopen_s(&infile,"sim.csv","r");
	for (int i=0;i<item_size;i++){
		for (int j=0;j<item_size;j++){
			fscanf_s(infile,"%lf%c",&temp,&ch);
			tempSim.movie_id = j;
			tempSim.sim_level = temp;
			simSet[i].push_back(tempSim);
		}
		sort(simSet[i].begin(),simSet[i].end(),cmpp);
	}

	fclose(infile);

	for (int i=0;i<question_num;i++){
		int whichUser = indexContent[i].whichUser;
		int whichMovie = indexContent[i].whichMovie;

		int count = 0;
		double sum1 = 0.00,sum2 = 0.00,result = 0.00;

		for (int j=0;j<item_size-1 && count <= 100;j++){
			int simMovie = simSet[whichMovie][j].movie_id;
			double simLevel = simSet[whichMovie][j].sim_level;

			if (user[whichUser][simMovie] != '0'){
				count ++;
				sum1 += (simLevel*(user[whichUser][simMovie]-'0'-ex[simMovie]));
				sum2 += abs(simLevel);
			}
		}
		
		result = ex[whichMovie] + sum1/sum2;
		indexContent[i].theWantScore = ((int) (result+0.5))+'0';
		if (indexContent[i].theWantScore == '6')
			indexContent[i].theWantScore = '5';
	}

	sort(indexContent.begin(),indexContent.end(),cmpp1);

	FILE *outfile;
	fopen_s(&outfile,"test.csv","w");
	for (int i=0;i<question_num;i++){
		fprintf_s(outfile,"%c\n",indexContent[i].theWantScore);
	}
	fclose(outfile);

	for (int i= 0;i<item_size;i++)
		simSet[i].clear();
}
int main(){
	/*��ȡ���ݼ���*/
	readDataFile();

	/*��ȡ��Ҫ���۵ļ���*/
	vector<user_question> indexContent;
	read_question_set(indexContent);

	getSim();
	writeSimToDisk();
	getNeighbor(indexContent);

	indexContent.clear();
	ex.clear();
	ex2.clear();
	return 0;
}