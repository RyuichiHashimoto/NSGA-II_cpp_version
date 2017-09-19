#pragma once

#include<vector>
#include<math.h>


namespace WFG{

	const double PI = 3.141592653;
	double linear(std::vector<double> &x, int &m);
	
	double convex(std::vector<double> &x, int m);
	double concave(std::vector<double> &x, int m);
	double mixed(std::vector<double> &x, int A, double alpha);

	double disc(std::vector<double> &x, int A, double alpha, double beta);

}


namespace Transformtions {

	const double PI = 3.141592653;
	double min(double a, double b) { return  a > b ? b : a; }

	const double epsilon = (double)1.0e-10;

	double b_poly(double y, double alpha);


		/**
		* b_flat transformation
		*/
		double b_flat(double y, double A, double B, double C);
	// b_flat

	   /**
	   * s_linear transformation
	   */
		double s_linear(double y, double A);

	  /**
	  * s_decept transformation
	  */
		double s_decept(double y, double A, double B, double C);

	  /**
	  * s_multi transformation
	  */
		double s_multi(double y, int A, int B, double C);

	  /**
	  * r_sum transformation
	  */
		double r_sum(std::vector<double>  y, std::vector<double>  w);

		double r_nonsep(std::vector<double>  y, int A);

	  /**
	  * b_param transformation
	  */
		double b_param(double y, double u, double A, double B, double C);
		double correct_to_01(double a);



}