class MissionCaseBase extends Container_Base
{
	override void EEInit()
	{
		super.EEInit();
		
		SetAllowDamage(false);
	}
	
	override bool CanPutInCargo(EntityAI parent)
	{
		return false;
	}
	
	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		Delete();
		
		return true;
	}
}