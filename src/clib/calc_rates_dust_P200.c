#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "grackle_macros.h"
#include "grackle_types.h"
#include "grackle_chemistry_data.h"
#include "phys_constants.h"
#ifdef _OPENMP
#include <omp.h>
#endif

#define tiny 1.0e-20
#define huge 1.0e+20
#define tevk 1.1605e+4

extern int grackle_verbose;

int calc_rates_dust_P200(chemistry_data *my_chemistry, chemistry_data_storage *my_rates)
{

  int NTd, Nmom;
  double Td0;
  double dTd;
  int iTd, imom, itab;

  my_chemistry->P200_r0SiM      = malloc(3 * sizeof(double));
  my_chemistry->P200_r0FeM      = malloc(3 * sizeof(double));
  my_chemistry->P200_r0Mg2SiO4  = malloc(3 * sizeof(double));
  my_chemistry->P200_r0AC       = malloc(3 * sizeof(double));
  my_chemistry->P200_r0SiO2D    = malloc(3 * sizeof(double));
  my_chemistry->P200_r0MgO      = malloc(3 * sizeof(double));

  my_chemistry->P200_XC  =   3.65050e-02;
  my_chemistry->P200_XO  =   4.88552e-01;
  my_chemistry->P200_XMg =   2.69665e-02;
  my_chemistry->P200_XAl =   1.36872e-04;
  my_chemistry->P200_XSi =   1.87324e-01;
  my_chemistry->P200_XS  =   1.15582e-01;
  my_chemistry->P200_XFe =   6.79294e-02;

  my_chemistry->P200_fC  =   3.64677e-02;
  my_chemistry->P200_fO  =   4.88307e-01;
  my_chemistry->P200_fMg =   2.69665e-02;
  my_chemistry->P200_fAl =   1.36872e-04;
  my_chemistry->P200_fSi =   1.87051e-01;
  my_chemistry->P200_fS  =   1.15582e-01;
  my_chemistry->P200_fFe =   6.75026e-02;

  my_chemistry->P200_fSiM     =   5.90622e-05;
  my_chemistry->P200_fFeM     =   4.26809e-04;
  my_chemistry->P200_fMg2SiO4 =   4.08246e-15;
  my_chemistry->P200_fAC      =   3.72287e-05;
  my_chemistry->P200_fSiO2D   =   4.59330e-04;
  my_chemistry->P200_fMgO     =   5.38389e-09;

  my_chemistry->P200_r0SiM     [0] =   8.86269e-07;
  my_chemistry->P200_r0FeM     [0] =   2.02272e-06;
  my_chemistry->P200_r0Mg2SiO4 [0] =   1.42189e-05;
  my_chemistry->P200_r0AC      [0] =   7.46096e-07;
  my_chemistry->P200_r0SiO2D   [0] =   1.73471e-05;
  my_chemistry->P200_r0MgO     [0] =   1.26307e-05;

  my_chemistry->P200_r0SiM     [1] =   1.71166e-12;
  my_chemistry->P200_r0FeM     [1] =   5.41308e-12;
  my_chemistry->P200_r0Mg2SiO4 [1] =   2.04834e-10;
  my_chemistry->P200_r0AC      [1] =   9.32091e-13;
  my_chemistry->P200_r0SiO2D   [1] =   3.08556e-10;
  my_chemistry->P200_r0MgO     [1] =   1.59673e-10;

  my_chemistry->P200_r0SiM     [2] =   5.46663e-18;
  my_chemistry->P200_r0FeM     [2] =   2.06248e-17;
  my_chemistry->P200_r0Mg2SiO4 [2] =   2.98805e-15;
  my_chemistry->P200_r0AC      [2] =   1.99556e-18;
  my_chemistry->P200_r0SiO2D   [2] =   5.66409e-15;
  my_chemistry->P200_r0MgO     [2] =   2.02075e-15;

  NTd =            35;
  Td0 =     0.0000000;
  dTd =     0.1000000;
 Nmom =             4;

  my_rates->P200_kpSiM      = malloc(NTd * Nmom * sizeof(double));
  my_rates->P200_kpFeM      = malloc(NTd * Nmom * sizeof(double));
  my_rates->P200_kpMg2SiO4  = malloc(NTd * Nmom * sizeof(double));
  my_rates->P200_kpAC       = malloc(NTd * Nmom * sizeof(double));
  my_rates->P200_kpSiO2D    = malloc(NTd * Nmom * sizeof(double));
  my_rates->P200_kpMgO      = malloc(NTd * Nmom * sizeof(double));

  double P200_kpSiM[] = 
  {  1.54645e-01,   1.37048e-07,   2.64662e-13,   8.45209e-19,
     1.94685e-01,   1.72534e-07,   3.33193e-13,   1.06408e-18,
     2.45092e-01,   2.17207e-07,   4.19469e-13,   1.33961e-18,
     3.08551e-01,   2.73447e-07,   5.28084e-13,   1.68649e-18,
     3.88446e-01,   3.44254e-07,   6.64830e-13,   2.12322e-18,
     4.89028e-01,   4.33396e-07,   8.36986e-13,   2.67303e-18,
     6.15654e-01,   5.45619e-07,   1.05372e-12,   3.36522e-18,
     7.75056e-01,   6.86892e-07,   1.32656e-12,   4.23661e-18,
     9.75414e-01,   8.64464e-07,   1.66951e-12,   5.33191e-18,
     1.22498e+00,   1.08564e-06,   2.09668e-12,   6.69620e-18,
     1.52119e+00,   1.34817e-06,   2.60370e-12,   8.31550e-18,
     1.83682e+00,   1.62792e-06,   3.14401e-12,   1.00412e-17,
     2.15660e+00,   1.91133e-06,   3.69138e-12,   1.17894e-17,
     2.55494e+00,   2.26439e-06,   4.37331e-12,   1.39675e-17,
     3.22768e+00,   2.86067e-06,   5.52501e-12,   1.76460e-17,
     4.33077e+00,   3.83839e-06,   7.41349e-12,   2.36779e-17,
     5.81399e+00,   5.15308e-06,   9.95292e-12,   3.17892e-17,
     7.48107e+00,   6.63084e-06,   1.28076e-11,   4.09082e-17,
     9.20965e+00,   8.16336e-06,   1.57686e-11,   5.03682e-17,
     1.11868e+01,   9.91669e-06,   1.91573e-11,   6.11981e-17,
     1.39824e+01,   1.23969e-05,   2.39531e-11,   7.65315e-17,
     1.78531e+01,   1.58317e-05,   3.05972e-11,   9.77803e-17,
     2.17179e+01,   1.92624e-05,   3.72355e-11,   1.19020e-16,
     2.37018e+01,   2.10255e-05,   4.06526e-11,   1.29977e-16,
     2.29438e+01,   2.03578e-05,   3.93739e-11,   1.25940e-16,
     2.02577e+01,   1.79829e-05,   3.48015e-11,   1.11389e-16,
     1.70972e+01,   1.51927e-05,   2.94374e-11,   9.43240e-17,
     1.43876e+01,   1.28090e-05,   2.48736e-11,   7.98414e-17,
     1.23927e+01,   1.10758e-05,   2.16034e-11,   6.95714e-17,
     1.14807e+01,   1.03984e-05,   2.05890e-11,   6.70125e-17,
     1.34941e+01,   1.30878e-05,   2.78918e-11,   9.54730e-17,
     2.46530e+01,   2.87907e-05,   7.29927e-11,   2.79411e-16,
     6.22628e+01,   8.83029e-05,   2.60128e-10,   1.09021e-15,
     1.73608e+02,   2.73721e-04,   8.65552e-10,   3.78030e-15,
     4.81453e+02,   7.67244e-04,   2.43830e-09,   1.06714e-14  };

  double P200_kpFeM[] = 
  {  9.09085e-04,   3.41941e-09,   1.80920e-14,   1.27369e-19,
     1.61039e-03,   6.04845e-09,   3.18823e-14,   2.22622e-19,
     2.49320e-03,   9.35673e-09,   4.92187e-14,   3.42113e-19,
     3.60452e-03,   1.35207e-08,   7.10297e-14,   4.92299e-19,
     5.89215e-03,   2.20677e-08,   1.15535e-13,   7.95087e-19,
     9.02912e-03,   3.37737e-08,   1.76355e-13,   1.20713e-18,
     1.39130e-02,   5.19580e-08,   2.70494e-13,   1.84076e-18,
     2.14719e-02,   8.00206e-08,   4.15192e-13,   2.80850e-18,
     3.30912e-02,   1.23012e-07,   6.35936e-13,   4.27570e-18,
     5.03917e-02,   1.86799e-07,   9.62098e-13,   6.43127e-18,
     7.63291e-02,   2.81960e-07,   1.44615e-12,   9.61004e-18,
     1.14179e-01,   4.19929e-07,   2.14346e-12,   1.41576e-17,
     1.67303e-01,   6.12055e-07,   3.10728e-12,   2.03974e-17,
     2.39689e-01,   8.71248e-07,   4.39580e-12,   2.86715e-17,
     3.35470e-01,   1.21013e-06,   6.06256e-12,   3.92787e-17,
     4.59119e-01,   1.64148e-06,   8.15789e-12,   5.24812e-17,
     6.15407e-01,   2.17768e-06,   1.07246e-11,   6.84719e-17,
     8.10332e-01,   2.83301e-06,   1.38055e-11,   8.74075e-17,
     1.05438e+00,   3.63322e-06,   1.74835e-11,   1.09639e-16,
     1.37021e+00,   4.63773e-06,   2.19726e-11,   1.36212e-16,
     1.80496e+00,   5.97282e-06,   2.77433e-11,   1.69529e-16,
     2.45118e+00,   7.88356e-06,   3.57016e-11,   2.14206e-16,
     3.48432e+00,   1.08228e-05,   4.74799e-11,   2.78412e-16,
     5.23381e+00,   1.56143e-05,   6.59474e-11,   3.76121e-16,
     8.31585e+00,   2.37506e-05,   9.61230e-11,   5.31044e-16,
     1.38802e+01,   3.79407e-05,   1.46823e-10,   7.83600e-16,
     2.40529e+01,   6.30826e-05,   2.33568e-10,   1.20322e-15,
     4.26908e+01,   1.07918e-04,   3.83527e-10,   1.90929e-15,
     7.65687e+01,   1.87651e-04,   6.43418e-10,   3.10502e-15,
     1.37077e+02,   3.27739e-04,   1.09108e-09,   5.12746e-15,
     2.42517e+02,   5.69117e-04,   1.85185e-09,   8.51948e-15,
     4.21112e+02,   9.75067e-04,   3.11997e-09,   1.41236e-14,
     7.14738e+02,   1.63904e-03,   5.18038e-09,   2.31656e-14,
     1.18235e+03,   2.68818e-03,   8.40281e-09,   3.71602e-14,
     1.90342e+03,   4.27908e-03,   1.31829e-08,   5.74720e-14  };

  double P200_kpMg2SiO4[] = 
  {  1.05240e-01,   1.49640e-06,   2.15567e-11,   3.14463e-16,
     1.32588e-01,   1.88525e-06,   2.71584e-11,   3.96179e-16,
     1.67016e-01,   2.37479e-06,   3.42106e-11,   4.99054e-16,
     2.10360e-01,   2.99108e-06,   4.30887e-11,   6.28566e-16,
     2.71889e-01,   3.86597e-06,   5.56922e-11,   8.12421e-16,
     3.55700e-01,   5.05766e-06,   7.28594e-11,   1.06285e-15,
     4.84944e-01,   6.89538e-06,   9.93331e-11,   1.44904e-15,
     6.99796e-01,   9.95035e-06,   1.43342e-10,   2.09104e-15,
     1.05867e+00,   1.50532e-05,   2.16853e-10,   3.16340e-15,
     1.62919e+00,   2.31655e-05,   3.33717e-10,   4.86818e-15,
     2.54303e+00,   3.61594e-05,   5.20906e-10,   7.59887e-15,
     3.96603e+00,   5.63932e-05,   8.12393e-10,   1.18511e-14,
     6.10897e+00,   8.68643e-05,   1.25136e-09,   1.82548e-14,
     9.29384e+00,   1.32151e-04,   1.90378e-09,   2.77724e-14,
     1.39407e+01,   1.98229e-04,   2.85574e-09,   4.16600e-14,
     2.05705e+01,   2.92507e-04,   4.21400e-09,   6.14759e-14,
     3.01423e+01,   4.28630e-04,   6.17529e-09,   9.00909e-14,
     4.57104e+01,   6.50055e-04,   9.36595e-09,   1.36648e-13,
     7.53064e+01,   1.07104e-03,   1.54328e-08,   2.25181e-13,
     1.30815e+02,   1.86065e-03,   2.68126e-08,   3.91253e-13,
     2.17127e+02,   3.08849e-03,   4.45083e-08,   6.49502e-13,
     3.23880e+02,   4.60717e-03,   6.63972e-08,   9.68963e-13,
     4.35662e+02,   6.19759e-03,   8.93224e-08,   1.30358e-12,
     5.38932e+02,   7.66706e-03,   1.10506e-07,   1.61282e-12,
     6.09467e+02,   8.67078e-03,   1.24977e-07,   1.82406e-12,
     6.16707e+02,   8.77390e-03,   1.26464e-07,   1.84580e-12,
     5.52479e+02,   7.86016e-03,   1.13294e-07,   1.65358e-12,
     4.40975e+02,   6.27379e-03,   9.04293e-08,   1.31986e-12,
     3.18791e+02,   4.53552e-03,   6.53747e-08,   9.54183e-13,
     2.12803e+02,   3.02766e-03,   4.36414e-08,   6.36986e-13,
     1.33761e+02,   1.90318e-03,   2.74344e-08,   4.00448e-13,
     8.11305e+01,   1.15453e-03,   1.66451e-08,   2.42996e-13,
     4.95598e+01,   7.05594e-04,   1.01773e-08,   1.48640e-13,
     3.25906e+01,   4.64465e-04,   6.70585e-09,   9.80294e-14,
     2.45153e+01,   3.49814e-04,   5.05664e-09,   7.40047e-14  };

  double P200_kpAC[] = 
  {  3.27960e-01,   2.44690e-07,   3.05689e-13,   6.54462e-19,
     4.38752e-01,   3.27351e-07,   4.08957e-13,   8.75569e-19,
     5.78230e-01,   4.31415e-07,   5.38965e-13,   1.15393e-18,
     7.53823e-01,   5.62424e-07,   7.02635e-13,   1.50436e-18,
     1.04013e+00,   7.76039e-07,   9.69511e-13,   2.07581e-18,
     1.41735e+00,   1.05749e-06,   1.32113e-12,   2.82873e-18,
     1.95292e+00,   1.45707e-06,   1.82034e-12,   3.89771e-18,
     2.71531e+00,   2.02589e-06,   2.53098e-12,   5.41951e-18,
     3.79675e+00,   2.83276e-06,   3.53905e-12,   7.57851e-18,
     5.29742e+00,   3.95242e-06,   4.93793e-12,   1.05749e-17,
     7.37833e+00,   5.50501e-06,   6.87773e-12,   1.47304e-17,
     1.02168e+01,   7.62282e-06,   9.52385e-12,   2.04006e-17,
     1.40421e+01,   1.04770e-05,   1.30901e-11,   2.80446e-17,
     1.92021e+01,   1.43270e-05,   1.79012e-11,   3.83618e-17,
     2.61616e+01,   1.95199e-05,   2.43907e-11,   5.22874e-17,
     3.55307e+01,   2.65108e-05,   3.31285e-11,   7.10543e-17,
     4.81611e+01,   3.59357e-05,   4.49107e-11,   9.63939e-17,
     6.53170e+01,   4.87382e-05,   6.09196e-11,   1.30888e-16,
     8.87668e+01,   6.62390e-05,   8.28118e-11,   1.78181e-16,
     1.20705e+02,   9.00772e-05,   1.12647e-10,   2.42873e-16,
     1.63621e+02,   1.22115e-04,   1.52778e-10,   3.30388e-16,
     2.20575e+02,   1.64642e-04,   2.06114e-10,   4.47715e-16,
     2.96104e+02,   2.21060e-04,   2.76991e-10,   6.05473e-16,
     3.97026e+02,   2.96479e-04,   3.71917e-10,   8.19263e-16,
     5.31526e+02,   3.97049e-04,   4.98696e-10,   1.10695e-15,
     7.06983e+02,   5.28345e-04,   6.64405e-10,   1.48343e-15,
     9.30949e+02,   6.96139e-04,   8.76417e-10,   1.96294e-15,
     1.21659e+03,   9.10536e-04,   1.14776e-09,   2.57160e-15,
     1.58765e+03,   1.18982e-03,   1.50225e-09,   3.36001e-15,
     2.08069e+03,   1.56242e-03,   1.97748e-09,   4.41103e-15,
     2.74685e+03,   2.06876e-03,   2.62823e-09,   5.84923e-15,
     3.65712e+03,   2.76611e-03,   3.53431e-09,   7.86205e-15,
     4.91402e+03,   3.73838e-03,   4.81486e-09,   1.07337e-14,
     6.67206e+03,   5.11081e-03,   6.64539e-09,   1.48739e-14,
     9.17096e+03,   7.06881e-03,   9.26820e-09,   2.07940e-14  };

  double P200_kpSiO2D[] = 
  {  7.60136e-02,   1.31860e-06,   2.34539e-11,   4.30529e-16,
     9.06981e-02,   1.57333e-06,   2.79848e-11,   5.13702e-16,
     1.09185e-01,   1.89402e-06,   3.36890e-11,   6.18411e-16,
     1.32458e-01,   2.29774e-06,   4.08700e-11,   7.50232e-16,
     1.58888e-01,   2.75623e-06,   4.90252e-11,   8.99935e-16,
     1.91549e-01,   3.32281e-06,   5.91032e-11,   1.08494e-15,
     2.30478e-01,   3.99813e-06,   7.11152e-11,   1.30544e-15,
     2.76790e-01,   4.80151e-06,   8.54053e-11,   1.56776e-15,
     3.33085e-01,   5.77806e-06,   1.02776e-10,   1.88663e-15,
     4.05362e-01,   7.03188e-06,   1.25078e-10,   2.29603e-15,
     5.08238e-01,   8.81651e-06,   1.56822e-10,   2.87877e-15,
     6.72650e-01,   1.16686e-05,   2.07555e-10,   3.81010e-15,
     9.48976e-01,   1.64623e-05,   2.92824e-10,   5.37545e-15,
     1.41897e+00,   2.46158e-05,   4.37862e-10,   8.03808e-15,
     2.19768e+00,   3.81252e-05,   6.78181e-10,   1.24501e-14,
     3.47459e+00,   6.02792e-05,   1.07231e-09,   1.96868e-14,
     5.79486e+00,   1.00542e-04,   1.78877e-09,   3.28453e-14,
     1.18370e+01,   2.05418e-04,   3.65563e-09,   6.71473e-14,
     3.21108e+01,   5.57348e-04,   9.92083e-09,   1.82279e-13,
     8.81851e+01,   1.53068e-03,   2.72473e-08,   5.00649e-13,
     1.95201e+02,   3.38815e-03,   6.03099e-08,   1.10811e-12,
     3.40883e+02,   5.91645e-03,   1.05307e-07,   1.93471e-12,
     5.10268e+02,   8.85442e-03,   1.57557e-07,   2.89365e-12,
     7.17917e+02,   1.24511e-02,   2.21410e-07,   4.06297e-12,
     9.57120e+02,   1.65879e-02,   2.94709e-07,   5.40198e-12,
     1.14369e+03,   1.98088e-02,   3.51649e-07,   6.43917e-12,
     1.17995e+03,   2.04271e-02,   3.62410e-07,   6.63127e-12,
     1.05086e+03,   1.81866e-02,   3.22531e-07,   5.89860e-12,
     8.23986e+02,   1.42573e-02,   2.52780e-07,   4.62145e-12,
     5.83014e+02,   1.00864e-02,   1.78801e-07,   3.26825e-12,
     3.80801e+02,   6.58750e-03,   1.16763e-07,   2.13399e-12,
     2.33954e+02,   4.04697e-03,   7.17275e-08,   1.31079e-12,
     1.37203e+02,   2.37328e-03,   4.20617e-08,   7.68622e-13,
     7.77017e+01,   1.34403e-03,   2.38199e-08,   4.35268e-13,
     4.28856e+01,   7.41814e-04,   1.31471e-08,   2.40245e-13  };

  double P200_kpMgO[] = 
  {  2.25374e-04,   2.84663e-09,   3.59861e-14,   4.55424e-19,
     4.04950e-04,   5.11481e-09,   6.46597e-14,   8.18303e-19,
     6.31024e-04,   7.97028e-09,   1.00758e-13,   1.27514e-18,
     9.15633e-04,   1.15651e-08,   1.46202e-13,   1.85026e-18,
     1.52197e-03,   1.92235e-08,   2.43017e-13,   3.07552e-18,
     2.37410e-03,   2.99866e-08,   3.79080e-13,   4.79746e-18,
     3.77219e-03,   4.76455e-08,   6.02318e-13,   7.62266e-18,
     6.14378e-03,   7.76004e-08,   9.80998e-13,   1.24151e-17,
     1.01916e-02,   1.28728e-07,   1.62733e-12,   2.05948e-17,
     1.68921e-02,   2.13360e-07,   2.69722e-12,   3.41348e-17,
     2.96213e-02,   3.74139e-07,   4.72974e-12,   5.98574e-17,
     6.10970e-02,   7.71701e-07,   9.75560e-12,   1.23463e-16,
     1.43533e-01,   1.81293e-06,   2.29185e-11,   2.90047e-16,
     3.27806e-01,   4.14044e-06,   5.23423e-11,   6.62424e-16,
     6.40565e-01,   8.09084e-06,   1.02282e-10,   1.29445e-15,
     1.05534e+00,   1.33298e-05,   1.68513e-10,   2.13267e-15,
     1.58348e+00,   2.00015e-05,   2.52868e-10,   3.20044e-15,
     3.07310e+00,   3.88206e-05,   4.90841e-10,   6.21320e-15,
     1.37089e+01,   1.73169e-04,   2.18940e-09,   2.77122e-14,
     7.13521e+01,   9.01235e-04,   1.13932e-08,   1.44189e-13,
     2.52035e+02,   3.18325e-03,   4.02394e-08,   5.09217e-13,
     5.88759e+02,   7.43595e-03,   9.39947e-08,   1.18943e-12,
     9.70270e+02,   1.22542e-02,   1.54897e-07,   1.96005e-12,
     1.20866e+03,   1.52648e-02,   1.92951e-07,   2.44153e-12,
     1.20927e+03,   1.52725e-02,   1.93046e-07,   2.44272e-12,
     1.02223e+03,   1.29102e-02,   1.63185e-07,   2.06485e-12,
     7.60460e+02,   9.60416e-03,   1.21396e-07,   1.53608e-12,
     5.14029e+02,   6.49187e-03,   8.20570e-08,   1.03830e-12,
     3.23438e+02,   4.08481e-03,   5.16318e-08,   6.53316e-13,
     1.92889e+02,   2.43607e-03,   3.07917e-08,   3.89618e-13,
     1.10502e+02,   1.39557e-03,   1.76399e-08,   2.23204e-13,
     6.14046e+01,   7.75500e-04,   9.80225e-09,   1.24031e-13,
     3.33434e+01,   4.21106e-04,   5.32274e-09,   6.73503e-14,
     1.77894e+01,   2.24668e-04,   2.83978e-09,   3.59327e-14,
     9.36317e+00,   1.18251e-04,   1.49468e-09,   1.89126e-14  };


  itab = 0;
  for(imom = 0; imom < Nmom; imom++) {
    for(iTd = 0; iTd < NTd; iTd++) {
      my_rates->P200_kpSiM     [itab] = P200_kpSiM     [itab];
      my_rates->P200_kpFeM     [itab] = P200_kpFeM     [itab];
      my_rates->P200_kpMg2SiO4 [itab] = P200_kpMg2SiO4 [itab];
      my_rates->P200_kpAC      [itab] = P200_kpAC      [itab];
      my_rates->P200_kpSiO2D   [itab] = P200_kpSiO2D   [itab];
      my_rates->P200_kpMgO     [itab] = P200_kpMgO     [itab];
      itab++;
    }
  }

  return SUCCESS;
}
