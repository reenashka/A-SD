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

  BigInt operator + (const BigInt &a){
    
    vector<int> result;
    int carry = 0;
    
    for(int i = 0; i < min(a.number.size(), this->number.size()); i++){
      int cur_sum = carry + a.number[i] + this->number[i];
      result.push_back(cur_sum % 10);
      carry = cur_sum / 10;
   
    }
    
    for(int i = min(a.number.size(), this->number.size()); i < max(a.number.size(), this->number.size()); i++){
      
      if(a.number.size() > this->number.size()){
        int cur_sum = carry + a.number[i] + this->number[i];
        result.push_back(cur_sum % 10);
        carry = cur_sum / 10;
      
      }
      
      else{
        int cur_sum = carry + this->number[i];
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

private:
  vector<int> number;
};

int main(){
  
  BigInt a("1234567890987654321");
  BigInt b("55555");
  
  BigInt c = a + b;
  c.write();
  return 0;
  
}