/***********************************************************************
/
/ Chemistry data structure
/
/
/ Copyright (c) 2013, Enzo/Grackle Development Team.
/
/ Distributed under the terms of the Enzo Public Licence.
/
/ The full license is in the file LICENSE, distributed with this 
/ software.
************************************************************************/

#ifndef __CHEMISTRY_DATA_H__
#define __CHEMISTRY_DATA_H__

/**********************************
 *** Grackle runtime parameters ***
 **********************************/
typedef struct
{

  /* grackle on/off flag
     0) off, 1) on */
  int use_grackle;

  /* include cooling in chemistry solver
     0) no, 1) yes */
  int with_radiative_cooling;

  /* chemistry network
     0) tabulated cooling (no chemistry)
     1) HI, HII, HeI, HeII, HeIII, e
     2) + H2, H2I+, H-
     3) + D, D+, HD */
  int primordial_chemistry;

  /* dust chemistry and cooling
     0) no dust chemistry or cooling
     1) basic dust treatment
        - photo-electric heating
        - recombination cooling
        - with primordial_chemistry > 1:
          - H2 formation on dust grains
          - gas/grain heat transfer */
  int dust_chemistry;

  /* metal cooling on/off
     0) off, 1) on */
  int metal_cooling;

  /* add heating from UV background model
     0) off, 1) on */
  int UVbackground;

  /* data file containing cooling and UV background tables */
  char *grackle_data_file;

  /* Use a CMB temperature floor
     0) no, 1) yes */
  int cmb_temperature_floor;

  /* adiabatic index */
  double Gamma;

  /* H2 formation on dust grains and dust cooling
     0) off, 1) on */
  int h2_on_dust;

  /* Flag to supply a dust density field */
  int use_dust_density_field;

//#ifdef GRACKLE_MD
  /* Flag to solve metal chemistry */
  int metal_chemistry;

  /* Flag to solve grain growth reactions */
  int grain_growth;

  /* Flag to solve multiple metal sources */
  int multi_metals;

  /* Select pop III metal/dust model
         For multi_metals = 0, select a dust model
         For multi_metals > 0, select a set of dust models */
  int metal_pop3;

  /* Flag to solve multiple grain species */
  int dust_species;

  /* Flag to solve temperatures of multiple grain species */
  int dust_temperature_species;

  /* Flag to supply dust sublimation */
  int dust_sublimation;
//#endif

  /* photo-electric heating from irradiated dust */
  int photoelectric_heating;
  double photoelectric_heating_rate;

  /* Flag to supply a field for the interstellar radiation field */
  int use_isrf_field;

  // local FUV interstellar radiation field in Habing units
  double interstellar_radiation_field;

  /* flags to signal that arrays of volumetric or
     specific heating rates are being provided */

  int use_volumetric_heating_rate;
  int use_specific_heating_rate;

  /* additional chemistry solver parameters */
  int three_body_rate;
  int cie_cooling;
  int h2_optical_depth_approximation;
  int ih2co; // flag for H2 cooling (0-off/1-on)
  int ipiht; // flag for photoionization cooling
  double HydrogenFractionByMass;
  double DeuteriumToHydrogenRatio;
  double SolarMetalFractionByMass;
  double local_dust_to_gas_ratio;

//#ifdef GRACKLE_MD
  /* metal/dust abundance */

  /* Local ISM (Pollack et al. 1994) */
  double loc_XC , loc_XO , loc_XMg, loc_XAl, loc_XSi, loc_XS , loc_XFe;
  double loc_fC , loc_fO , loc_fMg, loc_fAl, loc_fSi, loc_fS , loc_fFe;
  double loc_fFeM    , loc_fMg2SiO4, loc_fMgSiO3 , loc_fFeS  
       , loc_freforg , loc_fvolorg , loc_fH2Oice ;
  double *loc_r0FeM    , *loc_r0Mg2SiO4, *loc_r0MgSiO3 , *loc_r0FeS    
       , *loc_r0reforg , *loc_r0volorg , *loc_r0H2Oice ;

  /* Pop III SN */
  /* normal CCSN 30 Msun */
  double C30_XC , C30_XO , C30_XMg, C30_XAl, C30_XSi, C30_XS , C30_XFe;
  double C30_fC , C30_fO , C30_fMg, C30_fAl, C30_fSi, C30_fS , C30_fFe;
  double C30_fSiM    , C30_fFeM    , C30_fMg2SiO4, C30_fMgSiO3
       , C30_fAC     , C30_fSiO2D  , C30_fMgO    , C30_fFeS    , C30_fAl2O3;
  double *C30_r0SiM    , *C30_r0FeM    , *C30_r0Mg2SiO4, *C30_r0MgSiO3
       , *C30_r0AC     , *C30_r0SiO2D  , *C30_r0MgO    , *C30_r0FeS    , *C30_r0Al2O3;

  /* faint SN 13 Msun */
  double F13_XC , F13_XO , F13_XMg, F13_XAl, F13_XSi, F13_XS , F13_XFe;
  double F13_fC , F13_fO , F13_fMg, F13_fAl, F13_fSi, F13_fS , F13_fFe;
  double F13_fFeM    , F13_fMg2SiO4, F13_fMgSiO3 , F13_fFe3O4  
       , F13_fAC     , F13_fSiO2D  , F13_fAl2O3;
  double *F13_r0FeM    , *F13_r0Mg2SiO4, *F13_r0MgSiO3 , *F13_r0Fe3O4
       , *F13_r0AC     , *F13_r0SiO2D  , *F13_r0Al2O3;
//#endif

  int NumberOfTemperatureBins;
  int CaseBRecombination;
  double TemperatureStart;
  double TemperatureEnd;
  int NumberOfDustTemperatureBins;
  double DustTemperatureStart;
  double DustTemperatureEnd;

  /* additional radiation background parameters */
  int Compton_xray_heating;
  int LWbackground_sawtooth_suppression;
  double LWbackground_intensity;   // [in units of 10^21 erg/s/cm^2/Hz/sr]
  double UVbackground_redshift_on;
  double UVbackground_redshift_off;
  double UVbackground_redshift_fullon;
  double UVbackground_redshift_drop;

  /* Factor to account for extra electrons from metals.
     Only for old-style Cloudy tables.
     f = SUM { A_i * i }, for i = 3 to N.
     N = Atomic number of heaviest element in cooling model.
     For solar abundance patters and N = 30 (Zn), f = 9.153959e-3. */
  double cloudy_electron_fraction_factor;

  /* flags and parameters to signal that RT
     is being used, and appropriate parameters
     for setting RT solvers */
  int use_radiative_transfer;
  int radiative_transfer_coupled_rate_solver;
  int radiative_transfer_intermediate_step;
  int radiative_transfer_hydrogen_only;

  /* flag for approximiate self-shielding as well
     as spectrum averaged photo heating and
     photo ionization shielding factors */
  int self_shielding_method;

  /* flag for Wolcott-Green+ 2011 H2 self-shielding */
  int H2_self_shielding;

  /* number of OpenMP threads, if supported */
# ifdef _OPENMP
  int omp_nthreads;
# endif

} chemistry_data;

