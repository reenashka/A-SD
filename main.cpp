#include <vector>
#include <fstream>
#include <string>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <iostream>


using namespace std;

struct BigInt
{
public:

	//пустой конструктор 
	BigInt()
	{
		number.resize( 1 );
		number[0] = 0;
	}

	// инициализация 
	BigInt( string s )
	{
		if ( s[0] == '-' && s[1] == '0' )
		{
			for ( int i = 1; i < s.size(); i++ )
			{
				number.push_back( s[i] - '0' );
			}
		}
		else

			if ( s[0] == '-' )
			{
				is_negative = true;
				for ( int i = 1; i < s.size(); i++ )
				{
					number.push_back( s[i] - '0' );
				}
			}
			else
			{
				for ( auto digit : s )
				{
					number.push_back( digit - '0' );
				}
			}

		reverse( number.begin(), number.end() );
	}

	BigInt( vector<int> number )
	{
		this->number = number;
	}

	BigInt( long long number )
	{
		while ( number )
		{
			this->number.push_back( number % base );
			number /= base;
		}
	}

	//функция для вывода числа в обратном порядке
	void write_reversed() const
	{
		for ( auto digit : number )
		{
			cout << digit;
		}
		cout << "\n";
	}

	//функция для вывода числа
  /*  void write() const {

	  if(is_negative){
		fout << "-";
	  }

	  for(int i = number.size() - 1; i >= 0; i--){
		fout << number[i];
	  }
	  //fout << "\n";
	  fout.close();
	}*/

	//функция для вывода длины числа
	void lenght_num() const
	{
		int len = number.size();
		cout << len;
		cout << "\n";
	}

	friend BigInt operator + (  BigInt& a,  BigInt& b );
	friend BigInt operator - (  BigInt& a,  BigInt& b );
	friend BigInt operator * (  BigInt& a,  BigInt& b );
	friend BigInt operator / (   BigInt& a,  BigInt& b );
	friend bool operator <= (  BigInt& a,  BigInt& b );
	friend bool operator >= (  BigInt& a,  BigInt& b );
	friend bool operator == ( const BigInt& a, const BigInt& b );
	friend bool operator > (  BigInt& a,  BigInt& b );
	friend bool operator < (  BigInt& a,  BigInt& b );
	//BigInt& operator = ( const BigInt& a);
	bool is_negative = false;

	int base = 10;
	vector<int> number;
	
};

//СЛОЖЕНИЕ
BigInt operator + ( BigInt& a, BigInt& b )
{
	if ( !a.is_negative && !b.is_negative )
	{
		vector<int> result;
		int carry = 0;
		for ( int i = 0; i < min( a.number.size(), b.number.size() ); i++ )
		{
			int cur_sum = carry + a.number[i] + b.number[i];
			result.push_back( cur_sum % 10 );
			carry = cur_sum / 10;

		}
		for ( int i = min( a.number.size(), b.number.size() ); i < max( a.number.size(), b.number.size() ); i++ )
		{
			if ( a.number.size() > b.number.size() )
			{
				int cur_sum = carry + a.number[i];
				result.push_back( cur_sum % 10 );
				carry = cur_sum / 10;
			}
			else
			{
				int cur_sum = carry + b.number[i];
				result.push_back( cur_sum % 10 );
				carry = cur_sum / 10;
			}
		}
		if ( carry != 0 )
		{
			result.push_back( carry );
		}

		BigInt c( result );
		return c;
	}
	else if ( !a.is_negative && b.is_negative )
	{
		b.is_negative = false;

		if ( a >= b )
		{
			BigInt res = a - b;

			b.is_negative = true;
			return res;
		}
		else
		{
			BigInt res = b - a;
			b.is_negative = true;
			res.is_negative = true;

			return res;
		}


	}
	else if ( a.is_negative && !b.is_negative )
	{
		a.is_negative = false;
		if ( b >= a )
		{
			BigInt res = b - a;
			a.is_negative = true;
			return res;
		}
		else
		{
			BigInt res = b - a;
			a.is_negative = true;
			res.is_negative = true;
			return res;
		}
	}
	else
	{
		a.is_negative = false;
		b.is_negative = false;
		BigInt res = a + b;
		a.is_negative = true;
		b.is_negative = true;
		res.is_negative = true;
		return res;
	}

}

