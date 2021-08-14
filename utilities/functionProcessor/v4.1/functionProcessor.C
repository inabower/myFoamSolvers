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

    Info<< "Reading decomposeParDict\n" << endl;
    IOdictionary dict
    (
        IOobject
        (
            "decomposeParDict",
            runTime.system(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );

    // field of distribution of processor
    volScalarField cellDist
    (
        IOobject
        (
            "cellDist",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("cellDist", dimless, -1.0)
    );

    // list to decomposePar
    labelIOList cellDecomposition
    (
        IOobject
        (
            "cellDecomposition",
            mesh.time().constant(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh.V().size()
    );

    // number of processor is read from decomposeParDict
    label nProc;
    dict.readIfPresent("numberOfSubdomains", nProc);

    // count cells for each processors
    labelList nCell(nProc, 0);
    label err(0);

    // if -overwrite, cellDist is wrote in  directory
    if(!overwrite) runTime++;

    // execute your code in "codeEnd"
    runTime.functionObjects().end();

    // count the cells which are not distributed
    // and write into constant/cellDecomposition
    forAll(cellDist, i)
    {
        if(cellDist[i] < 0) err++;
        else
        {
            cellDecomposition[i] = round(cellDist[i]);
            nCell[cellDecomposition[i]]++;
        }
    }

    cellDist.write();
    cellDecomposition.write();

    forAll(nCell, i) Info << "processor" << i << " : " << nCell[i] << " cells" << endl;
    Info << "error : " << err << "cells" << endl;

    Info<< "\nEnd\n" << endl;

    return 0;
}


// ************************************************************************* //
