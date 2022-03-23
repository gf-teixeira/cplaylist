# cplaylist

cplaylist é um progama que gerencia uma playlist de música (ou uma playlist de qualquer mídia .mp3).

cplaylist possibilita:

- Inserir música

- Excluir música

- Listar playlist

- Ordenar por ordem de inserção

- Ordenar por Título

- Tocar música anterior
 
- Tocar música atual.
 
- Tocar próxima música
 
- Pausar
 
- Voltar a tocar
 
# Requisitos/dependências

- MPV Playler

- Sistema Operacional derivado de Unix.

# Como rodar?

- compile

      gcc *.c -o cplaylist
    
 - execute

       ./cplaylist
    
Para conseguir tocar uma música é necessário possuir um arquivo mp3 de mesmo nome no diretório raiz do projeto. 
Exemplo: quero tocar a música "Stromae - Alors On Danse.mp3", então é necessário ter o arquivo no diretório raiz do projeto e, no momento da inserção da música na playlist, basta inserir o mesmo nome do arquivo (sem a extensão .mp3).



