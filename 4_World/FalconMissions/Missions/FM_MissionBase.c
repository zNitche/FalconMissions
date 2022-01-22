class FM_MissionBase
{
	ref array<Object> missionObjects = new ref array<Object>();
	ref array<string> lootItemNames = new ref array<string>();
	ref array<string> missionObjectsNames = new ref array<string>();
	
	string lootItemContainerName;
	string missionName;
	int missionId;
	vector missionCenter;
	int missionRadius;
	int missionLifespan;
	int maxMissionItems;
	
	
	void init()
	{
		
	}
	
	int getMaxMissionItems()
	{
		return maxMissionItems;
	}
	
	string getMissionName()
	{
		return missionName;
	}
	
	int getMissionId()
	{
		return missionId;
	}
	
	vector getMissionCenter()
	{
		return missionCenter;
	}
	
	int getMissionRadius()
	{
		return missionRadius;
	}
	
	void setLootItemNames(array<string> items)
	{
		lootItemNames = items;
	}
	
	void update()
	{
		missionLifespan--;
	}
	
	void spawnMission()
	{
		spawnObjectInCenter(lootItemContainerName, missionCenter);
		spawnObjectsInRadius(missionObjectsNames);
	}
	
	void spawnMissionLoot()
	{
		Container_Base container = Container_Base.Cast(getObjectByName(lootItemContainerName));
		
		for (int i = 0; i < lootItemNames.Count(); i++)
		{
			container.GetInventory().CreateInInventory(lootItemNames[i]);	
		}
	}
	
	void spawnMissionLootInRandomContainer(string containerName, int itemsCount)
	{
		Object obj = GetGame().CreateObject(containerName, generateRandomPosition(missionRadius), false, false, true);
		
		missionObjects.Insert(obj);
		
		Container_Base container = Container_Base.Cast(obj);
		
		for (int i = 0; i < itemsCount; i++)
		{
			container.GetInventory().CreateInInventory(lootItemNames[i]);	
		}
	}

	void spawnSmokeOnObject(Object obj)
	{
		Particle m_ParticleEfx = Particle.PlayOnObject(ParticleList.SMOKING_HELI_WRECK, obj, Vector(1, 1, 1));
	}
	
	void spawnRandomizedMissionObjects(array<string> objectsNames, int count, int radius)
	{
		Object obj;
		vector objPos;
		MissionWreckBase wreck;

		for (int i = 0; i < count; i++)
		{
			objPos = generateRandomPosition(radius);
			
			obj = GetGame().CreateObject(objectsNames.GetRandomElement(), objPos, false, true);
			
			if (obj.IsInherited(MissionWreckBase))
			{
				wreck = MissionWreckBase.Cast(obj);
				
				objPos[1] = objPos[1] + wreck.heightOffset;
				
				obj.SetPosition(objPos);
			}
			
			obj.SetDirection(Vector(Math.RandomFloat(-1, 1), 0, Math.RandomFloat(-1, 1)));
			
			obj.PlaceOnSurface();
			
			missionObjects.Insert(obj);
		}
	}
	
	Object getObjectByName(string itemName)
	{
		Object obj;
		
		for (int i = 0; i < missionObjects.Count(); i++)
		{
			if (missionObjects[i].GetType() == itemName)
			{
				obj = missionObjects[i];
			}
		}
		
		return obj;
	}
	
	bool checkLifespan()
	{
		bool isAlive = true;
		
		if (missionLifespan <= 0)
		{
			deleteMissionObjects();
			
			isAlive = false;
		}
		
		return isAlive;
	}
	
	void deleteMissionObjects()
	{
		for (int i = 0; i < missionObjects.Count(); i++)
		{
			GetGame().ObjectDelete(missionObjects[i]);
		}
	}
	
	void spawnObjectInCenter(string objectName, vector objectPos)
	{
		Object obj = GetGame().CreateObject(objectName, objectPos, false, false, true);
		
		missionObjects.Insert(obj);
	}
	
	void spawnObjectsInRadius(array<string> objectsNames)
	{
		if (objectsNames != null)
		{
			array<vector> positions = new array<vector>();
			positions = generateRandomPositions(objectsNames.Count(), missionRadius);
			
			Object obj;
	
			for (int k = 0; k < positions.Count(); k++)
			{
				obj = GetGame().CreateObject(objectsNames[k], positions[k], false, false, true);
				
				missionObjects.Insert(obj);
			}
		}
	}
	
	array<vector> generateRandomPositions(int count, int radius)
	{
		array<vector> positions = new array<vector>();
			
		for (int i = 0; i < count; i++)
		{
			positions.Insert(generateRandomPosition(radius));
		}
		
		return positions;
	}
	
	void initFlaresInZone(int count)
	{
		MissionFlare flare;
		array<vector> positions = new array<vector>();
		positions = generateRandomPositions(count, missionRadius);
		
		
		for (int i = 0; i < count; i++)
		{
			flare = MissionFlare.Cast(GetGame().CreateObject("MissionFlare", positions[i], false, false, true));
		
		    flare.SetModelState(RoadflareModelStates.UNCAPPED_IGNITED);
			flare.SetBurningStateSynchronized(RoadflareBurningState.MAIN_BURN);
			flare.ShowSelection("Sticks_Flare_Unfolded");
			flare.HideSelection("Sticks_Flare_Folded");
			flare.GetCompEM().SwitchOn();
			
			missionObjects.Insert(flare);
		}
	}
	
	vector generateRandomPosition(int radius)
	{
		float x;
		float y;
		float z;
		
		vector outpos;
		
		x = Math.RandomInt(missionCenter[0] - radius, missionCenter[0] + radius);
		z = Math.RandomInt(missionCenter[2] - radius, missionCenter[2] + radius);
		
		y = GetGame().SurfaceY(x, z);
		
		outpos = Vector(x, y, z);
		
		return outpos;
	}
	
	void makeExplosion()
	{
		for (int i = 0; i < 5; i++)
		{
			Grenade_Base grenade = Grenade_Base.Cast(GetGame().CreateObject("M67Grenade", missionCenter));
			grenade.ActivateImmediate();
			
			missionObjects.Insert(Object.Cast(grenade));
		}
	}
}
