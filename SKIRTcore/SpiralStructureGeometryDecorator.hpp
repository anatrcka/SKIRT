/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef SPIRALSTRUCTUREGEOMETRYDECORATOR_HPP
#define SPIRALSTRUCTUREGEOMETRYDECORATOR_HPP

#include "AxGeometry.hpp"
#include "GenGeometry.hpp"

////////////////////////////////////////////////////////////////////

/** The SpiralStructureGeometryDecorator class is a geometry decorator that adds spiral
    structure to any isotropic axisymmetric geometry (any anisotropic aspect of the original
    geometry is lost). The spiral arm perturbation (with an
    arbitrary weight factor) is a logarithmic spiral arm pattern, based on the
    formulation of Schechtman-Rook et al. (2012, ApJ, 746, 70). The decorator
    basically alters the uniform distribution in azimuth (by definition, the
    density \f$\rho_{\text{ax}}\f$ of the original geometry is independent of
    \f$\phi\f$). In formula form, the density of the new geometry behaves as \f[
    \rho(R,\phi,z) = \rho_{\text{ax}}(R,z)\, \xi(R,\phi) \f]
    where \f$\xi(R,\phi)\f$ is a perturbation given by
    \f[ \xi(R,\phi) = (1-w) + w\, C_N \sin^{2N}
    \left[\frac{m}{2}\left( \frac{\ln (R/R_0)}{\tan p}-(\phi-\phi_0)\right) +
    \frac{\pi}{4} \right]. \f] Apart from the reference to the original
    geometry that is being decorated, the model contains six parameters: the number
    of spiral arms \f$m\f$, the pitch angle \f$p\f$, the spiral arm radius and
    phase zero-points \f$R_0\f$ and \f$\phi_0\f$, the spiral perturbation weight
    \f$w\f$, and the integer index \f$N>0\f$ that sets the arm-interarm size ratio
    (larger values of \f$N\f$ correspond to larger arm-interarm size ratios). The
    factor \f$C_N\f$ is not a free parameter, but a normalization factor that ensures
    that the total mass equals one, \f[ C_N = \frac{\sqrt{\pi}\,
    \Gamma(N+1)}{\Gamma(N+\tfrac12)}. \f] For \f$N=1\f$ the expression for the
    perturbation reduces to \f[ \xi(R,\phi) = 1 +
    w\, \sin \left[m \left( \frac{\ln (R/R_0)}{\tan p} - (\phi-\phi_0)\right)
    \right], \f] as in Misiriotis et al. (2000, A&A, 353, 117). Note that
    the parameters \f$R_0\f$ and \f$\phi_0\f$ in fact have the same effect (both of
    them add an offset to the spiral structure). In principle one of them could be
    suppressed, but it is confortable to include both of them. */
class SpiralStructureGeometryDecorator : public GenGeometry
{
    Q_OBJECT
    Q_CLASSINFO("Title", "a decorator that adds spiral structure to any axisymmetric geometry")

    Q_CLASSINFO("Property", "geometry")
    Q_CLASSINFO("Title", "the axisymmetric geometry to be decorated with spiral structure")

    Q_CLASSINFO("Property", "arms")
    Q_CLASSINFO("Title", "the number of spiral arms")
    Q_CLASSINFO("MinValue", "1")
    Q_CLASSINFO("MaxValue", "100")
    Q_CLASSINFO("Default", "1")

    Q_CLASSINFO("Property", "pitch")
    Q_CLASSINFO("Title", "the pitch angle")
    Q_CLASSINFO("Quantity", "posangle")
    Q_CLASSINFO("MinValue", "0 deg")
    Q_CLASSINFO("MaxValue", "90 deg")
    Q_CLASSINFO("Default", "10 deg")

    Q_CLASSINFO("Property", "radius")
    Q_CLASSINFO("Title", "the radius zero-point")
    Q_CLASSINFO("Quantity", "length")
    Q_CLASSINFO("MinValue", "0")

    Q_CLASSINFO("Property", "phase")
    Q_CLASSINFO("Title", "the phase zero-point")
    Q_CLASSINFO("Quantity", "posangle")
    Q_CLASSINFO("MinValue", "0 deg")
    Q_CLASSINFO("MaxValue", "360 deg")
    Q_CLASSINFO("Default", "0 deg")

    Q_CLASSINFO("Property", "perturbWeight")
    Q_CLASSINFO("Title", "the weight of the spiral perturbation")
    Q_CLASSINFO("MinValue", "0")
    Q_CLASSINFO("MaxValue", "1")

    Q_CLASSINFO("Property", "index")
    Q_CLASSINFO("Title", "the arm-interarm size ratio index")
    Q_CLASSINFO("MinValue", "0")
    Q_CLASSINFO("MaxValue", "10")
    Q_CLASSINFO("Default", "1")

