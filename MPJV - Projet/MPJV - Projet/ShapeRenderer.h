#pragma once
#include "Component.h"
#include "Shape.h"

class ShapeRenderer : public Component
{
public:
	ShapeRenderer(Entity* owner) : Component(owner) 
	{

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

        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, m_shape->getPosition());
        model = glm::rotate(model, glm::radians(m_shape->getRotation().z), glm::vec3(0.f, 0.f, 1.f));
        model = glm::rotate(model, glm::radians(m_shape->getRotation().y), glm::vec3(0.f, 1.f, 0.f));
        model = glm::rotate(model, glm::radians(m_shape->getRotation().x), glm::vec3(1.f, 0.f, 0.f));
        model = glm::scale(model, m_shape->getScale());
        m_shader->setMat4("model", model);

        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        m_shader->use();
        m_shader->setVec3("light.position", lightPos);
        m_shader->setVec3("viewPos", display->getCamera()->Position);

        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);
        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
        m_shader->setVec3("light.ambient", ambientColor);
        m_shader->setVec3("light.diffuse", diffuseColor);
        m_shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // material properties
        m_shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        m_shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        m_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        m_shader->setFloat("material.shininess", 32.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);
	}

private:
	Shape* m_shape;
	Shader* m_shader;
};