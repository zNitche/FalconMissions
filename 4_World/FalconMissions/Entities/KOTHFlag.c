class KOTHFlag extends BaseBuildingBase
{
	private string ownerID;
	
	
	override void EEInit()
	{
		super.EEInit();
		
		SetAllowDamage(false);
	}
	
	void setOwnerID(string newOnwerID)
	{
		ownerID = newOnwerID;
	}
	
	string getOwnerID()
	{
		return ownerID;
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		Delete();
		
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionCaptureFlag);
	}
}