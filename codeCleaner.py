# -*- coding: utf-8 -*-
import re
import sys
import string
import numpy as np

def commentsCleaner(code): # função com Regex para retirar comentários de um arquivo do tipo .c
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " " 
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, code)

def preprocessingCode(code): # Padroniza o código para lower case (letras minúsculas)
    code = code.lower()
    return code