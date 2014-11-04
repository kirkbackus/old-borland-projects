#ifndef BLACKBOX_COLLISION_H
#define BLACKBOX_COLLISION_H

float CalculateMass(const Vector* A, int Anum, float density) {
    if (Anum < 2) return 5.0f * density;

    float mass = 0.0f;

    for(int j = Anum-1, i = 0; i < Anum; j = i, i ++) {
        Vector P0 = A[j];
	Vector P1 = A[i];
	mass +=  (float) fabs(P0 ^ P1);
    }
    if (Anum <= 2) mass = 10.0f;

    mass *= density * 0.5f;

    return mass;
}

float CalculateInertia(const Vector* A, int Anum, float mass)
{
    if (Anum == 1) return 0.0f;

    float denom = 0.0f;
    float numer = 0.0f;

    for(int j = Anum-1, i = 0; i < Anum; j = i, i ++) {
        Vector P0 = A[j];
	Vector P1 = A[i];

	float a = (float) fabs(P0 ^ P1);
	float b = (P1*P1 + P1*P0 + P0*P0);

	denom += (a * b);
	numer += a;
    }

    float inertia = (mass / 6.0f) * (denom / numer);
    return inertia;
}

bool FindMTD(Vector* xAxis, float* taxis, int iNumAxes, Vector& N, float& t)
{
    int mini = -1;
    t = 0.0f;
    for(int i = 0; i < iNumAxes; i ++) {
        if (taxis[i] > 0) {
            if (taxis[i] > t) {
                mini = i;
		t = taxis[i];
		N = xAxis[i];
                N = N.Normalize();
            }
        }
    }

    if (mini != -1) return true;

    mini = -1;
    for(int i = 0; i < iNumAxes; i ++) {
        float n = xAxis[i].Length();
        xAxis[i]=xAxis[i].Normalize();
    	taxis[i] /= n;

    	if (taxis[i] > t || mini == -1) {
    		mini = i;
    		t = taxis[i];
    		N = xAxis[i];
    	}
    }

    return (mini != -1);
}

// calculate the projection range of a polygon along an axis
void GetInterval(const Vector *axVertices, int iNumVertices, const Vector& xAxis, float& min, float& max) {
    min = max = (axVertices[0] * xAxis);

    for(int i = 1; i < iNumVertices; i ++) {
        float d = (axVertices[i] * xAxis);
	if (d < min) min = d; else if (d > max) max = d;
    }
}

bool IntervalIntersect(const Vector* A, int Anum, const Vector* B, int Bnum, const Vector& xAxis, const Vector& xOffset, const Vector& xVel, const Matrix& xOrient, float& taxis, float tmax) {
    float min0, max0;
    float min1, max1;
    GetInterval(A, Anum, xAxis ^ xOrient, min0, max0);
    GetInterval(B, Bnum, xAxis, min1, max1);

    float h = xOffset * xAxis;
    min0 += h;
    max0 += h;

    float d0 = min0 - max1; // if overlapped, do < 0
    float d1 = min1 - max0; // if overlapped, d1 > 0

    // separated, test dynamic intervals
    if (d0 > 0.0f || d1 > 0.0f) {
        float v = xVel * xAxis;

	// small velocity, so only the overlap test will be relevant.
	if (fabs(v) < 0.0000001f) return false;

        float t0 =-d0 / v; // time of impact to d0 reaches 0
	float t1 = d1 / v; // time of impact to d0 reaches 1

	if (t0 > t1) { float temp = t0; t0 = t1; t1 = temp; }
	taxis  = (t0 > 0.0f)? t0 : t1;

	if (taxis < 0.0f || taxis > tmax) return false;

        return true;
    } else {
        // overlap. get the interval, as a the smallest of |d0| and |d1|
	// return negative number to mark it as an overlap
	taxis = (d0 > d1)? d0 : d1;
	return true;
    }
}

bool Collide(const Vector* A, int Anum, const Vector& PA, const Vector& VA, const Matrix& OA, const Vector* B, int Bnum, const Vector& PB, const Vector& VB, const Matrix& OB, Vector& N, float& t) {
    if (!A || !B) return false;

    if (Anum < 2 && Bnum < 2) return false;

    Matrix xOrient = OA ^ OB;
    Vector xOffset = (PA - PB) ^ OB;
    Vector xVel    = (VA - VB) ^ OB;

    // All the separation axes
    Vector xAxis[64]; // note : a maximum of 32 vertices per poly is supported
    float  taxis[64];
    int    iNumAxes=0;

    float fVel2 = xVel * xVel;

    if (fVel2 > 0.00001f) {
        xAxis[iNumAxes] = Vector(-xVel.y, xVel.x);

	if (!IntervalIntersect(	A, Anum, B, Bnum, xAxis[iNumAxes], xOffset, xVel, xOrient, taxis[iNumAxes], t)) return false;
	iNumAxes++;
    }

    if (Anum > 1) {
        // test separation axes of A
	for(int j = Anum-1, i = 0; i < Anum; j = i, i ++)
	{
            Vector E0 = A[j];
	    Vector E1 = A[i];
	    Vector E  = E1 - E0;
	    xAxis[iNumAxes] = Vector(-E.y, E.x) * xOrient;

	    if (!IntervalIntersect(A, Anum, B, Bnum, xAxis[iNumAxes], xOffset, xVel, xOrient, taxis[iNumAxes], t)) return false;
            iNumAxes++;
	}
    }

    // test separation axes of B
    if (Bnum > 1) {
        for(int j = Bnum-1, i = 0; i < Bnum; j = i, i ++) {
            Vector E0 = B[j];
            Vector E1 = B[i];
            Vector E  = E1 - E0;
            xAxis[iNumAxes] = Vector(-E.y, E.x);

            if (!IntervalIntersect(	A, Anum, B, Bnum, xAxis[iNumAxes], xOffset, xVel, xOrient, taxis[iNumAxes], t))	return false;

            iNumAxes++;
        }
    }

    // special case for segments
    if (Bnum == 2) {
        Vector E  = B[1] - B[0];
	xAxis[iNumAxes] = E;

	if (!IntervalIntersect( A, Anum, B, Bnum, xAxis[iNumAxes], xOffset, xVel, xOrient, taxis[iNumAxes], t)) return false;
        iNumAxes++;
    }

    // special case for segments
    if (Anum == 2) {
        Vector E  = A[1] - A[0];
	xAxis[iNumAxes] = E * xOrient;

	if (!IntervalIntersect( A, Anum, B, Bnum, xAxis[iNumAxes], xOffset, xVel, xOrient, taxis[iNumAxes], t)) return false;
        iNumAxes++;
    }

    if (!FindMTD(xAxis, taxis, iNumAxes, N, t)) return false;

    if (N * xOffset < 0.0f) N = -N;

    N *= OB;

    return true;
}

bool FindRoots(float a, float b, float c, float& t0, float& t1) {
	float d = b*b - (4.0f * a * c);
	if (d < 0.0f) return false;
	d = (float) sqrt(d);

	float one_over_two_a = 1.0f / (2.0f * a);

	t0 = (-b - d) * one_over_two_a;
	t1 = (-b + d) * one_over_two_a;

	if (t1 < t0)
	{
		float t = t0;
		t0 = t1;
		t1 = t;
	}
	return true;
}

#endif
