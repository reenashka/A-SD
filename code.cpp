#include <vector>
#include <string>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct BigInt{
public:
  
  //пустой конструктор 
  BigInt(){
    number.resize(1);
    number[0] = 0;
  }

  // инициализация 
  BigInt(string s){
    // аналогично
    // for (int i = 0; i < s.lenght(); i++){
    //  digit = s[i];
    //}
    for(auto digit : s){
      number.push_back(digit - '0');
    }
    reverse(number.begin(), number.end());
  }

  BigInt(vector<int> number){
    this->number = number;
  }

  BigInt(long long number){
    while(number){
      this->number.push_back(number % base);
      number /= base;
    }
  }

  //функция для вывода числа в обратном порядке
  void write_reversed() const {
    for(auto digit : number){
      cout << digit;
    }
    cout << "\n";
  }

  //функция для вывода числа
  void write() const {
    for(int i = number.size() - 1; i >= 0; i--){
      cout << number[i];
    }
    cout << "\n";
  }

  friend BigInt operator + (const BigInt &a, const BigInt &b) ;
  friend BigInt operator - (const BigInt &a, const BigInt &b) ;

private:
  int base = 10;
  vector<int> number;
};

//СЛОЖЕНИЕ
BigInt operator + (const BigInt &a, const BigInt &b) {
    
  vector<int> result;
  int carry = 0;
  
  for(int i = 0; i < min(a.number.size(), b.number.size()); i++){
    int cur_sum = carry + a.number[i] + b.number[i];
    result.push_back(cur_sum % 10);
    carry = cur_sum / 10;
 
  }
  
  for(int i = min(a.number.size(), b.number.size()); i < max(a.number.size(), b.number.size()); i++){
    
    if(a.number.size() > b.number.size()){
      int cur_sum = carry + a.number[i];
      result.push_back(cur_sum % 10);
      carry = cur_sum / 10;
    
    }
    
    else{
      int cur_sum = carry + b.number[i];
      result.push_back(cur_sum % 10);
      carry = cur_sum / 10;
    
    }
  
  }

  if(carry != 0){
    result.push_back(carry);
  }
  
  BigInt c(result);
  return c;
}

//ВЫЧИТАНИЕ
BigInt operator - (const BigInt &a, const BigInt &b) {
    
  vector<int> result;
  int carry = 0;
  
  for(int i = 0; i < b.number.size(); i++){
    int cur_diff = a.number[i] - b.number[i] - carry;

    if(cur_diff < 0){
      cur_diff += 10;
      carry = 1;
    }
      
    else{
      carry = 0;
    }
    
    result.push_back(cur_diff);
  }
  
  for(int i = b.number.size(); i < a.number.size(); i++){
    
    if(a.number[i] - carry < 0){
      result.push_back(a.number[i] + 10 - carry);
      carry = 1;
    }

    else{
      result.push_back(a.number[i] - carry);
      carry = 0;
    }
    
  }

  if(carry != 0){
    result.push_back(carry);
  }

  while(!result.back() && result.size() > 1){
    result.pop_back();
  }
  
  BigInt d(result);
  return d;
}
int main(){
  
  BigInt a("1256");
  BigInt b(354);
  
  BigInt c = a + b;
  BigInt d = a - b;
  c.write();
  d.write();
  return 0;
  
}