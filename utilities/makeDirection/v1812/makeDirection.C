/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.
    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.
    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.
Version
    OpenFOAM4.1
Description
    Decompose cells to each processor as you want.
    You have to modify system/cotrolDict/functions.
    If not, this is a utility just to read 0/cellDist and to write 
    constant/cellDecomposition. 
\*---------------------------------------------------------------------------*/

#include "argList.H"
#include "Time.H"
#include "fvMesh.H"
#include "argList.H"
#include "timeSelector.H"
#include "vectorIOField.H"

#include "topoSetSource.H"
#include "cellSet.H"
#include "faceSet.H"
#include "volFields.H"
#include "functionObject.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "addOverwriteOption.H"
    #include "addRegionOption.H"
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createNamedMesh.H"

    const bool overwrite = args.optionFound("overwrite");

    // list to x,y,z
    vectorIOField radialDirection
    (
        IOobject
        (
            "radialDirection",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh.V().size()
    );
    
    vectorIOField angularDirection
    (
        IOobject
        (
            "angularDirection",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh.V().size()
    );
    
    vectorIOField heightDirection
    (
        IOobject
        (
            "heightDirection",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh.V().size()
    );
    
    volVectorField radialVolDirection
    (
        IOobject
        (
            "radialVolDirection",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector("r", dimless, Zero)
    );
    
    volVectorField angularVolDirection
    (
        IOobject
        (
            "angularVolDirection",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector("r", dimless, Zero)
    );
    
    volVectorField heightVolDirection
    (
        IOobject
        (
            "heightVolDirection",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector("r", dimless, Zero)
    );

    // if -overwrite, cellDist is wrote in  directory
    if(!overwrite) runTime++;

    // execute your code in "codeEnd"
    runTime.functionObjects().end();

    radialVolDirection.primitiveFieldRef() = radialDirection;
    angularVolDirection.primitiveFieldRef() = angularDirection;
    heightVolDirection.primitiveFieldRef() = heightDirection;

    radialDirection.write();
    angularDirection.write();
    heightDirection.write();
    
    radialVolDirection.write();
    angularVolDirection.write();
    heightVolDirection.write();

    Info<< "\nEnd\n" << endl;

    return 0;
}


// ************************************************************************* //
