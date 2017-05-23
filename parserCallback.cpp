
#include <iostream>
#include <boost/filesystem.hpp>

extern "C" {
#include "parserCallback.h"
#include "parseCmdLine.h"
#include "moreString.h"
}





#if MODE != COMPRESS && MODE != DECOMPRESS
#error "This program must be compiled either for compression or decompression (set MODE as COMPRESS or DECOMPRESS)."
#endif

using namespace std;
int	parserCallback (char * key, char * value, void * data)
{
	cmdLineParserData_t * d = (cmdLineParserData_t *) data;
	int isValid = (int) false;

	if (key == NULL) {	//parametro: debe ser el path
		if (d->path == NULL && boost::filesystem::exists(value)) {  //es valido si no se habia recibido el path
			d->path = value;										//hasta ahora y el directorio existe
			isValid = (int) true;
		}
	}
#if MODE == COMPRESS
	else {  
		if (d->fidelity == 0.0 && strcmp(key , "fidelity") == 0) { 
			// solo me fijo si es valido el threshold si no se habia recibido hasta ahora
			d->fidelity = getFloat(value, &isValid);	//isValid queda con false si no era un float y viceversa
			if (bool(isValid) == true && (d->fidelity >= 100 || d->fidelity <= 0 ) )
				isValid = (int) false;	// si era un float pero no estaba en el rango permitido, igual es error
		}
	}
#endif // MODE == COMPRESS
	
	return isValid;
}
