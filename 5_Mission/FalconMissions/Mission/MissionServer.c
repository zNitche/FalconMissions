modded class MissionServer
{
	private int missionsSpawnTick = 1;
	private int missionsCT;
	private int nTimeMissions = 0;
	
	private ref MissionsHelpers missionsHelpers;
	
	private ref MissionsManager missionsManager;
	private ref AI_MissionsManager ai_missionsManager;
	private ref KOTHMissionsManager kothMissionsManager;
	
	
	void MissionServer()
	{
		missionsHelpers = new MissionsHelpers();
		missionsManager = new MissionsManager();
		ai_missionsManager = new AI_MissionsManager();
		kothMissionsManager = new KOTHMissionsManager();
		
		GetRPCManager().AddRPC("FalconMissions", "getMissionsDetailsS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC("FalconMissions", "getKOTHDetailsS", this, SingeplayerExecutionType.Server );
	}
	
	override void OnInit()
	{
		super.OnInit();
		
		// MissionsUtils.clearMissionsItems();
	}
	
	private void getMissionsDetailsS(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        Param1<string> data;
        if (!ctx.Read(data)) return;
        
        if (type == CallType.Server) 
		{
			array<ref MissionPlace> missionsDetails = new array<ref MissionPlace>();
			
			missionsDetails = getAIMissionManager().getMissionsDetails();
			
			GetRPCManager().SendRPC("FalconMissions", "getMissionsDetailsC", new Param1<array<ref MissionPlace>>(missionsDetails), true, sender);
        }
    }
	
	private void getKOTHDetailsS(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        Param1<string> data;
        if (!ctx.Read(data)) return;
        
        if (type == CallType.Server)
		{
			array<ref KOTHPlace> kothDetails = new array<ref KOTHPlace>();
			
			kothDetails = getKOTHMissionsManager().getMissionsPlaces();
			
			GetRPCManager().SendRPC("FalconMissions", "getKOTHDetailsC", new Param1<array<ref KOTHPlace>>(kothDetails), true, sender);
        }
    }
	
	override void OnMissionLoaded()
	{
		// loadMissionsConfig();
		// loadAIMissionsConfig();
	}
	
	override void TickScheduler( float timeslice )
	{	
		super.TickScheduler( timeslice );
		
		missionsCT = GetGame().GetTime() * 0.001;
		
		if (missionsCT >= nTimeMissions + missionsSpawnTick)
		{
			// Loading config from OnMissionLoaded() sometimes fails, dunno why
			loadMissionsConfig();
			loadAIMissionsConfig();
			loadKOTHMissionsConfig();
			//
			
			missionsManager.checkMissionsCount();
			missionsManager.updateMissions();
			
			// Debug
			// missionsManager.getMissionsDetails();
			
			ai_missionsManager.checkMissionsCount();
			ai_missionsManager.updateMissions();
			
			kothMissionsManager.checkMissionsCount();
			kothMissionsManager.updateMissions();
			
			// kothMissionsManager.getMissionsDetails();
		
			nTimeMissions = missionsCT;
		}
	}
	
	MissionsManager getMissionManager()
	{
		return missionsManager;
	}
	
	AI_MissionsManager getAIMissionManager()
	{
		return ai_missionsManager;
	}
	
	KOTHMissionsManager getKOTHMissionsManager()
	{
		return kothMissionsManager;
	}
	
	private void loadMissionsConfig()
	{
		if (!missionsManager.config)
		{
			missionsManager.loadConfig();
			missionsManager.setup();
			missionsManager.spawnTimeout();
		}
	}
	
	private void loadAIMissionsConfig()
	{
		if (!ai_missionsManager.config)
		{
			ai_missionsManager.loadConfig();
			ai_missionsManager.setup();
			ai_missionsManager.spawnTimeout();
		}
	}
	
	private void loadKOTHMissionsConfig()
	{
		if (!kothMissionsManager.config)
		{
			kothMissionsManager.loadConfig();
			kothMissionsManager.setup();
			kothMissionsManager.spawnTimeout();
		}
	}
}