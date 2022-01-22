class AISyncPackage
{
	int eventID;
	int animID;
	DayZPlayer player;
	Magazine mag;
	
	
	void AISyncPackage(int eventID, int animID, DayZPlayer player, Magazine mag)
	{
		this.eventID = eventID;
		this.animID = animID;
		this.player = player;
		this.mag = mag;
	}
}