from RSA import RSA


def main():
    rsa = RSA()
    test_str = "I like to sniff.... packets"
    print("String:", test_str)
    encrypted = rsa.encrypt(rsa.public_key, test_str)
    print("Encrypted:", encrypted)
    decrypted = rsa.decrypt(encrypted)
    print("Decrypted:", decrypted)


if __name__ == "__main__":
    main()
