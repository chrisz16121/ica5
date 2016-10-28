#include <iostream>
#include <cstring>

using namespace std;

// --------- BaseSig class and methods ------------------------------
class BaseSig{
	private:
		// neither derived classes nor other users
		// can access private members
	
	protected:	// accessible by derived classes, not by other users.
		int length;
		int *raw_data;
		
	public:
		BaseSig();		// default constructor.
		//BaseSig(int L);	// parametric constructor
		~BaseSig();		// destructor
		int getLength() { return length; };
		int getRawValue(int pos);
		static int numObjects;	// static, only one member for the entire hierarchy
		virtual void printInfo();
};

BaseSig::BaseSig(){
	int i =0;
	char fileString[50];
	sprintf(fileString,"Raw_data_01.txt");//this is the file that i open by default 
	FILE* fp = fopen(fileString,"r");//opening file
	if(fp == NULL)//from this point on, the constructors are identical
	{
		cout << "Could not open the file, terminating\n" << endl;
		return;
	}
	fscanf(fp,"%d %lf",&numEl,&maxVal);
	raw_data = new double[length];
	double* arrStart = raw_data;
	while(i < numEl)
	{
		int temp;
		fscanf(fp,"%d\n",&temp); 
		*array = temp;
		array++;
		i++;
	}
	numObjects++;
}
BaseSig::~BaseSig(){
	delete[] raw_data;
	cout << "Goodbye, BaseSig." << endl;
}
class ProcessedSig : public BaseSig{
	
