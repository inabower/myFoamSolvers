/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2017 OpenFOAM Foundation
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

Application
    manualDecomposition

Description
    This is a utility to make decomposition as you want.
    Processor Nomber is decided as position (x y z) of each cells.
    Result of decomposition is saved in "case/const/cellDecomposition" and "latestTime/cellDist".
    You can confirm with paraFoam.

    And you have to set "system/decomposeParDict" as following.

    numberOfSubdomains  8;
    method              manual;
    manualCoeffs
    {
        dataFile        "cellDecomposition";
    }

    Then after "decomposePar", you can get decomposition as you want.
    
   -additional option-
    You can use cellSet data if you want.
    (example)
       If mesh is created by "mergeMeshes" and is connected with "cyclicAMI",
       Each meshes are automaticly set in "cellSet" after "checkMesh".
       These names are region0, region1, ...

\*---------------------------------------------------------------------------*/
#include "fvCFD.H"
#include "topoSet.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    // const label nRegion = 2; // You have to modify before compiling
    const label nProc = 8; // You have to modify before compiling

    #include "setRootCase.H"
    #include "createTime.H"

    #include "createMeshField.H"
    //#include "createCellSet.H" // If reading cellSet

    List<label> n(nProc, 0);
    label err = 0;

    // Distribute all cell
    forAll(dec, cellI)
    {
        const vector& C = mesh.C()[cellI];
        const scalar& x = C[0];
        const scalar& y = C[1];
        const scalar& z = C[2];

        label r = -1;

        #include "setNumber.H"

        dec[cellI] = r;
        dist[cellI] = r;

        if(r != -1) n[r]++;
    }


    // Distribute all cell by cellSets
    /*
    forAll(sets, regionI)
    {
        forAllConstIter(labelHashSet, sets[regionI], iter)
        {
            const label& cellI = iter.key();

            const vector& C = mesh.C()[cellI];
            const scalar& x = C[0];
            const scalar& y = C[1];
            const scalar& z = C[2];

            label r = -1;

            #include "setNumber.H"

            dec[cellI] = r;
            dist[cellI] = r;

            if(r != -1) n[r]++;
        }
    }
    */

    // Check cells which are not distributed
    forAll(dec, i)
    {
        if(dec[i] == -1) err++;
    }

    dec.write();
    dist.write();

    forAll(n, i) Info << "region " << i << " : " << n[i] << " cells" << endl; 
    Info << "error : " << err << "cells" << endl;

    Info<< nl << "End" << endl;

    return 0;
}


// ************************************************************************* //
