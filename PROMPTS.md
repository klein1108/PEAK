
# Prompt 1
Estou tentando adicionar isso no meu codigo mas nao funciona, fica esquisito. <br>

_[Imagem do erro]_

```c++
glm::mat4 modelground = Matrix_Translate(0.0f, 0.0f, 0.0f) * Matrix_Scale(

                                                                         GROUND_DEFAULT_SX,

                                                                         GROUND_DEFAULT_SY,

                                                                         GROUND_DEFAULT_SZ);

        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(modelground));

        glUniform1i(g_object_id_uniform, PLANE);

        DrawVirtualObject("the_plane");
```




meu while:


```c++
while (!glfwWindowShouldClose(window))

    {

        // Aqui executamos as operações de renderização



        // Definimos a cor do "fundo" do framebuffer como branco.  Tal cor é

        // definida como coeficientes RGBA: Red, Green, Blue, Alpha; isto é:

        // Vermelho, Verde, Azul, Alpha (valor de transparência).

        // Conversaremos sobre sistemas de cores nas aulas de Modelos de Iluminação.

        //

        //           R     G     B     A

        glClearColor(0.9f, 0.9f, 1.0f, 1.0f);



        // "Pintamos" todos os pixels do framebuffer com a cor definida acima,

        // e também resetamos todos os pixels do Z-buffer (depth buffer).

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        // Pedimos para a GPU utilizar o programa de GPU criado acima (contendo

        // os shaders de vértice e fragmentos).

        glUseProgram(g_GpuProgramID);



        // Computamos a posição da câmera utilizando coordenadas esféricas.  As

        // variáveis g_CameraDistance, g_CameraPhi, e g_CameraTheta são

        // controladas pelo mouse do usuário. Veja as funções CursorPosCallback()

        // e ScrollCallback().

        float r = g_CameraDistance;

        float y = r * sin(g_CameraPhi);

        float z = r * cos(g_CameraPhi) * cos(g_CameraTheta);

        float x = r * cos(g_CameraPhi) * sin(g_CameraTheta);



        // Abaixo definimos as varáveis que efetivamente definem a câmera virtual.

        // Veja slides 195-227 e 229-234 do documento Aula_08_Sistemas_de_Coordenadas.pdf.

        glm::vec4 camera_position_c = glm::vec4(x, y, z, 1.0f);             // Ponto "c", centro da câmera

        glm::vec4 camera_lookat_l = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);      // Ponto "l", para onde a câmera (look-at) estará sempre olhando

        glm::vec4 camera_view_vector = camera_lookat_l - camera_position_c; // Vetor "view", sentido para onde a câmera está virada

        glm::vec4 camera_up_vector = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);     // Vetor "up" fixado para apontar para o "céu" (eito Y global)



        // Computamos a matriz "View" utilizando os parâmetros da câmera para

        // definir o sistema de coordenadas da câmera.  Veja slides 2-14, 184-190 e 236-242 do documento Aula_08_Sistemas_de_Coordenadas.pdf.

        glm::mat4 view = Matrix_Camera_View(camera_position_c, camera_view_vector, camera_up_vector);



        // Agora computamos a matriz de Projeção.

        glm::mat4 projection;



        // Note que, no sistema de coordenadas da câmera, os planos near e far

        // estão no sentido negativo! Veja slides 176-204 do documento Aula_09_Projecoes.pdf.

        float nearplane = -0.1f; // Posição do "near plane"

        float farplane = -500.0f; // Posição do "far plane"



        if (g_UsePerspectiveProjection)

        {

            // Projeção Perspectiva.

            // Para definição do field of view (FOV), veja slides 205-215 do documento Aula_09_Projecoes.pdf.

            float field_of_view = 3.141592 / 3.0f;

            projection = Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);

        }

        else

        {

            // Projeção Ortográfica.

            // Para definição dos valores l, r, b, t ("left", "right", "bottom", "top"),

            // PARA PROJEÇÃO ORTOGRÁFICA veja slides 219-224 do documento Aula_09_Projecoes.pdf.

            // Para simular um "zoom" ortográfico, computamos o valor de "t"

            // utilizando a variável g_CameraDistance.

            float t = 1.5f * g_CameraDistance / 2.5f;

            float b = -t;

            float r = t * g_ScreenRatio;

            float l = -r;

            projection = Matrix_Orthographic(l, r, b, t, nearplane, farplane);

        }



        glm::mat4 model = Matrix_Identity(); // Transformação identidade de modelagem



        // Enviamos as matrizes "view" e "projection" para a placa de vídeo

        // (GPU). Veja o arquivo "shader_vertex.glsl", onde estas são

        // efetivamente aplicadas em todos os pontos.

        glUniformMatrix4fv(g_view_uniform, 1, GL_FALSE, glm::value_ptr(view));

        glUniformMatrix4fv(g_projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));



        // Desenhamos o modelo da esfera

        // model = Matrix_Translate(-1.0f, 0.0f, 0.0f) * Matrix_Rotate_Z(0.6f) * Matrix_Rotate_X(0.2f) * Matrix_Rotate_Y(g_AngleY + (float)glfwGetTime() * 0.1f);

        // glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));

        // glUniform1i(g_object_id_uniform, SPHERE);

        // DrawVirtualObject("the_sphere");



        // Desenhamos o modelo do coelho

        // model = Matrix_Translate(1.0f, 0.0f, 0.0f) * Matrix_Rotate_X(g_AngleX + (float)glfwGetTime() * 0.1f);

        // glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));

        // glUniform1i(g_object_id_uniform, BUNNY);

        // DrawVirtualObject("the_bunny");



        // Desenhamos o plano do chão

        // model = Matrix_Translate(0.0f, -1.1f, 0.0f);

        // glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));

        // glUniform1i(g_object_id_uniform, PLANE);

        // DrawVirtualObject("the_plane");



        glm::mat4 modelground = Matrix_Translate(0.0f, 0.0f, 0.0f) * Matrix_Scale(

                                                                         GROUND_DEFAULT_SX,

                                                                         GROUND_DEFAULT_SY,

                                                                         GROUND_DEFAULT_SZ);

        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(modelground));

        glUniform1i(g_object_id_uniform, PLANE);

        DrawVirtualObject("the_plane");



        // DESENHANDO PARTES DO PERSONAGEM

        glUniform1i(g_object_id_uniform, CHARACTER_BODY);

        DrawVirtualObject("the_peakchar_body");



        glUniform1i(g_object_id_uniform, CHARACTER_CLOTHES);

        DrawVirtualObject("the_peakchar_clothes");



        glUniform1i(g_object_id_uniform, CHARACTER_HEAD);

        DrawVirtualObject("the_peakchar_head");



        glUniform1i(g_object_id_uniform, CHARACTER_HAT);

        DrawVirtualObject("the_peakchar_hat");



        // Imprimimos na tela os ângulos de Euler que controlam a rotação do

        // terceiro cubo.

        TextRendering_ShowEulerAngles(window);



        // Imprimimos na informação sobre a matriz de projeção sendo utilizada.

        TextRendering_ShowProjection(window);



        // Imprimimos na tela informação sobre o número de quadros renderizados

        // por segundo (frames per second).

        TextRendering_ShowFramesPerSecond(window);



        // O framebuffer onde OpenGL executa as operações de renderização não

        // é o mesmo que está sendo mostrado para o usuário, caso contrário

        // seria possível ver artefatos conhecidos como "screen tearing". A

        // chamada abaixo faz a troca dos buffers, mostrando para o usuário

        // tudo que foi renderizado pelas funções acima.

        // Veja o link: https://en.wikipedia.org/w/index.php?title=Multiple_buffering&oldid=793452829#Double_buffering_in_computer_graphics

        glfwSwapBuffers(window);



        // Verificamos com o sistema operacional se houve alguma interação do

        // usuário (teclado, mouse, ...). Caso positivo, as funções de callback

        // definidas anteriormente usando glfwSet*Callback() serão chamadas

        // pela biblioteca GLFW.

        glfwPollEvents();

    }
```    

