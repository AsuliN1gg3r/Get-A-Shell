import time


class HttpResponse:
    @staticmethod
    def generate_response(request_status, content):
        """
        This function generates HTTP response
        :param request_status: status code
        :type request_status: int
        :param content: html content
        :type content: str
        :return: HTTP response
        :rtype: str
        """
        # Generate Response Header
        header = str()
        if request_status == 200:
            header += "HTTP/1.1 200 OK\n"
        elif request_status == 404:
            header += "HTTP/1.1 404 Not Found\n"
        time_now = time.strftime("%a, %d %b %Y %H:%M:%S", time.localtime())
        header += 'Date: {now}\n'.format(now=time_now)
        header += 'Server: Microsoft Update Services Server\n'
        header += 'Connection: close\n\n'

        return header + content

    @staticmethod
    def load_html_file(path):
        """
        This function loads html file
        :param path: path of html file on server
        :type path: str
        :return: html file content
        :rtype: str
        """
        try:
            with open(path, 'r') as html_file:
                return html_file.read()
        except FileNotFoundError:
            return ""
