#================================
# Source files
#
# Here is where you can add the name of your local io classes.
#================================
SET ( Local_SRCS
vtkTracker.cxx
vtkTrackerTool.cxx
vtkTrackerBuffer.cxx
vtkPOLARISTracker.cxx
vtkFrameToTimeConverter.cxx
)


SET ( NDI_SRCS  ndicapi.c
                ndicapi_serial.c
                ndicapi_thread.c
                ndicapi_math.c )

SET ( NDI_HDRS ndicapi.h
               ndicapi_serial.h
               ndicapi_thread.h
               ndicapi_math.h )

SET (Tracker_SRCS  vtkTracker.cxx
                   vtkTrackerTool.cxx
                   vtkTrackerBuffer.cxx
                   vtkPOLARISTracker.cxx
                   vtkFrameToTimeConverter.cxx
                   ndicapi.c
                   ndicapi_serial.c
                   ndicapi_thread.c
                   ndicapi_math.c )

SET( Tracker_HDRS vtkTracker.h
                  vtkTrackerTool.h
                  vtkTrackerBuffer.h
                  vtkPOLARISTracker.h
                  vtkFrameToTimeConverter.h
                  ndicapi.h
                  ndicapi_serial.h
                  ndicapi_thread.h
                  ndicapi_math.h )


SET_SOURCE_FILES_PROPERTIES(
vtkTracker.cxx
vtkAbstractFunction.cxx
ABSTRACT
)

# --------------------------------------------------------------------------
# You probably do not need to modify anything below this line

# Create the vtkTracker C++ library
ADD_LIBRARY (vtkTracker ${Tracker_SRCS} ${Tracker_HDRS} )
ADD_LIBRARY (ndicapi ${NDI_SRCS} ${NDI_HDRS} )

TARGET_LINK_LIBRARIES(vtkTracker ndicapi)

if( IBIS_INSTALL_LIBS_AND_HEADERS )
    INSTALL_TARGETS(/lib vtkTracker ndicapi)
    INSTALL_FILES(/include .+h$)
endif( IBIS_INSTALL_LIBS_AND_HEADERS )
