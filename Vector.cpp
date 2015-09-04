#include "stdafx.h"
#include "Vector.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//For class cVector
cVector::cVector()  //default constructor, sets everything as 0
{
	xComp = 0.0;
	yComp = 0.0;
	magnitude = 0.0;
	angle = 0.0;
}
cVector::cVector(double x1, double y1, bool n = 0)  //parameterized constructor,Set n as False for component entry, TRUE for magnitude and angle entry
{
	if (!n)
	{
		xComp = x1;
		yComp = y1;
		magnitude = 0.0;
		angle = 0.0;
		calculateAngle();
		calculateMagnitude();
	}
	else
	{
		if (x1 == 0.0)
		{
			magnitude = 0.0;
			angle = 0.0;
			xComp = 0.0;
			yComp = 0.0;
		}
		else if (x1 < 0)
		{
			magnitude = (-x1);
			angle = (y1 + pi);
			xComp = 0.0;
			yComp = 0.0;
			calculateComponents();
		}
		else
		{
			magnitude = x1;
			angle = y1;
			xComp = 0.0;
			yComp = 0.0;
			calculateComponents();
		}
	}
}
void cVector::setValues(double x, double y, bool n = 0)      //INTERFACE:sets values for both components, angle and magnitude set n as False for component entry, TRUE for magnitude and angle entry
{
	if (!n)
	{
		xComp = x;              //set X Component
		yComp = y;              //set Y Component
		calculateAngle();       //calculate new angle
		calculateMagnitude();   //calculate new magnitude
	}
	else
	{
		if (x == 0.0)
		{
			magnitude = 0.0;
			angle = 0.0;
			xComp = 0.0;
			yComp = 0.0;
		}
		else if (x < 0)
		{
			magnitude = (-x);
			angle = (y + pi);
			xComp = 0.0;
			yComp = 0.0;
			calculateComponents();
		}
		else
		{
			magnitude = x;
			angle = y;
			xComp = 0.0;
			yComp = 0.0;
			calculateComponents();
		}
	}
}
double cVector::giveMagnitude()                  //INTERFACE:returns magnitude
{
	if (magnitude == 0.0 && (xComp != 0.0 || yComp != 0.0)) //just in case
	{
		calculateMagnitude();
		return magnitude;
	}
	else
		return magnitude;
}
inline void cVector::calculateAngle()                    //calculates angle with the positive X Axis
{
	double x;
	x = atan2(yComp, xComp);
	if (x < 0.0)
	{
		while (x < 0.0)   //convert to angle between [0,2pi)
		{
			x += 2 * pi;
		}
		angle = x;        //set angle
	}
	else
	{
		angle = x;        //set angle
	}
}
inline void cVector::calculateMagnitude()                   //calculates magnitude of vector
{
	double x;
	x = sqrt((xComp*xComp) + (yComp*yComp));
	magnitude = x;        //set magnitude
}
inline void cVector::calculateComponents()           //calculate X and Y components
{
please:                                          //please forgive me for using goto
	if (angle >= 0.0 && angle <= (0.5*pi))           //first quadrant
	{
		xComp = magnitude*cos(angle);
		yComp = magnitude*sin(angle);
	}
	else if (angle > (0.5*pi) && angle <= pi)        //second quadrant
	{
		//(Theta-(0.5*pi))
		xComp = (-1.0)*magnitude*sin((angle - (0.5*pi)));
		yComp = magnitude*cos((angle - (0.5*pi)));
	}
	else if (angle > pi && angle <= (1.5*pi))        //third quadrant
	{
		//(Theta-pi)
		xComp = (-1.0)*magnitude*cos((angle - pi));
		yComp = (-1.0)*magnitude*sin((angle - pi));
	}
	else if (angle > (1.5*pi) && angle < (2.0*pi))   //fourth quadrant
	{
		//(Theta-(1.5*pi))
		xComp = magnitude*sin((angle - (1.5*pi)));
		yComp = (-1.0)*magnitude*cos((angle - (1.5*pi)));
	}
	else if (angle >= (2.0*pi))                      //grater than 2pi
	{
		while (angle >(2.0*pi))
		{
			angle -= (2.0*pi);                       //bring down to equivalent value in [0,2pi)
		}
		goto please;                                  //sorry :(
	}
	else                                             //must have negative value
	{
		while (angle < 0.0)
		{
			angle += 2.0*pi;                         //change to equivalent value in [0,2pi)
		}
		goto please;                                 //please forgive me, I can't stop loving you  (BA)
	}
}
double cVector::giveAngle()                          //INTERFACE:returns angle with the positive X Axis [0,2pi)
{
	if (angle == 0.0 && xComp != 0.0 && yComp != 0.0) //just in case
	{
		calculateAngle();
		return angle;
	}
	else
	{
		return angle;
	}

}
double cVector::giveX()
{
	return xComp;
}
double cVector::giveY()
{
	return yComp;
}
void cVector::rotateVector(double angleAlpha)         //INTERFACE:OPERATION:rotates the vector on its tail by the given angle + or -)
{
	double mag, Theta;
	mag = giveMagnitude();
	Theta = giveAngle();
	Theta += angleAlpha;                             //change angle
sorry:                                           //sorry for using goto
	if (Theta >= 0.0 && Theta <= (0.5*pi))           //first quadrant
	{
		xComp = mag*cos(Theta);
		yComp = mag*sin(Theta);
	}
	else if (Theta > (0.5*pi) && Theta <= pi)        //second quadrant
	{
		//(Theta-(0.5*pi))
		xComp = (-1.0)*mag*sin((Theta - (0.5*pi)));
		yComp = mag*cos((Theta - (0.5*pi)));
	}
	else if (Theta > pi && Theta <= (1.5*pi))        //third quadrant
	{
		//(Theta-pi)
		xComp = (-1.0)*mag*cos((Theta - pi));
		yComp = (-1.0)*mag*sin((Theta - pi));
	}
	else if (Theta > (1.5*pi) && Theta < (2.0*pi))   //fourth quadrant
	{
		//(Theta-(1.5*pi))
		xComp = mag*sin((Theta - (1.5*pi)));
		yComp = (-1.0)*mag*cos((Theta - (1.5*pi)));
	}
	else if (Theta >= (2.0*pi))                      //grater than 2pi
	{
		while (Theta >(2.0*pi))
		{
			Theta -= (2.0*pi);                       //bring down to equivalent value in [0,2pi)
		}
		goto sorry;                                  //sorry :(
	}
	else                                             //must have negative value
	{
		while (Theta < 0.0)
		{
			Theta += 2.0*pi;                         //change to equivalent value in [0,2pi)
		}
		goto sorry;                                  //sorry again :(
	}
	angle = Theta;
}
/*
//add and subtract functions not needed because of overloaded operators for this class
cVector vectorAdd(cVector vec1, cVector vec2)  //INTERFACE:OPERATION:add two vectors
{
double newX, newY;
newX = vec1.xComp + vec2.xComp;
newY = vec1.yComp + vec2.yComp;
cVector temp(newX, newY);
return temp;
}
cVector vectorSubtract(cVector vec1, cVector vec2) //INTERFACE:OPERATION:subtract two vectors
{
double newX, newY;
newX = vec1.xComp - vec2.xComp;
newY = vec1.yComp - vec2.yComp;
cVector temp(newX, newY);
return temp;
}
*/
double vectorDotProduct(cVector vec1, cVector vec2)  //OPERATION:returns dot product of two vectors, is a friend
{
	return ((vec1.xComp*vec2.xComp) + (vec1.yComp*vec2.yComp));
}
cVector& cVector::operator =(const cVector &vec)  //assignment operator, overloaded for this class
{
	xComp = vec.xComp;
	yComp = vec.yComp;
	magnitude = vec.magnitude;
	angle = vec.angle;

	return *this;
}
cVector cVector::operator +(const cVector &vec)   //addition operator, overloaded for this class
{
	cVector temp((xComp + vec.xComp), (yComp + vec.yComp));
	return temp;
}
cVector cVector::operator -(const cVector &vec)   //subtraction operator, overloaded for this class
{
	cVector temp((xComp - vec.xComp), (yComp - vec.yComp));
	return temp;
}
/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//For cNormalVector
cNormalVector::cNormalVector(double m = 0.0, double angle = 0.0)
{
magnitude = m;
if (angle >= 0.0)
theta = angle;
else
theta = (angle + pi);
}
void cNormalVector::setValues(double m, double angle)
{
magnitude = m;
if (angle >= 0.0)
theta = angle;
else
theta = (angle + pi);
}
*/




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//For 
