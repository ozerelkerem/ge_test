#include "SkinnedModelComponent.h"

#include<Api.h>
#include<engine/ActorManager.h>
#include <editor/ConstantModels.h>
SkinnedModelComponent::SkinnedModelComponent(Model *m) : IModelComponent(), Component(), rootBone(ActorID::INVALID_HANDLE)
{
	setModel(m);
	numberOfMaterials = m->numOfMeshes;
	materials.resize(numberOfMaterials, ConstantMaterials::Materials::defaultMaterial);
}


SkinnedModelComponent::~SkinnedModelComponent()
{
}

void SkinnedModelComponent::matchBones()
{
	if (!getModel())
		return;
	effectlist.clear();
	effectlist.resize(getModel()->numOfMeshes);
	for (int i = 0; i < effectlist.size(); i++)
		effectlist[i].resize(((SkinnedMesh *)getModel()->meshes[i])->bones.size(),ActorID::INVALID_HANDLE);
	Actor *a = GE_Engine->actorManager->GetActor(this->rootBone);

	std::list<Actor *> queue;
	Actor *s;
	queue.push_back(a);
	//AnimationNodeMap tempmap(currentAnimation->animationNodeMap);

	while (!queue.empty())
	{
		s = queue.front();
		
		for (int i = 0; i < effectlist.size(); i++)
		{
			auto bonelist = ((SkinnedMesh*)getModel()->meshes[i])->bones;
			auto it = std::find_if(bonelist.begin(), bonelist.end(),
				[&s](const std::pair<std::string, glm::mat4>& element) { return element.first == s->name; });
			if (it != bonelist.end())
			{//found
				effectlist[i][it - bonelist.begin()] = s->actorID;
			}
		
		}


		queue.pop_front();

		for (int i = 0; i < s->numberOfChildren; i++)
		{
			queue.push_back(GE_Engine->actorManager->GetActor(s->children[i]));
		}
	}



}
