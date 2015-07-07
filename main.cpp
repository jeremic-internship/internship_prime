#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

bool isPrime(int num) {
	if (std::find(primes.begin(), primes.end(), num) != primes.end()) {
		return true;
	}
	for(int i = 2; i < (num-1); i++){
		if(num%i == 0){
			return false;
		}
	}
	primes.push_back(num);
	return true;
}

vector<int> getPrimeFactorization(int num, vector<int> startVector) {
	vector<int> returnVector = startVector;
	for (int i = 0; i < primes.size(); i++) {
		if (num % primes[i] == 0) {
			returnVector.push_back(num/primes[i]);
			num = num/primes[i];
			if (isPrime(num)) {
				returnVector.push_back(num);
				return returnVector;
			} else {
				getPrimeFactorization(num, returnVector);
			}
		}
	}
	for (int i = 2; i <= (num-1); i++) {
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