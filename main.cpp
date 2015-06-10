#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <math.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

//	QFile file("D://Object_Templates//release//mog_objects_05-09-11.txt");
	QFile file("D://Test_files//visitor_objects_small.txt");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);

	QFile file2("D://Test_files//visitor_objects_NEW.txt");
	file2.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file2);

	QString line, xposstr, yposstr, rotastr, p3dobj;
	QStringList list;

	while (!in.atEnd())
	{
		line = in.readLine();
		list = line.split(";");
		qDebug() << list[0] << " " << list[1] << " " << list[2];

		xposstr = list[1];
		yposstr = list[2];
		rotastr = list[4];

		bool ok;
		float xPos = xposstr.toFloat(&ok);
		float yPos = yposstr.toFloat(&ok);
		float Rotation = rotastr.toFloat(&ok);
		p3dobj = "\"pmc\\pmc_somalia_obj\\pmc_house_small_01\"";

		// starting x,y
		float x_new = xPos;
		float y_new = yPos;
		
		// my stupid test
		if (Rotation < 0)
		{
			Rotation += 360;
		}
		
		// if its negative number, this goes nut. if its 45, 90, 270 etc positive number,
		// then this calculation makes the below sin/cos code work fine.
		// what the fuck is up with the negative values visitor export script gives?
		float Rota = (Rotation * 3.14159265 / 180);
		//float Rota = Rotation;

		// offset
		float offsetx = 7;
		float offsety = 7;
		float xtrans = 0;
		float ytrans = 0;

		//_newX = (_orgX * (cos _dir)) - (_orgY * (sin _dir));
		//_newY = (_orgX * (sin _dir)) + (_orgY * (cos _dir));

		xtrans = offsetx * cos (Rota) - offsety * sin (Rota);
		ytrans = offsetx * sin (Rota) + offsety * cos (Rota);

		x_new = xPos + xtrans;
		y_new = yPos + ytrans;

		out << p3dobj << ";" << x_new << ";" << y_new << ";" << list[3] << ";" << Rotation << ";\n";

		offsetx = -7;
		offsety = -7;

		xtrans = offsetx * cos (Rota) - offsety * sin (Rota);
		ytrans = offsetx * sin (Rota) + offsety * cos (Rota);

		x_new = xPos + xtrans;
		y_new = yPos + ytrans;

		out << p3dobj << ";" << x_new << ";" << y_new << ";" << list[3] << ";" << Rotation << ";\n";

		offsetx = 7;
		offsety = -7;

		xtrans = offsetx * cos (Rota) - offsety * sin (Rota);
		ytrans = offsetx * sin (Rota) + offsety * cos (Rota);

		x_new = xPos + xtrans;
		y_new = yPos + ytrans;

		out << p3dobj << ";" << x_new << ";" << y_new << ";" << list[3] << ";" << Rotation << ";\n";

		offsetx = -7;
		offsety = 7;

		xtrans = offsetx * cos (Rota) - offsety * sin (Rota);
		ytrans = offsetx * sin (Rota) + offsety * cos (Rota);

		x_new = xPos + xtrans;
		y_new = yPos + ytrans;

		out << p3dobj << ";" << x_new << ";" << y_new << ";" << list[3] << ";" << Rotation << ";\n";
	}
	file.close();
	file2.close();

	return 0;
}
