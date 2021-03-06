/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "FatalError.hpp"
#include "RangeGrainSizeDistribution.hpp"

////////////////////////////////////////////////////////////////////

RangeGrainSizeDistribution::RangeGrainSizeDistribution()
    : _amin(0), _amax(0)
{
}

////////////////////////////////////////////////////////////////////

void RangeGrainSizeDistribution::setupSelfBefore()
{
    GrainSizeDistribution::setupSelfBefore();

    // verify the distribution range
    if (_amin <= 0) throw FATALERROR("Minimum grain size must be positive");
    if (_amax <= _amin) throw FATALERROR("Maximum grain size must be larger than minimum grain size");
}

////////////////////////////////////////////////////////////////////

void RangeGrainSizeDistribution::setMinSize(double value)
{
    _amin = value;
}

////////////////////////////////////////////////////////////////////

double RangeGrainSizeDistribution::minSize() const
{
    return _amin;
}

////////////////////////////////////////////////////////////////////

void RangeGrainSizeDistribution::setMaxSize(double value)
{
    _amax = value;
}

////////////////////////////////////////////////////////////////////

double RangeGrainSizeDistribution::maxSize() const
{
    return _amax;
}

////////////////////////////////////////////////////////////////////

double RangeGrainSizeDistribution::amin() const
{
    return _amin;
}

////////////////////////////////////////////////////////////////////

double RangeGrainSizeDistribution::amax() const
{
    return _amax;
}

////////////////////////////////////////////////////////////////////
