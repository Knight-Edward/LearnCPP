#include <ostream>
#include <iostream>
using namespace std;

class num_sequence {
public:
	virtual ~num_sequence() {};
	
	virtual int elem(int pos) = 0; //pure virtual function
	virtual const char* what_am_i() const = 0; 
	static int max_elems() {
		return _max_elems;
	}
    virtual ostream& print(ostream &os = cout)  = 0; //this function can only read, cannot modify object

protected:
    virtual void gen_elems(int pos) = 0;
	bool check_integrity(int pos, int size);

	const static int _max_elems = 1024;
};

bool num_sequence::
check_integrity(int pos, int size)
{
	if(pos <= 0 || pos > _max_elems )
	{
		cerr << "!! invalid postion: " << pos << "cannot honor request\n";
		return false;
	}
	
	if( pos > size ) {
		gen_elems( pos );
	}	

	return true;
}

ostream& operator<< (ostream& os, num_sequence &ns)
{
	return ns.print( os );
}
