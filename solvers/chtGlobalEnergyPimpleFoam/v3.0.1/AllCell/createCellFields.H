    Info<< "Reading cell field T\n" << endl;
    volScalarField TCell
    (
        IOobject
        (
            "T",
            runTime.timeName(),
            cellRegions,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        cellRegions
    );

    Info<< "Reading cell field h\n" << endl;
    volScalarField hCell
    (
        IOobject
        (
            "h",
            runTime.timeName(),
            cellRegions,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        cellRegions,
        dimensionedScalar("ent", dimTemperature*dimSpecificHeatCapacity, 0) 
    );

    Info<< "Reading cell field p\n" << endl;
    volScalarField pCell
    (
        IOobject
        (
            "p",
            runTime.timeName(),
            cellRegions,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        cellRegions
    );

    volScalarField rhoCell
    (
        IOobject
        (
            "rho",
            runTime.timeName(),
            cellRegions,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        cellRegions,
        dimensionedScalar("rh", dimDensity, 0)        
    );

    volScalarField CpCell
    (
        IOobject
        (
            "Cp",
            runTime.timeName(),
            cellRegions,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        cellRegions,
        dimensionedScalar("cp", dimSpecificHeatCapacity, 0)        
    );

    surfaceScalarField rhoPhiCell
    (
        IOobject
        (
            "rhoPhi",
            runTime.timeName(),
            cellRegions,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        cellRegions,
        dimensionedScalar("rhp", dimDensity*dimVelocity*dimArea, 0)
    );

    surfaceScalarField rhoCpPhiCell
    (
        IOobject
        (
            "rhoCpPhi",
            runTime.timeName(),
            cellRegions,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        cellRegions,
        dimensionedScalar("rhcp", dimVelocity*dimArea*dimDensity*dimSpecificHeatCapacity, 0)
    );

    volScalarField kappaCell
    (
        IOobject
        (
            "kappa",
            runTime.timeName(),
            cellRegions,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        cellRegions,
        dimensionedScalar("al", dimensionSet(1, 1, -3, -1, 0, 0, 0), 0)
    );

    volScalarField KCell
    (
        IOobject
        (
            "K",
            runTime.timeName(),
            cellRegions,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        cellRegions,
        dimensionedScalar("rK", dimVelocity*dimVelocity, 0)
    );

    volScalarField UgCell
    (
        IOobject
        (
            "Ug",
            runTime.timeName(),
            cellRegions,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        cellRegions,
        dimensionedScalar("rUg", dimVelocity*dimAcceleration, 0)
    );

    // Volumetric heat source
    volScalarField TsourceCell
    (
        IOobject
        (
            "Tsource",
            runTime.timeName(),
            cellRegions,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        cellRegions,
        dimensionedScalar("ts", dimensionSet(1, -1, -3, 0, 0, 0, 0), 0)
    );

    // Volume
    volScalarField VolCell
    (
        IOobject
        (
            "cellVolume",
            runTime.timeName(),
            cellRegions,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        cellRegions,
        dimensionedScalar("zero", dimVolume, 0)
    );
    VolCell.internalField() = cellRegions.V();


