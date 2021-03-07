# -*- coding: utf-8 -*-
import re
import string
import numpy as np

# Constrói um vocabulário acerca do código

def vocabularyConstructor(textsList): # utiliza-se um set (conjunto) para receber as palavras do vocabulário, assim não teremos repetições
    textSet = set()
    for w in [words.split() for words in textsList]:
        textSet.update(w)
    return textSet

def fit_transform(text, words): # Converte o texto em um vetor, onde compara se cada palavra obtida no vetor de todas as palavras contém ou não em cada texto. Insere 1 se sim e 0 se não.
 
    return [int(word in text.split()) for word in words]

def cosineSimilarity(v, w):
    return np.dot(v, w)/np.sqrt(np.dot(v, v)*np.dot(w, w)) # cálculo de similaridade entre dois elementos (ALMA DO ALGORITMO!!!)   

def codeSimilarities(codeNames, idCode, features, allCodes, nOfCodes):
    """
    Dado o texto a ser analisado, a função retorna em ordem descrecente quais os demais textos são
    similares ao analisado. A função retorna matriz de 2 por nOfCodes (número de códigos), na qual a primeira e a segunda coluna
    refere-se ao código analisado e a similaridade do código analisado, respectivamente.
    """
    similarity = [[cosineSimilarity(features[idCode], feature), int(i)] for i, feature in enumerate(features)]
    similarity = np.array(sorted(similarity, key=lambda sim: sim[0], reverse=True))    
    return [[codeNames[y], similarity[x, 0]] for x, y in enumerate(np.int0(similarity[1:,1]), 1)][:nOfCodes]