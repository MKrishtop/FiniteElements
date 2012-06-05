#ifndef FINITEELEMENTS_H
#define FINITEELEMENTS_H
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class FiniteElements
{
private:
	int n,m,**rel,bpn,**triang,*gln;
        double *X,*Y,*T,x,y,result_temp;
	int eval_result;
	int init(const char*);
	int split();
	int global_node();
	int local_node();
	const char* fn;
        double dist(int,int);
	int minmax_dist();
        int minel(double*,int);
        int maxel(double*,int);
        int triang_num(double,double);
        bool is_in_triang(double,double,double,double,double,double,double,double);
        double TinXY(double,double,int);
public:
        FiniteElements(){};
	FiniteElements(const char*); 
	~FiniteElements();
	int evaluate();
	int GetN();
        double GetResultTemp();
        double GetX();
        double GetY();
	int** GetRelations();
        int** GetTriangles();
        double* GetXArray();
        double* GetYArray();
        double* GetTArray();
	void SetFN(const char*);
};

#endif
