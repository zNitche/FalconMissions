class MissionsUtils
{
	const static string missionsConfigPath = FalconMissionsConsts.MISSIONS_CONFIG_DATA_PATH;
	const static string aiMissionsConfigPath = FalconMissionsConsts.AI_MISSIONS_CONFIG_DATA_PATH;
	const static string aiLoaudoutsConfigPath = FalconMissionsConsts.AI_LOADOUTS_CONFIG_DATA_PATH;
	const static string kothMissionsConfigPath = FalconMissionsConsts.KOTH_MISSIONS_CONFIG_DATA_PATH;
	
	// Client
	const static string missionsPlacesDumpPath = FalconMissionsConsts.MISSIONS_PLACES_DATA_PATH;
	
	
	static MissionsConfig loadMissionsConfig()
	{		
		if (FileExist(missionsConfigPath))
		{
			MissionsConfig config = new MissionsConfig();
			
			JsonFileLoader<MissionsConfig>.JsonLoadFile(missionsConfigPath, config);
			
			return config;
		}	
		
		return null;
	}
	
	static AI_MissionsConfig loadAIMissionsConfig()
	{
		if (FileExist(aiMissionsConfigPath))
		{
			AI_MissionsConfig config = new AI_MissionsConfig();
			
			JsonFileLoader<AI_MissionsConfig>.JsonLoadFile(aiMissionsConfigPath, config);
			
			return config;
		}	
		
		return null;
	}
	
	static AILoadoutPack loadAIMissionsLoadoutsConfig()
	{
		if (FileExist(aiLoaudoutsConfigPath))
		{
			AILoadoutPack config = new AILoadoutPack();
			
			JsonFileLoader<AILoadoutPack>.JsonLoadFile(aiLoaudoutsConfigPath, config);
			
			return config;
		}	
		
		return null;
	}
	
	static KOTHMissionsConfig loadKOTHMissionsConfig()
	{
		if (FileExist(kothMissionsConfigPath))
		{
			KOTHMissionsConfig config = new KOTHMissionsConfig();
			
			JsonFileLoader<KOTHMissionsConfig>.JsonLoadFile(kothMissionsConfigPath, config);
			
			return config;
		}	
		
		return null;
	}
	
	//Not used anymore
	
	static void dumpMissionsPlaces(array<ref MissionPlace> missionsPlaces)
	{
		JsonFileLoader<array<ref MissionPlace>>.JsonSaveFile(missionsPlacesDumpPath, missionsPlaces);
	}
	
	static array<ref MissionPlace> loadMissionsPlaces()
	{
		if (FileExist(missionsPlacesDumpPath))
		{
			array<ref MissionPlace> missionsPlaces = new array<ref MissionPlace>();
			
			JsonFileLoader<array<ref MissionPlace>>.JsonLoadFile(missionsPlacesDumpPath, missionsPlaces);
			
			return missionsPlaces;
		}	
		
		return null;
	}
	
	//
	
	static int getEmptyMissionCordsIndex(array<string> missionsCords, array<int> runningMissionsIDs)
	{
		int outputInd = -1;
		bool running = true;
		int randInd;
		
		while (running)
		{
			randInd = missionsCords.GetRandomIndex();
			
			if (runningMissionsIDs.Find(randInd) < 0)
			{
				outputInd = randInd;
				running = false;
			}
		}
		
		return outputInd;
	}
	
	static void clearMissionsItems()
	{
		vector center = "8600 465 9225";
		array<Object> allWorldObjects = new array<Object>();
		
		
		GetGame().GetObjectsAtPosition3D(center, 40000, allWorldObjects, null);
		
		for (int i = 0; i < allWorldObjects.Count(); i++)
		{
			if (allWorldObjects[i].GetType() == "MissionFlare")
			{
				GetGame().ObjectDelete(allWorldObjects[i]);
			}
		}
		
		allWorldObjects.Clear();
	}
	
	static array<string> getPlayersIDsInRadius(vector center, float radius)
	{
		array<Object> objectsInRadius = new array<Object>();
		
		array<string> ids = new array<string>();
		PlayerBase player;
		string playerID;
		
		GetGame().GetObjectsAtPosition3D(center, radius, objectsInRadius, null);
		
		for (int i = 0; i < objectsInRadius.Count(); i++)
		{
			if (objectsInRadius[i].IsInherited(PlayerBase))
			{
				player = PlayerBase.Cast(objectsInRadius[i]);
				
				playerID = player.GetIdentity().GetId();
			
				if (playerID)
				{
					ids.Insert(playerID);
				}
			}
		}
		
		return ids;
	}
	
	static bool checkIfIDinIDs(array<string> ids, string id)
	{
		bool cond = false;
		
		for (int i = 0; i < ids.Count(); i++)
		{
			if (id == ids[i])
			{
				cond = true;
				break;
			}
		}
		
		return cond;
	}
}
