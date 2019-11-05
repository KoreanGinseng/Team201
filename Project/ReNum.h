#pragma once
class ReNum
{
private:
	int		Zanki;

	ReNum::ReNum(){}
public:
	static ReNum&	GetInstance()
	{
		static	ReNum obj;
		return obj;
	}
	
	int GetReNumber()
	{
		return Zanki;
	}
	
	void addReNumber()
	{
		Zanki++;
	}
	void SubReNumber()
	{
		if(Zanki>=0)
		Zanki--;
	}

	void SetReNum()
	{
		Zanki = 3;
	}

};