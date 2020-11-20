import random


class RSA:
    @staticmethod
    def __log_power(n, p, mod):
        result = 1
        while p:
            if p & 1:
                result = (result * n) % mod
            n = (n * n) % mod
            p >>= 1
        return result

    # Prime number checker (Rabin Miller Algorithm)
    def __rabin_miller(self, n):
        ok = True
        i = 1
        while i <= 5 and ok:
            a = random.randint(1, 10000)
            result = self.__log_power(a, n - 1, n)
            ok &= (result == 1)
            i += 1
        return ok

    @staticmethod
    def __gcd(num1, num2):
        while num2:
            r = num1 % num2
            num1 = num2
            num2 = r
        return num1

    def __generate_coprime(self, num):
        generated = random.randint(1, 10000)
        while self.__gcd(num, generated) != 1:
            generated = random.randint(1, 10000)
        return generated

    # Rand a prime number
    def __generate_prime(self):
        generated = random.randint(1, 10000)
        while not self.__rabin_miller(generated):
            generated = random.randint(1, 10000)
        return generated

    def __euclid_extended(self, a, b):
        if a == 0:
            return 0, 1
        x1, y1 = self.__euclid_extended(b % a, a)
        x = y1 - (b // a) * x1
        y = x1
        return x, y

    def __modular_inverse(self, n, mod):
        inverse = self.__euclid_extended(n, mod)[0]
        while inverse < 0:
            inverse += mod
        return inverse

    def __init__(self):
        prime1 = self.__generate_prime()
        prime2 = self.__generate_prime()
        n = prime1 * prime2
        phi = (prime1 - 1) * (prime2 - 1)

        # generate public key {e} [coprime to ø(n) and 1 < e < ø(n)]
        e = self.__generate_coprime(phi)
        self.public_key = (e, n)

        # generate private key {d}
        d = self.__modular_inverse(e, phi)
        self.private_key = (d, n)

    # Decrypt encoded bytes
    def decrypt(self, encoded_msg):
        decrypted_msg = str()
        i = 0
        while encoded_msg[i] != -1:
            decrypted_msg += chr(self.__log_power(encoded_msg[i], self.private_key[0], self.private_key[1]))
            i += 1
        return decrypted_msg

    # Encrypt a string
    @staticmethod
    def encrypt(public_key, msg):
        encoded_msg = list()
        for c in msg:
            encoded_msg.append(RSA.__log_power(ord(c), public_key[0], public_key[1]))
        encoded_msg.append(-1)  # End of data- used for decryption
        return encoded_msg
