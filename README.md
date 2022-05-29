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

<p align="middle">
  <img src="/Previews/Ex1-1.jpg" width="300" />
  <img src="/Previews/Ex1-2.jpg" width="300" />
  <br/>
  <img src="/Previews/Ex1-3.jpg" width="300" />
  <img src="/Previews/Ex1-4.jpg" width="300" /> 
</p>

### Exercicio 2: Explorar números diferentes de oitavas, frequencia e persistência

| Parâmetros | Resultado |
| --- | --- |
| Octave = 3<br/>Frequency = 6<br/>Persistence = 0.4 | <img src="/Previews/Ex2-1.jpg" width="500" /> |
| Octave = 4<br/>Frequency = 8<br/>Persistence = 1.0 | <img src="/Previews/Ex2-2.jpg" width="500" /> |
| Octave = 2<br/>Frequency = 3<br/>Persistence = 0.7 | <img src="/Previews/Ex2-3.jpg" width="500" /> |
| Octave = 3<br/>Frequency = 10<br/>Persistence = 0.1 | <img src="/Previews/Ex2-4.jpg" width="500" /> |
| Octave = 5<br/>Frequency = 11<br/>Persistence = 0.2 | <img src="/Previews/Ex2-5.jpg" width="500" /> |
| Octave = 1<br/>Frequency = 16<br/>Persistence = 0.9 | <img src="/Previews/Ex2-6.jpg" width="500" /> |
| Octave = 6<br/>Frequency = 6<br/>Persistence = 0.6 | <img src="/Previews/Ex2-7.jpg" width="500" /> |
| Octave = 4<br/>Frequency = 12<br/>Persistence = 0.5 | <img src="/Previews/Ex2-8.jpg" width="500" /> |

### Exercicio 3: Criar 2 diferentes mapeamentos de biomas

#### (Tentativa de criar) Planície:
<img src="/Previews/Ex3-1.jpg" width="600" />

#### (Tentativa de criar) Galáxia:
<img src="/Previews/Ex3-2.jpg" width="600" />
