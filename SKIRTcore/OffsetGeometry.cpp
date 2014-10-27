/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "OffsetGeometry.hpp"

////////////////////////////////////////////////////////////////////

OffsetGeometry::OffsetGeometry()
    : _geometry(0), _offsetX(0), _offsetY(0), _offsetZ(0)
{
}

////////////////////////////////////////////////////////////////////

void OffsetGeometry::setGeometry(Geometry* value)
{
    if (_geometry) delete _geometry;
    _geometry = value;
    if (_geometry) _geometry->setParent(this);
}

////////////////////////////////////////////////////////////////////

Geometry* OffsetGeometry::geometry() const
{
    return _geometry;
}

////////////////////////////////////////////////////////////////////

void OffsetGeometry::setOffsetX(double value)
{
    _offsetX = value;
}

////////////////////////////////////////////////////////////////////

double OffsetGeometry::offsetX() const
{
    return _offsetX;
}

////////////////////////////////////////////////////////////////////

void OffsetGeometry::setOffsetY(double value)
{
    _offsetY = value;
}

////////////////////////////////////////////////////////////////////

double OffsetGeometry::offsetY() const
{
    return _offsetY;
}

////////////////////////////////////////////////////////////////////

void OffsetGeometry::setOffsetZ(double value)
{
    _offsetZ = value;
}

////////////////////////////////////////////////////////////////////

double OffsetGeometry::offsetZ() const
{
    return _offsetZ;
}

////////////////////////////////////////////////////////////////////

int OffsetGeometry::dimension() const
{
    return (_offsetX || _offsetY || _geometry->dimension()==3) ? 3 : 2;
}

////////////////////////////////////////////////////////////////////

double
OffsetGeometry::density(Position bfr)
const
{
    double x,y,z;
    bfr.cartesian(x,y,z);
    return _geometry->density(Position(x-_offsetX, y-_offsetY, z-_offsetZ));
}

////////////////////////////////////////////////////////////////////

Position
OffsetGeometry::generatePosition()
const
{
    Position bfr = _geometry->generatePosition();
    double x,y,z;
    bfr.cartesian(x,y,z);
    return Position(x+_offsetX, y+_offsetY, z+_offsetZ);
}

////////////////////////////////////////////////////////////////////

double
OffsetGeometry::SigmaX()
const
{
    return _geometry->SigmaX();
}

////////////////////////////////////////////////////////////////////

double
OffsetGeometry::SigmaY()
const
{
    return _geometry->SigmaY();
}

////////////////////////////////////////////////////////////////////

double
OffsetGeometry::SigmaZ()
const
{
    return _geometry->SigmaZ();
}

////////////////////////////////////////////////////////////////////

double
OffsetGeometry::probabilityForDirection(Position bfr, Direction bfk)
const
{
    double x,y,z;
    bfr.cartesian(x,y,z);
    return _geometry->probabilityForDirection(Position(x-_offsetX, y-_offsetY, z-_offsetZ),bfk);
}

////////////////////////////////////////////////////////////////////

Direction
OffsetGeometry::generateDirection(Position bfr)
const
{
    double x,y,z;
    bfr.cartesian(x,y,z);
    return _geometry->generateDirection(Position(x-_offsetX, y-_offsetY, z-_offsetZ));
}

////////////////////////////////////////////////////////////////////
