
#ifndef GLOBALCONSTANTS_H
#define GLOBALCONSTANTS_H

// --------------------------------------------------
// Define some constants that will be used throughout
// --------------------------------------------------

// These are constants for the input and output parameters
enum params {iB,iT,iP,iD,iC,iC0,iO,iU,iH,iS,iA,iG,iQ,iV,iL,iI,iMM,iTcrit,iTtriple,iTreduce,iPtriple,iPcrit,iRhocrit,iRhoreduce,iAccentric,iDpdT,iDrhodT_p,iTmin,iDipole,iPhase,iPHASE_LIQUID,iPHASE_GAS,iPHASE_SUPERCRITICAL,iPHASE_TWOPHASE,iODP,iGWP20,iGWP100,iGWP500, iCritSplineT,iHcrit,iScrit};

// These are constants for the phases of the fluid
enum phases {iLiquid, iSupercritical, iGas, iTwoPhase};

// These are constants for the units
enum unit_constants{UNIT_KPA, UNIT_PA, UNIT_BAR, UNIT_KG_M3, UNIT_KG_L};

// These are constants for the unit systems (currently only SI and KSI are supported)
enum unit_systems{UNIT_SYSTEM_SI, UNIT_SYSTEM_KSI, UNIT_SYSTEM_KSI_MOLAR, UNIT_SYSTEM_SI_MOLAR};

#endif