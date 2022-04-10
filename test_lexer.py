import unittest
import lexer
import os

class TestLexer(unittest.TestCase):
    
    def test_tokenize(self):
        path_valid = "examples/valid/"
        path_invalid = "examples/invalid/"
        path_extra = "examples/extra/"

        valid_files = [path_valid + f for f in os.listdir(path_valid) if f.endswith(".c")]
        invalid_files = [path_invalid + f for f in os.listdir(path_invalid) if f.endswith(".c")]
        extra_files = [path_extra + f for f in os.listdir(path_extra) if f.endswith(".c")]
        
        for f in valid_files + invalid_files:
            tokens = lexer.tokenize(f)
            self.assertTrue(tokens)
            self.assertIsInstance(tokens, list)
            self.assertTrue(all(t and isinstance(t, str) for t in tokens))

    def test_is_hexa(self):
        self.assertTrue(lexer.is_hexa('0x1945abcDC'))
        self.assertTrue(lexer.is_hexa('0X123'))
        self.assertTrue(lexer.is_hexa('0x00a'))
        self.assertFalse(lexer.is_hexa('0x123abcdefg'))
        self.assertFalse(lexer.is_hexa('0xx'))
        self.assertFalse(lexer.is_hexa('0x'))
        self.assertFalse(lexer.is_hexa('00x12'))


if __name__ == '__main__':
    unittest.main()
