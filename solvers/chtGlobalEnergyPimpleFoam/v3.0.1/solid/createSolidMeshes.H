    const wordList solidsNames(rp["solid"]);

    PtrList<fvMesh> solidRegions(solidsNames.size());

    PtrList<labelIOList> solidFaceRegionAddressing(solidsNames.size());
    PtrList<labelList> solidFaceMap(solidsNames.size());
    PtrList<labelList> solidFaceMask(solidsNames.size());
    PtrList<labelIOList> solidCellMap(solidsNames.size());
    PtrList<labelIOList> solidPatchesMap(solidsNames.size());

    forAll(solidsNames, i)
    {
        Info<< "Create solid mesh for region " << solidsNames[i]
            << " for time = " << runTime.timeName() << nl << endl;

        solidRegions.set
        (
            i,
            new fvMesh
            (
                IOobject
                (
                    solidsNames[i],
                    runTime.timeName(),
                    runTime,
                    IOobject::MUST_READ
                )
            )
        );

        solidFaceRegionAddressing.set
        (
            i,
            new labelIOList
            (
                IOobject
                (
                    "faceRegionAddressing",
                    solidRegions[i].time().findInstance
		    (
			solidRegions[i].meshDir(),
			"faces"
		    ),
                    polyMesh::meshSubDir,
                    solidRegions[i],
                    IOobject::MUST_READ
                )
            )
        );

        solidFaceMap.set
        (
            i,
            new labelList
            (
                solidFaceRegionAddressing[i].size()
            )
        );
        solidFaceMask.set
        (
            i,
            new labelList
            (
                solidFaceRegionAddressing[i].size()
            )
        );

        forAll(solidFaceMap[i], j)
        {
            solidFaceMap[i][j] = mag(solidFaceRegionAddressing[i][j]) - 1;
            solidFaceMask[i][j] = sign(solidFaceRegionAddressing[i][j]);
        }

        solidCellMap.set
        (
            i,
            new labelIOList
            (
                IOobject
                (
                    "cellRegionAddressing",
                    solidRegions[i].time().findInstance
		    (
			solidRegions[i].meshDir(),
			"faces"
		    ),
                    polyMesh::meshSubDir,
                    solidRegions[i],
                    IOobject::MUST_READ
                )
            )
        );

        solidPatchesMap.set
        (
            i,
            new labelIOList
            (
                IOobject
                (
                    "boundaryRegionAddressing",
                    solidRegions[i].time().findInstance
		    (
			solidRegions[i].meshDir(),
			"faces"
		    ),
                    polyMesh::meshSubDir,
                    solidRegions[i],
                    IOobject::MUST_READ
                )
            )
        );

    }


    PtrList<PtrList<labelList> > solidPatchMap(solidsNames.size());
    PtrList<PtrList<scalarField> > solidPatchMask(solidsNames.size());

    forAll(solidsNames, i)
    {
        solidPatchMap.set
        (
            i,
            new PtrList<labelList>
            (
                solidRegions[i].boundary().size()
            )
        );

        solidPatchMask.set
        (
            i,
            new PtrList<scalarField>
            (
                solidRegions[i].boundary().size()
            )
        );

        forAll(solidPatchesMap[i], patchI)
        {
            if(solidPatchesMap[i][patchI] >= 0)
            {

                solidPatchMap[i].set
                (
                    patchI,
                    new labelList
                    (
                        solidRegions[i].boundary()[patchI].size()
                    )
                );

                solidPatchMask[i].set
                (
                    patchI,
                    new scalarField
                    (
                        solidRegions[i].boundary()[patchI].size()
                    )
                );

                forAll(solidPatchMap[i][patchI], j)
                {
                    solidPatchMap[i][patchI][j] = mag(solidFaceRegionAddressing[i][j]) - 1;
                    solidPatchMask[i][patchI][j] = sign(solidFaceRegionAddressing[i][j]);
                }
            }
        }

    }
