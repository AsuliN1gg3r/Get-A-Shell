#include "rsa.h"

// Prime number checker (Rabin Miller Algorithem)
bool RSA::_rabinMiller(int n)
{
    bool ok = true;

    for (int i = 1; i <= 5 && ok; i++) {
        int a = rand() + 1;
        int result = this->_logPower(a, n - 1, n);
        ok &= (result == 1);
    }

    return ok;
}

int RSA::_logPower(int n, int p, int mod)
{
    int result = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            result = (1LL * result * n) % mod;
        n = (1LL * n * n) % mod;
    }
    return result;
}

int RSA::_gcd(int num1, int num2)
{
    while (num2)
    {
        int r = num1 % num2;
        num1 = num2;
        num2 = r;
    }
    return num1;
}

int RSA::_generateCoprime(int num)
{
    int generated = rand() % LIMIT;
    while (this->_gcd(num, generated) != 1)
        generated = rand() % LIMIT;
    return generated;
}

// Rand a prime number
int RSA::_generatePrime()
{
    int generated = rand() % LIMIT;
    while (!this->_rabinMiller(generated))
        generated = rand() % LIMIT;
    return generated;
}

std::pair<int, int> RSA::_euclidExtended(int a, int b)
{
    if (!b) {
        return { 1, 0 };
    }

    auto result = this->_euclidExtended(b, a % b);
    return { result.second, result.first - (a / b) * result.second };
}

int RSA::_modularInverse(int n, int mod)
{
    int inverse = this->_euclidExtended(n, mod).first;
    while (inverse < 0)
        inverse += mod;
    return inverse;
}


RSA::RSA()
{
    srand(time(NULL));

    int prime1 = this->_generatePrime(), prime2 = this->_generatePrime();
    int n = prime1 * prime2;
    int phi = (prime1 - 1) * (prime2 - 1);

    // Generate public key {e} [coprime to ø(n) and 1 < e < ø(n)]
    int e = this->_generateCoprime(phi);
    this->_publicKey = std::make_pair(e, n);
    
    //Generate private key {d}
    int d = this->_modularInverse(e, phi);
    this->_privateKey = std::make_pair(d, n); 
}

// Decrypt encoded bytes
std::string RSA::decrypt(int* encodedMsg)
{
    std::string decryptedMsg = "";

    for (int i = 0; encodedMsg[i] != -1; i++)
    {
        decryptedMsg += (char)this->_logPower(encodedMsg[i], this->_privateKey.first, this->_privateKey.second);
    }

    return decryptedMsg;
}

// Encrypt a string
int* RSA::encrypt(std::pair<int, int> publicKey, std::string msg)
{
    int* encodedMsg = new int[msg.length() + 1];
    for (int i = 0; i < msg.length(); i++)
    {
        encodedMsg[i] = RSA::_logPower(msg[i], publicKey.first, publicKey.second);
    }
    encodedMsg[msg.length()] = -1; // End of data- used for decryption
    return encodedMsg;
}
