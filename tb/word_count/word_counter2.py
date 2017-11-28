#coding=utf-8 
import re
from HTMLParser import HTMLParser
import operator
from collections import Counter


# https://docs.python.org/2/library/htmlparser.html
# create a subclass and override the handler methods
class MyHTMLParser(HTMLParser):

    def __init__(self):
        HTMLParser.__init__(self)
        self.arrData = []

    def handle_starttag(self, tag, attrs):
        #print "Encountered a start tag:", tag
        pass

    def handle_endtag(self, tag):
        #print "Encountered an end tag :", tag
        pass

    def handle_data(self, data):
        #print "Encountered some data  :", data
        self.arrData.append(data)

class Word(object):
    """
    Word Class
    """
    wordElementPattern = re.compile(r"[a-z0-9'\-_]", re.I)
    letterPattern = re.compile(r"[a-z]", re.I)
    wordPattern = re.compile(r"^('?[a-z])[a-z0-9'\-_]*([a-z]|[0-9]|s')$", re.I)

    @classmethod
    def isWordElement(cls, element):
        """
        only consist of ASCII letters, ASCII digits, apostrophes, hyphens, and underscores
        Any character that cannot occur in a word should be considered to be a word delimiter.
        :param element:
        :return: boolean
        """
        if cls.wordElementPattern.match(element):
            return True

        return False

    @classmethod
    def isWord(cls, sequence):
        """
        start with a letter or start with an apostrophe followed by a letter,
        end with (a) a letter, (b) a digit, or (c) an apostrophe preceded by the letter s,
        should be considered to be words.

        :param sequence:
        :return: boolean
        """
        if cls.wordPattern.match(sequence):
            return True

        # one letter case
        if len(sequence) == 1 and cls.letterPattern.match(sequence): 
            return True

        if sequence == "s'": 
            return True

        return False


class WordStack(object):
    """
    WordStack Class
    """

    def __init__(self):
        self.elementList = []

    def push(self, element):
        self.elementList.append(str(element))

    def elements(self):
        word = ''.join(self.elementList)
        self.elementList = []

        return word.lower()


class WordParser(object):

    def __init__(self, txt):
        self.txt = self.stripHtmlTags(txt)
        self.txt = self.seperateDashesWords(self.txt)
        self.wordList = list()

    @classmethod
    def stripHtmlTags(cls, txt):
        """
        HTML comments should be removed and HTML tags and words within HTML tags should not be counted.
        strip html tags from text
        """
        parser = MyHTMLParser()
        parser.feed(txt)
        words = ' '.join(parser.arrData)
        parser.close()

        words = words.strip(' ')
        return re.sub(r'\s{2,}', ' ', words)


    @classmethod
    def seperateDashesWords(cls, txt):
        """
        The words contain em-dashes should be separated
        :param txt:
        :return:
        """

        return re.sub(r'-{2,3}', ' ', txt)

    def appendWord(self, elements): 
        """add word to wordList
        """
        self.wordList.append(elements)

    def parse(self):
        stack = WordStack()
        for s in self.txt:
            if Word.isWordElement(s):
                stack.push(s)
            else:
                elements = stack.elements()
                if elements and Word.isWord(elements):
                    self.appendWord(elements)

                continue

        elements = stack.elements()
        if elements and Word.isWord(elements):
            self.appendWord(elements)

        return self.wordList


class WordCounter(object):
    """the word count class
    """
    def __init__(self, text): 
        """ init
        """
        self.text = text

    def go(self): 
        """ go
        """
        parser = WordParser(self.text)
        wordList = parser.parse()
        totalWordCount = len(wordList)

        #https://docs.python.org/2/library/collections.html#collections.Counter
        counter = Counter(wordList)
        wordCommon      = counter.most_common()

        wordMostCommon  = wordCommon[0:10]
        wordLeastCommon = wordCommon[:-10-1:-1]

        arrMost = []
        arrLeast = []
        for item in wordMostCommon: 
            arrMost.append({
                'word': item[0],
                'count': item[1]
            })

        for item in wordLeastCommon: 
            arrLeast.append({
                'word': item[0],
                'count': item[1]
            })

        arrData = {
            'total_word_count': totalWordCount,
            'most': arrMost,
            'least': arrLeast,
        }
        return arrData

    def test(self):
        """count words test.
        """

        parser = WordParser(self.text)
        wordList = parser.parse()

        return len(set(wordList)), len(wordList)


