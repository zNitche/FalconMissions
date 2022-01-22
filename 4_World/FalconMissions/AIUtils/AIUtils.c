class AIUtils
{
	static void spawnWeapon(FalconAI fAI, string weaponName, string magName)
	{
		EntityAI weapon;
		
		if (weaponName == "M4A1")
		{
			weapon = fAI.GetHumanInventory().CreateInHands("M4A1");
					
			weapon.GetInventory().CreateAttachment("M4_OEBttstck");
			weapon.GetInventory().CreateAttachment("M4_CarryHandleOptic");
			weapon.GetInventory().CreateAttachment("M4_PlasticHndgrd");
			
			fAI.GetInventory().CreateInInventory(magName);
		}
		
		else if (weaponName == "MakarovIJ70")
		{
			weapon = fAI.GetHumanInventory().CreateInHands("MakarovIJ70");
			
			fAI.GetInventory().CreateInInventory(magName);
		}
	}
	
	static void initAILoadout(FalconAI fAI, AILoadout loadout)
	{
		fAI.GetInventory().CreateInInventory(loadout.head);
		fAI.GetInventory().CreateInInventory(loadout.body);
		fAI.GetInventory().CreateInInventory(loadout.pants);
		fAI.GetInventory().CreateInInventory(loadout.boots);
		
		for (int i = 0; i < loadout.extraItems.Count(); i++)
		{
			fAI.GetInventory().CreateInInventory(loadout.extraItems[i]);
		}
		
		spawnWeapon(fAI, loadout.weaponName, loadout.magName);
	}
	
	static void clearEmptyMags(FalconAI fAI, string magName)
	{
		array<ItemBase> mags = new array<ItemBase>();
		
		mags = getItemsFromInventory(Man.Cast(fAI), magName);
		
		for (int i = 0; i < mags.Count(); i++)
		{
			GetGame().ObjectDelete(mags[i]);
		}
	}
	
	static array<ItemBase> getItemsFromInventory(Man player, string itemName)
	{
		ItemBase bodyPart;
		array<ItemBase> items = new array<ItemBase>();
		ItemBase item;
		array<string> bodyParts = new array<string>();
		
		bodyParts = getBodyParts();

		ItemBase itemInHands = PlayerBase.Cast(player).GetItemInHands();
		
		if (itemInHands)
		{
			if (itemInHands.ClassName() == itemName)
			{
				items.Insert(itemInHands);
			}
		}
		
		for (int i = 0; i < bodyParts.Count(); i++)
		{
			bodyPart =  ItemBase.Cast(player.GetInventory().FindAttachmentByName(bodyParts[i]));
		
			if (bodyPart)
			{
				for (int j = 0; j < bodyPart.GetInventory().GetCargo().GetItemCount(); j++)
				{
					item = ItemBase.Cast(bodyPart.GetInventory().GetCargo().GetItem(j));
					
					if (item.ClassName() == itemName)
					{
						items.Insert(item);
					}
				}
			}
		}
		
		return items;
	}
	
	private static array<string> getBodyParts()
	{
		array<string> bodyParts = new array<string>();
		
		bodyParts.Insert("Body");
		bodyParts.Insert("Back");
		bodyParts.Insert("Vest");
		bodyParts.Insert("Legs");
		
		return bodyParts;
	}
	
	static int getMinIndex(array<float> input)
	{
		int minIndex = 0;
		float min = input[minIndex];
		
		for (int i = 0; i < input.Count(); i++)
		{
			if (input[i] < min)
			{
				min = input[i];
				minIndex = i;
			}
		}
		
		return minIndex;
	}
	
	static bool calculateHit(float accuracy, float distanceToTarget)
	{
		bool cond = false;
		int rand = Math.RandomInt(0, 100) + distanceToTarget / 100;
		
		if (rand <= accuracy)
		{
			cond = true;
		}
		
		return cond;
	}
}
