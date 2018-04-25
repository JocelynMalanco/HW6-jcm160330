/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu

 * Modifications: Jocelyn Malanco
 * Email:  jcm160330@utdallas.edu
 * Class: CS 3377
 */

#include <iostream>
#include <sstream>
#include <cstring>
#include <stdint.h>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <string>
#include "cdk.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 18
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

const int maxRecordStringLength = 25;

class BinaryFileRecord{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};


class BinaryFileHeader{
public:

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);


  //************PHASE 3*************************** //
  
   //create BinaryFileHeader object
   BinaryFileHeader *myHeader = new BinaryFileHeader();
   //create BinaryFileRecord ojbect
   BinaryFileRecord *myRecord = new BinaryFileRecord();

   //Open file for reading
   ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

   //check if file is opened
   if(!binInfile){
     return -1;
   }

   //read the binary file header
   binInfile.read((char *)myHeader, sizeof(BinaryFileHeader));
   
    //Build a string with the values in using string stream and place that string into the setCDkMatrixCell() function but remeber to use .c_str();

   //do Magic
   stringstream magic;
   string mg = "Magic: 0x";
   magic << mg << hex << myHeader->magicNumber;
   const char *magicString = magic.str().c_str();
   setCDKMatrixCell(myMatrix, 1, 1, magicString);

   //do version number
   stringstream version;
   string vrs = "Version: ";
   version << vrs << myHeader->versionNumber;
   const char *versionString = version.str().c_str();
   setCDKMatrixCell(myMatrix, 1, 2, versionString);
 
  
   //do number of records
   stringstream records;
   string rec = "NumRecords: ";
   records << rec << myHeader->numRecords;
   const char *recordsString = records.str().c_str();
   setCDKMatrixCell(myMatrix, 1, 3, recordsString);
   
   // binInfile.close();

   //******PHASE 4********//
   
  string stringLength = "strlen: ";
  int stringL;
  stringstream length;
  stringstream name; 

 //i=row
 //j = column
 for(int i=2 ; i<=5 ; i++){
    for(int j=2 ; j>1 ; j--){
      length.str("");
      name.str("");
      //read record object
      binInfile.read((char *)myRecord, sizeof(BinaryFileRecord));
     
      //get name and output
      name << myRecord->stringBuffer;
      const char *nameString = name.str().c_str();
      setCDKMatrixCell(myMatrix, i, j, nameString);
     
      //get length of string
      stringL = strlen(nameString);
      
      //go to left column
      j--;

      //output strlen
      length << stringLength << stringL;
      const char *lengthString = length.str().c_str();
      setCDKMatrixCell(myMatrix, i, j, lengthString);
    }
 } 
   
   drawCDKMatrix(myMatrix, true);
   binInfile.close();


  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
