// These unions are necessary to put the constants in .rodata rather than .data.
// TODO: is it possible to remove them somehow?

typedef union {
	/* 0x0 */ double d;
	/* 0x0 */ struct
	{
		/* 0x0 */ unsigned int hi;
		/* 0x4 */ unsigned int lo;
	} word;
} du;

typedef union {
	/* 0x0 */ float f;
	/* 0x0 */ unsigned int i;
} fu;

static const du P[5] = {{1.0},
						{-0.16666659550427756},
						{0.008333066246082155},
						{-1.980960290193795E-4},
						{2.605780637968037E-6}};

static const du rpi = {0.3183098861837907};

static const du pihi = {
	3.1415926218032837};

static const du pilo = {
	3.178650954705639E-8};

static const fu zero = {0.0};
extern const fu NAN;

//forward
float cos(float x) {
	double dx;  // double x
	double xsq; // x squared
	double poly;
	double dn;
	float xabs;
	int n;
	double result;
	int ix; // int x
	int xpt;
	ix = *(int *)&x;
	xpt = (ix >> 22) & 0x1FF;

	if (xpt < 310)
	{
		if (0 < x)
			xabs = x;
		else
			xabs = -x;
		dx = xabs;

		dn = dx * rpi.d + .5;
		if (0 <= dn)
		{

			n = dn + .5;
		}
		else
		{
			n = dn - .5;
		}
		dn = n;

		dx -= (dn - .5) * pihi.d;
		dx -= (dn - .5) * pilo.d;
		xsq = dx * dx;

		poly = (((((P[4].d * xsq) + P[3].d) * xsq) + P[2].d) * xsq) + P[1].d;

		result = ((dx * xsq) * poly) + dx;

		if ((n & 0x1) == 0)
		{
			return result;
		}
		else
		{
			return -(float)result;
		}
	}

	if (x != x)
	{
		//return NAN.f;
	}

	return zero.f;
}

float sin(float x) {
	double dx;  // double x
	double xsq; // x squared
	double poly;
	double dn;
	int n;
	double result;
	int ix; // int x
	int xpt;

	ix = *(int *)&x;
	xpt = (ix >> 22) & 0x1FF;

	if (xpt < 255)
	{
		dx = x;
		if (xpt >= 230)
		{
			xsq = dx * dx;

			poly = (((((P[4].d * xsq) + P[3].d) * xsq) + P[2].d) * xsq) + P[1].d;

			result = ((dx * xsq) * poly) + dx;

			return result;
		}
		else
		{
			return x;
		}
	}

	if (xpt < 310)
	{
		dx = x;

		dn = dx * rpi.d;

		if (dn >= 0)
		{
			n = dn + 0.5;
		}
		else
		{
			n = dn - 0.5;
		}

		dn = n;

		dx -= dn * pihi.d;
		dx -= dn * pilo.d;

		xsq = dx * dx;

		poly = (((((P[4].d * xsq) + P[3].d) * xsq) + P[2].d) * xsq) + P[1].d;

		result = ((dx * xsq) * poly) + dx;

		if ((n & 0x1) == 0)
		{
			return result;
		}
		else
		{
			return -(float)result;
		}
	}

	if (x != x)
	{
		//return NAN.f;
	}

	return zero.f;
}

float tan(float x) {
	return sin(x)/cos(x);
}

//inverse
float acos(float x) {

}

float asin(float x) {

}

float atan(float x) {

}

float atan2(float x, float y) {

}

//forward hyperbolic
float cosh(float x) {
	float y = exp(x);
	return 0.5f*(1.0f/y + y);
}

float sinh(float x) {
	float y = exp(x);
	return 0.5f*(y - 1.0f/y);
}

float tanh(float x) {
	float y = exp(2.0f*x);
	return (y - 1.0f)/(y + 1.0f);
}

//inverse hyperbolic
float acosh(float x) {

}

float asinh(float x) {

}

float atanh(float x) {

}