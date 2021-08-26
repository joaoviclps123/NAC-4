# NAC4 - Disruptive Architectures IOT e IA

**Nome dos alunos:**

Bruno Muhlmann - RM84840

Gabriel Andrade - RM83197

João Victor - RM84878

Larissah Santos - RM85169

Victor Fernando - RM85058

**Turma:** 2TDSF

**Ano:** 2021

## Objetivo / descrição do Projeto

O projeto tem como objetivo desenvolver uma estação meteorológica que recebe as informações sobre vento, temperatura e 
luminosidade de sensores e envia para um servidor que mostra as informações em um dashboard, e caso o vento passe de 80km/h 
envia um alerta automaticamente via twitter, as informações ficam armazenadas em um banco de dados na cloud. 
Foram utilizados para o desenvolvimento do projeto: Com0Com, SimulIDE, Node-Red, IBM Cloud e GitHub

## Diagrama do projeto

<img src="/imagem.PNG" width="250"> <img src="/imagem.PNG" width="250">

## Como usar 

* Link para instalar o [Com0Com](https://sourceforge.net/projects/com0com/)

* Link para instalar o [SimulIde](https://www.simulide.com/p/downloads.html)

* Link para instalar o [NodeJS LTS](https://nodejs.org/en/download/)
Após a instalação abra o cmd e digite npm install -g --unsafe-perm node-red
Abrira uma url para o acesso 

* Link passar acessar o [IBM Cloud](https://www.ibm.com/br-pt/cloud?p1=Search&p4=43700054913953751&p5=e&gclid=CjwKCAjw95yJBhAgEiwAmRrutMdXf2RZ53UaSt_7rcANxcpKgpxVYbwDkmON2THrv4wz6orTqbXRZxoCZxYQAvD_BwE&gclsrc=aw.ds)

* Link para acessar o [Twitter Developer](https://developer.twitter.com/en/apps)



Após a instalação dos aplicativos clone o repositório:

    cd /home/nac
    git clone https://github.com/joaoviclps123/NAC-4.git
    cd nac4
    ls


Abra os arquivos .ino, .simu e .hex no SimulIde e compile.                                                                    
Abra o arquivo .json no node-red coloque as extensões do dashboard e twitter e de um deploy. Para acessar o Dashboard coloque /ui no final da url                               
E abra o twitter developer para ver os tweets.                                                                                             

## Link de vídeo demonstração

[NAC 4 - Estação Meteorológica](https://www.youtube.com/watch?v=KR_ZOCSi4BA)


### Referências 

* [Canal Arnaldo Viana Jr.](https://www.youtube.com/channel/UCb6MEkxngDA5E1XBs_zULgQ)
