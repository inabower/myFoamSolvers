/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
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
    reverseSurface

Version of OpenFOAM
    4.1

Description
    This is utility to reverse all faces of STL.
    This is made on "surfaceOrient"
    "reverseSurface old.stl new.stl 0" -> do nothing (precision is change).
    "reverseSurface old.stl new.stl 1" -> flip all surfaces (precision is change).

    example
       STL file made from SALOME, to make one region with interfaces and surfaces.
       But if one or more interface is reversed, you can not snappyHexMesh nor cfMesh.
       You have to change the directions of faces.

\*---------------------------------------------------------------------------*/

#include "argList.H"
#include "triSurfaceSearch.H"
#include "orientedSurface.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


int main(int argc, char *argv[])
{
    argList::validArgs.append("surfaceFile");
    argList::validArgs.append("output surfaceFile");
    argList::validArgs.append("if flip : 1, if no : 0");

    argList args(argc, argv);

    const fileName surfFileName = args[1];
    const fileName outFileName  = args[2];
    const label flip  = args.argRead<label>(3);

    Info<< "Making a new STL named " << outFileName << " from " << surfFileName << nl << endl;

    // Load surface
    triSurface s(surfFileName);

    if ( flip == 1 )
    {
        label fCp = 0;

        forAll (s, faceI)
        {
            labelledTri& tri=s[faceI];

            label tmp = tri[0];

            tri[0] = tri[1];
            tri[1] = tmp;

            fCp++;
        }

        Info<< fCp << "faces was flipped" << endl;
        Info<< "Writing new surface to " << outFileName << endl;
    }
    else
    {
        Info << "no flipped" << endl;
        Info<< "Writing new surface to " << outFileName << endl;
    }

    s.write(outFileName);

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
