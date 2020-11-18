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
    long int phi = (prime1 - 1) * (prime2 - 1); 

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
            this->_publicKey = i;
            if (cd(_publicKey, phi) > 0)
            {
                _privateKey = cd(_publicKey, phi);
                break;
            }
        }
        
    }

    std::cout << _publicKey << "\t" << _privateKey << std::endl;

    // encrypt
    /*long int temp[50];
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
    en[i] = -1;*/

    std::cout << "\n\nTHE ENCRYPTED MESSAGE IS\n";
    std::string encoded = encrypt(this->_publicKey, this->_primeMul, "C");
    std::cout << encoded << std::endl;

    decode(encoded);
    // decrypt
    /*char m[9];
    long int temp[50];
    long int pt, ct;
    long int key = _privateKey;
    int i = 0;
    
    while (encoded[i] != -1)
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

    std::cout << std::endl;*/
}

long int RSA::getPublicKey()
{
    return this->_publicKey;
}

std::string RSA::decode(std::string encodedMsg)
{
    int* temp = new int[encodedMsg.length()];
    std::string decodedMsg = "";

    long double power = pow(encodedMsg[0], _privateKey);
    std::cout << power << std::endl;
    std::cout << char((fmod(power, _primeMul)))<< std::endl;

    return std::string();
}

std::string RSA::encrypt(long int publicKey, long int primeMul, std::string msg)
{
    const char* msgChar = new char[msg.length()];
    int* temp = new int[msg.length()];
    std::string encodedMsg = "";
    msgChar = msg.c_str();
    long int pt, ct, k;
    
    /*for (int i = 0; i < msg.length(); i++)
    {
        pt = msgChar[i];
        pt -= 96;
        k = 1;
        for (int j = 0; j < publicKey; j++)
        {
            k = k * pt;
            k = k % primeMul;
        }
        temp[i] = k;
        ct = k + 96;
        encodedMsg += ct;
    }
    encodedMsg += -1;*/
    long double power = pow(msg[0], publicKey);
    encodedMsg += fmod(power, primeMul);

    return encodedMsg;
}
