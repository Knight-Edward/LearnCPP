#include "num_sequence.h"
#include <vector>
using namespace std;

class Fibonacci : public num_sequence {
public:
	Fibonacci( int len = 1, int beg_pos = 1)
			 : _length( len ), _beg_pos( beg_pos){ }
	virtual int elem( int pos ) ;
	virtual const char* what_am_i() const {return "Fibonacci";}
	virtual ostream& print( ostream &os = cout );
	int length() const { return _length; }
	int beg_pos() const { return _beg_pos; }

protected:
	virtual void gen_elems( int pos );
	int _length;
	int _beg_pos;
	vector<int> _elems;
		
};

int Fibonacci::
elem (int pos ) 
{
	if ( ! check_integrity(pos, _elems.size()) ){
		return 0;
	}
	if ( pos > _elems.size() ) {
		Fibonacci::gen_elems( pos );
	}
	
	return _elems[ pos - 1 ];
}

void Fibonacci::gen_elems(int pos)
{
	if ( _elems.empty() ) 
	{
		_elems.push_back(1);
		_elems.push_back(1);
	}
	if ( _elems.size() <= pos ) 
	{
		int ix = _elems.size();
		int n_2 = _elems[ ix - 2];
		int n_1 = _elems[ ix - 1];
		
		for ( ; ix <= pos; ++ix )
		{
			int elem = n_2 + n_1;
			_elems.push_back( elem );
			n_2 = n_1; n_1 = elem;
		}
	}
}

ostream& Fibonacci::
print( ostream &os )
{
	int elem_pos = _beg_pos - 1;
	int end_pos = elem_pos + _length;

	if ( end_pos > _elems.size() )
	{
		Fibonacci::gen_elems( end_pos );
	}
	while ( elem_pos < end_pos )
	{
		os << _elems[ elem_pos++ ] << ' ';
	}
	return os;
}


int main()
{
	Fibonacci fib;
    cout << "fib: begining at element 1 for 1 elements: " << fib << endl;

	Fibonacci fib2( 16 ); 
	cout <<  "fib: begining at element 1 for 16 elements: "	<< fib2 << endl;

	Fibonacci fib3( 8, 12 ); 
	cout <<  "fib: begining at element 12 for 8 elements: "	<< fib3 << endl;

	return 0;
}



