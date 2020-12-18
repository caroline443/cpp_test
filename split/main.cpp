#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Token {
	int sign;
	string tokenStr;
public:
	Token();
	Token(int s, string str);
	Token* inIt(int s, string str);
	string getToken();
	int getSign();
};

Token::Token() {
	sign = -1;
}
Token::Token(int s, string str) {
	sign = s;
	tokenStr.assign(str);
}
Token* Token::inIt(int s, string str) {
	sign = s;
	tokenStr.assign(str);
	return this;
}
string Token::getToken() {
	return tokenStr;
}
int Token::getSign() {
	return sign;
}

bool Split(string str, vector<Token> &token) {
	int strLength = str.length();
	Token tempToken;
	string strNum;
	string strChar;
	string strOpe;
	int numVal = 0, opeVal = 1;

	for (int i = 0; i < strLength; i++) {
		if (str[i] <= '9' && str[i] >= '0' ) {
			for (int j = i; j < strLength; j++) {
				if (str[j] > '9' || str[j] < '0') {
					strNum.assign(str, i, j - i);
					tempToken.inIt(numVal, strNum);
					i = j - 1;
					break;
				}
			}
		}
		else if (str[i] <= 'z' && str[i] >= 'a') {
			for (int j = i; j < strLength; j++) {
				if (str[j] > 'z' || str[j] < 'a') {
					strChar.assign(str, i, j - i);
					tempToken.inIt(opeVal, strChar);
					i = j - 1;
					break;
				}
			}
		}
		else {
			strOpe.assign(str, i, 1);
			tempToken.inIt(opeVal, strOpe);
		}
		
		token.push_back(tempToken);
	}
	return true;
}

int main() {
	string str("(1+2*sin&3)");
	vector<Token> token;
	Split(str, token);
	for (unsigned int i = 0; i < token.size(); i++) {
		cout << token[i].getSign() << " " << token[i].getToken() << endl;
	}
	return 0;
}