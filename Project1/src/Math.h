#pragma once
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
namespace MathUtils 
{
	class Math
	{
	public:
		static bool DecomposeTransform(const glm::mat4& transform, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale);
		static int GetRandomIntNumber(int min, int max);
		static float GetRandomFloatNumber(float min, float max);
		static glm::vec2 randomInsideUnitCircle(float radius);
		static glm::vec2 randomInsideUnitCircle();
		static float squareMagnitude(glm::vec2 value);
		static glm::vec4 LerpVec4(const glm::vec4& start, const glm::vec4& end, float t);
		static glm::vec3 LerpVec3(const glm::vec3& start, const glm::vec3& end, float t);
		static glm::vec2 LerpVec2(const glm::vec2& start, const glm::vec2& end, float t);
	};

}