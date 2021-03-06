#include<editor/ConstantModels.h>
#include<Engine.h>
#include<engine/resource/ResourceManager.h>

namespace ConstantTextures
{
	Texture * Textures::lightTexture = nullptr;
	Texture * Textures::noTexture = nullptr;
	Texture * Textures::sceneTexture = nullptr;
	Texture * Textures::scriptTexture = nullptr;
	Texture * Textures::animationTexture = nullptr;
	Texture * Textures::modelTexture = nullptr;
	void Textures::initTextures()
	{
		Textures::lightTexture = GE_Engine->resourceManager->getResource<Texture>("ConstantIcons\\light.png");
		Textures::noTexture = GE_Engine->resourceManager->getResource<Texture>("ConstantIcons\\notexture.png");
		Textures::sceneTexture = GE_Engine->resourceManager->getResource<Texture>("ConstantIcons\\scene.png");
		Textures::animationTexture = GE_Engine->resourceManager->getResource<Texture>("ConstantIcons\\animation.png");
		Textures::scriptTexture = GE_Engine->resourceManager->getResource<Texture>("ConstantIcons\\script.png");
		Textures::modelTexture = GE_Engine->resourceManager->getResource<Texture>("ConstantIcons\\model.png");
		//Textures::cameraTexture->loadTexture();
	}
}
namespace ConstantMaterials
{
	Material * Materials::defaultMaterial = nullptr;

	void Materials::initMaterial()
	{
		Materials::defaultMaterial = new Material("Default-Material");
		Materials::defaultMaterial->ambientColor = glm::vec3(0.8, 0.8, 0.8);

		//Textures::cameraTexture->loadTexture();
	}
}

namespace ConstantPhysicMaterials
{
	physx::PxMaterial* PhysicMaterials::defaultMaterial = nullptr;

	void PhysicMaterials::initMaterials()
	{
		PhysicMaterials::defaultMaterial = PxGetPhysics().createMaterial(0.1, 0.1, 0.5);
	}
}
