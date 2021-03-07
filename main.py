# -*- coding: utf-8 -*-
from os import listdir
from os.path import isfile, join
from codeCleaner import commentsCleaner, preprocessingCode
from similarityCalculator import vocabularyConstructor, fit_transform, codeSimilarities
from termcolor import colored
import numpy as np

plagiarism = 0.7 # limites para definição de plágio
maybePlagiarism = 0.3 # limites para definição de provável plágio

path = "inputCodes/" # caminho da pasta onde estão os arquivos
myFiles = [path+oneFile for oneFile in listdir(path) if isfile(join(path, oneFile))] # cria lista com todos os caminhos de todos os arquivos

print("{} arquivo(s) a serem analisados: ".format(len(myFiles)))
for oneFile in myFiles: print('\t'+oneFile)
print("\nIniciando limpeza dos códigos...")

listOfCode = [] # lista que armazena todos os códigos a serem comparados
for oneFile in myFiles: # leitura de arquivo por arquivo
    with open(oneFile, encoding = "ISO-8859-1") as f:
        noCommentsFile = commentsCleaner(f.read()) # chama função de limpeza do código (remove comentários)
        codePreprocessed = preprocessingCode(noCommentsFile) # padroniza todos os códigos em lower case (letras minúsculas)
        updateFile = open(oneFile, "w")
        updateFile.write(codePreprocessed) # grava código padronizado no respectivo arquivo antigo
        updateFile.close()
        listOfCode.append(codePreprocessed) # adiciona a lista de códigos o referente ao arquivo atual do loop

print("Criando vocabulário...")
vocabulary = vocabularyConstructor(listOfCode) # cria um vocabulário sobre todos os códigos em análise

print("Verificando presença de palavras no vocabulário...")
features = [fit_transform(code, vocabulary) for code in listOfCode] # cria uma matriz para cada código averiguando a existência ou não da palavra do vocabulário no código
features = np.array(features)

print("\nCalculando matriz de similaridade...")
for count, oneFile in enumerate(myFiles):
    print("\nCódigo analisado: "+oneFile)
    for codeName, similarity in codeSimilarities(myFiles, count, features, listOfCode, len(myFiles)): # cálculo de similaridade entre códigos
        if (similarity >= plagiarism):
            print(colored('\tCódigo: {:<70} Similaridade: {:>10,.2f}'.format(codeName, round(similarity, 2)),'red', attrs=['bold','blink']))
        elif (similarity >= maybePlagiarism):
            print(colored('\tCódigo: {:<70} Similaridade: {:>10,.2f}'.format(codeName, round(similarity, 2)),'yellow', attrs=['bold']))
        else:
            print(colored('\tCódigo: {:<70} Similaridade: {:>10,.2f}'.format(codeName, round(similarity, 2)),'green', attrs=['bold']))