//ВЫЧИТАНИЕ
BigInt operator - ( BigInt& a, BigInt& b )
{
	if ( !a.is_negative && !b.is_negative )
	{
		if ( a < b )
		{
			BigInt res = b - a;
			res.is_negative = true;
			return res;
		}
		vector<int> result;
		int carry = 0;
		for ( int i = 0; i < b.number.size(); i++ )
		{
			int cur_diff = a.number[i] - b.number[i] - carry;

			if ( cur_diff < 0 )
			{
				cur_diff += 10;
				carry = 1;
			}
			else
			{
				carry = 0;
			}
			result.push_back( cur_diff );
		}
		for ( int i = b.number.size(); i < a.number.size(); i++ )
		{
			if ( a.number[i] - carry < 0 )
			{
				result.push_back( a.number[i] + 10 - carry );
				carry = 1;
			}
			else
			{
				result.push_back( a.number[i] - carry );
				carry = 0;
			}
		}
		if ( carry != 0 )
		{
			result.push_back( carry );
		}
		while ( !result.back() && result.size() > 1 )
		{
			result.pop_back();
		}
		BigInt d( result );
		return d;
	}

	else if ( !a.is_negative && b.is_negative )
	{
		b.is_negative = false;
		BigInt res = a + b;
		b.is_negative = true;
		return res;
	}
	else if ( a.is_negative && !b.is_negative )
	{
		a.is_negative = false;

		BigInt res = a + b;
		res.is_negative = true;
		a.is_negative = false;
		return res;

	}
	else if ( a.is_negative && b.is_negative )
	{

		a.is_negative = false;
		b.is_negative = false;
		if ( a >= b )
		{
			BigInt res = a - b;

			a.is_negative = false;
			b.is_negative = false;
			return res;
		}
		else
		{
			BigInt res = a + b;

			a.is_negative = false;
			b.is_negative = false;
			res.is_negative = true;
			return res;
		}
	}
}

//УМНОЖЕНИЕ
BigInt operator * ( BigInt& a, BigInt& b )
{
	if ( a.is_negative == b.is_negative )
	{
		vector<int> result( a.number.size() * b.number.size(), 0 );

		for ( int i = 0; i < a.number.size(); i++ )
		{
			int carry = 0;

			for ( int j = 0; j < b.number.size(); j++ )
			{
				int cur = result[i + j] + a.number[i] * b.number[j] + carry;
				carry = cur / a.base;
				result[i + j] = cur % a.base;
			}

			int cur = b.number.size();
			while ( carry )
			{
				result[i + cur] = carry % a.base;
				cur++;
				carry /= a.base;
			}
		}
		while ( !result.back() && result.size() > 1 )
		{
			result.pop_back();
		}
		BigInt e( result );
		return e;
	}
	else
	{
		if ( a.is_negative && !b.is_negative )
		{
			a.is_negative = false;
			BigInt res = a * b;
			a.is_negative = true;
			res.is_negative = true;
			return res;
		}
		else if ( !a.is_negative && b.is_negative )
		{
			b.is_negative = false;
			BigInt res = a * b;
			b.is_negative = true;
			BigInt zero( "0" );
			if ( !(res == zero) )
			{
				res.is_negative = true;
			}
			return res;
		}
	}
}

