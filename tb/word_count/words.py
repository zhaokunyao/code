#! /usr/local/bin/python3
#coding=utf-8 
from urllib import request

import cgi
import re
import html.parser as h  

# https://stackoverflow.com/questions/15014310/why-is-there-no-xrange-function-in-python3
# python3 does not have xrange
def xrange(x):
    return iter(range(x))

# https://docs.python.org/2/library/htmlparser.html
# create a subclass and override the handler methods
class MyHTMLParser(h.HTMLParser):

    def __init__(self):
        h.HTMLParser.__init__(self)
        self.arrData = []

    def handle_data(self, data):
        #print "Encountered some data  :", data
        self.arrData.append(data)

# allowed letter in word: 
wordElementPattern = re.compile(r"[a-z0-9'\-_]", re.I)
# single letter pattern
letterPattern = re.compile(r"[a-z]", re.I)
# word pattern
wordPattern = re.compile(r"^('?[a-z])[a-z0-9'\-_]*([a-z]|[0-9]|s')$", re.I)

def isWord(sequence):
    """
    start with a letter or start with an apostrophe followed by a letter,
    end with (a) a letter, (b) a digit, or (c) an apostrophe preceded by the letter s,
    should be considered to be words.
    """
    if wordPattern.match(sequence):
        return True

    # one letter case
    if len(sequence) == 1 and letterPattern.match(sequence): 
        return True

    if sequence == "s'": 
        return True

    return False

def wordCount(text, isTest=False):
    """count words test.
    """

    #HTML comments should be removed and HTML tags and words within HTML tags should not be counted.
    #strip html tags from text
    parser = MyHTMLParser()
    parser.feed(text)
    text = ' '.join(parser.arrData)
    parser.close()

    # Viii.All words should be converted to lower-case before being counted
    text = text.lower()

    # iV. The words contain em-dashes should be separated
    text = text.replace('---', ' ')
    text = text.replace('--', ' ')

    word = ""
    arrWords = {}
    totalWordCount = 0

    for s in text:

        if wordElementPattern.match(s): 
            word += s
            continue

        if isWord(word):
            if word not in arrWords: 
                arrWords[word] = 0
            arrWords[word] += 1
            totalWordCount += 1

        word = ""

    # at the end of the text.
    if len(word) > 0: 
        if isWord(word): 
            if word not in arrWords: 
                arrWords[word] = 0
            arrWords[word] += 1
            totalWordCount += 1

    # for test.
    if isTest: 
        return len(arrWords), totalWordCount

    # sort by count
    arrWords = sorted(arrWords.items(), key=lambda x: x[1])

    arrMost = arrWords[:-10-1:-1]
    arrLeast = arrWords[0:10]
    arrData = {
        'total_word_count': totalWordCount,
        'most': arrMost,
        'least': arrLeast,
    }
    return arrData

