import time


class HttpResponse:
    @staticmethod
    def header_headline(status_code):
        headline = str()
        if status_code == 200:  # OK
            headline += 'HTTP/1.1 200 OK\r\n'
        elif status_code == 302:  # Redirect- Object moved
            headline += 'HTTP/1.1 302 Object moved\r\n'
        headline += 'Content-type: text/html\r\n'

        return headline

    @staticmethod
    def header_metadata(connection_mode):
        metadata = str()
        time_now = time.strftime("%a, %d %b %Y %H:%M:%S", time.localtime())
        metadata += 'Date: {now}\r\n'.format(now=time_now)
        metadata += 'Server: Microsoft-IIS/10.0\n'
        metadata += 'Connection: ' + ('keep-alive' if connection_mode else 'close') + '\r\n'

        return metadata

    @staticmethod
    def generate_response(request_status, content, connection_mode=True, set_cookie=""):
        """
        This function generates HTTP response
        :param request_status: status code
        :type request_status: int
        :param content: html content
        :type content: str
        :param connection_mode: Keep-Alive or Close the connection
        :type connection_mode: bool
        :param set_cookie: cookie value
        :type set_cookie: str
        :return: HTTP response
        :rtype: str
        """
        header = str()
        header += HttpResponse.header_headline(request_status)
        header += ('Set-Cookie: sessionId=' + set_cookie) if set_cookie else ''
        header += HttpResponse.header_metadata(connection_mode)
        header += "Content-Length: " + str(len(content)) + "\r\n\r\n"

        return header + content

    @staticmethod
    def generate_redirect_response(redirect_url):
        """
        This function generates response for redirection
        :param redirect_url: url for redirection
        :type redirect_url: str
        :return: HTTP response
        :rtype: str
        """
        # Generate Response Header
        header = str()
        header += HttpResponse.header_headline(302)
        header += HttpResponse.header_metadata(False)  # False- Close connection
        header += 'Location: ' + redirect_url + '\r\n'
        header += 'Content-Length: 0\r\n\r\n'

        return header
