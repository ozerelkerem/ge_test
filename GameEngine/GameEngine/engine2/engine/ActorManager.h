#pragma once
#include<Api.h>
#include<util/Handle.h>

#include<memory/MemoryChuckAllocator.h>
#include<engine/Actor.h>

class ActorContainer : public MemoryChunkAllocator<Actor, ACTOR_CHUNK_SIZE>
{
	ActorContainer(const ActorContainer&) = delete;
	ActorContainer& operator=(ActorContainer&) = delete;

public:
	ActorContainer() : MemoryChunkAllocator() {}
	virtual ~ActorContainer() {}

	virtual void DestroyActor(Actor* object)
	{
		// call d'tor
		object->~Actor();

		this->DestroyObject(object);
	}
};
class Actor;

class ActorManager
{
	ComponentManager *componentManagerInstance;

	using PendingDestroyedActors = std::vector<ActorID>;
	PendingDestroyedActors pendingDestroyedActors;
	size_t numPendingDestroyedActors;


public:

	using ActorHandleTable = GameEngine::Util::HandleTable<Actor, ActorID>;
	ActorContainer* actorContainer;
	ActorHandleTable actorHandleTable;

	ActorManager(ComponentManager* componentManagerInstance);
	~ActorManager();

private:
	inline ActorContainer* GetActorContainer() { return this->actorContainer; }

public:


	ActorID AqcuireActorID(Actor* actor);
	void ReleaseActorID(ActorID id);


	inline Actor* GetActor(ActorID entityId)
	{
		return this->actorHandleTable[entityId];
	}

	inline ActorID GetActorID(ActorID::value_type index) const
	{
		return this->actorHandleTable[index];
	}

	template<class... ARGS>
	ActorID CreateActor(ARGS&&... args)
	{
		// aqcuire memory for new entity object of type T
		void* pObjectMemory = GetActorContainer()->CreateObject();
		ActorID actorid = this->AqcuireActorID((Actor*)pObjectMemory);
		Actor* actor = new (pObjectMemory)Actor(std::forward<ARGS>(args)...,actorid);
		actor->transformation = Transform();
	

//		actor->actorID = actorid;
		((Actor*)pObjectMemory)->componentManagerInstance = this->componentManagerInstance;

		// create entity inplace
		

		return actorid;
	}
	void DestroyActor(ActorID actorid)
	{
		Actor* actor = this->actorHandleTable[actorid];

		if (this->numPendingDestroyedActors < this->pendingDestroyedActors.size())
		{
			this->pendingDestroyedActors[this->numPendingDestroyedActors++] = actorid;
		}
		else
		{
			this->pendingDestroyedActors.push_back(actorid);
			this->numPendingDestroyedActors++;
		}
	}

	void RemoveDestroyedActors();

	



};

