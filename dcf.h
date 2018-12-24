/*DCF Utilies for the Design rule for Camera File system (DCF)
 * 
 */

/*
 *  $Id: dcf.h 3 2017-07-08 22:26:34Z clement $
 */

#ifndef _DCF_
#define _DCF_

#include <stdio.h>

#define DCF_FILEPATH_LENGTH 28
#define DCF_FILEBASENAME_LENGTH 9
#define DCF_DIRPATH_LENGTH 15

void getDcfDirectoryPath(unsigned long iCapture, char *dirPath);
void getDcfFileBaseName(unsigned long iCapture, char *fileBaseName);
void getDcfFilePath(unsigned long iCapture, const char *ext, char *path);

#endif
