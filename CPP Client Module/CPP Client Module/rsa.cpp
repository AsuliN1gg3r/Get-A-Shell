#include "rsa.h"

// This function checks if a number is prime
bool RSA::_primeNumberCheck(int num)
{
    int max = sqrt(num);
    for (int i = 2; i <= max; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int RSA::_randPrimeNumber()
{ 
    int primeNumber = 0;
    while (primeNumber % 2 == 0) // Rand odd number
    {
        primeNumber = rand() % RAND_MAX + RAND_MIN;
    }

    while (!this->_primeNumberCheck(primeNumber)) // Search for prime number
    {
        primeNumber += 2;
    }

    return primeNumber;
}

int RSA::_gcd(int num1, int num2)
{
    int temp;
    while (true)
    {
        temp = num1 % num2;
        if (temp == 0)
        {
            return num2;
        }
        num1 = num2;
        num2 = temp;
    } 
}

RSA::RSA()
{
    srand(time(NULL));

    int prime1 = this->_randPrimeNumber(), prime2 = this->_randPrimeNumber();
    this->_primeMul = prime1 * prime2;
    long int phi = (prime1 - 1) * (prime2 - 1);
    std::cout << "phi: " << phi << std::endl;

    // Calculating public key
    this->_publicKey = (prime1 + prime2) / 2;
    for (long int i = 1; i < phi; i++)
    {
        if (this->_gcd(this->_publicKey, phi) == 1 && this->_publicKey != prime1 && this->_publicKey != prime2)
        {
            std::cout << "public key: " << this->_publicKey << std::endl;
            break;
        }
        else
        {
            this->_publicKey++;
        }
    }

    // Calculating private key
    this->_privateKey = 1 / (this->_publicKey % phi);
    //this->_privateKey = fmod(this->_privateKey, phi);
    std::cout << "private key: " << this->_privateKey << std::endl;

    int message = 9;
    std::cout << "original message: " << message << std::endl;

    long int c = pow(message, this->_publicKey);
    c = c % this->_primeMul;
    long int m = pow(c, this->_privateKey);
    
    std::cout << "encoded message: " << c << std::endl;

    
    m = m % this->_primeMul;
    std::cout << "decoded message: " << m << std::endl;
}
