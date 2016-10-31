// L14_Ex1_Inheritance.cpp
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// --------- BaseSig class and methods ------------------------------
class BaseSig{
	private:
		// neither derived classes nor other users
		// can access private members
	
	protected:	// accessible by derived classes, not by other users.
		int length;
		double *raw_data;
		int maximum;
		
	public:
		BaseSig();		// default constructor.
		BaseSig(int L);	// parametric constructor
		~BaseSig();		// destructor
		int getLength() { return length; };
		int getRawValue(int pos);
		static int numObjects;	// static, only one member for the entire hierarchy
		virtual void printInfo();
};

int BaseSig::numObjects = 0;	// initialize static data member

// Base class constructor
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
	fscanf(fp,"%d %d",&length,&maximum);
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

// Base class parametric constructor
// Note that the data array is not being initialized (we could read from a file)
BaseSig::BaseSig(int L){
	length = L;
	raw_data = new double[L];
	if(raw_data == NULL)
		cerr << "Error in memory allocation";
	numObjects++;
}

// Base class destructor
BaseSig::~BaseSig(){
	delete[] raw_data;
	cout << "Goodbye, baseSig." << endl;
}

int BaseSig::getRawValue(int pos) {
	if(pos < 0)			// invalid index
		return(raw_data[0]);
	else if(pos >= length)	// invalid index
		return(raw_data[length-1]);	
	else
		return(raw_data[pos]);
}

void BaseSig::printInfo() {
	cout << "Length: " << length << endl;
}
// ------------------------------------------------------------------
class processedSig : public BaseSig{
	private:
		double maxVal;
		double minVal;
	public:
		
		double maxVal_finder(void);
		double minVal_finder(void);
		void normalize(void);
		void printInfo();
};
double processedSig::maxVal_finder(void){
	int i = 0;
	double* startPtr = raw_data;
	maxVal = *raw_data;
	while(i<length)
	{
		double temp = *raw_data;
		if(temp > maxVal) maxVal = *raw_data;	
		raw_data++;
		i++;
	}
	raw_data = startPtr;
	return maxVal;
}
double processedSig::minVal_finder(void){
	int i = 0;
	double* startPtr = raw_data;
	minVal = *raw_data;
	while(i<length)
	{
		double temp = *raw_data;
		if(temp < minVal) minVal = *raw_data;	
		raw_data++;
		i++;
	}
	raw_data = startPtr;
	return minVal;
}
void processedSig::printInfo(){
	cout << "Length: " << length << "\tMaxVal: " << maxVal << "\tMinVal: " << minVal << endl;
	return;
}
void processedSig::normalize(void){
	int i = 0;
	double* startPtr = raw_data;
	while(i<length)
	{
		double temp = *raw_data;
		*raw_data = temp/maximum;
		raw_data++;
		i++;
	}
	raw_data = startPtr;
	return;
}
// --------- ExtendSig class and methods ----------------------------
		
class ExtendSig : public BaseSig{ // ExtendSig is derived from class BaseSig
//BaseSig is a public base class
	private: 
		double average;		// add new data members
		double *data;
		
	public:
		ExtendSig(int L);	//derived classes need a new constructor
		~ExtendSig();
		
		// define new member functions
		double getValue(int pos);
		int setValue(int pos, double val);
		double getAverage();
		
		// redefine member function. Virtual keyword not needed
		void printInfo();	// new standard: explicit "override" keyword can be used
};

// Derived class constructor. Note how the Base constructor is called.
ExtendSig::ExtendSig(int L) : BaseSig(L) {
	data = new double[L];
	if(data == NULL)
		cerr << "Error in memory allocation";
	else{
		for(int i = 0; i < L; i++)
			data[i] = (double)raw_data[i];
		average = getAverage();
	}
}

// Derived class destructor
ExtendSig::~ExtendSig() {
	//delete raw_data;
	delete data;
	cout << "Goodbye, ExtendSig." << endl;
}

double ExtendSig::getValue(int pos) {
	if(pos < 0)			// invalid index
		return(data[0]);
	else if(pos >= length)	// invalid index
		return(data[length-1]);	
	else
		return(data[pos]);
}

int ExtendSig::setValue(int pos, double val) {
	if((pos < 0) || (pos >= length))
		return(-1);	// invalid index
	else {
		data[pos] = val;
		average = getAverage();
		return(0);	// success
	}
}

double ExtendSig::getAverage() {
	if(length == 0)
		return(0.0);
	else {
		double temp = 0.0;
		for(int i = 0; i < length; i++)
			temp += data[i];
		return(temp/(double)length);
	}
}

// Redefined printInfo function for derived class
void ExtendSig::printInfo() {
	cout << "\nLength: " << length << endl
		 << "Average: " << average << endl;
}
// ------------------------------------------------------------------
/*class processedSig_v2 : public BaseSig::ExendSig{
	private:
		double maxVal;
		double minVal;
	public:
		double maxVal_finder(void);
		double minVal_finder(void);
		void normalize(void);
		void printInfo();
};
*/
int main(){
	int max;
	int min;
	cout << "BASE SIGNAL:" << endl;
	BaseSig sig1;
	sig1.printInfo();
	processedSig sig2;
	max = sig2.maxVal_finder();
	min = sig2.minVal_finder();
	cout << "-------------------------------------------------------------------------\nPROCESSED SIGNAL BEFORE NORMALIZING:" << endl;
	sig2.printInfo();
	sig2.normalize();
	cout <<  "-------------------------------------------------------------------------\nPROCESSED SIGNAL AFTER NORMALIZING:" << endl;
	max = sig2.maxVal_finder();
	min = sig2.minVal_finder();
	sig2.printInfo();
	//processedSig_v2 sig3;
	//max = sig3.maxVal_finder();
	//min = sig3.minVal_finder();
	//cout << "-------------------------------------------------------------------------\nPROCESSED SIGNAL_V2 BEFORE NORMALIZING:" << endl;
	//sig3.printInfo();
	//sig3.normalize();
	//cout <<  "-------------------------------------------------------------------------\nPROCESSED SIGNAL_V2 AFTER NORMALIZING:" << endl;
	//sig3.printInfo();
	//sig3.normalize();
	
	cout << "--------------------------------------------" << endl;
	return 0;
}
