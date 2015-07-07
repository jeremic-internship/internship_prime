#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

bool isPrime(int num) {
	for(int i = 2; i < (num-1); i++){
		if(num%i == 0){
			return false;
		}
	}
	return true;
}

vector<int> getPrimeFactorization(int num, vector<int> startVector) {
	vector<int> returnVector = startVector;
	for (int i = (num-1); i >= 2; i--) {
		if (num%i == 0) {
			returnVector.push_back(num/i);
			num = i;
			if (isPrime(num)) {
				returnVector.push_back(num);
				return returnVector;
			} else {
				getPrimeFactorization(num, returnVector);
			}
		}
	}
}

int main() {
	vector<int> dataVector;

	std::ifstream t("data.dat");
	std::string fileText((std::istreambuf_iterator<char>(t)),
	std::istreambuf_iterator<char>());

	stringstream ssin(fileText);

	while (ssin.good()) {
		string tmp;
		ssin >> tmp;
		dataVector.push_back(atoi(tmp.c_str()));
	}

	dataVector.erase(dataVector.end() - 1); // Fix bug where EOF == 0

	for (int i = 0; i < dataVector.size(); i++) {
		if (isPrime(dataVector[i])) {
			printf("The given number %i is prime\n", dataVector[i]);
		} else {
			cout << "The prime factorization is " << dataVector[i] << " = ";
			vector<int> tmpVector;
			vector<int> path = getPrimeFactorization(dataVector[i], tmpVector);
			for(int z=0; z<path.size(); ++z) {
				if (z != 0) {
					cout << "*";
				}
				cout << path[z];
			}
			cout << "\n";
		}
	}

}