/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "OligoDustSystem.hpp"
#include "FatalError.hpp"

//////////////////////////////////////////////////////////////////////

OligoDustSystem::OligoDustSystem()
{
}

//////////////////////////////////////////////////////////////////////

bool OligoDustSystem::dustemission() const
{
    return false;
}

//////////////////////////////////////////////////////////////////////

void OligoDustSystem::absorb(int /*m*/, int /*ell*/, double /*DeltaL*/, bool /*ynstellar*/)
{
    throw FATALERROR("This function should never be called");
}

//////////////////////////////////////////////////////////////////////
