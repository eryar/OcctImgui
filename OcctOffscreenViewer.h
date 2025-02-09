#pragma once

#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ViewCube.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
//! Sample offscreen viewer class.
class OcctOffscreenViewer {
 public:
  //! Return view instance.
  const Handle(V3d_View) & View() const { return myView; }

  //! Return AIS context.
  const Handle(AIS_InteractiveContext) & Context() const { return myContext; }

  //! Initialize offscreen viewer.
  //! @param[in] theWinSize view dimensions
  //! @return FALSE in case of initialization error
  bool InitOffscreenViewer(const Graphic3d_Vec2i& theWinSize) {
    try {
      OCC_CATCH_SIGNALS

      // create graphic driver
      Handle(Aspect_DisplayConnection) aDispConnection =
          new Aspect_DisplayConnection();
      Handle(OpenGl_GraphicDriver) aDriver =
          new OpenGl_GraphicDriver(aDispConnection, true);
      aDriver->ChangeOptions().ffpEnable = false;
      aDriver->ChangeOptions().swapInterval = 0;

      // create viewer and AIS context
      myViewer = new V3d_Viewer(aDriver);
      myContext = new AIS_InteractiveContext(myViewer);

      // light sources setup
      myViewer->SetDefaultLights();
      myViewer->SetLightOn();

      // create offscreen window
      const TCollection_AsciiString aWinName("OCCT offscreen window");
      Handle(Aspect_NeutralWindow) aWindow = new Aspect_NeutralWindow();
      aWindow->SetSize(theWinSize.x(), theWinSize.y());
      aWindow->SetVirtual(true);

      // create 3D view from offscreen window
      myView = new V3d_View(myViewer);
      myView->SetWindow(aWindow);

      // Display something
      gp_Pnt cubeCenter(0.0, 0.0, 0.0);
      TopoDS_Solid cube =
          BRepPrimAPI_MakeBox(cubeCenter, 1.0, 1.0, 1.0).Solid();

      // Create an AIS_Shape from the result
      Handle(AIS_Shape) aisShape = new AIS_Shape(cube);

      // Display the shape
      myContext->Display(aisShape, AIS_Shaded, 0, false);
    } catch (const Standard_Failure& theErr) {
      Message::SendFail() << "Offscreen Viewer creation FAILED:\n" << theErr;
      return false;
    }
    return true;
  }

  //! Print information about graphics context.
  void DumpGlInfo() {
    TColStd_IndexedDataMapOfStringString aGlCapsDict;
    myView->DiagnosticInformation(aGlCapsDict, Graphic3d_DiagnosticInfo_Basic);
    TCollection_AsciiString anInfo = "OpenGL info:\n";
    for (TColStd_IndexedDataMapOfStringString::Iterator aValueIter(aGlCapsDict);
         aValueIter.More(); aValueIter.Next()) {
      if (!aValueIter.Value().IsEmpty()) {
        anInfo += TCollection_AsciiString("  ") + aValueIter.Key() + ": " +
                  aValueIter.Value() + "\n";
      }
    }
    Message::SendInfo(anInfo);
  }

 private:
  Handle(V3d_Viewer) myViewer;
  Handle(V3d_View) myView;
  Handle(AIS_InteractiveContext) myContext;
};