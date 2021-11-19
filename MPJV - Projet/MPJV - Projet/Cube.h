#pragma once
#include "Shape.h";


class Cube : public Shape{

public:
	Cube(glm::vec3 position, glm::vec3 size):Shape(position)
	{
        m_shader = new Shader("Shaders/cubeShader.vs", "Shaders/cubeShader.fs");
        float x = size.x / 2;
        float y = size.y / 2;
        float z = size.z / 2;
        float vertices[] = {
        //back face
        -x, -y, -z,
         x, -y, -z,
         x,  y, -z,
         x,  y, -z,
        -x,  y, -z,
        -x, -y, -z,

        //front face
        -x, -y,  z,
         x, -y,  z,
         x,  y,  z,
         x,  y,  z,
        -x,  y,  z,
        -x, -y,  z,

        //left face
        -x,  y,  z,
        -x,  y, -z,
        -x, -y, -z,
        -x, -y, -z,
        -x, -y,  z,
        -x,  y,  z,

        //right face
         x,  y,  z,
         x,  y, -z,
         x, -y, -z,
         x, -y, -z,
         x, -y,  z,
         x,  y,  z,

         //bottom face
        -x, -y, -z,
         x, -y, -z,
         x, -y,  z,
         x, -y,  z,
        -x, -y,  z,
        -x, -y, -z,

        //top face
        -x,  y, -z,
         x,  y, -z,
         x,  y,  z,
         x,  y,  z,
        -x,  y,  z,
        -x,  y, -z,
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        m_shader->use();
	}
	void render(Display* display) override
	{
        int width, height;
        glfwGetWindowSize(display->getWindow(), &width, &height);

        glBindVertexArray(m_VAO);
        // activate shader
        m_shader->use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(display->getCamera()->Zoom), (float)width / (float)height, 0.1f, 100.0f);
        m_shader->setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = display->getCamera()->GetViewMatrix();
        m_shader->setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, m_position);
        float angle = 20.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        m_shader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
	}
};