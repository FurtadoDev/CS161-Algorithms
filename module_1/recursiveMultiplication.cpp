//============================================================================
// Name        : recursiveMultiplication.cpp
// Author      : Veinstin Furtado
// Version     :
// Copyright   : Your copyright notice
// Description : Recursive Multiplication in C++, Ansi-style
//============================================================================

#include<iostream>
#include<string.h>
using namespace std;

//function to reverse a string
string string_reverse(string input){
	int str_len = input.length();
	char temp;
	for(int i = 0; i <= (str_len-1)/2; i++ ){
		temp = input.at(str_len-1-i);
		input.at(str_len-1-i) = input.at(i);
		input.at(i) = temp;
	}
	return input;
}

//function to find the sum of two multiple-digit numbers
string findSum(string num1, string num2){

	int input_str_len;
	int sum = 0;
	int carry = 0;
	string result;

	//check to make sure both strings are of equal length
	while(num1.length() < num2.length()){
		num1.insert(0,"0");
	}
	while(num2.length() < num1.length()){
		num2.insert(0,"0");
	}

	//Add the two strings and store the result in string variable result
	input_str_len = num1.length();
	for(int i = input_str_len-1; i >= 0; i--){
		sum = (num1.at(i) - '0') + (num2.at(i) - '0') + carry;
		result.push_back(sum%10+'0');
		carry = sum/10;
	}
	if(carry != 0)
		result.push_back(carry+'0');

	//Reverse the the string stored in result
	result = string_reverse(result);

	return result;
}

//function to find the product of two single digit integers
string singleDigitProduct(string num1, string num2){
	string result;
	int product;
	int carry;
	product = (num1.at(0) - '0') * (num2.at(0) - '0');
	carry = product/10;
	result.push_back(product%10 + '0');
	if(carry != 0){
		result.push_back(carry + '0');
		result = string_reverse(result);
	}
	return result;
}

//Recursive multiplication
string RecursiveMultiply(string x, string y){
	string a;
	string b;
	string c;
	string d;
	string ac;
	string ad;
	string bc;
	string bd;
	string ad_bc;
	string final_result;
	int n;
	int str_len_x;
	int str_len_y;

	//Stopping Condition
	if((x.length() != 1) || (y.length() != 1)){
		//check to make sure both strings are of equal length
		while(x.length() < y.length()){
			x.insert(0,"0");
		}
		while(y.length() < x.length()){
			y.insert(0,"0");
		}
		str_len_x = x.length();
		str_len_y = y.length();

		//Check to see if the strings have even number of characters
		if(str_len_x%2 == 0){
			a = x.substr(0, str_len_x/2);
			b = x.substr(str_len_x/2, str_len_x/2);
			c = y.substr(0, str_len_y/2);
			d = y.substr(str_len_y/2, str_len_y/2);
			n = str_len_x;
		}else{
			a = x.substr(0, str_len_x/2);
			b = x.substr(str_len_x/2, (str_len_x + 1)/2);
			c = y.substr(0, str_len_y/2);
			d = y.substr(str_len_y/2, (str_len_y + 1)/2);
			n = str_len_x+1;
		}

		ac = RecursiveMultiply(a, c);
		ad = RecursiveMultiply(a, d);
		bc = RecursiveMultiply(b, c);
		bd = RecursiveMultiply(b, d);
		ad_bc = findSum(ad,bc);
		if(ac.compare("0") != 0){
			for(int i = 0; i < n; i++){
				ac.push_back('0');
			}
		}
		if(ad_bc.compare("0") != 0){
			for(int i = 0; i < n/2; i++){
				ad_bc.push_back('0');
			}
		}

		ac = findSum(ac, ad_bc);
		ac = findSum(ac, bd);

		return ac;
	}else{
		return singleDigitProduct(x, y);
	}



}

// DRIVER CODE
int main()
{
    string x = "3141592653589793238462643383279502884197169399375105820974944592";
    string y = "2718281828459045235360287471352662497757247093699959574966967627";
	//string x = "1234";
	//string y = "5678";
    cout << RecursiveMultiply(x,y) << endl;

    return 0;
}