    const wordList fluidNames(rp["fluid"]);

    PtrList<fvMesh> fluidRegions(fluidNames.size());

    PtrList<labelIOList> fluidFaceRegionAddressing(fluidNames.size());
    PtrList<labelList> fluidFaceMap(fluidNames.size());
    PtrList<scalarField> fluidFaceMask(fluidNames.size());
    PtrList<labelList> fluidInternalFaceMap(fluidNames.size());
    PtrList<scalarField> fluidInternalFaceMask(fluidNames.size());    
    PtrList<labelIOList> fluidCellMap(fluidNames.size());
    PtrList<labelIOList> fluidPatchesMap(fluidNames.size());

    forAll(fluidNames, i)
    {
        Info<< "Create fluid mesh for region " << fluidNames[i]
            << " for time = " << runTime.timeName() << nl << endl;

        fluidRegions.set
        (
            i,
            new fvMesh
            (
                IOobject
                (
                    fluidNames[i],
                    runTime.timeName(),
                    runTime,
                    IOobject::MUST_READ
                )
            )
        );

        // To connect the adresses inter "AllCell" and "Fluid"
        fluidFaceRegionAddressing.set
        (
            i,
            new labelIOList
            (
                IOobject
                (
                    "faceRegionAddressing",
                    fluidRegions[i].time().findInstance
		    (
			fluidRegions[i].meshDir(),
			"faces"
		    ),
                    polyMesh::meshSubDir,
                    fluidRegions[i],
                    IOobject::MUST_READ
                )
            )
        );

        // To number the adresses
        fluidFaceMap.set
        (
            i,
            new labelList
            (
                fluidFaceRegionAddressing[i].size()
            )
        );

        // degree of the faces
        fluidFaceMask.set
        (
            i,
            new scalarField
            (
                fluidFaceRegionAddressing[i].size()
            )
        );

        // Only internal Face
        fluidInternalFaceMap.set
        (
            i,
            new labelList
            (
                fluidRegions[i].nInternalFaces()
            )
        );

        fluidInternalFaceMask.set
        (
            i,
            new scalarField
            (
                fluidRegions[i].nInternalFaces()
            )
        );

        forAll(fluidFaceMap[i], j)
        {
            fluidFaceMap[i][j] = mag(fluidFaceRegionAddressing[i][j]) - 1;
            fluidFaceMask[i][j] = sign(fluidFaceRegionAddressing[i][j]);
        }

        forAll(fluidInternalFaceMap[i], j)
        {
            fluidInternalFaceMap[i][j] = mag(fluidFaceRegionAddressing[i][j]) - 1;
            fluidInternalFaceMask[i][j] = sign(fluidFaceRegionAddressing[i][j]);
        }

        // You don't use in this solver
        fluidCellMap.set
        (
            i,
            new labelIOList
            (
                IOobject
                (
                    "cellRegionAddressing",
                    fluidRegions[i].time().findInstance
		    (
			fluidRegions[i].meshDir(),
			"faces"
		    ),
                    polyMesh::meshSubDir,
                    fluidRegions[i],
                    IOobject::MUST_READ
                )
            )
        );

        fluidPatchesMap.set
        (
            i,
            new labelIOList
            (
                IOobject
                (
                    "boundaryRegionAddressing",
                    fluidRegions[i].time().findInstance
		    (
			fluidRegions[i].meshDir(),
			"faces"
		    ),
                    polyMesh::meshSubDir,
                    fluidRegions[i],
                    IOobject::MUST_READ
                )
            )
        );
    }


    PtrList<PtrList<labelList> > fluidPatchMap(fluidNames.size());
    PtrList<PtrList<scalarField> > fluidPatchMask(fluidNames.size());

    forAll(fluidNames, i)
    {
        fluidPatchMap.set
        (
            i,
            new PtrList<labelList>
            (
                fluidRegions[i].boundary().size()
            )
        );

        fluidPatchMask.set
        (
            i,
            new PtrList<scalarField>
            (
                fluidRegions[i].boundary().size()
            )
        );

        forAll(fluidPatchesMap[i], patchI)
        {
            if(fluidPatchesMap[i][patchI] >= 0)
            {

                fluidPatchMap[i].set
                (
                    patchI,
                    new labelList
                    (
                        fluidRegions[i].boundary()[patchI].size()
                    )
                );

                fluidPatchMask[i].set
                (
                    patchI,
                    new scalarField
                    (
                        fluidRegions[i].boundary()[patchI].size()
                    )
                );

                forAll(fluidPatchMap[i][patchI], j)
                {
                    fluidPatchMap[i][patchI][j] = mag(fluidFaceRegionAddressing[i][j]) - 1;
                    fluidPatchMask[i][patchI][j] = sign(fluidFaceRegionAddressing[i][j]);
                }
            }
        }

    }