if __name__ == '__main__':

    # test cases.
    text = " A B B C C C D D D D E E E E E F F F F F F G G G G G G G "
    o = WordCounter(text)
    print o.go()

    text = """ A B B C C C D D D D E E E E E F F F F F F G G G G G G G 
    H H H H H H H H 
    I I I I I I I I I 
    J J J J J J J J J J
    K K K K K K K K K K K"""
    o = WordCounter(text)
    print o.go()

    text = "A"
    o = WordCounter(text)
    assert (1, 1) == o.test()

    text = "s'"
    o = WordCounter(text)
    assert (1, 1) == o.test()

    text = "10, 123-reg, even-, evenin'"
    o = WordCounter(text)
    assert (0, 0) == o.test()

    text = " p0wned, l33t, hello_world, reg-123, ClickMe, 'twas, o'clock, has' "
    o = WordCounter(text)
    assert (8, 8) == o.test()

    text = "$1.2bn"
    o = WordCounter(text)
    assert (0, 0) == o.test()

    text = "six%two"
    o = WordCounter(text)
    assert (2, 2) == o.test()

    text = """<!-- This is a 
        comment --> <a href="url">some words</a> <ul type="disc"><li>one</li> 
        <li>two</li></ul>"""
    o = WordCounter(text)
    assert (4, 4) == o.test()

    text = "sign-writer, easy-to-use, non-disposable, honest-to-goodness, catch-22"
    o = WordCounter(text)
    assert (5, 5) == o.test()

    text = """has-
    been
    """
    o = WordCounter(text)
    assert (1, 1) == o.test()

    text = "again--time"
    o = WordCounter(text)
    assert (2, 2) == o.test()


    text = "again---time"
    o = WordCounter(text)
    assert (2, 2) == o.test()

    text = "doesn't"
    o = WordCounter(text)
    assert (1, 1) == o.test()

    text = "there's"
    o = WordCounter(text)
    assert (1, 1) == o.test()

    text = "I've"
    o = WordCounter(text)
    assert (1, 1) == o.test()

    text = "you'll"
    o = WordCounter(text)
    assert (1, 1) == o.test()

    text = "doesn't, there's, I've  you'll"
    o = WordCounter(text)
    assert (4, 4) == o.test()

    text = "doesn't, there's, I've  you'll ,does, not, there, is, I, have, you ,will "
    o = WordCounter(text)
    assert (12, 12) == o.test()

    text = "Peter's"
    o = WordCounter(text)
    assert (1, 1) == o.test()

    text = "Moses'"
    o = WordCounter(text)
    assert (1, 1) == o.test()

    text = "business's"
    o = WordCounter(text)
    assert (1, 1) == o.test()

    text = "Peter's, Moses', business's"
    o = WordCounter(text)
    assert (3, 3) == o.test()

    text = "Peter's, Moses', business's Peter Moses  business"
    o = WordCounter(text)
    assert (6, 6) == o.test()

    text = "boys  boys' "
    o = WordCounter(text)
    assert (2, 2) == o.test()

    text = "Hotel  hotel "
    o = WordCounter(text)
    assert (1, 2) == o.test()

    filename = './test1.txt'
    text = open(filename).read(100000000)
    o = WordCounter(text)
    assert (16, 136) == o.test()

    filename = './test2.txt'
    text = open(filename).read(100000000)
    o = WordCounter(text)
    assert (16, 136) == o.test()

    filename = './test3.txt'
    text = open(filename).read(100000000)
    o = WordCounter(text)
    assert (0, 0) == o.test()

    filename = './test4.txt'
    text = open(filename).read(100000000)
    o = WordCounter(text)
    assert (1, 1) == o.test()

    filename = './test_html.txt'
    text = open(filename).read(100000000)
    o = WordCounter(text)
    assert (7, 11) == o.test()



