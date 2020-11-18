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

long int cd(long int a, long int phi)
{
    long int k = 1;
    while (1)
    {
        k = k + phi;
        if (k % a == 0)
            return(k / a);
    }
}

RSA::RSA()
{
    srand(time(NULL));

    int prime1 = 7, prime2 = 13; // this->_randPrimeNumber(), prime2 = this->_randPrimeNumber();
    this->_primeMul = prime1 * prime2;
    long int phi = (prime1 - 1) * (prime2 - 1); //t
    std::cout << "phi: " << phi << std::endl;

    // Calculating keys
    int k = 0;
    for (int i = 2; i < phi; i++)
    {
        if (phi % i == 0)
        {
            continue;
        }
        if (this->_primeNumberCheck(i) && i != prime1 && i != prime2)
        {
            this->_publicKey[k] = i;
            if (cd(_publicKey[k], phi) > 0)
            {
                _privateKey[k] = cd(_publicKey[k], phi);
                k++;
            }
            if (k == 99)
                break;
        }
        
    }

    // encrypt
    long int  temp[50];
    char m[] = "abcdefg", en[50];
    long int pt, ct, key = _publicKey[0];
    int len = strlen(m);
    int i = 0;
    while (i != len)
    {
        pt = m[i];
        pt -= 96;
        k = 1;
        for (int j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % _primeMul;
        }

        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    std::cout << "\n\nTHE ENCRYPTED MESSAGE IS\n";
    for (i = 0; en[i] != -1; i++)
        std::cout << en[i];

    // decrypt

    key = _privateKey[0];
    i = 0;
    while (en[i] != -1)
    {
        ct = temp[i];
        k = 1;
        for (int j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % _primeMul;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    std::cout << "\n\nTHE DECRYPTED MESSAGE IS\n";
    for (i = 0; m[i] != -1; i++)
        std::cout << m[i];

    std::cout << std::endl;
}
