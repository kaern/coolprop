#if defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <crtdbg.h>
#endif

#if defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#include "REFPROP.h"
#endif

#include <stdlib.h>
#include "string.h"
#include <stdio.h>

#include "CoolProp.h"


// Some constants for REFPROP... defined by macros for ease of use 
#define refpropcharlength 255
#define filepathlength 255
#define lengthofreference 3
#define errormessagelength 255
#define ncmax 20		// Note: ncmax is the max number of components
#define numparams 72 
#define maxcoefs 50


double SecFluids(char Output, double T, double p,char * Ref)
{
	double Tfreeze,Tmax,rho,cp,k,mu,TC,C_gly;
	// Temperature and Pressure are the inputs
		
	if (!strcmp(Ref,"Water"))
	{
		/*
		Brine() takes inputs of temperature [C]  and secondary fluid concentration in water [mass %]
		Outputs are freezing temperature [C], density [kg/m^3], Specific Heat [J/kg-K], Conductivity [W/m-K], Viscosity [mPa-s]
		*/
		Brine("EG", T - 273.15, 0.0, &Tfreeze, &Tmax, &rho, &cp, &k, &mu);
		switch(Output)
		{
			case 'D':
				return rho;
			case 'C':
				return cp/1000;
			case 'L':
				return k/1000;
			case 'V':
				return mu / 1000.0;
			case 'F':
				return Tfreeze+273.15;
			case 'M':
				return Tmax+273.15;
			default:
				return _HUGE;
		}
	}

	else if (!strcmp(Ref,"HC-10"))
	{
		// Curve fits generated from Microsoft Excel fit of manufacturer data
		// Input temperature is in deg C
		TC=T-273.15;
		switch(Output)
		{
			case 'D':
				return -4.52609118E-01*TC + 1.19919457E+03;
			case 'C':
				return 2.4797494E-03*TC + 3.2708330E+00;
			case 'L':
				return 1.00000E-06*TC + 5.04400E-04;
			case 'V':
				return 2.937072591E-12*TC*TC*TC*TC - 1.713938938E-09*TC*TC*TC + 3.826311605E-07*TC*TC - 4.253611683E-05*TC + 2.509839772E-03;
			case 'F':
				return 263.15;
			case 'M':
				return 390;
			default:
				return _HUGE;
		}
	}


	// Ethylene glycol blends and pure water
	// "EG-10%" is 10% by mass ethylene glycol
	else if (Ref[0]=='E' && Ref[1]=='G')
	{
		switch (Ref[3])
		{
			case '1':
				C_gly=10; break;
			case '2':
				C_gly=20; break;
			case '3':
				C_gly=30; break;
			case '4':
				C_gly=40; break;
			case '5':
				C_gly=50; break;
			default:
				return _HUGE;
		}

		/*
		Brine() takes inputs of temperature [C]  and secondary fluid concentration in water [mass %]
		Outputs are freezing temperature [C], density [kg/m^3], Specific Heat [J/kg-K], Conductivity [W/m-K], Viscosity [mPa-s]
		*/
		Brine("EG", T - 273.15, C_gly, &Tfreeze, &Tmax, &rho, &cp, &k, &mu);
		switch(Output)
		{
			case 'D':
				return rho;
			case 'C':
				return cp/1000;
			case 'L':
				return k/1000;
			case 'V':
				return mu / 1000.0;
			case 'F':
				return Tfreeze+273.15;
			case 'M':
				return Tmax+273.15;
			default:
				return _HUGE;
		}
	}

	// Propylene glycol blends and pure water
	// "PG-10%" is 10% by mass propylene glycol
	else if (Ref[0]=='P' && Ref[1]=='G')
	{
		switch (Ref[3])
		{
			case '1':
				C_gly=10; break;
			case '2':
				C_gly=20; break;
			case '3':
				C_gly=30; break;
			case '4':
				C_gly=40; break;
			case '5':
				C_gly=50; break;
			default:
				return _HUGE;
		}

		/*
		Brine() takes inputs of temperature [C]  and secondary fluid concentration in water [mass %]
		Outputs are freezing temperature [C], density [kg/m^3], Specific Heat [J/kg-K], Conductivity [W/m-K], Viscosity [mPa-s]
		*/
		Brine("PG", T - 273.15, C_gly, &Tfreeze, &Tmax, &rho, &cp, &k, &mu);
		switch(Output)
		{
			case 'D':
				return rho;
			case 'C':
				return cp/1000;
			case 'L':
				return k/1000;
			case 'V':
				return mu / 1000.0;
			case 'F':
				return Tfreeze+273.15;
			case 'M':
				return Tmax+273.15;
			default:
				return _HUGE;
		}
	}

	else if (strncmp(Ref,"Methanol",8)==0)
	{
		switch (Ref[9])
		{
			case '1':
				C_gly=10; break;
			case '2':
				C_gly=20; break;
			case '3':
				C_gly=30; break;
			case '4':
				C_gly=40; break;
			default:
				return _HUGE;
		}

		/*
		Brine() takes inputs of temperature [C]  and secondary fluid concentration in water [mass %]
		Outputs are freezing temperature [C], density [kg/m^3], Specific Heat [J/kg-K], Conductivity [W/m-K], Viscosity [mPa-s]
		*/
		Brine("Methanol", T - 273.15, C_gly, &Tfreeze, &Tmax, &rho, &cp, &k, &mu);
		switch(Output)
		{
			case 'D':
				return rho;
			case 'C':
				return cp/1000;
			case 'L':
				return k/1000;
			case 'V':
				return mu / 1000.0;
			case 'F':
				return Tfreeze+273.15;
			case 'M':
				return Tmax+273.15;
			default:
				return _HUGE;
		}
	}

	else if (strncmp(Ref,"NH3/H2O",7)==0)
	{
		switch (Ref[8])
		{
			case '1':
				C_gly=10; break;
			case '2':
				C_gly=20; break;
			default:
				return _HUGE;
		}

		/*
		Brine() takes inputs of temperature [C]  and secondary fluid concentration in water [mass %]
		Outputs are freezing temperature [C], density [kg/m^3], Specific Heat [J/kg-K], Conductivity [W/m-K], Viscosity [mPa-s]
		*/
		Brine("NH3", T - 273.15, C_gly, &Tfreeze, &Tmax, &rho, &cp, &k, &mu);
		switch(Output)
		{
			case 'D':
				return rho;
			case 'C':
				return cp/1000;
			case 'L':
				return k/1000;
			case 'V':
				return mu / 1000.0;
			case 'F':
				return Tfreeze+273.15;
			case 'M':
				return Tmax+273.15;
			default:
				return _HUGE;
		}
	}
}
#if defined(_WIN32) || defined(__WIN32__) //Check if it is a windows machine, ir not, hide this function
double REFPROP(char Output,char Name1, double Prop1, char Name2, double Prop2, char * Ref)
{

	long i,ierr=0;
	char hf[refpropcharlength*ncmax], hrf[lengthofreference+1],
	herr[errormessagelength+1],hfmix[refpropcharlength+1];
	char LoadedREFPROPRef[255];
	double x[ncmax],xliq[ncmax],xvap[ncmax];
	char RefString[255];
	double T,p,d,dl,dv,q,e,h,s,cv,cp,w,MW,hl,hv,sl,sv,ul,uv,pl,pv,eta,tcx,Q,Tcrit,pcrit,dcrit;

	// First create a pointer to an instance of the library
	// Then have windows load the library.
		HINSTANCE RefpropdllInstance;
		RefpropdllInstance = LoadLibrary("c:/Program Files/REFPROP/refprop.dll");

	// Then get pointers into the dll to the actual functions.
		ABFL1dll = (fp_ABFL1dllTYPE) GetProcAddress(RefpropdllInstance,"ABFL1dll");
		ABFL2dll = (fp_ABFL2dllTYPE) GetProcAddress(RefpropdllInstance,"ABFL2dll");
		ACTVYdll = (fp_ACTVYdllTYPE) GetProcAddress(RefpropdllInstance,"ACTVYdll");
		AGdll = (fp_AGdllTYPE) GetProcAddress(RefpropdllInstance,"AGdll");
		CCRITdll = (fp_CCRITdllTYPE) GetProcAddress(RefpropdllInstance,"CCRITdll");
		CP0dll = (fp_CP0dllTYPE) GetProcAddress(RefpropdllInstance,"CP0dll");
		CRITPdll = (fp_CRITPdllTYPE) GetProcAddress(RefpropdllInstance,"CRITPdll");
		CSATKdll = (fp_CSATKdllTYPE) GetProcAddress(RefpropdllInstance,"CSATKdll");
		CV2PKdll = (fp_CV2PKdllTYPE) GetProcAddress(RefpropdllInstance,"CV2PKdll");
		CVCPKdll = (fp_CVCPKdllTYPE) GetProcAddress(RefpropdllInstance,"CVCPKdll");
		CVCPdll = (fp_CVCPdllTYPE) GetProcAddress(RefpropdllInstance,"CVCPdll"); 
		DBDTdll = (fp_DBDTdllTYPE) GetProcAddress(RefpropdllInstance,"DBDTdll");
		DBFL1dll = (fp_DBFL1dllTYPE) GetProcAddress(RefpropdllInstance,"DBFL1dll");
		DBFL2dll = (fp_DBFL2dllTYPE) GetProcAddress(RefpropdllInstance,"DBFL2dll");
		DDDPdll = (fp_DDDPdllTYPE) GetProcAddress(RefpropdllInstance,"DDDPdll");
		DDDTdll = (fp_DDDTdllTYPE) GetProcAddress(RefpropdllInstance,"DDDTdll");
		DEFLSHdll = (fp_DEFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"DEFLSHdll");
		DHD1dll = (fp_DHD1dllTYPE) GetProcAddress(RefpropdllInstance,"DHD1dll");
		DHFLSHdll = (fp_DHFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"DHFLSHdll");
		DIELECdll = (fp_DIELECdllTYPE) GetProcAddress(RefpropdllInstance,"DIELECdll");
		DOTFILLdll = (fp_DOTFILLdllTYPE) GetProcAddress(RefpropdllInstance,"DOTFILLdll");
		DPDD2dll = (fp_DPDD2dllTYPE) GetProcAddress(RefpropdllInstance,"DPDD2dll");
		DPDDKdll = (fp_DPDDKdllTYPE) GetProcAddress(RefpropdllInstance,"DPDDKdll");
		DPDDdll = (fp_DPDDdllTYPE) GetProcAddress(RefpropdllInstance,"DPDDdll");
		DPDTKdll = (fp_DPDTKdllTYPE) GetProcAddress(RefpropdllInstance,"DPDTKdll");
		DPDTdll = (fp_DPDTdllTYPE) GetProcAddress(RefpropdllInstance,"DPDTdll");
		DPTSATKdll = (fp_DPTSATKdllTYPE) GetProcAddress(RefpropdllInstance,"DPTSATKdll");
		DSFLSHdll = (fp_DSFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"DSFLSHdll");
		ENTHALdll = (fp_ENTHALdllTYPE) GetProcAddress(RefpropdllInstance,"ENTHALdll"); //**
		ENTROdll = (fp_ENTROdllTYPE) GetProcAddress(RefpropdllInstance,"ENTROdll");
		ESFLSHdll = (fp_ESFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"ESFLSHdll");
		FGCTYdll = (fp_FGCTYdllTYPE) GetProcAddress(RefpropdllInstance,"FGCTYdll");
		FPVdll = (fp_FPVdllTYPE) GetProcAddress(RefpropdllInstance,"FPVdll");
		GERG04dll = (fp_GERG04dllTYPE) GetProcAddress(RefpropdllInstance,"GERG04dll");
		GETFIJdll = (fp_GETFIJdllTYPE) GetProcAddress(RefpropdllInstance,"GETFIJdll");
		GETKTVdll = (fp_GETKTVdllTYPE) GetProcAddress(RefpropdllInstance,"GETKTVdll");
		GIBBSdll = (fp_GIBBSdllTYPE) GetProcAddress(RefpropdllInstance,"GIBBSdll");
		HSFLSHdll = (fp_HSFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"HSFLSHdll");
		INFOdll = (fp_INFOdllTYPE) GetProcAddress(RefpropdllInstance,"INFOdll");
		LIMITKdll = (fp_LIMITKdllTYPE) GetProcAddress(RefpropdllInstance,"LIMITKdll");
		LIMITSdll = (fp_LIMITSdllTYPE) GetProcAddress(RefpropdllInstance,"LIMITSdll");
		LIMITXdll = (fp_LIMITXdllTYPE) GetProcAddress(RefpropdllInstance,"LIMITXdll");
		MELTPdll = (fp_MELTPdllTYPE) GetProcAddress(RefpropdllInstance,"MELTPdll");
		MELTTdll = (fp_MELTTdllTYPE) GetProcAddress(RefpropdllInstance,"MELTTdll");
		MLTH2Odll = (fp_MLTH2OdllTYPE) GetProcAddress(RefpropdllInstance,"MLTH2Odll");
		NAMEdll = (fp_NAMEdllTYPE) GetProcAddress(RefpropdllInstance,"NAMEdll");
		PDFL1dll = (fp_PDFL1dllTYPE) GetProcAddress(RefpropdllInstance,"PDFL1dll");
		PDFLSHdll = (fp_PDFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"PDFLSHdll");
		PEFLSHdll = (fp_PEFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"PEFLSHdll");
		PHFL1dll = (fp_PHFL1dllTYPE) GetProcAddress(RefpropdllInstance,"PHFL1dll");
		PHFLSHdll = (fp_PHFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"PHFLSHdll");
		PQFLSHdll = (fp_PQFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"PQFLSHdll");
		PREOSdll = (fp_PREOSdllTYPE) GetProcAddress(RefpropdllInstance,"PREOSdll");
		PRESSdll = (fp_PRESSdllTYPE) GetProcAddress(RefpropdllInstance,"PRESSdll");
		PSFL1dll = (fp_PSFL1dllTYPE) GetProcAddress(RefpropdllInstance,"PSFL1dll");
		PSFLSHdll = (fp_PSFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"PSFLSHdll");
		PUREFLDdll = (fp_PUREFLDdllTYPE) GetProcAddress(RefpropdllInstance,"PUREFLDdll");
		QMASSdll = (fp_QMASSdllTYPE) GetProcAddress(RefpropdllInstance,"QMASSdll");
		QMOLEdll = (fp_QMOLEdllTYPE) GetProcAddress(RefpropdllInstance,"QMOLEdll");
		SATDdll = (fp_SATDdllTYPE) GetProcAddress(RefpropdllInstance,"SATDdll");
		SATEdll = (fp_SATEdllTYPE) GetProcAddress(RefpropdllInstance,"SATEdll");
		SATHdll = (fp_SATHdllTYPE) GetProcAddress(RefpropdllInstance,"SATHdll");
		SATPdll = (fp_SATPdllTYPE) GetProcAddress(RefpropdllInstance,"SATPdll");
		SATSdll = (fp_SATSdllTYPE) GetProcAddress(RefpropdllInstance,"SATSdll");
		SATTdll = (fp_SATTdllTYPE) GetProcAddress(RefpropdllInstance,"SATTdll");
		SETAGAdll = (fp_SETAGAdllTYPE) GetProcAddress(RefpropdllInstance,"SETAGAdll");
		SETKTVdll = (fp_SETKTVdllTYPE) GetProcAddress(RefpropdllInstance,"SETKTVdll");
		SETMIXdll = (fp_SETMIXdllTYPE) GetProcAddress(RefpropdllInstance,"SETMIXdll");
		SETMODdll = (fp_SETMODdllTYPE) GetProcAddress(RefpropdllInstance,"SETMODdll");
		SETREFdll = (fp_SETREFdllTYPE) GetProcAddress(RefpropdllInstance,"SETREFdll");
		SETUPdll = (fp_SETUPdllTYPE) GetProcAddress(RefpropdllInstance,"SETUPdll");
		SPECGRdll = (fp_SPECGRdllTYPE) GetProcAddress(RefpropdllInstance,"SPECGRdll");
		SUBLPdll = (fp_SUBLPdllTYPE) GetProcAddress(RefpropdllInstance,"SUBLPdll");
		SUBLTdll = (fp_SUBLTdllTYPE) GetProcAddress(RefpropdllInstance,"SUBLTdll");
		SURFTdll = (fp_SURFTdllTYPE) GetProcAddress(RefpropdllInstance,"SURFTdll");
		SURTENdll = (fp_SURTENdllTYPE) GetProcAddress(RefpropdllInstance,"SURTENdll");
		TDFLSHdll = (fp_TDFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"TDFLSHdll");
		TEFLSHdll = (fp_TEFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"TEFLSHdll");
		THERM0dll = (fp_THERM0dllTYPE) GetProcAddress(RefpropdllInstance,"THERM0dll");
		THERM2dll = (fp_THERM2dllTYPE) GetProcAddress(RefpropdllInstance,"THERM2dll");
		THERM3dll = (fp_THERM3dllTYPE) GetProcAddress(RefpropdllInstance,"THERM3dll");
		THERMdll = (fp_THERMdllTYPE) GetProcAddress(RefpropdllInstance,"THERMdll");
		THFLSHdll = (fp_THFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"THFLSHdll");
		TPFLSHdll = (fp_TPFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"TPFLSHdll");
		TPRHOdll = (fp_TPRHOdllTYPE) GetProcAddress(RefpropdllInstance,"TPRHOdll");
		TQFLSHdll = (fp_TQFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"TQFLSHdll");
		TRNPRPdll = (fp_TRNPRPdllTYPE) GetProcAddress(RefpropdllInstance,"TRNPRPdll");
		TSFLSHdll = (fp_TSFLSHdllTYPE) GetProcAddress(RefpropdllInstance,"TSFLSHdll");
		VIRBdll = (fp_VIRBdllTYPE) GetProcAddress(RefpropdllInstance,"VIRBdll");
		VIRCdll = (fp_VIRCdllTYPE) GetProcAddress(RefpropdllInstance,"VIRCdll");
		WMOLdll = (fp_WMOLdllTYPE) GetProcAddress(RefpropdllInstance,"WMOLdll");
		XMASSdll = (fp_XMASSdllTYPE) GetProcAddress(RefpropdllInstance,"XMASSdll");
		XMOLEdll = (fp_XMOLEdllTYPE) GetProcAddress(RefpropdllInstance,"XMOLEdll");

		i=1;
		strcpy(RefString,"");
		strcat(RefString,Ref);
		strcat(RefString,".fld");
		strcpy(hf,RefString);

		strcpy(hfmix,"hmx.bnc");
		strcpy(hrf,"DEF");
		strcpy(herr,"Ok");
		x[0]=1.0;     //Air composition

		// If the name of the refrigerant doesn't match 
		// that of the currently loaded refrigerant
		if (strcmp(LoadedREFPROPRef,Ref))
		{
			//...Call SETUP to initialize the program
			SETUPdll(&i, hf, hfmix, hrf, &ierr, herr,
				refpropcharlength*ncmax,refpropcharlength,
				lengthofreference,errormessagelength);
			if (ierr != 0) printf("%s\n",herr);
			//Copy the name of the loaded refrigerant back into the temporary holder
			strcpy(LoadedREFPROPRef,Ref);
		}

		// Get the molar mass of the fluid
		WMOLdll(x,&MW);
		if (Output=='B')
		{
			// Critical temperature
			CRITPdll(x,&Tcrit,&pcrit,&dcrit,&ierr,herr,255);
			return Tcrit;
		}
		else if (Output=='E')
		{
			// Critical pressure
			CRITPdll(x,&Tcrit,&pcrit,&dcrit,&ierr,herr,255);
			return pcrit;
		}
		else if (Name1=='T' && Name2=='P')
		{
			// T in K, P in kPa

			// Use flash routine to find properties
			T=Prop1;
			p=Prop2;  
			TPFLSHdll(&T,&p,x,&d,&dl,&dv,xliq,xvap,&q,&e,&h,&s,&cv,&cp,&w,&ierr,herr,errormessagelength);
			if (Output=='H') return h/MW;
			else if (Output=='D') return d*MW;
			else if (Output=='S') return s/MW;
			else if (Output=='U') return e/MW;
			else if (Output=='C') return cp/MW;
			else if (Output=='O') return cv/MW;
			else if (Output=='V') 
			{
				TRNPRPdll(&T,&d,x,&eta,&tcx,&ierr,herr,errormessagelength);
				return eta/1.0e6; //uPa-s to Pa-s
			} 
			else if (Output=='L')
			{
				TRNPRPdll(&T,&d,x,&eta,&tcx,&ierr,herr,errormessagelength);
				return tcx/1000.0; //W/m-K to kW/m-K
			}
			else
				return _HUGE;
		}
		else if (Name1=='T' && Name2=='Q')
		{
			T=Prop1;
			Q=Prop2;
			// Saturation Density
			SATTdll(&T,x,&i,&p,&dl,&dv,xliq,xvap,&ierr,herr,errormessagelength);

			if (Output=='D') 
			{
				return 1/(Q/dv+(1-Q)/dl)*MW;
			}
			else if (Output=='P') 
			{
				PRESSdll(&T,&dl,x,&pl);
				PRESSdll(&T,&dv,x,&pv);
				return (pv*Q+pl*(1-Q));
			}
			else if (Output=='H') 
			{
				ENTHALdll(&T,&dl,x,&hl);
				ENTHALdll(&T,&dv,x,&hv);
				return (hv*Q+hl*(1-Q))/MW; // J/kg to kJ/kg
			}
			else if (Output=='S') 
			{
				ENTROdll(&T,&dl,x,&sl);
				ENTROdll(&T,&dv,x,&sv);
				return (sv*Q+sl*(1-Q))/MW; // J/kg-K to kJ/kg-K
			}
			else if (Output=='U') 
			{
				ENTHALdll(&T,&dl,x,&hl);
				ENTHALdll(&T,&dv,x,&hv);
				ul=hl-p/dl;
				uv=hv-p/dv;
				return (uv*Q+ul*(1-Q))/MW; // J/kg to kJ/kg
			}
			else if (Output=='C') 
			{
				d=1/(Q/dv+(1-Q)/dl);
				CVCPdll(&T,&d,x,&cv,&cp);
				return cp/MW; // J/kg-K to kJ/kg-K
			}
			else if (Output=='O') 
			{
				d=1/(Q/dv+(1-Q)/dl);
				CVCPdll(&T,&d,x,&cv,&cp);
				return cv/MW; // J/kg-K to kJ/kg-K
			}
			else if (Output=='V') 
			{
				d=1/(Q/dv+(1-Q)/dl);
				TRNPRPdll(&T,&d,x,&eta,&tcx,&ierr,herr,errormessagelength);
				return eta/1.0e6; //uPa-s to Pa-s
			}
			else if (Output=='L') 
			{
				d=1/(Q/dv+(1-Q)/dl);
				TRNPRPdll(&T,&d,x,&eta,&tcx,&ierr,herr,errormessagelength);
				return tcx/1000.0; //W/m-K to kW/m-K
			}
			else
				return _HUGE;
		}
		else
			return _HUGE;
}
#endif

