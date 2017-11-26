#coding=utf-8 

import urllib2

from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler
import cgi
import json
# word_count.py
from word_count import WordCount

class WordCountHTTPHandler(BaseHTTPRequestHandler): 

    errorMsg = None

    def do_GET(self): 
        """display a web page that contains a form 
        """
        buf = """<html><body>
        """
        if self.errorMsg: 
            buf += """
            <div style='color:red'>%s</div>
            """ % (self.errorMsg)
        buf += """
        <div style="margin-left:100px;">
        <form method="POST">
        <br />
        <input type=submit name=submit value=Submit /><br />
        <br />
        <input type=text name='url' value='' placeholder='enter a single URL' size=100 /><br />
        <br />
        input text: </br >
        <br />
        <textarea cols=100 rows=20 name="text"></textarea>
        </form>
        </div>
        </body></html>
        """
        self.protocal_version = 'HTTP/1.1'
        self.send_response(200)
        self.send_header("Welcome", "Contect")
        self.end_headers()
        self.wfile.write(buf)

    def myCheck(self, postvars): 
        """check
        """
        ok = False
        msg = ''

        if 'url' not in postvars or len(postvars['url']) == 0: 
            msg = "no url received"
            return ok, msg

        if 'text' not in postvars or len(postvars['text']) == 0: 
            msg = "no text received"
            return ok, msg

        # without entering anything 
        # into either of the two fields
        # indicate an error 
        if len(postvars['text'][0]) == 0 and len(postvars['url'][0]) == 0: 
            msg = "pls input url or text."
            return ok, msg

        # A user may enter both a URL into the first text field 
        # and text into your second text field
        # indicate an error 
        if len(postvars['text'][0]) > 0 and len(postvars['url'][0]) > 0: 
            msg = "pls input url or text.."
            return ok, msg
        ok = True
        return ok, msg

    def do_POST(self): 
        """ process data
        """
        length = int(self.headers['content-length'])
        # parse the form.
        postvars = cgi.parse_qs(self.rfile.read(length), 
            keep_blank_values=1)

        # check user input.
        ok, self.errorMsg = self.myCheck(postvars)
        if not ok: 
            return self.do_GET()

        url = postvars['url'][0]
        text = postvars['text'][0]

        # If a user enters a URL 
        if url: 
            # retrieve the document that the URL points to
            text = self.myRetrieveFromUrl(url)
            # there is nothing to retrieve at that URL
            # indicate an error to the user in such a case
            # and allow the user to start again
            if len(text) == 0: 
                self.errorMsg = "nothing to retrieve at that URL"
                return self.do_GET()

        # everything is ok, do the word count.
        self.send_response(200)
        self.end_headers()
        o = WordCount(text)
        arrData = o.go()
        html = self.myMakeHtml(arrData, url, text)
        self.wfile.write(html)

    def myMakeHtml(self, arrData, url, text): 
        """ make html
        """
        html = """<html><body>
        """

        # • a statement of the URL that the user has entered 
        # (if one was entered);
        if url: 
            html += """<div>
            Word Count Statistics for %s
            <br />
            <br />
            </div>
            """ % (url)

        # • the document that was processed, 
        # visibly showing any HTML markup that it may have contained;
        html += cgi.escape(text, True)

        # • a statement of the total number of word occurrences in the document;
        wordText = "words"
        #uses `1 word' instead of `1 words'
        if arrData['total_word_count'] == 1: 
            wordText = 'word'

        html += """<div><br /><br />
            The document contains %s %s.
            <br />
            <br />
            <br />
            </div>""" % (arrData['total_word_count'], wordText)

        # • two HTML tables
        # does not print the tables if the document does not contain any words 
        if arrData['total_word_count'] > 0: 
            html += "<table border=1>"
            # the first showing the ten words occurring most often 
            # and the number of occurrences for each of these words 
            # the second showing the ten words occurring least often 
            # and the number of occurrences for each of these words

            html += """<tr>
            <th colspan=2>10 Words Occurring Most Often</th>
            <th colspan=2>10 Words Occurring Least Often</th>
            </tr>"""

            html += """<tr>
            <th>No of occurrences</th>
            <th>Word</th>
            <th>No of occurrences</th>
            <th>Word</th>
            </tr>"""

            for i in xrange(0, 10): 
                arrMost = arrData['most'][i]
                arrLeast = arrData['least'][i]
                html += """<tr>
                <td>%s</td>
                <td>%s</td>
                <td>%s</td>
                <td>%s</td>
                </tr>""" % (arrMost['count'], arrMost['word'],
                    arrLeast['count'], arrLeast['word'])

            html += "</table>"
        html += "</body></html>"
        return html

    def myRetrieveFromUrl(self, url): 
        """ retrieve the document that the URL points to
        """
        text = ""
        # cater for the possibility that the URL is not valid,
        try: 
            text = urllib2.urlopen(url).read(10000000)
        except Exception as e: 
            text = ""
        return text


if __name__ == '__main__': 
    # change the port as you need.
    port = 8889
    http_server = HTTPServer(('0.0.0.0', int(port)), WordCountHTTPHandler)  
    print "server started at http://youip:%s/" % (port);
    http_server.serve_forever()
