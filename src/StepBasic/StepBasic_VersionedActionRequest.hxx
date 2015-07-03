// Created on: 1999-11-26
// Created by: Andrey BETENEV
// Copyright (c) 1999 Matra Datavision
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

#ifndef _StepBasic_VersionedActionRequest_HeaderFile
#define _StepBasic_VersionedActionRequest_HeaderFile

#include <Standard.hxx>
#include <Standard_Type.hxx>

#include <Standard_Boolean.hxx>
#include <MMgt_TShared.hxx>
class TCollection_HAsciiString;


class StepBasic_VersionedActionRequest;
DEFINE_STANDARD_HANDLE(StepBasic_VersionedActionRequest, MMgt_TShared)

//! Representation of STEP entity VersionedActionRequest
class StepBasic_VersionedActionRequest : public MMgt_TShared
{

public:

  
  //! Empty constructor
  Standard_EXPORT StepBasic_VersionedActionRequest();
  
  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init (const Handle(TCollection_HAsciiString)& aId, const Handle(TCollection_HAsciiString)& aVersion, const Handle(TCollection_HAsciiString)& aPurpose, const Standard_Boolean hasDescription, const Handle(TCollection_HAsciiString)& aDescription);
  
  //! Returns field Id
  Standard_EXPORT Handle(TCollection_HAsciiString) Id() const;
  
  //! Set field Id
  Standard_EXPORT void SetId (const Handle(TCollection_HAsciiString)& Id);
  
  //! Returns field Version
  Standard_EXPORT Handle(TCollection_HAsciiString) Version() const;
  
  //! Set field Version
  Standard_EXPORT void SetVersion (const Handle(TCollection_HAsciiString)& Version);
  
  //! Returns field Purpose
  Standard_EXPORT Handle(TCollection_HAsciiString) Purpose() const;
  
  //! Set field Purpose
  Standard_EXPORT void SetPurpose (const Handle(TCollection_HAsciiString)& Purpose);
  
  //! Returns field Description
  Standard_EXPORT Handle(TCollection_HAsciiString) Description() const;
  
  //! Set field Description
  Standard_EXPORT void SetDescription (const Handle(TCollection_HAsciiString)& Description);
  
  //! Returns True if optional field Description is defined
  Standard_EXPORT Standard_Boolean HasDescription() const;




  DEFINE_STANDARD_RTTI(StepBasic_VersionedActionRequest,MMgt_TShared)

protected:




private:


  Handle(TCollection_HAsciiString) theId;
  Handle(TCollection_HAsciiString) theVersion;
  Handle(TCollection_HAsciiString) thePurpose;
  Handle(TCollection_HAsciiString) theDescription;
  Standard_Boolean defDescription;


};







#endif // _StepBasic_VersionedActionRequest_HeaderFile