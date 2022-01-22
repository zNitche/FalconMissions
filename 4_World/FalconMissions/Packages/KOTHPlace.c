class KOTHPlace
{
	string name;
	int captureProgress;
	string position;
	int missionID;
	
	void KOTHPlace(string name, int captureProgress,  string position, int missionID)
	{
		this.name = name;
		this.captureProgress = captureProgress;
		this.position = position;
		this.missionID = missionID;
	}
}