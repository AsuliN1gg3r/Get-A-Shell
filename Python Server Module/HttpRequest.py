import email
import pprint
from io import StringIO
import os


class HttpRequest:
    def __init__(self, request_method, request_path, request_headers, request_content):
        """
        Constructor of HttpRequest
        :param request_method: GET or POST
        :type request_method: str
        :param request_path: default- "/", or other pages on web server
        :type request_path: str
        :param request_headers: `Configuration` of the request
        :type request_headers: dict
        :param request_content: params
        :type request_content: str
        """
        self.request_method = request_method
        self.request_path = request_path
        self.request_headers = request_headers
        self.request_content = request_content

    @staticmethod
    def parse_http_request(request):
        """
        This function is parse raw http request into HttpRequest object
        :param request: raw http request
        :type request: str
        :return: Http request object
        :rtype: HttpRequest
        """
        request_method = request.split(' ')[0]  # GET or POST
        request_path = request.split(' ')[1].split('?')[0]  # /<path>
        request_headers, request_content = request.split('\r\n', 1)[1].split("\r\n\r\n")  # headers and content/params
        message = email.message_from_file(StringIO(request_headers))
        request_headers = dict(message.items())
        return HttpRequest(request_method, request_path, request_headers, request_content)

    @staticmethod
    def shell_user_agent(request):
        """
        This function checks if the request's User-Agent is from a reversed shell or any other software.
        Reversed shell agent stored at OS environment variables to protect against code stealing.
        :param request: Http request object
        :type request: HttpRequest
        :return: the request is from reversed shell or any other software
        :rtype: bool
        """
        return request.request_headers["User-Agent"] == os.environ['ShellUserAgent']
