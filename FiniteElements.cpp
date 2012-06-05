#include "FiniteElements.h"

FiniteElements::FiniteElements(const char* filename)
{
	fn=filename;
	this->evaluate();
}

FiniteElements::~FiniteElements()
{
	delete [] T;
	delete [] X;
	delete [] Y;
}

int FiniteElements::evaluate()
{
	int res=0;
	res=this->init(fn);
	res=this->split();
	res=this->global_node();
	res=this->local_node();
	res=this->triang_num(x,y);
        if (res!=-1) result_temp=this->TinXY(x,y,this->triang_num(x,y));
	else res=2;

	return res;
}

int FiniteElements::init(const char* filename)
{
	ifstream fin(filename);
	if (!fin) return 1;

	fin >> n;
        T=new double [n];
        X=new double [n];
        Y=new double [n];
	for (int i=0;i<n;i++)
	{
		fin >> X[i];
		fin >> Y[i];
		fin >> T[i];
	}
	fin >> x;
	fin >> y;

	return 0;
}

int FiniteElements::split()
{
	rel=new int* [n];
	for (int i=0;i<n;i++)
	{
		rel[i]=new int[n];
		for (int j=0;j<n;j++)
			if (j==0) rel[i][j]=i;
			else rel[i][j]=-1;
	}
	for (int i=0;i<n;i++)
	{
		rel[i][1]=i+1;
		rel[i][2]=i-1;
	}
	rel[n-1][1]=0;
	rel[0][2]=n-1;

	bpn=this->minmax_dist();
	
	bool key;
	int tmp=3;
	for (int i=0;i<n;i++)
	{
		key=false;
		for (int j=0;j<n;j++)
			if (rel[i][j]==bpn)
			{
				key=true;
				break;
			}
		if (!key) 
		{
			rel[i][3]=bpn;
			rel[bpn][tmp++]=i;
		}
	}
	return 0;
}

double FiniteElements::dist(int a, int b)
{
        double tmp=sqrt(pow(X[a]-X[b],2)+pow(Y[a]-Y[b],2));
	return tmp;
}

int FiniteElements::minmax_dist()
{
        double **sqrm,*linm,res;
        sqrm=new double * [n];
        linm=new double [n];
	for (int i=0;i<n;i++)
	{
                sqrm[i]=new double [n];
		for (int j=0;j<n;j++)
		{
			sqrm[i][j]=this->dist(i,j);
		}
		linm[i]=sqrm[i][maxel(sqrm[i],n)];
	}
	res=minel(linm,n);
	return res;
}

int FiniteElements::minel(double* arr, int num)
{
        double min=arr[0];
	int res=0;
	for (int i=0;i<num;i++)
		if (arr[i]<min) 
		{
			min=arr[i];
			res=i;
		}
	return res;
}

int FiniteElements::maxel(double* arr, int num)
{
        double max=arr[0];
	int res=0;
	for (int i=0;i<num;i++)
		if (arr[i]>max)
		{
			max=arr[i];
			res=i;
		}
	return res;
}

int FiniteElements::global_node()
{
	gln=new int[n];
	gln[bpn]=((n % 2)==0) ? (n/2) : (n/2+1);

	int i=1,k=0,sm=bpn;
	while (k!=n)
	{
		gln[sm+i]= ((k==gln[bpn]) ? ++k : k);
		k++;
		i++;
		if (sm+i>=n) {sm=0;i=0;}
	}

	for (i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			rel[i][j]=(rel[i][j]!=-1) ? gln[rel[i][j]] : -1;
		}
	}

        double *tmp;
        tmp=new double[n];
	for (i=0;i<n;i++)
		tmp[i]=X[i];
	for (i=0;i<n;i++)
		X[gln[i]]=tmp[i];

	for (i=0;i<n;i++)
		tmp[i]=Y[i];
	for (i=0;i<n;i++)
		Y[gln[i]]=tmp[i];

	for (i=0;i<n;i++)
		tmp[i]=T[i];
	for (i=0;i<n;i++)
		T[gln[i]]=tmp[i];

	return 0;
}

