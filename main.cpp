#include <bits/stdc++.h>
#define MAX_N 1000
using namespace std;

string filenamereference, filenamedata;

double reference[100*MAX_N], data[MAX_N];

int nobj, nd, nr;//objectives, data size, reference size
double p = 2.0;

double dist(double *a, double *b)
{
   double d = 0.0;
   for(int i = 0; i < nobj; i++) d += pow(a[i]-b[i], p);
   return d;
}
double GD(double *reference, int size_r, double  *point, int size_p)
{
   double totaldist = 0.0;
   for(int i = 0; i < size_r; i++)
   {
      double mind = DBL_MAX;
      for(int  j = 0; j < size_p; j++)
	 mind = min(mind, dist(reference + i*nobj, point + j*nobj));
      totaldist +=mind;
   } 
   return pow((totaldist/size_r), 1.0/p);
}
void readpoints(double *points, int &size, FILE *fin)
{
   nobj=0;
   int end=1, r=0, c=0;
   double num;
   char trimm[2];
   do //each row
   {
      c = 0;
      do //each column
      {
        fscanf(fin, "%lf", points + r*nobj+c);
        fscanf(fin, "%*[ \t]");
        end = fscanf (fin, "%1[\r\n]", trimm);
	c++;
      }while(!end);
      nobj = max(nobj, c);
      //skip over successive empty lines
  do { 
       if(!fscanf (fin, "%1[#]%*[^\n\r]", trimm))
            fscanf (fin, "%*[ \t]");
       end = fscanf (fin, "%1[\r\n]", trimm);
     } while (end == 1);
     r++;
   }while(end!= EOF);
   nobj = c;
   size = r;
}
void readdata()
{
   //FILE *fin_ref = fopen(filenamereference.c_str(), "r"), *fin_point = stdin;
   FILE *fin_ref = fopen(filenamereference.c_str(), "r"), *fin_point = fopen(filenamedata.c_str(), "r");
   readpoints(reference, nr, fin_ref);
   readpoints(data, nd, fin_point);
}
void inputArg(int argc, char **argv)
{
   for(int i = 1; i < argc ; i++)
   {
      string Terminal(argv[i]);
      if(Terminal == "--r" )
         filenamereference = string(argv[++i]);
      else if(Terminal == "--p" )
         p = atof(argv[++i]);
      else if(Terminal == "--d" )
         filenamedata = string(argv[++i]);

   }
}
int main(int argc, char **argv)
{
   inputArg(argc, argv);
   readdata();
   cout << max(GD(reference, nr, data, nd), GD(data, nd, reference, nr))<<endl;   
   return 0;
}
