#include <vtkSmartPointer.h>
#include <vtkVariant.h>
#include <vtkMySQLDatabase.h>
#include <vtkSQLQuery.h>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkIOMySQL);

// url syntax:
// mysql://'[[username[':'password]'@']hostname[':'port]]'/'[dbname]
#define VTK_DB_URL "mysql://root:winter09@localhost/vtk"

int main(int, char *[])
{
	vtkSmartPointer<vtkMySQLDatabase> db =
		vtkSmartPointer<vtkMySQLDatabase>::Take(
			vtkMySQLDatabase::SafeDownCast(
			vtkMySQLDatabase::CreateFromURL( VTK_DB_URL )
			)
		);
	bool status = db->Open();
	std::cout << "Database open? " << status << std::endl;
	if(!status)
	{
		return EXIT_FAILURE;
	}

	vtkSmartPointer<vtkSQLQuery> query = vtkSmartPointer<vtkSQLQuery>::Take(db->GetQueryInstance());

	std::string queryStr;

	std::string createQuery( "select * from vtk.dumped_data where LABID = 'asds' and Frame = 0 order by Address LIMIT 0,10;");

	
	std::cout << createQuery << std::endl;
	query->SetQuery( createQuery.c_str() );
	query->Execute();

	for ( int col = 0; col < query->GetNumberOfFields(); ++ col )
	{
		if ( col > 0 )
		{
			cerr << ", ";
		}
		cerr << query->GetFieldName( col );
	}
	cerr << endl;
	while ( query->NextRow() )
	{
		for ( int field = 0; field < query->GetNumberOfFields(); ++ field )
		{
			if ( field > 0 )
			{
				cerr << ", ";
			}
			cerr << query->DataValue( field ).ToString().c_str();
		}
		cerr << endl;
	}

	system("PAUSE");

	return EXIT_SUCCESS;
}