//ДЕЛЕНИЕ
BigInt operator / (  BigInt& a,  BigInt& b )
{

	BigInt zero( "0" );
	if ( b == zero )
	{
		BigInt res( "-1" );
		return res;
	}
	
	if ( !a.is_negative && !b.is_negative )
	{
		vector<int> result( a.number.size() - b.number.size() + 1, 0 );
		BigInt c( result );

		BigInt k;

		BigInt res = 0;

		if ( a <= b )
		{
			return zero;
		}

		BigInt one( "1" );
		while ( !(a <= zero) )
		{
			res = a - b;
			k = k + one;
			a = res;

		}
		return k;
	}
	
	else if ( !a.is_negative && b.is_negative )
	{
		b.is_negative = false;
		if ( a <= b )
		{
			return zero;
		}
		BigInt res = a / b;
		res.is_negative = true;
		b.is_negative = true;
		return res;
	}
	
	else if ( a.is_negative && !b.is_negative )
	{
		a.is_negative = false;
		if ( a <= b )
		{
			return zero;
		}
		BigInt res = a / b;
		res.is_negative = true;
		a.is_negative = true;
		return res;
	}
	
	else if ( a.is_negative && b.is_negative )
	{
		a.is_negative = false;
		b.is_negative = false;
		if ( a <= b )
		{
			return zero;
		}
		BigInt res = a / b;

		a.is_negative = true;
		b.is_negative = true;

		return res;
	}

	
}

//СРАВНЕНИЕ <=
bool operator <= ( BigInt& a, BigInt& b )
{
	// -5 <= 10
	if ( a.is_negative && !b.is_negative )
	{
		return true;
	}// 5 <= -10
	else if ( !a.is_negative && b.is_negative )
	{
		return false;
	}

	else
	{    // -5 <= -10 == false  5 < 10
		if ( a.is_negative && b.is_negative )
		{
			a.is_negative = false;
			b.is_negative = false;
			bool ans = a >= b;
			a.is_negative = true;
			b.is_negative = true;
			return ans;
		}

		if ( a.number.size() < b.number.size() )
		{
			return true;
		}

		else if ( a.number.size() > b.number.size() )
		{
			return false;
		}
		for ( int i = a.number.size() - 1; i >= 0; i-- )
		{

			if ( a.number[i] > b.number[i] )
			{
				return false;
			}

			if ( a.number[i] < b.number[i] )
			{
				return false;
			}

		}
		return true;
	}

}
//СРАВНЕНИЕ >=
bool operator >= ( BigInt& a, BigInt& b )
{
	if ( !a.is_negative && b.is_negative )
	{
		return true;
	}
	else if ( a.is_negative && !b.is_negative )
	{
		return false;
	}
	else
	{
		if ( a.is_negative && b.is_negative )
		{
			a.is_negative = false;
			b.is_negative = false;
			bool ans = a <= b;
			a.is_negative = true;
			b.is_negative = true;
			return ans;
		}

		if ( a.number.size() > b.number.size() )
		{
			return true;
		}

		else if ( a.number.size() < b.number.size() )
		{
			return false;
		}
		for ( int i = a.number.size() - 1; i >= 0; i-- )
		{

			if ( a.number[i] < b.number[i] )
			{
				return false;
			}
		}
		return true;
	}
}
//СРАВНЕНИЕ ==
bool operator == ( const BigInt& a, const BigInt& b )
{
	if ( a.is_negative != b.is_negative )
	{
		return false;
	}
	else
	{
		if ( a.number.size() != b.number.size() )
		{
			return false;
		}
		for ( int i = a.number.size() - 1; i >= 0; i-- )
		{
			if ( a.number[i] != b.number[i] )
			{
				return false;
			}
		}
		return true;
	}
}
//СРАВНЕНИЕ <
bool operator < (  BigInt& a,  BigInt& b )
{
	
	if ( a.is_negative && !b.is_negative )
	{
		return true;
	}
	else if ( !a.is_negative && b.is_negative )
	{
		return false;
	}
	else
	{
		if ( a.is_negative && b.is_negative )
		{
			a.is_negative = false;
			b.is_negative = false;
			bool ans = a > b;
			a.is_negative = true;
			b.is_negative = true;
			return ans;
		}


		if ( a.number.size() < b.number.size() )
		{
			return true;
		}
		else if ( a.number.size() > b.number.size() )
		{
			return false;
		}

		for ( int i = a.number.size() - 1; i >= 0; i-- )
		{

			if ( a.number[i] >= b.number[i] )
			{
				return false;
			}
		}
		return true;
	}

}
//СРАВНЕНИЕ >
bool operator > ( BigInt& a, BigInt& b )
{
	if ( a.is_negative && !b.is_negative )
	{
		return false;
	}
	else if ( !a.is_negative && b.is_negative )
	{
		return true;
	}
	else
	{
		if ( a.is_negative && b.is_negative )
		{
			a.is_negative = false;
			b.is_negative = false;
			bool ans = a < b;
			a.is_negative = true;
			b.is_negative = true;
			return ans;
		}
		else
		{
			if ( a.number.size() > b.number.size() )
			{
				return true;
			}
			if ( a.number.size() < b.number.size() )
			{
				return false;
			}
			for ( int i = a.number.size() - 1; i >= 0; i-- )
			{
				if ( a.number[i] <= b.number[i] )
				{
					return false;
				}
			}
			return true;
		}
	}
}


