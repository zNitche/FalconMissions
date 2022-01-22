modded class MissionGameplay
{
	ref array<ref MissionPlace> missionsPlaces = new array<ref MissionPlace>();
	ref array<ref KOTHPlace> kothPlaces = new array<ref KOTHPlace>();
		
	ref MissionsHelpers missionsHelpers;
	
	
	void MissionGameplay()
	{
		missionsHelpers = new MissionsHelpers();
		
		GetRPCManager().AddRPC("FalconMissions", "updateAIWeapon", this, SingeplayerExecutionType.Server);
		GetRPCManager().AddRPC("FalconMissions", "getMissionsDetailsC", this, SingeplayerExecutionType.Server);
		GetRPCManager().AddRPC("FalconMissions", "getKOTHDetailsC", this, SingeplayerExecutionType.Server);
	}
	
	private void getMissionsDetailsC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) 
	{
		Param1<array<ref MissionPlace>> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				missionsPlaces = data.param1;
			}
		}
	}
	
	void updateMissionsDetails()
	{
		GetRPCManager().SendRPC("FalconMissions", "getMissionsDetailsS", new Param1<string>(""), true);
	}
	
	private void getKOTHDetailsC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) 
	{
		Param1<array<ref KOTHPlace>> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				kothPlaces = data.param1;
			}
		}
	}
	
	void updateKOTHDetails()
	{
		GetRPCManager().SendRPC("FalconMissions", "getKOTHDetailsS", new Param1<string>(""), true);
	}
	
	private void updateAIWeapon(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) 
	{
		Param1<AISyncPackage> data;
		
        if (!ctx.Read(data)) return;
		
		if (type == CallType.Client) 
		{
			if (data.param1)
			{
				AIHelpers.syncAIInventoryWithPlayer(data.param1);
			}
		}
	}
}