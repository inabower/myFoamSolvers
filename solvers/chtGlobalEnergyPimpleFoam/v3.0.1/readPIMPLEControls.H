    const dictionary& pimple = cellRegions.solutionDict().subDict("PIMPLE");

    const int nOuterCorr =
        pimple.lookupOrDefault<int>("nOuterCorrectors", 1);

    const int nOuterNonOrthCorr =
        pimple.lookupOrDefault<int>("nOuterNonOrthogonalCorrectors", 0);

    const scalar Tmax = pimple.lookupOrDefault<scalar>("TMax", 1000);
    const scalar Tmin = pimple.lookupOrDefault<scalar>("TMin", 0);
    const scalar phimax = pimple.lookupOrDefault<scalar>("rhoPhiMax", 1e-3);
    const scalar phimin = pimple.lookupOrDefault<scalar>("rhoPhiMin", -1e-3);
    const scalar Umax = pimple.lookupOrDefault<scalar>("UMax", 10);
    const scalar Tstart = pimple.lookupOrDefault<scalar>("TStartTime", 0);

