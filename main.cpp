#include <vector>
#include <fstream>
#include <string>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

ifstream fin("1.in");
ofstream fout("1.out");

struct BigInt{
public:
  
  //пустой конструктор 
  BigInt(){
    number.resize(1);
    number[0] = 0;
  }

  // инициализация 
  BigInt(string s){
    
    if(s[0] == '-'){
      is_negative = true;
    }
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
   
    if(is_negative){
      fout << "-";
    }
    
    for(int i = number.size() - 1; i >= 0; i--){
      fout << number[i];
    }
    //fout << "\n";
    fout.close();
  }

  //функция для вывода длины числа
  void lenght_num() const{
    int len = number.size();
    cout << len;
    cout << "\n";
  }

  friend BigInt operator + (const BigInt &a, const BigInt &b) ;
  friend BigInt operator - (const BigInt &a, const BigInt &b) ;
  friend BigInt operator * (const BigInt &a, const BigInt &b) ;
  friend BigInt operator / (const BigInt &a, const BigInt &b) ;
  friend bool operator <= (const BigInt &a, const BigInt &b) ;

private:
  int base = 10;
  vector<int> number;
  bool is_negative = false;
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

//УМНОЖЕНИЕ
BigInt operator * (const BigInt &a, const BigInt &b) {
    
  vector<int> result(a.number.size() * b.number.size(), 0);
  
  for(int i = 0; i < a.number.size(); i++){
    int carry = 0;

    for(int j = 0; j < b.number.size(); j++){
      int cur = result[i + j] + a.number[i] * b.number[j] + carry;
      carry = cur / a.base;
      result[i+j] = cur % a.base;
    }

    int cur = b.number.size();
    while(carry){
      result[i+cur] = carry % a.base;
      cur++;
      carry /= a.base;
    }
  }

  while(!result.back() && result.size() > 1){
    result.pop_back();
  }
  
  BigInt e(result);
  return e;
}

//ДЕЛЕНИЕ
BigInt operator / (const BigInt &a, const BigInt &b) {
    
  vector<int> result(a.number.size() - b.number.size() + 1, 0);
  BigInt c(result);
  
  for(int i = result.size() - 1; i >= 0; i--){
    
    while(b * c <= a){
      c.number[i]++;
    }
    c.number[i]--;
  }
  
  while(c.number.size() > 1 && !c.number.back()){
    c.number.pop_back();
  }
  
  return c;
}

//СРАВНЕНИЕ
bool operator <= (const BigInt &a, const BigInt &b) {

  if(a.number.size() < b.number.size()){
    return true;
  }

  else if(a.number.size() > b.number.size()){
    return false;
  }

  else{
    for(int i = a.number.size() - 1; i >= 0; i++){

      if(a.number[i] > b.number[i]){
        return false;
      }

      if(a.number[i] < b.number[i]){
        return false;
      }
      
    }
    return true;
  }
  
}

int main(){

  ifstream fans("1.ans");
  
  string number1, number2, operand, number_ans;
  fin >> number1 >> operand >> number2;
  fans >> number_ans;

  BigInt a(number1), b(number2);

  BigInt res = 0;
  if(operand == "+") { 
    res = a + b;
  }
  else if(operand == "/") { 
    res = a / b;
  }

  res.write();

  ifstream finres("1.out");
  
  string number_out;
  finres >> number_out;

  if(number_out == number_ans){
    cout << "Ok";
  }
  else{
    cout << "WA";
  }
  
  return 0;
  
}