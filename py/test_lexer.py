import unittest
import lexer
import os

class TestLexer(unittest.TestCase):
    
    def test_tokenize(self):
        paths = ["examples/valid/", "examples/invalid/"]
        files = [path + f for path in paths for f in os.listdir(path) if f.endswith(".c")]
        
        for file in files:
            tokens_text = lexer.tokenize(file)
            self.assertTrue(tokens_text)
            self.assertIsInstance(tokens_text, list)
            self.assertTrue(all(t and isinstance(t, str) for t in tokens_text))

    def test_is_hexa(self):
        valid = ['0x1945abcDC', '0X123', '0x00a', '0X1', '0x123AbCdEf', '0XA', '0x0CFC', '0x0']
        invalid = ['0x123abcdefg', '0xx', '0x', '00x12', '01x1', '1x0', '0x0156I0, 0b0', '0', '123']

        for hex in valid:
            self.assertTrue(lexer.is_hexa(hex))
        for not_hex in invalid:
            self.assertFalse(lexer.is_hexa(not_hex))

    def test_lex(self):
        paths = ["examples/valid/", "examples/invalid/"]
        files = [path + f for path in paths for f in os.listdir(path) if f.endswith(".c")]
        
        for file in files:
            tokens = lexer.lex(file)
            self.assertTrue(tokens)
            self.assertIsInstance(tokens, list)
            self.assertTrue(all(t.text and isinstance(t.text, str) for t in tokens))
            self.assertTrue(all(isinstance(t.type, lexer.TokenType) and t.type != lexer.TokenType.UNKNOWN for t in tokens))


if __name__ == '__main__':
    unittest.main()