/*****************************
 *** Cooling table storage ***
 *****************************/
typedef struct
{

  // Rank of dataset.
  long long grid_rank;

  // Dimension of dataset.
  long long *grid_dimension;

  // Dataset parameter values.
  double **grid_parameters;

  // Heating values
  double *heating_data;

  // Cooling values
  double *cooling_data;

  // Mean Molecular Weight values
  double *mmw_data;

  // Length of 1D flattened data
  long long data_size;

} cloudy_data;

/**********************************
 *** UVbackground table storage ***
 **********************************/

typedef struct
{

    long long Nz;

    double zmin, zmax;    
    double *z;

    /* Radiative rates for 6-species. */
    double *k24;
    double *k25;
    double *k26;
    /* Radiative rates for 9-species. */
    double *k27;
    double *k28;
    double *k29;
    double *k30;
    double *k31;

    double *piHI;
    double *piHeI;
    double *piHeII;

    // spectrum averaged absorption cross sections
    double *crsHI;
    double *crsHeI;
    double *crsHeII;

} UVBtable;

/******************************************
 *** Chemistry and cooling data storage ***
 ******************************************/
typedef struct
{

  /**********************************
   * primordial chemistry rate data *
   **********************************/

  /* 6 species rates */
  double *k1;
  double *k2;
  double *k3;
  double *k4;
  double *k5;
  double *k6;

  /* 9 species rates (including H2) */
  double *k7;
  double *k8;
  double *k9;
  double *k10;
  double *k11;
  double *k12;
  double *k13;
  double *k14;
  double *k15;
  double *k16;
  double *k17;
  double *k18;
  double *k19;
  double *k20;  /* currently not used */
  double *k21;  /* currently not used */
  double *k22;  /* 3-body H2 formation */
  double *k23;  /* H2-H2 dissociation */
  double *k13dd;  /* density dependent version of k13 (collisional H2
                    dissociation); actually 7 functions instead of 1. */

  /* Radiative rates for 6-species (for external field). */
  double k24;
  double k25;
  double k26;

  /* Radiative rates for 9-species (for external field). */
  double k27;
  double k28;
  double k29;
  double k30;
  double k31;

  /* 12 species rates (with Deuterium). */
  double *k50;
  double *k51;
  double *k52;
  double *k53;
  double *k54;
  double *k55;
  double *k56;

  /* New H-ionizing reactions, used for 6, 9 & 12 species chemistry */
  double *k57;
  double *k58;

//#ifdef GRACKLE_MD
  /* 15 species rates (with DM, HDII, HeHII) */
  double *k125;
  double *k129;
  double *k130;
  double *k131;
  double *k132;
  double *k133;
  double *k134;
  double *k135;
  double *k136;
  double *k137;
  double *k148;
  double *k149;
  double *k150;
  double *k151;
  double *k152;
  double *k153;

  /* Metal species */
  double *kz15;
  double *kz16;
  double *kz17;
  double *kz18;
  double *kz19;
  double *kz20;
  double *kz21;
  double *kz22;
  double *kz23;
  double *kz24;
  double *kz25;
  double *kz26;
  double *kz27;
  double *kz28;
  double *kz29;
  double *kz30;
  double *kz31;
  double *kz32;
  double *kz33;
  double *kz34;
  double *kz35;
  double *kz36;
  double *kz37;
  double *kz38;
  double *kz39;
  double *kz40;
  double *kz41;
  double *kz42;
  double *kz43;
  double *kz44;
  double *kz45;
  double *kz46;
  double *kz47;
  double *kz48;
  double *kz49;
  double *kz50;
  double *kz51;
  double *kz52;
  double *kz53;
  double *kz54;
//#endif

  /* H2 formation on dust grains */
  double *h2dust;
  double *h2dustS;
  double *h2dustC;

  /* Grain growth rate */
  double *grogr;

  /* Chemical heating from H2 formation. */
  /* numerator and denominator of Eq 23 of Omukai ea. 2000. */
  double *n_cr_n;
  double *n_cr_d1;
  double *n_cr_d2;

  /********************************
   * primordial cooling rate data *
   ********************************/

  /* 6 species rates */
  double *ceHI;                   // collisional excitation rates
  double *ceHeI;
  double *ceHeII;
  double *ciHI;                   // collisional ionization
  double *ciHeI;
  double *ciHeIS;
  double *ciHeII;
  double *reHII;                  // recombination
  double *reHeII1;
  double *reHeII2;
  double *reHeIII;
  double *brem;                   // free-free (Bremsstrahlung)
  double comp;                    // Compton cooling
  double comp_xray;               // X-ray compton heating coefficient
  double temp_xray;               // X-ray compton heating temperature (K)

  /* radiative rates (external field). */
  double piHI;                    // photo-ionization cooling
  double piHeI;                   //    (no temperature dependance)
  double piHeII;

  // spectrum averaged absorption cross sections
  double crsHI;
  double crsHeI;
  double crsHeII;

  /* 9 species rates (including H2) 
       The first five are for the Lepp & Shull rates.
       The next two are for the (better) Galli & Palla 1999 rates. 
       The selection is controlled by a flag in cool1d_multi_g.F. */
  double *hyd01k;
  double *h2k01;
  double *vibh;
  double *roth;
  double *rotl;
  double *GP99LowDensityLimit;
  double *GP99HighDensityLimit;

  /* Revised H2 cooling rates from Glover & Abel 2008 */
  double *GAHI;
  double *GAH2;
  double *GAHe;
  double *GAHp;
  double *GAel;

  /* Updated H2 LTE rate from Glover (2015, MNRAS, 451, 2082) */
  double *H2LTE;

  /* 12 species rates (including HD) */
  double *HDlte;
  double *HDlow;

  /* CIE cooling */
  double *cieco;

  /*******************************
   * dust chemistry/cooling data *
   *******************************/

  // Photo-electric heating (code units)
  double gammah;

  // Electron recombination onto dust grains
  double *regr;

  // Heating of dust by interstellar radiation field
  double gamma_isrf;
  // for arbitrary grain size distribution
  double gamma_isrf2;

  /* Gas/grain energy transfer. */
  double *gas_grain;
  // for arbitrary grain size distribution
  double *gas_grain2;

//#ifdef GRACKLE_MD
  /* CIE cooling rate (Yoshida et al. 2006) */
  double *cieY06;

  /* H2 and HD cooling rates (collision with HI; Hollenbach & McKee 1979) */
  int    *LH2_N, LH2_Size;
  double *LH2_D, *LH2_T, *LH2_H, LH2_dD, LH2_dT, LH2_dH, *LH2_L;
  int    *LHD_N, LHD_Size;
  double *LHD_D, *LHD_T, *LHD_H, LHD_dD, LHD_dT, LHD_dH, *LHD_L;

  /* Fine-structure cooling rates (collision with HI; Maio et al. 2007) */
  int    *LCI_N, LCI_Size;
  double *LCI_D, *LCI_T, *LCI_H, LCI_dD, LCI_dT, LCI_dH, *LCI_L;
  int    *LCII_N, LCII_Size;
  double *LCII_D, *LCII_T, *LCII_H, LCII_dD, LCII_dT, LCII_dH, *LCII_L;
  int    *LOI_N, LOI_Size;
  double *LOI_D, *LOI_T, *LOI_H, LOI_dD, LOI_dT, LOI_dH, *LOI_L;

  /* metal molecular cooling rates (collision with H2I; UMIST table) */
  int    *LCO_N, LCO_Size;
  double *LCO_D, *LCO_T, *LCO_H, LCO_dD, LCO_dT, LCO_dH, *LCO_L;
  int    *LOH_N, LOH_Size;
  double *LOH_D, *LOH_T, *LOH_H, LOH_dD, LOH_dT, LOH_dH, *LOH_L;
  int    *LH2O_N, LH2O_Size;
  double *LH2O_D, *LH2O_T, *LH2O_H, LH2O_dD, LH2O_dT, LH2O_dH, *LH2O_L;

  /* primordial opacity */
  int    *alphap_N, alphap_Size;
  double *alphap_D, *alphap_T, alphap_dD, alphap_dT;
  double *alphap_Data;

  /* dust opacity */
  int    *grain_N, grain_Size;
  double *grain_D, *grain_T, grain_dD, grain_dT;
  double *Hgrain, *Tgrain, *Ograin, *Lgrain;

  /* Dust model */
  int    *gr_N, gr_Size;
  double gr_dT, *gr_Td;

  /* Local ISM (Pollack et al. 1994) */
//double loc_dfFeM    , loc_dfMg2SiO4, loc_dfMgSiO3 , loc_dfFeS    
//     , loc_dfreforg , loc_dfvolorg , loc_dfH2Oice ;
//double *loc_fdFeM    , *loc_fdMg2SiO4, *loc_fdMgSiO3 , *loc_fdFeS    
//     , *loc_fdreforg , *loc_fdvolorg , *loc_fdH2Oice ;
  double *loc_kpFeM    , *loc_kpMg2SiO4, *loc_kpMgSiO3 , *loc_kpFeS    
       , *loc_kpreforg , *loc_kpvolorg , *loc_kpH2Oice ;


  /* Pop III dust model */
//double C30_dfSiM    , C30_dfFeM    , C30_dfMg2SiO4, C30_dfMgSiO3
//     , C30_dfAC     , C30_dfSiO2D  , C30_dfMgO    , C30_dfFeS    , C30_dfAl2O3;
//double *C30_fdSiM    , *C30_fdFeM    , *C30_fdMg2SiO4, *C30_fdMgSiO3
//     , *C30_fdAC     , *C30_fdSiO2D  , *C30_fdMgO    , *C30_fdFeS    , *C30_fdAl2O3;
  double *C30_kpSiM    , *C30_kpFeM    , *C30_kpMg2SiO4, *C30_kpMgSiO3
       , *C30_kpAC     , *C30_kpSiO2D  , *C30_kpMgO    , *C30_kpFeS    , *C30_kpAl2O3;

  /* faint SN 13 Msun */
//double F13_dfFeM    , F13_dfMg2SiO4, F13_dfMgSiO3 , F13_dfFe3O4  
//     , F13_dfAC     , F13_dfSiO2D  , F13_dfAl2O3;
//double *F13_fdFeM    , *F13_fdMg2SiO4, *F13_fdMgSiO3 , *F13_fdFe3O4  
//     , *F13_fdAC     , *F13_fdSiO2D  , *F13_fdAl2O3;
  double *F13_kpFeM    , *F13_kpMg2SiO4, *F13_kpMgSiO3 , *F13_kpFe3O4  
       , *F13_kpAC     , *F13_kpSiO2D  , *F13_kpAl2O3;
//#endif

  /* UV background data */
  UVBtable UVbackground_table;

  /* Primordial cooling table */
  cloudy_data cloudy_primordial;

  /* Metal cooling table */
  cloudy_data cloudy_metal;

  /* New/old cloudy data flag */
  int cloudy_data_new;

} chemistry_data_storage;

/**************************
 *** photo-rate storage ***
 **************************/

typedef struct
{

    /* Radiative rates for 6-species. */
    double k24;
    double k25;
    double k26;
    /* Radiative rates for 9-species. */
    double k27;
    double k28;
    double k29;
    double k30;
    double k31;

    double piHI;
    double piHeI;
    double piHeII;

    // spectrum averaged absorption cross sections
    double crsHI;
    double crsHeI;
    double crsHeII;

    // X-ray compton heating coefficient
    double comp_xray;
    // X-ray compton heating temperature (K)
    double temp_xray;

} photo_rate_storage;

#endif
