class RogueFarmersMission extends FM_AI_MissionBase
{
	ref array<string> botsTypes = new ref array<string>();	
	

	void RogueFarmersMission(int missionId, vector missionCenter, int missionRadius)
	{
		this.missionId = missionId;
		this.missionCenter = missionCenter;
		
		this.missionCenter = generateRandomPosition(missionRadius);
		
		this.missionRadius = 30;
		
		missionLVL = 1;
		containerName = "AIMissionCase";
		
		missionName = "Rogue Farmers";
		missionType = FalconMissionsConsts.MISSION_TYPE_BANDITS;
		missionLifespan = 3600;
		
		botsTypes.Insert("FalconAITaiki");
		
		addItemsToReward("Apple", 5);
		addItemsToReward("Plum", 2);
		addItemsToReward("Winchester70", 3);
	}
	
	override void init()
	{
		spawnRandomizedAI(botsTypes, 5, 25);
	}
}