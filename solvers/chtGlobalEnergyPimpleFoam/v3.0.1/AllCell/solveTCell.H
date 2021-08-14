    Info << nl << "Solving Temperature" << endl;

    if (finalIter)
    {
        cellRegions.data::add("finalIteration", true);
    }

    for (int nonOrth=0; nonOrth<=nOuterNonOrthCorr; nonOrth++)
    {

        fvScalarMatrix TEqn
        (
              fvm::ddt(rho*Cp, T)
            + fvc::ddt(rho, K)
            + fvm::div(rhoCpPhi, T)
            + fvc::div(rhoPhi, K)
            - fvm::laplacian(kappa, T) 
            - rho * Ug
            - TsourceCell
    //        + fvOptions(rhoCp, T)
        );

        T.correctBoundaryConditions();

        TEqn.relax(); 
        TEqn.solve(); 
    }

    T.max(Tmin);
    T.min(Tmax);

    h = T * Cp;

    if (finalIter)
    {
        cellRegions.data::remove("finalIteration");
    }
