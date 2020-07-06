/**
 * ExpansionRaidValues.c
 *
 * DayZ Expansion Mod
 * www.dayzexpansion.com
 * © 2020 DayZ Expansion Mod Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

class ExpansionRaidValues
{
	string Projectile;
	float Damage;
	ref TStringArray DamagableBaseBuilding;

	void ExpansionRaidValues( string projectile, float damage, TStringArray damagablebasebuilding )
	{
		Projectile = projectile;
		Damage = damage;
		DamagableBaseBuilding = damagablebasebuilding;
	}
/*
	string GetProjectile()
	{
		return m_Projectile;
	}

	float GetDamage()
	{
		return m_Damage;
	}

	TStringArray GetDamagableBaseBuilding()
	{
		return m_DamagableBaseBuilding;
	}
*/
}