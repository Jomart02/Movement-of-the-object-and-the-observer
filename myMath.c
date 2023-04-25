#include "myMath.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

int sign( double x ){
    if ( x >= 0 )
       return 1;
    return -1;
}

double sqr(double grad){
		 return grad*grad;
}

double rad(double grad){
		 return grad*M_PI/180;
}

double grad(double rad){
		 return rad*180/M_PI;
}

double priv2Pi(double rad){
		 while(rad>=2*M_PI) rad=rad-2*M_PI;
		 while(rad<0) rad=rad+2*M_PI;
		 //if(0<=rad && rad<2*M_PI) return rad;
		 return rad;
}

double privPi(double rad){
		 while(rad>M_PI) rad=rad-2*M_PI;
		 while(rad<=-M_PI) rad=rad+2*M_PI;
		 return rad;
}

double coordX(double dist, double angleRad){
		 return dist*sin(angleRad);
}

double coordY(double dist, double angleRad){
		 return dist*cos(angleRad);
}

double dist_1to2(double x1, double y1, double x2, double y2){
		 return sqrt(sqr(x2-x1)+sqr(y2-y1));
}

double angle_1to2(double x1, double y1, double x2, double y2){
		 
		 if(fabs(y2-y1)<=delta && (x2-x1)>=0) 
	         return M_PI/2;
		 else if(fabs(y2-y1)<=delta && (x2-x1)<0) 
		 		return M_PI*3/2;
		 else if(fabs(y2-y1)>delta && (y2-y1)>=0 && (x2-x1)>=0) 
		 		return atan((x2-x1)/(y2-y1));
		 else if(fabs(y2-y1)>delta && (y2-y1)>=0 && (x2-x1)<0) 
		 		return atan((x2-x1)/(y2-y1))+2*M_PI;
		 else if(fabs(y2-y1)>delta && (y2-y1)<0) 
		 		return atan((x2-x1)/(y2-y1))+M_PI;
		 return 0.0;
}

double uniformDistribution(double a, double b){
		 return a+rand()*(b-a)/RAND_MAX;
}

double normalDistribution(double m, double sigma){
		 double sum=0.0;
		 int i;
		 for(i=0; i<=11; i++)
			sum=sum+uniformDistribution(0,1);//-6;
		 return m+sigma*(sum-6);
}

double getMean(double *mas, unsigned int sizeMas){
		 double sum=0.0;
		 int i;
		 for(i=0; i<sizeMas; i++)
			sum=sum+mas[i];
		 return sum/sizeMas;
}

double getVariance(double *mas, unsigned int sizeMas){
		 double sum=0.0;
		 int i;
		 double mean = getMean(mas, sizeMas);
		 for(i=0; i<sizeMas; i++)
			sum=sum+sqr(mas[i]);//sum=sum+sqr(mas[i]-mean);
		 return sum/sizeMas-sqr(mean);
}

double findDetMatrix_3x3(Matrix3x3 a){
	return a[0][0]*a[1][1]*a[2][2] + a[0][1]*a[1][2]*a[2][0] + a[0][2]*a[1][0]*a[2][1]  -a[0][2]*a[1][1]*a[2][0]-a[0][1]*a[1][0]*a[2][2]-a[0][0]*a[1][2]*a[2][1];
}


int findInvMatrix_3x3(Matrix3x3 a, Matrix3x3 *inv){
	int i,j;
	double det = findDetMatrix_3x3(a);
	if(!det) return -1;
	double union_a[3][3] = {{(a[1][1]*a[2][2]-a[1][2]*a[2][1]), -1*(a[1][0]*a[2][2]-a[1][2]*a[2][0]), (a[1][0]*a[2][1]-a[1][1]*a[2][0])}, {-1*(a[0][1]*a[2][2]-a[0][2]*a[2][1]), (a[0][0]*a[2][2]-a[0][2]*a[2][0]), -1*(a[0][0]*a[1][2]-a[0][2]*a[1][0])}, {(a[0][1]*a[1][2]-a[0][2]*a[1][1]), -1*(a[0][0]*a[2][1]-a[0][1]*a[2][0]), (a[0][0]*a[1][1]-a[0][1]*a[1][0])}};
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			(*inv)[i][j] = union_a[i][j]*1/det;
		}
    }
	return 0;
}

void multiplyMatrices_3x3_3x1(Matrix3x3 a, Matrix3x1 b, Matrix3x1 *res){
	int i;
	for(i=0;i<3;i++) (*res)[i] = 0; //zeros
	for(i=0;i<3;i++)
		(*res)[i] = (*res)[i] + a[i][0]*b[0] + a[i][1]*b[1] + a[i][2]*b[2];
}

int findTimesToMan(TrajPart *trajPartMas, unsigned int sizeMas){
	int code = 0;
	int i;
	for(i=0;i<sizeMas;i++){
		double deltaK = trajPartMas[i].headingEnd - trajPartMas[i].headingStart;
		deltaK = privPi( trajPartMas[i].headingEnd - trajPartMas[i].headingStart );
		double Rc = trajPartMas[i].radiusCirc;
		if(fabs(deltaK)>=delta && Rc>=delta){
			double tk=fabs((deltaK*Rc)/(trajPartMas[i].speed));
			double tu=tk;
			trajPartMas[i].timeTrajPart = tu;
		} else{
			if(!(fabs(deltaK)<delta && Rc<delta)){
				code--;
				return code;
			}
		}
	}
	return code;
}

PosAndVelocity findPos_manH(double time, Point2D posStart, TrajPart *trajPartMas, unsigned int sizeMas){
	PosAndVelocity res;
	res.x = posStart.x;
	res.y = posStart.y;
	res.speed = 0;
	res.heading = 0;
	int timeSum = 0;
	int i;
	for(i=0;i<sizeMas;i++){
		int timeLeft = 0;
		double tu = trajPartMas[i].timeTrajPart;
		if(timeSum+tu <= time) timeLeft = tu;
		else timeLeft = time-timeSum;
		double deltaK = privPi( trajPartMas[i].headingEnd - trajPartMas[i].headingStart );
		double Rc = trajPartMas[i].radiusCirc;
		if(fabs(deltaK)<delta && Rc<delta){
			res.x = res.x + trajPartMas[i].speed*timeLeft*sin(trajPartMas[i].headingStart);
			res.y = res.y + trajPartMas[i].speed*timeLeft*cos(trajPartMas[i].headingStart);
			res.speed = trajPartMas[i].speed;
			res.heading = trajPartMas[i].headingStart;
		} else {
			if(fabs(deltaK)>=delta && Rc>=delta){
				double psi = priv2Pi(trajPartMas[i].headingStart+(sign(deltaK)*trajPartMas[i].speed*timeLeft/Rc));
				res.x = res.x + Rc * sign(deltaK)*(cos(trajPartMas[i].headingStart)-cos(psi));
				res.y = res.y + Rc * sign(deltaK)*(sin(psi)-sin(trajPartMas[i].headingStart));
				res.speed = trajPartMas[i].speed;
				res.heading = trajPartMas[i].headingStart;
			} else{
				perror("findPos_manH error");
				return res;
			}
		}
		timeSum = timeSum + timeLeft;
	}
	return res;
}

