#pragma once
#include "../../model.h"

struct CircleCollider
{
    CircleCollider() = default;
    CircleCollider(const glm::vec3& _centre, float _radius) : 
        centre(_centre), 
        radius(radius) { }

    glm::vec3 centre = glm::vec3(0);
    float radius = 0.5f;
};
class FlockAgent : public Model
{  
public:
    FlockAgent(const glm::vec3& postion);
	FlockAgent();
	~FlockAgent();

    void DrawProperties() override;
    void SceneDraw() override;

    void Start() override;
    void Update(float deltaTime) override;
    void Render() override;
    void OnDestroy() override;

    void Move(const glm::vec3& velocity);
    void SetAgentColor(const glm::vec4& color);

    CircleCollider GetAgentCollider();
private:

    void DrawAgentProperties();

    CircleCollider agentCollider;

    glm::vec3 agentScale{ 0.10f };
    glm::vec4 agentDefaultColor{ 0,1,0,1 };
    glm::vec4 agentRenderColor{0.8f,0.8f,0,1 };

    bool showDebug = false;

   


};

