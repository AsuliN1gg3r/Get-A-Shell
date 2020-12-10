// Created by Eyal Asulin™
#pragma once

#include <iostream>
#include <time.h>

#define LIMIT 10000


class RSA
{
	std::pair<int, int> _publicKey;
	std::pair<int, int> _privateKey;
	
	static int _logPower(int n, int p, int mod);
	bool _rabinMiller(int n);
	int _gcd(int num1, int num2);
	int _generateCoprime(int num);
	int _generatePrime();
	std::pair<int, int> _euclidExtended(int a, int b);
	int _modularInverse(int n, int mod);

public:
	RSA();
	std::pair<int, int> getPublicKey() { return this->_publicKey; };
	std::string decrypt(int* encodedMsg);
	static int* encrypt(std::pair<int, int> publicKey, std::string msg);
};