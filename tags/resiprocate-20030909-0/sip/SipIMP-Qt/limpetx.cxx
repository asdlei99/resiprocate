#include <qapplication.h>
#include "LimpetImpl.hxx"

int main ( int argc, char* argv[] )
{
	QApplication app( argc, argv );

        LimpetImpl limpet;
	app.setMainWidget (&limpet);

	limpet.show();

	int ret = app.exec();

	return ret;
}


/* ====================================================================
 * The Vovida Software License, Version 1.0 
 */
