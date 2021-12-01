#pragma once
#include "Component.h"
#include "Shape.h"

class ShapeRenderer : public Component
{
public:
	ShapeRenderer(Entity* owner) : Component(owner) 
	{
        m_name = "Shape Renderer";
        m_shader = new Shader("Shaders/cubeShader.vs", "Shaders/cubeShader.fs");
        m_shape = new Cube(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	}

	void setShape(Shape shape)
	{
		m_shape = &shape;
	}

	void setShader(Shader shader)
	{
		m_shader = &shader;
	}

	void render(Display* display)
	{
        int width, height;
        glfwGetWindowSize(display->getWindow(), &width, &height);

        glBindVertexArray(m_shape->getVAO());

        // activate shader
        m_shader->use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(display->getCamera()->Zoom), (float)width / (float)height, 0.1f, 100.0f);
        m_shader->setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = display->getCamera()->GetViewMatrix();
        m_shader->setMat4("view", view);
        
        
        float* position = m_owner->transform->getPosition();
        float* rotation = m_owner->transform->getRotation();
        float* scale = m_owner->transform->getScale();

        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(position[0], position[1], position[2]));
        model = glm::rotate(model, glm::radians(rotation[2]), glm::vec3(0.f, 0.f, 1.f));
        model = glm::rotate(model, glm::radians(rotation[1]), glm::vec3(0.f, 1.f, 0.f));
        model = glm::rotate(model, glm::radians(rotation[0]), glm::vec3(1.f, 0.f, 0.f));
        model = glm::scale(model, glm::vec3(scale[0], scale[1], scale[2]));
        m_shader->setMat4("model", model);

        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        m_shader->setVec3("light.position", lightPos);
        m_shader->setVec3("viewPos", display->getCamera()->Position);

        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);

        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
        m_shader->setVec3("light.ambient", ambientColor);
        m_shader->setVec3("light.diffuse", diffuseColor);
        m_shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // material properties
        m_shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        m_shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        m_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        m_shader->setFloat("material.shininess", 32.0f);

        if (wireframeMode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
	}

    void renderComponentUI()
    {
        ImGui::Checkbox("Enable wireframe mode", &wireframeMode);
    }

private:
    
	Shape* m_shape;
	Shader* m_shader;
    bool wireframeMode;
};