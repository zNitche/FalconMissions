class ActionCaptureFlag extends ActionInteractBase
{
	void ActionCaptureFlag()
	{
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}
	
	override string GetText()
	{
		return "Capture Flag";
	}
	
	override typename GetInputType()
	{
		return InteractActionInput;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		KOTHFlag flag = KOTHFlag.Cast(target.GetObject());
		
		if (flag)
		{
			return true;
		}
		
		return false;
	}
	
	override void OnExecuteServer(ActionData action_data)
	{
		KOTHFlag flag = KOTHFlag.Cast(action_data.m_Target.GetObject());
		
		if (flag)
		{
			PlayerBase player = action_data.m_Player;
			
			flag.setOwnerID(player.GetIdentity().GetId());
		}
	}
}