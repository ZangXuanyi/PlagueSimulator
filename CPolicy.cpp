#pragma once
#include "PlagueSimulatorLib.hpp"

namespace Ethene
{
	void CPolicy::Execute(CCountry &country) const
	{
		country.changeToLocalCorpseTransmission += changeToLocalCorpseTransmission;
		country.changeToLocalInfectivity += changeToLocalInfectivity;
		country.changeToLocalLethality += changeToLocalLethality;
		country.changeToLocalOrder += changeToLocalOrder;
		country.changeToLocalSeverity += changeToLocalSeverity;
		country.changeToResearchInvestment += changeToMedicalInput;
        switch(changeToBorder)
        {
        case 0:break;
        case 1:country.isBorderOpen = false;break;
        case -1:country.isBorderOpen = true; break;
        }

        // std::cout<<name<<" executed in country: "<<country.name<<std::endl;
	}
	bool CPolicy::CanExecute(CWorld &world, CCountry &country) const
	{
        bool flag1 = cond_localAttention <= country.realAreaAttention && cond_localAttention!=0;
        bool flag2 = cond_localDeadRatio <= country.deadRatio&&cond_localDeadRatio!=0;
        bool flag3 = cond_localInfectedRatio <= country.infectedRatio&&cond_localInfectedRatio!=0;
        bool flag4 = cond_worldAttention <= world.worldAttention&&cond_worldAttention!=0;
        bool flag5 = cond_worldDeadRatio <= world.deadRatio&&cond_worldDeadRatio!=0;
        bool flag6 = cond_worldInfectedRatio <= world.infectedRatio&&cond_worldInfectedRatio!=0;
        if (flag1 || flag2 || flag3 || flag4 || flag5 || flag6)
			return true;
		else
			return false;
	}
}
