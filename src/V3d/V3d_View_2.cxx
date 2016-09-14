// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

/***********************************************************************
     FONCTION :
     ----------
        Classe V3d_View_2.cxx :
     HISTORIQUE DES MODIFICATIONS   :
     --------------------------------
      00-09-92 : GG  ; Creation.
      24-12-97 : FMN ; Suppression de GEOMLITE
      23-11-00 : GG  ; Add IsActiveLight() and IsActivePlane() methods
************************************************************************/
/*
 * Includes
 */

#include <Aspect_GradientBackground.hxx>
#include <Aspect_Grid.hxx>
#include <Aspect_Window.hxx>
#include <Bnd_Box.hxx>
#include <gp_Ax3.hxx>
#include <gp_Dir.hxx>
#include <Graphic3d_Group.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <Graphic3d_Structure.hxx>
#include <Graphic3d_TextureEnv.hxx>
#include <Graphic3d_Vector.hxx>
#include <Quantity_Color.hxx>
#include <Standard_MultiplyDefined.hxx>
#include <Standard_TypeMismatch.hxx>
#include <V3d.hxx>
#include <V3d_BadValue.hxx>
#include <V3d_Light.hxx>
#include <V3d_UnMapped.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>

//=============================================================================
//function : SetLightOn
//purpose  :
//=============================================================================
void V3d_View::SetLightOn (const Handle(V3d_Light)& theLight)
{
  if (!MyActiveLights.Contains (theLight))
  {
    V3d_BadValue_Raise_if (MyActiveLights.Extent() >= LightLimit(),
                           "V3d_View::SetLightOn, "
                           "too many lights");
    MyActiveLights.Append (theLight);
    UpdateLights();
  }
}

//=============================================================================
//function : SetLightOff
//purpose  :
//=============================================================================
void V3d_View::SetLightOff (const Handle(V3d_Light)& theLight)
{
  Standard_TypeMismatch_Raise_if (MyViewer->IsGlobalLight (theLight),
                                  "V3d_View::SetLightOff, "
                                  "the light is global");
  MyActiveLights.Remove (theLight);
  UpdateLights();
}

//=============================================================================
//function : IsActiveLight
//purpose  :
//=============================================================================
Standard_Boolean V3d_View::IsActiveLight (const Handle(V3d_Light)& theLight) const
{
  if (theLight.IsNull())
  {
    return Standard_False;
  }
  return MyActiveLights.Contains(theLight);
}

//=============================================================================
//function : SetLightOn
//purpose  :
//=============================================================================
void V3d_View::SetLightOn()
{
  for (MyViewer->InitDefinedLights(); MyViewer->MoreDefinedLights(); MyViewer->NextDefinedLights())
  {
    if (!MyActiveLights.Contains (MyViewer->DefinedLight()))
    {
      MyActiveLights.Append (MyViewer->DefinedLight());
    }
  }
  UpdateLights();
}

//=============================================================================
//function : SetLightOff
//purpose  :
//=============================================================================
void V3d_View::SetLightOff()
{
  InitActiveLights();
  while(MoreActiveLights())
  {
    if (!MyViewer->IsGlobalLight (ActiveLight()))
    {
      MyActiveLights.Remove (ActiveLight());
    }
    else
    {
      NextActiveLights();
    }
  }
  UpdateLights();
}

//=============================================================================
//function : InitActiveLights
//purpose  :
//=============================================================================
void V3d_View::InitActiveLights()
{
  myActiveLightsIterator.Initialize(MyActiveLights);
}

//=============================================================================
//function : MoreActiveLights
//purpose  :
//=============================================================================
Standard_Boolean V3d_View::MoreActiveLights() const
{
  return myActiveLightsIterator.More();
}

//=============================================================================
//function : NextActiveLights
//purpose  :
//=============================================================================
void V3d_View::NextActiveLights()
{
  myActiveLightsIterator.Next();
}

//=============================================================================
//function : ActiveLight
//purpose  :
//=============================================================================
Handle(V3d_Light) V3d_View::ActiveLight() const
{
  return (Handle(V3d_Light)&)(myActiveLightsIterator.Value());
}

//=============================================================================
//function : IfMoreLights
//purpose  :
//=============================================================================
Standard_Boolean V3d_View::IfMoreLights() const
{
  return MyActiveLights.Extent() < LightLimit();
}

//=======================================================================
//function : LightLimit
//purpose  :
//=======================================================================
Standard_Integer V3d_View::LightLimit() const
{
  return Viewer()->Driver()->InquireLightLimit();
}

//=======================================================================
//function : AddClipPlane
//purpose  :
//=======================================================================
void V3d_View::AddClipPlane (const Handle(Graphic3d_ClipPlane)& thePlane)
{
  Handle(Graphic3d_SequenceOfHClipPlane) aSeqOfPlanes = ClipPlanes();
  if (aSeqOfPlanes.IsNull())
  {
    aSeqOfPlanes = new Graphic3d_SequenceOfHClipPlane();
  }

  aSeqOfPlanes->Append (thePlane);
  SetClipPlanes (aSeqOfPlanes);
}

//=======================================================================
//function : RemoveClipPlane
//purpose  :
//=======================================================================
void V3d_View::RemoveClipPlane (const Handle(Graphic3d_ClipPlane)& thePlane)
{
  Handle(Graphic3d_SequenceOfHClipPlane) aSeqOfPlanes = ClipPlanes();
  if (aSeqOfPlanes.IsNull())
  {
    return;
  }

  for (Graphic3d_SequenceOfHClipPlane::Iterator aPlaneIt(*aSeqOfPlanes); aPlaneIt.More(); aPlaneIt.Next())
  {
    const Handle(Graphic3d_ClipPlane)& aPlane = aPlaneIt.Value();
    if (aPlane != thePlane)
      continue;

    aSeqOfPlanes->Remove (aPlaneIt);
    SetClipPlanes (aSeqOfPlanes);
    return;
  }
}

//=======================================================================
//function : SetClipPlanes
//purpose  :
//=======================================================================
void V3d_View::SetClipPlanes (const Handle(Graphic3d_SequenceOfHClipPlane)& thePlanes)
{
  myView->SetClipPlanes (thePlanes);
}

//=======================================================================
//function : ClipPlanes
//purpose  :
//=======================================================================
const Handle(Graphic3d_SequenceOfHClipPlane)& V3d_View::ClipPlanes() const
{
  return myView->ClipPlanes();
}

//=======================================================================
//function : PlaneLimit
//purpose  :
//=======================================================================
Standard_Integer V3d_View::PlaneLimit() const
{
  return Viewer()->Driver()->InquirePlaneLimit();
}
