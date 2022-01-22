class PlaneCrashMission extends FM_MissionBase
{
	ref array<string> zombiesTypes = new ref array<string>();
	ref array<string> wrecksTypes = new ref array<string>();	
	
	void PlaneCrashMission(int missionId, vector missionCenter, int missionRadius)
	{
		this.missionId = missionId;
		this.missionCenter = missionCenter;
		this.lootItemNames = lootItemNames;
		
		this.missionCenter = generateRandomPosition(missionRadius);
		
		this.missionRadius = 20;
		
		lootItemContainerName = "PlaneCrashCase";
		missionName = "Plane Crash";
		missionLifespan = 3600;
		maxMissionItems = 5;
		
		wrecksTypes.Insert("C130Crash_Mission");
		
		zombiesTypes.Insert("ZmbM_SoldierNormal");
	}
	
	override void init()
	{
		spawnMission();
		makeExplosion();
		spawnMissionLoot();
		fallTrees();
		
		initFlaresInZone(5);
		spawnRandomizedMissionObjects(zombiesTypes, 10, 15);
		spawnRandomizedMissionObjects(wrecksTypes, 1, 20);
	}
	
	private void fallTrees()
	{
		array<Object> objects = new array<Object>();
		
		GetGame().GetObjectsAtPosition(missionCenter, 50, objects, null);
		
		for (int i = 0; i < objects.Count(); i++)
		{
			if (objects[i].IsTree())
			{
				objects[i].SetHealth(0);
			}
		}
	}
}
