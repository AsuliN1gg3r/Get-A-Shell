import random


def log_power(n, p, mod):
    result = 1
    while p:
        if p & 1:
            result = (result * n) % mod
        n = (n * n) % mod
        p >>= 1
    return result


def rabin_miller(n):
    ok = True
    i = 1
    while i <= 5 and ok:
        a = random.randint(1, 10000)
        result = log_power(a, n - 1, n)
        ok &= (result == 1)
        i += 1

    return ok


def gcd(num1, num2):
    while num2:
        r = num1 % num2
        num1 = num2
        num2 = r
    return num1


def generate_coprime(num):
    generated = random.randint(1, 10000)
    while gcd(num, generated) != 1:
        generated = random.randint(1, 10000)
    return generated


def generate_prime():
    generated = random.randint(1, 10000)
    while not rabin_miller(generated):
        generated = random.randint(1, 10000)
    return generated


def euclid_extended(a, b):
    if not b:
        return 1, 0
    result = euclid_extended(b, a % b)
    return result[1], result[0] - (a / b) * result[1]


def modular_inverse(n, mod):
    inverse = euclid_extended(n, mod)[0]
    while inverse < 0:
        inverse += mod;
    return inverse;

