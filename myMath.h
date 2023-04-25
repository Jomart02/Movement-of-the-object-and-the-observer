#ifndef MYMATH_H
#define MYMATH_H
#define delta 10e-5

#if defined( BUILD_LIB )
# define EXPORT __declspec (dllexport)
#else
# if defined( BUILD_TEST )
#  define EXPORT 
# else
#  define EXPORT __declspec (dllimport)
# endif
#endif

 EXPORT int sign( double x );

 EXPORT double sqr(double x);
 
 EXPORT double rad (double grad);
 
 EXPORT double grad(double rad);
 
 EXPORT double priv2Pi(double rad);
 
 EXPORT double privPi(double rad);
 
 EXPORT double coordX( double dist, double angleRad);
 
 EXPORT double coordY(double dist, double angleRad);
 
 EXPORT double dist_1to2(double x1, double y1, double x2, double y2);
 
 EXPORT double angle_1to2( double x1 , double y1, double x2, double y2);
 
 EXPORT double uniformDistribution( double a, double b);
 
 EXPORT double normalDistribution (double m ,double sigma);
 
 EXPORT double getMean (double *mas, unsigned int sizeMas);
 
 EXPORT double getVariance(double *mas, unsigned int sizeMas);
 
 EXPORT void V_ozen_X_Y(double *D_mas_2 , double *P_mas_2,double *D_mas,double *P_mas,double *V_b,double *K_b,double *V_oz_X,double *V_oz_Y,double *t);
 
 EXPORT double V_1_ozen(double *V_oz_X,double *V_oz_Y);
 
 EXPORT void Sigma_dx_dy( double*Pel_mass, double*Di_mass,double*sigma0,double*sigman, double*sigma_dx1,double*sigma_dy1 );

 EXPORT void Sigma_v1x_v1y(double*sigma_dx1,double*sigma_dy1,double*sigma_v1x,double*sigma_v1y,double*sigma_dx2,double*sigma_dy2,double *t);
 
 EXPORT void K_v1x_v1y1(double*K1_dx_dy,double*K2_dx_dy,double*K_vx_vy,double *t);
 
 EXPORT void K_dx_dy1( double*Pel_mass, double*Di_mass,double*sigma0,double*sigman, double*K_dx_dy );
 
 EXPORT void sigma_K1_V1(double*V_oz_X,double*V_oz_y,double*V_1,double*sigma_v1x,double*sigma_v1y,double*K_vx_vy,double*sigma_K1,double*sigma_V1);
 
typedef double Matrix3x3[3][3];
typedef double Matrix3x1[3];
 
 EXPORT double findDetMatrix_3x3(Matrix3x3 a);//детерминант
 
 EXPORT int findYnvMatrix_3x3(Matrix3x3 a , Matrix3x3 *inv);//обратная матрица 
 //EXPORT int findYnvMatrix_3x3(Matrix3x3 a);
 EXPORT void multiplyMatrices_3x3_3x1(Matrix3x3 a, Matrix3x1 b, Matrix3x1 *res);// перемножение  3на3 на 3на1
 

 //EXPORT void СompletionMas(int counterIzm,double *BASE,double timeIzm ,double Va ,double Ka ,double xa_1 ,double ya_1 ,double Vb,double Kb ,double xb_1,double yb_1,double Dist,double Peleng ,double Dist_1 ,double Peleng_1 ,double VX ,double VY, double *Vism ,double *K );


typedef struct TPoint2D{
       double x;
       double y;
}Point2D;

typedef struct TTrajPart{
        double speed;
        double headingStart;
        double headingEnd;
        double radiusCirc;
        double timeTrajPart;        
}TrajPart;

typedef struct TPosAndVelocity{
       double x;// 
       double y;
       double heading;
       double speed;
}PosAndVelocity;

 EXPORT int findTimesToMan(TrajPart *trajpartMas,  unsigned int sizeMas);
 EXPORT PosAndVelocity findPos_manH(double time, Point2D posStart, TrajPart *trajPartMAs,  unsigned int sizeMas);




#endif //MYMATH_H
