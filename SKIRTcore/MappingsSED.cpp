/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "MappingsSED.hpp"
#include "MappingsSEDFamily.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////

MappingsSED::MappingsSED()
    : _Z(0), _logC(0), _pressure(0), _fPDR(0)
{
}

////////////////////////////////////////////////////////////////////

void MappingsSED::setupSelfBefore()
{
    StellarSED::setupSelfBefore();

    // construct the library of SED models
    MappingsSEDFamily mappings(this);

    // get the luminosities for arbitrary SFR and for the appropriate Z, logC, pressure and fPDR
    setluminosities(mappings.luminosities(1., _Z, _logC, _pressure, _fPDR));
}

////////////////////////////////////////////////////////////////////

void MappingsSED::setMetallicity(double value)
{
    _Z = value;
}

////////////////////////////////////////////////////////////////////

double MappingsSED::metallicity() const
{
    return _Z;
}

////////////////////////////////////////////////////////////////////

void MappingsSED::setCompactness(double value)
{
    _logC = value;
}

////////////////////////////////////////////////////////////////////

double MappingsSED::compactness() const
{
    return _logC;
}

////////////////////////////////////////////////////////////////////

void MappingsSED::setPressure(double value)
{
    _pressure = value;
}

////////////////////////////////////////////////////////////////////

double MappingsSED::pressure() const
{
    return _pressure;
}

////////////////////////////////////////////////////////////////////

void MappingsSED::setCoveringFactor(double value)
{
    _fPDR = value;
}

////////////////////////////////////////////////////////////////////

double MappingsSED::coveringFactor() const
{
    return _fPDR;
}

////////////////////////////////////////////////////////////////////
