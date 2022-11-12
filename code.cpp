#include <vector>
#include <string>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;

class big_integer {

	static const int BASE = 1000000000;

  big_integer(string str);
  void _remove_leading_zeros();

	vector<int> _digits;

	bool _is_negative;
};

//удаление нулей
void big_integer::_remove_leading_zeros(){

  while(this->_digits.size() > 1 && this->_digits.size() == 0){
    this->_digits.pop_back();
  }
  
  if (this->_digits.size() == 1 && this->_digits[0] == 0) {
    this->_is_negative = false;
  }
  
}

//создание числа
big_integer::big_integer(string str) {

  if(str.size() == 0){
    this->_is_negative = false;
  }

  else{
    
    if(str[0] == '-'){
      str = str.substr(1);
      this->_is_negative = true;
    }

    else{
      this->_is_negative = false;
    }

    for(long long i = str.size(); i > 0; i -= 9){
      
      if (i < 9){
        this->_digits.push_back(atoi(str.substr(0, i).c_str())); //переводим строку в число и отсылаем в вектор
      }

      else{
        this->_digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
      }

       this->_remove_leading_zeros(); //удаление нулей
      
    }
  }
  
}

