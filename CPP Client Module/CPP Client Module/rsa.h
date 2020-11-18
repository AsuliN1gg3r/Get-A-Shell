#pragma once

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <time.h>

#define RAND_MIN 5
#define RAND_MAX 180

class RSA
{
	long int _privateKey;
	long int _publicKey;
	long int _primeMul;
	bool _primeNumberCheck(int num);
	int _randPrimeNumber();
	int _gcd(int num1, int num2);

public:
	RSA();
	std::string getPublicKey();
	std::string decode();
	static std::string encrypt(std::string publicKey);
};