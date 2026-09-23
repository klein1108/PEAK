# Especificação da Implementação

## Integrantes da dupla

- **Aluno 1 - Nome**: Lucas Rossi Klein
- **Aluno 1 - Cartão UFRGS**: 586981

- **Aluno 2 - Nome**: André Torquato Pedreira
- **Aluno 2 - Cartão UFRGS**: 600986 

## Detalhes do que será implementado

- **Título do trabalho**: PEAK
- **Parágrafo curto descrevendo o que será implementado**: 
O projeto consiste na re-implementação do jogo PEAK, que é um jogo de escalada no estilo cartoon. A dinamica principal do jogo exige com que o jogador passe por obstáculos utilizando da escalada e movimentação como forma de atingir o objetivo de chegar até o ponto mais alto do cenário.  

## Especificação visual

### Vídeo - Link
https://drive.google.com/file/d/1zBXzbzcNcBtvnMKIn-JOcTQs8mJrp0rK/view?usp=sharing

### Vídeo - Timestamp
- **Timestamp inicial**: 19:00
- **Timestamp final**: 19:30

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

- **Representação da escalada dentro do jogo :**
  
![Imagem 1](images/spec/image1.png)

#### Imagem 2

- **Representação do funcionamento do vento dentro do jogo:**

![Imagem 2](images/spec/image2.png)

#### Imagem 3

- **Representação da alternância de câmera de visão do personagem:**

![Imagem 3](images/spec/image3.png)

## Especificação textual

### Malhas poligonais complexas
O jogo vai utilizar de modelos 3D para superfícies de escalada e obstáculos, para o personagem do jogador, cenário e objetos. O terreno, arvores mostradas no video foram modeladas atraves de malhas poligonais em 3d.

### Transformações geométricas controladas pelo usuário
Assim como no video, o jogador vai controlar a movimentação do próprio modelo do personagem, podendo andar, girar e executar ações de forma fluidas pelo cenário.

> Comentário Professor: Implementem as mãos do personagem: elas são essenciais para que o resultado fique próximo da referência visual.

### Diferentes tipos de câmeras
O jogador vai poder jogar em primeira pessoa, no formato padrão, ou poderá escolher jogar em terceira pessoa, ambas cameras mostradas no video.

### Instâncias de objetos
A ambientação de cenários e objetos interagiveis vai fazer uso de múltiplas instancias de mesmos objetos, em situações ou locais diferentes. O modelo das árvores que aparecem no vídeo é um exemplo de mais de uma instância do objeto "árvore".

### Testes de intersecção
Todo o principio da escalada no jogo se baseia nessa dinâmica. Quando o jogador for subir uma superfície, o jogo exige um contato entre ambos para que a mecânica seja realizada. A mecânica é demonstrada no video. 

### Modelos de Iluminação em todos os objetos
O jogo, assim como mostrado no video, vai possuir um sistema de iluminação a partir do Sol.

> Comentário Professor: Vocês descrevem apenas que a iluminação provém do Sol. Especifiquem o modelo de iluminação que aplicarão a todos os objetos.

### Mapeamento de texturas em todos os objetos
Utilizaremos de texturas, no estilo cartoon, disponíveis na internet, corrigindo as coordenadas UV dos modelos para que fiquem corretas e que não pareçam artificialmente esticadas e aplicando nos elementos do jogo.
 

### Movimentação com curva Bézier cúbica
Será realizada as correntes de ar em partículas que seguem caminhos curvos, indicando visualmente ao jogador quando há ventos fortes podendo causar a queda.

### Animações baseadas no tempo ($\Delta t$)
O movimento de escalada do jogador é um exemplo de implementação desse caso. Será calculado multiplicando a velocidade pelo tempo entre cada quadro, o chamado Delta t, fazendo com que a velocidade o personagem seja constante e uniforme, sem ser afetada pelas variações na taxa de FPS.

### Funcionalidade extra obrigatória

- Interface gráfica de stamina e itens carregados 
- Sprite de itens

> Comentário Professor: A interface gráfica do jogo é relativamente simples, e não entendi o que vocês querem dizer com os sprites mencionados. Descrevam melhor essas funcionalidades ou escolham outra funcionalidade extra. Sugiro alternativas como sombras e seleção de objetos com o mouse (picking).

## Limitações esperadas

>   Mútiplos biomas/níveis/fases : Como a criação de múltiplas fases na re-implementação não é necessária para demonstrar a maioria das mecânicas, efeitos gráficos e complexidades inerentes ao jogo original, a decisão de simplificação do número de níveis foi tomada.

>   Possibilidade de arremessar itens : Tal ação não se torna necessária quando o jogo é jogado sozinho. Como a re-implementação é single player , tal funcionalidade será descartada.

>   Efeitos prejudiciais à saúde do jogador como : envenenamento , congelamento e fome não serão implementados pois não trazem ganho direto para a demonstração das técnicas de computação gráfica e físicas de escalada, que são o foco central do trabalho.

>   Alguns itens ou objetos do ambiente como : certas pedras específicas , cogumelos e alguns dos vários consumíveis do jogo original não serão implementados pois há uma quantidade e variedade enorme desses elementos , o que torna a sua íntegra implementação algo inviável dentro do contexto do nosso projeto.

> "A Névoa " não será incluída à nossa re-implementação , pois seu objetivo no jogo original é aumentar a dificuldade da gameplay ao limitar o tempo de conclusão de fase do jogador , porém o foco do projeto é mais demonstrativo do que uma real aplicação de um jogo competitivo funcional.
