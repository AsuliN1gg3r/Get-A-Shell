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

public:
	RSA();
	long int getPublicKey();
	std::string decode(std::string encodedMsg);
	static std::string encrypt(long int publicKey, long int primeMul, std::string msg);
};