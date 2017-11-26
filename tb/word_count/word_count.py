#coding=utf-8 

from HTMLParser import HTMLParser

# https://docs.python.org/2/library/htmlparser.html
# create a subclass and override the handler methods
class MyHTMLParser(HTMLParser):
    arrData = list()

    def handle_starttag(self, tag, attrs):
        #print "Encountered a start tag:", tag
        pass

    def handle_endtag(self, tag):
        #print "Encountered an end tag :", tag
        pass

    def handle_data(self, data):
        #print "Encountered some data  :", data
        self.arrData.append(data)


"""
the word count class
"""

class WordCount(object): 
    """the word count class
    """
    def __init__(self, text): 
        """ init
        """
        self.text = text

    def strip_html_tags(self): 
        """strip html tags from text
        """
        # instantiate the parser and fed it some HTML
        parser = MyHTMLParser()
        parser.feed(self.text)
        self.text = ' '.join(parser.arrData)
        # print self.text

    def go(self): 
        """count words
        """
        self.strip_html_tags()
        arrData = {
            'total_word_count': 2,
            'most': [
                {'word': 'sixteen', 'count': 16},
                {'word': 'fifteen', 'count': 15},
                {'word': 'fourteen', 'count': 14},
                {'word': 'thirteen', 'count': 13},
                {'word': 'twelve', 'count': 12},
                {'word': 'eleven', 'count': 11},
                {'word': 'ten', 'count': 10},
                {'word': 'nine', 'count': 9},
                {'word': 'eight', 'count': 8},
                {'word': 'seven', 'count': 7},
            ],
            'least': [
                {'word': 'one', 'count': 1},
                {'word': 'two', 'count': 2},
                {'word': 'three', 'count': 3},
                {'word': 'four', 'count': 4},
                {'word': 'five', 'count': 5},
                {'word': 'six', 'count': 6},
                {'word': 'seven', 'count': 7},
                {'word': 'eight', 'count': 8},
                {'word': 'nine', 'count': 9},
                {'word': 'ten', 'count': 10},
            ]
        }

        return arrData

if __name__ == '__main__': 

    # test cases.
    filename = './test_html.txt'
    text = open(filename).read(100000000) 
    o = WordCount(text)
    o.go()
    import sys
    sys.exit(0)

    filename = './test1.txt'
    text = open(filename).read(100000000) 
    o = WordCount(text)
    o.go()

    filename = './test2.txt'
    text = open(filename).read(100000000) 
    o = WordCount(text)
    o.go()

    filename = './test3.txt'
    text = open(filename).read(100000000) 
    o = WordCount(text)
    o.go()

    filename = './test4.txt'
    text = open(filename).read(100000000) 
    o = WordCount(text)
    o.go()