double Props(char Output,char Name1, double Prop1, char Name2, double Prop2, char * Ref)
{
	double T,p,Q,rhoV,rhoL,Value,rho;
	int errCode;
	char errString[ERRSTRLENGTH];
	


	/*
	Following the naming conventions of MATLAB linked with REFPROP,
	each outputproperty is represented by one character:

	P   Pressure [kPa]
	T   Temperature [K]
	D   Density [kg/m3]
	H   Enthalpy [kJ/kg]
	S   Entropy [kJ/(kg/K)]
	U   Internal energy [kJ/kg]
	C   Cp [kJ/(kg K)]
	O   Cv [kJ/(kg K)]
	K   Ratio of specific heats (Cp/Cv) [-]
	A   Speed of sound [m/s]
	X   liquid phase and gas phase composition (mass fractions)
	V   Dynamic viscosity [Pa*s]
	L   Thermal conductivity [kW/(m K)]
	Q   Quality (vapor fraction) (kg/kg)
	I   Surface tension [N/m]
	F	Freezing point of secondary fluid [K] **NOT IN MATLAB-REFPROP **
	M	Maximum temperature for secondary fluid [K] **NOT IN MATLAB-REFPROP **
	B	Critical Temperature [K] **NOT IN MATLAB-REFPROP **
	E	Critical Pressure [K] **NOT IN MATLAB-REFPROP **
	*/

	// Pointers to the functions
	double (*p_func)(double,double);
	double (*h_func)(double,double,int);
	double (*s_func)(double,double,int);
	double (*u_func)(double,double,int);
	double (*rho_func)(double,double,int);
	double (*cp_func)(double,double,int);
	double (*cv_func)(double,double,int);
	double (*visc_func)(double,double,int);
	double (*k_func)(double,double,int);
	double (*w_func)(double,double,int);
	double (*rhosatV_func)(double);
	double (*rhosatL_func)(double);
	
	double (*Tc_func)(void);
	double (*pc_func)(void);
	double (*MM_func)(void);

	char * (*errCode_func)(void);

	errCode=0;
	
	


	// **********************************************************************************
	// **********************************************************************************
	//                                   REFPROP
	// **********************************************************************************
	// **********************************************************************************
	
	/* 
	If the fluid name is not actually a refrigerant name, but a string beginning with "REFPROP-",
	then REFPROP is used to calculate the desired property.
	*/
	#if defined(_WIN32) || defined(__WIN32__)
	if (strncmp(Ref,"REFPROP-",8)==0)  // First eight characters match "REFPROP-"
	{
	#else
	if (0) // Automatically skip it because REFPROP is not supported on this platform
	{
	#endif
		char *REFPROPRef=NULL,*RefCopy=NULL;
		double prop;
		// Allocate space for refrigerant name
			RefCopy=malloc(strlen(Ref)+1);
		// Make a backup copy
			strcpy(RefCopy,Ref);
		// Chop off the "REFPROP-"
			REFPROPRef = strtok(RefCopy,"-");
			REFPROPRef = strtok(NULL,"-");
		// Call REFPROP with your fluid name
			prop = REFPROP(Output,Name1,Prop1,Name2,Prop2,REFPROPRef);
		// Free allocated memory
			free(RefCopy);
		return prop;
	}

	// **********************************************************************************
	// **********************************************************************************
	//                                Normal Property evaluation
	// **********************************************************************************
	// **********************************************************************************

	// It's a secondary fluid
	else if (!strcmp(Ref,"Water")|| !strcmp(Ref,"HC-10") || (Ref[0]=='E' && Ref[1]=='G') || 
		(Ref[0]=='P' && Ref[1]=='G') || strncmp(Ref,"Methanol",8)==0 || strncmp(Ref,"NH3/H2O",7)==0)
	{
		return SecFluids(Output,Prop1,Prop2,Ref);
	}
	else if (Name1=='T' && (Name2=='P' || Name2=='D' || Name2=='Q'))
	{
		T=Prop1; 

		// Wire up the function pointers for the given refrigerant
		if (!strcmp(Ref,"Argon"))
		{
			p_func=p_Argon;
			h_func=h_Argon;
			s_func=s_Argon;
			u_func=u_Argon;
			rho_func=rho_Argon;
			cp_func=cp_Argon;
			cv_func=cv_Argon;
			visc_func=visc_Argon;
			k_func=k_Argon;
			w_func=w_Argon;
			Tc_func=Tcrit_Argon;
			pc_func=pcrit_Argon;
			MM_func=MM_Argon;
			rhosatV_func=rhosatV_Argon;
			rhosatL_func=rhosatL_Argon;
		}
		else if (!strcmp(Ref,"Nitrogen") || !strcmp(Ref,"N2"))
		{
			p_func=p_Nitrogen;
			h_func=h_Nitrogen;
			s_func=s_Nitrogen;
			u_func=u_Nitrogen;
			rho_func=rho_Nitrogen;
			cp_func=cp_Nitrogen;
			cv_func=cv_Nitrogen;
			visc_func=visc_Nitrogen;
			k_func=k_Nitrogen;
			w_func=w_Nitrogen;
			Tc_func=Tcrit_Nitrogen;
			pc_func=pcrit_Nitrogen;
			MM_func=MM_Nitrogen;
			rhosatV_func=rhosatV_Nitrogen;
			rhosatL_func=rhosatL_Nitrogen;
		}
		else if (!strcmp(Ref,"R744") || !strcmp(Ref,"CO2"))
		{
			p_func=p_R744;
			h_func=h_R744;
			s_func=s_R744;
			u_func=u_R744;
			rho_func=rho_R744;
			cp_func=cp_R744;
			cv_func=cv_R744;
			visc_func=visc_R744;
			k_func=k_R744;
			w_func=w_R744;
			Tc_func=Tcrit_R744;
			pc_func=pcrit_R744;
			MM_func=MM_R744;
			rhosatV_func=rhosatV_R744;
			rhosatL_func=rhosatL_R744;
		}
		
		else if (!strcmp(Ref,"R134a"))
		{
			p_func=p_R134a;
			h_func=h_R134a;
			s_func=s_R134a;
			u_func=u_R134a;
			rho_func=rho_R134a;
			cp_func=cp_R134a;
			cv_func=cv_R134a;
			visc_func=visc_R134a;
			k_func=k_R134a;
			w_func=w_R134a;
			Tc_func=Tcrit_R134a;
			pc_func=pcrit_R134a;
			MM_func=MM_R134a;
			rhosatV_func=rhosatV_R134a;
			rhosatL_func=rhosatL_R134a;
		}

		else if (!strcmp(Ref,"R290"))
		{
			p_func=p_R290;
			h_func=h_R290;
			s_func=s_R290;
			u_func=u_R290;
			rho_func=rho_R290;
			cp_func=cp_R290;
			cv_func=cv_R290;
			visc_func=visc_R290;
			k_func=k_R290;
			w_func=w_R290;
			Tc_func=Tcrit_R290;
			pc_func=pcrit_R290;
			MM_func=MM_R290;
			rhosatV_func=rhosatV_R290;
			rhosatL_func=rhosatL_R290;
		}
		else if (!strcmp(Ref,"R717") || !strcmp(Ref,"NH3") || !strcmp(Ref,"Ammonia") || !strcmp(Ref,"ammonia"))
		{
			p_func=p_R717;
			h_func=h_R717;
			s_func=s_R717;
			u_func=u_R717;
			rho_func=rho_R717;
			cp_func=cp_R717;
			cv_func=cv_R717;
			visc_func=visc_R717;
			k_func=k_R717;
			w_func=w_R717;
			Tc_func=Tcrit_R717;
			pc_func=pcrit_R717;
			MM_func=MM_R717;
			rhosatV_func=rhosatV_R717;
			rhosatL_func=rhosatL_R717;
		}
		else if (!strcmp(Ref,"R32"))
		{
			p_func=p_R32;
			h_func=h_R32;
			s_func=s_R32;
			u_func=u_R32;
			rho_func=rho_R32;
			cp_func=cp_R32;
			cv_func=cv_R32;
			visc_func=visc_R32;
			k_func=k_R32;
			w_func=w_R32;
			Tc_func=Tcrit_R32;
			pc_func=pcrit_R32;
			MM_func=MM_R32;
			rhosatV_func=rhosatV_R32;
			rhosatL_func=rhosatL_R32;
		}
		else if (!strcmp(Ref,"R410A"))
		{
			p_func=p_R410A;
			h_func=h_R410A;
			s_func=s_R410A;
			u_func=u_R410A;
			rho_func=rho_R410A;
			cp_func=cp_R410A;
			cv_func=cv_R410A;
			visc_func=visc_R410A;
			k_func=k_R410A;
			w_func=w_R410A;
			Tc_func=Tcrit_R410A;
			pc_func=pcrit_R410A;
			MM_func=MM_R410A;
			rhosatV_func=rhosatV_R410A;
			rhosatL_func=rhosatL_R410A;
		}
		else if (!strcmp(Ref,"R404A"))
		{
			p_func=p_R404A;
			h_func=h_R404A;
			s_func=s_R404A;
			u_func=u_R404A;
			rho_func=rho_R404A;
			cp_func=cp_R404A;
			cv_func=cv_R404A;
			visc_func=visc_R404A;
			k_func=k_R404A;
			w_func=w_R404A;
			Tc_func=Tcrit_R404A;
			pc_func=pcrit_R404A;
			MM_func=MM_R404A;
			rhosatV_func=rhosatV_R404A;
			rhosatL_func=rhosatL_R404A;
		}
		else if (!strcmp(Ref,"R407C"))
		{
			p_func=p_R407C;
			h_func=h_R407C;
			s_func=s_R407C;
			u_func=u_R407C;
			rho_func=rho_R407C;
			cp_func=cp_R407C;
			cv_func=cv_R407C;
			visc_func=visc_R407C;
			k_func=k_R407C;
			w_func=w_R407C;
			Tc_func=Tcrit_R407C;
			pc_func=pcrit_R407C;
			MM_func=MM_R407C;
			rhosatV_func=rhosatV_R407C;
			rhosatL_func=rhosatL_R407C;
		}
		else if (!strcmp(Ref,"R507A"))
		{
			p_func=p_R507A;
			h_func=h_R507A;
			s_func=s_R507A;
			u_func=u_R507A;
			rho_func=rho_R507A;
			cp_func=cp_R507A;
			cv_func=cv_R507A;
			visc_func=visc_R507A;
			k_func=k_R507A;
			w_func=w_R507A;
			Tc_func=Tcrit_R507A;
			pc_func=pcrit_R507A;
			MM_func=MM_R507A;
			rhosatV_func=rhosatV_R507A;
			rhosatL_func=rhosatL_R507A;
		}
		else
		{
			fprintf(stderr,"Refrigerant %s not allowed\n",Ref);
		}

		// Temperature and Pressure are the inputs
		if (Name2=='P')
		{
			p=Prop2;
			switch (Output)
			{
				case 'H':
					Value=h_func(T,p,TYPE_TPNoLookup); break;
				case 'D':
					Value=rho_func(T,p,TYPE_TPNoLookup); break;
				case 'S':
					Value=s_func(T,p,TYPE_TPNoLookup); break;
				case 'U':
					Value=u_func(T,p,TYPE_TPNoLookup); break;
				case 'C':
					Value=cp_func(T,p,TYPE_TPNoLookup); break;
				case 'O':
					Value=cv_func(T,p,TYPE_TPNoLookup); break;
				case 'V':
					Value=visc_func(T,p,TYPE_TPNoLookup); break;
				case 'L':
					Value=k_func(T,p,TYPE_TPNoLookup); break;
				case 'A':
					Value=w_func(T,p,TYPE_TPNoLookup); break;
				case 'M':
					Value=MM_func(); break;
				default:
					strcpy(errString,"Invalid Output Name");
					return -100;
			}
		/*	if (errCode_R410A()!=0)
			{
				printf("Ref error code %d found\n",Ref, errCode_func());
				return _HUGE;
			}*/
			//else
				return Value;
		}
		// Temperature and density are the inputs
		else if (Name2=='D')
		{
			rho=Prop2;
			switch (Output)
			{
				case 'P':
					Value=p_func(T,rho); break;
				case 'H':
					Value=h_func(T,rho,TYPE_Trho); break;
				case 'S':
					Value=s_func(T,rho,TYPE_Trho); break;
				case 'U':
					Value=u_func(T,rho,TYPE_Trho); break;
				case 'C':
					Value=cp_func(T,rho,TYPE_Trho); break;
				case 'O':
					Value=cv_func(T,rho,TYPE_Trho); break;
				case 'V':
					Value=visc_func(T,rho,TYPE_Trho); break;
				case 'L':
					Value=k_func(T,rho,TYPE_Trho); break;
				case 'A':
					Value=w_func(T,rho,TYPE_Trho); break;
				case 'M':
					Value=MM_func(); break;
				default:
					strcpy(errString,"Invalid Output Name");
					return -100;
			}
			/*if (errCode_func()!=0)
			{
				printf("%s error code %d found\n",Ref,errCode_func());
				return _HUGE;
			}*/
			//else
				return Value;
		}

		// Temperature and quality are the inputs
		else if (Name2=='Q')
		{
			Q=Prop2;
			rhoV=rhosatV_func(T);
			rhoL=rhosatL_func(T);
			rho=1/(Q/rhoV+(1-Q)/rhoL);

			switch (Output)
			{
				case 'P':
					Value=Q*p_func(T,rhoV)+(1-Q)*p_func(T,rhoL); 
					break;
				case 'H':
					Value=Q*h_func(T,rhoV,TYPE_Trho)+(1-Q)*h_func(T,rhoL,TYPE_Trho); 
					break;
				case 'D':
					Value=rho; break;
				case 'S':
					Value=Q*s_func(T,rhoV,TYPE_Trho)+(1-Q)*s_func(T,rhoL,TYPE_Trho); 
					break;
				case 'U':
					Value=Q*u_func(T,rhoV,TYPE_Trho)+(1-Q)*u_func(T,rhoL,TYPE_Trho); 
					break;
				case 'C':
					Value=Q*cp_func(T,rhoV,TYPE_Trho)+(1-Q)*cp_func(T,rhoL,TYPE_Trho); 
					break;
				case 'O':
					Value=Q*cv_func(T,rhoV,TYPE_Trho)+(1-Q)*cv_func(T,rhoL,TYPE_Trho); 
					break;
				case 'V':
					Value=Q*visc_func(T,rhoV,TYPE_Trho)+(1-Q)*visc_func(T,rhoL,TYPE_Trho); 
					break;
				case 'L':
					Value=Q*k_func(T,rhoV,TYPE_Trho)+(1-Q)*k_func(T,rhoL,TYPE_Trho); 
					break;
				case 'A':
					Value=Q*w_func(T,rhoV,TYPE_Trho)+(1-Q)*w_func(T,rhoL,TYPE_Trho); 
					break;
				case 'M':
					Value=MM_func(); break;
				default:
					strcpy(errString,"Invalid Output Name");
					return -100;
			}
			/*if (errCode_func()!=0)
			{
				printf("%s error code %d found\n",Ref,errCode_func());
				return _HUGE;
			}
			else*/
				return Value;
		}
		else
		{
			fprintf(stderr,"Names of input properties invalid (%c,%c) with refrigerant %s.  Valid choices are T,P or T,Q or T,D",Name1,Name2,Ref);
			return _HUGE;
		}

	}
	else
	{
		fprintf(stderr,"Names of input properties invalid (%c,%c).  Valid choices are T,P or T,Q or T,D",Name1,Name2);
		return _HUGE;
	}
}

double pcrit(char *Ref)
{
	if (!strcmp(Ref,"R134a"))
		return pcrit_R134a();
	else if (!strcmp(Ref,"R290"))
		return pcrit_R290();
	else if (!strcmp(Ref,"R744"))
		return pcrit_R744();
	else if (!strcmp(Ref,"R410A"))
		return pcrit_R410A();
	else if (!strcmp(Ref,"R404A"))
		return pcrit_R404A();
	else if (!strcmp(Ref,"R717"))
		return pcrit_R717();
	else if (!strcmp(Ref,"R32"))
		return pcrit_R32();
	else if (!strcmp(Ref,"Nitrogen"))
		return pcrit_Nitrogen();
	else if (!strcmp(Ref,"Argon"))
		return pcrit_Argon();

	else if (strncmp(Ref,"REFPROP-",8)==0)  // First eight characters match "REFPROP-"
	{
		char *REFPROPRef=NULL,*RefCopy=NULL;
		double pcrit;
		RefCopy=malloc(strlen(Ref)+1);
		strcpy(RefCopy,Ref);
		REFPROPRef = strtok(RefCopy,"-");
		REFPROPRef = strtok(NULL,"-");
		// 'E' is the code for the critical pressure (ran out of sensible characters).  
		pcrit=REFPROP('E','T',0.0,'Q',0.0,REFPROPRef);
		free(RefCopy);
		return pcrit;
	}
	else
		return _HUGE;
}

double Tcrit(char *Ref)
{
	if (!strcmp(Ref,"R134a"))
		return Tcrit_R134a();
	else if (!strcmp(Ref,"R290"))
		return Tcrit_R290();
	else if (!strcmp(Ref,"R744"))
		return Tcrit_R744();
	else if (!strcmp(Ref,"R410A"))
		return Tcrit_R410A();
	else if (!strcmp(Ref,"R404A"))
		return Tcrit_R404A();
	else if (!strcmp(Ref,"R717"))
		return Tcrit_R717();
	else if (!strcmp(Ref,"R32"))
		return Tcrit_R32();
	else if (!strcmp(Ref,"Nitrogen"))
		return Tcrit_Nitrogen();
	else if (!strcmp(Ref,"Argon"))
		return Tcrit_Argon();
	else if (strncmp(Ref,"REFPROP-",8)==0)  // First eight characters match "REFPROP-"
	{
		char *REFPROPRef=NULL,*RefCopy=NULL;
		double Tcrit;
		RefCopy=malloc(strlen(Ref)+1);
		strcpy(RefCopy,Ref);
		REFPROPRef = strtok(RefCopy,"-");
		REFPROPRef = strtok(NULL,"-");
		// 'B' is the code for the critical pressure (ran out of sensible characters).
		Tcrit=REFPROP('B','T',0.0,'Q',0.0,REFPROPRef);
		free(RefCopy);
		return Tcrit;
	}
	else
		return _HUGE;
}

int errCode(char * Ref)
{
	if (!strcmp(Ref,"R134a"))
		return errCode_R134a();
	if (!strcmp(Ref,"R290"))
		return errCode_R290();
	if (!strcmp(Ref,"R744"))
		return errCode_R744();
	if (!strcmp(Ref,"R717"))
		return errCode_R717();
	if (!strcmp(Ref,"R32"))
		return errCode_R32();
	if (!strcmp(Ref,"R404A"))
		return errCode_R404A();
	if (!strcmp(Ref,"R410A"))
		return errCode_R410A();
	return -1;
}

double T_hp(char *Ref, double h, double p, double T_guess)
{
	double x1=0,x2=0,x3=0,y1=0,y2=0,eps=1e-8,change=999,f,T=300;
	int iter=1;
	while ((iter<=3 || change>eps) && iter<100)
	{
		if (iter==1){x1=T_guess; T=x1;}
		if (iter==2){x2=T_guess+0.1; T=x2;}
		if (iter>2) {T=x2;}
			f=Props('H','T',T,'P',p,Ref)-h;
		if (iter==1){y1=f;}
		if (iter>1)
		{
			y2=f;
			x3=x2-y2/(y2-y1)*(x2-x1);
			change=fabs(y2/(y2-y1)*(x2-x1));
			y1=y2; x1=x2; x2=x3;
		}
		iter=iter+1;
		if (iter>50)
		{
			printf("T_hp not converging with inputs(%s,%g,%g,%g)\n",Ref,h,p,T_guess);
		}
	}
	return T;
}

double h_sp(char *Ref, double s, double p, double T_guess)
{
	double x1=0,x2=0,x3=0,y1=0,y2=0,eps=1e-8,change=999,f=999,T=300;
	int iter=1;

	
	while ((iter<=3 || change>eps) && iter<100)
	{
		if (iter==1){x1=T_guess; T=x1;}
		if (iter==2){x2=T_guess+1.0; T=x2;}
		if (iter>2) {T=x2;}

			// Find the temperature which gives the same entropy
			f=Props('S','T',T,'P',p,Ref)-s;

		if (iter==1){y1=f;}
		if (iter>1)
		{
			y2=f;
			x3=x2-y2/(y2-y1)*(x2-x1);
			change=fabs(y2/(y2-y1)*(x2-x1));
			y1=y2; x1=x2; x2=x3;
		}
		iter=iter+1;
		if (iter>50)
		{
			printf("h_sp not converging with inputs(%s,%g,%g,%g)\n",Ref,s,p,T_guess);
		}
	}
	return Props('H','T',T,'P',p,Ref);
}


double Tsat(char *Ref, double p, double Q, double T_guess)
{
	double x1=0,x2=0,x3=0,y1=0,y2=0,eps=1e-8,change=999,f=999,T=300;
	int iter=1;

	
	while ((iter<=3 || change>eps) && iter<100)
	{
		if (iter==1){x1=T_guess; T=x1;}
		if (iter==2){x2=T_guess+1.0; T=x2;}
		if (iter>2) {T=x2;}

			// Find the temperature which gives the same entropy
			f=Props('P','T',T,'Q',Q,Ref)-p;

		if (iter==1){y1=f;}
		if (iter>1)
		{
			y2=f;
			x3=x2-y2/(y2-y1)*(x2-x1);
			change=fabs(y2/(y2-y1)*(x2-x1));
			y1=y2; x1=x2; x2=x3;
		}
		iter=iter+1;
		if (iter>50)
		{
			printf("Tsat not converging with inputs(%s,%g,%g,%g)\n",Ref,p,Q,T_guess);
		}
	}
	return x2;
}

double K2F(double T)
{
	return T * 9 / 5 - 459.67;
}

double F2K(double T_F)
{
	return (T_F + 459.67) * 5 / 9;
}

void PrintSaturationTable(char *FileName, char * Ref,double Tmin, double Tmax)
{

	double T;
	FILE *f;
	f=fopen(FileName,"w");
	fprintf(f,"T,pL,pV,rhoL,rhoV,uL,uV,hL,hV,sL,sV,cvL,cvV,cpL,cpV,kL,kV,muL,muV\n");
	fprintf(f,"[K],[kPa],[kPa],[kg/m^3],[kg/m^3],[kJ/kg],[kJ/kg],[kJ/kg],[kJ/kg],[kJ/kg-K],[kJ/kg-K],[kJ/kg-K],[kJ/kg-K],[kJ/kg-K],[kJ/kg-K],[kW/m-K],[kW/m-K],[Pa-s],[Pa-s]\n");
	fprintf(f,"--------------------------------------------------------------------------\n");

	for (T=Tmin;T<Tmax;T+=1.0)
	{
	fprintf(f,"%0.3f,",T);
	fprintf(f,"%0.6f,",Props('P','T',T,'Q',0,Ref));
	fprintf(f,"%0.6f,",Props('P','T',T,'Q',1,Ref));
	fprintf(f,"%0.6f,",Props('D','T',T,'Q',0,Ref));
	fprintf(f,"%0.6f,",Props('D','T',T,'Q',1,Ref));
	fprintf(f,"%0.6f,",Props('U','T',T,'Q',0,Ref));
	fprintf(f,"%0.6f,",Props('U','T',T,'Q',1,Ref));
	fprintf(f,"%0.6f,",Props('H','T',T,'Q',0,Ref));
	fprintf(f,"%0.6f,",Props('H','T',T,'Q',1,Ref));
	fprintf(f,"%0.6f,",Props('S','T',T,'Q',0,Ref));
	fprintf(f,"%0.6f,",Props('S','T',T,'Q',1,Ref));
	fprintf(f,"%0.6f,",Props('O','T',T,'Q',0,Ref));
	fprintf(f,"%0.6f,",Props('O','T',T,'Q',1,Ref));
	fprintf(f,"%0.6f,",Props('C','T',T,'Q',0,Ref));
	fprintf(f,"%0.6f,",Props('C','T',T,'Q',1,Ref));
	fprintf(f,"%0.9f,",Props('L','T',T,'Q',0,Ref));
	fprintf(f,"%0.9f,",Props('L','T',T,'Q',1,Ref));
	fprintf(f,"%0.6g,",Props('V','T',T,'Q',0,Ref));
	fprintf(f,"%0.6g,",Props('V','T',T,'Q',1,Ref));
	fprintf(f,"\n");
	}
	fclose(f);
}

double DerivTerms(char *Term,char Name1, double Prop1, char Name2, double Prop2, char * Ref)
{
	// Pointers to the functions
	double (*dhdT)(double,double,int);
	double (*dpdT)(double,double,int);
	double (*dhdrho)(double,double,int);
	double (*dpdrho)(double,double,int);
	
	// Wire up the pointers for the given refrigerant
	if (!strcmp(Ref,"Argon"))
	{
		dhdT=dhdT_Argon;
		dpdT=dpdT_Argon;
		dhdrho=dhdrho_Argon;
		dpdrho=dpdrho_Argon;
	}
	else if (!strcmp(Ref,"Nitrogen") || !strcmp(Ref,"N2"))
	{
		dhdT=dhdT_Nitrogen;
		dpdT=dpdT_Nitrogen;
		dhdrho=dhdrho_Nitrogen;
		dpdrho=dpdrho_Nitrogen;
	}
	else if (!strcmp(Ref,"R744") || !strcmp(Ref,"CO2"))
	{
		dhdT=dhdT_R744;
		dpdT=dpdT_R744;
		dhdrho=dhdrho_R744;
		dpdrho=dpdrho_R744;
	}
	else if (!strcmp(Ref,"R410A"))
	{
		dhdT=dhdT_R410A;
		dpdT=dpdT_R410A;
		dhdrho=dhdrho_R410A;
		dpdrho=dpdrho_R410A;
	}
	else if (!strcmp(Ref,"R134a") )
	{
		dhdT=dhdT_R134a;
		dpdT=dpdT_R134a;
		dhdrho=dhdrho_R134a;
		dpdrho=dpdrho_R134a;
	}
	else
	{
		printf("Bad Refrigerant Name in DerivTerms [%s]\n",Ref);
	}
	
	if (Name1=='T' && Name2=='P' && !strcmp(Term,"dhdT"))
		return dhdT(Prop1,Prop2,TYPE_TPNoLookup);
	else if (Name1=='T' && Name2=='P' && !strcmp(Term,"dhdrho"))
		return dhdrho(Prop1,Prop2,TYPE_TPNoLookup);
	else if (Name1=='T' && Name2=='P' && !strcmp(Term,"dpdT"))
		return dpdT(Prop1,Prop2,TYPE_TPNoLookup);
	else if (Name1=='T' && Name2=='P' && !strcmp(Term,"dpdrho"))
		return dpdrho(Prop1,Prop2,TYPE_TPNoLookup);
	
	else if (Name1=='T' && Name2=='D' && !strcmp(Term,"dhdT"))
		return dhdT(Prop1,Prop2,TYPE_Trho);
	else if (Name1=='T' && Name2=='D' && !strcmp(Term,"dhdrho"))
		return dhdrho(Prop1,Prop2,TYPE_Trho);
	else if (Name1=='T' && Name2=='D' && !strcmp(Term,"dpdT"))
		return dpdT(Prop1,Prop2,TYPE_Trho);
	else if (Name1=='T' && Name2=='D' && !strcmp(Term,"dpdrho"))
		return dpdrho(Prop1,Prop2,TYPE_Trho);
	
	else if (Name1=='T' && Name2=='P' && !strcmp(Term,"dhdTnum"))
		return dhdT(Prop1,Prop2,99);
	else if (Name1=='T' && Name2=='P' && !strcmp(Term,"dhdrhonum"))
		return dhdrho(Prop1,Prop2,99);
	else if (Name1=='T' && Name2=='P' && !strcmp(Term,"dpdTnum"))
		return dpdT(Prop1,Prop2,99);
	else if (Name1=='T' && Name2=='P' && !strcmp(Term,"dpdrhonum"))
		return dpdrho(Prop1,Prop2,99);

	else if (Name1=='T' && Name2=='P' && !strcmp(Term,"dhdTnum"))
		return dhdT(Prop1,Prop2,99);
	else if (Name1=='T' && Name2=='P' && !strcmp(Term,"dhdrhonum"))
		return dhdrho(Prop1,Prop2,99);
	else if (Name1=='T' && Name2=='P' && !strcmp(Term,"dpdTnum"))
		return dpdT(Prop1,Prop2,99);
	else if (Name1=='T' && Name2=='P' && !strcmp(Term,"dpdrhonum"))
		return dpdrho(Prop1,Prop2,99);
	else
	{
		printf("Bad pair of properties[%c,%c] and derivative name [%s]\n",Name1,Name2,Term);
		return _HUGE;
	}
	
}