def doTest(): 

    # test cases.
    text = " A B B C C C D D D D E E E E E F F F F F F G G G G G G G "
    print (wordCount(text))

    text = """ A B B C C C D D D D E E E E E F F F F F F G G G G G G G 
    H H H H H H H H 
    I I I I I I I I I 
    J J J J J J J J J J
    K K K K K K K K K K K"""
    print (wordCount(text))

    text = "A"
    assert (1, 1) == wordCount(text, True)

    text = "s'"
    assert (1, 1) == wordCount(text, True)

    text = "10, 123-reg, even-, evenin'"
    assert (0, 0) == wordCount(text, True)

    text = " p0wned, l33t, hello_world, reg-123, ClickMe, 'twas, o'clock, has' "
    assert (8, 8) == wordCount(text, True)

    text = "$1.2bn"
    assert (0, 0) == wordCount(text, True)

    text = "six%two"
    assert (2, 2) == wordCount(text, True)

    text = """<!-- This is a 
        comment --> <a href="url">some words</a> <ul type="disc"><li>one</li> 
        <li>two</li></ul>"""
    assert (4, 4) == wordCount(text, True)

    text = "sign-writer, easy-to-use, non-disposable, honest-to-goodness, catch-22"
    assert (5, 5) == wordCount(text, True)

    text = """has-
    been
    """
    assert (1, 1) == wordCount(text, True)

    text = "again--time"
    assert (2, 2) == wordCount(text, True)


    text = "again---time"
    assert (2, 2) == wordCount(text, True)

    text = "doesn't"
    assert (1, 1) == wordCount(text, True)

    text = "there's"
    assert (1, 1) == wordCount(text, True)

    text = "I've"
    assert (1, 1) == wordCount(text, True)

    text = "you'll"
    assert (1, 1) == wordCount(text, True)

    text = "doesn't, there's, I've  you'll"
    assert (4, 4) == wordCount(text, True)

    text = "doesn't, there's, I've  you'll ,does, not, there, is, I, have, you ,will "
    assert (12, 12) == wordCount(text, True)

    text = "Peter's"
    assert (1, 1) == wordCount(text, True)

    text = "Moses'"
    assert (1, 1) == wordCount(text, True)

    text = "business's"
    assert (1, 1) == wordCount(text, True)

    text = "Peter's, Moses', business's"
    assert (3, 3) == wordCount(text, True)

    text = "Peter's, Moses', business's Peter Moses  business"
    assert (6, 6) == wordCount(text, True)

    text = "boys  boys' "
    assert (2, 2) == wordCount(text, True)

    text = "Hotel  hotel "
    assert (1, 2) == wordCount(text, True)

    filename = './test1.txt'
    text = open(filename).read(100000000)
    assert (16, 136) == wordCount(text, True)

    filename = './test2.txt'
    text = open(filename).read(100000000)
    assert (16, 136) == wordCount(text, True)

    filename = './test3.txt'
    text = open(filename).read(100000000)
    assert (0, 0) == wordCount(text, True)

    filename = './test4.txt'
    text = open(filename).read(100000000)
    assert (1, 1) == wordCount(text, True)



def doGet(errorMsg=None): 
    """display a web page that contains a form 
    """
    # header blankline and HTML
    buf = """Content-type:text/html

    """
    buf += """<html><body>
    """
    # show error msg
    if errorMsg: 
        buf += """
        <div style='color:red'>%s</div>
        """ % (errorMsg)

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
    print(buf)

def doPost(form): 
    """ process data
    """
    # check user input.

    # without entering anything 
    # into either of the two fields
    # indicate an error 
    if 'text' not in form and 'url' not in form: 
        errorMsg = "pls input url or text."
        return doGet(errorMsg)

    # A user may enter both a URL into the first text field 
    # and text into your second text field
    # indicate an error 
    if 'text' in form and 'url' in form: 
        errorMsg = "pls input url or text.."
        return doGet(errorMsg)

    url = ""
    text = ""
    if 'url' in form: 
        url     = form['url'].value
    if 'text' in form: 
        text    = form['text'].value

    # If a user enters a URL 
    if url: 
        # retrieve the document that the URL points to
        # cater for the possibility that the URL is not valid,
        try: 
            text = request.urlopen(url).read(10000000).decode('utf-8')
        except Exception as e: 
            text = ""

        # there is nothing to retrieve at that URL
        # indicate an error to the user in such a case
        # and allow the user to start again
        if len(text) == 0: 
            errorMsg = "nothing to retrieve at that URL"
            return doGet(errorMsg)

    # everything is ok, do the word count.
    arrData = wordCount(text)
    # output
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
            </tr>""" % (arrMost[1], arrMost[0],
                arrLeast[1], arrLeast[0])

        html += "</table>"
    html += "</body></html>"
    print (html)

# it goes from here.
# https://docs.python.org/3/library/cgi.html
form = cgi.FieldStorage() 
if 'submit' in form: 
    doPost(form)
else: 
    doGet('')

#doTest()
