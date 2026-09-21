# Especificação da Implementação

## Integrantes da dupla

- **Aluno 1 - Nome**: Lucas Rossi Klein
- **Aluno 1 - Cartão UFRGS**: 586981

- **Aluno 2 - Nome**: <mark>`<preencher>`</mark>
- **Aluno 2 - Cartão UFRGS**: <mark>`<preencher>`</mark>

## Detalhes do que será implementado

- **Título do trabalho**: PEAK
- **Parágrafo curto descrevendo o que será implementado**: 
O projeto consiste na re-implementação do jogo PEAK, que é um jogo de escalada no estilo cartoon. A dinamica principal do jogo exige com que o jogador passe por obstáculos utilizando da escalada e movimentação como forma de atingir o objetivo de chegar até o ponto mais alto do cenário.  

## Especificação visual

### Vídeo - Link

> [!IMPORTANT]
> - Coloque aqui um link para um vídeo que mostre a aplicação gráfica
>   de referência que você vai implementar. **Sua implementação deverá
>   ser o mais parecido possível com o que é mostrado no vídeo (mais
>   detalhes abaixo).**
> - **Você não pode escolher como referência: (1) algum trabalho realizado
>   por outros alunos desta disciplina, em semestres anteriores. (2) Minecraft.**
> - Por exemplo, você pode colocar um vídeo de um jogo que você gosta,
>   e seu trabalho final será uma re-implementação do jogo.
> - O vídeo pode ser um link para YouTube, Google Drive, ou arquivo mp4 dentro
>   do próprio repositório. Mas, garanta que qualquer um tenha
>   permissão de acesso ao vídeo através deste link.

<mark>`<preencher>`</mark>

### Vídeo - Timestamp

> [!IMPORTANT]
> - Coloque aqui um **intervalo de ~30 segundos** do vídeo acima, que
>   será a base de comparação para avaliar se o seu trabalho final
>   conseguiu ou não reproduzir a referência.

- **Timestamp inicial**: <mark>`<preencher>`</mark>
- **Timestamp final**: <mark>`<preencher>`</mark>

### Imagens

> [!IMPORTANT]
> - Coloque aqui **três imagens** capturadas do vídeo acima, que você
>   irá usar como ilustração para as explicações que vêm abaixo.
> - As imagens devem estar armazenadas neste repositório, no diretório
>   `images/spec/`, com os nomes `image1`, `image2` e `image3`.
> - Cada imagem deve usar o formato `.jpg` ou `.png`. Ajuste a extensão
>   nos vínculos abaixo para que corresponda ao arquivo armazenado.
> - Escolha imagens que correspondam a momentos do intervalo indicado
>   acima ou que sejam relevantes para a comparação com a implementação.

#### Imagem 1

- **Descrição**: <mark>`<preencher>`</mark>

![Imagem 1](images/spec/image1.jpg)

#### Imagem 2

- **Descrição**: <mark>`<preencher>`</mark>

![Imagem 2](images/spec/image2.jpg)

#### Imagem 3

- **Descrição**: <mark>`<preencher>`</mark>

![Imagem 3](images/spec/image3.jpg)

## Especificação textual

### Malhas poligonais complexas
O jogo vai utilizar de modelos 3D para superfícies de escalada e obstáculos, para o personagem do jogador, cenário e objetos. O terreno, arvores mostradas no video foram modeladas atraves de malhas poligonais em 3d.

### Transformações geométricas controladas pelo usuário
Assim como no video, o jogador vai controlar a movimentação do próprio modelo do personagem, podendo andar, girar e executar ações de forma fluidas pelo cenário.

### Diferentes tipos de câmeras
O jogador vai poder jogar em primeira pessoa, no formato padrão, ou poderá escolher jogar em terceira pessoa, ambas cameras mostradas no video.

### Instâncias de objetos
A ambientação de cenários e objetos interagiveis vai fazer uso de múltiplas instancias de mesmos objetos, em situações ou locais diferentes. O modelo das árvores que aparecem no vídeo é um exemplo de mais de uma instância do objeto "árvore".

### Testes de intersecção
Todo o principio da escalada no jogo se baseia nessa dinâmica. Quando o jogador for subir uma superfície, o jogo exige um contato entre ambos para que a mecânica seja realizada. A mecânica é demonstrada no video. 

### Modelos de Iluminação em todos os objetos
O jogo, assim como mostrado no video, vai possuir um sistema de iluminação a partir do Sol.

### Mapeamento de texturas em todos os objetos
Utilizaremos de texturas, no estilo cartoon, disponíveis na internet, corrigindo as coordenadas UV dos modelos para que fiquem corretas e que não pareçam artificialmente esticadas e aplicando nos elementos do jogo.
 

### Movimentação com curva Bézier cúbica
Será realizada as correntes de ar em partículas que seguem caminhos curvos, indicando visualmente ao jogador quando há ventos fortes podendo causar a queda.

### Animações baseadas no tempo ($\Delta t$)
O movimento de escalada do jogador é um exemplo de implementação desse caso. Será calculado multiplicando a velocidade pelo tempo entre cada quadro, o chamado Delta t, fazendo com que a velocidade o personagem seja constante e uniforme, sem ser afetada pelas variações na taxa de FPS.

### Funcionalidade extra obrigatória

- Interface gráfica de stamina e itens carregados 
- Sprite de itens

## Limitações esperadas

> [!IMPORTANT]
> - Coloque aqui uma lista de detalhes visuais ou de interação que
>   aparecem no vídeo e/ou imagens acima, mas que você **não pretende
>   implementar** ou que você **irá implementar parcialmente**.
> - Para cada item, **explique por que** não será implementado ou por
>   que será implementado parcialmente.

<mark>`<preencher>`</mark>