int FiniteElements::local_node()
{
	int kf=0,i=bpn,k=0;
	triang=new int*[n-2];
	for (int k=0;k<n-2;k++)
		triang[k]=new int [3];

	for (int k=0;k<n-2;k++)
	{
		triang[k][0]=bpn;
		triang[k][1]=bpn+k+1;
		triang[k][2]=bpn+k+2;
	}

	for (int k=0;k<n-2;k++)
	{
		if (triang[k][1]>=n) triang[k][1]-=n;
		if (triang[k][2]>=n) triang[k][2]-=n;
	}

	for (int k=0;k<n-2;k++)
	{
		triang[k][0]=gln[triang[k][0]];
		triang[k][1]=gln[triang[k][1]];
		triang[k][2]=gln[triang[k][2]];
	}

	return 0;
}

int FiniteElements::triang_num(double a, double b)
{
	for (int i=0;i<n-2;i++)
		if (is_in_triang(X[triang[i][0]],Y[triang[i][0]],X[triang[i][1]],Y[triang[i][1]],X[triang[i][2]],Y[triang[i][2]],a,b)) return i;
	return -1;
}

bool FiniteElements::is_in_triang(double x1, double y1, double x2, double y2, double x3, double y3, double a, double b)
{
        double dl12=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
        double dl23=sqrt(pow(x2-x3,2)+pow(y2-y3,2));
        double dl13=sqrt(pow(x1-x3,2)+pow(y1-y3,2));
        double dlx1=sqrt(pow(x1-a,2)+pow(y1-b,2));
        double dlx2=sqrt(pow(x2-a,2)+pow(y2-b,2));
        double dlx3=sqrt(pow(x3-a,2)+pow(y3-b,2));
        double pall=(dl12+dl23+dl13)/2;
        double p1=(dl12+dlx1+dlx2)/2;
        double p2=(dl23+dlx2+dlx3)/2;
        double p3=(dl13+dlx1+dlx3)/2;
        double s123=sqrt(pall*(pall-dl12)*(pall-dl23)*(pall-dl13));
        double s12x=sqrt(p1*(p1-dl12)*(p1-dlx1)*(p1-dlx2));
        double s23x=sqrt(p2*(p2-dl23)*(p2-dlx2)*(p2-dlx3));
        double s13x=sqrt(p3*(p3-dl13)*(p3-dlx1)*(p3-dlx3));
	return (fabs(s123-(s12x+s23x+s13x))<0.01) ? true : false;
}

double FiniteElements::TinXY(double r, double t, int key)
{
        double result=0;
        double s,a,b,c;
	int i=triang[key][0],
		j=triang[key][1],
		k=triang[key][2];

	s=0.5*((Y[j]-Y[k])*X[i] + (Y[k]-Y[i])*X[j] + (Y[i]+Y[j])*X[k]);
	if (s>0) s*=-1;

	a=X[j]*Y[k]-X[k]*Y[j];
	b=Y[j]-Y[k];
	c=X[k]-X[j];
	result+=(1/(s*2))*(a+b*r+c*t)*T[i];

	a=X[k]*Y[i]-X[i]*Y[k];
	b=Y[k]-Y[i];
	c=X[i]-X[k];
	result+=(1/(s*2))*(a+b*r+c*t)*T[j];

	a=X[i]*Y[j]-X[j]*Y[i];
	b=Y[i]-Y[j];
	c=X[j]-X[i];
	result+=(1/(s*2))*(a+b*r+c*t)*T[k];

	return result;
}

double FiniteElements::GetResultTemp()
{
	return result_temp;
}

int FiniteElements::GetN()
{
	return n;
}

double FiniteElements::GetX()
{
	return x;
}

double FiniteElements::GetY()
{
	return y;
}

int** FiniteElements::GetRelations()
{
	return rel;
}

double* FiniteElements::GetXArray()
{
	return X;
}

double* FiniteElements::GetYArray()
{
	return Y;
}

double* FiniteElements::GetTArray()
{
	return T;
}

void FiniteElements::SetFN(const char* filename)
{
    fn=filename;
}

int** FiniteElements::GetTriangles()
{
    return triang;
}
