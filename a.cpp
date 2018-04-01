#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm> 
#include <map>
#include <vector>

#define LENTH 40000
#define ROW 60483//18043 1251
#define LIST 1215//161//1102//113//18043 1251

using namespace std;


double Mean(const double *data, int num)
{
	int i;
	double mean=0.0;
	
	for(i=0; i<num; i++)
		mean += data[i];
	
	return mean/(double)num;
}

double Sigma(const double *data, int num)
{
	int i;
	double mean=0.0, sum=0.0, tmp;
	
	for(i=0; i<num; i++)
		mean += data[i];
	
	mean /= (double) num;
	
	for(i=0; i<num; i++)
	{
		tmp = data[i] - mean;
		sum += tmp*tmp;
	}
	
	return sqrt(sum/(double)num);
}

double MyPearons(const double *x,double mx,double sx,const double *y,double my,double sy,int len)
{
	int i;
	double sumxy=0;
	for(i=0;i<len;i++)
		sumxy += x[i]*y[i];
//	cout<<(sumxy/len - Mean(x,len)*Mean(y,len))/(Sigma(x,len)*Sigma(y,len))<<endl;
	return (sumxy/len - mx*my)/(sx*sy);
}
double MyPearons1(const double *x,const double *y,int len)
{
	int i;
	double sumxy=0;
	for(i=0;i<len;i++)
		sumxy += x[i]*y[i];
//	cout<<(sumxy/len - Mean(x,len)*Mean(y,len))/(Sigma(x,len)*Sigma(y,len))<<endl;
	return (sumxy/len - Mean(x,len)*Mean(y,len))/(Sigma(x,len)*Sigma(y,len));
}



int main()
{
	FILE*inFile, *outFile; 

//	inFile = fopen("out2.txt", "r");
	inFile = fopen("Merge_matrix.txt", "r");
	FILE*outFile1 = fopen("m2sall.txt", "w");
	char name[13]="pearson0.txt"; 
	char str[LENTH], *str1;
	double *bi = (double*)malloc(LIST * ROW * sizeof(double));
	int i = 0;
	fgets(str, LENTH, inFile);
	cout<<str<<endl;
	while (fgets(str, LENTH, inFile))
	{
		str1 = strtok(str, " \t\n");
		str1 = strtok(NULL, " \t\n");
		while (str1)
		{
			bi[i++] = atof(str1);
			str1 = strtok(NULL, " \t\n");
		}
	}
	int j, k;
	double temp;
	double mean[ROW],sig[ROW];
	for(i=0;i<ROW;i++)
	{
		mean[i]=Mean(bi+LIST*i,LIST);
		sig[i]=Sigma(bi+LIST*i,LIST);
		fprintf(outFile1,"%f\t%f\n", mean[i],sig[i]);

	}
	fclose(outFile1);
	for(i=0;i<ROW;i++)
	{
		
		if(i%10000==0)
		{
			k=i/10000;
			if(k!=0)
			fclose(outFile);
			name[7]='0'+k;
			outFile=fopen(name,"w");
			}	
		for(j=0;j<ROW;j++)
		{
			if(sig[i]!=0&&sig[j]!=0)
			{
				temp=MyPearons(bi+LIST*i,mean[i],sig[i],bi+LIST*j,mean[j],sig[j],LIST);
			//	if(temp>0.2||temp<-0.2)
					fprintf(outFile,"%d\t%d\t%f\n",i,j,temp);
			} 
		}
//		fprintf(outFile,"\n");
		if(i%100==0)
			cout<<"this is "<<i<<" row."<<endl;
	}
	cout<<"sjdfls"<<endl;
	fclose(inFile);
	fclose(outFile);
	return 0;
}
