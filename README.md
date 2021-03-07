# codeSimilarity
Esse projeto é focado na comparação de códigos na busca de plágio.

Configuração utilizada:
- O algoritmo foi validado com Linux Debian 9;
- Python 3.7.3

## Instale as dependências

Para instalar as dependências é muito simples! Apenas copie e cole a linha abaixo no seu terminal. Lembre-se de estar dentro da pasta que possui o arquivo "requiments.txt":

$ pip install -r requirements.txt

## Como executar a verificação de plágio

Para executar a verificação de plágio você deve seguir os passos abaixo:
- Mova para dentro da pasta "inputCodes" todos os códigos que você deseja analisar;
- Execute o arquivo "main.py" e ele far todo o trabalho! Para isso basta copiar a linha abaixo:

$ python main.py

## Como interpretar a saída

A saída do programa será uma lista de similaridades entre todos os códigos analisados. A similaridade é dada entre **0 a 1**, isto é, se for 1 é 100% igual, se 0 é 0% igual. A figura abaixo mostra exatamente como a sada  formatada:

![image](https://user-images.githubusercontent.com/68967742/110228309-d9fce080-7ede-11eb-9010-63297b8ffccb.png)

## Observações

O foco desse projeto é a análise de similaridade entre CÓDIGOS, não obstante este humilde autor fez alguns testes com textos e notou que o algoritmo conseguir estabelecer relações entre os textos analisados com sucesso!

Na figura abaixo podemos observar seis textos sob análise. Evidencio aqui que o "texto6.txt"  oriundo de uma fusão entre partes dos textos 1, 3 e 4. Nota-se que o algoritmo conseguiu extrair a similaridade com sucesso de tais arquivos e possibilitou um alerta para que esses textos sejam olhados com carinho.

![image](https://user-images.githubusercontent.com/68967742/110228465-31e81700-7ee0-11eb-968d-5f39a5dde608.png)
