#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
//Собственные библиотеки 
#include "myMath.h"


int main(int argc, char*argv[]){
    
    setlocale(LC_ALL, "Rus");
    setlocale(LC_NUMERIC, "English_USA");
    //=================================Начальное положение ===============================================
    Point2D StartPosition;
    StartPosition.x = 0;
    StartPosition.y = 0;
   
    srand(time(0));
   
   	double t_start=0;
	double t_end=8000;
	double dt=200;    
    int nt=(t_end/dt)+1;                                                          //шаг моделирования
	//=================================Массив значений по каждому участку================================= 
	TrajPart MovementPosition[7];
    
    
	//=================================Участок №1=================================
	MovementPosition[0].headingStart = rad(0);
	MovementPosition[0].headingEnd = MovementPosition[0].headingStart;
	MovementPosition[0].radiusCirc = 0;
	MovementPosition[0].speed = 3;
	MovementPosition[0].timeTrajPart = dt*2;
	//=================================Участок №2=================================
	MovementPosition[1].headingStart = MovementPosition[0].headingEnd;
	MovementPosition[1].headingEnd = priv2Pi(MovementPosition[0].headingEnd + rad(90));
	MovementPosition[1].radiusCirc = 500;
	MovementPosition[1].speed = MovementPosition[0].speed;
	MovementPosition[1].timeTrajPart = 261.799388;
	//=================================Участок №3=================================
	MovementPosition[2].headingStart = MovementPosition[1].headingEnd;
	MovementPosition[2].headingEnd = MovementPosition[2].headingStart;
	MovementPosition[2].radiusCirc = 0;
	MovementPosition[2].speed = MovementPosition[1].speed;
	MovementPosition[2].timeTrajPart = dt*3;
	//=================================Участок №4=================================
	MovementPosition[3].headingStart = MovementPosition[2].headingEnd;
	MovementPosition[3].headingEnd = priv2Pi(MovementPosition[2].headingEnd + rad(90));
	MovementPosition[3].radiusCirc = 500;
	MovementPosition[3].speed = MovementPosition[0].speed;;
	MovementPosition[3].timeTrajPart = 261.799388;
	//=================================Участок №5=================================
	MovementPosition[4].headingStart = MovementPosition[3].headingEnd;
	MovementPosition[4].headingEnd = MovementPosition[4].headingStart;
	MovementPosition[4].radiusCirc = 0;
	MovementPosition[4].speed = MovementPosition[0].speed;
	MovementPosition[4].timeTrajPart = dt*3;
	//=================================Участок №6=================================
	MovementPosition[5].headingStart = MovementPosition[4].headingEnd;
	MovementPosition[5].headingEnd = priv2Pi(MovementPosition[4].headingEnd - rad(90));
	MovementPosition[5].radiusCirc = 500;
	MovementPosition[5].speed = MovementPosition[0].speed;
	MovementPosition[5].timeTrajPart = 261.799388;
	//=================================Участок №7=================================
	MovementPosition[6].headingStart = MovementPosition[5].headingEnd;
	MovementPosition[6].headingEnd = MovementPosition[6].headingStart;
	MovementPosition[6].radiusCirc = 0;
	MovementPosition[6].speed = MovementPosition[0].speed;
	MovementPosition[6].timeTrajPart = dt*3;
/*	//=================================Участок №8=================================
	MovementPosition[7].headingStart =MovementPosition[6].headingEnd;
	MovementPosition[7].headingEnd = priv2Pi(MovementPosition[6].headingEnd + rad(90));
	MovementPosition[7].radiusCirc = 500;
	MovementPosition[7].speed = MovementPosition[0].speed;
	MovementPosition[7].timeTrajPart = 261.799388;
	//=================================Участок №9=================================
	MovementPosition[8].headingStart = MovementPosition[7].headingEnd;
	MovementPosition[8].headingEnd = MovementPosition[8].headingStart;
	MovementPosition[8].radiusCirc = 0;
	MovementPosition[8].speed = MovementPosition[0].speed;
	MovementPosition[8].timeTrajPart = 10000;
*/
	//============================================================================
    
    findTimesToMan( MovementPosition , 7 );
    //PosAndVelocity pv = findPos_manH(2070, StartPosition , MovementPosition ,7); // movement A

    //FILE *T = fopen("Time.txt","w");
    //FILE *H = fopen("Head.txt","w");
    //FILE *D = fopen("Distance.txt","w");
    //FILE *X = fopen("X.txt","w");
    //FILE *Y = fopen("Y.txt","w");
    //FILE *REZ = fopen("REZ.txt","w");
/*
	double sigma = 0;
	double k = 1;                                                               //pow(sigma,2);
	int sizeMas=9;
	double Vb = 5;
	double Kb = rad(90);
	unsigned int I=0;                                                           // solution status
	double time;
	*/
	int i=0,j=0,n=0 ,counter;
	
	double start_bearing = rad( 20 );
	double start_distance[5] = {20000 , 15000 , 10000 , 5000 , 2000};

    
    unsigned int calc, calc_count;
	calc_count = 100;
	double sko_v_static[calc_count][nt];
	double sko_h_static[calc_count][nt];
	double v_data[calc_count][nt];
	double h_data[calc_count][nt];
	double v_data_inverted[nt][calc_count];
	double h_data_inverted[nt][calc_count];
    double velocity=0;
    double heading = 0;
      
	for(n= 0; n<5 ; n++){
           
        double sigma = 0;
	    double k = 1;                                                               //pow(sigma,2);
	    int sizeMas=9;
	    double Vb = 5;
	    double Kb = rad(90);
	    unsigned int I=0;                                                           // solution status
	    double time;  
           
        
        counter=0;
        for(calc=0;calc<calc_count;calc++){//Для набора ско по испытаниям   
                                              
        FILE *REZ = fopen("C:/FilesBack/NPeleng/ResultFile/REZ.txt","a");
        FILE *T = fopen("C:/FilesBack/NPeleng/ResultFile/Time.txt","w");
        FILE *H = fopen("C:/FilesBack/NPeleng/ResultFile/Head.txt","w");
        FILE *D = fopen("C:/FilesBack/NPeleng/ResultFile/Distance.txt","w");
       // FILE *Xobj = fopen("C:/FilesBack/NPeleng/ResultFile/Xobj.txt","w+");
       // FILE *Yobj = fopen("C:/FilesBack/NPeleng/ResultFile/Yobj.txt","w+");
       // FILE *Xn = fopen("C:/FilesBack/NPeleng/ResultFile/Xnab.txt","w+");
       // FILE *Yn = fopen("C:/FilesBack/NPeleng/ResultFile/Ynab.txt","w+"); 
          
        
        fprintf(REZ,"Расчет номер %d\n", n+1);  
        printf("Расчет номер %d\n", n+1);                          
        double Xb0=StartPosition.x + coordX( start_distance[n], start_bearing);
        double Yb0=StartPosition.y + coordY( start_distance[n], start_bearing);
        double Xb=Xb0;
        double Yb=Yb0;
        
        Matrix3x3 Ak;
        Matrix3x1 Bk;
        Matrix3x3 Pk;
        Matrix3x1 Xk;
        for(i=0;i<3;i++) for(j=0;j<3;j++) Ak[i][j]=0;
        for(i=0;i<3;i++) Bk[i]=0;
        
       	
                                           
            FILE *Xobj = fopen("C:/FilesBack/NPeleng/ResultFile/Xobj.txt","w+");
            FILE *Yobj = fopen("C:/FilesBack/NPeleng/ResultFile/Yobj.txt","w+");
            FILE *Xn = fopen("C:/FilesBack/NPeleng/ResultFile/Xnab.txt","w+");
            FILE *Yn = fopen("C:/FilesBack/NPeleng/ResultFile/Ynab.txt","w+"); 
            
            for(time=t_start;time<=t_end;time+=dt){
                
                 printf("Dist %10f  X %10f  Y %10f\n", start_distance[n] , Xb, Yb); 
            	// movement B
            	double Vxb=coordX(Vb,Kb);
            	double Vyb=coordY(Vb,Kb);
            	
            	PosAndVelocity pv = findPos_manH(time, StartPosition , MovementPosition ,sizeMas); // movement A
            	double bearing = normalDistribution(angle_1to2(pv.x,pv.y,Xb,Yb),sigma);
            	if(time==t_start) start_bearing = bearing;
            	
            	double Sx = pv.x-StartPosition.x;
            	double Sy = pv.y-StartPosition.y;
            	
            	double a = sin(start_bearing-bearing);
            	double b = cos(bearing)*(time-t_start);
            	double c = -sin(bearing)*(time-t_start);
            	double h = Sx*cos(bearing)-Sy*sin(bearing);
            	
            	Ak[0][0] = Ak[0][0]+pow(a,2)*k;
            	Ak[0][1] = Ak[0][1]+a*b*k;
            	Ak[0][2] = Ak[0][2]+a*c*k;
            	Ak[1][0] = Ak[1][0]+a*b*k;
            	Ak[1][1] = Ak[1][1]+pow(b,2)*k;
            	Ak[1][2] = Ak[1][2]+b*c*k;
            	Ak[2][0] = Ak[2][0]+a*c*k;
            	Ak[2][1] = Ak[2][1]+b*c*k;
            	Ak[2][2] = Ak[2][2]+pow(c,2)*k;
            	
            	Bk[0] = Bk[0]+a*h*k;
            	Bk[1] = Bk[1]+b*h*k;
            	Bk[2] = Bk[2]+c*h*k;
            	
            	I=!findInvMatrix_3x3(Ak,Pk);
            	if(I){
            		multiplyMatrices_3x3_3x1(Pk,Bk,Xk);
            		double D0 = Xk[0];
            		double Vx = Xk[1];
            		double Vy = Xk[2];
            		heading = grad(angle_1to2(0,0,Vx,Vy));
            		velocity = sqrt(pow(Vx,2)+pow(Vy,2));
            		
            		h_data[calc][counter] = heading;
			    	v_data[calc][counter] = velocity;
				    counter++;
            		
            		//printf("Time: %15f	VelocityX: %15f	VelocityY: %15f	Heading: %15f	Velocity: %15f	Distance: %15f\n",time,Vx,Vy,heading,velocity,D0);	
            	}
            	
            	fprintf(REZ,"Time: %10f Head: %10f X: %10f Y:%10f \n",time, grad(pv.heading), pv.x,pv.y);
            	printf("Time: %10f Head: %10f X: %10f Y:%10f Xn %10f  Yn %10f vel %10f hed %10f \n",time, grad(pv.heading), pv.x,pv.y ,Xb, Yb , velocity ,heading);
            	fprintf(Xobj,"%10f ",pv.x);
            	fprintf(Yobj,"%10f ",pv.y);
            	
            	Xb=Xb+Vxb*dt;
            	Yb=Yb+Vyb*dt;
            	
            	fprintf(Xn,"%10f ",Xb);
            	fprintf(Yn,"%10f ",Yb);
            }
            fclose(Xobj);
            fclose(Yobj);
            fclose(Xn);
            fclose(Yn);
            fclose(T);
            fclose(H);
            fclose(D);
            fclose(REZ);
           // sleep(1500);
            
            
        } 
        
        system("matlab -nodisplay -nosplash -nodesktop -r \"run('C:/FilesBack/NPeleng/MatlabFile/build_graph.m'); \" ");
        
        for(i=0;i<nt;i++) for(calc=0;calc<calc_count;calc++){
            v_data_inverted[i][calc]=v_data[calc][i];
            h_data_inverted[i][calc]=h_data[calc][i];
	    }
	
    	for(calc=0;calc<calc_count;calc++) for(i=0;i<nt;i++){
    		sko_v_static[calc][i] = getVariance(v_data_inverted[i],calc_count);
    		sko_h_static[calc][i] = getVariance(h_data_inverted[i],calc_count);
    		printf("sko_v_static[%d][%d]=%f\n",calc,i,sko_v_static[calc][i]);
    		printf("sko_h_static[%d][%d]=%f\n",calc,i,sko_h_static[calc][i]);
    	}   
        
        
        /*
        fclose(Xobj);
        fclose(Yobj);
        fclose(Xn);
        fclose(Yn);
        fclose(T);
        fclose(H);
        fclose(D);
        fclose(REZ);
        sleep(1500);
        */
   }
        
   //system("matlab -nodisplay -nosplash -nodesktop -r \"run('C:/FilesBack/NPeleng/MatlabFile/build_graph.m'); \" ");
   //system("matlab -nodisplay -nosplash -nodesktop -r \"run('build_graphH.m'); \" ");
   system("PAUSE");
   return 0;
}
