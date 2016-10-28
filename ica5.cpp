#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
int numObjects = 0;
// --------- BaseSig class and methods ------------------------------
class BaseSig{
	private:
		// neither derived classes nor other users
		// can access private members
	
	protected:	// accessible by derived classes, not by other users.
		int length;
		double *raw_data;
		int maxVal;
	public:
		BaseSig();		// default constructor.
		//BaseSig(int L);	// parametric constructor
		~BaseSig();		// destructor
		//int getLength() { return length; };
		//int getRawValue(int pos);
		//static int numObjects;	// static, only one member for the entire hierarchy
		virtual void printInfo();
};
void BaseSig::printInfo(){
	int i;
	cout << "Length is: " << length << "\nMaximum value is: " << maxVal << endl;
}
BaseSig::BaseSig(){
	int i =0;
	char fileString[50];
	sprintf(fileString,"Raw_data_01.txt");//this is the file that i open by default 
	FILE* fp = fopen(fileString,"r");//opening file
	if(fp == NULL)
	{
		cout << "Could not open the file, terminating\n" << endl;
		return;
	}
	fscanf(fp,"%d %d",&length,&maxVal);
	raw_data = new double[length];
	double* arrStart = raw_data;
	while(i < length)
	{
		int temp;
		fscanf(fp,"%d\n",&temp); 
		*raw_data = temp;
		raw_data++;
		i++;
	}
	raw_data = arrStart;
	numObjects++;
}
BaseSig::~BaseSig(){
	delete raw_data;
	cout << "Goodbye, BaseSig." << endl;
}
//class ProcessedSig : public BaseSig{
int main(void)
{
	BaseSig sig1;
	sig1.printInfo();
	return 1;
}	
