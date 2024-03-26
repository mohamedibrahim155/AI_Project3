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
	};

}