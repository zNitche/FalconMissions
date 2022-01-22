class MissionFlare extends Roadflare
{
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		SetHealth(0);
		GetCompEM().SwitchOff();
		GetGame().ObjectDelete(this);
		
		return true;
	}
}