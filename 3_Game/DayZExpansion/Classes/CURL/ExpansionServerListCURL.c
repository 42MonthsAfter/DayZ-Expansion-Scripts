/**
 * ExpansionServerListCURL.c
 *
 * DayZ Expansion Mod
 * www.dayzexpansion.com
 * © 2020 DayZ Expansion Mod Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

class ExpansionServerCURL
{
	string Adress;
	int Port;
	
	// ------------------------------------------------------------
	// ExpansionServerCURL Constructor
	// ------------------------------------------------------------
	void ExpansionServerCURL( string adr, int prt )
	{
		Adress = adr;
		Port = prt;
	}
}

class ExpansionServerListCURL
{
	string serverip;
	int serverport;
}