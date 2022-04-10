import unittest
import parser

class TestParser(unittest.TestCase):
    
    def test_tokenize(self):
        self.assertIs(parser.parse(), None)

if __name__ == '__main__':
    unittest.main()