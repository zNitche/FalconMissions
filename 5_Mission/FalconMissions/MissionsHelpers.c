class MissionsHelpers
{	
	void MissionsHelpers()
	{
		GetRPCManager().AddRPC( "FalconMissions", "messagePlayersC", this, SingeplayerExecutionType.Server );
	}
	
	private void messagePlayersC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
        if ( type == CallType.Client ) 
		{
			GetGame().Chat("[FalconMissions] " + data.param1, "colorFriendly");
        }
    }
	
	void messagePlayer(PlayerIdentity playerIdentity, string message) 
	{
		GetRPCManager().SendRPC( "FalconMissions", "messagePlayersC", new Param1<string>(message), true, playerIdentity);
	}
	
	void messagePlayers(string message)
	{
		array<Man> players = new array<Man>();
		
		GetGame().GetPlayers(players);
		
		for (int i = 0; i < players.Count(); i++)
		{
			if (canBeMessaged(players[i]))
			{
				messagePlayer(players[i].GetIdentity(), message);
			}
		}
	}
	
	private bool canBeMessaged(Man player)
	{
		bool cond = false;
		array<ItemBase> items = new array<ItemBase>();
		TransmitterBase radio;
		
		
		items = AIUtils.getItemsFromInventory(player, "PersonalRadio");
		
		for (int i = 0; i < items.Count(); i++)
		{
			radio = TransmitterBase.Cast(items[i]);
			
			if (radio.IsOn())
			{
				cond = true;
				break;
			}
		}
		
		return cond;
	}
}