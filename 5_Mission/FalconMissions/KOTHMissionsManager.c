class KOTHMissionsManager
{
	ref MissionsHelpers missionsHelpers = new MissionsHelpers();
	
	ref KOTHMissionsConfig config;
	
	private bool spawnMissions;
	
	ref array<ref KOTHMission> kothBaseMissions = new array<ref KOTHMission>();
	private int maxKothBaseMissions;
	private ref array<string> kothBaseMissionsCords = new array<string>();
	private float kothBaseMissionRadius;
	private ref Timer kothBaseMissionsSpawnerTimer = new Timer();
	private int kothBaseMissionsMinSpawnTime;
	private int kothBaseMissionsMaxSpawnTime;
	
	
	void setup()
	{
		spawnMissions = config.spawnMissions;	
		maxKothBaseMissions = config.maxKothBaseMissions;
		kothBaseMissionsCords = config.kothBaseMissionsCords;
		kothBaseMissionRadius = config.kothBaseMissionRadius;
		kothBaseMissionsMinSpawnTime = config.kothBaseMissionsMinSpawnTime;
		kothBaseMissionsMaxSpawnTime = config.kothBaseMissionsMaxSpawnTime;
	}
	
	void loadConfig()
	{
		config = new KOTHMissionsConfig();
		config = MissionsUtils.loadKOTHMissionsConfig();
	}
	
	void checkMissionsCount()
	{		
		if (spawnMissions)
		{
			spawnKothBaseMission();
		}
	}
	
	void spawnTimeout()
	{
		kothBaseMissionsSpawnerTimer.Run(Math.RandomInt(kothBaseMissionsMinSpawnTime, kothBaseMissionsMaxSpawnTime), null, "");
	}
	
	private void spawnKothBaseMission()
	{
		if (!kothBaseMissionsSpawnerTimer.IsRunning())
		{
			if (kothBaseMissions.Count() < maxKothBaseMissions)
			{
				array<int> runningMissionsInds = new array<int>();
				
				for (int i = 0; i < kothBaseMissions.Count(); i++)
				{
					runningMissionsInds.Insert(kothBaseMissions[i].missionId);
				}
				
				int randIndex = MissionsUtils.getEmptyMissionCordsIndex(kothBaseMissionsCords, runningMissionsInds);
				
				vector pos = kothBaseMissionsCords.Get(randIndex).ToVector();
				
				KOTHMission mission = new KOTHMission(randIndex, pos, kothBaseMissionRadius);
				
				mission.init();
				
				kothBaseMissions.Insert(mission);
				
				kothBaseMissionsSpawnerTimer.Run(Math.RandomInt(kothBaseMissionsMinSpawnTime, kothBaseMissionsMaxSpawnTime), null, "");
				
				missionsHelpers.messagePlayers(FalconMissionsConsts.KOTH_SPAWN_MISSION_MESSAGE + " " + pos[0] + " " + pos[2]);
			}
		}
	}
	
	void updateMissions()
	{
		for (int i = 0; i < kothBaseMissions.Count(); i++)
		{
			kothBaseMissions[i].update();
			
			if (!kothBaseMissions[i].checkLifespan())
			{
				kothBaseMissions.Remove(i);
			}
			
			else
			{
				if (kothBaseMissions[i].currentCapture && kothBaseMissions[i].missionCenter)
				{
					messageProgress(kothBaseMissions[i].currentCapture, kothBaseMissions[i].missionCenter);
				}
			}
		}
	}
	
	void messageProgress(int progress, vector missionCenter)
	{
		int perc = progress * 100 / FalconMissionsConsts.KOTH_MAX_CAPTURE;
		
		if (perc == 50 || perc == 10 || perc == 90 || perc == 100)
		{
			string message = FalconMissionsConsts.KOTH_SPAWN_MISSION_CURRENT_CAPTURE_MESSAGE_START + missionCenter[0] + " " + missionCenter[2] + FalconMissionsConsts.KOTH_SPAWN_MISSION_CURRENT_CAPTURE_MESSAGE_END + perc + " %";
			
			missionsHelpers.messagePlayers(message);
		}
	}
	
	array<ref KOTHPlace> getMissionsPlaces()
	{
		array<ref KOTHPlace> missionsDetails = new array<ref KOTHPlace>();
		
		for (int i = 0; i < kothBaseMissions.Count(); i++)
		{
			missionsDetails.Insert(kothBaseMissions[i].getMissionPlace());
		}
		
		return missionsDetails;
	}
	
	//Debug
	void getMissionsDetails()
	{
		for (int i = 0; i < kothBaseMissions.Count(); i++)
		{
			Print("KOTH " + kothBaseMissions[i].missionCenter.ToString() + "ID: " + kothBaseMissions[i].missionId);
		}
	}
	
	void clearMissionsDebug()
	{
		for (int i = 0; i < kothBaseMissions.Count(); i++)
		{
			kothBaseMissions[i].flag.Delete();
		}
		
		kothBaseMissions.Clear();
	}
	
	void spawnBaseKOTHMissionDebug()
	{
		vector pos = kothBaseMissionsCords.GetRandomElement().ToVector();
		KOTHMission mission = new KOTHMission(-1, pos, kothBaseMissionRadius);
		
		mission.init();
		
		kothBaseMissions.Insert(mission);
	}
}
