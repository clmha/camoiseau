/*DCF Utilies for the Design rule for Camera File system (DCF)
 * 
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
