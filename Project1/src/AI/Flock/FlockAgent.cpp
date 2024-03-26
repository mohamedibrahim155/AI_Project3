#include "FlockAgent.h"
#include "../../Time.h"
#include "../../GraphicsRender.h"
#include "../../Time.h"
FlockAgent::FlockAgent(const glm::vec3& postion)
{
	LoadModel("Models/DefaultCube/DefaultCube.fbx");

	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().defaultShader);
	
	SetAgentColor(agentDefaultColor);
	
	transform.SetPosition(postion);
	transform.SetScale(agentScale);

	agentCollider.centre = transform.position;
	agentCollider.radius = 0.5f;
}
FlockAgent::FlockAgent()
{
	LoadModel("Models/DefaultCube/DefaultCube.fbx");

	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().defaultShader);
	
	SetAgentColor(agentDefaultColor);

	transform.SetScale(agentScale);

	agentCollider.centre = transform.position;
	agentCollider.radius = 0.5f;
}

FlockAgent::~FlockAgent()
{
}

void FlockAgent::DrawProperties()
{
	Model::DrawProperties();

	DrawAgentProperties();
}

void FlockAgent::SceneDraw()
{
	Model::SceneDraw();
}

void FlockAgent::Start()
{
}

void FlockAgent::Update(float deltaTime)
{
}

void FlockAgent::Render()
{
	if (!showDebug) return;

	GraphicsRender::GetInstance().DrawSphere(agentCollider.centre, agentCollider.radius, agentRenderColor, true);
}

void FlockAgent::OnDestroy()
{
}

void FlockAgent::Move(const glm::vec3& velocity)
{
	glm::vec3 direction = glm::normalize(velocity);

	if (glm::length(direction) >= 0)
	{

		glm::quat rotation = glm::quatLookAt(-direction, glm::vec3(0, 1, 0));


		glm::quat lerpValue = glm::slerp(transform.quaternionRotation, rotation, (float)Time::GetInstance().deltaTime);


		transform.SetQuatRotation(lerpValue);
	}


	transform.position += velocity * (float)Time::GetInstance().deltaTime;
}

void FlockAgent::SetAgentColor(const glm::vec4& color)
{
	for (std::shared_ptr<Mesh> mesh : meshes)
	{
		mesh->meshMaterial->material()->SetBaseColor(color);
	}
}

CircleCollider FlockAgent::GetAgentCollider()
{
	return agentCollider;
}

void FlockAgent::DrawAgentProperties()
{
	if (!ImGui::TreeNodeEx("Agent Properties", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	ImGui::Text("Show Debug");
	ImGui::SameLine();
	if (!ImGui::Checkbox("###ShowDebug", &showDebug))
	{
		ImGui::Text("Radius");
		ImGui::SameLine();
		ImGui::DragFloat("###Radius", &agentCollider.radius);
	}




	ImGui::TreePop();
}
