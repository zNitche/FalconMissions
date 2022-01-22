class HiddenTreasureMission extends FM_MissionBase
{
	void HiddenTreasureMission(int missionId, vector missionCenter, int missionRadius)
	{
		this.missionId = missionId;
		this.missionCenter = missionCenter;
		this.missionRadius = missionRadius;
		this.lootItemNames = lootItemNames;
		
		this.missionCenter = generateRandomPosition(missionRadius);
		
		lootItemContainerName = "HiddenWoodenCase";
		missionName = "Hidden Treasure";
		missionLifespan = 1800;
		maxMissionItems = 5;
	}
	
	override void init()
	{
		spawnMission();
		spawnMissionLoot();
	}
}