#include "TH2PolyBinLite.h"
#include "TError.h"

////////////////////////////////////////////////////////////////////////////////
/// Default constructor.

//TH2PolyBinLite::TH2PolyBinLite()
//{
//	fPoly = 0;
//	fContent = 0.;
//	fNumber = 0;
//	fXmax = -1111;
//	fXmin = -1111;
//	fYmax = -1111;
//	fYmin = -1111;
//	fArea = 0;
//	SetChanged(kTRUE);
//}

////////////////////////////////////////////////////////////////////////////////
/// Normal constructor.

TH2PolyBinLite::TH2PolyBinLite(Int_t _nVerts, const Double_t* _x, const Double_t* _y, Int_t bin_number) : nVerts(_nVerts)
{
	x = new Double_t[nVerts];
	y = new Double_t[nVerts];

    std::copy(_x, _x + nVerts, this->x);
    std::copy(_y, _y + nVerts, this->y);

    Info("DRAW", "TH2PolyBinLite::TH2PolyBinLite");

	fContent = 0.;
	fNumber = bin_number;
	fArea = 0.;
	fXmax = -1111;
	fXmin = -1111;
	fYmax = -1111;
	fYmin = -1111;
	SetChanged(kTRUE);
}

////////////////////////////////////////////////////////////////////////////////
/// Destructor.

TH2PolyBinLite::~TH2PolyBinLite()
{
	// ???
	if (x) delete[] x;
	if (y) delete[] y;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns the area of the bin.

Double_t TH2PolyBinLite::GetDet()
{
	if (nVerts != 3) return 0;

	Double_t v1x = x[1] - x[0];
	Double_t v2x = x[2] - x[0];
	Double_t v1y = y[1] - y[0];
	Double_t v2y = y[2] - y[0];

	return v1x * v2y - v1y * v2x;
}

Double_t TH2PolyBinLite::GetArea()
{
	if (nVerts == 2)
	{
		return std::fabs((x[1] - x[0]) * (y[1] - y[0]));
	}
	else if (nVerts == 3)
	{
        return std::fabs(GetDet()) * 0.5;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns the maximum value for the x coordinates of the bin.

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

Double_t TH2PolyBinLite::GetXMax()
{
	if (fXmax != -1111) return fXmax;

	fXmax = (nVerts == 2 ? (MAX(x[0], x[1])) : (MAX(MAX(x[0], x[1]), x[2])));

	return fXmax;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns the minimum value for the x coordinates of the bin.

Double_t TH2PolyBinLite::GetXMin()
{
	if (fXmin != -1111) return fXmin;

	fXmax = (nVerts == 2 ? (MIN(x[0], x[1])) : (MIN(MIN(x[0], x[1]), x[2])));

	return fXmax;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns the maximum value for the y coordinates of the bin.

Double_t TH2PolyBinLite::GetYMax()
{
	if (fYmax != -1111) return fYmax;

	fYmax = (nVerts == 2 ? (MAX(y[0], y[1])) : (MAX(MAX(y[0], y[1]), y[2])));

	return fYmax;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns the minimum value for the y coordinates of the bin.

Double_t TH2PolyBinLite::GetYMin()
{
	if (fYmin != -1111) return fYmin;

	fYmin = (nVerts == 2 ? (MIN(y[0], y[1])) : (MIN(MIN(y[0], y[1]), y[2])));

	return fYmin;
}

#undef MIN
#undef MAX

////////////////////////////////////////////////////////////////////////////////
/// Return the set of vertices to build TGraph object

Int_t TH2PolyBinLite::BuildFullPolyDescription(Double_t *_x, Double_t *_y)
{
    if (nVerts == 2) { // RECTANGLE CASE
        _x[0] = this->x[0]; _y[0] = this->y[0];
        _x[1] = this->x[0]; _y[1] = this->y[1];
        _x[2] = this->x[1]; _y[2] = this->y[1];
        _x[3] = this->x[1]; _y[3] = this->y[0];
        _x[4] = this->x[0]; _y[4] = this->y[0];

        return 5;
    }
    else if (nVerts == 3) { // TRIANGLE CASE
        _x[0] = this->x[0]; _y[0] = this->y[0];
        _x[1] = this->x[1]; _y[1] = this->y[1];
        _x[2] = this->x[2]; _y[2] = this->y[2];
        _x[3] = this->x[0]; _y[3] = this->y[0];

        return 4;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Return "kTRUE" if the point (x,y) is inside the bin.

Bool_t TH2PolyBinLite::IsInside(Double_t _x, Double_t _y)
{
    Bool_t in = kFALSE;

	if (nVerts == 2)
	{
        if (GetXMin() <= _x && _x <= GetXMax() &&
            GetYMin() <= _y && _y <= GetYMax())
            in = kTRUE;
	}
	else if (nVerts == 3)
	{
		Double_t detInv = 1. / GetDet();

        Double_t l1 = ((this->y[1] - this->y[2]) * (_x - this->x[2]) +
            (this->x[2] - this->x[1]) * (_y - this->y[2])) * detInv;

        Double_t l2 = ((this->y[2] - this->y[0]) * (_x - this->x[2]) +
            (this->x[0] - this->x[2]) * (_y - this->y[2])) * detInv;

        in = (l1 > 0.0 && l2 > 0.0 && l1 + l2 < 1.0) ? kTRUE : kFALSE;
	}

	return in;
}
