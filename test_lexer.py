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
            self.assertTrue(all(isinstance(t, str) for t in tokens))

if __name__ == '__main__':
    unittest.main()