import requests
import re


def validate_email(email_address):
    """
    Regex is used to validate the syntax of the Email address.
    Used an API to check if the email exists.
    :param email_address:
    """
    regex = '^[a-z0-9]+[\._]?[a-z0-9]+[@]\w+[.]\w{2,3}$'
    response = requests.get("https://isitarealemail.com/api/email/validate", params={'email': email_address})
    if re.search(regex, email_address):
        if response.json()['status'] == "valid":
            return True
    return "Email is invalid"


def validate_password(passwd):
    """
    Validate the syntx of the password.
    The password should be secure, with at least 6 chars.
    return value will be displayed at the web interface.
    :param passwd:
    """

    if len(passwd) < 6:
        return 'Length of a password should be at least 6'

    if not any(char.isdigit() for char in passwd):
        return 'Password should have at least one numeral'

    if not any(char.isupper() for char in passwd):
        return 'Password should have at least one uppercase letter'

    if not any(char.islower() for char in passwd):
        return 'Password should have at least one lowercase letter'

    else:
        return True


def validate_name(name):
    special_sym = ['$', '@', '#', '%', ';']

    if any(char in special_sym for char in name):
        return 'Username should not have any symbols like @#$;'

    else:
        return True



