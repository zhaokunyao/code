#! /usr/local/bin/python3
#coding=utf-8 

#import urllib2
#import urllib
from urllib import request


import cgi
import json
# word_counter.py
from word_counter import WordCounter

# https://stackoverflow.com/questions/15014310/why-is-there-no-xrange-function-in-python3
# python3 does not have xrange
def xrange(x):
    return iter(range(x))


class WordCountHTTPHandler(object): 

    errorMsg = None

    def do_GET(self): 
        """display a web page that contains a form 
        """
        # header blankline and HTML
        buf = """Content-type:text/html

        """
        buf += """<html><body>
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
        #self.protocal_version = 'HTTP/1.1'
        #self.send_response(200)
        #self.send_header("Welcome", "Contect")
        #self.end_headers()
        #self.wfile.write(bytes(buf, 'utf-8'))
        print(buf)

    def myCheck(self, form): 
        """check
        """
        ok = False
        msg = ''

        # without entering anything 
        # into either of the two fields
        # indicate an error 
        if 'text' not in form and 'url' not in form: 
            msg = "pls input url or text."
            return ok, msg

        # A user may enter both a URL into the first text field 
        # and text into your second text field
        # indicate an error 
        if 'text' in form and 'url' in form: 
            msg = "pls input url or text.."
            return ok, msg

        ok = True
        return ok, msg

    def do_POST(self, form): 
        """ process data
        """
        #form = cgi.FieldStorage() 
        # check user input.
        ok, self.errorMsg = self.myCheck(form)
        if not ok: 
            return self.do_GET()

        url = ""
        text = ""
        if 'url' in form: 
            url     = form['url'].value
        if 'text' in form: 
            text    = form['text'].value

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
        #self.send_response(200)
        #self.end_headers()
        o = WordCounter(text)
        arrData = o.go()
        # debug log
        #f = open("/tmp/my.debug.log","a")
        #f.write(text)
        html = self.myMakeHtml(arrData, url, text)
        #self.wfile.write(bytes(html, 'utf-8'))
        print (html)

    def myMakeHtml(self, arrData, url, text): 
        """ make html
        """

        html = """Content-type:text/html

        """
        html += """<html><body>
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
        html += cgi.escape(text, True).replace('\n','<br />\n')

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

            for i in xrange(len(arrData['most'])): 
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
            #text = urllib2.urlopen(url).read(10000000)
            text = request.urlopen(url).read(10000000).decode('utf-8')
        except Exception as e: 
            #text = str(e)
            text = ""
        return text


o = WordCountHTTPHandler()

# https://docs.python.org/3/library/cgi.html
form = cgi.FieldStorage() 
if 'submit' in form: 
    o.do_POST(form)
else: 
    o.do_GET()
