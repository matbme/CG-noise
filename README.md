# Exercício de geração procedural
#### Disciplina: Computação Gráfica
Autor: Mateus Melchiades

## Compilando e executando

Compilando a biblioteca libnoise:
```sh
# Primeiramente, inicializar o submodule que contém a libnoise
$ git submodule update --init
# Rodar script gerado para compilar a biblioteca
$ ./build-libnoise.sh
```

Compilando e executando o código de geração:
```sh
$ mkdir -p build && cd build
$ cmake ..
$ make
$ ./app
```

## Resultados

### Exercicio 1: Gerar 4 mapas "vizinhos"
