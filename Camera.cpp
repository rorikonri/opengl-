#include "Camera.h"
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup) {
	Position = position;
	WorldUp = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::cross(Forward, WorldUp);
	Up = glm::normalize(glm::cross(Forward, Right));


}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup) {
	Position = position;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(pitch) * glm::sin(yaw);
	Forward.y = glm::sin(pitch);
	Forward.z = glm::cos(pitch) * glm::cos(yaw);
	Right = glm::cross(Forward, WorldUp);
	Up = glm::normalize(glm::cross(Forward, Right));
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::UpdateCameraVectors() {
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY) {
	Pitch -= deltaY*0.001f;
	Yaw -= deltaX*0.001f;
	UpdateCameraVectors();
}

void Camera::UpdataCameraPos() {
	//Position += glm::vec3(speedX/100, 0, -speedZ/100);
	Position += Forward * speedZ * 0.01f + Right * speedX * 0.01f + Up * speedY * 0.01f;
}