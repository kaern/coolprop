#ifndef COOLPROPDLL_H
#define COOLPROPDLL_H

	#if defined(COOLPROP_LIB)
	#define EXPORT_CODE extern "C" __declspec(dllexport)
	#ifndef CONVENTION
		#define CONVENTION __stdcall
	#endif
	#else
        #ifndef EXPORT_CODE
            #if defined(EXTERNC)
                #define EXPORT_CODE extern "C"
            #else
                #define EXPORT_CODE
            #endif
        #endif
		#ifndef CONVENTION
			#define CONVENTION
		#endif
	#endif

	// Hack for PowerPC compilation to only use extern "C"
	#if defined(__powerpc__) || defined(EXTERNC)
	#define EXPORT_CODE extern "C"
	#endif
	
	// Functions with the call type like
    // EXPORT_CODE void CONVENTION AFunction(double, double);
	// will be exported to the DLL

	// They can only use data types that play well with DLL wrapping (int, long, double, char*, void, etc.)
	
	EXPORT_CODE double CONVENTION Props(char *Output,char Name1, double Prop1, char Name2, double Prop2, char * Ref);
	EXPORT_CODE double CONVENTION Props1(char *Ref, char * Output);

	EXPORT_CODE long CONVENTION get_global_param_string(char *param, char * Output);
	EXPORT_CODE long CONVENTION get_fluid_param_string(char *fluid, char *param, char * Output);
	
	// This version uses the indices in place of the strings for speed.  Get the parameter indices
	// from get_param_index('D') for instance and the Fluid index from get_Fluid_index('Air') for instance
	EXPORT_CODE double CONVENTION IProps(long iOutput, long iName1, double Prop1, long iName2, double Prop2, long iFluid);

	// Convenience functions
	EXPORT_CODE int CONVENTION IsFluidType(char *Ref, char *Type);
	EXPORT_CODE double CONVENTION DerivTerms(char *Term, double T, double rho, char * Ref);
	EXPORT_CODE long CONVENTION Phase(char *Fluid, double T, double p, char *Phase_str);
	EXPORT_CODE long CONVENTION Phase_Trho(char *Fluid, double T, double p, char *Phase_str);
	EXPORT_CODE long CONVENTION Phase_Tp(char *Fluid, double T, double rho, char *Phase_str);
	EXPORT_CODE void CONVENTION set_phase(char *Phase_str);
	EXPORT_CODE double CONVENTION F2K(double T_F);
	EXPORT_CODE double CONVENTION K2F(double T);
	
	EXPORT_CODE long CONVENTION get_param_index(char * param);
	EXPORT_CODE long CONVENTION get_Fluid_index(char * param);
	EXPORT_CODE long CONVENTION get_index_units(long param, char * units);

	/*EXPORT_CODE int CONVENTION get_debug_level();
	EXPORT_CODE void CONVENTION set_debug_level(int level);*/

	EXPORT_CODE double CONVENTION rhosatL_anc(char* Fluid, double T);
	EXPORT_CODE double CONVENTION rhosatV_anc(char* Fluid, double T);
	EXPORT_CODE double CONVENTION psatL_anc(char* Fluid, double T);
	EXPORT_CODE double CONVENTION psatV_anc(char* Fluid, double T);

	/// -------------------------------------------
	///     TTSE Tabular Taylor Series Expansion
	/// -------------------------------------------
	/// Enable the TTSE
	EXPORT_CODE bool CONVENTION enable_TTSE_LUT(char *FluidName);
	/// Check if TTSE is enabled
	EXPORT_CODE bool CONVENTION isenabled_TTSE_LUT(char *FluidName);
	/// Disable the TTSE
	EXPORT_CODE bool CONVENTION disable_TTSE_LUT(char *FluidName);
	/// Enable the writing of TTSE tables to file for this fluid
	EXPORT_CODE bool CONVENTION enable_TTSE_LUT_writing(char *FluidName);
	/// Check if the writing of TTSE tables to file is enabled
	EXPORT_CODE bool CONVENTION isenabled_TTSE_LUT_writing(char *FluidName);
	/// Disable the writing of TTSE tables to file for this fluid
	EXPORT_CODE bool CONVENTION disable_TTSE_LUT_writing(char *FluidName);
	/// Over-ride the default size of both of the saturation LUT
	EXPORT_CODE bool CONVENTION set_TTSESat_LUT_size(char *FluidName, int);
	/// Over-ride the default size of the single-phase LUT
	EXPORT_CODE bool CONVENTION set_TTSESinglePhase_LUT_size(char *FluidName, int Np, int Nh);
	/// Over-ride the default range of the single-phase LUT
	EXPORT_CODE bool CONVENTION set_TTSESinglePhase_LUT_range(char *FluidName, double hmin, double hmax, double pmin, double pmax);
	/// Get the current range of the single-phase LUT
	EXPORT_CODE bool CONVENTION get_TTSESinglePhase_LUT_range(char *FluidName, double *hmin, double *hmax, double *pmin, double *pmax);

	/// Set the TTSE mode (normal or bicubic)
	EXPORT_CODE int CONVENTION set_TTSE_mode(char *FluidName, char * Value);

	EXPORT_CODE int CONVENTION set_reference_stateS(char *Ref, char *reference_state);
	EXPORT_CODE int CONVENTION set_reference_stateD(char *Ref, double T, double rho, double h0, double s0);

	// Expose some functions that are useful for ECS debugging
	EXPORT_CODE double CONVENTION viscosity_dilute(char* FluidName, double T);
	EXPORT_CODE double CONVENTION viscosity_residual(char* FluidName, double T, double rho);
	EXPORT_CODE double CONVENTION conductivity_critical(char* FluidName, double T, double rho);
	EXPORT_CODE double CONVENTION conductivity_background(char* FluidName, double T, double rho);
	EXPORT_CODE double CONVENTION conformal_Trho(char* FluidName, char* ReferenceFluidName, double T, double rho, double *Tconform, double *rhoconform);

#endif