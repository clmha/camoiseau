/*DCF Utilies for the Design rule for Camera File system (DCF)
 * 
 */

/*
 *  $Id: dcf.cpp 3 2017-07-08 22:26:34Z clement $
 */

/* TODO Check Capture Count Against Maximum of Captures Supported in DCF
 * 
 */

#include "dcf.h"

const unsigned long maxDcfFilesCountPerFolder = 9999;

void getDcfDirectoryPath(unsigned long iCapture, char *dirPath) {
  //GETDCFDIRECTORY Gives the directory of a capture

  sprintf(dirPath, "/DCIM/%03lu_ARDU", iCapture/maxDcfFilesCountPerFolder+100);
}

void getDcfFileBaseName(unsigned long iCapture, char *fileBaseName) {
  //GETDCFID Gives the capture DCF capture file base name from a capture count

  sprintf(fileBaseName, "DSCF%04lu", iCapture%maxDcfFilesCountPerFolder+1);
}

void getDcfFilePath(unsigned long iCapture, const char *ext, char *path) {
  //GETDCFFILEPATH Gives a valid DCF file path from a capture number
  
  char fileBaseName[DCF_FILEBASENAME_LENGTH],
    dirPath[DCF_DIRPATH_LENGTH];

  getDcfDirectoryPath(iCapture, dirPath);
  getDcfFileBaseName(iCapture, fileBaseName);
  sprintf(path, "%s/%s%s", dirPath, fileBaseName, ext);
}

