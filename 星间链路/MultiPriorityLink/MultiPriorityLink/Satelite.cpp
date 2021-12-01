#include "Satelite.h"

Satelite::Satelite()
{
	name = "";
	JNX = false;
	link = false;
	send = false;
	JL = false;
	Normal = true;
	visit = false;
}

Satelite::~Satelite()
{
}

void Satelite::SetSateliteName(string _name)
{
	name = _name;
}

bool Satelite::GetSateliteJNX()
{
	return JNX;
}

void Satelite::SetSateliteJN_JW(bool flag)
{
	JNX = flag;
}

void Satelite::SetSateliteSend(bool flag)
{
	send = flag;
}

bool Satelite::GetSateliteSend()
{
	return send;
}

bool Satelite::GetSateliteJL()
{
	return JL;
}

void Satelite::SetSateliteJL(bool flag)
{
	JL = flag;
}

bool Satelite::GetSatNormal()
{
	return Normal;
}

void Satelite::SetSatNomral(bool flag)
{
	Normal = flag;
}

bool Satelite::GetSatVisit()
{
	return visit;
}

void Satelite::SetSatVisit(bool flag)
{
	visit = flag;
}
