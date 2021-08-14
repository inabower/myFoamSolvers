scalar DiNum = -GREAT;

forAll(solidRegions, i)
{
    //- Note: do not use setRegionSolidFields.H to avoid double registering Cp
    //#include "setRegionSolidFields.H"
    const solidThermo& thermo = thermos[i];

    tmp<volScalarField> magKappa;
    if (thermo.isotropic())
    {
        magKappa = thermo.kappa();
    }
    else
    {
        magKappa = mag(thermo.Kappa());
    }

    tmp<volScalarField> tcp = thermo.Cp();
    const volScalarField& cp = tcp();

    tmp<volScalarField> trho = thermo.rho();
    const volScalarField& rho = trho();

    DiNum = max
    (
        cellRegionDiffNo
        (
            solidRegions[i],
            runTime,
            rho*cp,
            magKappa()
        ),
        DiNum
    );
}

forAll(fluidRegions, i)
{
    //- Note: do not use setRegionSolidFields.H to avoid double registering Cp
    //#include "setRegionSolidFields.H"
    const fluidThermo& thermo = thermoFluid[i];

    tmp<volScalarField> magKappa;
    magKappa = thermo.kappa();

    tmp<volScalarField> tcp = thermo.Cp();
    const volScalarField& cp = tcp();

    tmp<volScalarField> trho = thermo.rho();
    const volScalarField& rho = trho();

    DiNum = max
    (
        cellRegionDiffNo
        (
            fluidRegions[i],
            runTime,
            rho*cp,
            magKappa()
        ),
        DiNum
    );
}
