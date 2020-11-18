#pragma once

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <time.h>

#define RAND_MIN 5
#define RAND_MAX 180
#define KEY_LENGTH 50

class RSA
{
	long int _privateKey[KEY_LENGTH];
	long int _publicKey[KEY_LENGTH];
	long int _primeMul; //n
	bool _primeNumberCheck(int num);
	int _randPrimeNumber();

public:
	RSA();
	std::string getPublicKey();
	std::string decode();
	static std::string encrypt(std::string publicKey);
};