class FM_AI_MissionBase
{
	ref array<Object> missionObjects = new ref array<Object>();
	ref array<FalconAI> missionAI = new ref array<FalconAI>();
	
	ref array<string> missionObjectsNames = new ref array<string>();
	
	ref array<string> missionRewardItems = new ref array<string>();
	
	string containerName;
	
	string missionName;
	int missionId;
	vector missionCenter;
	int missionRadius;
	int missionLifespan;
	int missionLVL;
	string missionType;
	
	bool rewardSpawned = false;
	
	
	void init()
	{
		
	}
	
	void update()
	{
		missionLifespan--;
		
		if (!rewardSpawned)
		{
			checkReward();
		}
	}
	
	MissionPlace getMissionPlace()
	{
		string pos = missionCenter[0].ToString() + " " + missionCenter[1].ToString() + " " + missionCenter[2].ToString();
		
		MissionPlace place = new MissionPlace(missionName, missionLVL, pos, missionType);
		
		return place;
	}
	
	private void checkReward()
	{
		bool done = true;
		
		for (int i = 0; i < missionAI.Count(); i++)
		{
			if (missionAI[i].IsAlive())
			{
				done = false;
				break;
			}	
		}
		
		if (done)
		{
			spawnReward();
			rewardSpawned = true;
			
			initSmokeOnPos(missionCenter);
			
			missionLifespan = FalconMissionsConsts.MISSION_LIFESPAN_AFTER_COMPLETED;
		}
	}
	
	private void spawnReward()
	{
		Container_Base container = Container_Base.Cast(GetGame().CreateObject(containerName, missionCenter, false, false));
		container.PlaceOnSurface();
		
		missionObjects.Insert(Container_Base.Cast(container));
		
		for (int i = 0; i < missionRewardItems.Count(); i++)
		{
			container.GetInventory().CreateInInventory(missionRewardItems[i]);
		}
	}
	
	private Object getObjectByName(string itemName)
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
			deleteMissionAI();
			
			isAlive = false;
		}
		
		return isAlive;
	}
	
	void clearMission()
	{
		deleteMissionObjects();
		deleteMissionAI();
	}
	
	private void deleteMissionObjects()
	{
		for (int i = 0; i < missionObjects.Count(); i++)
		{
			GetGame().ObjectDelete(missionObjects[i]);
		}
	}
	
	private void deleteMissionAI()
	{
		FalconAI fAI;
		
		for (int i = 0; i < missionAI.Count(); i++)
		{
			fAI = FalconAI.Cast(missionAI[i]);
			
			fAI.SetHealth(0);
			fAI.Delete();
		}
	}
	
	void spawnRandomizedAI(array<string> aiNames, int count, float radius)
	{
		Object obj;
		vector objPos;
		FalconAI ai;

		for (int i = 0; i < count; i++)
		{
			objPos = generateRandomPosition(radius);
			
			obj = GetGame().CreateObject(aiNames.GetRandomElement(), objPos, false, true);
			obj.PlaceOnSurface();
			
			ai = FalconAI.Cast(obj);
			
			ai.setupAILoadout(getLoadout());
			ai.setMissionParams(missionCenter, missionRadius, missionLVL, missionType);
			ai.runInit();
			
			missionAI.Insert(ai);
		}
	}
	
	private AILoadout getLoadout()
	{
		AILoadout loadout = new AILoadout();
		AILoadoutPack loadoutPack = new AILoadoutPack();
		
		loadoutPack = MissionsUtils.loadAIMissionsLoadoutsConfig();
		
		if (missionLVL == 1)
		{
			loadout = loadoutPack.civilian.GetRandomElement();
		}
		
		else if (missionLVL == 2)
		{
			loadout = loadoutPack.medium.GetRandomElement();
		}
		
		else if (missionLVL == 3)
		{
			loadout = loadoutPack.military.GetRandomElement();
		}
		
		else 
		{
			loadout = loadoutPack.civilian.GetRandomElement();
		}
		
		return loadout;
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
	
	void addItemsToReward(string itemName, int itemsCount)
	{
		for (int i = 0; i < itemsCount; i++)
		{
			missionRewardItems.Insert(itemName);
		}
	}
	
	private void initSmokeOnPos(vector pos)
	{
		MissionSmoke grenade = MissionSmoke.Cast(GetGame().CreateObject("MissionSmoke", pos, false, false, true));
		
		grenade.PlaceOnSurface();
		
		grenade.Unpin();
		
		missionObjects.Insert(grenade);
	}
}