    //============= Construction - Setup - Destruction =============

public:
    /** The default constructor. */
    Q_INVOKABLE SpiralStructureGeometryDecorator();

    /** This function verifies the validity of the different parameters, and caches some
        frequently used combinations of them. */
    void setupSelfBefore();

    //======== Setters & Getters for Discoverable Attributes =======

public:
    /** Sets the original axisymmetric geometry (i.e. the geometry being decorated). */
    Q_INVOKABLE void setGeometry(AxGeometry* value);

    /** Returns the original axisymmetric geometry. */
    Q_INVOKABLE AxGeometry* geometry() const;

    /** Sets the number of spiral arms. */
    Q_INVOKABLE void setArms(int value);

    /** Returns the number of spiral arms. */
    Q_INVOKABLE int arms() const;

    /** Sets the pitch angle \f$p\f$. */
    Q_INVOKABLE void setPitch(double value);

    /** Returns the pitch angle \f$p\f$. */
    Q_INVOKABLE double pitch() const;

    /** Sets the radius zero-point \f$R_0\f$. */
    Q_INVOKABLE void setRadius(double value);

    /** Returns the radius zero-point \f$R_0\f$. */
    Q_INVOKABLE double radius() const;

    /** Sets the phase zero-point \f$\phi_0\f$. */
    Q_INVOKABLE void setPhase(double value);

    /** Returns the phase zero-point \f$\phi_0\f$. */
    Q_INVOKABLE double phase() const;

    /** Sets the weight \f$w\f$ of the spiral perturbation. */
    Q_INVOKABLE void setPerturbWeight(double value);

    /** Returns the weight \f$w\f$ of the spiral perturbation. */
    Q_INVOKABLE double perturbWeight() const;

    /** Sets the arm-interarm size ratio index \f$N\f$. */
    Q_INVOKABLE void setIndex(int value);

    /** Returns the arm-interarm size ratio index \f$N\f$. */
    Q_INVOKABLE int index() const;

    //======================== Other Functions =======================

public:
    /** This function returns the density \f$\rho({\bf{r}})\f$ at the position \f${\bf{r}}\f$. It
        just implements the analytical formula. */
    double density(Position bfr) const;

    /** This function generates a random position from the geometry by
        drawing a random point from the three-dimensional probability density
        \f$p({\bf{r}})\,{\text{d}}{\bf{r}} = \rho({\bf{r}})\, {\text{d}}{\bf{r}}\f$. We use a
        combination of the conditional distribution technique and the rejection technique. */
    Position generatePosition() const;

    /** This function returns the surface mass density along the X-axis, i.e.
        the integration of the mass density along the entire X-axis, \f[
        \Sigma_X = \int_{-\infty}^\infty \rho(x,0,0)\, {\text{d}}x.\f] This integral cannot be
        calculated analytically, but when averaged over all lines-of-sight in the equatorial plane,
        the contribution of the spiral arm perturbation cancels out, and we recover the
        X-axis surface density of the corresponding unperturbed model. */
    double SigmaX() const;

    /** This function returns the surface mass density along the Y-axis, i.e.
        the integration of the mass density along the entire Y-axis, \f[
        \Sigma_Y = \int_{-\infty}^\infty \rho(0,y,0)\, {\text{d}}y.\f] This integral cannot be
        calculated analytically, but when averaged over all lines-of-sight in the equatorial plane,
        the contribution of the spiral arm perturbation cancels out, and we recover the
        Y-axis surface density of the corresponding unperturbed model. */
    double SigmaY() const;

    /** This function returns the surface mass density along the Z-axis, i.e.
        the integration of the mass density along the entire Z-axis, \f[
        \Sigma_Z = \int_{-\infty}^\infty \rho(0,0,z)\, {\text{d}}z.\f] For the present decorator, this integral
        is not really well defined, as the logarithmic spiral perturbation winds ever stronger when we get closer
        to the Z-axis. We use the Z-axis surface density of the corresponding unperturbed model. */
    double SigmaZ() const;

private:
    /** This private function implements the analytical formula for the perturbation \f$\xi(R,\phi)\f$. */
    double perturbation(double R, double phi) const;

    //======================== Data Members ========================

private:
    // data members for discoverable attributes
    AxGeometry* _geometry;
    int _m;
    double _p;
    double _R0;
    double _phi0;
    double _w;
    int _N;

    // data members initialized during setup
    double _tanp;
    double _CN;
    double _c;
};

////////////////////////////////////////////////////////////////////

#endif // SPIRALSTRUCTUREGEOMETRYDECORATOR_HPP