## Resposta:
O problema ocorre porque o OpenGL funciona como uma máquina de estados: quando você envia a matriz modelground (que provavelmente tem um valor de escala enorme para criar o chão) para a placa de vídeo usando o glUniformMatrix4fv, essa mesma matriz continua ativa para tudo o que for desenhado logo em seguida.

Como você não definiu e enviou uma nova matriz de modelo antes de chamar o DrawVirtualObject das partes do personagem, o seu personagem está sendo desenhado com a exata mesma escala gigante do chão. É por isso que ele fica esquisito ou some da tela (como visto na sua captura "image_9c1b05.png").

Para resolver isso, você precisa criar uma matriz para o personagem e enviá-la para a GPU logo após desenhar o chão.

Veja como corrigir o seu código:

```C++
        // Desenhamos o plano do chão
        glm::mat4 modelground = Matrix_Translate(0.0f, 0.0f, 0.0f) * Matrix_Scale(
                                                                 GROUND_DEFAULT_SX,
                                                                 GROUND_DEFAULT_SY,
                                                                 GROUND_DEFAULT_SZ);
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(modelground));
        glUniform1i(g_object_id_uniform, PLANE);
        DrawVirtualObject("the_plane");


        // --- CORREÇÃO AQUI ---
        // Criamos uma nova matriz para o personagem (sem a escala gigante do chão)
        // Se o chão estiver em Y = 0.0f, você pode precisar subir o personagem um pouco no eixo Y
        // para ele não ficar enterrado pela metade (ex: Matrix_Translate(0.0f, 1.0f, 0.0f))
        glm::mat4 model_character = Matrix_Translate(0.0f, 0.0f, 0.0f) * Matrix_Scale(1.0f, 1.0f, 1.0f); 
        
        // Enviamos a nova matriz do personagem para substituir a matriz do chão na GPU
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model_character));
        // ---------------------


        // DESENHANDO PARTES DO PERSONAGEM
        glUniform1i(g_object_id_uniform, CHARACTER_BODY);
        DrawVirtualObject("the_peakchar_body");

        glUniform1i(g_object_id_uniform, CHARACTER_CLOTHES);
        DrawVirtualObject("the_peakchar_clothes");

        glUniform1i(g_object_id_uniform, CHARACTER_HEAD);
        DrawVirtualObject("the_peakchar_head");

        glUniform1i(g_object_id_uniform, CHARACTER_HAT);
        DrawVirtualObject("the_peakchar_hat");
```

Resumo da regra de ouro do OpenGL: Sempre que você for desenhar um objeto diferente que está em uma posição ou tem um tamanho diferente, você precisa atualizar a variável g_model_uniform com a matriz específica dele antes de chamar a função que o desenha.

___

# Prompt 2