void Test( int cnt_tests )
{
	for ( int i = 1; i <= cnt_tests; i++ )
	{

		string i_str = to_string( i );

		ifstream fin( to_string( i ) + ".in" );
		ofstream fout( to_string( i ) + ".out" );

		string number1, number2, operand, number_ans;

		fin >> number1 >> operand >> number2;


		BigInt a( number1 ), b( number2 );

		BigInt res = 0;

		bool ans = false;
		bool flag = false;
		if ( operand == "+" )
		{
			res = a + b;
		}

		else if ( operand == "/" )
		{
			res = a / b;
		}

		else if ( operand == "-" )
		{
			res = a - b;
		}
		else if ( operand == "*" )
		{
			res = a * b;
		}
		else if ( operand == ">=" )
		{
			flag = true;
			ans = (a >= b);
		}

		else if ( operand == ">" )
		{
			flag = true;
			ans = (a > b);
		}
		else if ( operand == "<" )
		{
			flag = true;
			ans = (a < b);
		}
		else if ( operand == "<=" )
		{
			flag = true;
			ans = (a <= b);
		}
		else if ( operand == "==" )
		{
			flag = true;
			ans = (a == b);
		}

		
		if ( flag )
		{
			fout << ans;
		}
		else
		{
			if ( res.is_negative )
			{
				fout << "-";
			}

			for ( int j = res.number.size() - 1; j >= 0; j-- )
			{
				fout << res.number[j];
			}
		}

		

		fout.close();
		fin.close();

		ifstream finres( i_str + ".out" );

		ifstream fans( i_str + ".ans" );
		string number_out;

		finres >> number_out;


		fans >> number_ans;
		if ( number_out == number_ans )
		{
		    cout << to_string( i ) + " Ok\n";
		}
		else
		{
			cout << to_string( i ) + " WA \t" << number1 << " " << operand << " " << number2 << endl;;
		}

		fans.close();
		finres.close();

	}
}

void Write()
{
	ifstream main( "main.txt" );

	int n;
	string value1, operand, value2, result;
	main >> n;
	for ( int i = 0; i < n; i++ )
	{
		ofstream fin( to_string( i + 1 ) + ".in" );
		ofstream fans( to_string( i + 1 ) + ".ans" );
		main >> value1 >> operand >> value2 >> result;
		string s = value1 + " " + operand + " " + value2;
		fin << s;
		fans << result;
		fin.close();
		fans.close();

		ifstream fiout( to_string( i + 1 ) + ".out" );
		fiout.close();
		ofstream fout( to_string( i + 1 ) + ".out" );
		fout.close();
	}
}

int main()
{
	int cnt_tests = 91;
	Test( cnt_tests );

}